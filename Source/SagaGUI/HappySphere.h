#pragma once

#include "GameFramework/Actor.h"
#include "HappySphere.generated.h"

UCLASS(Blueprintable)
class SAGAGUI_API AHappySphere : public AActor
{
	GENERATED_BODY()
	
public:	
	AHappySphere();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

	virtual void ReceiveActorBeginOverlap(AActor* otherActor) override;
	
};
