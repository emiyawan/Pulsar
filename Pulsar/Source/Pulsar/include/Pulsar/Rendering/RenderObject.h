#pragma once
#include <gfx/GFXApplication.h>
#include <gfx/GFXBuffer.h>
#include <Pulsar/EngineMath.h>
#include <Pulsar/Assets/Material.h>

namespace pulsar::rendering
{

    struct MeshBatchElement
    {
        gfx::GFXBuffer_sp Vertex;
        gfx::GFXBuffer_sp Indices;
        gfx::GFXDescriptorSet_sp ModelDescriptor;
    };

    struct MeshBatch
    {
        array_list<MeshBatchElement> Elements;
        gfx::GFXDescriptorSetLayout_sp DescriptorSetLayout;
        Material_ref Material;

        gfx::GFXGraphicsPipelineState State{};
        bool IsUsedIndices;
        bool IsWireframe;
        bool IsCastShadow;

        size_t GetRenderState() const
        {
            constexpr size_t prime = 16777619;
            return (2166136261 * prime
                ^ std::hash<ObjectPtrBase>()(Material)) * prime
                ^ State.GetHashCode() * prime;
        }

        void Append(const MeshBatch& batch)
        {
            for (const auto& element : batch.Elements)
            {
                Elements.push_back(element);
            }
        }
    };


    class RenderObject
    {
    public:
        virtual ~RenderObject() = default;
        void SetTransform(const Matrix4f& localToWorld)
        {
            m_localToWorld = localToWorld;
            m_isLocalToWorldDeterminantNegative = localToWorld.Determinant() < 0;

            OnChangedTransform();
        }
        virtual void OnChangedTransform() {}
        void UpdateConstantBuffer()
        {

        }

        virtual void OnCreateResource() {}
        virtual void OnDestroyResource() {}

        virtual array_list<MeshBatch> GetMeshBatchs() = 0;
        virtual bool IsActive() const { return m_active; };

        bool IsDetermiantNegative() const { return m_isLocalToWorldDeterminantNegative; }

    public:

    protected:
        bool      m_active = false;
        Matrix4f  m_localToWorld{1};
        bool      m_isLocalToWorldDeterminantNegative{};
        int       m_lineWidth{1};
    };
    CORELIB_DECL_SHORTSPTR(RenderObject);
}