// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipDoor.generated.h"

UCLASS()
class FTLPROTOTYPE_API AShipDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipDoor();

	UPROPERTY(EditAnywhere)
	class UMyPointLightComponent* pLight = nullptr;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* pMesh = nullptr;

	UPROPERTY(EditAnywhere)
		float Intensity;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsActivated = false;

public:	
	UFUNCTION()
	void Activate();
	UFUNCTION()
	void Open();
	UFUNCTION()
	void Close();

};
