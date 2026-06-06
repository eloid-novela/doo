#include <iostream>
#include "../include/doo/app.hpp"

int main(int argc, char** argv) try
{
    doo::app app;
    return app.run(argc, argv);
}
catch (const std::exception& e)
{
    std::cerr << "[Doo] Fatal error: " << e.what() << '\n';
    return 1;
}