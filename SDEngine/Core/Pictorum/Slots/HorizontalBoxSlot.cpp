#include "HorizontalBoxSlot.h"

HorizontalBoxSlot::HorizontalBoxSlot() {
	VerticalAlignment = EVerticalAlignment::LEFT;
	HorizontalAlignment = EHorizontalAlignment::LEFT;
}
HorizontalBoxSlot::~HorizontalBoxSlot() {

}

const EFillRule& HorizontalBoxSlot::GetFillRule() const{ 
	return FillRule.GetFillRule();
}
const float& HorizontalBoxSlot::GetFillRatio() const {
	return FillRule.GetFillRatio();
}
const EVerticalAlignment& HorizontalBoxSlot::GetVerticalAlignment() const { 
	return VerticalAlignment;
}
const EHorizontalAlignment& HorizontalBoxSlot::GetHorizontalAlignment() const{ 
	return HorizontalAlignment;
}

HorizontalBoxSlot& HorizontalBoxSlot::SetUseWidgetDesiredSpace() {
	FillRule.SetUseWidgetDesiredSpace();
	return *this;
}
HorizontalBoxSlot& HorizontalBoxSlot::SetFillAvilableSpace(float Ratio) {
	FillRule.SetFillAllSpace(Ratio);
	return *this;
}
HorizontalBoxSlot& HorizontalBoxSlot::SetHorizontalAlignment(EHorizontalAlignment Alignment){ 
	HorizontalAlignment = Alignment;
	return *this;
}
HorizontalBoxSlot& HorizontalBoxSlot::SetVerticalAlignment(EVerticalAlignment Alignment) {
	VerticalAlignment = Alignment;
	return *this;
}