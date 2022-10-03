
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mylib.h"
#include "perfilAdmin.h"

static int GenerarID(void);
static int GenerarID(void){
	static int idIncremental = 1;

	return idIncremental++;
}


int PerfilAdministrador(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos, sAuxiliar auxEquipos[]){
	int opcion;

	do{
		printf("\n[Perfil Administrador]\n 1.Dar de alta figurita\n 2.Modificar figurita\n 3.Listar figuritas ordenadas por equipo\n 4.Salir\n");
		getInt(&opcion, "\nOpcion: ", "[ERROR] La opcion que ingreso no es correcta.", 1, 4);

		switch(opcion){
			case 1:
				CargarListaDeFiguritas(figuritas, cantFiguritas, equipos, cantEquipos);
				ContarJugadoresPorEquipo(figuritas, cantFiguritas, auxEquipos, cantEquipos, equipos);
				break;

			case 2:
				ModificarFigurita(figuritas, cantFiguritas, equipos, cantEquipos);
				ContarJugadoresPorEquipo(figuritas, cantFiguritas, auxEquipos, cantEquipos, equipos);
				break;

			case 3:
				MostrarDatosOrdenadosPorEquipos(figuritas, cantFiguritas, equipos, cantEquipos);
				break;

			case 4:
				printf("Volviendo al menu...\n");
				break;
		}
	}while(opcion != 4);

	return 0;
}


sFigurita AltaFigurita(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos){
	sFigurita figurita;
	int validacionPos;

	validacionPos = 0;

	figurita.idFigurita = ObtenerIDIncremental();

	getString(figurita.nombreJugador, 30, "\nIngrese el nombre del jugador: ", "\n[ERROR] Nombre no valido.\n");
	StringUpper(figurita.nombreJugador, strlen(figurita.nombreJugador));

	do{
		getString(figurita.posicion, 25, "\nIngrese la posicion del jugador (Delantero, Mediocampista, Defensor, Arquero): ", "\n[ERROR] Posicion no valida.\n");
		validacionPos = ValidarPosicionFigurita(figurita.posicion);
	}while(validacionPos == 0);
	figurita.posicion[0] = toupper(figurita.posicion[0]);

	figurita.idEquipo = CargarEquipo(figuritas, cantFiguritas, equipos, cantEquipos);

//	getFloat(&figurita.altura, "\nIngrese la altura del jugador (en metros): ", "\n[ERROR] Altura no valida.\n", 0, 3);
//	getFloat(&figurita.peso, "\nIngrese el peso del jugador (en kilos): ", "\n[ERROR] Peso no valido.\n", 0, 150);
//	getInt(&figurita.anioDeIngreso, "\nIngrese el anio de ingreso a la seleccion: ", "\n[ERROR] Anio no valido.\n", 1, 2500);
//	getInt(&figurita.fechaNacimiento.dia, "\nIngrese el dia de nacimiento del jugador: ", "\n[ERROR] Dia no valido.\n", 1, 31);
//	getInt(&figurita.fechaNacimiento.mes, "\nIngrese el mes de nacimiento del jugador: ", "\n[ERROR] Mes no valido.\n", 1, 12);
//	getInt(&figurita.fechaNacimiento.anio, "\nIngrese el anio de nacimiento del jugador: ", "\n[ERROR] Anio no valido.\n", 1, 2022);

	figurita.estado = OCUPADO;

	return figurita;
}


int ObtenerIDIncremental(void){
	int id;

	id = GenerarID();

	return id;
}


int CargarEquipo(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos){
	int idEquipo;
	char bufferEquipo[25];
	int jugadorIngresado;
	int maxEquiposIngresados;
	int maxAlcanzado;

	jugadorIngresado = 0;
	maxEquiposIngresados = 1;

		do{
			do{
				maxAlcanzado = 0;

				getString(bufferEquipo, 25, "\nIngrese el equipo del jugador: ", "\n[ERROR] Equipo no valido.\n");
				StringUpper(bufferEquipo, strlen(bufferEquipo));

				for(int i = 0; i < cantEquipos; i++){
					if(strcasecmp(equipos[i].nombreEquipo, bufferEquipo) == 0){
						if(equipos[i].equipoLleno == VACIO){
							jugadorIngresado = 1;
							maxEquiposIngresados = 0;
							idEquipo = equipos[i].idEquipo;
							break;
						}
						else{
							maxAlcanzado = 1;
							printf("%s ya tiene los 11 jugadores cargados. Ingrese otro equipo.", bufferEquipo);
							break;
						}
					}
				}
			}while(maxAlcanzado == 1);

			if(jugadorIngresado == 0){
				for(int i = 0; i < cantEquipos; i++){
					if(equipos[i].estado == LIBRE){
						maxEquiposIngresados = 0;
						strcpy(equipos[i].nombreEquipo, bufferEquipo);
						idEquipo = equipos[i].idEquipo;
						equipos[i].estado = OCUPADO;
						break;
					}
				}

				if(maxEquiposIngresados == 1){
					printf("[ERROR] Ya se alcanzo el maximo de equipos. Ingrese uno que ya este cargado.");
				}
			}
		}while(maxEquiposIngresados == 1 || maxAlcanzado == 1);

	return idEquipo;
}


