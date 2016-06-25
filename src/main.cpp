#include <iostream>
#include "Game.hpp"
#include "Error.hpp"

#define UNUSED(x) x=x
#define BITS_PER_PIXEL 8

using namespace std;

bool parseArgs(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    return false;
}

int main(int argc, char *argv[]) {
    if(parseArgs(argc, argv)) {
        cout << "Boxen voxel engine help" << endl;
        return 0;
    }

    try {
        Game game;

        game.run();
    } catch(Error &error) {
        cout << error.type << ":" << error.file << ":" << error.line << " " << error.message << endl;
    }

    return 0;
}
