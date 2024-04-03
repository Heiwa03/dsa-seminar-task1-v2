#ifndef GROUP_PRODUCT_BY_REVENUE_H
#define GROUP_PRODUCT_BY_REVENUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sales.h"

typedef struct GroupProductByRevenue {
    char product[100];
    int num_of_sales;
    double revenue;
} GroupProductByRevenue;

typedef struct ListOfGroupProductByRevenue {
    GroupProductByRevenue ** group_product_by_revenue;
    int nr_of_groups;
} ListOfGroupProductByRevenue;

GroupProductByRevenue * create_group_product_by_revenue(char* product, int num_of_sales, double revenue);
ListOfGroupProductByRevenue * create_list_of_group_product_by_revenue();
void add_group_product_by_revenue(ListOfGroupProductByRevenue * list, GroupProductByRevenue * group);
void print_group_product_by_revenue(GroupProductByRevenue * group);
void print_list_of_group_product_by_revenue(ListOfGroupProductByRevenue * list);
void free_group_product_by_revenue(GroupProductByRevenue * group);
void populate_group_product_by_revenue(ListOfGroupProductByRevenue * list, SalesList * sales_list);
GroupProductByRevenue * find_group_product_by_revenue(ListOfGroupProductByRevenue * list, char* product);
void populate_group_product_by_revenue(ListOfGroupProductByRevenue * list, SalesList * sales_list);
void free_list_of_group_product_by_revenue(ListOfGroupProductByRevenue * list);

#endif // GROUP_PRODUCT_BY_REVENUE_H