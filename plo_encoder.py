import sys
import multiprocessing
from PIL import Image

# ==============================================================================
# ESTE SCRIPT CONVIERTE CUALQUIER IMAGEN A TU FORMATO PROPIETARIO .PLO
# Usando todos los hilos del procesador para máxima velocidad.
# ==============================================================================

CABECERA_PLO = b"ARA\xd1ATELADEARA\xd1AUNICORNIOCORAZ\xd3NNEGROFUEGOCOHETE"

def rgb_a_token(r, g, b):
    # ==========================================================================
    # AQUI CONECTARIAS TU "PARADISE.BIN"
    # Como no tengo tu archivo paradise.bin físico, simularé la creación de un token.
    # En tu versión real, aquí cargarías paradise.bin a la memoria (un diccionario)
    # y simplemente harías: return diccionario_paradise[(r,g,b)]
    # ==========================================================================
    
    # Simulación de un Token de 32 bits basado en RGB (ignorando Alfa)
    token = (r << 16) | (g << 8) | b 
    return token

def procesar_fila_de_pixeles(fila_datos):
    """
    Esta función es la que procesarán los múltiples núcleos de tu CPU.
    Recibe una fila de píxeles (RGB o RGBA), elimina el Alfa,
    y la convierte a Tokens de Paradise.
    """
    y, pixeles_fila = fila_datos
    tokens_fila = []
    
    for pixel in pixeles_fila:
        r, g, b = pixel[0], pixel[1], pixel[2] # Ignoramos pixel[3] si es que hay Alfa
        token = rgb_a_token(r, g, b)
        tokens_fila.append(token)
        
    return (y, tokens_fila)

def convertir_imagen_a_plo(ruta_entrada, ruta_salida):
    print(f"Abriendo imagen: {ruta_entrada}...")
    
    # 1. Cargar la imagen con Pillow
    img = Image.open(ruta_entrada)
    
    # 2. Asegurarnos de que está en modo RGB (Pillow quita el Alfa automáticamente si convertimos a RGB)
    img = img.convert("RGB")
    width, height = img.size
    
    print(f"Resolucion: {width}x{height}. Iniciando tokenizacion Multihilo...")
    
    # 3. Preparar los datos por filas para repartir el trabajo a la CPU
    pixeles = list(img.getdata())
    filas = []
    for y in range(height):
        inicio = y * width
        fin = inicio + width
        filas.append((y, pixeles[inicio:fin]))
        
    # 4. EXPRIMIR LA CPU: Usar Pool de Multiprocesamiento
    # multiprocessing.cpu_count() detecta todos tus núcleos (ej. 8, 16 o 32 hilos)
    nucleos = multiprocessing.cpu_count()
    print(f"Exprimiendo {nucleos} nucleos del procesador...")
    
    tokens_ordenados = []
    with multiprocessing.Pool(processes=nucleos) as pool:
        # Mapeamos la función a todas las filas en paralelo
        resultados = pool.map(procesar_fila_de_pixeles, filas)
        
        # Volvemos a ordenar los resultados por si un hilo terminó antes que otro
        resultados.sort(key=lambda x: x[0])
        for res in resultados:
            tokens_ordenados.extend(res[1])

    # 5. ESCRIBIR EL ARCHIVO .PLO BINARIO FINAL
    print(f"Escribiendo archivo {ruta_salida}...")
    with open(ruta_salida, "wb") as f:
        # Escribimos la cabecera mágica
        f.write(CABECERA_PLO)
        # Escribimos el Ancho y Alto (ej: W1920H1080)
        dimensiones = f"W{width}H{height}".encode('utf-8')
        f.write(dimensiones)
        
        # Escribimos los tokens binarios (Asumiendo tokens de 4 bytes / 32 bits)
        for token in tokens_ordenados:
            f.write(token.to_bytes(4, byteorder='little'))

    print(f"¡Exito! La imagen ahora es un archivo .PLO listo para Neoground.")

if __name__ == '__main__':
    # Requiere instalar Pillow: pip install Pillow
    # Ejemplo de uso (cambia 'imagen.png' por una imagen que tengas):
    # convertir_imagen_a_plo('imagen.png', 'textura.plo')
    print("Codificador PLO cargado. Edita el script para procesar tu imagen.")
