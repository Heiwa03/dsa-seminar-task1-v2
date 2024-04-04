#ifndef GROUP_UTIL_H
#define GROUP_UTIL_H

#include "GroupCityByRevenue.h"
#include "GroupProductByRevenue.h"
#include "GroupMonthByRevenue.h"
#include "Sales.h"

void find_total_revenue_per_each_month(SalesList * sales_list);
void find_top_5_products_by_revenue(SalesList * sales_list);

void _print_compact_list_group_month_by_revenue(ListOfGroupMonthByRevenue * list);
void _print_compact_list_group_product_by_revenue(ListOfGroupProductByRevenue * list);
void _sort_list_of_group_month_by_revenue(ListOfGroupMonthByRevenue * list);
void _sort_list_of_group_product_by_revenue(ListOfGroupProductByRevenue * list);

#endif // GROUP_UTIL_H