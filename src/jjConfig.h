/*
    jjConfig 0.6:
    Librería simple para guardar opciones de configuración en un archivo.
    
    Copyright (C) 2013  Juan Bertinetti <juanbertinetti@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * \file jjConfig.h
 *
 * \brief Librería simple para guardar opciones de configuración en un archivo.
 *
 * jjConfig es una pequeña librería bien sencilla que permite guardar
 * opciones de configuración en un archivo de texto plano, escrita totalmente
 * en C++ estándar, y por lo tanto multiplataforma.
 * Su uso es muy sencillo: instanciar un objeto de tipo jjConfig pasándole una
 * ruta de archivo con el que trabajará, y luego usar sus métodos para guardar
 * o leer opciones.
 * jjConfig permite trabajar con varios tipos de datos (cadenas, enteros y
 * flotantes) y posee los métodos adecuados para guardar y leer opciones en
 * estos tipos.
 * Un ejemplo de su uso:
 * \code
 *      //creamos el objeto:
 *      jjConfig opciones("archivo.conf");
 *      //leemos una opción:
 *      int anchoventana = opciones.ValorInt("ancho", valor_por_defecto);
 *      //leemos otra opción:
 *      string archivo = opciones.Valor("archivo", archivo_por_defecto);
 *      //guardamos algunas opciones:
 *      opciones.SetValor("nombre", "Documento sin título");
 *      opciones.SetValor("tamaño", 1024);
 *      //persistir los datos:
 *      opciones.Guardar();
 * \endcode
 *
 * El archivo de configuración usado es de texto plano, donde las opciones son
 * guardadas en la forma <tt>clave=valor</tt>. No soporta grupos como los
 * archivos INI (un grupo o sección se indica mediante <tt>[corchetes]</tt>).
 * Al crear el objeto, lee el archivo parseándolo y dejando en memoria su
 * contenido en forma de mapa (<tt>map<string, string></tt> de la STL) para
 * luego poder acceder a las distintas claves y sus valores.
 * 
 */

#ifndef _JJCONFIG_H_
#define _JJCONFIG_H_

#include <map>
#include <string>


/// Clase principal.
/**
 * Para usar la librería hay que crear un objeto de tipo jjConfig y luego
 * trabajar con sus métodos públicos. Al instanciar el objeto se cargan las
 * opciones de configuración a memoria leídas de un archivo.
 */
class jjConfig {
private:
    std::map<std::string, std::string> data; ///< Mapa que guarda los datos
    std::string file; ///< Indica la ruta del archivo de configuración en disco

    ///Carga los datos del archivo de configuración.
    /**
     * Esta función carga todos los datos que se encuentren en el archivo de
     * configuración con que fue instanciada la clase y los deja disponible
     * en memoria. Si el archivo no existe, la función lo creará.
     * 
     * \return \c true si no hubo ningún error, \c false en caso contrario.
     */
    bool cargar_datos();
    
    /* funciones de utilería: */
    
    ///Quita espacios de sobra a una cadena.
    /**
     * \c trim borra los espacios y tabulaciones al inicio y final de una
     * cadena.
     * Se puede llamar directamente <tt>trim(cadena)</tt>, los cambios son
     * reflejados en la cadena sin necesidad de una nueva asignación.
     * 
     * \param Cadena Cadena por referencia, los cambios se aplican sobre ella.
     * \return Una referencia de la cadena trabajada.
     */
    std::string& trim(std::string &Cadena);


    ///Cadena a entero.
    /**
     * Convierte una cadena \c string a entero \c int. Si no se puede realizar
     * la conversión retorna un 0.
     * 
     * \param Cadena Cadena a convertir a entero.
     * \return La cadena convertida a \c int.
     */
    int str2int(const std::string &Cadena);


    ///Cadena a entero sin signo.
    /**
     * Convierte una cadena \c string a entero sin signo <tt>unsigned int</tt>.
     * Si no se puede realizar la conversión retorna un 0.
     * 
     * \param Cadena Cadena a convertir a entero sin signo.
     * \return La cadena convertida a <tt>unsigned int</tt>.
     */
    unsigned int str2uint(const std::string &Cadena);


    ///Cadena a flotante de doble precisión.
    /**
     * Convierte una cadena \c string a número flotante de doble precisión
     * \c double.
     * Si no se puede realizar la conversión retorna un 0.
     * 
     * \param Cadena Cadena a convertir a flotante de doble precisión.
     * \return La cadena convertida a \c double.
     */
    double str2dbl(const std::string &Cadena);


    ///Cadena a booleano.
    /**
     * Convierte una cadena \c string a un booleano.
     * 
     * \param Cadena Cadena a convertir a booleano.
     * \return La cadena convertida a \c bool.
     */
    bool str2bool(const std::string &Cadena);


    ///Entero a cadena.
    /**
     * Convierte un entero \c int a cadena \c string.
     * 
     * \param Entero Entero a convertir en cadena.
     * \return El número convertido a \c string.
     */
    std::string int2str(int Entero);


    ///Entero sin signo a cadena.
    /**
     * Convierte un entero sin signo <tt>unsigned int</tt> a cadena \c string.
     * 
     * \param Entero Entero sin signo a convertir en cadena.
     * \return El número convertido a \c string.
     */
    std::string uint2str(unsigned int Entero);


    ///Flotante a cadena.
    /**
     * Convierte un flotante de doble precisión \c double a cadena \c string.
     * 
     * \param Doble Flotante de doble precisión a convertir en cadena.
     * \return El número convertido a \c string.
     */
    std::string dbl2str(double Doble);

    
public:

