#include "Group.h"

GroupMonthByRevenue * create_group_month_by_revenue(int month, int year, int num_of_sales, double revenue) {
    GroupMonthByRevenue * new_group = (GroupMonthByRevenue *) malloc(sizeof(GroupMonthByRevenue));
    if(new_group == NULL) {
        fprintf(stderr, "Failed to allocate memory for GroupMonthByRevenue.\n");
        return NULL;
    }

    new_group->month = month;
    new_group->year = year;
    new_group->num_of_sales = num_of_sales;
    new_group->revenue = revenue;

    return new_group;
}

void free_group_month_by_revenue(GroupMonthByRevenue * group) {
    if (group == NULL) {
        return;
    }
    free(group);
}

void add_group_month_by_revenue(ListOfGroupMonthByRevenue * list, GroupMonthByRevenue * group) {
    // Increase the size of the array
    list->nr_of_groups++;
    list->group_month_by_revenue = (GroupMonthByRevenue **) realloc(list->group_month_by_revenue, list->nr_of_groups * sizeof(GroupMonthByRevenue *));
    
    // Check if the memory allocation was successful
    if(list->group_month_by_revenue == NULL) {
        fprintf(stderr, "Failed to allocate memory for GroupMonthByRevenue.\n");
        return;
    }

    // Add the new group to the end of the array
    list->group_month_by_revenue[list->nr_of_groups - 1] = group;
}

void print_group_month_by_revenue(GroupMonthByRevenue * group) {
    if(group == NULL) {
        printf("Group is NULL.\n");
        return;
    }

    printf("Month: %d\n", group->month);
    printf("Year: %d\n", group->year);
    printf("Number of Sales: %d\n", group->num_of_sales);
    printf("Revenue: %.2f\n", group->revenue);
}

void print_list_of_group_month_by_revenue(ListOfGroupMonthByRevenue * list) {
    if(list == NULL) {
        printf("List is NULL.\n");
        return;
    }

    printf("Number of Groups: %d\n", list->nr_of_groups);
    for(int i = 0; i < list->nr_of_groups; i++) {
        printf("Group %d:\n", i + 1);
        print_group_month_by_revenue(list->group_month_by_revenue[i]);
        printf("\n");
    }
}

ListOfGroupMonthByRevenue * create_list_of_group_month_by_revenue() {
    ListOfGroupMonthByRevenue * new_list = (ListOfGroupMonthByRevenue *) malloc(sizeof(ListOfGroupMonthByRevenue));
    if(new_list == NULL) {
        fprintf(stderr, "Failed to allocate memory for ListOfGroupMonthByRevenue.\n");
        return NULL;
    }

    new_list->group_month_by_revenue = NULL;
    new_list->nr_of_groups = 0;

    return new_list;
}

GroupMonthByRevenue * find_group_month_by_revenue(ListOfGroupMonthByRevenue * list, int month, int year) {
    if(list == NULL) {
        fprintf(stderr, "List is NULL.\n");
        return NULL;
    }

    for(int i = 0; i < list->nr_of_groups; i++) {
        GroupMonthByRevenue * group = list->group_month_by_revenue[i];
        if(group->month == month && group->year == year) {
            return group;
        }
    }

    return NULL;
}

void populate_group_month_by_revenue(ListOfGroupMonthByRevenue * list, SalesList * sales_list) {
    if(list == NULL || sales_list == NULL) {
        fprintf(stderr, "List or SalesList is NULL.\n");
        return;
    }

    for(int i = 0; i < sales_list->num_of_sales; i++) {
        Sale * sale = sales_list->sales[i];
        int month = get_month_from_date(sale->sale_date);
        int year = get_year_from_date(sale->sale_date);
        double revenue = atof(sale->unit_price) * atoi(sale->sale_quantity);

        GroupMonthByRevenue * group = find_group_month_by_revenue(list, month, year);
        if(group == NULL) {
            group = create_group_month_by_revenue(month, year, 1, revenue);
            add_group_month_by_revenue(list, group);
        } else {
            group->num_of_sales++;
            group->revenue += revenue;
        }
    }
}

void free_list_of_group_month_by_revenue(ListOfGroupMonthByRevenue * list) {
    if(list == NULL) {
        fprintf(stderr, "List is NULL.\n");
        return;
    }

    for(int i = 0; i < list->nr_of_groups; i++) {
        free_group_month_by_revenue(list->group_month_by_revenue[i]);
    }

    free(list->group_month_by_revenue);
    free(list);
}