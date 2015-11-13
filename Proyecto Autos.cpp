#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>

using namespace std;

//================Clase Servicio para ser introducida en Pila================//

class Servicio{
private:
	string fecha, tipo, descripcion;
	int costo;
public:
	Servicio();
	void setFecha(string f);
	void setTipo(string t);
	void setDescripcion(string d);
	void setCosto(int c);
	string getFecha();
	string getTipo();
	string getDescripcion();
	int getCosto();
};

Servicio::Servicio(){
	fecha="No hay fecha";
	tipo="No hay tipo";
	descripcion="No hay descripcion";
	costo=0;
}

void Servicio::setFecha(string f){
	fecha=f;
}

void Servicio::setTipo(string t){
	tipo=t;
}

void Servicio::setDescripcion(string d){
	descripcion=d;
}

void Servicio::setCosto(int c){
	costo=c;
}

string Servicio::getFecha(){
	return fecha;
}

string Servicio::getTipo(){
	return tipo;
}

string Servicio::getDescripcion(){
	return descripcion;
}

int Servicio::getCosto(){
	return costo;
}

//================Declaración de pila================//

class NodoPila{
private:
    Servicio s;
    NodoPila *sig;
friend class PServicios;
};

class PServicios{
private:
	NodoPila *aptope;
public:
	PServicios();
	int pilaVacia();
	void push(Servicio x);
	Servicio pop();
	void muestra();
	void buscarServicio(Servicio b);
};

PServicios::PServicios(){
	aptope=NULL;
}

int PServicios::pilaVacia(){
	return (aptope == NULL);
}

void PServicios::push(Servicio x){
	NodoPila *p;
	p = new NodoPila();
	p->s = x;
	p->sig = aptope;
	aptope = p;	
}

Servicio PServicios::pop(){
	Servicio x;
	NodoPila *p = aptope;
	if (pilaVacia()){
		cout<<"\nLista de servicios vacia";
	}
	else{
		aptope=aptope->sig;
		x=p->s;
		delete p;
		return x;
	}
}

void PServicios::muestra(){
	PServicios aux;
	Servicio x;
	while (!pilaVacia()){
		x = pop();
		cout<<"\nFecha: "<<x.getFecha()<<"\nTipo: "<<x.getTipo()<<"\nDescripcion: "<<x.getDescripcion()<<"\nCosto: "<<x.getCosto()<<"\n";
		aux.push(x);
	}
	while (!aux.pilaVacia()){
		push(aux.pop());
	}
}

void PServicios::buscarServicio(Servicio b){
	PServicios aux;
	Servicio x;
	int encontrado=0;
	while (!pilaVacia()&&encontrado!=1){
		x = pop();
		if (x.getTipo()==b.getTipo()){
			encontrado=1;
		}
		aux.push(x);
	}
	while (!aux.pilaVacia()){
		push(aux.pop());
	}
	if(encontrado=1){
		cout<<"\nEste mantenimiento si se ha hecho previamente";
	}
	else{
		cout<<"\nEste mantenimiento no se ha hecho previamente";
	}
}

//================Declaracion de vehiculo================//

class Vehiculo{
private:
	string tipoVehiculo, placa, marca, modelo, color;
	int kilometraje;
	PServicios ps;
public:
	Vehiculo();
	void setTipoVehiculo(string tv);
	void setPlaca(string p);
	void setMarca(string mar);
	void setModelo(string mod);
	void setColor(string col);
	void setKilometraje(int k);
	string getTipoVehiculo();
	string getPlaca();
	string getMarca();
	string getModelo();
	string getColor();
	int getKilometraje();
};

Vehiculo::Vehiculo(){
	tipoVehiculo="No hay tipo";
	placa="No hay placa";
	marca="No hay marca";
	modelo="No hay modelo";
	color="No hay color";
	kilometraje=0;
}

void Vehiculo::setTipoVehiculo(string tv){
	tipoVehiculo=tv;
}

void Vehiculo::setPlaca(string p){
	placa=p;
}

