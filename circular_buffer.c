#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"


int circular_buffer_create(struct circular_buffer_t *cb, int N)
{
    if(cb==NULL || N<=0)
    {
        return 1;
    }

    int *temp;
    temp = (int*)malloc(N*sizeof(int ));
    if(temp==NULL)
    {
        return 2;
    }

    cb->ptr = temp;
    cb->capacity = N;
    cb->begin=0;
    cb->end=0;
    cb->full = 0;

    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N)
{
    if(cb==NULL || N<=0)
    {
        return 1;
    }

    *cb = (struct circular_buffer_t*)malloc(sizeof(struct circular_buffer_t));

    if(cb==NULL)
    {
        return 2;
    }

    if(circular_buffer_create(*cb, N)!=0)
    {
        free(*cb);
        return 2;
    }


    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *cb)
{
    if(cb==NULL || cb->ptr==NULL)
        return;

    free(cb->ptr);
}

void circular_buffer_destroy_struct(struct circular_buffer_t **cb)
{
    if(cb==NULL)
    {
        return;
    }

    if((*cb)->ptr==NULL)
    {
        free(*cb);
        return;
    }

    circular_buffer_destroy(*cb);

    free(*cb);
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value)
{
    if(cb==NULL || cb->ptr==NULL || cb->capacity<=0 || cb->begin>=cb->capacity || cb->begin<0 || cb->end>=cb->capacity || cb->end<0)
    {
        return 1;
    }

    *(cb->ptr + cb->end) = value;
    cb->end++;

    if(cb->end == cb->capacity)
    {
        cb->end=0;
    }

    if(cb->full!=0)
    {
        cb->begin++;
    }

    if(cb->begin == cb->capacity)
    {
        cb->begin=0;
    }

    if(cb->end==cb->begin)
    {
        cb->full=1;
    }
    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *cb, int *err_code)
{
    if(cb==NULL || cb->ptr==NULL || cb->capacity<=0 || cb->begin>=cb->capacity || cb->begin<0 || cb->end>=cb->capacity || cb->end<0)
    {
        if(err_code!=NULL)
            *err_code = 1;
        return 1;
    }

    if(circular_buffer_empty(cb)!=0)
    {
        if(err_code!=NULL)
            *err_code = 2;
        return 2;
    }

    int x = *(cb->ptr+cb->begin);

    cb->begin++;
    if(cb->begin == cb->capacity)
    {
        cb->begin=0;
    }

    cb->full=0;

    if(err_code!=NULL)
        *err_code = 0;
    return x;
}

int circular_buffer_pop_back(struct circular_buffer_t *cb, int *err_code)
{
    if(cb==NULL || cb->ptr==NULL || cb->capacity<=0 || cb->begin>=cb->capacity || cb->begin<0 || cb->end>=cb->capacity || cb->end<0)
    {
        if(err_code!=NULL)
            *err_code = 1;
        return 1;
    }

    if(circular_buffer_empty(cb)!=0)
    {
        if(err_code!=NULL)
            *err_code = 2;
        return 2;
    }

    cb->end--;
    if(cb->end == -1)
    {
        cb->end=cb->capacity-1;
    }

    int x = *(cb->ptr+cb->end);

    cb->full=0;

    if(err_code)
        *err_code = 0;
    return x;
}

int circular_buffer_empty(const struct circular_buffer_t *cb)
{
    if(cb==NULL || cb->ptr==NULL || cb->capacity<=0 || cb->begin>=cb->capacity || cb->begin<0 || cb->end>=cb->capacity || cb->end<0)
    {
        return -1;
    }
    if(cb->begin == cb->end && cb->full==0)
    {
        return 1;
    }

    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *cb)
{
    if(cb==NULL || cb->ptr==NULL || cb->capacity<=0 || cb->begin>=cb->capacity || cb->begin<0 || cb->end>=cb->capacity || cb->end<0)
    {
        return -1;
    }
    if(cb->begin == cb->end  && cb->full==1)
    {
        return 1;
    }
    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *cb)
{
    if(cb==NULL || cb->ptr==NULL || cb->capacity<=0 || cb->begin>=cb->capacity || cb->begin<0 || cb->end>=cb->capacity || cb->end<0 || circular_buffer_empty(cb)==1)
        return ;


    if(cb->begin>cb->end)
    {
        for(int i=cb->begin;i<cb->capacity;i++)
            printf("%d ", *(cb->ptr+i));

        for(int i=0;i<cb->end;i++)
            printf("%d ", *(cb->ptr+i));

    }
    if(cb->begin==cb->end)
    {
        for(int i=cb->begin;i<cb->capacity;i++)
            printf("%d ", *(cb->ptr+i));

        for(int i=0;i<cb->end;i++)
            printf("%d ", *(cb->ptr+i));
    }
    else
    {
        for(int i=cb->begin;i<cb->end;i++)
            printf("%d ", *(cb->ptr+i));
    }

    printf("\n");
}
