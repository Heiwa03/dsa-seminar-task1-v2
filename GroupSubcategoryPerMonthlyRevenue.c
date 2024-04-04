#include "GroupSubcategoryPerMonthlyRevenue.h"

GroupSubcategoryByMonthlyRevenue * create_group_subcategory_by_monthly_revenue(char* subcategory) {
    GroupSubcategoryByMonthlyRevenue * group = (GroupSubcategoryByMonthlyRevenue *) malloc(sizeof(GroupSubcategoryByMonthlyRevenue));
    strcpy(group->subcategory, subcategory);
    group->list_of_group_month_by_revenue = create_list_of_group_month_by_revenue();
    return group;
}

ListOfGroupSubcategoryByMonthlyRevenue * create_list_of_group_subcategory_by_monthly_revenue() {
    ListOfGroupSubcategoryByMonthlyRevenue * list = (ListOfGroupSubcategoryByMonthlyRevenue *) malloc(sizeof(ListOfGroupSubcategoryByMonthlyRevenue));
    list->group_subcategory_by_monthly_revenue = NULL;
    list->nr_of_groups = 0;
    return list;
}

void add_group_subcategory_by_monthly_revenue(ListOfGroupSubcategoryByMonthlyRevenue * list, GroupSubcategoryByMonthlyRevenue * group) {
    list->nr_of_groups++;
    list->group_subcategory_by_monthly_revenue = (GroupSubcategoryByMonthlyRevenue **) realloc(list->group_subcategory_by_monthly_revenue, list->nr_of_groups * sizeof(GroupSubcategoryByMonthlyRevenue *));
    list->group_subcategory_by_monthly_revenue[list->nr_of_groups - 1] = group;
}

void print_group_subcategory_by_monthly_revenue(GroupSubcategoryByMonthlyRevenue * group) {
    printf("Subcategory: %s\n", group->subcategory);
    _print_compact_list_group_month_by_revenue(group->list_of_group_month_by_revenue);
}

void print_list_of_group_subcategory_by_monthly_revenue(ListOfGroupSubcategoryByMonthlyRevenue * list) {
    for(int i = 0; i < list->nr_of_groups; i++) {
        print_group_subcategory_by_monthly_revenue(list->group_subcategory_by_monthly_revenue[i]);
        printf("\n");
    }
}

void free_group_subcategory_by_monthly_revenue(GroupSubcategoryByMonthlyRevenue * group) {
    free_list_of_group_month_by_revenue(group->list_of_group_month_by_revenue);
    free(group);
}

void free_list_of_group_subcategory_by_monthly_revenue(ListOfGroupSubcategoryByMonthlyRevenue * list) {
    for(int i = 0; i < list->nr_of_groups; i++) {
        free_group_subcategory_by_monthly_revenue(list->group_subcategory_by_monthly_revenue[i]);
    }
    free(list->group_subcategory_by_monthly_revenue);
    free(list);
}

GroupSubcategoryByMonthlyRevenue * find_group_subcategory_by_monthly_revenue(ListOfGroupSubcategoryByMonthlyRevenue * list, char* subcategory) {
    for(int i = 0; i < list->nr_of_groups; i++) {
        if(strcmp(list->group_subcategory_by_monthly_revenue[i]->subcategory, subcategory) == 0) {
            return list->group_subcategory_by_monthly_revenue[i];
        }
    }
    return NULL;
}

void populate_group_subcategory_by_monthly_revenue(ListOfGroupSubcategoryByMonthlyRevenue * list, SalesList * sales_list) {
    for(int i = 0; i < sales_list->num_of_sales; i++) {
        Sale * sale = sales_list->sales[i];
        char* subcategory = sale->product_subcategory;
        double revenue = atof(sale->unit_price) * atoi(sale->sale_quantity);

        // Extract month and year from sale_date
        int month, year;
        sscanf(sale->sale_date, "%d-%d", &year, &month);

        GroupSubcategoryByMonthlyRevenue * group = find_group_subcategory_by_monthly_revenue(list, subcategory);
        if(group == NULL) {
            group = create_group_subcategory_by_monthly_revenue(subcategory);
            add_group_subcategory_by_monthly_revenue(list, group);
        }

        GroupMonthByRevenue * month_group = find_group_month_by_revenue(group->list_of_group_month_by_revenue, month, year);
        if(month_group == NULL) {
            month_group = create_group_month_by_revenue(month, year, 1, revenue);
            add_group_month_by_revenue(group->list_of_group_month_by_revenue, month_group);
        } else {
            month_group->num_of_sales++;
            month_group->revenue += revenue;
        }
    }
    // Sorting the list of groups by year and month
    for(int i = 0; i < list->nr_of_groups; i++) {
        _sort_list_of_group_month_by_revenue(list->group_subcategory_by_monthly_revenue[i]->list_of_group_month_by_revenue);
    }
}

