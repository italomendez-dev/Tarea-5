Tarea 5 - Patrones de Diseño
Curso: Programación III
Ciclo: 2026-2

Este repositorio contiene la solución de los cuatro ejercicios de la Tarea 5, centrados en la aplicación de patrones de diseño en C++.
Contenido
Ejercicio 1: Singleton - Transaction Manager Concurrente
Archivo: ejercicio1.cpp

Sistema de gestión de transacciones bancarias en el que una única instancia de TransactionManager coordina depósitos y retiros. El ejercicio trabaja con múltiples hilos y busca garantizar operaciones atómicas, evitando condiciones de carrera.
Ejercicio 2: Abstract Factory - Motor Multiplataforma
Archivo: ejercicio2.cpp

Sistema de renderizado que utiliza el patrón Abstract Factory para crear ventanas, botones y shaders compatibles con OpenGL o Vulkan. Permite cambiar de fábrica durante la ejecución sin modificar la lógica del cliente.
Ejercicio 3: Composite - Expresiones Matemáticas
Archivo: ejercicio3.cpp

Representación de expresiones matemáticas mediante una estructura de objetos compuestos. El ejercicio contempla la evaluación, la derivación simbólica y la representación en texto de expresiones, incluyendo:

f(x) = (x² + 3x) * sin(x)
Ejercicio 4: Iterator - Recorrido de Grafo
Archivo: ejercicio4.cpp

Implementación de un grafo dirigido con iteradores personalizados para recorrer sus nodos mediante BFS (búsqueda en anchura) y DFS (búsqueda en profundidad), sin exponer su estructura interna.
Estructura del repositorio
Tarea-5/
├── README.md
├── ejercicio1.cpp
├── ejercicio2.cpp
├── ejercicio3.cpp
└── ejercicio4.cpp
Compilación y ejecución
Los ejercicios están separados en archivos .cpp. Para compilar y ejecutar uno de ellos con un compilador compatible con C++17, por ejemplo el primero:
g++ -std=c++17 -pthread ejercicio1.cpp -o ejercicio1
./ejercicio1
Para los demás ejercicios, reemplazar ejercicio1 por ejercicio2, ejercicio3 o ejercicio4 según corresponda.ejercicio3 o ejercicio4, según corresponda. En Windows, el ejecutable puede tener la extensión .exe.
