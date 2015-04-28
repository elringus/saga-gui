#include "SGUI.h"
#include "InventoryWidget.h"

UInventoryWidget* UInventoryWidget::Create()
{
	auto widget = InstantiateWidget<UInventoryWidget>();

	return widget;
}



