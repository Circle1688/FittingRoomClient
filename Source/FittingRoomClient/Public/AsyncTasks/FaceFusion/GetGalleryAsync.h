// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "GetGalleryAsync.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGetGalleryHttpDelegate, int32, Code, const TArray<FString>&, GalleryUrls, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UGetGalleryAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 获取图库里的所有图的Url，请在登录后调用
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Face Fusion|Gallery", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Get All Gallery"))
	static UGetGalleryAsync* GetGallery();

	// 成功
	UPROPERTY(BlueprintAssignable)
	FGetGalleryHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FGetGalleryHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest();

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
