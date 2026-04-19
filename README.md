# PARKING_SYSTEM

## Integrante
- Alessandro De Bonis

---

## Desarrollo del proyecto por fases

### Fase 1 — Spot único (MVP)

En esta fase se construyó un mvp con un solo espacio de parqueadero para validar toda la lógica de negocio antes de escalar a mas espacios y mas vehiculos. Se creó la estructura modular del proyecto con los archivos pedidos por el profesor.

**Archivos creados:**

- `main.cpp`: Solo corre el programa. llama a la función `startProgram()`.

- `menu.h / menu.cpp`: En `menu.h` se declara la función `startProgram` que inicia todo el programa. En `menu.cpp` se implementa el menú interactivo donde el usuario elige opciones por terminal. Usa un `do-while` con un `switch` para cada opción.

- `spot.h / spot.cpp`: En `spot.h` se define la estructura `Spot` con los campos(caracteristicas del struc) para representar un espacio de parqueadero (placa, hora de entrada, ocupado/libre) y los prototipos de funciones. 
En `spot.cpp` se implementan las funciones para inicializar el spot, registrar entrada, registrar salida y mostrar estado.

- `cobro.h / cobro.cpp`: En `cobro.h` se define la constante de tarifa por minuto y los prototipos de cálculo. En `cobro.cpp` se implementan dos funciones: `calculateMinutes` que calcula la diferencia en minutos entre entrada y salida usando `std::difftime`, y `calculateFee` que multiplica los minutos por la tarifa. Se cobra mínimo 1 minuto aunque sea fracción.

---

### Fase 2 — Matriz 16x16 y mapa visual

En esta fase el proyecto paso de un spot único a una matriz de 16x16 con mapa visual en consola, permitiendo administrar múltiples vehículos simultáneamente.

**Archivos nuevos:**

- `map.h / map.cpp`: En `map.h` se definen las variables constantes del mapa (dimensiones, caracteres para muros, vías, entrada, salida, espacio libre y ocupado). En `map.cpp` se implementan tres funciones: `initMap` que llena la matriz con el diseño del parqueadero usando un array `design` de 16x16 y un doble `for` para copiarlo. En `showMap` se recorre la matriz y se imprime cada celda, y en `updateMap` se recorre el vector de spots y seactualiza las celdas del mapa según estén libres u ocupados.

**Cambios principales de fase 1 a fase 2:**

- El struct `Spot` recibió dos campos nuevos: `row` y `col` para saber la posición de cada espacio en el mapa.
- Se agregó `#include <vector>` para manejar múltiples spots dinámicamente.
- Se crearon funciones nuevas: `initSpots` (recorre el mapa y crea un Spot por cada 'P' encontrada), `findFreeSpot` (busca el primer espacio libre, devuelve -1 si no hay), `findSpotByPlate` (busca un vehículo por placa).
- Las funciones `registerEntry`, `registerExit` y `showStatus` se modificaron para trabajar con el vector en vez de un solo spot.

---

### Fase 3 — Diseño visual e innovaciones

En esta fase se mejoró la interfaz visual y se agregaron funcionalidades adicionales.

**Diseño visual:**

Se usan códigos ANSI  para colorear cada tipo de celda en el mapa: verde para espacios libres (P), rojo para carros (C), magenta para motos (M), amarillo para vías, cian para entrada/salida, y blanco para muros. Se agregaron bordes decorativos con caracteres Unicode (╔, ║, ╚, ═) y una leyenda de colores debajo del mapa.(recomendado y en colaboracion con claude)

Para la limpieza de pantalla se usa `std::cout << "\033[2J\033[H" << std::flush` y se agregó una pausa con `std::cin.ignore()` para que el usuario pueda ver los resultados antes de que se redibuje el mapa.(Recomendado por claude)

**Innovaciones implementadas:**

1. **Tipo de vehículo (Carro vs Moto):** Se agregó un campo `char type` al struct Spot. Al registrar un vehículo el usuario elige si es carro ('C') o moto ('M'). En el mapa se muestra C en rojo para carros y M en magenta para motos.(para ponerle colores en el mapa me ayude con claude)

2. **Tarifas diferenciadas:** Los carros pagan $190/min y las motos $100/min. La función `calculateFee` recibe el tipo de vehículo y aplica la tarifa correspondiente. Tarifas basadas en parqueaderos reales de Bogotá.

3. **Validación de placas colombianas:** Se implementaron dos funciones de validación: `validateCarPlate` verifica el formato ABC123 (3 letras + 3 números) para carros, y `validateMotoPlate` verifica el formato ABC12D (3 letras + 2 números + 1 letra) para motos. Se usa `std::isalpha` y `std::isdigit` de la librería `<cctype>`.

4. **Conversión automática a mayúsculas:** Se usa `std::toupper` para convertir tanto el tipo de vehículo como la placa a mayúsculas antes de validar y buscar. Así el usuario puede escribir en minúsculas o mayúsculas sin que el sistema falle.(recomendado por claude para facilidad del usuario)

5. **Visualización de vehículos registrados:** Esta función nació porque para registrar la salida de un vehículo se le puede olvidar al usuario cuál es la placa. Con la opción "Ver vehículos registrados" se puede ver la placa, tipo, tarifa y posición de cada vehículo y después registrar la salida.

6. **Interfaz visual con colores ANSI y bordes Unicode:** El mapa se muestra con colores diferenciados para cada tipo de celda y bordes decorativos, mejorando la experiencia de usuario.(recomendado por claude)

7. **Modularidad avanzada:** El proyecto se divide en 9 archivos con responsabilidades separadas. Cada módulo (.h para declaraciones, .cpp para implementación) se encarga de una sola cosa: cobro, spots, mapa y menú.

---

## Cómo compilar y ejecutar

```bash
g++ main.cpp menu.cpp spot.cpp cobro.cpp map.cpp -o parking
./parking
```

---

## Leyenda del mapa

- P (verde) = Espacio libre
- C (rojo) = Carro estacionado
- M (magenta) = Moto estacionada
- E (cian) = Entrada
- S (cian) = Salida
- . (amarillo) = Vía de acceso
- # (blanco) = Muro

## Tarifas

- Carro: $190 COP por minuto
- Moto: $100 COP por minuto
- Fracción de minuto se cobra como minuto completo (mínimo 1 minuto)

---

*README creado por Alessandro y mejorado en redaccion por parte de claude.*