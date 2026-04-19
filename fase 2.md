# Guía Paso a Paso: Fase 2 — Matriz 16x16 y Mapa Visual

> **Objetivo:** Escalar el spot único a una matriz 16x16 con mapa visual, vías de acceso, entrada/salida, y manejo de múltiples vehículos.

---

## Índice

1. [¿Qué cambia respecto a Fase 1?](#qué-cambia-respecto-a-fase-1)
2. [Diseño del mapa](#diseño-del-mapa)
3. [Nuevos archivos](#nuevos-archivos)
4. [Bloque A: El mapa](#bloque-a-el-mapa)
5. [Bloque B: Adaptar el spot a múltiples carros](#bloque-b-adaptar-el-spot-a-múltiples-carros)
6. [Bloque C: Adaptar el menú](#bloque-c-adaptar-el-menú)
7. [Compilación y prueba](#compilación-y-prueba)
8. [Checklist final Fase 2](#checklist-final-fase-2)

---

## ¿Qué cambia respecto a Fase 1?

| Fase 1 | Fase 2 |
|--------|--------|
| 1 solo spot | Múltiples spots en una matriz |
| Sin mapa visual | Mapa 16x16 en consola |
| Sin vías ni entrada/salida | Vías, entrada y salida definidas |
| Salida directa (solo 1 carro) | Buscar carro por placa para sacarlo |

**Lo que NO cambia:** la lógica de cobro (`cobro.h` y `cobro.cpp`) queda exactamente igual. Esa es la ventaja de la modularidad.

---

## Diseño del mapa

### Caracteres del mapa

Cada celda de la matriz es un `char` que representa:

| Caracter | Significado |
|----------|-------------|
| `#` | Muro (borde del parqueadero) |
| `.` | Vía (camino por donde circulan carros) |
| `P` | Parqueadero libre |
| `X` | Parqueadero ocupado |
| `E` | Entrada |
| `S` | Salida |

### Diseño propuesto (16x16)

```
# # # # E # # # # # # # # # # #
# . . . . . . . . . . . . . . #
# . P P P . P P P . P P P . . #
# . P P P . P P P . P P P . . #
# . . . . . . . . . . . . . . #
# . P P P . P P P . P P P . . #
# . P P P . P P P . P P P . . #
# . . . . . . . . . . . . . . #
# . P P P . P P P . P P P . . #
# . P P P . P P P . P P P . . #
# . . . . . . . . . . . . . . #
# . P P P . P P P . P P P . . #
# . P P P . P P P . P P P . . #
# . . . . . . . . . . . . . . #
# . . . . . . . . . . . . . . #
# # # # S # # # # # # # # # # #
```

**Características:**
- Bordes de muros (`#`) en todo el perímetro
- Entrada (`E`) arriba, Salida (`S`) abajo
- Vías (`.`) que conectan la entrada con todos los parqueaderos
- Bloques de 3x2 parqueaderos separados por vías
- Total: 72 espacios de parqueadero
- Todos los parqueaderos son accesibles desde las vías

**IMPORTANTE:** Este es un diseño sugerido. Puedes modificarlo como quieras, pero debe cumplir:
- Mínimo 16x16
- Tener entrada y salida
- Tener vías que conecten entrada → parqueaderos → salida
- Los parqueaderos deben ser accesibles por las vías

---

## Nuevos archivos

Agregamos un módulo nuevo para el mapa:

```
parqueadero/
├── main.cpp        ← sin cambios
├── menu.h          ← agregar nuevos prototipos
├── menu.cpp        ← modificar para usar el mapa
├── spot.h          ← agregar vector y nuevas funciones
├── spot.cpp        ← modificar funciones para múltiples spots
├── cobro.h         ← SIN CAMBIOS
├── cobro.cpp       ← SIN CAMBIOS
├── mapa.h          ← NUEVO: declaraciones del mapa
└── mapa.cpp        ← NUEVO: implementación del mapa
```

---

## Bloque A: El mapa

### Paso 1: Crear `mapa.h`

**Qué debe tener:**

1. Header guards
2. Includes necesarios: `"spot.h"` y `<vector>`
3. Constantes del mapa:
   - `const int ROWS = 16;`
   - `const int COLS = 16;`
   - Constantes para cada tipo de celda:
     - `const char WALL = '#';`
     - `const char ROAD = '.';`
     - `const char SPOT_FREE = 'P';`
     - `const char SPOT_TAKEN = 'X';`
     - `const char ENTRY = 'E';`
     - `const char EXIT_GATE = 'S';`
4. Prototipos de funciones:
   - `void initMap(char map[ROWS][COLS]);` → llena la matriz con el diseño del parqueadero
   - `void showMap(char map[ROWS][COLS]);` → imprime el mapa en consola
   - `void updateMap(char map[ROWS][COLS], std::vector<Spot>& spots);` → actualiza el mapa según los spots ocupados/libres

**Esqueleto:**

```cpp
#ifndef MAPA_H
#define MAPA_H

#include "spot.h"
#include <vector>

const int ROWS = 16;
const int COLS = 16;

// constantes de celdas aquí

// prototipos aquí

#endif
```

### Paso 2: Crear `mapa.cpp`

#### Función `initMap`

Esta función llena la matriz 16x16 con el diseño del parqueadero. Aquí es donde defines dónde van los muros, vías, parqueaderos, entrada y salida.

**Hay dos formas de hacerlo:**

**Opción A — Hardcoded (más fácil):**

Defines el mapa como un arreglo de strings y lo copias a la matriz:

```cpp
void initMap(char map[ROWS][COLS]) {
    const char layout[ROWS][COLS] = {
        {'#','#','#','#','E','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','P','P','P','.','P','P','P','.','P','P','P','.','.','#'},
        // ... resto de filas
    };

    // copiar con for
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = layout[i][j];
        }
    }
}
```

**Opción B — Generado (más elegante, suma puntos de innovación):**

Usas lógica para generar el mapa: bordes son muros, ciertas posiciones son parqueaderos, el resto vías. Más complejo pero más impresionante.

**Recomendación:** empieza con Opción A para que funcione rápido. Si te sobra tiempo, refactorizas a Opción B como innovación.

#### Función `showMap`

Recorre la matriz con dos `for` anidados e imprime cada caracter:

```cpp
void showMap(char map[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << map[i][j] << " ";
        }
        std::cout << "\n";
    }
}
```

**Concepto importante:** aquí usas los ciclos `for` que el enunciado pide como obligatorios.

#### Función `updateMap`

Recorre el vector de spots y actualiza las celdas del mapa:

```cpp
void updateMap(char map[ROWS][COLS], std::vector<Spot>& spots) {
    for (int i = 0; i < spots.size(); i++) {
        int r = spots[i].row;
        int c = spots[i].col;
        if (spots[i].occupied) {
            map[r][c] = SPOT_TAKEN;   // 'X'
        } else {
            map[r][c] = SPOT_FREE;    // 'P'
        }
    }
}
```

---

## Bloque B: Adaptar el spot a múltiples carros

### Paso 3: Modificar `spot.h`

**Agregar al struct Spot:**

Dos campos nuevos para saber dónde está cada spot en el mapa:

```cpp
struct Spot {
    int row;                // fila en el mapa
    int col;                // columna en el mapa
    std::string plate;
    std::time_t entryTime;
    bool occupied;
};
```

**Agregar nuevos includes:**

```cpp
#include <vector>
```

**Agregar nuevos prototipos:**

```cpp
void initSpots(std::vector<Spot>& spots, char map[16][16]);
// recorre el mapa y crea un Spot por cada 'P' encontrada

int findSpotByPlate(std::vector<Spot>& spots, std::string plate);
// busca un carro por placa, devuelve la posición en el vector (-1 si no lo encuentra)

int findFreeSpot(std::vector<Spot>& spots);
// busca el primer spot libre, devuelve la posición (-1 si está lleno)

void registerEntry(std::vector<Spot>& spots);
// versión nueva: pide placa, busca spot libre, registra

void registerExit(std::vector<Spot>& spots);
// versión nueva: pide placa, busca el carro, calcula cobro, libera

void showStatus(std::vector<Spot>& spots);
// versión nueva: muestra cuántos libres y ocupados
```

**Nota:** las funciones viejas (`initSpot`, `registerEntry`, `registerExit`, `showStatus`) que recibían `Spot*` van a cambiar para trabajar con el vector. Puedes mantener `initSpot(Spot*)` como helper interno y agregar las nuevas.

### Paso 4: Implementar nuevas funciones en `spot.cpp`

#### `initSpots` — Crear spots desde el mapa

Recorre la matriz y por cada celda que sea `'P'`, crea un Spot y lo agrega al vector:

```cpp
void initSpots(std::vector<Spot>& spots, char map[16][16]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (map[i][j] == 'P') {
                Spot s;
                s.row = i;
                s.col = j;
                s.plate = "";
                s.entryTime = 0;
                s.occupied = false;
                spots.push_back(s);  // agregar al vector
            }
        }
    }
}
```

**Concepto importante:** `push_back` agrega un elemento al final del vector. No necesitas saber de antemano cuántos parqueaderos hay.

#### `findSpotByPlate` — Buscar carro por placa

```cpp
int findSpotByPlate(std::vector<Spot>& spots, std::string plate) {
    for (int i = 0; i < spots.size(); i++) {
        if (spots[i].occupied && spots[i].plate == plate) {
            return i;   // encontrado, devuelve posición
        }
    }
    return -1;   // no encontrado
}
```

**Concepto:** devuelve `-1` si no existe. Esto es un patrón clásico en programación: -1 como "no encontrado".

#### `findFreeSpot` — Buscar primer espacio libre

```cpp
int findFreeSpot(std::vector<Spot>& spots) {
    for (int i = 0; i < spots.size(); i++) {
        if (!spots[i].occupied) {
            return i;   // primer libre
        }
    }
    return -1;   // parqueadero lleno
}
```

#### `registerEntry` — Nueva versión

Flujo:
1. Buscar spot libre con `findFreeSpot`
2. Si no hay → "Parqueadero lleno" y return
3. Pedir placa
4. Validar placa con `validatePlate`
5. Verificar que la placa no esté ya registrada con `findSpotByPlate`
6. Registrar en el spot libre

#### `registerExit` — Nueva versión

Flujo:
1. Pedir la placa del carro que sale
2. Buscar con `findSpotByPlate`
3. Si no existe → "Vehiculo no encontrado" y return
4. Calcular minutos y cobro
5. Imprimir recibo
6. Liberar el spot con `initSpot`

#### `showStatus` — Nueva versión

Contar cuántos spots libres y ocupados:

```cpp
void showStatus(std::vector<Spot>& spots) {
    int free = 0;
    int taken = 0;
    for (int i = 0; i < spots.size(); i++) {
        if (spots[i].occupied) taken++;
        else free++;
    }
    std::cout << "Libres: " << free << "\n";
    std::cout << "Ocupados: " << taken << "\n";
    std::cout << "Total: " << spots.size() << "\n";
}
```

---

## Bloque C: Adaptar el menú

### Paso 5: Modificar `menu.h`

No cambia: `startProgram()` sigue siendo el único prototipo público.

### Paso 6: Modificar `menu.cpp`

**Nuevos includes:**

```cpp
#include "mapa.h"
```

**Modificar `startProgram()`:**

Ahora necesita:
1. Crear la matriz del mapa: `char map[ROWS][COLS];`
2. Inicializar el mapa: `initMap(map);`
3. Crear el vector de spots: `std::vector<Spot> spots;`
4. Inicializar spots desde el mapa: `initSpots(spots, map);`
5. En el loop, antes del menú:
   - Actualizar el mapa: `updateMap(map, spots);`
   - Mostrar el mapa: `showMap(map);`
6. Los cases del switch ahora pasan `spots` en vez de `&spot`

**Esqueleto:**

```cpp
void startProgram() {
    char map[ROWS][COLS];
    initMap(map);

    std::vector<Spot> spots;
    initSpots(spots, map);

    int option = 0;
    do {
        updateMap(map, spots);
        showMap(map);
        showMenu();
        std::cin >> option;
        std::cin.ignore();

        switch (option) {
            case 1:
                showStatus(spots);
                break;
            case 2:
                registerEntry(spots);
                break;
            case 3:
                registerExit(spots);
                break;
            case 4:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida\n";
                break;
        }
    } while (option != 4);
}
```

---

## Compilación y prueba

### Compilar

Ahora incluye los nuevos archivos:

```bash
g++ main.cpp menu.cpp spot.cpp cobro.cpp mapa.cpp -o parqueadero
```

### Plan de prueba

1. Al iniciar → debe mostrar el mapa con todas las `P` libres
2. Registrar entrada → el mapa debe mostrar una `X` donde se estacionó
3. Registrar 2-3 carros más → deben aparecer más `X` en el mapa
4. Ver estado → debe mostrar cuántos libres y ocupados
5. Registrar salida por placa → la `X` vuelve a ser `P`
6. Llenar todos los spots → debe decir "Parqueadero lleno"
7. Buscar placa inexistente → debe decir "No encontrado"

---

## Checklist final Fase 2

Antes de pasar a Fase 3, confirma que cumples TODO:

- [ ] Mapa 16x16 visible en consola
- [ ] Muros, vías, entrada y salida definidos
- [ ] Parqueaderos accesibles desde las vías
- [ ] Se pueden registrar múltiples carros
- [ ] El mapa se actualiza mostrando P (libre) y X (ocupado)
- [ ] Se busca por placa para registrar salida
- [ ] El cobro sigue funcionando correctamente
- [ ] Validación de placa sigue funcionando
- [ ] Compila sin warnings
- [ ] Commit en GitHub

---

## Requisitos del enunciado que se cumplen con esta fase

- ✅ Mapa visual mayor a 15x15 (16x16)
- ✅ Vías de acceso y salida
- ✅ Parqueaderos accesibles desde las vías
- ✅ Registro de vehículos (placa + hora)
- ✅ Sistema de cobro por minuto
- ✅ Disponibilidad en tiempo real (P vs X en el mapa)
- ✅ Funciones definidas por el usuario
- ✅ Ciclos for (para recorrer la matriz)
- ✅ Punteros (en las funciones)
- ✅ Arreglos/matrices (mapa 16x16)
- ✅ Modularidad (main mínimo, todo en funciones)

Con la Fase 2 completa, tu proyecto ya cumple TODOS los requisitos mínimos para la nota base de 3.0.
