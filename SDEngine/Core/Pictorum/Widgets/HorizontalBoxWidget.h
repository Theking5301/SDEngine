#pragma once
#include "Core/Pictorum/PictorumWidget.h"
#include "Core/Pictorum/Slots/HorizontalBoxSlot.h"

class HorizontalBoxWidget : public PictorumWidget {
public:
	HorizontalBoxWidget(const TString& Name);
	virtual const bool CanAddChild() const override;
	virtual void CalculateChildRenderGeometry(const FRenderGeometry& CurrentRenderGeometry, FRenderGeometry& OutputGeometry, int32 ChildIndex) const override;
	virtual HorizontalBoxSlot* CreateSlotForWidget(PictorumWidget* WidgetForSlot) const override;
	virtual HorizontalBoxSlot* AddChild(PictorumWidget* Widget) override;
protected:
	float GetFillRatioForChild(int32 ChildIndex) const;
	float GetNonFillSpaceRequirements(const FRenderGeometry& CurrentRenderGeometry) const;
	virtual void DrawContents(const float& DeltaTime, const FRenderGeometry& Geometry) override;
	float lastXPosition;
};

