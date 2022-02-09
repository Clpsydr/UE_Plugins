// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestEditor.h"
#include "QuestEditorStyle.h"
#include "QuestEditorCommands.h"
#include "LevelEditor.h"
#include "Editor/EditorEngine.h"
#include "Engine/Selection.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "QuestTableRow.h"
#include "Quest.h"
#include "QuestGiverNpc.h"

static const FName QuestEditorTabName("QuestEditor");

#define LOCTEXT_NAMESPACE "FQuestEditorModule"

void FQuestEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FQuestEditorStyle::Initialize();
	FQuestEditorStyle::ReloadTextures();

	FQuestEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FQuestEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FQuestEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FQuestEditorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(QuestEditorTabName, FOnSpawnTab::CreateRaw(this, &FQuestEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FQuestEditorTabTitle", "QuestEditor"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	// Adding plugin access hooks

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());	//???
	MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands,
		FMenuExtensionDelegate::CreateRaw(this, &FQuestEditorModule::AddMenuExtension));

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender());   //??? formerly new FExtender  without brackets
	ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands,
		FToolBarExtensionDelegate::CreateRaw(this ,&FQuestEditorModule::AddToolBarExtension));

	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);

	//
}

void FQuestEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FQuestEditorStyle::Shutdown();

	FQuestEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(QuestEditorTabName);
}

void FQuestEditorModule::AddMenuExtension(FMenuBuilder& Build)
{
	Build.AddMenuEntry(FQuestEditorCommands::Get().OpenPluginWindow);
}

void FQuestEditorModule::AddToolBarExtension(FToolBarBuilder& Build)
{
	Build.AddToolBarButton(FQuestEditorCommands::Get().OpenPluginWindow);
}

TSharedRef<ITableRow> FQuestEditorModule::GenerateQuestRecord(AQuest* Quest, const TSharedRef<STableViewBase>& Table)
{
	return SNew(SQuestTableRow, Table)
		.Quest(Quest);
}

TSharedRef<SWidget> FQuestEditorModule::GetTableRowHeader(FString RowText)
{
	return SNew(SBorder)
		.HAlign(HAlign_Center)
		.Padding(5.f)
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString(RowText))
		];
}

FReply FQuestEditorModule::OnMoveObjects()
{
	if (GEditor)		//global static variable that contains state of the editor
	{
		for (auto Iter = GEditor->GetSelectedActorIterator(); Iter; ++Iter)
		{
			if (AActor* Actor = Cast<AActor>(*Iter))
			{
				Actor->AddActorLocalOffset(FVector(30.f, 20.f, 10.f));
			}
		}
	}

	return FReply::Handled();
}

TSharedRef<SDockTab> FQuestEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	const FText WidgetText = LOCTEXT("MoveObjects", "Move Objects");

	UpdateQuestInfo();

	return SNew(SDockTab)
			.TabRole(NomadTab)
			.OnTabClosed_Raw(this, &FQuestEditorModule::TabClosed)  // Cleanup
			[
				SNew(SBox)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(SButton)
						.OnClicked_Raw(this, &FQuestEditorModule::OnMoveObjects)
						[
							SNew(STextBlock)
							.Text(WidgetText)
						]
					]

					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(SButton)
						.OnPressed_Raw(this, &FQuestEditorModule::UpdateQuestListView) //Onpressed function doesnt require FReply in returns for function argument
						[
							SNew(STextBlock)
							.Text(FText::FromString("Get Selected Quest Data"))
						]
					]

					+ SVerticalBox::Slot()
					.FillHeight(1.f)
					[
						SNew(SBox)
						[
							SAssignNew(QuestsList, SListView<AQuest*>)
							.ItemHeight(30)
							.ListItemsSource(&Quests)
							.OnGenerateRow_Raw(this, &FQuestEditorModule::GenerateQuestRecord)  //
							.HeaderRow
							(
								SNew(SHeaderRow)
								+ SHeaderRow::Column("Name")[GetTableRowHeader("Name")]
								+ SHeaderRow::Column("Description")[GetTableRowHeader("Description")]
								+ SHeaderRow::Column("IsStory")[GetTableRowHeader("Story related")]
							)
						]

					]
				]
			];
}

void FQuestEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(QuestEditorTabName);
}

void FQuestEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
}

void FQuestEditorModule::UpdateQuestInfo()
{
	Quests.Empty();
	for (FSelectionIterator Iter(*GEditor->GetSelectedActors()); Iter; ++Iter)
	{
		if (auto* Quest = Cast<AQuest>(*Iter))
		{
			Quests.AddUnique(Quest);		// updating container for later listview process
		}

		// attempt to not just copy the code
		if (auto* QuestActor = Cast<AQuestGiverNpc>(*Iter))
		{
			for (auto* ThisQuest : QuestActor->GetQuests())
			{
				Quests.AddUnique(ThisQuest);
			}
		}
	}

	if (Quests.Num() > 0)
	{
		GEditor->SelectNone(true, true);
		for (auto* Quest : Quests)
		{
			GEditor->SelectActor(Quest, true, false);
		}
	}
}

void FQuestEditorModule::UpdateQuestListView()
{
	UpdateQuestInfo();
	QuestsList->RequestListRefresh();  //Only updates properly if structure is not fundamentally changed
}

void FQuestEditorModule::TabClosed(TSharedRef<SDockTab> ClosingTab)
{
	QuestsList.Reset();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestEditorModule, QuestEditor)