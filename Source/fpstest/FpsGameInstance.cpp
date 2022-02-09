#include "FpsGameInstance.h"
#include "SaveManager.h"
#include "Kismet/GameplayStatics.h"

void UFpsGameInstance::Init()
{
	Super::Init();

	GLog->Log(ELogVerbosity::Warning, TEXT("Mygameinstance::Init success"));

	SaveManager = NewObject<USaveManager>(this);
	SaveManager->Init();
}

USaveManager* UFpsGameInstance::GetSaveManager(UObject* WorldContextObject)
{
	auto* GameInstance = Cast<UFpsGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));

	return GameInstance ? GameInstance->SaveManager : nullptr;
}
