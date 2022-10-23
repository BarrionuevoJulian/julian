// Maquina de estado 2

#include <Arduino.h>
#define LED LED_BUILTIN
#define PULSADOR 3 // pin 3

uint8_t lectura = 0xFF; // igual a 0b11111111
int ciclo = 0;
bool cambio = false, anterior_cam = false;

#define CICLO 7 // cada cuanto se leera el boton

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
    if(ciclo > CICLO){  //Lecturas del pulsador
        lectura = lectura << 1;  // Mover de lugar el bit
        if (digitalRead(led) != 0){
            lectura = lectura + 1;
        }
        if(lectura == 0){
            cambio = false;
        }
        else if(lectura == 0xFF){  // otra forma de poner 0b11111111
            cambio = true;            
        }
        if(cambio < anterior_cam){
            digitalWrite(led, !digitalRead(led));
            /*
            if (ESTADO == apagado) ESTADO = prendido;
            else ESTADO = apagado; 
            */
        }
        anterior_cam = cambio;
        ciclo = 0;
    }
    ciclo++;
}