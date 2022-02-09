#include "QuestObjective.h"
#include "LocationMarker.h"
#include "CollectibleActor.h"
#include "ShootableActor.h"
#include "QuestInteractObject.h"
#include "Engine/StaticMesh.h"

UInteractionObjective::UInteractionObjective()
{
	Type = EObjectiveType::Ot_Interact;
}

void UInteractionObjective::ActivateObjective(AActor* Instigator)
{
	if (auto* InteractTarget = Cast<IQuestInteractObject>(Target))   //Instead of a cast interface should have had a function that returns OnInteractionFinished
	{
		InteractTarget->OnInteractionFinished.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
		{
			if (bCanBeCompleted && Instigator == InteractInstigator)
			{
				bIsCompleted = true;
				OnObjectiveCompleted.Broadcast(this);
			}
		});
	}
}

AActor* UInteractionObjective::GetInteractiveComponent() const 
{
	return Target;
}

void UInteractionObjective::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		Ar << bIsCompleted << bCanBeCompleted;
	}
}

ULocationObjective::ULocationObjective()
{
	Type = EObjectiveType::Ot_Location;
}

void ULocationObjective::ActivateObjective(AActor* Instigator)
{
	if (auto* InteractTarget = Cast<ILocationMarker>(Marker))
	{
		InteractTarget->OnLocationReached.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
		{
			if (bCanBeCompleted && Instigator == InteractInstigator)
			{
				bIsCompleted = true;
				if (OnObjectiveCompleted.IsBound())
				{
					OnObjectiveCompleted.Broadcast(this);
				}
			}
		});
	}
}

AActor* ULocationObjective::GetInteractiveComponent() const
{
	return Marker;
}

void ULocationObjective::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		Ar << bIsCompleted << bCanBeCompleted;
	}
}

UCollectibleObjective::UCollectibleObjective()
{
	Type = EObjectiveType::Ot_Collect;
}

void UCollectibleObjective::ActivateObjective(AActor* Instigator)
{
	if (auto* InteractTarget = Cast<ICollectibleActor>(Collectible))
	{
		InteractTarget->OnBeingPickedUp.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
		{
			if (bCanBeCompleted && Instigator == InteractInstigator)
			{

				Collectible->SetActorHiddenInGame(true);		// being disable only at completion

				bIsCompleted = true;
				if (OnObjectiveCompleted.IsBound())
				{
					OnObjectiveCompleted.Broadcast(this);
				}
			}
		});
	}
}

AActor* UCollectibleObjective::GetInteractiveComponent() const
{
	return Collectible;
}


void UCollectibleObjective::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		Ar << bIsCompleted << bCanBeCompleted;
		if (Ar.IsLoading())
		{
			Collectible->SetActorHiddenInGame(bIsCompleted);
		}
	}
}

UShootableObjective::UShootableObjective()
{
	Type = EObjectiveType::Ot_Hit;
}

void UShootableObjective::ActivateObjective(AActor* Instigator)
{
	if (auto* InteractTarget = Cast<IShootableActor>(Shootable))
	{
		InteractTarget->OnHitByProjectile.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
		{
			if (bCanBeCompleted && Instigator == InteractInstigator)
			{
				Shootable->SetActorHiddenInGame(true); /// only hidden on collision with completion

				bIsCompleted = true;
				if (OnObjectiveCompleted.IsBound())
				{
					OnObjectiveCompleted.Broadcast(this);
				}
			}
		});
	}
}

AActor* UShootableObjective::GetInteractiveComponent() const
{
	return Shootable;
}

void UShootableObjective::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		// Ar << Actor->TextureColor if it changes from the shot
		Ar << bIsCompleted << bCanBeCompleted;

		if (Ar.IsLoading())
		{
			Shootable->SetActorHiddenInGame(bIsCompleted);
		}
	}
}