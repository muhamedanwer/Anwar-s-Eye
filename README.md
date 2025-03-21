# Anwar's Eye

Anwar's Eye is a **lightweight and efficient** system monitoring tool built with **Rust**. It provides a **graphical interface** to visualize real-time system metrics, including CPU usage, memory consumption, disk activity, and network performance.

## Features
- **Real-time Monitoring:** Live updates for CPU, memory, disk, and network statistics.
- **Interactive Charts:** Displays CPU and memory usage trends.
- **Process Management:** View running processes with resource utilization.
- **Minimal & Performance-Oriented:** Optimized for low resource consumption.
- **Dark Mode UI:** Aesthetic design with Gruvbox dark theme.
- **Cross-Platform:** Runs on Linux and potentially other Unix-like systems.

## Installation
### Prerequisites
Ensure you have **Rust** installed. If not, install it using:
```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

### Clone the Repository
```sh
git clone https://github.com/yourusername/anwars-eye.git
cd anwars-eye
```

### Build and Run
```sh
cargo build --release
cargo run
```

## Usage
Once running, Anwar's Eye provides an interactive system monitor with the following views:
- **CPU Usage:** Real-time CPU load visualization.
- **Memory Usage:** Used vs. available memory.
- **Disks:** Information about mounted disks and their available space.
- **Network Activity:** Data transmitted and received.
- **Processes:** List of running processes and their resource consumption.

### Keyboard Shortcuts
- `q` - Quit the application
- `r` - Refresh stats manually
- `1, 2, 3` - Switch between different views

## Technologies Used
- **Rust** with `sysinfo` for system data collection
- **Plotters** for visualization
- **GTK or egui** (to be finalized) for GUI rendering

## Contributing
Pull requests are welcome. If you'd like to contribute, please open an issue or submit a PR.

## License
MIT License

---
Developed by **Noah** as part of a university software engineering project 🚀.

