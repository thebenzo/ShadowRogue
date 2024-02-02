// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRGameplayInterface.h"
#include "SRTreasureChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class SHADOWROGUE_API ASRTreasureChest : public AActor, public ISRGameplayInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	float TargetLidPitch;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ChestBaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ChestLidMesh;
	
public:	
	// Sets default values for this actor's properties
	ASRTreasureChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Interact_Implementation(APawn* InstigatorPawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
