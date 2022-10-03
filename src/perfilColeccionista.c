
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mylib.h"
#include "perfilColeccionista.h"
#include "perfilAdmin.h"


int perfilColeccionista(sAlbum miAlbum, sFigurita figuritas[], int cantFiguritas, sRepetida pilaRepetidas[], sEquipo equipos[], int cantEquipos){
	int opcion;
	int contadorFiguritas;
	int contadorSobres;
	int albumLleno;
	int cantSobresAlbumLleno;
	float precioPaquete;
	float dineroGastado;
	float dineroGastadoHastaAlbumLleno;
	int verificarRepetidas;

	contadorFiguritas = 0;
	contadorSobres = 0;
	albumLleno = 0;
	precioPaquete = 170;

	InicializarRepetidas(pilaRepetidas, figuritas, cantFiguritas);
	miAlbum = InicializarFiguritasAlbum(miAlbum, cantFiguritas);

	do{
		albumLleno = VerificarAlbumLleno(miAlbum, cantFiguritas);
		if(albumLleno == 1 && miAlbum.estado == VACIO){
			cantSobresAlbumLleno = contadorSobres;
			dineroGastadoHastaAlbumLleno = (float)precioPaquete * contadorSobres;
			printf("\nFELICITACIONES!! Completaste el album.");
			miAlbum.estado = LLENO;
		}

		printf("\n\n[Perfil Coleccionista]\n 1.Comprar un paquete de figuritas\n 2.Intercambiar figuritas\n 3.Informes\n 4.Salir\n");
		getInt(&opcion, "\nOpcion: ", "[ERROR] La opcion que ingreso no es correcta.", 1, 4);

		switch(opcion){
			case 1:// Comprar un paquete de figuritas random de 5 figuritas
				miAlbum = ComprarPaquete(miAlbum, pilaRepetidas, &contadorFiguritas, figuritas, cantFiguritas);
				contadorSobres++;

				dineroGastado = (float)precioPaquete * contadorSobres;
				break;

			case 2: // Intercambiar figuritas
				verificarRepetidas = VerificarSiHayRepetidas(pilaRepetidas, cantFiguritas);

				if(verificarRepetidas == 1){
					miAlbum = IntercambiarFiguritas(figuritas, cantFiguritas, pilaRepetidas, miAlbum, equipos, cantEquipos);
				}
				else{
					printf("[ERROR] Para intercambiar figuritas tenes que tener repetidas.");
				}
				break;

			case 3: // Informes
				if(contadorSobres > 0){
					Informes(figuritas, cantFiguritas, miAlbum, equipos, cantEquipos, pilaRepetidas, cantSobresAlbumLleno, dineroGastado, dineroGastadoHastaAlbumLleno);
				}
				else{
					printf("[ERROR] Para mostrar los informes primero tenes que abrir al menos un sobre.");
				}
				break;

			case 4:
				printf("Volviendo al menu...\n");
				break;
		}
	}while(opcion != 4);

	return 0;
}

int GenerarNumeroRandom(int min, int max){
	int numRandom;

	numRandom = rand() % (max) + min;

	return numRandom;
}

sAlbum ComprarPaquete(sAlbum album, sRepetida pilaRepetidas[], int* pContadorFiguritas, sFigurita figuritas[], int cantFiguritas){
	srand(time(NULL));
	int paquete[FIGURITAS_POR_PAQUETE];
	int contadorFiguritas;
	int figuritaDorada;
	figuritaDorada = -1;

	contadorFiguritas = *pContadorFiguritas;

	printf("\nCompraste un paquete! Suerte :)\n");

	for(int i = 0; i < FIGURITAS_POR_PAQUETE; i++){
		paquete[i] = GenerarNumeroRandom(1, CANT_FIGURITAS);

		if(contadorFiguritas == 50){ // todo cada cuantas figuritas toca una dorada
			figuritaDorada = paquete[i];
			printf("\nTe toco una figurita dorada! Su ID es el %d", figuritaDorada);

			for(int j = 0; j < cantFiguritas; j++){
				if(album.esDorada[j] == -1){
					album.esDorada[j] = figuritaDorada;
					break;
				}
			}

			contadorFiguritas = 0;
		}

		contadorFiguritas++;
	}

	for(int i = 0; i < FIGURITAS_POR_PAQUETE; i++){
		album = PegarFigurita(figuritas, cantFiguritas, album, paquete[i], pilaRepetidas);
	}

	*pContadorFiguritas = contadorFiguritas;

	return album;
}

sAlbum PegarFigurita(sFigurita figuritas[], int cantFiguritas, sAlbum album, int figuritaAPegar, sRepetida pilaRepetidas[]){

	for(int j = 0; j < cantFiguritas; j++){
		if(figuritaAPegar == figuritas[j].idFigurita){
			if(album.idFigurita[j] != -1){
				printf("\nLa figurita %d esta repetida, sumandola a la pila de repetidas...", figuritaAPegar);

				AgregarRepetidaALaPila(pilaRepetidas, cantFiguritas, figuritaAPegar);
			}
			else{
				album.idFigurita[j] = figuritas[j].idFigurita;
			}
		}
	}

	return album;
}

