#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "weather_utils.h"
#include "array_helpers.h"

int min(int x, int y){
    int r;

    if (x > y){
        r = y;
    }
    else{
        r = x;
    }

    return r;
}

int max (int x, int y){
    int r;
    if(x > y){
        r = x;
    }
    else{
        r = y;
    }
    return r;
}


int min_temp (WeatherTable a) {
    int min_temp = INT_MAX;

    for (unsigned int i = 0u; i < YEARS; i++) {

        for (unsigned int j = 0u; j < MONTHS; j++) {

            for (unsigned int k = 0u; k < DAYS; k++) {

                min_temp = min(min_temp,a[YEARS][MONTHS][DAYS]._min_temp);

            }
        }
    }

    return min_temp;
}

void max_year_temp (WeatherTable a, int output[]) {
    int max_temp = INT_MIN;
   
    for(unsigned int year = 0u; year < YEARS; year++) {

        max_temp = INT_MIN;

        for(unsigned int month = 0u; month < MONTHS; month++){

            for(unsigned int day = 0u; day < DAYS; day++){

                if (max_temp <= a[year][month][day]._max_temp){  

                    max_temp = a[year][month][day]._max_temp; 

                }
            }
        }

        output[year] = max_temp;

    }


}


void max_month_prec_per_year (WeatherTable a,unsigned int output[]) {
    int max_rainfall,rainfall_sum;   
    month_t max_month;
   
    for(unsigned int year = 0u; year < YEARS; year++) { 

        max_rainfall = INT_MAX;

        for(unsigned int month = 0u; month < MONTHS; month++){

        rainfall_sum = 0;
        
            for(unsigned int day = 0u; day < DAYS; day++){

                rainfall_sum = a[year][month][day]._rainfall + rainfall_sum;

            }

        if (max_rainfall <= rainfall_sum) {

            max_month = month;

            } 
        }

        output[year] = max_month;

    }


}