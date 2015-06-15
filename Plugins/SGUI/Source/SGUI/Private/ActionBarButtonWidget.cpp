#include "SGUI.h"
#include "ActionBarButtonWidget.h"

UActionBarButtonWidget* UActionBarButtonWidget::Create(UObject* worldContextObject, float cooldown)
{
	auto widget = InstantiateWidget<UActionBarButtonWidget>(worldContextObject);
	if (!widget) return nullptr;

	widget->cd = cooldown;

	widget->InitializeButton(Cast<UButton>(widget->GetWidgetFromName(TEXT("ActionButton"))));
	widget->cdLabel = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("CDLabel")));

	return widget;
}

void UActionBarButtonWidget::NativeTick(const FGeometry& myGeometry, float deltaTime)
{
	Super::NativeTick(myGeometry, deltaTime);

	cdTimer = cdTimer > 0.f ? cdTimer - deltaTime : 0.f;
	if (cdTimer > 0) cdLabel->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), cdTimer)));
	cdLabel->SetVisibility(cdTimer == 0 ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	button->SetIsEnabled(cdTimer == 0);
}

void UActionBarButtonWidget::DoClick()
{
	if (cdTimer > 0) return;

	Super::DoClick();

	cdTimer = cd;
}
