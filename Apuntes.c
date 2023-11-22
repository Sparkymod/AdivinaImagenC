#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <string.h>
struct Apuntes
{
    int numero;
    int inicio;
    int fin;
};

int main(void)
{
    setlocale(LC_CTYPE,"es_ES.UTF-8");
    srand(time(NULL));
    
    struct Apuntes nuevos[] =
        {
            {1, 1, 30},
            {2, 31, 60},
            {3, 61, 90},
            {4, 91, 120},
            {5, 121, 150},
            {6, 151, 180},
            {7, 181, 210},
            {8, 211, 240},
            {9, 241, 270},
            {10, 271, 300},
            {11, 301, 330},
            {12, 331, 360},
            {13, 361, 390},
            {14, 391, 420},
            {15, 421, 450},
            {16, 451, 480},
            {17, 481, 510},
            {18, 511, 540},
            {19, 541, 570},

        };
    char palabras[][20] = { "CASA", "TIBURON", "ARBOL", "GATO", "BARCO", "PASTEL", "MANOS", "PELOTA",
                           "MANZANA", "PIZZA", "MOTOCICLETA", "CARRO", "FLORES", "FANTASMA",
                           "GUITARRA", "ESTRELLA", "PEZ", "GALLO", "PELUCHE"};
     int x = (sizeof(nuevos) / sizeof(nuevos[0]));

    int flujo = 0;
    do
    {

        FILE *archivo = fopen("Img.txt", "r");
        if (archivo == NULL)
        {
            perror("Error al abrir el archivo");
            return 1;
        }

        int numeroAleatorio = (rand() % x);
        int numeroDeLinea = 0;

        printf("%s\n", palabras[numeroAleatorio]);
        char linea[512];

        while (fgets(linea, sizeof(linea), archivo) != NULL)
        {
            numeroDeLinea++;

            if (numeroDeLinea >= nuevos[numeroAleatorio].inicio && numeroDeLinea <= nuevos[numeroAleatorio].fin)
            {
                printf("%s", linea);
            }

            // Salir del bucle después de imprimir la línea final
            if (numeroDeLinea == nuevos[numeroAleatorio].fin)
            {
                break;
            }
        }

        printf("Si desea seguir jugando inserte un (1), de lo contrario otro numero: ");
        scanf("%d", &flujo);

        // Cerrar el archivo
        fclose(archivo);

    } while (flujo == 1);

    return 0;
}