#include <retro/Application.h>
#include <retro/Core.h>
#include <retro/Log.h>
#include <retro/Renderer.h>

int main(int argc, char* argv[])
{
    retro::Log::init();

    retro::Application app(1280, 720, "Retroportal");
    retro::Renderer renderer(app);

    retro::Core core("../cores/snes9x_libretro.dll");
    core.loadGame("E:\\Spiele\\SNES\\Final Fantasy III (U) (V1.1) [!].smc");

    while (app.isRunning()) {
        app.pollEvents();
        core.run();

        renderer.clear();
        renderer.draw(core);
        renderer.swapBuffers();
    }

    core.unloadCurrentGame();

    atexit(retro::Log::shutdown);

    return 0;
}
