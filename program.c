#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
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
	const char* directoryPath = "./Datos";

	// Aqui guardaremos los nombres. Si son muchos pues habria que manejar la excepcion aqui.
	char* respuestas[1000];

	int fileCount = listFiles(respuestas, directoryPath);
	if (fileCount < 0) return 1;

	// Esta funcion permite definir la localizacion para determinar si tiene characteres especiales, es util aqui porque usamos ASCII.
	setlocale(LC_CTYPE, "es_ES.UTF-8");
	srand(time(NULL));

	int flujo = 0;
	int puntos = 0;
	int fallos = 0;

	printf("Bienvenido al Juego de Adivinanzas ASCII\n");
	printf("-----------------------------------------\n\n");

	do
	{
		printf("Corazones: %s\n", fallos == 0 ? "***" : fallos == 1 ? "**" : "*");
		printf("Cargando una nueva imagen...\n\n");

		// Dentro de todos los archivos, elegimos uno al azar y lo seleccionamos como imagen a mostrar.
		int numeroAleatorio = rand() % fileCount;
		char archivoPath[256];
		snprintf(archivoPath, sizeof(archivoPath), "./Datos/%s", respuestas[numeroAleatorio]);

		FILE* archivo = fopen(archivoPath, "r");
		if (archivo == NULL)
		{
			printf("Intentando abrir: %s\n", archivoPath);
			perror("Error al abrir el archivo");
			return 1;
		}

		char linea[512];
		while (fgets(linea, sizeof(linea), archivo) != NULL)
		{
			printf("%s", linea);
		}

		fclose(archivo);

		printf("\n¿Qué imagen se muestra? (Ingrese su respuesta): ");

		char respuestaUsuario[100];

		// Obtenemos el nombre de la imagen que se mostro y la guardamos para que sea la respuesta correcta.
		char respuestaCorrecta[100];
		strcpy(respuestaCorrecta, getBaseName(respuestas[numeroAleatorio]));

		scanf("%99s", respuestaUsuario);

		if (strcmp(respuestaCorrecta, respuestaUsuario) == 0)
		{
			puntos++;
			printf("¡Correcto! Puntos actuales: %d\n\n", puntos);
		}
		else {
			fallos++;
			printf("Incorrecto. Quedan %d corazones.\n", 3 - fallos);
			printf("Corazones: %s\n", fallos == 0 ? "***" : fallos == 1 ? "**" : "*");

			if (fallos == 3) {
				printf("¡Has perdido! Puntos acumulados: %d\n", puntos);
				printf("¿Deseas jugar de nuevo? [Sí = 1, No = 0]: ");
				scanf("%d", &flujo);
				if (flujo == 1) {
					fallos = 0; // Reiniciar los fallos si el usuario quiere jugar de nuevo
					puntos = 0; // Reiniciar los puntos
				}
				else {
					printf("\nGracias por jugar. ¡Hasta la próxima!\n");
					break;
				}
			}
		}

		if (fallos < 3) {
			printf("¿Continuar jugando? [Sí = 1, No = cualquier otro número]: ");
			scanf("%d", &flujo);
		}

	} while (flujo == 1);

	// Liberar la memoria de los nombres de archivo
	printf("\nFin del juego. Puntuación final: %d puntos.\n", puntos);

	for (int i = 0; i < fileCount; i++)
	{
		free(respuestas[i]);
	}

	return 0;
}