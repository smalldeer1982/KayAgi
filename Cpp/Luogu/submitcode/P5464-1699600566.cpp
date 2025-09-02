#include<bits/stdc++.h>

using namespace std ;

#define N 3000
const int Mod = 1e9 + 7 ;

inline int read()
{
    int x = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9') { c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}

int n ;
int dp[N][N] , sum[N][N] , pre[N] ;

struct node{
    int L , R ;
}A[N] ;

bool operator < ( node a , node b ){ return a.R < b.R ; }

int main()
{
    n = read() ;

    for(int i = 1 ; i <= n ; i++ ) A[i].L = read() , A[i].R = read() ;
    sort( A + 1 , A + n + 1 ) ;


    for(int i = 1 ; i <= n ; i++ ){
        pre[i] = 0 ;
        for(int j = i - 1 ; j >= 1 ; j-- ){
            if( A[j].R < A[i].L ){
                pre[i] = j ;
                break ;
            }
        }
    }
    for(int i = 1 ; i <= n ; i++ ){
        for(int j = 1 ; j <= i - 1 ; j++ ){
            if( A[j].R < A[i].L ){
                sum[i][j] = sum[i][j - 1] ;
                continue ;
            }
            if( A[i].L > A[j].L ){
                //for(int k = 1 ; k <= j - 1 ; k++ ){ if( A[k].R < A[i].L ) dp[i][j] = ( dp[i][j] + dp[j][k] ) % Mod ; }
                dp[i][j] = 1 + sum[j][ pre[i] ] ;
            }else{
                //for(int k = 1 ; k <= j - 1 ; k++ ) if( A[k].R < A[j].L ) dp[i][j] = ( dp[i][j] + dp[i][k] ) % Mod ;
                dp[i][j] = 1 + sum[i][ pre[j] ] ;
            }
            if( dp[i][j] >= Mod ) dp[i][j] -= Mod ;
            sum[i][j] = dp[i][j] + sum[i][j - 1] ;
            if( sum[i][j] >= Mod ) sum[i][j] -= Mod ;
        }
    }
    int ans = 0 ;
    for(int i = 1 ; i <= n ; i++ ){
        ans = ans + sum[i][i - 1] ;
        if( ans >= Mod ) ans -= Mod ;
    }
    printf("%d\n" , ( ans + n ) % Mod ) ;

    return 0 ;
}