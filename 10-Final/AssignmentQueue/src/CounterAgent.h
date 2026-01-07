

#ifndef COUNTERAGENT_H_
#define COUNTERAGENT_H_

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Agent.h"

// Configuration pour 8 LEDs (Octet complet)
#define COUNT_LEDS          8
#define COUNT_QUEUE_LEN     10
#define COUNT_BLINK_DELAY   500

class CounterAgent : public Agent {
public:
    /***
     * Constructeur pour 8 LEDs
     */
    CounterAgent(uint8_t gp1, uint8_t gp2, uint8_t gp3, uint8_t gp4,
                 uint8_t gp5, uint8_t gp6, uint8_t gp7, uint8_t gp8);

    virtual ~CounterAgent();

    // Envoie une commande "ON" avec une valeur 8-bit à la Queue
    virtual void on(uint8_t count);

    // Envoie une commande "OFF" à la Queue
    virtual void off();

    // Envoie une commande "BLINK" à la Queue
    virtual void blink(uint8_t count);

protected:
    virtual void run();
    virtual configSTACK_DEPTH_TYPE getMaxStackSize();
    virtual void init();
    virtual void setLeds(uint8_t count);

    uint8_t pLedPads[COUNT_LEDS];
    QueueHandle_t xCmdQ;
};

#endif /* COUNTERAGENT_H_ */