#include "GroupProductByRevenue.h"

GroupProductByRevenue * create_group_product_by_revenue(char* product, int num_of_sales, double revenue) {
    GroupProductByRevenue * new_group = (GroupProductByRevenue *) malloc(sizeof(GroupProductByRevenue));
    if(new_group == NULL) {
        fprintf(stderr, "Failed to allocate memory for GroupProductByRevenue.\n");
        return NULL;
    }

    strncpy(new_group->product, product, 99);
    new_group->product[99] = '\0';
    new_group->num_of_sales = num_of_sales;
    new_group->revenue = revenue;

    return new_group;
}

void free_group_product_by_revenue(GroupProductByRevenue * group) {
    if (group == NULL) {
        fprintf(stderr, "Group is NULL.\n");
        return;
    }
    free(group);
}

void add_group_product_by_revenue(ListOfGroupProductByRevenue * list, GroupProductByRevenue * group) {
    // Increase the size of the array
    list->nr_of_groups++;
    list->group_product_by_revenue = (GroupProductByRevenue **) realloc(list->group_product_by_revenue, list->nr_of_groups * sizeof(GroupProductByRevenue *));
    
    // Check if the memory allocation was successful
    if(list->group_product_by_revenue == NULL) {
        fprintf(stderr, "Failed to allocate memory for GroupProductByRevenue.\n");
        return;
    }

    // Add the new group to the end of the array
    list->group_product_by_revenue[list->nr_of_groups - 1] = group;
}

void print_group_product_by_revenue(GroupProductByRevenue * group) {
    if(group == NULL) {
        printf("Group is NULL.\n");
        return;
    }

    printf("Product: %s\n", group->product);
    printf("Number of Sales: %d\n", group->num_of_sales);
    printf("Revenue: %.2f\n", group->revenue);
}

void print_list_of_group_product_by_revenue(ListOfGroupProductByRevenue * list) {
    if(list == NULL) {
        printf("List is NULL.\n");
        return;
    }

    printf("Number of Products: %d\n", list->nr_of_groups);
    for(int i = 0; i < list->nr_of_groups; i++) {
        printf("Product %d:\n", i + 1);
        print_group_product_by_revenue(list->group_product_by_revenue[i]);
        printf("\n");
    }
}

ListOfGroupProductByRevenue * create_list_of_group_product_by_revenue() {
    ListOfGroupProductByRevenue * new_list = (ListOfGroupProductByRevenue *) malloc(sizeof(ListOfGroupProductByRevenue));
    if(new_list == NULL) {
        fprintf(stderr, "Failed to allocate memory for ListOfGroupProductByRevenue.\n");
        return NULL;
    }

    new_list->group_product_by_revenue = NULL;
    new_list->nr_of_groups = 0;

    return new_list;
}

GroupProductByRevenue * find_group_product_by_revenue(ListOfGroupProductByRevenue * list, char* product) {
    if(list == NULL || product == NULL) {
        fprintf(stderr, "List or product is NULL.\n");
        return NULL;
    }

    for(int i = 0; i < list->nr_of_groups; i++) {
        GroupProductByRevenue * group = list->group_product_by_revenue[i];
        if(strcmp(group->product, product) == 0) {
            return group;
        }
    }

    return NULL;
}

void populate_group_product_by_revenue(ListOfGroupProductByRevenue * list, SalesList * sales_list) {
    if(list == NULL || sales_list == NULL) {
        fprintf(stderr, "List or SalesList is NULL.\n");
        return;
    }

    for(int i = 0; i < sales_list->num_of_sales; i++) {
        Sale * sale = sales_list->sales[i];
        char* product = sale->product_name;
        double revenue = atof(sale->unit_price) * atoi(sale->sale_quantity);

        GroupProductByRevenue * group = find_group_product_by_revenue(list, product);
        if(group == NULL) {
            group = create_group_product_by_revenue(product, 1, revenue);
            add_group_product_by_revenue(list, group);
        } else {
            group->num_of_sales++;
            group->revenue += revenue;
        }
    }
}

void free_list_of_group_product_by_revenue(ListOfGroupProductByRevenue * list) {
    if(list == NULL) {
        fprintf(stderr, "List is NULL.\n");
        return;
    }

    for(int i = 0; i < list->nr_of_groups; i++) {
        free_group_product_by_revenue(list->group_product_by_revenue[i]);
    }

    free(list->group_product_by_revenue);
    free(list);
}