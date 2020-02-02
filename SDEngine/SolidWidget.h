#pragma once
#include "UserInterface/PictorumWidget.h"
class SolidWidget : public PictorumWidget {
public:
	SolidWidget();
	~SolidWidget();
	virtual void Draw(float DeltaTime) override;

	virtual void OnMouseEnter(vec2 MousePosition, FUserInterfaceEvent& Event) override;
	virtual void OnMouseExit(vec2 MousePosition, FUserInterfaceEvent& Event) override;
	virtual void OnMouseDown(vec2 MousePosition, EMouseButton Button, FUserInterfaceEvent& Event) override;
	virtual void OnMouseUp(vec2 MousePosition, EMouseButton Button, FUserInterfaceEvent& Event) override;
	virtual void OnMouseMove(vec2 MousePosition, vec2 MouseDelta, FUserInterfaceEvent& Event) override;

	virtual TString GetDetailsPanelName() override;
	virtual bool PopulateDetailsPanel() override;

private:
	float BorderRadius;
	FColor BackgroundColor;
	bool bWasMouseDownInWidget;

	GLuint quadVAO = 0;
	GLuint quadVBO;
};

