#ifndef GROUP_MONTH_BY_REVENUE_H
#define GROUP_MONTH_BY_REVENUE_H

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

typedef struct ListOfGroupMonthByRevenue {
    GroupMonthByRevenue ** group_month_by_revenue;
    int nr_of_groups;
} ListOfGroupMonthByRevenue;


GroupMonthByRevenue * create_group_month_by_revenue(int month, int year, int num_of_sales, double revenue);
ListOfGroupMonthByRevenue * create_list_of_group_month_by_revenue();
void add_group_month_by_revenue(ListOfGroupMonthByRevenue * list, GroupMonthByRevenue * group);
void print_group_month_by_revenue(GroupMonthByRevenue * group);
void print_list_of_group_month_by_revenue(ListOfGroupMonthByRevenue * list);
void free_group_month_by_revenue(GroupMonthByRevenue * group);
void populate_group_month_by_revenue(ListOfGroupMonthByRevenue * list, SalesList * sales_list);
GroupMonthByRevenue * find_group_month_by_revenue(ListOfGroupMonthByRevenue * list, int month, int year);
void populate_group_month_by_revenue(ListOfGroupMonthByRevenue * list, SalesList * sales_list);
void free_list_of_group_month_by_revenue(ListOfGroupMonthByRevenue * list);

#endif // GROUP_MONTH_BY_REVENUE_H