// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerClassInformation.h"
#include "BasePlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerInteractSignature, class ABasePlayer*, Player);


UCLASS()
class FTLPROTOTYPE_API ABasePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayer();

	UPROPERTY(EditAnywhere, Category = "Class Information")
		FClassInformation classInformation; //A Struct to hold all the class specific information

	/** First person camera */ //Copied from Prototype Character
	UPROPERTY(EditAnywhere, Category = "Camera")
		class UCameraComponent* pCameraComponent;

	UPROPERTY(EditAnywhere, Category = "Mesh | Player")
		class USkeletalMeshComponent* pMeshComponent = nullptr;
	UPROPERTY(EditAnywhere, Category = "Mesh | Weapon")
		class USkeletalMeshComponent* pWeaponMesh = nullptr;


	UPROPERTY()
		class UUInventory* pInventoryComponent = nullptr; //A nullptr to the Inventory, created later

	UPROPERTY()
		class UHealthComponent* pHealthComponent = nullptr; //A ptr to the Health set to null for now

	UPROPERTY()
		class URaycastComponent* pRaycastComponent = nullptr;



	UPROPERTY()
		class AWeapon* pActiveWeapon = nullptr; //A pointer to the active weapon



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//A Repair function
	void Repair(); //Raycasts and finds us the repair object
	void Repair(AActor *repairObj); //We have an object we already want to repair

	virtual void ClassSpecialty();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnInteract();

	void SetWeaponMesh();

	UPROPERTY(BlueprintCallable)
		FPlayerInteractSignature onPlayerInteract;


	void ReplenishHealth();


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
		void UseWeapon(); //A Function to use our pActiveItem // StartFire();
	UFUNCTION()
		void StopUsingWeapon(); //StopFire()

	UFUNCTION()
		void Interact();



	UFUNCTION()
		void SwitchToInventorySlot(int item); //A Function to switch our pActiveItem when a number key is pressed
	//Individual key press functions
	UFUNCTION()
		void SwitchToItemOne() ;  
	UFUNCTION()
		void SwitchToItemTwo() ;  
	UFUNCTION()
		void SwitchToItemThree();
	UFUNCTION()
		void SwitchToItemFour();  

	UFUNCTION()
		void SwitchInventoryMouseWheelUp();
	UFUNCTION()
		void SwitchInventoryMouseWheelDown();


	UFUNCTION()
		void MoveRight(float val);
	UFUNCTION()
		void MoveForward(float val);


private:

	bool bHasPopulatedInventory = false; //We only want to populate the inventory once
	void PopulateInventory();	//Fill the inventory component with our items

	void AddPlayerTags();		//Add the tags we want to add to the player

};
