// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/Account/UpdateUserInfoAsync.h"
#include "Utils/FittingRoomUtils.h"


UUpdateUserInfoAsync* UUpdateUserInfoAsync::Register(const FUserInfo& UserInfo)
{
	UUpdateUserInfoAsync* Node = NewObject<UUpdateUserInfoAsync>();
	Node->SendRequest(UserInfo);
	return Node;
}

void UUpdateUserInfoAsync::SendRequest(const FUserInfo& UserInfo)
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/update_user_info");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("POST");

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	FString Body = MakeRequestBody(UserInfo);
	
	Request->SetContentAsString(Body);

	Request->OnProcessRequestComplete().BindUObject(this, &UUpdateUserInfoAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UUpdateUserInfoAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
		FString Message;
	
		if (Code == 200)
		{
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);
			Message = JsonObj->GetStringField(TEXT("message"));
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, Message);
			}
		}
		else
		{
			Message = UFittingRoomUtils::ParseException(Data);
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

FString UUpdateUserInfoAsync::MakeRequestBody(const FUserInfo& UserInfo)
{
	TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject);

	Body->SetStringField(TEXT("mobile"), UserInfo.Mobile);
	Body->SetStringField(TEXT("username"), UserInfo.Username);
	Body->SetNumberField(TEXT("birth"), UserInfo.Birth);
	Body->SetNumberField(TEXT("ethnicity"), static_cast<int32>(UserInfo.Ethnicity));
	
	FString OutJsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJsonData);
	FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);

	return OutJsonData;
}
