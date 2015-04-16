#include "SagaGUI.h"
#include "PlayerHPWidget.h"

TSubclassOf<class UPlayerHPWidget> UPlayerHPWidget::widgetInstance;

UPlayerHPWidget::UPlayerHPWidget(const class FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UClass> widgetBP(TEXT("/Game/UMG/PlayerHP.PlayerHP_C"));
	if (widgetBP.Succeeded()) widgetInstance = widgetBP.Object;
}

UPlayerHPWidget* UPlayerHPWidget::Create(APlayerController* masterController)
{
	auto widget = CreateWidget<UPlayerHPWidget>(masterController, widgetInstance);
	widget->AddToViewport();

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




