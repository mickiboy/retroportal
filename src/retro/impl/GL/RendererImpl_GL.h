#pragma once

#include <glm/glm.hpp>
#include <retro/Application.h>
#include <retro/Renderer.h>

namespace retro
{
    class RendererImpl_GL : public Renderer::Impl, public ResizeEventReceiver
    {
    public:
        RendererImpl_GL(Application& app);
        virtual ~RendererImpl_GL() = default;

        void clear() override;
        void draw(Drawable& drawable) override;
        void swapBuffers() override;

        void onResize(int width, int height) override;

    private:
        Application& app;

        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    };
}
