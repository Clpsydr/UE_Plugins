#include "FpsSaveGame.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Kismet/GameplayStatics.h"
#include "QuestGiverNpc.h"

void UFpsSaveGame::CollectData(UWorld* World)
{
	if (APawn* SavePawn = World->GetFirstPlayerController()->GetPawn())
	{
		FMemoryWriter MemoryWriter(Bytes, true);
		
		FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, true);
		Ar.ArIsSaveGame = true;

		/// order of serialization here
		SavePawn->Serialize(Ar);

		TArray<AActor*> NpcCollection;
		UGameplayStatics::GetAllActorsOfClass(World, AQuestGiverNpc::StaticClass(), NpcCollection);  // Should have been a collection manager
		for (auto* Npc : NpcCollection)
		{
			Npc->Serialize(Ar);
		}
		///
	}
}

void UFpsSaveGame::ApplyData(UWorld* World)
{
	if (APawn* SavePawn = World->GetFirstPlayerController()->GetPawn())
	{
		FMemoryReader MemoryReader(Bytes, true);

		FObjectAndNameAsStringProxyArchive Ar(MemoryReader, true);
		Ar.ArIsSaveGame = true;


		///		
		SavePawn->Serialize(Ar);

		TArray<AActor*> NpcCollection;
		UGameplayStatics::GetAllActorsOfClass(World, AQuestGiverNpc::StaticClass(), NpcCollection); 
		for (auto* Npc : NpcCollection)
		{
			Npc->Serialize(Ar);
		}
		///
	}
}