#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ============================================
// ESTRUCTURAS DE DATOS
// ============================================

typedef struct {
    char apellidoNombre[60];
    char usuario[20];
    char contrasena[40];
} Usuario;

typedef struct {
    int idSocio;
    int dni;
    char nombre[30];
    char apellido[30];
    char telefono[20];
    char plan[20];
    int estado; // 1=activo, 0=inactivo
} Socio;

typedef struct NodoLista {
    Socio dato;
    struct NodoLista *siguiente;
} NodoLista;

// ============================================
// PROTOTIPOS DE FUNCIONES
// ============================================

// Archivos
void crearArchivoUsuarios();
void crearArchivoSocios();

// Usuarios
void altaUsuario();
int login();
void mostrarUsuarios();

// Validaciones
int validarUsuario(char *usuario);
int validarContrasena(char *contrasena);
int validarLongitud(char *cadena, int min, int max);
int validarPrimerCaracter(char *cadena);
int contarMayusculas(char *cadena);
int contarDigitos(char *cadena);
int validarCaracteresUsuario(char *cadena);
int validarCaracteresContrasena(char *cadena);
int usuarioUnico(char *usuario);
int tieneMayuscula(char *cadena);
int tieneMinuscula(char *cadena);
int tieneNumero(char *cadena);
int tieneTresNumerosConsecutivos(char *cadena);
int tieneLetrasConsecutivas(char *cadena);

// Socios
void altaSocio();
void listarSocios();
void bajaLogica();
void bajaFisica();
void modificarSocio();
void buscarSocioDNI();
void buscarSocioApellido();
void buscarSociosPlan();
void mostrarSocio(Socio s);

// Listas dinámicas
NodoLista* cargarSociosEnLista();
void mostrarListaSocios(NodoLista *lista);
void liberarLista(NodoLista *lista);

// Estadísticas
void mostrarEstadisticas();
int contarTotalSocios();
int contarSociosActivos();
int contarSociosPlan(char *plan);

// Utilidades
void limpiarPantalla();
void pausa();
void mostrarMenuPrincipal();
void mostrarMenuSocios();

// ============================================
// FUNCIONES PRINCIPALES
// ============================================

int main() {
    int opcion;
    system("chcp 65001");
    // Crear archivos si no existen
    crearArchivoUsuarios();
    crearArchivoSocios();
    
    do {
        limpiarPantalla();
        mostrarMenuPrincipal();
        
        printf("Seleccione una opcion: ");
        if(scanf("%d", &opcion) != 1) {
            printf("Error en la entrada.\n");
            while(getchar() != '\n');
            pausa();
            continue;
        }
        
        switch(opcion) {
            case 1:
                if(login()) {
                    mostrarMenuSocios();
                }
                break;
            case 2:
                altaUsuario();
                break;
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida.\n");
                pausa();
        }
    } while(opcion != 0);
    
    return 0;
}

// ============================================
// MENÚS
// ============================================

void mostrarMenuPrincipal() {
    printf("\n========================================\n");
    printf("     SISTEMA DE GESTION - HAMMERX      \n");
    printf("========================================\n");
    printf("1. INICIAR SESION\n");
    printf("2. CREAR NUEVO USUARIO\n");
    printf("0. SALIR\n");
    printf("========================================\n");
}

