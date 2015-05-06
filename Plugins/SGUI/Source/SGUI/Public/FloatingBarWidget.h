#pragma once

#include "Blueprint/UserWidget.h"
#include "FloatingBarWidget.generated.h"

/**
 *  Widget for floating bars. 
 *  Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UFloatingBarWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/* Hide the widget, when distane between follow target and the master controller is more than this value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI")
	float VisibleRadius = 1500.f;

	/* Speed of revealing\hiding the widget, controlled by visible radius. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI")
	float VisibilityTransitionSpeed = 5.f;

	/** 
	 *  Creates a floating bar widget and adds it to the viewport.
	 *  @param worldContextObject Any UObject to get world context from.
	 *  @param followTarget An actor, which the widget will allign itsels with.
	 *  @param offset Offset to the follow target location in world space.
	 *  @param barColor Fill color of the bar.
	 *  @return Instance of the created widget.
	 */
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Create Floating Bar", 
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|FloatingBar")
	static UFloatingBarWidget* Create(UObject* worldContextObject, AActor* followTarget, FVector offset = FVector::ZeroVector, FLinearColor fillColor = FLinearColor::Red);

	/**
	*  Sets player name that will appear with the bar.
	*  @param value Player name text.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Player Name"), Category = "SagaGUI|FloatingBar")
	void SetPlayerName(FText value);

	/**
	 *  Sets fill amount of the floating bar. 
	 *  @param value Fill value. Should be in 0.0 to 1.0 range.
	 */
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Floating Bar HP"), Category = "SagaGUI|FloatingBar")
	void SetFillAmount(const float& value);
	
	/**
	*  Binds fill amount of the progress bar.
	*  @param functor The lambda expression, which will be called on every tick to update fill value. 
	*  Should return float and take no parameters.
	*/
	template<typename FunctorType>
	void BindFillAmount(FunctorType&& functor) { onTick.BindLambda(Forward<FunctorType>(functor)); }

	/**
	*  Sets fill color of the progress bar.
	*  @param fillColor The color.
	*/
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Set Floating Bar Color"), Category = "SagaGUI|FloatingBar")
	void SetFillColor(FLinearColor fillColor);

protected:
	virtual void Tick_Implementation(FGeometry myGeometry, float deltaTime) override;

private:
	class UProgressBar* floatingBar;
	class AActor* followTarget;
	class UTextBlock* hpLabel;
	class UTextBlock* nameLabel;
	FVector offset;

	DECLARE_DELEGATE_RetVal(float, FOnTick)
	FOnTick onTick;

	void SetOpacity(float opacity);
};
