// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FaceSwapUtilsBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FITTINGROOMCLIENT_API UFaceSwapUtilsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*
	 * 保存二进制数据到本地硬盘路径
	 */
	UFUNCTION(BlueprintCallable,Category="Fitting Room|Utils|File")
	static bool SaveBytesToFile(const FString& FilePath,const TArray<uint8>& InFileData);

	/*
	 * 从文件路径读取二进制数据
	 */
	UFUNCTION(BlueprintCallable,Category="Fitting Room|Utils|File")
	static void LoadFileToBytes(const FString& FilePath, bool& bSuccess, TArray<uint8>& OutData);

	/*
	 * 读取图像二进制数据到Texture2D
	 */
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Utils|Convert")
	static void BinaryImageToTexture2D(TArray<uint8> BinaryImage, UPARAM(DisplayName = "Texture2D") UTexture2D*& texture_out);

	/*
	 * 转换Base64字符串到二进制
	 */
	UFUNCTION(BlueprintCallable, Category = "Fitting Room|Utils|Convert")
	static bool Base64_StringToBytes(const FString& Base64_String, TArray<uint8>& OutBytes);
	
};
