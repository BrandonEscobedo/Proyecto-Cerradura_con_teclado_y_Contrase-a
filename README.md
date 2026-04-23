
## Información del proyecto: Cerradura con Teclado y Contraseña 
Autores: 
*	Brandon Yahir Escobedo Rodriguez 1998697  
*	Mauricio Campos Tamez 2002942 
*	Andrea Danaee Arrieta Martínez 2005151  

Materia: Laboratorio de controladores y microcontroladores programables. 

Docente: Ing. Héctor Hugo Flores Moreno 

Fecha:	23-04-2026

## Descripción general del proyecto
Este proyecto consiste en una cerradura electrónica controlada mediante un teclado matricial 4x4 conectado a un Arduino UNO R3. Permite al usuario ingresar una contraseña (PIN) para activar un servomotor que simula la apertura de una puerta.
El sistema incorpora una pantalla LCD con interfaz I2C, la cual muestra mensajes en tiempo real como instrucciones, estado del sistema, intentos fallidos y acceso concedido o denegado, mejorando la interacción con el usuario.
Además, el sistema permite actualizar la contraseña directamente desde el teclado, almacenándola en memoria EEPROM del Arduino, lo que garantiza que la contraseña se mantenga incluso después de reiniciar el dispositivo.

## Problema que resuelve
Este sistema simula un mecanismo de seguridad de acceso restringido, permitiendo controlar la apertura de una “puerta” mediante autenticación por contraseña, evitando accesos no autorizados.
En un contexto real, resuelve la necesidad de proteger espacios físicos o dispositivos donde no se desea acceso libre, como habitaciones, laboratorios, lockers o cajas de seguridad. A diferencia de cerraduras tradicionales, este tipo de solución permite un mayor control sobre quién puede ingresar, reduciendo riesgos asociados a llaves físicas como pérdida, duplicación o uso indebido.
Además, introduce un mecanismo de seguridad adicional al limitar los intentos de acceso y activar una alarma ante múltiples fallos, lo cual ayuda a disuadir intentos de intrusión. Este tipo de sistemas es una base para soluciones más avanzadas utilizadas en control de acceso moderno, como sistemas electrónicos en oficinas, edificios o instalaciones industriales.
A diferencia de versiones básicas con contraseña fija, este sistema permite la modificación segura del PIN por parte del usuario, aumentando la flexibilidad y seguridad del sistema sin necesidad de reprogramar el microcontrolador.
## Propósito
El objetivo principal es diseñar e implementar un sistema funcional de control de acceso que permita aplicar conceptos de microcontroladores, manejo de entradas/salidas digitales y control de actuadores.
## Contexto
Este sistema puede ser aplicado en:
*	Puertas electrónicas
*	Cajas de seguridad
*	Sistemas de acceso en oficinas o laboratorios
*	Proyectos educativos de electrónica y programación.


Además, el proyecto se desarrolla en el contexto de microcontroladores programables de bajo costo, utilizando componentes accesibles y ampliamente disponibles como el Arduino UNO, un teclado matricial 4x4, un servomotor, LEDs ,un buzzer y una pantalla LCD I2C. Esto permite replicar soluciones reales de control de acceso sin requerir hardware especializado o costoso.

## Alcance
### Incluye
*	Validación de una contraseña fija
*	Control de apertura/cierre mediante servomotor
*	Indicadores visuales (LEDs)
*	Alarma sonora tras intentos fallidos
*	Almacenamiento persistente de contraseña en EEPROM 
*	Modo de configuración para cambio de contraseña 
*	Validación de contraseña actual antes de permitir cambios 
*	Confirmación de nueva contraseña

### No incluye
*	Conectividad remota
*	Base de datos de usuarios
*	Interfaz gráfica avanzada

## Cómo funciona internamente?
### Descripción general
El sistema funciona mediante la interacción entre dispositivos de entrada (teclado), un módulo de procesamiento (Arduino) y dispositivos de salida (servo, LEDs y buzzer). El usuario introduce una contraseña que es evaluada por el microcontrolador, el cual decide si permite o no el acceso.
El sistema utiliza la memoria EEPROM del Arduino para almacenar la contraseña, permitiendo conservarla incluso si el dispositivo se apaga.
### Arquitectura del sistema
#### Entrada
* Teclado matricial 4x4

