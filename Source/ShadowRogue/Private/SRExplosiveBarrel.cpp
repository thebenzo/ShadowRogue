// Fill out your copyright notice in the Description page of Project Settings.


#include "SRExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASRExplosiveBarrel::ASRExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->SetAutoActivate(false);
	RadialForceComponent->Radius = 250.0f;
	RadialForceComponent->ImpulseStrength = 500.0f;
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

// Called when the game starts or when spawned
void ASRExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

}

void ASRExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Mesh->OnComponentHit.AddDynamic(this, &ASRExplosiveBarrel::OnComponentHit);
}

void ASRExplosiveBarrel::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();
}

// Called every frame
void ASRExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

