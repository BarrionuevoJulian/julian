#include <Arduino.h>
#define LED_1 3
#define LED_2 4

enum ESTADO
{
    inicial,
    prendido,
	apagado
};

void brilloLeds( char led , int brillo );

void setup()
{
    
}

void loop()
{
    brilloLeds(LED_1, 1);
    brilloLeds(LED_2, 5);
    delay(1);
}

/**
 * @brief Brillo de un led en PWM con periodo de 20 m.
 * 
 * @param led Pin del led.
 * @param brillo escala de brillo de 0 a 10.
 */
void brilloLeds( char led , int brillo )
{
    static char ESTADO = inicial;
    static int contador = 0;
    static bool bandera = false;
//----------------------------------------------------- inicial ---
    if (ESTADO == inicial){
        pinMode(led, OUTPUT);
		digitalWrite(led, prendido);
        ESTADO = prendido;
    }
//----------------------------------------------------- prendido --
    if (ESTADO == prendido){
        // si la bandera es verdadera y contador mayor igual a parada
        if(contador >= brillo && bandera){
            digitalWrite(led, LOW);
			ESTADO = apagado;
            bandera = false;
		}
	}
//----------------------------------------------------- apagado ---
	if (ESTADO == apagado){
		// si la bandera es false y contador menor a parada
		if (contador < brillo && !bandera){
			digitalWrite(led, HIGH);
			ESTADO = prendido;
			bandera = true;
		}
	}
    // contador vuelve a resetear el periodo
    if(contador > 10) contador = 0;
}
