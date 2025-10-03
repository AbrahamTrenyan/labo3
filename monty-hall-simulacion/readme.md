# Simulación del Problema de Monty Hall

Este programa lo hice por diversión mientras trataba de agarrarle la mano al lenguaje C para la materia Laboratorio 3. Quería probar empíricamente si realmente se cumple el famoso problema de Monty Hall. Spoiler: sí, se cumple.

## ¿Qué es el Problema de Monty Hall?

Es un problema de probabilidad basado en un programa de televisión estadounidense. La idea es así:

1. Tenés 3 puertas cerradas
2. Detrás de una hay un auto (el premio), detrás de las otras dos hay cabras
3. Elegís una puerta
4. El presentador, que sabe dónde está el auto, abre una de las otras dos puertas mostrando una cabra
5. Te pregunta: ¿te quedás con tu elección o cambiás a la otra puerta cerrada?

Lo contra intuitivo es que **cambiar de puerta te da 66.6% de probabilidad de ganar**, mientras que quedarte con tu elección inicial solo te da 33.3%.

## ¿Por qué funciona así?

Para entenderlo mejor, pensalo con más puertas:

**Con 10 puertas:** Elegís una (10% de chance). El presentador abre 8 puertas sin premio. ¿Realmente pensás que tu elección inicial tenía 50% de probabilidad? No, seguís teniendo 10%. La otra puerta cerrada tiene 90%.

**Con 99 puertas:** Elegís una (1% de chance). El presentador abre 97 puertas vacías. ¿Tu elección inicial ahora mágicamente vale 50%? No. Sigue siendo 1%. La otra puerta tiene 99%.

**Con 1000 puertas:** Elegís una entre 1000 (0.1% de chance). El presentador abre 998 puertas. Quedás vos y otra. ¿De verdad vas a creer que tu pálpito inicial de 0.1% ahora vale 50%? Cambiar te da 99.9% de probabilidad.

Cuando lo ves así, se hace obvio: tu primera elección siempre fue mala (probabilísticamente), y el presentador básicamente te está mostrando dónde está el premio al eliminar todas las otras opciones malas.

## La matemática detrás 

Este problema es un caso clásico de **probabilidad condicional** y aplicación del **Teorema de Bayes**. La clave está en entender que la acción del presentador NO es un evento independiente, sino que está condicionada por información que él tiene y vos no.

Cuando elegís la puerta inicial, tenés P(ganar) = 1/3. Lo que la gente no capta es que esta probabilidad no cambia cuando el presentador abre una puerta. Tu elección inicial sigue teniendo 1/3 de probabilidad de ser correcta, pero ahora toda la probabilidad restante (2/3) se concentra en la otra puerta cerrada.

El truco mental que te confunde es pensar que se trata de **eventos independientes** (como dos tiradas de moneda), cuando en realidad son **eventos dependientes**. El presentador tiene **información perfecta** del sistema y su acción está correlacionada con la ubicación del premio. Él nunca abre la puerta con el auto, y esa restricción es información valiosa que cambia la distribución de probabilidad posterior.

En términos bayesianos: la **probabilidad a priori** de tu elección es 1/3, y la acción del presentador te da nueva evidencia. Pero como él está obligado a mostrarte una cabra (no puede mostrarte el auto), esa evidencia no actualiza la probabilidad de tu puerta, pero sí actualiza dramáticamente la de la otra puerta cerrada a 2/3.

Es básicamente un problema de **actualización bayesiana de creencias** con información asimétrica. Por eso es tan contra intuitivo: estamos mal cableados para procesar probabilidades condicionales.

### Teoría de Juegos: ¿Y si el presentador sabe que yo sé?

Acá se pone interesante. El problema clásico asume que el presentador **siempre** te ofrece cambiar. Pero ¿qué pasa si es estratégico?

Si el presentador sabe que vos sabés que hay que cambiar, y él quiere que pierdas, podría solo ofrecerte cambiar cuando tu elección inicial era correcta. En ese caso, la estrategia óptima sería nunca cambiar... pero entonces el presentador cambia su estrategia, y entramos en un bucle de **conocimiento común** ("yo sé que él sabe que yo sé...") donde ambos terminan en un **equilibrio de Nash mixto**: aleatorizando sus decisiones para no ser predecibles.

El Monty Hall clásico funciona porque las reglas están fijas de antemano: el presentador no puede jugar estratégicamente basándose en tu conocimiento; tiene que elegir una puerta con una cabra siempre.
Sin esa regla fija, todo el análisis se cae a pedazos y se vuelve un juego mucho más complejo donde "siempre cambiar" ya no es óptimo.

## ¿Cómo funciona este programa?

El programa hace una simulación de 10 millones de juegos para probar esto empíricamente:

- En cada juego coloca el premio al azar en una puerta
- El jugador elige una puerta al azar
- El presentador abre una puerta sin premio que el jugador no eligió
- Calcula cuántas veces ganás si cambias vs si te quedás

## Resultados

Cuanto mayor es el número de simulaciones, más se acercan los resultados al valor teórico del 66.6% al cambiar. Con 10 millones de simulaciones, ya se ve clarísimo.

## Lo increíble de esto

Este problema es un ejemplo perfecto de cómo nuestra intuición puede fallarnos completamente. La primera vez que lo escuchás, jurás que da lo mismo cambiar o quedarte (50/50), pero la matemática dice otra cosa totalmente distinta.

En 1990, Marilyn vos Savant (que estaba en el Guinness por tener uno de los IQ más altos registrados) publicó este problema en su columna "Ask Marilyn" de la revista Parade. Recibió más de 10,000 cartas, muchas de matemáticos y profesores con PhDs, diciéndole que estaba totalmente equivocada. Algunas respuestas fueron bastante agresivas. Al final, ella tenía razón y todos esos expertos tuvieron que admitirlo después de hacer simulaciones como esta.

Es fascinante cómo algo tan simple puede ser tan contra intuitivo y cómo los números nunca mienten: corré este programa las veces que quieras y siempre vas a ver el mismo resultado.

La matemática tiene esa magia de mostrarte que el universo funciona de maneras que tu cerebro no espera.

## Compilar y ejecutar

```bash
gcc monty.c -o monty
./monty
```

