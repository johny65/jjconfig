jjConfig
========

_Librería simple para guardar opciones de configuración en un archivo._

---

**jjConfig** es una pequeña librería bien sencilla que permite guardar opciones de configuración en un archivo de texto plano, escrita totalmente en C++ estándar, y por lo tanto multiplataforma.

Su uso es muy sencillo: instanciar un objeto de tipo `jjConfig` pasándole una ruta de archivo con el que trabajará, y luego usar sus métodos para guardar o leer opciones.

**jjConfig** permite trabajar con varios tipos de datos (cadenas, enteros y flotantes) y posee los métodos adecuados para guardar y leer opciones en estos tipos.

Un ejemplo de su uso:

    :::cpp
    //creamos el objeto:
    jjConfig opciones("archivo.conf");
    //leemos una opción:
    int anchoventana = opciones.ValorInt("ancho", valor_por_defecto);
    //leemos otra opción:
    string archivo = opciones.Valor("archivo", archivo_por_defecto);
    //guardamos algunas opciones:
    opciones.SetValor("nombre", "Documento sin título");
    opciones.SetValor("tamaño", 1024);
    //persistir los datos:
    opciones.Guardar();

El archivo de configuración usado es de texto plano, donde las opciones son guardadas en la forma `clave=valor`. No soporta grupos como los archivos INI (un grupo o sección se indica mediante `[corchetes]`).

Al crear el objeto, lee el archivo parseándolo y dejando en memoria su contenido en forma de mapa (`map<string, string>` de la STL) para luego poder acceder a las distintas claves y sus valores.


Instrucciones:
-------------

Para usar **jjConfig** en tu aplicación puedes compilar la librería y enlazarla estáticamente a tu programa. Para eso puedes usar el archivo `Makefile` incluido:

    $ make

Esto creará el archivo `libjjconfig.a` en una carpeta llamada `lib`. En la misma carpeta se encontrará el archivo `jjconfig.h` que es el que debes incluir en tu código:

    :::cpp
    #include <jjconfig.h>

Suponiendo que la ruta completa de la carpeta `lib` creada en el paso anterior es `${JJCONFIG_LIB}`, debes compilar tu programa con:

    $ g++ src_de_tu_programa -I${JJCONFIG_LIB} -L${JJCONFIG_LIB} -ljjconfig

Como la librería es pequeña y sólo contiene 2 archivos fuentes (`jjConfig.h` y `jjConfig.cpp`) directamente puedes copiar estos archivos en el directorio de código fuente de tu aplicación y considerarlos parte de la misma.

Documentación completa sobre la API de la librería se puede generar a través de [Doxygen](http://www.doxygen.org/index.html). Para ello sólo ejecuta el comando:

    $ make doc


Qué hay de nuevo:
----------------

**v0.5:**

* Agregados métodos para trabajar con tipo de dato booleano (`bool`).

**v0.4:**

* Primera versión pública liberada.


Licencia:
--------

Este software es software libre, licenciado bajo la GNU General Public License (GPL). El texto completo de la misma viene incluido con el código fuente.
