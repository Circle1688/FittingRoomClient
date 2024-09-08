// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/Account/LoginAsync.h"
#include "Utils/FittingRoomUtils.h"


ULoginAsync* ULoginAsync::Login(const FString& UserName, const FString& Password)
{
	ULoginAsync* Node = NewObject<ULoginAsync>();
	Node->SendRequest(UserName, Password);
	return Node;
}

void ULoginAsync::SendRequest(const FString& UserName, const FString& Password)
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/login");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("POST");

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	FString Body = MakeRequestBody(UserName, Password);
	
	Request->SetContentAsString(Body);

	Request->OnProcessRequestComplete().BindUObject(this, &ULoginAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void ULoginAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
	
		if (Code == 200)
		{
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);
			FString Token = JsonObj->GetStringField(TEXT("token"));
			
			UFittingRoomUtils::SetToken(Token);
			
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, TEXT("Login successfully"));
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

FString ULoginAsync::MakeRequestBody(const FString& UserName, const FString& Password)
{
	TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject);
	
	Body->SetStringField(TEXT("username"), UserName);
	Body->SetStringField(TEXT("password"), Password);
	
	FString OutJsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJsonData);
	FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);

	return OutJsonData;
}