void mostrarMenuSocios() {
    int opcion;
    NodoLista *listaSocios = NULL;
    
    do {
        limpiarPantalla();
        printf("\n========================================\n");
    printf("        GESTION DE SOCIOS HAMMERX       \n");
    printf("========================================\n");
    printf("1. CREAR ARCHIVO DE SOCIOS\n");
    printf("2. ALTA DE SOCIO\n");
    printf("3. LISTAR SOCIOS ACTIVOS\n");
    printf("4. BAJA LOGICA DE SOCIO\n");
    printf("5. BAJA FISICA DE SOCIO\n");
    printf("6. MODIFICAR DATOS DE SOCIO\n");
    printf("7. BUSCAR SOCIO POR DNI\n");
    printf("8. BUSCAR SOCIO POR APELLIDO\n");
    printf("9. BUSCAR SOCIOS POR PLAN\n");
    printf("10. CARGAR SOCIOS EN LISTA DINAMICA\n");
    printf("11. MOSTRAR LISTA DINAMICA DE SOCIOS\n");
    printf("12. VER ESTADISTICAS\n");
    printf("13. MOSTRAR TODOS LOS USUARIOS\n");
    printf("0. VOLVER AL MENU PRINCIPAL\n");
    printf("========================================\n");
        
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                crearArchivoSocios();
                pausa();
                break;
            case 2:
                altaSocio();
                pausa();
                break;
            case 3:
                listarSocios();
                pausa();
                break;
            case 4:
                bajaLogica();
                pausa();
                break;
            case 5:
                bajaFisica();
                pausa();
                break;
            case 6:
                modificarSocio();
                pausa();
                break;
            case 7:
                buscarSocioDNI();
                pausa();
                break;
            case 8:
                buscarSocioApellido();
                pausa();
                break;
            case 9:
                buscarSociosPlan();
                pausa();
                break;
            case 10:
                listaSocios = cargarSociosEnLista();
                printf("Socios cargados en lista dinamica.\n");
                pausa();
                break;
            case 11:
                if(listaSocios != NULL) {
                    mostrarListaSocios(listaSocios);
                } else {
                    printf("Primero cargue los socios en lista (opcion 10).\n");
                }
                pausa();
                break;
            case 12:
                mostrarEstadisticas();
                pausa();
                break;
            case 13:
                mostrarUsuarios();
                pausa();
                break;
            case 0:
                if(listaSocios != NULL) {
                    liberarLista(listaSocios);
                }
                printf("Volviendo al menu principal...\n");
                pausa();
                break;
            default:
                printf("Opcion invalida.\n");
                pausa();
        }
    } while(opcion != 0);
}

// ============================================
// ARCHIVOS
// ============================================

void crearArchivoUsuarios() {
    FILE *archivo = fopen("usuarios.dat", "ab");
    if(archivo != NULL) {
        fclose(archivo);
    }
}

void crearArchivoSocios() {
    FILE *archivo = fopen("socios.dat", "ab");
    if(archivo != NULL) {
        fclose(archivo);
        printf("Archivo de socios creado/verificado.\n");
    }
}

// ============================================
// VALIDACIONES
// ============================================

int validarLongitud(char *cadena, int min, int max) {
    int len = strlen(cadena);
    return (len >= min && len <= max);
}

int validarPrimerCaracter(char *cadena) {
    return (cadena[0] >= 'a' && cadena[0] <= 'z');
}

int contarMayusculas(char *cadena) {
    int count = 0;
    for(int i = 0; cadena[i]; i++) {
        if(cadena[i] >= 'A' && cadena[i] <= 'Z') count++;
    }
    return count;
}

int contarDigitos(char *cadena) {
    int count = 0;
    for(int i = 0; cadena[i]; i++) {
        if(isdigit(cadena[i])) count++;
    }
    return count;
}

