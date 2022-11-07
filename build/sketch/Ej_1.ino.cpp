#line 1 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_1.ino"
#line 1 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_1.ino"
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

#line 19 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_1.ino"
void setup();
#line 24 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_1.ino"
void loop();
#line 34 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_2.ino"
void mef(char led, bool pulsar);
#line 33 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_3.ino"
void brilloLeds( char led , int brillo );
#line 98 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_5.ino"
void maquinaFrec(char led, int tiempoT);
#line 19 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_1.ino"
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

void mef(char led, int repite)
{
    static int contador = repite;
    static char ESTADO = inicial;

//----------------------------------------------------- inicial ---
    if (ESTADO == inicial)
    {
        pinMode(led, OUTPUT);
        contador = repite;
        ESTADO = prendido;
        digitalWrite(led, HIGH);
    }
//----------------------------------------------------- prendido ---
    if (ESTADO == prendido && contador <= 0)
    {
        digitalWrite(led, LOW);
        contador = repite;
        ESTADO = apagado;
    }
    if (ESTADO == prendido)contador--;
//----------------------------------------------------- apagado ---
    if (ESTADO == apagado && contador <= 0)
    {
        digitalWrite(led, HIGH);
        contador = repite;
        ESTADO = prendido;
    }
    if (ESTADO == prendido)contador--;
}

//////////////////////////////////////////////////////

// git add
// git commit -m
// git status -s
// git log --oneline
// git push // para subir el archivo a github
// git pull // traer los cambios de github a local

// git tag (nombre tag) -m "(info)"
// git push --tags // para guardar la version/tag a github

// git clone // para clonar

// git branch "(nombre de nueva rama)"
// git branch // para ver el estado de las ramas
// git branch -d (n de la rama a eliminar)
// git checkout (n de la rama a ir)

// git merge (n de la rama a fusionar) // desde master se hace 

/* https://github.com/BarrionuevoJulian/julian.git */

#line 1 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_2.ino"
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

#line 1 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_3.ino"
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

void setup()
{
    
}

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
void brilloLeds( char led , int brillo )
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
void brilloLeds( char led , int brillo )
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

#line 1 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_4.ino"
#include <Arduino.h>
#define LED_1 2
#define LED_2 3
#define LED_3 4

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
    mef(LED_1, 500);
    mef(LED_2,  50);
    mef(LED_3,   5);
    delay(1);
}

void mef(char led, int repite)
{
    static int contador = repite;
    static char ESTADO = inicial;
//----------------------------------------------------- inicial ---
    if (ESTADO == inicial)
    {
        pinMode(led, OUTPUT);
        contador = repite;
        ESTADO = prendido;
        digitalWrite(led, HIGH);
    }
//----------------------------------------------------- prendido ---
    if (ESTADO == prendido && contador <= 0)
    {
        digitalWrite(led, LOW);
        contador = repite;
        ESTADO = apagado;
    }
    if (ESTADO == prendido)contador--;
//----------------------------------------------------- apagado ---
    if (ESTADO == apagado && contador <= 0)
    {
        digitalWrite(led, HIGH);
        contador = repite;
        ESTADO = prendido;
    }
    if (ESTADO == prendido)contador--;
}
#line 1 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_5.ino"
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
  //----------------------------------------------------- config ----
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
#line 1 "c:\\Users\\ariel\\Desktop\\Nueva carpeta\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_6.ino"


void setup()
{
    
}

void loop()
{
    
}
