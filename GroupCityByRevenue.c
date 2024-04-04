#include "GroupCityByRevenue.h"

GroupCityByRevenue * create_group_city_by_revenue(char* city, char* country, int num_of_sales, double revenue) {
    GroupCityByRevenue * new_group = (GroupCityByRevenue *) malloc(sizeof(GroupCityByRevenue));
    if(new_group == NULL) {
        fprintf(stderr, "Failed to allocate memory for GroupCityByRevenue.\n");
        return NULL;
    }

    strncpy(new_group->city, city, 99);
    new_group->city[99] = '\0';
    strncpy(new_group->country, country, 99);
    new_group->country[99] = '\0';
    new_group->num_of_sales = num_of_sales;
    new_group->revenue = revenue;

    return new_group;
}

void free_group_city_by_revenue(GroupCityByRevenue * group) {
    if(group == NULL) {
        fprintf(stderr, "Group is NULL.\n");
        return;
    }

    free(group);
}

void add_group_city_by_revenue(ListOfGroupCityByRevenue * list, GroupCityByRevenue * group) {
    // Increase the size of the array
    list->nr_of_groups++;
    list->group_city_by_revenue = (GroupCityByRevenue **) realloc(list->group_city_by_revenue, list->nr_of_groups * sizeof(GroupCityByRevenue *));
    
    // Check if the memory allocation was successful
    if(list->group_city_by_revenue == NULL) {
        fprintf(stderr, "Failed to allocate memory for GroupCityByRevenue.\n");
        return;
    }

    // Add the new group to the end of the array
    list->group_city_by_revenue[list->nr_of_groups - 1] = group;
}

void print_group_city_by_revenue(GroupCityByRevenue * group) {
    if(group == NULL) {
        printf("Group is NULL.\n");
        return;
    }

    printf("City: %s\n", group->city);
    printf("Country: %s\n", group->country);
    printf("Number of Sales: %d\n", group->num_of_sales);
    printf("Revenue: %.2f\n", group->revenue);
}

void print_list_of_group_city_by_revenue(ListOfGroupCityByRevenue * list) {
    if(list == NULL) {
        printf("List is NULL.\n");
        return;
    }

    printf("Number of Cities: %d\n", list->nr_of_groups);
    for(int i = 0; i < list->nr_of_groups; i++) {
        printf("City %d:\n", i + 1);
        print_group_city_by_revenue(list->group_city_by_revenue[i]);
        printf("\n");
    }
}

ListOfGroupCityByRevenue * create_list_of_group_city_by_revenue() {
    ListOfGroupCityByRevenue * new_list = (ListOfGroupCityByRevenue *) malloc(sizeof(ListOfGroupCityByRevenue));
    if(new_list == NULL) {
        fprintf(stderr, "Failed to allocate memory for ListOfGroupCityByRevenue.\n");
        return NULL;
    }

    new_list->group_city_by_revenue = NULL;
    new_list->nr_of_groups = 0;

    return new_list;
}

GroupCityByRevenue * find_group_city_by_revenue(ListOfGroupCityByRevenue * list, char* city, char* country) {
    if(list == NULL || city == NULL || country == NULL) {
        fprintf(stderr, "List, city or country is NULL.\n");
        return NULL;
    }

    for(int i = 0; i < list->nr_of_groups; i++) {
        GroupCityByRevenue * group = list->group_city_by_revenue[i];
        if(strcmp(group->city, city) == 0 && strcmp(group->country, country) == 0) {
            return group;
        }
    }

    return NULL;
}

void populate_group_city_by_revenue(ListOfGroupCityByRevenue * list, SalesList * sales_list) {
    if(list == NULL || sales_list == NULL) {
        fprintf(stderr, "List or SalesList is NULL.\n");
        return;
    }

    for(int i = 0; i < sales_list->num_of_sales; i++) {
        Sale * sale = sales_list->sales[i];
        char* city = sale->sale_city;
        char* country = sale->sale_country;
        double revenue = atof(sale->unit_price) * atoi(sale->sale_quantity);

        GroupCityByRevenue * group = find_group_city_by_revenue(list, city, country);
        if(group == NULL) {
            group = create_group_city_by_revenue(city, country, 1, revenue);
            add_group_city_by_revenue(list, group);
        } else {
            group->num_of_sales++;
            group->revenue += revenue;
        }
    }
}

void free_list_of_group_city_by_revenue(ListOfGroupCityByRevenue * list) {
    if(list == NULL) {
        fprintf(stderr, "List is NULL.\n");
        return;
    }

    for(int i = 0; i < list->nr_of_groups; i++) {
        free_group_city_by_revenue(list->group_city_by_revenue[i]);
    }

    free(list->group_city_by_revenue);
    free(list);
}