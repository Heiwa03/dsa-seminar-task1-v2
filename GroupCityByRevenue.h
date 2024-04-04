#ifndef GROUP_CITY_BY_REVENUE_H
#define GROUP_CITY_BY_REVENUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sales.h"

typedef struct GroupCityByRevenue {
    char city[100];
    char country[100];
    int num_of_sales;
    double revenue;
} GroupCityByRevenue;

typedef struct ListOfGroupCityByRevenue {
    GroupCityByRevenue ** group_city_by_revenue;
    int nr_of_groups;
} ListOfGroupCityByRevenue;

GroupCityByRevenue * create_group_city_by_revenue(char* city, char* country, int num_of_sales, double revenue);
ListOfGroupCityByRevenue * create_list_of_group_city_by_revenue();
void add_group_city_by_revenue(ListOfGroupCityByRevenue * list, GroupCityByRevenue * group);
void print_group_city_by_revenue(GroupCityByRevenue * group);
void print_list_of_group_city_by_revenue(ListOfGroupCityByRevenue * list);
void free_group_city_by_revenue(GroupCityByRevenue * group);
void populate_group_city_by_revenue(ListOfGroupCityByRevenue * list, SalesList * sales_list);
GroupCityByRevenue * find_group_city_by_revenue(ListOfGroupCityByRevenue * list, char* city, char* country);
void free_list_of_group_city_by_revenue(ListOfGroupCityByRevenue * list);

#endif // GROUP_CITY_BY_REVENUE_H