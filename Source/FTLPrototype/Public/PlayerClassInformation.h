#pragma once

#include "CoreMinimal.h"
#include "PlayerClassInformation.generated.h"

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
