#include "SGUI.h"
#include "ActionBarWidget.h"

UActionBarWidget* UActionBarWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UActionBarWidget>(worldContextObject);

	widget->actionBarHorizontal = Cast<UHorizontalBox>(widget->GetWidgetFromName(TEXT("ActionBarHorizontal")));

	return widget;
}

UActionBarButtonWidget* UActionBarWidget::AddActionButton(UObject* worldContextObject, int32 cooldown, UTexture2D* buttonTexture)
{
	auto button = InstantiateWidget<UActionBarButtonWidget>(worldContextObject);
	if (buttonTexture) button->SetTexture(buttonTexture);

	buttons.Add(button);

	actionBarHorizontal->AddChildToHorizontalBox(button);

	return button;
}
