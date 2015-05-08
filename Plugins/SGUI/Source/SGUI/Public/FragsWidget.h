#pragma once

#include "Blueprint/UserWidget.h"
#include "FragsWidget.generated.h"

/**
*  Widget for frags.
*  Institiates with the static Create() method.
*/
UCLASS()
class SGUI_API UFragsWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/**
	*  Creates a frags widget and adds it to the viewport.
	*  @param worldContextObject Any UObject to get world context from.
	*  @return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Create Frags", 
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|Frags")
	static UFragsWidget* Create(UObject* worldContextObject);

	/**
	 *  Sets frag count. 
	 *  @param value Frag count to set.
	 */
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Frags Count"), Category = "SagaGUI|Frags")
	void SetFragsCount(int32 value);

private:
	class UTextBlock* fragsLabel;
	
};
