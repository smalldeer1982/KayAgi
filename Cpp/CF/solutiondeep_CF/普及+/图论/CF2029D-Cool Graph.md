# 题目信息

# Cool Graph

## 题目描述

You are given an undirected graph with $ n $ vertices and $ m $ edges.

You can perform the following operation at most $ 2\cdot \max(n,m) $ times:

- Choose three distinct vertices $ a $ , $ b $ , and $ c $ , then for each of the edges $ (a,b) $ , $ (b,c) $ , and $ (c,a) $ , do the following: 
  - If the edge does not exist, add it. On the contrary, if it exists, remove it.

A graph is called cool if and only if one of the following holds:

- The graph has no edges, or
- The graph is a tree.

You have to make the graph cool by performing the above operations. Note that you can use at most $ 2\cdot \max(n,m) $ operations.

It can be shown that there always exists at least one solution.

## 说明/提示

In the first test case, the graph is already cool because there are no edges.

In the second test case, after performing the only operation, the graph becomes a tree, so it is cool.

In the third test case, the graph is already cool because it is a tree.

In the fourth test case, after performing the only operation, the graph has no edges, so it is cool.

In the fifth test case:

 OperationGraph before the operationGraph after the operation $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/b0f7ac35f24bdd1ef25527e8445c75c07c81b1cd.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/967d0caf549d17edc01f85e8fd3b92d4a29c78a4.png) $ 2 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/8fc9b337d57d63328a0f768cb6979898a6acb589.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/e76a67a3a1dfd30fecae063029760f2fec760cd4.png) $ 3 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/cd4bbe994192de9db9336eff41b4aa05bb7c27af.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/278495e89dce856c8d1c4a31851cd95fdb2f1cd3.png)Note that after the first operation, the graph has already become cool, and there are two extra operations. As the graph is still cool after the two extra operations, this is a valid answer.

## 样例 #1

### 输入

```
5
3 0
3 1
1 2
3 2
1 2
2 3
3 3
1 2
2 3
3 1
6 6
1 2
1 6
4 5
3 4
4 6
3 6```

### 输出

```
0
1
1 2 3
0
1
1 2 3
3
1 3 6
2 4 5
3 4 6```

# AI分析结果

### 题目内容中文重写
## 酷炫图

### 题目描述
给定一个包含 $n$ 个顶点和 $m$ 条边的无向图。

你可以最多进行 $2\cdot \max(n,m)$ 次以下操作：
- 选择三个不同的顶点 $a$、$b$ 和 $c$，然后对于边 $(a,b)$、$(b,c)$ 和 $(c,a)$ 分别执行以下操作：
  - 如果该边不存在，则添加它；相反，如果该边存在，则删除它。

当且仅当满足以下条件之一时，一个图被称为酷炫图：
- 图中没有边；
- 图是一棵树。

你必须通过执行上述操作使图变为酷炫图。注意，你最多只能使用 $2\cdot \max(n,m)$ 次操作。

可以证明，总是至少存在一种解决方案。

### 说明/提示
在第一个测试用例中，图已经是酷炫图，因为没有边。

在第二个测试用例中，执行唯一的一次操作后，图变成了一棵树，因此它是酷炫图。

在第三个测试用例中，图已经是酷炫图，因为它是一棵树。

在第四个测试用例中，执行唯一的一次操作后，图中没有边，因此它是酷炫图。

在第五个测试用例中：

|操作|操作前的图|操作后的图|
|----|----|----|
|$1$|![操作前](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/b0f7ac35f24bdd1ef25527e8445c75c07c81b1cd.png)|![操作后](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/967d0caf549d17edc01f85e8fd3b92d4a29c78a4.png)|
|$2$|![操作前](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/8fc9b337d57d63328a0f768cb6979898a6acb589.png)|![操作后](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/e76a67a3a1dfd30fecae063029760f2fec760cd4.png)|
|$3$|![操作前](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/cd4bbe994192de9db9336eff41b4aa05bb7c27af.png)|![操作后](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/278495e89dce856c8d1c4a31851cd95fdb2f1cd3.png)|

注意，在第一次操作后，图已经变成了酷炫图，并且还有两次额外的操作。由于在这两次额外操作后图仍然是酷炫图，所以这是一个有效的答案。

### 样例 #1
#### 输入
```
5
3 0
3 1
1 2
3 2
1 2
2 3
3 3
1 2
2 3
3 1
6 6
1 2
1 6
4 5
3 4
4 6
3 6
```
#### 输出
```
0
1
1 2 3
0
1
1 2 3
3
1 3 6
2 4 5
3 4 6
```

