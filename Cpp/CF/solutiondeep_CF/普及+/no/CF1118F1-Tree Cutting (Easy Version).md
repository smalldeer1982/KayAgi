# 题目信息

# Tree Cutting (Easy Version)

## 题目描述

You are given an undirected tree of $ n $ vertices.

Some vertices are colored blue, some are colored red and some are uncolored. It is guaranteed that the tree contains at least one red vertex and at least one blue vertex.

You choose an edge and remove it from the tree. Tree falls apart into two connected components. Let's call an edge nice if neither of the resulting components contain vertices of both red and blue colors.

How many nice edges are there in the given tree?

## 说明/提示

Here is the tree from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/ab0319e6d1b3fdf0a12318f77b159c6dc359f231.png)The only nice edge is edge $ (2, 4) $ . Removing it makes the tree fall apart into components $ \{4\} $ and $ \{1, 2, 3, 5\} $ . The first component only includes a red vertex and the second component includes blue vertices and uncolored vertices.

Here is the tree from the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/7f13f482fb950c8fef37bc2658aa383ebfb7bf5b.png)Every edge is nice in it.

Here is the tree from the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/f3485c6c57decb8200c34309a45ff67d9c4b5fd0.png)Edge $ (1, 3) $ splits the into components $ \{1\} $ and $ \{3, 2\} $ , the latter one includes both red and blue vertex, thus the edge isn't nice. Edge $ (2, 3) $ splits the into components $ \{1, 3\} $ and $ \{2\} $ , the former one includes both red and blue vertex, thus the edge also isn't nice. So the answer is 0.

## 样例 #1

### 输入

```
5
2 0 0 1 2
1 2
2 3
2 4
2 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 0 0 0 2
1 2
2 3
3 4
4 5
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
1 1 2
2 3
1 3
```

### 输出

```
0
```

# AI分析结果

### 题目内容翻译
## 砍树（简单版本）

### 题目描述
给定一棵包含 $n$ 个顶点的无向树。

一些顶点被染成蓝色，一些被染成红色，还有一些未染色。保证树中至少有一个红色顶点和至少一个蓝色顶点。

你选择一条边并将其从树中移除。树会分裂成两个连通分量。如果移除某条边后得到的两个分量中都不同时包含红色和蓝色顶点，那么我们称这条边为“好边”。

给定的树中有多少条好边？

### 说明/提示
以下是第一个样例中的树：
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/ab0319e6d1b3fdf0a12318f77b159c6dc359f231.png)
唯一的好边是边 $(2, 4)$。移除它会使树分裂成分量 $\{4\}$ 和 $\{1, 2, 3, 5\}$。第一个分量只包含一个红色顶点，第二个分量包含蓝色顶点和未染色顶点。

以下是第二个样例中的树：
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/7f13f482fb950c8fef37bc2658aa383ebfb7bf5b.png)
其中的每条边都是好边。

以下是第三个样例中的树：
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/f3485c6c57decb8200c34309a45ff67d9c4b5fd0.png)
边 $(1, 3)$ 将树分裂成分量 $\{1\}$ 和 $\{3, 2\}$，后者同时包含红色和蓝色顶点，因此这条边不是好边。边 $(2, 3)$ 将树分裂成分量 $\{1, 3\}$ 和 $\{2\}$，前者同时包含红色和蓝色顶点，因此这条边也不是好边。所以答案是 $0$。

### 样例 #1
#### 输入
```
5
2 0 0 1 2
1 2
2 3
2 4
2 5
```
#### 输出
```
1
```

### 样例 #2
#### 输入
```
5
1 0 0 0 2
1 2
2 3
3 4
4 5
```
#### 输出
```
4
```

### 样例 #3
#### 输入
```
3
1 1 2
2 3
1 3
```
#### 输出
```
0
```

### 算法分类
深度优先搜索 DFS

### 综合分析与结论
这些题解的核心思路都是通过深度优先搜索（DFS）遍历树，统计每个子树中红色和蓝色节点的数量，然后根据这些数量判断每条边是否为“好边”。具体来说，对于每条边，判断删除该边后形成的两个子树是否不同时包含红色和蓝色节点。

各题解的算法要点基本相同，都是利用 DFS 递归地统计子树信息，然后进行判断。不同之处在于代码实现细节，如存储图的方式（邻接表、链式前向星等）、数组命名和判断条件的书写方式等。

解决的难点在于如何正确地统计每个子树的信息，并根据这些信息准确判断边的合法性。

### 较高评分题解
- **Edmundino（4星）**
  - **关键亮点**：思路清晰，代码简洁易懂，详细解释了 DFS 过程中如何统计子树信息和判断边的合法性。
  - **个人心得**：无

### 重点代码
```cpp
void dfs(int u,int fa)
{
  if(a[u]==1) s[u][1]++;
  if(a[u]==2) s[u][2]++;
  int lon=vec[u].size();
  for(int i=0;i<lon;i++)
  {
    int v=vec[u][i];
    if(v!=fa)
    {
       dfs(v,u);
       s[u][1]+=s[v][1];
       s[u][2]+=s[v][2];
    }
  }
  if(s[u][1]==0&&s[u][2]==sumb||s[u][2]==0&&s[u][1]==suma)
  {
     zs++;
  }
}
```
**核心实现思想**：通过 DFS 递归地统计每个子树中红色和蓝色节点的数量。对于当前节点 $u$，如果它是红色节点，则 $s[u][1]$ 加 1；如果是蓝色节点，则 $s[u][2]$ 加 1。然后遍历 $u$ 的所有子节点 $v$，递归调用 DFS 并将 $v$ 的子树信息累加到 $u$ 上。最后，根据 $s[u][1]$ 和 $s[u][2]$ 的值判断以 $u$ 为根的子树是否满足“好边”的条件，如果满足则计数器 $zs$ 加 1。

### 拓展思路
同类型题或类似算法套路：这类树形结构上的搜索问题在很多题目中都会出现，例如计算树的直径、树的重心等。通常的解题思路都是通过 DFS 或 BFS 遍历树，统计节点信息，然后根据题目要求进行判断和计算。

### 推荐题目
1. [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)
2. [P1131 [ZJOI2007] 时态同步](https://www.luogu.com.cn/problem/P1131)
3. [P1273 有线电视网](https://www.luogu.com.cn/problem/P1273)

### 个人心得摘录与总结
- **EDqwq**：提到如果使用记录 $fa$ 的 DFS，要把初始 $fa$ 设为 $0$ 而不是 $-1$，提醒注意 DFS 中父节点初始值的设置，避免因初始值错误导致程序出错。 

---
处理用时：44.65秒