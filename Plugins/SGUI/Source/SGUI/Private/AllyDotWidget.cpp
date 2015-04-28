#include "SGUI.h"
#include "AllyDotWidget.h"

UAllyDotWidget* UAllyDotWidget::Create(AActor* followTarget, FVector offset)
{
	auto widget = InstantiateWidget<UAllyDotWidget>();
	widget->followTarget = followTarget;
	widget->offset = offset;

	widget->allyDotImage = Cast<UImage>(widget->GetWidgetFromName(TEXT("AllyDotImage")));

	return widget;
}

void UAllyDotWidget::SetHPRatio(const float& value)
{
	allyDotImage->SetColorAndOpacity(FLinearColor(1.0 - value, value, 0, allyDotImage->ColorAndOpacity.A));
}

void UAllyDotWidget::Tick_Implementation(FGeometry myGeometry, float inDeltaTime)
{
	if (!MasterController || !followTarget || followTarget->IsPendingKill()) RemoveFromViewport();

	FVector targetLocation = followTarget->GetActorLocation() + offset;
	auto pivotCorrection = FVector2D(GetSlot(allyDotImage)->GetSize().X / 2, 0) * GetViewportScale();
	if (SetPositionFromWorld(targetLocation, pivotCorrection))
	{
		allyDotImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		allyDotImage->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	float opacity;
	if (MasterController->GetPawn())
	{
		opacity = FMath::InterpExpoOut(allyDotImage->ColorAndOpacity.A,
			(allyDotImage->ColorAndOpacity.G <= .01f) ? 0 :
			FMath::Clamp((VisibleRadius - FVector::Dist(MasterController->GetPawn()->GetActorLocation(), followTarget->GetActorLocation())) / VisibleRadius, 0.f, 1.f),
			inDeltaTime * VisibilityTransitionSpeed);
	}
	else opacity = 0;
	FLinearColor color = allyDotImage->ColorAndOpacity;
	color.A = opacity;
	allyDotImage->SetColorAndOpacity(color);

	if (onTick.IsBound()) SetHPRatio(onTick.Execute());
}


