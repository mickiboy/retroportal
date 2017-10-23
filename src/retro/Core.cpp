#include <sstream>
#include <retro/Core.h>
#include <retro/Log.h>
#include <retro/ui/Shaders.h>

namespace retro
{
    Core* Core::instance = nullptr;

    const std::string& vertexShaderCode =
        "#version 410 core\n"
        ""
        "layout (location = 0) in vec3 a_pos;"
        "layout (location = 1) in vec4 a_color;"
        "layout (location = 2) in vec2 a_texCoord;"
        ""
        "out vec2 v_texCoord;"
        ""
        "uniform mat4 u_model;"
        "uniform mat4 u_view;"
        "uniform mat4 u_projection;"
        ""
        "void main()"
        "{"
        "    gl_Position = u_projection * u_view * u_model * vec4(a_pos, 1.0);"
        "    v_texCoord = a_texCoord;"
        "}";

    const std::string& fragmentShaderCode =
        "#version 410 core\n"
        ""
        "in vec2 v_texCoord;"
        ""
        "out vec4 f_fragColor;"
        ""
        "uniform sampler2D u_tex;"
        ""
        "void main()"
        "{"
        "    f_fragColor = texture(u_tex, v_texCoord);"
        "}";

    Core::Core(const std::string& path) : shaderProgram(vertexShaderCode, fragmentShaderCode)
    {
        instance = this;

        handle = dylib_load(path.c_str());
        if (!handle) {
            std::ostringstream ss;
            ss << "Core library could not be loaded: " << dylib_error();

            Log::error(ss.str());

            return;
        }

        Log::debug("Loaded core library");

        retroSetEnvironment = reinterpret_cast<retroSetEnvironmentFn>(dylib_proc(handle, "retro_set_environment"));
        retroSetVideoRefresh = reinterpret_cast<retroSetVideoRefreshFn>(dylib_proc(handle, "retro_set_video_refresh"));
        retroSetAudioSample = reinterpret_cast<retroSetAudioSampleFn>(dylib_proc(handle, "retro_set_audio_sample"));
        retroSetAudioSampleBatch = reinterpret_cast<retroSetAudioSampleBatchFn>(dylib_proc(handle, "retro_set_audio_sample_batch"));
        retroSetInputPoll = reinterpret_cast<retroSetInputPollFn>(dylib_proc(handle, "retro_set_input_poll"));
        retroSetInputState = reinterpret_cast<retroSetInputStateFn>(dylib_proc(handle, "retro_set_input_state"));
        retroInit = reinterpret_cast<retroInitFn>(dylib_proc(handle, "retro_init"));
        retroDeinit = reinterpret_cast<retroDeinitFn>(dylib_proc(handle, "retro_deinit"));
        retroApiVersion = reinterpret_cast<retroApiVersionFn>(dylib_proc(handle, "retro_api_version"));
        retroGetSystemInfo = reinterpret_cast<retroGetSystemInfoFn>(dylib_proc(handle, "retro_get_system_info"));
        retroGetSystemAvInfo = reinterpret_cast<retroGetSystemAvInfoFn>(dylib_proc(handle, "retro_get_system_av_info"));
        retroSetControllerPortDevice = reinterpret_cast<retroSetControllerPortDeviceFn>(dylib_proc(handle, "retro_set_controller_port_device"));
        retroReset = reinterpret_cast<retroResetFn>(dylib_proc(handle, "retro_reset"));
        retroRun = reinterpret_cast<retroRunFn>(dylib_proc(handle, "retro_run"));
        retroSerializeSize = reinterpret_cast<retroSerializeSizeFn>(dylib_proc(handle, "retro_serialize_size"));
        retroSerialize = reinterpret_cast<retroSerializeFn>(dylib_proc(handle, "retro_serialize"));
        retroUnserialize = reinterpret_cast<retroUnserializeFn>(dylib_proc(handle, "retro_unserialize"));
        retroCheatReset = reinterpret_cast<retroCheatResetFn>(dylib_proc(handle, "retro_cheat_reset"));
        retroCheatSet = reinterpret_cast<retroCheatSetFn>(dylib_proc(handle, "retro_cheat_set"));
        retroLoadGame = reinterpret_cast<retroLoadGameFn>(dylib_proc(handle, "retro_load_game"));
        retroLoadGameSpecial = reinterpret_cast<retroLoadGameSpecialFn>(dylib_proc(handle, "retro_load_game_special"));
        retroUnloadGame = reinterpret_cast<retroUnloadGameFn>(dylib_proc(handle, "retro_unload_game"));
        retroGetRegion = reinterpret_cast<retroGetRegionFn>(dylib_proc(handle, "retro_get_region"));
        retroGetMemoryData = reinterpret_cast<retroGetMemoryDataFn>(dylib_proc(handle, "retro_get_memory_data"));
        retroGetMemorySize = reinterpret_cast<retroGetMemorySizeFn>(dylib_proc(handle, "retro_get_memory_size"));

        Log::debug("Loaded core functions");

        retroSetEnvironment(onRetroEnvironment);
        retroSetVideoRefresh(onRetroVideoRefresh);
        retroSetAudioSample(onRetroAudioSample);
        retroSetAudioSampleBatch(onRetroAudioSampleBatch);
        retroSetInputPoll(onRetroInputPoll);
        retroSetInputState(onRetroInputState);

        retroInit();
        Log::debug("Initialized core");

        retro_system_info systemInfo;
        retroGetSystemInfo(&systemInfo);

        Log::debug(systemInfo.library_name);
        Log::debug(systemInfo.library_version);
        Log::debug(systemInfo.valid_extensions);
    }

