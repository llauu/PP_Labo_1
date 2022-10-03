
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mylib.h"


// Ingresos de datos -----------------------------------------------------------------
int getInt(int* pResultado, char* mensaje, char* mensajeError, int min, int max){
	int retorno;
	int numero;
	char buffer[4096];

	retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensaje != NULL && min < max){
		do{
			printf("%s", mensaje);
			scanf("%s", buffer);

			if(esNumerica(buffer)){
				numero = atoi(buffer);

				if(numero >= min && numero <= max){
					*pResultado = numero;
					retorno = 0;
				}
				else{
					printf("%s", mensajeError);
				}
			}
			else{
				printf("%s", mensajeError);
			}

		}while(retorno == -1);
	}

	return retorno;
}

int getFloat(float* pResultado, char* mensaje, char* mensajeError, float min, float max){
	int retorno;
	float numero;
	char buffer[4096];

	retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensaje != NULL && min < max){
		do{
			printf("%s", mensaje);
			scanf("%s", buffer);

			if(esNumerica(buffer)){
				numero = atof(buffer);

				if(numero >= min && numero <= max){
					*pResultado = numero;
					retorno = 0;
				}
				else{
					printf("%s", mensajeError);
				}
			}
			else{
				printf("%s", mensajeError);
			}

		}while(retorno == -1);
	}

	return retorno;
}

int getChar(char* pCaracter, char* mensaje, char* mensajeError, char min, char max){
	int retorno;
	char buffer;

	retorno = -1;

	if(pCaracter != NULL && mensaje != NULL && mensaje != NULL && min < max){
		do{
			printf("%s", mensaje);
			__fpurge(stdin);
			scanf("%c", &buffer);

			if(buffer >= min && buffer <= max){
				*pCaracter = buffer;
				retorno = 0;
			}
			else{
				printf("%s", mensajeError);
			}

		}while(retorno == -1);
	}

	return retorno;
}

int getString(char string[], int sizeString, char* mensaje, char* mensajeError){
	int retorno;
	char buffer[1024];

	retorno = -1;

	if(string != NULL && mensaje != NULL && mensaje != NULL && sizeString > 0){
		do{
			printf("%s", mensaje);
			__fpurge(stdin);
			scanf("%[^\n]", buffer); // El %[^\n] marca que va a leer hasta q detecte un salto de linea

			if(strlen(buffer) < sizeString){
				strcpy(string, buffer);
				retorno = 0;
			}
			else{
				printf("%s", mensajeError);
			}

		}while(retorno == -1);
	}

	return retorno;
}

int esNumerica(char* string){
    int retorno = 1;
    int i = 0;

    if(string[0] == '-'){
        i = 1;
    }

    for( ; string[i] != '\0'; i++){
        if(string[i] == '.')
        {
            if((string[i] > '9' || string[i] < '0') && (string[i] != '.')){
                retorno = 0;
                break;
            }
        } else
            {
                if((string[i] > '9' || string[i] < '0') && (string[i] != '.')){
                    retorno = 0;
                    break;
             }
        }

    }

    return retorno;
}

// Pasar todo un string a MAYUS
int StringUpper(char string[], int size){
	int retorno;

	retorno = -1;

	if(string != NULL && size > 0){
		for(int i = 0; i < size; i++){
			string[i] = toupper(string[i]);
		}

		retorno = 0;
	}

	return retorno;
}




















