#ifndef GROUP_SUBCATEGORY_PER_MONTHLY_REVENUE_H
#define GROUP_SUBCATEGORY_PER_MONTHLY_REVENUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Sales.h"
#include "GroupMonthByRevenue.h"
#include "GroupUtil.h"

typedef struct GroupSubcategoryByMonthlyRevenue {
    char subcategory[100];
    ListOfGroupMonthByRevenue * list_of_group_month_by_revenue;
} GroupSubcategoryByMonthlyRevenue;

typedef struct ListOfGroupSubcategoryByMonthlyRevenue {
    GroupSubcategoryByMonthlyRevenue ** group_subcategory_by_monthly_revenue;
    int nr_of_groups;
} ListOfGroupSubcategoryByMonthlyRevenue;

GroupSubcategoryByMonthlyRevenue * create_group_subcategory_by_monthly_revenue(char* subcategory);
ListOfGroupSubcategoryByMonthlyRevenue * create_list_of_group_subcategory_by_monthly_revenue();
void add_group_subcategory_by_monthly_revenue(ListOfGroupSubcategoryByMonthlyRevenue * list, GroupSubcategoryByMonthlyRevenue * group);
void print_group_subcategory_by_monthly_revenue(GroupSubcategoryByMonthlyRevenue * group);
void print_list_of_group_subcategory_by_monthly_revenue(ListOfGroupSubcategoryByMonthlyRevenue * list);
void free_group_subcategory_by_monthly_revenue(GroupSubcategoryByMonthlyRevenue * group);
void populate_group_subcategory_by_monthly_revenue(ListOfGroupSubcategoryByMonthlyRevenue * list, SalesList * sales_list);
GroupSubcategoryByMonthlyRevenue * find_group_subcategory_by_monthly_revenue(ListOfGroupSubcategoryByMonthlyRevenue * list, char* subcategory);
void free_list_of_group_subcategory_by_monthly_revenue(ListOfGroupSubcategoryByMonthlyRevenue * list);

#endif // GROUP_SUBCATEGORY_PER_MONTHLY_REVENUE_H