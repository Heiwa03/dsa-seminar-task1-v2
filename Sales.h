#ifndef SALES_H
#define SALES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sale {
    char* sale_date;
    char* product_id;
    char* product_name;
    char* product_category;
    char* product_subcategory;
    char* unit_price;
    char* sale_quantity;
    char* sale_country;
    char* sale_city;
} Sale;

typedef struct SalesList {
    Sale** sales;
    int num_of_sales;
} SalesList;

SalesList* create_sales_list();
void add_sale(SalesList* sales_list, Sale* sale);
void free_sales_list(SalesList* sales_list);
Sale* create_sale(char* sale_date, char* product_id, char* product_name, char* product_category, char* product_subcategory, char* unit_price, char* sale_quantity, char* sale_country, char* sale_city);
void free_sale(Sale* sale);
void populate_sales_list(SalesList* sales_list, char* file_name);
void print_sale(Sale* sale);
void print_sales_list(SalesList* sales_list);

int get_month_from_date(char* date);
int get_year_from_date(char* date);

#endif // SALES_H