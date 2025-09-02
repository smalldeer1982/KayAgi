# The least round way

## 题目描述

给定由非负整数组成的 $n\times n$ 的正方形矩阵，你需要寻找一条路径：

+ 以左上角为起点。
+ 每次只能向右或向下走。
+ 以右下角为终点。
+ 如果我们把沿路遇到的数进行相乘，积应当以尽可能少的 $0$ 结尾。

## 样例 #1

### 输入

```
3
1 2 3
4 5 6
7 8 9
```

### 输出

```
0
DDRR
```

# 题解

## 作者：Loner_Knowledge (赞：42)

这是一道动态规划题

---

题目要求尾0数最少的路径与最少的尾随0个数，如果两个数字相乘后积有尾0有两种情况：两个数字的质因数集合中必有至少一对的2和5；两个数字至少一个为0。


**对于情况1**，我们可以使用动态规划的思想统计路径上取到最少的2与5因子个数的方案，定义`f[i][j]`为走到点`(i,j)`时最少取得给定因子的个数，`num[i][j]`表示`(i,j)`位置上给定因子的个数，转移方程即为：


$$f_{i,j}=min(f_{i,j-1},f_{i-1,j})+num_{i,j}$$


明显的，只有成对的2和5因子才能乘出一个尾0，于是最少的尾0个数$ans=min(f_{n,n,2},f_{n,n,5})$，输出路径可以使用递归函数实现。


**对于情况2**，如果矩阵中存在0，那么经过这个为0的位置的路径尾0个数恒为1，此时需要与情况1相比较，如果$ans>1$，那么输出经过0的路径，否则按照情况1处理。




```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int Inf=0x7FFFFFFF;
int n,t,num[1002][1002][2],f[1002][1002][2];
void Print(int i,int j,int k) {
    if(i==1&&j==1) {                //递归输出函数
        putchar(k? 'D':'R');
        return ;            //边界
    }
    if(i==1)
        Print(i,j-1,0);
    else if(j==1)
        Print(i-1,j,1);
    else if(f[i][j][t]==f[i][j-1][t]+num[i][j][t])
        Print(i,j-1,0);
    else
        Print(i-1,j,1);
    if(i!=n||j!=n)
        putchar(k? 'D':'R');    //在(n,n)处不输出
}
int main() {
    int ans;
    scanf("%d",&n);
    for(int i=1,k;i<=n;++i)
        for(int j=1;j<=n;++j) {        //预处理因子个数
            scanf("%d",&k);
            if(!k) {
                num[i][j][0]=num[i][j][1]=1;
                t=i;    //特判0，记录位置
            }
            else {
                for(;!(k%2);k/=2)
                    ++num[i][j][0];
                for(;!(k%5);k/=5)
                    ++num[i][j][1];
            }
        }
    for(int i=1;i<=n;++i)
        f[0][i][0]=f[i][0][0]=f[0][i][1]=f[i][0][1]=Inf;    //由于转移方程使用min，将边界赋为最大值
    f[1][1][0]=num[1][1][0];
    f[1][1][1]=num[1][1][1];
    for(int k=0;k<2;++k)
        for(int i=1;i<=n;++i)
            for(int j=i==1? 2:1;j<=n;++j)
                f[i][j][k]=min(f[i][j-1][k],f[i-1][j][k])+num[i][j][k];
    ans=min(f[n][n][0],f[n][n][1]);
    if(t&&ans>1) {            //情况2
        printf("1\n");
        for(int i=1;i<t;++i)
            putchar('D');
        for(int i=1;i<n;++i)
            putchar('R');
        for(int i=t;i<n;++i)
            putchar('D');
    }
    else {                    //情况1
        printf("%d\n",ans);
        t=!(f[n][n][0]<f[n][n][1]);
        Print(n,n,0);
    }
    return 0;
}
```

---

---

## 作者：Nepenthe (赞：9)

我们通过数学知识知道,后缀0代表该数是10的倍数,应由若干2*5产生

我们把每个格子里的数因数分解预处理出它包含的2和5的数量

即用$a[i][j][0]$表示因子中2的数量,用$a[i][j][1]$表示因子中5的数量

则问题转化为:从左上角到右下角找一条路径,使得路过的min(2,5)最小
则dp方程很好设计:$$dp[i][j][0/1]=min(dp[i-1][j][0/1],dp[i][j-1][0/1])+a[i][j][0/1]$$
其中$dp[i][j][0]$表示从左上角到$(i,j)$经过的最少2数,$dp[i][j][1]$表示从左上角到$(i,j)$经过的最少5数,还要用c数组记录路径(或者递归找路径)

$!$ 注意:如果出现0,经过它的路径就会只有1个后缀0,但是可能找到没有后缀0的路径,所以我们先把0当成10

**Code**
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define MAX 1007

using namespace std;

int n,x;
int dp[2][MAX][MAX];
int p[2][MAX][MAX];

