#include "SagaGUI.h"
#include "FloatingBarWidget.h"

TSubclassOf<class UFloatingBarWidget> UFloatingBarWidget::widgetInstance;

UFloatingBarWidget::UFloatingBarWidget(const class FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> widgetBP(TEXT("WidgetBlueprint'/Game/UMG/FloatingBar.FloatingBar'"));
	if (widgetBP.Succeeded()) widgetInstance = (UClass*)widgetBP.Object->GeneratedClass;
}

UFloatingBarWidget* UFloatingBarWidget::Create(APlayerController* masterController, AActor* followTarget, FVector offset)
{
	auto widget = CreateWidget<UFloatingBarWidget>(masterController, widgetInstance);
	widget->followTarget = followTarget;
	widget->AddToViewport();
	widget->offset = offset;

	widget->floatingBar = Cast<UProgressBar>(widget->GetWidgetFromName(TEXT("FloatingBar")));

	return widget;
}

void UFloatingBarWidget::Tick_Implementation(FGeometry myGeometry, float inDeltaTime)
{
	FVector2D screenPos; 
	GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(followTarget->GetActorLocation() + offset, screenPos);
	(Cast<UCanvasPanelSlot>(floatingBar->Slot))->SetPosition(screenPos);

	if (onTick.IsBound()) SetFillAmount(onTick.Execute());
}

