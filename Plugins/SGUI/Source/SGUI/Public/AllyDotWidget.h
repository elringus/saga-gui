#pragma once

#include "Blueprint/UserWidget.h"
#include "AllyDotWidget.generated.h"

/**
 *  Widget for showing status of an ally in form of a color dot. 
 *  Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UAllyDotWidget : public USagaWidget
{
	GENERATED_BODY()
	
public:
	/* Hide the widget, when distane between follow target and the master controller is more than this value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI")
	float VisibleRadius = 3000.f;

	/* Speed of revealing\hiding the widget, controlled by visible radius. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI")
	float VisibilityTransitionSpeed = 1.f;

	/**
	*  Creates an ally dot widget and adds it to the viewport.
	*  @param worldContextObject Any UObject to get world context from.
	*  @param followTarget An actor, which the widget will allign itsels with.
	*  @param offset Offset to the follow target location in world space.
	*  @return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Ally Dot",
		HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"), Category = "SagaGUI|AllyDot")
	static UAllyDotWidget* Create(UObject* worldContextObject, AActor* followTarget, FVector offset = FVector::ZeroVector);

	/**
	*  Sets red-to-green ratio for tint color of the ally dot image.
	*  @param value Ratio. Should be in 0.0 to 1.0 range.
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Ally Dot HP"), Category = "SagaGUI|AllyDot")
	void SetHPRatio(const float& value);

	/**
	*  Binds red-to-green ratio for tint color of the ally dot image.
	*  @param functor The lambda expression, which will be called on every tick to update the ratio.
	*    Should return float and take no parameters.
	*/
	template<typename FunctorType>
	FORCEINLINE void BindHPRatio(FunctorType&& functor) { onTick.BindLambda(Forward<FunctorType>(functor)); }

protected:
	virtual void NativeTick(const FGeometry& myGeometry, float deltaTime) override;

private:
	UImage* allyDotImage;
	AActor* followTarget;
	FVector offset;

	DECLARE_DELEGATE_RetVal(float, FOnTick)
	FOnTick onTick;
	
};
