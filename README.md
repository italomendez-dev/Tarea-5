Tarea 5 — Patrones de Diseño en C++
Curso: Programación III
Periodo: 2026-2
Docente: José A. Chávez Álvarez
Descripción
Este repositorio reúne los cuatro ejercicios de la Tarea 5 de Programación III, enfocados en la aplicación de patrones de diseño mediante C++. Cada ejercicio se encuentra en un archivo independiente.
Contenido del repositorio
Archivo	Patrón de diseño	Tema
ejercicio1.cpp	Singleton	Administrador concurrente de transacciones bancarias
ejercicio2.cpp	Abstract Factory	Motor de renderizado multiplataforma (OpenGL y Vulkan)
ejercicio3.cpp	Composite	Expresiones matemáticas simbólicas y derivación
ejercicio4.cpp	Iterator	Recorrido de grafos dirigidos mediante BFS y DFS


Ejercicios
Ejercicio 1: Singleton — Transaction Manager concurrente
Plantea un administrador único de transacciones bancarias (TransactionManager) para coordinar depósitos y retiros sobre cuentas. El ejercicio contempla ejecución concurrente, operaciones atómicas y prevención de condiciones de carrera.
Ejercicio 2: Abstract Factory — Motor multiplataforma
Plantea una interfaz RenderFactory con fábricas para OpenGL y Vulkan. El objetivo es crear productos relacionados (Window, Button y Shader) y permitir el cambio de plataforma sin modificar el código cliente.
Ejercicio 3: Composite — Expresiones matemáticas
Plantea una jerarquía de expresiones que permite representar operaciones anidadas, evaluarlas, obtener su derivada y mostrarlas como texto. La expresión propuesta es:

f(x) = (x² + 3x) · sin(x)
Ejercicio 4: Iterator — Recorrido de grafo
Plantea un grafo dirigido con iteradores para recorrer sus nodos utilizando BFS (búsqueda en anchura) y DFS (búsqueda en profundidad), sin exponer su estructura interna y evitando recorridos infinitos por ciclos.
Estructura
Tarea-5/
├── README.md
├── ejercicio1.cpp
├── ejercicio2.cpp
├── ejercicio3.cpp
└── ejercicio4.cpp
Compilación y ejecución
Con un compilador compatible con C++17, se puede compilar cada ejercicio por separado. Por ejemplo, desde la terminal:
g++ -std=c++17 -pthread ejercicio1.cpp -o ejercicio1
./ejercicio1
Para los otros ejercicios, reemplazar ejercicio1 por ejercicio2, ejercicio3 o ejercicio4, según corresponda. En Windows, el ejecutable puede tener la extensión .exe.
