# 题目信息

# Tree XOR

## 题目描述

You are given a tree with $ n $ vertices labeled from $ 1 $ to $ n $ . An integer $ a_{i} $ is written on vertex $ i $ for $ i = 1, 2, \ldots, n $ . You want to make all $ a_{i} $ equal by performing some (possibly, zero) spells.

Suppose you root the tree at some vertex. On each spell, you can select any vertex $ v $ and any non-negative integer $ c $ . Then for all vertices $ i $ in the subtree $ ^{\dagger} $ of $ v $ , replace $ a_{i} $ with $ a_{i} \oplus c $ . The cost of this spell is $ s \cdot c $ , where $ s $ is the number of vertices in the subtree. Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Let $ m_r $ be the minimum possible total cost required to make all $ a_i $ equal, if vertex $ r $ is chosen as the root of the tree. Find $ m_{1}, m_{2}, \ldots, m_{n} $ .

 $ ^{\dagger} $ Suppose vertex $ r $ is chosen as the root of the tree. Then vertex $ i $ belongs to the subtree of $ v $ if the simple path from $ i $ to $ r $ contains $ v $ .

## 说明/提示

In the first test case, to find $ m_1 $ we root the tree at vertex $ 1 $ .

1. In the first spell, choose $ v=2 $ and $ c=1 $ . After performing the spell, $ a $ will become $ [3, 3, 0, 1] $ . The cost of this spell is $ 3 $ .
2. In the second spell, choose $ v=3 $ and $ c=3 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 1] $ . The cost of this spell is $ 3 $ .
3. In the third spell, choose $ v=4 $ and $ c=2 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 3] $ . The cost of this spell is $ 2 $ .

Now all the values in array $ a $ are equal, and the total cost is $ 3 + 3 + 2 = 8 $ .

The values $ m_2 $ , $ m_3 $ , $ m_4 $ can be found analogously.

In the second test case, the goal is already achieved because there is only one vertex.

## 样例 #1

### 输入

```
2
4
3 2 1 0
1 2
2 3
2 4
1
100```

### 输出

```
8 6 12 10 
0```

# AI分析结果



# Tree XOR

## 题目描述

给定一棵 $n$ 个节点的树，节点编号为 $1$ 到 $n$。每个节点 $i$ 有一个整数权值 $a_i$。当以节点 $r$ 为根时，可以通过以下操作使所有节点权值相等：选择节点 $v$ 和非负整数 $c$，将 $v$ 子树中所有节点的权值异或 $c$，代价为子树大小乘以 $c$。要求对每个节点作为根的情况，计算最小总代价。

## 样例解释

当根为节点1时，通过三次操作达成全等，总代价为8。其他根的计算方式类似。

---

## 题解分析与结论

### 关键思路
1. **贪心策略**：将子树权值统一调整为当前根节点权值，避免重复操作。
2. **换根DP**：以任意根初始化后，通过父子关系推导其他根的答案。
3. **贡献分析**：将问题分解为边的异或值贡献，利用子树大小快速计算。

### 精选题解

#### 西瓜nd的题解（★★★★★）
**亮点**：严格证明贪心策略的正确性，清晰展示状态转移方程，代码可读性强  
```cpp
void dfs1(int x,int fath){
    siz[x]=1;
    for(int to:g[x]){
        if(to==fath)continue;
        dfs1(to,x);
        siz[x]+=siz[to];
        dp[x] += dp[to] + siz[to]*(a[x]^a[to]);
    }
    f[x]=dp[x];
}

void dfs2(int x,int fath){
    for(int to:g[x]){
        if(to==fath)continue;
        f[to] += f[x] - (dp[to]+siz[to]*(a[x]^a[to])) 
                + (n-siz[to])*(a[x]^a[to]);
        dfs2(to,x);
    }
}
```
**核心思想**：首次DFS计算根的初始代价，二次DFS通过父节点答案推导子节点答案，利用子树大小差调整贡献。

#### xkcdjerry的题解（★★★★☆）
**亮点**：巧妙转化为边贡献问题，利用差分降低复杂度  
```cpp
void dfs1(int x,int fa){
    sz[x]=1;
    for(auto i:e[x]) if(i!=fa){
        dfs1(i,x);
        sz[x]+=sz[i];
        ll w=a[x]^a[i];
        f[1]+=sz[i]*w;
        f[i] += w*(n-2*sz[i]);
    }
}

void dfs2(int x,int fa){
    f[x]+=f[fa];
    for(auto i:e[x]) if(i!=fa) dfs2(i,x);
}
```
**核心思想**：将总代价拆分为全局基础贡献和子树修正项，通过一次DFS预处理，二次DFS累加差分数组。

---

## 关键技巧
1. **异或性质运用**：利用异或的自反性（$x \oplus x = 0$）简化操作分析。
2. **子树贡献分离**：通过维护子树大小快速计算换根时的贡献变化量。
3. **差分优化**：将区间修改转化为端点操作，降低时间复杂度。

## 拓展练习
1. [CF1324F - Maximum White Subtree](https://codeforces.com/problemset/problem/1324/F)（换根DP经典题）
2. [P3478 [POI2008] STA-Station](https://www.luogu.com.cn/problem/P3478)（换根DP求最长链）
3. [CF1394B - Boboniu Walks on Graph](https://codeforces.com/problemset/problem/1394/B)（位运算与图论结合）

---
处理用时：51.96秒