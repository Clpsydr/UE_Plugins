#include "QuestDescriptionWidget.h"
#include "Quest.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "ObjectiveWidget.h"

void UQuestDescriptionWidget::Init(AQuest* Quest)
{
	if (Quest == nullptr)
	{
		return;
	}

	NameText->SetText(Quest->Name);
	DescriptionText->SetText(Quest->Description);

	if (ObjectiveWidgetClass)
	{
		ObjectiveList->ClearChildren();
		for (auto* Objective : Quest->GetObjectives())
		{
			auto* ObjectiveWidget = CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
			ObjectiveWidget->Init(Objective);
			ObjectiveList->AddChild(ObjectiveWidget);
		}
	}

}

