// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/FaceFusion/RemoveGalleryImageAsync.h"
#include "Utils/FittingRoomUtils.h"


URemoveGalleryImageAsync* URemoveGalleryImageAsync::RemoveGalleryImage(const FString& Url)
{
	URemoveGalleryImageAsync* Node = NewObject<URemoveGalleryImageAsync>();
	Node->SendRequest(Url);
	return Node;
}

void URemoveGalleryImageAsync::SendRequest(const FString& Url)
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/remove_gallery_image/") + Url;
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("DELETE");
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + UFittingRoomUtils::GetToken());
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->OnProcessRequestComplete().BindUObject(this, &URemoveGalleryImageAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void URemoveGalleryImageAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
	
		if (Code == 200)
		{
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);
			FString Message = JsonObj->GetStringField(TEXT("message"));
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, Message);
			}
		}
		else
		{
			FString Message = UFittingRoomUtils::ParseException(Data);
			if (OnFailure.IsBound())
			{
				OnFailure.Broadcast(Code, Message);
			}
		}
	}
	else
	{
		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(404, TEXT("Not Found"));
		}
	}

	RemoveFromRoot();
}

