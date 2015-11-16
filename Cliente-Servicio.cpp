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

//<<<<<<<<<<<<<<<<<<   Clase Servicio  >>>>>>>>>>>>>>>>>>
class Servicio{
private:
    string fecha, tipo, descripcion;
    float costo;
public:
    Servicio();
    void mostrar();
    void agregar(string f, string t, float c, string d);
    void agregar();
    float getCosto();
};
Servicio::Servicio(){
    fecha="";
    tipo="";
    costo=0;
    descripcion="";
}
void Servicio::mostrar(){
    if(descripcion!=""){
        cout << setw(10) << "Servicio: " << setw(12) << descripcion << "\n";
        cout << setw(10) << "Tipo de servicio: " << setw(12) << tipo<< "\n";
        cout << setw(10) << "Fecha: " << setw(12) << fecha<< "\n";
        cout << setw(10) << "Costo: " << setw(12) << costo << "\n\n";
    }
}
void Servicio::agregar(string f, string t, float c, string d){
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
float Servicio::getCosto(){
    return costo;
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
     float precio();
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
     cout<<"No tiene servicios";
  }
  aptope = aptope->sig;
  x = p->serv; 
  delete p;
  return  x; 
}
void Pila::muestra(){
Pila aux;
Servicio x;
int con=1;
cout << "-----------------------------------------------------\n";
while(!estaVacia()){
    cout << "Servicio: " << con << "\n";
    x = pop();
    x.mostrar();
    aux.push(x);
    con++;
}
cout<<"\n-----------------------------------------------------\n\n";
while(!aux.estaVacia())
    push(aux.pop());
return;
}
float Pila::precio(){
    return aptope->serv.getCosto();
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
    void agregarServ();
    Pila getServ();
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
        cout << setw(10) << "Marca: " << setw(12) << marca << "\n";
        cout << setw(10) << "Tipo de auto: " << setw(12) << tipo<< "\n";
        cout << setw(10) << "Color: " << setw(12) << color << "\n";
        cout << setw(10) << "Placa: " << setw(12) << placa<< "\n";
        cout << setw(10) << "Kilómetros: " << setw(12) << kilometros << "\nServicios: \n";
        servicio.muestra();
    }
}
void Vehiculo::agregar(){
    char d='s';
    cout << "\n Registro del auto\n Proporciona lo que se pide, sin espacios: \n";
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
    if(!servicio.estaVacia()){
        cout << "¿Deseas agregar servicio? (s/n)";
        cin >>d;
    }
    if(d=='s' ||d=='S')
        agregarServ();
}
void Vehiculo::agregarServ(){
    Servicio x;
    x.agregar();
    servicio.push(x);
    cout <<"\nServicio Agregado\n\n";
}
Pila Vehiculo::getServ(){
    return servicio;
}
//==============================================================================

//<<<<<<<<<<<<<<<   Clase Cliente   >>>>>>>>>>>>>>>
class Cliente{
private:
    string nombre;
    string telefono;
    Vehiculo coche;
public:
    void muestra();
    void setCliente();
    void agregarAuto();
    string getNom();
    Vehiculo getV();
};
void Cliente::setCliente(){
    cout << "Nombre: ";
    cin >>nombre;
    cout << "Telefono: ";
    cin >>telefono;
    agregarAuto();
}
string Cliente::getNom(){
    return nombre;
}
Vehiculo Cliente::getV(){
    return coche;
}
void Cliente::agregarAuto(){
    coche.agregar();
}
void Cliente::muestra(){
    cout << "Nombre: " << nombre;
    cout << "   Teléfono: "<<telefono;
    coche.mostrar();
}
//==============================================================================

