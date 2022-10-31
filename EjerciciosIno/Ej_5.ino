
// #include <Arduino.h>

#define LED_1 7
#define PUL_1 8
#define PUL_2 9

enum EST_1
{
  inicial_1,
  mas_1,
  menos_1,
  pulso_1
};

enum EST_2
{
  inicial_2,
  mas_2,
  menos_2,
  pulso_2
};

enum ESTADO
{
  inicial_3,
  prendido_3,
  apagado_3
};

void mef_PUL_1(int pulsador); //controla pulsador
void mef_PUL_2(int pulsador); //controla pulsador
void mef_2(char led, int repite); //controla la frecuencia
bool AntiRebotePulso(char pull);
bool AntiRebotePulso_1(char pull);

int frecuencia = 1000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  bool pulsador_1 = AntiRebotePulso (PUL_1);
  bool pulsador_2 = AntiRebotePulso_1 (PUL_2);
  // Serial.println(pulsador);
  mef_PUL_1(pulsador_1);
  mef_PUL_2(pulsador_2);
  mef_2(LED_1, frecuencia);
  delay(1);

}
void mef_PUL_1(bool pulsar)                                    //control pulsador 1
{
  static char EST_1 = inicial_1;
  static bool bandera = false;
  static bool onoff;
  //----------------------------------------------------- inicial ---
  if (EST_1 == inicial_1)
  {
    EST_1 = mas_1;
    onoff = true;
  }
  //----------------------------------------------------- prendido ---
  if (EST_1 == mas_1) {
    frecuencia = frecuencia + 100;
    onoff = true;
    EST_1 = pulso_1;
  }
  //----------------------------------------------------- apagado ---
  if (EST_1 == menos_1) {
    onoff = false;
    EST_1 = pulso_1;
  }
  //------------------------------------------------------- pulso ---
  if (EST_1 == pulso_1) {
    if (pulsar == true && bandera == false) {
      if (onoff)EST_1 = menos_1;
      else EST_1 = mas_1;
      bandera = true;
    } else if (!pulsar) bandera = false;
  }
}
void mef_PUL_2(bool pulsar)                                            //control pulsador 2
{
  static char EST_2 = inicial_2;
  static bool bandera = false;
  static bool onoff;
  //----------------------------------------------------- inicial ---
  if (EST_2 == inicial_2)
  {
    EST_2 = mas_2;
    onoff = true;
  }
  //----------------------------------------------------- prendido ---
  if (EST_2 == mas_2) {

    onoff = true;
    EST_2 = pulso_2;
  }
  //----------------------------------------------------- apagado ---
  if (EST_2 == menos_2) {
    frecuencia = frecuencia - 100;
    onoff = false;
    EST_2 = pulso_2;
  }
  //------------------------------------------------------- pulso ---
  if (EST_2 == pulso_2) {
    if (pulsar == true && bandera == false) {
      if (onoff)EST_2 = menos_2;
      else EST_2 = mas_2;
      bandera = true;
    } else if (!pulsar) bandera = false;
  }
}
void mef_2(char led, int repite)                                     //CONTROL FRECUENCIA
{
  static int contador = repite;
  static char ESTADO = inicial_3;

  //----------------------------------------------------- inicial ---
  if (ESTADO == inicial_3)
  {
    pinMode(led, OUTPUT);
    contador = repite;
    ESTADO = prendido_3;
    digitalWrite(led, HIGH);
  }
  //----------------------------------------------------- prendido ---
  if (ESTADO == prendido_3 && contador <= 0)
  {
    digitalWrite(led, LOW);
    contador = repite;
    ESTADO = apagado_3;
  }
  if (ESTADO == prendido_3)contador--;
  //----------------------------------------------------- apagado ---
  if (ESTADO == apagado_3 && contador > 0)
  {
    digitalWrite(led, HIGH);
    contador = repite;
    ESTADO = prendido_3;
  }
  if (ESTADO == prendido_3)contador--;
}

enum LEC_1                                                        //ANTIREBOTE PUL 1
{
  config,
  conteo,
  muestreo,
  retorno_true,
  retorno_false
};

