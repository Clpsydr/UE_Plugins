#include "ObjectiveWidget.h"
#include "QuestObjective.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UObjectiveWidget::Init(UQuestObjective* Objective)
{
	if (Objective == nullptr)
	{
		return; 
	}

	CompletedState->SetIsChecked(Objective->bIsCompleted);
	DescriptionText->SetText(Objective->Description);
}

