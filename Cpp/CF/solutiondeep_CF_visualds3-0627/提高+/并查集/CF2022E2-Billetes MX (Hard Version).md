# 题目信息

# Billetes MX (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, it is guaranteed that $ q \leq 10^5 $ . You can make hacks only if both versions of the problem are solved.

An integer grid $ A $ with $ p $ rows and $ q $ columns is called beautiful if:

- All elements of the grid are integers between $ 0 $ and $ 2^{30}-1 $ , and
- For any subgrid, the XOR of the values at the corners is equal to $ 0 $ . Formally, for any four integers $ i_1 $ , $ i_2 $ , $ j_1 $ , $ j_2 $ ( $ 1 \le i_1 < i_2 \le p $ ; $ 1 \le j_1 < j_2 \le q $ ), $ A_{i_1, j_1} \oplus A_{i_1, j_2} \oplus A_{i_2, j_1} \oplus A_{i_2, j_2} = 0 $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

There is a partially filled integer grid $ G $ with $ n $ rows and $ m $ columns where only $ k $ cells are filled. Polycarp wants to know how many ways he can assign integers to the unfilled cells so that the grid is beautiful.

However, Monocarp thinks that this problem is too easy. Therefore, he will perform $ q $ updates on the grid. In each update, he will choose an unfilled cell and assign an integer to it. Note that these updates are persistent. That is, changes made to the grid will apply when processing future updates.

For each of the $ q + 1 $ states of the grid, the initial state and after each of the $ q $ queries, determine the number of ways Polycarp can assign integers to the unfilled cells so that the grid is beautiful. Since this number can be very large, you are only required to output their values modulo $ 10^9+7 $ .

## 说明/提示

In the first test case of the example, we initially have the following grid:

  $ 0 $  $ 6 $  $ 10 $  $ 6 $  $ 0 $  $ 12 $  $ 10 $  $ 12 $  $ ? $ It can be proven that the only valid value for tile $ (3, 3) $ is $ 0 $ , so the first answer is $ 1 $ . For the second query, the grid does not satisfy the condition, and thus the answer is $ 0 $ .

## 样例 #1

### 输入

```
3
3 3 8 1
2 1 6
3 2 12
1 2 6
2 2 0
1 3 10
1 1 0
2 3 12
3 1 10
3 3 1
2 5 2 0
1 1 10
1 2 30
2 5 0 2
1 1 10
1 2 30```

### 输出

```
1
0
489373567
651321892
769740174
489373567```

# AI分析结果



**算法分类**  
并查集（带权并查集）

---

**题解思路、算法要点与解决难点**  
本题核心是维护网格的异或约束条件，将每个单元格的约束转化为图论问题。通过并查集维护行和列变量之间的异或关系，统计连通块数目并检查冲突。

1. **建模关键**  
   每个元素 `A[i][j]` 可表示为 `w_i XOR w_{j+n}`（`w` 是虚拟变量）。这使得任意四个角异或为 0，满足题目条件。
2. **并查集设计**  
   - 节点：行变量 `1~n`，列变量 `n+1~n+m`。
   - 权值：`fv[x]` 表示节点 `x` 到父节点的异或值。
3. **合并与冲突检查**  
   - 添加约束 `A[r][c] = v` 对应合并行 `r` 和列 `c+n`，权值为 `v`。
   - 若合并时发现环且异或值矛盾，则无解。
4. **答案计算**  
   若无冲突，答案为 `2^(30*(连通块数-1))`，利用快速幂预处理结果。

---

**题解评分**  
1. **larsr (★★★★★)**  
   - **亮点**：简洁的并查集实现，高效处理异或约束，时间复杂度接近线性。
   - **代码可读性**：路径压缩与权值更新逻辑清晰，预处理幂次优化计算。

---

**最优思路与技巧**  
- **虚拟变量分解**：将矩阵元素拆解为行和列变量的异或，巧妙转化约束为图论问题。
- **带权并查集**：维护异或权值，路径压缩时同步更新权值，确保动态约束一致性。
- **冲突检测**：合并时检查异或矛盾，保证约束合法性。

---

**同类型题与算法套路**  
- **异或约束问题**：类似 P1525 关押罪犯（扩展域并查集）。
- **连通块计数**：如 P1197 星球大战（动态维护连通性）。
- **动态更新与持久化**：参考 P3402 可持久化并查集。

---

**推荐题目**  
1. P1525 关押罪犯（扩展域并查集）  
2. P1197 星球大战（连通块动态维护）  
3. P4185 MooTube（离线查询与并查集结合）

---

**代码实现核心逻辑**  
```cpp
int f[N], fv[N]; // 并查集父节点与异或权值

int getfa(int x) {
    if (f[x] == x) return x;
    int root = getfa(f[x]);
    fv[x] ^= fv[f[x]]; // 路径压缩时更新权值
    f[x] = root;
    return root;
}

void uni(int u, int v, int w) {
    int fu = getfa(u), fv_node = getfa(v);
    if (fu == fv_node) {
        if ((fv[u] ^ fv[v]) != w) hf = 0; // 冲突检测
        return;
    }
    f[fu] = fv_node;
    fv[fu] = fv[u] ^ fv[v] ^ w; // 权值合并
    ans--; // 连通块数减1
}
```

---

**可视化与算法演示**  
**动画设计**：  
1. **节点与边表示**：行节点为红色方块，列节点为蓝色方块，边权显示异或值。  
2. **合并过程**：点击单元格时，高亮对应行列节点，动态绘制边并播放合并音效。  
3. **冲突提示**：检测到矛盾时，节点闪烁红色并播放失败音效。  
4. **连通块统计**：右侧面板实时显示当前连通块数和计算结果。  

**复古像素风格**：  
- **调色板**：8位红/蓝/绿色表示节点，黄色边线。  
- **音效**：合并成功（高音嘟声），冲突（低音嗡鸣），背景芯片音乐循环。  
- **Canvas 绘制**：网格布局，节点用 16x16 像素块，边线动态连接。  

**交互功能**：  
- **步进控制**：支持单步执行更新，观察合并细节。  
- **自动模式**：AI 逐步添加约束，展示算法动态决策过程。  

---

**结论**  
本题通过并查集将异或约束转化为连通性问题，高效处理动态更新。核心在于虚拟变量建模与带权合并，可视化设计通过像素风格和动态交互直观展示算法流程。

---
处理用时：137.43秒