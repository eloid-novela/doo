# Doo

**Doo** is a lightweight Linux service for monitoring network usage and enforcing a configured data cap.

It helps you keep track of your network usage and automatically limits or blocks internet access when a defined data quota is reached.

---

## Features

- Real-time network usage monitoring
- Daily, weekly, and monthly cap profiles
- Automatic NetworkManager shutdown when the cap is reached
- JSON configuration with validation
- One-shot checks for automation and diagnostics
- Native CMake, systemd, Docker, and Docker Compose support

---

## How it works

Doo reads cumulative network statistics directly from Linux system interfaces:

- `/sys/class/net/<interface>/statistics/rx_bytes`
- `/sys/class/net/<interface>/statistics/tx_bytes`

It adds received and transmitted bytes for the configured interface and compares the result with the cap. When the cap is reached, Doo calls NetworkManager to disable networking.

---

## Installation

### Build from source with CMake

```bash
git clone https://github.com/eloid-novela/doo.git
cd doo
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
````

The binary is written to `build/doo` (or `build/doo.exe` on Windows). Network statistics and NetworkManager integration require Linux.

---

## Configuration

The default configuration is `configs/doo.json`:

```json
{
  "limit_gb": 5,
  "period": "monthly",
  "interface": "eth0",
  "poll_interval_seconds": 60
}
```

`limit_gb` uses decimal gigabytes. Valid periods are `daily`, `weekly`, and `monthly`. The current monitor reads the Linux cumulative counters for the configured interface.

---

## Usage

```bash
./build/doo --config configs/doo.json
```

Use `--once` to check the current usage and exit, or `--help` to list all options.

Or with systemd:

```bash
sudo systemctl enable doo.service
sudo systemctl start doo.service
```

After installation, copy the sample configuration to `/etc/doo/doo.json` and adjust the interface name. The service needs root privileges because it controls NetworkManager.

### Docker Compose

```bash
docker compose up --build -d
docker compose logs -f doo
```

The Compose service uses host networking, the host D-Bus socket, and elevated network permissions so that `nmcli networking off` can control the host NetworkManager. Review this trust boundary before deploying it.

---

## Motivation

In environments where internet data is limited or expensive, it’s easy to lose track of usage.

**Doo** was created to bring visibility and control over network consumption directly from the system level.

---

## Operational notes

- Run on Linux with NetworkManager installed.
- Replace `eth0` with the real interface from `ip link`.
- The service exits with code `2` after disabling networking and with code `0` when usage is below the cap.
- Containerized operation requires host networking and privileged network control; a native systemd installation has a smaller attack surface.

---

## License

This project is licensed under the MIT License.

---

## Name, lol

"Doo" is inspired by Scooby-Doo — always tracking things down… in this case, your data usage.
