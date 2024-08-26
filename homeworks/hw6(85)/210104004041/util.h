#ifndef _UTIL_H_
#define _UTIL_H_

#define MAX_LINE_LEN 100
#define MAX_PRODUCT 100
#define MAX_FEAT_NAME_LEN 15

int str_comparer(char str1[], char str2[]);
void reader(int *feat_count,int *product_cnt,int *stock_count,char all_in_one_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN]);

void file_operations();
void add_new_product(int *feat_count,int *product_count);
void delete_product(int *product_count);
void add_feature();
void update_product(int *feat_count,int *product_count,char all_in_one_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN]);
void add_stock(int *stock_count);
void delete_stock(int *stock_count);
void update_stock(int *stock_count,char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN]);

void query_products();
void list_all_products();
void filter_products(char all_in_one_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],int feat_num,int product_num);

void check_stock_status();
void by_pid_branch(char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],int stock_count);
void by_branch(char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],int stock_count);
void outofstock(char allstocks[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],int stock_count,char all_in_one_array[MAX_PRODUCT][MAX_LINE_LEN][MAX_FEAT_NAME_LEN],int product_count,int feat_count);

void brand_stock_control(double results[MAX_PRODUCT][MAX_FEAT_NAME_LEN],int *size,int *matched_products);

void stock_report(double results[MAX_PRODUCT][MAX_FEAT_NAME_LEN],int size,int matched_products);
#endif /* _UTIL_H_ */
