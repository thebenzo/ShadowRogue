// Fill out your copyright notice in the Description page of Project Settings.


#include "SRTreasureChest.h"

// Sets default values
ASRTreasureChest::ASRTreasureChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChestBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseStaticMesh");
	RootComponent = ChestBaseMesh;

	ChestLidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidStaticMesh");
	ChestLidMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASRTreasureChest::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASRTreasureChest::Interact_Implementation(APawn* InstigatorPawn)
{
	ChestLidMesh->SetRelativeRotation(FRotator(TargetLidPitch, 0.0f, 0.0f));
}

// Called every frame
void ASRTreasureChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

