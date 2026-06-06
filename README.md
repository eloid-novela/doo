# Doo 

**Doo** is a lightweight Linux tool for monitoring and enforcing internet data caps on Ubuntu.

It helps you keep track of your network usage and automatically limits or blocks internet access when a defined data quota is reached.

---

## Features

- Real-time network usage monitoring
- Monthly/daily data caps
- Automatic internet blocking when limit is reached
- Persistent usage tracking across reboots
- Simple configuration via JSON
- Built for Linux (Ubuntu focused)

---

## How it works

Doo reads network statistics directly from Linux system interfaces:

- `/sys/class/net/<interface>/statistics/rx_bytes`
- `/sys/class/net/<interface>/statistics/tx_bytes`

It then:
1. Tracks total upload + download
2. Stores usage persistently
3. Compares against your configured limit
4. Disables network access when the limit is reached

---

## Installation

### Build from source

```bash
git clone https://github.com/eloid-novela/doo.git
cd doo
mkdir build && cd build
cmake ..
make
````

---

## Configuration

Example `configs/doo.json`:

```json
{
  "limit_gb": 5,
  "period": "monthly",
  "interface": "wlan0",
  "poll_interval_seconds": 10
}
```

---

## Usage

```bash
./doo
```

Or with systemd:

```bash
sudo systemctl enable doo.service
sudo systemctl start doo.service
```

---

## Motivation

In environments where internet data is limited or expensive, it’s easy to lose track of usage.

**Doo** was created to bring visibility and control over network consumption directly from the system level.

---

## Roadmap

* [ ] CLI arguments (`--limit`, `--interface`)
* [ ] Daily/weekly reset support
* [ ] Multi-interface support
* [ ] Better systemd integration

---

## License

This project is licensed under the MIT License.

---

## Name, lol

"Doo" is inspired by Scooby-Doo — always tracking things down… in this case, your data usage.
