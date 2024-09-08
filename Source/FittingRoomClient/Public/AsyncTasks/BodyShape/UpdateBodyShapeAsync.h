// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "UpdateBodyShapeAsync.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateBodyShapeHttpDelegate, int32, Code, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UUpdateBodyShapeAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 更新身材数据，请在登录后调用
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Body Shape", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Update Body Shape"))
	static UUpdateBodyShapeAsync* UpdateBodyShape(const FString& FieldName, float Value);

	// 成功
	UPROPERTY(BlueprintAssignable)
	FUpdateBodyShapeHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FUpdateBodyShapeHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FString& FieldName, float Value);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 构造请求体
	static FString MakeRequestBody(const FString& FieldName, float Value);
};
