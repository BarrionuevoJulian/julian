#include <Arduino.h>
#define LED_1 3
#define LED_2 4

enum ESTADO
{
    inicial,
    prendido,
	apagado
};

void brilloLeds_1( char led , int brillo );
void brilloLeds_2( char led , int brillo );

void setup(){}

void loop()
{
    brilloLeds_1(LED_1, 1);
    brilloLeds_2(LED_2, 5);
    delay(1);
}

/**
 * @brief Brillo de un led en PWM con periodo de 20 m.
 * 
 * @param led Pin del led.
 * @param brillo escala de brillo de 0 a 10.
 */
void brilloLeds_1( char led , int brillo )
{
    static ESTADO est_1 = inicial;
    static int contador = 0;
    static bool bandera = false;
//----------------------------------------------------- inicial ---
    if (est_1 == inicial){
        pinMode(led, OUTPUT);
		digitalWrite(led, prendido);
        est_1 = prendido;
    }
//----------------------------------------------------- prendido --
    if (est_1 == prendido){
        // si la bandera es verdadera y contador mayor igual a parada
        if(contador >= brillo && bandera){
            digitalWrite(led, LOW);
			est_1 = apagado;
            bandera = false;
		}
	}
//----------------------------------------------------- apagado ---
	if (est_1 == apagado){
		// si la bandera es false y contador menor a parada
		if (contador < brillo && !bandera){
			digitalWrite(led, HIGH);
			est_1 = prendido;
			bandera = true;
		}
	}
    // contador vuelve a resetear el periodo
    if(contador > 10) contador = 0;
    contador++;
}

/**
 * @brief Brillo de un led en PWM con periodo de 20 m.
 * 
 * @param led Pin del led.
 * @param brillo escala de brillo de 0 a 10.
 */
void brilloLeds_2( char led , int brillo )
{
    static ESTADO est_2 = inicial;
    static int contador = 0;
    static bool bandera = false;
//----------------------------------------------------- inicial ---
    if (est_2 == inicial){
        pinMode(led, OUTPUT);
		digitalWrite(led, prendido);
        est_2 = prendido;
    }
//----------------------------------------------------- prendido --
    if (est_2 == prendido){
        // si la bandera es verdadera y contador mayor igual a parada
        if(contador >= brillo && bandera){
            digitalWrite(led, LOW);
			est_2 = apagado;
            bandera = false;
		}
	}
//----------------------------------------------------- apagado ---
	if (est_2 == apagado){
		// si la bandera es false y contador menor a parada
		if (contador < brillo && !bandera){
			digitalWrite(led, HIGH);
			est_2 = prendido;
			bandera = true;
		}
	}
    // contador vuelve a resetear el periodo
    if(contador > 10) contador = 0;
    contador++;
}
