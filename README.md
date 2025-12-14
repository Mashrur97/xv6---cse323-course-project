# 🖥️ XV6 – CSE323 Course Project

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![GitHub Repo Size](https://img.shields.io/github/repo-size/Mashrur97/xv6---cse323-course-project)]()

This repository contains the **modified XV6 operating system** for the **CSE323 course project**.  
We added new system calls, priority-based scheduling, and test programs to explore process management.

---

## ✨ Features Implemented

### 1️⃣ `meminfo` System Call
Displays information about all processes:

| PID | NAME     | MEMORY (bytes) | CREATED (ticks) | STATE    | PRIORITY |
|-----|----------|----------------|----------------|----------|----------|
| 1   | init     | 12288          | 0              | SLEEP    | 2        |
| 2   | sh       | 16384          | 2              | SLEEP    | 2        |
| 3   | meminfo  | 12288          | 950            | RUNNING  | 2        |
| 9   | dpro     | 12288          | 2587           | RUNNABLE | 10       |

- **Ticks**: Time is measured in timer ticks (100 ticks = 1 second).  
- **State**: Shows the current process state (RUNNING, SLEEP, RUNNABLE, UNUSED).  
- **Priority**: Shows the scheduling priority of the process.

---

### 2️⃣ Priority-Based Round-Robin Scheduling
- Combines **round-robin** and **priority scheduling**.  
- Reduces starvation while giving higher priority processes more CPU time.  
- Implemented by modifying `scheduler()` in `proc.c`.  
- Default child process priority set in `exec.c`.

---

### 3️⃣ `priority` Command
- Change the priority of a process at runtime.  
- **Example:**  

priority 9 1

Sets process with PID 9 to priority 1.

4️⃣ CPU-Consuming Test Program (dpro)

Spawns multiple child processes to simulate CPU load.

Used to test scheduling and priority behavior.

dpro &

🗂 File Structure
xv6-public/
├── user/
│   ├── meminfo.c
│   ├── dpro.c
│   ├── priority.c
│   └── ... (other user programs)
├── kernel/
│   ├── proc.c
│   ├── sysproc.c
│   ├── exec.c
│   └── ... (kernel source files)
├── Makefile
└── README.md

🚀 Installation and Running

Clone the repository

git clone https://github.com/Mashrur97/xv6---cse323-course-project.git
cd xv6---cse323-course-project


Build and run XV6

make qemu


Use QEMU to emulate the OS.

Commands available: meminfo, dpro &, priority, and standard XV6 shell commands.

📝 Notes

Ticks: Emulated hardware timer ticks (100 ticks/sec).

Process Creation Time (ctime): Tracks when each process is created.

State Names: RUNNING, SLEEP, RUNNABLE, UNUSED, etc.

👤 Contributors

Mashrur Fardin – Implemented meminfo
SM Tazbid Siddiqui - Implemented priority scheduling
