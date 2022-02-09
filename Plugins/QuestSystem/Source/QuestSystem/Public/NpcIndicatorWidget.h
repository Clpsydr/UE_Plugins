#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NpcIndicatorWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class QUESTSYSTEM_API UNpcIndicatorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* QuestIndicator;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* NpcName;

public:
	UFUNCTION()
		void ShowExclamation();

	UFUNCTION()
		void HideExclamation();

	UFUNCTION()
		void ChangeText(FString NewText);
};
