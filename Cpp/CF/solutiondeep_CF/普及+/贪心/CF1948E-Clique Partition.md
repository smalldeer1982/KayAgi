# 题目信息

# Clique Partition

## 题目描述

You are given two integers, $ n $ and $ k $ . There is a graph on $ n $ vertices, numbered from $ 1 $ to $ n $ , which initially has no edges.

You have to assign each vertex an integer; let $ a_i $ be the integer on the vertex $ i $ . All $ a_i $ should be distinct integers from $ 1 $ to $ n $ .

After assigning integers, for every pair of vertices $ (i, j) $ , you add an edge between them if $ |i - j| + |a_i - a_j| \le k $ .

Your goal is to create a graph which can be partitioned into the minimum possible (for the given values of $ n $ and $ k $ ) number of cliques. Each vertex of the graph should belong to exactly one clique. Recall that a clique is a set of vertices such that every pair of vertices in it are connected with an edge.

Since BledDest hasn't really brushed his programming skills up, he can't solve the problem "given a graph, partition it into the minimum number of cliques". So we also ask you to print the partition itself.

## 样例 #1

### 输入

```
3
2 3
5 4
8 16```

### 输出

```
2 1
1
1 1
3 1 5 2 4
2
1 1 2 1 2
1 2 3 4 5 6 7 8
1
1 1 1 1 1 1 1 1```

# AI分析结果



### 题目内容中文翻译

# 团划分

## 题目描述

给定两个整数 $n$ 和 $k$。初始时，编号为 $1$ 到 $n$ 的顶点构成的无边图。你需要为每个顶点分配一个唯一的 $1$ 到 $n$ 的整数 $a_i$。对于任意顶点对 $(i,j)$，若 $|i - j| + |a_i - a_j| \le k$，则在其间连边。要求将该图划分为尽可能少的团（完全子图），并输出划分方案。

## 样例 #1

### 输入

```
3
2 3
5 4
8 16
```

### 输出

```
2 1
1
1 1
3 1 5 2 4
2
1 1 2 1 2
1 2 3 4 5 6 7 8
1
1 1 1 1 1 1 1 1
```

---

### 题解综合分析

所有题解均基于两个核心观察：  
1. **团内编号连续且权值连续**：每个团的顶点编号连续，且其权值集合对应一个连续区间。  
2. **最大团大小不超过 $k$**：若团大小为 $m$，则任意两点需满足 $|i-j| + |a_i-a_j| \le k$，这要求 $m \le k$。

最优策略是将顶点划分为 $\lceil n/k \rceil$ 个连续块，每个块内构造特殊排列使得所有点对满足条件。关键构造技巧为将块分为前后两半并逆序排列，从而保证曼哈顿距离总和不超过 $k$。

---

### 精选题解

#### 题解1：作者：_Z_F_R_（★★★★★）
**关键亮点**：  
- 严谨的数学证明与构造思路，详细分析了团的性质及构造可行性。  
- 代码简洁高效，直接生成每块的逆序排列。  
**核心代码**：  
```cpp
vector<int> Gen_vec(int siz) {
    vector<int> vec;
    for(int i = siz/2; i >= 1; i--) vec.push_back(i);
    for(int i = siz; i > siz/2; i--) vec.push_back(i);
    return vec;
}
// 调用示例：生成每个块的排列
for(int i=1; i<=n; i+=k) {
    int l=i, r=min(i+k-1, n);
    auto vec = Gen_vec(r-l+1);
    for(auto v : vec) cout << v + l -1 << " ";
}
```

#### 题解2：作者：elbissoPtImaerD（★★★★☆）
**关键亮点**：  
- 从坐标系视角将问题转化为曼哈顿距离覆盖，直观且易于理解。  
- 代码实现简洁，直接对每块中点进行逆序处理。  
**核心代码**：  
```cpp
for(int l=0; l<n; l+=k) {
    int r=min(n, l+k), mid=(l+r)>>1;
    for(int i=mid; i>=l; i--) a[i] = --t; // 前半逆序
    for(int i=r-1; i>mid; i--) a[i] = --t; // 后半逆序
}
```

#### 题解3：作者：Drind（★★★★☆）
**关键亮点**：  
- 明确构造方案的数学表达式，并给出严格下界证明。  
- 代码清晰，通过分组偏移实现权值分配。  
**核心代码**：  
```cpp
for(int i=l; i<=mid; i++) 
    ans[i] = i + (len+1)/2; // 前半偏移
for(int i=mid+1; i<=r; i++) 
    ans[i] = i - len/2;     // 后半偏移
```

---

### 关键思路总结
1. **分块策略**：将 $n$ 个顶点划分为 $\lceil n/k \rceil$ 个连续块，每块最多 $k$ 个顶点。  
2. **逆序构造**：每块内部将前一半和后一半分别逆序排列，使得任意两点的曼哈顿距离总和不超过 $k$。  
3. **团编号分配**：直接按块顺序标记顶点所属团，保证划分结果的最小性。

---

### 拓展与举一反三
- **类似问题**：涉及曼哈顿距离构造的题目（如 CF1542C Strange Function）、分块贪心策略（如洛谷 P1969 积木大赛）。  
- **推荐练习**：  
  1. [CF1542C - Strange Function](https://codeforces.com/problemset/problem/1542/C)  
  2. [洛谷 P1969 积木大赛](https://www.luogu.com.cn/problem/P1969)  
  3. [CF1367D Task On The Board](https://codeforces.com/problemset/problem/1367/D)  

---

### 个人心得摘录
- **调试经验**：多位作者提到需注意奇数/偶数块的中位点处理，避免边界错误。  
- **构造顿悟**：将曼哈顿距离转化为坐标系中的菱形覆盖，是此类问题的通用分析技巧。

---
处理用时：67.36秒