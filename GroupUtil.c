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

char * _get_user_option () {
    char user_input[10];
    printf("Do you want to save the results to a file? (yes/no): ");
    fgets(user_input, sizeof(user_input), stdin);
    strtok(user_input, "\n"); // remove newline character
    if(!strcmp(user_input, "yes")) {
        char file_name[50];
        printf("Enter the file name: ");
        fgets(file_name, sizeof(file_name), stdin);
        strtok(file_name, "\n"); // remove newline character
        return strdup(file_name);
    }
    return NULL;
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
    FILE * file = fopen(_get_user_option(), "w");
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
    char user_input[10];
    printf("Do you want to save the results to a file? (yes/no): ");
    fgets(user_input, sizeof(user_input), stdin);
    strtok(user_input, "\n"); // remove newline character
    if(!strcmp(user_input, "yes")) {
        char file_name[50];
        printf("Enter the file name: ");
        fgets(file_name, sizeof(file_name), stdin);
        strtok(file_name, "\n"); // remove newline character
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

void find_cities_with_highest_revenue_per_country(SalesList * sales_list) {
    ListOfGroupCityByRevenue* list_of_groups = create_list_of_group_city_by_revenue();
    if (list_of_groups == NULL) {
        printf("Error creating list of groups.\n");
        free_sales_list(sales_list);
        return;
    }
    
    populate_group_city_by_revenue(list_of_groups, sales_list);
    
    _sort_list_of_group_city_by_revenue(list_of_groups);

    _print_compact_list_group_city_by_revenue(list_of_groups);
    char user_input[10];
    printf("Do you want to save the results to a file? (yes/no): ");
    fgets(user_input, sizeof(user_input), stdin);
    strtok(user_input, "\n"); // remove newline character
    if(!strcmp(user_input, "yes")) {
        char file_name[50];
        printf("Enter the file name: ");
        fgets(file_name, sizeof(file_name), stdin);
        strtok(file_name, "\n"); // remove newline character
        FILE * file = fopen(file_name, "w");
        if(file == NULL) {
            printf("Error opening file.\n");
            return;
        }
        for(int i = 0; i < list_of_groups->nr_of_groups; i++) {
            GroupCityByRevenue * group = list_of_groups->group_city_by_revenue[i];
            fprintf(file, "%d: City: %s, Country: %s, Number of Sales: %d, Revenue: %.2f\n", 
                    i + 1, group->city, group->country, group->num_of_sales, group->revenue);
        }
        fclose(file);
    }

    free_list_of_group_city_by_revenue(list_of_groups);
}

void _print_compact_list_group_city_by_revenue(ListOfGroupCityByRevenue * list) {
    if(list == NULL) {
        printf("List is NULL.\n");
        return;
    }

    printf("Number of Groups: %d\n", list->nr_of_groups);
    for(int i = 0; i < list->nr_of_groups; i++) {
        GroupCityByRevenue * group = list->group_city_by_revenue[i];
        if(group == NULL) {
            printf("Group %d is NULL.\n", i + 1);
            continue;
        }

        printf("%d: Country: %s, City: %s, Number of Sales: %d, Revenue: %.2f\n", 
               i + 1, group->country, group->city, group->num_of_sales, group->revenue);
    }
}

void _sort_list_of_group_city_by_revenue(ListOfGroupCityByRevenue * list) {
    if(list == NULL) {
        printf("List is NULL.\n");
        return;
    }

    for(int i = 0; i < list->nr_of_groups; i++) {
        for(int j = i + 1; j < list->nr_of_groups; j++) {
            // Compare countries
            int countryComparison = strcmp(list->group_city_by_revenue[i]->country, list->group_city_by_revenue[j]->country);
            if (countryComparison > 0 || (countryComparison == 0 && list->group_city_by_revenue[i]->revenue < list->group_city_by_revenue[j]->revenue)) {
                GroupCityByRevenue * temp = list->group_city_by_revenue[i];
                list->group_city_by_revenue[i] = list->group_city_by_revenue[j];
                list->group_city_by_revenue[j] = temp;
            }
        }
    }
}

float _compute_mean_revenue_per_category (SalesList * sales_list, ListOfGroupCategoryByRevenue * list_of_groups) {
    double sum = 0;
    for(int i = 0; i < list_of_groups->nr_of_groups; i++) {
        GroupCategoryByRevenue * group = list_of_groups->group_category_by_revenue[i];
        sum += group->revenue;
    }
    double mean = sum / list_of_groups->nr_of_groups;
    return mean;
}

float _compute_standard_deviation_per_category (SalesList * sales_list, ListOfGroupCategoryByRevenue * list_of_groups, float mean) {
    double sum_of_squares = 0;
    for(int i = 0; i < list_of_groups->nr_of_groups; i++) {
        GroupCategoryByRevenue * group = list_of_groups->group_category_by_revenue[i];
        sum_of_squares += pow(group->revenue - mean, 2);
    }
    double standard_deviation = sqrt(sum_of_squares / list_of_groups->nr_of_groups);
    return standard_deviation;
}

void standard_deviation_of_revenue_per_category (SalesList * sales_list) {
    ListOfGroupCategoryByRevenue* list_of_groups = create_list_of_group_category_by_revenue();
    if (list_of_groups == NULL) {
        printf("Error creating list of groups.\n");
        free_sales_list(sales_list);
        return;
    }
    
    populate_group_category_by_revenue(list_of_groups, sales_list);
    
    double mean = _compute_mean_revenue_per_category(sales_list, list_of_groups);
    double standard_deviation = _compute_standard_deviation_per_category(sales_list, list_of_groups, mean);
    
    printf("Standard Deviation of Revenue per Category: %.2f\n", standard_deviation);
    printf("Mean Revenue per Category: %.2f\n", mean);

    char user_input[10];
    printf("Do you want to save the results to a file? (yes/no): ");
    fgets(user_input, sizeof(user_input), stdin);
    strtok(user_input, "\n"); // remove newline character
    if(!strcmp(user_input, "yes")) {
        char file_name[50];
        printf("Enter the file name: ");
        fgets(file_name, sizeof(file_name), stdin);
        strtok(file_name, "\n"); // remove newline character
        FILE * file = fopen(file_name, "w");
        if(file == NULL) {
            printf("Error opening file.\n");
            return;
        }
        fprintf(file, "Standard Deviation of Revenue per Category: %.2f\nMean Revenue per Category: %.2f\n", standard_deviation, mean);
        fclose(file);
    }
    free_list_of_group_category_by_revenue(list_of_groups);
}

void find_trend_of_revenue_per_subcategory(SalesList * sales_list) {
    ListOfGroupSubcategoryByMonthlyRevenue* list_of_groups = create_list_of_group_subcategory_by_monthly_revenue();
    if (list_of_groups == NULL) {
        printf("Error creating list of groups.\n");
        free_sales_list(sales_list);
        return;
    }
    
    populate_group_subcategory_by_monthly_revenue(list_of_groups, sales_list);
    
    print_list_of_group_subcategory_by_monthly_revenue(list_of_groups);
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
            GroupSubcategoryByMonthlyRevenue * group = list_of_groups->group_subcategory_by_monthly_revenue[i];
            fprintf(file, "%d: Subcategory: %s\n", i + 1, group->subcategory);
            for(int j = 0; j < group->list_of_group_month_by_revenue->nr_of_groups; j++) {
                GroupMonthByRevenue * month_group = group->list_of_group_month_by_revenue->group_month_by_revenue[j];
                fprintf(file, "Month: %d, Year: %d, Number of Sales: %d, Revenue: %.2f\n", 
                        month_group->month, month_group->year, month_group->num_of_sales, month_group->revenue);
            }
        }
        fclose(file);
    }

    free_list_of_group_subcategory_by_monthly_revenue(list_of_groups);
}