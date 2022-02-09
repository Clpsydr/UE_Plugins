#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FpsGameInstance.generated.h"

class USaveManager;

UCLASS()
class FPSTEST_API UFpsGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init() override;

	// its not a complete static object, so it needs worldcontextobject, but it will be supplied to blueprints
	UFUNCTION(BlueprintPure, meta = (WorldContext = WorldContextObject))
		static USaveManager* GetSaveManager(UObject* WorldContextObject);

protected:

	UPROPERTY()
		USaveManager* SaveManager;
};
