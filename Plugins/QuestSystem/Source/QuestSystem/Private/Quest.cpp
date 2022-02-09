#include "Quest.h"
#include "QuestObjective.h"

AQuest::AQuest()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AQuest::BeginPlay()
{
	Super::BeginPlay();

	AActor* ParentActor = GetAttachParentActor();
}

void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuest::UpdateLocation()
{
	AActor* ParentActor = GetAttachParentActor();
	if (ParentActor)
	{
		SetActorLocation(ParentActor->GetActorLocation());
	}
}

void AQuest::AcceptQuest(AActor* Character)
{
	if (bIsTaken)
	{
		return;
	}

	for (int32 i = 0; i < ObjectiveSet.Num(); i++)
	{
		auto* Objective = ObjectiveSet[i];
		if (Objective == nullptr)
		{
			continue;
		}

		Objective->ActivateObjective(Character);
		Objective->bCanBeCompleted = i == 0 || !bAreObjectivesInSequence;    // adaptive objective activation
		Objective->OnObjectiveCompleted.AddUObject(this, &ThisClass::OnObjectiveCompleted);   // binds local function to objective delegate
	}

	bIsTaken = true;
	CurrentEmployer = Character;

	if (OnQuestStatusCompleted.IsBound())
	{
		OnQuestStatusCompleted.Broadcast(this);
	}
}

void AQuest::OnObjectiveCompleted(UQuestObjective* Objective)		// bound / activated by objectives
{
	if (bAreObjectivesInSequence)
	{
		int32 Index;
		if (ObjectiveSet.Find(Objective, Index) && ObjectiveSet.IsValidIndex(Index + 1))
		{
			ObjectiveSet[Index + 1]->bCanBeCompleted = true;
		}
	}

	if (OnQuestStatusUpdated.IsBound())
	{
		OnQuestStatusUpdated.Broadcast(this);
	}

	if (OnQuestStatusCompleted.IsBound() && IsCompleted())
	{
			OnQuestStatusCompleted.Broadcast(this);
	}
	
}

bool AQuest::IsCompleted() const
{
	if (bAreObjectivesInSequence && ObjectiveSet.IsValidIndex(ObjectiveSet.Num() - 1))
	{
		return ObjectiveSet[ObjectiveSet.Num() - 1]->bIsCompleted;
	}

	for (auto* Objective : ObjectiveSet)
	{
		if (Objective && !Objective->bIsCompleted)
		{
			return false;
		}
	}

	return true;
}

TArray<AActor*> AQuest::GetObjectiveComponents()
{
	TArray<AActor*> ObjCollection;
	for (auto* ThisObjective : ObjectiveSet)
	{
		ObjCollection.Add(ThisObjective->GetInteractiveComponent());
	}

	return ObjCollection;
}

#if WITH_EDITOR

void AQuest::AddInteractObjective()
{
	ObjectiveSet.Add(NewObject<UInteractionObjective>(this));
}

void AQuest::AddLocationObjective()
{
	ObjectiveSet.Add(NewObject<ULocationObjective>(this));
}

void AQuest::AddCollectibleObjective()
{
	ObjectiveSet.Add(NewObject<UCollectibleObjective>(this));
}

void AQuest::AddShootableObjective()
{
	ObjectiveSet.Add(NewObject<UShootableObjective>(this));
}

void AQuest::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
		Ar << bIsTaken << bIsCompleted << CurrentEmployer;  // might need manual update

		for (auto* Obj : ObjectiveSet)
		{
			Obj->Serialize(Ar);
		}
	}
}

#endif