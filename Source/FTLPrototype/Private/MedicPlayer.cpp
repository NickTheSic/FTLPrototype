// Fill out your copyright notice in the Description page of Project Settings.


#include "MedicPlayer.h"
#include "Engine/Engine.h"
#include "RaycastComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

AMedicPlayer::AMedicPlayer()
{
	this->Tags.Add("Medic");
	classInformation.playerClass = PlayerClass::Medic;

	//OPTIONAL: Once we know how to balance the players exactly we can set it here in code

}

void AMedicPlayer::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



}

void AMedicPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (pWeaponMesh)
	{
		pWeaponMesh->SetDebugDrawColor(FColor::Purple);
	}

}

void AMedicPlayer::ClassSpecialty()
{

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Medic Class Special");

	if (bHealingSelf) 
		HealSelf();
	else
	{
		FHitResult hit;
		if (pRaycastComponent != nullptr)
		{
			if (pRaycastComponent->RaycastSingleFromPlayer(hit, 200))
			{
				ABasePlayer* otherPlayer = Cast<ABasePlayer>(hit.GetActor());
				if (otherPlayer != nullptr)
				{
					HealOther(otherPlayer);

					return;
				}

				//ELSE
				//We can refill the Medics Syringe to heal people
				//If we use the syring at the healing station in the medbay

			}
		}
	}
	

}

void AMedicPlayer::HealSelf()
{
	//Increase self health I guess
	//Probably in healthcomponent 
	//and if the medic uses the specific item to heal
	ReplenishHealth();
}

void AMedicPlayer::HealOther(ABasePlayer* other)
{
	//Probably in healthcomponent 
	//and if the medic uses the specific item to heal another player
	other->ReplenishHealth();
}
