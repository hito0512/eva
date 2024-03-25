# 机体
一款直观的大模型应用软件：机体 (qt5+llama.cpp)

视频介绍 https://www.bilibili.com/video/BV15r421h728/?share_source=copy_web&vd_source=569c126f2f63df7930affe9a2267a8f8

<img src="https://github.com/ylsdamxssjxxdd/eva/assets/63994076/836433f4-1ee4-4cf6-8502-d2c1f938a9a8" width="300px">



## 特点

- 轻量
    - 机体没有其它依赖组件，就是一个exe程序
- win7
    - 最低支持32位windows7
    - 具有编译到(x86，arm，windows，linux，macos，android，cuda，rocm，vulkan)的潜力
- 多功能
    - 本地模型交互，多模态，在线模型交互，对外api服务，智能体，知识库问答，模型量化，文生图，声转文，语音朗读 (全都有就是效果不咋地)
- 直观 
    - 输出区的内容就是模型的全部现实
    - 状态区的内容就是运行的全部流程

## 快速开始
1. 下载一个机体
- https://pan.baidu.com/s/18NOUMjaJIZsV_Z0toOzGBg?pwd=body
2. 下载一个gguf格式模型
- https://pan.baidu.com/s/18NOUMjaJIZsV_Z0toOzGBg?pwd=body
- 也可以前往 https://hf-mirror.com 搜索，支持几乎所有开源大语言模型:千问、零一、猎户、百川、llama、gemma、phi、mamba、bloom、mistral、moe、deepseek、gpt2...
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
- 在输出区键入任意文字，模型对其进行补完，这是机体所有功能实现的基础
3. 服务模式
- 机体成为一个开放api端口的服务，也可以在网页上进行聊天，但是挂载的工具失效
4. 链接状态
- 机体可以链接到其它api服务的对话端点，不需要装载模型也能运行
5. 知识库
- 用户可以上传文档，经过嵌入处理后成为模型的知识库，挂载后可供模型调用

<img src="https://github.com/ylsdamxssjxxdd/eva/assets/63994076/a0b8c4e7-e8dd-4e08-bcb2-2f890d77d632" width="500px">

6. 文生图
- 可以使用sd模型绘制图像，挂载后可供模型调用

<img src="https://github.com/ylsdamxssjxxdd/eva/assets/63994076/627e5cd2-2361-4112-9df4-41b908fb91c7" width="500px">

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
    - 安装cuda-tooklit https://developer.nvidia.com/cuda-toolkit-archive 这也是cuda版本的机体运行时必须的
    - 安装cudnn https://developer.nvidia.com/cudnn

2. 克隆源代码
```bash
git clone https://github.com/ylsdamxssjxxdd/eva.git
```
3. 根据CMakeLists.txt文件中的说明修改相应配置
4. 编译

## 主线
- 装载流程
    - 【ui】->用户点击装载->选择路径->发送设置参数->【bot】->处理参数->发送重载信号->【ui】->预装载->装载中界面状态->发送装载信号->【bot】->开始装载->发送装载动画信号->装载完重置->发送装载完成信号->【ui】->加速装载动画->装载动画结束->滚动动画开始->动画结束->强制解锁->触发发送->发送预解码(只解码不采样输出)指令->【bot】->预解码系统指令->发送解码完毕信号->【ui】->正常界面状态->END
- 发送流程
    - 【ui】->用户点击发送->模式/标签/内容分析->对话模式的话->推理中界面状态->发送输入参数->发送推理信号->【bot】->预处理用户输入->流式循环输出->循环终止->发送推理结束信号->【ui】->正常界面状态->END
- 约定流程
    - 【ui】->用户点击约定->展示最近一次配置->点击确认->记录用户配置->发送约定参数->【bot】->记录用户配置->发送约定重置信号->【ui】->触发界面重置->发送重置信号->【bot】->初始化模型运行所需组件->发送重置完成信号->【ui】->如果系统指令变化则预解码->END
