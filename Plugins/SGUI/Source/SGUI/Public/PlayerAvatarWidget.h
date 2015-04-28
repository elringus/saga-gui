#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerAvatarWidget.generated.h"

/**
 *	Widget for player avatar. 
 *  Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UPlayerAvatarWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/**
	*	Creates player avatar widget and adds it to the viewport.
	*	@return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Create Player Avatar"), Category = "SagaGUI|PlayerAvatar")
	static UPlayerAvatarWidget* Create();

	/**
	*	Sets image of the player avatar.
	*	@param value The image.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Player Avatar Image"), Category = "SagaGUI|PlayerAvatar")
	void SetImage(const float& value);

private:
	UImage* avatarImage;

};
