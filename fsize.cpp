#include <iostream>
#include <filesystem>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

struct SizeInfo {
    uintmax_t bytes;
    double kilobytes;
    double megabytes;
    double gigabytes;
    double terabytes;
};

void printHelp() {
    std::cout << "Uso: fsize [OPCION]... [ARCHIVO/DIRECTORIO]...\n";
    std::cout << "Muestra el tamaño de archivos o directorios en diferentes unidades.\n\n";
    std::cout << "Opciones:\n";
    std::cout << "  -f, --file ARCHIVO       Especifica un archivo para analizar\n";
    std::cout << "  -d, --directory DIR      Especifica un directorio para analizar\n";
    std::cout << "  -h, --help               Muestra esta ayuda y sale\n";
    std::cout << "  -p                       Muestra una barra de progreso (no implementado aún)\n\n";
    std::cout << "Ejemplos:\n";
    std::cout << "  fsize --file /ruta/archivo.ext\n";
    std::cout << "  fsize -d /ruta/directorio/\n";
}

SizeInfo calculateSize(const fs::path& path) {
    SizeInfo info{0, 0.0, 0.0, 0.0, 0.0};
    
    if (fs::is_regular_file(path)) {
        info.bytes = fs::file_size(path);
    } else if (fs::is_directory(path)) {
        for (const auto& entry : fs::recursive_directory_iterator(path)) {
            if (fs::is_regular_file(entry.status())) {
                info.bytes += fs::file_size(entry.path());
            }
        }
    }
    
    // Calcular las diferentes unidades
    info.kilobytes = static_cast<double>(info.bytes) / 1024;
    info.megabytes = info.kilobytes / 1024;
    info.gigabytes = info.megabytes / 1024;
    info.terabytes = info.gigabytes / 1024;
    
    return info;
}

void printSizeInfo(const fs::path& path, const SizeInfo& info) {
    std::cout << std::fixed << std::setprecision(2);
    
    if (fs::is_regular_file(path)) {
        std::cout << "Archivo: \"" << path.string() << "\"\n";
    } else {
        std::cout << "Directorio: \"" << path.string() << "\"\n";
    }
    
    std::cout << "Tamaño: ";
    
    // Mostrar siempre Bytes
//    std::cout << "  Bytes: " << info.bytes << " B\n";
    
    // Mostrar solo las unidades relevantes
    if (info.bytes < 1024) {
        std::cout << "Kilobytes: " << info.kilobytes << " KB\n";
    } 
    else if (info.kilobytes < 1024) {
        std::cout << "Kilobytes: " << info.kilobytes << " KB\n";
    } 
    else if (info.megabytes < 1024) {
        std::cout << "Megabytes: " << info.megabytes << " MB\n";
    } 
    else if (info.gigabytes < 1024) {
        std::cout << "Gigabytes: " << info.gigabytes << " GB\n";
    } 
    else {
        std::cout << "Terabytes: " << info.terabytes << " TB\n";
    }
    
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Se requiere al menos un argumento.\n";
        printHelp();
        return 1;
    }
    
    std::vector<std::string> args(argv + 1, argv + argc);
    fs::path targetPath;
    bool isFile = false;
    bool isDirectory = false;
    bool showProgress = false;
    
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == "--help" || args[i] == "-h") {
            printHelp();
            return 0;
        } else if (args[i] == "-p") {
            showProgress = true;
        } else if (args[i] == "--file" || args[i] == "-f") {
            if (i + 1 >= args.size()) {
                std::cerr << "Error: Se esperaba un archivo después de " << args[i] << "\n";
                return 1;
            }
            targetPath = args[++i];
            isFile = true;
        } else if (args[i] == "--directory" || args[i] == "-d") {
            if (i + 1 >= args.size()) {
                std::cerr << "Error: Se esperaba un directorio después de " << args[i] << "\n";
                return 1;
            }
            targetPath = args[++i];
            isDirectory = true;
        } else if (i == 0 && args.size() == 1) {
            // Asumir que es un archivo o directorio sin flag
            targetPath = args[i];
        }
    }
    
    // Validar la ruta
    if (!fs::exists(targetPath)) {
        std::cerr << "Error: La ruta \"" << targetPath.string() << "\" no existe.\n";
        return 1;
    }
    
    // Determinar si es archivo o directorio si no se especificó
    if (!isFile && !isDirectory) {
        if (fs::is_regular_file(targetPath)) {
            isFile = true;
        } else if (fs::is_directory(targetPath)) {
            isDirectory = true;
        }
    }
    
    // Verificar consistencia
    if ((isFile && !fs::is_regular_file(targetPath)) || 
        (isDirectory && !fs::is_directory(targetPath))) {
        std::cerr << "Error: El tipo de la ruta no coincide con la opción especificada.\n";
        return 1;
    }
    
    // Calcular y mostrar el tamaño
    SizeInfo sizeInfo = calculateSize(targetPath);
    printSizeInfo(targetPath, sizeInfo);
    
    return 0;
}
