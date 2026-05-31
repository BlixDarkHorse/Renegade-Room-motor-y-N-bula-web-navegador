#ifndef NEOGROUND_H
#define NEOGROUND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PINKGET.h" // Necesitamos saber cómo es un Pinkget

// =========================================================================
// FIRMA INTERNA DE UNA IMAGEN .PLO
// =========================================================================
#define PLO_MAGIC_HEADER "ARAÑATELADEARAÑAUNICORNIOCORAZÓNNEGROFUEGOCOHETE"

// =========================================================================
// ESTRUCTURA DE NEOGROUND (El visor de imágenes dentro de Pinkget)
// =========================================================================
typedef struct {
    EntidadBase base; // Hereda la estructura. AQUÍ irá el ID del Pinkget
    
    int width;
    int height;
    
    // Puntero a la memoria donde se cargará el archivo .PLO decodificado
    // En tu diseño, este array guardará los "Tokens" de PARADISE.bin
    unsigned int* tokens_colores; 
    
} Neoground;

// =========================================================================
// LÓGICA DE NEOGROUND
// =========================================================================

Neoground* crear_neoground(const char* archivo_plo) {
    Neoground* ng = (Neoground*)malloc(sizeof(Neoground));
    
    // 1. PASAPORTE PARA EL PINKGET:
    // Neoground vive dentro de un Pinkget, así que debe tener la firma del GLOBO
    strcpy(ng->base.id, PINKGET_INTERNO_ID);
    
    // 2. Aquí iría la lógica de lectura del archivo .PLO
    // Abres el archivo, verificas que empiece con la cabecera del UNICORNIO,
    // lees W(ancho) y H(alto), y luego cargas los tokens a la memoria.
    
    // (Simulación)
    ng->width = 0;
    ng->height = 0;
    ng->tokens_colores = NULL;
    
    return ng;
}

#endif // NEOGROUND_H
