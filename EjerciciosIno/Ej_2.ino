// Maquina de estado 2

#include <Arduino.h>
#define LED LED_BUILTIN
#define PULSADOR 3 // pin 3

enum ESTADO
{
    inicial,
    prendido,
    apagado
};

/**
 * @brief Maquina de estado para cambiar estado de prendido a apagado
 * 
 * @param led Pin del led
 * @param repite Tiempo pren/apagado
 */
void mef(char led, int pulsador);

void setup()
{
    
}

void loop()
{
    mef(LED, PULSADOR);
    delay(1);
}

void mef(char led, int pulsador)
{
    static char ESTADO = inicial;

    if (ESTADO == inicial)
    {
        pinMode(led, OUTPUT);
        ESTADO = prendido;
        digitalWrite(led, HIGH);
    }
    
}