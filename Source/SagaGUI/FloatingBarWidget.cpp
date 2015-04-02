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
	widget->masterController = masterController;
	widget->masterActor = masterController->GetPawn();
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

	if (masterActor) 
	{
		float opacity; 
		opacity = FMath::InterpExpoOut(floatingBar->FillColorAndOpacity.A,
			(!masterController->LineOfSightTo(followTarget) || floatingBar->Percent <= .01f) ? 0 :
			FMath::Clamp((VisibleRadius - FVector::Dist(masterActor->GetActorLocation(), followTarget->GetActorLocation())) / VisibleRadius, 0.f, 1.f), 
			inDeltaTime * VisibilityTransitionSpeed);

		FLinearColor color = floatingBar->FillColorAndOpacity;
		color.A = opacity;
		floatingBar->SetFillColorAndOpacity(color);

		color = floatingBar->WidgetStyle.BackgroundImage.TintColor.GetSpecifiedColor();
		floatingBar->WidgetStyle.BackgroundImage.TintColor = FSlateColor(FLinearColor(color.R, color.G, color.B, opacity));
	}
	else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SagaGUI: can't find master actor for floating bar."));

	if (onTick.IsBound()) SetFillAmount(onTick.Execute());
}

