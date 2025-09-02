# 题目信息

# Longest Simple Cycle

## 题目描述

You have $ n $ chains, the $ i $ -th chain consists of $ c_i $ vertices. Vertices in each chain are numbered independently from $ 1 $ to $ c_i $ along the chain. In other words, the $ i $ -th chain is the undirected graph with $ c_i $ vertices and $ (c_i - 1) $ edges connecting the $ j $ -th and the $ (j + 1) $ -th vertices for each $ 1 \le j < c_i $ .

Now you decided to unite chains in one graph in the following way:

1. the first chain is skipped;
2. the $ 1 $ -st vertex of the $ i $ -th chain is connected by an edge with the $ a_i $ -th vertex of the $ (i - 1) $ -th chain;
3. the last ( $ c_i $ -th) vertex of the $ i $ -th chain is connected by an edge with the $ b_i $ -th vertex of the $ (i - 1) $ -th chain.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1476C/c3d2e7e1f5aff9aaa07bb3c082d03d1303c3b897.png)Picture of the first test case. Dotted lines are the edges added during uniting processCalculate the length of the longest simple cycle in the resulting graph.

A simple cycle is a chain where the first and last vertices are connected as well. If you travel along the simple cycle, each vertex of this cycle will be visited exactly once.

## 说明/提示

In the first test case, the longest simple cycle is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1476C/85078a1da0cf5e3248371659b535343ffec9669a.png)We can't increase it with the first chain, since in such case it won't be simple — the vertex $ 2 $ on the second chain will break simplicity.

## 样例 #1

### 输入

```
3
4
3 4 3 3
-1 1 2 2
-1 2 2 3
2
5 6
-1 5
-1 1
3
3 5 2
-1 1 1
-1 3 5```

### 输出

```
7
11
8```

# AI分析结果

### 题目翻译
# 最长简单环

## 题目描述
你有 $n$ 条链，第 $i$ 条链由 $c_i$ 个顶点组成。每条链中的顶点沿着链从 $1$ 到 $c_i$ 独立编号。换句话说，第 $i$ 条链是一个有 $c_i$ 个顶点和 $(c_i - 1)$ 条边的无向图，其中对于每个 $1 \le j < c_i$，第 $j$ 个顶点和第 $(j + 1)$ 个顶点相连。

现在你决定按以下方式将这些链合并成一个图：
1. 跳过第一条链；
2. 第 $i$ 条链的第 $1$ 个顶点与第 $(i - 1)$ 条链的第 $a_i$ 个顶点相连；
3. 第 $i$ 条链的最后一个（第 $c_i$ 个）顶点与第 $(i - 1)$ 条链的第 $b_i$ 个顶点相连。

![第一个测试用例的图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1476C/c3d2e7e1f5aff9aaa07bb3c082d03d1303c3b897.png)
（虚线是合并过程中添加的边）

计算合并后图中最长简单环的长度。

简单环是一条链，其第一个和最后一个顶点也相连。如果你沿着简单环遍历，这个环中的每个顶点只会被访问一次。

## 说明/提示
在第一个测试用例中，最长简单环如下图所示：

![第一个测试用例中最长简单环的图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1476C/85078a1da0cf5e3248371659b535343ffec9669a.png)

我们不能用第一条链来增加环的长度，因为这样就不是简单环了——第二条链上的顶点 $2$ 会破坏简单性。

## 样例 #1
### 输入
```
3
4
3 4 3 3
-1 1 2 2
-1 2 2 3
2
5 6
-1 5
-1 1
3
3 5 2
-1 1 1
-1 3 5
```
### 输出
```
7
11
8
```

### 算法分类
动态规划

### 综合分析与结论
本题的题干是给定 $n$ 条链，每条链有 $c_i$ 个顶点，按特定规则将链合并成一个图，要求计算合并后图中最长简单环的长度。各题解均采用动态规划的方法来解决该问题，通过定义不同的状态表示和状态转移方程来计算最长简单环的长度。

### 题解评分与分析
- **registerGen（4星）**
    - **亮点**：思路清晰，直接给出状态定义和状态转移方程，并配有图示辅助理解，代码给出链接。
    - **核心思路**：设 $f_i$ 表示用前 $i$ 条链，且第 $i$ 条链必须选所能组成的最大的环。状态转移方程为：
$$f_i=\begin{cases}c_i+1,&a_i=b_i\\\max(c_i+1+f_{i-1}-|a_i-b_i|,c_i+1+|a_i-b_i|),&a_i\ne b_i\end{cases}$$
答案即为 $f_1\sim f_n$ 中的最大值。
- **copper_ingot（4星）**
    - **亮点**：思路详细，通过定义 $r_i = |a_i - b_i|$ 辅助理解，配有多幅图示说明状态转移的两种情况和特殊情况，代码实现清晰。
    - **核心思路**：定义 $dp_i$ 为以第 $i$ 条链为最右边时环的最长长度，$dp_1 = 0$。递推公式为：
当 $r_i = 0$ 时，$dp_i = c_i + 1$；
当 $r_i \ne 0$ 时，$dp_i = \max(c_i + 1 + dp_{i - 1} - r_i, c_i + 1 + r_i)$。
最后的答案是所有 $dp_i$ 中的最大值。
- **ka_da_Duck（4星）**
    - **亮点**：思路简洁明了，直接分析成环的两种情况并给出状态转移方程，代码实现较为简洁。
    - **核心思路**：如果 $b_i = c_i$，则 $f_i = (a_i - 1) + 2$；否则 $f_i = \max(f_{i - 1} + a_i - 1 + 2 - |b_i - c_i|, a_i - 1 + 2 + |b_i - c_i|)$。答案为所有 $f_i$ 中的最大值。

### 关键思路或技巧
- **状态定义**：通过定义合适的状态（如 $f_i$ 或 $dp_i$）来表示前 $i$ 条链能组成的最大环的长度，方便进行状态转移。
- **分类讨论**：根据 $a_i$ 和 $b_i$ 是否相等进行分类讨论，分别得出不同的状态转移方程。

### 拓展思路
同类型题或类似算法套路通常涉及图的构造和动态规划求解最优解。例如，在一些图的合并问题中，需要根据不同的连接规则来计算图的某些属性（如最长路径、最大连通分量等），可以采用类似的动态规划思想，通过定义合适的状态和状态转移方程来解决问题。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，考察动态规划的基本应用。
- [P1854 花店橱窗布置](https://www.luogu.com.cn/problem/P1854)：需要根据一定的规则进行状态转移，计算最优解。
- [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)：通过动态规划计算两个字符串之间的编辑距离。

### 个人心得
题解中未包含个人心得。

---
处理用时：46.81秒