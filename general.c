#include "general.h"


/**
*   Crea una lista dinamica (inicio o nodo)
*/
listadin* listadin_new()
{
    listadin* lista = malloc(sizeof(listadin));

    lista->siguiente = NULL;
    lista->valor = NULL;

    return lista;
}

/**
*   Setea un valor nuevo al final de la lista, con el valor que se le pasa
*/
void listadin_set_valor(listadin* lista, t_elem_listadin valor)
{
    if(lista->valor == NULL)
    {
        lista->valor = valor;
        return;
    }
    while( lista->siguiente != NULL)
    {
        lista = lista->siguiente;
    }
    lista->siguiente = listadin_new();  ///donde era el fin agrego un nodo y le asigno los valor nuevo
    lista->siguiente->valor = valor;
}

/**
* recorre la lista, buscando la posicion que se le indica por parametro
* De encontrarla retorta un puntero a esa posicion, sino NULL
*/
listadin* listadin_get(listadin* lista, int posicion)
{
    listadin* resultado = NULL;
    int contador = 0;

    while( contador < posicion && (lista != NULL && lista->siguiente!=NULL)) ///si no llegue a la posicion
    {                                                               ///la lista no es nula y no veo el final
        lista = lista->siguiente;
        contador++;
    }
    if (lista != NULL && contador == posicion)  ///si la lista no esta vacia y llegue a la posicion
    {
        resultado = lista; ///lo encontre
    }

    return resultado;
}

/**
* Simulo una lectura individual, a donde apunta la medicion le asigno un valor aleatorio tanto de minuto como temp
*/
void simulacion_lectura_individual(reading* p_reading)
{
    reading_set_minute(p_reading, generar_valor_aleatorio(1440,0));
    reading_set_temperature(p_reading, generar_valor_aleatorio(50,-10));
}

/**
* Devuelve un stack con simulaciones individuales de las lecturas diarias
*/
stack* simulacion_lectura_1_dia()
{
    int lecturas_diarias = generar_valor_aleatorio(1440,1); ///para cada dia leer diferentes cantidades, de 1 med a 1440(todo el dia)
    stack* p_stack = stack_new(lecturas_diarias);

    if (p_stack != NULL)
    {
        while(!stack_isfull(p_stack))
        {
            reading* lectura = reading_new();
            if (lectura!= NULL)
            {
                simulacion_lectura_individual(lectura);
                push(p_stack,lectura);
            }
        }
    }

    return p_stack;
}

listadin* simulacion_lectura_n_dias(int dias)
{

    listadin* resultado = listadin_new();
    stack* undia = NULL;
    int repeticiones = 0;

    if (resultado != NULL)
    {
        while(dias>0 && repeticiones<dias)
        {
            undia = simulacion_lectura_1_dia(); ///simulo 1 dia de lectura
            if(undia != NULL)                   ///mientras no sea NULL, agrego al listado de dias
            {
                listadin_set_valor(resultado, undia);   ///asigno un puntero al dia en la ultima posicion de la lista
                repeticiones++;
            }
        }
    }

    return resultado;
}


/**
* genera un valor aleatorio y lo devuelve, dentro de un rango que se le indica, el otro parametro es para mover el rango
* Ej = rango:20 origen:-10 (0,20) desplazado -10 => (-10,10)
*/
int generar_valor_aleatorio(int rango, int origen_intervalo)
{
    int numero = rand() % (rango+1) + origen_intervalo;
    return numero;
}

/**
* Libero un stack, primero borrando sus readings
*/
void stack_free_readings (stack* s_a_lib){

    reading* aux = NULL;

    while(!stack_isempty(s_a_lib)){
        aux = pop(s_a_lib);
        reading_free(aux);
    }

    stack_free(s_a_lib);

}

/**
* Duplica una queue
*/
queue* queue_duplicate(queue* cola_original)
{
    queue* aux_queue_result = queue_new(queue_getmaxsize(cola_original));
    queue* aux_queue_1 = queue_new(queue_getmaxsize(cola_original));

    if( aux_queue_result== NULL || aux_queue_1== NULL)
    {
        return NULL;
    }

    reading* aux_reading = NULL;

    while (!queue_isempty(cola_original))
    {
        aux_reading = dequeue(cola_original);
        enqueue(aux_queue_result, aux_reading);
        enqueue(aux_queue_1, aux_reading);
    }


    while (!queue_isempty(aux_queue_1))
    {
        aux_reading = dequeue(aux_queue_1);
        enqueue(cola_original, aux_reading);
    }

    queue_free(aux_queue_1);

    return aux_queue_result;
}

