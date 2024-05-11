// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Dynamite.h"

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// turning off for now
	PrimaryActorTick.bCanEverTick = false;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->bIgnoreBaseRotation = true; // fix for physics bug that causes rotation on physics interaction

	DynamiteSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	DynamiteSpawnPoint->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// input mapping context
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller)){
		if(UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}
	}

}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up action bindings
	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)){
		// move action
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &APlayableCharacter::Move);
		// drop dynamite action
		EnhancedInputComponent->BindAction(DropInputAction, ETriggerEvent::Triggered, this, &APlayableCharacter::Drop);
	}

}


void APlayableCharacter::Move(const FInputActionValue& Value){

	FVector2D MovementVector = Value.Get<FVector2D>();

	if(Controller){
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayableCharacter::Drop() {
	// UE_LOG(LogTemp, Warning, TEXT("drop triggered"));

	FVector DynamiteSpawnPointLocation = DynamiteSpawnPoint->GetComponentLocation();
	FRotator DynamiteSpawnPointRotation = DynamiteSpawnPoint->GetComponentRotation();

	ADynamite* Dynamite = GetWorld()->SpawnActor<ADynamite>(DynamiteClass, DynamiteSpawnPointLocation, DynamiteSpawnPointRotation);
	Dynamite->SetOwner(this);
}

void APlayableCharacter::SetSpeed(float Speed) {
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

float APlayableCharacter::GetSpeed() const {
	return GetCharacterMovement()->MaxWalkSpeed;
}