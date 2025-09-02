# 题目信息

# Vitaly and Cycle

## 题目描述

After Vitaly was expelled from the university, he became interested in the graph theory.

Vitaly especially liked the cycles of an odd length in which each vertex occurs at most once.

Vitaly was wondering how to solve the following problem. You are given an undirected graph consisting of $ n $ vertices and $ m $ edges, not necessarily connected, without parallel edges and loops. You need to find $ t $ — the minimum number of edges that must be added to the given graph in order to form a simple cycle of an odd length, consisting of more than one vertex. Moreover, he must find $ w $ — the number of ways to add $ t $ edges in order to form a cycle of an odd length (consisting of more than one vertex). It is prohibited to add loops or parallel edges.

Two ways to add edges to the graph are considered equal if they have the same sets of added edges.

Since Vitaly does not study at the university, he asked you to help him with this task.

## 说明/提示

The simple cycle is a cycle that doesn't contain any vertex twice.

## 样例 #1

### 输入

```
4 4
1 2
1 3
4 2
4 3
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
0 1
```

## 样例 #3

### 输入

```
3 0
```

### 输出

```
3 1
```

# AI分析结果

### 题目内容
# 维塔利和环

## 题目描述
维塔利被大学开除后，对图论产生了兴趣。

维塔利特别喜欢长度为奇数且每个顶点最多出现一次的环。

维塔利想知道如何解决以下问题。给定一个由 $n$ 个顶点和 $m$ 条边组成的无向图，该图不一定连通，没有平行边和环。你需要找到 $t$，即必须添加到给定图中的最少边数，以形成一个长度为奇数且顶点数大于 1 的简单环。此外，他还必须找到 $w$，即添加 $t$ 条边以形成奇数长度环（顶点数大于 1）的方法数。禁止添加环或平行边。

如果两种添加边的方法具有相同的添加边集，则认为它们是相同的。

由于维塔利不再在大学学习，他请你帮他完成这项任务。

## 说明/提示
简单环是指不包含任何顶点两次的环。

## 样例 #1
### 输入
```
4 4
1 2
1 3
4 2
4 3
```
### 输出
```
1 2
```

## 样例 #2
### 输入
```
3 3
1 2
2 3
3 1
```
### 输出
```
0 1
```

## 样例 #3
### 输入
```
3 0
```
### 输出
```
3 1
```

### 算法分类
图论

### 题解综合分析与结论
这三道题解思路基本一致，均通过分类讨论加边数量来解决问题：
 - **加 3 条边**：当 $m = 0$ 时，从 $n$ 个点中选 3 个点连成环，方案数为 $C_{n}^{3}$。
 - **加 2 条边**：最大连通块大小小于 3 时，即存在多个大小为 2 的连通块，每个连通块可向非当前连通块的节点连两条边，方案数为 $(n - 2) \times m$。
 - **加 1 条边**：存在一个连通块内点数 $\geq 3$ 时，对连通块黑白染色，连接同色点可形成奇环，统计同色点对数作为方案数。
 - **加 0 条边**：图中已存在奇环，方案数为 1。

题解难点在于准确判断各种情况，并通过合适的算法实现，如利用染色 DFS 判断奇环、统计同色点等。

### 所选的题解
 - **作者：spider_oyster（5 星）**
   - **关键亮点**：思路清晰，代码简洁高效，利用染色 DFS 函数 `dfs` 同时完成奇环判断和同色点统计，整体逻辑连贯。
   - **个人心得**：做 30 个深蹲后思维格外清醒。
   - **重点代码**：
```cpp
bool dfs(int u,int col)
{
    if(~co[u]) return co[u]!=col;
    co[u]=col;
    col?c1++:c2++;
    bool f=0;
    for(int v:G[u]) f|=dfs(v,col^1);
    return f;
}
```
核心实现思想：对节点 `u` 进行染色，若已染色则判断颜色是否冲突；若未染色则染上当前颜色，并统计同色点数量，同时递归处理相邻节点，判断是否存在奇环。
 - **作者：Stream月（4 星）**
   - **关键亮点**：详细地对每种加边情况进行分析，逻辑严谨，代码实现虽然较冗长但注释详细，便于理解。
   - **重点代码**：
```cpp
bool dfs(int u, int c) {
    if(col[u]) {
        if(col[u]!= c) return false;
        return true;
    }
    col[u] = c;
    if(c == 1) ++b;
    else ++w;
    ++num;
    bool flag = true;
    int v;
    for(int i = head[u]; i; i = e[i].next) {
        v = e[i].to;
        flag &= dfs(v, -c);
    }
    return flag;
}
```
核心实现思想：类似染色 DFS，对节点 `u` 染色，统计同色点数量 `b` 和 `w`，并递归处理相邻节点，判断当前连通块是否存在奇环。
 - **作者：FL_sleake（4 星）**
   - **关键亮点**：对每种情况的分析详细，代码注释虽少但结构清晰，通过在 DFS 中传递参数 `len` 判断奇环的方式较为独特。
   - **重点代码**：
```cpp
void dfs(int x,int len){
    if(vis[x]){
        if(len-num[x]>=3&&(len-num[x])%2){
            cout<<"0 1"<<endl;
            exit(0);
        }
        return;
    }
    vis[x]=1,num[x]=len;
    if(num[x]%2) cnt_1++;
    else cnt_0++;
    for(int v:G[x]) dfs(v,len+1);
}
```
核心实现思想：在 DFS 过程中记录节点访问顺序 `num[x]`，当再次访问已访问节点时，通过 `len - num[x]` 判断是否形成奇环，并统计同色点数量。

### 最优关键思路或技巧
 - **染色 DFS**：通过对图进行染色，在遍历过程中判断是否存在奇环以及统计同色点数量，巧妙解决问题。
 - **分类讨论**：根据图的不同状态（边数、连通块大小等），细致地分类讨论加边情况，使问题逐步简化。

### 可拓展思路
此类题目属于图论中关于环的构造与计数问题，类似套路是先分析图的基本性质（连通性、边数等），再根据目标环的特点（长度、奇偶性等）进行分类讨论。同类型题目可能会改变环的条件，如要求特定长度的环，或者在有向图中寻找环等。

### 洛谷推荐题目
 - [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：同样涉及图的连通性与染色判断，可加深对图论基本操作的理解。
 - [P1345 凝聚核心](https://www.luogu.com.cn/problem/P1345)：需要判断图中是否存在奇环，与本题判断奇环思路类似。
 - [P2746 [USACO5.3]校园网Network of Schools](https://www.luogu.com.cn/problem/P2746)：图论相关问题，通过分析图的结构来解决，锻炼图论分析能力。

### 个人心得摘录与总结
 - **spider_oyster**：做 30 个深蹲后思维格外清醒。总结：适当运动可能有助于提升思维活跃度。 

---
处理用时：60.42秒