//
//  main.c
//  UserProfile
//
//  Created by LiShanshan on 12/06/2014.
//  Copyright (c) 2014 Shanshan. All rights reserved.
//

//

#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#define PI 3.141592654
#define Max_Vertices 100000
#define Random_Prob 0.001
#define Profile_Dimension 3
#define profile_factor 2
#define max_degree 150
#define IS_LESS(v1, v2)  (v1 < v2)
#define SWAP(r,s)  do{double t=r; r=s; s=t; } while(0)
#define SWAP_int(r,s) do{int t=r; r=s; s=t; } while(0)


int main(int argc, const char * argv[])
{
    
    double Beta_random_generator(double a, double b);
    double Gamma_Random_generator(double alpha, double beta);
	int    i,j,k;
    double User_Profile[Max_Vertices][Profile_Dimension];
    double *Profile_Distance;
    double *Users_distance;
    double *Tweet_Rate_day;
    double distance_users=0.;
    double theta;
    
    time_t t;
    srand((unsigned)time(&t));
    
    
    
    FILE *U_Profile;
    FILE *User_Distance;
	FILE *Profile_distance;
    FILE *User_Tweet_Rate;
    
    
    theta = sqrt((double)Profile_Dimension) / profile_factor;
    Profile_Distance = (double*)calloc(Max_Vertices*Max_Vertices, sizeof(double));
	Users_distance = (double*)calloc(Max_Vertices*Max_Vertices, sizeof(double));
    Tweet_Rate_day=(double*)calloc(Max_Vertices, sizeof(double));
    
    if (Profile_Distance == NULL) exit(1);
    if (Users_distance == NULL)   exit(1);
    if (Tweet_Rate_day ==NULL)    exit(1);



   	for (i = 0; i<Max_Vertices; i++) {
		for (j = 2; j <Profile_Dimension + 2; j++) {
             User_Profile[i][j - 2] = Beta_random_generator(2.0, (double)j);
		}
	}
    
    
	U_Profile = fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/UserProfile/UserProfile/user_profile.txt", "w+");
	for (i = 0; i < Max_Vertices; i++) {
		for (j = 0; j < Profile_Dimension; j++) {
			fprintf(U_Profile, "%f ", User_Profile[i][j]);
		}
    }
	fclose(U_Profile);
    
    
    for (i = 0; i < Max_Vertices; i++)
	{
		for (j = 0; j < Max_Vertices; j++)
		{
			
			
				for (k = 0; k < Profile_Dimension; k++)
				{
					distance_users += pow(User_Profile[i][k] - User_Profile[j][k], 2);
				}
				Users_distance[i*Max_Vertices + j] = sqrt((double)distance_users);
                
				if (Users_distance[i*Max_Vertices + j]< theta)
				{
					Profile_Distance[i*Max_Vertices + j] = 1 - Users_distance[i*Max_Vertices + j] / theta;
				}
				else
				{
					Profile_Distance[i*Max_Vertices + j] = 0;
				}
				distance_users = 0;
			
		}
        
	}
    
    User_Distance = fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/UserProfile/UserProfile/User_Distance.txt", "w+");
	for (i = 0; i<Max_Vertices; i++) {
		for (j = 0; j<Max_Vertices; j++) {
			fprintf(User_Distance, "%f ", Users_distance[i*Max_Vertices + j]);
		}
    }
	fclose(User_Distance);
    
	Profile_distance = fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/UserProfile/UserProfile/Profile_Distance.txt", "w+");
	for (i = 0; i<Max_Vertices; i++) {
		for (j = 0; j<Max_Vertices; j++) {
			fprintf(Profile_distance, "%f ", Profile_Distance[i*Max_Vertices + j]);
		}
    }
    fclose(Profile_distance);
    
    for (i = 0; i<Max_Vertices; i++) {
		Tweet_Rate_day[i] = Gamma_Random_generator(5.0, 1.0);
	}
    
    User_Tweet_Rate = fopen("/Users/lishanshan/Documents/coevolutionary_netowrk/algorithm/UserProfile/UserProfile/user_tweet_rate.txt", "w+");
	for (i = 0; i<Max_Vertices; i++) {
		fprintf(User_Tweet_Rate, "%f ", Tweet_Rate_day[i]);
	}
    fclose(User_Tweet_Rate);
    
    free(Profile_Distance);
    free(Users_distance);
    free(Tweet_Rate_day);
    
    
    
    return 0;
}

double Beta_random_generator(double a, double b)

