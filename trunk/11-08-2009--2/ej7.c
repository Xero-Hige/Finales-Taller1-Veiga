/* 7)
Escriba un programa ANSI C que procese el archivo datos.bin. El procesamiento consiste en reemplazar las secuencias de bytes 0x2F,0x31,0x3A por 0x31,0x3A. Adicionalmente, las búsquedas deben reiniciarse 3 bytes antes del último byte reemplazado. */
#include <stdlib.h>
#include <stdio.h>

#define LEN 3

static char* patron = {0x2F, 0x31, 0x3A};
static char* reemplazo = {0x31, 0x3A};

bool hayMatch(char* buffer) {
	bool comparacion = true;
	int pos = 0;
	while (comparacion && pos < LEN) {
		comparacion = (*(patron + pos) == *(buffer + pos));
	}
	return comparacion;
}

int main(int argc, char** argv) {
	FILE* archivo = fopen("datos.bin", "rb+");
	if (!archivo)
		return 1;
	bool termine = false;
	char buffer[3];
	while (!termine) {
		fread(buffer, sizeof(char), 3, archivo);
		if (hayMatch(buffer)) {
			
		}
		termine = feof(archivo);
	}
	return 0;
}
