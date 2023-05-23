#include "reading.h"

reading* reading_new()
{
    reading* p_reading = malloc (sizeof(reading));
    return p_reading;
}

void reading_set_minute(reading* p_reading, t_elem_reading valor)
{
    p_reading->minute = valor;
}

void reading_set_temperature(reading* p_reading, t_elem_reading valor)
{
    p_reading->temperature = valor;
}

t_elem_reading reading_get_minute(reading* p_reading)
{
    return p_reading->minute;
}

t_elem_reading reading_get_temperature(reading* p_reading)
{
    return p_reading->temperature;
}


/**
* Compara dos lecturas por temperatura
* devuelve el numero de la mayor, la 1 o la 2
* 0 si son iguales
**/
int reading_compare_by_temp(reading* reading1, reading* reading2)
{
    int resultado = 0;

    if(reading1->temperature > reading2->temperature){
        resultado = 1;
    }
    if(reading1->temperature < reading2->temperature){
        resultado = 2;
    }

    return resultado;
}

/**
* Compara dos lecturas por tiempo
* devuelve el numero de la mayor, la 1 o la 2
* 0 si son iguales
**/
int reading_compare_by_time(reading* reading1, reading* reading2)
{
    int resultado = 0;

    if(reading1->minute > reading2->minute){
        resultado = 1;
    }
    if(reading1->minute < reading2->minute){
        resultado = 2;
    }

    return resultado;
}


void reading_free(reading* p_reading){
    free(p_reading);
}
