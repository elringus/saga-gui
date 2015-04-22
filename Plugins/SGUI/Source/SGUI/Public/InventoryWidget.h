#pragma once

#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
*	Widget for player inventory.
*   Institiates with the static Create() method.
*/
UCLASS()
class SGUI_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventoryWidget(const class FObjectInitializer& objectInitializer);

	/**
	*	Creates the widget and adds it to the viewport.
	*	@param masterController Controller of the player, that will own the widget.
	*	@return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, Category = "SagaGUI|InventoryWidget")
	static UInventoryWidget* Create(APlayerController* masterController);

private:
	static TSubclassOf<class UInventoryWidget> widgetInstance;
	
	
};
