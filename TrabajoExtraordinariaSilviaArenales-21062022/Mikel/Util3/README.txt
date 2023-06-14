Utilidad (3): Escribe una utilidad en C de nombre lanzador_temporizado, que
recibe un número de segundos y entre 1 y 5 comandos/programas sin argumentos (por
ejemplo, date, ls, ps, who). Estos comandos/programas se lanzarán de manera
concurrente. Cuando un comando/programa termine, la utilidad imprimirá una línea en
la salida estándar indicándolo. Transcurrido el número de segundos pasado como primer
argumento, la utilidad forzará la terminación de aquellos comandos/programas que no
hubieran terminado aún, indicándolo igualmente en la salida estándar. Ejemplo de uso:
lanzador_temporizado  10  date  ls  ps  sleep20  who
donde sleep20 es un programa que realiza una espera de 20 segundos antes de
terminar (debes programarlo tú). En cuanto todos los comandos/programas hayan
terminado, la utilidad escribirá en la salida estándar la duración total en segundos del
experimento y finalizará su ejecución.
Nota. No se permite usar la función system().
