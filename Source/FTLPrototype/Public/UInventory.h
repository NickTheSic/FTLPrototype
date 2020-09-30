// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FTLPROTOTYPE_API UUInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUInventory();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        class AWeapon* GunItem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        class AWeapon* MeleeItem;

    UPROPERTY(EditDefaultsOnly, Category = Projectile)
       class AWeapon* GrenadeItemClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        class AWeapon* ClassItem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        class AWeapon* CurrentWeapon;


    int grenadeLeft = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        class AItem* questItem;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;




		
};
