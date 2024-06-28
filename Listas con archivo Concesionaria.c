#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AUTOS 30
#define NOMBRE_ARCHIVO "ARCHIVO_AUTOS.txt"

typedef struct car {
    char Modelo[45];
    int Precio;
    struct car* next;
} autos_t;  

autos_t* concesionaria = NULL;

void menu(void);
void mostrar_autos(autos_t*);
void ingresar(autos_t*);
void precio(autos_t*);
void salir(void);
void subir_auto(void);
void ver_autos(void);
void liberar_memoria(void);
void cargar_autos(void);

int main() {
    cargar_autos();
    menu();
    liberar_memoria();
    return 0;
}

void mostrar_autos(autos_t* car) {
    printf("Modelo de auto: %s\n", car->Modelo);
    printf("Precio: %d\n", car->Precio);
}

void ingresar(autos_t* car) {
    printf("Ingrese el modelo de auto: ");
    fgets(car->Modelo, sizeof(car->Modelo), stdin);
    car->Modelo[strcspn(car->Modelo, "\n")] = '\0'; // Elimina el salto de línea
}

void precio(autos_t* car) {
    printf("Ingrese el precio del auto: ");
    scanf("%d", &car->Precio);
    getchar(); // Limpia el buffer de entrada
}

void salir(void) {
    printf("Gracias por usar el programa\n");
}

void menu(void) {
    int opcion;
    do {
        printf("1. Cargar modelo de auto\n");
        printf("2. Mostrar lista de autos\n");
        printf("3. Ver archivo y salir\n");
        scanf("%d", &opcion);
        getchar(); // Limpia el buffer de entrada

        switch (opcion) {
        case 1:
            subir_auto();
            break;

        case 2:
            ver_autos();
            break;

        case 3:
            salir();
            break;

        default:
            printf("Opción no válida\n");
            break;
        }
    } while (opcion != 3);
}

void subir_auto() {
    autos_t* nuevo_auto = malloc(sizeof(autos_t));
    if (nuevo_auto == NULL) {
        printf("No hay más espacio en la memoria.\n");
        return;
    }
    ingresar(nuevo_auto);
    precio(nuevo_auto);
    nuevo_auto->next = concesionaria;
    concesionaria = nuevo_auto;

    FILE *archivo = fopen(NOMBRE_ARCHIVO, "a"); // Abrir en modo append (para poder modificar el archivo una vez abierto)
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "%s;%d\n", nuevo_auto->Modelo, nuevo_auto->Precio);
    fclose(archivo);
    printf("Auto guardado en archivo.\n");
}

void ver_autos() {
    autos_t* autos_actual = concesionaria;
    if (autos_actual == NULL) {
        printf("No hay autos cargados\n");
        return;
    }
    while (autos_actual != NULL) {
        mostrar_autos(autos_actual);
        autos_actual = autos_actual->next;
    }
}

void liberar_memoria() {
    autos_t* autos_actual = concesionaria;
    autos_t* autos_temporal;
    while (autos_actual != NULL) {
        autos_temporal = autos_actual->next;
        free(autos_actual);
        autos_actual = autos_temporal;
    }
    concesionaria = NULL;
}

void cargar_autos() {
    FILE *archivo = fopen(NOMBRE_ARCHIVO, "r");
    if (archivo == NULL) {
        return; // Si no existe el archivo, no hace nada
    }

    char modelo[45];
    int precio;
    while (fscanf(archivo, "%[^;];%d\n", modelo, &precio) != EOF) {
        autos_t *auto_aux = malloc(sizeof(autos_t));
        if (auto_aux == NULL) {
            printf("No hay más espacio en la memoria.\n");
            fclose(archivo);
            return;
        }

        strcpy(auto_aux->Modelo, modelo);
        auto_aux->Precio = precio;
        auto_aux->next = concesionaria;
        concesionaria = auto_aux;
    }

    fclose(archivo);
}
