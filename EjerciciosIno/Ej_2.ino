// Maquina de estado 2

#include <Arduino.h>
#define LED LED_BUILTIN
#define PULSADOR 3 // pin 3

uint8_t lectura = 0xFF; // igual a 0b11111111
int ciclo = 0;

#define CICLO 7 // cada cuanto se leera el boton

enum ESTADO
{
    inicial,
    prendido,
    apagado,
};

/**
 * @brief Maquina de estado para cambiar estado de prendido a apagado
 * 
 * @param led Pin del led
 * @param repite Tiempo pren/apagado
 */
void mef(char led, int pulsador);

void setup(){}

void loop()
{
	bool pulsador = lectura (PULSADOR);
    mef(LED, pulsador);
    delay(1);
}

void mef(char led, bool cambio)
{
    static char ESTADO = inicial;
//----------------------------------------------------- inicial ---
    if (ESTADO == inicial)
    {
        pinMode(led, OUTPUT);
        ESTADO = apagado;
        digitalWrite(led, HIGH);
    }
//----------------------------------------------------- prendido ---
    if (ESTADO == prendido) {
		digitalWrite(led,HIGH);
	}
//----------------------------------------------------- apagado ---
    if (ESTADO == apagado) {
		 digitalWrite(led, LOW);
	}
//-----------------------------------------------------------------
	if (cambio) ESTADO = prendido;
	else ESTADO = apagado; 
}

bool lectura(char pulsador)
{
	static bool cambio = false, anterior_cam = false;
	static bool fin = false;
	static bool est = false;
	
	if (ciclo > CICLO){  //Lecturas del pulsador
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
			fin = true;
		}
		anterior_cam = cambio;
		ciclo = 0;
	}
	
	if (fin){
		fin = false;
		return est =! est;
	}
}
