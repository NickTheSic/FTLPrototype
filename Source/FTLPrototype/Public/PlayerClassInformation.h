#pragma once
 
#include "CoreMinimal.h"
#include "PlayerClassInformation.generated.h"

//An enum so we know what class the player is
UENUM()
enum class PlayerClass
{
	Unknown = -1, //I guess I wanted to have an error in case
	Base = 0,	// Just the basic unset character
	Gunner = 1,	//Gunner type
	Engineer = 2,	//Engineer type
	Medic = 3,	//Medic type
};


USTRUCT()
struct FClassWeaponInformation
{
	GENERATED_USTRUCT_BODY()

public:
	//Weapon templates setup
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class AWeapon> gunItemTemplate;		//The template for the Main gun

	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class AWeapon> meleeItemTemplate;	//The template item for the Melee weapon

	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class AWeapon> classItemTemplate;	//The class specific item template

	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class AWeapon> grenadeItemTemplate;	//The throwable item template

};

USTRUCT()
struct FClassRepairInformation
{
	GENERATED_USTRUCT_BODY()

public:


	//Repair speed setup
	UPROPERTY(EditAnywhere, Category = "Repairing")
		float fEngineeringRepairSpeed = 10.0f; //Speed to repair Engineering type objects

	UPROPERTY(EditAnywhere, Category = "Repairing")
		float fMedicRepairSpeed = 10.0f; //Speed for repairing stuff in medic bay

	UPROPERTY(EditAnywhere, Category = "Repairing")
		float fCommonRepairSpeed = 10.0f; //Speed for repairing common items

	UPROPERTY(EditAnywhere, Category = "Repairing")
		float fDefaultRepairSpeed = 10.0f; //A Default repair speed in case we add anything or I miss anything

};


USTRUCT()
struct FClassExtraInformation
{
	GENERATED_USTRUCT_BODY()

public:

	//Extra inventory stuff because I am bored and not sure what else I can do
	UPROPERTY(EditAnywhere, Category = "")
		float fExtraConsumables = 1.0f;

	UPROPERTY(EditAnywhere, Category = "")
		float fExtraAmmo = 1.0f;

	UPROPERTY(EditAnywhere, Category = "")
		float fExtraThrowables = 1.0f;

};


//A Struct to hold all the Class information to keep the player a little more clean
USTRUCT()
struct FClassInformation
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category = "Weapons")
		FClassWeaponInformation weaponInformation;

	UPROPERTY(EditAnywhere, Category = "Repair")
		FClassRepairInformation repairInformation;

	//
	UPROPERTY(EditAnywhere, Category = "Status")
		float fReloadSpeed = 10.0f; //How quickly the player can reload

	UPROPERTY(EditAnywhere, Category = "Status")
		float fHealspeed = 10.0f; //How quickly the player can heal

	UPROPERTY(EditAnywhere, Category = "Status")
		float fMaxHealth = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Status")
		float fWalkSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Status")
		float fSprintSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Status")
		float fOxygenReplenishRate = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Status")
		float fLungSize = 10.0f; //

	UPROPERTY(EditAnywhere, Category = "Status")
		float fMaxStamina = 10.0f; //The maximum stamina that a player can have

	UPROPERTY(EditAnywhere, Category = "Status")
		float fStaminaRegenRate = 10.0f; //How fast the players stamina can regenerate, if we have it

	UPROPERTY(EditAnywhere, Category = "Status")
		float fAmbientLightInDarkness = 10.0f; //How well can this player see in the darkness


	UPROPERTY(EditAnywhere, Category = "Status")
		PlayerClass playerClass;	//Holds the class type for the player


	UPROPERTY(EditAnywhere, Category = "")
		FClassExtraInformation extraInformation;

};

