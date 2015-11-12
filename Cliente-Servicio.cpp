/* 
 * File:   main.cpp
 * Author: zerhogie
 *
 * Created on 11 de noviembre de 2015, 21:07
 */

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <utility>
#include <map>
#include <iomanip>
using namespace std;
typedef pair<string, string> persona;

//<<<<<<<<<<<<<<<   Clase Cliente   >>>>>>>>>>>>>>>
class Cliente{
private:
    string nombre;
    string telefono;
    Vehiculo coche;
public:
    void muestra();
    void setCliente();
};
void Cliente::setCliente(){
    cout << "Nombre: ";
    cin >>nombre;
    cout << "Telefono: ";
    cin >>telefono;
    coche.agregar();
}
void muestra(){
    
}

//<<<<<<<<<<<<<<<   Clase Persona  >>>>>>>>>>>>>>>
class Persona{
private:
    map<int, Cliente> agenda;
public:
    void menu();
    void ingresar(string nom, string num);
    void borrar(string nom);
    void encontrar(string nom);
    void mostrarDir();
};
void Persona::menu(){
    string nom, num;
    int des;
    cout << "\n1)Ingresar cliente al sistema\n2)Borrar cliente\n3)Encontar cliente\n4)Mostrar Directorio\n5)Salir\nOpción: ";
    cin >> des;
    switch(des){
        case 1:
            cout << "Nombre: ";
            cin >> nom;
            cout << "Teléfono: ";
            cin >> num;
            ingresar(nom, num);
            break;
        case 2:
            cout << "Dame el nombre de quien borro: ";
            cin >> nom;
            borrar(nom);
            break;
        case 3:
            cout << "¿A quien buscas? ";
            cin >> nom;
            encontrar(nom);
            break;
        case 4:
            mostrarDir();
            break;
        case 5:
            cout << " Gracias por usar el directorio \1 \n";
            exit(1);
            break;
        default:
            cout << "Opción inválida\n";
            break;
    }
}

void Persona::ingresar(string nom, string num){
    agenda.insert(persona(nom, num));
}

void Persona::borrar(string nom){
    map<string, string>::iterator p = agenda.find(nom);
    if(p != agenda.end())
        agenda.erase(p);
    else 
        cout << nom << " no está en el directorio.\n";
}
void Persona::encontrar(string nom){
    map<string, string>::iterator p = agenda.find(nom);
    if(p != agenda.end())
     cout << "Numero telefonico de : " << nom << " = " << p->second << endl;
    else 
     cout << nom << " no está en el directorio.\n";
}
//==============================================================================

//<<<<<<<<<<<<<<<<<<   Clase Vehiculo   >>>>>>>>>>>>>>>>>>
class Vehiculo{
private:
    string marca, modelo, tipo, color, placa;
    int kilometros;
    Pila servicio;
public:
    Vehiculo();
    void mostrar();
    void agregar();
};
Vehiculo::Vehiculo(){
    marca="";
    modelo="";
    tipo="";
    color="";
    placa="";
    kilometros=0;
}
void Vehiculo::mostrar(){
    if(modelo!=""){
        cout << "\n";
        cout << setw(10) << "Modelo: " << setw(12) << modelo<< "\n";
        cout << setw(10) << "Marca: " << setw(12) << marca;
        cout << setw(10) << "Tipo de auto: " << setw(12) << tipo<< "\n";
        cout << setw(10) << "Color: " << setw(12) << color << "\n";
        cout << setw(10) << "Placa: " << setw(12) << placa<< "\n";
        cout << setw(10) << "Kilómetros: " << setw(12) << kilometros << "\n";
    }
}
void Vehiculo::agregar(){
    cout << "Proporciona lo que se pide, sin espacios: \n";
    cout << "Modelo: ";
    cin >> modelo;
    cout << "Marca: ";
    cin >> marca;
    cout << "Tipo de auto (estándar/automático): ";
    cin >> tipo;
    cout << "Color: ";
    cin >> color;
    cout << "Placas: ";
    cin >> placa;
    cout << "Kilómetros: ";
    cin >> kilometros;
}
//==============================================================================

