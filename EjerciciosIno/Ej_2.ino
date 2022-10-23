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

/*

if (millis >= led_lm)
        {
            gpio_toggle(GPIOB, GPIO11);
            led_lm = millis + 500;
        }
        if (millis >= puls_lm)  
        {
            //  acumulo la última lectura y descarto la más vieja:
            puls_est = puls_est << 1;
            // leo el estado del pulsador:
            if (gpio_get(GPIOB, GPIO9) != GPIO9)
                puls_est = puls_est | 1;
            // verifico si hubo 8 lecturas iguales
            if (puls_est == 0b00000000)
                estado_actual = 0;
            else if (puls_est == 0b11111111)
                estado_actual = 1;
            // detección del flanco:
            if (estado_actual > estado_anterior)
            {
                gpio_toggle(GPIOB, GPIO12);
            }
            // el proximo anterior es el actual:
            estado_anterior = estado_actual;
            // ejecuto denuevo el testeo en 7ms
            puls_lm = millis + 7;
        }

*/