#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sales.h"
#include "GroupUtil.h"

#define PATH_TO_CSV "./resources/sales.csv"

int main() {
    SalesList* sales_list = create_sales_list();
    if (sales_list == NULL) {
        return 1;
    }

    populate_sales_list(sales_list, PATH_TO_CSV);
    //print_sales_list(sales_list);
    //find_total_revenue_per_each_month(sales_list);
    //find_top_5_products_by_revenue(sales_list);
    //find_cities_with_highest_revenue_per_country(sales_list);
    //standard_deviation_of_revenue_per_category(sales_list);

    ListOfGroupSubcategoryByMonthlyRevenue* list_of_groups = create_list_of_group_subcategory_by_monthly_revenue();
    if (list_of_groups == NULL) {
        free_sales_list(sales_list);
        return 1;
    }

    populate_group_subcategory_by_monthly_revenue(list_of_groups, sales_list);
    print_list_of_group_subcategory_by_monthly_revenue(list_of_groups);

    free_list_of_group_subcategory_by_monthly_revenue(list_of_groups);


    /*
    ListOfGroupCategoryByRevenue* list_of_groups = create_list_of_group_category_by_revenue();
    if (list_of_groups == NULL) {
        free_sales_list(sales_list);
        return 1;
    }

    populate_group_category_by_revenue(list_of_groups, sales_list);
    print_list_of_group_category_by_revenue(list_of_groups);

    free_list_of_group_category_by_revenue(list_of_groups);
    */
    /*
    ListOfGroupMonthByRevenue* list_of_groups = create_list_of_group_month_by_revenue();
    if (list_of_groups == NULL) {
        free_sales_list(sales_list);
        return 1;
    }
    
    populate_group_month_by_revenue(list_of_groups, sales_list);
    print_list_of_group_month_by_revenue(list_of_groups);

    free_list_of_group_month_by_revenue(list_of_groups);
    */

    /*
    ListOfGroupProductByRevenue* list_of_groups = create_list_of_group_product_by_revenue();
    if (list_of_groups == NULL) {
        free_sales_list(sales_list);
        return 1;
    }

    populate_group_product_by_revenue(list_of_groups, sales_list);
    print_list_of_group_product_by_revenue(list_of_groups);

    free_list_of_group_product_by_revenue(list_of_groups);
    */

    /*
    ListOfGroupCityByRevenue* list_of_groups = create_list_of_group_city_by_revenue();
    if (list_of_groups == NULL) {
        free_sales_list(sales_list);
        return 1;
    }

    populate_group_city_by_revenue(list_of_groups, sales_list);
    print_list_of_group_city_by_revenue(list_of_groups);

    free_list_of_group_city_by_revenue(list_of_groups);
    */

    free_sales_list(sales_list);

    return 0;
}
