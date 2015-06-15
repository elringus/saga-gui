#pragma once

#include "Blueprint/UserWidget.h"
#include "SagaButtonWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSagaButtonClicked);

/**
*  Base widget for buttons. 
*/
UCLASS()
class SGUI_API USagaButtonWidget : public USagaWidget
{
	GENERATED_BODY()

public:
	void InitializeButton(UButton* button);

	/**
	*  Event fires when user clicks the button.
	*/
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "Event On Clicked"), Category = "SagaGUI")
	FOnSagaButtonClicked OnSagaButtonClicked;

	/**
	*  Executes logic binded to FOnSagaButtonClicked event.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Do Click"), Category = "SagaGUI")
	virtual void DoClick();

	/**
	*  Sets texture for the button.
	*  @param texture The texture to use.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Button Texture"), Category = "SagaGUI")
	void SetTexture(UTexture2D* texture);

	/**
	*  Sets tooltip for the button to show on hover.
	*  @param text The tooltip text.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Button Tooltip"), Category = "SagaGUI")
	void SetTooltip(FText text);

protected:
	class UButton* button;

};
