/*
    jjConfig 0.5:
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

#include <fstream>
#include <cstdlib>
#include "jjConfig.h"

using namespace std;

jjConfig::jjConfig(const string &Archivo)
{
    this->file = Archivo;
    cargar_datos();
}

bool jjConfig::cargar_datos()
{
    ifstream entrada(this->file.c_str());
    if (!entrada.good())
        return false;
    string linea, clave, valor;
    //analizar cada línea separando clave de valor (clave=valor):
    while (getline(entrada, linea)){
        size_t posigual = linea.find("=");
        if (posigual != string::npos){
            clave = linea.substr(0, posigual);
            valor = linea.substr(posigual+1);
            trim(clave);
            trim(valor);
            this->data.insert(make_pair(clave, valor));
        }
    }
    entrada.close();
    return true;
}

bool jjConfig::Guardar()
{
    ofstream salida(this->file.c_str(), ios::trunc);
    if (!salida.good())
        return false;
    map<string, string>::iterator it = this->data.begin();
    while (it != this->data.end()){
        salida<<it->first<<"="<<it->second<<'\n';
        it++;
    }
    salida.close();
    return true;
}

void jjConfig::SetValor(const string &Clave, const string &Val)
{
    this->data[Clave] = Val;
}

void jjConfig::SetValor(const std::string &Clave, const char *Val)
{
    this->data[Clave] = Val;
}

void jjConfig::SetValor(const string &Clave, int Val)
{
    string v = int2str(Val);
    SetValor(Clave, v);
}

void jjConfig::SetValor(const string &Clave, unsigned int Val)
{
    string v = uint2str(Val);
    SetValor(Clave, v);
}

void jjConfig::SetValor(const string &Clave, double Val)
{
    string v = dbl2str(Val);
    SetValor(Clave, v);
}

void jjConfig::SetValor(const string &Clave, bool Val)
{
    SetValor(Clave, Val ? "true" : "false");
}

string jjConfig::Valor(const string &Clave, const string &Default)
{
    map<string, string>::iterator it;
    it = this->data.find(Clave);
    if (it == this->data.end())
        return Default;
    return it->second;
}

int jjConfig::ValorInt(const string &Clave, int Default)
{
    map<string, string>::iterator it;
    it = this->data.find(Clave);
    if (it == this->data.end())
        return Default;
    return str2int(it->second);
}

unsigned int jjConfig::ValorUInt(const string &Clave, unsigned int Default)
{
    map<string, string>::iterator it;
    it = this->data.find(Clave);
    if (it == this->data.end())
        return Default;
    return str2uint(it->second);
}

double jjConfig::ValorDouble(const string &Clave, double Default)
{
    map<string, string>::iterator it;
    it = this->data.find(Clave);
    if (it == this->data.end())
        return Default;
    return str2dbl(it->second);
}

bool jjConfig::ValorBool(const string &Clave, bool Default)
{
    map<string, string>::iterator it;
    it = this->data.find(Clave);
    if (it == this->data.end())
        return Default;
    return str2bool(it->second);
}


/****************************************************************************
 * FUNCIONES DE UTILERÍA (PRIVADAS):
 ***************************************************************************/

string& jjConfig::trim(string &Cadena)
{
    unsigned int i, j;
    for (i=0; i<Cadena.length(); ++i){
        if (Cadena[i] != ' ' && Cadena[i] != char(13)) break;
    }
    for (j=Cadena.length()-1; j>=0; --j){
        if (Cadena[j] != ' ' && Cadena[j] != char(13)) break;
    }
    Cadena = Cadena.substr(i, j+1);
    return Cadena;
}

int jjConfig::str2int(const string &Cadena)
{
    return strtol(Cadena.c_str(), NULL, 10);
}

unsigned int jjConfig::str2uint(const string &Cadena)
{
    return strtoul(Cadena.c_str(), NULL, 10);
}

double jjConfig::str2dbl(const string &Cadena)
{
    return strtod(Cadena.c_str(), NULL);
}

bool jjConfig::str2bool(const string &Cadena)
{
    string s(Cadena);
    for (int i=0; i<s.size(); ++i){
        s[i] = tolower(s[i]);
    }
    return (s == "yes" || s == "y" || s == "true" || s == "t" || s == "1" ||
        s == "sí" || s == "s" || s == "verdadero" || s == "v" || s == "on");
}

string jjConfig::int2str(int Entero)
{
    char buf[25];
    sprintf(buf, "%d", Entero);
    string s(buf);
    return s;
}

string jjConfig::uint2str(unsigned int Entero)
{
    char buf[25];
    sprintf(buf, "%ud", Entero);
    string s(buf);
    return s;
}

string jjConfig::dbl2str(double Doble)
{
    char buf[500];
    sprintf(buf, "%f", Doble);
    string s(buf);
    return s;
}
