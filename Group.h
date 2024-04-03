#ifndef GROUP.H
#define GROUP.H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sales.h"

typedef struct GroupMonthByRevenue {
    int month;
    int year;
    int num_of_sales;
    double revenue;
} GroupMonthByRevenue;

typedef struct GroupProductByRevenue {
    char product[100];
    int num_of_sales;
    double revenue;
} GroupProductByRevenue;

typedef struct GroupCityByRevenue {
    char city[100];
    char country[100];
    int num_of_sales;
    double revenue;
} GroupCityByRevenue;



#endif // GROUP.H