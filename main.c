#include "general.h"
#include <stdio.h>
#include <time.h>

int main()
{
    srand(time(NULL));
///SENSOR 1
    listadin* lista_1_sensor = simulacion_lectura_n_dias(1200);

    if (lista_1_sensor != NULL){
    queue* cola = mediciones_ordenadas(lista_1_sensor);
    listadin_free_stacks(lista_1_sensor);

    cola->a[24]->temperature = 800; ///MODIFICACION POR ALGUN MOTIVO DE ESE DATO PARA MOSTRAR ERROR SOBRE ESTE SENSOR

    //queue_print(cola);
    printf("el test del sensor 1 dio %d \n",queue_testing(cola));
    queue_free_readings(cola);
    }

///SENSOR 2
    listadin* lista_2_sensor = simulacion_lectura_n_dias(6000);

    if (lista_2_sensor != NULL){
    queue* cola_2 = mediciones_ordenadas(lista_2_sensor);
    listadin_free_stacks(lista_2_sensor);

    printf("el test del sensor 2 dio %d \n",queue_testing(cola_2));
    queue_free_readings(cola_2);
    }

    return 0;
}
