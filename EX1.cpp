//Jose Alberto Esquivel Patino A01139626
/*
 * =====================================================================================
 *
 *       Filename:  EX1.cpp
 *
 *    Description:  Realiza la implementacion del ADT Cola Priorizada (metodo inserta,
 *    procesa y empty) con dos constructores, uno en el que el usuario define el numero
 *    de prioridades y otro en el que el usuario no lo define y el default es 3.
 *    Las cola priorizada sera representada por un arreglo de queues de stl. El queue 
 *    en la posicion 0 tendra mayor prioridad que el queue en la posicion 1, y asi
 *    sucesivamente.
 *
 *        Version:  1.0
 *        Created:  10/03/2013 08:44:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose ALberto Esquivel Patino A01139626 
 *   Organization:  ITESM
 *
 * =====================================================================================
 */
#include <queue>
#include <iostream>

using namespace std;

bool debug = true;

template <class T>
class ColaPriorizada
{
	private:
		int numero_de_prioridades;
		queue<T> *arregloDeColas;	

	public:
		ColaPriorizada();
		ColaPriorizada(int num_de_prioridades);

		void inserta(T dato, int prioridad);
		T procesa();
		bool vacia();

		~ColaPriorizada();
};

template <class T>
ColaPriorizada<T>::ColaPriorizada()
{
	numero_de_prioridades = 3;
	arregloDeColas = new queue<T>[numero_de_prioridades];
}
template <class T>
ColaPriorizada<T>::ColaPriorizada(int num_de_prioridades)
{
	numero_de_prioridades = num_de_prioridades;
	arregloDeColas = new queue<T>[numero_de_prioridades];
}

template <class T>
void ColaPriorizada<T>::inserta(T dato, int prioridad)
{
	//inserta un dato de acuerdo a su prioridad
	cout<<"Inserto el dato "<<dato<<" con prioridad "<<prioridad<<endl;
	arregloDeColas[prioridad].push(dato);
}
template <class T>
T ColaPriorizada<T>::procesa()
{
	//Se asume que a nivel aplicacion, se verifico que la colaPriorizada no estuviera vacia.
	//saca un dato de acuerdo a su prioridad
	cout<<"Proceso un dato."<<endl;
	int i = 0;
	T dato;
	while(i<numero_de_prioridades)
	{
		if(!arregloDeColas[i].empty())
		{
			dato = arregloDeColas[i].front();
			arregloDeColas[i].pop();
			return dato;
		}

		i++;
	}
}
template <class T>
bool ColaPriorizada<T>::vacia()
{
	bool colaPriorizadaVacia = true;
	int i = 0;
	while(i<numero_de_prioridades && colaPriorizadaVacia)
	{
		colaPriorizadaVacia = (arregloDeColas[i].empty()) ? true:false;
		i++;
	}
	return colaPriorizadaVacia;
}

template <class T>
ColaPriorizada<T>::~ColaPriorizada()
{
	delete []arregloDeColas;
}

//PILA DOBLEMENTE ENCADENADA====================================
template <class T>
class Nodo
{
	public:
		T info;
		Nodo<T> *sig, *ant;
		Nodo() { sig = ant = NULL; }
		Nodo(T dato) { info = dato; sig = ant = NULL; }
};

template <class T>
class ListaDEC
{ 
	private:
		Nodo<T>* externo;

	public:
		ListaDEC() { externo = NULL; }
		bool Insertar(T dato);
		bool SACAR_PILA();
		bool SACAR_FILA();
		T ROTAR(int pos);
		~ListaDEC();
};

template <class T>
bool ListaDEC<T>::Insertar(T dato)
{
	Nodo<T>* aux = new Nodo<T>(dato);
	if (aux == NULL) return false;
	if (externo == NULL)
	{ 
		aux->sig = aux->ant = aux;
		externo = aux;
	}
	else
	{
		aux->sig = externo->sig;
		aux->ant = externo;
		externo->sig->ant = aux;
		externo->sig = aux;
		externo = aux; //esta linea la inserte yo, no se si esta bien o mal.
	}
	return true;
}

