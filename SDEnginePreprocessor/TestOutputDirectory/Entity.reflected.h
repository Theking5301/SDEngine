//LastModifiedTime:504911232000000000
#pragma once
#include "Core/Reflection/Reflection.h"
#include "../../../../SDEngine\Core\Objects\Entities\Entity.h"


//Reflection for class Entity
REFLECT_CLASS_BEGIN(Entity)
REFLECT_CLASS_PARENT(EngineObject)
REFLECT_CLASS_MEMBER(LastFrameTransform, "Last Frame Transform",  "Default", true)
REFLECT_CLASS_MEMBER(bVisible, "Visible",  "Entity", false)
REFLECT_CLASS_MEMBER(bHiddenInGame, "Hidden In Game",  "Entity", false)
REFLECT_CLASS_MEMBER(bNeedsTick, "Needs Tick",  "Entity", false)
REFLECT_CLASS_MEMBER(bNeedsBeginPlay, "Needs Begin Play",  "Entity", false)
REFLECT_CLASS_MEMBER(bCastShadows, "Cast Shadows",  "Entity", false)
REFLECT_CLASS_MEMBER(Transform, "Transform",  "Transform", false)
REFLECT_CLASS_FUNCTION(IsVisible, false, bool, 0, true)
REFLECT_CLASS_FUNCTION(SetVisibility, false, void, 0, false, {Show, bool, True, 1})
REFLECT_CLASS_FUNCTION(ToggleVisibility, false, void, 0, false)
REFLECT_CLASS_FUNCTION(IsHiddenInGame, false, bool, 0, true)
REFLECT_CLASS_FUNCTION(SetHiddenInGame, false, void, 0, false, {Hidden, bool, True, 1})
REFLECT_CLASS_FUNCTION(CastsShadows, false, bool, 0, true)
REFLECT_CLASS_FUNCTION(SetCastShadows, false, void, 0, false, {CastShadows, bool, True, 1})
REFLECT_CLASS_FUNCTION(GetLocation, true, Vector3D, 1, true)
REFLECT_CLASS_FUNCTION(GetRotation, true, Vector3D, 1, true)
REFLECT_CLASS_FUNCTION(GetScale, true, Vector3D, 1, true)
REFLECT_CLASS_FUNCTION(GetLinearVelocity, true, Vector3D, 0, true)
REFLECT_CLASS_FUNCTION(GetAngularVelocity, true, Vector3D, 0, true)
REFLECT_CLASS_FUNCTION(AddLocation, false, void, 0, false, {Offset, Vector3D, True, 0})
REFLECT_CLASS_FUNCTION(AddLocation, false, void, 0, false, {X, float, True, 1}, {Y, float, True, 1}, {Z, float, True, 1})
REFLECT_CLASS_FUNCTION(SetLocation, false, void, 0, false, {Location, Vector3D, True, 1})
REFLECT_CLASS_FUNCTION(SetLocation, false, void, 0, false, {X, float, True, 1}, {Y, float, True, 1}, {Z, float, True, 1})
REFLECT_CLASS_FUNCTION(AddRotation, false, void, 0, false, {RotationDelta, Vector3D, True, 1})
REFLECT_CLASS_FUNCTION(AddRotation, false, void, 0, false, {X, float, True, 1}, {Y, float, True, 1}, {Z, float, True, 1})
REFLECT_CLASS_FUNCTION(SetRotation, false, void, 0, false, {Rotation, Vector3D, True, 1})
REFLECT_CLASS_FUNCTION(SetRotation, false, void, 0, false, {X, float, True, 1}, {Y, float, True, 1}, {Z, float, True, 1})
REFLECT_CLASS_FUNCTION(AddScale, false, void, 0, false, {ScaleDelta, Vector3D, True, 1})
REFLECT_CLASS_FUNCTION(AddScale, false, void, 0, false, {X, float, True, 1}, {Y, float, True, 1}, {Z, float, True, 1})
REFLECT_CLASS_FUNCTION(SetScale, false, void, 0, false, {Scale, Vector3D, True, 1})
REFLECT_CLASS_FUNCTION(SetScale, false, void, 0, false, {X, float, True, 1}, {Y, float, True, 1}, {Z, float, True, 1})
REFLECT_CLASS_FUNCTION(SetUniformScale, false, void, 0, false, {Scale, float, True, 1})
REFLECT_CLASS_FUNCTION(GetTransform, true, FTransform, 1, true)
REFLECT_CLASS_FUNCTION(SetTransform, false, void, 0, false, {NewTransform, FTransform, True, 1})
REFLECT_CLASS_FUNCTION(GetLastFrameTransform, true, FTransform, 1, true)
REFLECT_CLASS_FUNCTION(SetLastFrameTransform, false, void, 0, false, {OldTransform, FTransform, True, 1})
REFLECT_CLASS_END()
