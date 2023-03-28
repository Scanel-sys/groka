#include <stdio.h>
#include <stdlib.h>



struct queue
{
    struct human * tail;
    struct human * head;
};

struct human
{
    int numb;

    struct human * q_next;
    struct human * q_prev;
};

int * arr_init(int *size);
int ** adj_matrix_init(int ** adj_matrix, int people);
void handle_and_avocado_init(int *handled_ones, int *if_avocado_seller, int people);
struct human * human_init(int human_id);
struct queue * queue_init(struct queue *q);
void push(struct queue* q, int human_id);
int pop(struct queue *q);

/*
    weak place of bin_ser - if there s no items to find - endless iteration 
*/
int bin_search(int *data, int size, int to_find);
void sort_by_choice(int *data, int size);
void quick_sort(int *data, int l, int r);
int recourse_sum(int *data, int size, int ind);
void bfs(struct queue *q, int **adj_mat, int *handled_ones, int *if_avocado_seller, int people);

void try_bin_search();
void try_recource_sum();
void try_qsort();
void try_bfs();

int main()
{
    
}

int * arr_init(int *size)
{    
    printf("Size of array: ");
    scanf("%d", size);

    int *data = (int *)malloc(sizeof(int) * *size);
    printf("Array data: ");
    
    for(int i = 0; i < *size; i++)
        scanf("%d", &data[i]);

    return data;
}

int ** adj_matrix_init(int ** adj_matrix, int people)
{
    printf("fulfill adj_matrix\n");
    for(int i = 0; i < people; i++)
    {
        adj_matrix[i] = (int *)malloc(people * sizeof(int));
        for(int z = 0; z < people; z++)
            scanf("%d", &adj_matrix[i][z]);
    }
    return adj_matrix;
}

void handle_and_avocado_init(int *handled_ones, int *if_avocado_seller, int people)
{
    printf("fullfill people who is avocado seller with 1\n");
    for(int i = 0; i < people; i++)
    {
        handled_ones[i] = 0;
        scanf("%d", &if_avocado_seller[i]);
    }
}

struct human * human_init(int human_id)
{
    struct human * out = (struct human *)malloc(sizeof(struct human));
    out->numb = human_id;
    out->q_next = out->q_prev = NULL;
    return out;
}

struct queue * queue_init(struct queue *q)
{
    q = (struct queue *)malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void push(struct queue* q, int human_id)
{
    struct human * h = human_init(human_id);
    if(q->head != NULL)
    {
        h->q_next = q->tail;
        h->q_next->q_prev = h;
        q->tail = h;
    }
    else
    {
        q->tail = q->head = h;   
    }
}

int pop(struct queue *q)
{
    struct human * h_to_del = q->head;
    int h_id;
    if(h_to_del == NULL)
        return -1;
    
    if(q->head != q->tail)
    {
        q->head = h_to_del->q_prev;
        q->head->q_next = NULL;
        h_to_del->q_prev = NULL;
    }
    else
    {
        q->head = q->tail = NULL;
    }
    h_id = h_to_del->numb;
    free(h_to_del);

    return h_id;
}


int bin_search(int *data, int size, int to_find)
{
    int l = 0, r = size - 1;
    int mid = (l + r) / 2;

     while(data[l] != to_find)
    {
        if(data[mid] < to_find)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
        mid = (l + r) / 2;
    }

    return l;
}

void sort_by_choice(int *data, int size)
{
    int t_num, t_ind;

    for(int i_1 = 0; i_1 < size - 1; i_1++)
    {
        t_ind = i_1;
        for(int i_2 = i_1 + 1; i_2 < size; i_2++)
            if(data[t_ind] > data[i_2])
                t_ind = i_2;

        if(t_ind != i_1)
        {
            t_num = data[i_1];
            data[i_1] = data[t_ind];
            data[t_ind] = t_num;
        }
    }
}

void quick_sort(int *data, int l, int r)
{
    int t_l, t_r, prop, t;
    t_l = l;
    t_r = r;
    prop = data[(l + r) / 2];
    do
    {
        while(data[t_l] < prop)
            t_l++;
        while(data[t_r] > prop)
            t_r--;
        if(t_l <= t_r)
        {
            t = data[t_l];
            data[t_l] = data[t_r];
            data[t_r] = t;
            t_l++;
            t_r--;
        }
    }while(t_l <= t_r);

    if(t_r > l)
        quick_sort(data, l, t_r);
    if(t_l < r)
        quick_sort(data, t_l, r);
}

int recourse_sum(int *data, int size, int ind)
{
    if(ind < size)
        return (data[ind] + recourse_sum(data, size, ind + 1));
    
    return 0;
}

void bfs(struct queue *q, int **adj_mat, int *handled_ones, int *if_avocado_seller, int people)
{
    int human_id;
    while (q->head != NULL)
    {
        human_id = pop(q);   
        handled_ones[human_id] = 1;

        if(if_avocado_seller[human_id] == 1)
            printf("%d human - avocado seller\n", human_id);

        for(int i = 0; i < people; i++)
        {
            if(adj_mat[human_id][i] == 1 && handled_ones[i] == 0)
                push(q, i);
        }
    }
}


void try_bin_search()
{
    int to_find;
    int *size = (int *)malloc(sizeof(int));
    int *data = arr_init(size);
    
    printf("Number to find: ");
    scanf("%d", &to_find);

    printf("\n%d - index", bin_search(data, *size, to_find));

    free(size);
    free(data);
}

void try_recource_sum()
{
    int sum;
    int *size = (int *)malloc(sizeof(int));
    int *data = arr_init(size);

    sum = recourse_sum(data, *size, 0);

    printf("%d",sum);
    
    free(size);
    free(data);
}

void try_qsort()
{
    int *size = (int *)malloc(sizeof(int));
    int *data = arr_init(size);
    quick_sort(data, 0, *size - 1);

    for(int i = 0; i < *size; i++)
        printf("%d ", data[i]);
    
    free(size);
    free(data);
}

void try_bfs()
{
    struct queue *q;
    q = queue_init(q);
    
    int people;
    printf("People quantity: ");
    scanf("%d", &people);

    int * handled_ones = (int *)malloc(sizeof(int) * people);
    int * if_avocado_seller = (int *)malloc(sizeof(int) * people);
    int ** adj_matrix = (int **)malloc(sizeof(int *) * people);

    handle_and_avocado_init(handled_ones, if_avocado_seller, people);    
    adj_matrix = adj_matrix_init(adj_matrix, people);

    push(q, 0);

    bfs(q, adj_matrix, handled_ones, if_avocado_seller, people);

    free(q);
    free(adj_matrix);
    free(handled_ones);
    free(if_avocado_seller);
}
