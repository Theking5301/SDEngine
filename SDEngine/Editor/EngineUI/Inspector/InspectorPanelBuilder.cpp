#include "InspectorPanelBuilder.h"
#include "Core/DataTypes/TypeDefenitions.h"
#include "Core/Pictorum/Pictorum.h"
#include "Core/Pictorum/Widgets/SeparatorWidget.h"
#include "Core/Pictorum/Widgets/VectorInspectorWidget.h"
#include "Core/Pictorum/Widgets/CheckboxWidget.h"
#include "Core/Pictorum/Pictorum.h"
#include "Core/Reflection/ReflectionHelpers.h"
#include "Core/Utilities/EngineFunctionLibrary.h"
#include "Core/Utilities/Math/Transform.h"

InspectorPanelBuilder::InspectorPanelBuilder(PictorumVerticalBox* Owner, EngineObject* CustomizationTarget) {
	Parent = Owner;
	Target = CustomizationTarget;
	AddedPropertyCount = 0;
}
template<>
void InspectorPanelBuilder::AddControlForPropertyInternal(const TString& Name, Vector4D* Property) {
	AssignNewToChildLocal(Parent, PictorumHorizontalBox, hBox, "PropertyHBox");
	AssignNewToChildLocal(hBox, TextWidget, label, "PropertyLabel");
	label->SetText(Name);
	label->SetFontSize(10);
	label->SetFontWeight(EFontWeight::Bold);
	label->GetParentSlot<HorizontalBoxSlot>()->SetFillAvilableSpace(0.5f).SetVerticalAlignment(EVerticalAlignment::CENTER);
	AssignNewToChildLocal(hBox, VectorInspectorWidget, floatEditor, "VectorInspectorWidget");

	SArray<TString> labels;
	labels.Add("X");
	labels.Add("Y");
	labels.Add("Z");
	labels.Add("W");
	floatEditor->SetControlledValue(labels, &(*Property)[0], 4);
	floatEditor->GetParentSlot<HorizontalBoxSlot>()->SetFillAvilableSpace(1.0f);
}
template<>
void InspectorPanelBuilder::AddControlForPropertyInternal(const TString& Name, Vector3D* Property) {
	AssignNewToChildLocal(Parent, PictorumHorizontalBox, hBox, "PropertyHBox");
	AssignNewToChildLocal(hBox, TextWidget, label, "PropertyLabel");
	label->SetText(Name);
	label->SetFontSize(10);
	label->SetFontWeight(EFontWeight::Bold);
	label->GetParentSlot<HorizontalBoxSlot>()->SetFillAvilableSpace(0.5f).SetVerticalAlignment(EVerticalAlignment::CENTER);
	AssignNewToChildLocal(hBox, VectorInspectorWidget, floatEditor, "VectorInspectorWidget");

	SArray<TString> labels;
	labels.Add("X");
	labels.Add("Y");
	labels.Add("Z");
	floatEditor->SetControlledValue(labels, &(*Property)[0], 3);
	floatEditor->GetParentSlot<HorizontalBoxSlot>()->SetFillAvilableSpace(1.0f);
}
template<>
void InspectorPanelBuilder::AddControlForPropertyInternal(const TString& Name, Vector2D* Property) {
	AssignNewToChildLocal(Parent, PictorumHorizontalBox, hBox, "PropertyHBox");
	AssignNewToChildLocal(hBox, TextWidget, label, "PropertyLabel");
	label->SetText(Name);
	label->SetFontSize(10);
	label->SetFontWeight(EFontWeight::Bold);
	label->GetParentSlot<HorizontalBoxSlot>()->SetFillAvilableSpace(0.5f).SetVerticalAlignment(EVerticalAlignment::CENTER);
	AssignNewToChildLocal(hBox, VectorInspectorWidget, floatEditor, "VectorInspectorWidget");

	SArray<TString> labels;
	labels.Add("X");
	labels.Add("Y");
	floatEditor->SetControlledValue(labels, &(*Property)[0], 2);
	floatEditor->GetParentSlot<HorizontalBoxSlot>()->SetFillAvilableSpace(1.0f);
}
template<>
void InspectorPanelBuilder::AddControlForPropertyInternal(const TString& Name, Transform* Property) {
	AddControlForPropertyInternal("Location", ReflectionHelpers::GetProperty<Vector3D, Transform>("Location", Property));
	AssignNewToChildLocal(Parent, SeparatorWidget, sep1, "Separator");
	sep1->SetSize(0.0f, 5.0f);
	AddControlForPropertyInternal("Rotation", ReflectionHelpers::GetProperty<Vector3D, Transform>("Rotation", Property));
	AssignNewToChildLocal(Parent, SeparatorWidget, sep2, "Separator");
	sep2->SetSize(0.0f, 5.0f);
	AddControlForPropertyInternal("Scale", ReflectionHelpers::GetProperty<Vector3D, Transform>("Scale", Property));
}
template<>
void InspectorPanelBuilder::AddControlForPropertyInternal(const TString& Name, bool* Property) {
	AssignNewToChildLocal(Parent, PictorumHorizontalBox, hBox, "PropertyHBox");
	AssignNewToChildLocal(hBox, TextWidget, label, "PropertyLabel");
	label->SetText(Name);
	label->SetFontSize(10);
	label->SetFontWeight(EFontWeight::Bold);
	label->GetParentSlot<HorizontalBoxSlot>()->SetFillAvilableSpace(0.5f).SetVerticalAlignment(EVerticalAlignment::CENTER);

	AssignNewToChildLocal(hBox, CheckboxWidget, checkbox, "CheckboxWidget");
	checkbox->Bind(Property);
	checkbox->GetParentSlot<HorizontalBoxSlot>()->SetFillAvilableSpace(1.0f);
}
void InspectorPanelBuilder::AddControlForProperty(const FProperty& Property) {
	if (AddedPropertyCount > 0) {
		AssignNewToChildLocal(Parent, SeparatorWidget, sep, "Separator");
		sep->SetSize(0.0f, 5.0f);
	}
	const TString& typeName = Property.Type->Name;
	if (typeName == "Vector4D") {
		AddControlForPropertyInternal(Property.InspectorName, ReflectionHelpers::GetProperty<Vector4D>(Property, Target));
	} else if (typeName == "Vector3D") {
		AddControlForPropertyInternal(Property.InspectorName, ReflectionHelpers::GetProperty<Vector3D>(Property, Target));
	} else if (typeName == "Vector2D") {
		AddControlForPropertyInternal(Property.InspectorName, ReflectionHelpers::GetProperty<Vector2D>(Property, Target));
	} else if (typeName == "Transform") {
		AddControlForPropertyInternal(Property.InspectorName, ReflectionHelpers::GetProperty<Transform>(Property, Target));
	} else if (typeName == "bool") {
		AddControlForPropertyInternal(Property.InspectorName, ReflectionHelpers::GetProperty<bool>(Property, Target));
	}
	AddedPropertyCount++;
}