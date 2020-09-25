// Fill out your copyright notice in the Description page of Project Settings.


#include "RaycastComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
URaycastComponent::URaycastComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

#pragma region FCollisionObjectQueryParams
bool URaycastComponent::RaycastSingle(FHitResult& hit, FVector start, FRotator dir, float dist, FCollisionObjectQueryParams query)
{
	FVector end = start + dir.Vector() * dist;
	FCollisionQueryParams traceParams(FName(""), false, GetOwner());
	return GetWorld()->LineTraceSingleByObjectType(hit, start, end, query, traceParams);
}

bool URaycastComponent::RaycastMulti(TArray<FHitResult>& hits, FVector start, FRotator dir, float dist, FCollisionObjectQueryParams query)
{
	FVector end = start + dir.Vector() * dist;
	FCollisionQueryParams traceParams(FName(""), false, GetOwner());
	return GetWorld()->LineTraceMultiByObjectType(hits, start, end, query, traceParams);
}

bool URaycastComponent::RaycastSingle(FHitResult& hit, FVector start, FVector end, FCollisionObjectQueryParams query)
{
	FCollisionQueryParams traceParams(FName(""), false, GetOwner());
	return GetWorld()->LineTraceSingleByObjectType(hit, start, end, query, traceParams);
}

bool URaycastComponent::RaycastMulti(TArray<FHitResult>& hits, FVector start, FVector end, FCollisionObjectQueryParams query)
{
	FCollisionQueryParams traceParams(FName(""), false, GetOwner());
	return GetWorld()->LineTraceMultiByObjectType(hits, start, end, query, traceParams);
}

bool URaycastComponent::RaycastSingleFromPlayer(FHitResult& hit, float dist, FCollisionObjectQueryParams query)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	if (character != nullptr)
	{
		//This component is attached to a character, so this only works on characters.
		APlayerController* controller = character->GetController<APlayerController>();
		if (controller != nullptr)
		{
			//Player has controller
			FVector start, end;
			FRotator rot;
			controller->GetPlayerViewPoint(start, rot);
			return RaycastSingle(hit, start, rot, dist, query);
		}
		else return false; //No controller, or invalid
	}
	else return false; //Was not a character
}

bool URaycastComponent::RaycastMultiFromPlayer(TArray<FHitResult>& hits, float dist, FCollisionObjectQueryParams query)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	if (character != nullptr)
	{
		//This component is attached to a character, so this only works on characters.
		APlayerController* controller = character->GetController<APlayerController>();
		if (controller != nullptr)
		{
			//Player has controller
			FVector start, end;
			FRotator rot;
			controller->GetPlayerViewPoint(start, rot);
			return RaycastMulti(hits, start, rot, dist, query);
		}
		else return false; //No controller, or invalid
	}
	else return false; //Was not a character
}
#pragma endregion

#pragma region ProfileName
bool URaycastComponent::RaycastSingle(FHitResult& hit, FVector start, FRotator dir, float dist, FName name)
{
	FVector end = start + dir.Vector() * dist;
	FCollisionQueryParams traceParams(FName(""), false, GetOwner());
	return GetWorld()->LineTraceSingleByProfile(hit, start, end, name, traceParams);
}

bool URaycastComponent::RaycastMulti(TArray<FHitResult>& hits, FVector start, FRotator dir, float dist, FName name)
{
	FVector end = start + dir.Vector() * dist;
	FCollisionQueryParams traceParams(FName(""), false, GetOwner());
	return GetWorld()->LineTraceMultiByProfile(hits, start, end, name, traceParams);
}

bool URaycastComponent::RaycastSingle(FHitResult& hit, FVector start, FVector end, FName name)
{
	FCollisionQueryParams traceParams(FName(""), false, GetOwner());
	return GetWorld()->LineTraceSingleByProfile(hit, start, end, name, traceParams);
}

bool URaycastComponent::RaycastMulti(TArray<FHitResult>& hits, FVector start, FVector end, FName name)
{
	FCollisionQueryParams traceParams(FName(""), false, GetOwner());
	return GetWorld()->LineTraceMultiByProfile(hits, start, end, name, traceParams);
}

bool URaycastComponent::RaycastSingleFromPlayer(FHitResult& hit, float dist, FName name)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	if (character != nullptr)
	{
		//This component is attached to a character, so this only works on characters.
		APlayerController* controller = character->GetController<APlayerController>();
		if (controller != nullptr)
		{
			//Player has controller
			FVector start, end;
			FRotator rot;
			controller->GetPlayerViewPoint(start, rot);
			return RaycastSingle(hit, start, rot, dist, name);
		}
		else return false; //No controller, or invalid
	}
	else return false; //Was not a character
}

bool URaycastComponent::RaycastMultiFromPlayer(TArray<FHitResult>& hits, float dist, FName name)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	if (character != nullptr)
	{
		//This component is attached to a character, so this only works on characters.
		APlayerController* controller = character->GetController<APlayerController>();
		if (controller != nullptr)
		{
			//Player has controller
			FVector start, end;
			FRotator rot;
			controller->GetPlayerViewPoint(start, rot);
			return RaycastMulti(hits, start, rot, dist, name);
		}
		else return false; //No controller, or invalid
	}
	else return false; //Was not a character
}

#pragma endregion