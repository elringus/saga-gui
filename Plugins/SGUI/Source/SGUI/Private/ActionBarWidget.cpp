#include "SGUI.h"
#include "ActionBarWidget.h"

UActionBarWidget* UActionBarWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UActionBarWidget>(worldContextObject);

	widget->actionBarHorizontal = Cast<UHorizontalBox>(widget->GetWidgetFromName(TEXT("ActionBarHorizontal")));

	return widget;
}

UActionBarButtonWidget* UActionBarWidget::AddActionButton(UObject* worldContextObject, float cooldown, UTexture2D* buttonTexture, FText tooltipTxt)
{
	auto button = UActionBarButtonWidget::Create(worldContextObject, cooldown);
	if (buttonTexture) button->SetTexture(buttonTexture);
	button->SetTooltip(tooltipTxt);

	buttons.Add(button);

	actionBarHorizontal->AddChildToHorizontalBox(button);

	return button;
}