int validarCaracteresUsuario(char *cadena) {
    char permitidos[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-/*?¿!¡";
    
    for(int i = 0; cadena[i]; i++) {
        int valido = 0;
        for(int j = 0; permitidos[j]; j++) {
            if(cadena[i] == permitidos[j]) {
                valido = 1;
                break;
            }
        }
        if(!valido) return 0;
    }
    return 1;
}

int validarCaracteresContrasena(char *cadena) {
    for(int i = 0; cadena[i]; i++) {
        char c = cadena[i];
        if(!((c >= 'a' && c <= 'z') || 
             (c >= 'A' && c <= 'Z') || 
             (c >= '0' && c <= '9'))) {
            return 0;
        }
    }
    return 1;
}

int usuarioUnico(char *usuario) {
    FILE *archivo = fopen("usuarios.dat", "rb");
    if(archivo == NULL) return 1;
    
    Usuario u;
    while(fread(&u, sizeof(Usuario), 1, archivo)) {
        if(strcmp(u.usuario, usuario) == 0) {
            fclose(archivo);
            return 0;
        }
    }
    fclose(archivo);
    return 1;
}

int tieneMayuscula(char *cadena) {
    for(int i = 0; cadena[i]; i++) {
        if(cadena[i] >= 'A' && cadena[i] <= 'Z') return 1;
    }
    return 0;
}

int tieneMinuscula(char *cadena) {
    for(int i = 0; cadena[i]; i++) {
        if(cadena[i] >= 'a' && cadena[i] <= 'z') return 1;
    }
    return 0;
}

int tieneNumero(char *cadena) {
    for(int i = 0; cadena[i]; i++) {
        if(isdigit(cadena[i])) return 1;
    }
    return 0;
}

int tieneTresNumerosConsecutivos(char *cadena) {
    int consecutivos = 0;
    for(int i = 0; cadena[i]; i++) {
        if(isdigit(cadena[i])) {
            consecutivos++;
            if(consecutivos >= 3) return 1;
        } else {
            consecutivos = 0;
        }
    }
    return 0;
}

int tieneLetrasConsecutivas(char *cadena) {
    for(int i = 0; cadena[i] && cadena[i+1]; i++) {
        if(isalpha(cadena[i]) && isalpha(cadena[i+1])) {
            if((tolower(cadena[i+1]) - tolower(cadena[i])) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

int validarUsuario(char *usuario) {
    // Longitud 6-10
    if(!validarLongitud(usuario, 6, 10)) {
        printf("Error: Debe tener 6-10 caracteres.\n");
        return 0;
    }
    
    // Primer caracter minuscula
    if(!validarPrimerCaracter(usuario)) {
        printf("Error: Debe comenzar con minuscula.\n");
        return 0;
    }
    
    // Al menos 2 mayusculas
    if(contarMayusculas(usuario) < 2) {
        printf("Error: Al menos 2 mayusculas.\n");
        return 0;
    }
    
    // Maximo 3 digitos
    if(contarDigitos(usuario) > 3) {
        printf("Error: Maximo 3 digitos.\n");
        return 0;
    }
    
    // Caracteres permitidos
    if(!validarCaracteresUsuario(usuario)) {
        printf("Error: Caracteres no permitidos.\n");
        return 0;
    }
    
    // Unico
    if(!usuarioUnico(usuario)) {
        printf("Error: Usuario ya existe.\n");
        return 0;
    }
    
    return 1;
}

int validarContrasena(char *contrasena) {
    // Longitud 6-32
    if(!validarLongitud(contrasena, 6, 32)) {
        printf("Error: Debe tener 6-32 caracteres.\n");
        return 0;
    }
    
    // Al menos 1 mayuscula, 1 minuscula, 1 numero
    if(!tieneMayuscula(contrasena)) {
        printf("Error: Falta mayuscula.\n");
        return 0;
    }
    if(!tieneMinuscula(contrasena)) {
        printf("Error: Falta minuscula.\n");
        return 0;
    }
    if(!tieneNumero(contrasena)) {
        printf("Error: Falta numero.\n");
        return 0;
    }
    
    // Solo alfanumericos
    if(!validarCaracteresContrasena(contrasena)) {
        printf("Error: Solo caracteres alfanumericos.\n");
        return 0;
    }
    
    // Max 3 numeros consecutivos
    if(tieneTresNumerosConsecutivos(contrasena)) {
        printf("Error: Maximo 3 numeros consecutivos.\n");
        return 0;
    }
    
    // No 2 letras consecutivas
    if(tieneLetrasConsecutivas(contrasena)) {
        printf("Error: No letras alfabeticamente consecutivas.\n");
        return 0;
    }
    
    return 1;
}

// ============================================
// USUARIOS
// ============================================

void altaUsuario() {
    limpiarPantalla();
    printf("\n=== CREAR NUEVO USUARIO ===\n");
    
    Usuario nuevo;
    char tempUsuario[20];
    char tempContrasena[40];
    
    // Validar usuario
    do {
        printf("Nombre de usuario: ");
        fflush(stdin);
        gets(tempUsuario);
    } while(!validarUsuario(tempUsuario));
    strcpy(nuevo.usuario, tempUsuario);
    
    // Validar contraseña
    do {
        printf("Contraseña: ");
        fflush(stdin);
        gets(tempContrasena);
    } while(!validarContrasena(tempContrasena));
    strcpy(nuevo.contrasena, tempContrasena);
    
    // Datos personales
    printf("Apellido y Nombre: ");
    fflush(stdin);
    gets(nuevo.apellidoNombre);
    
    // Guardar en archivo
    FILE *archivo = fopen("usuarios.dat", "ab");
    if(archivo == NULL) {
        printf("Error al guardar usuario.\n");
        return;
    }
    
    fwrite(&nuevo, sizeof(Usuario), 1, archivo);
    fclose(archivo);
    
    printf("\n¡Usuario creado exitosamente!\n");
    pausa();
}

int login() {
    limpiarPantalla();
    printf("\n=== INICIAR SESION ===\n");
    
    char usuario[20], contrasena[40];
    printf("Usuario: ");
    fflush(stdin);
    gets(usuario);
    
    printf("Contraseña: ");
    fflush(stdin);
    gets(contrasena);
    
    FILE *archivo = fopen("usuarios.dat", "rb");
    if(archivo == NULL) {
        printf("No hay usuarios registrados.\n");
        pausa();
        return 0;
    }
    
    Usuario u;
    while(fread(&u, sizeof(Usuario), 1, archivo)) {
        if(strcmp(u.usuario, usuario) == 0 && 
           strcmp(u.contrasena, contrasena) == 0) {
            printf("\n¡Bienvenido %s!\n", u.apellidoNombre);
            fclose(archivo);
            return 1;
        }
    }
    
    fclose(archivo);
    printf("\nUsuario o contraseña incorrectos.\n");
    pausa();
    return 0;
}

void mostrarUsuarios() {
    limpiarPantalla();
    printf("\n=== USUARIOS REGISTRADOS ===\n");
    
    FILE *archivo = fopen("usuarios.dat", "rb");
    if(archivo == NULL) {
        printf("No hay usuarios registrados.\n");
        return;
    }
    
    Usuario u;
    printf("%-20s %-40s\n", "USUARIO", "NOMBRE COMPLETO");
    printf("----------------------------------------------------------\n");
    
    while(fread(&u, sizeof(Usuario), 1, archivo)) {
        printf("%-20s %-40s\n", u.usuario, u.apellidoNombre);
    }
    
    fclose(archivo);
}

// ============================================
// SOCIOS
// ============================================

void mostrarSocio(Socio s) {
    printf("ID: %d\n", s.idSocio);
    printf("DNI: %d\n", s.dni);
    printf("Nombre: %s %s\n", s.nombre, s.apellido);
    printf("Telefono: %s\n", s.telefono);
    printf("Plan: %s\n", s.plan);
    printf("Estado: %s\n", s.estado ? "ACTIVO" : "INACTIVO");
    printf("----------------------------------------\n");
}

void altaSocio() {
    limpiarPantalla();
    printf("\n=== ALTA DE SOCIO ===\n");
    
    Socio nuevo;
    static int ultimoId = 0;
    
    // Obtener último ID
    FILE *archivo = fopen("socios.dat", "rb");
    if(archivo != NULL) {
        Socio temp;
        while(fread(&temp, sizeof(Socio), 1, archivo)) {
            if(temp.idSocio > ultimoId) ultimoId = temp.idSocio;
        }
        fclose(archivo);
    }
    
    nuevo.idSocio = ultimoId + 1;
    printf("ID asignado: %d\n", nuevo.idSocio);
    
    printf("DNI: ");
    scanf("%d", &nuevo.dni);
    fflush(stdin);
    
    printf("Nombre: ");
    gets(nuevo.nombre);
    
    printf("Apellido: ");
    gets(nuevo.apellido);
    
    printf("Telefono: ");
    gets(nuevo.telefono);
    
    printf("Plan (Basico/Intermedio/Premium): ");
    gets(nuevo.plan);
    
    nuevo.estado = 1;
    
    archivo = fopen("socios.dat", "ab");
    if(archivo == NULL) {
        printf("Error al guardar socio.\n");
        return;
    }
    
    fwrite(&nuevo, sizeof(Socio), 1, archivo);
    fclose(archivo);
    
    printf("\n¡Socio agregado exitosamente!\n");
}

void listarSocios() {
    limpiarPantalla();
    printf("\n=== SOCIOS ACTIVOS ===\n");
    
    FILE *archivo = fopen("socios.dat", "rb");
    if(archivo == NULL) {
        printf("No hay socios registrados.\n");
        return;
    }
    
    Socio s;
    int contador = 0;
    
    while(fread(&s, sizeof(Socio), 1, archivo)) {
        if(s.estado == 1) {
            mostrarSocio(s);
            contador++;
        }
    }
    
    if(contador == 0) {
        printf("No hay socios activos.\n");
    } else {
        printf("Total: %d socios activos\n", contador);
    }
    
    fclose(archivo);
}

void bajaLogica() {
    limpiarPantalla();
    printf("\n=== BAJA LOGICA DE SOCIO ===\n");
    
    int dni, encontrado = 0;
    printf("DNI del socio a dar de baja: ");
    scanf("%d", &dni);
    
    FILE *archivo = fopen("socios.dat", "r+b");
    if(archivo == NULL) {
        printf("No hay socios registrados.\n");
        return;
    }
    
    Socio s;
    while(fread(&s, sizeof(Socio), 1, archivo)) {
        if(s.dni == dni && s.estado == 1) {
            s.estado = 0;
            fseek(archivo, -sizeof(Socio), SEEK_CUR);
            fwrite(&s, sizeof(Socio), 1, archivo);
            encontrado = 1;
            printf("Socio dado de baja logicamente.\n");
            break;
        }
    }
    
    if(!encontrado) {
        printf("No se encontro socio activo con ese DNI.\n");
    }
    
    fclose(archivo);
}

void bajaFisica() {
    limpiarPantalla();
    printf("\n=== BAJA FISICA DE SOCIO ===\n");
    
    int dni, encontrado = 0;
    printf("DNI del socio a eliminar: ");
    scanf("%d", &dni);
    
    FILE *archivo = fopen("socios.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    
    if(archivo == NULL || temp == NULL) {
        printf("Error al abrir archivos.\n");
        return;
    }
    
    Socio s;
    while(fread(&s, sizeof(Socio), 1, archivo)) {
        if(s.dni != dni) {
            fwrite(&s, sizeof(Socio), 1, temp);
        } else {
            encontrado = 1;
        }
    }
    
    fclose(archivo);
    fclose(temp);
    
    if(encontrado) {
        remove("socios.dat");
        rename("temp.dat", "socios.dat");
        printf("Socio eliminado fisicamente.\n");
    } else {
        remove("temp.dat");
        printf("No se encontro socio con ese DNI.\n");
    }
}

void modificarSocio() {
    limpiarPantalla();
    printf("\n=== MODIFICAR SOCIO ===\n");
    
    int dni, encontrado = 0;
    printf("DNI del socio a modificar: ");
    scanf("%d", &dni);
    fflush(stdin);
    
    FILE *archivo = fopen("socios.dat", "r+b");
    if(archivo == NULL) {
        printf("No hay socios registrados.\n");
        return;
    }
    
    Socio s;
    while(fread(&s, sizeof(Socio), 1, archivo)) {
        if(s.dni == dni && s.estado == 1) {
            printf("\nSocio encontrado. Ingrese nuevos datos:\n");
            
            printf("Nuevo nombre: ");
            gets(s.nombre);
            
            printf("Nuevo apellido: ");
            gets(s.apellido);
            
            printf("Nuevo telefono: ");
            gets(s.telefono);
            
            printf("Nuevo plan: ");
            gets(s.plan);
            
            fseek(archivo, -sizeof(Socio), SEEK_CUR);
            fwrite(&s, sizeof(Socio), 1, archivo);
            
            encontrado = 1;
            printf("\nSocio modificado exitosamente.\n");
            break;
        }
    }
    
    if(!encontrado) {
        printf("No se encontro socio activo con ese DNI.\n");
    }
    
    fclose(archivo);
}

void buscarSocioDNI() {
    limpiarPantalla();
    printf("\n=== BUSCAR SOCIO POR DNI ===\n");
    
    int dni, encontrado = 0;
    printf("Ingrese DNI: ");
    scanf("%d", &dni);
    
    FILE *archivo = fopen("socios.dat", "rb");
    if(archivo == NULL) {
        printf("No hay socios registrados.\n");
        return;
    }
    
    Socio s;
    while(fread(&s, sizeof(Socio), 1, archivo)) {
        if(s.dni == dni) {
            printf("\nSOCIO ENCONTRADO:\n");
            mostrarSocio(s);
            encontrado = 1;
            break;
        }
    }
    
    if(!encontrado) {
        printf("No se encontro socio con DNI %d.\n", dni);
    }
    
    fclose(archivo);
}

void buscarSocioApellido() {
    limpiarPantalla();
    printf("\n=== BUSCAR SOCIO POR APELLIDO ===\n");
    
    char apellido[30];
    int encontrado = 0;
    printf("Ingrese apellido: ");
    fflush(stdin);
    gets(apellido);
    
    FILE *archivo = fopen("socios.dat", "rb");
    if(archivo == NULL) {
        printf("No hay socios registrados.\n");
        return;
    }
    
    Socio s;
    printf("\nRESULTADOS:\n");
    while(fread(&s, sizeof(Socio), 1, archivo)) {
        if(strcasecmp(s.apellido, apellido) == 0 && s.estado == 1) {
            mostrarSocio(s);
            encontrado = 1;
        }
    }
    
    if(!encontrado) {
        printf("No se encontraron socios con apellido '%s'.\n", apellido);
    }
    
    fclose(archivo);
}

void buscarSociosPlan() {
    limpiarPantalla();
    printf("\n=== BUSCAR SOCIOS POR PLAN ===\n");
    
    char plan[20];
    int encontrado = 0;
    printf("Ingrese plan (Basico/Intermedio/Premium): ");
    fflush(stdin);
    gets(plan);
    
    FILE *archivo = fopen("socios.dat", "rb");
    if(archivo == NULL) {
        printf("No hay socios registrados.\n");
        return;
    }
    
    Socio s;
    printf("\nSOCIOS CON PLAN '%s':\n", plan);
    while(fread(&s, sizeof(Socio), 1, archivo)) {
        if(strcasecmp(s.plan, plan) == 0 && s.estado == 1) {
            mostrarSocio(s);
            encontrado = 1;
        }
    }
    
    if(!encontrado) {
        printf("No se encontraron socios con plan '%s'.\n", plan);
    }
    
    fclose(archivo);
}

// ============================================
// LISTAS DINÁMICAS
// ============================================

NodoLista* cargarSociosEnLista() {
    FILE *archivo = fopen("socios.dat", "rb");
    if(archivo == NULL) {
        printf("No hay socios registrados.\n");
        return NULL;
    }
    
    NodoLista *lista = NULL;
    NodoLista *ultimo = NULL;
    Socio s;
    
    while(fread(&s, sizeof(Socio), 1, archivo)) {
        NodoLista *nuevo = (NodoLista*)malloc(sizeof(NodoLista));
        if(nuevo == NULL) {
            printf("Error de memoria.\n");
            fclose(archivo);
            return lista;
        }
        
        nuevo->dato = s;
        nuevo->siguiente = NULL;
        
        if(lista == NULL) {
            lista = nuevo;
        } else {
            ultimo->siguiente = nuevo;
        }
        ultimo = nuevo;
    }
    
    fclose(archivo);
    return lista;
}

void mostrarListaSocios(NodoLista *lista) {
    limpiarPantalla();
    printf("\n=== LISTA DINAMICA DE SOCIOS ===\n");
    
    if(lista == NULL) {
        printf("La lista está vacía.\n");
        return;
    }
    
    NodoLista *actual = lista;
    int contador = 0;
    
    while(actual != NULL) {
        mostrarSocio(actual->dato);
        actual = actual->siguiente;
        contador++;
    }
    
    printf("Total en lista: %d socios\n", contador);
}

void liberarLista(NodoLista *lista) {
    NodoLista *actual = lista;
    NodoLista *siguiente;
    
    while(actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

// ============================================
// ESTADÍSTICAS
// ============================================

int contarTotalSocios() {
    FILE *archivo = fopen("socios.dat", "rb");
    if(archivo == NULL) return 0;
    
    Socio s;
    int contador = 0;
    while(fread(&s, sizeof(Socio), 1, archivo)) {
        contador++;
    }
    fclose(archivo);
    return contador;
}

int contarSociosActivos() {
    FILE *archivo = fopen("socios.dat", "rb");
    if(archivo == NULL) return 0;
    
    Socio s;
    int contador = 0;
    while(fread(&s, sizeof(Socio), 1, archivo)) {
        if(s.estado == 1) contador++;
    }
    fclose(archivo);
    return contador;
}

int contarSociosPlan(char *plan) {
    FILE *archivo = fopen("socios.dat", "rb");
    if(archivo == NULL) return 0;
    
    Socio s;
    int contador = 0;
    while(fread(&s, sizeof(Socio), 1, archivo)) {
        if(strcasecmp(s.plan, plan) == 0 && s.estado == 1) {
            contador++;
        }
    }
    fclose(archivo);
    return contador;
}

void mostrarEstadisticas() {
    limpiarPantalla();
    printf("\n=== ESTADISTICAS DEL SISTEMA ===\n");
    
    int total = contarTotalSocios();
    int activos = contarSociosActivos();
    int inactivos = total - activos;
    
    printf("Total de socios registrados: %d\n", total);
    printf("Socios activos: %d\n", activos);
    printf("Socios inactivos: %d\n", inactivos);
    printf("\nSocios por plan:\n");
    printf("  Basico: %d\n", contarSociosPlan("Basico"));
    printf("  Intermedio: %d\n", contarSociosPlan("Intermedio"));
    printf("  Premium: %d\n", contarSociosPlan("Premium"));
    
    // Contar usuarios
    FILE *archivo = fopen("usuarios.dat", "rb");
    if(archivo != NULL) {
        Usuario u;
        int usuarios = 0;
        while(fread(&u, sizeof(Usuario), 1, archivo)) usuarios++;
        fclose(archivo);
        printf("\nTotal de usuarios del sistema: %d\n", usuarios);
    }
}

// ============================================
// UTILIDADES
// ============================================

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausa() {
    printf("\nPresione Enter para continuar...");
    fflush(stdin);
    getchar();
}