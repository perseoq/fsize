# FSize - Herramienta CLI para mostrar tamaños de archivos y directorios

## Descripción

FSize es una herramienta de línea de comandos escrita en C++ que muestra el tamaño de archivos y directorios en diferentes unidades (KB, MB, GB, TB) de forma clara y concisa.

## Características

- Muestra tamaños en las unidades más apropiadas
- Soporta tanto archivos como directorios
- Proporciona una salida formateada y fácil de leer
- Incluye sistema de ayuda integrado
- Soporta múltiples formatos de argumentos

## Instalación

1. Clona el repositorio o descarga el código fuente
2. Compila el programa (requiere C++17):
   ```bash
   g++ -std=c++17 fsize.cpp -o fsize
   ```
3. (Opcional) Mueve el ejecutable a tu PATH:
   ```bash
   sudo mv fsize /usr/local/bin/
   ```

## Uso

### Sintaxis básica:
```bash
fsize [OPCIÓN]... [ARCHIVO/DIRECTORIO]...
```

### Opciones:
| Opción          | Descripción                               |
|-----------------|-------------------------------------------|
| `-f, --file`    | Especifica un archivo para analizar      |
| `-d, --directory` | Especifica un directorio para analizar |
| `-h, --help`    | Muestra la ayuda y sale                   |

### Ejemplos:

Mostrar tamaño de un archivo:
```bash
fsize --file documento.pdf
# O
fsize -f imagen.jpg
```

Mostrar tamaño de un directorio:
```bash
fsize --directory /ruta/directorio
# O
fsize -d /ruta/directorio
```

Mostrar ayuda:
```bash
fsize --help
```

## Ejemplos de salida

Para un archivo de 2.25MB:
```
Archivo: "/ruta/archivo.png"
Tamaño: Megabytes: 2.25 MB
```

Para un archivo de 648KB:
```
Archivo: "/ruta/documento.docx"
Tamaño: Kilobytes: 648.33 KB
```

Para un directorio grande:
```
Directorio: "/ruta/gran_directorio"
Tamaño: Gigabytes: 5.00 GB
```

## Requisitos

- Compilador C++ compatible con C++17
- Sistema operativo Linux, macOS o Windows con soporte para filesystem de C++17

## Contribuciones

Las contribuciones son bienvenidas. Por favor abre un issue o envía un pull request.