//<<<<<<<<<<<<<<<   Clase Persona  >>>>>>>>>>>>>>>
class Persona{
private:
    map<int, Cliente> agenda;
public:
    void menu();
    void ingresar(int id, Cliente c);
    void borrar(int id);
    Cliente encontrar(int id);
    void mostrarDir();
};
void Persona::menu(){
    int id=0;
    Cliente c;
    int des;
    cout << "\n1)Ingresar cliente al sistema\n2)Borrar cliente\n3)Encontar cliente\n4)Mostrar Directorio\n5)Salir\nOpción: ";
    cin >> des;
    switch(des){
        case 1:
            cout << "Numero identificador";
            cin >> id;
            c.setCliente();
            ingresar(id, c);
            break;
        case 2:
            cout << "Dame el numero de quien borro: ";
            cin >> id;
            borrar(id);
            break;
        case 3:
            cout << "Dame numero de quien buscas: ";
            cin >> id;
            encontrar(id).muestra();
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

void Persona::ingresar(int id, Cliente c){
    agenda.insert(pair<int, Cliente>(id, c));
}

void Persona::borrar(int id){
    map<int, Cliente>::iterator p = agenda.find(id);
    if(p != agenda.end())
        agenda.erase(p);
    else 
        cout << id << " no está en el directorio.\n";
    
}
Cliente Persona::encontrar(int id){
    map<int, Cliente>::iterator p = agenda.find(id);
    if(p != agenda.end()){
     return p->second;
    }
    else 
     cout << id << " no está en el directorio.\n";
}
void Persona::mostrarDir(){
    map<int, Cliente>::iterator p = agenda.begin();
    while (p != agenda.end())
    {
      cout << p->first << setw(12);
      p->second.muestra();
      p ++;
    }
}
//==============================================================================

//<<<<<<<<<<<<<<<<<<   Clase Encargo (En una cola)   >>>>>>>>>>>>>>>>>>
class Encargo{
private:
    Cliente cl;
    Encargo *sig;
    friend class Cola;
};
class Cola{
private:
    Encargo *ini;
    Encargo *fin;
public:
    //Operaciones básicas
    Cola();
    //~Cola();
    int estaVacia();
    void mete(Cliente x);
    void saca();
    Cliente datoFte();
    void mostrar();
    int contar();
    void menu();
};
Cola::Cola(){
    ini=NULL;
    fin=NULL;
}

//Indica si está vacía
int Cola::estaVacia(){
    return (ini==NULL);
}

//Mete un elemento
void Cola::mete(Cliente x){
    Encargo *p;
    p= new Encargo();
    p->cl=x;
    p->sig=NULL;
    if(!estaVacia()){
        fin->sig=p;
        fin=p;
    }
    else{
        ini=p;
        fin=p;
    }
        
}
//Saca
void Cola::saca(){
    if(ini==NULL&&fin==NULL){
        cout << "\n(!)Error no hay encargos";
        exit(1);
    }
    Encargo *p=ini;
    ini=ini->sig;
    if(ini==NULL)
        fin=NULL;
    delete p;
}

//Muestra el dato de enfrente
Cliente Cola::datoFte(){
    return ini->cl;
}

//Muestra los elementos de la cola
void Cola::mostrar(){
    Cola aux;
    cout << "\n";
    while(!estaVacia()){
        datoFte().muestra();
        aux.mete(datoFte());
        saca();
    }
    ini=aux.ini;
    fin=aux.fin;
}

//Cuenta los elementos de la cola
int Cola::contar(){
    Cola aux;
    int con;
    while(!estaVacia()){
        con++;
        aux.mete(datoFte());
        saca();
    }
    ini=aux.ini;
    fin=aux.fin;
    return con;
}
//==============================================================================

// <<<<<<<<<<<<<<<<<<   Menú para el usuario    >>>>>>>>>>>>>>>>>>
class Menu{
private:
    int des;
    int id;
    Persona x;
    Cola co;
    float ganancia;
public:
    void menu();
    Menu();
};
Menu::Menu(){
    ganancia=0;
}
void Menu::menu(){ 
    Cliente c;
    Servicio s;
    cout << "\n1)Ha llegado un nuevo cliente \n2)Llego un cliente ya conocido"
            "\n3)Se ha atendido al cliente\n4)Mostrar clientes por atender"
            "\n5)Mostrar siguiente cliente\n6)Mostrar Servicios del siguiente cliente\n"
            "7)Administrar directorio\n8)Salir\nDesición: ";
    cin >>des;
    switch(des){
        case 1:
            cout << "Numero identificador";
            cin >> id;
            c.setCliente();
            x.ingresar(id, c);
            co.mete(x.encontrar(id));
            break;
        case 2:
            cout << "Dame el numero de cliente: ";
            cin >> id;
            c=x.encontrar(id);
            if(c.getNom()!=co.datoFte().getNom()){
                c.muestra();
                cout << "\nAgrega el servicio que se le dará esta ves:\n";
                c.getV().agregarServ();
                x.borrar(id);
                x.ingresar(id, c);
                co.mete(x.encontrar(id));
            }
            else{
                c.muestra();
                cout <<"\nAgrega el servicio adicional:\n";
                if(!co.datoFte().getV().getServ().estaVacia()){
                    ganancia+=(co.datoFte().getV().getServ().precio());
                }
                co.datoFte().getV().agregarServ();
                x.borrar(id);
                x.ingresar(id,c);
            }
            break;
        case 3:
            if(!co.estaVacia()){
                ganancia+=(co.datoFte().getV().getServ().precio());
                cout << "Se ha atendido a: " << co.datoFte().getNom();
                co.saca();
                cout << "\nSe han generado: $"<< ganancia << " de ganancias\n\n";
            }
            else
                cout << "\nError, no tenías a nadie a quien atender\n";
            break;
        case 4:
            co.mostrar();
            break;
        case 5:
            co.datoFte().muestra();
            break;
        case 6:
            co.datoFte().getV().getServ().muestra();
            break;
        case 7:
            x.menu();
            break;
        case 8:
            cout << "Se fueron todos";
            exit(1);
            break;
        default:
            cout << "Opcion invalida";
            break;
    }
}
//==============================================================================
int main(int argc, char** argv) {
    Menu x;
    while(1){
        x.menu();
    }    
    return 0;
}

