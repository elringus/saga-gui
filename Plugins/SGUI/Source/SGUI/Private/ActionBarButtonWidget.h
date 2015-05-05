#pragma once

#include "Blueprint/UserWidget.h"
#include "ActionBarButtonWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionBarButtonClicked);

/**
*  Widget for action bar button. 
*  Should not be instantiated manually.
*/
UCLASS()
class SGUI_API UActionBarButtonWidget : public USagaWidget
{
	GENERATED_BODY()

	friend class UActionBarWidget;

public:
	/**
	*  Event fires when user clicks the button.
	*/
	UPROPERTY(BlueprintAssignable, meta = (FriendlyName = "Event On Clicked"), Category = "SagaGUI|ActionBar")
	FOnActionBarButtonClicked OnActionBarButtonClicked;

	/**
	*  Sets texture for the button.
	*  @param texture The texture to use.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Action Button Texture"), Category = "SagaGUI|ActionBar")
	void SetTexture(UTexture2D* texture);

	/**
	*  Sets tooltip for the button to show on hover.
	*  @param text The tooltip text.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Action Button Tooltip"), Category = "SagaGUI|ActionBar")
	void SetTooltip(FText text);

	/**
	*  Calls functions binded to the FOnActionBarButtonClicked event of the button.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Fire On Button Clicked Event"), Category = "SagaGUI|ActionBar")
	void FireOnClicked();

protected:
	virtual void Tick_Implementation(FGeometry myGeometry, float deltaTime) override;

private:
	static UActionBarButtonWidget* Create(UObject* worldContextObject, float cooldown);

	class UButton* actionButton;
	class UTextBlock* cdLabel;

	float cd = 0.f;
	float cdTimer = 0.f;
};
