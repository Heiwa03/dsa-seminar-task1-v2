#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sales.h"

#define PATH_TO_CSV "./resources/sales.csv"

int main() {
    SalesList* sales_list = create_sales_list();
    if (sales_list == NULL) {
        return 1;
    }

    populate_sales_list(sales_list, PATH_TO_CSV);
    print_sales_list(sales_list);

    free_sales_list(sales_list);

    return 0;
}
