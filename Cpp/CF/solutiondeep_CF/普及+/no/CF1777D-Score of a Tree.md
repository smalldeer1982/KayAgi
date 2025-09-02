# 题目信息

# Score of a Tree

## 题目描述

You are given a tree of $ n $ nodes, rooted at $ 1 $ . Every node has a value of either $ 0 $ or $ 1 $ at time $ t=0 $ .

At any integer time $ t>0 $ , the value of a node becomes the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of the values of its children at time $ t - 1 $ ; the values of leaves become $ 0 $ since they don't have any children.

Let $ S(t) $ denote the sum of values of all nodes at time $ t $ .

Let $ F(A) $ denote the sum of $ S(t) $ across all values of $ t $ such that $ 0 \le t \le 10^{100} $ , where $ A $ is the initial assignment of $ 0 $ s and $ 1 $ s in the tree.

The task is to find the sum of $ F(A) $ for all $ 2^n $ initial configurations of $ 0 $ s and $ 1 $ s in the tree. Print the sum modulo $ 10^9+7 $ .

## 说明/提示

Let us find $ F(A) $ for the configuration $ A = [0,1,0,0,1,1] $ ( $ A[i] $ denotes the value of node $ i $ ). Initially (at $ t = 0 $ ) our tree is as shown in the picture below. In each node, two values are shown: the number and the value of this node. $ S(0) $ for this configuration is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1777D/10211706e57f1b1e88b0d4ddb7c1af191838660c.png)At $ t = 1 $ the configuration changes to $ [1,0,0,0,0,0] $ . The tree looks as shown below. $ S(1) = 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1777D/c3bc7f260147d61f562afc931fe76e6b883432c7.png)At $ t = 2 $ the configuration changes to $ [0,0,0,0,0,0] $ . The tree looks as shown below. $ S(2) = 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1777D/fa1abea375196a437b8f0800465795a0a4b9553a.png)For all $ t>2 $ , the graph remains unchanged, so $ S(t)=0 $ for all $ t > 2 $ . So, for the initial configuration $ A = [0,1,0,0,1,1] $ , the value of $ F(A) = 3 + 1 = 4 $ .

Doing this process for all possible $ 2^{6} $ configurations yields us an answer of $ \textbf{288} $ .

## 样例 #1

### 输入

```
1
6
1 2
1 3
3 4
3 5
3 6```

### 输出

```
288```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一棵有 $n$ 个节点的树，根节点为 $1$。每个节点在 $t=0$ 时刻的值为 $0$ 或 $1$。

在任意整数时间 $t>0$，节点的值变为其子节点在 $t-1$ 时刻的值的异或和；叶子节点的值变为 $0$，因为它们没有子节点。

定义 $S(t)$ 为时间 $t$ 时所有节点的值之和。

定义 $F(A)$ 为所有 $t$ 满足 $0 \le t \le 10^{100}$ 时 $S(t)$ 的总和，其中 $A$ 是树在 $t=0$ 时刻的初始值配置。

任务是求所有 $2^n$ 种初始配置下 $F(A)$ 的总和，输出结果对 $10^9+7$ 取模。

#### 说明/提示

举例说明 $F(A)$ 的计算过程。假设初始配置 $A = [0,1,0,0,1,1]$，$S(0) = 3$。在 $t=1$ 时，配置变为 $[1,0,0,0,0,0]$，$S(1) = 1$。在 $t=2$ 时，配置变为 $[0,0,0,0,0,0]$，$S(2) = 0$。对于所有 $t>2$，$S(t)=0$。因此，$F(A) = 3 + 1 = 4$。

对所有 $2^6$ 种初始配置进行计算，最终答案为 $288$。

#### 样例 #1

##### 输入

```
1
6
1 2
1 3
3 4
3 5
3 6
```

##### 输出

```
288
```

### 算法分类
数学、概率论、组合数学

### 题解分析与结论

本题的核心在于分析每个节点在不同时间点的值变化规律，并利用对称性和概率论的思想，将问题转化为对每个节点的贡献进行统计。通过树形 DP 或 DFS 计算每个节点的深度，最终利用组合数学的结论得出答案。

### 高星题解

#### 题解1：作者：yemuzhe (赞：10)

**星级：5星**

**关键亮点：**
- 通过观察和推导，得出每个节点在不同时间点的贡献规律。
- 利用树形 DP 计算每个节点的深度，并结合组合数学的结论得出答案。
- 代码实现清晰，避免了不必要的初始化操作。

**核心代码：**
```cpp
int dfs(int x) {
    int res = 0, mx = 0;
    v[x] = 1;
    for (int i = head[x], y; i; i = nxt[i]) {
        if (v[y = ver[i]]) continue;
        res = (res + dfs(y)) % MOD;
        mx = max(mx, s[y]);
    }
    res = (res + (s[x] = mx + 1)) % MOD;
    return res;
}
```

#### 题解2：作者：ExplodingKonjac (赞：10)

**星级：5星**

**关键亮点：**
- 通过对称性构造，简化了问题的复杂度。
- 利用概率论的思想，证明了每个节点在特定时间点的贡献概率为 $1/2$。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
void dfs(int u, int fa=0) {
    dep[u] = 1;
    for(auto &v: g[u]) {
        if(v==fa) continue;
        dfs(v,u);
        dep[u] = max(dep[u], dep[v]+1);
    }
    ans += dep[u];
}
```

#### 题解3：作者：NaN_HQJ2007_NaN (赞：8)

**星级：4星**

**关键亮点：**
- 通过异或性质，推导出每个节点在不同时间点的贡献规律。
- 利用树形 DP 计算每个节点的深度，并结合组合数学的结论得出答案。
- 代码实现简洁，逻辑清晰。

**核心代码：**
```cpp
void dfs(int u, int lst) {
    dis[u] = 1;
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i]; if (v == lst) continue;
        dfs(v, u); dis[u] = max(dis[u], 1 + dis[v]);
    }
}
```

### 最优关键思路或技巧

1. **对称性构造**：通过对称性构造，简化了问题的复杂度，使得每个节点的贡献可以通过概率论的思想进行计算。
2. **树形 DP**：利用树形 DP 计算每个节点的深度，从而得出每个节点在不同时间点的贡献。
3. **组合数学**：利用组合数学的结论，得出每个节点在特定时间点的贡献概率为 $1/2$，从而简化了计算。

### 可拓展之处

类似的问题可以通过对称性和概率论的思想进行简化，尤其是在涉及到大量状态或组合数的问题中。树形 DP 是处理树结构问题的常用方法，可以应用于多种树相关的算法问题。

### 推荐题目

1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
3. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)

### 个人心得

- **调试经历**：在实现树形 DP 时，需要注意避免重复访问父节点，否则会导致无限递归。
- **顿悟感想**：通过对称性和概率论的思想，可以将复杂的问题简化为简单的概率计算，极大地提高了问题的解决效率。

---
处理用时：48.91秒