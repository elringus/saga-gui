#include "SGUI.h"
#include "SagaButtonWidget.h"

void USagaButtonWidget::InitializeButton(UButton* button)
{
	this->button = button;
	button->OnClicked.AddUniqueDynamic(this, &USagaButtonWidget::DoClick);
}

void USagaButtonWidget::DoClick()
{
	if (OnSagaButtonClicked.IsBound())
		OnSagaButtonClicked.Broadcast();
}

void USagaButtonWidget::SetTexture(UTexture2D* texture)
{
	button->WidgetStyle.Normal.SetResourceObject(texture);
	button->WidgetStyle.Normal.ImageSize = FVector2D(texture->GetSizeX(), texture->GetSizeY());

	button->WidgetStyle.Hovered.SetResourceObject(texture);
	button->WidgetStyle.Hovered.ImageSize = FVector2D(texture->GetSizeX(), texture->GetSizeY());

	button->WidgetStyle.Pressed.SetResourceObject(texture);
	button->WidgetStyle.Pressed.ImageSize = FVector2D(texture->GetSizeX(), texture->GetSizeY());

	button->WidgetStyle.Disabled.SetResourceObject(texture);
	button->WidgetStyle.Disabled.ImageSize = FVector2D(texture->GetSizeX(), texture->GetSizeY());
}

void USagaButtonWidget::SetTooltip(FText text)
{
	if (button) button->SetToolTipText(text);
}
