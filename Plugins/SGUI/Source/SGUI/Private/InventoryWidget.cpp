#include "SGUI.h"
#include "InventoryWidget.h"

UInventoryWidget* UInventoryWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UInventoryWidget>(worldContextObject);

	return widget;
}



