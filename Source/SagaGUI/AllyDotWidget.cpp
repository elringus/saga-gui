#include "SagaGUI.h"
#include "AllyDotWidget.h"

TSubclassOf<class UAllyDotWidget> UAllyDotWidget::widgetInstance;

UAllyDotWidget::UAllyDotWidget(const class FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> widgetBP(TEXT("WidgetBlueprint'/Game/UMG/AllyDot.AllyDot'"));
	if (widgetBP.Succeeded()) widgetInstance = (UClass*)widgetBP.Object->GeneratedClass;
}

UAllyDotWidget* UAllyDotWidget::Create(APlayerController* masterController, AActor* followTarget, FVector offset)
{
	auto widget = CreateWidget<UAllyDotWidget>(masterController, widgetInstance);
	widget->followTarget = followTarget;
	widget->masterController = masterController;
	widget->masterActor = masterController->GetPawn();
	widget->AddToViewport();
	widget->offset = offset;

	widget->allyDotImage = Cast<UImage>(widget->GetWidgetFromName(TEXT("AllyDotImage")));

	return widget;
}

void UAllyDotWidget::Tick_Implementation(FGeometry myGeometry, float inDeltaTime)
{
	FVector2D screenPos;
	if (Cast<APlayerController>(masterController)->ProjectWorldLocationToScreen(followTarget->GetActorLocation() + offset, screenPos)) 
	{
		allyDotImage->SetVisibility(ESlateVisibility::Visible);

		Scalability::FQualityLevels scalabilityQuality = Scalability::GetQualityLevels();
		float qualityScale = (scalabilityQuality.ResolutionQuality / 100.0f);

		SetPositionInViewport(screenPos / qualityScale - FVector2D(Cast<UCanvasPanelSlot>(allyDotImage->Slot)->GetSize().X / 2, 0));
	}
	else 
	{
		allyDotImage->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	if (masterActor)
	{
		float opacity;
		opacity = FMath::InterpExpoOut(allyDotImage->ColorAndOpacity.A,
			(allyDotImage->ColorAndOpacity.G <= .01f) ? 0 :
			FMath::Clamp((VisibleRadius - FVector::Dist(masterActor->GetActorLocation(), followTarget->GetActorLocation())) / VisibleRadius, 0.f, 1.f),
			inDeltaTime * VisibilityTransitionSpeed);

		FLinearColor color = allyDotImage->ColorAndOpacity;
		color.A = opacity;
		allyDotImage->SetColorAndOpacity(color);
	}
	else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SagaGUI: can't find master actor for floating bar."));

	if (onTick.IsBound()) SetHPRatio(onTick.Execute());
}


