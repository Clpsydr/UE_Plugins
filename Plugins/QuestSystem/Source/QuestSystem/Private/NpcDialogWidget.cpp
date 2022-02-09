#include "NpcDialogWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "QuestDescriptionWidget.h"
#include "Quest.h"

void UNpcDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AcceptButton)
	{
		AcceptButton->OnReleased.AddDynamic(this, &ThisClass::OnAccepted);
	}

	if (CancelButton)
	{
		CancelButton->OnReleased.AddDynamic(this, &ThisClass::OnCancelled);
	}

	auto* PlayerCtrl = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerCtrl, this);
	PlayerCtrl->SetShowMouseCursor(true);

}

void UNpcDialogWidget::Init(AQuest* Quest)
{
	if (Description)
	{
		Description->Init(Quest);
	}
}

void UNpcDialogWidget::OnAccepted()
{
	HideDialog();
	OnQuestAccepted.ExecuteIfBound();
}

void UNpcDialogWidget::OnCancelled()
{
	HideDialog();
}

void UNpcDialogWidget::HideDialog()
{
	auto* PlayerCtrl = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerCtrl);
	PlayerCtrl->SetShowMouseCursor(false);

	RemoveFromViewport();

	OnDialogExit.ExecuteIfBound();
}

