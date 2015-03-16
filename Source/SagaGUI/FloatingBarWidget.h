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
	static UFloatingBarWidget* Create(APlayerController* masterController);
	
protected:
	virtual void OnWidgetRebuilt() override;

private:
	static TSubclassOf<class UFloatingBarWidget> widgetInstance;

};
