// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/FaceFusion/GetGalleryImageAsync.h"
#include "Utils/FittingRoomUtils.h"


UGetGalleryImageAsync* UGetGalleryImageAsync::GetGalleryImage(const FString& Url)
{
	UGetGalleryImageAsync* Node = NewObject<UGetGalleryImageAsync>();
	Node->SendRequest(Url);
	return Node;
}

void UGetGalleryImageAsync::SendRequest(const FString& Url)
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl = UFittingRoomUtils::GetServerUrl() + TEXT("/get_gallery_image/") + Url;
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("GET");

	// Request header
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + UFittingRoomUtils::GetToken());
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->OnRequestProgress().BindUObject(this, &UGetGalleryImageAsync::OnDownloadProgress);
	Request->OnProcessRequestComplete().BindUObject(this, &UGetGalleryImageAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UGetGalleryImageAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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

void UGetGalleryImageAsync::OnDownloadProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived)
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