#### Procesamiento
*	Arduino UNO

#### Salida
*	Servomotor
*	LED verde
*	LED rojo
*	Buzzer
*	Pantalla LCD I2C
### Flujo del sistema
1.	El sistema inicia con la puerta cerrada 
2.	La pantalla LCD muestra mensaje de espera 
3.	El usuario ingresa la contraseña 
4.	Presiona ‘#’ para validar 
5.	Si es correcta → abre servo + LED verde + LCD muestra “Acceso correcto” 
6.	Si es incorrecta → LED rojo + buzzer + LCD muestra “Incorrecto” 
7.	Después de 3 intentos fallidos → alarma + LCD muestra “Alerta” 
8.	El usuario puede presionar ‘A’ para entrar en modo configuración 
9.	Se solicita la contraseña actual 
10.	Si es correcta → permite ingresar nueva contraseña 
11.	Se solicita confirmación 
12.	Si coinciden → se guarda en EEPROM 
13.	Si no coinciden → se muestra error
 
## Estructura del proyecto
```
Proyecto-Cerradura_con_teclado_y_Contrase-a
│
├── lab_micro.ino
├── LICENSE
├── .gitignore
├── README.md
├── /diagramas
│   ├── diagrama_bloques.png
│   ├── diagrama_flujo.png
│   └── diagrama_esquematico.png
```

## Tecnologías utilizadas

### Requisitos del Hardware

*	Arduino UNO
*	Teclado matricial 4x4
*	Servomotor
*	LEDs (rojo y verde)
*	Buzzer
*	Resistencias 220Ω
*	Pantalla LCD I2C

### Requisitos del Software 
*	Arduino IDE
*	Lenguaje C/C++
*	Librerías:
*	Keypad.h
*	Servo.h
*	LiquidCrystal_I2C.h

## Conexiones del sistema
| Componente       | Pin Arduino |
| ---------------- | ----------- |
| Filas teclado    | 2, 3, 4, 5  |
| Columnas teclado | 6, 7, 8, 9  |
| Servo            | 10          |
| Buzzer           | 11          |
| LED verde        | 12          |
| LED rojo         | 13          |
| Pantalla LCD I2C | SDA → A4, SCL → A5 |
## Comunicación entre módulos
*	El teclado envía datos al Arduino mediante pines digitales
*	El Arduino procesa la contraseña
*	El servo recibe señal PWM
*	LEDs y buzzer reciben señales digitales
*	Todo ocurre dentro del ciclo ‘loop()‘

La pantalla LCD se comunica con el Arduino mediante el protocolo I2C, utilizando solo dos pines (SDA y SCL), lo que permite optimizar el uso de pines del microcontrolador y simplificar el cableado.

El Arduino también interactúa con la memoria EEPROM para almacenar y recuperar la contraseña, permitiendo persistencia de datos sin necesidad de almacenamiento externo.
## Decisiones técnicas
*	Uso de contraseña configurable almacenada en EEPROM para mayor flexibilidad y persistencia 
*	Contador de intentos para seguridad
*	Uso de PWM para control del servo
*	Teclado matricial para optimizar pines
*	Retroalimentación visual y sonora
*	Uso de pantalla LCD I2C para mostrar información al usuario sin consumir muchos pines
*	Implementación de validación doble (nueva contraseña y confirmación) para evitar errores del usuario 
*	Uso de modo de configuración activado por teclado (tecla 'A') 
 
## Modo de configuración de contraseña
El sistema incluye un modo de configuración que permite cambiar la contraseña sin necesidad de reprogramar el Arduino.
### Activación:
*	Se presiona la tecla 'A' desde el teclado 
### Flujo de cambio:
1.	El sistema solicita la contraseña actual 
2.	Si es correcta, solicita una nueva contraseña 
3.	Se pide confirmación de la nueva contraseña 
4.	Si ambas coinciden y tienen la longitud correcta: 
o	Se guarda en EEPROM 
o	Se muestra mensaje de éxito 
5.	Si hay error: 
o	Se muestra mensaje de error 
o	No se realiza el cambio 
### Validaciones implementadas:
*	Verificación de contraseña actual 
*	Confirmación de nueva contraseña 
*	Longitud fija (4 dígitos) 
Esto garantiza que solo usuarios autorizados puedan modificar el acceso.

