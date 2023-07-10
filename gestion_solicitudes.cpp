#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct tSolicitud{
    int codigo;
    string nombre, apellido, dni;
};

const int MAX_ARTICULOS = 100;

typedef tSolicitud tArray[MAX_ARTICULOS];

struct tContador{
    tArray solicitudes; 
    int num_articulos = 0; 
};

void cargar_datos(tContador& lista); 
void guardar_datos(tContador& lista); 
void mostrar_menu();
void alta_articulo(tContador& lista);
void baja_articulo(tContador& lista);
void modificar_articulo(tContador& lista);
void listar_articulo(tContador lista);
void buscar_articulo(tContador lista);

int main (){

    mostrar_menu();

    return 0;
}

void mostrar_menu(){
    tContador lista;

    cargar_datos(lista);

    int opcion = 0; 

    do{
        cout << "\n----- GESTION DE SOLICITUDES - BIUTY-SAND -----" << endl;
        cout << "\n1. Dar de alta una solicitud." << endl;
        cout << "2. Dar de baja una solicitud." << endl;
        cout << "3. Modificar una solicitud." << endl;
        cout << "4. Listar todas las solicitudes." << endl;
        cout << "5. Buscar una solicitud." << endl;
        cout << "6. Salir del programa." << endl;

        cout << "\nIngrese la opcion que desea realizar (1 - 6): "; cin >> opcion;
        cin.ignore(); 

        switch(opcion){
            case 1:
                alta_articulo(lista);
                break;
            case 2: 
                baja_articulo(lista);
                break;
            case 3:
                modificar_articulo(lista);
                break;
            case 4:
                listar_articulo(lista);
                break;
            case 5:
                buscar_articulo(lista);
                break;
            case 6:
                guardar_datos(lista);
                cout << "Saliendo del programa..." << endl;
                exit(0);
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl; 
        }
    } while (opcion != 6); 
}

void cargar_datos(tContador& lista){
    ifstream archivo_solicitudes;

    archivo_solicitudes.open("solicitudes.csv");

    if (archivo_solicitudes.is_open()){
        lista.num_articulos = 0; 

        string linea; 
        
        while(getline(archivo_solicitudes, linea)){    
            stringstream ss(linea);

            string codigo_str, nombre, apellido, dni; 

            getline(ss, codigo_str, ','); 
            getline(ss, nombre, ','); 
            getline(ss, apellido, ','); 
            getline(ss, dni, ','); 

            int codigo = stoi(codigo_str);

            lista.solicitudes[lista.num_articulos].codigo = codigo;
            lista.solicitudes[lista.num_articulos].nombre = nombre;
            lista.solicitudes[lista.num_articulos].apellido = apellido;
            lista.solicitudes[lista.num_articulos].dni = dni;

            lista.num_articulos++;
        }
        
        archivo_solicitudes.close(); 

    } else {
        cout << "No se encontro el archivo. Una vez finalizado, se creara un archivo nuevo" << endl;
    }
}

void guardar_datos(tContador& lista){
    ofstream archivo_solicitudes; 

    archivo_solicitudes.open("solicitudes.csv"); 

    if (archivo_solicitudes.is_open()){
        
        for (int i = 0; i < lista.num_articulos; i++) {
            archivo_solicitudes << lista.solicitudes[i].codigo << "," << lista.solicitudes[i].nombre << "," << lista.solicitudes[i].apellido  << "," << lista.solicitudes[i].dni<< endl;
        }

        archivo_solicitudes.close();

    } else {
        cout << "Error al guardar los datos." << endl;
    }
}

void alta_articulo(tContador& lista){
    tSolicitud nueva_solicitud;

    string opcion; 

    cout << "\n----- Agregar una solicitud -----\n" << endl;

    do {
        if(lista.num_articulos >= MAX_ARTICULOS){
            cout << "No se puede agregar mas solicitudes." << endl;
            return;
        }

        cout << "Ingrese el nombre: "; getline (cin, nueva_solicitud.nombre);
        cout << "Ingrese el primer apellido: "; cin >> nueva_solicitud.apellido;
        cout << "Ingrese el dni: "; cin >> nueva_solicitud.dni;

        nueva_solicitud.codigo = 100 + lista.num_articulos;

        if (nueva_solicitud.codigo == lista.solicitudes[lista.num_articulos -1].codigo){
            nueva_solicitud.codigo++;
        };

        cout << "\nLa solicitud del cliente " << nueva_solicitud.nombre << " " << nueva_solicitud.apellido << " fue agregada correctamente con el codigo #" << nueva_solicitud.codigo << endl;

        lista.solicitudes[lista.num_articulos] = nueva_solicitud;
        lista.num_articulos++; 

        cout << "\nDesea agregar otra solicitud? (s/n) "; cin >> opcion;
        cin.ignore();
        cout << endl;
        
    } while (opcion == "s"); 

}