template <class T>
bool ListaDEC<T>::SACAR_PILA()
{
	if (externo == NULL)
	{ 
		//la pila esta vacia
		return false;
	}
	else
	{
		Nodo<T>* aux = externo;
		if(externo->sig != externo)
		{
			externo = externo->ant;
			externo->sig = aux->sig;
			aux->sig->ant = externo; 
		}
		else
			externo = NULL;
		delete aux;
	}
	return true;
}

template <class T>
bool ListaDEC<T>::SACAR_FILA()
{
	if (externo == NULL)
	{ 
		//la fila esta vacia
		return false;
	}
	else
	{
		Nodo<T>* aux = externo->sig;
		if(externo->sig != externo)
		{
			externo->sig = aux->sig;
			aux->sig->ant = externo;
		}
		else
			externo = NULL;
		delete aux;
	}
	return true;
}

template <class T>
T ListaDEC<T>::ROTAR(int pos)
{

	if(pos<0)
	{
		//aqui recorreria la cantidad de posiciones hacia atras con ant[
		while(pos<0)
		{
			//aqui las recorreria hacia atras.
			externo = externo->ant;
			pos++;
		}
	}else if(pos>0) 
	{
		while(pos>0)
		{
			//aqui las recorreria hacia adelante.
			externo = externo->sig;
			pos--;
		}
	}
	return externo->info;
}

template <class T>
ListaDEC<T>::~ListaDEC()
{
	if (externo != NULL)
	{
		externo->ant->sig= NULL;
		Nodo<T> *aux = externo;
		while (aux != NULL)
		{
			externo = aux->sig;
			delete aux;
			aux = externo;
		}
	}
}
//PILA DOBLEMENTE ENCADENADA====================================

template <class T>
class DobleFila:private ListaDEC<T>
{
	public:
		DobleFila(){ListaDEC<T>::ListaDEC();}
		bool METERFRENTE(T dato)
		{
			ListaDEC<T>::ROTAR(1);
			bool exito = ListaDEC<T>::insertar(dato);
			ListaDEC<T>::ROTAR(-1);
			return exito;
		}
		bool SACARFRENTE(){return ListaDEC<T>::SACAR_FILA();}
		
		bool METERFINAL(T dato)
		{
			return ListaDEC<T>::insertar(dato);
		}
		bool SACARFINAL(){return ListaDEC<T>::SACAR_PILA();}
		
		~DobleFila(){ListaDEC<T>::~ListaDEC();}
};
int main()
{
	/* PARA PROBAR LA COLA PRIORIZADA
	cout<<"Prueba de mi cola priorizada."<<endl;
	cout<<"Cola Priorizada Default: "<<endl;
	ColaPriorizada<int> cola_default;

	int entrada;

	cout<<"Introduzca la prioridad del dato a introducir (0,1,2):"<<endl;
	cout<<"Nota: -1 para dejar de insertar e imprimir la cola priorizada"<<endl;
	cin>>entrada;
	while(entrada!=-1)
	{
		cola_default.inserta(entrada,entrada);
		cout<<"Introduzca la prioridad del dato a introducir (0,1,2):"<<endl;
		cout<<"Nota: -1 para dejar de insertar e imprimir la cola priorizada"<<endl;
		cin>>entrada;
	}
	
	while(!cola_default.vacia())
	{
		cout<<cola_default.procesa()<<endl;
	}
	
	int prioridades;
	cout<<"Prueba de mi cola priorizada."<<endl;
	cout<<"Cola Priorizada con prioridad: "<<endl;
	cin>>prioridades;	
	cout<<prioridades<<endl;

	ColaPriorizada<int> cola(prioridades);

	cout<<"Introduzca la prioridad del dato a introducir: (0-"<<prioridades-1<<")"<<endl;
	cout<<"Nota: -1 para dejar de insertar e imprimir la cola priorizada"<<endl;
	cin>>entrada;
	while(entrada!=-1)
	{
		cola.inserta(entrada,entrada);
		cout<<"Introduzca la prioridad del dato a introducir: (0-"<<prioridades-1<<")"<<endl;
		cout<<"Nota: -1 para dejar de insertar e imprimir la cola priorizada"<<endl;
		cin>>entrada;
	}
	
	while(!cola.vacia())
	{
		cout<<cola.procesa()<<endl;
	}

	cout<<"Ejecucion terminada. Gracias."<<endl;
	FIN DE LA PRUEBA DE LA COLA PRIORIZADA*/
	
	
}
