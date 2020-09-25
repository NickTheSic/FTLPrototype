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

//A Struct to hold all the Class information to keep the player a little more clean
USTRUCT()
struct FClassInformation
{
	GENERATED_USTRUCT_BODY()

public:
	//Weapon templates setup
	UPROPERTY(EditAnywhere, Category = "Class Config | Weapon")
		TSubclassOf<class AWeapon> gunItemTemplate;		//The template for the Main gun

	UPROPERTY(EditAnywhere, Category = "Class Config | Weapon")
		TSubclassOf<class AWeapon> meleeItemTemplate;	//The template item for the Melee weapon

	UPROPERTY(EditAnywhere, Category = "Class Config | Weapon")
		TSubclassOf<class AWeapon> classItemTemplate;	//The class specific item template

	UPROPERTY(EditAnywhere, Category = "Class Config | Weapon")
		TSubclassOf<class AWeapon> grenadeItemTemplate;	//The throwable item template


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
		PlayerClass playerClass;	//Holds the class type for the player
};
