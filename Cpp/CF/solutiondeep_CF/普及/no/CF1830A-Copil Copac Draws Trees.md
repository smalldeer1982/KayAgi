# 题目信息

# Copil Copac Draws Trees

## 题目描述

Copil Copac is given a list of $ n-1 $ edges describing a tree of $ n $ vertices. He decides to draw it using the following algorithm:

- Step $ 0 $ : Draws the first vertex (vertex $ 1 $ ). Go to step $ 1 $ .
- Step $ 1 $ : For every edge in the input, in order: if the edge connects an already drawn vertex $ u $ to an undrawn vertex $ v $ , he will draw the undrawn vertex $ v $ and the edge. After checking every edge, go to step $ 2 $ .
- Step $ 2 $ : If all the vertices are drawn, terminate the algorithm. Else, go to step $ 1 $ .

The number of readings is defined as the number of times Copil Copac performs step $ 1 $ .

Find the number of readings needed by Copil Copac to draw the tree.

## 说明/提示

In the first test case:

After the first reading, the tree will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/96592d8d6a7376d06a499045a206685f9a68df31.png)After the second reading:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/7b7bd2d2b1a9ad0d44021bb292052bd1a2395dfd.png)Therefore, Copil Copac needs $ 2 $ readings to draw the tree.

## 样例 #1

### 输入

```
2
6
4 5
1 3
1 2
3 4
1 6
7
5 6
2 4
2 7
1 3
1 2
4 5```

### 输出

```
2
3```

# AI分析结果

### 题目内容重写
# Copil Copac 画树

## 题目描述

Copil Copac 被给定一个包含 $n-1$ 条边的列表，这些边描述了一棵有 $n$ 个顶点的树。他决定使用以下算法来绘制这棵树：

- 步骤 $0$：绘制第一个顶点（顶点 $1$）。进入步骤 $1$。
- 步骤 $1$：对于输入中的每一条边，按顺序检查：如果这条边连接一个已经绘制的顶点 $u$ 和一个未绘制的顶点 $v$，他将绘制未绘制的顶点 $v$ 和这条边。在检查完所有边后，进入步骤 $2$。
- 步骤 $2$：如果所有顶点都已绘制，则终止算法。否则，返回步骤 $1$。

“读取次数”定义为 Copil Copac 执行步骤 $1$ 的次数。

请找出 Copil Copac 绘制这棵树所需的读取次数。

## 说明/提示

在第一个测试用例中：

第一次读取后，树将如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/96592d8d6a7376d06a499045a206685f9a68df31.png)

第二次读取后：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1830A/7b7bd2d2b1a9ad0d44021bb292052bd1a2395dfd.png)

因此，Copil Copac 需要 $2$ 次读取来绘制这棵树。

## 样例 #1

### 输入

```
2
6
4 5
1 3
1 2
3 4
1 6
7
5 6
2 4
2 7
1 3
1 2
4 5
```

### 输出

```
2
3
```

### 算法分类
深度优先搜索 DFS

### 题解分析与结论
1. **核心思路**：通过深度优先搜索（DFS）遍历树，记录每条边的编号，并在遍历过程中判断当前边的编号是否小于前一条边的编号。如果是，则需要增加一轮读取次数。
2. **难点**：如何在不模拟整个绘制过程的情况下，通过边编号的比较来确定读取次数。
3. **优化**：利用DFS遍历树，通过比较边编号来减少计算复杂度，避免暴力模拟。

### 所选高分题解
#### 题解1：theb0t (5星)
- **关键亮点**：通过DFS遍历树，利用边编号的比较来确定读取次数，代码简洁且高效。
- **个人心得**：作者提到要注意多测清空，这是一个常见的调试经验。

```cpp
int dfs(int x,int fa,int pre){ //x当前节点，fa上一个节点（因为是无向图），pre上一条边的编号
    int res=0;
    for(int i=0;i<to[x].size();i++){
        if(to[x][i]!=fa) res=max(res,dfs(to[x][i],x,id[x][i])+(id[x][i]<pre)); //(id[x][i]<pre)是一个布尔表达式，如果为真就加1
    }
    return res;
}
```

#### 题解2：Malkin_Moonlight (4星)
- **关键亮点**：详细分析了题目的绘制过程，并通过边编号的比较来优化算法。
- **个人心得**：作者强调了最坏情况下要 $n - 1$ 次操作，提醒不能暴力模拟。

```cpp
ll dfs(ll x, ll p, ll pre) { //pre代表上一条边，p代表父节点 
    ll ans = 0;
    for (int i = 0; i < v[x].size(); i++) {
        if (v[x][i] != p) {
            ans = max(ans, dfs(v[x][i], x, id[x][i]) + (id[x][i] < pre));
        }
    }
    return ans;
}
```

### 最优关键思路
通过DFS遍历树，利用边编号的比较来确定读取次数，避免暴力模拟，提高算法效率。

### 可拓展之处
类似的问题可以扩展到其他图论问题，如最短路径、最小生成树等，通过边或节点的属性来优化算法。

### 推荐题目
1. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
2. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
3. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)

---
处理用时：31.25秒