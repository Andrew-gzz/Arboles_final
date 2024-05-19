#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>

using namespace std;

class nodo {
public:
    int ID;
    char User_Name[25];
    nodo* izq;
    nodo* der;
};

class arbol {
public:
    nodo* raiz;
    arbol() {
        this->raiz = nullptr;
    }
    ~arbol() {
        // Destructor para liberar recursos si es necesario
    }
    void preOrden(nodo* arbol) {
        if (arbol != nullptr) {
            printf("ID = %d\tname = %s\n", arbol->ID, arbol->User_Name);
            preOrden(arbol->izq);
            preOrden(arbol->der);
        }
    }  
    void insertaNodo(nodo** arbol, nodo data) {
        nodo* nuevo = nullptr;
        if (*arbol == nullptr) {
            nuevo = new nodo;
            nuevo->ID = data.ID;
            strcpy_s(nuevo->User_Name, data.User_Name);
            nuevo->der = nullptr;
            nuevo->izq = nullptr;
            *arbol = nuevo;
        }
        else if (strcmp(data.User_Name, (*arbol)->User_Name) < 0)
            insertaNodo(&(*arbol)->izq, data);
        else if (strcmp(data.User_Name, (*arbol)->User_Name) > 0)
            insertaNodo(&(*arbol)->der, data);
        else
            printf("Dato duplicado.\n");
    }
    nodo* buscarPorNombre(nodo* arbol, const char* nombre) {
        if (arbol == nullptr) {
            return nullptr;
        }
        if (strcmp(nombre, arbol->User_Name) == 0) {
            return arbol;
        }
        else if (strcmp(nombre, arbol->User_Name) < 0) {
            return buscarPorNombre(arbol->izq, nombre);
        }
        else {
            return buscarPorNombre(arbol->der, nombre);
        }
    }
    void modificarNodo(nodo* arbol, const char* nombre, int nuevoID) {
        nodo* nodoAModificar = buscarPorNombre(arbol, nombre);
        if (nodoAModificar != nullptr) {
            nodoAModificar->ID = nuevoID;
            printf("Datos del nodo actualizados: ID = %d, Nombre = %s\n", nodoAModificar->ID, nodoAModificar->User_Name);
        }
        else {
            printf("Nodo con nombre %s no encontrado.\n", nombre);
        }
    }
    // Método para guardar el árbol en un archivo binario
    void guardarEnArchivo(const char* nombreArchivo) {
        ofstream archivo(nombreArchivo, ios::binary);
        if (archivo.is_open()) {
            guardarNodo(archivo, raiz);
            archivo.close();
            cout << "Árbol guardado en " << nombreArchivo << endl;
        }
        else {
            cout << "No se pudo abrir el archivo." << endl;
        }
    }

    // Método para cargar el árbol desde un archivo binario
    void cargarDesdeArchivo(const char* nombreArchivo) {
        ifstream archivo(nombreArchivo, ios::binary);
        if (archivo.is_open()) {
            destruirArbol(raiz);
            raiz = nullptr;
            cargarNodo(archivo, &raiz);
            archivo.close();
            cout << "Árbol cargado desde " << nombreArchivo << endl;
        }
        else {
            cout << "No se pudo abrir el archivo." << endl;
        }
    }
    void Char(ofstream& file, const char* Char) {
        uint32_t text = static_cast<uint32_t>(strlen(Char)); 
        file.write(reinterpret_cast<const char*>(text), sizeof(text)); 
        file.write(Char, text); 
    }

private:
    // Método auxiliar para guardar cada nodo
    void guardarNodo(ofstream& archivo, nodo* arbol) {
        if (arbol != nullptr) {
            archivo.write(reinterpret_cast<char*>(&arbol->ID), sizeof(arbol->ID));
            Char(archivo, arbol->User_Name); 
            guardarNodo(archivo, arbol->izq);
            guardarNodo(archivo, arbol->der);
        }
    }

    // Método auxiliar para cargar cada nodo
    void cargarNodo(ifstream& archivo, nodo** arbol) {
        int ID;
        char User_Name[30];
        if (archivo.read(reinterpret_cast<char*>(&ID), sizeof(ID))) {
            archivo.read(User_Name, sizeof(User_Name));
            nodo* nuevo = new nodo;
            nuevo->ID = ID;
            strcpy_s(nuevo->User_Name, User_Name);
            nuevo->izq = nullptr;
            nuevo->der = nullptr;
            *arbol = nuevo;
            cargarNodo(archivo, &(*arbol)->izq);
            cargarNodo(archivo, &(*arbol)->der);
        }
    }

    // Método para destruir el árbol y liberar memoria
    void destruirArbol(nodo* arbol) {
        if (arbol != nullptr) {
            destruirArbol(arbol->izq);
            destruirArbol(arbol->der);
            delete arbol;
        }
    }
};

nodo CapturaNodo();

int main() {
    arbol Arbol1;
    nodo info;
    int opc = 0;
    //Arbol1.cargarDesdeArchivo("arbol.bin");
    do {
        system("cls");
        printf("\n MANEJO DE ARBOLES BINARIOS\n\n");
        printf(" 1. Agregar nodo\n");
        printf(" 2. Mostrar arbol Pre-Orden\n");
        printf(" 3. Buscar por nombre\n");
        printf(" 4. Modificar\n");
        printf(" 5 Salir\n");
        cin >> opc;
        switch (opc) {
            case 1:
                system("cls");
                printf(" AGREGAR NODO:\n");
                info = CapturaNodo();
                Arbol1.insertaNodo(&Arbol1.raiz, info);
                printf("Elemento agregado\n");
                _getch();
                break;
            case 2:
                system("cls");
                printf("Pre-Orden\n");
                Arbol1.preOrden(Arbol1.raiz);
                printf("fin\n");
                _getch();
                break;      
            case 3: {
               system("cls");
               printf("Buscar por nombre:\n");
               char nombre[25];
               printf("Nombre: "); cin >> nombre;
               nodo* resultado = Arbol1.buscarPorNombre(Arbol1.raiz, nombre);
               if (resultado != nullptr) {
                   printf("Nodo encontrado: ID = %d, Nombre = %s\n", resultado->ID, resultado->User_Name);
               }
               else {
                   printf("Nodo con nombre %s no encontrado.\n", nombre);
               }
               
               _getch();
                }break;
            case 4: {
               char nombre[25];
               system("cls");
               printf("Modificar datos del nodo:\n"); 
               printf("Nombre del nodo a modificar: "); cin >> nombre; 
               printf("Nuevo ID: "); int nuevoID; cin >> nuevoID; 
               Arbol1.modificarNodo(Arbol1.raiz, nombre, nuevoID); 
               _getch();
               }break;
        }
        
    } while (opc < 5);
  
   // Arbol1.guardarEnArchivo("arbol.bin");
    return 0;
}

nodo CapturaNodo() {
    nodo info;
    printf("Id: "); cin >> info.ID;
    printf("Nombre: "); cin >> info.User_Name;

    return info;
}
