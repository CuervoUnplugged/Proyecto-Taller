#include <iostream>
#include "damas.h"

void menuPrincipal() {
    int opcion;
    bool salir = false;

    do {
        std::cout << "\n*** BIENVENIDO AL JUEGO DE DAMAS ***" << std::endl;
        std::cout << "1. Ver reglas del juego" << std::endl;
        std::cout << "2. Iniciar partida de Damas" << std::endl;
        std::cout << "3. Probar version grafica (SFML)" << std::endl;
        std::cout << "4. Terminar programa" << std::endl;
        std::cout << "Selecciona una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 3:
            std::cout << "\n*** Cargando Damas en SFML ***" << std::endl;
            std::cout << "Aviso: La modalidad grafica no esta disponible por ahora. Regresando al menu." << std::endl;
            break;
        case 1:
            std::cout << "\n*** Instrucciones del Juego ***" << std::endl;
            std::cout << "1. Tablero de 10x10 casillas." << std::endl;
            std::cout << "2. 20 fichas por jugador al inicio." << std::endl;
            std::cout << "3. Movimientos diagonales solo hacia adelante." << std::endl;
            std::cout << "4. Alcanzar el borde opuesto convierte la ficha en reina." << std::endl;
            std::cout << "5. Gana quien elimine todas las fichas rivales." << std::endl;
            std::cout << "6. Las reinas pueden desplazarse libremente en diagonal." << std::endl;
            std::cout << "7. Introduce coordenadas asi: fila_origen col_origen fila_destino col_destino." << std::endl;
            break;
        case 2:
            std::cout << "\n*** Comenzando Juego de Damas ***" << std::endl;
            jugarDamas();
            break;
        case 4:
            std::cout << "Cerrando el programa. ¡Hasta luego!" << std::endl;
            salir = true;
            break;
        default:
            std::cout << "Eleccion no reconocida. Prueba otra vez." << std::endl;
        }
    } while (!salir);
}

int main() {
    menuPrincipal();
    return 0;
}