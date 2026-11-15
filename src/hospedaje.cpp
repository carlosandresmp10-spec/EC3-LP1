#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "hospedaje.h"

using namespace std;

void inicializarHabitaciones(char habitaciones[PISOS][HABITACIONES_POR_PISO]) {
    for (int i = 0; i < PISOS; i++) {
        for (int j = 0; j < HABITACIONES_POR_PISO; j++) {
            habitaciones[i][j] = 'L';
        }
    }
}

double obtenerTarifaPorPiso(int piso) {
    if (piso == 1) return 60.00;
    if (piso == 2) return 90.00;
    return 120.00;
}

void mostrarTarifas() {
    cout << "\n--- TARIFARIO HOSPEDAJE D' CARLO ---" << endl;
    cout << left << setw(18) << "Piso" << setw(18) << "Categoria" << "Tarifa por Noche" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << left << setw(18) << "Piso 1 (101-105)" << setw(18) << "Simple" << "S/ 60.00" << endl;
    cout << left << setw(18) << "Piso 2 (201-205)" << setw(18) << "Doble" << "S/ 90.00" << endl;
    cout << left << setw(18) << "Piso 3 (301-305)" << setw(18) << "Matrimonial" << "S/ 120.00" << endl;
    cout << "Nota: Estadias mayores a 3 noches tienen 10% de descuento." << endl;
}

void mostrarMapaHabitaciones(char habitaciones[PISOS][HABITACIONES_POR_PISO]) {
    cout << "\n--- MAPA DE HABITACIONES ([L] Libre | [O] Ocupada) ---" << endl;
    for (int i = 0; i < PISOS; i++) {
        cout << "Piso " << (i + 1) << ":  ";
        for (int j = 0; j < HABITACIONES_POR_PISO; j++) {
            int numHab = (i + 1) * 100 + (j + 1);
            cout << numHab << " [" << habitaciones[i][j] << "]   ";
        }
        cout << endl;
    }
}

bool validarDNI(string dni) {
    if (dni.length() != 8) return false;
    for (int i = 0; i < dni.length(); i++) {
        if (!isdigit(dni[i])) return false;
    }
    return true;
}

