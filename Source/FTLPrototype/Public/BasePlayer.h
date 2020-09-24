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
		FClassInformation classInformation; //A Struct to hold all the class information


	UPROPERTY()
		class UUInventory* pInventoryComponent = nullptr;

	UPROPERTY()
		class UHealthComponent* pHealthComponent = nullptr;

	UPROPERTY()
		class AWeapon* pActiveWeapon = nullptr;

	UFUNCTION()
		void UseWeapon(); //A Function to use our pActiveItem

	UFUNCTION()
		void SwitchToInventorySlot(int item); //A Function to switch our pActiveItem when a number key is pressed

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
