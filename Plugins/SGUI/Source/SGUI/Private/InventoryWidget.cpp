#include "SGUI.h"
#include "InventoryWidget.h"

UInventoryWidget* UInventoryWidget::Create(APlayerController* masterController)
{
	auto widget = InstantiateWidget<UInventoryWidget>(masterController);

	return widget;
}



