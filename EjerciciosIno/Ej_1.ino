#include <Arduino.h>
#define LED LED_BUILTIN

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
    mef(LED, 500);
    delay(1);
}

void inicio(void)
{
    pinMode(LED_BUILTIN, OUTPUT);
}

void mef(char led, int repite)
{
    static int contador = repite;
    static char ESTADO = inicial;

    //----------------------------------------------------
    if (ESTADO == inicial)
    {
        pinMode(led, OUTPUT);
        contador = repite;
        ESTADO = prendido;
        digitalWrite(led, HIGH);
    }
    //----------------------------------------------------
    if (ESTADO == prendido && contador <= 0)
    {
        digitalWrite(led, LOW);
        contador = repite;
        ESTADO = apagado;
    }
    if (ESTADO == prendido)
        contador--;

    //----------------------------------------------------

    if (ESTADO == apagado && contador <= 0)
    {
        digitalWrite(led, HIGH);
        contador = repite;
        ESTADO = prendido;
    }
    if (ESTADO == prendido)
        contador--;
}

////////////////////////////////////////////////////////

/*

estancia

*/

/* https://github.com/BarrionuevoJulian/julian.git */