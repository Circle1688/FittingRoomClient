// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/Account/ResetPasswordAsync.h"
#include "Utils/FittingRoomUtils.h"


UResetPasswordAsync* UResetPasswordAsync::ResetPassword(const FString& UserName, const FString& NewPassword, const FString& Mobile)
{
	UResetPasswordAsync* Node = NewObject<UResetPasswordAsync>();
	Node->SendRequest(UserName, NewPassword, Mobile);
	return Node;
}

void UResetPasswordAsync::SendRequest(const FString& UserName, const FString& Password, const FString& Mobile)
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/reset_password");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("POST");

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	FString Body = MakeRequestBody(UserName, Password, Mobile);
	
	Request->SetContentAsString(Body);

	Request->OnProcessRequestComplete().BindUObject(this, &UResetPasswordAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UResetPasswordAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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

FString UResetPasswordAsync::MakeRequestBody(const FString& UserName, const FString& Password, const FString& Mobile)
{
	TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject);
	
	Body->SetStringField(TEXT("username"), UserName);
	Body->SetStringField(TEXT("password"), Password);
	Body->SetStringField(TEXT("mobile"), Mobile);
	
	FString OutJsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJsonData);
	FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);

	return OutJsonData;
}
