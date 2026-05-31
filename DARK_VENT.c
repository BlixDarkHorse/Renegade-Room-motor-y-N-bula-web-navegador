#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DARK_PINK_NEO_ID "ARAÑATELADEARAÑACIUDADALATARDECERCORAZÓNNEGROFUEGOCOHETE"

// =========================================================================
// ESTRUCTURAS DEL FRAMEWORK
// =========================================================================

typedef struct {
    char id[100];
    int x, y;
    int width, height;
} EntidadBase;

typedef struct {
    uint8_t b, g, r, a;
} Pixel;

// La DARK VENT: El Universo Contenedor (Invisible, abarca toda la pantalla)
typedef struct {
    int screen_width;
    int screen_height;
    Pixel* buffer; // El Framebuffer GIGANTE de toda tu pantalla
    
    EntidadBase* hijos[100];
    int cantidad_hijos;
} DarkVent;

DarkVent* crear_dark_vent_fullscreen() {
    DarkVent* vent = (DarkVent*)malloc(sizeof(DarkVent));
    
    // Obtenemos el tamaño REAL del monitor del usuario
    vent->screen_width = GetSystemMetrics(SM_CXSCREEN);
    vent->screen_height = GetSystemMetrics(SM_CYSCREEN);
    
    // Reservamos la memoria RAM para TODA LA PANTALLA
    vent->buffer = (Pixel*)calloc(vent->screen_width * vent->screen_height, sizeof(Pixel));
    vent->cantidad_hijos = 0;
    return vent;
}

void anadir_hijo_a_vent(DarkVent* vent, EntidadBase* nuevo_hijo) {
    if (strcmp(nuevo_hijo->id, DARK_PINK_NEO_ID) == 0) {
        if (vent->cantidad_hijos < 100) {
            vent->hijos[vent->cantidad_hijos] = nuevo_hijo;
            vent->cantidad_hijos++;
        }
    } else {
        MessageBox(NULL, "ALERTA: Objeto sin firma Dark Pink Neo.", "Seguridad", MB_ICONERROR);
    }
}

// =========================================================================
// CÓDIGO WINDOWS (Dark Vent Invisible)
// =========================================================================

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    
    // 1. Creamos la Dark Vent (Nuestro Framebuffer Invisible gigante)
    DarkVent* universo = crear_dark_vent_fullscreen();
    
    // 2. Registrar la ventana
    const char CLASS_NAME[] = "DarkVentClass";
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    // IMPORTANTE: Ponemos un color de fondo especial (Ej. Negro o Magenta)
    wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 255)); 
    RegisterClass(&wc);

    // 3. NACE LA VENTANA: 
    // WS_POPUP = Sin bordes ni botones de cerrar.
    // WS_EX_LAYERED = Permite que la ventana sea transparente a nivel de píxeles.
    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOOLWINDOW, // TOOLWINDOW evita que salga en el Alt+Tab molestando
        CLASS_NAME, 
        "Dark Vent Invisible",
        WS_POPUP, // Sin bordes (Fullscreen)
        0, 0, universo->screen_width, universo->screen_height,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 0;

    // MAGIA DE LA INVISIBILIDAD:
    // Le decimos a Windows: "Todo píxel que sea color Magenta (255, 0, 255) hazlo INVISIBLE".
    // Así la Dark Vent no se ve, puedes ver tu escritorio normal. 
    // SOLO se verán los Pinkgets o DarkDoors que pintes de OTRO color encima.
    SetLayeredWindowAttributes(hwnd, RGB(255, 0, 255), 0, LWA_COLORKEY);

    // Mostrar (la verás invisible, pero está ahí atrapando la pantalla entera)
    ShowWindow(hwnd, nCmdShow);

    // Bucle infinito
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
