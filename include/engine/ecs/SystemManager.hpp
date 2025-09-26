#pragma once

#include "System.hpp"
#include "Types.hpp"

class SystemManager {
    public:
        template<typename T>
        std::shared_ptr<T> RegisterSystem() {
            const char* typeName = typeid(T).name();
            if (m_Systems.find(typeName) != m_Systems.end())
                std::cout << "ERROR::ECS::SYSTEM_MANAGER::This system has already been registered" << std::endl;
            
            auto system = std::make_shared<T>();
            m_Systems.insert({typeName, system});
            return system;
        }

        template<typename T>
        void SetSignature(Signature signature) {
            const char* typeName = typeid(T).name();
            if (m_Systems.find(typeName) == m_Systems.end())
                std::cout << "ERROR::ECS::SYSTEM_MANAGER::System not registered before use" << std::endl;
            
            m_Signatures.insert({typeName, signature});
        }

        void EntityDestroyed(Entity entity) {
            for (auto const& pair : m_Systems) {
		        auto const& system = pair.second;
                system->m_Entities.erase(entity);
	        }
        }

        void EntitySignatureChanged(Entity entity, Signature entitySignature) {
            for (auto const& pair : m_Systems) {
                auto const& type = pair.first;
                auto const& system = pair.second;
                auto const& systemSignature = m_Signatures[type];

                if ((entitySignature & systemSignature) == systemSignature) {
                    system->m_Entities.insert(entity);
                } else {
                    system->m_Entities.erase(entity);
                }
            }
        }
    
    private:
        std::unordered_map<const char*, Signature> m_Signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> m_Systems{};
};