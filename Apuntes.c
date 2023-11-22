#define _CRT_SECURE_NO_WARNINGS

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
	char* respuestas[1000];

	// 
	int fileCount = listFiles(respuestas, directoryPath);
	if (fileCount < 0) return 1;

	setlocale(LC_CTYPE, "es_ES.UTF-8");
	srand(time(NULL));

	struct Apuntes nuevos[] =
	{
		{1, 1, 30}
	};

	char palabras[][20] = { "CASA" };

	int flujo = 0;
	do
	{
		FILE* archivo = fopen("./Datos/CASA.TXT", "r");
		if (archivo == NULL)
		{
			perror("Error al abrir el archivo");
			return 1;
		}

		int numeroAleatorio = (rand() % fileCount);
		int numeroDeLinea = 0;

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

int listFiles(char* filenames[], const char* directoryPath) {
	DIR* d = opendir(directoryPath);
	if (d == NULL) {
		perror("opendir failed");
		return -1;
	}

	struct dirent* dir;
	int count = 0;

	while ((dir = readdir(d)) != NULL) {
		if (dir->d_type == DT_REG) {
			filenames[count] = _strdup(dir->d_name); // Store filename
			count++;
		}
	}
	closedir(d);
	return count;
}