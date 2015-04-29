#include "SGUI.h"
#include "PlayerHPWidget.h"

UPlayerHPWidget* UPlayerHPWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UPlayerHPWidget>(worldContextObject);

	widget->hpBar = Cast<UProgressBar>(widget->GetWidgetFromName(TEXT("HPBar")));
	widget->hpLabel = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("HPLabel")));

	return widget;
}

void UPlayerHPWidget::SetFillAmount(const float& value)
{
	hpBar->SetPercent(value);
	hpLabel->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), (uint8)(value * 100))));
}

void UPlayerHPWidget::Tick_Implementation(FGeometry myGeometry, float inDeltaTime)
{
	if (onTick.IsBound()) 
		SetFillAmount(onTick.Execute());
}

