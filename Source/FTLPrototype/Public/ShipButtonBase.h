// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipButtonBase.generated.h"

UCLASS()
class FTLPROTOTYPE_API AShipButtonBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipButtonBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
		class AShipDoor* pObjectToActivate;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* pMesh = nullptr;

	void Activate();

};
