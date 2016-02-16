//
//  main.c
//  TRF_event
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
#define Random_Prob 0.01
#define Profile_Dimension 3
#define profile_factor 2
#define max_degree 144
#define Max_step 1.0e+08
#define IS_LESS(v1, v2)  (v1 < v2)
#define SWAP(r,s)  do{double t=r; r=s; s=t; } while(0)
#define SWAP_int(r,s) do{int t=r; r=s; s=t; } while(0)


int main(int argc, const char * argv[])
{
    

	int    i, j, k, step=0;
    int    Target_User=0, Delete_User=0, Potential_Followee=0;
	int    *Adjacency_matrix;
	double *Users_Distance;
	int    *Maximum_Outcome_degree;
	double *Profile_Distance;
    double *Tweet_Rate_day;
	double *Renewal_Rate;
	double Renewal_Lambda = 601768087559.376709;
	double Decomposition_U1;
    double Decomposition_U2;
	double *Cumulative_Rate;
    double *Cumulative_Rate_one_user;
    int    **neighbor_matrix;
    double **neighbor_distance;
    time_t t;
    srand((unsigned)time(&t));
	
	
    FILE *Initial_Graph;
    FILE *Degree_Distribution;
	FILE *Final_Graph;
	FILE *User_distance;
	FILE *Profile_distance;
    FILE *User_Tweet_Rate;
	FILE *CumulativeRate;
    FILE *CumulativeRate_OneUser;
	FILE *RenewalRate;
    FILE *Neighbor_matrix;
    FILE *Neighbor_distance;
    
    
    
    
    
	Renewal_Rate = (double*)calloc(Max_Vertices*Max_Vertices, sizeof(double));
	Cumulative_Rate = (double*)calloc(Max_Vertices*Max_Vertices, sizeof(double));
    Cumulative_Rate_one_user=(double*)calloc(Max_Vertices*Max_Vertices, sizeof(double));
	Maximum_Outcome_degree = (int*)calloc(Max_Vertices, sizeof(int));
	Profile_Distance = (double*)calloc(Max_Vertices*Max_Vertices, sizeof(double));
	Users_Distance = (double*)calloc(Max_Vertices*Max_Vertices, sizeof(double));
	Tweet_Rate_day = (double*)calloc(Max_Vertices, sizeof(double));
	Adjacency_matrix = (int*)calloc(Max_Vertices*Max_Vertices, sizeof(int));
    neighbor_matrix = (int**)calloc(Max_Vertices, sizeof(int*));
    neighbor_distance=(double**)calloc(Max_Vertices, sizeof(double*));
    
    
    
    

    
	if (Renewal_Rate == NULL) exit(1);
	if (Cumulative_Rate == NULL) exit(1);
    if (Cumulative_Rate_one_user == NULL) exit(1);
	if (Maximum_Outcome_degree == NULL) exit(1);
	if (Profile_Distance == NULL) exit(1);
	if (Tweet_Rate_day == NULL) exit(1);
	if (Adjacency_matrix == NULL) exit(1);
	if (Users_Distance == NULL) exit(1);
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
    
    Degree_Distribution=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/InitialGraph/InitialGraph/degree_distribution.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        fscanf(Degree_Distribution,"%d",&Maximum_Outcome_degree[i]);
    }
    fclose(Degree_Distribution);
    
    User_distance=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/UserProfile/UserProfile/User_Distance.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<Max_Vertices; j++) {
            fscanf(User_distance,"%lf",&Users_Distance[i*Max_Vertices+j]);
        }
    }
    fclose(User_distance);
    
    Profile_distance = fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/UserProfile/UserProfile/Profile_Distance.txt", "r");
	for (i = 0; i<Max_Vertices; i++) {
		for (j = 0; j<Max_Vertices; j++) {
			fscanf(Profile_distance, "%lf ", &Profile_Distance[i*Max_Vertices + j]);
		}
    }
    fclose(Profile_distance);
    
    User_Tweet_Rate = fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/UserProfile/UserProfile/user_tweet_rate.txt", "r");
	for (i = 0; i<Max_Vertices; i++) {
		fscanf(User_Tweet_Rate, "%lf ",&Tweet_Rate_day[i]);
	}
    fclose(User_Tweet_Rate);
    
    
    Neighbor_matrix=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/neighbor/neighbor/neighbor_matrix.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<max_degree; j++) {
            fscanf(Neighbor_matrix,"%d ",&neighbor_matrix[i][j]);
        }
    }
    fclose(Neighbor_matrix);
    
    
    Neighbor_distance=fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/neighbor/neighbor/neighbor_distance.txt", "r");
    for (i=0; i<Max_Vertices; i++) {
        for (j=0; j<max_degree; j++) {
            fscanf(Neighbor_distance,"%lf ",&neighbor_distance[i][j]);
        }
    }
    fclose(Neighbor_distance);
    
    
    
	CumulativeRate = fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/renewalprocess/renewalprocess/Cumulative_Rate.txt", "r");
	for (i = 0; i<Max_Vertices; i++) {
        fscanf(CumulativeRate, "%lf ", &Cumulative_Rate[i]);
    }
    
    fclose(CumulativeRate);
    
    CumulativeRate_OneUser= fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/renewalprocess/renewalprocess/CumulativeRate_OneUser.txt", "r");
	for (i = 0; i<Max_Vertices; i++) {
        fscanf(CumulativeRate_OneUser, "%lf ", &Cumulative_Rate_one_user[i]);
    }
    
    fclose(CumulativeRate_OneUser);

    
    
    
    
    RenewalRate= fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/renewalprocess/renewalprocess/Renewal_Rate.txt", "r");
	for (i = 0; i<Max_Vertices; i++) {
        for (j=0;j<Max_Vertices; j++) {
            fscanf(RenewalRate, "%lf ", &Renewal_Rate[i*Max_Vertices+j]);
            
        }
    }
    fclose(RenewalRate);
    
    
    
    
   do
	{
        
        
		Decomposition_U1 = (double)rand() / RAND_MAX;
	    for (i = 0; i < Max_Vertices; i++) {
			if (Decomposition_U1 <= Cumulative_Rate[i] / Renewal_Lambda){
                Target_User=i;
                break;
            }
        }
        
        Decomposition_U2= (double)rand() / RAND_MAX;
        for (j=0; j<Max_Vertices; j++) {
            if (Decomposition_U2<=Renewal_Rate[Target_User*Max_Vertices+j]/Cumulative_Rate_one_user[Target_User]) {
                Potential_Followee=j;
               break;
            }
        }
        
        if (Users_Distance[Target_User*Max_Vertices + Potential_Followee] < neighbor_distance[Target_User][Maximum_Outcome_degree[Target_User]-1])
		{
			Delete_User = neighbor_matrix[Target_User][Maximum_Outcome_degree[Target_User]-1];
            Adjacency_matrix[Target_User*Max_Vertices + Delete_User] = 0;
			Adjacency_matrix[Target_User*Max_Vertices + Potential_Followee] = 1;
            neighbor_matrix[Target_User][Maximum_Outcome_degree[Target_User]-1]=Potential_Followee;
            neighbor_distance[Target_User][Maximum_Outcome_degree[Target_User]-1]=Users_Distance[Target_User*Max_Vertices+Potential_Followee];
			
            
            Cumulative_Rate_one_user[Target_User] -=Renewal_Rate[Target_User*Max_Vertices + Potential_Followee];
			Renewal_Rate[Target_User*Max_Vertices + Potential_Followee] = 0.;
           
            
            
            for (k=0; k<Maximum_Outcome_degree[Delete_User]; k++) {
                if (neighbor_matrix[Delete_User][k]!=Target_User && Adjacency_matrix[Target_User*Max_Vertices + neighbor_matrix[Delete_User][k]] == 0 && neighbor_matrix[Delete_User][k]!= Potential_Followee) {
                    Renewal_Rate[Target_User*Max_Vertices + neighbor_matrix[Delete_User][k]] -= Tweet_Rate_day[neighbor_matrix[Delete_User][k]] * Profile_Distance[Delete_User*Max_Vertices + neighbor_matrix[Delete_User][k]] * Profile_Distance[Target_User*Max_Vertices + neighbor_matrix[Delete_User][k]];
                    Cumulative_Rate_one_user[Target_User]-=Tweet_Rate_day[neighbor_matrix[Delete_User][k]] * Profile_Distance[Delete_User*Max_Vertices + neighbor_matrix[Delete_User][k]] * Profile_Distance[Target_User*Max_Vertices + neighbor_matrix[Delete_User][k]];
                }
            }
			
			
            for (k = 0; k < Max_Vertices; k++) {
				if (Adjacency_matrix[k*Max_Vertices + Target_User] != 0 && Adjacency_matrix[k*Max_Vertices + Delete_User] == 0 && k!=Delete_User )
				{
					Renewal_Rate[k*Max_Vertices + Delete_User] -= Tweet_Rate_day[Delete_User] * Profile_Distance[Target_User*Max_Vertices + Delete_User] * Profile_Distance[k*Max_Vertices + Delete_User];
                    Cumulative_Rate_one_user[k]-= Tweet_Rate_day[Delete_User] * Profile_Distance[Target_User*Max_Vertices + Delete_User] * Profile_Distance[k*Max_Vertices + Delete_User];

                }
			}
            
            
            
			for (j = 0; j < Maximum_Outcome_degree[Target_User]; j++)
			{
              if(Adjacency_matrix[(neighbor_matrix[Target_User][j])*Max_Vertices + Delete_User] == 1){
               Renewal_Rate[Target_User*Max_Vertices + Delete_User] += Tweet_Rate_day[Delete_User] * Profile_Distance[(neighbor_matrix[Target_User][j])*Max_Vertices + Delete_User] * Profile_Distance[Target_User*Max_Vertices + Delete_User];
                
                 Cumulative_Rate_one_user[Target_User]+=Tweet_Rate_day[Delete_User] * Profile_Distance[(neighbor_matrix[Target_User][j])*Max_Vertices + Delete_User] * Profile_Distance[Target_User*Max_Vertices + Delete_User];
                 
              }
			}
            
            
			for (k = 0; k < Maximum_Outcome_degree[Potential_Followee]; k++) {
				if ( neighbor_matrix[Potential_Followee][k]!= Target_User && Adjacency_matrix[Target_User*Max_Vertices + neighbor_matrix[Potential_Followee][k]] == 0) {
					Renewal_Rate[Target_User*Max_Vertices + neighbor_matrix[Potential_Followee][k]] += Tweet_Rate_day[neighbor_matrix[Potential_Followee][k]] * Profile_Distance[Potential_Followee*Max_Vertices + neighbor_matrix[Potential_Followee][k]] * Profile_Distance[Target_User*Max_Vertices + neighbor_matrix[Potential_Followee][k]];
					Cumulative_Rate_one_user[Target_User] += Tweet_Rate_day[neighbor_matrix[Potential_Followee][k]] * Profile_Distance[Potential_Followee*Max_Vertices + neighbor_matrix[Potential_Followee][k]] * Profile_Distance[Target_User*Max_Vertices + neighbor_matrix[Potential_Followee][k]];
                    
				}
			}
            
			for (k = 0; k < Max_Vertices; k++) {
				if (Adjacency_matrix[k*Max_Vertices + Target_User] != 0 && k != Potential_Followee && Adjacency_matrix[k*Max_Vertices + Potential_Followee] == 0)
				{
                Renewal_Rate[k*Max_Vertices + Potential_Followee] += Tweet_Rate_day[Potential_Followee] * Profile_Distance[Target_User*Max_Vertices + Potential_Followee] * Profile_Distance[k*Max_Vertices + Potential_Followee];
                Cumulative_Rate_one_user[k] += Tweet_Rate_day[Potential_Followee] * Profile_Distance[Target_User*Max_Vertices + Potential_Followee] * Profile_Distance[k*Max_Vertices + Potential_Followee];

                }
			}
            
            Renewal_Lambda=0;
            
            for (i=0; i<Max_Vertices; i++) {
                Renewal_Lambda += Cumulative_Rate_one_user[i];
                Cumulative_Rate[i]=Renewal_Lambda;
            }
            
            for (i=Maximum_Outcome_degree[Target_User]-1; i>0; i--) {
                if (IS_LESS(neighbor_distance[Target_User][i], neighbor_distance[Target_User][i-1])) {
                    SWAP(neighbor_distance[Target_User][i], neighbor_distance[Target_User][i-1]);
                    SWAP_int(neighbor_matrix[Target_User][i], neighbor_distance[Target_User][i-1]);
                }
            }
        }
			     
			
			        step++;
        
	} while (step <= Max_step);
    
    
    
    
    
    
    
    
    
    
	Final_Graph = fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/TRF_event/TRF_event/final_topology.txt", "w+");
	for (i = 0; i<Max_Vertices; i++) {
		for (j = 0; j<Max_Vertices; j++) {
			fprintf(Final_Graph, "%d ", Adjacency_matrix[i*Max_Vertices + j]);
		}
    }
	fclose(Final_Graph);
    

	    
	free(Renewal_Rate);
	free(Cumulative_Rate);
    free(Cumulative_Rate_one_user);
	free(Maximum_Outcome_degree);
	free(Profile_Distance);
	free(Adjacency_matrix);
	free(Users_Distance);
	free(Tweet_Rate_day);
	for (i=0;i<Max_Vertices;i++) {
            free(neighbor_distance[i]);
        }
    free(neighbor_distance);
    for (i=0;i<Max_Vertices;i++) {
            free(neighbor_matrix[i]);
        }
    free(neighbor_matrix);

        return 0;
    }