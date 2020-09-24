// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractableBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInteractableBoxInteractSignature, AActor*, Caller, class UInteractableBox*, Box, bool, State);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FTLPROTOTYPE_API UInteractableBox : public USceneComponent
{
	GENERATED_BODY()
		TArray<class ABasePlayer*> actorsInRange;

public:
	// Sets default values for this component's properties
	UInteractableBox();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Collision")
		class UBoxComponent* collider;

	UFUNCTION()
		void OnComponentOverlapBegin(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 Index, bool bSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentOverlapEnd(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 index);
	UFUNCTION()
		void OnPlayerInteract(ABasePlayer* Player);
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintAssignable)
		FInteractableBoxInteractSignature onActorInteract;

		
};
