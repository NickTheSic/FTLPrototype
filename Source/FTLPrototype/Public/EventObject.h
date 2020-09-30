// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventObject.generated.h"

UCLASS()
class FTLPROTOTYPE_API AEventObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Base Mesh so it is visible
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		class UStaticMeshComponent* pStaticMesh;
	
	//Temporary Box Collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collider)
		class UBoxComponent* pBoxCollider;

	//The material that will be when active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
		class UMaterial* pActiveMaterial;

	//The material that will be when deactived
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
		class UMaterial* pDeactiveMaterial;

	//When activated can be interacted with
	bool bisActive;
	bool IsActive() { return bisActive; }

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Set of bools to determine type of event, how fast they occur when active and by how much, which will be set in blueprints per event
	//Values must be set in blueprints as code will set them to 0

	//Health Event
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EventType)
		bool bHealthEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EventType)
		float fHealthEventSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EventType)
		float fHealthEventValue;
	
	//Oxygen Event
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EventType)
		bool bOxygenEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EventType)
		float fOxygenEventSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EventType)
		float fOxygenEventValue;

	//Spawn Event
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EventType)
		bool bSpawnEvent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EventType)
		float fSpawnEventSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EventType)
		float fSpawnEventValue;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Timer for when it will randomly activate
	FTimerHandle ActivationTimer;

	//Timer to decrement health
	FTimerHandle HealthDecrementTimer;

	//Timer to decrement oxygen
	FTimerHandle OxygenDecrementTimer;

	//Timer to spawn the AI
	FTimerHandle SpawnTimer;

	//Called when Timer is done
	UFUNCTION()
		void Activate();

	//Called when Player has interacted with the object
	UFUNCTION()
		void Deactivate();

	//Is called on HealthEvent objects to lower health
	UFUNCTION()
		void LowerHealth();

	//Is called on OxygenEvent objects to lower the oxygen count
	UFUNCTION()
		void LowerOxygen();

	//Is called on SpawnEvent objects to spawn AI
	UFUNCTION()
		void SpawnEnemy();
};
