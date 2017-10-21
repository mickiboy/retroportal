#include "impl/GL/RendererImpl_GL.h"

namespace retro
{
    Renderer::Renderer(Application& app)
    {
        impl = std::make_shared<RendererImpl_GL>(app);
    }

    Renderer::~Renderer()
    {
        impl.reset();
    }

    template<typename T> T* Renderer::getImpl()
    {
        return static_cast<T*>(impl.get());
    }

    template RendererImpl_GL* Renderer::getImpl<RendererImpl_GL>();

    void Renderer::clear()
    {
        impl->clear();
    }

    void Renderer::draw(Drawable& drawable)
    {
        impl->draw(drawable);
    }

    void Renderer::swapBuffers()
    {
        impl->swapBuffers();
    }
}
