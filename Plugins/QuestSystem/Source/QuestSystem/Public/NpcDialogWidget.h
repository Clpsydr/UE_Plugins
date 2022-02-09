#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NpcDialogWidget.generated.h"

class UQuestDescriptionWidget;
class AQuest;
class UButton;

UCLASS()
class QUESTSYSTEM_API UNpcDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void Init(AQuest* Quest);

	FSimpleDelegate OnQuestAccepted;

	FSimpleDelegate OnDialogExit;

protected:
	UPROPERTY(meta = (BindWidget))
		UQuestDescriptionWidget* Description;

	UPROPERTY(meta = (BindWidget))
		UButton* AcceptButton;

	UPROPERTY(meta = (BindWidget))
		UButton* CancelButton;

	UFUNCTION()
		void OnAccepted();

	UFUNCTION()
		void OnCancelled();

	UFUNCTION()
		void HideDialog();
};


