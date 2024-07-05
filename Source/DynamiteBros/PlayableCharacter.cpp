// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Dynamite.h"
#include "DynamiteBrosGameMode.h"
#include "Components/PointLightComponent.h"

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

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	PointLightComponent->SetupAttachment(RootComponent);
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
	
	if(PointLightComponent){
		PointLightComponent->SetLightColor(ExplosionColor);
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
	
	// if we have a dynamite to drop
	if(DynamiteCount > 0){
		FVector DynamiteSpawnPointLocation = DynamiteSpawnPoint->GetComponentLocation();
		float RandomOffset = FMath::RandRange(0.f, 90.f);
		FRotator DynamiteSpawnPointRotation = DynamiteSpawnPoint->GetComponentRotation() + FRotator(0, RandomOffset, 0);

		ADynamite* Dynamite = GetWorld()->SpawnActor<ADynamite>(DynamiteClass, DynamiteSpawnPointLocation, DynamiteSpawnPointRotation);
		Dynamite->SetOwner(this);
		RemoveDynamite();
	}
}

void APlayableCharacter::DamageCharacter() {

	ADynamiteBrosGameMode* GameMode = GetWorld()->GetAuthGameMode<ADynamiteBrosGameMode>();
	if(GameMode){
		GameMode->PawnKilled(this);
	}

	DetachFromControllerPendingDestroy();
	Destroy();
}

void APlayableCharacter::SetUpCharacter(FString Name, FLinearColor Color) {
	
	SetPlayerName(Name);
	SetExplosionColor(Color);

	if(PointLightComponent){
		PointLightComponent->SetLightColor(ExplosionColor);
	}
}

void APlayableCharacter::ChangeCharacterMesh(USkeletalMesh* CharMesh) {

	USkeletalMeshComponent* CurrentMesh = GetMesh();
	CurrentMesh->SetSkeletalMesh(CharMesh);
}

int APlayableCharacter::GetDynamiteCount() const {
	return DynamiteCount;
}

void APlayableCharacter::AddDynamite() {
	DynamiteCount++;
}

void APlayableCharacter::RemoveDynamite() {
	DynamiteCount--;
}

void APlayableCharacter::SetSpeed(float Speed) {
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

float APlayableCharacter::GetSpeed() const {
	return GetCharacterMovement()->MaxWalkSpeed;
}

void APlayableCharacter::SetExplosionPower(int Power) {
	ExplosionPower = Power;
}

int APlayableCharacter::GetExplosionPower() const {
	return ExplosionPower;
}

FLinearColor APlayableCharacter::GetExplosionColor() const {
	return ExplosionColor;
}

void APlayableCharacter::SetExplosionColor(FLinearColor Color) {
	ExplosionColor = Color;
}

FString APlayableCharacter::GetPlayerName() const{
	return PlayerName;
}

void APlayableCharacter::SetPlayerName(FString Name){
	PlayerName = Name;
}