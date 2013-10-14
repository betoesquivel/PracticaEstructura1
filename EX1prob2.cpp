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
		void Insertar(T dato);
		~ListaDEC();
};

template <class T>
void ListaDEC<T>::Insertar(T dato)
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
	}
	return true;
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
