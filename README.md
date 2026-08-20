# The Santa Claus Problem: Process Synchronization

A C-based multi-threaded application demonstrating process synchronization and concurrent programming concepts by solving the classic Santa Claus Problem.

This project utilizes POSIX threads (Pthreads) and semaphores to coordinate interactions between multiple independent entities, effectively managing shared resources, preventing race conditions, and avoiding deadlocks.

## Problem Description
Santa Claus sleeps at the North Pole and is only awakened under two specific conditions:
1. **Reindeers (Priority 1):** All 9 reindeers return from vacation. Santa must immediately hitch them to the sleigh and deliver toys.
2. **Elves (Priority 2):** Exactly 3 elves encounter a problem in the workshop and need Santa's help.

## Features
* **Thread Synchronization:** Utilizes `sem_wait` and `sem_post` from the `<semaphore.h>` library to orchestrate 20 independent threads (1 Santa, 9 Reindeers, 10 Elves).
* **Mutual Exclusion:** Implements a binary semaphore (`counterGuard`) as a mutex to protect shared variables (elf and reindeer counters) from race conditions during concurrent access.
* **Deadlock Prevention:** Ensures critical sections are safely locked and unlocked before waiting on secondary semaphores.
* **Starvation Handling:** Includes specific logic to prevent elves from starving if reindeers continuously return, ensuring all threads make progress.
* **Condition & Barrier Synchronization:** Employs semaphores (`wakeUpSanta`, `reindeerQueue`, `elfWorkshop`) to force threads to wait until specific thresholds (9 reindeers or 3 elves) are met.

## Tech Stack
* **Language:** C
* **Libraries:** `<pthread.h>`, `<semaphore.h>`
* **Environment:** POSIX-compliant OS (macOS/Linux)

## How to Run
Compile the program using `gcc` and ensure you link the pthread library:

```bash
gcc main.c -o santa_claus -lpthread
./santa_claus
