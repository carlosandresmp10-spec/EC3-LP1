#pragma once
#include <string>
#include <vector>

using namespace std;

// Constantes del hospedaje
const int PISOS = 3;
const int HABITACIONES_POR_PISO = 5;

// Estructura de datos para cada huesped
struct RegistroHuesped {
    string dni;
    string nombre;
    int numHabitacion;
    int noches;
    double cargosExtra;
    double totalPagado;
    bool activa; // true = hospedado, false = check-out realizado
};

// Prototipos de funciones
void inicializarHabitaciones(char habitaciones[PISOS][HABITACIONES_POR_PISO]);
void mostrarMapaHabitaciones(char habitaciones[PISOS][HABITACIONES_POR_PISO]);
void mostrarTarifas();
double obtenerTarifaPorPiso(int piso);
bool validarDNI(string dni);
void registrarCheckIn(char habitaciones[PISOS][HABITACIONES_POR_PISO], vector<RegistroHuesped> &historial);
void registrarCheckOut(char habitaciones[PISOS][HABITACIONES_POR_PISO], vector<RegistroHuesped> &historial);
void listarEstadiasActivas(vector<RegistroHuesped> historial);
void buscarHuespedPorDNI(vector<RegistroHuesped> historial);
void generarReporteTXT(vector<RegistroHuesped> historial, char habitaciones[PISOS][HABITACIONES_POR_PISO]);
void leerReporteTXT();
