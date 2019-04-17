#include "Vision.h"

/**
 * Main entry point for the good foxfest vision program
 */
int main() {
    std::cout << "Vision man is here" << std::endl;
    PostProcessor worker = PostProcessor();
    worker.Loop();
    std::cout << "Goodbye!" << std::endl;

    return 0;
}