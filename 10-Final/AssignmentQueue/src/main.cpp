/**
 * PROJET FINAL - CHAPITRE 10
 * MULTICORE, QUEUE, ET 8 LEDS BINAIRES
 */

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <math.h>

#include "BlinkAgent.h"
#include "CounterAgent.h"

#define TASK_PRIORITY (tskIDLE_PRIORITY + 1UL)

// Définition des 8 Pins GPIO pour les LEDs (Exemple: GPIO 2 à 9)
#define L0 2
#define L1 3
#define L2 4
#define L3 5
#define L4 6
#define L5 7
#define L6 8
#define L7 9

// Instance globale de l'agent 8 LEDs
CounterAgent counter(L0, L1, L2, L3, L4, L5, L6, L7);

/**
 * Fonction s'exécutant sur le CORE 1 (Multicore)
 * Gère une tâche de calcul séparée
 */
void core1_entry() {
    printf("Core 1: Initialisé et prêt\n");
    while (1) {
        // Le Core 1 peut gérer des calculs lourds ici
        tight_loop_contents();
    }
}

/**
 * Tâche principale FreeRTOS (Core 0)
 */
void mainTask(void *params){
    printf("Main Task: Lancement du projet final\n");
    
    // Démarrage de l'agent
    counter.start("Counter8Bit", TASK_PRIORITY);

    while (true) {
        // Génération d'une valeur aléatoire 8-bit (0-255)
        uint8_t val = rand() & 0xFF;
        
        printf("Queue: Envoi valeur %d (0x%X) vers LEDs\n", val, val);
        
        // On demande à l'agent de faire clignoter cette valeur
        counter.blink(val);
        
        // Délai de 3 secondes avant la prochaine valeur
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

int main( void )
{
    stdio_init_all();
    sleep_ms(2000);
    printf("--- DEMARRAGE CHAPITRE 10 FINAL ---\n");

    // 1. Lancement du Multicore (Core 1)
    multicore_launch_core1(core1_entry);

    // 2. Lancement du Scheduler FreeRTOS (Core 0)
    xTaskCreate(mainTask, "MainThread", 512, NULL, TASK_PRIORITY, NULL);
    vTaskStartScheduler();

    return 0;
}