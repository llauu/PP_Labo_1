
#ifndef PERFILCOLECCIONISTA_H_
#define PERFILCOLECCIONISTA_H_
#include "perfilAdmin.h"

#define CANT_FIGURITAS 55
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

// Compra de paquetes
int GenerarNumeroRandom(int min, int max);
sAlbum InicializarFiguritasAlbum(sAlbum album, int cantFiguritas);
sAlbum ComprarPaquete(sAlbum album, sRepetida pilaRepetidas[], int* pContadorFiguritas, sFigurita figuritas[], int cantFiguritas);

// Repetidas
int InicializarRepetidas(sRepetida pilaRepetidas[], sFigurita figuritas[], int cantFiguritas);
int AgregarRepetidaALaPila(sRepetida pilaRepetidas[], int tamRepetidas, int repetida);

// Intercambio de figuritas
sAlbum IntercambiarFiguritas(sFigurita figuritas[], int cantFiguritas, sRepetida pilaRepetidas[], sAlbum album, sEquipo equipos[], int cantEquipos);
sAlbum PegarFigurita(sFigurita figuritas[], int cantFiguritas, sAlbum album, int figuritaAPegar, sRepetida pilaRepetidas[]);
int VerificarAlbumLleno(sAlbum album, int cantFiguritas);
int VerificarSiHayRepetidas(sRepetida pilaRepetidas[], int cantFiguritas);

// Informes
int Informes(sFigurita figuritas[], int cantFiguritas, sAlbum album, sEquipo equipos[], int cantEquipos, sRepetida pilaRepetidas[], int cantSobresAlbumLleno, float dineroGastado, float dineroGastadoHastaAlbumLleno);
int MostrarFiguritasPegadas(sFigurita figuritas[], int cantFiguritas, sAlbum album, sEquipo equipos[], int cantEquipos);
int MostrarDatosJugador(sFigurita figuritas[], sAlbum album, sEquipo equipos[], int cantEquipos, int posicionFiguritas);
int MostrarRepetidas(sRepetida pilaRepetidas[], sFigurita figuritas[], int cantFiguritas, sEquipo equipos[], int cantEquipos);
int MostrarFiguritasDoradas(sFigurita figuritas[], int cantFiguritas, sAlbum album);
void MostrarPaquetesLlenado(int cantPaquetes);
void MostrarDineroGastado(float dineroGastado);
void MostrarDineroGastadoParaLlenarlo(float dineroGastadoHastaAlbumLleno);
int MostrarFiguritasPorEquipo(sEquipo equipos[], int cantEquipos, sAlbum album, sFigurita figuritas[], int cantFiguritas);

#endif /* PERFILCOLECCIONISTA_H_ */
