# 题目信息

# [EC Final 2021] Fenwick Tree

## 题目描述

Prof. Pang is giving a lecture on the Fenwick tree (also called binary indexed tree). 

In a Fenwick tree, we have an array $c[1\ldots n]$ of length $n$ which is initially all-zero ($c[i]=0$ for any $1\le i\le n$). Each time, Prof. Pang can call the following procedure for some position $pos$ ($1\leq pos \leq n$) and value $val$:

```cpp
def update(pos, val):
    while (pos <= n):
        c[pos] += val
        pos += pos & (-pos)
```

Note that `pos & (-pos)` equals to the maximum power of $2$ that divides `pos` for any positive integer `pos`. 

In the procedure, $val$ can be **any real** number. After calling it some (zero or more) times, Prof. Pang forgets the exact values in the array $c$. He only remembers whether $c[i]$ is zero or not for each $i$ from $1$ to $n$. Prof. Pang wants to know what is the minimum possible number of times he called the procedure assuming his memory is accurate.

## 说明/提示

For the first example, Prof. Pang can call `update(1,1)`, `update(2,-1)`, `update(3,1)` in order.

For the third example, Prof. Pang can call `update(1,1)`, `update(3,1)`, `update(5,1)` in order.

## 样例 #1

### 输入

```
3
5
10110
5
00000
5
11111
```

### 输出

```
3
0
3
```

# AI分析结果

### 算法分类
树状数组、贪心

### 综合分析与结论
该题的核心在于理解树状数组的更新机制，并通过贪心策略最小化更新次数。所有题解都基于树状数组的 `lowbit` 操作，通过分析每个位置的目标状态和其子节点的影响，来决定是否需要额外的更新操作。虽然各题解的表述方式不同，但核心思路一致，均通过统计子节点的影响来判断当前节点是否需要更新。

### 所选高星题解

#### 1. 作者：naroto2022 (4星)
- **关键亮点**：清晰地解释了树状数组的更新机制，并通过统计子节点的影响来判断是否需要更新当前节点。代码简洁且逻辑清晰。
- **核心代码**：
  ```cpp
  for(int i=1; i<=n; i++){
      if(!b[i]&&a[i]||b[i]==1&&!a[i]) ++ans;
      if(a[i]&&(i&-i)+i<=n) ++b[(i&-i)+i];
  }
  ```
  **核心思想**：通过 `b[]` 数组记录子节点的影响，根据 `a[i]` 和 `b[i]` 的值决定是否需要更新。

#### 2. 作者：scp020 (4星)
- **关键亮点**：详细讨论了不同情况下是否需要更新操作，并通过 `f[]` 数组记录子节点的影响。代码结构清晰，逻辑严谨。
- **核心代码**：
  ```cpp
  for(int i=1,j,cnt;i<=n;i++)
  {
      if(st[i-1]=='1')
      {
          if(f[i]==0) ans++;
          if(i+lowbit(i)<=n) f[i+lowbit(i)]++;
      }else if(f[i]==1) ans++;
  }
  ```
  **核心思想**：通过 `f[]` 数组记录子节点的影响，根据 `st[i-1]` 和 `f[i]` 的值决定是否需要更新。

#### 3. 作者：SICKO (4星)
- **关键亮点**：通过 `the_change[]` 数组记录子节点的影响，并根据 `str[i-1]` 和 `the_change[i]` 的值决定是否需要更新。代码简洁且逻辑清晰。
- **核心代码**：
  ```cpp
  for(int i=1; i<=n; i++)
  {
      if(str[i-1] == '1' && i+(i&-i)<=n) the_change[i+(i&-i)]++;
  }
  for(int i=1; i<=n; i++)
  {
      if(str[i-1] == '0' && the_change[i]==1) ans++;
      if(str[i-1] == '1' && the_change[i]==0) ans++;
  }
  ```
  **核心思想**：通过 `the_change[]` 数组记录子节点的影响，根据 `str[i-1]` 和 `the_change[i]` 的值决定是否需要更新。

### 最优关键思路
1. **树状数组的 `lowbit` 操作**：理解 `lowbit` 操作是解决问题的关键，它决定了每个节点的更新路径。
2. **贪心策略**：通过统计子节点的影响，决定当前节点是否需要更新，从而最小化更新次数。
3. **状态转移**：通过数组记录子节点的影响，并根据当前节点的目标状态决定是否需要更新。

### 拓展思路
- **类似题目**：可以尝试解决其他基于树状数组的题目，如区间更新、区间查询等问题。
- **优化技巧**：在实际应用中，可以通过预处理或动态规划进一步优化更新次数。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

---
处理用时：20.47秒