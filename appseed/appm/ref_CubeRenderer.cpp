CubeRenderer::CubeRenderer() :
    m_loadingComplete(false),
    m_indexCount(0)
{
}

CubeRenderer::~CubeRenderer()
{
}

void CubeRenderer::CreateDeviceResources()
{
    DirectXBase::CreateDeviceResources();

/*    auto loadVSTask = DX::ReadDataAsync("SimpleVertexShader.cso");
    auto loadPSTask = DX::ReadDataAsync("SimplePixelShader.cso");

    auto createVSTask = loadVSTask.then([this](DX::ByteArray ba) {
        auto bytecodeVS = ba.data;
        ::win::throw_if_failed(
            m_d3dDevice->CreateVertexShader(
                bytecodeVS->Data,
                bytecodeVS->Length,
                nullptr,
                &m_vertexShader
                )
            );

        const D3D11_INPUT_ELEMENT_DESC vertexDesc[] = 
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };

        ::win::throw_if_failed(
            m_d3dDevice->CreateInputLayout(
                vertexDesc,
                ARRAYSIZE(vertexDesc),
                bytecodeVS->Data,
                bytecodeVS->Length,
                &m_inputLayout
                )
            );
    });

    auto createPSTask = loadPSTask.then([this](DX::ByteArray ba) {
        auto bytecodePS = ba.data;
        ::win::throw_if_failed(
            m_d3dDevice->CreatePixelShader(
                bytecodePS->Data,
                bytecodePS->Length,
                nullptr,
                &m_pixelShader
                )
            );

        ::win::throw_if_failed(
            m_d3dDevice->CreateBuffer(
                &CD3D11_BUFFER_DESC(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER),
                nullptr,
                &m_constantBuffer
                )
            );
    });

    auto createCubeTask = (createPSTask && createVSTask).then([this] () {
        VertexPositionColor cubeVertices[] = 
        {
            {XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
            {XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
            {XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
            {XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
            {XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
            {XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
            {XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
            {XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
        };

        D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
        vertexBufferData.pSysMem = cubeVertices;
        vertexBufferData.SysMemPitch = 0;
        vertexBufferData.SysMemSlicePitch = 0;
        ::win::throw_if_failed(
            m_d3dDevice->CreateBuffer(
                &CD3D11_BUFFER_DESC(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER),
                &vertexBufferData,
                &m_vertexBuffer
                )
            );

        unsigned short cubeIndices[] = 
        {
            0,2,1, // -x
            1,2,3,

            4,5,6, // +x
            5,7,6,

            0,1,5, // -y
            0,5,4,

            2,6,7, // +y
            2,7,3,

            0,4,6, // -z
            0,6,2,

            1,3,7, // +z
            1,7,5,
        };

        m_indexCount = ARRAYSIZE(cubeIndices);

        D3D11_SUBRESOURCE_DATA indexBufferData = {0};
        indexBufferData.pSysMem = cubeIndices;
        indexBufferData.SysMemPitch = 0;
        indexBufferData.SysMemSlicePitch = 0;
        ::win::throw_if_failed(
            m_d3dDevice->CreateBuffer(
                &CD3D11_BUFFER_DESC(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER),
                &indexBufferData,
                &m_indexBuffer
                )
            );
    });

    createCubeTask.then([this] () {
        m_loadingComplete = true;
    });*/
}

void CubeRenderer::CreateWindowSizeDependentResources()
{
    DirectXBase::CreateWindowSizeDependentResources();

    float aspectRatio = m_windowBounds.Width / m_windowBounds.Height;
    float fovAngleY = 70.0f * XM_PI / 180.0f;
    if (aspectRatio < 1.0f)
    {
        fovAngleY /= aspectRatio;
    }

    m_constantBufferData.projection = XMMatrixTranspose(XMMatrixPerspectiveFovRH(
        fovAngleY,
        aspectRatio,
        0.01f,
        100.0f
        ));
}

void CubeRenderer::Update(float timeTotal, float timeDelta)
{
    XMVECTOR eye = XMVectorSet(0.0f, 0.7f, 1.5f, 0.0f);
    XMVECTOR at = XMVectorSet(0.0f, -0.1f, 0.0f, 0.0f);
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    m_constantBufferData.view = XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up));
    m_constantBufferData.model = XMMatrixTranspose(XMMatrixRotationY(timeTotal * XM_PIDIV4));
}

void CubeRenderer::Render()
{
    const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };
    m_d3dContext->ClearRenderTargetView(
        m_d3dRenderTargetView.Get(),
        midnightBlue
        );

    m_d3dContext->ClearDepthStencilView(
        m_d3dDepthStencilView.Get(),
        D3D11_CLEAR_DEPTH,
        1.0f,
        0
        );

    // only draw the cube once it's loaded (this is async)
    if (!m_loadingComplete)
        return;

    m_d3dContext->OMSetRenderTargets(
        1,
        m_d3dRenderTargetView.GetAddressOf(),
        m_d3dDepthStencilView.Get()
        );

    m_d3dContext->UpdateSubresource(
        m_constantBuffer.Get(),
        0,
        NULL,
        &m_constantBufferData,
        0,
        0
        );

    UINT stride = sizeof(VertexPositionColor);
    UINT offset = 0;
    m_d3dContext->IASetVertexBuffers(
        0,
        1,
        m_vertexBuffer.GetAddressOf(),
        &stride,
        &offset
        );

    m_d3dContext->IASetIndexBuffer(
        m_indexBuffer.Get(),
        DXGI_FORMAT_R16_UINT,
        0
        );

    m_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_d3dContext->IASetInputLayout(m_inputLayout.Get());

    m_d3dContext->VSSetShader(
        m_vertexShader.Get(),
        nullptr,
        0
        );

    m_d3dContext->VSSetConstantBuffers(
        0,
        1,
        m_constantBuffer.GetAddressOf()
        );

    m_d3dContext->PSSetShader(
        m_pixelShader.Get(),
        nullptr,
        0
        );

    m_d3dContext->DrawIndexed(
        m_indexCount,
        0,
        0
        );



}
