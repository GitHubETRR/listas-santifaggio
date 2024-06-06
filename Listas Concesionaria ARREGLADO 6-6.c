#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#define MAX_AUTOS 30

typedef struct car {
    char Modelo[MAX_AUTOS];
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

int main() {
    menu();
    liberar_memoria();
    return 0;
}

void mostrar_autos(autos_t* car) {
    printf("Modelo de auto: %s\n", car->Modelo);
    printf("Precio: %d\n", car->Precio);
}

void ingresar(autos_t* car) {
    printf("Ingrese el modelo de auto\n");
    __fpurge(stdin);
    scanf("%[^\n]", car->Modelo);
}

void precio(autos_t* car) {
    printf("Ingrese el precio del auto\n");
    __fpurge(stdin);
    scanf("%d", &car->Precio);
}

void salir(void) {
    printf("Gracias por usar el programa\n");
}

void menu(void) {
    int opcion;
    do {
        printf("1. Cargar modelo de auto\n");
        printf("2. Mostrar lista de autos\n");
        printf("3. Salir\n");
        scanf("%d", &opcion);

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
    autos_t* autos_nuevos = malloc(sizeof(autos_t));
    if (autos_nuevos == NULL) {
        printf("sin memoria\n");
    } else {
        ingresar(autos_nuevos);
        precio(autos_nuevos);
        autos_nuevos->next = concesionaria;
        concesionaria = autos_nuevos;
    }
}

void ver_autos() {
    autos_t* autos_actual = concesionaria;
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