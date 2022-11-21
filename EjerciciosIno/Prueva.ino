// #include <Arduino.h>
#define LED 4
#define PULSADOR 8
#define MUESTREO 10

enum GENERAL
{
    config,
    cero,
    uno
};

bool MEFantirrebote(char pull);
bool MEFinvertir(bool pulsador, bool comenzar);

bool PULSAR, Led_1;

void setup()
{
    // <>
    Serial.begin(9600);
}
// the loop function runs over and over again forever
void loop()
{
  PULSAR = MEFantirrebote(PULSADOR);
  Led_1 = MEFinvertir(PULSAR, false);
  // Serial.println(Led_1);
  digitalWrite(LED, Led_1);
  delay(1);
}
/**
 * @brief Antirrebote, toma dos valores continuos cada 10 ms.
 * Con el cual cambia de estado si ambos valores son iguales.
 * 
 * @param pull Pin pulsador
 * @return true 
 * @return false 
 */
bool MEFantirrebote(char pull)
{
  static char est_re = config;
  static int conteo = MUESTREO;
  static bool ant_pul = true;
  static bool est_pul = true;
  static bool valor = true;
//------------------------------------------------ config -
  if(est_re == config){
    pinMode(pull,INPUT_PULLUP);
    digitalWrite(pull,HIGH);
    est_re = uno;
  }
//--------------------------------------------------- uno -
  if(est_re == uno && conteo <= 0){ 
    est_pul = digitalRead(pull);
  }
  /* Si est. anterior es igual a est. actual ( LOW ) */
  if(est_re == uno && !ant_pul && !est_pul){ 
    est_re = cero;
  }
  if(est_re == uno && conteo <= 0){
    ant_pul = est_pul;
  }
//--------------------------------------------------- cero -
  if(est_re == cero && conteo <= 0){
    est_pul = digitalRead(pull);
  }
  /* Si est. anterior es igual a est. actual ( HIGH ) */
  if(est_re == cero && ant_pul && est_pul){
    est_re = uno;
  }
  if(est_re == cero && conteo <= 0){
    ant_pul = est_pul;
  }
//-------------------------------------------------------------
  
/* Nesesario al final para devolver valor a la función */
  if(est_re == uno){
    conteo--;
    return true;
  }
  if(est_re == cero){
    conteo--;
    return false;
  }
}

/**
 * @brief Inversor, toglea el valor a su salida. 
 * Si "pulsador" da cero logico, realiza la accion de cambio.
 * 
 * @param pulsador Pin de pulsador 
 * @param comenzar Nivel logico de inicio
 * @return true 
 * @return false 
 */
bool MEFinvertir(bool pulsador, bool comenzar)
{
  static char est_inv = config;
  static bool bandera;
//--------------------------------------------------- config -
  if(est_inv == config && comenzar){
    bandera = true;
    est_inv = uno;
  }
  if(est_inv == config && !comenzar){
    bandera = true;
    est_inv = cero;
  }
//------------------------------------------------------ uno -
  /* Si presiono y bandera, cambaiamos de estado a cero */
  if(est_inv == uno && !pulsador && bandera){
    bandera = false; // encargado de guardar que esta presionado pulsador
    est_inv = cero;
  }
  /* Si se dejo de presionar, se resetea bandera */
  if(est_inv == uno && pulsador) bandera = true;
//------------------------------------------------------ cero -
  /* Si presiono y bandera, cambaiamos de estado a uno */
  if(est_inv == cero && !pulsador && bandera){
    bandera = false; // encargado de guardar que esta presionado pulsador
    est_inv = uno;
  }
  /* Si se dejo de presionar, se resetea bandera */
  if(est_inv == cero && pulsador) bandera = true; 
//-------------------------------------------------------------

/* Nesesario al final para devolver valor a la función */
  if(est_inv == uno)  return true;
  if(est_inv == cero) return false;
}

////////////////////////////////////////////////////////

/* https://github.com/BarrionuevoJulian/julian.git */