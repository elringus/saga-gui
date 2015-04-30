#include "SGUI.h"
#include "ActionBarWidget.h"

UActionBarWidget* UActionBarWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UActionBarWidget>(worldContextObject);

	//widget->avatarImage = Cast<UImage>(widget->GetWidgetFromName(TEXT("AvatarImage")));

	return widget;
}
