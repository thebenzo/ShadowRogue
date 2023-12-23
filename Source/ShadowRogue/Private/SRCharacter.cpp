// Fill out your copyright notice in the Description page of Project Settings.


#include "SRCharacter.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"


// Sets default values
ASRCharacter::ASRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ASRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASRCharacter::Move(float scale)
{
	AddMovementInput(GetActorForwardVector(), scale);
}

// Called every frame
void ASRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move", this, &ASRCharacter::Move);
	PlayerInputComponent->BindAxis("Turn", this, &ASRCharacter::AddControllerYawInput);
}

