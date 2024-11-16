#include "tag_functions.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }
    Metadata metadata = getMetadata(argv[1]);
    std::cout << metadata << std::endl;
    return 0;
}