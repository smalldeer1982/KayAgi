# 题目信息

# Not Assigning

## 题目描述

You are given a tree of $ n $ vertices numbered from $ 1 $ to $ n $ , with edges numbered from $ 1 $ to $ n-1 $ . A tree is a connected undirected graph without cycles. You have to assign integer weights to each edge of the tree, such that the resultant graph is a prime tree.

A prime tree is a tree where the weight of every path consisting of one or two edges is prime. A path should not visit any vertex twice. The weight of a path is the sum of edge weights on that path.

Consider the graph below. It is a prime tree as the weight of every path of two or less edges is prime. For example, the following path of two edges: $ 2 \to 1 \to 3 $ has a weight of $ 11 + 2 = 13 $ , which is prime. Similarly, the path of one edge: $ 4 \to 3 $ has a weight of $ 5 $ , which is also prime.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/3add991eaafca4c0491e3513c8ebd38f1627bca9.png)Print any valid assignment of weights such that the resultant tree is a prime tree. If there is no such assignment, then print $ -1 $ . It can be proven that if a valid assignment exists, one exists with weights between $ 1 $ and $ 10^5 $ as well.

## 说明/提示

For the first test case, there are only two paths having one edge each: $ 1 \to 2 $ and $ 2 \to 1 $ , both having a weight of $ 17 $ , which is prime.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/22666e3c2f70cbd5edc23fd608081fffda0715fc.png)The second test case is described in the statement.

It can be proven that no such assignment exists for the third test case.

## 样例 #1

### 输入

```
3
2
1 2
4
1 3
4 3
2 1
7
1 2
1 3
3 4
3 5
6 2
7 2```

### 输出

```
17
2 5 11
-1```

# AI分析结果

### 题目中文重写
## 不赋值问题

### 题目描述
给定一棵有 $n$ 个顶点的树，顶点编号从 $1$ 到 $n$，边编号从 $1$ 到 $n - 1$。树是一个无环的连通无向图。你需要为树的每条边分配整数权重，使得得到的图是一棵质数树。

质数树是指每一条由一条或两条边组成的路径的权重都是质数的树。路径不应重复访问任何顶点。路径的权重是该路径上各边权重之和。

考虑下图，它是一棵质数树，因为每一条由两条或更少边组成的路径的权重都是质数。例如，由两条边组成的路径 $2 \to 1 \to 3$ 的权重为 $11 + 2 = 13$，是质数。同样，由一条边组成的路径 $4 \to 3$ 的权重为 $5$，也是质数。

![示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/3add991eaafca4c0491e3513c8ebd38f1627bca9.png)
输出任意一种有效的权重分配方案，使得得到的树是质数树。如果不存在这样的分配方案，则输出 $-1$。可以证明，如果存在有效的分配方案，那么也存在权重在 $1$ 到 $10^5$ 之间的分配方案。

### 说明/提示
对于第一个测试用例，只有两条由一条边组成的路径：$1 \to 2$ 和 $2 \to 1$，它们的权重都是 $17$，是质数。

![第一个测试用例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627C/22666e3c2f70cbd5edc23fd608081fffda0715fc.png)
第二个测试用例在题目描述中已有说明。

可以证明，第三个测试用例不存在这样的分配方案。

### 样例 #1
#### 输入
```
3
2
1 2
4
1 3
4 3
2 1
7
1 2
1 3
3 4
3 5
6 2
7 2
```
#### 输出
```
17
2 5 11
-1
```

### 综合分析与结论
这些题解的核心思路都是先证明满足条件的树一定是链状结构，然后对链上的边交替赋值。

#### 思路对比
- 所有题解都通过质数的奇偶性来证明树必须是链状。因为除 2 以外的质数都是奇数，两个奇数相加为偶数，不是质数，所以一个点连接的边中最多只能有一条边权为 2，若一个点连接超过两条边则无法满足条件。
- 在链的构造上，大部分题解选择交替赋值 2 和 3，也有部分选择 2 和 17、2 和 5 等。

#### 算法要点
1. **判断树是否为链**：通过统计每个节点的度数，若存在度数大于 2 的节点，则树不是链，无解。
2. **找到链的一端**：选择一个度数为 1 的节点作为链的起点。
3. **交替赋值**：从链的一端开始，对边交替赋上特定的质数（如 2 和 3）。

#### 解决难点
- **证明树的形态**：利用质数的奇偶性进行推理，排除非链状结构的可能性。
- **构造边权**：选择合适的质数进行交替赋值，确保满足路径权重为质数的条件。

### 评分较高的题解
- **作者：wosile（5 星）**
    - **关键亮点**：思路清晰，证明严谨，代码可读性高，注释详细。
    - **核心代码**：
```cpp
void dfs(int rt,int fa,int col){
    for(int i=0;i<T[rt].size();i++)if(T[rt][i].first!=fa){
        ans[T[rt][i].second]=col+2;
        dfs(T[rt][i].first,rt,col^1);
    }
}
```
核心实现思想：通过深度优先搜索遍历树，根据当前颜色 `col` 为边赋值（`col + 2` 得到 2 或 3），并将颜色取反传递给下一层。

- **作者：zhaoyp（4 星）**
    - **关键亮点**：思路简洁，通过反证法清晰地证明了树必须是链状。
    - **核心思路**：通过反证法，假设树不是链状，存在分界点，推出矛盾，从而证明树必须是链状，然后交替赋值 2 和 3。

- **作者：LRL65（4 星）**
    - **关键亮点**：代码简洁，逻辑清晰，通过深度优先搜索实现边权赋值。
    - **核心代码**：
```cpp
void dfs(int x,int fa,int la) {
    for(int i=0;i<e[x].size();i++) {
        if(e[x][i].first==fa)continue;
        if(fa==0&&i==1)la=5-la;
        ans[e[x][i].second]=5-la;
        dfs(e[x][i].first,x,5-la);
    }
}
```
核心实现思想：深度优先搜索遍历树，根据上一条边的权值 `la` 计算当前边的权值（`5 - la` 得到 2 或 3）。

### 最优关键思路或技巧
- **质数奇偶性分析**：利用质数的奇偶性来判断树的形态，是解决本题的关键思维方式。
- **交替赋值**：通过交替赋值 2 和 3 等质数，简单有效地构造出满足条件的边权。

### 可拓展之处
同类型题可能会改变路径长度的限制或质数的条件，解题思路仍然是先分析限制条件对图结构的影响，再进行构造。类似算法套路包括利用数论性质分析问题、通过图的遍历进行构造等。

### 推荐题目
1. [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：涉及图的遍历和连通性问题。
2. [P1346 电车](https://www.luogu.com.cn/problem/P1346)：图的最短路径问题，需要对图进行合理建模。
3. [P1629 邮递员送信](https://www.luogu.com.cn/problem/P1629)：涉及图的单源最短路径和多源最短路径问题。

### 个人心得摘录与总结
- **作者：wosile**：自己 VP 了这场比赛，做到了 C 题，赛后做到了 E 题。总结了做题的经历。
- **作者：PosVII**：自己整了场 VP，打完发题解，吐槽样例诈骗。分享了比赛体验和对题目的感受。 

---
处理用时：37.99秒