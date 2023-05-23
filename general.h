#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "stack_static.h"
#include "arbolb.h"
#include "queue_static.h"

#define t_elem_listadin stack*

typedef struct _listadin
{
    t_elem_listadin valor;
    struct _listadin* siguiente;

} listadin;


listadin* listadin_new();
listadin* simulacion_lectura_n_dias(int dias);
listadin* listadin_get(listadin* lista, int posicion);
void listadin_set_valor(listadin* lista, t_elem_listadin valor);
void listadin_free_stacks(listadin* lista);
int listadin_get_measuring(listadin* una_lista);
int listadin_get_largure(listadin* una_lista);


void simulacion_lectura_individual(reading* p_reading);
int generar_valor_aleatorio(int rango, int origen_intervalo);


stack* simulacion_lectura_1_dia();
stack* stack_duplicate(stack* stack_original);
void stack_free_readings (stack* s_a_lib);


void btn_insert_in_order(btn** arbol, t_elem_btree elem_arbol, int cmp(t_elem_btree, t_elem_btree));
void meter_data_arbol(listadin* una_lista, btn** arbol);
void btn_free2(btn ** node);
void freear_nodos(btn* elem_btn, void* p_algo);
void print_values(btn* node, char* str);


void queue_free_readings(queue* cola);
void queue_print (queue* cola);
queue* mediciones_ordenadas(listadin* lista);
queue* queue_duplicate(queue* cola_original);
void poner_dato_en_cola(btn* elem_btn, void* p_cola);
int queue_testing(queue* cola_a_copiar);


#endif // GENERAL_H_INCLUDED
