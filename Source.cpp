#include <iostream>
#include <conio.h>
#include <string.h> 
#include <cstring> // para strcpy y strcmp
#include <fstream>

using namespace std;

class nodo {
public:
    int id;
    char name[30];
    nodo* izq;
    nodo* der;
};

class arbol {
public:
    nodo* raiz;

    arbol() {
        this->raiz = 0;
    }

    ~arbol() {
        // Podrías implementar un destructor que libere la memoria de todos los nodos
    }

    void preOrden(nodo* arbol) {
        if (arbol != 0) {
            printf("id = %d\tname = %s\n", arbol->id, arbol->name);
            preOrden(arbol->izq);
            preOrden(arbol->der);
        }
    }

    void inOrden(nodo* arbol) {
        if (arbol != 0) {
            inOrden(arbol->izq);
            printf("id = %d\tname = %s\n", arbol->id, arbol->name);
            inOrden(arbol->der);
        }
    }

    void postOrden(nodo* arbol) {
        if (arbol != 0) {
            postOrden(arbol->izq);
            postOrden(arbol->der);
            printf("id = %d\tname = %s\n", arbol->id, arbol->name);
        }
    }

    void insertaNodo(nodo** arbol, nodo data) {
        nodo* nuevo = 0;
        if (*arbol == 0) {
            nuevo = new nodo;
            nuevo->id = data.id;
            strcpy_s(nuevo->name, data.name); 
            nuevo->der = 0;
            nuevo->izq = 0;
            *arbol = nuevo;
        }
        else if (strcmp(data.name, (*arbol)->name) < 0) {
            insertaNodo(&(*arbol)->izq, data);
        }
        else if (strcmp(data.name, (*arbol)->name) > 0) {
            insertaNodo(&(*arbol)->der, data);
        }
        else {
            printf("Dato duplicado.\n");
        }
    }

    int EsHoja(nodo* r) {
        return !r->der && !r->izq;
    }

    int Vacio(nodo* r) {
        return r == NULL;
    }
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

private:
    // Método auxiliar para guardar cada nodo
    void guardarNodo(ofstream& archivo, nodo* arbol) {
        if (arbol != nullptr) {
            archivo.write(reinterpret_cast<char*>(&arbol->id), sizeof(arbol->id));
            archivo.write(arbol->name, sizeof(arbol->name));
            guardarNodo(archivo, arbol->izq);
            guardarNodo(archivo, arbol->der);
        }
    }
    void cargarNodo(ifstream& archivo, nodo** arbol) {
        int id;
        char name[30];
        if (archivo.read(reinterpret_cast<char*>(&id), sizeof(id))) {
            archivo.read(name, sizeof(name));
            nodo* nuevo = new nodo;
            nuevo->id = id;
            strcpy_s(nuevo->name, name);
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

nodo CapturaNodo() {
    nodo info;
    printf("Id: "); cin >> info.id;
    printf("Nombre: "); cin >> info.name;
    return info;
}

int main() {
    arbol Arbol1;
    nodo info;
    int opc = 0;
    Arbol1.cargarDesdeArchivo("arbol.bin"); 
    do {
        system("cls");
        printf("\n MANEJO DE ARBOLES BINARIOS\n\n");
        printf(" 1. Agregar nodo\n");
        printf(" 2. Mostrar arbol Pre-Orden\n");
        printf(" 3. Mostrar arbol In-Orden\n");
        printf(" 4. Mostrar arbol Post-Orden\n");
        printf(" 5. Eliminar nodo\n");
        printf(" 6. Salir\n");
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
        case 3:
            system("cls");
            printf("In-Orden\n");
            Arbol1.inOrden(Arbol1.raiz);
            printf("fin\n");
            _getch();
            break;
        case 4:
            system("cls");
            printf("Post-Orden\n");
            Arbol1.postOrden(Arbol1.raiz);
            printf("fin\n");
            _getch();
            break;
        case 5:
            system("cls");
            printf("Capture Id a eliminar: ");
            cin >> info.name;            
            _getch();
            break;
        }
    } while (opc < 6);
    Arbol1.guardarEnArchivo("arbol.bin"); 
    return 0;
}
