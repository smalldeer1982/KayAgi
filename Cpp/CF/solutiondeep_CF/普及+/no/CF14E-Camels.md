# 题目信息

# Camels

## 题目描述

Bob likes to draw camels: with a single hump, two humps, three humps, etc. He draws a camel by connecting points on a coordinate plane. Now he's drawing camels with $ t $ humps, representing them as polylines in the plane. Each polyline consists of $ n $ vertices with coordinates $ (x_{1},y_{1}) $ , $ (x_{2},y_{2}) $ , ..., $ (x_{n},y_{n}) $ . The first vertex has a coordinate $ x_{1}=1 $ , the second — $ x_{2}=2 $ , etc. Coordinates $ y_{i} $ might be any, but should satisfy the following conditions:

- there should be $ t $ humps precisely, i.e. such indexes $ j $ ( $ 2<=j<=n-1 $ ), so that $ y_{j-1}&lt;y_{j}&gt;y_{j+1} $ ,
- there should be precisely $ t-1 $ such indexes $ j $ ( $ 2<=j<=n-1 $ ), so that $ y_{j-1}&gt;y_{j}&lt;y_{j+1} $ ,
- no segment of a polyline should be parallel to the $ Ox $ -axis,
- all $ y_{i} $ are integers between 1 and 4.

For a series of his drawings of camels with $ t $ humps Bob wants to buy a notebook, but he doesn't know how many pages he will need. Output the amount of different polylines that can be drawn to represent camels with $ t $ humps for a given number $ n $ .

## 说明/提示

In the first sample test sequences of $ y $ -coordinates for six camels are: 123421, 123431, 123432, 124321, 134321 и 234321 (each digit corresponds to one value of $ y_{i} $ ).

## 样例 #1

### 输入

```
6 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 骆驼

## 题目描述
鲍勃喜欢画骆驼：单峰、双峰、三峰等等。他通过在坐标平面上连接点来画骆驼。现在他正在画有 $t$ 个驼峰的骆驼，并将它们表示为平面上的折线。每条折线由 $n$ 个顶点组成，坐标为 $(x_{1},y_{1})$ ，$(x_{2},y_{2})$ ，...，$(x_{n},y_{n})$ 。第一个顶点的横坐标 $x_{1}=1$ ，第二个顶点的横坐标 $x_{2}=2$ ，依此类推。纵坐标 $y_{i}$ 可以是任意值，但需满足以下条件：
- 恰好有 $t$ 个驼峰，即存在这样的索引 $j$（$2\leq j\leq n - 1$），使得 $y_{j - 1}<y_{j}>y_{j + 1}$ 。
- 恰好有 $t - 1$ 个这样的索引 $j$（$2\leq j\leq n - 1$），使得 $y_{j - 1}>y_{j}<y_{j + 1}$ 。
- 折线的任何线段都不与 $Ox$ 轴平行。
- 所有的 $y_{i}$ 都是介于 1 到 4 之间的整数。

对于他画的一系列有 $t$ 个驼峰的骆驼，鲍勃想买一个笔记本，但他不知道需要多少页。请输出对于给定的 $n$，可以画出多少种不同的折线来表示有 $t$ 个驼峰的骆驼。

## 说明/提示
在第一个样例测试中，六只骆驼的 $y$ 坐标序列为：123421、123431、123432、124321、134321 和 234321（每个数字对应一个 $y_{i}$ 的值）。

## 样例 #1
### 输入
```
6 1
```
### 输出
```
6
```

## 样例 #2
### 输入
```
4 2
```
### 输出
```
0
```

### 算法分类
动态规划

### 综合分析与结论
这些题解均围绕动态规划展开，核心思路是通过定义合适的状态和状态转移方程来计算满足条件的折线数量。各题解的主要区别在于状态的定义方式，有的从转折点数量出发，有的从驼峰、波谷数量结合位置信息来定义，还有的考虑了上升下降趋势等。解决难点在于如何准确地定义状态以满足题目条件，并推导出正确的状态转移方程。

### 所选的题解
- **作者：叶枫 (5星)**
    - **关键亮点**：思路清晰，将问题分解为求转折点数量，通过三维DP数组`dp[x][y][t]`表示当最后一点落在`(x,y)`上时，出现`t`个转折点的总数，状态定义简洁高效，代码实现简洁明了。
    - **重点代码**：
```cpp
int dp[25][5][25];
signed main(){
    for(int i=1;i<=3;i++) dp[1][i][0]=1;
    for(int x=2;x<22;x++)
        for(int y=1;y<=4;y++)
            for(int t=0;t<21;t++)
                for(int h=1;h<=4;h++){
                    if(x==2){
                        if(y>h){
                            if(t%2) dp[2][y][t+1]+=dp[1][h][t];
                            else dp[2][y][t]+=dp[1][h][t];
                        }
                    }
                    else{
                        if(t%2){
                            if(h>y) dp[x][y][t]+=dp[x-1][h][t];
                            else if(h<y) dp[x][y][t+1]+=dp[x-1][h][t];
                        }
                        else{
                            if(h<y) dp[x][y][t]+=dp[x-1][h][t];
                            else if(h>y) dp[x][y][t+1]+=dp[x-1][h][t];
                        }
                    }
                }
    int n=read(),t=read();
    if(t*2+1>n||n>6*t+1) return puts("0"),0;
    int ans=0;
    for(int i=1;i<=4;i++)
        ans+=dp[n][i][2*t-1];
    printf("%d",ans); 
    return 0;
}
```
    - **核心实现思想**：初始化`dp[1][i][0]`，通过四层循环进行状态转移，根据`t`的奇偶性以及当前点与前一点的高度关系更新`dp`数组，最后根据输入的`n`和`t`计算并输出结果。
- **作者：ZJMZJM (5星)**
    - **关键亮点**：状态定义直观，使用四维数组`f[i][j][k][r]`表示第`i`个数为`j`时在第`k`个驼峰上处于`r=1`上升、`r=0`下降状态的方案数，通过四层`for`循环实现状态转移，代码简洁易懂。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define For(k,i,j) for(int k=i;k<=j;k++)
#pragma GCC optimize(4)
#define MAXN 20
#define MAXT 10
#define MAXK 4
#define MAXR 2
using namespace std;
inline int read()
{
    char ch;
    int res=1;
    while((ch=getchar())<'0'||ch>'9') if(ch=='-') res=-1;
    res*=ch-48;
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-48;
    return res;
}
int f[MAXN+2][MAXK+2][MAXT+2][MAXR+2];
int main()
{   
    int n=read(),t=read(),ans;
    f[2][2][1][1]=1;
    f[2][3][1][1]=2;
    f[2][4][1][1]=3;
    For(i,3,n)
        For(j,1,4)
            For(k,1,t) 
            {
                for(int r=4;r>j;r--)
                    f[i][j][k][0]+=f[i-1][r][k][0]+f[i-1][r][k][1];
                For(r,1,j-1)
                    f[i][j][k][1]+=f[i-1][r][k][1]+f[i-1][r][k-1][0];
            }
    For(i,1,MAXK)
        ans+=f[n][i][t][0];
    printf("%d\n",ans);
    return 0;
}
```
    - **核心实现思想**：初始化`f[2][j][1][1]`的值，通过四层循环，根据当前点与前一点的大小关系，更新处于不同状态的方案数，最后累加`f[n][i][t][0]`得到结果。
