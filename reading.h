#ifndef READING_H_INCLUDED
#define READING_H_INCLUDED

#define t_elem_reading int
#include <stdlib.h>

typedef struct
{
    int minute;
    int temperature;
} reading;

reading* reading_new();
void reading_set_minute(reading* p_reading, t_elem_reading valor);
void reading_set_temperature(reading* p_reading, t_elem_reading valor);
t_elem_reading reading_get_minute(reading* p_reading);
t_elem_reading reading_get_temperature(reading* p_reading);
int reading_compare_by_temp(reading* reading1, reading* reading2);
int reading_compare_by_time(reading* reading1, reading* reading2);
void reading_free(reading* p_reading);







#endif // READING_H_INCLUDED
