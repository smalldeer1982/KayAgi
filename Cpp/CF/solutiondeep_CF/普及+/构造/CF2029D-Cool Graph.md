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

### 题目中文重写
## 酷图

### 题目描述
给定一个包含 $n$ 个顶点和 $m$ 条边的无向图。

你可以最多进行 $2\cdot \max(n,m)$ 次以下操作：
- 选择三个不同的顶点 $a$、$b$ 和 $c$，然后对于边 $(a,b)$、$(b,c)$ 和 $(c,a)$ 分别执行以下操作：
  - 如果边不存在，则添加它；相反，如果边存在，则删除它。

当且仅当满足以下条件之一时，图被称为酷图：
- 图没有边；
- 图是一棵树。

你必须通过执行上述操作使图变成酷图。注意，你最多可以使用 $2\cdot \max(n,m)$ 次操作。

可以证明，总是至少存在一种解决方案。

### 说明/提示
在第一个测试用例中，图已经是酷图，因为没有边。

在第二个测试用例中，执行唯一的操作后，图变成了一棵树，因此它是酷图。

在第三个测试用例中，图已经是酷图，因为它是一棵树。

在第四个测试用例中，执行唯一的操作后，图没有边，因此它是酷图。

在第五个测试用例中：
|操作|操作前的图|操作后的图|
|----|----|----|
|$1$|![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/b0f7ac35f24bdd1ef25527e8445c75c07c81b1cd.png)|![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/967d0caf549d17edc01f85e8fd3b92d4a29c78a4.png)|
|$2$|![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/8fc9b337d57d63328a0f768cb6979898a6acb589.png)|![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/e76a67a3a1dfd30fecae063029760f2fec760cd4.png)|
|$3$|![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/cd4bbe994192de9db9336eff41b4aa05bb7c27af.png)|![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2029D/278495e89dce856c8d1c4a31851cd95fdb2f1cd3.png)|

注意，在第一次操作后，图已经变成了酷图，并且还有两个额外的操作。由于在这两个额外操作后图仍然是酷图，因此这是一个有效的答案。

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

### 综合分析与结论
这些题解的核心目标都是将给定的无向图通过不超过 $2\cdot \max(n,m)$ 次操作转化为酷图（无边图或树）。主要思路可分为两类：
- **减少边数再合并连通块**：先通过操作使每个点的度不超过 1，将图转化为单点和孤立边的形式，再把这些连通块合并成一棵树。如 Autumn_Rain、bsdsdb、_lmh_、tai_chi 的题解。
- **构建特殊树**：构建以 1 为根的菊花图，先删除与 1 无关的边，再将孤立点连接到菊花图上。如 Enoch006、Exp10re、gu51yo 的题解。

### 算法要点对比
|作者|算法要点|
|----|----|
|Autumn_Rain|先选度不小于 2 的点及其相邻两点操作减少边数，再合并大小为 2 的连通块成树，最后将单点合并到树中|
|Enoch006|先对非 1 节点间的边进行 (1,x,y) 操作构建菊花图，再将孤立点连接到菊花图上|
|Exp10re|读入边时对非 1 端点的边进行 (1,u,v) 操作构建类菊花图，再将孤立点合并到树中|
|bsdsdb|用优先队列维护点的度数，先让每个点的度不超过 1，再将连通分量连成树|
|gu51yo|删除与 1 无关的边，再将孤立点连接到与 1 相连的点上|
|_lmh_|枚举度数 > 1 的节点操作减少边数，用并查集维护连通性合并连通块|
|tai_chi|对度数不小于 2 的点及其相邻节点操作使图稀疏，再合并连通块成树|

### 难点对比
|作者|难点|解决方法|
|----|----|----|
|Autumn_Rain|合并连通块和单点到树中|按特定规则选择操作的三个点|
|Enoch006|将孤立点连接到菊花图上|找一条原有的边进行操作|
|Exp10re|优化寻找点的时间复杂度|记录操作后的点，遍历所有点|
|bsdsdb|动态维护点的度数和边的信息|用优先队列和 set|
|gu51yo|判断点是否与 1 相连|用异或记录点的度数|
|_lmh_|避免操作后出现度数大于 1 的节点|合理选择操作的节点|
|tai_chi|动态维护边的信息|用 set 维护相邻点|

### 题解评分与选择
|作者|星级|关键亮点|
|----|----|----|
|Autumn_Rain|4星|思路清晰，有详细的图文解释，操作次数分析合理|
|Enoch006|4星|思路明确，代码实现简洁，有详细的注释|
|Exp10re|4星|考虑了时间复杂度的优化，思路和分析较为全面|

### 重点代码及核心实现思想
#### Autumn_Rain
```plaintext
先选度不小于 2 的点及其相邻两点操作减少边数，再合并大小为 2 的连通块成树，最后将单点合并到树中。
```
#### Enoch006
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
核心思想：先对非 1 节点间的边进行 (1,x,y) 操作构建菊花图，再将孤立点连接到菊花图上。

#### Exp10re
```plaintext
读入边时对非 1 端点的边进行 (1,u,v) 操作构建类菊花图，再将孤立点合并到树中，通过记录操作后的点和遍历所有点优化时间复杂度。
```

### 最优关键思路或技巧
- **构建特殊树**：构建以 1 为根的菊花图，简化了图的结构，便于后续将孤立点连接到树上。
- **动态数据结构**：使用 set 维护节点的相邻边，优先队列维护点的度数，方便动态更新图的信息。
- **操作次数分析**：通过合理的操作设计，保证操作次数不超过 $2\cdot \max(n,m)$。

### 拓展思路
同类型题可能会改变操作规则或酷图的定义，类似算法套路可用于解决需要通过特定操作将图转化为特定结构的问题，如将图转化为二分图、完全图等。

### 洛谷相似题目推荐
- P1197 [JSOI2008]星球大战：涉及图的连通性和动态操作。
- P2814 家谱：可使用并查集维护图的连通性。
- P3367 【模板】并查集：基础的并查集题目，可用于巩固连通性维护的知识。

### 个人心得摘录与总结
题解中未包含个人心得。

---
处理用时：58.28秒