#define CICLO 5 // cada cuanto se leera el boton

/**
   @brief Lee pulsador y devuelve sin rebote.
   muestro del mismo cada CICLOS ms.

   @param pull Pin del pulsador
   @return true
   @return false
*/
bool AntiRebotePulso(char pull)
{
  static char LEC_1 = config;

  static uint8_t lectura = 0x00;  // igual a 0b00000000
  static int ciclo = 0;
  static bool valorDevuelto = false;

  static bool cambio = false, anterior_cam = false;
  //----------------------------------------------------- config ----
  if (LEC_1 == config) {
    pinMode(pull, INPUT_PULLUP);
    digitalWrite(pull, HIGH);
    LEC_1 = conteo;
  }
  //----------------------------------------------------- conteo -----
  if (LEC_1 == conteo) ciclo++;
  if (LEC_1 == conteo && ciclo > CICLO) LEC_1 = muestreo;
  //----------------------------------------------------- muestreo ---
  if (LEC_1 == muestreo)
  {
    lectura = lectura << 1;  // Mover de lugar el bit
    if (digitalRead(pull) == 0) {
      lectura = lectura | 1;
    }
    if (lectura == 0) {
      cambio = false;
      LEC_1 = retorno_false;
    }
    if (lectura == 0xFF) { // otra forma de poner 0b11111111
      cambio = true;
      LEC_1 = retorno_true;
    }/*
    if(cambio > anterior_cam){
      LEC = retorno_true;
    }
    if(cambio < anterior_cam){
      LEC = retorno_false;
    }*/
    anterior_cam = cambio;
    ciclo = 0;
  }
  //----------------------------------------------------- retorno_true -
  if (LEC_1 == retorno_true) {
    LEC_1 = conteo;
    return valorDevuelto = true;
  }
  //---------------------------------------------------- retorno_false -
  if (LEC_1 == retorno_false) {
    LEC_1 = conteo;
    return valorDevuelto = false;
  }
}


enum LEC_2                                                                   //ANTIREBOTE PUL 2
{
  config,
  conteo,
  muestreo,
  retorno_true,
  retorno_false
};

#define CICLO 5 // cada cuanto se leera el boton

/**
   @brief Lee pulsador y devuelve sin rebote.
   muestro del mismo cada CICLOS ms.

   @param pull Pin del pulsador
   @return true
   @return false
*/
bool AntiRebotePulso(char pull)
{
  static char LEC_2     = config;

  static uint8_t lectura = 0x00;  // igual a 0b00000000
  static int ciclo = 0;
  static bool valorDevuelto = false;

  static bool cambio = false, anterior_cam = false;
  //----------------------------------------------------- config ----
  if (LEC_2     == config) {
    pinMode(pull, INPUT_PULLUP);
    digitalWrite(pull, HIGH);
    LEC_2     = conteo;
  }
  //----------------------------------------------------- conteo -----
  if (LEC_2     == conteo) ciclo++;
  if (LEC_2     == conteo && ciclo > CICLO) LEC_2     = muestreo;
  //----------------------------------------------------- muestreo ---
  if (LEC_2     == muestreo)
  {
    lectura = lectura << 1;  // Mover de lugar el bit
    if (digitalRead(pull) == 0) {
      lectura = lectura | 1;
    }
    if (lectura == 0) {
      cambio = false;
      LEC_2     = retorno_false;
    }
    if (lectura == 0xFF) { // otra forma de poner 0b11111111
      cambio = true;
      LEC_2     = retorno_true;
    }/*
    if(cambio > anterior_cam){
      LEC = retorno_true;
    }
    if(cambio < anterior_cam){
      LEC = retorno_false;
    }*/
    anterior_cam = cambio;
    ciclo = 0;
  }
  //----------------------------------------------------- retorno_true -
  if (LEC_2     == retorno_true) {
    LEC_2     = conteo;
    return valorDevuelto = true;
  }
  //---------------------------------------------------- retorno_false -
  if (LEC_2     == retorno_false) {
    LEC_2     = conteo;
    return valorDevuelto = false;
  }
}

// enum preguntar como mejorarlo el tema de no repetir muchos;