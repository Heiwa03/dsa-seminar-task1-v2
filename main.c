#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sales.h"
#include "GroupUtil.h"

#define PATH_TO_CSV "./resources/sales.csv"

void open_option_menu (SalesList* sales_list);

int main() {
    SalesList* sales_list = create_sales_list();
    if (sales_list == NULL) {
        return 1;
    }

    populate_sales_list(sales_list, PATH_TO_CSV);

    open_option_menu(sales_list);

    free_sales_list(sales_list);

    return 0;
}

void print_options() {
    printf("1. Find total revenue per each month\n");
    printf("2. Find top 5 products by revenue\n");
    printf("3. Find cities with highest revenue per country\n");
    printf("4. Find standard deviation of revenue per category\n");
    printf("5. Find trend of revenue per subcategory\n");
    printf("6. Exit\n");
}

void open_option_menu (SalesList* sales_list) {
    char input[10];
    int option;
    do {
        print_options();
        printf("Choose an option: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &option);
        switch (option) {
            case 1:
                find_total_revenue_per_each_month(sales_list);
                break;
            case 2:
                find_top_5_products_by_revenue(sales_list);
                break;
            case 3:
                find_cities_with_highest_revenue_per_country(sales_list);
                break;
            case 4:
                standard_deviation_of_revenue_per_category(sales_list);
                break;
            case 5:
                find_trend_of_revenue_per_subcategory(sales_list);
                break;
            case 6:
                break;
            default:
                printf("Invalid option\n");
        }
    } while (option != 6);
}