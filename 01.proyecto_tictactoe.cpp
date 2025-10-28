#include <iostream>
#include <vector>
#include <limits> 
#include <string>

using namespace std;

// --- Prototipos de funciones ---
void mostrarTablero(const vector<vector<char>>& tablero);
bool realizarJugada(vector<vector<char>>& tablero, int posicion, char jugador); 
bool hayGanador(const vector<vector<char>>& tablero, char jugador);
bool tableroLleno(const vector<vector<char>>& tablero);
void inicializarTablero(vector<vector<char>>& tablero); 

// ------------------------------------------------------------------
// --- FUNCIÓN PRINCIPAL (main) ---
// ------------------------------------------------------------------

int main() {
    vector<vector<char>> tablero(3, vector<char>(3)); 
    char jugadorActual = 'X'; 
    char opcion;

    cout << "=== 💡 PROYECTO TIC TAC TOE ===\n";
    cout << "  NOTA: Jugador 1 usa 'X' | Jugador 2 usa 'O'\n"; // Solo nota informativa

    do {
        inicializarTablero(tablero); 
        bool juegoTerminado = false;
        jugadorActual = 'X';

        while (!juegoTerminado) {
            mostrarTablero(tablero);
            
            // Define el nombre del jugador: SOLO "Jugador 1" o "Jugador 2"
            string nombreJugador = (jugadorActual == 'X') ? "Jugador 1" : "Jugador 2";

            int posicion;
            // 🎯 MENSAJE DE TURNO: Solo usa la variable 'nombreJugador'
            cout << "➡️ Turno de " << nombreJugador << ", elige una posición (1-9): ";
            
            // Validación de entrada (Formato)
            if (!(cin >> posicion)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "⚠️ Entrada inválida. Debes ingresar un número entero.\n";
                continue;
            }

            // Validación de entrada (Rango)
            if (posicion < 1 || posicion > 9) {
                cout << "⚠️ Posición fuera de rango. Elije un número entre 1 y 9.\n";
                continue;
            }

            // Realizar Jugada y Validación de entrada (Casilla ocupada)
            if (!realizarJugada(tablero, posicion, jugadorActual)) {
                cout << "⚠️ Casilla ya ocupada. Elija otra.\n";
                continue;
            }

            // Detección de Ganador o Empate
            if (hayGanador(tablero, jugadorActual)) {
                mostrarTablero(tablero);
                // Define el ganador: SOLO "Jugador 1" o "Jugador 2"
                string ganador = (jugadorActual == 'X') ? "Jugador 1" : "Jugador 2";
                cout << "🏆 ¡El " << ganador << " ha GANADO la partida! ¡Felicidades! 🏆\n";
                juegoTerminado = true;
            } else if (tableroLleno(tablero)) {
                mostrarTablero(tablero);
                cout << "🤝 ¡Empate! Nadie ha ganado.\n";
                juegoTerminado = true;
            } else {
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
// --- IMPLEMENTACIÓN DE FUNCIONES (LÓGICA TECLADO 7-8-9) ---
// ------------------------------------------------------------------

/**
 * @brief Inicializa el tablero con los números de guía (7-8-9, 4-5-6, 1-2-3).
 */
void inicializarTablero(vector<vector<char>>& tablero) {
    tablero[0][0] = '7'; tablero[0][1] = '8'; tablero[0][2] = '9';
    tablero[1][0] = '4'; tablero[1][1] = '5'; tablero[1][2] = '6';
    tablero[2][0] = '1'; tablero[2][1] = '2'; tablero[2][2] = '3';
}

/**
 * @brief Dibuja el estado actual del tablero.
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
 * @brief Coloca la ficha del jugador en la posición usando el mapeo de teclado numérico.
 */
bool realizarJugada(vector<vector<char>>& tablero, int posicion, char jugador) {
    int fila, columna;

    // Lógica de mapeo para teclado (7-8-9 en la primera fila, 1-2-3 en la última)
    columna = (posicion - 1) % 3;
    
    if (posicion >= 7) {
        fila = 0; 
    } else if (posicion >= 4) {
        fila = 1; 
    } else {
        fila = 2; 
    }
    
    // La casilla está libre si no contiene 'X' ni 'O'
    if (tablero[fila][columna] != 'X' && tablero[fila][columna] != 'O') {
        tablero[fila][columna] = jugador;
        return true;
    }
    return false;
}

/**
 * @brief Comprueba si el jugador actual ha ganado (Filas, Columnas y Diagonales).
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
 * @brief Verifica si el tablero está completamente lleno.
 */
bool tableroLleno(const vector<vector<char>>& tablero) {
    for (const auto& fila : tablero) {
        for (char celda : fila) {
            if (celda >= '1' && celda <= '9') {
                return false; 
            }
        }
    }
    return true;
}