## 📝 Overview

The goal of this project is to simulate the classic Dining Philosophers problem, a fundamental exercise in concurrent programming.
It focuses on learning multithreading, synchronization, and data management to avoid issues like deadlocks, race conditions, and starvation.

---

## 🍽 The Problem

A number of philosophers sit around a table. Each philosopher alternates between thinking, eating, and sleeping.
However, there are limited forks on the table — one between each pair of philosophers — and each philosopher needs two forks to eat.

The challenge is to design a program that allows all philosophers to live harmoniously without conflicts or deadlocks.

---

## ⚙️ Rules

Each philosopher must take two forks (one on the left and one on the right) to eat.

If a philosopher doesn’t start eating before a certain time (time_to_die), they die.

After eating, they must sleep, then think before attempting to eat again.

The simulation stops when:

A philosopher dies.

Or, if a limit is specified, all philosophers have eaten a certain number of times.

---

## 🧠 Implementation Details

Written in C, using POSIX threads (pthread).

Synchronization is handled via mutexes to protect shared resources (forks and log output).

Each philosopher runs in its own thread.

A separate thread (or logic) monitors philosopher deaths and the end condition.

---

## 🧵 Key Concepts

Threads: Each philosopher is a separate thread.

Mutexes: Used to represent forks and synchronize shared access.

Timing control: Accurate use of usleep and timestamps to ensure precise simulation.

Race condition prevention: Proper ordering and locking to avoid undefined behavior.
Emphasis on avoiding data races, proper timing, and clean thread management.

---

## 🚀 Usage

### 🛠 Compile:

Compile with:

```bash
make
```

Run with:
```bash
./philo nbr_of_philos time_to_die time_to_eat time_to_sleep [nbr_times_each_philo_must_eat]
```

Example
```bash
./philo 4 410 200 200 200
