
#include "Graphics.h"

int main() {
    Graphics graphics = Graphics();
    try {
        graphics.init();
        graphics.run();
        graphics.cleanup();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
