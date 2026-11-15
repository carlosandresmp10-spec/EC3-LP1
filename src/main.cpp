#include <iostream>
#include <vector>
#include <limits>
#include "hospedaje.h"

using namespace std;

int main() {
    char habitaciones[PISOS][HABITACIONES_POR_PISO];
    vector<RegistroHuesped> historial;

    inicializarHabitaciones(habitaciones);

    int opcion = 0;

    do {
        cout << "\n==========================================" << endl;
        cout << "   SISTEMA DE RECEPCION - HOSPEDAJE D' CARLO" << endl;
        cout << "==========================================" << endl;
        cout << "1. Ver mapa de habitaciones (RF-01)" << endl;
        cout << "2. Consultar tarifario (RF-02)" << endl;
        cout << "3. Registrar Check-In (RF-03, RF-04)" << endl;
        cout << "4. Registrar Check-Out y Cobro (RF-11..14)" << endl;
        cout << "5. Listar estadias activas (RF-06)" << endl;
        cout << "6. Buscar huesped por DNI (RF-20)" << endl;
        cout << "7. Generar reporte de caja TXT (RF-25)" << endl;
        cout << "8. Ver reporte TXT en consola" << endl;
        cout << "9. Salir" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
