#include "VideoPlayer.h"
#include "DesktopPlatform/Public/IDesktopPlatform.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "MediaPlayer.h"
#include "FileMediaSource.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "MediaSoundComponent.h"

AVideoPlayer::AVideoPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

	TabloidBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("playback frame"));
	RootComponent = TabloidBody;
}

void AVideoPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (MediaPlayer)
	{
		FString VideoPath;
		
		IDesktopPlatform* Platform = FDesktopPlatformModule::Get();
		if (Platform)
		{
			auto* ParentHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

			FString FileTypes = "All Files(*.PNG;*.JPG;*.MP4)|*.PNG;*.JPG;*.MP4|"
				"Image Files(*.PNG;*.JPG;)|*.PNG;*.JPG;|"
				"Video Files(*.MP4)|*.MP4";

			TArray<FString> OutFiles;

			Platform->OpenFileDialog(ParentHandle, "Select a media file", FPaths::GameSourceDir(), "", FileTypes, 0, OutFiles);

			if (OutFiles.Num() > 0)
			{
				VideoPath = OutFiles[0];
			}
		}

		/*if (VideoPath.EndsWith(".png"))
		{
			//requires dynamic material unless its just loaded into widget
			UTexture2D* BoardTexture = UKismetRenderingLibrary::ImportFileAsTexture2D(this, VideoPath);
		}*/

		UFileMediaSource* MediaSource = NewObject<UFileMediaSource>();
		MediaSource->FilePath = VideoPath;
		MediaPlayer->OpenSource(MediaSource);

		UMediaSoundComponent* MediaSound = NewObject<UMediaSoundComponent>(this);  //newobject requires outer actor. It will have to be bound
		MediaSound->SetMediaPlayer(MediaPlayer);
		MediaSound->RegisterComponent();

		//MediaPlayer->OnMediaOpened
		//MediaPlayer->GetVideoTrackDimensions();
		if (MediaPlayer->IsReady())
		{
			MediaPlayer->Play();
		}
	}
}