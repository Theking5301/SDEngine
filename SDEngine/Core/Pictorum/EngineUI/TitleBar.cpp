#include "TitleBar.h"
#include "Core/Engine/Window.h"
#include "Core/Pictorum/PictorumRenderer.h"
#include "Core/Pictorum/Widgets/HorizontalBoxWidget.h"
#include "Core/Pictorum/Widgets/ImageWidget.h"
#include "Core/Pictorum/Widgets/SolidWidget.h"
#include "Core/Pictorum/Widgets/TextWidget.h"
#include "Core/Utilities/EngineFunctionLibrary.h"


TitleBar::TitleBar(const TString& Name) : PictorumWidget(Name) {
	TitleBarHeight = 30.0f;

	CloseTexture = Engine::GetInstance()->GetAssetManager()->GetAsset<Texture2D>("./Res/Assets/Editor/Textures/UI/CloseIcon.sasset");
	MinimizeTexture = Engine::GetInstance()->GetAssetManager()->GetAsset<Texture2D>("./Res/Assets/Editor/Textures/UI/MinimizeIcon.sasset");
	RestoreTexture = Engine::GetInstance()->GetAssetManager()->GetAsset<Texture2D>("./Res/Assets/Editor/Textures/UI/RestoreIcon.sasset");
	MaximizeTexture = Engine::GetInstance()->GetAssetManager()->GetAsset<Texture2D>("./Res/Assets/Editor/Textures/UI/MaximizeIcon.sasset");

	SolidWidget* bg = new SolidWidget("TitleBarBackground");
	bg->SetBackgroundColor(FColor(0.2f, 0.2f, 0.3f));
	bg->OnMouseDownDelegate.Add<TitleBar, &TitleBar::OnTitleBarMouseDown>(this);
	bg->OnMouseUpDelegate.Add<TitleBar, &TitleBar::OnTitleBarMouseUp>(this);
	bg->OnMouseMoveDelegate.Add<TitleBar, &TitleBar::OnTitleBarMouseMove>(this);
	bMouseDownOnTitleBar = false;
	AddChild(bg);

	HorizontalBoxWidget* buttonContainer = new HorizontalBoxWidget("ButtonContainer");
	AddChild(buttonContainer);

	WindowTitleWidget = new TextWidget("WindowTitle");
	WindowTitleWidget->SetText("SD Engine");
	WindowTitleWidget->SetTextColor(FColor(0.9f, 0.9f, 0.9f));
	WindowTitleWidget->SetFontSize(11);
	buttonContainer->AddChild(WindowTitleWidget)->SetFillAvilableSpace(1.0f).SetVerticalAlignment(EVerticalAlignment::CENTER);

	MinimizeButton = new ImageWidget("Minimize");
	MinimizeButton->SetImage(MinimizeTexture);
	MinimizeButton->SetSize(vec2(TitleBarHeight, TitleBarHeight));
	MinimizeButton->OnMouseUpDelegate.Add<TitleBar, &TitleBar::OnMinimizeButtonClicked>(this);
	buttonContainer->AddChild(MinimizeButton);

	MaximizeButton = new ImageWidget("Maximize");
	MaximizeButton->SetImage(MaximizeTexture);
	MaximizeButton->SetSize(vec2(TitleBarHeight, TitleBarHeight));
	MaximizeButton->OnMouseUpDelegate.Add<TitleBar, &TitleBar::OnMaximizeClicked>(this);
	buttonContainer->AddChild(MaximizeButton);

	CloseButton = new ImageWidget("Close");
	CloseButton->SetImage(CloseTexture);
	CloseButton->SetSize(vec2(TitleBarHeight, TitleBarHeight));
	CloseButton->OnMouseUpDelegate.Add<TitleBar, &TitleBar::OnCloseButtonClicked>(this);
	buttonContainer->AddChild(CloseButton);
}
TitleBar::~TitleBar() {

}
void TitleBar::OnCreated() {
	SDL_SetWindowHitTest(GetOwningRenderer()->GetOwningWindow()->GetWindow(), &MouseHitTestCallback, this);
}
void TitleBar::Tick(float DeltaTime, const FRenderGeometry& Geometry) {
	PictorumWidget::Tick(DeltaTime, Geometry);
	WindowTitleWidget->SetText("SD Engine " + to_string(1.0f / DeltaTime));
}
const bool TitleBar::CanAddChild() const {
	return true;
}
void TitleBar::CalculateChildRenderGeometry(const FRenderGeometry& CurrentRenderGeometry, FRenderGeometry& OutputGeometry, int32 ChildIndex) const {
	OutputGeometry.SetLocation(vec2(0.0f, CurrentRenderGeometry.GetRenderResolution().y - TitleBarHeight));
	OutputGeometry.SetAllotedSpace(vec2(CurrentRenderGeometry.GetRenderResolution().x, TitleBarHeight));
}
void TitleBar::OnCloseButtonClicked(const vec2& MousePosition, FUserInterfaceEvent& UIEvent) {
	SDL_Event sdlevent;
	sdlevent.type = SDL_QUIT;
	SDL_PushEvent(&sdlevent);
}
void TitleBar::OnMinimizeButtonClicked(const vec2& MousePosition, FUserInterfaceEvent& UIEvent) {
	SDL_MinimizeWindow(GetOwningRenderer()->GetOwningWindow()->GetWindow());
}
void TitleBar::OnMaximizeClicked(const vec2& MousePosition, FUserInterfaceEvent& UIEvent) {
	uint32 flags = SDL_GetWindowFlags(GetOwningRenderer()->GetOwningWindow()->GetWindow());
	if (flags & SDL_WINDOW_MAXIMIZED) {
		SDL_RestoreWindow(GetOwningRenderer()->GetOwningWindow()->GetWindow());
		MaximizeButton->SetImage(MaximizeTexture);
		MaximizeButton->SetSize(vec2(TitleBarHeight, TitleBarHeight));
	} else {
		SDL_MaximizeWindow(GetOwningRenderer()->GetOwningWindow()->GetWindow());
		MaximizeButton->SetImage(RestoreTexture);
		MaximizeButton->SetSize(vec2(TitleBarHeight, TitleBarHeight));
	}
}
void TitleBar::OnTitleBarMouseDown(const vec2& MousePosition, FUserInterfaceEvent& UIEvent) {
	bMouseDownOnTitleBar = true;
	UIEvent.CaptureMouse();
}
void TitleBar::OnTitleBarMouseUp(const vec2& MousePosition, FUserInterfaceEvent& UIEvent) {
	bMouseDownOnTitleBar = false;
}
void TitleBar::OnTitleBarMouseMove(const vec2& MousePosition, const vec2& Delta, FUserInterfaceEvent& UIEvent) {

}

SDL_HitTestResult TitleBar::MouseHitTestCallback(SDL_Window* Window, const SDL_Point* MouseLocation, void* Data) {
	TitleBar* titleBar = (TitleBar*)Data;
	if (MouseLocation->y < titleBar->TitleBarHeight && MouseLocation->x < titleBar->GetOwningRenderer()->GetOwningWindow()->GetDimensions().x - (titleBar->TitleBarHeight * 3)) {
		return SDL_HITTEST_DRAGGABLE;
	}
	return SDL_HITTEST_NORMAL;
}