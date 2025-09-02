# Two Circles

## 题目描述

假设我们有一个 $ n \times m $ 的表格，其中每个单元格都填有一个整数。我们用 $ (i, j) $ 表示第 $ i $ 行第 $ j $ 列的单元格。因此，$ (1, 1) $ 是表格的左上角单元格，而 $ (n, m) $ 是右下角单元格。假设一个以 $ (i_0, j_0) $ 为中心、半径为 $ r $ 的圆包含了所有满足 $(i - i_0)^2 + (j - j_0)^2 \leq r^2$ 的单元格 $ (i, j) $。我们只考虑那些不超出表格边界的圆，即满足 $ r+1 \leq i_0 \leq n-r $ 和 $ r+1 \leq j_0 \leq m-r $ 的圆。

如图所示是一个以 $ (4, 5) $ 为中心、半径为 3 的圆。我们的任务是找到两个不同的、彼此不相交的圆，它们的半径均为 $ r $，且这两个圆所包含的数字之和最大。注意，如果两个圆有公共单元格，则认为它们是相交的。由于可能有多种选择使得两个圆的数值之和达到最大，因此我们还需要计算这样的圆对的数量。对于一个无序的圆对（例如，两个圆的中心分别为 $ (3, 4) $ 和 $ (7, 7) $），它与中心分别为 $ (7, 7) $ 和 $ (3, 4) $ 的圆对视为相同的一对。

## 样例 #1

### 输入

```
2 2 0
1 2
2 4
```

### 输出

```
6 2
```

## 样例 #2

### 输入

```
5 6 1
4 2 1 3 2 6
2 3 2 4 7 2
5 2 2 1 1 3
1 4 3 3 6 4
5 1 4 2 3 2
```

### 输出

```
34 3
```

## 样例 #3

### 输入

```
3 3 1
1 2 3
4 5 6
7 8 9
```

### 输出

```
0 0
```

# 题解

## 作者：lotus_grow (赞：1)

题意

给一个 $n*m$ 大小的矩阵，位置 $(i,j)$ 上的数为 $a[i][j]$ 。现有一个整数 $r$ ，求在矩阵中两个不相交的半径为 $r$ 的圆内所有位置元素的和的最大值。

感想

这道题真 $^{_T}$ $^{_M}$恶心，想法不难，细节一堆......

思路

1. 求半径为 $r$ 的圆的形状。

	设 $h[i]$ 表示离圆心 $i$ 行时这个圆能往一个方向占 $h[i]$ 列。
    
1. 求每一行的前缀和 。

1. 设 $p[i][j]$ 为以位置 $(i,j)$ 为圆心的圆内元素的和。
	
      $mxl[i][j]$ 为第 $i$ 行前 $j$ 个 $p[i][j]$ 的最大值，$mxr[i][j]$ 为第 $i$ 行后 $j$ 个 $p[i][j]$ 的最大值。
      
      $pol[i][j]$ 为第 $i$ 行前 $j$ 个 $p[i][j]$ 取最大值的方案数，$por[i][j]$ 为第 $i$ 行后 $j$ 个 $p[i][j]$ 取最大值的方案数。

1. 设 $d[i]$ 为两圆心相差 $i$ 行时两圆心至少相差 $d[i]$ 列。   $(i<=2r)$

1. 那么枚举圆心位置 $(i,j)$ ，再枚举第二个圆心的行数 $k$ ，若 $|k-i|<=2r$ 则用 $d[i]$ 确定 $k$ 行能够用于更新的列数范围后利用 $mxl[i][j]$，$mxr[i][j]$，$pol[i][j]$，$por[i][j]$ 更新答案与方案数。若$|k-i|>2r$ ，直接用 $k$ 行的最大值来更新答案与方案数。（因为无论如何两圆都不相交）

代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

int d[510],h[510];
long long s[510][510],p[510][510],mxl[510][510],pol[510][510],mxr[510][510],por[510][510];
int n,m,r,x;
long long ans,cnt;

int main()
{
    scanf("%d%d%d",&n,&m,&r);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        scanf("%d",&x);
        s[i][j]=s[i][j-1]+x;
    }
    h[0]=r;
    for(int i=1;i<=r;i++)
    h[i]=(int)sqrt(r*r-i*i);
    for(int i=0;i<=2*r;i++)
    for(int j=0;j<=r;j++)
    if(j>=i-r) d[i]=max(d[i],h[j]+h[abs(i-j)]+1);
    for(int i=r+1;i<=n-r;i++)
    for(int j=r+1;j<=m-r;j++)
    for(int k=-r;k<=r;k++)
    p[i][j]+=s[i+k][j+h[abs(k)]]-s[i+k][j-h[abs(k)]-1];
    for(int i=r+1;i<=n-r;i++)
    for(int j=r+1;j<=m-r;j++)
    {
        mxl[i][j]=mxl[i][j-1],pol[i][j]=pol[i][j-1];
        if(p[i][j]>mxl[i][j]) mxl[i][j]=p[i][j],pol[i][j]=1;
        else if(p[i][j]==mxl[i][j]) pol[i][j]++;
    }
    for(int i=r+1;i<=n-r;i++)
    for(int j=m-r;j>=r+1;j--)
    {
        mxr[i][j]=mxr[i][j+1],por[i][j]=por[i][j+1];
        if(p[i][j]>mxr[i][j]) mxr[i][j]=p[i][j],por[i][j]=1;
        else if(p[i][j]==mxr[i][j]) por[i][j]++;
    }
    for(int i=r+1;i<=n-r;i++)
    for(int j=r+1;j<=m-r;j++)
    {
        long long res=p[i][j];
        for(int k=r+1;k<=n-r;k++)
        {
            if(abs(k-i)>=2*r+1)
            {
                if(res+mxl[k][m-r]>ans) ans=res+mxl[k][m-r],cnt=pol[k][m-r];
                else if(res+mxl[k][m-r]==ans) cnt+=pol[k][m-r];
                continue;
            }
            if(j-d[abs(k-i)]>=r+1)
            if(res+mxl[k][j-d[abs(k-i)]]>ans) ans=res+mxl[k][j-d[abs(k-i)]],cnt=pol[k][j-d[abs(k-i)]];
            else if(res+mxl[k][j-d[abs(k-i)]]==ans) cnt+=pol[k][j-d[abs(k-i)]];
            if(j+d[abs(k-i)]<=m-r)
            if(res+mxr[k][j+d[abs(k-i)]]>ans) ans=res+mxr[k][j+d[abs(k-i)]],cnt=por[k][j+d[abs(k-i)]];
            else if(res+mxr[k][j+d[abs(k-i)]]==ans) cnt+=por[k][j+d[abs(k-i)]];
        }
    }
    printf("%lld %lld",ans,cnt>>1);
    return 0;
}
```

后记

WA时的我



[![image.png](https://s22.postimg.cc/ealnh7xq9/image.png)](https://postimg.cc/image/653lj29h9/)


AC了的我




[![image.png](https://s22.postimg.cc/yhz39pq4h/image.png)](https://postimg.cc/image/l124qufst/)




---

