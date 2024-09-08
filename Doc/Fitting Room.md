# Fitting Room
## Account
### Check User Exists

**所属类：UCheckUserExistAsync**

检查用户名是否存在



静态节点

**蓝图异步节点**



 - **输入**

| 命名     | 类型    | 描述           |
| -------- | ------- | -------------- |
| UserName | FString | 要检查的用户名 |


 - **输出**

| 命名      | 类型                   | 描述                         |
| --------- | ---------------------- | ---------------------------- |
| OnSuccess | FCheckUserHttpDelegate | 当用户名检查成功时触发的事件 |
| OnFailure | FCheckUserHttpDelegate | 当用户名检查失败时触发的事件 |


 - **委托输出**

| 命名     | 类型           | 描述           |
| -------- | -------------- | -------------- |
| Code     | int32          | 响应码         |
| IsExists | bool           | 用户名是否存在 |
| Message  | const FString& | 响应消息       |





### User Login

**所属类：ULoginAsync**

用户登录



静态节点

**蓝图异步节点**



 - **输入**

| 命名     | 类型    | 描述   |
| -------- | ------- | ------ |
| UserName | FString | 用户名 |
| Password | FString | 密码   |


 - **输出**

| 命名      | 类型               | 描述           |
| --------- | ------------------ | -------------- |
| OnSuccess | FLoginHttpDelegate | 登录成功时触发 |
| OnFailure | FLoginHttpDelegate | 登录失败时触发 |


 - **委托输出**

| 命名    | 类型    | 描述     |
| ------- | ------- | -------- |
| Code    | int32   | 返回码   |
| Message | FString | 返回消息 |





### Change Password

**所属类：UModifyPasswordAsync**

修改密码，请在登录后调用



静态节点

**蓝图异步节点**



 - **输入**

| 命名        | 类型    | 描述   |
| ----------- | ------- | ------ |
| OldPassword | FString | 旧密码 |
| NewPassword | FString | 新密码 |


 - **输出**

| 命名      | 类型                        | 描述             |
| --------- | --------------------------- | ---------------- |
| OnSuccess | FModifyPasswordHttpDelegate | 成功时调用的委托 |
| OnFailure | FModifyPasswordHttpDelegate | 失败时调用的委托 |


 - **委托输出**

| 命名    | 类型    | 描述     |
| ------- | ------- | -------- |
| Code    | int32   | 响应码   |
| Message | FString | 响应消息 |





### Register user

**所属类：URegisterAsync**

用户注册



静态节点

**蓝图异步节点**



 - **输入**

| 命名     | 类型    | 描述   |
| -------- | ------- | ------ |
| UserName | FString | 用户名 |
| Password | FString | 密码   |
| Mobile   | FString | 手机号 |


 - **输出**

| 命名      | 类型          | 描述           |
| --------- | ------------- | -------------- |
| OnSuccess | FHttpDelegate | 注册成功时触发 |
| OnFailure | FHttpDelegate | 注册失败时触发 |


 - **委托输出**

| 命名    | 类型    | 描述     |
| ------- | ------- | -------- |
| Code    | int32   | 响应码   |
| Message | FString | 响应消息 |





### Reset Password

**所属类：UResetPasswordAsync**

通过用户名和手机号重置密码



静态节点

**蓝图异步节点**



 - **输入**

| 命名        | 类型    | 描述   |
| ----------- | ------- | ------ |
| UserName    | FString | 用户名 |
| NewPassword | FString | 新密码 |
| Mobile      | FString | 手机号 |


 - **输出**

| 命名      | 类型                       | 描述             |
| --------- | -------------------------- | ---------------- |
| OnSuccess | FResetPasswordHttpDelegate | 成功时调用的委托 |
| OnFailure | FResetPasswordHttpDelegate | 失败时调用的委托 |


 - **委托输出**

| 命名    | 类型    | 描述         |
| ------- | ------- | ------------ |
| Code    | int32   | 返回的状态码 |
| Message | FString | 返回的消息   |





### User Logout

**所属类：UFittingRoomUtils**

退出登录，在切换用户之前一定要记得登出



静态节点






## Body Shape
### Get All Body Shape

**所属类：UGetBodyShapeAsync**

获取身材数据，返回Map，请在登录后调用



静态节点

**蓝图异步节点**



 - **输出**

| 命名      | 类型                      | 描述             |
| --------- | ------------------------- | ---------------- |
| OnSuccess | FGetBodyShapeHttpDelegate | 成功时调用的委托 |
| OnFailure | FGetBodyShapeHttpDelegate | 失败时调用的委托 |


 - **委托输出**

| 命名       | 类型                 | 描述              |
| ---------- | -------------------- | ----------------- |
| Code       | int32                | 返回的状态码      |
| BodyShapes | FBodyShapeMapWrapper | 包含身材数据的Map |
| Message    | FString              | 返回的消息        |





