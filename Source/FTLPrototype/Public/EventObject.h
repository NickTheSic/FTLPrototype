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

	//How a player will interact with the Event
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactable)
		class UInteractableBox* pInteractableBox;

	//The material that will be when active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
		class UMaterial* pActiveMaterial;

	//The material that will be when deactived
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
		class UMaterial* pDeactiveMaterial;

	//When activated can be interacted with
	bool bisActive;

	//Timer for when it will randomly activate
	FTimerHandle ActivationTimer;


	//Called when Timer is done
	UFUNCTION()
		void Activate();

	//Called when Player has interacted with the object
	UFUNCTION()
		void Deactivate();

	//A bool call to check if the object is active or not
	UFUNCTION()
		bool IsActive();
};
