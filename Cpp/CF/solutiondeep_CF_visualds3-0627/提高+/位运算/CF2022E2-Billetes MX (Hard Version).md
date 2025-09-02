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



## 唯一算法分类  
**并查集（Union-Find）**

---

## 综合分析与结论  

### 题目核心与难点  
题目要求构造满足特定异或条件的网格，并处理动态更新后的方案数。核心难点在于：  
1. **异或约束的全局性**：所有子矩阵四角异或和为0，等价于任意两行/两列的异或差固定。  
2. **动态更新的合法性维护**：每次更新需快速判断是否引入矛盾，并维护剩余自由变量数目。  
3. **高效计算方案数**：合法状态下，答案需快速计算为 \(2^{30 \times (s-1)}\)，其中 \(s\) 是连通块数。  

### 题解对比与核心算法流程  
1. **larsr的题解**  
   - **核心思路**：将行和列视为图节点，已知值 \(A_{r,c}=v\) 转化为边 \(r \leftrightarrow (c+n)\)，权为 \(v\)。  
   - **并查集维护**：合并节点时检查异或环的合法性，连通块数 \(s\) 决定方案数 \(2^{30(s-1)}\)。  
   - **关键数据结构**：带权并查集，记录父节点和路径异或值。  
   - **时间复杂度**：\(O((k+q) \alpha(n+m))\)，适用于大规模数据。  

2. **2020HZ06的题解**  
   - **核心思路**：维护行的异或前缀和 \(s_j\)，通过并查集合并列约束。  
   - **权值维护**：合并时调整权值，确保 \(s_{j_1} \oplus s_{j_2} = v\)。  
   - **难点**：路径权值的动态调整，合并时需处理异或偏移量。  

3. **lfxxx的题解**  
   - **核心思路**：逐位拆解，每比特位独立处理，扩展域并查集维护约束。  
   - **复杂度**：\(O(30 \times (k+q) \alpha(m))\)，实现复杂但模块化。  

### 最优思路提炼  
**larsr的并查集模型**为最优：  
1. **图论建模**：行/列作为节点，已知值作为边，将全局约束转化为连通性问题。  
2. **动态合并与冲突检测**：每次合并检查异或环合法性，冲突则方案数为0。  
3. **方案数计算**：连通块数 \(s\) 决定自由变量，快速幂计算 \(2^{30(s-1)}\)。  

---

## 题解清单 (≥4星)  

### 1. larsr的题解（⭐⭐⭐⭐⭐）  
- **亮点**：简洁高效，直接建模为并查集问题，代码可读性强。  
- **核心代码**：  
  ```cpp
  void uni(int u, int v, int w) {
      int xu = u, xv = v;
      u = getfa(u); v = getfa(v);
      if(u == v) {
          if((fv[xu] ^ fv[xv] ^ w) != 0) hf = 0;
          return;
      }
      f[u] = v;
      fv[u] = w ^ fv[xu] ^ fv[xv];
      ans--;
  }
  ```

---

## 可视化与算法演示  

### 动画设计  
1. **并查集合并过程**：  
   - **节点表示**：行节点（红色方块）、列节点（蓝色方块）。  
   - **边添加**：已知值 \(A_{r,c}=v\) 时，绘制红蓝方块间的连线，标注权值 \(v\)。  
   - **合并动画**：高亮合并的父节点，显示路径异或值的更新。  

2. **冲突检测**：  
   - **矛盾环**：检测到环异或非零时，高亮相关节点和边为闪烁红色，播放“失败”音效。  

3. **连通块计数**：  
   - **动态计数面板**：实时显示当前连通块数 \(s\)，公式 \(2^{30(s-1)}\) 动态计算。  

### 复古像素风格  
- **8位像素UI**：节点用8x8像素块表示，边为像素线条，权值用点阵字体显示。  
- **音效设计**：  
  - **合并成功**：短促“哔”声（8位音效）。  
  - **冲突发生**：低沉“嗡”声。  
  - **自动播放模式**：背景播放芯片音乐，节奏随操作频率变化。  

### 交互功能  
- **步进控制**：暂停/继续/单步执行，调节动画速度。  
- **AI自动演示**：自动按输入顺序添加边，高亮当前操作，展示算法全流程。  

---

## 同类型题与推荐  
1. **洛谷 P1892 [BOI2003]团伙**（并查集扩展应用）  
2. **洛谷 P2024 [NOI2001] 食物链**（带权并查集）  
3. **洛谷 P1525 关押罪犯**（二分+并查集）  

---

## 个人心得摘录  
- **larsr的调试经验**：“合并时需同时更新路径异或值，否则无法正确检测环矛盾。”  
- **lfxxx的顿悟**：“按位拆分后，每位独立处理，避免复杂全局约束。”  

---

## 代码实现片段（关键逻辑）  
```cpp
// 并查集查询与合并（larsr的题解核心）
int getfa(int x) {
    if(f[x] == x) return x;
    int xx = getfa(f[x]);
    fv[x] ^= fv[f[x]]; // 路径压缩时更新异或值
    f[x] = xx;
    return xx;
}

void uni(int u, int v, int w) {
    int xu = u, xv = v;
    u = getfa(u); v = getfa(v);
    if(u == v) {
        if((fv[xu] ^ fv[xv]) != w) hf = 0; // 冲突检测
        return;
    }
    f[u] = v;
    fv[u] = fv[xu] ^ fv[xv] ^ w; // 合并时设置异或偏移
    ans--; // 连通块减少
}
```

---
处理用时：78.90秒