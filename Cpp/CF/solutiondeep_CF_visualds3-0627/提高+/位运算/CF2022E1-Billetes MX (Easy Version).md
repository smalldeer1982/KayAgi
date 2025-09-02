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



**唯一算法分类**  
并查集

---

**综合分析与结论**  
本题要求构造满足特定异或条件的矩阵，其核心在于将矩阵元素转化为行与列变量的异或关系。关键难点在于维护动态更新中的约束一致性，通过并查集高效处理连通性与异或权值。

**核心算法流程**  
1. **变量建模**：将矩阵元素视为行变量与列变量的异或组合（即 `A[i][j] = w_i ⊕ w_{n+j}`）。  
2. **并查集维护**：当填充一个值时，合并对应的行与列变量，维护路径上的异或值。  
3. **矛盾检测**：若合并过程中发现异或值不一致，则无解。  
4. **自由度计算**：答案由连通块数量决定，公式为 `2^(30*(s-1)) mod 1e9+7`，其中 `s` 为连通块数。

**可视化设计思路**  
- **动态合并动画**：用像素方块表示行/列变量，颜色区分连通块。合并时显示连线，矛盾时闪烁红色。  
- **复古音效**：合并成功播放“滴”声，矛盾时播放“哔”声，计算自由度时播放胜利音效。  
- **自动演示模式**：AI 自动添加约束，展示并查集状态与答案更新过程。

---

**题解清单 (≥4星)**  
1. **larsr 的题解（5星）**  
   - **亮点**：高效并查集建模，直接处理异或关系，代码简洁。  
   - **关键代码**：通过 `uni(x, n+y, v)` 合并行与列，维护异或权值。  

---

**最优思路提炼**  
- **并查集异或建模**：将矩阵元素拆为行与列变量的异或，避免枚举所有子矩阵。  
- **权值路径压缩**：在 `getfa` 时更新每个节点到根的异或值，确保快速查询。  
- **连通块计数**：初始连通块数为 `n+m`，每次合并减少计数，最终计算 `2^(30*(s-1))`。

---

**同类型题与算法套路**  
- **异或约束问题**：通过并查集维护变量间的异或关系。  
- **动态连通性**：处理动态更新的连通块合并与矛盾检测。  

**推荐题目**  
1. 洛谷 P1892（团伙：扩展域并查集）  
2. 洛谷 P1525（关押罪犯：最大值约束下的并查集）  
3. 洛谷 P2024（食物链：带权并查集经典题）

---

**个人心得摘录**  
- **调试关键**：路径压缩时需同步更新异或权值，否则会导致计算错误。  
- **顿悟点**：将矩阵元素拆解为行与列变量后，所有约束自动满足，极大简化问题。

---

**代码实现**  
```cpp
// larsr 题解的核心代码
void upd(int x, int y, int v) {
    uni(x, n + y, v); // 合并行x与列y，权值为v
}

void uni(int u, int v, int w) {
    int xu = getfa(u), xv = getfa(v);
    if (xu == xv) {
        if (fv[u] ^ fv[v] != w) hf = 0; // 检测矛盾
        return;
    }
    f[xu] = xv;
    fv[xu] = fv[u] ^ fv[v] ^ w; // 更新权值
    ans--; // 连通块减少
}
```

---

**可视化与游戏化设计**  
- **8位像素风格**：行变量用绿色方块，列变量用蓝色，合并后变为黄色。  
- **Canvas动画**：点击单元格添加约束，自动演示并查集合并过程。  
- **音效设计**：成功合并播放 `8-bit click.wav`，矛盾时播放 `error.wav`。  
- **自动演示模式**：按空格键启动AI，随机添加约束并展示结果。

---
处理用时：79.35秒