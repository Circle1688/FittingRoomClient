// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Http.h"
#include "FaceSwapProxy.generated.h"

/*
 * FaceFusion服务的请求结构体
 */
USTRUCT(BlueprintType)
struct FFaceFusionRequest
{
	GENERATED_BODY()

	/*增强部分与之前的面部混合指数*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Face Fusion Parameters")
	int32 FaceEnhancerBlend = 80;
};


// 字节数组为图像二进制数据，可以直接保存到本地或是通过网络传输
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGenImageDelegate, int32, Code, const FString&, TaskId, const FString&, Message);

/**
 * 换脸服务，输入一个头像和目标图像，即可进行换脸
 */
UCLASS()
class FITTINGROOMCLIENT_API UFaceSwapProxy : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	/*
	 * 换脸服务
	 * 输入字节数组为原始图像二进制数据，请勿使用Texture2D转换的字节数组
	 * 
	 * InTargetImageData: 输入的目标图像二进制数据
	 * 
	 * return: 任务id
	 *
	 * 状态码:
	 * 200 请求成功
	 * 201 请求已创建
	 * 204 无法解析服务器发回的内容
	 * 400 请求参数错误，服务器拒绝处理
	 * 404 无法找到服务器
	 * 500 服务器内部错误，无法完成请求
	 * 502 作为网关或代理角色的服务器，从上游服务器中接收到的响应是无效的，一般是开了vpn
	 * 其他状态码查看网络上的资料
	 */
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Face Fusion", meta = (BlueprintInternalUseOnly = "true", DisplayName = "Face Fusion"))
	static UFaceSwapProxy* FaceSwap(const FFaceFusionRequest& Parameters, const TArray<uint8>& InTargetImageData);

	// 生成成功
	UPROPERTY(BlueprintAssignable)
	FGenImageDelegate OnSuccess;

	// 失败
	UPROPERTY(BlueprintAssignable)
	FGenImageDelegate OnFailure;

	virtual void Activate() override;

private:
	FFaceFusionRequest RequestData;
	TArray<uint8> TargetImageData;

private:
	
	// 发送数据
	void SendRequest();
	
	// 请求响应
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// 构造请求体
	static FString MakeRequestBody(const FFaceFusionRequest& FaceFusionRequest, const TArray<uint8>& InTargetImageData);
};
