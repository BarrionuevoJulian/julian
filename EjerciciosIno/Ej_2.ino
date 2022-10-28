// Maquina de estado 2

#include <Arduino.h>
#define LED LED_BUILTIN
#define PULSADOR 3 // pin 3

enum EST
{
    inicial,
    prendido,
    apagado
};

enum LEC
{
    conteo,
    muestreo,
    retorno
};

/**
 * @brief Maquina de estado para cambiar estado de prendido a apagado
 * 
 * @param led Pin del led
 * @param repite Tiempo pren/apagado
 */
void mef(char led, int pulsador);
bool pulsoToggle(char pulsador);

void setup(){}

void loop()
{
	bool pulsador = pulsoToggle (PULSADOR);
    mef(LED, pulsador);
    delay(1);
}

void mef(char led, bool cambio)
{
    static char EST = inicial;
//----------------------------------------------------- inicial ---
    if (EST == inicial)
    {
        pinMode(led, OUTPUT);
        EST = apagado;
        digitalWrite(led, HIGH);
    }
//----------------------------------------------------- prendido ---
    if (EST == prendido) {
		digitalWrite(led,HIGH);
	}
//----------------------------------------------------- apagado ---
    if (EST == apagado) {
		 digitalWrite(led, LOW);
	}
//-----------------------------------------------------------------
	if (cambio) EST = prendido;
	else EST = apagado; 
}

#define CICLO 7 // cada cuanto se leera el boton

uint8_t lectura = 0xFF; // igual a 0b11111111
int ciclo = 0;

/**
 * @brief Lee pulsador y togglea valor de su función cuando se presiona el mismo.
 * muestro del mismo cada CICLOS ms.
 * 
 * @param pulsador Pin del pulsador
 * @return true 
 * @return false 
 */
bool pulsoToggle(char pulsador)
{
	static char LEC = conteo;

	static uint8_t lectura = 0xFF;      // igual a 0b11111111
	static int ciclo = 0;
	static bool valorDevuelto = false;
	
	static bool cambio = false, anterior_cam = false;
	
	if (LEC == conteo) ciclo++;
	
	if (LEC == conteo && ciclo > CICLO) LEC = muestreo;

	if (LEC == muestreo)
	{
		lectura = lectura << 1;  // Mover de lugar el bit
		if (digitalRead(pulsador) != 0){
			lectura = lectura + 1;
		}
		if(lectura == 0){
			cambio = false;
		}
		else if(lectura == 0xFF){  // otra forma de poner 0b11111111
			cambio = true;
		}
		if(cambio < anterior_cam){
			// digitalWrite(led, !digitalRead(led));
			LEC = retorno;
		}
		anterior_cam = cambio;
		ciclo = 0;
	}

	if (LEC == retorno){
		LEC = conteo;
		return valorDevuelto = !valorDevuelto;
	}
}
