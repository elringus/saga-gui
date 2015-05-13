#include "SGUI.h"
#include "AllyDotWidget.h"

UAllyDotWidget* UAllyDotWidget::Create(UObject* worldContextObject, AActor* followTarget, FVector offset)
{
	auto widget = InstantiateWidget<UAllyDotWidget>(worldContextObject, -100);
	widget->followTarget = followTarget;
	widget->offset = offset;

	widget->allyDotImage = Cast<UImage>(widget->GetWidgetFromName(TEXT("AllyDotImage")));

	return widget;
}

void UAllyDotWidget::SetHPRatio(const float& value)
{
	allyDotImage->SetColorAndOpacity(FLinearColor(1.0 - value, value, 0, allyDotImage->ColorAndOpacity.A));
}

void UAllyDotWidget::Tick_Implementation(FGeometry myGeometry, float deltaTime)
{
	Super::Tick_Implementation(myGeometry, deltaTime);

	if (!MasterController || !followTarget || followTarget->IsPendingKillPending()) { RemoveFromViewport(); return; }

	FVector targetLocation = followTarget->GetActorLocation() + offset;
	if (SetPositionFromWorld(targetLocation, GetSlot(allyDotImage)))
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
			deltaTime * VisibilityTransitionSpeed);
	}
	else opacity = 0;
	FLinearColor color = allyDotImage->ColorAndOpacity;
	color.A = opacity;
	allyDotImage->SetColorAndOpacity(color);

	if (onTick.IsBound()) SetHPRatio(onTick.Execute());
}


