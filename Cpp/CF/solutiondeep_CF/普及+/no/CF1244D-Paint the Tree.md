# 题目信息

# Paint the Tree

## 题目描述

You are given a tree consisting of $ n $ vertices. A tree is an undirected connected acyclic graph.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1244D/0b019d9da08990633b2a6779b2699db8afb883d7.png)Example of a tree.You have to paint each vertex into one of three colors. For each vertex, you know the cost of painting it in every color.

You have to paint the vertices so that any path consisting of exactly three distinct vertices does not contain any vertices with equal colors. In other words, let's consider all triples $ (x, y, z) $ such that $ x \neq y, y \neq z, x \neq z $ , $ x $ is connected by an edge with $ y $ , and $ y $ is connected by an edge with $ z $ . The colours of $ x $ , $ y $ and $ z $ should be pairwise distinct. Let's call a painting which meets this condition good.

You have to calculate the minimum cost of a good painting and find one of the optimal paintings. If there is no good painting, report about it.

## 说明/提示

All vertices should be painted in different colors in the first example. The optimal way to do it is to paint the first vertex into color $ 1 $ , the second vertex — into color $ 3 $ , and the third vertex — into color $ 2 $ . The cost of this painting is $ 3 + 2 + 1 = 6 $ .

## 样例 #1

### 输入

```
3
3 2 3
4 3 2
3 1 3
1 2
2 3
```

### 输出

```
6
1 3 2 
```

## 样例 #2

### 输入

```
5
3 4 2 1 2
4 2 1 5 4
5 3 2 1 1
1 2
3 2
4 3
5 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
3 4 2 1 2
4 2 1 5 4
5 3 2 1 1
1 2
3 2
4 3
5 4
```

### 输出

```
9
1 3 2 1 3 
```

# AI分析结果

### 题目翻译
# 给树染色

## 题目描述
给定一棵由 $n$ 个顶点组成的树。树是一种无向、连通且无环的图。

![树的示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1244D/0b019d9da08990633b2a6779b2699db8afb883d7.png)

你需要将每个顶点染成三种颜色之一。对于每个顶点，你已知将其染成每种颜色的代价。

你需要对顶点进行染色，使得任意由恰好三个不同顶点组成的路径中不包含颜色相同的顶点。换句话说，考虑所有满足 $x \neq y$，$y \neq z$，$x \neq z$，$x$ 与 $y$ 有边相连，且 $y$ 与 $z$ 有边相连的三元组 $(x, y, z)$。$x$、$y$ 和 $z$ 的颜色应两两不同。我们称满足此条件的染色方案为“好的”染色方案。

你需要计算“好的”染色方案的最小代价，并找出一种最优的染色方案。如果不存在“好的”染色方案，请予以报告。

## 说明/提示
在第一个示例中，所有顶点的颜色都应不同。最优的染色方法是将第一个顶点染成颜色 $1$，第二个顶点染成颜色 $3$，第三个顶点染成颜色 $2$。这种染色方案的代价是 $3 + 2 + 1 = 6$。

## 样例 #1
### 输入
```
3
3 2 3
4 3 2
3 1 3
1 2
2 3
```
### 输出
```
6
1 3 2 
```

## 样例 #2
### 输入
```
5
3 4 2 1 2
4 2 1 5 4
5 3 2 1 1
1 2
3 2
4 3
5 3
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
5
3 4 2 1 2
4 2 1 5 4
5 3 2 1 1
1 2
3 2
4 3
5 4
```
### 输出
```
9
1 3 2 1 3 
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是先判断树是否为链（若存在节点度数大于 2 则无解），因为只有链才能满足染色条件。接着通过枚举链上前两个或前三个点的颜色，根据相邻三个点颜色不同的规则确定整条链的颜色，最后计算每种染色方案的代价，找出最小代价及对应的染色方案。

不同题解的主要差异在于实现细节，如建图方式（邻接表、链式前向星等）、枚举颜色的具体实现、确定链的方式等。部分题解使用了深度优先搜索（DFS）来确定链上节点的颜色，部分题解则通过循环直接递推。

### 所选题解
- **作者：installb (赞：13)，4星**
  - **关键亮点**：思路清晰，配有图示帮助理解，代码注释详细，使用 DFS 标记颜色，逻辑清晰。
  - **个人心得**：提到考场代码直接用了 DFS，虽不是最优但复杂度正确。
- **作者：woshishei (赞：7)，4星**
  - **关键亮点**：对无解情况的证明详细，通过邻接表建图，利用 `next_permutation` 枚举颜色排列，代码简洁。
- **作者：AutumnKite (赞：5)，4星**
  - **关键亮点**：思路简洁明了，直接指出确定链上前三个点颜色就能确定整条链颜色，代码实现较为精炼。

### 重点代码
#### installb 的题解
```cpp
LL chg(LL x,LL y){
    return 6 - x - y; // 小技巧 根据另外两点颜色确定该点颜色
}

void dfs(LL u,LL f,LL uc,LL fc){ // 标记颜色
    for(LL i = hed[u];i;i = nxt[i]){
        LL v = to[i];
        if(v == f) continue;
        col[v] = chg(uc,fc);
        dfs(v,u,col[v],uc);
    }
}
```
**核心实现思想**：`chg` 函数通过另外两个点的颜色计算当前点的颜色。`dfs` 函数从当前节点出发，递归标记相邻节点的颜色。

#### woshishei 的题解
```cpp
do
{
    sum=0;
    for(int i=1;i<=n;i++)
    {
        tmp[a[i]]=p[(i-1)%3+1]+1;//链上的第i个节点（编号为a[i]）标为相应的颜色
        sum+=c[p[(i-1)%3+1]][a[i]];//计入花费
    }
    if(sum<mi)//更新答案
    {
        mi=sum;
        memcpy(ans,tmp,sizeof(tmp));
    }
}while(next_permutation(p+1,p+4));//枚举颜色的排列
```
**核心实现思想**：使用 `next_permutation` 枚举颜色的排列，对于每种排列计算染色的总代价，更新最小代价及对应的染色方案。

#### AutumnKite 的题解
```cpp
while (1){
    long long s = 0;
    for (register int i = 1; i <= n; ++i) s += c[id[i % 3]][p[i]];
    if (s < ans) ans = s, memcpy(ansid, id, sizeof ansid);
    if (!std :: next_permutation(id, id + 3)) break;
}
```
**核心实现思想**：通过 `next_permutation` 枚举前三个点的颜色排列，计算每种排列下的总代价，更新最小代价及对应的颜色排列。

### 扩展思路
同类型题或类似算法套路：
- 其他图的染色问题，如给定图的结构和染色规则，求满足条件的染色方案数或最小代价。
- 序列的约束性填充问题，如给定序列长度和元素取值范围，以及相邻元素的约束条件，求满足条件的序列。

### 推荐题目
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：树形 DP 问题，与树的结构相关。
- [P1122 最大子树和](https://www.luogu.com.cn/problem/P1122)：树的遍历和动态规划问题。
- [P2016 战略游戏](https://www.luogu.com.cn/problem/P2016)：树的覆盖问题，涉及树的结构和状态转移。

---
处理用时：51.23秒