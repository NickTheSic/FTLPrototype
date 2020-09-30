// Fill out your copyright notice in the Description page of Project Settings.


#include "FTLPrototypeWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Engine.h"
//#include "JustinFolder/FTLPrototypeAI.h"
#include "FTLPrototypeAI.h"
#include "FTLPrototypeHealthComponent.h"

// Sets default values
AFTLPrototypeWeapon::AFTLPrototypeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	MuzzleSocketName = "MuzzleSocket";
	TracerTargetName = "Target";

	BaseDamage = 5.f;

	MaxAmmo = 128.f; 
	CurrentAmmo = MaxAmmo;

	FireTimer = 0.f;
	TimeBetweenShots = 0.2f;
	BulletSpread = 12;

	//HitActor = nullptr;
}

// Called when the game starts or when spawned
void AFTLPrototypeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFTLPrototypeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentAmmo > MaxAmmo)
	{
		CurrentAmmo = MaxAmmo;
	}

	FireTimer -= DeltaTime;

	// HACK CODE - USE GAMESTATE GAMEOVER TO STOP ENEMIES SHOOTING WHEN DEAD
	/*if (HitActor && HitActor->ActorHasTag("Player"))
	{
		HitActorHealth = Cast<UFTLPrototypeHealthComponent>(HitActor->GetComponentByClass(UFTLPrototypeHealthComponent::StaticClass()));
	}*/
}

void AFTLPrototypeWeapon::Fire()
{
	if (CurrentAmmo > 0 && FireTimer <= 0)
	{
		// If player dies, dont let enemies fire!
		//if (HitActorHealth && HitActorHealth->bIsDead) //HACK CODE! get rid of when gamestates are introduced
		//{
		//	return;
		//}

		FireTimer = TimeBetweenShots;

		CurrentAmmo--;

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());

		AActor* MyOwner = GetOwner();
		if (MyOwner)
		{
			ACharacter* Character = Cast<ACharacter>(MyOwner); //You might have to change

			if (Character)
			{
				APlayerController* PC = Cast<APlayerController>(Character->GetController());
				if (PC)
				{
					//PC->AddPitchInput(3.2f); 
				}
			}

			FVector EyeLocation;
			FRotator EyeRotation;
			MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

			FVector ShotDirection = EyeRotation.Vector();

			// Bullet Spread
			float HalfRad = FMath::DegreesToRadians(BulletSpread);
			ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad);

			FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(MyOwner);
			QueryParams.AddIgnoredActor(this);
			QueryParams.bTraceComplex = true;
			//QueryParams.bReturnPhysicalMaterial = true;

			FVector TracerEndPoint = TraceEnd;

			FHitResult Hit;
			if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams)) //ECC_Visibility? I DONT KNOW
			{
				//AActor* HitActor = Hit.GetActor();
				HitActor = Hit.GetActor();

				// Implement head shots/ physic impact shot effects AFTER

				UGameplayStatics::ApplyPointDamage(HitActor, BaseDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(), MyOwner, DamageType);

				TracerEndPoint = Hit.ImpactPoint;
			}

			if (TracerEffect)
			{
				FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

				UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);
				if (TracerComp)
				{
					//TracerTargetName is an FName!!! Can be used here. Represents "Target" in constructor
					TracerComp->SetVectorParameter(TracerTargetName, TracerEndPoint);
				}
			}

			MakeNoise(320.0f);
		}	
	}
}

void AFTLPrototypeWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &AFTLPrototypeWeapon::Fire, TimeBetweenShots + 0.02, true, 0);
}

void AFTLPrototypeWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

