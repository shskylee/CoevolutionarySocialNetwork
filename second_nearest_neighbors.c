//
//  main.c
//  second_nearest_neighbors
//
//  Created by LiShanshan on 14/06/2014.
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
#define Random_Prob 0.005
#define Profile_Dimension 3
#define profile_factor 2
#define max_degree 83


int main(int argc, const char * argv[])
{
    int    i,j,k=0;
    int    **second_neighbor_matrix;
    int    *second_neighbor_degree;
    int    max_second_degree=0;
    double *Renewal_Rate;
  
    FILE *RenewalRate;
    FILE *Second_Nearest_Neighbor;
    
    
    
    
    Renewal_Rate=(double*)calloc(Max_Vertices*Max_Vertices, sizeof(double));
    second_neighbor_matrix = (int**)calloc(Max_Vertices, sizeof(int*));
    second_neighbor_degree = (int*)calloc(Max_Vertices, sizeof(int));
    
    if (Renewal_Rate == NULL)             exit(1);
    if (second_neighbor_matrix == NULL)   exit(1);
    if (second_neighbor_degree == NULL)   exit(1);
        
    
    for (i=0; i<Max_Vertices; i++) {
        second_neighbor_matrix[i]=(int*)calloc(100*max_degree, sizeof(int));
        if (second_neighbor_matrix[i]== NULL) exit(2);
    }
    
    
    
    RenewalRate=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/renewalprocess/renewalprocess/Renewal_Rate.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<Max_Vertices; j++) {
            fscanf(RenewalRate,"%lf",&Renewal_Rate[i*Max_Vertices+j]);
        }
    }
    fclose(RenewalRate);
 
    
    
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<Max_Vertices; j++) {
            if (Renewal_Rate[i*Max_Vertices+j]!=0) {
                second_neighbor_matrix[i][k]=j;
                k++;
                second_neighbor_degree[i]+=1;
               
            }
        }
        k=0;
    }
    
    for (i=0; i<Max_Vertices; i++) {
        if (max_second_degree<second_neighbor_degree[i]) {
            max_second_degree=second_neighbor_degree[i];
        }
    }
    
    printf("%d",max_second_degree);
    
    Second_Nearest_Neighbor=fopen("//Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/second_nearest_neighbors/second_nearest_neighbors/second_nearest_neighbors.txt", "w+");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<5*max_degree; j++) {
            fprintf(Second_Nearest_Neighbor,"%d",second_neighbor_matrix[i][j]);
        }
    }
    fclose(Second_Nearest_Neighbor);
    
    
    for (i=0;i<Max_Vertices;i++) {
        free(second_neighbor_matrix[i]);
    }
    free(second_neighbor_matrix);
    
    
    
    return 0;
}


