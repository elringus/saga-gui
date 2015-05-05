#pragma once

#include "Blueprint/UserWidget.h"
#include "ActionBarWidget.generated.h"

/**
 *  Widget for action bar. 
 *  Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UActionBarWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/**
	*  Creates action bar widget and adds it to the viewport.
	*  @param worldContextObject Any UObject to get world context from.
	*  @return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Create Action Bar", 
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|ActionBar")
	static UActionBarWidget* Create(UObject* worldContextObject);

	/**
	*  Adds an action button to the bar. 
	*  To implement OnClick event, use the returned UActionBarButtonWidget instance.
	*  @param worldContextObject Any UObject to get world context from.
	*  @param cooldown The cooldown of the action. Leave zero (default) to disable CD.
	*  @param buttonTexture The texture to use for the action button.
	*  @param tooltip The tooltip text to show on hover for the action button.
	*  @return Instance of the created button.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Add Action Button",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|ActionBar")
	UActionBarButtonWidget* AddActionButton(UObject* worldContextObject, float cooldown = 0, UTexture2D* buttonTexture = nullptr, FText tooltipTxt = FText::FromString(TEXT("")));

private:
	TArray<UActionBarButtonWidget*> buttons;

	class UHorizontalBox* actionBarHorizontal;
};
