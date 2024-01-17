// Fill out your copyright notice in the Description page of Project Settings.


#include "SRMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASRMagicProjectile::ASRMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	RootComponent = SphereComponent;
	SphereComponent->SetCollisionProfileName("Projectile");
	SphereComponent->SetSphereRadius(16.0f);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	ParticleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASRMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASRMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

