# 题目信息

# Diameter of Graph

## 题目描述

CQXYM wants to create a connected undirected graph with $ n $ nodes and $ m $ edges, and the diameter of the graph must be strictly less than $ k-1 $ . Also, CQXYM doesn't want a graph that contains self-loops or multiple edges (i.e. each edge connects two different vertices and between each pair of vertices there is at most one edge).

The diameter of a graph is the maximum distance between any two nodes.

The distance between two nodes is the minimum number of the edges on the path which endpoints are the two nodes.

CQXYM wonders whether it is possible to create such a graph.

## 说明/提示

In the first test case, the graph's diameter equal to 0.

In the second test case, the graph's diameter can only be 2.

In the third test case, the graph's diameter can only be 1.

## 样例 #1

### 输入

```
5
1 0 3
4 5 3
4 6 3
5 4 1
2 1 1```

### 输出

```
YES
NO
YES
NO
NO```

# AI分析结果

### 题目内容重写
CQXYM 想要创建一个包含 $n$ 个节点和 $m$ 条边的连通无向图，并且该图的直径必须严格小于 $k-1$。此外，CQXYM 不希望图中包含自环或多重边（即每条边连接两个不同的顶点，且每对顶点之间最多只有一条边）。

图的直径定义为图中任意两个节点之间的最大距离。

两个节点之间的距离是指连接这两个节点的路径中所经过的边数的最小值。

CQXYM 想知道是否有可能创建这样的图。

### 算法分类
构造、图论

### 题解分析与结论
各题解的核心思路都是通过构造图来满足题目条件，主要分为以下几种情况：
1. **图的连通性**：首先确保图是连通的，即边数 $m$ 至少为 $n-1$。
2. **边数的限制**：边数 $m$ 不能超过完全图的边数 $\frac{n(n-1)}{2}$。
3. **直径的限制**：通过构造菊花图或完全图来控制图的直径。

### 精选题解
#### 题解1：Gokix (5星)
**关键亮点**：
- 通过构造菊花图来控制直径，并详细讨论了不同 $k$ 值的情况。
- 代码简洁，逻辑清晰，涵盖了所有边界情况。

**代码核心实现**：
```cpp
if(m>n*(n-1)/2 || m<n-1 || k<0){
    cout<<"NO"<<endl;
    continue;
}
if(k==0){
    if(n==1){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
}
if(k>=2){
    cout<<"YES"<<endl;
    continue;
}
else if(k==1){
    if(m==n*(n-1)/2){
        cout<<"YES"<<endl;
        continue;
    }
    else{
        cout<<"NO"<<endl;
    }
}
```

#### 题解2：E1_de5truct0r (4星)
**关键亮点**：
- 详细描述了如何通过选取中心点并连边来控制直径。
- 提供了图示帮助理解构造过程。

**代码核心实现**：
```cpp
if(k<2 || m<n-1 || m>n*(n-1)/2){puts("nO");continue;}
if(k==2)
{
    if(n==1) puts("Yes");
    else puts("No");
    continue;
}
if(k==3)
{
    if(m==n*(n-1)/2) puts("Yes");
    else puts("No");
    continue;
}
else puts("yEs");
```

#### 题解3：ZolaWatle (4星)
**关键亮点**：
- 通过分类讨论不同 $k$ 值的情况，逻辑严谨。
- 特别强调了 $n=1$ 时的特殊情况。

**代码核心实现**：
```cpp
if(m<n-1 || k<=1 || m>n*(n-1)/2)
    cout << "NO" << endl;
if(m==0 && n==1)
    cout << "YES" << endl;
if(k==2 || (k==3 && (n*(n-1)/2!=m))) 
    cout << "NO" << endl;
else
    cout << "YES" << endl;
```

### 最优关键思路
通过构造菊花图或完全图来控制图的直径，确保图的连通性和边数的合理性。特别需要注意 $n=1$ 时的特殊情况。

### 可拓展之处
类似题目可以通过构造不同的图结构来满足特定的条件，如控制图的直径、连通性等。

### 推荐题目
1. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)
2. [P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)
3. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)

### 个人心得摘录
- **Gokix**：出题人通过数据整心态，需要特别注意边界情况。
- **E1_de5truct0r**：比赛时没想到简单的分支结构，导致思路混乱。
- **ZolaWatle**：$n=1$ 时的特殊情况容易被忽略，需要特别注意。

---
处理用时：28.11秒