#pragma once

#include <wrl/client.h>
#include <memory>

#include "DirectXBase.h"
#include <DirectXMath.h>

struct ModelViewProjectionConstantBuffer
{
    DirectX::XMMATRIX model;
    DirectX::XMMATRIX view;
    DirectX::XMMATRIX projection;
};

struct VertexPositionColor
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT3 color;
};

ref class CubeRenderer sealed : public DirectXBase
{
public:
	CubeRenderer();
	virtual ~CubeRenderer();
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;
	void Update(float timeTotal, float timeDelta);

private:
	bool m_loadingComplete;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	uint32 m_indexCount;
	ModelViewProjectionConstantBuffer m_constantBufferData;
};
