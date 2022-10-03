
#ifndef PERFILADMIN_H_
#define PERFILADMIN_H_

#define LIBRE 0
#define OCUPADO 1
#define CANT_FIGURITAS 55
#define CANT_EQUIPOS 5
#define TAM_STRINGS 25
#define VACIO 0
#define LLENO 1
#define MAX_JUGADORES 11


typedef struct{
	int dia;
	int mes;
	int anio;
}sFecha;

typedef struct{
	int idEquipo;
	char descripcion[TAM_STRINGS];
	char directorTecnico[TAM_STRINGS];
	int idAux;
	int estado;
	int equipoLleno;
}sEquipo;

typedef struct{
	int id;
	int contador;
}sAuxiliar;

typedef struct{
	int idFigurita;
	char nombreJugador[TAM_STRINGS];
	char posicion[TAM_STRINGS];
	int idEquipo;
	float altura;
	float peso;
	int anioDeIngreso;
	sFecha fechaNacimiento;
	int estado;
}sFigurita;


int InicializarFiguritas(sFigurita figuritas[], int cantFiguritas);
int InicializarEquipos(sEquipo equipos[], int cantEquipos);
int InicializarAuxiliar(sEquipo equipos[], int cantEquipos, sAuxiliar auxEquipos[]);

int PerfilAdministrador(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos, sAuxiliar auxEquipos[]);

sFigurita AltaFigurita(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos);
int ObtenerIDIncremental(void);
int ValidarIDFigurita(sFigurita figuritas[], int cantFiguritas, int idAComparar);
int ValidarPosicionFigurita(char posicion[]);
int CargarListaDeFiguritas(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos);
int CargarEquipo(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos);
int ContarJugadoresPorEquipo(sFigurita figuritas[], int cantFiguritas, sAuxiliar auxEquipos[], int cantEquipos, sEquipo equipos[]);
int ModificarFigurita(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos);
int OrdenarEquipos(sEquipo equipos[], int cantEquipos);
int MostrarDatosOrdenadosPorEquipos(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos);
void MostrarListaFiguritas(sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos);


#endif /* PERFILADMIN_H_ */