int ValidarIDFigurita(sFigurita figuritas[], int cantFiguritas, int idAComparar){
	int retorno;
	retorno = 0;

	for(int i = 0; i < cantFiguritas; i++){
		if(figuritas[i].estado == OCUPADO){
			if(idAComparar == figuritas[i].idFigurita){
				retorno = idAComparar;
				break;
			}
		}
	}

	return retorno;
}


int ValidarPosicionFigurita(char posicion[]){
	int retorno;
	retorno = 1;

	if((strcasecmp("Arquero", posicion) != 0) && (strcasecmp("Defensor", posicion) != 0) && (strcasecmp("Mediocampista", posicion) != 0) && (strcasecmp("Delantero", posicion) != 0)){
		printf("La posicion que ingreso no es correcta.");
		retorno = 0;
	}

	return retorno;
}


int CargarListaDeFiguritas(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos){
	int retorno;
	int ingresoACargar;

	retorno = -1;
	ingresoACargar = 0;

	for(int i = 0; i < cantFiguritas; i++){
		if(figuritas[i].estado == LIBRE){
			figuritas[i] = AltaFigurita(figuritas, cantFiguritas, equipos, cantEquipos);
			ingresoACargar = 1;
			retorno = 0;
			break;
		}
	}

	if(ingresoACargar == 0){
		printf("[ERROR] Ya se ingresaron las %d figuritas.\n", cantFiguritas);
	}

	return retorno;
}


int InicializarFiguritas(sFigurita figuritas[], int cantFiguritas){
	int retorno;
	retorno = -1;

	for(int i = 0; i < cantFiguritas; i++){
		figuritas[i].estado = LIBRE;
	}

	retorno = 0;

	return retorno;
}


int InicializarEquipos(sEquipo equipos[], int cantEquipos){
	int retorno;
	int asignarIDs;

	retorno = -1;
	asignarIDs = 0;

	for(int i = 0; i < cantEquipos; i++){
		asignarIDs++;
		equipos[i].estado = LIBRE;
		equipos[i].idEquipo = asignarIDs;
	}

	retorno = 0;

	return retorno;
}


int ModificarFigurita(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos){
	int opcion;
	int idFigurita;
	int validacionPos;
	int validacionFigurita;
	validacionFigurita = 0;

	do{
		printf("\nModificar figurita\n 1.Nombre del jugador\n 2.Posicion del jugador\n 3.Equipo del jugador\n 4.Altura del jugador"
				"\n 5.Peso del jugador\n 6.Anio de ingreso a la seleccion\n 7.Fecha de nacimiento del jugador\n 8.Salir\n");
		getInt(&opcion, "\nIngrese el numero de lo que quiere modificar: ", "[ERROR] La opcion que ingreso no es correcta.", 1, 8);

		if(opcion != 8){
			MostrarDatosOrdenadosPorEquipos(figuritas, cantFiguritas, equipos, cantEquipos);

			do{
				getInt(&idFigurita, "\nIngrese el ID de la figurita que quiere modificar: ", "[ERROR] La opcion que ingreso no es correcta.", 1, 55);
				validacionFigurita = ValidarIDFigurita(figuritas, cantFiguritas, idFigurita);

				if(validacionFigurita == 0){
					printf("El ID %d no esta ingresado, pruebe con otro.", idFigurita);
				}
			}while(validacionFigurita == 0);

			switch(opcion){
				case 1:// nombre
					for(int i = 0; i < cantFiguritas; i++){
						if(figuritas[i].idFigurita == idFigurita){
							getString(figuritas[i].nombreJugador, 30, "\nIngrese el nuevo nombre del jugador: ", "\n[ERROR] Nombre no valido.\n");
							StringUpper(figuritas[i].nombreJugador, strlen(figuritas[i].nombreJugador));
							break;
						}
					}

					break;

				case 2:// posicion
					validacionPos = 0;

					for(int i = 0; i < cantFiguritas; i++){
						if(figuritas[i].idFigurita == idFigurita){
							do{
								getString(figuritas[i].posicion, 25, "\nIngrese la nueva posicion del jugador: ", "\n[ERROR] Posicion no valida.\n");
								validacionPos = ValidarPosicionFigurita(figuritas[i].posicion);
							}while(validacionPos == 0);
							figuritas[i].posicion[0] = toupper(figuritas[i].posicion[0]);
							break;
						}
					}

					break;

				case 3:// equipo
					for(int i = 0; i < cantFiguritas; i++){
						if(figuritas[i].idFigurita == idFigurita){
							figuritas[i].idEquipo = CargarEquipo(figuritas, cantFiguritas, equipos, cantEquipos);
							break;
						}
					}
					break;

				case 4:// altura
					for(int i = 0; i < cantFiguritas; i++){
						if(figuritas[i].idFigurita == idFigurita){
							getFloat(&figuritas[i].altura, "\nIngrese la nueva altura del jugador: ", "\n[ERROR] Altura no valida.\n", 0, 3);
							break;
						}
					}
					break;

				case 5://peso
					for(int i = 0; i < cantFiguritas; i++){
						if(figuritas[i].idFigurita == idFigurita){
							getFloat(&figuritas[i].peso, "\nIngrese el nuevo peso del jugador: ", "\n[ERROR] Peso no valido.\n", 0, 150);
							break;
						}
					}
					break;

				case 6://anio ingreso
					for(int i = 0; i < cantFiguritas; i++){
						if(figuritas[i].idFigurita == idFigurita){
							getInt(&figuritas[i].anioDeIngreso, "\nIngrese el anio de ingreso a la seleccion: ", "\n[ERROR] Anio no valido.\n", 1, 2500);
							break;
						}
					}
					break;

				case 7://fecha nacimiento
					for(int i = 0; i < cantFiguritas; i++){
						if(figuritas[i].idFigurita == idFigurita){
							getInt(&figuritas[i].fechaNacimiento.dia, "\nIngrese el dia de nacimiento del jugador: ", "\n[ERROR] Dia no valido.\n", 1, 31);
							getInt(&figuritas[i].fechaNacimiento.mes, "\nIngrese el mes de nacimiento del jugador: ", "\n[ERROR] Mes no valido.\n", 1, 12);
							getInt(&figuritas[i].fechaNacimiento.anio, "\nIngrese el anio de nacimiento del jugador: ", "\n[ERROR] Anio no valido.\n", 1, 2022);
							break;
						}
					}
					break;
			}
		}
	}while(opcion != 8);

	return 0;
}


