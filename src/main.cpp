#include <cstdint>
#include <string>

#include "game.hpp"

int main(/*int argc, char const *argv[]*/)
{
    std::string configFile = "config.txt";
    
    Game g(configFile);
    g.run();

    return 0;
}
