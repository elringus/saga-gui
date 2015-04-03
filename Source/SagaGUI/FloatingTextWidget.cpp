#include "SagaGUI.h"
#include "FloatingTextWidget.h"

TSubclassOf<class UFloatingTextWidget> UFloatingTextWidget::widgetInstance;

UFloatingTextWidget::UFloatingTextWidget(const class FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> widgetBP(TEXT("WidgetBlueprint'/Game/UMG/FloatingText.FloatingText'"));
	if (widgetBP.Succeeded()) widgetInstance = (UClass*)widgetBP.Object->GeneratedClass;
}

UFloatingTextWidget* UFloatingTextWidget::Create(APlayerController* masterController, FString message, FLinearColor color)
{
	auto widget = CreateWidget<UFloatingTextWidget>(masterController, widgetInstance);
	widget->AddToViewport();
	widget->messageLabel = Cast<UTextBlock>(widget->GetWidgetFromName(TEXT("MessageLabel")));
	widget->messageLabel->SetText(FText::FromString(message));
	widget->SetColor(color);

	return widget;
}

void UFloatingTextWidget::Spawn(APlayerController* masterController, FString message, FLinearColor color /*= FLinearColor::White*/)
{
	auto widget = Create(masterController, message, color);

	const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D viewportCenter = FVector2D(viewportSize.X / 2, viewportSize.Y / 2);
	(Cast<UCanvasPanelSlot>(widget->messageLabel->Slot))->SetPosition(viewportCenter);
}

void UFloatingTextWidget::Spawn(APlayerController* masterController, FVector2D screenPosition, FString message, FLinearColor color /*= FLinearColor::White*/)
{
	auto widget = Create(masterController, message, color);

	(Cast<UCanvasPanelSlot>(widget->messageLabel->Slot))->SetPosition(screenPosition);
}

void UFloatingTextWidget::Spawn(APlayerController* masterController, AActor* targetActor, FString message, FLinearColor color /*= FLinearColor::White*/)
{
	auto widget = Create(masterController, message, color);

	FVector2D screenPos;
	masterController->ProjectWorldLocationToScreen(targetActor->GetActorLocation(), screenPos);
	(Cast<UCanvasPanelSlot>(widget->messageLabel->Slot))->SetPosition(screenPos);
}

void UFloatingTextWidget::Tick_Implementation(FGeometry myGeometry, float inDeltaTime)
{
	(Cast<UCanvasPanelSlot>(messageLabel->Slot))->SetPosition((Cast<UCanvasPanelSlot>(messageLabel->Slot))->GetPosition() + FVector2D(0, FloatingSpeed * inDeltaTime));
}

void UFloatingTextWidget::SetColor(const FLinearColor& color)
{
	messageLabel->SetColorAndOpacity(color);
	auto shadowColor = messageLabel->ShadowColorAndOpacity;
	// base shadow opacity is .8 (.2 less than base text opacity), so excluding it
	messageLabel->SetShadowColorAndOpacity(FLinearColor(shadowColor.R, shadowColor.G, shadowColor.B, FMath::Clamp(color.A - .2f, 0.f, 1.f)));
}