void Vehiculo::setMarca(string mar){
	marca=mar;
}

void Vehiculo::setModelo(string mod){
	modelo=mod;
}

void Vehiculo::setColor(string col){
	color=col;
}

void Vehiculo::setKilometraje(int k){
	kilometraje=k;
}

string Vehiculo::getTipoVehiculo(){
	return tipoVehiculo;
}

string Vehiculo::getPlaca(){
	return placa;
}

string Vehiculo::getMarca(){
	return marca;
}

string Vehiculo::getModelo(){
	return modelo;
}

string Vehiculo::getColor(){
	return color;
}

int Vehiculo::getKilometraje(){
	return kilometraje;
}

//================Declaracion de cliente================//

class Cliente{
private:
	string nombre, apPat, apMat, telefono;
	Vehiculo v;
public:
	Cliente();
	void setNombre(string n);
	void setApPat(string ap);
	void setApMat(string am);
	void setTelefono(string t);
	string getNombre();
	string getApPat();
	string getApMat();
	string getTelefono();
};

Cliente::Cliente(){
	nombre="No hay nombre";
	apPat="No hay apellido paterno";
	apMat="No hay apellido materno";
	telefono="No hay telefono";
}

void Cliente::setNombre(string n){
	nombre=n;
}

void Cliente::setApPat(string ap){
	apPat=ap;
}

void Cliente::setApMat(string am){
	apMat=am;
}

void Cliente::setTelefono(string t){
	telefono=t;
}

string Cliente::getNombre(){
	return nombre;
}

string Cliente::getApPat(){
	return apPat;
}
string Cliente::getApMat(){
	return apMat;
}
string Cliente::getTelefono(){
	return telefono;
}

//================Declaracion de la cola================//

class NodoCola{
private:
    Cliente c;
    NodoCola *sig;
friend class CCliente;
};

class CCliente{
private:
	NodoCola *ini;
	NodoCola *fin;
public:
	CCliente();
	int colaVacia();
	void mete(Cliente x);
	Cliente saca();
	void buscarCliente(Cliente b);
	void muestra();
};

CCliente::CCliente(){
	ini = NULL;
 	fin = NULL;
}

int CCliente::colaVacia(){
  return (ini == NULL && fin == NULL);
}

void CCliente::mete(Cliente x){
  	NodoCola *p;
  	p = new NodoCola();
  	p->c = x;
  	p->sig = NULL;
  	if(fin != NULL){
    	fin->sig = p;
  	}
  	fin = p;
  	if(ini == NULL){
    	ini = p;
  	}
}

Cliente CCliente::saca(){
	Cliente x;
	if(ini==NULL && fin == NULL){
     	cout<<"Cola de clientes vacia";
     	exit(1);
  	}
  	NodoCola *p = ini;
  	x=p->c;
  	ini = ini->sig;
  	if(ini == NULL){
    	fin = NULL;
  	}
  	return x;
  	delete p;
}

void CCliente::buscarCliente(Cliente b){
	CCliente aux;
	Cliente x;
	int encontrado=0;
	while (!colaVacia() && encontrado!=1){
		x=saca();
		if (x.getApPat()==b.getApPat() && x.getApMat()==b.getApMat() && x.getNombre()==b.getNombre()){
			encontrado=1;
		}
		aux.mete(x);
	}
	while(!aux.colaVacia()){
		mete(aux.saca());
	}
	if(encontrado=1){
		cout<<"\nEste cliente se encuentra en al cola";
	}
	else{
		cout<<"\nEste cliente no se encuentra en la cola";
	}
}

void CCliente::muestra(){
	CCliente aux;
	Cliente x;
	while (!colaVacia()){
		x=saca();
		cout<<"\nNombre: "<<x.getNombre()<<" "<<x.getApPat()<<" "<<x.getApMat();
		cout<<"\nCorreo: "<<x.getTelefono();
		aux.mete(x);
	}
	while (!aux.colaVacia()){
		mete(aux.saca());
	}
}