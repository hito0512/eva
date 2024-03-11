# 机体
一款轻量的大模型应用软件：机体 (qt5+llama.cpp)

![image](https://github.com/ylsdamxssjxxdd/eva/blob/main/utils/ui/ui_demo.png)
![image](:/ui/ui_demo.png)

## 特点
- 轻量
    - 机体没有其它依赖组件，就是一个exe程序
- win7
    - 最低支持32位windows7
    - 具有编译到(x86，arm，windows，linux，macos，android，cuda，rocm，vulkan)的潜力
- 多功能
    - 本地模型交互，视觉，听觉，在线模型交互(待完善)，模型评测，对外api服务，agent(待完善)，RAG(待完善)
- 直观
    - 输出区的内容就是模型的全部现实
    - 状态区的内容就是全部工作流程

## 快速开始
1. 下载一个机体
- https://pan.baidu.com/s/18NOUMjaJIZsV_Z0toOzGBg?pwd=body
2. 下载一个gguf格式模型
- https://pan.baidu.com/s/18NOUMjaJIZsV_Z0toOzGBg?pwd=body
3. 装载！
- 点击装载按钮，选择一个gguf模型载入内存
4. 发送！
- 在输入区输入聊天内容，点击发送

## 功能介绍
1. 对话模式
- 机体的默认模式，在输入区输入聊天内容，模型进行回复
- 可以事先约定好角色
- 可以使用挂载的工具，但是会影响模型智力
- 可以上传csv格式的题库进行测试
- 可以按f1截图，按f2进行录音，截图和录音会发送给多模态或whisper模型进行相应处理
2. 补完模式
- 在输出区输入一段文字，模型对其进行补完
3. 服务模式
- 机体成为一个开放api端口的服务，也可以在网页上进行聊天
4. 链接状态
- 机体利用api服务的端点，不需要装载模型也能运行
5. 知识库
- 用户可以上传文档，经过嵌入处理后成为模型的知识库

## 源码编译
1. 配置环境
- 64bit版本(option选项全部关闭)
    - 我的工具链为mingw81_64+qt5.15.10(静态库)
- 32bit版本(BODY_32BIT选项打开，其它关闭)
    - 我的工具链为mingw81_32+qt5.15.10(静态库)
- opencl版本(CLBLAST选项打开，其它关闭)
    - 我的工具链为mingw81_64+clblast(静态库)+qt5.15.10(静态库) 
    - 下载opencl-sdk，将其include目录添加到环境变量  https://github.com/KhronosGroup/OpenCL-SDK
    - 下载clblast，build_shared_lib选项关闭，静态编译并添加到环境变量 https://github.com/CNugteren/CLBlast   
- cuda版本(CUBLAST选项打开，其它关闭)
    - 我的工具链为msvc2022+qt5.15.10+cuda12
    - 安装cuda-tooklit https://developer.nvidia.com/cuda-toolkit-archive
    - 安装cudnn https://developer.nvidia.com/cudnn

2. 克隆源代码
```bash
git clone --recurse-submodules https://github.com/ylsdamxssjxxdd/eva.git
```
3. 根据需要修改CMakeLists.txt文件中的配置
4. 编译

## 主线
- 装载流程
    - 【ui】->用户点击装载->选择路径->发送设置参数->【bot】->处理参数->发送重载信号->【ui】->预装载->装载中界面状态->发送装载信号->【bot】->开始装载->发送装载动画信号->装载完重置->发送装载完成信号->【ui】->加速装载动画->装载动画结束->滚动动画开始->动画结束->强制解锁->触发发送->发送预解码指令->【bot】->预解码系统指令->发送解码完毕信号->【ui】->正常界面状态->END
- 发送流程
    - 【ui】->用户点击发送->模式/标签/内容分析->对话模式的话->推理中界面状态->发送输入参数->发送推理信号->【bot】->预处理用户输入->流式循环输出->循环终止->发送推理结束信号->【ui】->正常界面状态->END
- 约定流程
    - 【ui】->用户点击约定->展示最近一次配置->点击确认->记录用户配置->发送约定参数->【bot】->记录用户配置->发送约定重置信号->【ui】->触发界面重置->发送重置信号->【bot】->初始化模型运行所需组件->发送重置完成信号->【ui】->如果系统指令变化则预解码->END
- 设置流程
    - 【ui】->用户点击设置->展示最近一次配置->点击确认->记录用户配置->发送设置参数->【bot】->记录用户配置->分析配置变化->END/发送重载信号/发送设置重置信号->【ui】->预装载/触发界面重置->END
- 工具调用流程
    - 【ui】->用户点击发送->模式/标签/内容分析->对话模式的话->推理中界面状态->发送输入参数->发送推理信号->【bot】->预处理用户输入->流式循环输出->循环终止->发送推理结束信号->【ui】->提取模型本次输出中的json字段->发送json字段->发送工具推理信号->【tool】->根据json字段执行相应函数->执行完毕返回结果->【ui】->触发发送->···->没有合理的json字段->正常界面状态->END
- 链接流程
    - 【ui】->用户右击装载->配置ip和端点->点击确认->锁定界面->记录配置->连接测试->测试通过->解锁界面->END
    - 链接状态下的其它流程与上面类似，【bot】替换为【net】

## 待办事项
在扩展窗口增加知识库、以及模型/图像/声音增殖选项
- 知识库
    - 借助server.exe的v1/embeddings端点计算嵌入
- 模型增殖
    - 借助llama.cpp项目进行模型的转化、量化、微调
- 图像增殖
    - 借助stable-diffusion.cpp项目进行文生图
- 声音增殖
    - 借助whisper.cpp项目将声音转文字

## 已知BUG
- 模型推理有内存泄漏，定位在xbot.cpp的stream函数，待修复
- 达到最大上下文后截断一次后再达到，解码会失败，通过暂时置入空的记忆来缓解，定位在xbot.cpp的llama_decode返回1（找不到kv槽），待修复
- 链接模式下，无法无间隔的连续发送，通过定时100ms后触发来缓解，定位在xnet.cpp的QNetworkAccessManager不能及时释放，待修复
- 挂载yi-vl视觉后模型输出异常，待修复
- csv文件存在特殊符号时不能正确解析，定位在utils.cpp的readCsvFile函数待修复
---
- 部分字符utf-8解析有问题，已修复（模型输出不完整的utf8字符，需要手动将3个拼接成1个）
- 切换模型时显存泄露，已修复（使用cuda时，不使用mmp）
- 服务模式点击设置就会先终止server.exe而不是点ok后，已修复（将全局的运行线程变为局部变量）