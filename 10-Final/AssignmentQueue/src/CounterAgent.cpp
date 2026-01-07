/**
 * CounterAgent.cpp
 * Implémentation de la file d'attente (Queue) et Buffer 8-bit
 */

#include "CounterAgent.h"
#include "stdio.h"

// Définition de la structure de commande pour la Queue
enum CounterAction {CounterOff, CounterOn, CounterBlink};

struct CounterCmd {
    CounterAction action;
    uint8_t       count; // Valeur 0-255
};

typedef struct CounterCmd CounterCmdT;

CounterAgent::CounterAgent(uint8_t gp1, uint8_t gp2, uint8_t gp3, uint8_t gp4,
                           uint8_t gp5, uint8_t gp6, uint8_t gp7, uint8_t gp8) {
    pLedPads[0] = gp1; pLedPads[1] = gp2; pLedPads[2] = gp3; pLedPads[3] = gp4;
    pLedPads[4] = gp5; pLedPads[5] = gp6; pLedPads[6] = gp7; pLedPads[7] = gp8;

    // Création de la Queue
    xCmdQ = xQueueCreate(COUNT_QUEUE_LEN, sizeof(CounterCmdT));
    if (xCmdQ == NULL){
        printf("ERREUR: Impossible de créer la Queue\n");
    }
}

CounterAgent::~CounterAgent() {
    if (xCmdQ != NULL) vQueueDelete(xCmdQ);
}

void CounterAgent::init(){
    for (int i = 0 ; i < COUNT_LEDS; i++){
        gpio_init(pLedPads[i]);
        gpio_set_dir(pLedPads[i], GPIO_OUT);
        gpio_put(pLedPads[i], 0);
    }
}

void CounterAgent::run(){
    BaseType_t res;
    init();
    printf("Agent 8-LEDs démarré sur Core 0\n");

    CounterAction action = CounterOff;
    uint8_t count = 0;
    bool blinkState = false;
    CounterCmdT cmd;

    while (true) {
        // Lecture de la Queue (Buffer de commande)
        res = xQueueReceive(xCmdQ, (void *)&cmd, pdMS_TO_TICKS(COUNT_BLINK_DELAY));
        
        if (res == pdTRUE){
            action = cmd.action;
            count = cmd.count;
        }

        switch(action){
            case CounterOff:
                setLeds(0);
                break;
            case CounterOn:
                setLeds(count);
                break;
            case CounterBlink:
                blinkState = !blinkState;
                setLeds(blinkState ? count : 0);
                break;
        }
    }
}

void CounterAgent::setLeds(uint8_t count){
    for (int i = 0; i < COUNT_LEDS; i++){
        // Extraction de chaque bit (0 à 7)
        gpio_put(pLedPads[i], (count >> i) & 0x01);
    }
}

configSTACK_DEPTH_TYPE CounterAgent::getMaxStackSize(){
    return 256;
}

void CounterAgent::on(uint8_t count){
    CounterCmdT cmd = {CounterOn, count};
    xQueueSendToBack(xCmdQ, &cmd, 0);
}

void CounterAgent::off(){
    CounterCmdT cmd = {CounterOff, 0};
    xQueueSendToBack(xCmdQ, &cmd, 0);
}

void CounterAgent::blink(uint8_t count){
    CounterCmdT cmd = {CounterBlink, count};
    xQueueSendToBack(xCmdQ, &cmd, 0);
}