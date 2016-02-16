//
//  main.c
//  MaxDistance
//
//  Created by LiShanshan on 12/06/2014.
//  Copyright (c) 2014 Shanshan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#define Max_Vertices 10000

int main()
{
  
    int     i,j;
    int     *Maximum_Outcome_degree;
    int     *Adjacency_matrix;
    int     max_degree=0;
    
    FILE    *Degree_Distribution;
    FILE    *Initial_Graph;
   
    
    Maximum_Outcome_degree = (int*)calloc(Max_Vertices, sizeof(int));
    Adjacency_matrix = (int*)calloc(Max_Vertices*Max_Vertices, sizeof(int));
    
  
    if (Adjacency_matrix == NULL) exit(1);
    if (Maximum_Outcome_degree ==NULL) exit(1);
    

    
    Initial_Graph=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/InitialGraph/InitialGraph/initial_topology.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<Max_Vertices; j++) {
            fscanf(Initial_Graph,"%d",&Adjacency_matrix[i*Max_Vertices+j]);
        }
    }
    fclose(Initial_Graph);
    
    
    
   Degree_Distribution=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/InitialGraph/InitialGraph/degree_distribution.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
             fscanf(Degree_Distribution,"%d",&Maximum_Outcome_degree[i]);
        }
    fclose(Degree_Distribution);
    

    for (i=0; i<Max_Vertices; i++) {
        if (max_degree<Maximum_Outcome_degree[i]) {
            max_degree=Maximum_Outcome_degree[i];
        }
    }
    
    printf("%d",max_degree);
    

    
    free(Adjacency_matrix);
    free(Maximum_Outcome_degree);
    
    return 0;
}

