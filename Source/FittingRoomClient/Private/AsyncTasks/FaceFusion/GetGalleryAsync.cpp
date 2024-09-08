// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/FaceFusion/GetGalleryAsync.h"
#include "Utils/FittingRoomUtils.h"


UGetGalleryAsync* UGetGalleryAsync::GetGallery()
{
	UGetGalleryAsync* Node = NewObject<UGetGalleryAsync>();
	Node->SendRequest();
	return Node;
}

void UGetGalleryAsync::SendRequest()
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/get_gallery");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("GET");
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + UFittingRoomUtils::GetToken());
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->OnProcessRequestComplete().BindUObject(this, &UGetGalleryAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UGetGalleryAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
	
		if (Code == 200)
		{
			TArray<FString> Gallery_urls;
			
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);

			for (auto Gallery_url : JsonObj->GetArrayField("gallery_urls"))
			{
				Gallery_urls.Add(Gallery_url->AsString());
			}
			
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, Gallery_urls, TEXT("Get gallery successfully"));
			}
		}
		else
		{
			FString Message = UFittingRoomUtils::ParseException(Data);
			if (OnFailure.IsBound())
			{
				OnFailure.Broadcast(Code, {}, Message);
			}
		}
	}
	else
	{
		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(404, {}, TEXT("Not Found"));
		}
	}

	RemoveFromRoot();
}

