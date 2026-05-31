import sys
import ctypes
from ctypes import wintypes

# 1. ENLACE DIRECTO A LAS DLL DEL KERNEL DE WINDOWS (RING 3 A RING 0)
user32 = ctypes.windll.user32
kernel32 = ctypes.windll.kernel32
gdi32 = ctypes.windll.gdi32

# 2. DEFINICIÓN DE CONSTANTES HEXADECIMALES DE LA API WIN32
WS_POPUP = 0x80000000      # Ventana sin barra de título ni bordes
WS_VISIBLE = 0x10000000    # Hacerla visible inmediatamente
WS_EX_TOPMOST = 0x00000008 # Prioridad de renderizado por encima de todo
WM_DESTROY = 0x0002        # Señal de destrucción de memoria
WM_KEYDOWN = 0x0100        # Señal de intercepción de teclado
VK_ESCAPE = 0x1B           # Código de la tecla ESC
BLACK_BRUSH = 4            # Puntero fáctico al color negro puro del sistema

# 3. DEFINICIÓN ESTRUCTURAL BARE METAL (C STRUCTS EN PYTHON)
LRESULT = ctypes.c_long
WNDPROCTYPE = ctypes.WINFUNCTYPE(LRESULT, wintypes.HWND, wintypes.UINT, wintypes.WPARAM, wintypes.LPARAM)

class WNDCLASS(ctypes.Structure):
    _fields_ = [("style", wintypes.UINT),
                ("lpfnWndProc", WNDPROCTYPE),
                ("cbClsExtra", ctypes.c_int),
                ("cbWndExtra", ctypes.c_int),
                ("hInstance", wintypes.HINSTANCE),
                ("hIcon", wintypes.HICON),
                ("hCursor", wintypes.HICON),
                ("hbrBackground", wintypes.HBRUSH),
                ("lpszMenuName", wintypes.LPCWSTR),
                ("lpszClassName", wintypes.LPCWSTR)]

class MSG(ctypes.Structure):
    _fields_ = [("hwnd", wintypes.HWND),
                ("message", wintypes.UINT),
                ("wParam", wintypes.WPARAM),
                ("lParam", wintypes.LPARAM),
                ("time", wintypes.DWORD),
                ("pt", wintypes.POINT)]

# 4. FUNCIÓN CALLBACK (EL CEREBRO DE LA VENTANA)
def PyWndProc(hwnd, msg, wParam, lParam):
    """ Intercepción fáctica de los eventos del procesador para esta ventana """
    if msg == WM_DESTROY:
        user32.PostQuitMessage(0)
        return 0
    elif msg == WM_KEYDOWN:
        if wParam == VK_ESCAPE:
            user32.DestroyWindow(hwnd)
            return 0
    # Devolver el control al sistema para mensajes no manejados
    return user32.DefWindowProcW(hwnd, msg, wintypes.WPARAM(wParam), wintypes.LPARAM(lParam))

def invocar_hwnd_absoluto():
    # Identificador de la aplicación en memoria
    hInst = kernel32.GetModuleHandleW(None)
    clase_nombre = "LienzoBDH"

    # Enlace de la función de cerebro (WndProc)
    WndProc = WNDPROCTYPE(PyWndProc)

    # 5. REGISTRO DE LA ESTRUCTURA EN EL SISTEMA OPERATIVO
    wndclass = WNDCLASS()
    wndclass.style = 0
    wndclass.lpfnWndProc = WndProc
    wndclass.cbClsExtra = 0
    wndclass.cbWndExtra = 0
    wndclass.hInstance = hInst
    wndclass.hIcon = 0
    wndclass.hCursor = user32.LoadCursorW(0, 32512) # Cursor estándar (IDC_ARROW)
    wndclass.hbrBackground = gdi32.GetStockObject(BLACK_BRUSH) # Fondo negro puro
    wndclass.lpszMenuName = None
    wndclass.lpszClassName = clase_nombre

    if not user32.RegisterClassW(ctypes.byref(wndclass)):
        raise SystemError("Fallo crítico: El SO rechazó el registro de la WNDCLASS.")

    # 6. EXTRACCIÓN DE METRICAS DEL MONITOR PRINCIPAL
    ancho_pantalla = user32.GetSystemMetrics(0) # SM_CXSCREEN
    alto_pantalla = user32.GetSystemMetrics(1)  # SM_CYSCREEN

    # 7. INVOCACIÓN DEL HWND EN LA MEMORIA RAM
    hwnd = user32.CreateWindowExW(
        WS_EX_TOPMOST,          # dwExStyle
        clase_nombre,           # lpClassName
        "Lienzo Fáctico BDH",   # lpWindowName
        WS_POPUP | WS_VISIBLE,  # dwStyle
        0, 0,                   # x, y (Coordenadas de inicio)
        ancho_pantalla,         # nWidth
        alto_pantalla,          # nHeight
        0,                      # hWndParent
        0,                      # hMenu
        hInst,                  # hInstance
        None                    # lpParam
    )

    if not hwnd:
        raise SystemError("Fallo crítico: El SO denegó la creación del HWND.")

    # 8. BUCLE DE MENSAJES INFINITO (EL MOTOR DE VIDA)
    msg = MSG()
    while user32.GetMessageW(ctypes.byref(msg), 0, 0, 0) != 0:
        user32.TranslateMessage(ctypes.byref(msg))
        user32.DispatchMessageW(ctypes.byref(msg))

if __name__ == "__main__":
    invocar_hwnd_absoluto()