#include "SGUI.h"
#include "ActionBarButtonWidget.h"

UActionBarButtonWidget* UActionBarButtonWidget::Create(UObject* worldContextObject, float cooldown)
{
	auto widget = InstantiateWidget<UActionBarButtonWidget>(worldContextObject);
	widget->cd = cooldown;

	widget->actionButton = Cast<UButton>(widget->GetWidgetFromName(TEXT("ActionButton")));
	widget->cdLabel = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("CDLabel")));

	return widget;
}

void UActionBarButtonWidget::SetTexture(UTexture2D* texture)
{
	//actionButton->WidgetStyle.Normal.SetResourceObject(texture);
	//actionButton->WidgetStyle.Hovered.SetResourceObject(texture);
	//actionButton->WidgetStyle.Pressed.SetResourceObject(texture);
	//actionButton->WidgetStyle.Disabled.SetResourceObject(texture);
}

void UActionBarButtonWidget::SetTooltip(FText text)
{
	actionButton->SetToolTipText(text);
}

void UActionBarButtonWidget::FireOnClicked()
{
	if (cdTimer > 0) return;

	if (OnActionBarButtonClicked.IsBound())
		OnActionBarButtonClicked.Broadcast();

	cdTimer = cd;
}

void UActionBarButtonWidget::Tick_Implementation(FGeometry myGeometry, float deltaTime)
{
	Super::Tick_Implementation(myGeometry, deltaTime);

	cdTimer = cdTimer > 0.f ? cdTimer - deltaTime : 0.f;
	if (cdTimer > 0) cdLabel->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), cdTimer)));
	cdLabel->SetVisibility(cdTimer == 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	actionButton->SetIsEnabled(cdTimer == 0);
}
