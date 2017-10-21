#include <glad/glad.h>
#include <retro/Log.h>
#include "ApplicationImpl_GLFW.h"

namespace retro
{
    ApplicationImpl_GLFW::ApplicationImpl_GLFW(int width, int height, const std::string& title)
    {
        if (!glfwInit()) {
            Log::error("Initialization of GLFW failed");
        }

        Log::debug("Initialized GLFW");

        // Set a OpenGL 4.1 Core context
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Window should not be resizable
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // Create a window
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            Log::error("Creation of a window failed");
        }

        Log::debug("Created a window");

        int left;
        int top;
        int right;
        int bottom;
        glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);

        int windowWidth = left + width + right;
        int windowHeight = top + height + bottom;
        auto videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        // Center the window
        glfwSetWindowPos(window, (videoMode->width - windowWidth) / 2, (videoMode->height - windowHeight) / 2);

        // Activate the context of the window for rendering
        glfwMakeContextCurrent(window);
        Log::debug("Activated the window context");

        // Load all GL extensions
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        Log::debug("Loaded GL extensions");
    }

    ApplicationImpl_GLFW::~ApplicationImpl_GLFW()
    {
        glfwTerminate();
        Log::debug("Terminated GLFW");
    }

    bool ApplicationImpl_GLFW::isRunning()
    {
        return !glfwWindowShouldClose(window);
    }

    void ApplicationImpl_GLFW::pollEvents()
    {
        glfwPollEvents();
    }

    void ApplicationImpl_GLFW::swapBuffers()
    {
        glfwSwapBuffers(window);
    }
}
