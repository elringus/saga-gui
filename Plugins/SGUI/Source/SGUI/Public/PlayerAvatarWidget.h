#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerAvatarWidget.generated.h"

/**
 *  Widget for player avatar. 
 *  Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UPlayerAvatarWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/**
	*  Creates player avatar widget and adds it to the viewport.
	*  @param worldContextObject Any UObject to get world context from.
	*  @return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Create Player Avatar", 
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|PlayerAvatar")
	static UPlayerAvatarWidget* Create(UObject* worldContextObject);

	/**
	*  Sets image of the player avatar.
	*  @param texture The texture to use with the image for player avatar.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Player Avatar Texture"), Category = "SagaGUI|PlayerAvatar")
	void SetTexture(UTexture2D* texture);

private:
	UImage* avatarImage;

};
