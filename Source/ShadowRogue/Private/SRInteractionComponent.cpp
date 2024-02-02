// Fill out your copyright notice in the Description page of Project Settings.


#include "SRInteractionComponent.h"
#include "SRGameplayInterface.h"

// Sets default values for this component's properties
USRInteractionComponent::USRInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	range = 1000.0f;
	// ...
}


// Called when the game starts
void USRInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USRInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USRInteractionComponent::Interact()
{
	AActor* owner = GetOwner();

	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	const float radius = 30.0f;
	FCollisionShape collisionShape;
	collisionShape.SetSphere(radius);

	FVector eyeLocation;
	FRotator eyeRotation;
	owner->GetActorEyesViewPoint(eyeLocation, eyeRotation);

	FVector end = eyeLocation + (eyeRotation.Vector() * range);

	TArray<FHitResult> hitResults;
	bool bHit = GetWorld()->SweepMultiByObjectType(hitResults, eyeLocation, end, FQuat::Identity, objectQueryParams, collisionShape);

	FColor lineColor = bHit ? FColor::Green : FColor::Red;

	for (FHitResult hit : hitResults)
	{
		DrawDebugSphere(GetWorld(), hit.ImpactPoint, radius, 32, lineColor, false, 2.0f);

		AActor* hitActor = hit.GetActor();
		if (hitActor)
		{
			if (hitActor->Implements<USRGameplayInterface>())
			{
				APawn* instigatorPawn = Cast<APawn>(owner);
				ISRGameplayInterface::Execute_Interact(hitActor, instigatorPawn);

				break;
			}
		}
	}

	DrawDebugLine(GetWorld(), eyeLocation, end, lineColor, false, 2.0f, 0, 1.0f);
}

