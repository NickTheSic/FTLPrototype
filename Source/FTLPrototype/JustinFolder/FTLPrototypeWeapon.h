// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FTLPrototypeWeapon.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;
class UParticleSystem;
class USoundBase;
class UDamageType;
class UFTLPrototypeHealthComponent;

UCLASS()
class FTLPROTOTYPE_API AFTLPrototypeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFTLPrototypeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName TracerTargetName; // meant for line trace effect

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* TracerEffect; //line effect

	//UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		//TSubclassOf<UCameraShake> FireCamShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShots;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	float CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	float MaxAmmo;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* FireSound;

	float FireTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float BulletSpread;

	FTimerHandle TimerHandle_TimeBetweenShots;


	// used to disable shooting when player dies - HACK! Use gamestate "GameOver" after prototype
	AActor* HitActor;
	UFTLPrototypeHealthComponent* HitActorHealth;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;;

	virtual void Fire();

	void StartFire();

	void StopFire();

};