    Core::~Core()
    {
        unloadCurrentGame();

        retroDeinit();
        Log::debug("Deinitialized core");

        dylib_close(handle);
        Log::debug("Closed core library");

        instance = nullptr;
    }

    Mesh& Core::getMesh()
    {
        return mesh;
    }

    ShaderProgram& Core::getShaderProgram()
    {
        return shaderProgram;
    }

    Texture& Core::getTexture()
    {
        return texture;
    }

    void Core::loadGame(const std::string& path)
    {
        retro_game_info info = {
            path.c_str(),
            nullptr,
            0,
            nullptr
        };

        if (!retroLoadGame(&info)) {
            Log::error("Loading the game failed");
        }

        Log::debug("Loaded game");

        retro_system_av_info avInfo;
        retroGetSystemAvInfo(&avInfo);

        std::ostringstream resolution;
        resolution << "Resolution: " << std::to_string(avInfo.geometry.base_width) << 'x' << std::to_string(avInfo.geometry.base_height);
        Log::debug(resolution.str());

        std::ostringstream fps;
        fps << "FPS: " << std::to_string(avInfo.timing.fps);
        Log::debug(fps.str());

        std::ostringstream sampleRate;
        sampleRate << "Sample rate: " << std::to_string(avInfo.timing.sample_rate);
        Log::debug(sampleRate.str());

        Vertex topLeft = { {}, {}, {} };
        Vertex topRight = { { static_cast<float>(avInfo.geometry.base_width), 0.0f, 0.0f }, {}, { 1.0f, 0.0f } };
        Vertex bottomRight = { { static_cast<float>(avInfo.geometry.base_width), static_cast<float>(avInfo.geometry.base_height), 0.0f }, {}, { 1.0f, 1.0f } };
        Vertex bottomLeft = { { 0.0f, static_cast<float>(avInfo.geometry.base_height), 0.0f }, {}, { 0.0f, 1.0f } };

        mesh.addVertex(topLeft);
        mesh.addVertex(topRight);
        mesh.addVertex(bottomRight);
        mesh.addVertex(bottomLeft);

        mesh.addIndex(0);
        mesh.addIndex(1);
        mesh.addIndex(2);
        mesh.addIndex(0);
        mesh.addIndex(2);
        mesh.addIndex(3);

        mesh.build();

        texture.init(avInfo.geometry.base_width, avInfo.geometry.base_height);
    }

    void Core::unloadCurrentGame()
    {
        retroUnloadGame();
        Log::debug("Unloaded current game");
    }

    void Core::run()
    {
        retroRun();
    }

    bool Core::onRetroEnvironment(unsigned cmd, void* data)
    {
        switch (cmd) {
            case RETRO_ENVIRONMENT_SET_PIXEL_FORMAT:
                instance->texture.setPixelFormat(*reinterpret_cast<retro_pixel_format*>(data));
                return true;

            default:
                return false;
        }
    }

    void Core::onRetroVideoRefresh(const void* data, unsigned width, unsigned height, size_t pitch)
    {
        instance->texture.update(data, width, height, pitch);
    }

    void Core::onRetroAudioSample(int16_t left, int16_t right)
    {
    }

    size_t Core::onRetroAudioSampleBatch(const int16_t* data, size_t frames)
    {
        return 0;
    }

    void Core::onRetroInputPoll()
    {
    }

    int16_t Core::onRetroInputState(unsigned port, unsigned device, unsigned index, unsigned id)
    {
        return 0;
    }
}
