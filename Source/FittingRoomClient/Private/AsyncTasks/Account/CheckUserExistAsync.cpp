// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/Account/CheckUserExistAsync.h"
#include "Utils/FittingRoomUtils.h"


UCheckUserExistAsync* UCheckUserExistAsync::CheckUserExists(const FString& Email)
{
	UCheckUserExistAsync* Node = NewObject<UCheckUserExistAsync>();
	Node->SendRequest(Email);
	return Node;
}

void UCheckUserExistAsync::SendRequest(const FString& Email)
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/check_user_exists");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("POST");

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	FString Body = MakeRequestBody(Email);
	
	Request->SetContentAsString(Body);

	Request->OnProcessRequestComplete().BindUObject(this, &UCheckUserExistAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UCheckUserExistAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
	
		if (Code == 200)
		{
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);
			bool user_exists = JsonObj->GetBoolField(TEXT("user_exists"));
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, user_exists, TEXT("Query successfully"));
			}
		}
		else
		{
			FString Message = UFittingRoomUtils::ParseException(Data);
			if (OnFailure.IsBound())
			{
				OnFailure.Broadcast(Code, true, Message);
			}
		}
	}
	else
	{
		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(404, true, TEXT("Not Found"));
		}
	}

	RemoveFromRoot();
}

FString UCheckUserExistAsync::MakeRequestBody(const FString& Email)
{
	TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject);
	
	Body->SetStringField(TEXT("email"), Email);
	
	FString OutJsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJsonData);
	FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);

	return OutJsonData;
}
