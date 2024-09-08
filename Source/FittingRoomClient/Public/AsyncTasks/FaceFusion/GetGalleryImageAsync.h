// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "GetGalleryImageAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGetGalleryImageHttpDelegate, int32, Code, const FString&, Message, float, ProgressPercent, const TArray<uint8>&, BinaryData);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UGetGalleryImageAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 异步下载图库里的图片，请在登录后调用
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Face Fusion|Gallery", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Get Gallery Image"))
	static UGetGalleryImageAsync* GetGalleryImage(const FString& Url);

	// 下载中
	UPROPERTY(BlueprintAssignable)
	FGetGalleryImageHttpDelegate OnProgress;
	
	// 成功
	UPROPERTY(BlueprintAssignable)
	FGetGalleryImageHttpDelegate OnFinish;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FGetGalleryImageHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FString& Url);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 下载进度
	void OnDownloadProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived);
};

