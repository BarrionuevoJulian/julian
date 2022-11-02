// Maquina de estado 2

#include <Arduino.h>
#define LED LED_BUILTIN
#define PULSADOR 8 // pin 8

enum EST
{
    inicial,
    prendido,
    apagado,
	pulso
};

/**
 * @brief Maquina de estado para cambiar estado de prendido a apagado
 * 
 * @param led Pin del led
 * @param repite Tiempo pren/apagado
 */
void mef(char led, bool pulsador);
bool AntiRebotePulso(char pull);

void setup(){
	Serial.begin(9600);
}

void loop()
{
	mef(LED,AntiRebotePulso (PULSADOR));
    delay(1);
}

void mef(char led, bool pulsar)
{
    static char EST = inicial;
	static bool bandera = false;
	static bool onoff;
//----------------------------------------------------- inicial ---
    if (EST == inicial)
    {
        pinMode(led, OUTPUT);
        EST = prendido;
        onoff = true;
    }
//----------------------------------------------------- prendido ---
    if (EST == prendido) {
		digitalWrite(led,HIGH);
		onoff = true;
		EST = pulso;
	}
//----------------------------------------------------- apagado ---
    if (EST == apagado) {
		digitalWrite(led, LOW);
        onoff = false;
		EST = pulso;
	}
//------------------------------------------------------- pulso ---
	if (EST == pulso){
		if (pulsar == true && bandera == false){
			if (onoff) EST = apagado;
			else EST = prendido;
			bandera = true;
		} else if (!pulsar) bandera = false;
	}
}

enum LEC
{
	config,
    conteo,
    muestreo,
    retorno
};

#define CICLO 5 // cada cuanto se leera el boton

/**
 * @brief Lee pulsador y devuelve sin rebote.
 * muestro del mismo cada CICLOS ms.
 * 
 * @param pull Pin del pulsador
 * @return true 
 * @return false 
 */
bool AntiRebotePulso(char pull)
{
	static char LEC = config;

	static uint8_t lectura = 0x00;  // igual a 0b00000000
	static int ciclo = 0;
	static bool valorDevuelto = false;
	
	static bool cambio = false, anterior_cam = false;
//----------------------------------------------------- config ----
	if (LEC == config){
		pinMode(pull, INPUT_PULLUP);
		digitalWrite(pull, HIGH);
		LEC = conteo;
	}
//----------------------------------------------------- conteo -----
	if (LEC == conteo && ciclo > CICLO) LEC = muestreo;
	if (LEC == conteo) {
		ciclo++;
		LEC = retorno;
	}
//----------------------------------------------------- muestreo ---
	if (LEC == muestreo)
	{
		lectura = lectura << 1;  // Mover de lugar el bit
		if (digitalRead(pull) == 0){
			lectura = lectura | 1;
		}
		if(lectura == 0){
			cambio = false;
		}
		if(lectura == 0xFF){  // otra forma de poner 0b11111111
			cambio = true;
		}
		LEC = retorno;
		anterior_cam = cambio;
		ciclo = 0;
	}
//----------------------------------------------------- retorno ----
	if (LEC == retorno){
		if (cambio){
			LEC = conteo;
			return true;
		}
		if (!cambio){
			LEC = conteo;
			return false;
		}
	}
	
}
