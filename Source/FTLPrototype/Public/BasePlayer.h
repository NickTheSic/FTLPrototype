// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerInteractSignature, class ABasePlayer*, Player);

/*This should be in a different header*/
//An enum so we know what class the player is
UENUM()
enum class PlayerClass
{
	Unknown = -1,
	Base = 0,
	Gunner = 1,
	Engineer = 2,
	Medic = 3
};

/*This should be in a different header*/
//A Struct to hold all the Class information to keep the player a little more clean
USTRUCT()
struct FClassInformation
{
	GENERATED_USTRUCT_BODY()

public:
	//Weapon templates setup
	UPROPERTY(EditAnywhere, Category = "Class Config | Weapon")
		TSubclassOf<class AWeapon> gunItemTemplate;

	UPROPERTY(EditAnywhere, Category = "Class Config | Weapon")
		TSubclassOf<class AWeapon> meleeItemTemplate;

	UPROPERTY(EditAnywhere, Category = "Class Config | Weapon")
		TSubclassOf<class AWeapon> classItemTemplate;

	UPROPERTY(EditAnywhere, Category = "Class Config | Weapon")
		TSubclassOf<class AWeapon> grenadeItemTemplate;


	//Repair speed setup
	UPROPERTY(EditAnywhere, Category = "Class Config | Repairing")
		float fEngineeringRepairSpeed = 10.0f; //Speed to repair Engineering type objects

	UPROPERTY(EditAnywhere, Category = "Class Config | Repairing")
		float fMedicRepairSpeed = 10.0f; //Speed for repairing stuff in medic bay

	UPROPERTY(EditAnywhere, Category = "Class Config | Repairing")
		float fCommonRepairSpeed = 10.0f; //Speed for repairing common items

	UPROPERTY(EditAnywhere, Category = "Class Config | Repairing")
		float fDefaultRepairSpeed = 10.0f; //A Default repair speed in case we add anything or I miss anything


	//
	UPROPERTY(EditAnywhere, Category = "Class Config | Status")
		float fReloadSpeed = 10.0f; //How quickly the player can reload

	UPROPERTY(EditAnywhere, Category = "Class Config | Status")
		float fHealspeed = 10.0f; //How quickly the player can heal

	UPROPERTY(EditAnywhere, Category = "Class Config | Status")
		PlayerClass playerClass;
};


UCLASS()
class FTLPROTOTYPE_API ABasePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayer();

	UPROPERTY(EditAnywhere, Category = "Class Information")
		FClassInformation classInformation; //A Struct to hold all the class information

	UPROPERTY()
		class UUInventory* pInventoryComponent = nullptr;

	UPROPERTY()
		class UHealthComponent* pHealthComponent = nullptr;

	UPROPERTY()
		class AWeapon* pActiveItem = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//A Repair function
	void Repair();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnInteract();

	UPROPERTY(BlueprintCallable)
		FPlayerInteractSignature onPlayerInteract;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool bHasPopulatedInventory = false; //We only want to populate the inventory once
	void PopulateInventory();

	void AddPlayerTags();

};
