#include "trunk.h"

using namespace ROK;

int main() {
    Trunk& trunk = Trunk::instance();

    trunk.run();
}