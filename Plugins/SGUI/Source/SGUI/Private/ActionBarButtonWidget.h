#pragma once

#include "Blueprint/UserWidget.h"
#include "ActionBarButtonWidget.generated.h"

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
	UFUNCTION(BlueprintNativeEvent, meta = (FriendlyName = "Event On Click"), Category = "SagaGUI|ActionBar")
	void OnClick();
	virtual void OnClick_Implementation();

	/**
	*  Sets texture for the button.
	*  @param texture The texture to use.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Action Button Texture"), Category = "SagaGUI|ActionBar")
	void SetTexture(UTexture2D* texture);

private:
	static UActionBarButtonWidget* Create(UObject* worldContextObject);

	class UButton* actionButton;
	class UTextBlock* cdLabel;

};
