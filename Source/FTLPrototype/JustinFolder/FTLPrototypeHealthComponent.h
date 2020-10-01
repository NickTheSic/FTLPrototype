// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FTLPrototypeHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, UFTLPrototypeHealthComponent*, HealthComp, float, Health, float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FTLPROTOTYPE_API UFTLPrototypeHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFTLPrototypeHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(BlueprintReadOnly, Category = "HealthComponent")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float DefaultHealth;

	UPROPERTY(BlueprintReadOnly, Category = "OxygenComponent")
		float fOxygen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OxygenComponent")
		float fDefaultOxygen;
	
	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	bool bIsDead;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void Heal(float HealAmount);

	//UFUNCTION(BlueprintCallable, BlueprintPure, Category = "HealthComponent")
	//static bool IsFriendly(AActor* ActorA, AActor* ActorB);

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
		void SetHealth(float val) { Health = val; }
		
	UFUNCTION(BlueprintCallable)
		float GetOxygen() const { return fOxygen; }

	UFUNCTION(BlueprintCallable)
		void SetOxygen(float val) { fOxygen = FMath::Clamp<float>( val, 0, fDefaultOxygen); }
};
