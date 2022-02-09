#include "MediaSelector.h"
#include "DesktopPlatform/Public/IDesktopPlatform.h"
#include "DesktopPlatform/Public/DesktopPlatformModule.h"
#include "FileMediaSource.h"
#include "MediaPlayer.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MediaSoundComponent.h"

#include "Components/Button.h"

void UMediaSelector::NativeConstruct()
{
	Super::NativeConstruct();

	if (SelectMediaButton)
	{
		SelectMediaButton->OnPressed.AddDynamic(this, &ThisClass::OnMediaButtonPress);
	}
}

void UMediaSelector::OnMediaButtonPress()
{
	if (MediaPlayer)
	{
		FString MediaPath;

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
				MediaPath = OutFiles[0];
			}
		}

		if (MediaPath.Len() > 0)
		{

			//assuming mediapath would always have extension in the end, we wont have to run stuff for a wrong filetype
			if (MediaPath.EndsWith(".png") || MediaPath.EndsWith(".jpg"))
			{
				//requires dynamic material unless its just loaded into widget
				UTexture2D* BoardTexture = UKismetRenderingLibrary::ImportFileAsTexture2D(this, MediaPath);
				float ImgRatio = float(BoardTexture->GetSizeX()) / float(BoardTexture->GetSizeY());

				// Hardcoded to 500px for the sake of fast fixup to the widget that cant grow more than that.
				if (ScaleSetter && ImgRatio != 0)
				{
					if (ImgRatio > 1.f)
					{
						ScaleSetter->SetWidthOverride(500);
						ScaleSetter->SetHeightOverride(500 / ImgRatio);
					}
					else
					{
						ScaleSetter->SetWidthOverride(500 * ImgRatio);
						ScaleSetter->SetHeightOverride(500);
					}


				}

				ImagePresenter->SetBrushFromTexture(BoardTexture);
			}

			if (MediaPath.EndsWith(".mp4"))
			{
				UFileMediaSource* MediaSource = NewObject<UFileMediaSource>();
				MediaSource->FilePath = MediaPath;
				MediaPlayer->OpenSource(MediaSource);

				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

				// also lazy binding to whatever actor on scene
				if (FoundActors[0])
				{
					UMediaSoundComponent* MediaSound = NewObject<UMediaSoundComponent>(FoundActors[0]);
					MediaSound->SetMediaPlayer(MediaPlayer);
					MediaSound->RegisterComponent();


					// This is awful but thankfully I dont have to use that yet, 'cause I couldnt figure out how to bind local method to someone elses delegate
				/*	FIntPoint Something = MediaPlayer->GetVideoTrackDimensions(0, 0);
					FVector NewDimensions = FVector(2.f * Something.X / Something.Y, 2.f * Something.Y / Something.X, 2.f);
					FoundActors[32]->SetActorScale3D(NewDimensions);*/
				}

				// this can't respond in time either tbh, but mediaplayer handles it automatically anyway
				if (MediaPlayer->IsReady())
				{
					MediaPlayer->Play();
				}
			}

		}
	}
}
