#include "SagaGUI.h"
#include "PlayerHPWidget.h"

TSubclassOf<class UPlayerHPWidget> UPlayerHPWidget::widgetInstance;

UPlayerHPWidget::UPlayerHPWidget(const class FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> widgetBP(TEXT("WidgetBlueprint'/Game/UMG/PlayerHP.PlayerHP'"));
	if (widgetBP.Succeeded()) widgetInstance = (UClass*)widgetBP.Object->GeneratedClass;
}

UPlayerHPWidget* UPlayerHPWidget::Create(APlayerController* masterController)
{
	auto widget = CreateWidget<UPlayerHPWidget>(masterController, widgetInstance);
	widget->AddToViewport();

	widget->hpBar = Cast<UProgressBar>(widget->GetWidgetFromName(TEXT("HPBar")));
	widget->hpLabel = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("HPLabel")));

	return widget;
}

void UPlayerHPWidget::Tick_Implementation(FGeometry myGeometry, float inDeltaTime)
{
	if (onTick.IsBound()) 
	{
		SetFillAmount(onTick.Execute());
		hpLabel->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), (uint8)(hpBar->Percent * 100))));
	}
}




