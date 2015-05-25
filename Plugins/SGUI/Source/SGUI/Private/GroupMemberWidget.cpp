#include "SGUI.h"
#include "GroupMemberWidget.h"

UGroupMemberWidget* UGroupMemberWidget::Create(UObject* worldContextObject, FText memberName)
{
	auto widget = InstantiateWidget<UGroupMemberWidget>(worldContextObject);
	if (!widget) return nullptr;

	widget->nameLabel = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("NameLabel")));
	widget->hpBar = Cast<UProgressBar>(widget->GetWidgetFromName(TEXT("HPBar")));
	widget->hpLabel = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("HPLabel")));
	widget->staminaBar = Cast<UProgressBar>(widget->GetWidgetFromName(TEXT("StaminaBar")));

	widget->nameLabel->SetText(memberName);

	return widget;
}

void UGroupMemberWidget::SetHPFillAmount(const float& value)
{
	hpBar->SetPercent(value);
	hpLabel->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), (uint8)(value * 100))));
}

void UGroupMemberWidget::SetStaminaFillAmount(const float& value)
{
	staminaBar->SetPercent(value);
}
