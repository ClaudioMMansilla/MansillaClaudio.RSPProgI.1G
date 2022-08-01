#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado (limpiando basura)
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= (LinkedList*) malloc(sizeof(LinkedList));
    this->pFirstNode = NULL;
    this->size = 0;
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista (size)
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	returnAux = this->size; // si el puntero no es null, existe linklist al que accedo a su campo size
    }						   //  size 0 no es lo mismo que null. This existe, pero no tiene elementos (aun)
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* nodo = NULL;
	if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this)) // valido el rango de index ingresado
	{
		nodo = this->pFirstNode;

		while(nodeIndex > 0)
		{
			nodo = nodo->pNextNode; // nodo ira iterando ascendentemente al proximo pNextNode en cada loop
			nodeIndex--;		   // nodeIndex ira decrementandose, para ser quien rompa el ciclo
								  // Es decir, se "encierra" por izquierda y por derecha el nodo a obtener
		}
	}

    return nodo;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex, void* pElement)
{
    int returnAux = -1;
    Node* nodoNuevo = NULL;
    Node* nodoAnterior = NULL;

    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this) )
    {
    	nodoNuevo = (Node*) malloc(sizeof(Node));
    	if(nodoNuevo != NULL)
    	{
    		nodoNuevo->pElement = pElement; // apunto el nodo creado hacia la carga
    		if(nodeIndex == 0)
    		{
    			nodoNuevo->pNextNode = this->pFirstNode;
    			this->pFirstNode = nodoNuevo;
    		 // El nuevo nodo apunta al viejo nodo que ocupaba el index 0, convirtiendolo en el index 1
    	    //  y pFirstNode deja de apuntar al viejo index 0 (ahora 1), y pasa a apuntar al nuevo nodo(index 0)
    		}
    		else
    		{
    	    //	me paro una posicion anterior al index recibido por parametro
    			nodoAnterior = getNode(this, nodeIndex -1);
    		//	al nodo nuevo lo conecto al nextNode apuntado por el nodoAnterior (que es el desplazado)
    			nodoNuevo->pNextNode = nodoAnterior->pNextNode;
    		//  conecto al nodoAnterior con el nuevo nodo
    			nodoAnterior->pNextNode = nodoNuevo;
    		//  Ruta linkeada:  nodoAnterior -> nodoNuevo -> nodo desplazado
    		}

    		this->size++; // incremento size porque se ha creado un nuevo elemento a la lista
    		returnAux = 0; // todo ok
    	}
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement) // ll_add agrega &memo de un elemento, al final del "tren"
{
    int returnAux = -1;
    // invoca a addNode y le paso como index el valor de size (size = 5, ultimo index seria el 4)
    if( (addNode(this, ll_len(this), pElement)) == 0)
    {
    	returnAux = 0;
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 */
void* ll_get(LinkedList* this, int index) //retorna &memoria del pElement apuntado por el nodo en dicho index
{
    void* returnAux = NULL;
    Node* nodoAux = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this) ) // si index es positivo y menor al size del linkedlist
    {
    	nodoAux = getNode(this, index); // nodoAux recibe el puntero al nodo pasado por param index
    	returnAux = nodoAux->pElement; // a traves de nodoAux accedo al campo pElement
    }

    return returnAux; // retorno puntero del tipo void hacia el elemento (carga)
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement) // cambia el pElement actual hacia un pElement nuevo,
{													  //  el nodo pasa a apuntar hacia un elemento distinto.
    int returnAux = -1;
    Node* nodoAux = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this) )
    {
    	nodoAux = getNode(this, index);
    	nodoAux->pElement = pElement;
    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* nodoARemover = NULL;
    Node* nodoAnterior = NULL;

    if(this != NULL && index >= 0 && index < ll_len(this) ) // si index es positivo y menor al size del linkedlist
    {
    	nodoARemover = getNode(this, index);
    	if(index == 0) // si se va a remover al primer vagon
    	{
    		// guardo la &memoria del first node, el cual se va a eliminar
    		nodoARemover = this->pFirstNode;
    		// piso el valor de firstNode con la &memoria del que era el segundo nodo (ahora sera el primero)
    		this->pFirstNode = nodoARemover->pNextNode;
    	}
    	else // eliminar cualquier otra posicion distinta del indice 0
    	{
    		// me paro en el nodo anterior al pasado por parametro, el cual conoce la &memoria
    		nodoAnterior = getNode(this, index -1);
    		// a traves del nodoAnterior, puedo saber la &memo del que se quiere eliminar
    		nodoARemover = nodoAnterior->pNextNode;
    		// conecto al nodoAnterior con el nextNode al cual el nodo a eliminar apuntaba antes
    		nodoAnterior->pNextNode = nodoARemover->pNextNode;
    	}
    	free(nodoARemover); // libero de memoria el nodo y se deja de apuntar al pElement
    	this->size--; // ajusto el size a su nuevo tamanio
    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	while(this->pFirstNode != NULL) // mientras haya vagones enganchados
    	{
    		ll_remove(this, 0); // elimino uno a uno los elementos, por desplazamiento de nodos de atras a adelante
    	}
    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if( (ll_clear(this)) == 0)
    	{
        	free(this);
        	returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement) // buscar el pElement en el array de nodos (retorna el index)
{
    int returnAux = -1;
    int sizeAux;

    if(this != NULL)
    {
    	sizeAux = ll_len(this);
    	for(int i=0; i < sizeAux; i++)
    	{
    		if(ll_get(this, i) == pElement) // si pElement en i es == a pElement recibido por parametro
    		{
    			returnAux = i; // retorno el indice (i) en donde se hizo el matcheo
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this) // consultar si el linkedlist esta vacio (no tiene elementos)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(this->pFirstNode == NULL)
    	{
    		returnAux = 1; // si pFirstNode no tiene elementos, entonces isEmpty es true
    	}
    	else
    	{
    		returnAux = 0; // else, es false
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement) { // insertar un nuevo nodo en un indice, desplazando en una
													      //  posicion al nodo que ocupaba dicho index
    int returnAux = -1;
    if(this != NULL && index >= 0 && index <= ll_len(this) )
    {
    	returnAux = addNode(this, index, pElement);
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index) {

    void* returnAux = NULL;
    if(this != NULL && index >= 0 && index < ll_len(this) )
    {
    	returnAux = ll_get(this, index); // retorno el pElement que va a ser des-referenciado / des-apuntado
    	ll_remove(this, index); 		// se realiza free del nodo, pero el elemento sigue existiendo como tal
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement) { // verificar que un elemento existe en la lista

    int returnAux = -1;
    if(this != NULL)
    {
    	returnAux = 0; // retorno 0 porque se ejecuta verificacion, retorno sera 1 si tiene exito
    	if(ll_indexOf(this, pElement) >= 0) // si indexOf retorna un index (>= 0), es porque pElement existe
    	{
    		returnAux = 1; // retorno 1 porque la verificacion tuvo exito
    	}
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2) { // verifica si los pElements de this2 estan en this

    int returnAux = -1;
    void* aux = NULL; // auxiliar porque pElement es un dato tipo void

    if(this != NULL && this2 != NULL)
    {
    	returnAux = 1;
    	int tam = ll_len(this2);

    	for(int i =0; i < tam; i++)
    	{
    		aux = ll_get(this, i); // recorro todos los pElement de this utilizando el iterador
    		if( ! ll_contains(this2, aux)) // niego return para salir al NO encontrar un elemento
    		{
    			returnAux = 0;
    			break; // si al menos un pElement no esta, no necesito seguir iterando
    		}
    	}
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to){
	LinkedList* cloneArray = NULL;
	void* elementAux = NULL;

	if(this != NULL && from >= 0 && to <= ll_len(this) && to >= from) {

		cloneArray = ll_newLinkedList();
		if(cloneArray != NULL)
		{
			for(int i = from; i < to; i++)
			{
				elementAux = ll_get(this, i);
				ll_add(cloneArray, elementAux);
			}
		}
	}
	return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this) {

	return ll_subList(this, 0, ll_len(this));
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order) {

    int returnAux =-1;
    void* auxElement = NULL;
    void* elementI = NULL;
    void* elementJ = NULL;
    int tam = ll_len(this);

    if(this != NULL && pFunc != NULL && order >= 0 && order <= 1)
    {
        for(int i=0; i<tam-1; i++)
        {
            for(int j=i; j<tam; j++)
            {
                elementI = ll_get(this, i);
                elementJ = ll_get(this, j);

                if(((pFunc(elementI, elementJ)) > 0 && order == 1)
                        || ((pFunc(elementI, elementJ)) < 0 && order == 0))
                {
                    auxElement = elementI;
                    ll_set(this, i, elementJ);
                    ll_set(this, j, auxElement);
                }
            }
        }
        returnAux = 0;
    }
    return returnAux;
}


LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*)) {

    LinkedList* listaFiltrada = NULL;
    int len = ll_len(this);

    if(this != NULL && pFunc != NULL)
    {
    	listaFiltrada = ll_newLinkedList();
        if(listaFiltrada != NULL)
        {
            for(int i=0; i<len ; i++)
            {
                if(pFunc(ll_get(this, i)))
                {
                    ll_add(listaFiltrada, ll_get(this, i));
                }
            }
        }
    }
    return listaFiltrada;
}


LinkedList* ll_map(LinkedList* this, void*(*pFunc)(void*)){

    void* auxElement = NULL;
    LinkedList* listaProcesada = NULL;
    int len = ll_len(this);

    if(this!=NULL && pFunc!=NULL)
    {
    	listaProcesada=ll_newLinkedList();
        for(int i=0; i<len ; i++)
        {
        	auxElement=ll_get(this,i); //auxElement va a ir reciendo los pElement iterados en cada nodo
        	auxElement=pFunc(auxElement); // auxElement recibe el return de pFunc con el setter ejecutado
            if(auxElement!=NULL)
            {
                ll_add(listaProcesada,auxElement);
            }
        }
    }
    return listaProcesada; // devuelve lista con la funcion pFunc ejecutada
}

/**
int ll_count(LinkedList* this, int (*fn)(void* element))
La función “ll_count” recibirá una lista y una función criterio “fn”. Se deberá iterar todos los elementos
de la lista y pasárselos a la funcion “fn”. La función “fn” devolverá la cantidad que debe contarse segun
el criterio. La función “ll_count” almacenará un acumulador al cual sumará el valor de retorno de “fn” en
cada iteración. Al finalizar las iteraciones, la función “ll_count” devolverá el valor acumulado.
 */
int ll_count(LinkedList* this, int (*pFunc)(void* element)){

    void* auxElement = NULL;
    int len = ll_len(this);
    int acumulador = 0;

    if(this!=NULL && pFunc!=NULL)
    {
        for(int i=0; i<len ; i++)
        {
        	auxElement = ll_get(this,i); //auxElement va a ir reciendo los pElement iterados en cada nodo
            if(auxElement!=NULL)
            {
            	acumulador += pFunc(auxElement); // auxElement recibe el return de pFunc con el setter ejecutado
            }
        }
    }
    return acumulador; // devuelve cantidad luego de ejecutar pFunc
}




