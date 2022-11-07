// #include <Arduino.h>

#define UNVALOR 25
#define LIMITE_INF 10
#define LIMITE_SUP 500
int frecuencia = 250;
typedef enum estado
{
  pulso,
  valorFinal
} ESTADO;
int menosMas(bool plMenos, bool plMas, int valor, int moreOrLess, int limInferior, int limSuperior);

#define LED_1 7
typedef enum onoff
{
  inicial,
  prendido,
  apagado
} ONOFF;
void maquinaFrec(char ledPin, int tiempoT);

#define PUL_1 8
#define PUL_2 9
typedef enum pull
{
	config,
  conteo,
  muestreo,
  retorno
} PULL;
bool AntiRebotePulso_1(char pulsador);
bool AntiRebotePulso_2(char pulsador);

void setup() {}

void loop() {

  bool pulsador_1 = AntiRebotePulso_1(PUL_1);
  bool pulsador_2 = AntiRebotePulso_2(PUL_2);

  frecuencia = menosMas(pulsador_1, pulsador_2, frecuencia, UNVALOR, LIMITE_INF, LIMITE_SUP);

  maquinaFrec(LED_1, frecuencia);

  delay(1);
}

/**
 * @brief Lee dos pulsadores (bool) los cuales aumentaran o disminuiran un "valor" (int)
 * cada "moreOrLess" (int). Reotrnando un entero (int).
 * 
 * @param plMenos Pulsador para menos
 * @param plMas Pulsador para mas
 * @param valor Valor inicial de disminucion
 * @param moreLess Cuanto mas y menos
 * @param limInferior Limite de disminución
 * @param limSuperior Limite de aumento
 * @return int 
 */
int menosMas(bool plMenos, bool plMas, int valor, int moreOrLess, int limInferior, int limSuperior)                                            //control pulsador 2
{
  static ESTADO est = pulso;
  static bool bandera_1 = false;
  static bool bandera_2 = false;
  static int variable = valor;
//------------------------------------------------------- pulso ---
  if (est == pulso) {
    /* Pulsa, plmenos disminulle "moreOrLess" */
    if (plMenos == true && bandera_1 == false) {
      variable += moreOrLess;
      if (variable >= limSuperior) variable = limSuperior;
      bandera_1 = true;
    } else if (!plMenos) bandera_1 = false;
    /* Pulsa, plmas aumenta "moreOrLess"      */
    if (plMas == true && bandera_2 == false) {
      variable -= moreOrLess;
      if (variable <= limInferior) variable = limInferior;
      bandera_2 = true;
    } else if (!plMas) bandera_2 = false;
    /* Reseteammos el estado a valorFinal */
    est = valorFinal;
  }
//------------------------------------------------- valorFinal ---
  if (est == valorFinal){
    est = pulso;
    return variable;
  }
}

/**
 * @brief Controla la Frecuencia del led.
 * Prende apaga un led con periodos ton y off iguales de valor "frecuencia".
 * 
 * @param led Pin del led
 * @param tiempoT Tiempo de ton y toff
 */
void maquinaFrec (char led, int tiempoT)     // CONTROL FRECUENCIA
{
  static ONOFF onoff = inicial;
  static int contador = tiempoT;
  //----------------------------------------------------- inicial ---
  if (onoff == inicial)
  {
    pinMode(led, OUTPUT);
    contador = tiempoT;
    onoff = prendido;
    digitalWrite(led, HIGH);
  }
  //----------------------------------------------------- prendido ---
  if (onoff == prendido && contador <= 0)
  {
    digitalWrite(led, LOW);
    contador = tiempoT;
    onoff = apagado;
  }
  if (onoff == prendido) contador--;
  //----------------------------------------------------- apagado ---
  if (onoff == apagado && contador > 0)
  {
    digitalWrite(led, HIGH);
    contador = tiempoT;
    onoff = prendido;
  }
  if (onoff == prendido) contador--;
}

#define CICLO 5 // cada cuanto se leera el boton

/**
 * @brief Antirebote de un pulsador. Retorna pulso sin rebote con true y false 
 * 
 * @param pulsador Pin del pulsador
 * @return true Pulsando
 * @return false Sin pulsar
 */
bool AntiRebotePulso_1(char pulsador)
{
  static PULL pull_1 = config;

  static uint8_t lectura = 0x00;  // igual a 0b00000000
  static int ciclo = 0;

  static bool cambio = false;
  //---------------------------------------------------- config ----
	if (pull_1 == config){
		pinMode(pulsador, INPUT_PULLUP);
		digitalWrite(pulsador, HIGH);
		pull_1 = conteo;
	}
//----------------------------------------------------- conteo -----
	if (pull_1 == conteo && ciclo > CICLO) pull_1 = muestreo;
	if (pull_1 == conteo) {
		ciclo++;
		pull_1 = retorno;
	}
//----------------------------------------------------- muestreo ---
	if (pull_1 == muestreo)
	{
		lectura = lectura << 1;  // Mover de lugar el bit
		if (digitalRead(pulsador) == 0){
			lectura = lectura | 1;
		}
		if(lectura == 0){
			cambio = false;
		}
		if(lectura == 0xFF){  // otra forma de poner 0b11111111
			cambio = true;
		}
		pull_1 = retorno;
		ciclo = 0;
	}
//----------------------------------------------------- retorno ----
	if (pull_1 == retorno){
		if (cambio){
			pull_1 = conteo;
			return true;
		}
		if (!cambio){
			pull_1 = conteo;
			return false;
		}
	}
}

bool AntiRebotePulso_2(char pulsador)
{
  static PULL pull_2 = config;

  static uint8_t lectura = 0x00;  // igual a 0b00000000
  static int ciclo = 0;

  static bool cambio = false;
  //----------------------------------------------------- config ----
	if (pull_2 == config){
		pinMode(pulsador, INPUT_PULLUP);
		digitalWrite(pulsador, HIGH);
		pull_2 = conteo;
	}
//----------------------------------------------------- conteo -----
	if (pull_2 == conteo && ciclo > CICLO) pull_2 = muestreo;
	if (pull_2 == conteo) {
		ciclo++;
		pull_2 = retorno;
	}
//----------------------------------------------------- muestreo ---
	if (pull_2 == muestreo)
	{
		lectura = lectura << 1;  // Mover de lugar el bit
		if (digitalRead(pulsador) == 0){
			lectura = lectura | 1;
		}
		if(lectura == 0){
			cambio = false;
		}
		if(lectura == 0xFF){  // otra forma de poner 0b11111111
			cambio = true;
		}
		pull_2 = retorno;
		ciclo = 0;
	}
//----------------------------------------------------- retorno ----
	if (pull_2 == retorno){
		if (cambio){
			pull_2 = conteo;
			return true;
		}
		if (!cambio){
			pull_2 = conteo;
			return false;
		}
	}
}