- **作者：starrylasky (4星)**
    - **关键亮点**：状态定义详细，`f_{i,j,k,p,q}`表示到第`i`个，有`j`个`a_{i - 1}>a_i<a_{i + 1}` ，`k`个`a_{i - 1}<a_i>a_{i + 1}` ，当前位置取`p` ，`q:a_{i - 1}<a_i:0,a_{i - 1}>a_i:1`，转移方程清晰，代码注释详细。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
#define fep(i,l,r) for(re int i=l;i<=r;++i)
#define For(i,u) for(re int i=head[u];i;i=e[i].nxt)
#define feb(i,r,l) for(re int i=r;i>=l;--i)
using namespace std;

const int N = 21,M = 11;
int f[N][M][M][5][2],n,t;

inline int read() { int s=0,w=1; char ch=getchar(); while(!(ch<='9'&&ch>='0')) {if(ch=='-') w=-1; ch=getchar();} while(ch<='9'&&ch>='0') {s=(s<<1)+(s<<3)+ch-'0'; ch=getchar();} return s*w; }
inline void write(int x) { if(x>=10) write(x/10); putchar(x%10+'0'); }
inline void print(int x,char ch) { if(x<0) putchar('-'),x=~(x-1); write(x);  putchar(ch);}
inline void swap(int &x,int &y) {x^=y,y^=x,x^=y;}

signed main()
{
    n=read(),t=read();
    if(n<=2) puts("0"),exit(0);
    fep(i,1,4) f[2][0][0][i][0]=i-1,f[2][0][0][i][1]=4-i;
    fep(i,3,n)
    {
        fep(j,0,t-1)
        {
            fep(k,0,t)
            {
                fep(p,1,4)
                {
                    fep(q,1,p-1) f[i][j][k][p][0]+=f[i-1][j][k][q][0]+f[i-1][j-1][k][q][1];
                    fep(q,p+1,4) f[i][j][k][p][1]+=f[i-1][j][k][q][1]+f[i-1][j][k-1][q][0];
                }
            }
        }
    }
    int ans=0;
    fep(p,1,4) ans+=f[n][t-1][t][p][0]+f[n][t-1][t][p][1];
    print(ans,'\n');
    return 0;
}
```
    - **核心实现思想**：初始化`f[2][0][0][i][0]`和`f[2][0][0][i][1]`，通过五层循环，依据当前位置与前一位置的大小关系及已满足的条件数量更新`f`数组，最后累加`f[n][t - 1][t][p][0]`和`f[n][t - 1][t][p][1]`得到答案。

### 最优关键思路或技巧
定义合适的状态是解决此类问题的关键。像叶枫题解中，通过巧妙地以转折点数量作为状态的一维，简化了状态转移的过程，使得代码实现简洁高效。同时，利用循环嵌套来遍历所有可能的情况，根据题目条件准确更新状态值。

### 拓展思路
此类题目属于动态规划中状态定义较为复杂的类型，可拓展到其他需要根据特定序列特征计数的问题，例如在一定规则下的序列生成计数问题。解题套路通常是根据题目给定的条件，挖掘序列中的关键特征，以此来定义状态，再根据特征之间的关系推导状态转移方程。

### 洛谷相似题目
- [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)：同样是通过动态规划求解路径和的最大值，需要合理定义状态和状态转移方程。
- [P1006 传纸条](https://www.luogu.com.cn/problem/P1006)：涉及二维空间中的动态规划，与本题类似，需考虑不同位置之间的状态转移关系。
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的背包问题，通过动态规划解决资源分配与价值最大化问题，有助于理解动态规划的应用。 

---
处理用时：134.02秒