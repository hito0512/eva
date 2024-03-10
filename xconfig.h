#ifndef XCONFIG_H
#define XCONFIG_H

#include <QDebug>

//约定
#define DEFAULT_PROMPT "You are a helpful assistant."
#define DEFAULT_PREFIX "User"
#define DEFAULT_SUFFIX "Assistant"
//采样
#define DEFAULT_NPREDICT 2048
#define DEFAULT_TEMP 0.5
#define DEFAULT_REPEAT 1.2
//推理
#ifdef BODY_USE_32BIT
    #define DEFAULT_NCTX 256
    #define DEFAULT_BATCH 32
#else
    #define DEFAULT_NCTX 2048
    #define DEFAULT_BATCH 256
#endif    

#define DEFAULT_NTHREAD 1
#define DEFAULT_NGL 0
//模型
#define DEFAULT_MODELPATH "D:/soul/qwen-1.8b-q4_0.gguf"


//约定内容
struct DATES{
    QString system_prompt;
    QString input_pfx;
    QString input_sfx;
    bool is_load_tool;
    QStringList extra_stop_words;//额外停止标志
};

//设置参数
struct SETTINGS{
    float temp = DEFAULT_TEMP;
    double repeat = DEFAULT_REPEAT;
    int npredict = DEFAULT_NPREDICT;

    int ngl = DEFAULT_NGL;
    int nctx = DEFAULT_NCTX;
    int batch = DEFAULT_BATCH;
    int nthread = DEFAULT_NTHREAD;

    QString modelpath = "";
    QString lorapath = "";
    QString mmprojpath = "";

    bool complete_mode = false;
};

//模型参数,模型装载后发送给ui的参数
struct PARAMS{
    int n_ctx_train;//最大值
};

//api配置参数
struct APIS{
    QString api_ip = "";
    QString api_port = "8080";
    QString api_chat_endpoint = "/v1/chat/completions";
    QString api_complete_endpoint = "/completion";
    bool is_cache = false;
};

//端点接收参数
struct ENDPOINT_DATA{
    QString date_prompt;
    QString input_pfx;
    QString input_sfx;
    QString input_prompt;//续写模式用
    QStringList user_history;//对话模式用
    QStringList assistant_history;//对话模式用
    bool complete_mode;
    float temp;
    double repeat;
    int n_predict;
    QStringList stopwords;//停止标志
};

//单参数工具
struct TOOLS{
    QString tool_name;//工具名
    QString func_name;//函数名
    QString func_describe_zh;//功能描述中
    QString func_describe_en;//功能描述英
};

//传递的前缀/输入/后缀
struct INPUTS{
    QString input_prefix;
    QString input;
    QString input_suffix;
};

//状态区信号枚举
enum STATE {
        USUAL_,//一般输出，黑色
        SIGNAL_,//信号，蓝色
        SUCCESS_,//成功，绿色
        WRONG_,//错误，红色
        EVA_,//机体，紫色
        TOOL_,//工具，橘色
};
//模式枚举
enum MODE {
    CHAT_,//对话模式
    COMPLETE_,//补完模式
    SERVER_,//服务模式
    LINK_,//链接模式
};

//音频采样相关
struct WAVHEADER
{
    // RIFF 头
    char RiffName[4];
    unsigned long nRiffLength;
    // 数据类型标识符
    char WavName[4];
    // 格式块中的块头
    char FmtName[4];
    unsigned long nFmtLength;
    // 格式块中的块数据
    unsigned short nAudioFormat;
    unsigned short nChannleNumber;
    unsigned long nSampleRate;
    unsigned long nBytesPerSecond;
    unsigned short nBytesPerSample;
    unsigned short nBitsPerSample;
    // 数据块中的块头
    char    DATANAME[4];
    unsigned long   nDataLength;
};

//whisper.exe可以传入的参数
struct Whisper_Params {
    int32_t n_threads    = 1;
    int32_t n_processors =  1;
    int32_t offset_t_ms  =  0;
    int32_t offset_n     =  0;
    int32_t duration_ms  =  0;
    int32_t progress_step =  5;
    int32_t max_context  = -1;
    int32_t max_len      =  0;
    //int32_t best_of      = whisper_full_default_params(WHISPER_SAMPLING_GREEDY).greedy.best_of;
    //int32_t beam_size    = whisper_full_default_params(WHISPER_SAMPLING_BEAM_SEARCH).beam_search.beam_size;
    int32_t audio_ctx   = 0;

    float word_thold    =  0.01f;
    float entropy_thold =  2.40f;
    float logprob_thold = -1.00f;

    bool speed_up        = false;
    bool debug_mode      = false;
    bool translate       = false;
    bool detect_language = false;
    bool diarize         = false;
    bool tinydiarize     = false;
    bool split_on_word   = false;
    bool no_fallback     = false;
    bool output_txt      = false;
    bool output_vtt      = false;
    bool output_srt      = false;
    bool output_wts      = false;
    bool output_csv      = false;
    bool output_jsn      = false;
    bool output_jsn_full = false;
    bool output_lrc      = false;
    bool no_prints       = false;
    bool print_special   = false;
    bool print_colors    = false;
    bool print_progress  = false;
    bool no_timestamps   = false;
    bool log_score       = false;
    bool use_gpu         = true;

    std::string language  = "zh";
    std::string prompt;
    std::string font_path = "/System/Library/Fonts/Supplemental/Courier New Bold.ttf";
    std::string model     = "D:/soul/whisper-base-q5_1.bin";

    // [TDRZ] speaker turn string
    std::string tdrz_speaker_turn = " [SPEAKER_TURN]"; // TODO: set from command line

    std::string openvino_encode_device = "CPU";

    std::vector<std::string> fname_inp = {};
    std::vector<std::string> fname_out = {};
};

//extern QMap<QString, DATE_> date_map;//extern定义后可以多个.cpp访问



#endif
