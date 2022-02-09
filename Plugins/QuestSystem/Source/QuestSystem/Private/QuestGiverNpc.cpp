#include "QuestGiverNpc.h"
#include "Quest.h"
#include "NpcDialogWidget.h"
#include "QuestList.h"
#include "Components/WidgetComponent.h"
#include "Engine/StaticMesh.h"
#include "NpcIndicatorWidget.h"

AQuestGiverNpc::AQuestGiverNpc()
{
	StatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatusPic"));
	StatusWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StatusWidget->SetWidgetClass(StatusWidgetClass);
	ChangeQuestIndication(false);
}

void AQuestGiverNpc::BeginPlay()
{
	Super::BeginPlay();

	// collecting all quests, assuming we dont add or remove any in runtime
	// also binding quest updating to npc widget
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (auto& Actor : AttachedActors)
	{
		AQuest* Quest = Cast<AQuest>(Actor);
		if (Quest != nullptr)
		{
			Quests.Add(Quest);
			Quest->OnQuestStatusCompleted.AddUObject(this, &AQuestGiverNpc::CheckQuestIndication);
		}
	}

	if (Quests.Num() > 0)
	{
		ChangeQuestIndication(true);
	}
}

void AQuestGiverNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestGiverNpc::Interact_Implementation(AActor* InteractInstigator)
{
	if (InteractInstigator == nullptr)
	{
		return;
	}

	UQuestList* QuestList = Cast<UQuestList>(InteractInstigator->GetComponentByClass(UQuestList::StaticClass()));
	if (QuestList == nullptr)
	{
		return;
	}

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (auto& Actor : AttachedActors)
	{
		AQuest* Quest = Cast<AQuest>(Actor);
		if (Quest == nullptr)
		{
			continue;
		};

		if (Quest->bIsTaken || (Quest->PrerequisiteQuest && !Quest->PrerequisiteQuest->IsCompleted()))
		{
			continue;
		}

		if (QuestDialogWidgetClass)
		{
			UNpcDialogWidget* QuestDialog = CreateWidget<UNpcDialogWidget>(GetWorld(), QuestDialogWidgetClass);
			QuestDialog->Init(Quest);
			QuestDialog->OnQuestAccepted.BindUObject(QuestList, &UQuestList::AddQuest, Quest);
			QuestDialog->OnDialogExit.BindLambda([this, InteractInstigator]()
			{
				NotifyInteractionFinished(this, InteractInstigator);
			});

			QuestDialog->AddToViewport();
			return;
		}
	}

	NotifyInteractionFinished(this, InteractInstigator);
}

void AQuestGiverNpc::CheckQuestIndication(AQuest* PlayerQuest)
{
	bool TempValue = IsQuestAvailable(PlayerQuest);
	ChangeQuestIndication(TempValue);
}

// overly cautious but blind attempt to check for untaken incomplete quests.
bool AQuestGiverNpc::IsQuestAvailable(AQuest* Quest)
{
	if (Quest->bIsTaken)
	{
		if (Quest->IsCompleted())
		{
			for (AQuest* OtherQuest : Quests)
			{
				if (!OtherQuest->bIsTaken)
				{
					return true;
				}
			}

			return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true; //technically no point to check for taken status given how you get in this function on quest update anyway
	}
}

bool AQuestGiverNpc::HasQuests()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	return (AttachedActors.Num() > 0);
}

void AQuestGiverNpc::ChangeQuestIndication(bool FlagState)
{
	if (StatusWidget->GetWidget())
	{
		UNpcIndicatorWidget* ThisWidget = Cast<UNpcIndicatorWidget>(StatusWidget->GetUserWidgetObject());

		if (FlagState)
		{
			ThisWidget->ShowExclamation();
		}
		else
		{
			ThisWidget->HideExclamation();
		}
	}
}

TArray<AActor*> AQuestGiverNpc::GetAllObjectiveComps()
{
	TArray<AActor*> ObjectiveComponents;
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (auto& Actor : AttachedActors)
	{
		AQuest* Quest = Cast<AQuest>(Actor);
		if (Quest == nullptr)
		{
			continue;
		};

		ObjectiveComponents.Append(Quest->GetObjectiveComponents());
	}

	return ObjectiveComponents;
}

const TArray<AQuest*> AQuestGiverNpc::GetQuests()
{
	TArray<AActor*> AttachedActors;
	TArray<AQuest*> QuestList;
	GetAttachedActors(AttachedActors);
	for (auto& Actor : AttachedActors)
	{
		AQuest* Quest = Cast<AQuest>(Actor);
		if (Quest == nullptr)
		{
			continue;
		};

		QuestList.Add(Quest);
	}

	return QuestList;
}

void AQuestGiverNpc::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaveGame())
	{
	
		for (auto* ThisQuest : GetQuests())
		{
			ThisQuest->Serialize(Ar);  // save/load

			if (Ar.IsLoading())		// reinitializing quest widget on player
			{
				if (ThisQuest->bIsTaken && ThisQuest->GetCurrentEmployer())
				{
					UQuestList* QuestList = Cast<UQuestList>(ThisQuest->GetCurrentEmployer()->GetComponentByClass(UQuestList::StaticClass()));
					if (QuestList)
					{
						QuestList->PurgeQuests();		//very stupid widget clearance, because theres no way to purge list only once, with any player amount
														//without some extreme sorting of players and taken quests, AND finding which quest is active
						QuestList->AddQuest(ThisQuest);
						QuestList->SetActiveQuest(ThisQuest);
					}
				}
			}
		}


	}
	
}