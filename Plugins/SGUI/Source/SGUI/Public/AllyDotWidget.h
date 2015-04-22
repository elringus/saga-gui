#pragma once

#include "Blueprint/UserWidget.h"
#include "AllyDotWidget.generated.h"

/**
 *	Widget for showing status of an ally in form of a color dot. 
 *	Institiates with the static Create() method.
 */
UCLASS()
class SGUI_API UAllyDotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UAllyDotWidget(const class FObjectInitializer& objectInitializer);

	/* Hide the widget, when distane between follow target and the master controller is more than this value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI|AllyDotWidget")
	float VisibleRadius = 3000.f;

	/* Speed of revealing\hiding the widget, controlled by visible radius. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI|AllyDotWidget")
	float VisibilityTransitionSpeed = 5.f;

	/**
	*	Creates the widget and adds it to the viewport.
	*	@param masterController Controller of the player, that will own the widget.
	*	@param followTarget An actor, which the widget will allign itsels with.
	*	@param offset Offset to the follow target location in world space.
	*	@return Instance of the created widget.
	*/
	UFUNCTION(BlueprintCallable, Category = "SagaGUI|AllyDotWidget")
	static UAllyDotWidget* Create(APlayerController* masterController, AActor* followTarget, FVector offset = FVector::ZeroVector);

	/**
	*	Sets the red-to-green ratio for tint color of the dot image.
	*	@param value Ratio. Should be in 0.0 to 1.0 range.
	*/
	UFUNCTION(BlueprintCallable, Category = "SagaGUI|AllyDotWidget")
	void SetHPRatio(const float& value);

	/**
	*	Binds the red-to-green ratio for tint color of the dot image.
	*	@param functor The lambda expression, which will be called on every tick to update the ratio.
	*	Should return float and take no parameters.
	*/
	template<typename FunctorType>
	FORCEINLINE void BindHPRatio(FunctorType&& functor) { onTick.BindLambda(Forward<FunctorType>(functor)); }

protected:
	virtual void Tick_Implementation(FGeometry myGeometry, float inDeltaTime) override;

private:
	static TSubclassOf<class UAllyDotWidget> widgetInstance;

	UPROPERTY() UImage* allyDotImage;
	UPROPERTY() AActor* followTarget;
	UPROPERTY() AController* masterController;
	UPROPERTY() FVector offset;

	DECLARE_DELEGATE_RetVal(float, FOnTick)
	FOnTick onTick;
	
};
