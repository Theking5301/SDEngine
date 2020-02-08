#pragma once
#include "Core/Pictorum/IWidgetSlot.h"

class HorizontalBoxSlot : public IWidgetSlot {
public:
	HorizontalBoxSlot();
	virtual ~HorizontalBoxSlot();

	const EFillRule& GetFillRule() const;
	const float& GetFillRatio() const;
	const EVerticalAlignment& GetVerticalAlignment() const;
	const EHorizontalAlignment& GetHorizontalAlignment() const;

	HorizontalBoxSlot& SetUseWidgetDesiredSpace();
	HorizontalBoxSlot& SetFillAvilableSpace(float Ratio);
	HorizontalBoxSlot& SetHorizontalAlignment(EHorizontalAlignment Alignment);
	HorizontalBoxSlot& SetVerticalAlignment(EVerticalAlignment Alignment);
private:
	FFillRule FillRule;
	EHorizontalAlignment HorizontalAlignment;
	EVerticalAlignment VerticalAlignment;
};