int AgregarRepetidaALaPila(sRepetida pilaRepetidas[], int tamRepetidas, int repetida){
	for(int i = 0; i < tamRepetidas; i++){
		if(pilaRepetidas[i].idFigurita == repetida){
			pilaRepetidas[i].vecesRepetida = pilaRepetidas[i].vecesRepetida + 1;
			break;
		}
	}

	return 0;
}

sAlbum InicializarFiguritasAlbum(sAlbum album, int cantFiguritas){
    for(int i = 0; i < cantFiguritas; i++){
    	album.idFigurita[i] = -1;
    	album.esDorada[i] = -1;
    }

	return album;
}

int InicializarRepetidas(sRepetida pilaRepetidas[], sFigurita figuritas[], int cantFiguritas){
	int retorno;
	retorno = -1;

	if(pilaRepetidas != NULL && cantFiguritas > 0){
		for(int i = 0; i < cantFiguritas; i++){
			pilaRepetidas[i].idFigurita = figuritas[i].idFigurita;
			pilaRepetidas[i].vecesRepetida = 0;
		}

		retorno = 0;
	}

	return retorno;
}

sAlbum IntercambiarFiguritas(sFigurita figuritas[], int cantFiguritas, sRepetida pilaRepetidas[], sAlbum album, sEquipo equipos[], int cantEquipos){
	int figuritaSolicitada;
	int figuritaEntregada;
	int tieneLaFigurita;

	tieneLaFigurita = 0;

	getInt(&figuritaSolicitada, "\nIngrese la figurita que necesite: ", "[ERROR] La opcion que ingreso no es correcta.", 1, 55);

	do{
		MostrarRepetidas(pilaRepetidas, figuritas, cantFiguritas, equipos, cantEquipos);
		getInt(&figuritaEntregada, "\nIngrese la figurita que va a entregar: ", "[ERROR] La opcion que ingreso no es correcta.", 1, 55);

		for(int i = 0; i < cantFiguritas; i++){
			if(figuritaEntregada == pilaRepetidas[i].idFigurita && pilaRepetidas[i].vecesRepetida > 0){
				pilaRepetidas[i].vecesRepetida = pilaRepetidas[i].vecesRepetida - 1;
				tieneLaFigurita = 1;
			}
		}

		if(tieneLaFigurita == 0){
			printf("\n[ERROR] No tenes la figurita %d, ingresa una que tengas.\n", figuritaEntregada);
		}

	}while(tieneLaFigurita == 0);

	printf("\nFiguritas intercambiadas con exito!");

	album = PegarFigurita(figuritas, cantFiguritas, album, figuritaSolicitada, pilaRepetidas);

	return album;
}

int VerificarAlbumLleno(sAlbum album, int cantFiguritas){
	int retorno;
	int verificador;

	retorno = 0;
	verificador = 0;

	for(int i = 0; i < cantFiguritas; i++){
		if(album.idFigurita[i] != -1){
			verificador++;
		}
	}

	if(verificador == cantFiguritas){
		retorno = 1;
	}

	return retorno;
}

int VerificarSiHayRepetidas(sRepetida pilaRepetidas[], int cantFiguritas){
	int retorno;
	retorno = -1;

	for(int i = 0; i < cantFiguritas; i++){
		if(pilaRepetidas[i].vecesRepetida > 0){
			retorno = 1;
			break;
		}
	}

	return retorno;
}

