// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "CheckUserExistAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCheckUserHttpDelegate, int32, Code, bool, IsExists, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UCheckUserExistAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 检查用户名是否存在
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Account", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Check User Exists"))
	static UCheckUserExistAsync* CheckUserExists(const FString& UserName);

	// 成功
	UPROPERTY(BlueprintAssignable)
	FCheckUserHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FCheckUserHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FString& UserName);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 构造请求体
	static FString MakeRequestBody(const FString& UserName);

};
