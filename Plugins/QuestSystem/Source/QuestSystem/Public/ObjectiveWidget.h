#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWidget.generated.h"

class UQuestObjective;
class UCheckBox;
class UTextBlock;

UCLASS()
class QUESTSYSTEM_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(UQuestObjective* Objective);

protected:
	UPROPERTY(meta = (BindWidget))
		UCheckBox* CompletedState;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DescriptionText;

	
};
