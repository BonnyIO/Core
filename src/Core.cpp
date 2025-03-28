#include <iostream>
#include <memory>
#include "h/Log.hpp"
#include "h/Program.hpp"

class Tests : public Core::Program {

    virtual void on_update() override {}    
};

int main() {

    auto Prog = std::make_unique<Tests>();

    int returnCode = Prog->start(640, 480, "Core");

    std::cin.get();

    return returnCode;
}
