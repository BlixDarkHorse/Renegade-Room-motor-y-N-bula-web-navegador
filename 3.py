import webview

# 1. Se define la ventana con directivas de evasión del OS
webview.create_window(
    'Universo BDH - Motor WebView2', 
    'file:///C:/Users/katon/Documents/index.html',
    frameless=True,       # 🦇 ORDEN FÁCTICA: Elimina barra de título, botones y bordes
    transparent=True      # 🦇 ORDEN FÁCTICA: (Opcional) Permite fondo holográfico si el HTML no tiene color de fondo
)

# 2. Se inicia el motor
webview.start()