{
    
    double max_ab, min_ab, sum_ab, log_sum;
    
    double u1, u2, v, w, lambda, c, z, r, s, t;
    
    
    assert(a>0 && b>0);
    
    
    max_ab = (a >= b) ? a : b;
    min_ab = (a <= b) ? a : b;
    sum_ab = a + b;
    
    if (max_ab<0.5) {
        do
        {
            u1 = (double)rand() / RAND_MAX;
            u2 = (double)rand() / RAND_MAX;
            v = exp(log(u1) / a);
            w = exp(log(u2) / b);
            log_sum = (log(v)>log(w)) ? log(v) + log(1 + exp(log(w) - log(v))) : log(w) + log(1 + exp(log(v) - log(w)));
        } while (log_sum>0.0);
        assert(log(v) <= log_sum);
        return exp(log(v) - log_sum);
    }
    if (min_ab>1.0) {
        lambda = sqrt(sum_ab - 2.0) / (2.0*a*b - sum_ab);
        c = min_ab + 1.0 / lambda;
        do
        {
            u1 = (double)rand() / RAND_MAX;
            u2 = (double)rand() / RAND_MAX;
            v = lambda*log(u1 / (1.0 - u1));
            w = min_ab*exp(v);
            z = u1*u1*u2;
            r = c*v - 1.38629436112;
            s = min_ab + r - w;
            if (s + 2.609438 >= 5.0*z) break;
            t = log(z);
        } while (r + sum_ab*log(sum_ab / (max_ab + w))<t);
        return (a == min_ab) ? w / (w + max_ab) : max_ab / (w + max_ab);
    }
    if (max_ab >= 1.0) {
        t = (1 - min_ab) / (1 + max_ab - min_ab);
        r = max_ab*t / (max_ab*t + min_ab*pow(1 - t, max_ab));
        for (;;)
        {
            u1 = (double)rand() / RAND_MAX;
            u2 = (double)rand() / RAND_MAX;
            if (u1<r) {
                w = t*pow(u1 / r, 1 / min_ab);
                if (log(u2)<(max_ab - 1)*log(1 - w)) break;
            }
            else
            {
                w = 1 - (1 - t)*pow((1 - u1) / (1 - r), 1 / max_ab);
                if (log(u2)<(min_ab - 1)*log(w / t)) break;
            }
        }
        return (a == min_ab) ? w : (1 - w);
    }
    else
    {
        if (min_ab == 1.0) {
            t = r = 0;
        }
        else
        {
            t = 1 / (1 + sqrt(max_ab*(1 - max_ab) / (min_ab*(1 - min_ab))));
            r = max_ab*t;
        }
        for (;;) {
            u1 = (double)rand() / RAND_MAX;
            u2 = (double)rand() / RAND_MAX;
            if (u1<r) {
                w = t*pow(u1 / r, 1 / min_ab);
                if (log(u2)<(max_ab - 1)*log((1 - w) / (1 - t))) break;
            }
            else
            {
                w = 1 - (1 - t)*pow((1 - u1) / (1 - r), 1 / max_ab);
                if (log(u2)<(min_ab - 1)*log(w / t)) break;
            }
            
        }
        return (a == min_ab) ? w : (1 - w);
    }
}


double Gamma_Random_generator(double alpha, double beta)
{
    double Gamma_Random(double a);
    double X = 0, U;
    
    
    
    if (alpha >= 1) {
        if (beta == 1) {
            X = Gamma_Random(alpha);
            
        }
        else
        {
            X = Gamma_Random(alpha)*beta;
            
        }
        
    }
    if (alpha<1 && alpha>0) {
        if (beta == 1) {
            X = Gamma_Random(alpha + 1.0);
            U = (double)rand() / RAND_MAX;
            X = X*pow(U, 1 / alpha);
        }
        else
        {
            X = Gamma_Random(alpha + 1.0);
            U = (double)rand() / RAND_MAX;
            X = X*pow(U, 1 / alpha)*beta;
        }
        
    }
    
    return X;
    
}

double Gamma_Random(double a)
{
    double Box_Muller_Gaussian_random(double m, double s);
    double c, d, Z, U, V, X = 0;
    if (a >= 1) {
        d = a - 1 / 3;
        c = 1 / sqrt(9 * d);
        do {
            Z = Box_Muller_Gaussian_random(0, 1);
            U = (double)rand() / RAND_MAX;
            V = pow(1 + c*Z, 3);
            X = d*V;
        } while (Z <= -1 / c || log(U) >= 1 / 2 * pow(Z, 2) + d - d*V + d*log(V));
    }
    return X;
}

double Box_Muller_Gaussian_random(double m, double s)
{
    double x1, x2, w, y1, y2;
    do{
        x1 = 2.0*(double)rand() / RAND_MAX - 1.0;
        x2 = 2.0*(double)rand() / RAND_MAX - 1.0;
        w = x1*x1 + x2*x2;
    } while (w>1.0 || w == 0);
    w = sqrt((-2.0*log(w)) / w);
    y1 = x1*w;
    y2 = x2*w;
    return  m + y1 * s;
    
}
