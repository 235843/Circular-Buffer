#include <stdio.h>
#include "circular_buffer.h"


int main() {
    struct circular_buffer_t* buff;
    int size;
    int error_code;
    int* err = &error_code;

    printf("Podaj rozmiar bufora :");
    if((scanf("%d", &size))!=1)
    {
        printf("Incorrect input");
        return 1;
    }
    if(size<=0)
    {
        printf("Incorrect input data");
        return 2;
    }

    if(circular_buffer_create_struct(&buff, size)!=0)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    while(getchar()!='\n');
    for(;;)
    {
        int choice;
        printf("Co chcesz zrobic? :");
        if((scanf("%d", &choice))!=1)
        {
            printf("Incorrect input");
            circular_buffer_destroy_struct(&buff);
            return 1;
        }
        while (getchar()!='\n');

        if(choice==0)
        {
            break;
        }

        else if(choice==1)
        {
            int temp;
            printf("Podaj liczbe :");

            if((scanf("%d", &temp))!=1)
            {
                printf("Incorrect input");
                circular_buffer_destroy_struct(&buff);
                return 1;
            }
            circular_buffer_push_back(buff, temp);
            while (getchar()!='\n');
        }

        else if(choice==2)
        {
            int temp = circular_buffer_pop_back(buff, err);
            if(*err!=0)
            {
                printf("Buffer is empty\n");
            }
            else
            {
                printf("%d\n", temp);
            }
        }

        else if(choice==3)
        {
            int temp = circular_buffer_pop_front(buff, err);
            if(*err!=0)
            {
                printf("Buffer is empty\n");
            }
            else
            {
                printf("%d\n", temp);
            }
        }

        else if(choice==4)
        {
            if(circular_buffer_empty(buff)==1)
            {
                printf("Buffer is empty\n");
            }
            else
            {
                circular_buffer_display(buff);
            }
        }

        else if(choice==5)
        {
            printf("%d\n", circular_buffer_empty(buff));
        }

        else if(choice==6)
        {
            printf("%d\n", circular_buffer_full(buff));
        }

        else
        {
            printf("Incorrect input data\n");
        }

    }

    circular_buffer_destroy_struct(&buff);

    return 0;
}
