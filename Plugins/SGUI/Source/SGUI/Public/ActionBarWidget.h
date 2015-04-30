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

private:
	

};
