# 题目信息

# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
3 5 6
```

### 输出

```
5```

# AI分析结果



# Amr and Chemistry

## 题目描述

Amr 热爱化学实验，他需要将所有化学试剂的体积调整为相同值。给定 $n$ 个试剂的初始体积 $a_i$，允许两种操作：
1. 将试剂体积加倍（即 $a_i \gets 2a_i$）
2. 将试剂体积折半取下整（即 $a_i \gets \lfloor a_i/2 \rfloor$）

求使所有试剂体积相等所需的最少操作次数。

## 样例 #1

### 输入
```
3
4 8 2
```

### 输出
```
2
```

---

### 综合题解分析

#### 最优解法思路
**核心思路**：将数值映射为完全二叉树节点（$x$ 的左儿子为 $2x$，右儿子为 $2x+1$），操作转化为树上移动。找到所有数的最近公共祖先（LCA）作为初始根，通过换根DP计算每个可能目标节点的总操作次数，取最小值。

**关键技巧**：
1. **树形结构建模**：数值操作转化为树节点的父子移动
2. **子树统计优化**：统计每个节点的子树包含的原始数值数量
3. **换根公式**：$dp[son] = dp[father] + (n - 2 \times cnt[son])$，快速转移计算结果

---

### 高分题解选录（评分4★+）

#### 题解1 - KokiNiwa（评分4.5★）
**亮点**：
- 巧妙利用数值结构隐式建树，避免显式Trie的内存开销
- 通过DFS预处理子树大小，换根时直接套用数学公式
- 时间复杂度 $O(n + \max a_i)$ 效率极高

**核心代码**：
```cpp
void dfs(int u) {
    if (u > maxVal) return;
    dfs(u*2); dfs(u*2+1);
    siz[u] = siz[u*2] + siz[u*2+1] + mark[u];
}

int main() {
    // 预处理子树大小
    dfs(1);
    
    // 寻找初始根（所有数的LCA）
    while (siz[root] != n) root >>= 1;
    
    // 换根计算
    while ((root << 1) <= maxVal) {
        tans += (n - 2*siz[root<<1]);
        root <<= 1;
        ans = min(ans, tans);
    }
}
```

#### 题解2 - Marsrayd（评分4★）
**亮点**：
- 显式维护每个节点的深度和子树信息
- 通过两次DFS实现换根DP
- 代码结构清晰易扩展

**个人心得**：
> "发现操作本质是树节点移动后，立即想到用经典树形DP框架。第二次DFS时的状态转移公式需要仔细推导父子节点贡献的变化关系。"

---

### 相似题目推荐
1. [P1099 树网的核](https://www.luogu.com.cn/problem/P1099) - 树形结构的最优路径选择
2. [P3177 树上染色](https://www.luogu.com.cn/problem/P3177) - 换根DP的经典应用
3. [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551) - 基于Trie树的路径处理

---
处理用时：51.83秒