#include "SagaGUI.h"
#include "SagaGUICharacter.h"

ASagaGUICharacter::ASagaGUICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASagaGUICharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ASagaGUICharacter::OnOverlapEnd);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 
}

void ASagaGUICharacter::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AActor> actorIt(GetWorld()); actorIt; ++actorIt)
	{
		if (actorIt->GetActorLabel().Equals(TEXT("HappySphere")))
		{
			auto floatingBar = UFloatingBarWidget::Create(Cast<APlayerController>(GetController()), *actorIt, FVector(0, 0, 100));
			floatingBar->BindFillAmount([=]()->float{ return FMath::Abs(FMath::Sin(GetWorld()->TimeSeconds)) + .1f; });
		}
	}

	auto hpBar = UPlayerHPWidget::Create(Cast<APlayerController>(GetController()));
	hpBar->BindFillAmount([=]()->float{ return FMath::Abs(FMath::Cos(GetWorld()->TimeSeconds)) + .1f; });
}

void ASagaGUICharacter::OnOverlapBegin(class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor && (otherActor != this) && otherComp) 
	{
		UFloatingTextWidget::Spawn(Cast<APlayerController>(GetController()), FString::Printf(TEXT("Happy collided with %s"), *otherActor->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *otherActor->GetName());
	}
}

void ASagaGUICharacter::OnOverlapEnd(class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{

}

#pragma region Control
void ASagaGUICharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &ASagaGUICharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASagaGUICharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ASagaGUICharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ASagaGUICharacter::LookUpAtRate);

	InputComponent->BindTouch(IE_Pressed, this, &ASagaGUICharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ASagaGUICharacter::TouchStopped);
}

void ASagaGUICharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1) Jump();
}

void ASagaGUICharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1) StopJumping();
}

void ASagaGUICharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASagaGUICharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASagaGUICharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		//floatingBar->SetPercent(1.f);

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASagaGUICharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		//floatingBar->SetPercent(.5f);

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
#pragma endregion
