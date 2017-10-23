#include <retro/Application.h>
#include <retro/Core.h>
#include <retro/Log.h>
#include <retro/Renderer.h>

int main(int argc, char* argv[])
{
    retro::Log::init();

    retro::Application app(1280, 720, "Retroportal");
    retro::Renderer renderer(app);

    while (app.isRunning()) {
        app.pollEvents();

        renderer.clear();
        renderer.swapBuffers();
    }

    atexit(retro::Log::shutdown);

    return 0;
}
