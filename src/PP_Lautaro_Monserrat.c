/*
 ============================================================================
	Parcial Laboratorio de computacion I

	Nombre: Lautaro Monserrat
	DNI: 45426439
	DIV: 1C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "perfilAdmin.h"
#include "perfilColeccionista.h"

int main(void){
	sFigurita bancoDeFiguritas[CANT_FIGURITAS];
	sEquipo equiposIngresados[CANT_EQUIPOS];
	sAuxiliar auxEquipos[CANT_EQUIPOS];
	sAlbum miAlbum;
	sRepetida pilaRepetidas[CANT_FIGURITAS];
	int opcion;

	miAlbum.estado = VACIO;

// DATOS HARDCODEADOS PARA TEST
//	sEquipo equiposIngresados[CANT_EQUIPOS] = {
//			{1, "Boca", "Bianchi", 1, OCUPADO, VACIO},
//			{2, "River", "Gallardo", 2, OCUPADO, VACIO},
//			{3, "Defensa", "kuko", 3, OCUPADO, VACIO},
//			{4, "Independiente", "masallanes", 4, OCUPADO, VACIO},
//			{5, "Racing", "milito", 5, OCUPADO, VACIO},
//	};
//
//	sFigurita bancoDeFiguritas[CANT_FIGURITAS] = {
//	                {1,"miranda","mediocampista",1,1.7,70,2009,{14,4,1995}, OCUPADO},
//	                {2,"ramiro","delantero",2,1.9,80,2008,{9,1,2003}, OCUPADO},
//	                {3,"agustin","arquero",2,1.8,90,2007,{1,3,2001}, OCUPADO},
//	                {4,"german","delantero",4,1.6,60,2005,{23,6,1987}, OCUPADO},
//	                {5,"juan","defensor",5,1.5,65,2006,{30,7,2000}, OCUPADO},
//					{6,"mariano","delantero",1,1.8,90,2007,{23,3,2001}, OCUPADO},
//					{7,"martin","mediocampista",3,1.8,90,2007,{1,12,2000}, OCUPADO},
//					{8,"julian","mediocampista",2,1.8,90,2007,{31,12,2001}, OCUPADO},
//					{9,"lautaro","arquero",1,1.8,90,2007,{12,11,2001}, OCUPADO},
//					{10,"diego","defensor",3,1.8,90,2007,{13,9,2001}, OCUPADO},
//					{11,"messi","delantero",4,1.8,90,2007,{1,3,2001}, OCUPADO},
//					{12,"giovani","delantero",5,1.8,90,2007,{14,3,2001}, OCUPADO},
//					{13,"matias","defensor",5,1.8,90,2007,{1,3,2001}, OCUPADO},
//					{14,"felipe","arquero",4,1.8,90,2007,{1,3,2001}, OCUPADO},
//					{15,"mauricio","defensor",4,1.8,90,2007,{1,5,2001}, OCUPADO},
//					{16,"alberto","mediocampista",5,1.8,90,2007,{1,3,2001}, OCUPADO},
//					{17,"cristina","delantero",3,1.8,90,2007,{1,2,2001}, OCUPADO},
//					{18,"lorenzo","mediocampista",3,1.8,90,2007,{1,3,2001}, OCUPADO},
//					{19,"riquelme","arquero",1,1.8,90,2007,{1,8,2001}, OCUPADO},
//					{20,"palermo","mediocampista",1,1.8,90,2007,{1,7,2001}, OCUPADO},
//					{21,"enrique","delantero",1,1.8,90,2007,{1,9,2001}, OCUPADO},
//					{22,"leonardo","mediocampista",1,1.8,90,2007,{1,10,2001}, OCUPADO}};

	InicializarFiguritas(bancoDeFiguritas, CANT_FIGURITAS);
	InicializarEquipos(equiposIngresados, CANT_EQUIPOS);
	InicializarAuxiliar(equiposIngresados, CANT_EQUIPOS, auxEquipos);

	do{
		printf("\n         [Menu principal]\n"
				"\n1.Perfil Administrador\n2.Perfil Coleccionista\n3.Salir\n");
		getInt(&opcion, "\nOpcion: ", "[ERROR] La opcion que ingreso no es correcta.", 1, 4);

		switch(opcion){
			case 1:
				PerfilAdministrador(bancoDeFiguritas, CANT_FIGURITAS, equiposIngresados, CANT_EQUIPOS, auxEquipos);
				break;

			case 2:
				perfilColeccionista(miAlbum, bancoDeFiguritas, CANT_FIGURITAS, pilaRepetidas, equiposIngresados, CANT_EQUIPOS);
				break;

			case 3:
				printf("Saliendo...\n");
				break;
		}
	}while(opcion != 3);

	return EXIT_SUCCESS;
}





















