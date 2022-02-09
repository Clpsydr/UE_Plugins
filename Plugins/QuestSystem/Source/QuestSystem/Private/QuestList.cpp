#include "QuestList.h"
#include "Quest.h"
#include "ObjectiveWatcherWidget.h"

void UQuestList::AddQuest(AQuest* Quest)
{
	if (ActiveQuest == nullptr || ActiveQuest->IsCompleted())
	{
		ActiveQuest = Quest;
		OnActiveQuestUpdated.Broadcast(ActiveQuest);
	}

	if (Quest)
	{
		AcceptedQuests.AddUnique(Quest);
		Quest->AcceptQuest(GetOwner());
		Quest->OnQuestStatusUpdated.AddLambda([this](AQuest* NewQuest)  
		{
			if (ActiveQuest == NewQuest)
			{
				if (OnActiveQuestUpdated.IsBound())
				{
					OnActiveQuestUpdated.Broadcast(NewQuest);
				}
			}
		});
	}

}

void UQuestList::SetActiveQuest(AQuest* Quest)
{
	if (AcceptedQuests.Contains(Quest))
	{
		ActiveQuest = Quest;
		if (OnActiveQuestUpdated.IsBound())
		{
			OnActiveQuestUpdated.Broadcast(Quest);
		}
	}
}

void UQuestList::PurgeQuests()
{
	AcceptedQuests.Empty();
}

void UQuestList::BeginPlay()
{
	Super::BeginPlay();

	if (ObjectiveWatcherWidgetClass)
	{
		UObjectiveWatcherWidget* CurrentObjectiveWidget = CreateWidget<UObjectiveWatcherWidget>(GetWorld(), ObjectiveWatcherWidgetClass);

		OnActiveQuestUpdated.AddUObject(CurrentObjectiveWidget, &UObjectiveWatcherWidget::SetCurrentObjective);

		CurrentObjectiveWidget->AddToViewport();
	}
}
