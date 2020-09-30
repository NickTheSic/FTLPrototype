// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawDebugHelpers.h"
#include "Melee.h"

AMelee::AMelee()
{
    bIsFiring = false;
    bIsAutomatic = false;
    uiMagAmmo = 0;
    uiMaxMagAmmo = 0;
    iReserveAmmo = 0;
    uiMaxReserveAmmo = 0;
    fReloadTime = 0.0f;
    fFireRate = 1.25f;

    pRayCast = CreateDefaultSubobject<URaycastComponent>("RayCast");

    PrimaryActorTick.bCanEverTick = true;
}

void AMelee::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    if (bIsFiring == false)
    {
        FireStart();
    }
}

void AMelee::BeginPlay()
{
    Super::BeginPlay();
}

void AMelee::FireStart()
{
    //if we're not attacking yet
        //bIsFiring = true
        //Set timer to call FireEnd() based on fireRate
        //call Fire()
    //

    if (bIsFiring == false)
    {
        bIsFiring = true;
        FTimerManager& Timer = GetWorldTimerManager(); 
        Timer.SetTimer(attackTimer, this, &AMelee::FireEnd, fFireRate, false);
        GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Red, "STAB");
        Fire();
    }
}

void AMelee::Fire()
{
    //do a short-range raycast and deal damage
    //Raycast shenanigans
    FHitResult hit;
    pRayCast->RaycastSingle(hit,
        GetActorLocation(),                 //raycast was coming out the side for some reason, the + 90 seems to fix
        FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + 90.0f, GetActorRotation().Roll),
        100.0f,
        FCollisionObjectQueryParams::AllObjects);

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
        //FPrimitiveDrawInterface::DrawLine(hit.TraceStart, hit.TraceEnd, FLinearColor::Green, 0, 2.0f, 2.0f, true);
    }
}

void AMelee::FireEnd()
{
    //when called, set bIsFiring to false so we can attack again
    bIsFiring = false;
}