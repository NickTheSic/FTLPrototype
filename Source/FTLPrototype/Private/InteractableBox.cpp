// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableBox.h"
#include "Components/BoxComponent.h"
#include "BasePlayer.h"

// Sets default values for this component's properties
UInteractableBox::UInteractableBox()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = true;

#pragma region collision
	collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	collider->SetGenerateOverlapEvents(true);
	collider->OnComponentBeginOverlap.AddDynamic(this, &UInteractableBox::OnComponentOverlapBegin);
	collider->OnComponentEndOverlap.AddDynamic(this, &UInteractableBox::OnComponentOverlapEnd);
	collider->SetupAttachment(this);

#pragma endregion
}


// Called when the game starts
void UInteractableBox::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UInteractableBox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UInteractableBox::OnComponentOverlapBegin(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 Index, bool bSweep, const FHitResult& SweepResult)
{
	//if within range interact
	if (!actorsInRange.Contains(OtherActor))
	{
		if (ABasePlayer* player = Cast<ABasePlayer>(OtherActor))
		{
			actorsInRange.Add(player);
			player->onPlayerInteract.AddDynamic(this, &UInteractableBox::OnPlayerInteract);
		}
	}
}


void UInteractableBox::OnComponentOverlapEnd(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 Index)
{
	//remove player when out of range
	if (actorsInRange.Contains(OtherActor))
	{
		ABasePlayer* actor = Cast<ABasePlayer>(OtherActor);
		actorsInRange.Remove(actor);
		actor->onPlayerInteract.RemoveDynamic(this, &UInteractableBox::OnPlayerInteract);
	}
}

void UInteractableBox::OnPlayerInteract(ABasePlayer* Player)
{
	onActorInteract.Broadcast(Player, this, true);
}