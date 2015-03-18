#include "SagaGUI.h"
#include "FloatingBarWidget.h"

TSubclassOf<class UFloatingBarWidget> UFloatingBarWidget::widgetInstance;

UFloatingBarWidget::UFloatingBarWidget(const class FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> widgetBP(TEXT("WidgetBlueprint'/Game/UMG/FloatingBar.FloatingBar'"));
	if (widgetBP.Succeeded()) widgetInstance = (UClass*)widgetBP.Object->GeneratedClass;
}

UFloatingBarWidget* UFloatingBarWidget::Create(APlayerController* masterController, AActor* followTarget)
{
	auto widget = CreateWidget<UFloatingBarWidget>(masterController, widgetInstance);
	widget->FollowTarget = followTarget;
	widget->AddToViewport();

	return widget;
}

void UFloatingBarWidget::Tick_Implementation(FGeometry MyGeometry, float InDeltaTime)
{
	FVector2D screenPos; 
	GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(FollowTarget->GetActorLocation(), screenPos);
	(Cast<UCanvasPanelSlot>(floatingBar->Slot))->SetPosition(screenPos);
}

void UFloatingBarWidget::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	floatingBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("FloatingBar")));
}