## Instalación y ejecución
### Instalación
1.	Clonar el repositorio:

““bash
git clone https://github.com/BrandonEscobedo/Proyecto-Cerradura_con_teclado_y_Contrasena
““

2.	Abrir el archivo:

““
lab_micro.ino
““

3.	Instalar librerías en Arduino IDE:

*	Keypad
*	Servo

### Ejecución
1.	Conectar el circuito según la tabla de conexiones
2.	Seleccionar:

*	Placa: Arduino UNO
*	Puerto correcto según donde se conecto 
3.	Subir el código
4.	Probar el sistema

## Uso
*	Ingresar contraseña (ejemplo: ‘1234‘)
*	Presionar ‘#‘ para validar
*	Presionar ‘*‘ para borrar
*	Presionar ‘A’ para entrar en modo configuración de contraseña
### Cambio de contraseña
1.	Presionar ‘A’ 
2.	Ingresar contraseña actual 
3.	Ingresar nueva contraseña (4 dígitos) 
4.	Confirmar nueva contraseña 
5.	Si es correcta → se guarda en memoria EEPROM 
6.	Si hay error → se muestra mensaje y no se realiza el cambio

## Pruebas
Se realizaron pruebas para validar el comportamiento del sistema:
* Acceso correcto → apertura de servo + LED verde + mensaje en LCD
* Acceso incorrecto → LED rojo + buzzer + mensaje en LCD
* 3 intentos fallidos → activación de alarma sonora y visual
* Visualización de mensajes en pantalla LCD en cada estado
* Funcionamiento del borrado de entrada con ‘*’
* Validación del modo configuración (tecla ‘A’)
* Cambio de contraseña exitoso con almacenamiento en EEPROM
* Validación de errores al confirmar contraseña incorrecta
* Persistencia de la contraseña después de reiniciar el sistema

## Contribución
1.	Clonar el repositorio
2.	Crear una rama
3.	Realizar mejoras
4.	Documentar cambios
5.	Enviar pull request

## Simulación (Tinkercad)
Se incluye una simulación del proyecto en Tinkercad para facilitar la comprensión y permitir probar el sistema sin necesidad de hardware físico.
Link de la simulación:
““
https://www.tinkercad.com/things/7DyngwwBPCO-micropia?sharecode=4p2gxqOqlpozgwG4k3_QkpuPfoD9Gry3laLse22mmSg
““

**Uso de la simulación:**
*	Abrir el enlace en el navegador
*	Iniciar la simulación
*	Probar el ingreso de la contraseña (‘1234‘) desde el teclado
*	Verificar el comportamiento del servo, LEDs, buzzer y pantalla LCD I2C
*	Nota: Este recurso es opcional y sirve como apoyo visual para replicar el circuito y validar el funcionamiento antes de implementarlo físicamente.

## Diagramas

El proyecto incluye:

* Diagrama de bloques

![Diagrama de bloques](diagramas/diagrama_bloques.png)

* Diagrama pictorico

![Diagrama de bloques](diagramas/diagrama_PICTÓRICO.png)

* Diagrama esquemático

![Diagrama de bloques](diagramas/diagrama_ESQUEMÁTICO.png)
## Resumen técnico
Sistema embebido basado en Arduino que integra:
*	Entrada digital (teclado) 
*	Procesamiento lógico 
*	Persistencia de datos mediante EEPROM 
*	Salidas físicas (servo, LEDs, buzzer) 
*	Interfaz de usuario mediante pantalla LCD I2C 
•	Configuración dinámica de contraseña

## FAQ

**¿La contraseña se pierde al apagar el Arduino?**
No, se almacena en la EEPROM, por lo que permanece guardada.
**¿Cómo cambio la contraseña?**
Presionando la tecla 'A' e ingresando la contraseña actual.
**¿Por qué no funciona el teclado?**
Revisar conexiones de filas y columnas.
**¿Por qué el servo no gira?**
Verificar alimentación y pin.
**¿Por qué no funciona la pantalla LCD?**
Verificar la dirección I2C (0x27 o 0x20), conexiones SDA/SCL y la librería utilizada.

