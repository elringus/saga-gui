#pragma once

#include "Blueprint/UserWidget.h"
#include "GroupStatusWidget.generated.h"

/**
 *  Widget for group status window. 
 *  Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UGroupStatusWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/**
	*  Creates group status widget and adds it to the viewport.
	*  @param worldContextObject Any UObject to get world context from.
	*  @return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Group Status",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|GroupStatus")
	static UGroupStatusWidget* Create(UObject* worldContextObject);

	/**
	*  Adds group member to the group status window. 
	*  @param worldContextObject Any UObject to get world context from.
	*  @param memberName Name of the added group member.
	*  @return Instance of the created button.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Group Member",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|GroupStatus")
	UGroupMemberWidget* AddGroupMember(UObject* worldContextObject, FText memberName);

	/**
	*  Removes group member from the group status window.
	*  @param worldContextObject Any UObject to get world context from.
	*  @param memberWidget Widget of the group member to remove.
	*  @return Instance of the created button.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remove Group Member",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|GroupStatus")
	void RemoveGroupMember(UObject* worldContextObject, UGroupMemberWidget* memberWidget);

private:
	TArray<UGroupMemberWidget*> members;

	class UVerticalBox* groupWindowVertical;
};
