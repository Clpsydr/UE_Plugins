#include "SaveManager.h"

#include "FpsSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "fpstestCharacter.h"
#include "CountBlock.h"

void USaveManager::Init()
{
	CurrentSave = Cast<UFpsSaveGame>(UGameplayStatics::CreateSaveGameObject(UFpsSaveGame::StaticClass()));
}

bool USaveManager::DoesSaveGameExist(const FString& SlotName) const
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);
}

//asynchronous solutions for save and load
//sync method would involve CurrentSave = Cast<UTestSaveGame>(UGameplayStatics::LoadGameFromSlot(Slotname, 0))
void USaveManager::LoadGame(const FString& SlotName)
{
	if (!DoesSaveGameExist(SlotName))
	{
		return;
	}

	FAsyncLoadGameFromSlotDelegate LoadDelegate;
	LoadDelegate.BindUObject(this, &ThisClass::OnGameLoadedFunc);

	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, LoadDelegate);
}

void USaveManager::SaveGame(const FString& SlotName)
{
	/// saving through UE4 means
	/*auto* SavedPlayer = Cast<AfpstestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (SavedPlayer)
	{
		CurrentSave->SavedPlayerStats.Ammo = SavedPlayer->GetAmmo();
		CurrentSave->SavedPlayerStats.Position = SavedPlayer->GetActorTransform().GetLocation();
		CurrentSave->SavedPlayerStats.Health = SavedPlayer->GetHealth();
		
		for (auto& Box : SavedPlayer->BoxSet)
		{
			FBoxInfo NewDataSet;
			NewDataSet.Position = Box.Value->GetActorLocation();
			NewDataSet.Rotation = FVector(Box.Value->GetActorRotation().Yaw, Box.Value->GetActorRotation().Pitch, Box.Value->GetActorRotation().Roll);
			NewDataSet.Scale = Box.Value->GetActorScale();
			NewDataSet.Counter = Cast<ACountBlock>(Box.Value)->BlockParam;
			CurrentSave->SavedBoxes.Emplace(Box.Key, NewDataSet);
		}
	}*/
	///

	FAsyncSaveGameToSlotDelegate SaveDelegate;
	SaveDelegate.BindUObject(this, &ThisClass::OnGameSavedFunc);

	///binary archive collection
	CurrentSave->CollectData(GetWorld());
	///

	UGameplayStatics::AsyncSaveGameToSlot(CurrentSave, SlotName, 0, SaveDelegate);
}

void USaveManager::OnGameLoadedFunc(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	CurrentSave = Cast<UFpsSaveGame>(SaveGame);

	/// returning saved info
	/*auto* SavedPlayer = Cast<AfpstestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (SavedPlayer)
	{
		SavedPlayer->SetAmmoAndPos(CurrentSave->SavedPlayerStats.Ammo, CurrentSave->SavedPlayerStats.Position, CurrentSave->SavedPlayerStats.Health);

		for (auto& Box : CurrentSave->SavedBoxes)
		{
			AActor** WorldBox = SavedPlayer->BoxSet.Find(Box.Key);
			if (WorldBox)
			{
				(*WorldBox)->SetActorLocation(Box.Value.Position);
				(*WorldBox)->SetActorRotation(Box.Value.Rotation.ToOrientationRotator());
				(*WorldBox)->SetActorScale3D(Box.Value.Scale);
				Cast<ACountBlock>((*WorldBox))->BlockParam = Box.Value.Counter;
			}
		}
	}*/
	///
		
	OnGameLoaded.Broadcast(SlotName);

	/// Binary loading
		CurrentSave->ApplyData(GetWorld());
	///
}

void USaveManager::OnGameSavedFunc(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	OnGameSaved.Broadcast(SlotName);
}
