#include "ObjectiveWatcherWidget.h"
#include "Quest.h"
#include "Components/VerticalBox.h"
#include "QuestObjective.h"
#include "ObjectiveWidget.h"

void UObjectiveWatcherWidget::SetCurrentObjective(AQuest* Quest)
{
	if (ObjectivesList && ObjectiveWidgetClass)
	{
		ObjectivesList->ClearChildren();
		for (UQuestObjective* Objective : Quest->GetObjectives())
		{
			UObjectiveWidget* ObjectiveWidget = CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
			ObjectiveWidget->Init(Objective);
			ObjectivesList->AddChildToVerticalBox(ObjectiveWidget);
		}
	}
}



