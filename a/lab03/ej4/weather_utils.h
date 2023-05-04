#ifdef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H
#include "array_helpers.h"

int min_temp_year (WatherTable a);
 // Gets the historical minimum temp.

void max_temp_year (WeatherTable a, int output[YEARS]);
 // Gets the hmax temo by year and returns it in the output[YEARS] array.

void max_month_prec_year (WeathrtTable a, unsigned int output[]):
 // Gets the month with max rain by year and returns it in the output[YEARS] array.

#endif