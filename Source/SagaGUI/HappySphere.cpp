#include "SagaGUI.h"
#include "HappySphere.h"


AHappySphere::AHappySphere()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AHappySphere::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHappySphere::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void AHappySphere::ReceiveActorBeginOverlap(AActor* otherActor)
{
	Destroy();
}
