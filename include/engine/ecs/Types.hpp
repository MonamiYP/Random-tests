#pragma once

#include <cstdint>
#include <bitset>

using Entity = std::uint32_t; // Entity is just an integer ID
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>; // Bitmask of which components an entity has

using EventType = std::uint32_t;