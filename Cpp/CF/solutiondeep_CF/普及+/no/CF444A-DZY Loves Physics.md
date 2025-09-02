# 题目信息

# DZY Loves Physics

## 题目描述

DZY loves Physics, and he enjoys calculating density.

Almost everything has density, even a graph. We define the density of a non-directed graph (nodes and edges of the graph have some values) as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/a425e0bd8ecdace80b53301f0ed617a22d06cb47.png) where $ v $ is the sum of the values of the nodes, $ e $ is the sum of the values of the edges.Once DZY got a graph $ G $ , now he wants to find a connected induced subgraph $ G' $ of the graph, such that the density of $ G' $ is as large as possible.

An induced subgraph $ G'(V',E') $ of a graph $ G(V,E) $ is a graph that satisfies:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/205d30887fed54bfaabe37b0daf749cd5804bf34.png);
- edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/7ea118e128a0519e2d5be64db2d60ebfb7343781.png) if and only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/ea6ddeec58cbe4a1da10914bab9d3a37e180ee3e.png), and edge ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/a10ab0808c4b5f03a82ae1ae0a40b33ad030284e.png);
- the value of an edge in $ G' $ is the same as the value of the corresponding edge in $ G $ , so as the value of a node.

Help DZY to find the induced subgraph with maximum density. Note that the induced subgraph you choose must be connected.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF444A/3a3e9eb2a63d273e409ca45b73267a13b68b4d42.png)

## 说明/提示

In the first sample, you can only choose an empty subgraph, or the subgraph containing only node $ 1 $ .

In the second sample, choosing the whole graph is optimal.

## 样例 #1

### 输入

```
1 0
1
```

### 输出

```
0.000000000000000
```

## 样例 #2

### 输入

```
2 1
1 2
1 2 1
```

### 输出

```
3.000000000000000
```

## 样例 #3

### 输入

```
5 6
13 56 73 98 17
1 2 56
1 3 29
1 4 42
2 3 95
2 4 88
3 4 63
```

### 输出

```
2.965517241379311
```

# AI分析结果

### 题目内容
# DZY喜欢物理

## 题目描述
DZY喜欢物理，他喜欢计算密度。
几乎所有东西都有密度，甚至图也有。我们定义一个无向图（图的节点和边都有一些值）的密度如下：
\[ \frac{v}{e} \]
其中 \( v \) 是节点值的总和， \( e \) 是边值的总和。有一次DZY得到了一个图 \( G \) ，现在他想找到图 \( G \) 的一个连通诱导子图 \( G' \) ，使得 \( G' \) 的密度尽可能大。
图 \( G(V, E) \) 的诱导子图 \( G'(V', E') \) 是一个满足以下条件的图：
- \( V' \subseteq V \) ；
- 边 \( (u, v) \in E' \) 当且仅当 \( u, v \in V' \) ，且边 \( (u, v) \in E \) ；
- \( G' \) 中一条边的值与 \( G \) 中相应边的值相同，节点的值也是如此。
帮助DZY找到密度最大的诱导子图。注意，你选择的诱导子图必须是连通的。

## 说明/提示
在第一个样例中，你只能选择一个空图，或者只包含节点1的子图。
在第二个样例中，选择整个图是最优的。

## 样例 #1
### 输入
```
1 0
1
```
### 输出
```
0.000000000000000
```

## 样例 #2
### 输入
```
2 1
1 2
1 2 1
```
### 输出
```
3.000000000000000
```

## 样例 #3
### 输入
```
5 6
13 56 73 98 17
1 2 56
1 3 29
1 4 42
2 3 95
2 4 88
3 4 63
```
### 输出
```
2.965517241379311
```

### 算法分类
贪心

### 综合分析与结论
这几道题解都围绕寻找图中密度最大的连通诱导子图展开，核心思路均为证明最优解是一条两节点链，从而通过贪心策略解决问题。不同之处在于证明过程和阐述方式。

### 所选的题解
- **一铭君一（5星）**
  - **关键亮点**：详细且易懂地证明了环中一定包含一条链比它优，长链中一定包含一个短链比它优，通过严谨的数学推导，从环与链、长链与短链的比较得出最优解为两节点链，逻辑清晰。
  - **个人心得**：无
  - **重点代码**：无（未提供代码），核心实现思想为读边时扫点求值，维护最大密度值。
- **loctopus（4星）**
  - **关键亮点**：先证明选出的子图不含环，再通过推导得出加边使密度增大的条件，进而得出只选择密度最大的一条边的解题策略，思路较为清晰，还给出了CF原题解通道。
  - **个人心得**：无
  - **重点代码**：
```c++
#include<cstdio>
#include<iostream>
#define N 550
using namespace std;
int n,m,a,b;
double x[N],c,ans=0;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lf",&x[i]);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%lf",&a,&b,&c);
        ans=max(ans,(x[a]+x[b])/c);
    }
    printf("%.15lf",ans);
    return 0;
}
```
  - **核心代码片段**：读入节点数 \( n \) 和边数 \( m \) 以及各节点权值，遍历每条边，计算以该边及其两端点构成子图的密度并更新最大值，最后输出最大密度。
- **XL4453（4星）**
  - **关键亮点**：从直觉出发，通过数学推导证明新加入点使价值增大时，单独选择一条边更优，进而证明只选一条边的贪心策略的正确性，逻辑连贯。
  - **个人心得**：无
  - **重点代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,v[505],x,y,z;
double ans;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&v[i]);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        ans=max(ans,((double)v[x]+(double)v[y])/(double)z);
    }
    printf("%.15lf",ans);
    return 0;
}
```
  - **核心代码片段**：读入图的信息，遍历每条边，计算并更新以该边两端点构成子图的密度最大值，最后输出结果。

### 最优关键思路或技巧
通过数学证明得出最优解一定是一条两节点链，从而采用贪心策略，在遍历所有边时，计算每条边及其两端点构成子图的密度，取最大值。

### 可拓展之处
同类型题常围绕图的子结构性质及优化目标展开，类似算法套路是通过数学推导证明某种局部最优结构，进而利用贪心策略求解。

### 推荐洛谷题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：经典贪心题目，通过每次合并最小的两堆果子，求最小总代价。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需分析游戏规则，利用贪心策略找到最优策略。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过数学推导得出贪心排序策略，进而解决问题。 

---
处理用时：47.24秒