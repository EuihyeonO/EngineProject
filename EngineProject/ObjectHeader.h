#pragma once

#include "TransformComponent.h"
#include "EngineActor.h"
#include "EngineRenderBase.h"

template<typename T>
concept CommonActor = std::is_base_of_v<EngineActor, T>;

template<typename T>
concept Not_Trans_Component = std::is_base_of_v<EngineComponent, T> && !std::derived_from<T, TransformComponent>;

template<typename T>
concept Not_Trans_Render_Component = Not_Trans_Component<T> && !std::is_base_of_v<EngineRenderBase, T>;
