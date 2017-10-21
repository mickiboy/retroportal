#pragma once

#include <retro/Renderer.h>

namespace retro
{
    class RendererImpl_GL : public Renderer::Impl
    {
    public:
        RendererImpl_GL(Application& app);
        virtual ~RendererImpl_GL() = default;

        void clear() override;
        void draw(Drawable& drawable) override;
        void swapBuffers() override;

    private:
        Application& app;
    };
}