### Update Body Shape

**所属类：UUpdateBodyShapeAsync**

更新身材数据，请在登录后调用



静态节点

**蓝图异步节点**



 - **输入**

| 命名      | 类型    | 描述     |
| --------- | ------- | -------- |
| FieldName | FString | 字段名称 |
| Value     | float   | 数值     |


 - **输出**

| 命名      | 类型                         | 描述         |
| --------- | ---------------------------- | ------------ |
| OnSuccess | FUpdateBodyShapeHttpDelegate | 成功时的回调 |
| OnFailure | FUpdateBodyShapeHttpDelegate | 失败时的回调 |


 - **委托输出**

| 命名    | 类型    | 描述         |
| ------- | ------- | ------------ |
| Code    | int32   | 返回的状态码 |
| Message | FString | 返回的消息   |





## Clothes
### Get Clothes Preview

**所属类：UGetClothesPreviewAsync**

异步下载衣服数据库里的预览图



静态节点

**蓝图异步节点**



 - **输入**

| 命名 | 类型    | 描述                    |
| ---- | ------- | ----------------------- |
| Url  | FString | 要下载的预览图的URL地址 |


 - **委托输出**

| 命名       | 类型                           | 描述         |
| ---------- | ------------------------------ | ------------ |
| OnProgress | FGetClothesPreviewHttpDelegate | 下载进度事件 |
| OnFinish   | FGetClothesPreviewHttpDelegate | 下载完成事件 |
| OnFailure  | FGetClothesPreviewHttpDelegate | 下载失败事件 |





### Search Clothes

**所属类：USearchClothesAsync**

多关键词搜索衣服数据库



静态节点

**蓝图异步节点**



 - **输入**

| 命名     | 类型    | 描述       |
| -------- | ------- | ---------- |
| Keywords | FString | 搜索关键词 |


 - **输出**

| 命名      | 类型                       | 描述                 |
| --------- | -------------------------- | -------------------- |
| OnSuccess | FSearchClothesHttpDelegate | 搜索成功时触发的委托 |
| OnFailure | FSearchClothesHttpDelegate | 搜索失败时触发的委托 |


 - **委托输出**

| 命名    | 类型                        | 描述         |
| ------- | --------------------------- | ------------ |
| Code    | int32                       | HTTP响应码   |
| Results | TArray<FClothesInfoStruct>& | 搜索结果数组 |
| Message | FString                     | 响应消息     |





## Face Fusion
### Face Fusion

**所属类：UFaceSwapProxy**

换脸服务，输入字节数组为原始图像二进制数据，请勿使用Texture2D转换的字节数组。



静态节点

**蓝图异步节点**



 - **输入**

| 命名              | 类型               | 描述                                   |
| ----------------- | ------------------ | -------------------------------------- |
| Parameters        | FFaceFusionRequest | 增强部分与之前的面部混合指数的请求参数 |
| InTargetImageData | TArray<uint8>      | 输入的目标图像二进制数据               |


 - **输出**

| 命名      | 类型              | 描述                 |
| --------- | ----------------- | -------------------- |
| OnSuccess | FGenImageDelegate | 生成成功时触发的事件 |
| OnFailure | FGenImageDelegate | 失败时触发的事件     |


 - **委托输出**

| 命名    | 类型           | 描述       |
| ------- | -------------- | ---------- |
| Code    | int32          | 状态码     |
| TaskId  | const FString& | 任务id     |
| Message | const FString& | 返回的消息 |





### Get Task Status

**所属类：UGetTaskStatusAsync**

获取任务状态，完成之后可以直接用任务id下载图片



静态节点

**蓝图异步节点**



 - **输入**

| 命名   | 类型    | 描述   |
| ------ | ------- | ------ |
| TaskId | FString | 任务ID |


 - **输出**

| 命名      | 类型                       | 描述             |
| --------- | -------------------------- | ---------------- |
| OnSuccess | FGetTaskStatusHttpDelegate | 成功时调用的委托 |
| OnFailure | FGetTaskStatusHttpDelegate | 失败时调用的委托 |


 - **委托输出**

| 命名       | 类型        | 描述         |
| ---------- | ----------- | ------------ |
| Code       | int32       | 返回的状态码 |
| TaskStatus | ETaskStatus | 任务状态     |
| Message    | FString     | 返回的消息   |





### Avatar
#### Get Avatar

**所属类：UGetAvatarAsync**

异步下载头像，请在登录后调用



静态节点

**蓝图异步节点**



 - **输出**

| 命名       | 类型                   | 描述   |
| ---------- | ---------------------- | ------ |
| OnProgress | FGetAvatarHttpDelegate | 下载中 |
| OnFinish   | FGetAvatarHttpDelegate | 成功   |
| OnFailure  | FGetAvatarHttpDelegate | 失败   |


 - **委托输出**

