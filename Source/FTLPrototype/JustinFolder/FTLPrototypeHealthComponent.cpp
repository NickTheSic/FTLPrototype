// Fill out your copyright notice in the Description page of Project Settings.


#include "FTLPrototypeHealthComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UFTLPrototypeHealthComponent::UFTLPrototypeHealthComponent()
{
	// ...
	// TeamNum = 255;

	DefaultHealth = 100;
	bIsDead = false;
}


// Called when the game starts
void UFTLPrototypeHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UFTLPrototypeHealthComponent::HandleTakeAnyDamage);
	}

	Health = DefaultHealth;
}

void UFTLPrototypeHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || bIsDead)
	{
		return;
	}

	// DONT USE THIS CODE UNTIL LATER
	//if (DamageCauser != DamagedActor && IsFriendly(DamagedActor, DamageCauser)) //both are AActors with Healthcomponents
	//{
	//	return;
	//}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Log, TEXT("Health Changed: %s"), *FString::SanitizeFloat(Health));

	bIsDead = Health <= 0.0f;

	//sees if the player is dead or not.
	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser); 

	// DONT USE THIS CODE UNTIL LATER
	/*if (bIsDead)
	{
		ASGameMode* GM = Cast<ASGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			GM->OnActorKilled.Broadcast(GetOwner(), DamageCauser, InstigatedBy);
		}
	}*/
}

void UFTLPrototypeHealthComponent::Heal(float HealAmount)
{
	if (HealAmount <= 0 || Health <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health + HealAmount, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Log, TEXT("Health Changed: %s (+%s)"), *FString::SanitizeFloat(Health), *FString::SanitizeFloat(HealAmount));
	
	OnHealthChanged.Broadcast(this, Health, -HealAmount, nullptr, nullptr, nullptr); //if health is less then 0, then die.
}

float UFTLPrototypeHealthComponent::GetHealth() const
{
	return Health;
}

