# 题目信息

# Weights Assignment For Tree Edges

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. Vertices are numbered from $ 1 $ to $ n $ . Any vertex can be the root of a tree.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root.

The tree is specified by an array of ancestors $ b $ containing $ n $ numbers: $ b_i $ is an ancestor of the vertex with the number $ i $ . The ancestor of a vertex $ u $ is a vertex that is the next vertex on a simple path from $ u $ to the root. For example, on the simple path from $ 5 $ to $ 3 $ (the root), the next vertex would be $ 1 $ , so the ancestor of $ 5 $ is $ 1 $ .

The root has no ancestor, so for it, the value of $ b_i $ is $ i $ (the root is the only vertex for which $ b_i=i $ ).

For example, if $ n=5 $ and $ b=[3, 1, 3, 3, 1] $ , then the tree looks like this.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611D/d1bc9693f3c37aa82543dc99b8156e197e08fb59.png)An example of a rooted tree for $ n=5 $ , the root of the tree is a vertex number $ 3 $ .You are given an array $ p $ — a permutation of the vertices of the tree. If it is possible, assign any positive integer weights on the edges, so that the vertices sorted by distance from the root would form the given permutation $ p $ .

In other words, for a given permutation of vertices $ p $ , it is necessary to choose such edge weights so that the condition $ dist[p_i]<dist[p_{i+1}] $ is true for each $ i $ from $ 1 $ to $ n-1 $ . $ dist[u] $ is a sum of the weights of the edges on the path from the root to $ u $ . In particular, $ dist[u]=0 $ if the vertex $ u $ is the root of the tree.

For example, assume that $ p=[3, 1, 2, 5, 4] $ . In this case, the following edge weights satisfy this permutation:

- the edge ( $ 3, 4 $ ) has a weight of $ 102 $ ;
- the edge ( $ 3, 1 $ ) has weight of $ 1 $ ;
- the edge ( $ 1, 2 $ ) has a weight of $ 10 $ ;
- the edge ( $ 1, 5 $ ) has a weight of $ 100 $ .

The array of distances from the root looks like: $ dist=[1,11,0,102,101] $ . The vertices sorted by increasing the distance from the root form the given permutation $ p $ .

Print the required edge weights or determine that there is no suitable way to assign weights. If there are several solutions, then print any of them.

## 说明/提示

The first set of input data of the example is analyzed in the main part of the statement.

In the second set of input data of the example, it is impossible to assign the positive weights to obtain a given permutation of vertices.

## 样例 #1

### 输入

```
4
5
3 1 3 3 1
3 1 2 5 4
3
1 1 2
3 1 2
7
1 1 2 3 4 5 6
1 2 3 4 5 6 7
6
4 4 4 4 1 1
4 2 1 5 6 3```

### 输出

```
1 10 0 102 100
-1
0 3 100 1 1 2 4
6 5 10 0 2 3```

# AI分析结果

### 题目翻译
# 树边的权重分配

## 题目描述
给定一棵由 $n$ 个顶点组成的有根树。顶点编号从 $1$ 到 $n$，任意顶点都可以作为树的根。

树是一个无环的连通无向图。有根树是一棵选定了一个顶点作为根的树。

这棵树由一个包含 $n$ 个数字的祖先数组 $b$ 来表示：$b_i$ 是编号为 $i$ 的顶点的祖先。顶点 $u$ 的祖先是从 $u$ 到根的简单路径上的下一个顶点。例如，在从 $5$ 到 $3$（根）的简单路径上，下一个顶点是 $1$，所以 $5$ 的祖先是 $1$。

根没有祖先，所以对于根来说，$b_i$ 的值是 $i$（根是唯一满足 $b_i = i$ 的顶点）。

例如，如果 $n = 5$ 且 $b = [3, 1, 3, 3, 1]$，那么这棵树如下图所示。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1611D/d1bc9693f3c37aa82543dc99b8156e197e08fb59.png)

这是一棵 $n = 5$ 的有根树示例，树的根是编号为 $3$ 的顶点。

给定一个数组 $p$，它是树中顶点的一个排列。如果可能的话，为树的每条边分配任意正整数权重，使得按到根的距离排序后的顶点形成给定的排列 $p$。

换句话说，对于给定的顶点排列 $p$，需要选择这样的边权重，使得对于从 $1$ 到 $n - 1$ 的每个 $i$，条件 $dist[p_i] < dist[p_{i + 1}]$ 都成立。$dist[u]$ 是从根到 $u$ 的路径上的边的权重之和。特别地，如果顶点 $u$ 是树的根，则 $dist[u] = 0$。

例如，假设 $p = [3, 1, 2, 5, 4]$。在这种情况下，以下边权重满足这个排列：
- 边 $(3, 4)$ 的权重为 $102$；
- 边 $(3, 1)$ 的权重为 $1$；
- 边 $(1, 2)$ 的权重为 $10$；
- 边 $(1, 5)$ 的权重为 $100$。

