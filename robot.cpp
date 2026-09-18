#include <array>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

struct PuntoTrayectoria {
   int identificador;
   string nombre;
   array<double, 3> coordenadas;
   double distanciaOrigen;
   string clasificacion;
};

void clasificarPunto(PuntoTrayectoria& punto) {
   if (punto.distanciaOrigen <= 5) {
      punto.clasificacion = "CERCANO";
   } else if (punto.distanciaOrigen <= 10) {
      punto.clasificacion = "INTERMEDIO";
   } else if (punto.distanciaOrigen <= 20) {
      punto.clasificacion = "LEJANO";
   } else {
      punto.clasificacion = "EXTREMO";
   }
}

void registrarPunto(PuntoTrayectoria& punto) {
   cout << "Identificador: ";
   cin >> punto.identificador;
   cin.ignore();

   cout << "Nombre o descripcion: ";
   getline(cin, punto.nombre); //el getline funciona para escribir una descripcion del punto de string

   cout << "Coordenada X: ";
   cin >> punto.coordenadas[0];
   cout << "Coordenada Y: ";
   cin >> punto.coordenadas[1];
   cout << "Coordenada Z: ";
   cin >> punto.coordenadas[2];

   punto.distanciaOrigen = sqrt( //el sqrt funcina para calcular la distancia desde el origen es de la libreria math.m
      punto.coordenadas[0] * punto.coordenadas[0] +
      punto.coordenadas[1] * punto.coordenadas[1] +
      punto.coordenadas[2] * punto.coordenadas[2]);

   clasificarPunto(punto);
}

void calcularDistancia(PuntoTrayectoria *punto) {
   punto->distanciaOrigen = sqrt(
      punto->coordenadas[0] * punto->coordenadas[0] +
      punto->coordenadas[1] * punto->coordenadas[1] +
      punto->coordenadas[2] * punto->coordenadas[2]);
}

void corregirCoordenadas(
   PuntoTrayectoria& punto,
   float desplazamientoX,
   float desplazamientoY,
   float desplazamientoZ
) {
   punto.coordenadas[0] += desplazamientoX;
   punto.coordenadas[1] += desplazamientoY;
   punto.coordenadas[2] += desplazamientoZ;
}

PuntoTrayectoria* obtenerPuntoMasAlejado(
   PuntoTrayectoria puntos[],
   int cantidad
) {
   if (cantidad <= 0) {
      return nullptr;
   }

   PuntoTrayectoria* puntoMasAlejado = &puntos[0];

   for (int i = 1; i < cantidad; ++i) {
      if (puntos[i].distanciaOrigen > puntoMasAlejado->distanciaOrigen) {
         puntoMasAlejado = &puntos[i];
      }
   }

   return puntoMasAlejado;
}



int main() {
   constexpr int capacidadMaxima = 10;
   array<PuntoTrayectoria, capacidadMaxima> trayectoria;
   int cantidadPuntos;

   do {
      cout << "Ingrese la cantidad de puntos a registrar (1-10): ";
      cin >> cantidadPuntos;
   } while (cantidadPuntos < 1 || cantidadPuntos > capacidadMaxima);

   for (int i = 0; i < cantidadPuntos; ++i) {
      PuntoTrayectoria& punto = trayectoria[i];

      cout << "\nPunto " << i + 1 << '\n';
      registrarPunto(punto);
   }

   for (int i = 0; i < cantidadPuntos; ++i) {
      float desplazamientoX;
      float desplazamientoY;
      float desplazamientoZ;

      cout << "\nCorreccion del punto " << i + 1 << '\n';
      cout << "Desplazamiento X: ";
      cin >> desplazamientoX;
      cout << "Desplazamiento Y: ";
      cin >> desplazamientoY;
      cout << "Desplazamiento Z: ";
      cin >> desplazamientoZ;

      corregirCoordenadas(
         trayectoria[i],
         desplazamientoX,
         desplazamientoY,
         desplazamientoZ);
      calcularDistancia(&trayectoria[i]);
      clasificarPunto(trayectoria[i]);
   }

   cout << "\nResultados actualizados:\n";
   for (int i = 0; i < cantidadPuntos; ++i) {
      const PuntoTrayectoria& punto = trayectoria[i];

      cout << "\nID: " << punto.identificador << '\n';
      cout << "Nombre: " << punto.nombre << '\n';
      cout << "Coordenada X: " << punto.coordenadas[0] << '\n';
      cout << "Coordenada Y: " << punto.coordenadas[1] << '\n';
      cout << "Coordenada Z: " << punto.coordenadas[2] << '\n';
      cout << "Distancia al origen: " << punto.distanciaOrigen << '\n';
      cout << "Clasificacion: " << punto.clasificacion << '\n';
   }

   PuntoTrayectoria* puntoMasAlejado =
      obtenerPuntoMasAlejado(trayectoria.data(), cantidadPuntos);

   cout << "\nPunto mas alejado del origen:\n";
   cout << "ID: " << puntoMasAlejado->identificador << '\n';
   cout << "Nombre: " << puntoMasAlejado->nombre << '\n';
   cout << "Coordenada X: " << puntoMasAlejado->coordenadas[0] << '\n';
   cout << "Coordenada Y: " << puntoMasAlejado->coordenadas[1] << '\n';
   cout << "Coordenada Z: " << puntoMasAlejado->coordenadas[2] << '\n';
   cout << "Distancia al origen: " << puntoMasAlejado->distanciaOrigen << '\n';
   cout << "Clasificacion: " << puntoMasAlejado->clasificacion << '\n';

   return 0;
}