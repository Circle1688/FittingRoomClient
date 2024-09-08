// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/Clothes/GetClothesPreviewAsync.h"
#include "Utils/FittingRoomUtils.h"
#include "Misc/Paths.h"
#include "Utils/FaceSwapUtilsBPLibrary.h"


UGetClothesPreviewAsync* UGetClothesPreviewAsync::GetClothesPreview(const FString& Url)
{
	UGetClothesPreviewAsync* Node = NewObject<UGetClothesPreviewAsync>();
	Node->Url = Url;
	return Node;
}

void UGetClothesPreviewAsync::Activate()
{
	AddToRoot();
	const FString SaveDirPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
	FilePath = FPaths::Combine(SaveDirPath, TEXT("ClothesCache"), Url);
	
	if (FPaths::FileExists(FilePath))
	{
		TArray<uint8> Data;
		FFileHelper::LoadFileToArray(Data, *FilePath);
		if (OnFinish.IsBound())
		{
			OnFinish.Broadcast(200, TEXT("Use cache"), 1.0f, Data);
		}
		RemoveFromRoot();
	}
	else
	{
		SendRequest();
	}
}

void UGetClothesPreviewAsync::SendRequest()
{
	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl = UFittingRoomUtils::GetServerUrl() + TEXT("/get_preview/") + Url;
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("GET");

	// Request header
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->OnRequestProgress().BindUObject(this, &UGetClothesPreviewAsync::OnDownloadProgress);
	Request->OnProcessRequestComplete().BindUObject(this, &UGetClothesPreviewAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UGetClothesPreviewAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (Request->GetResponse()->GetContentLength() > 0)
	{
		if (OnProgress.IsBound())
		{
			OnProgress.Broadcast(200, "Download finished", 1.0f, {});
		}
	}
	
	if (bWasSuccessful && Response.IsValid())
	{
		int32 Code = Response->GetResponseCode();
	
		if (Code == 200)
		{
			UFaceSwapUtilsBPLibrary::SaveBytesToFile(FilePath, Response->GetContent());
			if (OnFinish.IsBound())
			{
				OnFinish.Broadcast(Code, TEXT("Download finished"), 1.0f, Response->GetContent());
			}
		}
		else
		{
			FString Data = Response->GetContentAsString();
			FString Message = UFittingRoomUtils::ParseException(Data);
			if (OnFailure.IsBound())
			{
				OnFailure.Broadcast(Code, Message, 0.0f, {});
			}
		}
	}
	else
	{
		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(404, TEXT("Not Found"), 0.0f, {});
		}
	}

	RemoveFromRoot();
}

void UGetClothesPreviewAsync::OnDownloadProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived)
{
	if (Request->GetResponse()->GetContentLength() > 0)
	{
		float Percent = BytesReceived / Request->GetResponse()->GetContentLength() * 100;
		if (OnProgress.IsBound())
		{
			OnProgress.Broadcast(200, "Downloading", Percent, {});
		}
	}
}
