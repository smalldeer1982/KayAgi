# 题目信息

# Billetes MX (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, it is guaranteed that $ q = 0 $ . You can make hacks only if both versions of the problem are solved.

An integer grid $ A $ with $ p $ rows and $ q $ columns is called beautiful if:

- All elements of the grid are integers between $ 0 $ and $ 2^{30}-1 $ , and
- For any subgrid, the XOR of the values at the corners is equal to $ 0 $ . Formally, for any four integers $ i_1 $ , $ i_2 $ , $ j_1 $ , $ j_2 $ ( $ 1 \le i_1 < i_2 \le p $ ; $ 1 \le j_1 < j_2 \le q $ ), $ A_{i_1, j_1} \oplus A_{i_1, j_2} \oplus A_{i_2, j_1} \oplus A_{i_2, j_2} = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

There is a partially filled integer grid $ G $ with $ n $ rows and $ m $ columns where only $ k $ cells are filled. Polycarp wants to know how many ways he can assign integers to the unfilled cells so that the grid is beautiful.

However, Monocarp thinks that this problem is too easy. Therefore, he will perform $ q $ updates on the grid. In each update, he will choose an unfilled cell and assign an integer to it. Note that these updates are persistent. That is, changes made to the grid will apply when processing future updates.

For each of the $ q + 1 $ states of the grid, the initial state and after each of the $ q $ queries, determine the number of ways Polycarp can assign integers to the unfilled cells so that the grid is beautiful. Since this number can be very large, you are only required to output their values modulo $ 10^9+7 $ .

## 说明/提示

In the first test case of the example, we have the following grid:

  $ 0 $  $ 6 $  $ 10 $  $ 6 $  $ 0 $  $ 12 $  $ 10 $  $ 12 $  $ ? $ It can be proven that the only valid value for tile $ (3, 3) $ is $ 0 $ .

## 样例 #1

### 输入

```
2
3 3 8 0
2 1 6
3 2 12
1 2 6
2 2 0
1 3 10
1 1 0
2 3 12
3 1 10
2 5 2 0
1 1 10
1 2 30```

### 输出

```
1
489373567```

# AI分析结果



## 算法分类
并查集

## 综合分析与结论

### 核心思路与难点
题目要求构造满足特定异或约束的网格。核心思路是将每个单元格的值视为两个变量（行变量和列变量）的异或。通过并查集维护这些变量间的约束关系，检测环中的矛盾，最终通过连通块数量计算方案数。

**关键步骤**：
1. **变量建模**：每个元素 $A_{i,j}$ 表示为 $w_i \oplus w_{n+j}$，其中 $w$ 是隐藏变量。
2. **约束转化为图**：已知值 $A_{r,c}=v$ 转化为边 $w_r \leftrightarrow w_{c+n}$，权值为 $v$。
3. **并查集维护连通性**：合并节点时检查路径异或是否合法，矛盾则无解。
4. **计算自由变量数**：连通块数 $s$ 决定方案数，公式为 $(2^{30})^{s-1} \mod 10^9+7$。

**难点**：
- 如何将网格约束抽象为图论问题。
- 动态维护异或路径的正确性。
- 避免重复计算并正确处理连通块数。

### 题解清单 (4星及以上)
1. **larsr的题解 (5星)**  
   - 思路清晰，将问题转化为并查集模型，代码简洁高效。
   - 正确维护异或路径和连通块数，时间复杂度接近线性。
   - 通过初始化技巧巧妙计算 $s-1$，避免冗余操作。

### 最优思路提炼
- **并查集+异或路径压缩**：将每个约束视为图中的边，用并查集同时维护连通性和异或值。
- **连通块计数**：初始自由度为 $n+m$，合并后剩余连通块数决定方案数指数。
- **矛盾检测**：合并时检查环的异或合法性，确保无解情况及时终止。

### 代码实现核心逻辑
```cpp
// 并查集实现核心代码
int getfa(int x) {
    if (f[x] == x) return x;
    int root = getfa(f[x]);
    fv[x] ^= fv[f[x]]; // 路径压缩时更新异或值
    f[x] = root;
    return root;
}

void uni(int u, int v, int w) {
    int fu = getfa(u), fv_node = getfa(v);
    if (fu == fv_node) {
        if ((fv[u] ^ fv[v]) != w) hf = 0; // 检测矛盾
        return;
    }
    f[fu] = fv_node;
    fv[fu] = fv[u] ^ fv[v] ^ w; // 更新异或关系
    ans--; // 连通块数减1
}
```

### 可视化设计
- **动画方案**：  
  1. **网格绘制**：Canvas绘制初始网格，已知值高亮显示。
  2. **节点合并动画**：点击单元格时，动态显示行/列节点合并过程，高亮当前操作边。
  3. **连通块染色**：不同连通块用不同颜色标记，自由变量闪烁提示。
  4. **矛盾提示**：检测到非法合并时，触发红色闪烁并播放错误音效。

- **复古像素风格**：  
  - 8位色调色板（16色），网格线使用深灰色。
  - 节点用2x2像素块表示，合并时显示像素扩散效果。
  - 背景音乐采用8位芯片音乐循环播放。

### 同类型题目推荐
1. P1525 [NOI2001] 食物链（并查集扩展域）
2. P2024 [NOI2001] 奇偶游戏（异或约束）
3. P1955 [NOI2015] 程序自动分析（并查集离散化）

---
处理用时：126.07秒