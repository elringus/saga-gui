#include "SGUI.h"
#include "PlayerAvatarWidget.h"

UPlayerAvatarWidget* UPlayerAvatarWidget::Create()
{
	auto widget = InstantiateWidget<UPlayerAvatarWidget>();

	widget->avatarImage = Cast<UImage>(widget->GetWidgetFromName(TEXT("AvatarImage")));

	return widget;
}


void UPlayerAvatarWidget::SetImage(const float& value)
{

}
