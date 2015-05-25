#include "SGUI.h"
#include "PlayerAvatarWidget.h"

UPlayerAvatarWidget* UPlayerAvatarWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UPlayerAvatarWidget>(worldContextObject);
	if (!widget) return nullptr;

	widget->avatarImage = Cast<UImage>(widget->GetWidgetFromName(TEXT("AvatarImage")));

	return widget;
}


void UPlayerAvatarWidget::SetTexture(UTexture2D* texture)
{
	avatarImage->SetBrushFromTexture(texture);
}
