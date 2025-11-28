#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4
typedef char my_int[MAX];

void my_add(my_int *ret, my_int input1, my_int input2);
void my_number_print(my_int input);
void trans_from_string(my_int *input, char *str);

int main(void)
{
    char temp_str1[100]; 
    char temp_str2[100];
    
    my_int str1, str2; 
    my_int result;   
    
    while(1)
    {
        printf("Please give a number less than %d: ", MAX);
        scanf("%s", temp_str1);
        printf("Please give another number less than %d: ", MAX);
        scanf("%s", temp_str2); 

        trans_from_string(&str1, temp_str1);
        trans_from_string(&str2, temp_str2);


        if (str1[0] == -1 || str2[0] == -1)
        {
            continue; 
        }
        my_add(&result, str1, str2);
    }
    return 0;
}


void my_add(my_int *ret, my_int input1, my_int input2)
{
    int carry = 0;

    for(int i = MAX - 1; i >= 0; i--)
    {
        int sum = input1[i] + input2[i] + carry;
    
        if(sum >= 10)
        {
            (*ret)[i] = sum - 10;
            carry = 1;
        }
        else
        {
            (*ret)[i] = sum;   
            carry = 0;
        }
    }

    if(carry == 1)
    {
        printf("Overflow!\n");
    }
    else
    {
        printf("The add result: ");
        my_number_print(*ret);
    }
}

void my_number_print(my_int input)
{
    int start_print = 0;

    for(int i = 0; i < MAX; i++)
    {
        if(input[i] != 0)
        {
            start_print = 1;
        }
        
        if(start_print == 1)
        {
            printf("%d", input[i]); 
        }
    }
    
    if(start_print == 0)
    {
        printf("0");
    }
    printf("\n");
}

void trans_from_string(my_int *input, char *str)
{
    int len = strlen(str);


    for(int k = 0; k < MAX; k++) {
        (*input)[k] = 0;
    }

    if(len > MAX) 
    {
        printf("Overflow!\n");
        (*input)[0] = -1; 
    }
    else
    {
        for(int i = 0; i < MAX; i++)
        {
            int str_index = len - MAX + i;
            
            if(str_index >= 0)
            {
                (*input)[i] = str[str_index] - '0';
            }
            else
            {
                (*input)[i] = 0;
            }
        }
    }
}
