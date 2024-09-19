#pragma once

#include "Resource.h"
#include "EngineProject.h"
#include "framework.h"
#include "Resource.h"
#include "targetver.h"

#include <comdef.h>
#include <wrl.h>
#include <iostream>

template <typename T>
using MSComPtr = Microsoft::WRL::ComPtr<T>;