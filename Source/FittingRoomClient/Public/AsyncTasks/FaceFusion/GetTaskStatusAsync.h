// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "GetTaskStatusAsync.generated.h"

UENUM(BlueprintType)
enum class ETaskStatus:uint8
{
	InQueue			UMETA(DisplayName = "In queue"),
	Processing		UMETA(DisplayName = "Processing"),
	Completed		UMETA(DisplayName = "Completed"),
	Failed			UMETA(DisplayName = "Failed"),
	Error			UMETA(DisplayName = "Error")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGetTaskStatusHttpDelegate, int32, Code, const ETaskStatus&, TaskStatus, const FString&, Message);

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UGetTaskStatusAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	// 获取任务状态，完成之后可以直接用任务id下载图片
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Face Fusion", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Get Task Status"))
	static UGetTaskStatusAsync* GetTaskStatus(const FString& TaskId);

	// 成功
	UPROPERTY(BlueprintAssignable)
	FGetTaskStatusHttpDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FGetTaskStatusHttpDelegate OnFailure;

private:
	// 发送数据
	void SendRequest(const FString& TaskId);

	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
