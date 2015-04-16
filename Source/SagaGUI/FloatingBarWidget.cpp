#include "SagaGUI.h"
#include "FloatingBarWidget.h"

TSubclassOf<class UFloatingBarWidget> UFloatingBarWidget::widgetInstance;

UFloatingBarWidget::UFloatingBarWidget(const class FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> widgetBP(TEXT("WidgetBlueprint'/Game/UMG/FloatingBar.FloatingBar'"));
	if (widgetBP.Succeeded()) widgetInstance = (UClass*)widgetBP.Object->GeneratedClass;
}

UFloatingBarWidget* UFloatingBarWidget::Create(APlayerController* masterController, AActor* followTarget, FVector offset, FLinearColor barColor)
{
	auto widget = CreateWidget<UFloatingBarWidget>(masterController, widgetInstance);
	widget->followTarget = followTarget;
	widget->masterController = masterController;
	widget->AddToViewport();
	widget->offset = offset;

	widget->floatingBar = Cast<UProgressBar>(widget->GetWidgetFromName(TEXT("FloatingBar")));
	widget->floatingBar->SetFillColorAndOpacity(barColor);
	widget->hpLabel = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("HPLabel")));

	widget->SetOpacity(0);

	return widget;
}

void UFloatingBarWidget::SetFillAmount(const float& value)
{
	floatingBar->SetPercent(value);
	hpLabel->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), (uint8)(floatingBar->Percent * 100))));
}

void UFloatingBarWidget::Tick_Implementation(FGeometry myGeometry, float inDeltaTime)
{
	if (!masterController || !followTarget || followTarget->IsPendingKill()) RemoveFromViewport();

	FVector2D screenPos; 
	if (Cast<APlayerController>(masterController)->ProjectWorldLocationToScreen(followTarget->GetActorLocation() + offset, screenPos))
	{
		floatingBar->SetVisibility(ESlateVisibility::Visible);

		Scalability::FQualityLevels scalabilityQuality = Scalability::GetQualityLevels();
		float qualityScale = (scalabilityQuality.ResolutionQuality / 100.0f);

		SetPositionInViewport(screenPos / qualityScale - FVector2D(Cast<UCanvasPanelSlot>(floatingBar->Slot)->GetSize().X / 2, 0));
	}
	else
	{
		floatingBar->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	if (masterController->GetPawn())
	{
		float opacity; 
		opacity = FMath::InterpExpoOut(floatingBar->FillColorAndOpacity.A,
			(!masterController->LineOfSightTo(followTarget) || floatingBar->Percent <= .01f) ? 0 :
			FMath::Clamp((VisibleRadius - FVector::Dist(masterController->GetPawn()->GetActorLocation(), followTarget->GetActorLocation())) / VisibleRadius, 0.f, 1.f),
			inDeltaTime * VisibilityTransitionSpeed);

		SetOpacity(opacity);
	}
	else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SagaGUI: can't find master actor for floating bar."));

	if (onTick.IsBound()) SetFillAmount(onTick.Execute());
}

void UFloatingBarWidget::SetOpacity(float opacity)
{
	FLinearColor color = floatingBar->FillColorAndOpacity;
	color.A = opacity;
	floatingBar->SetFillColorAndOpacity(color);

	color = floatingBar->WidgetStyle.BackgroundImage.TintColor.GetSpecifiedColor();
	floatingBar->WidgetStyle.BackgroundImage.TintColor = FSlateColor(FLinearColor(color.R, color.G, color.B, opacity));

	color = hpLabel->ColorAndOpacity.GetSpecifiedColor();
	color.A = opacity;
	hpLabel->SetColorAndOpacity(color);
	color = hpLabel->ShadowColorAndOpacity;
	color.A = FMath::Clamp(color.A - .2f, 0.f, 1.f);
	hpLabel->SetShadowColorAndOpacity(color);
}
