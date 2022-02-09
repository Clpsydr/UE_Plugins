#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestDescriptionWidget.generated.h"

class AQuest;
class UTextBlock;
class UScrollBox;
class UObjectiveWidget;

UCLASS()
class QUESTSYSTEM_API UQuestDescriptionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void Init(AQuest* Quest);

protected:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
		UScrollBox* ObjectiveList;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DescriptionText;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;



};
