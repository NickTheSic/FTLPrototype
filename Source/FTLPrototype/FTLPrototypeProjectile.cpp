// Copyright Epic Games, Inc. All Rights Reserved.

#include "FTLPrototypeProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "JustinFolder/FTLPrototypeHealthComponent.h"
#include "Kismet/GameplayStatics.h"

AFTLPrototypeProjectile::AFTLPrototypeProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFTLPrototypeProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	BaseDamage = 20.f;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AFTLPrototypeProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}

	AActor* Owner2 = GetOwner();

	if (Owner2)
	{
		UFTLPrototypeHealthComponent* Target = Cast<UFTLPrototypeHealthComponent>(OtherActor->GetComponentByClass(UFTLPrototypeHealthComponent::StaticClass())); //if actor has a health component
		if ((OtherActor != NULL) && (OtherActor != this) && OtherActor->ActorHasTag("BadGuys"))
		{
			//UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, nullptr, GetOwner(), DamageType);
			UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, Owner2->GetInstigatorController(), Owner2, DamageType);

			Destroy();
		}
	}
	



	//AActor* MyOwner = GetOwner();
	////AController* MyController = Cast<AController>(MyOwner->GetInstigatorController());
	////if (MyOwner)
	//{
	//	UFTLPrototypeHealthComponent* Target = Cast<UFTLPrototypeHealthComponent>(OtherActor->GetComponentByClass(UFTLPrototypeHealthComponent::StaticClass())); //if actor has a health component
	//	if (Target && Target->GetHealth() > 0.0f && OtherActor != this)
	//	{
	//		UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, MyOwner->GetInstigatorController(), MyOwner, DamageType);

	//		Destroy();
	//	}
	//}

}