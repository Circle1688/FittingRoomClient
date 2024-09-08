// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "GetClothesPreviewAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGetClothesPreviewHttpDelegate, int32, Code, const FString&, Message, float, ProgressPercent, const TArray<uint8>&, BinaryData);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UGetClothesPreviewAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 异步下载衣服数据库里的预览图
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Clothes", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Get Clothes Preview"))
	static UGetClothesPreviewAsync* GetClothesPreview(const FString& Url);

	// 下载中
	UPROPERTY(BlueprintAssignable)
	FGetClothesPreviewHttpDelegate OnProgress;
	
	// 成功
	UPROPERTY(BlueprintAssignable)
	FGetClothesPreviewHttpDelegate OnFinish;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FGetClothesPreviewHttpDelegate OnFailure;

	virtual void Activate() override;

private:
	FString Url;
	FString FilePath;
	
private:
	
	// 发送数据
	void SendRequest();

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 下载进度
	void OnDownloadProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived);
};

