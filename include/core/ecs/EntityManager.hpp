#pragma once

#include <queue>
#include <iostream>

#include "Types.hpp"

/*
    Keep track of entity IDs and make sure conflicts dont happen
*/

class EntityManager { 
    public:
        EntityManager() {
            for (Entity entity=0; entity<MAX_ENTITIES; entity++) {
                m_AvailableEntities.push(entity);
            }
        }

        Entity CreateEntity() {
            if (m_LivingEntityCount > MAX_ENTITIES)
                std::cout << "Maximum number of entities reached" << std::endl;
            
            Entity id = m_AvailableEntities.front();
            m_AvailableEntities.pop();
            m_LivingEntityCount++;

            return id;
        }

        void DestroyEntity(Entity entity) {
            if (entity > MAX_ENTITIES)
                std::cout << "Entity out of range" << std::endl;
            
            m_Signatures[entity].reset();
            m_AvailableEntities.push(entity);
            m_LivingEntityCount--;
        }

        void SetSignature(Entity entity, Signature signature) {
            if (entity > MAX_ENTITIES)
                std::cout << "Entity out of range" << std::endl;
            
            m_Signatures[entity] = signature;
        }

        Signature GetSignature(Entity entity) {
            if (entity > MAX_ENTITIES)
                std::cout << "Entity out of range" << std::endl;
            
            return m_Signatures[entity];
        }

    private:
        std::queue<Entity> m_AvailableEntities{};
        std::array<Signature, MAX_ENTITIES> m_Signatures{}; 
	    uint32_t m_LivingEntityCount{};
};