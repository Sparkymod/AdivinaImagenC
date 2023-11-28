#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <locale.h>
#include <string.h>
// Lista los archivos a guarda los nombres en un arreglo.
int listFiles(char* filenames[], const char* directoryPath) {

	// Puntero que contiene el directorio especificado.
	DIR* d = opendir(directoryPath);
	if (d == NULL) {
		perror("opendir failed");
		return -1;
	}

	// esto es una estructura que define los campos de un archivo. 
	// Necesitamos el campo de nombre(d_name) y el tipo(d_type) que ya este lo contiene.
	struct dirent* dir;
	int count = 0;

	// Mientras tenga archivo la carpeta entonces guardara el nombre del archivo en la lista.
	// DT_REG es una constante en C que significa que es un archivo regular -> https://www.gnu.org/software/libc/manual/html_node/Directory-Entries.html3
	// Asi identificamos que lo que leemos es almenos un archivo y no una carpeta.
	// TODO: Por el momento no tiene manejo de excepciones, si ponemos diferente tipos de archivos que no sea TXT u otra carpeta.
	while ((dir = readdir(d)) != NULL) {
		if (dir->d_type == DT_REG) {
			filenames[count] = _strdup(dir->d_name);
			count++;
		}
	}

	closedir(d);
	return count;
}

// Esta funcion directamente obtienes el nombre del archivo
char* getBaseName(char* filename)
{
	// Este extrae el nombre de la ruta, delimitado con el ultimo / que aparezca, es decir, seria ruta/de/archivo.txt
	// seria archivo.txt
	char* base = strrchr(filename, '/');
	if (!base)
	{
		base = filename;
	}
	else
	{
		base++;
	}

	// En base al anterior, entonces sacamos lo que esta delante del primer punto(.) que encuentre.
	// Esto limita a que el nombre del archivo sea directo sin characteres especiales. 
	char* ext = strrchr(base, '.');
	if (ext)
	{
		*ext = '\0';
	}

	return base;
}

// Esta funcion hace la simulacion de un ToLower() de C#. 
// Convierte todo a minuscula para que se trate la respuesta como Case Insensitive.
void toLowerCase(char* str) {
	if (str == NULL) return;

	for (int i = 0; str[i]; i++) {
		str[i] = tolower((unsigned char)str[i]);
	}
}