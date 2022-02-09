#include "NpcIndicatorWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UNpcIndicatorWidget::HideExclamation()
{
	QuestIndicator->SetVisibility(ESlateVisibility::Collapsed);
}

void UNpcIndicatorWidget::ShowExclamation()
{
	QuestIndicator->SetVisibility(ESlateVisibility::Visible);
}

void UNpcIndicatorWidget::ChangeText(FString NewText)
{
	NpcName->SetText(FText::FromString(NewText));
}
