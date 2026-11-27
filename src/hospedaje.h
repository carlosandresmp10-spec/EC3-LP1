#include <string>
#include <vector>

using namespace std;

const int PISOS = 3; // Representan Piso 2, Piso 3 y Piso 4
const int MAX_HAB = 9;

struct RegistroHuesped {
    string dni;
    string nombre;
    int numHabitacion;
    string tipoHabitacion;
    int noches;
    double cargosExtra;
    double totalPagado;
    bool activa;
};

void inicializarHabitaciones(char habitaciones[PISOS][MAX_HAB]);
void mostrarMapaHabitaciones(char habitaciones[PISOS][MAX_HAB]);
void mostrarTarifas();
double obtenerTarifa(int numHabitacion);
string obtenerTipo(int numHabitacion);
bool validarDNI(string dni);
void registrarCheckIn(char habitaciones[PISOS][MAX_HAB], vector<RegistroHuesped>& historial);
void registrarCheckOut(char habitaciones[PISOS][MAX_HAB], vector<RegistroHuesped>& historial);
void listarEstadiasActivas(vector<RegistroHuesped> historial);
void buscarHuespedPorDNI(vector<RegistroHuesped> historial);
void generarReporteTXT(vector<RegistroHuesped> historial, char habitaciones[PISOS][MAX_HAB]);
void leerReporteTXT();