void registrarCheckIn(char habitaciones[PISOS][HABITACIONES_POR_PISO], vector<RegistroHuesped> &historial) {
    RegistroHuesped nuevo;
    cout << "\n--- REGISTRO DE CHECK-IN ---" << endl;

    do {
        cout << "Ingrese DNI del huesped (8 digitos): ";
        cin >> nuevo.dni;
        if (!validarDNI(nuevo.dni)) {
            cout << "Error: El DNI debe tener exactamente 8 digitos numericos." << endl;
        }
    } while (!validarDNI(nuevo.dni));

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese nombre completo del huesped: ";
    getline(cin, nuevo.nombre);

    mostrarMapaHabitaciones(habitaciones);

    int piso, col;
    bool habValida = false;
    do {
        cout << "Ingrese numero de habitacion (ej. 101, 203, 305): ";
        if (!(cin >> nuevo.numHabitacion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Ingrese un numero valido." << endl;
            continue;
        }

        piso = (nuevo.numHabitacion / 100) - 1;
        col = (nuevo.numHabitacion % 100) - 1;

        if (piso >= 0 && piso < PISOS && col >= 0 && col < HABITACIONES_POR_PISO) {
            if (habitaciones[piso][col] == 'L') {
                habValida = true;
            } else {
                cout << "Error: La habitacion " << nuevo.numHabitacion << " ya se encuentra ocupada." << endl;
            }
        } else {
            cout << "Error: Numero de habitacion inexistente." << endl;
        }
    } while (!habValida);

    do {
        cout << "Cantidad de noches de estadia: ";
        if (!(cin >> nuevo.noches) || nuevo.noches <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Ingrese una cantidad de noches mayor a 0." << endl;
            nuevo.noches = 0;
        }
    } while (nuevo.noches <= 0);

    nuevo.cargosExtra = 0.0;
    nuevo.totalPagado = 0.0;
    nuevo.activa = true;

    habitaciones[piso][col] = 'O';
    historial.push_back(nuevo);

    cout << "Check-in registrado con exito en la habitacion " << nuevo.numHabitacion << "." << endl;
}

void registrarCheckOut(char habitaciones[PISOS][HABITACIONES_POR_PISO], vector<RegistroHuesped> &historial) {
    if (historial.empty()) {
        cout << "\nNo hay registros en el sistema." << endl;
        return;
    }

    string dniBuscado;
    cout << "\n--- PROCESO DE CHECK-OUT Y COBRO ---" << endl;
    cout << "Ingrese DNI del huesped a retirar: ";
    cin >> dniBuscado;

    bool encontrado = false;
    for (int i = 0; i < historial.size(); i++) {
        if (historial[i].dni == dniBuscado && historial[i].activa) {
            encontrado = true;
            int piso = (historial[i].numHabitacion / 100) - 1;
            int col = (historial[i].numHabitacion % 100) - 1;

            do {
                cout << "Ingrese cargos adicionales (frigobar/cochera) en S/ (0 si no hay): ";
                if (!(cin >> historial[i].cargosExtra) || historial[i].cargosExtra < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: El monto no puede ser negativo." << endl;
                    historial[i].cargosExtra = -1;
                }
            } while (historial[i].cargosExtra < 0);

            double tarifa = obtenerTarifaPorPiso(piso + 1);
            double subtotal = historial[i].noches * tarifa;
            double descuento = 0.0;
            if (historial[i].noches > 3) {
                descuento = subtotal * 0.10;
            }

            historial[i].totalPagado = (subtotal - descuento) + historial[i].cargosExtra;
            historial[i].activa = false;

            habitaciones[piso][col] = 'L';

            cout << fixed << setprecision(2);
            cout << "\n--- RESUMEN DE PAGO ---" << endl;
            cout << "Huesped: " << historial[i].nombre << endl;
            cout << "Habitacion liberada: " << historial[i].numHabitacion << endl;
            cout << "Subtotal (" << historial[i].noches << " noches): S/ " << subtotal << endl;
            cout << "Descuento aplicado (10%): -S/ " << descuento << endl;
            cout << "Cargos adicionales: S/ " << historial[i].cargosExtra << endl;
            cout << "TOTAL A PAGAR: S/ " << historial[i].totalPagado << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontro un huesped activo con el DNI " << dniBuscado << "." << endl;
    }
}

void listarEstadiasActivas(vector<RegistroHuesped> historial) {
    cout << "\n--- HUESPEDES ACTUALMENTE ALOJADOS ---" << endl;
    bool hayActivos = false;

    cout << left << setw(12) << "DNI" << setw(25) << "Nombre" << setw(12) << "Habitacion" << "Noches" << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (int i = 0; i < historial.size(); i++) {
        if (historial[i].activa) {
            hayActivos = true;
            cout << left << setw(12) << historial[i].dni 
                 << setw(25) << historial[i].nombre 
                 << setw(12) << historial[i].numHabitacion 
                 << historial[i].noches << endl;
        }
    }

    if (!hayActivos) {
        cout << "No hay huespedes alojados en este momento." << endl;
    }
}

void buscarHuespedPorDNI(vector<RegistroHuesped> historial) {
    if (historial.empty()) {
        cout << "\nEl historial esta vacio." << endl;
        return;
    }

    string dniBuscado;
    cout << "\n--- BUSQUEDA DE HUESPED ---" << endl;
    cout << "Ingrese DNI a consultar: ";
    cin >> dniBuscado;

    bool encontrado = false;
    cout << fixed << setprecision(2);
    for (int i = 0; i < historial.size(); i++) {
        if (historial[i].dni == dniBuscado) {
            encontrado = true;
            cout << "Nombre: " << historial[i].nombre << endl;
            cout << "Habitacion: " << historial[i].numHabitacion << endl;
            cout << "Noches: " << historial[i].noches << endl;
            if (historial[i].activa) {
                cout << "Estado: Hospedado (Activo)" << endl;
            } else {
                cout << "Estado: Check-out realizado" << endl;
                cout << "Total pagado: S/ " << historial[i].totalPagado << endl;
            }
            cout << "-----------------------------" << endl;
        }
    }

    if (!encontrado) {
        cout << "No existen registros asociados al DNI " << dniBuscado << "." << endl;
    }
}

void generarReporteTXT(vector<RegistroHuesped> historial, char habitaciones[PISOS][HABITACIONES_POR_PISO]) {
    ofstream archivo("data/reporte_hospedaje.txt");

    if (!archivo.is_open()) {
        archivo.open("reporte_hospedaje.txt");
    }

    if (!archivo.is_open()) {
        cout << "Error: No se pudo crear el archivo de reporte." << endl;
        return;
    }

    int ocupadas = 0;
    int totalHabitaciones = PISOS * HABITACIONES_POR_PISO;
    for (int i = 0; i < PISOS; i++) {
        for (int j = 0; j < HABITACIONES_POR_PISO; j++) {
            if (habitaciones[i][j] == 'O') {
                ocupadas++;
            }
        }
    }
    double porcentajeOcupacion = ((double)ocupadas / totalHabitaciones) * 100.0;
    double ingresosTotales = 0.0;

    archivo << "==========================================================" << endl;
    archivo << "       REPORTE DE CIERRE DE CAJA - HOSPEDAJE D' CARLO     " << endl;
    archivo << "==========================================================" << endl;
    archivo << fixed << setprecision(2);
    archivo << "Ocupacion actual: " << ocupadas << "/" << totalHabitaciones 
            << " (" << porcentajeOcupacion << "%)" << endl;
    archivo << "----------------------------------------------------------" << endl;
    archivo << left << setw(12) << "DNI" << setw(22) << "Huesped" 
            << setw(8) << "Hab." << setw(10) << "Estado" << "Pagado (S/)" << endl;
    archivo << "----------------------------------------------------------" << endl;

    for (int i = 0; i < historial.size(); i++) {
        string estadoTexto = historial[i].activa ? "Activo" : "Cerrado";
        archivo << left << setw(12) << historial[i].dni 
                << setw(22) << historial[i].nombre.substr(0, 20)
                << setw(8) << historial[i].numHabitacion 
                << setw(10) << estadoTexto
                << historial[i].totalPagado << endl;

        if (!historial[i].activa) {
            ingresosTotales += historial[i].totalPagado;
        }
    }

    archivo << "----------------------------------------------------------" << endl;
    archivo << "INGRESOS TOTALES RECAUDADOS EN CAJA: S/ " << ingresosTotales << endl;
    archivo << "==========================================================" << endl;

    archivo.close();
    cout << "\nReporte generado exitosamente (reporte_hospedaje.txt)." << endl;
}

void leerReporteTXT() {
    ifstream archivo("data/reporte_hospedaje.txt");
    if (!archivo.is_open()) {
        archivo.open("reporte_hospedaje.txt");
    }

    if (!archivo.is_open()) {
        cout << "\nAun no se ha generado ningun archivo de reporte." << endl;
        return;
    }

    cout << "\n";
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}
