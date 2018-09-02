//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include "framework.h"


using namespace Windows::UI::Core;
using namespace Windows::Foundation;
using namespace Microsoft::WRL;
using namespace Windows::UI::ViewManagement;
using namespace Windows::Graphics::Display;
using namespace D2D1;

SampleOverlay::SampleOverlay() :
    m_drawOverlay(true)
{
}

void SampleOverlay::Initialize(
    _In_ ID2D1Device*         d2dDevice,
    _In_ ID2D1DeviceContext*  d2dContext,
    _In_ IWICImagingFactory*  wicFactory,
    _In_ IDWriteFactory*      dwriteFactory,
    _In_ Platform::String^    caption
    )
{
    m_wicFactory = wicFactory;
    m_dwriteFactory = dwriteFactory;
    m_sampleName = caption;
    m_d2dDevice = d2dDevice;
    m_d2dContext = d2dContext;
    m_padding = 3.0f;
    m_textVerticalOffset = 5.0f;
    m_logoSize = D2D1::SizeF(0.0f, 0.0f);
    m_overlayWidth = 0.0f;

    ComPtr<ID2D1Factory> factory;
    d2dDevice->GetFactory(&factory);

    ::win::throw_if_failed(
        factory.As(&m_d2dFactory)
        );

    ResetDirectXResources();
}

void SampleOverlay::ResetDirectXResources()
{
    ::win::throw_if_failed(
        m_d2dContext->CreateSolidColorBrush(ColorF(ColorF::White), &m_whiteBrush)
        );

    ComPtr<IWICBitmapDecoder> wicBitmapDecoder;
    ::win::throw_if_failed(
        m_wicFactory->CreateDecoderFromFilename(
            L"ca2-5c-49.png",
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnDemand,
            &wicBitmapDecoder
            )
        );

    ComPtr<IWICBitmapFrameDecode> wicBitmapFrame;
    ::win::throw_if_failed(
        wicBitmapDecoder->GetFrame(0, &wicBitmapFrame)
        );

    ComPtr<IWICFormatConverter> wicFormatConverter;
    ::win::throw_if_failed(
        m_wicFactory->CreateFormatConverter(&wicFormatConverter)
        );

    ::win::throw_if_failed(
        wicFormatConverter->Initialize(
            wicBitmapFrame.Get(),
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.0,
            WICBitmapPaletteTypeCustom  // the BGRA format has no palette so this value is ignored
            )
        );

    double dpiX = 96.0f;
    double dpiY = 96.0f;
    ::win::throw_if_failed(
        wicFormatConverter->GetResolution(&dpiX, &dpiY)
        );

    ::win::throw_if_failed(
        m_d2dContext->CreateBitmapFromWicBitmap(
            wicFormatConverter.Get(),
            BitmapProperties(
                PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
                static_cast<float>(dpiX),
                static_cast<float>(dpiY)
                ),
            &m_logoBitmap
            )
        );

    m_logoSize = m_logoBitmap->GetSize();

    ComPtr<IDWriteTextFormat> nameTextFormat;
    ::win::throw_if_failed(
        m_dwriteFactory->CreateTextFormat(
            L"Segoe UI",
            nullptr,
            DWRITE_FONT_WEIGHT_LIGHT,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            36.0f,
            L"en-US",
            &nameTextFormat
            )
        );

    ::win::throw_if_failed(
        nameTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING)
        );

    ::win::throw_if_failed(
        nameTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR)
        );

    ::win::throw_if_failed(
        m_dwriteFactory->CreateTextLayout(
            m_sampleName->Data(),
            m_sampleName->Length(),
            nameTextFormat.Get(),
            4096.0f,
            4096.0f,
            &m_textLayout
            )
        );

    DWRITE_TEXT_METRICS metrics = {0};
    ::win::throw_if_failed(
        m_textLayout->GetMetrics(&metrics)
        );

    m_overlayWidth = m_padding * 3.0f + m_logoSize.width + metrics.width;

    ::win::throw_if_failed(
        m_d2dFactory->CreateDrawingStateBlock(&m_stateBlock)
        );

    UpdateForWindowSizeChange();
}

void SampleOverlay::UpdateForWindowSizeChange()
{
    if (CoreWindow::GetForCurrentThread()->Bounds.Width < m_overlayWidth)
    {
        m_drawOverlay = false;
    }
    else
    {
        m_drawOverlay = true;
    }
}

void SampleOverlay::Render()
{
    if (m_drawOverlay)
    {
        m_d2dContext->SaveDrawingState(m_stateBlock.Get());

        //m_d2dContext->BeginDraw();
        m_d2dContext->SetTransform(D2D1::Matrix3x2F::Identity());
        m_d2dContext->DrawBitmap(
            m_logoBitmap.Get(),
            D2D1::RectF(m_padding, 0.0f, m_logoSize.width + m_padding, m_logoSize.height)
            );

        m_d2dContext->DrawTextLayout(
            Point2F(m_logoSize.width + 2.0f * m_padding, m_textVerticalOffset),
            m_textLayout.Get(),
            m_whiteBrush.Get()
            );

        // We ignore D2DERR_RECREATE_TARGET here. This error indicates that the device
        // is lost. It will be handled during the next call to Present.
        //HRESULT hr = m_d2dContext->EndDraw();
        if (hr != D2DERR_RECREATE_TARGET)
        {
            ::win::throw_if_failed(hr);
        }

        m_d2dContext->RestoreDrawingState(m_stateBlock.Get());
    }
}

float SampleOverlay::GetTitleHeightInDips()
{
    return m_logoSize.height;
}
