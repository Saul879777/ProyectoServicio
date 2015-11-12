
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
    char d;
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
    cout << "¿Deseas agregar servicio? (s/n)";
    cin >>d;
    if(d=='s' ||d=='S')
        agregarServ();
}
void Vehiculo::agregarServ(){
    Servicio x;
    x.agregar();
    servicio.push(x);    
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
};
void Cliente::setCliente(){
    cout << "Nombre: ";
    cin >>nombre;
    cout << "Telefono: ";
    cin >>telefono;
    agregarAuto();
}
void Cliente::agregarAuto(){
    coche.agregar();
}
void Cliente::muestra(){
    cout << "Nombre: " << nombre;
    cout << "Teléfono: "<<telefono;
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
    void encontrar(int id);
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
            encontrar(id);
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
void Persona::encontrar(int id){
    map<int, Cliente>::iterator p = agenda.find(id);
    if(p != agenda.end()){
     cout << "Id: " << id << endl;
     p->second.muestra();
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
void menu(){
    int des;
    int id;
    Persona x;
    Cliente c;
    Cola co;
    cout << "1)Ha llegado un nuevo cliente \n2)Llego un cliente ya conocido"
            "\n3)Se ha atendido al cliente\n4)Mostrar clientes por atender"
            "\n5)Mostrar siguiente cliente\n6)Salir;";
    cin >>des;
    switch(des){
        case 1:
            cout << "Numero identificador";
            cin >> id;
            c.setCliente();
            x.ingresar(id, c);
            co.mete(c);
            break;
        case 2:
            cout << "Dame el numero de cliente: ";
            cin >> id;
            x.encontrar(id);
            break;
        case 3:
            co.saca();
            break;
        case 4:
            co.mostrar();
            break;
        case 5:
            co.datoFte().muestra();
            break;
        case 6:
            cout << "Se fueron todos";
            exit(1);
            break;
        default:
            cout << "Opcion invalida";
    }
}
//==============================================================================
int main(int argc, char** argv) {
    while(1){
        menu();
    }    
    return 0;
}
