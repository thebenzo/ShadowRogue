// Fill out your copyright notice in the Description page of Project Settings.


#include "SRCharacter.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "GameFramework\CharacterMovementComponent.h"


// Sets default values
ASRCharacter::ASRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ASRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASRCharacter::MoveForward(float scale)
{
	FRotator ControllerRotator = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector ControllerForwardVector = ControllerRotator.Vector();

	AddMovementInput(ControllerForwardVector, scale);
}

void ASRCharacter::MoveRight(float scale)
{
	FRotator ControllerRotator = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	FVector ControllerRightVector = FRotationMatrix(ControllerRotator).GetScaledAxis(EAxis::Y);

	AddMovementInput(ControllerRightVector, scale);
}

void ASRCharacter::PrimaryAttack()
{
	FTransform SpawnTM = FTransform(GetControlRotation(), GetMesh()->GetSocketLocation("Muzzle_01"));

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParameters);
}

// Called every frame
void ASRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector DebugLineStart = GetActorLocation() + (GetActorRightVector() * 100.0f);
	FVector ActorDebugLineEnd = DebugLineStart + (GetActorForwardVector() * 100.0f);
	FVector ControllerDebugLineEnd = DebugLineStart + (GetControlRotation().Vector() * 100.0f);

	DrawDebugDirectionalArrow(GetWorld(), DebugLineStart, ActorDebugLineEnd, 100.0f, FColor::Green, false, 0.0f, 0, 5.0f);
	DrawDebugDirectionalArrow(GetWorld(), DebugLineStart, ControllerDebugLineEnd, 100.0f, FColor::Blue, false, 0.0f, 0, 5.0f);
}

// Called to bind functionality to input
void ASRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ASRCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ASRCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ASRCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASRCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASRCharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASRCharacter::PrimaryAttack);
}

