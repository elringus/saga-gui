#include "SagaGUI.h"
#include "SagaGUICharacter.h"

ASagaGUICharacter::ASagaGUICharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

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
		if (actorIt->GetActorLabel().Contains(TEXT("EnemySphere")))
		{
			auto floatingBar = UFloatingBarWidget::Create(Cast<APlayerController>(GetController()), *actorIt, FVector(0, 0, 150));
			floatingBar->BindFillAmount([=]()->float{ return FMath::Abs(FMath::Sin(GetWorld()->TimeSeconds)) + .1f; });
		}
		else if (actorIt->GetActorLabel().Contains(TEXT("FriendSphere")))
		{
			auto allyDot = UAllyDotWidget::Create(Cast<APlayerController>(GetController()), *actorIt, FVector(0, 0, 150));
			auto location = actorIt->GetActorLocation();
			allyDot->BindHPRatio([=]()->float{ return 500.f / FVector::Dist(GetActorLocation(), location); });
		}
	}

	//UInventoryWidget::Create(Cast<APlayerController>(GetController()));
}

void ASagaGUICharacter::ReceiveActorBeginOverlap(AActor* otherActor)
{
	UFloatingTextWidget::SpawnAtActor(Cast<APlayerController>(GetController()), otherActor, FString::Printf(TEXT("Collided with %s"), *otherActor->GetName()));
}

void ASagaGUICharacter::ReceiveHit(class UPrimitiveComponent* myComp, AActor* otherActor, class UPrimitiveComponent* otherComp, bool selfMoved, 
	FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit)
{
	//UFloatingTextWidget::Spawn(Cast<APlayerController>(GetController()), FString::Printf(TEXT("Kicked %s"), *otherActor->GetName()), FLinearColor::Red);
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
