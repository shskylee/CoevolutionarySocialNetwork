//
//  main.c
//  renewalprocess
//
//  Created by LiShanshan on 12/06/2014.
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



int main(int argc, const char * argv[])
{
    int    i,j,k,m,n;
	int    *Adjacency_matrix;
    int    *Maximum_Outcome_degree;
    int    **neighbor_matrix;
    double *Cumulative_Rate;
    double *Cumulative_Rate_one_user;
    double *Renewal_Rate;
    double *Profile_Distance;
    double *Tweet_Rate_day;
    double Renewal_Lambda=0.;
   
    FILE *Profile_distance;
	FILE *User_Tweet_Rate;
    FILE *Initial_Graph;
    FILE *CumulativeRate;
    FILE *CumulativeRate_OneUser;
    FILE *RenewalRate;
    FILE *Degree_Distribution;
    FILE *Neighbor_matrix;
  
    

    
    Profile_Distance = (double*)calloc(Max_Vertices*Max_Vertices, sizeof(double));
	Tweet_Rate_day = (double*)calloc(Max_Vertices, sizeof(double));
	Adjacency_matrix = (int*)calloc(Max_Vertices*Max_Vertices, sizeof(int));
    Cumulative_Rate=(double*)calloc(Max_Vertices, sizeof(double));
    Renewal_Rate=(double*)calloc(Max_Vertices*Max_Vertices, sizeof(double));
    Maximum_Outcome_degree=(int*)calloc(Max_Vertices, sizeof(int));
    neighbor_matrix = (int**)calloc(Max_Vertices, sizeof(int*));
    Cumulative_Rate_one_user=(double*)calloc(Max_Vertices, sizeof(double));
   

   
	
   
	if (Cumulative_Rate == NULL)          exit(1);
    if (Cumulative_Rate_one_user == NULL) exit(1);
    if (Renewal_Rate == NULL)             exit(1);
    if (Profile_Distance == NULL)         exit(1);
	if (Tweet_Rate_day == NULL)           exit(1);
	if (Adjacency_matrix == NULL)         exit(1);
    if (Maximum_Outcome_degree == NULL)   exit(1);
    if (neighbor_matrix == NULL)          exit(1);
    
    
    
    
    
    for (i=0; i<Max_Vertices; i++) {
        neighbor_matrix[i]=(int*)calloc(max_degree, sizeof(int));
        if (neighbor_matrix[i]==NULL) exit(2);
    }

    
  
    Initial_Graph=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/InitialGraph/InitialGraph/initial_topology.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<Max_Vertices; j++) {
            fscanf(Initial_Graph,"%d",&Adjacency_matrix[i*Max_Vertices+j]);
        }
    }
    fclose(Initial_Graph);
    
    
    
    Neighbor_matrix=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/neighbor/neighbor/neighbor_users.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<max_degree; j++) {
            fscanf(Neighbor_matrix,"%d",&neighbor_matrix[i][j]);
        }
    }
    fclose(Neighbor_matrix);
    
    
    Degree_Distribution=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/InitialGraph/InitialGraph/degree_distribution.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        fscanf(Degree_Distribution,"%d",&Maximum_Outcome_degree[i]);
    }
    fclose(Degree_Distribution);
    
    
    Profile_distance=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/UserProfile/UserProfile/Profile_Distance.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<Max_Vertices; j++) {
            fscanf(Profile_distance,"%lf",&Profile_Distance[i*Max_Vertices+j]);
        }
    }
    fclose(Profile_distance);
    
    
    
   User_Tweet_Rate=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/UserProfile/UserProfile/user_tweet_rate.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        fscanf(User_Tweet_Rate,"%lf",&Tweet_Rate_day[i]);
        
    }
    fclose(User_Tweet_Rate);
    

    
    for (i = 0; i<Max_Vertices; i++) {
        for (j=0; j<Maximum_Outcome_degree[i]; j++) {
            m=neighbor_matrix[i][j];
            for (k=0; k<Maximum_Outcome_degree[m]; k++) {
                n=neighbor_matrix[m][k];
                if (Adjacency_matrix[i*Max_Vertices+n]==0 && n!=i) {
                    Renewal_Rate[i*Max_Vertices+n]+=Tweet_Rate_day[n] * Profile_Distance[m*Max_Vertices + n] * Profile_Distance[i*Max_Vertices + n];
                 Cumulative_Rate_one_user[i]+=Renewal_Rate[i*Max_Vertices+n];
                  
                }
            }
        }
        Renewal_Lambda += Cumulative_Rate_one_user[i];
        Cumulative_Rate[i]=Renewal_Lambda;
        
     
    }
    

    CumulativeRate = fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/renewalprocess/renewalprocess/Cumulative_Rate.txt", "w+");
	for (i = 0; i<Max_Vertices; i++) {
        fprintf(CumulativeRate, "%f ", Cumulative_Rate[i]);
    }
    
    fclose(CumulativeRate);
    
    
    
   CumulativeRate_OneUser= fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/renewalprocess/renewalprocess/CumulativeRate_OneUser.txt", "w+");
	for (i = 0; i<Max_Vertices; i++) {
        fprintf(CumulativeRate_OneUser, "%f ", Cumulative_Rate_one_user[i]);
    }
    
    fclose(CumulativeRate_OneUser);

    

    
    RenewalRate= fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/renewalprocess/renewalprocess/Renewal_Rate.txt", "w+");
	for (i = 0; i<Max_Vertices; i++) {
        for (j=0;j<Max_Vertices; j++) {
            fprintf(RenewalRate, "%f ", Renewal_Rate[i*Max_Vertices+j]);

        }
    }
    fclose(RenewalRate);
    
    printf("%f",Renewal_Lambda);
    
    
	free(Cumulative_Rate);
    free(Cumulative_Rate_one_user);
    free(Renewal_Rate);
    free(Profile_Distance);
	free(Tweet_Rate_day);
	free(Adjacency_matrix);
    free(Maximum_Outcome_degree);
    for (i=0;i<Max_Vertices;i++) {
        free(neighbor_matrix[i]);
    }
    free(neighbor_matrix);

    
    
        return 0;
    }

