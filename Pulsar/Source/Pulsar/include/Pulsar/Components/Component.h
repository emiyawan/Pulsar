#pragma once

#include <CoreLib/CoreLib.h>
#include <Pulsar/EngineMath.h>
#include <Pulsar/ObjectBase.h>
#include <Pulsar/Ticker.h>

namespace pulsar
{
    class Node;
    class World;
    class Scene;

    using MessageId = size_t;
    inline size_t MessageId_OnChangedTransform() { static bool b; return reinterpret_cast<size_t>(&b); };
    inline size_t MessageId_OnDrawGizmos() { static bool b; return reinterpret_cast<size_t>(&b); };
    inline size_t MessageId_OnSelectedDrawGizmos() { static bool b; return reinterpret_cast<size_t>(&b); };

    class AbstractComponentAttribute : public Attribute
    {
        CORELIB_DEF_TYPE(AssemblyObject_pulsar, pulsar::AbstractComponentAttribute, Attribute);
    };

    class Component : public ObjectBase, public ITickable
    {
        friend class Node;
        CORELIB_DEF_TYPE(AssemblyObject_pulsar, pulsar::Component, ObjectBase);
        CORELIB_CLASS_ATTR(new AbstractComponentAttribute);
    public:
        ObjectPtr<Node> GetAttachedNode() const;
        ObjectPtr<Node> GetOwnerNode() const;
        World* GetWorld() const;
        ObjectPtr<Scene> GetRuntimeScene() const;
        virtual bool get_is_tickable() const { return true; }
        virtual void OnReceiveMessage(MessageId id);
    public:
		virtual bool EqualsComponentType(Type* type);
    public:
        // Engine object lifecycle
        void OnDestroy() override {}

        virtual void BeginComponent();
        virtual void EndComponent();

        virtual void BeginPlay() {}
        virtual void EndPlay() {}

        virtual void OnMsg_TransformChanged() {}
    public:        
        // ITickable interface
        void OnTick(Ticker ticker) override;
    public:
        Component() = default;
    private:
        ObjectPtr<Node> m_ownerNode;
        ObjectPtr<Node> m_attachedNode;
        ObjectPtr<Scene> m_runtimeScene;
    protected:
        bool m_beginning = false;
    public:
        bool IsCollapsing = false;
    };
    DECL_PTR(Component);

    class ComponentInfoManager final
    {
    public:
        static string GetFriendlyComponentName(Type* type);
    };
}