- 设置流程
    - 【ui】->用户点击设置->展示最近一次配置->点击确认->记录用户配置->发送设置参数->【bot】->记录用户配置->分析配置变化->END/发送重载信号/发送设置重置信号->【ui】->预装载/触发界面重置->END
 - 预解码图像流程
    - 【ui】->用户上传图像/按f1截图->触发发送->推理中界面状态->发送预解码图像指令->【bot】->预解码图像->占用1024个token->发送解码完毕信号->【ui】->正常界面状态->END
- 录音转文字流程
    - 【ui】->用户初次按下f2->需要指定whisper模型路径->发送expend界面显示信号->【expend】->弹出声音增殖界面->选择路径->发送whisper模型路径->【ui】->用户再按f2->录音界面状态->开始录音->用户再按f2->结束录音->保存wav文件到本地->发送wav文件路径->【expend】->调用whisper.exe进行解码->解码完毕保存txt结果到本地->发送文字结果->【ui】->正常界面状态->显示到输入区->END   
- 工具调用流程
    - 【ui】->用户点击发送->模式/标签/内容分析->对话模式的情况->推理中界面状态->发送输入参数->发送推理信号->【bot】->预处理用户输入->流式循环输出->循环终止->发送推理结束信号->【ui】->提取模型本次输出中的json字段->发送json字段->发送工具推理信号->【tool】->根据json字段执行相应函数->执行完毕返回结果->【ui】->将返回结果作为发送内容并添加观察前缀->触发发送->···->没有合理的json字段->正常界面状态->END
- 构建知识库流程
    - 【expend】->用户进入知识库选项卡->用户点击选择模型->选择嵌入模型->启动server.exe->启动完成->自动将server的v1/embeddings端点写入地址栏->用户点击上传选择一个txt文本->文本分段->用户可以按需求修改待嵌入文本段内容->用户点击嵌入文本段->将每个文本段发送到端点地址并接收计算后的词向量->表格中显示已嵌入文本段->发送已嵌入文本段数据->【tool】->END
- 知识库问答流程
    - 【ui】->工具调用流程->json字段中包含knowledge关键字->发送json字段->发送工具推理信号->【tool】->执行knowledge函数->向嵌入端点发送查询字段->【server】->返回计算后的词向量->【tool】->计算查询字段词向量和每个已嵌入文本段词向量的余弦相似度->返回三个相似度最高的文本段->【ui】->将返回结果作为发送内容并添加观察前缀->触发发送->···->没有合理的json字段->正常界面状态->END
- 链接流程
    - 【ui】->用户右击装载->配置ip和端点->点击确认->锁定界面->记录配置->连接测试->测试通过->解锁界面->END
    - 链接状态下的其它流程与上面类似，【bot】替换为【net】
    
## 待办事项
- 逐步弃用xbot转为xcore，使用server.exe的/completion端点代替手撸的推理循环，提高系统稳定性
- 适配linux
- 适配国产cpu/gpu
- 英文版本

## 已知BUG
- 模型推理有内存泄漏，定位在xbot.cpp的stream函数，待修复
- 链接模式下，无法无间隔的连续发送，通过定时100ms后触发来缓解，定位在xnet.cpp的QNetworkAccessManager不能及时释放，待修复
- 多模态模型输出异常，需要向llava.cpp对齐，待修复
- csv文件存在特殊符号时不能正确解析，定位在utils.cpp的readCsvFile函数，待修复
---
- 达到最大上下文长度后截断一次后再达到，解码会失败，通过暂时置入空的记忆来缓解，定位在xbot.cpp的llama_decode返回1（找不到kv槽），没修复（实际上是截断后，送入的token数量与保留的部分依旧超过最大上下文长度，需要再截断一次）
- 部分字符utf-8解析有问题，已修复（模型输出不完整的utf8字符，需要手动将3个拼接成1个）
- 切换模型时显存泄露，已修复（使用cuda时，不使用mmp）
- mingw编译的版本装载时无法识别中文路径，定位在llama.cpp的fp = std::fopen(fname, mode);，已修复（利用QTextCodec::codecForName("GB2312")将字符转码）