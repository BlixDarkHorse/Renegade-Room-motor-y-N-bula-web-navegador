#ifndef PINKGET_H
#define PINKGET_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>

// =========================================================================
// FIRMA INTERNA EXCLUSIVA DEL PINKGET (Para sus propios hijos)
// =========================================================================
#define PINKGET_INTERNO_ID "ARAÑATELADEARAÑAGLOBOCORAZÓNNEGROFUEGOCOHETE"

// Necesitamos importar o definir la EntidadBase y Pixel 
// (Asumimos que están en una cabecera global, aquí las repito conceptualmente)
#ifndef ESTRUCTURAS_BASE
#define ESTRUCTURAS_BASE
typedef struct {
    char id[100]; // ID para entrar a la Dark Vent
    int x, y;
    int width, height;
} EntidadBase;

typedef struct {
    uint8_t b, g, r, a;
} Pixel;
#endif

// =========================================================================
// ESTRUCTURA DEL PINKGET
// =========================================================================
typedef struct {
    EntidadBase base; // Hereda la estructura base (Para poder entrar a Dark Vent)
    
    // LOS 4 PUNTOS QUE DEFINEN EL PERÍMETRO HUECO
    int x_izquierdo;
    int y_superior;
    int x_derecho;
    int y_inferior;
    
    // PROPIEDADES DEL BORDE
    int borde_grosor;    // Si es 0, es un "frameless hint" (invisible)
    Pixel color_borde;   // El color RGB del borde
    
    // CONTENEDOR: El Pinkget también puede tener sus propios hijos
    EntidadBase* hijos_internos[50];
    int cantidad_hijos;

} Pinkget;

// =========================================================================
// LÓGICA DEL PINKGET
// =========================================================================

// Función para inicializar un Pinkget vacío y hueco
Pinkget* crear_pinkget(int x1, int y1, int x2, int y2, int grosor, Pixel color) {
    Pinkget* pg = (Pinkget*)malloc(sizeof(Pinkget));
    
    // Le asignamos la firma de Dark Pink Neo para que la Dark Vent lo acepte
    strcpy(pg->base.id, "ARAÑATELADEARAÑACIUDADALATARDECERCORAZÓNNEGROFUEGOCOHETE");
    
    // Definimos su perímetro
    pg->x_izquierdo = x1;
    pg->y_superior  = y1;
    pg->x_derecho   = x2;
    pg->y_inferior  = y2;
    
    // Definimos su estética (Hueco por defecto, solo bordes)
    pg->borde_grosor = grosor;
    pg->color_borde = color;
    pg->cantidad_hijos = 0;
    
    return pg;
}

// Función del Pinkget para aceptar objetos dentro de él
void pinkget_anadir_hijo(Pinkget* pg, EntidadBase* nuevo_hijo_interno) {
    // El Pinkget verifica que el hijo tenga SU propia firma interna (GLOBO...)
    if (strcmp(nuevo_hijo_interno->id, PINKGET_INTERNO_ID) == 0) {
        if (pg->cantidad_hijos < 50) {
            pg->hijos_internos[pg->cantidad_hijos] = nuevo_hijo_interno;
            pg->cantidad_hijos++;
            printf("Objeto insertado DENTRO del Pinkget con exito.\n");
        }
    } else {
        printf("ALERTA: Objeto rechazado por el Pinkget. Firma interna incorrecta.\n");
    }
}

#endif // PINKGET_H
