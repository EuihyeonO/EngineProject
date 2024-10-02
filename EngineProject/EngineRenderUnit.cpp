#include "EngineRenderUnit.h"

EngineRenderUnit::EngineRenderUnit()
{
}

EngineRenderUnit::~EngineRenderUnit()
{
}

void EngineRenderUnit::SetMesh(const SMeshData& _Mesh)
{
	Material.VertexBuffer = _Mesh.VertexBuffer;
	Material.IndexBuffer = _Mesh.IndexBuffer;

	Material.DiffuseTexture = _Mesh.DiffuseTexture;
	Material.NormalTexture = _Mesh.NormalTexture;

	Material.IndexCount = _Mesh.IndexCount;
}

void EngineRenderUnit::SetVertexShader(std::shared_ptr<EngineVertexShader> _VertexShader)
{
	if (_VertexShader == nullptr)
	{
		return;
	}

	Material.VertexShader = nullptr;

	std::shared_ptr<EngineVertexShader> VertexShader = std::make_shared<EngineVertexShader>();

	const std::unordered_map<std::string, SConstantBuffer>& AllCBuffer = _VertexShader->GetAllConstantBuffer();
	for (const std::pair<std::string, SConstantBuffer>& Buffer : AllCBuffer)
	{
		VertexShader->AddConstantBuffer(Buffer.first, Buffer.second);
	}

	VertexShader->SetVertexShader(_VertexShader->GetVertexShader());
	VertexShader->SetInputLayOut(_VertexShader->GetInputLayOut());

	Material.VertexShader = VertexShader;
}

void EngineRenderUnit::SetPixelShader(std::shared_ptr<EnginePixelShader> _PixelShader)
{
	if (_PixelShader == nullptr)
	{
		return;
	}

	Material.PixelShader = nullptr;

	std::shared_ptr<EnginePixelShader> PixelShader = std::make_shared<EnginePixelShader>();

	const std::unordered_map<std::string, STextureData>& AllTexture = _PixelShader->GetAllTexture();
	for (const std::pair<std::string, STextureData>& Texture : AllTexture)
	{
		PixelShader->AddTexture(Texture.first, Texture.second);
	}

	if (PixelShader->HasTexture("DIFFUSETEX") == true)
	{
		PixelShader->SetTexture("DIFFUSETEX", Material.DiffuseTexture);
	}

	if (PixelShader->HasTexture("NORMALTEX") == true)
	{
		PixelShader->SetTexture("NORMALTEX", Material.NormalTexture);
	}

	const std::unordered_map<std::string, SSamplerState>& AllSampler = _PixelShader->GetAllSampler();
	for (const std::pair<std::string, SSamplerState>& Sampler : AllSampler)
	{
		PixelShader->AddSampler(Sampler.first, Sampler.second);

		MSComPtr<ID3D11SamplerState> SamplerState = EngineResourceManager::FindSampler(Sampler.first);
		if (SamplerState != nullptr)
		{
			PixelShader->SetSampler(Sampler.first, SamplerState);
		}
	}

	PixelShader->SetPixelShader(_PixelShader->GetPixelShader());

	Material.PixelShader = PixelShader;
}

void EngineRenderUnit::SetSampler(std::string_view _Name)
{
	MSComPtr<ID3D11SamplerState> Sampler = EngineResourceManager::FindSampler(_Name);

	if (EngineResourceManager::FindSampler(_Name) != nullptr)
	{
		Material.PixelShader->SetSampler(_Name, Sampler);
	}
}