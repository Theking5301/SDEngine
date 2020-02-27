#include "ReflectionHelpers.h"
#include "Core/Objects/EngineObject.h"

const void ReflectionHelpers::GetAllMembersOfClass(SArray<FProperty>& Properties, const EngineObject* Object) {
	worker_GetAllMembersOfClass(Object->StaticDescriptor(), Properties);
}
void ReflectionHelpers::worker_GetAllMembersOfClass(const TypeDescriptor_Class* CurrentNode, SArray<FProperty>& Output) {
	// Add the members of the current node.
	for (FProperty property : CurrentNode->Properties) {
		Output.Add(property);
	}

	// Continue down the tree.
	for (TypeDescriptor* desc : CurrentNode->ParentDescriptors) {
		TypeDescriptor_Class* parent = (TypeDescriptor_Class*)desc;
		if (parent) {
			worker_GetAllMembersOfClass((TypeDescriptor_Class*)desc, Output);
		}
	}
}