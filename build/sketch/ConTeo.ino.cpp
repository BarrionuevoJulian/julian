#line 1 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\ConTeo.ino"
#line 1 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\ConTeo.ino"
#include <Arduino.h>
#define PUL 9

enum MEF_AR // enum anti-rebote
{
  inicial,
  check,
  out

};

enum MEF_EST
{
  inicio,
  uno,
  tog,
  cero
};
#line 24 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\ConTeo.ino"
void setup();
#line 29 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\ConTeo.ino"
void loop();
#line 34 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_2.ino"
void mef(char led, bool pulsar);
#line 101 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_5.ino"
void maquinaFrec(char led, int tiempoT);
#line 53 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_6.ino"
void brilloLeds(char led ,int brillo );
#line 19 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\ConTeo.ino"

bool anti_rebote(int puerto); // Declaracion funciones
bool detector_flanco(bool anti);
unsigned long Clock_function();

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(7, anti_rebote(PUL));
  Serial.print(detector_flanco(anti_rebote(PUL)));
}

bool anti_rebote(int puerto)
{
  static char est = inicial;
  int TIEMPO = Clock_function(); // pido el tiempo a Clock_function
  int pulsador = puerto;
  static int Memoria = 0;
  static bool estado_ret = 1;
  int muestreo = 10; // determina la frecuencia de muestreo del pulsador

  if (est == inicial) // estado inicial MEf anti-rebote
  {
    pinMode(pulsador, INPUT_PULLUP);
    est = check;
  }
  if (est == check) // leo el estado del pulsador cada "Muestreo"
  {
    if (TIEMPO > Memoria)
    {
      Memoria = (TIEMPO + muestreo);
      estado_ret = digitalRead(pulsador);
    }
    est = out;
  }
  if (est == out) // devuelvo la lectura del pulsador
  {
    est = check;
    return estado_ret;
  }
}

bool detector_flanco(bool anti)
{
  static char est = inicio;
  static bool estado_mem = 1;
  static bool dev = 0;
  bool estado = anti;
  if (est == inicio)
  {
    est = uno;
  }

  if (est == uno)
  {
    if (estado_mem != estado)
    {
      est = tog;
      estado_mem = 0;
    }
  }
  if (est==tog)
  {
      dev = !dev;
      est = cero;
  }
  
  if (est == cero)
  {
    if (estado_mem != estado)
    {
      est = uno;
      estado_mem = 1;
    }
  }

  return dev;
}

unsigned long Clock_function() // aumento el clock cada 0,01s
{
  static unsigned long Clock;
  delay(10);
  Clock++;
  return Clock;
}
#line 1 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_1.ino"
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

#line 1 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_2.ino"
// Maquina de estado 2

#include <Arduino.h>
#define LED 2 //LED_BUILTIN
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
	if (EST == pulso && pulsar && !bandera && onoff) {
		 EST == apagado;
		 bandera = true;
	}
	if (EST == pulso && pulsar && !bandera && !onoff) {
		 EST == prendido;
		 bandera = true;
	}
	if (EST == pulso && !pulsar) bandera = false;
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

#line 1 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_3.ino"
#include <Arduino.h>
#define LED_1 2
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
    brilloLeds_1(LED_1, 0);
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
//----------------------------------------------------- inicial ---
    if (est_1 == inicial){
        pinMode(led, OUTPUT);
		digitalWrite(led, prendido);
        est_1 = prendido;
    }
//----------------------------------------------------- prendido --
    if (est_1 == prendido){
        // si la bandera es verdadera y contador mayor igual a parada
        if(contador >= brillo){
            digitalWrite(led, LOW);
			est_1 = apagado;
		}
	}
//----------------------------------------------------- apagado ---
	if (est_1 == apagado){
		// si la bandera es false y contador menor a parada
		if (contador < brillo){
			digitalWrite(led, HIGH);
			est_1 = prendido;
		}
	}
    // contador vuelve a resetear el periodo
    contador++;
    if(contador > 9) contador = 0;
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
	//----------------------------------------------------- inicial ---
	if (est_2 == inicial){
		pinMode(led, OUTPUT);
		digitalWrite(led, prendido);
		est_2 = prendido;
	}
	//----------------------------------------------------- prendido --
	if (est_2 == prendido){
		// si la bandera es verdadera y contador mayor igual a parada
		if(contador >= brillo){
			digitalWrite(led, LOW);
			est_2 = apagado;
		}
	}
	//----------------------------------------------------- apagado ---
	if (est_2 == apagado){
		// si la bandera es false y contador menor a parada
		if (contador < brillo){
			digitalWrite(led, HIGH);
			est_2 = prendido;
		}
	}
	// contador vuelve a resetear el periodo
	contador++;
	if(contador > 9) contador = 0;
}


#line 1 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_4.ino"
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
#line 1 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_5.ino"
/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

// #include <Arduino.h>

#define UNVALOR 200
#define LIMITE_INF 0
#define LIMITE_SUP 1000
int frecuencia = 500;
enum ESTADO 
{
  pulso,
  valorFinal
};
int menosMas(bool plMenos, bool plMas, int valor, int moreOrLess, int limInferior, int limSuperior);

#define LED_1 2
enum ONOFF
{
  inicial,
  prendido,
  apagado,
};
void maquinaFrec(char ledPin, int tiempoT);

