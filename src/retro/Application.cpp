#include "impl/GLFW/ApplicationImpl_GLFW.h"

namespace retro
{
    Application::Application(int width, int height, const std::string& title)
    {
        impl = std::make_shared<ApplicationImpl_GLFW>(width, height, title);
    }

    Application::~Application()
    {
        impl.reset();
    }

    template<typename T> T* Application::getImpl()
    {
        return static_cast<T*>(impl.get());
    }

    template ApplicationImpl_GLFW* Application::getImpl<ApplicationImpl_GLFW>();

    bool Application::isRunning()
    {
        return impl->isRunning();
    }

    void Application::pollEvents()
    {
        impl->pollEvents();
    }
}
