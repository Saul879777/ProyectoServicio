/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: SaúlEnrique
 *
 * Created on 11 de noviembre de 2015, 01:29 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

class NodoCola{
private:
    string cliente;
    NodoCola *sig;
friend class Cola;
};

class Cola{
private:
     NodoCola *ini;
     NodoCola *fin;
public:
  //operaciones basicas
     Cola();
     int estaVacia();
     void mete(string cl);
     void saca();
     string datoFte();  //se puede quitar este método y que la función saca regrese el dato del frente
     void muestra();
  //operaciones complementarias
     void elimina(string cliente);
     int nClientes();
     void copia(Cola c1);
};


//código de métodos

/*OPERACIONES BASICAS*****************************************/
Cola::Cola(){
  ini = NULL;
  fin = NULL;
}

int Cola::estaVacia(){
  return (ini == NULL && fin == NULL);
}

//agregar un elemento al final de la cola
void Cola::mete(string cl){
  //1) crear el nodo
  NodoCola *p;
  p = new NodoCola();
  p->cliente = cl;
  //2) Nodo siguiente apunta a NULL
  
  p->sig = NULL;
  //3) si hay elementos, el ultimo apunta al nuevo nodo
  if(fin != NULL){
    fin->sig = p;
  }
  //4) ultimo apunta al nuevo nodo
  fin = p;
  //5) Si la cola estava vacia, primero apunta al nodo
  if(ini == NULL){
    ini = p;
  }
}

//Sacar un dato de la cola
void Cola::saca(){
  //0) Verificar que tiene elementos
  if(ini==NULL && fin == NULL){
     cout<<"Error Cola vacia";
     exit(1);
  }
  //1)Nodo apunta al primer elemento de la cola
  NodoCola *p = ini;
  //2) Asignar a ini la direccion el segundo nodo de la lista
  ini = ini->sig;
  //3) Si ini apunta a NULL, hace que fin tambien apunta a NULL
  //   ya que la lista tenia un solo elemento
  if(ini == NULL){
    fin = NULL;
  }
  //4)Liberamos memoria del nodo
  delete p;
}

string Cola::datoFte(){
  NodoCola *p = ini;
  if(p == NULL){
     cout<<"Error: Apuntador nulo";
     exit(1);
  }
  return p->cliente;
}

void Cola::muestra(){
Cola aux;
string x;
  while(!estaVacia()){
     x = datoFte();
     saca();
     cout<<"<"<<x<<">";
     aux.mete(x);
  }
  cout<<"\n";

  copia(aux);

  return;
}

void Cola::copia(Cola c){
string x;
  while(!c.estaVacia()){
    x = c.datoFte();
    c.saca();
    mete(x);
  }
}

class NodoPila{
private:
    string servicio;
    NodoPila *sig;
friend class Pila;
};

class Pila{
private:
     NodoPila *aptope;
public:
  //operaciones basicas
     Pila();
     int estaVacia();
     void push(string x);
     string pop();
     void muestra();
  //operaciones complementarias
     void copia(Pila c1);
};


/*OPERACIONES BASICAS*****************************************/
Pila::Pila(){
  aptope = NULL;
 }
int Pila::estaVacia(){
  return (aptope == NULL);
}

void Pila::push(string x){
  NodoPila *p;
  p = new NodoPila();
  p->servicio = x;
  p->sig = aptope;
  aptope = p;
}

string Pila::pop(){
  NodoPila *p = aptope;
  string x;
  if(p==NULL){
     cout<<"Error lista vacia";
     exit(1);
  }
  aptope = aptope->sig;
  x = p->servicio; 
  delete p;
  return  x; 
}

void Pila::muestra(){
Pila aux;
string x;
  while(!estaVacia()){
     x = pop();
     cout<<"<"<<x<<">";
     aux.push(x);
  }
  cout<<"\n";
  copia(aux);
  return;
}

void Pila::copia(Pila c){
string x;
  while(!c.estaVacia()){
    x = c.pop();
    push(x);
  }
  return;
}

/*
 * 
 */
int main(int argc, char** argv) {

    return 0;
}