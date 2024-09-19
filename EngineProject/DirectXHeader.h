#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#include "BaseHeader.h"

#pragma comment(lib, "d3d11.lib")

//Comptr
template <typename T>
using MSComPtr = Microsoft::WRL::ComPtr<T>;

//����
using Float2 = DirectX::XMFLOAT2;
using Float3 = DirectX::XMFLOAT3;
using Float4 = DirectX::XMFLOAT4;
using Float4x4 = DirectX::XMFLOAT4X4;

//���
using Vector4 = DirectX::XMVECTOR;
using Matrix4x4 = DirectX::XMMATRIX;

