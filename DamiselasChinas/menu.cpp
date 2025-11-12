#include <iostream>
#include "damas.h"

void mostrarReglas() {
    std::cout << "\n*** REGLAS DEL JUEGO ***\n";
    std::cout << "1. El tablero es de 10x10 con columnas A-J y filas 0-9.\n";
    std::cout << "2. Cada jugador tiene 20 piezas:\n";
    std::cout << "   - Jugador 'a' empieza arriba.\n";
    std::cout << "   - Jugador 'y' empieza abajo.\n";
    std::cout << "3. Las piezas se mueven en diagonal hacia adelante sobre casillas oscuras.\n";
    std::cout << "4. Si una pieza llega al otro extremo del tablero, se convierte en reina (A o Y).\n";
    std::cout << "5. Las reinas pueden moverse en cualquier diagonal sin limite de distancia.\n";
    std::cout << "6. Cuando se puede capturar una pieza rival, la captura es obligatoria.\n";
    std::cout << "7. Si despues de capturar se puede seguir comiendo, la misma pieza debe continuar (captura encadenada).\n";
    std::cout << "8. Gana el jugador que elimine todas las piezas del rival.\n";
    std::cout << "Presione Enter para volver al menu.\n";
    std::cin.ignore();
    std::cin.get();
}

int main() {
    int opcion;
    do {
        std::cout << "\n*** JUEGO DE DAMAS ***\n";
        std::cout << "1. Ver reglas\n";
        std::cout << "2. Jugar\n";
        std::cout << "3. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1:
            mostrarReglas();
            break;
        case 2:
            jugarDamas();
            break;
        case 3:
            std::cout << "Saliendo del juego.\n";
            break;
        default:
            std::cout << "Opcion invalida.\n";
        }
    } while (opcion != 3);

    return 0;
}