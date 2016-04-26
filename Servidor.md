# **Introdución** #
El servidor es la aplicación que se encarga de manejar las consultas de los clientes y ejecutar las actualizaciones de los agentes. Maneja archivos de configuración y de datos.

# **Detalles** #
## **Uso** ##

La llamada al programa es la siguiente:

```
./servidor
```

Con dicha ejecución, el servidor quedará trabajando hasta que se dé la condición de salida. En nuestro caso, _Q_.

## **Descripción** ##

El servidor se maneja con un _motor de base de datos_ que es el encargado de manejar las consultas. Para poder realizar una consulta al motor, la misma tiene que estar bien formada. Por ende, también posee un _verificador de consulta_ que se encarga de verificar si el motor la podrá procesar.

La aplicación servidora deberá soportar tanto las actualizaciones de los clientes como las consultas de los clientes en forma simultánea. Para esto, se tendrán que procesar en multihilo. Por un lado, habrá un hilo escuchando conexiones. Por cada conexión que se acepte, se abrirá un hilo que procese la consulta.

Este aspecto nos permite definir algunas características adicionales. Por ejemplo, para que la estructura sea consistente, el motor debe ser thread-safe. Es decir, la escritura debe ser bloqueante.