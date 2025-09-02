# 题目信息

# Maximum Subrectangle

## 题目描述

You are given two arrays $ a $ and $ b $ of positive integers, with length $ n $ and $ m $ respectively.

Let $ c $ be an $ n \times m $ matrix, where $ c_{i,j} = a_i \cdot b_j $ .

You need to find a subrectangle of the matrix $ c $ such that the sum of its elements is at most $ x $ , and its area (the total number of elements) is the largest possible.

Formally, you need to find the largest number $ s $ such that it is possible to choose integers $ x_1, x_2, y_1, y_2 $ subject to $ 1 \leq x_1 \leq x_2 \leq n $ , $ 1 \leq y_1 \leq y_2 \leq m $ , $ (x_2 - x_1 + 1) \times (y_2 - y_1 + 1) = s $ , and $ $$ \sum_{i=x_1}^{x_2}{\sum_{j=y_1}^{y_2}{c_{i,j}}} \leq x. $ $$

## 说明/提示

Matrix from the first sample and the chosen subrectangle (of blue color):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/ea340f2e4123e359048067db39cb97e3a56962fb.png)Matrix from the second sample and the chosen subrectangle (of blue color):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/29ed72ba75c43c8c56e95a795caca1696bad260c.png)

## 样例 #1

### 输入

```
3 3
1 2 3
1 2 3
9
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 1
5 4 2 4 5
2
5
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# 最大子矩形

## 题目描述
给定两个正整数数组 $a$ 和 $b$，长度分别为 $n$ 和 $m$。
设 $c$ 是一个 $n \times m$ 的矩阵，其中 $c_{i,j} = a_i \cdot b_j$。
需要找到矩阵 $c$ 的一个子矩形，使得其元素之和至多为 $x$，且其面积（元素总数）尽可能大。
形式上，需要找到最大的数 $s$，使得可以选择整数 $x_1, x_2, y_1, y_2$，满足 $1 \leq x_1 \leq x_2 \leq n$，$1 \leq y_1 \leq y_2 \leq m$，$(x_2 - x_1 + 1) \times (y_2 - y_1 + 1) = s$，且 $\sum_{i=x_1}^{x_2}{\sum_{j=y_1}^{y_2}{c_{i,j}}} \leq x$。

## 说明/提示
第一个样例的矩阵和所选子矩形（蓝色部分）：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/ea340f2e4123e359048067db39cb97e3a56962fb.png)
第二个样例的矩阵和所选子矩形（蓝色部分）：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1060C/29ed72ba75c43c8c56e95a795caca1696bad260c.png)

## 样例 #1
### 输入
```
3 3
1 2 3
1 2 3
9
```
### 输出
```
4
```

## 样例 #2
### 输入
```
5 1
5 4 2 4 5
2
5
```
### 输出
```
1
```

### 综合分析与结论
所有题解都基于矩阵子矩形和的性质，利用乘法分配律将子矩形和转化为 $a$ 数组一段区间和与 $b$ 数组一段区间和的乘积。算法要点在于预处理出不同长度区间的最小和，以减少暴力枚举的复杂度。解决难点的关键在于优化枚举过程，避免 $O(n^4)$ 的暴力枚举。

### 所选的题解
- **作者：Bitter_Tea (5星)**
    - **关键亮点**：思路清晰，先点明利用乘法分配律转化问题，再详细说明预处理不同长度区间最小和的方法及代码实现，注释清晰，提醒开 `long long` 避免溢出。
    - **个人心得**：感叹似乎把小学乘法分配律知识遗忘。
    - **核心代码**：
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define ll long long
using namespace std;
const int N=2005;
int sa[N],sb[N],fa[N],fb[N];
int x,n,m,a,ans;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        sa[i]=sa[i-1]+a;
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&a);
        sb[i]=sb[i-1]+a;
    }
    memset(fa,0x3f,sizeof(fa));
    memset(fb,0x3f,sizeof(fb));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            fa[i-j+1]=min(fa[i-j+1],sa[i]-sa[j-1]);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=i;j++)
            fb[i-j+1]=min(fb[i-j+1],sb[i]-sb[j-1]);
    scanf("%d",&x);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if((ll)fa[i]*fb[j]<=x) ans=max(ans,i*j);
    printf("%d\n",ans);
    return 0;
}
```
核心实现思想：先对 $a$ 和 $b$ 数组求前缀和，再通过两层循环预处理出不同长度区间的最小和，最后枚举所有可能的区间长度组合，判断是否满足和的限制并更新最大面积。

- **作者：PR_CYJ (4星)**
    - **关键亮点**：同样清晰阐述利用乘法分配律化简式子，说明优化思路及贪心策略，代码简洁明了，也提醒开 `long long`。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3000;
int a[N],b[N],mina[N],minb[N];
int main()
{
    int n,m,t,k,ans=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>t;
        a[i]=a[i-1]+t;
    }
    for(int i=1;i<=m;i++)
    {
        cin>>t;
        b[i]=b[i-1]+t;
    }
    cin>>k;
    memset(mina,127,sizeof(mina));
    memset(minb,127,sizeof(minb));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            mina[i-j+1]=min(mina[i-j+1],a[i]-a[j-1]);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=i;j++)
            minb[i-j+1]=min(minb[i-j+1],b[i]-b[j-1]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if ((long long)(mina[i])*minb[j]<=k)
                ans=max(ans,i*j);
    cout<<ans<<endl;
}
```
核心实现思想：与上一题解类似，先求前缀和，预处理不同长度区间最小和，枚举区间长度组合更新最大面积。

### 最优关键思路或技巧
利用乘法分配律将子矩形和转化为两段数组区间和的乘积，通过预处理不同长度区间的最小和，以 $O(n^2)$ 的时间复杂度优化暴力枚举，避免不必要的计算。

### 可拓展之处
同类型题可考虑矩阵和相关的优化问题，类似算法套路为利用矩阵性质化简计算，通过预处理减少重复计算，优化暴力枚举过程。

### 洛谷相似题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：考察一维数组的最大子段和问题，与本题优化暴力枚举思想类似。
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：涉及二维矩阵中满足条件的最大正方形问题，可类比本题优化思路。
- [P2739 高楼序列](https://www.luogu.com.cn/problem/P2739)：通过预处理和优化枚举解决序列相关问题，与本题思路有相通之处。

### 个人心得摘录与总结
Bitter_Tea 感慨似乎遗忘小学乘法分配律知识，反映出基础知识在算法问题中的重要性，即使看似简单的知识也可能是解决复杂问题的关键。 

---
处理用时：30.13秒