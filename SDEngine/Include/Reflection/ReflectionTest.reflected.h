#pragma once
#include "Core/Reflection/Reflection.h"
#include "./Test\ReflectionTest.h"


//Reflection for struct FReflectionTest
REFLECT_STRUCT_BEGIN(FReflectionTest)
REFLECT_STRUCT_BEGIN_PARENTS()
REFLECT_STRUCT_PARENT_END()
REFLECT_STRUCT_MEMBERS_BEGIN()
REFLECT_STRUCT_MEMBER(testFloat)
REFLECT_STRUCT_MEMBER(testString)
REFLECT_STRUCT_MEMBER(testInt)
REFLECT_STRUCT_MEMBER(testVector4D)
REFLECT_STRUCT_MEMBER(testVector3D)
REFLECT_STRUCT_MEMBER(testVector2D)
REFLECT_STRUCT_MEMBER(testBool)
REFLECT_STRUCT_MEMBER(boolArray)
REFLECT_STRUCT_MEMBERS_END()
REFLECT_STRUCT_END()
