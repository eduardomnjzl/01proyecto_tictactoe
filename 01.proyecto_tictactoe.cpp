#include <iostream>
#include <vector>
using namespace std;

// --- Prototipos de funciones ---
void mostrarTablero(const vector<vector<char>>& tablero);
bool realizarJugada(vector<vector<char>>& tablero, int fila, int columna, char jugador);
bool hayGanador(const vector<vector<char>>& tablero, char jugador);
bool tableroLleno(const vector<vector<char>>& tablero);
void reiniciarTablero(vector<vector<char>>& tablero);

int main() {
    vector<vector<char>> tablero(3, vector<char>(3, ' '));
    char jugadorActual = 'X';
    bool juegoTerminado = false;
    char opcion;

    cout << "=== TIC TAC TOE ===" << endl;

    do {
        reiniciarTablero(tablero);
        juegoTerminado = false;
        jugadorActual = 'X';

        while (!juegoTerminado) {
            mostrarTablero(tablero);

            int fila, columna;
            cout << "Turno del jugador " << jugadorActual << endl;
            cout << "Ingrese fila (1-3): ";
            cin >> fila;
            cout << "Ingrese columna (1-3): ";
            cin >> columna;

            // Validación de entrada
            if (cin.fail() || fila < 1 || fila > 3 || columna < 1 || columna > 3) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "⚠️ Entrada inválida. Intente de nuevo.\n";
                continue;
            }

            // Intentar realizar jugada
            if (!realizarJugada(tablero, fila - 1, columna - 1, jugadorActual)) {
                cout << "⚠️ Casilla ocupada. Elija otra.\n";
                continue;
            }

            // Comprobar si hay ganador o empate
            if (hayGanador(tablero, jugadorActual)) {
                mostrarTablero(tablero);
                cout << "🎉 ¡Jugador " << jugadorActual << " gana! 🎉\n";
                juegoTerminado = true;
            } else if (tableroLleno(tablero)) {
                mostrarTablero(tablero);
                cout << "🤝 ¡Empate!\n";
                juegoTerminado = true;
            } else {
                // Cambiar turno
                jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
            }
        }

        cout << "¿Desea jugar de nuevo? (s/n): ";
        cin >> opcion;
    } while (opcion == 's' || opcion == 'S');

    cout << "Gracias por jugar. ¡Hasta pronto!\n";
    return 0;
}

// --- Funciones auxiliares ---

// Muestra el tablero actual
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

// Intenta colocar la ficha del jugador
bool realizarJugada(vector<vector<char>>& tablero, int fila, int columna, char jugador) {
    if (tablero[fila][columna] == ' ') {
        tablero[fila][columna] = jugador;
        return true;
    }
    return false;
}

// Comprueba si el jugador ha ganado
bool hayGanador(const vector<vector<char>>& tablero, char jugador) {
    // Filas y columnas
    for (int i = 0; i < 3; i++) {
        if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
            (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador))
            return true;
    }
    // Diagonales
    if ((tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
        (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador))
        return true;

    return false;
}

// Verifica si todas las casillas están ocupadas
bool tableroLleno(const vector<vector<char>>& tablero) {
    for (const auto& fila : tablero)
        for (char celda : fila)
            if (celda == ' ')
                return false;
    return true;
}

// Reinicia el tablero
void reiniciarTablero(vector<vector<char>>& tablero) {
    for (auto& fila : tablero)
        for (char& celda : fila)
            celda = ' ';
}