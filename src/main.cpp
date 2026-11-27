#include <iostream>
#include <vector>
#include "hospedaje.h"

using namespace std;

int main() {
    char habitaciones[PISOS][MAX_HAB];
    vector<RegistroHuesped> historial;

    inicializarHabitaciones(habitaciones);

    int opcion = 0;

    do {
        cout << "\n==========================================" << endl;
        cout << "   SISTEMA DE RECEPCION - HOSPEDAJE D' CARLO" << endl;
        cout << "==========================================" << endl;
        cout << "1. Ver mapa de habitaciones" << endl;
        cout << "2. Consultar tarifario" << endl;
        cout << "3. Registrar Check-In" << endl;
        cout << "4. Registrar Check-Out y Cobro" << endl;
        cout << "5. Listar estadias activas" << endl;
        cout << "6. Buscar huesped por DNI" << endl;
        cout << "7. Generar reporte de caja TXT" << endl;
        cout << "8. Ver reporte TXT en consola" << endl;
        cout << "9. Salir" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida. Por favor ingrese un numero del 1 al 9." << endl;
            continue;
        }

        switch (opcion) {
        case 1:
            mostrarMapaHabitaciones(habitaciones);
            break;
        case 2:
            mostrarTarifas();
            break;
        case 3:
            registrarCheckIn(habitaciones, historial);
            break;
        case 4:
            registrarCheckOut(habitaciones, historial);
            break;
        case 5:
            listarEstadiasActivas(historial);
            break;
        case 6:
            buscarHuespedPorDNI(historial);
            break;
        case 7:
            generarReporteTXT(historial, habitaciones);
            break;
        case 8:
            leerReporteTXT();
            break;
        case 9:
            cout << "Cerrando sistema. Hasta luego." << endl;
            break;
        default:
            cout << "Opcion fuera de rango. Intente nuevamente." << endl;
        }
    } while (opcion != 9);

    return 0;
}
