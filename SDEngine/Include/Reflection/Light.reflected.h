//LastModifiedTime:637193049626723051
#pragma once
#include "Core/Reflection/Reflection.h"
#include "./Core\Objects\Entities\Light.h"


//Reflection for class Light
REFLECT_CLASS_BEGIN(Light)
REFLECT_CLASS_BEGIN_PARENTS()
REFLECT_CLASS_PARENT(Actor)
REFLECT_CLASS_PARENT_END()
REFLECT_CLASS_MEMBERS_BEGIN()
REFLECT_CLASS_MEMBER(Intensity, "Intensity", false, "Light")
REFLECT_CLASS_MEMBER(Attenuation, "Attenuation", false, "Light")
REFLECT_CLASS_MEMBER(Color, "Color", false, "Light")
REFLECT_CLASS_MEMBERS_END()
REFLECT_CLASS_END()
