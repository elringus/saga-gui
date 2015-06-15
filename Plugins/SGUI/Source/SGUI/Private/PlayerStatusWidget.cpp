#include "SGUI.h"
#include "PlayerStatusWidget.h"

UPlayerStatusWidget* UPlayerStatusWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UPlayerStatusWidget>(worldContextObject);
	if (!widget) return nullptr;

	widget->hpBar = Cast<UProgressBar>(widget->GetWidgetFromName(TEXT("HPBar")));
	widget->hpLabel = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("HPLabel")));
	widget->staminaBar = Cast<UProgressBar>(widget->GetWidgetFromName(TEXT("StaminaBar")));

	return widget;
}

void UPlayerStatusWidget::SetHPFillAmount(const float& value)
{
	hpBar->SetPercent(value);
	hpLabel->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), (uint8)(value * 100))));
}

void UPlayerStatusWidget::SetStaminaFillAmount(const float& value)
{
	staminaBar->SetPercent(value);
}

void UPlayerStatusWidget::NativeTick(const FGeometry& myGeometry, float deltaTime)
{
	Super::NativeTick(myGeometry, deltaTime);

	if (onTick.IsBound()) 
		SetHPFillAmount(onTick.Execute());
}

