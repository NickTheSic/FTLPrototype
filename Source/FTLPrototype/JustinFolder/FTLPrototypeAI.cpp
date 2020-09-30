// Fill out your copyright notice in the Description page of Project Settings.


#include "FTLPrototypeAI.h"
#include "FTLPrototypeWeapon.h"
#include "FTLPrototypeHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFTLPrototypeAI::AFTLPrototypeAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UFTLPrototypeHealthComponent>(TEXT("HealthComp"));

	WeaponAttachSocketName = "WeaponSocket";

	bDied = false;
	StopFiring = false;
}

// Called when the game starts or when spawned
void AFTLPrototypeAI::BeginPlay()
{
	Super::BeginPlay();

	HealthComp->OnHealthChanged.AddDynamic(this, &AFTLPrototypeAI::OnHealthChanged);

	//Spawn a default weapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentWeapon= GetWorld()->SpawnActor<AFTLPrototypeWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
	}
	
}

void AFTLPrototypeAI::Fire()
{
	if (CurrentWeapon && !StopFiring)
	{
		CurrentWeapon->Fire();
	}
}
void AFTLPrototypeAI::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}
void AFTLPrototypeAI::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}
void AFTLPrototypeAI::OnHealthChanged(UFTLPrototypeHealthComponent* InHealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//DrawDebugString(GetWorld(), GetActorLocation(), FString::SanitizeFloat(Health));

	if (Health <= 0 && !bDied)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSounds, GetActorLocation());
		bDied = true;

		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		DetachFromControllerPendingDestroy();

		SetLifeSpan(10.0f);
		CurrentWeapon->SetLifeSpan(10.0f);
	}
}

// Called every frame
void AFTLPrototypeAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFTLPrototypeAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

