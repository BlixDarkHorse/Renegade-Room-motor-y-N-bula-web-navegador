#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// 1. Estructura para representar un Píxel (Color RGBA)
typedef struct {
    uint8_t b; // Azul
    uint8_t g; // Verde
    uint8_t r; // Rojo
    uint8_t a; // Alfa (Transparencia)
} Pixel;

// 2. Estructura del Framebuffer (La pantalla en memoria)
typedef struct {
    int width;
    int height;
    Pixel* buffer; // El "array" de píxeles que representa toda la pantalla
} Framebuffer;

// Función para crear y asignar memoria al Framebuffer
Framebuffer* create_framebuffer(int width, int height) {
    Framebuffer* fb = (Framebuffer*)malloc(sizeof(Framebuffer));
    if (!fb) return NULL;
    
    fb->width = width;
    fb->height = height;
    // Calloc inicializa la memoria en 0 (pantalla negra/transparente por defecto)
    fb->buffer = (Pixel*)calloc(width * height, sizeof(Pixel)); 
    
    return fb;
}

// Función para liberar la memoria
void destroy_framebuffer(Framebuffer* fb) {
    if (fb) {
        if (fb->buffer) free(fb->buffer);
        free(fb);
    }
}

// =========================================================================
// RENDERIZADOR BÁSICO (El inicio muy primitivo de un motor CSS/HTML)
// =========================================================================

// Función para pintar un pixel en coordenadas (x, y)
void draw_pixel(Framebuffer* fb, int x, int y, Pixel color) {
    if (x >= 0 && x < fb->width && y >= 0 && y < fb->height) {
        // Fórmula para encontrar la posición en un arreglo unidimensional
        fb->buffer[y * fb->width + x] = color;
    }
}

// Función para renderizar el equivalente a un <div> de HTML con background-color (CSS)
void render_div(Framebuffer* fb, int x, int y, int width, int height, Pixel color) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            draw_pixel(fb, x + j, y + i, color);
        }
    }
}

int main() {
    printf("Iniciando motor DARK DOOR...\n");

    // 1. Crear una pantalla virtual (Framebuffer) de 800x600 pixeles
    int screen_width = 800;
    int screen_height = 600;
    Framebuffer* my_screen = create_framebuffer(screen_width, screen_height);

    if (!my_screen) {
        printf("Error al asignar memoria para la pantalla.\n");
        return 1;
    }

    printf("Framebuffer creado con exito: %dx%d pixeles.\n", screen_width, screen_height);

    // 2. Simular renderizado de HTML/CSS
    // Imagina que parseaste esto:
    // <div style="width: 200px; height: 100px; background-color: red; position: absolute; left: 50px; top: 50px;"></div>
    
    Pixel color_rojo = {0, 0, 255, 255}; // B, G, R, A
    
    printf("Renderizando <div> rojo...\n");
    render_div(my_screen, 50, 50, 200, 100, color_rojo);

    // En un caso real, aquí enviarías 'my_screen->buffer' a la API de tu Sistema Operativo 
    // (como Windows GDI, OpenGL, o SDL2) para que realmente se dibuje en tu monitor.
    // Como esto es consola, no podemos "ver" los pixeles, pero están en la memoria RAM.

    // 3. Limpieza
    destroy_framebuffer(my_screen);
    printf("Motor cerrado. Memoria liberada.\n");

    return 0;
}
