#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

struct queue
{
    struct vershina * tail;
    struct vershina * head;
};

struct vershina
{
    int numb;

    struct vershina * q_next;
    struct vershina * q_prev;
};

struct edge_info
{
    int cost;
    int parent;
};

struct store_item
{
    int cost;
    int weight;
};

int min(int a, int b);
int max(int a, int b);

int * arr_init(int *size);
int ** adj_matrix_init(int size);
int * handle_init(int size);
int * avocado_init(int size);
struct edge_info * costs_init(int size);

struct vershina * vershina_init(int human_id);
struct queue * queue_init(struct queue *q);
void push(struct queue* q, int edge_id);
int pop(struct queue *q);
/*
    weak place of bin_ser - if there s no items to find - endless iteration 
*/
int bin_search(int *data, int size, int to_find);
void sort_by_choice(int *data, int size);
void quick_sort(int *data, int l, int r);
int recourse_sum(int *data, int size, int ind);
void bfs(struct queue *q, int **adj_mat, int *handled_ones, int *if_avocado_seller, int people);
void Deikstra(struct queue *q, int **adj_mat, int *handled_ones, struct edge_info *edge_info, int size, int where);
int vorishka(int ** matrix, struct store_item * items, int items_number, int backpack_size);

void try_bin_search();
void try_recource_sum();
void try_qsort();
void try_bfs();
void try_deikstra();
void try_vorishka();
