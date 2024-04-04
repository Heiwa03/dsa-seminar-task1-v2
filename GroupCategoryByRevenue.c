#include "GroupCategoryByRevenue.h"

GroupCategoryByRevenue * create_group_category_by_revenue(char* category, int num_of_sales, double revenue) {
    GroupCategoryByRevenue * group = (GroupCategoryByRevenue *) malloc(sizeof(GroupCategoryByRevenue));
    strcpy(group->category, category);
    group->num_of_sales = num_of_sales;
    group->revenue = revenue;
    return group;
}

ListOfGroupCategoryByRevenue * create_list_of_group_category_by_revenue() {
    ListOfGroupCategoryByRevenue * list = (ListOfGroupCategoryByRevenue *) malloc(sizeof(ListOfGroupCategoryByRevenue));
    list->group_category_by_revenue = NULL;
    list->nr_of_groups = 0;
    return list;
}

void add_group_category_by_revenue(ListOfGroupCategoryByRevenue * list, GroupCategoryByRevenue * group) {
    list->nr_of_groups++;
    list->group_category_by_revenue = (GroupCategoryByRevenue **) realloc(list->group_category_by_revenue, list->nr_of_groups * sizeof(GroupCategoryByRevenue *));
    list->group_category_by_revenue[list->nr_of_groups - 1] = group;
}

void print_group_category_by_revenue(GroupCategoryByRevenue * group) {
    printf("Category: %s, Number of Sales: %d, Revenue: %.2f\n", group->category, group->num_of_sales, group->revenue);
}

void print_list_of_group_category_by_revenue(ListOfGroupCategoryByRevenue * list) {
    for(int i = 0; i < list->nr_of_groups; i++) {
        print_group_category_by_revenue(list->group_category_by_revenue[i]);
    }
}

void free_group_category_by_revenue(GroupCategoryByRevenue * group) {
    if (group == NULL) {
        fprintf(stderr, "Group is NULL.\n");
        return;
    }
    free(group);
}

GroupCategoryByRevenue * find_group_category_by_revenue(ListOfGroupCategoryByRevenue * list, char* category) {
    for(int i = 0; i < list->nr_of_groups; i++) {
        if(strcmp(list->group_category_by_revenue[i]->category, category) == 0) {
            return list->group_category_by_revenue[i];
        }
    }
    return NULL;
}

void populate_group_category_by_revenue(ListOfGroupCategoryByRevenue * list, SalesList * sales_list) {
    for(int i = 0; i < sales_list->num_of_sales; i++) {
        Sale * sale = sales_list->sales[i];
        char* category = sale->product_category;
        double revenue = atof(sale->unit_price) * atoi(sale->sale_quantity);

        GroupCategoryByRevenue * group = find_group_category_by_revenue(list, category);
        if(group == NULL) {
            group = create_group_category_by_revenue(category, 1, revenue);
            add_group_category_by_revenue(list, group);
        } else {
            group->num_of_sales++;
            group->revenue += revenue;
        }
    }
}

void free_list_of_group_category_by_revenue(ListOfGroupCategoryByRevenue * list) {
    if (list == NULL) {
        fprintf(stderr, "List is NULL.\n");
        return;
    }
    for(int i = 0; i < list->nr_of_groups; i++) {
        free_group_category_by_revenue(list->group_category_by_revenue[i]);
    }
    free(list->group_category_by_revenue);
    free(list);
}