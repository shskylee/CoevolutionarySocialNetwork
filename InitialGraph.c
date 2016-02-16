//
//  main.c
//  InitialGraph
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


int main(int argc, const char * argv[])
{
    
    int    i,j;
    int    *Adjacency_matrix;
    int    *Maximum_Outcome_degree;
    
    time_t t;
    FILE   *Initial_Graph;
    FILE   *Degree_Distribution;
    
    Adjacency_matrix = (int*)calloc(Max_Vertices*Max_Vertices, sizeof(int));
    Maximum_Outcome_degree =(int*)calloc(Max_Vertices, sizeof(int));
    
    
    
    srand((unsigned)time(&t));
    
    
    
    if (Maximum_Outcome_degree == NULL) exit(1);
    if (Adjacency_matrix == NULL)       exit(1);
    
    
    for (i = 0; i < Max_Vertices; i++){
        for (j = 0; j < Max_Vertices; j++)
        {
            if (j != i)
            {
                if ((double)rand() / RAND_MAX < Random_Prob)
                {
                    Adjacency_matrix[i*Max_Vertices + j] = 1;
                }
                else
                {
                    Adjacency_matrix[i*Max_Vertices + j] = 0;
                }
            }
            else
            {
                Adjacency_matrix[i*Max_Vertices + j] = 0;
            }
            
            Maximum_Outcome_degree[i] += Adjacency_matrix[i*Max_Vertices + j];
        }
        
    }
    
    
    
    
    
    Initial_Graph = fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/InitialGraph/InitialGraph/initial_topology.txt", "w+");
    for (i = 0; i<Max_Vertices; i++) {
        for (j = 0; j<Max_Vertices; j++) {
            fprintf(Initial_Graph, "%d ", Adjacency_matrix[i*Max_Vertices + j]);
        }
    }
    fclose(Initial_Graph);
    
    
    
    Degree_Distribution = fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/InitialGraph/InitialGraph/degree_distribution.txt", "w+");
    for (i = 0; i<Max_Vertices; i++) {
        fprintf(Degree_Distribution, "%d ", Maximum_Outcome_degree[i]);
    }
    fclose(Degree_Distribution);
    
    free(Adjacency_matrix);
    free(Maximum_Outcome_degree);
    
    return 0;
}

