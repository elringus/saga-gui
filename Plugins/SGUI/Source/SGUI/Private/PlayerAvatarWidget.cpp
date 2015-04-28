#include "SGUI.h"
#include "PlayerAvatarWidget.h"

UPlayerAvatarWidget* UPlayerAvatarWidget::Create()
{
	auto widget = InstantiateWidget<UPlayerAvatarWidget>();

	widget->avatarImage = Cast<UImage>(widget->GetWidgetFromName(TEXT("AvatarImage")));

	return widget;
}


void UPlayerAvatarWidget::SetTexture(UTexture2D* texture)
{
	avatarImage->SetBrushFromTexture(texture);
}