### 题解综合分析与结论
这些题解的核心目标都是将给定的无向图通过特定操作转化为酷炫图（无边图或树），且操作次数不超过 $2\cdot \max(n,m)$。思路主要分为两类：
- **减少边数再合并连通块**：先通过操作使图中每个点的度数不超过 1，将图转化为单点和孤立边的集合，再将这些连通块合并成一棵树。如 Autumn_Rain、bsdsdb、_lmh_、tai_chi 的题解。
- **构建特殊树**：尝试构建以 1 为根的菊花图，先删除与 1 无关的边，再将孤立点连接到菊花图上。如 Enoch006、Exp10re、gu51yo 的题解。

算法要点包括使用 set 维护邻接关系、优先队列维护节点度数、并查集维护连通性等。难点在于如何控制操作次数在规定范围内，以及如何高效地合并连通块。

### 所选题解
- **Autumn_Rain（5星）**
  - **关键亮点**：思路清晰，通过图文结合详细展示了操作过程，对操作次数的分析严谨，能让读者很好地理解整个算法流程。
- **Enoch006（4星）**
  - **关键亮点**：提供了清晰的思考方向，代码实现简洁明了，对操作的解释和复杂度分析准确。
- **Exp10re（4星）**
  - **关键亮点**：从简化状态的角度出发，思路具有启发性，对操作的构造和复杂度分析详细，还给出了优化时间复杂度的方法。

### 重点代码及核心实现思想
#### Autumn_Rain
核心思想：先通过选择度不小于 2 的点及其相邻两点进行操作减少边数，将图转化为单点和孤立边的集合，再合并这些连通块成树。
```plaintext
找到所有度不小于 2 的点，选和它有另外两个相邻的点进行操作（这会使边的数量刚好减 1），直到没有这样的点。
找到所有大小为 2 的联通块，若有多于一个，选其中两个，从中随便选出三个点进行操作，变成一颗树。
若还有剩下的大小为 2 的联通块，选择已经生成树的树根，再把其两个点都选上，使其合并到树中。
选树根，树上与根相邻的一点，和一个单点进行操作，不断重复直到没有单点。
```

#### Enoch006
核心思想：构建以 1 为中心的菊花图，先删除与 1 无关的边，再将孤立点连接到菊花图上。
```cpp
for(int i=2;i<=n;i++){
    while(e[i].size()){
        int x=*e[i].rbegin();
        if(x==1)break;
        e[i].erase(x);e[x].erase(i);
        if(e[1].count(i))e[1].erase(i),e[i].erase(1);
        else e[1].insert(i),e[i].insert(1);
        if(e[1].count(x))e[1].erase(x),e[x].erase(1);
        else e[1].insert(x),e[x].insert(1);
        ans[++cnt]=(node){1,i,x};
    }
}
if(e[1].size()){
    int X=1,Y=*e[1].begin();
    for(int i=2;i<=n;i++){
        if(e[i].size())continue;
        ans[++cnt]=(node){X,Y,i};
        X=i;
    }
}
```

#### Exp10re
核心思想：先将图转化为类菊花图，再将孤立点合并到菊花图上形成树，通过优化减少时间复杂度。
```plaintext
在读入边时，若边的端点不为 1，进行操作 (1, u, v)，将图转化为类菊花图。
若图不为空，找到与 1 相连的点 p 和孤立点 q，执行操作 (1, p, q)，将 q 合并到连通块中，每次操作后更新 p 为 q。
```

### 最优关键思路或技巧
- **构建特殊树**：构建以 1 为根的菊花图，能有效减少边数并方便后续合并孤立点，操作简单且易于控制操作次数。
- **利用操作特性**：选择合适的三个点进行操作，使边数减少或连通块合并，如选择度不小于 2 的点及其相邻两点操作可减少边数。
- **数据结构优化**：使用 set 维护邻接关系，方便查找和删除边；使用优先队列维护节点度数，便于选择合适的节点进行操作。

### 可拓展之处
同类型题可能会改变操作规则或图的性质，如操作变为添加或删除多条边，图变为有向图等。类似算法套路可用于解决其他图的构造问题，如将图转化为特定的图结构（如完全图、二分图等）。

### 洛谷相似题目推荐
- [P1197 星球大战](https://www.luogu.com.cn/problem/P1197)：涉及图的连通性和动态操作。
- [P1991 无线通讯网](https://www.luogu.com.cn/problem/P1991)：与图的生成树相关。
- [P2872 [USACO07DEC]Building Roads S](https://www.luogu.com.cn/problem/P2872)：需要构建图的最小生成树。

### 个人心得摘录与总结
本题解中未包含个人心得内容。

---
处理用时：53.39秒