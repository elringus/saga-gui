#include "SGUI.h"
#include "GroupStatusWidget.h"

UGroupStatusWidget* UGroupStatusWidget::Create(UObject* worldContextObject)
{
	auto widget = InstantiateWidget<UGroupStatusWidget>(worldContextObject);

	widget->groupWindowVertical = Cast<UVerticalBox>(widget->GetWidgetFromName(TEXT("GroupWindowVertical")));

	return widget;
}

UGroupMemberWidget* UGroupStatusWidget::AddGroupMember(UObject* worldContextObject, FText memberName)
{
	auto member = UGroupMemberWidget::Create(worldContextObject, memberName);

	members.Add(member);

	groupWindowVertical->AddChildVerticalBox(member);

	return member;
}

void UGroupStatusWidget::RemoveGroupMember(UObject* worldContextObject, UGroupMemberWidget* memberWidget)
{
	members.Remove(memberWidget);
	groupWindowVertical->RemoveChild(memberWidget);
	memberWidget->RemoveFromViewport();
}
