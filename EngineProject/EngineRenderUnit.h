#pragma once
#include "DirectXHeader.h"
#include "EngineResourceManager.h"

class EngineRenderUnit
{

public:

	EngineRenderUnit();
	~EngineRenderUnit();

	EngineRenderUnit(const EngineRenderUnit& _Other) = delete;
	EngineRenderUnit(EngineRenderUnit&& _Other) noexcept = delete;
	EngineRenderUnit& operator=(const EngineRenderUnit& _Other) = delete;
	EngineRenderUnit& operator=(EngineRenderUnit&& _Other) noexcept = delete;

	void SetMesh(const SMeshData& _Mesh)
	{
		VertexBuffer = _Mesh.VertexBuffer;
		IndexBuffer = _Mesh.IndexBuffer;
	}

protected:

private:
	MSComPtr<ID3D11Buffer> VertexBuffer;
	MSComPtr<ID3D11Buffer> IndexBuffer;
};