/**
* Duplica un stack
*/
stack* stack_duplicate(stack* stack_original)
{
    stack* aux_stack_result = stack_new(stack_getmaxsize(stack_original));
    stack* aux_stack_1 = stack_new(stack_getmaxsize(stack_original));
    if( aux_stack_result == NULL || aux_stack_1 == NULL)
    {
        return NULL;
    }

    reading* aux_reading = NULL;

    while (!stack_isempty(stack_original))
    {
        aux_reading = pop(stack_original);
        push(aux_stack_result, aux_reading);
        push(aux_stack_1, aux_reading);
    }

    while (!stack_isempty(aux_stack_1))
    {
        aux_reading = pop(aux_stack_1);
        push(stack_original, aux_reading);
    }

    stack_free(aux_stack_1);

    return aux_stack_result;
}

/**
* testea la queue a ver si las mediciones previas son menores a las siguientes
*/
int queue_testing(queue* cola_a_copiar)
{
    if(cola_a_copiar == NULL || queue_isempty(cola_a_copiar))
    {
        return 0;
    }
    queue* cola = queue_duplicate(cola_a_copiar);

    reading* aux_reading = NULL;
    t_elem_reading aux_elem_reading_1_min;  ///descomposicion de elemento anterior
    t_elem_reading aux_elem_reading_1_temp;

    t_elem_reading aux_elem_reading_2_min;  ///descomposicion de elemento siguiente
    t_elem_reading aux_elem_reading_2_temp;

    int todo_bien = 1;
    aux_elem_reading_1_min = peek(cola)->minute;             ///inicializo anterior para la primer comparacion
    aux_elem_reading_1_temp = peek(cola)->temperature-1;     ///-1 para que sea coherente que la primer medicion será menor a ella misma

    while(!queue_isempty(cola) && todo_bien == 1)   ///mientras la cola no este vacia y todo este bien
    {
        aux_reading = dequeue(cola);

        aux_elem_reading_2_min = aux_reading->minute;       ///descompongo un elemento
        aux_elem_reading_2_temp = aux_reading->temperature;

        if(aux_elem_reading_1_min>aux_elem_reading_2_min)   ///lo comparo con su medicion anterior de tiempo
        {
            todo_bien = 0;
        }
        if (aux_elem_reading_1_min==aux_elem_reading_2_min) ///si son iguales, el tiempo del anterior debe ser menor
        {
            if(aux_elem_reading_1_temp>aux_elem_reading_2_temp)
            {
                todo_bien = 0;
            }
        }
        aux_elem_reading_1_min = aux_elem_reading_2_min;
        aux_elem_reading_1_temp = aux_elem_reading_2_temp;

    }

    queue_free(cola);

    return todo_bien;
}

/**
*   funcion que imprime el valor de un nodo. Usada como parametro en
*/
void print_values(btn* node, char* str)
{
    sprintf(str, "   min:%d temp:%d   ", node->value->minute, node->value->temperature);  // Usamos sprintf para convertir el entero a una cadena
}

/**
*   Obtengo la largura de la lista
*/
int listadin_get_largure(listadin* una_lista)
{
    int contador = 0;
    while(una_lista != NULL)
    {
        contador++;
        una_lista = una_lista->siguiente;
    }
    return contador;
}

/**
*   Obtengo la cantidad de mediciones que tiene la lista
*/
int listadin_get_measuring(listadin* una_lista)
{

    long contador = 0;
    stack* aux = NULL;
    while(una_lista != NULL)
    {
        aux = una_lista->valor;

        contador = contador + stack_getsize(aux);
        una_lista = una_lista->siguiente;
    }
    return contador;
}

