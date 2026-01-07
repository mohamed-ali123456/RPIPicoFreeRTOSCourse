For the 6 chapter
I add some LED in main.cpp and made the change in CounterAgent.h and CounterAgent.cpp

main :

void mainTask(void *params){
char line[80];
BlinkAgent blink(LED_PAD);
CounterAgent counter(LED1_PAD, LED2_PAD, LED3_PAD, LED4_PAD, LED5_PAD, LED6_PAD, LED7_PAD, LED8_PAD); //ADD OF LED5_PAD TO LED8_PAD
DecoderAgent decoder(&counter);

while (true) { // Loop forever
runTimeStats();
uint16_t r = rand() & 0x0FF; //CHANGE 0x0F TO 0x0FF

CounterAgent.cpp :

CounterAgent::CounterAgent(uint16_t gp1, uint16_t gp2, uint16_t gp3, uint16_t gp4, uint16_t gp5, uint16_t gp6, uint16_t gp7, uint16_t gp8) {

pLedPads[0] = gp1;
pLedPads[1] = gp2;
pLedPads[2] = gp3;
pLedPads[3] = gp4;
pLedPads[4] = gp5;
pLedPads[5] = gp6;
pLedPads[6] = gp7;
pLedPads[7] = gp8;

  // ADD SOME UINT16_T GPX AND SOME PLEDPADS[] = GP
  // I SWITCH UINT8_T TO UINT16_T BECAUSE WE NEED 8 LEDS

CounterAgent.h :

CounterAgent(uint16_t gp1=0, uint16_t gp2=0, uint16_t gp3=0, uint16_t gp4=0, uint16_t gp5=0, uint16_t gp6=0, uint16_t gp7=0, uint16_t gp8=0); //SAME I ADD UINT16_T GPx = 0

#define COUNT_LEDS 8 //I SWITCH 4 TO 8
