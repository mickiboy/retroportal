#pragma once

#include <glm/glm.hpp>
#include <retro/Application.h>
#include <retro/Event.h>
#include <retro/Renderer.h>

namespace retro
{
    class RendererImpl_GL : public Renderer::Impl,
        public Receiver<events::Resize>
    {
    public:
        RendererImpl_GL(Application& app);
        virtual ~RendererImpl_GL() = default;

        void clear() override;
        void draw(Drawable& drawable) override;
        void swapBuffers() override;

        void receiveEvent(const events::Resize& e) override;

    private:
        Application& app;

        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    };
}
