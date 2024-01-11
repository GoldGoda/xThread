# xThread - Microlibrería C++ para ThreadPool

`xThread` es una microlibrería C++ diseñada para proporcionar una implementación sencilla y eficiente de un ThreadPool. Facilita la ejecución concurrente de tareas en hilos múltiples, mejorando el rendimiento de aplicaciones que requieren procesamiento paralelo.

## Características Principales:

- **Fácil Integración:** Integrar `xThread` en tus proyectos C++ es sencillo y rápido, permitiéndote aprovechar la potencia del ThreadPool de manera eficiente.

- **Configuración Personalizada:** Adapta el número de hilos en el ThreadPool según tus necesidades específicas, proporcionando flexibilidad para optimizar el rendimiento.

- **Gestión Segura de Tareas:** La microlibrería utiliza mecanismos de sincronización, como `std::mutex` y `std::condition_variable`, para garantizar una ejecución segura de las tareas y la finalización ordenada del ThreadPool.

## Ejemplo de Uso:

```cpp
#include "xThread/ThreadPool.hpp"

int main() {
    xThread::ThreadPool pool(4);  // Crear un ThreadPool con 4 hilos
    
    // Agregar tareas al ThreadPool
    pool.addTask([] { /* Tu tarea aquí */ });
    pool.addTask([] { /* Otra tarea */ });

    // Ejecutar el ThreadPool
    pool.run();

    return 0;
}
