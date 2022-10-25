#include <Arduino.h>
#define LED_1 2
#define LED_2 3
#define LED_3 4

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
void mef(char led, int repite);

void setup()
{
    // <>
}
// the loop function runs over and over again forever
void loop()
{
    mef(LED_1, 500);
    mef(LED_2,  50);
    mef(LED_3,   5);
    delay(1);
}

void mef(char led, int repite)
{
    static int contador = repite;
    static char ESTADO = inicial;
//----------------------------------------------------- inicial ---
    if (ESTADO == inicial)
    {
        pinMode(led, OUTPUT);
        contador = repite;
        ESTADO = prendido;
        digitalWrite(led, HIGH);
    }
//----------------------------------------------------- prendido ---
    if (ESTADO == prendido && contador <= 0)
    {
        digitalWrite(led, LOW);
        contador = repite;
        ESTADO = apagado;
    }
    if (ESTADO == prendido)contador--;
//----------------------------------------------------- apagado ---
    if (ESTADO == apagado && contador <= 0)
    {
        digitalWrite(led, HIGH);
        contador = repite;
        ESTADO = prendido;
    }
    if (ESTADO == prendido)contador--;
}