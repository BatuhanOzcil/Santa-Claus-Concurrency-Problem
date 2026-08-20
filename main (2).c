/*
 * CMPE 312 - Operating Systems Project
 * The Santa Claus Problem - Final Synchronized Solution
 * Batuhan Özçil
 * ID: 125200023
 */

#include <pthread.h>    // Required for thread creation and management
#include <semaphore.h>  // Required for semaphore synchronization
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // Required for sleep() function

// --- Global Synchronization Tools ---
sem_t wakeUpSanta;      // Semaphore to signal Santa Claus to wake up (starts at 0)
sem_t reindeerQueue;    // Barrier for reindeers waiting for the sleigh (starts at 0)
sem_t elfWorkshop;      // Barrier for elves waiting for Santa's help (starts at 0)
sem_t counterGuard;     // Mutex to protect shared counters from race conditions (starts at 1)

// --- Shared State Variables ---
int count_reindeer = 0; // Number of reindeers currently back from vacation
int count_elves = 0;    // Number of elves currently waiting at the door

// Routine for the Santa Claus thread
void* santa_routine(void* arg) {
    printf("Santa: I'm going to sleep in my cabin...\n");

    while(1) {
        // Santa enters a blocked state until someone signals wakeUpSanta
        sem_wait(&wakeUpSanta);

        // Lock counterGuard to safely check shared counters (Critical Section)
        sem_wait(&counterGuard);

        // PRIORITY 1: Check if all 9 reindeers are back
        if (count_reindeer == 9) {
            printf("\n--- Santa: All 9 reindeers are here! Preparing the sleigh for Christmas! ---\n");

            // Release all 9 reindeer threads from the queue
            for (int i = 0; i < 9; i++) {
                sem_post(&reindeerQueue);
            }
            count_reindeer = 0; // Reset counter for the next cycle

            // STARVATION PREVENTION: If 3 elves were waiting while Santa was busy with reindeers,
            // Santa signals himself to wake up again in the next iteration
            if (count_elves == 3) {
                sem_post(&wakeUpSanta);
            }
        }
        // PRIORITY 2: If no reindeers, check if 3 elves are waiting
        else if (count_elves == 3) {
            printf("\n--- Santa: Helping 3 little elves with their problems... ---\n");

            // Release the 3 waiting elves into the workshop
            for (int i = 0; i < 3; i++) {
                sem_post(&elfWorkshop);
            }
            count_elves = 0; // Reset counter for the next group
        }

        // Release the mutex to allow other threads access
        sem_post(&counterGuard);
    }
    return NULL;
}

// Routine for the Reindeer threads
void* reindeer_routine(void* arg) {
    int id = *((int*)arg);
    while(1) {
        // Simulate random vacation duration
        sleep(rand() % 10 + 10);

        // Lock counterGuard to update the shared counter safely
        sem_wait(&counterGuard);
        count_reindeer++;
        printf("Reindeer %d: Back from vacation (%d/9)\n", id, count_reindeer);

        // If this is the 9th reindeer, signal Santa to wake up
        if (count_reindeer == 9) {
            sem_post(&wakeUpSanta);
        }
        sem_post(&counterGuard); // Unlock

        // Wait here until Santa signals the reindeerQueue
        sem_wait(&reindeerQueue);
        printf("Reindeer %d: Hitched to the sleigh and flying!\n", id);
        sleep(2); // Simulate gift delivery
    }
    return NULL;
}

// Routine for the Elf threads
void* elf_routine(void* arg) {
    int id = *((int*)arg);
    while(1) {
        // Simulate elves working on toy production
        sleep(rand() % 15 + 2);

        // Lock mutex to check and update elf counter
        sem_wait(&counterGuard);

        // Only allow a group of up to 3 elves to wait
        if (count_elves < 3) {
            count_elves++;
            printf("Elf %d: Needs help (%d/3)\n", id, count_elves);

            // If this is the 3rd elf, signal Santa
            if (count_elves == 3) {
                sem_post(&wakeUpSanta);
            }

            // Unlock mutex BEFORE waiting for Santa to avoid deadlock
            sem_post(&counterGuard);

            // Wait for Santa to signal elfWorkshop
            sem_wait(&elfWorkshop);
            printf("Elf %d: Received help and returned to work.\n", id);
        } else {
            // Door is busy, elf continues working until a spot is free
            sem_post(&counterGuard);
        }
    }
    return NULL;
}

int main() {
    // Initialize Synchronization Primitives
    sem_init(&wakeUpSanta, 0, 0);   // Santa starts asleep
    sem_init(&reindeerQueue, 0, 0); // Reindeers start waiting for Santa
    sem_init(&elfWorkshop, 0, 0);   // Elves start waiting for help
    sem_init(&counterGuard, 0, 1);  // Mutex initialized to 1 for mutual exclusion

    pthread_t santa_thread;
    pthread_t reindeer_threads[9];
    pthread_t elf_threads[10];

    int ids[20]; // Buffer for distinct thread IDs

    // Create Santa thread
    pthread_create(&santa_thread, NULL, santa_routine, NULL);

    // Create 9 Reindeer threads
    for (int i = 0; i < 9; i++) {
        ids[i] = i + 1;
        pthread_create(&reindeer_threads[i], NULL, reindeer_routine, &ids[i]);
    }

    // Create 10 Elf threads
    for (int i = 0; i < 10; i++) {
        ids[i+9] = i + 1;
        pthread_create(&elf_threads[i], NULL, elf_routine, &ids[i+9]);
    }

    // Main thread joins Santa to keep process alive
    pthread_join(santa_thread, NULL);

    // Resource Cleanup
    sem_destroy(&wakeUpSanta);
    sem_destroy(&reindeerQueue);
    sem_destroy(&elfWorkshop);
    sem_destroy(&counterGuard);

    return 0;
}