void baja_articulo(tContador& lista){
    int codigo;

    cout << "\n----- Eliminar una solicitud -----\n" << endl;

    cout << "Ingrese el codigo de la solicitud que desea eliminar: "; cin >> codigo;
    cin.ignore();

    bool encontrado = false; 

    for (int i = 0; i < lista.num_articulos; i++) {
        if (lista.solicitudes[i].codigo == codigo) {
            encontrado = true;

            for (int j = i; j < lista.num_articulos - 1; j++) {
                lista.solicitudes[j] = lista.solicitudes[j + 1];
            }

            lista.num_articulos--;

            cout << "\nLa solicitud ha sido dado de baja correctamente." << endl;
            break; 
        }
    }

    if (!encontrado) {
        cout << "Solicitud no encontrada." << endl;
    };
}

void modificar_articulo(tContador& lista){
    int codigo, opcion;

    cout << "\n----- Modificar una solicitud -----\n" << endl;

    cout << "Ingrese el codigo de la solicitud que desea modificar: "; cin >> codigo;
    cin.ignore();

    bool encontrado = false;

    for (int i = 0; i < lista.num_articulos; i++) {
        if (lista.solicitudes[i].codigo == codigo) {
            encontrado = true;

            cout << "\nSolicitud encontrada!\n" << endl;
            cout << "1. Nombre" << endl;
            cout << "2. Apellido" << endl;
            cout << "3. DNI" << endl;

            cout << "\nIngrese la opcion que desea modificar (1 - 3): "; cin >> opcion;
            cin.ignore();

            switch(opcion){
                case 1:
                    cout << "Ingrese el nuevo nombre: "; getline(cin, lista.solicitudes[i].nombre);
                    break;
                case 2:
                    cout << "Ingrese el nuevo apellido: "; cin >> lista.solicitudes[i].apellido;
                    break;
                case 3:
                    cout << "Ingrese el nuevo DNI: "; cin >> lista.solicitudes[i].dni;
                    break;
                default:
                    cout << "La opcion ingresada es incorrecta" << endl;
            } 

            cout << "\nLa solicitud ha sido modificada correctamente." << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "Solicitud no encontrada." << endl;
    }
}

void listar_articulo(tContador lista){
    cout << "\n----- Lista de solicitudes -----\n" << endl;

     if (lista.num_articulos == 0) {
        cout << "No hay solicitudes cargadas para mostrar." << endl;
        return;
    }

    for (int i = 0; i < lista.num_articulos; i++) {

        cout << "Codigo: " << lista.solicitudes[i].codigo << endl;
        cout << "Nombre: " << lista.solicitudes[i].nombre << endl;
        cout << "Apellido: " << lista.solicitudes[i].apellido << endl;
        cout << "DNI: " << lista.solicitudes[i].dni << endl;
        cout << endl;
        cout << "-----------------------------" << endl;
        cout << endl;
    }
}

void buscar_articulo(tContador lista){
    int codigo;
    
    cout << "\n----- Buscar una solicitud -----\n" << endl;

    cout << "Ingrese el codigo de la solicitud: "; cin >> codigo;

    bool encontrado = false;

    for (int i = 0; i < lista.num_articulos; i++) {
        if (lista.solicitudes[i].codigo == codigo) {
            
            cout << "\nSolicitud encontrada!\n" << endl;
            cout << "Codigo: " << lista.solicitudes[i].codigo << endl;
            cout << "Nombre: " << lista.solicitudes[i].nombre << endl;
            cout << "Apellido: " << lista.solicitudes[i].apellido << endl;
            cout << "DNI: " << lista.solicitudes[i].dni << endl;
            
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Solicitud no encontrada." << endl;
    }
}