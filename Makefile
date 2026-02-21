# ==============================================================================
# VARIABLES
# Las variables en un Makefile facilitan la ejecución del proyecto.
# ==============================================================================

# CXX define el compilador de C++ que vamos a utilizar (en este caso, GNU C++).
CXX := g++

# CXXFLAGS contiene las opciones que se le pasarán al compilador.
# -std=c++17 : Usa el estándar C++17.
# -Wall -Wextra -pedantic : Activa un nivel alto de advertencias (warnings) 
# para ayudarnos a detectar posibles errores y escribir un código más limpio y seguro.
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic

# TARGET es el nombre del archivo ejecutable final que se va a generar.
TARGET := app

# SRC es la lista de archivos de código fuente (.cpp) que necesitan ser compilados.
SRC := main.cpp hash_table.cpp

# ==============================================================================
# OBJETIVOS FALSOS (PHONY TARGETS)
# ==============================================================================
# .PHONY le dice a `make` que "all", "run" y "clean" no son archivos físicos.
# Esto evita problemas si por accidente se crea un archivo o carpeta llamado "clean",
# asegurando que `make clean` siga ejecutando el comando de limpieza en lugar de 
# pensar que el archivo "clean" ya está actualizado.
.PHONY: all run clean

# ==============================================================================
# REGLAS Y RECETAS
# ==============================================================================

# 'all' es el objetivo por defecto. Si en la terminal solo escribes `make`, 
# automáticamente buscará cumplir esta regla. Su única función es generar el $(TARGET).
all: $(TARGET)

# Esta es la regla principal para compilar. 
# Dice: "Para crear $(TARGET) (el archivo 'app'), necesito que existan y estén 
# actualizados los archivos en $(SRC) (main.cpp y hash_table.cpp)".
$(TARGET): $(SRC)
	# Esta es la "receta" (el comando real que se ejecuta en la terminal).
	# Se traduce a: g++ -std=c++17 -Wall -Wextra -pedantic main.cpp hash_table.cpp -o app
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# La palabra 'run' nos permite compilar (si es necesario) y ejecutar el programa de un solo golpe.
# Al tener a $(TARGET) como dependencia, make se asegura de que 'app' esté creado 
# o actualizado antes de intentar ejecutarlo.
run: $(TARGET)
	# Comando para ejecutar el programa resultante.
	./$(TARGET)

# La palabra 'clean' sirve para borrar los archivos generados y limpiar el espacio de trabajo.
# Se ejecuta escribiendo `make clean` en la terminal.
clean:
	# rm -f fuerza la eliminación del archivo ejecutable (el archivo 'app').
	rm -f $(TARGET)