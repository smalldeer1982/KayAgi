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



## 算法分类
树形动态规划（换根DP）

## 题解思路与解决难点
### 核心思路
1. **贪心策略**：以每个节点为根时，优先处理所有子树使其值与当前根节点相同。对每个子树根v，必须且仅需进行一次异或操作c = (a_v ^ a_root)，使得子树v所有节点值变为根的值。
2. **动态规划**：定义dp[u]为以u为根的子树调整为统一值的总代价。通过两次DFS实现：
   - **初始DFS**：计算以1号节点为根的dp值，转移方程：dp[u] += dp[v] + siz[v] * (a[u]^a[v])
   - **换根DFS**：根据父节点f的代价推导子节点u的代价，公式：g[u] = g[f] + (总节点数 - 2*siz[u])*(a[f]^a[u])

### 解决难点
1. **子树贡献的数学推导**：正确计算换根时不同子树贡献的变化，通过(n - 2*siz[u])巧妙调整全局贡献。
2. **线性复杂度**：两次DFS遍历即可完成所有节点的计算，时间复杂度O(n)。

## 题解评分
1. 西瓜nd（5星）：思路清晰，给出贪心证明，代码简洁高效。
2. hcywoi（4星）：代码简洁，直接给出最终公式，但缺乏详细推导。
3. syysongyuyang（4星）：公式推导简明，代码实现直观。

## 最优思路提炼
1. **贪心策略**：子树操作顺序不影响最终结果，只需保证每个子树先于父节点处理。
2. **换根公式**：利用父节点已计算的结果，通过(n - 2*siz[u])快速调整子树贡献。
3. **位独立处理**（可选扩展）：拆解每位单独处理，但主流解法利用异或性质直接整体处理。

## 同类型题目
- [CF1324F Maximum White Subtree](https://codeforces.com/problemset/problem/1324/F)
- [POJ 2378 Tree Cutting](http://poj.org/problem?id=2378)
- [洛谷 P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)

## 可视化设计
### 动画方案
1. **树结构渲染**：使用Canvas绘制树形结构，节点以圆点表示，边带权值(a_u^a_v)。
2. **换根过程**：
   - 初始状态高亮根节点1，逐步展开子树计算dp值。
   - 换根时用颜色渐变表示父节点切换，展示公式(n-2*siz[u])的推导过程。
3. **贡献调整**：当根从u切换到v时，用箭头标注受影响的子树区域，动态显示贡献值的变化。

### 复古像素风格
- **节点绘制**：8-bit风格圆点，不同颜色表示不同子树。
- **音效设计**：
  - 每次异或操作时播放"哔"声。
  - 换根成功时播放上升音阶。
- **自动演示**：按DFS顺序自动遍历节点，支持暂停/单步调试。

## 核心代码实现
```cpp
void dfs1(int x, int fath) {
    siz[x] = 1;
    for (int to : g[x]) {
        if (to == fath) continue;
        dfs1(to, x);
        siz[x] += siz[to];
        dp[x] += dp[to] + siz[to] * (a[x] ^ a[to]);
    }
}

void dfs2(int x, int fath) {
    for (int to : g[x]) {
        if (to == fath) continue;
        f[to] = f[x] - siz[to] * (a[x] ^ a[to]) 
               + (n - siz[to]) * (a[x] ^ a[to]);
        dfs2(to, x);
    }
}
```

## 关键代码说明
- **dfs1**：自底向上计算子树代价，siz记录子树大小，dp累加子树的异或代价。
- **dfs2**：换根时调整全局代价，利用父节点f的已知结果快速计算子节点to的代价。

---
处理用时：57.17秒