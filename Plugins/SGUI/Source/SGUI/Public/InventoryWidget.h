#pragma once

#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
*  Widget for player inventory.
*  Institiates with the static Create() method.
*/
UCLASS()
class SGUI_API UInventoryWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/**
	*  Creates an inventory window widget and adds it to the viewport.
	*  @param worldContextObject Any UObject to get world context from.
	*  @return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Create Inventory Window", 
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|Inventory")
	static UInventoryWidget* Create(UObject* worldContextObject);
	
};
