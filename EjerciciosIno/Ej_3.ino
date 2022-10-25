#include <Arduino.h>
#define LED_1 3
#define LED_2 4

enum ESTADO
{
    inicial,
    ejecucion
};

void brilloLeds( char led , int brillo );

void setup()
{
    
}

void loop()
{
    brilloLeds(LED_1, 10);
    brilloLeds(LED_2, 50);
    delay(1);
}

/**
 * @brief Brillo de un led en PWM con periodo de 20 m.
 * 
 * @param led Pin del led.
 * @param brillo escala de brillo de 0 a 100 %.
 */
void brilloLeds( char led , int brillo )
{
    static char ESTADO = inicial;
    static int contador = 0;
    static bool bandera = false;
    static int parada = brillo/5;
//----------------------------------------------------- inicial ---
    if (ESTADO == inicial){
        pinMode(led, OUTPUT);
        ESTADO = ejecucion;
    }
//----------------------------------------------------- ejecucion -
    if (ESTADO == ejecucion){
        // si la bandera es verdadera y contador mayor igual a parada
        if(contador >= parada && bandera){
            digitalWrite(led, LOW);
            bandera = false;
        }
        // si la bandera es false y contador menor a parada
        if (contador < parada && !bandera)
        {
            digitalWrite(led, LOW);
            bandera = true;
        }
        // contador vuelve a resetear el periodo
        if(contador >= 20) contador = 0;
    }
    contador++;
}