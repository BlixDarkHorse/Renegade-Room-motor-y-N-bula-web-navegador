#ifndef DARK_DOOR_H
#define DARK_DOOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PINKGET.h" // Usamos las estructuras base

// =========================================================================
// FIRMA INTERNA EXCLUSIVA DE DARK DOOR
// =========================================================================
#define DARK_DOOR_INTERNO_ID "ARAÑATELADEARAÑAPUERTALETRASNEGROFUEGOCOHETE"

// =========================================================================
// ESTRUCTURA DE LA DARK DOOR
// =========================================================================
typedef struct {
    EntidadBase base; // Hereda ID para entrar a la Dark Vent
    
    // Su propio ID interno para aceptar scripts o textos
    char firma_interna[100]; 
    
    // Perímetro de la puerta
    int x, y;
    int width, height;
    
    // Buffer de texto/HTML crudo que va a parsear
    char codigo_html_crudo[4096]; 
    
} DarkDoor;

// =========================================================================
// LÓGICA DE DARK DOOR (Módulo de Parseo)
// =========================================================================

DarkDoor* crear_dark_door(int x, int y, int w, int h) {
    DarkDoor* door = (DarkDoor*)malloc(sizeof(DarkDoor));
    
    // 1. Le damos pasaporte para la Dark Vent
    strcpy(door->base.id, "ARAÑATELADEARAÑACIUDADALATARDECERCORAZÓNNEGROFUEGOCOHETE");
    
    // 2. Geometría
    door->x = x; door->y = y;
    door->width = w; door->height = h;
    
    // 3. Vaciamos la memoria del texto HTML
    memset(door->codigo_html_crudo, 0, sizeof(door->codigo_html_crudo));
    
    return door;
}

// -------------------------------------------------------------------------
// EL "MICRO-PARSER" (Simulación rápida de lectura de HTML/CSS)
// -------------------------------------------------------------------------
void dark_door_parsear_html(DarkDoor* door, const char* html_input) {
    printf("\n[DARK DOOR] Iniciando parseo de HTML/CSS...\n");
    
    // Guardamos el código crudo en la memoria de la puerta
    strncpy(door->codigo_html_crudo, html_input, 4095);
    
    // SIMULACIÓN DE PARSEO RÁPIDO:
    // Aquí es donde un motor real leería los tags. Nosotros haremos una prueba básica:
    if (strstr(door->codigo_html_crudo, "<body>") != NULL) {
        printf("  -> [Exito] Etiqueta <body> detectada.\n");
    }
    
    if (strstr(door->codigo_html_crudo, "color: red") != NULL || strstr(door->codigo_html_crudo, "color:red") != NULL) {
        printf("  -> [CSS Detectado] El texto dentro de esta Dark Door sera ROJO.\n");
        // Aquí mandarías la orden al Framebuffer de pintar texto en color Rojo
    }
    
    printf("[DARK DOOR] Parseo finalizado. Listo para renderizar en Framebuffer.\n\n");
}

#endif // DARK_DOOR_H
