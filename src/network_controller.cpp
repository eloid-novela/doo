#include "../include/doo/network_controller.hpp"
#include <cstdlib>
#include <iostream>

namespace doo
{
void NetworkController::disable()
{
    std::cout << "[Doo] Disabling network...\n";

    // MVP: Ubuntu command
    std::cout << std::system("nmcli networking off") << std::endl;
}
}