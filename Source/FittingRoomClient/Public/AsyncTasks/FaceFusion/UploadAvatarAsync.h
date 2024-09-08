// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "UploadAvatarAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUploadAvatarHttpDelegate, int32, Code, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UUploadAvatarAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/* 临时函数，在像素流版本中移除
	 * 异步上传头像，请在登录后调用
	 */
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Face Fusion|Avatar", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Upload Avatar"))
	static UUploadAvatarAsync* UploadAvatar(const FString& FilePath);

	// 成功
	UPROPERTY(BlueprintAssignable)
	FUploadAvatarHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FUploadAvatarHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FString& FilePath);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
