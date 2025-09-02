# 题目信息

# Jamie and Interesting Graph

## 题目描述

Jamie has recently found undirected weighted graphs with the following properties very interesting:

- The graph is connected and contains exactly $ n $ vertices and $ m $ edges.
- All edge weights are integers and are in range $ [1,10^{9}] $ inclusive.
- The length of shortest path from $ 1 $ to $ n $ is a prime number.
- The sum of edges' weights in the minimum spanning tree (MST) of the graph is a prime number.
- The graph contains no loops or multi-edges.

If you are not familiar with some terms from the statement you can find definitions of them in notes section.

Help Jamie construct any graph with given number of vertices and edges that is interesting!



## 说明/提示

The graph of sample 1: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/03021596e10dc8211f3fe958e7629dc3a97d37e7.png) Shortest path sequence: $ {1,2,3,4} $ . MST edges are marked with an asterisk (\*).

Definition of terms used in the problem statement:

A shortest path in an undirected graph is a sequence of vertices $ (v_{1},v_{2},...\ ,v_{k}) $ such that $ v_{i} $ is adjacent to $ v_{i+1} $ $ 1<=i<k $ and the sum of weight ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/df0334815830e4f0c8788e37a58a6247ba52744b.png) is minimized where $ w(i,j) $ is the edge weight between $ i $ and $ j $ . ([https://en.wikipedia.org/wiki/Shortest\_path\_problem](https://en.wikipedia.org/wiki/Shortest_path_problem))

A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself. ([https://en.wikipedia.org/wiki/Prime\_number](https://en.wikipedia.org/wiki/Prime_number))

A minimum spanning tree (MST) is a subset of the edges of a connected, edge-weighted undirected graph that connects all the vertices together, without any cycles and with the minimum possible total edge weight. ([https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree))

[https://en.wikipedia.org/wiki/Multiple\_edges](https://en.wikipedia.org/wiki/Multiple_edges)

## 样例 #1

### 输入

```
4 4
```

### 输出

```
7 7
1 2 3
2 3 2
3 4 2
2 4 4
```

## 样例 #2

### 输入

```
5 4
```

### 输出

```
7 13
1 2 2
1 3 4
1 4 3
4 5 4
```

# AI分析结果

### 题目中文重写
# Jamie和有趣的图

## 题目描述
Jamie最近发现具有以下性质的无向加权图非常有趣：
- 该图是连通的，并且恰好包含 $n$ 个顶点和 $m$ 条边。
- 所有边的权重都是整数，且范围在 $[1,10^{9}]$ （包含边界）。
- 从顶点 $1$ 到顶点 $n$ 的最短路径长度是一个质数。
- 该图的最小生成树（MST）的边权之和是一个质数。
- 该图不包含自环或重边。

如果你对题目陈述中的某些术语不熟悉，可以在注释部分找到它们的定义。

请帮助Jamie构造任何具有给定顶点数和边数的有趣图！

## 说明/提示
示例1的图：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/03021596e10dc8211f3fe958e7629dc3a97d37e7.png) 最短路径序列：$ {1,2,3,4} $ 。最小生成树的边用星号（*）标记。

题目陈述中使用的术语定义：
无向图中的最短路径是一个顶点序列 $ (v_{1},v_{2},...\ ,v_{k}) $ ，使得 $ v_{i} $ 与 $ v_{i+1} $ 相邻（$ 1\leq i<k $），并且边权之和 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/df0334815830e4f0c8788e37a58a6247ba52744b.png) 最小，其中 $ w(i,j) $ 是顶点 $ i $ 和 $ j $ 之间的边权。（[https://en.wikipedia.org/wiki/Shortest\_path\_problem](https://en.wikipedia.org/wiki/Shortest_path_problem)）
质数是大于1的自然数，除了1和它本身外没有其他正因数。（[https://en.wikipedia.org/wiki/Prime\_number](https://en.wikipedia.org/wiki/Prime_number)）
最小生成树（MST）是连通的、带权无向图的边的一个子集，它连接所有顶点，没有任何环，并且总边权尽可能小。（[https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree)）
[https://en.wikipedia.org/wiki/Multiple\_edges](https://en.wikipedia.org/wiki/Multiple_edges)

## 样例 #1
### 输入
```
4 4
```
### 输出
```
7 7
1 2 3
2 3 2
3 4 2
2 4 4
```

## 样例 #2
### 输入
```
5 4
```
### 输出
```
7 13
1 2 2
1 3 4
1 4 3
4 5 4
```

### 综合分析与结论
这些题解的核心思路都是将最短路和最小生成树结合起来，通过构造一条从 $1$ 到 $n$ 的路径，使其边权和为质数，同时让其他边的边权很大，保证这条路径既是最短路也是最小生成树。

#### 思路对比
- **固定质数法**：大部分题解直接选取一个大于 $10^5$ 的固定质数（如 $10^5 + 3$），让 $1$ 到 $2$ 的边权为该质数减去 $n - 2$，其余 $i$ 到 $i + 1$ 的边权为 $1$。
- **筛选质数法**：部分题解通过线筛预处理质数，然后二分查找大于等于 $n$ 的第一个质数。

#### 算法要点
1. **构造路径**：先构造从 $1$ 到 $n$ 的路径，使其边权和为质数。
2. **添加大边权边**：将剩余的边连接起来，边权设为很大的值（如 $10^9$），确保不影响最短路和最小生成树。

#### 解决难点
- **质数选择**：通过固定质数或筛选质数的方法，保证路径边权和为质数。
- **边的连接**：避免重边和自环，合理连接剩余的边。

### 所选题解
- **作者：Fuko_Ibuki（5星）**
    - **关键亮点**：思路清晰，代码简洁，直接选取固定质数，实现简单易懂。
    - **核心代码**：
```cpp
#include<cstdio>
int main()
{
    int n,m,p=1e5+3,i;
    scanf("%d%d",&n,&m);
    printf("%d %d\n1 2 %d\n",p,p,p-n+2);
    for (i=2;i<n;i++) printf("%d %d 1\n",i,i+1);
    m-=n-1;
    for (int k=0,j=n;m--;)
    {
        if (++j>n) j=++k+2;
        printf("%d %d 9999999\n",k,j);
    }
}
```
核心实现思想：先确定一个质数 $p$，让 $1$ 到 $2$ 的边权为 $p - n + 2$，其余相邻顶点间边权为 $1$，构成最短路和最小生成树，再连接剩余边，边权设为 $9999999$。

- **作者：0xFF（4星）**
    - **关键亮点**：代码规范，注释详细，思路与Fuko_Ibuki类似，使用了快速读入。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define ll long long
#define ull unsigned long long
using namespace std;
const int MAXN = 2010;
const int prime = 1e5+3; 
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
ll n,m,cnt;
int main(){
    n = read() , m = read();
    printf("%d %d\n1 2 %d\n",prime,prime,prime-n+2);
    for(int i=2;i<n;i++){
        printf("%d %d 1\n",i,i+1);
    }
    m -= (n-1);
    for(int i=0,j=n;m--;){
        if(++j > n) j = ++i+2;
        printf("%d %d 1000000000\n",i,j);
    }
    return 0;
}
```
核心实现思想：与Fuko_Ibuki的思路相同，只是使用了快速读入，并且将多余边的边权设为 $10^9$。

- **作者：yimuhua（4星）**
    - **关键亮点**：思路清晰，代码简洁，同样采用固定质数的方法。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int p = 1e5 + 3;
int n, m;
int main() {
    cin >> n >> m;
    cout << p << ' ' << p << "\n" << "1 2 " << p - n + 2 << "\n";
    for(int i = 2; i < n; i++)
        cout << i << ' ' << i + 1 << " 1\n";
    m -= n - 1;
    for(int i = 0, j = n; m--; ) {
        if(++j > n)
            j = ++i + 2;
        cout << i << ' ' << j << " 1000000000\n";
    }
    return 0;
}
```
核心实现思想：选取质数 $p$，构造最短路和最小生成树，再连接剩余边，边权为 $10^9$。

### 最优关键思路或技巧
- **路径构造**：将最短路和最小生成树结合，构造一条从 $1$ 到 $n$ 的路径，让其边权和为质数，其余边权设为很大的值。
- **质数选择**：直接选取一个大于 $10^5$ 的固定质数，简化质数的查找过程。

### 可拓展之处
同类型题可能会对图的性质有更多要求，如要求图是二分图、平面图等。类似算法套路可以应用于其他构造图的问题，关键在于合理设计边权，满足特定的条件。

### 推荐洛谷题目
1. [P1194 买礼物](https://www.luogu.com.cn/problem/P1194)：涉及图的构造和最小生成树的应用。
2. [P2872 [USACO07DEC]Building Roads S](https://www.luogu.com.cn/problem/P2872)：与最小生成树相关，需要构造图并求解最小生成树。
3. [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)：基础的最小生成树模板题，可加深对最小生成树算法的理解。

### 个人心得
题解中未包含个人心得内容。

---
处理用时：74.29秒