int Informes(sFigurita figuritas[], int cantFiguritas, sAlbum album, sEquipo equipos[], int cantEquipos, sRepetida pilaRepetidas[], int cantSobresAlbumLleno, float dineroGastado, float dineroGastadoHastaAlbumLleno){
	int retorno;
	retorno = -1;

	if(figuritas != NULL && cantFiguritas > 0 && equipos != NULL && cantEquipos > 0 && pilaRepetidas != NULL){
		int opcion;

		do{
			printf("\n\n[Informes]\n 1.Listado de figuritas pegadas\n 2.Listado de figuritas repetidas\n 3.Listado de figuritas doradas que estan pegadas en el album\n"
					" 4.Cuantos sobres tuvo que comprar el coleccionista para llenar el album\n 5.Cuanto dinero lleva gastado el coleccionista\n"
					" 6.Cuanto dinero gasto el coleccionista para completar el album\n 7.Salir");
			getInt(&opcion, "\n\nOpcion: ", "[ERROR] La opcion que ingreso no es correcta.", 1, 7);

			switch(opcion){
				case 1:// Listado de figuritas pegadas
					MostrarFiguritasPegadas(figuritas, cantFiguritas, album, equipos, cantEquipos);
					break;

				case 2: // Listado de figuritas repetidas
					MostrarRepetidas(pilaRepetidas, figuritas, cantFiguritas, equipos, cantEquipos);
					break;

				case 3: //Listado de figuritas doradas que estan pegadas en el album
					MostrarFiguritasDoradas(figuritas, cantFiguritas, album);
					break;

				case 4: // Cuantos sobres tuvo que comprar el coleccionista para llenar el album
					if(album.estado == LLENO){
						MostrarPaquetesLlenado(cantSobresAlbumLleno);
					}
					else{
						printf("[ERROR] Se tiene que llenar el album primero para saber cuantos sobres tuvo que comprar el coleccionista para completarlo.");
					}

					break;

				case 5: //Cuanto dinero lleva gastado el coleccionista
					MostrarDineroGastado(dineroGastado);
					break;

				case 6: // Cuanto dinero gasto el coleccionista para completar el album
					if(album.estado == LLENO){
						MostrarDineroGastadoParaLlenarlo(dineroGastadoHastaAlbumLleno);
					}
					else{
						printf("[ERROR] Se tiene que llenar el album primero para saber cuanto dinero gasto el coleccionista para completarlo.");
					}

					break;

				case 7:
					printf("Volviendo al menu...\n");
					break;
			}
		}while(opcion != 7);

		retorno = 0;
	}

	return retorno;
}

int MostrarFiguritasPegadas(sFigurita figuritas[], int cantFiguritas, sAlbum album, sEquipo equipos[], int cantEquipos){
	int retorno;
	retorno = -1;

	if(figuritas != NULL && cantFiguritas > 0 && equipos != NULL && cantEquipos > 0){
		printf("\n[Figuritas pegadas]");
		for(int i = 0; i < cantFiguritas; i++){
			if(album.idFigurita[i] != -1){
				for(int j = 0; j < cantEquipos; j++){
					if(figuritas[i].idEquipo == equipos[j].idEquipo){
						printf("\n|ID: %2d | Jugador: %-20s | Equipo: %-14s | Posicion: %-15s|", album.idFigurita[i], figuritas[i].nombreJugador, equipos[j].descripcion, figuritas[i].posicion);
					}
				}
			}
		}

		retorno = 0;
	}

	return retorno;
}

int MostrarRepetidas(sRepetida pilaRepetidas[], sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos){
	int retorno;
	int hayRepetida;

	retorno = -1;
	hayRepetida = 0;

	if(pilaRepetidas != NULL && figuritas != NULL && cantFiguritas > 0 && cantEquipos > 0 && equipos != NULL){
		printf("\n[Repetidas]");
		for(int i = 0; i < cantFiguritas; i++){
			if(pilaRepetidas[i].vecesRepetida > 0){
				for(int j = 0; j < cantEquipos; j++){
					if(figuritas[i].idEquipo == equipos[j].idEquipo){
						hayRepetida = 1;
						printf("\n|ID: %2d | Jugador: %-20s | Equipo: %-14s | Repetida: %2d veces |", pilaRepetidas[i].idFigurita, figuritas[i].nombreJugador, equipos[j].descripcion, pilaRepetidas[i].vecesRepetida);
						break;
					}
				}
			}
		}
		if(hayRepetida == 0){
			printf("\nNo tenes figuritas repetidas.");
		}
		retorno = 0;
	}

	return retorno;
}

int MostrarFiguritasDoradas(sFigurita figuritas[], int cantFiguritas, sAlbum album){
	int retorno;
	int hayDorada;

	retorno = -1;
	hayDorada = 0;

	if(figuritas != NULL && cantFiguritas > 0){
		printf("\n[Figuritas doradas]");
		for(int i = 0; i < cantFiguritas; i++){
			if(album.idFigurita[i] != -1){
				for(int j = 0; j < cantFiguritas; j++){
					if(album.esDorada[j] == album.idFigurita[i]){
						hayDorada = 1;
						printf("\nID: %2d | Jugador: %-20s | DORADA", album.idFigurita[i], figuritas[i].nombreJugador);
						break;
					}
				}
			}
		}

		if(hayDorada == 0){
			printf("\nNo tenes figuritas doradas.");
		}

		retorno = 0;
	}

	return retorno;
}

void MostrarPaquetesLlenado(int cantPaquetes){
	printf("\nEl coleccionista tuvo que comprar %d paquetes para llenar el album.", cantPaquetes);
}

void MostrarDineroGastado(float dineroGastado){
	printf("\nEl coleccionista lleva gastado $%.2f.", dineroGastado);
}

void MostrarDineroGastadoParaLlenarlo(float dineroGastadoHastaAlbumLleno){
	printf("\nEl coleccionista gasto $%.2f para completar el album.", dineroGastadoHastaAlbumLleno);
}