/**
*   meto los datos de la lista en el arbol
*/
void meter_data_arbol(listadin* una_lista, btn** arbol)
{
    int cant = listadin_get_largure(una_lista);
    listadin* listaaux;
    stack* auxstack;
    reading* aux;

    for(int i=0; i<cant; i++)
    {
        listaaux = listadin_get(una_lista,i);

        if(listaaux != NULL)
        {
            auxstack = stack_duplicate(listaaux->valor);

            while( stack_isempty(auxstack) ==0 )
            {
                aux = pop(auxstack);
                btn_insert_in_order(arbol, aux, reading_compare_by_time);
            }

            stack_free(auxstack);
        }
    }

}


/**
*   Funcion que inserta in order para poder recorrerla despues y obtener los datos ordenados
*   LA FUNCION DE COMPARACION QUE SE LE INGRESE DEBE:
*   Devolver que elemento es mas grande 1 o 2, 0 si son iguales
*/
void btn_insert_in_order(btn** arbol, t_elem_btree elem_arbol, int cmp(t_elem_btree, t_elem_btree))
{

    if(*arbol == NULL)
    {
        *arbol = btn_new(elem_arbol);
        return ;
    }

    int comparacion = cmp((*arbol)->value, elem_arbol);
    if (comparacion == 1)                    ///si es mayor el valor a donde apunta arbol
    {
        btn_insert_in_order(&(*arbol)->left, elem_arbol, cmp);
    }
    if (comparacion == 2)                   ///si es mayor el elemento a poner
    {
        btn_insert_in_order(&(*arbol)->right, elem_arbol, cmp);
    }
    if (comparacion == 0)                   ///si son iguales
    {
        int comparacion_2 = reading_compare_by_temp((*arbol)->value, elem_arbol);///hago una 2 comparacion
        if (comparacion_2 == 1)             ///si es mayor a donde apunta arbol
        {
            ///CRITERIO SIGUIENTE TENIENDO EN CUENTA QUE SE RECORRE INORDER
            btn_insert_in_order(&(*arbol)->left, elem_arbol, cmp);  ///para que aparezca el mas chico primero
        }
        if (comparacion_2 == 2)                                     ///para que aparezca el mas chico primero
        {
            btn_insert_in_order(&(*arbol)->right, elem_arbol, cmp);
        }
    }
    return;
}

/**
* Usada en mediciones ordenadas
*/
void poner_dato_en_cola(btn* elem_btn, void* p_cola)
{
    enqueue((queue*)p_cola, elem_btn->value);
}

/**
*   Libera los stacks que hay en la lista y por ultimo la lista
*/
void listadin_free_stacks(listadin* lista){

    while(lista != NULL)            ///libero solo los stacks ya que los punteros a mediciones accedo desde la cola
    {
        stack_free(lista->valor);
        lista = lista->siguiente;
    }
    free(lista);
}

/**
*   Funcion que ordena las mediciones
*/
queue* mediciones_ordenadas(listadin* lista)
{

    btn* arbolb = NULL;
    meter_data_arbol(lista, &arbolb);
    int cantidad_mediciones = listadin_get_measuring(lista);

    queue* datos_ordenados = queue_new((cantidad_mediciones));  ///crea una cola con la cantidad de mediciones
    if (datos_ordenados != NULL)
    {
        btn_inorder(arbolb,poner_dato_en_cola,datos_ordenados);
    }

    //btn_free(&arbolb); /// POR QUE ESTA OPCION NO FUNCIONA?????
    btn_free2(&arbolb); ///solo elimino nodos, ya que las direcciones de las mediciones se pueden acceder de la lista

    return datos_ordenados;
}


void queue_print (queue* cola)
{

    queue* duplicado = queue_duplicate(cola);

    while(!queue_isempty(duplicado))
    {
        reading* aux = dequeue(duplicado);
        printf("min %d   temp %d\n",aux->minute, aux->temperature);
    }

    queue_free(duplicado);

}

/**
* libera las mediciones que hay en la cola
*/
void queue_free_readings(queue* cola){

    while(!queue_isempty(cola))
    {
        reading* aux = dequeue(cola);
        reading_free(aux);
    }
    queue_free(cola);

}

///Otra manera que probe y al parecer funciona pero no estoy seguro
/**
*   funcion utilizada en free_2
*/
void freear_nodos(btn* elem_btn, void* p_algo){
    free(elem_btn);
}

/**
*   en postorder para ir del piso hasta arriba libero las conexiones
*/
void btn_free2(btn ** node){
    btn_postorder(*node,freear_nodos, NULL);
}