//<<<<<<<<<<<<<<<<<<   Clase Servicio  >>>>>>>>>>>>>>>>>>
class Servicio{
private:
    string fecha, tipo, costo, descripcion;
public:
    Servicio();
    void mostrar();
    void agregar(string f, string t, string c, string d);
    void agregar();
};
Servicio::Servicio(){
    fecha="";
    tipo="";
    costo="";
    descripcion="";
}
void Servicio::mostrar(){
    if(descripcion!=""){
        cout << setw(10) << "Servicio: " << setw(12) << descripcion << "\n";
        cout << setw(10) << "Tipo de servicio: " << setw(12) << tipo<< "\n";
        cout << setw(10) << "Fecha: " << setw(12) << fecha<< "\n";
        cout << setw(10) << "Costo: " << setw(12) << costo;
    }
}
void Servicio::agregar(string f, string t, string c, string d){
    fecha=f;
    tipo=t;
    costo=c;
    descripcion=d;
}
void Servicio::agregar(){
    cout << "Proporciona lo que se te pide: \n Fecha(dd/mm/aaaa): ";
    cin >> fecha;
    cout <<"Tipo de servicio: "; cin >>tipo;
    cout << "Decripcion: "; cin >> descripcion;
    cout << "Precio: "; cin >> costo;
}
//==============================================================================

//<<<<<<<<<<<<<<<<<<   Clase Servicios (en una pila)   >>>>>>>>>>>>>>>>>>
class Servicios{
private:
    Servicio serv;
    Servicios *sig;
    friend class Pila;
};
class Pila{
private:
     Servicios *aptope;
public:
  //operaciones basicas
     Pila();
     int estaVacia();
     void push(Servicio x);
     Servicio pop();
     void muestra();
  //operaciones complementarias
     void copia(Pila c1);
};
/*OPERACIONES BASICAS*/
Pila::Pila(){
  aptope = NULL;
 }
int Pila::estaVacia(){
  return (aptope == NULL);
}
void Pila::push(Servicio x){
  Servicios *p;
  p = new Servicios();
  p->serv = x;
  p->sig = aptope;
  aptope = p;
}
Servicio Pila::pop(){
  Servicios *p = aptope;
  Servicio x;
  if(p==NULL){
     cout<<"Error lista vacia";
     exit(1);
  }
  aptope = aptope->sig;
  x = p->serv; 
  delete p;
  return  x; 
}
void Pila::muestra(){
Pila aux;
Servicio x;
cout << "-----------------------------------------------------\n";
while(!estaVacia()){
    x = pop();
    x.mostrar();
    aux.push(x);
}
cout<<"\n-----------------------------------------------------\n";
copia(aux);
return;
}
void Pila::copia(Pila c){
Servicio x;
  while(!c.estaVacia()){
    x = c.pop();
    push(x);
  }
  return;
}
//==============================================================================

//<<<<<<<<<<<<<<<<<<   Clase Reparación   >>>>>>>>>>>>>>>>>>
class Reparacion{
private:
    map<Vehiculo, Pila> reparo;
public:
    void menu();
    void ingresar(Vehiculo v, Pila s);
    void borrar(Vehiculo v);
    void encontrar(Vehiculo v);
    void mostrarDir();
};
void Reparacion::ingresar(Vehiculo v, Pila s){
    reparo.insert(pair<Vehiculo, Pila>(v, s));
}

void Reparacion::borrar(Vehiculo v){
    map<Vehiculo, Pila>::iterator p = reparo.find(v);
    if(p != reparo.end())
        reparo.erase(p);
    else 
        cout << " No está en el directorio.\n";
}
void Reparacion::encontrar(Vehiculo v){
    map<Vehiculo, Pila>::iterator p = reparo.find(v);
    if(p != reparo.end()){
        cout << "Vehiculo: ";
        v.mostrar(); 
        cout << "\nTiene los servicios: \n";
        Pila x = p->second;
        x.muestra();
    }
    else 
     cout << "El vehiculo no está en el directorio.\n";
}

//==============================================================================
int main(int argc, char** argv) {

    return 0;
}

