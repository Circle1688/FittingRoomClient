// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/Account/GetUserInfoAsync.h"
#include "Utils/FittingRoomUtils.h"


UGetUserInfoAsync* UGetUserInfoAsync::GetUserInfo()
{
	UGetUserInfoAsync* Node = NewObject<UGetUserInfoAsync>();
	Node->SendRequest();
	return Node;
}

void UGetUserInfoAsync::SendRequest()
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/get_user_info");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("GET");
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + UFittingRoomUtils::GetToken());
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->OnProcessRequestComplete().BindUObject(this, &UGetUserInfoAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UGetUserInfoAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FUserInfo UserInfo;
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
		FString Message;
	
		if (Code == 200)
		{
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);
			UserInfo.Mobile = JsonObj->GetStringField(TEXT("mobile"));
			UserInfo.Username = JsonObj->GetStringField(TEXT("username"));
			UserInfo.Birth = JsonObj->GetNumberField(TEXT("birth"));
			UserInfo.Ethnicity = static_cast<EEthnicity>(JsonObj->GetNumberField(TEXT("ethnicity")));
			
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, "ok", UserInfo);
			}
		}
		else
		{
			Message = UFittingRoomUtils::ParseException(Data);
			if (OnFailure.IsBound())
			{
				OnFailure.Broadcast(Code, Message, UserInfo);
			}
		}
	}
	else
	{
		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(404, TEXT("Not Found"), UserInfo);
		}
	}

	RemoveFromRoot();
}
