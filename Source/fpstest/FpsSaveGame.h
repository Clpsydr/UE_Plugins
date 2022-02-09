/*
* Two structs, for dummy object data, and player data.
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Engine/UserDefinedStruct.h"
#include "FpsSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FBoxInfo
{
	GENERATED_BODY()

	UPROPERTY()
		FVector Position;

	UPROPERTY()
		FVector Rotation;

	UPROPERTY()
		int32 Counter;

	UPROPERTY()
		FVector Scale;
};

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY()
		int32 Ammo;

	UPROPERTY()
		float Health;

	UPROPERTY()
		FVector Position;
};

UCLASS()
class FPSTEST_API UFpsSaveGame : public USaveGame
{
	GENERATED_BODY()

// saved info goes here! need to make sure it will be marked as uproperty
public:
	UPROPERTY(BlueprintReadWrite)
		float TestFloat;

	UPROPERTY(BlueprintReadWrite)
		TMap<int32, FBoxInfo> SavedBoxes;	

	UPROPERTY(BlueprintReadWrite)
		FPlayerData SavedPlayerStats;

	//binary serialization related data 
	UPROPERTY()
		TArray<uint8> Bytes;

	void CollectData(UWorld* World);

	void ApplyData(UWorld* World);

	
};
