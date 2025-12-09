#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITER 800
struct cord
{
    double val;
    struct cord *next;
};
struct vector
{
    struct vector *next;
    struct cord *cords;
};

typedef struct cord cord;

typedef struct vector vector;



double delta_helper(cord *p1, cord *p2){ /* Assume same size */
    if (p1 != NULL){
        return pow(((*p1).val-(*p2).val),2)+delta_helper((*p1).next,(*p2).next);
    }    
    return 0;
}

double delta(cord *p1, cord *p2){
    return sqrt(delta_helper(p1,p2));
}


vector* kmeans(vector *data_points, int k, int iters, vector **centroids){
    int i;
    vector head_point = *data_points;
    cord *curr_point = data_points->cords;
    
    for (i=0;i<k;i++){
        *((*centroids)->cords)=*curr_point;
        curr_point=curr_point->next; 
    }
}

vector* read_input(int *point_amount){
    vector *head_vec, *curr_vec;
    cord *head_cord, *curr_cord;
    double n;
    char c;

    head_cord = malloc(sizeof(cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = malloc(sizeof(vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;


    while (scanf("%lf%c", &n, &c) == 2)
    {

        if (c == '\n')
        {
            curr_cord->val = n;
            curr_vec->cords = head_cord;
            curr_vec->next = malloc(sizeof(vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            head_cord = malloc(sizeof(cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            *(point_amount)+=1;
            continue;
        }

        curr_cord->val = n;
        curr_cord->next = malloc(sizeof(cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
    }
    
    return head_vec;

}
int main(int argc, char **argv)
{

    vector* data_points;
    int point_amounts = 0;
    data_points = read_input(&point_amounts);
    int iters = 400;
    int k=0;
    if (argc==1){
        printf("An error has occured.");
        exit(1);
    }
    if (argc>=2){
        k = atoi(argv[1]);
        if (!((1<k)&&(k<point_amounts))){
            printf("Incorrect number of clusters!");
            exit(1);
        }
    }
    if (argc==3){
        iters = atoi(argv[2]);
        if (!(1<iters&&iters<MAX_ITER)){
            printf("Incorrect maximum iteration!");
            exit(1);
        }
    }

    vector* centroids = malloc(sizeof(vector));
    kmeans(data_points, k, iters, &centroids);

    /* Print centroids for testing */
    printf("\n=== Centroids ===\n");
    vector *curr_vec = centroids;
    int centroid_num = 0;
    while (curr_vec != NULL && centroid_num < k) {
        printf("Centroid %d: ", centroid_num);
        cord *curr_cord = curr_vec->cords;
        while (curr_cord != NULL) {
            printf("%.4f", curr_cord->val);
            if (curr_cord->next != NULL) {
                printf(",");
            }
            curr_cord = curr_cord->next;
        }
        printf("\n");
        curr_vec = curr_vec->next;
        centroid_num++;
    }

    return 0;
}

