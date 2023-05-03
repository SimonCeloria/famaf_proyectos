#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H
#include "array_helpers.h"



int min_temp (WeatherTable array);
/*
    gets the historical minimum temp
*/

void max_year_temp(WeatherTable array, int output[]);
/*
    gets the max temp by year and returns it in the output[YEARS] array
*/

void max_month_prec_per_year(WeatherTable array, unsigned int output[]);
/*
    gets the mont with max rain by year and returns it in the output[YEARS] array
*/




#endif