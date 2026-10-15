#include "../include/doo/network_controller.hpp"

#include <iostream>
#include <cstring>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>

namespace doo
{
bool NetworkController::disable(const char *interface)
{
    ifreq request{};

    const int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (fd == -1)
    {
        std::cerr << "[Doo] Failed to create socket\n";
        return false;
    }

    std::strncpy(
        request.ifr_name,
        interface,
        IFNAMSIZ - 1
    );

    if (ioctl(fd, SIOCGIFFLAGS, &request) == -1)
    {
        std::cerr << "[Doo] Failed to read interface flags\n";
        close(fd);
        return false;
    }

    request.ifr_flags &= ~IFF_UP;

    if (ioctl(fd, SIOCSIFFLAGS, &request) == -1)
    {
        const int error = errno;

        std::cerr << "[Doo] Failed to disable interface '"
                << interface << "': "
                << std::strerror(error)
                << " (errno=" << error << ")\n";
        close(fd);
        return false;
    }

    close(fd);

    std::cout << "[Doo] Interface disabled: "
                << interface << '\n';

    return true;
}
}