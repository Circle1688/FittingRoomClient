// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/FaceFusion/FaceSwapProxy.h"
#include "Utils/FittingRoomUtils.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/Base64.h"


UFaceSwapProxy* UFaceSwapProxy::FaceSwap(const FFaceFusionRequest& Parameters, const TArray<uint8>& InTargetImageData)
{
	UFaceSwapProxy* Node = NewObject<UFaceSwapProxy>();
	Node->RequestData = Parameters;
	Node->TargetImageData = InTargetImageData;
	return Node;
}

void UFaceSwapProxy::Activate()
{
	FString Message;

	if (RequestData.FaceEnhancerBlend < 0 || RequestData.FaceEnhancerBlend > 100)
	{
		Message = TEXT("The face enhancer blend value is out of range 0-100!");

		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(400, "", Message);
		}
		return;
	}
	
	if (TargetImageData.IsEmpty())
	{
		Message = TEXT("The Target Image Data is empty!");

		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(400, "", Message);
		}
		return;
	}
	
	SendRequest();
}

void UFaceSwapProxy::SendRequest()
{
	AddToRoot();

	// 网络请求
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	
	FString RequestUrl = UFittingRoomUtils::GetServerUrl() + TEXT("/face_swap");
	
	// 设置请求
	Request->SetURL(RequestUrl);

	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + UFittingRoomUtils::GetToken());
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	FString Body = MakeRequestBody(RequestData, TargetImageData);
	
	Request->SetContentAsString(Body);

	Request->OnProcessRequestComplete().BindUObject(this, &UFaceSwapProxy::OnHttpResponse);
	Request->ProcessRequest();
}

void UFaceSwapProxy::OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	bool bSuccess = false;
	TArray<uint8> OutputImageData;
	
	if (bWasSuccessful && Response.IsValid())
	{
		FString Data = Response->GetContentAsString();
		int32 Code = Response->GetResponseCode();
	
		if (Code == 200)
		{
			TSharedPtr<FJsonObject> JsonObj = UFittingRoomUtils::GetJsonObject(Data);
			FString TaskId = JsonObj->GetStringField(TEXT("task_id"));
			if (OnSuccess.IsBound())
			{
				OnSuccess.Broadcast(Code, TaskId, TEXT("Start facefusion successfully"));
			}
		}
		else
		{
			FString Message = UFittingRoomUtils::ParseException(Data);
			if (OnFailure.IsBound())
			{
				OnFailure.Broadcast(Code, "", Message);
			}
		}
	}
	else
	{
		if (OnFailure.IsBound())
		{
			OnFailure.Broadcast(404, "", TEXT("Not Found"));
		}
	}

	RemoveFromRoot();
}

FString UFaceSwapProxy::MakeRequestBody(const FFaceFusionRequest& FaceFusionRequest, const TArray<uint8>& InTargetImageData)
{
	TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject);

	// 转换成Base64字符串
	FString Base64_TargetImageData = FBase64::Encode(InTargetImageData);
	Body->SetStringField(TEXT("target_image"), Base64_TargetImageData);

	// 获取参数设置
	Body->SetNumberField(TEXT("face_enhancer_blend"), FaceFusionRequest.FaceEnhancerBlend);

	FString OutJsonData;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJsonData);
	FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);

	return OutJsonData;
}
