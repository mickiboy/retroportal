#pragma once

#include <GLFW/glfw3.h>
#include <retro/Application.h>

namespace retro
{
    class ApplicationImpl_GLFW : public Application::Impl
    {
    public:
        ApplicationImpl_GLFW(int width, int height, const std::string& title);
        virtual ~ApplicationImpl_GLFW();

        bool isRunning() override;
        void pollEvents() override;

        void swapBuffers();

    private:
        GLFWwindow* window = nullptr;
    };
}
