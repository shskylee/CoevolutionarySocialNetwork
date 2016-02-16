//
//  main.c
//  neighbor
//
//  Created by LiShanshan on 13/06/2014.
//  Copyright (c) 2014 Shanshan. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#define PI 3.141592654
#define Max_Vertices 10000
#define Random_Prob 0.01
#define Profile_Dimension 3
#define profile_factor 2
#define max_degree 144
#define IS_LESS(v1, v2)  (v1 < v2)
#define SWAP(r,s)  do{double t=r; r=s; s=t; } while(0)
#define SWAP_int(r,s) do{int t=r; r=s; s=t; } while(0)

int main(int argc, const char * argv[])
{
    
    void   HEAPSORT( double *a,int *b, int count);
    int    i,j,k=0;
    int    *Adjacency_matrix;
    double *User_Distance;
    int    **neighbor_matrix;
    double **neighbor_distance;
    
    FILE   *Initial_Graph;
    FILE   *Users_distance;
    FILE   *Neighbor_matrix;
    FILE   *Neighbor_distance;
    
    Adjacency_matrix = (int*)calloc(Max_Vertices*Max_Vertices, sizeof(int));
    User_Distance = (double*)calloc(Max_Vertices*Max_Vertices, sizeof(double));
    neighbor_matrix = (int**)calloc(Max_Vertices, sizeof(int*));
    neighbor_distance=(double**)calloc(Max_Vertices, sizeof(double*));
    
    if (Adjacency_matrix == NULL)   exit(1);
    if (User_Distance  == NULL)     exit(1);
    if (neighbor_matrix  == NULL)   exit(1);
    if (neighbor_distance == NULL)  exit(1);
    
    for (i=0; i<Max_Vertices; i++) {
        neighbor_matrix[i]=(int*)calloc(max_degree, sizeof(int));
        if (neighbor_matrix[i]==NULL) exit(2);
    }
    
    for (i=0; i<Max_Vertices; i++) {
        neighbor_distance[i]=(double*)calloc(max_degree, sizeof(double));
        if (neighbor_distance[i]==NULL) exit(2);
    }

    Initial_Graph=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/InitialGraph/InitialGraph/initial_topology.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<Max_Vertices; j++) {
            fscanf(Initial_Graph,"%d",&Adjacency_matrix[i*Max_Vertices+j]);
        }
    }
    fclose(Initial_Graph);
    
    Users_distance=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/UserProfile/UserProfile/User_Distance.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<Max_Vertices; j++) {
            fscanf(Users_distance,"%lf",&User_Distance[i*Max_Vertices+j]);
        }
    }
    fclose(Users_distance);
    
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<Max_Vertices;j++) {
            if (Adjacency_matrix[i*Max_Vertices+j]==1) {
                neighbor_matrix[i][k]=j;
                neighbor_distance[i][k]=User_Distance[i*Max_Vertices+j];
                k++;
            }
    }
        k=0;
        HEAPSORT(neighbor_distance[i], neighbor_matrix[i], max_degree);
    }
    
    
    
    Neighbor_matrix=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/neighbor/neighbor/neighbor_matrix.txt", "w+");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<max_degree; j++) {
            fprintf(Neighbor_matrix,"%d ",neighbor_matrix[i][j]);
        }
    }
    fclose(Neighbor_matrix);
  
    
    Neighbor_distance=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/neighbor/neighbor/neighbor_distance.txt", "w+");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<max_degree; j++) {
            fprintf(Neighbor_distance,"%f ",neighbor_distance[i][j]);
        }
    }
    fclose(Neighbor_distance);
    
    

    free(Adjacency_matrix);
    free(User_Distance);
    for (i=0;i<Max_Vertices;i++) {
        free(neighbor_matrix[i]);
    }
    free(neighbor_matrix);
    for (i=0;i<Max_Vertices;i++) {
        free(neighbor_distance[i]);
    }
    free(neighbor_distance);
    
    
    
    return 0;
}


void HEAPSORT( double *a,int *b, int count)
{
    int start, end;
    
    void siftDown( double *a,int *b, int start, int count);
    
    for (start = (count-2)/2; start >=0; start--) {
        siftDown( a, b, start, count);
    }
    
    for (end=count-1; end > 0; end--) {
        SWAP(a[end],a[0]);
        SWAP_int(b[end], b[0]);
        siftDown(a, b, 0, end);
    }
}

void siftDown ( double *a, int *b, int start, int end)
{
    int root = start;
    
    while ( root*2+1 < end ) {
        int child = 2*root + 1;
        if ((child + 1 < end) && IS_LESS(a[child],a[child+1])) {
            child += 1;
        }
        if (IS_LESS(a[root], a[child])) {
            SWAP( a[child], a[root] );
            SWAP_int(b[child],b[root]);
            root = child;
        }
        else
            return;
    }
}








