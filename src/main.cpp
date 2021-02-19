#include "trunk.h"

int main() {
    Trunk& trunk = Trunk::instance();

    trunk.run();
}