void print ( int x , int y , int k , int f  ) {
    if ( x == 1 && y == 1 );
    else if ( x == 1 ) print ( x , y-1 , k , 0);
    else if ( y == 1 ) print ( x-1 , y , k , 1);
    else {
        if ( dp[k][x][y] == dp[k][x-1][y] + p[k][x][y] )
            print ( x-1 , y , k , 1 );
        else print ( x , y-1 , k , 0);
    }
    if ( f == 3 ) return;
    printf ( "%c" , f?'D':'R' );
}

int main ( ) {
    while ( ~scanf ( "%d" , &n ) ) {
        int flag = 0,a,b;
        for ( int i = 1 ; i <= n ; i++ )
            for ( int j = 1 ; j <= n ; j++ ) {
                scanf ( "%d" , &x );
                if ( !x ) {
                    flag = 1;
                    p[0][i][j]++;
                    p[1][i][j]++;
                    a = i , b = j;
                    continue;
                }
                while ( x%2 == 0 ) {
                    p[0][i][j]++;
                    x /= 2;
                }
                while ( x%5 == 0 ) {
                    p[1][i][j]++;
                    x /= 5;
                }
            }
        memset ( dp , 0x3f , sizeof ( dp ) );
        for ( int k = 0 ; k < 2 ; k++ )
            for ( int i = 1 ; i <= n ; i++ )
                for ( int j = 1 ; j <= n ; j++ ) {
                    if ( i-1 )
                        dp[k][i][j] = min ( dp[k][i][j] , dp[k][i-1][j] );
                    if ( j-1 )
                        dp[k][i][j] = min ( dp[k][i][j] , dp[k][i][j-1] );
                    if ( i == j && i == 1 )
                        dp[k][i][j] = 0;
                    dp[k][i][j] +=  p[k][i][j];
                }
        int ans = min ( dp[0][n][n] , dp[1][n][n] );
        if ( ans > 1 && flag ) {
            puts ( "1" );
            for ( int i = 1 ; i < a ; i++ )
                printf ( "%c" , 'D' );
            for ( int j = 1 ; j < b ; j++ )
                printf ( "%c" , 'R' );
            for ( int i = a ; i < n ; i++ )
                printf ( "%c" , 'D' );
            for ( int j = b ; j < n ; j++ )
                printf ( "%c" , 'R' );
            puts ( "" );
            continue;
        }
        printf ( "%d\n" , ans );
        if ( dp[0][n][n] < dp[1][n][n] )
            print ( n , n , 0 , 3 );
        else print ( n , n , 1 , 3 );
        puts ( "" );
    }
}

```


---

## 作者：zrzring (赞：2)

[更好的阅读体验](http://zrzring.cn/index.php/archives/257)

> 给定一个$n\times n$矩阵，找出一条路径使得经过的数的积后缀0最少

后缀$0$可以理解为$10^x$，考虑分解质因数$10 = 2 \times 5$，记录每个数分解质因数后有多少个$2$和$5$，这个过程可以dp实现

对于$0$则可以单独计算，然后和不经过$0$的答案比较就行了

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
#define p(dir) putchar(dir ? 'D' : 'R');
using namespace std;
void file() {
    freopen("std.in", "r", stdin);
    freopen("wa.out", "w", stdout);
}
const int N = 1e6 + 10, inf = 1e9;
inline int read() {
    bool sym = 0; int res = 0; char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}
int n, m, a[1001][1001][2], dp[1001][1001][2];
void print(int x, int y, int k, int dir) {
    if (x == 1 && y == 1) {p(dir); return;}
    if (x == 1) {print(x, y - 1, k, 0); p(dir); return;}
    if (y == 1) {print(x - 1, y, k, 1); p(dir); return;}
    if (dp[x][y][k] == dp[x - 1][y][k] + a[x][y][k]) {
        print(x - 1, y, k, 1); if (dir == -1) return; p(dir);   
    } else {
        print(x, y - 1, k, 0); if (dir == -1) return; p(dir);
    }
}
int main() {
    n = read(); int flag[2] = {0, 0}, zi = 0, zj = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x = read(); if (!x) {flag[0] = 1; zi = i; zj = j; a[i][j][0] = a[i][j][1] = 1; continue;}
            while (x % 2 == 0) ++a[i][j][0], x /= 2; while (x % 5 == 0) ++a[i][j][1], x /= 5;
        }
    }
    memset(dp, 0x3f, sizeof(dp)); dp[1][1][0] = dp[1][1][1] = 0;
    for (int k = 0; k <= 1; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i - 1) dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k]);
                if (j - 1) dp[i][j][k] = min(dp[i][j][k], dp[i][j - 1][k]);
                dp[i][j][k] += a[i][j][k];
            }
        }
    }
    if (min(dp[n][n][0], dp[n][n][1]) > 1 && flag[0]) {
        puts("1\n");
        for (int i = 1; i < zi; i++) printf("D");
        for (int i = 1; i < zj; i++) printf("R");
        for (int i = zi; i < n; i++) printf("D");
        for (int i = zj; i < n; i++) printf("R");
        return 0;
    }
    if (dp[n][n][0] < dp[n][n][1]) printf("%d\n", dp[n][n][0]), print(n, n, 0, -1);
    else printf("%d\n", dp[n][n][1]), print(n, n, 1, -1);
    return 0;
}
```

---

