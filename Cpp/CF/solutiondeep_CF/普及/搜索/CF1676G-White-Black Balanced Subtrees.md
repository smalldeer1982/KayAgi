# 题目信息

# White-Black Balanced Subtrees

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root is vertex $ 1 $ . There is also a string $ s $ denoting the color of each vertex: if $ s_i = \texttt{B} $ , then vertex $ i $ is black, and if $ s_i = \texttt{W} $ , then vertex $ i $ is white.

A subtree of the tree is called balanced if the number of white vertices equals the number of black vertices. Count the number of balanced subtrees.

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root. In this problem, all trees have root $ 1 $ .

The tree is specified by an array of parents $ a_2, \dots, a_n $ containing $ n-1 $ numbers: $ a_i $ is the parent of the vertex with the number $ i $ for all $ i = 2, \dots, n $ . The parent of a vertex $ u $ is a vertex that is the next vertex on a simple path from $ u $ to the root.

The subtree of a vertex $ u $ is the set of all vertices that pass through $ u $ on a simple path to the root. For example, in the picture below, $ 7 $ is in the subtree of $ 3 $ because the simple path $ 7 \to 5 \to 3 \to 1 $ passes through $ 3 $ . Note that a vertex is included in its subtree, and the subtree of the root is the entire tree.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676G/70fb6ac8a70942903450f21b07ea9969f086df2c.png) The picture shows the tree for $ n=7 $ , $ a=[1,1,2,3,3,5] $ , and $ s=\texttt{WBBWWBW} $ . The subtree at the vertex $ 3 $ is balanced.

## 说明/提示

The first test case is pictured in the statement. Only the subtrees at vertices $ 2 $ and $ 3 $ are balanced.

In the second test case, only the subtree at vertex $ 1 $ is balanced.

In the third test case, only the subtrees at vertices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are balanced.

## 样例 #1

### 输入

```
3
7
1 1 2 3 3 5
WBBWWBW
2
1
BW
8
1 2 3 4 5 6 7
BWBWBWBW```

### 输出

```
2
1
4```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一棵由 $n$ 个顶点组成的根树，顶点编号从 $1$ 到 $n$，根为顶点 $1$。每个顶点都有一个颜色，用一个字符串 $s$ 表示：如果 $s_i = \texttt{B}$，则顶点 $i$ 是黑色；如果 $s_i = \texttt{W}$，则顶点 $i$ 是白色。

一棵子树被称为**平衡的**，当且仅当其中黑色顶点的数量等于白色顶点的数量。请计算这棵树中有多少棵平衡的子树。

树是一个无环的连通无向图。根树是指有一个被选为根的树。在本问题中，所有树的根都是顶点 $1$。

树由一个包含 $n-1$ 个数的父节点数组 $a_2, \dots, a_n$ 指定：$a_i$ 是顶点 $i$ 的父节点，$i = 2, \dots, n$。顶点 $u$ 的父节点是从 $u$ 到根的简单路径上的下一个顶点。

顶点 $u$ 的子树是指所有通过 $u$ 到根的简单路径上的顶点集合。例如，在下图中，$7$ 在 $3$ 的子树中，因为简单路径 $7 \to 5 \to 3 \to 1$ 经过 $3$。注意，顶点本身包含在其子树中，且根的子树是整个树。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676G/70fb6ac8a70942903450f21b07ea9969f086df2c.png) 图中展示了 $n=7$，$a=[1,1,2,3,3,5]$，$s=\texttt{WBBWWBW}$ 的树。顶点 $3$ 的子树是平衡的。

#### 说明/提示

第一个测试用例如题目描述所示。只有顶点 $2$ 和 $3$ 的子树是平衡的。

第二个测试用例中，只有顶点 $1$ 的子树是平衡的。

第三个测试用例中，只有顶点 $1$、$3$、$5$ 和 $7$ 的子树是平衡的。

#### 样例 #1

##### 输入

```
3
7
1 1 2 3 3 5
WBBWWBW
2
1
BW
8
1 2 3 4 5 6 7
BWBWBWBW
```

##### 输出

```
2
1
4
```

### 题解分析与结论

#### 题解对比

1. **a1co0av5ce5az1cz0ap_** 的题解：
   - **思路**：从根节点开始遍历，回溯时计算每个子树的黑色和白色节点数量，若两者相等则计数。
   - **亮点**：使用简单的DFS遍历，代码简洁，易于理解。
   - **评分**：4星

2. **Coros_Trusds** 的题解：
   - **思路**：通过DFS统计每个子树的黑色和白色节点数量，最后遍历所有节点判断是否平衡。
   - **亮点**：使用了结构体存储黑白节点数量，代码结构清晰。
   - **评分**：4星

3. **Withers** 的题解：
   - **思路**：使用树形DP，每个节点存储子树中黑色和白色节点数量，最后判断是否平衡。
   - **亮点**：树形DP的应用，思路清晰，代码结构良好。
   - **评分**：4星

#### 最优关键思路

- **DFS遍历**：从根节点开始DFS遍历，回溯时计算每个子树的黑色和白色节点数量，若两者相等则计数。
- **树形DP**：每个节点存储子树中黑色和白色节点数量，最后判断是否平衡。

#### 代码实现

```cpp
// a1co0av5ce5az1cz0ap_ 的代码
int co(int rt){
    int sum=color[rt];
    for(int i=0;i<v[rt].size();i++) sum+=co(v[rt][i]);
    if(sum==0) ans++;
    return sum;
}
```

#### 扩展思路

- **树形DP**：可以应用于类似的子树统计问题，如子树的最大值、最小值等。
- **DFS遍历**：适用于所有需要遍历树结构的问题，如路径查找、子树统计等。

#### 推荐题目

1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
2. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)
3. [P2014 选课](https://www.luogu.com.cn/problem/P2014)

---
处理用时：35.63秒