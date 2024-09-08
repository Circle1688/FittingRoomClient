// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/FaceFusion/GetTaskStatusAsync.h"
#include "Utils/FittingRoomUtils.h"


UGetTaskStatusAsync* UGetTaskStatusAsync::GetTaskStatus(const FString& TaskId)
{
	UGetTaskStatusAsync* Node = NewObject<UGetTaskStatusAsync>();
	Node->SendRequest(TaskId);
	return Node;
}

void UGetTaskStatusAsync::SendRequest(const FString& TaskId)
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	// 连接地址
	FString RequestUrl =  UFittingRoomUtils::GetServerUrl() + TEXT("/face_swap/") + TaskId;
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("GET");
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + UFittingRoomUtils::GetToken());
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->OnProcessRequestComplete().BindUObject(this, &UGetTaskStatusAsync::OnHttpResponse);
	Request->ProcessRequest();
	
}

void UGetTaskStatusAsync::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
	
		if (Code == 200)
		{
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);
			FString Status = JsonObj->GetStringField("status");

			ETaskStatus TaskStatus = ETaskStatus::Error;
			if (Status == "In queue")
			{
				TaskStatus = ETaskStatus::InQueue;
			}
			else if (Status == "Processing")
			{
				TaskStatus = ETaskStatus::Processing;
			}
			else if (Status == "Completed")
			{
				TaskStatus = ETaskStatus::Completed;
			}
			else if (Status == "Failed")
			{
				TaskStatus = ETaskStatus::Failed;
			}
			
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, TaskStatus, TEXT("Get task status successfully"));
			}
		}
		else
		{
			FString Message = UFittingRoomUtils::ParseException(Data);
			if (OnFailure.IsBound())
			{
				OnFailure.Broadcast(Code, ETaskStatus::Error, Message);
			}
		}
	}
	else
	{
		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(404, ETaskStatus::Error, TEXT("Not Found"));
		}
	}

	RemoveFromRoot();
}

