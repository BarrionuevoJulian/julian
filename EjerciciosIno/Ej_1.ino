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
