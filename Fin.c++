#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Estructura para almacenar información detallada del producto
struct Producto {
    string nombre;
    string marca;
    double precio;
    int cantidad;

    Producto() : nombre(""), marca(""), precio(0.0), cantidad(0) {}
    Producto(const string& n, const string& m, double p, int c) : nombre(n), marca(m), precio(p), cantidad(c) {}
};

// Función para mostrar el mensaje de bienvenida
void mostrarBienvenida() {
    cout << "************************************" << endl;
    cout << "*   Bienvenido al sistema de       *" << endl;
    cout << "*        gestión de tienda         *" << endl;
    cout << "************************************" << endl;
}

// Función para mostrar el menú principal y obtener la opción del usuario
char mostrarMenuPrincipal() {
    cout << "\nMenú Principal:" << endl;
    cout << "1. Administrador" << endl;
    cout << "2. Cliente" << endl;
    cout << "3. Salir" << endl;
    cout << "Ingrese su opción: ";
    char opcion;
    cin >> opcion;
    return opcion;
}

// Función para validar la clave de administrador
bool validarClaveAdmin(const string& claveIngresada, const string& claveAdmin) {
    return claveIngresada == claveAdmin;
}

// Función para cambiar la clave de administrador
void cambiarClaveAdmin(string& claveActual) {
    string claveNueva;
    string claveIngresada;

    cout << "Ingrese la clave actual: ";
    cin >> claveIngresada;

    if (validarClaveAdmin(claveIngresada, claveActual)) {
        cout << "Ingrese la nueva clave: ";
        cin >> claveNueva;
        claveActual = claveNueva;
        cout << "¡La clave se cambió con éxito!" << endl;
    } else {
        cout << "Clave incorrecta." << endl;
    }
}

// Función para mostrar el inventario de productos
void mostrarInventario(const map<string, map<string, Producto>>& inventario) {
    cout << "\nInventario:" << endl;
    for (const auto& categoria : inventario) {
        cout << "Categoría: " << categoria.first << endl;
        for (const auto& item : categoria.second) {
            cout << "Nombre: " << item.first << " | Marca: " << item.second.marca << " | Precio: $" << fixed << setprecision(2) << item.second.precio << " | Cantidad: " << item.second.cantidad << " unidades" << endl;
            if (item.second.cantidad < 5) {
                cout << "¡Alerta! Este producto tiene menos de 5 existencias." << endl;
            }
        }
        cout << endl;
    }
}

// Función para suministrar productos al inventario
void suministrarProductos(map<string, map<string, Producto>>& inventario) {
    cout << "\nSuministrar productos:" << endl;
    string categoria, producto;
    int cantidad;

    cout << "Categorías disponibles: " << endl;
    for (const auto& categoria : inventario) {
        cout << categoria.first << endl;
    }

    cout << "Ingrese la categoría del producto que desea suministrar: ";
    cin >> categoria;

    if (inventario.find(categoria) == inventario.end()) {
        cout << "La categoría ingresada no existe en el inventario." << endl;
        return;
    }

    cout << "Productos disponibles en la categoría " << categoria << ":" << endl;
    for (const auto& item : inventario[categoria]) {
        cout << item.first << endl;
    }

    cout << "Ingrese el producto que desea suministrar: ";
    cin >> producto;

    if (inventario[categoria].find(producto) == inventario[categoria].end()) {
        cout << "El producto ingresado no existe en la categoría seleccionada." << endl;
        return;
    }

    cout << "Ingrese la cantidad a suministrar: ";
    cin >> cantidad;

    if (cantidad <= 0) {
        cout << "La cantidad ingresada no es válida." << endl;
        return;
    }

    inventario[categoria][producto].cantidad += cantidad;
    cout << "Se suministraron " << cantidad << " unidades de " << producto << " en la categoría " << categoria << "." << endl;
}

// Función para mostrar el menú del administrador y obtener la opción del usuario
char mostrarMenuAdmin(string& claveAdmin, map<string, map<string, Producto>>& inventario) {
    cout << "\nMenú Administrador:" << endl;
    cout << "1. Cambio de clave" << endl;
    cout << "2. Inventario" << endl;
    cout << "3. Suministrar" << endl;
    cout << "4. Salir" << endl;
    cout << "Ingrese su opción: ";
    char opcion;
    cin >> opcion;
    switch (opcion) {
        case '1':
            cambiarClaveAdmin(claveAdmin);
            break;
        case '2':
            mostrarInventario(inventario);
            break;
        case '3':
            suministrarProductos(inventario);
            break;
    }
    return opcion;
}

// Función para mostrar el menú del cliente y obtener la opción del usuario
char mostrarMenuCliente(const map<string, map<string, Producto>>& inventario) {
    cout << "\nMenú Cliente:" << endl;
    cout << "1. Comprar producto" << endl;
    cout << "2. Salir" << endl;
    cout << "Ingrese su opción: ";
    char opcion;
    cin >> opcion;
    return opcion;
}

