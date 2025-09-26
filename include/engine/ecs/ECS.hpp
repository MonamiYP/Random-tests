#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"
// #include "EventManager.hpp"
#include "Types.hpp"
#include <memory>

class ECS {
    public:
        void Init() {
            m_EntityManager = std::make_unique<EntityManager>();
            m_ComponentManager = std::make_unique<ComponentManager>();
            m_SystemManager = std::make_unique<SystemManager>();
            // m_EventManager = std::make_unique<EventManager>();
        }

        /* Entities */
        Entity CreateEntity() { return m_EntityManager->CreateEntity(); }

        void DestroyEntity(Entity entity) {
            m_EntityManager->DestroyEntity(entity);
            m_ComponentManager->EntityDestroyed(entity);
            m_SystemManager->EntityDestroyed(entity);
        }


        /* Components */
        template<typename T>
        void RegisterComponent() { m_ComponentManager->RegisterComponent<T>(); }

        template<typename T>
        void AddComponent(Entity entity, T component) {
            m_ComponentManager->AddComponent<T>(entity, component);

            auto signature = m_EntityManager->GetSignature(entity);
            signature.set(m_ComponentManager->GetComponentType<T>(), true);
            m_EntityManager->SetSignature(entity, signature);
            m_SystemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        void RemoveComponent(Entity entity, T component) {
            m_ComponentManager->RemoveComponent<T>(entity);

            auto signature = m_EntityManager->GetSignature(entity);
            signature.set(m_ComponentManager->GetComponentType<T>(), false);
            m_EntityManager->SetSignature(entity, signature);
            m_SystemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        T& GetComponent(Entity entity) { return m_ComponentManager->GetComponent<T>(entity); }

        template<typename T>
        bool HasComponent(Entity entity) { return m_ComponentManager->HasComponent<T>(entity); }

        template<typename T>
        ComponentType GetComponentType() { return m_ComponentManager->GetComponentType<T>(); }


        /* Systems */
        template<typename T>
        std::shared_ptr<T> RegisterSystem() { return m_SystemManager->RegisterSystem<T>(); }

        template<typename T>
        void SetSystemSignature(Signature signature) { m_SystemManager->SetSignature<T>(signature); }
    
    private:
	    std::unique_ptr<EntityManager> m_EntityManager;
        std::unique_ptr<ComponentManager> m_ComponentManager;
	    std::unique_ptr<SystemManager> m_SystemManager;
        // std::unique_ptr<EventManager> m_EventManager;
};