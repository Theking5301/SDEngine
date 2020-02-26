#pragma once
#include "Core/Reflection/Reflection.h"
#include "../../../../SDEngine\Core\Objects\Entities\Camera.h"


//Reflection for class Camera
REFLECT_CLASS_BEGIN(Camera)
REFLECT_CLASS_BEGIN_PARENTS()
REFLECT_CLASS_PARENT(Actor)
REFLECT_CLASS_PARENT_END()
RREFLECT_CLASS_MEMBERS_BEGIN()
REFLECT_CLASS_MEMBERS_END(FieldOfView)
REFLECT_CLASS_MEMBERS_END(CurrentTransform)
REFLECT_CLASS_MEMBERS_END(LastFrameTransform)
REFLECT_CLASS_MEMBERS_END(bVisible)
REFLECT_CLASS_MEMBERS_END(bHiddenInGame)
REFLECT_CLASS_MEMBERS_END(bNeedsTick)
REFLECT_CLASS_MEMBERS_END(bNeedsBeginPlay)
REFLECT_CLASS_MEMBERS_END(bCastShadows)
REFLECT_CLASS_MEMBERS_END(EngineObjectType)
REFLECT_CLASS_MEMBERS_END(EngineObjectName)
REFLECT_CLASS_MEMBERS_END()
REFLECT_CLASS_END()
