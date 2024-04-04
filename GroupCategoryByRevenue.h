#ifndef GROUP_CATEGORY_BY_REVENUE_H
#define GROUP_CATEGORY_BY_REVENUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sales.h"
#include "math.h"

typedef struct GroupCategoryByRevenue {
    char category[100];
    int num_of_sales;
    double revenue;
} GroupCategoryByRevenue;

typedef struct ListOfGroupCategoryByRevenue {
    GroupCategoryByRevenue ** group_category_by_revenue;
    int nr_of_groups;
} ListOfGroupCategoryByRevenue;

GroupCategoryByRevenue * create_group_category_by_revenue(char* category, int num_of_sales, double revenue);
ListOfGroupCategoryByRevenue * create_list_of_group_category_by_revenue();
void add_group_category_by_revenue(ListOfGroupCategoryByRevenue * list, GroupCategoryByRevenue * group);
void print_group_category_by_revenue(GroupCategoryByRevenue * group);
void print_list_of_group_category_by_revenue(ListOfGroupCategoryByRevenue * list);
void free_group_category_by_revenue(GroupCategoryByRevenue * group);
void populate_group_category_by_revenue(ListOfGroupCategoryByRevenue * list, SalesList * sales_list);
GroupCategoryByRevenue * find_group_category_by_revenue(ListOfGroupCategoryByRevenue * list, char* category);
void populate_group_category_by_revenue(ListOfGroupCategoryByRevenue * list, SalesList * sales_list);
void free_list_of_group_category_by_revenue(ListOfGroupCategoryByRevenue * list);

#endif // GROUP_CATEGORY_BY_REVENUE_H