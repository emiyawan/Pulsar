#pragma once
#include "Component.h"
#include <Pulsar/Assets/RenderTexture.h>

namespace pulsar
{
    enum class CameraMode
    {
        Perspective,
        Orthographic
    };

    class CameraComponent : public Component
    {
        CORELIB_DEF_TYPE(AssemblyObject_Pulsar, pulsar::CameraComponent, Component);
    public:
        virtual ~CameraComponent() override
        {
            int a = 3;
        }
        void Render();
    public:
        Matrix4f GetViewMat();
        Matrix4f GetProjectionMat();
        static Matrix4f LookAtRH(
            Vector3f const& eye,
            Vector3f const& center,
            Vector3f const& up);

        void LookAt(const Vector3f& pos);
    public:
        CORELIB_REFL_DECL_FIELD(fov);
        float fov;

        CORELIB_REFL_DECL_FIELD(near);
        float near;

        CORELIB_REFL_DECL_FIELD(far);
        float far;

        CORELIB_REFL_DECL_FIELD(size_);
        Vector2f size_;
        CameraMode cameraMode;

        CORELIB_REFL_DECL_FIELD(backgroundColor);
        LinearColorf backgroundColor;

#ifdef WITH_APATITE_EDITOR
        CORELIB_REFL_DECL_FIELD(debug_view_mat);
        Matrix4f debug_view_mat;
#endif
    public:
        const RenderTexture_sp& GetRenderTarget() const { return m_renderTarget; }
        void SetRenderTarget(const RenderTexture_sp& value) { m_renderTarget = value; }
    protected:
        RenderTexture_sp m_renderTarget;
    };
    DECL_PTR(CameraComponent);
}