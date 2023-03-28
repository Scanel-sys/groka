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

int ** adj_matrix_init(int size)
{
    int ** adj_matrix = (int **)malloc(sizeof(int *) * size);
    printf("fulfill adj_matrix\n");
    for(int i = 0; i < size; i++)
    {
        adj_matrix[i] = (int *)malloc(size * sizeof(int));
        for(int z = 0; z < size; z++)
            scanf("%d", &adj_matrix[i][z]);
    }
    return adj_matrix;
}

int * handle_init(int size)
{
    int *handled_ones = (int *)malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++)
        handled_ones[i] = 0;
    
    return handled_ones;
}

int * avocado_init(int size)
{
    int * if_avocado_seller = (int *)malloc(sizeof(int) * size);
    printf("fullfill people who is avocado seller with 1\n");
    for(int i = 0; i < size; i++)
        scanf("%d", &if_avocado_seller[i]);
    
    return if_avocado_seller;
}

struct edge_info * costs_init(int size)
{
    struct edge_info * costs = (struct edge_info *)malloc(sizeof(struct edge_info) * size);
    for(int i = 0; i < size; i++)
    {
        costs[i].cost = INT_MAX;
        costs[i].parent = -1;
    }
    return costs;
}

struct vershina * vershina_init(int human_id)
{
    struct vershina * out = (struct vershina *)malloc(sizeof(struct vershina));
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

void push(struct queue* q, int edge_id)
{
    struct vershina * h = vershina_init(edge_id);
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
    struct vershina * h_to_del = q->head;
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

void Deikstra(struct queue *q, int **adj_mat, int *handled_ones, struct edge_info *edge_info, int size, int where)
{
    int edge_id;
    while(q->head != NULL)
    {
        edge_id = pop(q);
        for(int i = 0; i < size; i++)
        {
            if(i != edge_id && adj_mat[edge_id][i] > -1 && edge_info[i].cost > adj_mat[edge_id][i] + edge_info[edge_id].cost)
            {
                edge_info[i].cost = adj_mat[edge_id][i] + edge_info[edge_id].cost;
                edge_info[i].parent = edge_id;
                push(q, i);
            }
        }
    }
    if(edge_info[where].cost == INT_MAX && edge_info[where].parent == -1)
        printf("Impossible to reach this edge\n");
    else
    {
        printf("Shortest path from START to the END in reversed format :\n");
        int temp_id = where;
        while(edge_info[temp_id].parent != -1)
        {
            printf("%d \n", temp_id);
            temp_id = edge_info[temp_id].parent;
        }
        printf("%d - start\n", temp_id);
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

    int * handled_ones = handle_init(people);
    int * if_avocado_seller = avocado_init(people); 
    int ** adj_matrix = adj_matrix_init(people);

    push(q, 0);

    bfs(q, adj_matrix, handled_ones, if_avocado_seller, people);

    free(q);
    free(adj_matrix);
    free(handled_ones);
    free(if_avocado_seller);
}

void try_deikstra()
{
    struct queue *q;
    q = queue_init(q);
    
    int pinnacles;
    printf("Pinnacles quantity: ");
    scanf("%d", &pinnacles);

    struct edge_info * costs = costs_init(pinnacles);
    int * handled_ones = handle_init(pinnacles);
    int ** adj_matrix = adj_matrix_init(pinnacles);

    int start, end;
    printf("Type number of start edge and ending edge, format [0..n - 1]\n");
    scanf("%d %d", &start, &end);
    costs[start].cost = 0;
    push(q, start);

    Deikstra(q, adj_matrix, handled_ones, costs, pinnacles, end);

    free(q);
    free(adj_matrix);
    free(handled_ones);
}