| 命名            | 类型                 | 描述       |
| --------------- | -------------------- | ---------- |
| Code            | int32                | 返回码     |
| Message         | const FString&       | 消息       |
| ProgressPercent | float                | 进度百分比 |
| BinaryData      | const TArray<uint8>& | 二进制数据 |





#### Upload Avatar

**所属类：UUploadAvatarAsync**

异步上传头像，请在登录后调用



静态节点

**蓝图异步节点**



 - **输入**

| 命名     | 类型    | 描述           |
| -------- | ------- | -------------- |
| FilePath | FString | 头像文件的路径 |


 - **输出**

| 命名      | 类型                      | 描述           |
| --------- | ------------------------- | -------------- |
| OnSuccess | FUploadAvatarHttpDelegate | 上传成功时触发 |
| OnFailure | FUploadAvatarHttpDelegate | 上传失败时触发 |


 - **委托输出**

| 命名    | 类型    | 描述       |
| ------- | ------- | ---------- |
| Code    | int32   | HTTP响应码 |
| Message | FString | 响应消息   |





### Gallery
#### Get All Gallery

**所属类：UGetGalleryAsync**

获取图库里的所有图的Url，请在登录后调用



静态节点

**蓝图异步节点**



 - **输出**

| 命名      | 类型                    | 描述             |
| --------- | ----------------------- | ---------------- |
| OnSuccess | FGetGalleryHttpDelegate | 成功时触发的事件 |
| OnFailure | FGetGalleryHttpDelegate | 失败时触发的事件 |


 - **委托输出**

| 命名        | 类型             | 描述              |
| ----------- | ---------------- | ----------------- |
| Code        | int32            | 返回的状态码      |
| GalleryUrls | TArray<FString>& | 返回的图库URL数组 |
| Message     | FString          | 返回的消息        |





#### Get Gallery Image

**所属类：UGetGalleryImageAsync**

异步下载图库里的图片，请在登录后调用



静态节点

**蓝图异步节点**



 - **输入**

| 命名 | 类型    | 描述          |
| ---- | ------- | ------------- |
| Url  | FString | 图片的URL地址 |


 - **输出**

| 命名       | 类型                         | 描述                               |
| ---------- | ---------------------------- | ---------------------------------- |
| OnProgress | FGetGalleryImageHttpDelegate | 下载中的回调，包含下载进度         |
| OnFinish   | FGetGalleryImageHttpDelegate | 下载成功的回调，包含下载的图片数据 |
| OnFailure  | FGetGalleryImageHttpDelegate | 下载失败的回调，包含错误信息       |


 - **委托输出**

| 命名            | 类型          | 描述           |
| --------------- | ------------- | -------------- |
| Code            | int32         | 返回的状态码   |
| Message         | FString       | 返回的消息     |
| ProgressPercent | float         | 下载进度百分比 |
| BinaryData      | TArray<uint8> | 下载的图片数据 |





#### Remove Gallery Image

**所属类：URemoveGalleryImageAsync**

异步删除图库里的图像，请在登录后调用



静态节点

**蓝图异步节点**



 - **输入**

| 命名 | 类型    | 描述                  |
| ---- | ------- | --------------------- |
| Url  | FString | 要删除的图像的URL地址 |


 - **输出**

| 命名      | 类型                            | 描述                       |
| --------- | ------------------------------- | -------------------------- |
| OnSuccess | FRemoveGalleryImageHttpDelegate | 当删除操作成功时触发的事件 |
| OnFailure | FRemoveGalleryImageHttpDelegate | 当删除操作失败时触发的事件 |


 - **委托输出**

| 命名    | 类型    | 描述           |
| ------- | ------- | -------------- |
| Code    | int32   | HTTP响应状态码 |
| Message | FString | HTTP响应消息   |





## Utils
### Capture
#### Async Capture Texture2D

**所属类：UCaptureTexture2D**

运行时截图，不捕获UI



静态节点

**蓝图异步节点**



 - **输入**

| 命名               | 类型     | 描述           |
| ------------------ | -------- | -------------- |
| WorldContextObject | UObject* | 世界上下文对象 |
| bCaptureUI         | bool     | 是否捕获UI     |


 - **输出**

| 命名      | 类型                   | 描述                 |
| --------- | ---------------------- | -------------------- |
| OnSuccess | FCreateTextureDelegate | 截图成功时触发的事件 |
| OnFail    | FCreateTextureDelegate | 截图失败时触发的事件 |


 - **委托输出**

| 命名           | 类型           | 描述                 |
| -------------- | -------------- | -------------------- |
| OutTexture     | UTexture2D*    | 输出的纹理对象       |
| OutBinaryImage | TArray<uint8>& | 输出的二进制图像数据 |





