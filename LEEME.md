# Hash Table

A simple key-value data structure implemented from scratch over a raw array, without using C++ native map collections. It also implements an automatic mechanism that resizes the underlying array when a certain Load Factor is reached.

## Tech Used
- Language:
- Tools/Libraries:

## How to Run
```bash
# build
<command>

# run
<command>
```

## How It Works (Simple)

1. Step 1.
2. Step 2.
3. Step 3.

## Next Improvements

- Improvement 1.
- Improvement 2.

## What I Learned

### Core
- Una **función hash** es un algoritmo matemático que recibe un conjunto de datos (bytes) y retorna un número entero. Ese número puede representarse en base 2, 10, 16, etc., según convenga.
- Existen distintos tipos de funciones hash y cada una se elige según la tarea que se quiere resolver. La que se implementa en este programa es la variante **Polynomial Rolling Hash**.
  - Esta variante recibe un string y devuelve un número entero que, en este contexto, servirá como índice para un array. De manera iterativa, un contador se multiplica por un número como 31 o 53 y luego se suma el valor ASCII de la letra actual del string. Tras recorrer todo el string, se aplica módulo con el tamaño del array para obtener un índice dentro del rango disponible.
  - Multiplicar por un número primo como 31 ayuda mucho a reducir colisiones (pero no por completo). Por ejemplo, dos strings con las mismas letras (`"amor"` y `"roma"`) pueden tener el mismo índice si se omite la multiplicación.
- Utilizar esta variante es muy conveniente porque mejora la velocidad para insertar y buscar elementos dentro del array. En lugar de recorrer todo (`O(n)`), se accede directamente al índice recibido en tiempo promedio `O(1)`.
- El **Linear Probing** es una técnica muy sencilla para resolver **colisiones**. Cuando la función hash calcula un índice para un nuevo elemento, pero esa posición del array ya está ocupada, el algoritmo simplemente busca linealmente (sumando 1 al índice) hasta encontrar la siguiente posición que esté libre y lo inserta ahí.
- El **Load Factor** (o factor de carga) es un indicador que mide qué tan lleno está nuestro array. Se calcula dividiendo la cantidad de elementos insertados entre la capacidad total. Si este valor cruza un límite establecido (por ejemplo, `0.7` o el 70% de ocupación), nos advierte que el arreglo está muy lleno y el riesgo de colisiones es demasiado alto.
- El **Rehashing** es el proceso de rescate que ocurre cuando se excede el Load Factor. Consiste en crear un nuevo array, usualmente del doble de tamaño que el original, para tener más espacio y volver a la normalidad.
  - **¿Cómo funciona?** No basta con simplemente copiar los elementos al nuevo array. Al aumentar el tamaño del arreglo, el número por el que aplicamos el "módulo" en nuestra función hash cambia. Por lo tanto, la **función de rehashing** toma cada elemento del viejo array, recalcula su nuevo índice (usando la nueva capacidad) y lo reubica en el nuevo arreglo.

### Secondaries
- **Separación de archivos**: En C++, es una gran práctica separar la estructura en dos partes. Los archivos de encabezado (`.h` o `.hpp`) se usan solo para "declarar" qué clases, variables y funciones existirán, mientras que los archivos fuente (`.cpp`) contienen la "implementación" o la lógica real de esas funciones. Esto hace el código más ordenado y acelera el tiempo de compilación.
- **Structs**: Un `struct` (estructura) es una forma de empaquetar variables de distintos tipos bajo un solo nombre. Por ejemplo, un `struct Persona` puede contener un texto (nombre) y un número (edad). En C++, son casi idénticos a las clases, con la diferencia principal de que su contenido es público por defecto.
- **Convenciones de nombres**: Para mantener el código legible, se suele usar `camelCase` o `snake_case` para variables y funciones. Para las **variables globales** (aquellas accesibles desde cualquier parte del código), se acostumbra ponerles el prefijo `g_` (ej. `g_contador`) para identificarlas de inmediato y evitar modificarlas por accidente.
- **Manejo de excepciones**: Para evitar que el programa explote ante un error, se usan bloques `try...catch`. Se coloca el código riesgoso dentro de `try`, y si algo sale mal, el programa "lanza" (`throw`) un error que es atrapado y manejado pacíficamente dentro del `catch`.
- **El símbolo `&` (Referencias)**: Se usa para pasar una variable a una función por "referencia" y no por "copia". Es decir, en lugar de crear un clon de la variable, le damos a la función acceso directo a la original. Esto ahorra memoria y permite que los cambios hechos dentro de la función se reflejen afuera.
- **Punteros y `new`**: Un puntero es una variable especial que, en lugar de guardar un dato común, guarda la "dirección de memoria" de otro dato. La palabra clave `new` se usa junto con los punteros para pedir memoria dinámicamente al sistema operativo mientras el programa está corriendo. Toda memoria pedida con `new` debe liberarse manualmente después (usando `delete`).
- **`static_cast`**: Es la forma segura y moderna en C++ de convertir un tipo de dato en otro (por ejemplo, de un número decimal a un número entero). Es preferible usar esto porque el compilador verifica que la conversión tenga sentido antes de ejecutar el programa.
- **Validación de inputs numéricos**: Al pedir números al usuario con `std::cin`, este puede escribir letras por error. Para manejarlo, se revisa si la entrada no es un número. Si es así, se limpia el estado de error de la consola (`std::cin.clear()`) y se ignora la basura que el usuario escribió (`std::cin.ignore()`), permitiendo volver a pedir el número correctamente.
- **Makefiles**: Un `Makefile` es un archivo de texto que actúa como una receta para compilar tu programa. En lugar de escribir comandos largos en la terminal cada vez que haces un cambio, configuras este archivo para que, al escribir simplemente el comando `make`, tu código se ensamble y compile de forma automática e inteligente.
