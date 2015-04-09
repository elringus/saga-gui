#pragma once

#include "Blueprint/UserWidget.h"
#include "FloatingTextWidget.generated.h"

/**
 *	Widget for floating text messages.
 *	As of the transient nature of the widget, it doesn't have the Create() method
 *	and won't return its intance. Instead, you will create messages by calling
 *	overloaded static Spawn() methods.
 *	The particular instances of the widget will be destroyed abutomatically.
 */
UCLASS()
class SAGAGUI_API UFloatingTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFloatingTextWidget(const class FObjectInitializer& objectInitializer);

	/* Floating speed of the messages. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI|Floating text parameters")
	float FloatingSpeed = 10.f;

	/* How fast the message will fade out. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SagaGUI|Floating text parameters")
	float FadeSpeed = 1.f;
	                                                                              
	/**
	*	Spawns a floating text message in the center of the screen.
	*	@param masterController Controller of the player, that will own the widget.
	*	@param message Message to show.
	*	@param color Text color of the message.
	*/
	UFUNCTION(BlueprintCallable, Category = "SagaGUI|FloatingTextWidget")
	static void Spawn(APlayerController* masterController, FString message, FLinearColor textColor = FLinearColor::White);

	/**
	*	Spawns a floating text message in the specified screen space position.
	*	@param masterController Controller of the player, that will own the widget.
	*	@param screenPosition Starting position of the message in the screen space coordinates.
	*	@param message Message to show.
	*	@param color Text color of the message.
	*/
	UFUNCTION(BlueprintCallable, Category = "SagaGUI|FloatingTextWidget")
	static void SpawnAtPosition(APlayerController* masterController, FVector2D screenPosition, FString message, FLinearColor textColor = FLinearColor::White);

	/**
	*	Spawns a floating text message relative to the specified target actor.
	*	@param masterController Controller of the player, that will own the widget.
	*	@param targetActor Actor, which position will be transposed to the sreen space and used as a starting point for the message.
	*	@param message Message to show.
	*	@param color Text color of the message.
	*/
	UFUNCTION(BlueprintCallable, Category = "SagaGUI|FloatingTextWidget")
	static void SpawnAtActor(APlayerController* masterController, AActor* targetActor, FString message, FLinearColor textColor = FLinearColor::White);

protected:
	virtual void Tick_Implementation(FGeometry myGeometry, float inDeltaTime) override;

private:
	static UFloatingTextWidget* Create(APlayerController* masterController, FString message, FLinearColor color);
	static TSubclassOf<class UFloatingTextWidget> widgetInstance;

	void SetColor(const FLinearColor& color);

	UPROPERTY() UTextBlock* messageLabel;
	
};
