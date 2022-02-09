/*
* Savemanager is retrieving all information from playerinstance in the world, including collection of cubes to shoot
* cubes are spawned on start by playerinstance as well, their positions are hardcoded there.
*/
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveManager.generated.h"

class USaveGame;
class UFpsSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveAction, const FString&, SlotName);

UCLASS()
class FPSTEST_API USaveManager : public UObject
{
	GENERATED_BODY()

public:
	
	virtual UWorld* GetWorld() const override
	{
		//to avoid drawing getworld for ???
		return HasAnyFlags(RF_ClassDefaultObject) ? nullptr : GetOuter()->GetWorld();
	}

	UPROPERTY(BlueprintAssignable)
		FOnSaveAction OnGameSaved;

	UPROPERTY(BlueprintAssignable)
		FOnSaveAction OnGameLoaded;

	void Init();

	UFUNCTION(BlueprintPure)
		bool DoesSaveGameExist(const FString& SlotName) const;

	UFUNCTION(BlueprintCallable)
		void LoadGame(const FString& SlotName);

	UFUNCTION(BlueprintCallable)
		void SaveGame(const FString& SlotName);

protected:
	void OnGameLoadedFunc(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame);

	void OnGameSavedFunc(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	UPROPERTY(BlueprintReadWrite)
		UFpsSaveGame* CurrentSave;
};