从根的距离数组如下：$dist = [1, 11, 0, 102, 101]$。按到根的距离递增排序的顶点形成给定的排列 $p$。

输出所需的边权重，或者确定没有合适的权重分配方法。如果有多个解，则输出其中任意一个。

## 说明/提示
示例的第一组输入数据在题目的主要部分进行了分析。

在示例的第二组输入数据中，不可能分配正权重来得到给定的顶点排列。

## 样例 #1
### 输入
```
4
5
3 1 3 3 1
3 1 2 5 4
3
1 1 2
3 1 2
7
1 1 2 3 4 5 6
1 2 3 4 5 6 7
6
4 4 4 4 1 1
4 2 1 5 6 3
```

### 输出
```
1 10 0 102 100
-1
0 3 100 1 1 2 4
6 5 10 0 2 3
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过构造边权来满足顶点按到根的距离排序后与给定排列相同的条件。首先都需要找到根节点，然后根据排列顺序判断是否能构造出合法的边权。如果某个节点的父节点在排列中出现的位置比该节点靠后，那么就无法构造出满足条件的边权。在确定可以构造的情况下，通过假设每个节点到根的距离，进而计算出每条边的权值。

### 所选题解
- **JCLinux（4星）**
    - **关键亮点**：思路清晰，对解题过程的解释详细，代码可读性高，有详细的注释，便于理解。
    - **个人心得**：无
- **Inui_Sana（4星）**
    - **关键亮点**：简洁地阐述了构造思路，并对边权为正的情况进行了证明，代码实现较为简洁。
    - **个人心得**：认为题目难度可能不止绿题难度。
- **智子（4星）**
    - **关键亮点**：明确指出了判断无解的两种情况，代码结构清晰。
    - **个人心得**：无

### 重点代码
#### JCLinux 的核心代码
```cpp
for(int i=2;i<=n;i++)//核心代码
{
    if( tall[ tree[ p[i] ] ] <0 )//对于第i个排列来说，p[i] 的父节点必须比p[i]距离根要近，即在[1,i)中已经出现过才行，因为不可能做到父节点比子节点更远
    {
        flag=0;//出现矛盾
        break;
    }
    else
    {
        ans[ p[i] ] = i- tall[ tree[ p[i] ] ];//记录答案：假设第i个出现的点距离根节点的距离就是i，那么，这条边的长度就等于  i-父节点[ p[i] ] (即：i-tall[ tree[ p[i] ] ])
        tall[ p[i] ] =i;
    }
}
```
**核心实现思想**：遍历排列中的每个节点，判断其父节点的距离是否已知。如果已知，则计算当前节点与父节点之间的边权，并更新当前节点到根的距离；如果未知，则说明无法构造出满足条件的边权。

#### Inui_Sana 的核心代码
```cpp
void dfs(int u,int f){
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==f)continue;
        ans[v]=rk[v]-rk[u];
        if(ans[v]<0)flag=false;
        dep[v]=dep[u]+ans[v];
        dfs(v,u);
    }
}
```
**核心实现思想**：使用深度优先搜索遍历树，计算每个节点与其父节点之间的边权，并判断边权是否为正。如果边权为负，则说明无法构造出满足条件的边权。

#### 智子的核心代码
```cpp
for(int i = 1; i <= n; i++) {
    if(ans[fa[pos[i]]] == -1) {
        flag = 0;
        break;
    }
    if(pos[i] == rt) {
        continue;
    }
    dis[pos[i]] = dis[pos[i - 1]] + 1;
    ans[pos[i]] = dis[pos[i]] - dis[fa[pos[i]]];
}
```
**核心实现思想**：遍历排列中的每个节点，判断其父节点的答案是否已经计算出来。如果没有计算出来，则说明无法构造出满足条件的边权；如果已经计算出来，则计算当前节点与父节点之间的边权。

### 最优关键思路或技巧
- 假设排列中第 $i$ 个节点到根的距离为 $i$，通过这个假设来计算边权，简化了问题。
- 利用节点的排列顺序判断是否能构造出合法的边权，即父节点在排列中必须出现在子节点之前。

### 拓展思路
同类型的题目可能会在树的结构、排列的条件等方面进行变化，但核心思路仍然是通过构造边权来满足一定的条件。类似的算法套路包括先分析问题的约束条件，然后通过合理的假设来构造解，最后验证解的合法性。

### 推荐题目
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)
- [P1131 [ZJOI2007] 时态同步](https://www.luogu.com.cn/problem/P1131)
- [P1273 有线电视网](https://www.luogu.com.cn/problem/P1273)

---
处理用时：73.76秒