// Función para que los clientes compren productos
void comprarProducto(map<string, map<string, Producto>>& inventario) {
    cout << "\nComprar producto:" << endl;

    // Mostrar categorías disponibles
    cout << "Categorías disponibles: " << endl;
    for (const auto& categoria : inventario) {
        cout << categoria.first << endl;
    }

    string categoriaSeleccionada;
    cout << "Ingrese la categoría del producto que desea comprar: ";
    cin >> categoriaSeleccionada;

    // Verificar si la categoría existe
    auto it_categoria = inventario.find(categoriaSeleccionada);
    if (it_categoria == inventario.end()) {
        cout << "La categoría ingresada no existe." << endl;
        return;
    }

    // Mostrar productos disponibles en la categoría seleccionada
    cout << "Productos disponibles en la categoría " << categoriaSeleccionada << ":" << endl;
    for (const auto& producto : it_categoria->second) {
        cout << producto.first << endl;
    }

    string productoSeleccionado;
    cout << "Ingrese el producto que desea comprar: ";
    cin >> productoSeleccionado;

    // Verificar si el producto existe en la categoría seleccionada
    auto it_producto = it_categoria->second.find(productoSeleccionado);
    if (it_producto == it_categoria->second.end()) {
        cout << "El producto ingresado no existe en la categoría seleccionada." << endl;
        return;
    }

    // Mostrar información detallada del producto seleccionado
    cout << "Información del producto:" << endl;
    cout << "Nombre: " << it_producto->second.nombre << endl;
    cout << "Marca: " << it_producto->second.marca << endl;
    cout << "Precio: $" << fixed << setprecision(2) << it_producto->second.precio << endl;
    cout << "Cantidad en stock: " << it_producto->second.cantidad << " unidades" << endl;

    char opcionCompra;
    cout << "¿Desea comprar este producto? (S/N): ";
    cin >> opcionCompra;

    if (opcionCompra == 'S' || opcionCompra == 's') {
        int cantidadCompra;
        cout << "Ingrese la cantidad que desea comprar: ";
        cin >> cantidadCompra;

        // Verificar si hay suficiente stock
        if (cantidadCompra > it_producto->second.cantidad) {
            cout << "No hay suficiente stock disponible." << endl;
            return;
        }

        // Actualizar stock
        it_producto->second.cantidad -= cantidadCompra;
        cout << "Compra realizada exitosamente. Gracias por su compra!" << endl;
    } else {
        cout << "Compra cancelada." << endl;
    }
}

// Función principal
int main() {
    mostrarBienvenida();
    string claveAdmin = "1234";
    int intentosFallidos = 0;
    map<string, map<string, Producto>> inventario;

    // Inicializar inventario (podrías cargarlo desde un archivo)
    inventario["protecciones"] = {
        {"casco", {"adidas", "sm", 69.99, 10}},
        {"rodilleras", {"Sportman", "sm", 49.99, 5}},
        {"pechera", {"Sportman", "sm", 69.99, 8}},
        {"arnes", {"seguridad", "Sportman", 99.99, 15}},
        {"ProtectorBucal", {"sportman", "sm", 39.99, 3}}
    };
    inventario["camping"] = {
        {"carpa", {"muebles", "Exito", 799.99, 10}},
        {"sleeping", {"muebles", "Homecenter", 99.99, 5}},
        {"fogon", {"muebles", "Ikea", 69.99, 8}},
        {"gas", {"muebles", "Ikea", 9.99, 15}},
        {"linterna", {"Muebles", "Ikea", 9.99, 3}}
    };
    inventario["suplementos"] = {
        {"vitaminas", {"frutas&verduras", "delcampo", 9.99, 10}},
        {"granola", {"frutas&verduras", "delcampo", 5.99, 5}},
        {"conservas", {"carnes", "delcampo", 6.99, 8}},
        {"uvaspasas", {"frutas&verduras", "delcampo", 9.99, 15}},
        {"fruta", {"frutas&verduras", "delcampo", 3.99, 3}}
    };
    inventario["ropa"] = {
        {"camisa", {"ropa", "zara", 79.99, 10}},
        {"pantalon", {"ropa", "boss", 49.99, 5}},
        {"zapatos", {"calzado", "nike", 99.99, 8}},
        {"gorra", {"accesorios", "h&m", 9.99, 15}},
        {"guantes", {"accesorios", "h&m", 3.99, 3}}
    };
    inventario["complementos"] = {
        {"pico", {"herramienta", "sm", 79.99, 10}},
        {"pala", {"herramienta", "sm", 99.99, 5}},
        {"cantimplora", {"enser", "battlestat", 9.99, 8}},
        {"medkit", {"medicina", "arrowhead", 99.99, 15}},
        {"cuerda", {"herramienta", "sm", 39.99, 3}}
    };
    // Otras categorías...

    while (true) {
        char opcionPrincipal = mostrarMenuPrincipal();

        switch (opcionPrincipal) {
            case '1': { // Administrador
                string clave;
                cout << "Ingrese la clave: ";
                cin >> clave;
                if (validarClaveAdmin(clave, claveAdmin)) {
                    cout << "Clave correcta. Bienvenido." << endl;
                    char opcionAdmin;
                    do {
                        opcionAdmin = mostrarMenuAdmin(claveAdmin, inventario);
                    } while (opcionAdmin != '4');
                } else {
                    cout << "Clave incorrecta." << endl;
                    intentosFallidos++;
                    if (intentosFallidos >= 3) {
                        cout << "Demasiados intentos fallidos. Bloqueando..." << endl;
                        break;
                    }
                }
                break;
            }
            case '2': { // Cliente
                char opcionCliente;
                do {
                    opcionCliente = mostrarMenuCliente(inventario);
                    if (opcionCliente == '1') {
                        comprarProducto(inventario);
                    }
                } while (opcionCliente != '2');
                break;
            }
            case '3': // Salir
                cout << "¡Hasta luego!" << endl;
                return 0;
            default:
                cout << "Opción no válida. Por favor, intente de nuevo." << endl;
        }
    }

    return 0;
}
