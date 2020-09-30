// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FTLPrototypeAI.generated.h"

class AFTLPrototypeWeapon;
class UFTLPrototypeHealthComponent;
class USoundBase;

UCLASS()
class FTLPROTOTYPE_API AFTLPrototypeAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFTLPrototypeAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFTLPrototypeHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	AFTLPrototypeWeapon* CurrentWeapon; //needed class forward declaring

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<AFTLPrototypeWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName WeaponAttachSocketName;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void StopFire();

	UFUNCTION() //delegate
	void OnHealthChanged(UFTLPrototypeHealthComponent* InHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* DeathSounds;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	bool bDied;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//When enabled, the enemies chase the players automatically
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TriggerStart")
	bool EnableTriggerAtStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StopFire")
		bool StopFiring;

};
