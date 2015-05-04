#include "SGUI.h"
#include "ActionBarButtonWidget.h"

UActionBarButtonWidget* UActionBarButtonWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UActionBarButtonWidget>(worldContextObject);

	widget->actionButton = Cast<UButton>(widget->GetWidgetFromName(TEXT("ActionButton")));
	widget->cdLabel = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("CDLabel")));

	widget->actionButton->OnClicked.AddUniqueDynamic(widget, &UActionBarButtonWidget::OnClick);

	return widget;
}

void UActionBarButtonWidget::OnClick_Implementation()
{
	// this will be added to the BP overrided OnClick()
}

void UActionBarButtonWidget::SetTexture(UTexture2D* texture)
{
	actionButton->WidgetStyle.Normal.SetResourceObject(texture);
	actionButton->WidgetStyle.Hovered.SetResourceObject(texture);
	actionButton->WidgetStyle.Pressed.SetResourceObject(texture);
	actionButton->WidgetStyle.Disabled.SetResourceObject(texture);
}
