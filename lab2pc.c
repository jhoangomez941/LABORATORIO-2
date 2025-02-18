#include <stdio.h>
#include <sys/time.h>

struct timeval stop, start;
unsigned long tiempo;  // Tiempo medido en milisegundos
unsigned long clave = 0x3CF88FB7;  // Clave fija
unsigned long tokenCalculado = 0;
unsigned int tokenIngresado = 0;  // Ahora solo 2 dígitos (1 byte)

void imprimeCuadrado();

int main() {
    char continuar = 's';

    printf("Pulse ENTER para sincronizar...\n");
    getchar();  // Esperar que el usuario presione ENTER

    //  Mostrar recuadro blanco inmediatamente
    imprimeCuadrado();

    //  Iniciar conteo de tiempo
    gettimeofday(&start, NULL);

    while (continuar == 's' || continuar == 'S') {
        printf("\nIngrese los ULTIMOS 2 DIGITOS del TOKEN : ");
        scanf("%2x", &tokenIngresado);  // Leer solo 2 dígitos en formato hexadecimal

        //  Obtener tiempo actual
        gettimeofday(&stop, NULL);

        //  Calcular el tiempo transcurrido en milisegundos
        tiempo = ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) / 1000;
        printf("\nTiempo real: %lu ms\n", tiempo);

        //  Redondear el tiempo a múltiplos de 30,000 ms (30s)
        tiempo = (tiempo / 30000) * 30000;

        //  Aplicar XOR entre tiempo y clave para calcular el token esperado
        tokenCalculado = tiempo ^ clave;

        //  EXTRAER LOS ÚLTIMOS 2 DÍGITOS DEL TOKEN
        unsigned int tokenEsperado = tokenCalculado & 0xFF;

        //  Mostrar datos
        printf("\nTiempo redondeado: %lu ms\n", tiempo);
        printf("Tiempo en hex: %08lX\n", tiempo);
        printf("Clave en hex:  %08lX\n", clave);
        printf("Token completo: %08lX\n", tokenCalculado);
        printf("ultimos 2 digitos esperados: %02X\n", tokenEsperado);
        printf("Token ingresado: %02X\n", tokenIngresado);

        //  Verificar si el TOKEN es correcto
        if (tokenIngresado == tokenEsperado) {
            printf("\n TOKEN CORRECTO (Valido por 30s)\n");
        } else {
            printf("\n TOKEN INCORRECTO\n");
        }

        // Preguntar si desea ingresar otro token
        printf("\nDesea ingresar otro token (s/n): ");
        scanf(" %c", &continuar);  // Nota el espacio antes de %c para consumir el newline anterior
    }

    return 0;
}

// Función para imprimir el recuadro blanco
void imprimeCuadrado() {
    unsigned char dato = 219;
    for (int i = 1; i < 289; i++) {
        printf("%c", dato);
        if ((i % 24) == 0) printf("\n");
    }
}
