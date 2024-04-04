#include "GroupUtil.h"

// Compact form of printing the resulting group 
// Useful for textual reports and the fucking terminal line limit that can kiss my fucking ass
void _print_compact_list_group_month_by_revenue(ListOfGroupMonthByRevenue * list) {
    if(list == NULL) {
        printf("List is NULL.\n");
        return;
    }

    printf("Number of Groups: %d\n", list->nr_of_groups);
    for(int i = 0; i < list->nr_of_groups; i++) {
        GroupMonthByRevenue * group = list->group_month_by_revenue[i];
        if(group == NULL) {
            printf("Group %d is NULL.\n", i + 1);
            continue;
        }

        printf("Group %d: Month: %d, Year: %d, Number of Sales: %d, Revenue: %.2f\n", 
               i + 1, group->month, group->year, group->num_of_sales, group->revenue);
    }
}

// Sorts the month group by date (year and month)
void _sort_list_of_group_month_by_revenue(ListOfGroupMonthByRevenue * list) {
    if(list == NULL) {
        printf("List is NULL.\n");
        return;
    }

    for(int i = 0; i < list->nr_of_groups; i++) {
        for(int j = i + 1; j < list->nr_of_groups; j++) {
            // Compare year and month values
            if(list->group_month_by_revenue[i]->year > list->group_month_by_revenue[j]->year ||
               (list->group_month_by_revenue[i]->year == list->group_month_by_revenue[j]->year &&
                list->group_month_by_revenue[i]->month > list->group_month_by_revenue[j]->month)) {
                GroupMonthByRevenue * temp = list->group_month_by_revenue[i];
                list->group_month_by_revenue[i] = list->group_month_by_revenue[j];
                list->group_month_by_revenue[j] = temp;
            }
        }
    }
}

// Answer to BQ1 - Find the total revenue per each month
void find_total_revenue_per_each_month(SalesList * sales_list) {
    ListOfGroupMonthByRevenue* list_of_groups = create_list_of_group_month_by_revenue();
    if (list_of_groups == NULL) {
        printf("Error creating list of groups.\n");
        free_sales_list(sales_list);
        return;
    }
    
    populate_group_month_by_revenue(list_of_groups, sales_list);
    
    _sort_list_of_group_month_by_revenue(list_of_groups);

    _print_compact_list_group_month_by_revenue(list_of_groups);
    char * user_input;
    printf("Do you want to save the results to a file? (yes/no): ");
    scanf("%s", user_input);
    if(!strcmp(user_input, "yes")) {
        char * file_name;
        printf("Enter the file name: ");
        scanf("%s", file_name);
        FILE * file = fopen(file_name, "w");
        if(file == NULL) {
            printf("Error opening file.\n");
            return;
        }
        for(int i = 0; i < list_of_groups->nr_of_groups; i++) {
            GroupMonthByRevenue * group = list_of_groups->group_month_by_revenue[i];
            fprintf(file, "%d: Year: %d, Month: %d, Number of Sales: %d, Revenue: %.2f\n", 
                    i + 1, group->year, group->month, group->num_of_sales, group->revenue);
        }
        fclose(file);
    }

    free_list_of_group_month_by_revenue(list_of_groups);
}

void find_top_5_products_by_revenue(SalesList * sales_list) {
    ListOfGroupProductByRevenue* list_of_groups = create_list_of_group_product_by_revenue();
    if (list_of_groups == NULL) {
        printf("Error creating list of groups.\n");
        free_sales_list(sales_list);
        return;
    }
    
    populate_group_product_by_revenue(list_of_groups, sales_list);
    
    _sort_list_of_group_product_by_revenue(list_of_groups);

    _print_compact_list_group_product_by_revenue(list_of_groups);
    char * user_input;
    printf("Do you want to save the results to a file? (yes/no): ");
    scanf("%s", user_input);
    if(!strcmp(user_input, "yes")) {
        char * file_name;
        printf("Enter the file name: ");
        scanf("%s", file_name);
        FILE * file = fopen(file_name, "w");
        if(file == NULL) {
            printf("Error opening file.\n");
            return;
        }
        for(int index = 0; index < 5; index++) {
            GroupProductByRevenue * group = list_of_groups->group_product_by_revenue[index];
            fprintf(file, "%d: Product: %s, Number of Sales: %d, Revenue: %.2f\n", 
                    index + 1, group->product, group->num_of_sales, group->revenue);
        }
        fclose(file);
    }

    free_list_of_group_product_by_revenue(list_of_groups);
}

void _print_compact_list_group_product_by_revenue(ListOfGroupProductByRevenue * list) {
    if(list == NULL) {
        printf("List is NULL.\n");
        return;
    }

    printf("Number of Groups: %d\n", list->nr_of_groups);
    for(int i = 0; i < 5; i++) {
        GroupProductByRevenue * group = list->group_product_by_revenue[i];
        if(group == NULL) {
            printf("Group %d is NULL.\n", i + 1);
            continue;
        }

        printf("%d: Product: %s, Number of Sales: %d, Revenue: %.2f\n", 
               i + 1, group->product, group->num_of_sales, group->revenue);
    }
}

void _sort_list_of_group_product_by_revenue(ListOfGroupProductByRevenue * list) {
    if(list == NULL) {
        printf("List is NULL.\n");
        return;
    }

    for(int i = 0; i < list->nr_of_groups; i++) {
        for(int j = i + 1; j < list->nr_of_groups; j++) {
            // Compare revenues
            if(list->group_product_by_revenue[i]->revenue < list->group_product_by_revenue[j]->revenue) {
                GroupProductByRevenue * temp = list->group_product_by_revenue[i];
                list->group_product_by_revenue[i] = list->group_product_by_revenue[j];
                list->group_product_by_revenue[j] = temp;
            }
        }
    }
}
