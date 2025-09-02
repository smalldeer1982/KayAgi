# [USACO13FEB] Partitioning the Farm G

## 题目描述

Farmer John's farm is divided into an N x N square grid of pastures (2 <= N <= 15). Right now, there is a fence around the outside of the farm, but cows can move freely from pasture to pasture.

Farmer John has decided to build fences to separate the cows from each other. Because of zoning laws, each fence must be a horizontal or vertical line going across the entire farm and fences cannot go through pastures. Farmer John only has enough money to build at most K fences (1 <= K <= 2N - 2).

Farmer John wants to build the fences in order to minimize the size of the largest resulting group of cows (two cows are in the same group if they can reach each other without going through any fences). Given the current number of cows in each pasture, help Farmer John compute the size of the largest group of cows if he builds the fences optimally.

给出一个n\*n的矩阵，用k条水平或竖直直线分割矩阵，最小化区域和最大值。


## 说明/提示

Farmer John should build fences between columns 2 and 3 and between rows 2 and 3, which creates 4 groups each with 4 cows.


## 样例 #1

### 输入

```
3 2 
1 1 2 
1 1 2 
2 2 4 
```

### 输出

```
4 
```

# 题解

## 作者：巨型方块 (赞：4)

先二分答案嘛

然后我判断这个答案嘛

一看范围这么小嘛

那么我们爆搜i坐标，看在哪里分割；

再贪心得顺推j

在J上面尽可能少的划分

如果i的划分和j的划分结果>m

那就不行

i的搜索么直接大力压位

```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const int N=16;
int a[N][N],b[N][N],c[N][N];
bool ne[N];
int n,m,t;
bool check(int k,int v){
    int top=1,o;memset(c,0,sizeof c);
    for(int i=1;i<=n;i++){
        if(i>1&&((k>>(i-2))&1))top++;
        for(int j=1;j<=n;j++)c[top][j]+=b[i][j];        
    }
    if(top>m+1)return 0;o=m-top+1;
    for(int l=0,r=1;r<=n;r++)
        for(int i=1;i<=top;i++)
            if(c[i][r]-c[i][r-1]>v)return 0;else 
                if(c[i][r]-c[i][l]>v)l=r-1,o--;
    if(o<0)return 0;return 1;
}
int main()
{
    int l=0,r=0,mid,ans;bool ok;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)scanf("%d",&a[i][j]),r+=a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)b[i][j]=b[i][j-1]+a[i][j];
    t=(1<<(n-1));
    while(r>=l){
        mid=l+r>>1;ok=0;
        for(int i=0;i<t;i++)
            if(check(i,mid)){ok=1;break;}
        if(ok)ans=mid,r=mid-1;else l=mid+1;
    }
    printf("%d",ans);
}
但是这道题有一个更快的方法，可惜看不了别人代码，不知道怎么做，大家不妨想一想
```

---

## 作者：ccsc (赞：2)

对于本题：
	
    	我们要求的是用k条线，划分整个矩形，要求最小化最大值；
        
看一眼数据范围：$2<=N<=15$

然后就莫名和状压想到了一块……

我们想：他是类似于一种我拿刀划分一个矩形蛋糕的题

那我们就枚举每一行划了几刀，用二进制（状压思想）代表；

对于答案，我们不确定，，进行二分答案，然后check；

code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[17][17],b[17][17],c[17][17];
bool ne[17];
int n,m,t;
inline bool check(int k,int v)
{
    int top=1,o;
	memset(c,0,sizeof(c));
    for(register int i=1;i<=n;i++)
    {
        if(i>1&&((k>>(i-2))&1))top++;
        for(register int j=1;j<=n;j++)c[top][j]+=b[i][j];        
    }
    if(top>m+1)
        return 0;
    o=m-top+1;
    for(register int l=0,r=1;r<=n;r++)
    {
        for(register int i=1;i<=top;i++)
        {
            if(c[i][r]-c[i][r-1]>v)
                return 0;
            else
            {
                if(c[i][r]-c[i][l]>v)
                    l=r-1,o--;
            }
        }
    }
    if(o<0)return 0;return 1;
}
int main()
{
    int l=0,r=0,mid,ans;bool ok;
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=n;i++)
    {
        for(register int j=1;j<=n;j++)scanf("%d",&a[i][j]),r+=a[i][j];
    }
    for(register int i=1;i<=n;i++)
    {
        for(register int j=1;j<=n;j++)b[i][j]=b[i][j-1]+a[i][j];
    }
    t=(1<<n)-1;
    while(r>=l)
    {
        mid=(l+r)>>1;
		ok=0;
        for(register int i=0;i<t;i++)
        {
            if(check(i,mid))
            {
                ok=1;
                break;
            }
        }
        if(ok)
            ans=mid,r=mid-1;
        else
            l=mid+1;
    }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：冷月冰瞳 (赞：1)

枚举+动态规划。

我们先对水平直线进行枚举，最多是2^(N-1)种分割情况。对每种分割情况，在水平分割确定的情况下，在竖直方向上用动态规划求区域和最大值的最小值。

这个动态规划不难，F[i, j]表示前 i 列，切割了 j 次（最后一次切割在第 i 列右侧），那么 F[i, j] = min(max(F[k, j-1], calc\_max(k+1, i))，其中 calc\_max(s, t) 就是求第 s 列到第 t 列的区域和最大值（注意行的切割情况已经固定了）。


---

