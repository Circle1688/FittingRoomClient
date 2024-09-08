// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "RemoveGalleryImageAsync.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRemoveGalleryImageHttpDelegate, int32, Code, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API URemoveGalleryImageAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 异步删除图库里的图像，请在登录后调用
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Face Fusion|Gallery", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Remove Gallery Image"))
	static URemoveGalleryImageAsync* RemoveGalleryImage(const FString& Url);

	// 成功
	UPROPERTY(BlueprintAssignable)
	FRemoveGalleryImageHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FRemoveGalleryImageHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FString& Url);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