### File
#### SaveBytesToFile

**所属类：UFaceSwapUtilsBPLibrary**

保存二进制数据到本地硬盘路径



静态节点



 - **输入**

| 命名       | 类型          | 描述       |
| ---------- | ------------- | ---------- |
| FilePath   | FString       | 文件路径   |
| InFileData | TArray<uint8> | 二进制数据 |


 - **输出**

| 命名     | 类型 | 描述         |
| -------- | ---- | ------------ |
| bSuccess | bool | 保存是否成功 |





#### LoadFileToBytes

**所属类：UFaceSwapUtilsBPLibrary**

从文件路径读取二进制数据



静态节点



 - **输入**

| 命名     | 类型    | 描述     |
| -------- | ------- | -------- |
| FilePath | FString | 文件路径 |


 - **输出**

| 命名     | 类型          | 描述             |
| -------- | ------------- | ---------------- |
| bSuccess | bool          | 读取是否成功     |
| OutData  | TArray<uint8> | 读取的二进制数据 |





### Convert
#### BinaryImageToTexture2D

**所属类：UFaceSwapUtilsBPLibrary**

读取图像二进制数据到Texture2D



静态节点



 - **输入**

| 命名        | 类型          | 描述             |
| ----------- | ------------- | ---------------- |
| BinaryImage | TArray<uint8> | 图像的二进制数据 |


 - **输出**

| 命名        | 类型        | 描述              |
| ----------- | ----------- | ----------------- |
| texture_out | UTexture2D* | 转换后的Texture2D |





#### Base64_StringToBytes

**所属类：UFaceSwapUtilsBPLibrary**

转换Base64字符串到二进制



静态节点



 - **输入**

| 命名          | 类型    | 描述               |
| ------------- | ------- | ------------------ |
| Base64_String | FString | Base64编码的字符串 |


 - **输出**

| 命名     | 类型          | 描述               |
| -------- | ------------- | ------------------ |
| OutBytes | TArray<uint8> | 转换后的二进制数据 |





### File Dialog
#### OpenImageFileDialog

**所属类：UFileDialogHelper**

打开图像文件选择对话框，支持常见图像格式，*.png *.jpg *.jpeg *.bmp



静态节点



 - **输入**

| 命名        | 类型     | 描述         |
| ----------- | -------- | ------------ |
| DefaultPath | FString  | 默认路径     |
| FilePath    | FString& | 文件路径引用 |


 - **输出**

| 命名        | 类型 | 描述                   |
| ----------- | ---- | ---------------------- |
| ReturnValue | bool | 是否成功打开文件对话框 |





#### SaveImageFileDialog

**所属类：UFileDialogHelper**

保存PNG图像文件对话框



静态节点



 - **输入**

| 命名            | 类型     | 描述         |
| --------------- | -------- | ------------ |
| DefaultPath     | FString  | 默认路径     |
| DefaultFileName | FString  | 默认文件名   |
| FilePath        | FString& | 文件路径引用 |


 - **输出**

| 命名        | 类型 | 描述             |
| ----------- | ---- | ---------------- |
| ReturnValue | bool | 是否成功保存文件 |





## Pixel Stream
### Pixel Stream Upload Avatar

**所属类：UFittingRoomUtils**

上传头像时，发送到像素流前端，注意一定要登录之后才能用



静态节点



 - **输出**

| 命名   | 类型    | 描述                                         |
| ------ | ------- | -------------------------------------------- |
| Return | FString | 返回的字符串，具体内容取决于像素流前端的响应 |





### Pixel Stream Save Gallery Image

**所属类：UFittingRoomUtils**

保存生成的图时，发送到像素流前端，注意一定要登录之后才能用



静态节点



 - **输入**

| 命名 | 类型    | 描述                |
| ---- | ------- | ------------------- |
| Url  | FString | 图库中对应的图的url |


 - **输出**

| 命名   | 类型    | 描述                                         |
| ------ | ------- | -------------------------------------------- |
| Return | FString | 返回的字符串，具体内容取决于像素流前端的响应 |





### Parse Pixel Stream Response

**所属类：UFittingRoomUtils**

解析像素流前端发过来的信息，在像素流前端完成上传或保存时调用



静态节点



 - **输入**

| 命名       | 类型    | 描述     |
| ---------- | ------- | -------- |
| Descriptor | FString | 描述信息 |


 - **输出**

| 命名    | 类型              | 描述                       |
| ------- | ----------------- | -------------------------- |
| Result  | EUICommandNodePin | 返回的枚举值，代表操作结果 |
| Success | bool              | 操作是否成功               |
| Code    | int32             | 返回的状态码               |
| Message | FString           | 返回的消息                 |