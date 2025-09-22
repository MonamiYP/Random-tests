#include "Engine.hpp"

int main() {
    try {
        Engine engine;
        engine.Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}