int InicializarAuxiliar(sEquipo equipos[], int cantEquipos, sAuxiliar auxEquipos[]){
    int retorno;
    retorno = -1;

	for(int i = 0; i < cantEquipos; i++){
    	auxEquipos[i].id = equipos[i].idEquipo;
    }

	retorno = 0;

	return retorno;
}


int ContarJugadoresPorEquipo(sFigurita figuritas[], int cantFiguritas, sAuxiliar auxEquipos[], int cantEquipos, sEquipo equipos[]){
    int retorno;
    retorno = -1;

	for(int i = 0; i < cantEquipos; i++){
    	auxEquipos[i].contador = 0;

        for(int j = 0; j < cantFiguritas; j++){
        	if(figuritas[j].estado == OCUPADO){
                if(auxEquipos[i].id == figuritas[j].idEquipo){
                	auxEquipos[i].contador++;
                }
        	}
        }

        if(auxEquipos[i].contador == MAX_JUGADORES){
        	equipos[i].equipoLleno = LLENO;
        }
        else{
        	equipos[i].equipoLleno = VACIO;
        }
    }

	retorno = 0;

	return retorno;
}


int OrdenarEquipos(sEquipo equipos[], int cantEquipos){
	int flagSwap;
	int i;
	int contador = 0;
	int retorno = -1;
	sEquipo tmp;
    int nuevoTam;

    if(equipos != NULL && cantEquipos > 0){
    	nuevoTam = cantEquipos - 1;

    	do{
    		flagSwap = 0;

    		for(i = 0; i < nuevoTam; i++){

    			if(equipos[i].estado == OCUPADO && equipos[i+1].estado == OCUPADO){
        			contador++;

        			if(strcmp(equipos[i].nombreEquipo, equipos[i+1].nombreEquipo) > 0){
        				flagSwap = 1;

        				tmp = equipos[i];
        				equipos[i] = equipos[i+1];
        				equipos[i+1] = tmp;
        			}
    			}
    		}
    		nuevoTam--;
    	}
    	while(flagSwap);
    	retorno = contador;
    }

	return retorno;
}


int MostrarDatosOrdenadosPorEquipos(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos){
	int retorno;
	retorno = -1;

	if(figuritas != NULL && cantFiguritas > 0 && equipos != NULL && cantEquipos > 0){
		OrdenarEquipos(equipos, cantEquipos);

		for(int i = 0; i < cantEquipos; i++){
			if(equipos[i].estado == OCUPADO){
		        printf("\n[%s]\n", equipos[i].nombreEquipo);

		        for(int j = 0; j < cantFiguritas; j++){
		            if(figuritas[j].estado == OCUPADO){
		                if(equipos[i].idEquipo == figuritas[j].idEquipo){
		                	printf(" %4d %-20s %-15s %2.2fm %2.2fkg %6d %3d/%d/%d\n", figuritas[j].idFigurita, figuritas[j].nombreJugador, figuritas[j].posicion,
		                								   									figuritas[j].altura, figuritas[j].peso, figuritas[j].anioDeIngreso,
																							figuritas[j].fechaNacimiento.dia, figuritas[j].fechaNacimiento.mes,
																							figuritas[j].fechaNacimiento.anio);
		                }
		            }
		        }
			}
	    }

		retorno = 0;
	}

	return retorno;
}














