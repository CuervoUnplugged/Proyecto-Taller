# Proyecto: Damas Chinas 

## Integrantes
- **Juan Manuel Cuervo**  
- **Samuel Marín Vanegas**

---

## Innovación en la Jugabilidad

Nuestro proyecto de **Damas Chinas** busca mejorar la experiencia del jugador mediante una **jugabilidad más intuitiva e interactiva**, reemplazando el tradicional ingreso de coordenadas con letras y números por un sistema de **movimiento mediante teclas y la tecla Enter**.

Además, se añadió una función visual que **indica cuándo una ficha está disponible para ser comida**, mostrando símbolos como (**y**) o (**a**) sobre el tablero.  
Esto permite al jugador **identificar rápidamente las jugadas posibles** y planificar su estrategia sin confusiones.

---

### ¿Para qué se implementó?

Esta innovación se implementó con el objetivo de **hacer el juego más accesible y dinámico**, eliminando la necesidad de escribir coordenadas manualmente.  
De esta forma, los jugadores pueden moverse directamente sobre el tablero usando el teclado, lo que genera una experiencia **más fluida, rápida y similar a un videojuego real**.  
También se implementaron los indicadores (*y*, *a*) para **facilitar la visualización de movimientos y capturas posibles**.

---

### ¿Por qué se consideró necesario?

Se consideró necesario porque el método tradicional de ingresar movimientos (como “A3 B4”) resultaba **poco práctico y propenso a errores**.  
Además, queríamos ofrecer una interfaz más **ergonómica y atractiva**, aprovechando las ventajas de interacción directa por teclado para mejorar la **usabilidad y el ritmo del juego**.  
Los indicadores visuales se consideraron esenciales para **guiar al jugador** y mejorar la **comprensión del tablero**.

---

### ¿Cómo se llevó a cabo su implementación?

La implementación se realizó **detectando las teclas presionadas por el jugador** para desplazarse por el tablero, permitiendo seleccionar piezas y confirmar movimientos con la tecla **Enter**.  
Se programó una lógica de control que interpreta estas entradas y actualiza el tablero en tiempo real.  
Asimismo, se añadió un sistema que **revisa las posiciones alrededor de cada ficha** y, en caso de que haya una posible captura, **muestra los símbolos *y* o *a*** para señalarlo visualmente.  
Esto mantiene la esencia del juego de damas, pero con una **interacción moderna, visual y mejorada**.
