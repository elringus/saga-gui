#pragma once

#include "Blueprint/UserWidget.h"
#include "FloatingBarWidget.generated.h"

/**
 * Widget for floating bars.
 */
UCLASS()
class SAGAGUI_API UFloatingBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFloatingBarWidget(const class FObjectInitializer& objectInitializer);
	static UFloatingBarWidget* Create(APlayerController* masterController, AActor* followTarget);

	FORCEINLINE void SetPercent(const float& value) { floatingBar->SetPercent(value); }

	class AActor* FollowTarget;
	
protected:
	virtual void OnWidgetRebuilt() override;
	virtual void Tick_Implementation(FGeometry MyGeometry, float InDeltaTime) override;

private:
	static TSubclassOf<class UFloatingBarWidget> widgetInstance;
	class UProgressBar* floatingBar;
};
