#include "Sales.h"

SalesList* create_sales_list() {
    SalesList* list = (SalesList*)malloc(sizeof(SalesList));
    if (list == NULL) {
        return NULL;
    }

    list->sales = NULL;
    list->num_of_sales = 0;

    return list;
}

Sale* create_sale(char* sale_date, char* product_id, char* product_name, char* product_category, char* product_subcategory, char* unit_price, char* sale_quantity, char* sale_country, char* sale_city) {
    Sale* sale = (Sale*)malloc(sizeof(Sale));
    if (sale == NULL) {
        return NULL;
    }

    sale->sale_date = strdup(sale_date);
    sale->product_id = strdup(product_id);
    sale->product_name = strdup(product_name);
    sale->product_category = strdup(product_category);
    sale->product_subcategory = strdup(product_subcategory);
    sale->unit_price = strdup(unit_price);
    sale->sale_quantity = strdup(sale_quantity);
    sale->sale_country = strdup(sale_country);
    sale->sale_city = strdup(sale_city);

    return sale;
}

void free_sale(Sale* sale) {
    if (sale == NULL) {
        return; 
    }

    free(sale);
}

void free_sales_list(SalesList* sales_list) {
    if (sales_list == NULL) {
        return;
    }

    // Free each sale in the list
    for (int i = 0; i < sales_list->num_of_sales; i++) {
        free_sale(sales_list->sales[i]);
    }

    free(sales_list->sales);
    free(sales_list);
}

void add_sale(SalesList* sales_list, Sale* sale) {
    if (sales_list == NULL || sale == NULL) {
        return; // Nothing to add
    }

    // reallocate for new sale to fit
    sales_list->sales = (Sale**)realloc(sales_list->sales, (sales_list->num_of_sales + 1) * sizeof(Sale*));
    if (sales_list->sales == NULL) {
        return; // memory allocation failed
    }

    // append new sale to the end of the list
    sales_list->sales[sales_list->num_of_sales] = sale;

    // increment num_of_sales
    sales_list->num_of_sales++;
}

void populate_sales_list(SalesList* sales_list, char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return;
    }

    char line[1024];
    // Skip the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        Sale* sale = (Sale*)malloc(sizeof(Sale));
        sscanf(line, "%m[^,],%m[^,],%m[^,],%m[^,],%m[^,],%m[^,],%m[^,],%m[^,],%m[^,]",
               &sale->sale_date, &sale->product_id, &sale->product_name, &sale->product_category, &sale->product_subcategory, &sale->unit_price, &sale->sale_quantity, &sale->sale_country, &sale->sale_city);
        
        // fix the trailing newline character
        sale->sale_city[strcspn(sale->sale_city, "\n")] = 0;
        
        add_sale(sales_list, sale);
    }

    

    fclose(file);
}

void print_sale(Sale* sale) {
    if (sale == NULL) {
        printf("Sale is NULL\n");
        return;
    }

    printf("Sale Date: %s\n", sale->sale_date);
    printf("Product ID: %s\n", sale->product_id);
    printf("Product Name: %s\n", sale->product_name);
    printf("Product Category: %s\n", sale->product_category);
    printf("Product Subcategory: %s\n", sale->product_subcategory);
    printf("Unit Price: %s\n", sale->unit_price);
    printf("Sale Quantity: %s\n", sale->sale_quantity);
    printf("Sale Country: %s\n", sale->sale_country);
    printf("Sale City: %s\n", sale->sale_city);
}

void print_sales_list(SalesList* sales_list) {
    if (sales_list == NULL) {
        printf("Sales list is NULL\n");
        return;
    }

    for (int i = 0; i < sales_list->num_of_sales; i++) {
        printf("Sale %d:\n", i + 1);
        print_sale(sales_list->sales[i]);
        printf("\n");
    }
}