// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "GetAvatarAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGetAvatarHttpDelegate, int32, Code, const FString&, Message, float, ProgressPercent, const TArray<uint8>&, BinaryData);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UGetAvatarAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 异步下载头像，请在登录后调用
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Face Fusion|Avatar", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Get Avatar"))
	static UGetAvatarAsync* GetAvatar();

	// 下载中
	UPROPERTY(BlueprintAssignable)
	FGetAvatarHttpDelegate OnProgress;
	
	// 成功
	UPROPERTY(BlueprintAssignable)
	FGetAvatarHttpDelegate OnFinish;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FGetAvatarHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest();

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 下载进度
	void OnDownloadProgress(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived);
};

