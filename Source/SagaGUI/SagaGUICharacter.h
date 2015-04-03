#pragma once

#include "GameFramework/Character.h"
#include "SagaGUICharacter.generated.h"

UCLASS()
class ASagaGUICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASagaGUICharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void ReceiveActorBeginOverlap(AActor* otherActor) override;
	virtual void ReceiveHit(class UPrimitiveComponent* myComp, AActor* otherActor, class UPrimitiveComponent* otherComp, 
		bool selfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit) override;

	virtual void Jump() override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

};

