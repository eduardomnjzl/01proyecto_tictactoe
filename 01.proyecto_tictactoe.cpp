#include <iostream>
#include <vector>
#include <limits> 

using namespace std;

// --- Prototipos de funciones ---
void mostrarTablero(const vector<vector<char>>& tablero);
// La lógica de mapeo se ajusta internamente en esta función.
bool realizarJugada(vector<vector<char>>& tablero, int posicion, char jugador); 
bool hayGanador(const vector<vector<char>>& tablero, char jugador);
bool tableroLleno(const vector<vector<char>>& tablero);
void inicializarTablero(vector<vector<char>>& tablero); 

// ------------------------------------------------------------------
// --- FUNCIÓN PRINCIPAL Y LÓGICA DEL JUEGO ---
// ------------------------------------------------------------------

int main() {
    // Uso de arreglo/matriz (vector<vector<char>>) para el tablero.
    vector<vector<char>> tablero(3, vector<char>(3)); 
    char jugadorActual = 'X';
    char opcion;

    cout << "=== 💡 TIC TAC TOE ===\n";
    cout << "  Jugador 1: X  |  Jugador 2: O\n";

    // Mejora Opcional: Reinicio de Juego (Ciclo do-while)
    do {
        inicializarTablero(tablero); // Reinicia el tablero con 7-8-9...
        bool juegoTerminado = false;
        jugadorActual = 'X';

        // Estructura de Control: Ciclo principal del juego
        while (!juegoTerminado) {
            mostrarTablero(tablero);

            int posicion;
            cout << "Turno del Jugador " << jugadorActual << ", elige una posición (1-9, como en un teclado): ";
            
            // --- Validación de Entradas: 1. Formato numérico ---
            if (!(cin >> posicion)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "⚠️ Entrada inválida. Debes ingresar un número entero.\n";
                continue;
            }

            // --- Validación de Entradas: 2. Rango 1-9 ---
            if (posicion < 1 || posicion > 9) {
                cout << "⚠️ Posición fuera de rango. Elije un número entre 1 y 9.\n";
                continue;
            }

            // Realizar Jugada y Validación de Entradas: 3. Casilla ya marcada
            if (!realizarJugada(tablero, posicion, jugadorActual)) {
                cout << "⚠️ Casilla ya ocupada. Elija otra.\n";
                continue;
            }

            // --- Detección de Ganador o Empate ---
            if (hayGanador(tablero, jugadorActual)) {
                mostrarTablero(tablero);
                cout << "🎉 ¡El Jugador " << jugadorActual << " ha GANADO! 🎉\n";
                juegoTerminado = true;
            } else if (tableroLleno(tablero)) {
                mostrarTablero(tablero);
                cout << "🤝 ¡Empate!\n";
                juegoTerminado = true;
            } else {
                // Estructura de Control: Alternar jugador
                jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
            }
        }

        cout << "¿Desea jugar de nuevo? (s/n): ";
        cin >> opcion;
    } while (opcion == 's' || opcion == 'S');

    cout << "\nGracias por jugar. ¡Hasta pronto!\n";
    return 0;
}

// ------------------------------------------------------------------
// --- IMPLEMENTACIÓN DE FUNCIONES AUXILIARES CON LAYOUT 7-8-9 ---
// ------------------------------------------------------------------

/**
 * @brief Inicializa el tablero con los números del 7 al 1 como guía, simulando un teclado.
 */
void inicializarTablero(vector<vector<char>>& tablero) {
    // Fila 0: 7, 8, 9
    tablero[0][0] = '7'; tablero[0][1] = '8'; tablero[0][2] = '9';
    // Fila 1: 4, 5, 6
    tablero[1][0] = '4'; tablero[1][1] = '5'; tablero[1][2] = '6';
    // Fila 2: 1, 2, 3
    tablero[2][0] = '1'; tablero[2][1] = '2'; tablero[2][2] = '3';
}

/**
 * @brief Dibuja el estado actual del tablero. (No requiere cambios, solo muestra la matriz).
 */
void mostrarTablero(const vector<vector<char>>& tablero) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << tablero[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

/**
 * @brief Intenta colocar la ficha del jugador en la posición (1-9) elegida, 
 * usando el mapeo de teclado numérico.
 *
 * @param posicion Número de la casilla (1-9)
 * @return true Si la jugada fue válida y se realizó.
 * @return false Si la casilla ya estaba ocupada ('X' u 'O').
 */
bool realizarJugada(vector<vector<char>>& tablero, int posicion, char jugador) {
    int fila, columna;

    // --- LÓGICA DE MAPEO 7-8-9 A ÍNDICES DE MATRIZ ---
    
    // Mapeo de columna: El residuo de (posicion - 1) % 3 es constante (0, 1, 2)
    columna = (posicion - 1) % 3;
    
    // Mapeo de fila: 
    if (posicion >= 7) {
        fila = 0; // Fila superior (7, 8, 9)
    } else if (posicion >= 4) {
        fila = 1; // Fila media (4, 5, 6)
    } else {
        fila = 2; // Fila inferior (1, 2, 3)
    }
    
    // El caso especial del '9' requiere atención si se usa el módulo, pero el mapeo por rangos es más robusto.
    // Una alternativa matemática limpia es: fila = 2 - ((posicion - 1) / 3)

    // La casilla está libre si su contenido es un número (guía)
    if (tablero[fila][columna] != 'X' && tablero[fila][columna] != 'O') {
        tablero[fila][columna] = jugador;
        return true;
    }
    return false; // Casilla ocupada.
}

/**
 * @brief Comprueba si el jugador ha ganado verificando filas, columnas y diagonales. (No requiere cambios).
 */
bool hayGanador(const vector<vector<char>>& tablero, char jugador) {
    // Filas y columnas
    for (int i = 0; i < 3; i++) {
        if (tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) return true;
        if (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador) return true;
    }
    // Diagonales
    if ((tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
        (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador))
        return true;

    return false;
}

/**
 * @brief Verifica si todas las casillas están ocupadas por 'X' o 'O'. (No requiere cambios).
 */
bool tableroLleno(const vector<vector<char>>& tablero) {
    for (const auto& fila : tablero) {
        for (char celda : fila) {
            // Si la celda aún contiene un número ('1' a '9'), significa que está disponible.
            if (celda >= '1' && celda <= '9') {
                return false; 
            }
        }
    }
    return true;
}