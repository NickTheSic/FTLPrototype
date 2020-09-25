// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RaycastComponent.generated.h"


//Quick setup for use:
//1. Attach component to actor
//2. Call any of the functions
//E.g.:
//			FHitResult ray;
//			if (pRaycastComponent->RaycastSingleFromPlayer(ray, 150.f))
//			{
//				//Raycast succeeded
//			}


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FTLPROTOTYPE_API URaycastComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URaycastComponent();

public:	
	/*	Returns true if raycast found something. Data about raycast is stored in hit.

		FHitResult& hit: The raycast result;
		FVector start: The start of the raycast;
		FRotator dir: The angle to raycast towards;
		float dist: The distance from the start of the raycast to the end of it;
		FCollisionObjectQueryParams query: Extra query data. Set to ECollisionChannel::ECC_PhysicsBody by default;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastSingle(FHitResult& hit, FVector start, FRotator dir, float dist, FCollisionObjectQueryParams query = ECollisionChannel::ECC_PhysicsBody);
	/*	Returns true if raycast found something. Data about raycast is stored in hit.

		FHitResult& hit: The raycast result;
		FVector start: The start of the raycast;
		FVector start: The end of the raycast;
		FCollisionObjectQueryParams query: Extra query data. Set to ECollisionChannel::ECC_PhysicsBody by default;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastSingle(FHitResult& hit, FVector start, FVector end, FCollisionObjectQueryParams query = ECollisionChannel::ECC_PhysicsBody);
	/*	Returns true if raycast found something. Data about raycast is stored in hits.

		TArray<FHitResult>& hit: All raycast results;
		FVector start: The start of the raycast;
		FRotator dir: The angle to raycast towards;
		float dist: The distance from the start of the raycast to the end of it;
		FCollisionObjectQueryParams query: Extra query data. Set to ECollisionChannel::ECC_PhysicsBody by default;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastMulti(TArray<FHitResult>& hits, FVector start, FRotator dir, float dist, FCollisionObjectQueryParams query = ECollisionChannel::ECC_PhysicsBody);
	/*	Returns true if raycast found something. Data about raycast is stored in hits.

		TArray<FHitResult>& hit: All raycast results;
		FVector start: The start of the raycast;
		FVector start: The end of the raycast;
		FCollisionObjectQueryParams query: Extra query data. Set to ECollisionChannel::ECC_PhysicsBody by default;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastMulti(TArray<FHitResult>& hits, FVector start, FVector, FCollisionObjectQueryParams query = ECollisionChannel::ECC_PhysicsBody);
	/*	Performs a raycast starting at the player, towards where they are looking.
		Returns true if raycast found something. Data about raycast is stored in hit.
		Parent must be of type ACharacter, and must possess an APlayerController*

		FHitResult& hit: The raycast result;
		float dist: The distance from the start of the raycast to the end of it;
		FCollisionObjectQueryParams query: Extra query data. Set to ECollisionChannel::ECC_PhysicsBody by default;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastSingleFromPlayer(FHitResult& hit, float dist, FCollisionObjectQueryParams query = ECollisionChannel::ECC_PhysicsBody);
	/*	Performs a raycast starting at the player, towards where they are looking.
		Returns true if raycast found something. Data about raycast is stored in hit.
		Parent must be of type ACharacter, and must possess an APlayerController*

		TArray<FHitResult>& hit: The raycast results;
		float dist: The distance from the start of the raycast to the end of it;
		FCollisionObjectQueryParams query: Extra query data. Set to ECollisionChannel::ECC_PhysicsBody by default;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastMultiFromPlayer(TArray<FHitResult>& hit, float dist, FCollisionObjectQueryParams query = ECollisionChannel::ECC_PhysicsBody);
	
	/*	Returns true if raycast found something. Data about raycast is stored in hit.

		FHitResult& hit: The raycast result;
		FVector start: The start of the raycast;
		FRotator dir: The angle to raycast towards;
		float dist: The distance from the start of the raycast to the end of it;
		FName profileName: the raycast profile name to check;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastSingle(FHitResult& hit, FVector start, FRotator dir, float dist, FName profileName);
	/*	Returns true if raycast found something. Data about raycast is stored in hit.

		FHitResult& hit: The raycast result;
		FVector start: The start of the raycast;
		FVector end: The end of the raycast;
		FName profileName: the raycast profile name to check;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastSingle(FHitResult& hit, FVector start, FVector end, FName profileName);
	/*	Returns true if raycast found something. Data about raycast is stored in hit.

		TArray<FHitResult>& hits: The raycast results;
		FVector start: The start of the raycast;
		FRotator dir: The angle to raycast towards;
		float dist: The distance from the start of the raycast to the end of it;
		FName profileName: the raycast profile name to check;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastMulti(TArray<FHitResult>& hits, FVector start, FRotator dir, float dist, FName profileName);
	/*	Returns true if raycast found something. Data about raycast is stored in hit.

		TArray<FHitResult>& hits: The raycast results;
		FVector start: The start of the raycast;
		FVector end: The end of the raycast;
		FName profileName: the raycast profile name to check;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastMulti(TArray<FHitResult>& hits, FVector start, FVector, FName profileName);
	/*	Performs a raycast starting at the player, towards where they are looking.
		Returns true if raycast found something. Data about raycast is stored in hit.
		Parent must be of type ACharacter, and must possess an APlayerController*

		TArray<FHitResult>& hit: The raycast results;
		float dist: The distance from the start of the raycast to the end of it;
		FName profileName: the raycast profile name to check;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastSingleFromPlayer(FHitResult& hit, float dist, FName profileName);
	/*	Performs a raycast starting at the player, towards where they are looking.
		Returns true if raycast found something. Data about raycast is stored in hit.
		Parent must be of type ACharacter, and must possess an APlayerController*

		TArray<FHitResult>& hit: The raycast results;
		float dist: The distance from the start of the raycast to the end of it;
		FName profileName: the raycast profile name to check;
		RETURNS bool: If the raycast hit anything, returns true.
	*/
	bool RaycastMultiFromPlayer(TArray<FHitResult>& hit, float dist, FName profileName);

};
