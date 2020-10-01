// Fill out your copyright notice in the Description page of Project Settings.


#include "GunRifle.h"
#include "SceneManagement.h"
#include "DrawDebugHelpers.h"
#include "EnemyBase.h"
#include "../FTLPrototypeCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayer.h"

AGunRifle::AGunRifle()
{
    bIsFiring = false;
    bIsAutomatic = true;
    uiMagAmmo = 20;
    uiMaxMagAmmo = 20;
    iReserveAmmo = 60;
    uiMaxReserveAmmo = 60;
    fReloadTime = 3.0f;
    fFireRate = 12.0f;

    pRayCast = CreateDefaultSubobject<URaycastComponent>("RayCast");

    PrimaryActorTick.bCanEverTick = false;
}

void AGunRifle::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
}

void AGunRifle::BeginPlay()
{
    Super::BeginPlay();
}

//Called when player PRESSES left click
void AGunRifle::FireStart()
{
    //Setup Animations

    //Fire based on timer (which is based on firerate, 12 shots per second)
    FTimerManager& Timer = GetWorldTimerManager();
    Timer.SetTimer(attackTimer, this, &AGunRifle::Fire, 1.0f / fFireRate, true, 0.0f);
}

void AGunRifle::Fire()
{
    GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Blue, "GunRifle::Fire");

    //if we have ammo, shoot
    if (uiMagAmmo > 0)
    {
        uiMagAmmo--;
        GEngine->AddOnScreenDebugMessage(3, 2.0f, FColor::Red, FString::FromInt(uiMagAmmo));

        //Play a gunshot/laser sound
        
        //Raycast shenanigans
        FHitResult hit;
        /*pRayCast->RaycastSingle(hit, 
            GetActorLocation(),                 //raycast was coming out the side for some reason, the + 90 seems to fix
            FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 90.0f, GetActorRotation().Roll), 
            3000.0f, 
            FCollisionObjectQueryParams::AllObjects);*/
		ABasePlayer* character = Cast<ABasePlayer>(GetOwner());
		if (character != nullptr)
		{
			character->GetRaycastComponent()->RaycastSingleFromPlayer(hit, 3000.0f, FCollisionObjectQueryParams::AllObjects);
		}

		 //pRayCast->RaycastSingle(hit, 
   //         GetActorLocation(),                 //raycast was coming out the side for some reason, the + 90 seems to fix
   //         FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 90.0f, GetActorRotation().Roll), 
   //         3000.0f, 
   //         "Raycastable");

        if (hit.GetActor() == nullptr)
        {
            GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, "Hit.Actor was nullptr");
        }
        else
        {
            //rTodo: deal damage
            //if the actor we hit is an enemy, take damage
            //AEnemyBase* enemy = Cast<AEnemyBase>(hit.GetActor());
            //if (enemy != nullptr)
            //{
            //    enemy->TakeDamage(25.0f);
            //}


            GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, hit.GetActor()->GetFName().ToString());
            DrawDebugLine(GetWorld(), hit.TraceStart, hit.TraceEnd, FColor::Green, true);
			UGameplayStatics::ApplyDamage(hit.GetActor(), 25.0f, character->GetController(), GetOwner(), DamageType);
			//UGameplayStatics::ApplyPointDamage(hit.GetActor(), BaseDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(), MyOwner, DamageType);

            //FPrimitiveDrawInterface::DrawLine(hit.TraceStart, hit.TraceEnd, FLinearColor::Green, 0, 2.0f, 2.0f, true);
        }
    }
    //we have 0 bullets
    else
    {
        //play a click sound
        
        //rTODO: remove this, it's a temporary fix for ammo testing
        //FireEnd();
        //ReloadStart();
    }
}

//Called when player RELEASES left click
void AGunRifle::FireEnd()
{
    //clear attack timer so fire isn't called unless the player left clicks again
    FTimerManager& Timer = GetWorldTimerManager();
    Timer.ClearTimer(attackTimer);
}

void AGunRifle::ReloadStart()
{
    //reload animation?
    //reload sound?

    //Beginning of reload
    FTimerManager& Timer = GetWorldTimerManager();
    Timer.SetTimer(reloadTimer, this, &AGunRifle::Reload, fReloadTime, false);
    //Timer should only trigger once, no need to clear it
}

void AGunRifle::Reload()
{
    //if we have ammo to use
    if (iReserveAmmo != 0)
    {
        //if we have endless ammo, just set mag to max
        if (iReserveAmmo == -1)
        {
            uiMagAmmo = uiMaxMagAmmo;
        }
        //if we have more or equal to a full mag, reload accordingly
        else if (iReserveAmmo >= uiMaxMagAmmo)
        {
            uiMagAmmo = uiMaxMagAmmo;
            iReserveAmmo -= uiMaxMagAmmo;
        }
        //otherwise we are below a full mag, reload what we can
        else
        {
            uiMagAmmo = iReserveAmmo;
            iReserveAmmo = 0;
        }
    }

    ReloadEnd();
}

void AGunRifle::ReloadEnd()
{
    //End of reload if we need to do anything here
    //rTODO: remove this, it's a temporary fix for ammo testing
    //GEngine->AddOnScreenDebugMessage(4, 2.0f, FColor::Red, "End of reload");
    //FireStart();
}