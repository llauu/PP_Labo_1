
#ifndef PERFILCOLECCIONISTA_H_
#define PERFILCOLECCIONISTA_H_
#include "perfilAdmin.h"

#define CANT_FIGURITAS 22 // 55 todo cambiar
#define FIGURITAS_POR_PAQUETE 5

typedef struct{
	int idFigurita[CANT_FIGURITAS];
	int esDorada[CANT_FIGURITAS];
	int estado;
}sAlbum;

typedef struct{
	int idFigurita;
	int vecesRepetida;
}sRepetida;

int perfilColeccionista(sAlbum miAlbum, sFigurita figuritas[], int cantFiguritas, sRepetida pilaRepetidas[], sEquipo equipos[], int cantEquipos);
int GenerarNumeroRandom(int min, int max);
sAlbum InicializarFiguritasAlbum(sAlbum album, int cantFiguritas);
sAlbum ComprarPaquete(sAlbum album, sRepetida pilaRepetidas[], int* pContadorFiguritas, sFigurita figuritas[], int cantFiguritas);

int InicializarRepetidas(sRepetida pilaRepetidas[], sFigurita figuritas[], int cantFiguritas);
int AgregarRepetidaALaPila(sRepetida pilaRepetidas[], int tamRepetidas, int repetida);

sAlbum IntercambiarFiguritas(sFigurita figuritas[], int cantFiguritas, sRepetida pilaRepetidas[], sAlbum album, sEquipo equipos[], int cantEquipos);
sAlbum PegarFigurita(sFigurita figuritas[], int cantFiguritas, sAlbum album, int figuritaAPegar, sRepetida pilaRepetidas[]);
int VerificarAlbumLleno(sAlbum album, int cantFiguritas);
int VerificarSiHayRepetidas(sRepetida pilaRepetidas[], int cantFiguritas);

// Informes
int Informes(sFigurita figuritas[], int cantFiguritas, sAlbum album, sEquipo equipos[], int cantEquipos, sRepetida pilaRepetidas[], int cantSobresAlbumLleno, float dineroGastado, float dineroGastadoHastaAlbumLleno);
int MostrarFiguritasPegadas(sFigurita figuritas[], int cantFiguritas, sAlbum album, sEquipo equipos[], int cantEquipos);
int MostrarRepetidas(sRepetida pilaRepetidas[], sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos);
int MostrarFiguritasDoradas(sFigurita figuritas[], int cantFiguritas, sAlbum album);
void MostrarPaquetesLlenado(int cantPaquetes);
void MostrarDineroGastado(float dineroGastado);
void MostrarDineroGastadoParaLlenarlo(float dineroGastadoHastaAlbumLleno);

#endif /* PERFILCOLECCIONISTA_H_ */