#define PUL_1 8
#define PUL_2 9
enum PULL
{
	config,
  conteo,
  muestreo,
  retorno
};
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
  static char est = pulso;
  static bool bandera_1 = false;
  static bool bandera_2 = false;
  int variable = valor;
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
  static char onoff = inicial;
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
  if (onoff == apagado && contador <= 0)
  {
    digitalWrite(led, HIGH);
    contador = tiempoT;
    onoff = inicial;
  }
  if (onoff == apagado) contador--;
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
  static char pull_1 = config;

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
  static char pull_2 = config;

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

#line 1 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\Ej_6.ino"
#define LED 7
enum BRILLO
{
    inicial,
    prendido,
	apagado
};
void brilloLeds(char led, int brillo);

#define UNVALOR 10
#define LIMITE_INF 0
#define LIMITE_SUP 100
int frecuencia = 50;
enum ESTADO 
{
  pulso,
  valorFinal
};
int menosMas(bool plMenos, bool plMas, int valor, int moreOrLess, int limInferior, int limSuperior);

#define PUL_1 8
#define PUL_2 9
enum PULL
{
  config,
  conteo,
  muestreo,
  retorno
};
bool AntiRebotePulso_1(char pulsador);
bool AntiRebotePulso_2(char pulsador);

void setup() {}

void loop() {

  bool pulsador_1 = AntiRebotePulso_1(PUL_1);
  bool pulsador_2 = AntiRebotePulso_2(PUL_2);

  frecuencia = menosMas(pulsador_1, pulsador_2, frecuencia, UNVALOR, LIMITE_INF, LIMITE_SUP);

  brilloLeds (LED, frecuencia);

  delay(1);
}

/**
 * @brief Brillo de un led en PWM con periodo de 20 m.
 * 
 * @param led Pin del led.
 * @param brillo escala de brillo de 0 a 10.
 */
void brilloLeds(char led ,int brillo )
{
    static BRILLO est_1 = inicial;
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
  static char est = pulso;
  static bool bandera_1 = false;
  static bool bandera_2 = false;
  int variable = valor;
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
  static char pull_1 = config;

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
  static char pull_2 = config;

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
#line 1 "c:\\Users\\ariel\\Desktop\\Otto Krause\\Embebidos\\Programación\\julian\\EjerciciosIno\\Prueva.ino"
#include <Arduino.h>

#define MUESTRA 70 // en ms
#define PUL1 8 // en ms
#define PUL2 9

enum Antirebote{
    config,
    muestreo,
    ret,
};

bool AntiRebote_1 (char pulsador);
bool AntiRebote_2 (char pulsador);

enum ESTADO 
{
  pulso,
  limite,
  valorFinal
};
int menosMas(bool plMenos, bool plMas, int valor, int moreOrLess, int limInferior, int limSuperior);

void setup(){
    Serial.begin(9600);
}

int algo = 10;

void loop()
{
  bool pul1 = AntiRebote_1 (PUL1);
  bool pul2 = AntiRebote_1 (PUL2);

  algo = menosMas(pul1,pul2,algo,1,0,15);

  Serial.println(algo);
  delay(1); 
}

bool AntiRebote_1 (char pulsador){
    static char pull_est = config;
    static int muestra = MUESTRA;
    static bool retorno = 1;

    if(pull_est == config){
        pinMode(pulsador, INPUT_PULLUP);
		digitalWrite(pulsador, HIGH);
		pull_est = muestreo;
    }
    if(pull_est == muestreo && muestra <= 0){
        retorno = digitalRead(pulsador);
        muestra = MUESTRA;
    }
    if(pull_est == muestreo) {
        muestra--;
        pull_est = ret;
    }
    if (pull_est == ret){
        pull_est = muestreo;
        return retorno;
    }
}

bool AntiRebote_2 (char pulsador){
    static char pull_est = config;
    static int muestra = MUESTRA;
    static bool retorno = 1;

    if(pull_est == config){
        pinMode(pulsador, INPUT_PULLUP);
		digitalWrite(pulsador, HIGH);
		pull_est = muestreo;
    }
    if(pull_est == muestreo && muestra <= 0){
        retorno = digitalRead(pulsador);
        muestra = MUESTRA;
    }
    if(pull_est == muestreo) {
        muestra--;
        pull_est = ret;
    }
    if (pull_est == ret){
        pull_est = muestreo;
        return retorno;
    }
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
  static char est = pulso;
  static bool bandera_1 = false;
  static bool bandera_2 = false;
  int variable = valor;
//------------------------------------------------------- pulso ---
  if (est == pulso && plMas == true && bandera_1 == false) {
    /* Pulsa, plmenos disminulle "moreOrLess" */
      variable += moreOrLess;
      bandera_1 = true;
      est = limite;
  }
  if (est == pulso && plMenos == true && bandera_2 == false) {
    /* Pulsa, plmenos disminulle "moreOrLess" */
      variable -= moreOrLess;
      bandera_2 = true;
      est = limite;
  }
  if (est == limite && plMas == true && variable >= limSuperior) {
      variable = limSuperior;
  }
  if (est == limite && plMenos == true && variable <= limInferior) {
      variable = limInferior;
  }
  if (est == limite && plMas == false) {
    bandera_1 = false;
  }
  if (est == limite && plMenos == false) {
    bandera_2 = false;
  }
  if (est == limite){
    est = valorFinal;
  }
  if (est == valorFinal){
    est = pulso;
    return variable;
  }  
}
