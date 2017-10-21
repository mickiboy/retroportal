#pragma once

#include <string>
#include <libretro.h>
#include <dynamic/dylib.h>
#include "Drawable.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace retro
{
    class Core : public Drawable
    {
    public:
        Core(const std::string& path);
        virtual ~Core();

        Mesh& getMesh() override;
        ShaderProgram& getShaderProgram() override;
        Texture& getTexture() override;

        void loadGame(const std::string& path);

        void unloadCurrentGame();

        void run();

    private:
        static Core* instance;

        static bool onRetroEnvironment(unsigned cmd, void* data);
        static void onRetroVideoRefresh(const void* data, unsigned width, unsigned height, size_t pitch);
        static void onRetroAudioSample(int16_t left, int16_t right);
        static size_t onRetroAudioSampleBatch(const int16_t* data, size_t frames);
        static void onRetroInputPoll();
        static int16_t onRetroInputState(unsigned port, unsigned device, unsigned index, unsigned id);

        Mesh mesh;
        ShaderProgram shaderProgram;
        Texture texture;
        dylib_t handle = nullptr;

        typedef void(*retroSetEnvironmentFn)(retro_environment_t);
        retroSetEnvironmentFn retroSetEnvironment;

        typedef void(*retroSetVideoRefreshFn)(retro_video_refresh_t);
        retroSetVideoRefreshFn retroSetVideoRefresh;

        typedef void(*retroSetAudioSampleFn)(retro_audio_sample_t);
        retroSetAudioSampleFn retroSetAudioSample;

        typedef void(*retroSetAudioSampleBatchFn)(retro_audio_sample_batch_t);
        retroSetAudioSampleBatchFn retroSetAudioSampleBatch;

        typedef void(*retroSetInputPollFn)(retro_input_poll_t);
        retroSetInputPollFn retroSetInputPoll;

        typedef void(*retroSetInputStateFn)(retro_input_state_t);
        retroSetInputStateFn retroSetInputState;

        typedef void(*retroInitFn)();
        retroInitFn retroInit;

        typedef void(*retroDeinitFn)();
        retroDeinitFn retroDeinit;

        typedef unsigned(*retroApiVersionFn)();
        retroApiVersionFn retroApiVersion;

        typedef void(*retroGetSystemInfoFn)(retro_system_info*);
        retroGetSystemInfoFn retroGetSystemInfo;

        typedef void(*retroGetSystemAvInfoFn)(retro_system_av_info*);
        retroGetSystemAvInfoFn retroGetSystemAvInfo;

        typedef void(*retroSetControllerPortDeviceFn)(unsigned, unsigned);
        retroSetControllerPortDeviceFn retroSetControllerPortDevice;

        typedef void(*retroResetFn)();
        retroResetFn retroReset;

        typedef void(*retroRunFn)();
        retroRunFn retroRun;

        typedef size_t(*retroSerializeSizeFn)();
        retroSerializeSizeFn retroSerializeSize;

        typedef bool(*retroSerializeFn)(void*, size_t);
        retroSerializeFn retroSerialize;

        typedef bool(*retroUnserializeFn)(const void*, size_t);
        retroUnserializeFn retroUnserialize;

        typedef void(*retroCheatResetFn)();
        retroCheatResetFn retroCheatReset;

        typedef void(*retroCheatSetFn)(unsigned, bool, const char*);
        retroCheatSetFn retroCheatSet;

        typedef bool(*retroLoadGameFn)(const retro_game_info*);
        retroLoadGameFn retroLoadGame;

        typedef bool(*retroLoadGameSpecialFn)(unsigned, const retro_game_info*, size_t);
        retroLoadGameSpecialFn retroLoadGameSpecial;

        typedef void(*retroUnloadGameFn)();
        retroUnloadGameFn retroUnloadGame;

        typedef unsigned(*retroGetRegionFn)();
        retroGetRegionFn retroGetRegion;

        typedef void*(*retroGetMemoryDataFn)(unsigned);
        retroGetMemoryDataFn retroGetMemoryData;

        typedef size_t(*retroGetMemorySizeFn)(unsigned);
        retroGetMemorySizeFn retroGetMemorySize;
    };
}
