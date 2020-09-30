// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Item.generated.h"

UCLASS()
class FTLPROTOTYPE_API AItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* pSkeletalMesh;
	UPROPERTY(EditAnywhere, Category = "HitBox", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* pHitBox;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//For when an item is used/done being used I.e. pressing a button
	virtual void Use();
	virtual void StopUse();

	//In case we need to obliterate an item from existance
	virtual void Destroy();

	//To turn on/off items, to hide/show items, and whatever else you'd want switched on/off
	virtual void Enable();
	virtual void Disable();

	//Returns mesh 
	virtual USkeletalMeshComponent* GetMesh() { return pSkeletalMesh; };
};