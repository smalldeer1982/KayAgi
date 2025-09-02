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
- 所有边的权重都是整数，且范围在 $[1,10^{9}]$ （包含边界）内。
- 从顶点 $1$ 到顶点 $n$ 的最短路径长度是一个质数。
- 图的最小生成树（MST）的边权重之和是一个质数。
- 图中不包含环或重边。

如果你对题目陈述中的某些术语不熟悉，可以在注释部分找到它们的定义。

请帮助Jamie构造任意一个具有给定顶点数和边数的有趣图！

## 说明/提示
示例1的图：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/03021596e10dc8211f3fe958e7629dc3a97d37e7.png) 最短路径序列：$ {1,2,3,4} $ 。最小生成树的边用星号（*）标记。

题目陈述中使用的术语定义：
无向图中的最短路径是一个顶点序列 $ (v_{1},v_{2},...\ ,v_{k}) $ ，使得 $ v_{i} $ 与 $ v_{i+1} $ 相邻（$ 1\leq i < k $），并且权重之和 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916C/df0334815830e4f0c8788e37a58a6247ba52744b.png) 最小，其中 $ w(i,j) $ 是顶点 $ i $ 和 $ j $ 之间的边权重。（[https://en.wikipedia.org/wiki/Shortest\_path\_problem](https://en.wikipedia.org/wiki/Shortest_path_problem)）

质数是大于1的自然数，且除了1和它本身外没有其他正因数。（[https://en.wikipedia.org/wiki/Prime\_number](https://en.wikipedia.org/wiki/Prime_number)）

最小生成树（MST）是连通的、带边权的无向图的边的一个子集，它连接所有顶点，没有任何环，并且总边权尽可能小。（[https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree)）

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
这些题解的核心思路都是将最短路和最小生成树结合起来构造图。通过让大部分边权很大，留下一条从 $1$ 到 $n$ 的路径，使其边权和为质数，这条路径既是最短路也是最小生成树。不同题解在质数的选择和剩余边的连接方式上略有不同。

### 所选题解
- **作者：Fuko_Ibuki (赞：7)  ★★★★**
    - **关键亮点**：思路清晰，代码简洁，直接找出 $n - 1$ 条边连成所求的最短路和最小生成树，剩下边全连一个较大值。
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
- **作者：0xFF (赞：5)  ★★★★**
    - **关键亮点**：思路清晰，代码实现规范，详细说明了每一步的构造过程。
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
- **作者：yimuhua (赞：1)  ★★★★**
    - **关键亮点**：思路简洁明了，代码结构清晰，易于理解。
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

### 最优关键思路或技巧
- **思维方式**：将最短路和最小生成树结合起来，通过构造一条特殊的路径满足两者的条件。
- **代码实现技巧**：选择一个合适的质数，让路径上大部分边权为 $1$，调整第一条边的权值使路径和为质数，剩余边权设为很大的值。

### 可拓展之处
同类型题可以考虑不同的图的性质要求，如最长路径、次短路等，类似算法套路是通过构造特殊的图结构满足特定条件。

### 推荐题目
- [P1192 台阶问题](https://www.luogu.com.cn/problem/P1192)：考察递推和构造思想。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：涉及路径和的计算与构造。
- [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)：考察图的遍历和路径构造。

### 个人心得
题解中未包含个人心得内容。

---
处理用时：39.86秒