    ///Constructor.
    /**
     * Constructor de la clase. Recibe como parámetro la ruta en disco del
     * archivo de configuración que se usará. Carga todos los datos contenidos
     * en el archivo. Puede pasarse un archivo vacío o inexistente, en tales
     * casos no cargará ningún dato pero al momento de guardar creará los datos
     * necesarios.
     * 
     * \param Archivo Ruta del archivo de configuración.
     */
    jjConfig(const std::string &Archivo);

    
    ///Guarda todos los datos a disco.
    /**
     * Esta función guarda todas las opciones de configuración que tenga en
     * memoria la clase a disco, usando el archivo de configuración con que fue
     * instanciada la clase. Si desea hacerse permanentes todas las opciones
     * configuradas con la clase, debe llamarse a esta función manualmente para
     * persistir los datos, en ningún momento se lo hace automáticamente.
     * 
     * \return \c true si no hubo ningún error, \c false en caso contrario.
     */
    bool Guardar();


    /* setters: */

    ///Configurar un valor (cadena).
    /**
     * Agrega o actualiza un nuevo valor a las opciones de configuración.
     * 
     * \param Clave Nombre de la opción.
     * \param Val Valor a guardar.
     */
    void SetValor(const std::string &Clave, const std::string &Val);

    
    ///Configurar un valor (cadena).
    /**
     * Agrega o actualiza un nuevo valor a las opciones de configuración.
     * 
     * \param Clave Nombre de la opción.
     * \param Val Valor a guardar.
     */
    void SetValor(const std::string &Clave, const char *Val);
    

    ///Configurar un valor (entero).
    /**
     * Agrega o actualiza un nuevo valor a las opciones de configuración.
     * 
     * \param Clave Nombre de la opción.
     * \param Val Valor a guardar.
     */
    void SetValor(const std::string &Clave, int Val);

    
    ///Configurar un valor (entero sin signo).
    /**
     * Agrega o actualiza un nuevo valor a las opciones de configuración.
     * 
     * \param Clave Nombre de la opción.
     * \param Val Valor a guardar.
     */
    void SetValor(const std::string &Clave, unsigned int Val);


    ///Configurar un valor (flotante).
    /**
     * Agrega o actualiza un nuevo valor a las opciones de configuración.
     * 
     * \param Clave Nombre de la opción.
     * \param Val Valor a guardar.
     */
    void SetValor(const std::string &Clave, double Val);

    
    ///Configurar un valor (booleano).
    /**
     * Agrega o actualiza un nuevo valor a las opciones de configuración. El
     * valor es guardado como "true" si es verdadero, o "false" si es falso.
     * 
     * \param Clave Nombre de la opción.
     * \param Val Valor a guardar.
     */
    void SetValor(const std::string &Clave, bool Val);

    
    /* getters: */

    ///Obtener un valor (cadena).
    /**
     * Obtiene el valor de una opción de configuración. Si la opción no se
     * encuentra, devuelve el valor por defecto pasado como parámetro.
     * 
     * \param Clave Nombre de la opción.
     * \param Default Valor por defecto en caso de que la opción todavía no exista.
     * \return El valor de la opción (de tipo \c string).
     */
    std::string Valor(const std::string &Clave, const std::string &Default);


    ///Obtener un valor (entero).
    /**
     * Obtiene el valor de una opción de configuración. Si la opción no se
     * encuentra, devuelve el valor por defecto pasado como parámetro.
     * 
     * \param Clave Nombre de la opción.
     * \param Default Valor por defecto en caso de que la opción todavía no exista.
     * \return El valor de la opción (de tipo \c int).
     */
    int ValorInt(const std::string &Clave, int Default);


    ///Obtener un valor (entero sin signo).
    /**
     * Obtiene el valor de una opción de configuración. Si la opción no se
     * encuentra, devuelve el valor por defecto pasado como parámetro.
     * 
     * \param Clave Nombre de la opción.
     * \param Default Valor por defecto en caso de que la opción todavía no exista.
     * \return El valor de la opción (de tipo <tt>unsigned int</tt>).
     */
    unsigned int ValorUInt(const std::string &Clave, unsigned int Default);


    ///Obtener un valor (flotante).
    /**
     * Obtiene el valor de una opción de configuración. Si la opción no se
     * encuentra, devuelve el valor por defecto pasado como parámetro.
     * 
     * \param Clave Nombre de la opción.
     * \param Default Valor por defecto en caso de que la opción todavía no exista.
     * \return El valor de la opción (de tipo \c double).
     */
    double ValorDouble(const std::string &Clave, double Default);

    
    ///Obtener un valor (booleano).
    /**
     * Obtiene el valor de una opción de configuración. Si la opción no se
     * encuentra, devuelve el valor por defecto pasado como parámetro.
     * Los valores guardados en el archivo de configuración que son
     * considerados como verdaderos son:
     *
     * yes, y, true, t, sí, s, verdadero, v, on, 1
     *
     * Cualquier otro valor es considerado como falso.
     * 
     * \param Clave Nombre de la opción.
     * \param Default Valor por defecto en caso de que la opción todavía no exista.
     * \return El valor de la opción (de tipo \c bool).
     */
    bool ValorBool(const std::string &Clave, bool Default);


    ///Saber si una opción está presente.
    /**
     * Hay casos donde es útil conocer de antemano si una opción está presente
     * en el archivo de configuración o no. Esta función devuelve si la opción
     * pasada como parámetro existe o no en el archivo de configuración.
     *
     * \param Clave Nombre de la opción.
     * \return \c si la opción existe, \c false en caso contrario.
     */
    bool Existe(const std::string &Clave);
};

#endif
