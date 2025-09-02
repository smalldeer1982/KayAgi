# 题目信息

# Darth Vader and Tree

## 题目描述

When Darth Vader gets bored, he sits down on the sofa, closes his eyes and thinks of an infinite rooted tree where each node has exactly $ n $ sons, at that for each node, the distance between it an its $ i $ -th left child equals to $ d_{i} $ . The Sith Lord loves counting the number of nodes in the tree that are at a distance at most $ x $ from the root. The distance is the sum of the lengths of edges on the path between nodes.

But he has got used to this activity and even grew bored of it. 'Why does he do that, then?' — you may ask. It's just that he feels superior knowing that only he can solve this problem.

Do you want to challenge Darth Vader himself? Count the required number of nodes. As the answer can be rather large, find it modulo $ 10^{9}+7 $ .

## 说明/提示

Pictures to the sample (the yellow color marks the nodes the distance to which is at most three)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF514E/dfa75ce6cc0df1087a16e02cadbd273a08641d03.png)

## 样例 #1

### 输入

```
3 3
1 2 3
```

### 输出

```
8
```

# AI分析结果



0. **题目翻译**

---

# 达斯·维达与树

## 题目描述

当达斯·维达感到无聊时，他会坐在沙发上，闭上眼睛想象一棵无限的根树。每个节点恰好有 $n$ 个子节点，其中第 $i$ 个左子节点到父节点的距离为 $d_i$。这位西斯领主热衷于计算树中到根节点距离不超过 $x$ 的节点数量。距离定义为路径上各边长度之和。

但这一活动已无法满足他。"他为何还要这么做？"你或许会问。原因很简单：他享受着只有自己能解决这一问题的优越感。

你愿意挑战达斯·维达吗？计算满足条件的节点数。由于答案可能很大，请对 $10^9+7$ 取模。

## 说明/提示

样例图示（黄色标记表示到根节点距离不超过三的节点）

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF514E/dfa75ce6cc0df1087a16e02cadbd273a08641d03.png)

## 样例 #1

### 输入
```
3 3
1 2 3
```

### 输出
```
8
```

---

1. **算法分类**  
   **线性DP + 矩阵快速幂**

2. **综合分析与结论**  
   **核心思路**：  
   - 定义 $f_i$ 表示距离根节点**恰好为** $i$ 的节点数  
   - 状态转移方程：$f_i = \sum_{j=1}^{100} t_j \cdot f_{i-j}$（其中 $t_j$ 是距离为 $j$ 的边数）  
   - 前缀和数组 $s_i = \sum_{j=0}^i f_j$ 记录答案  
   - 通过构造转移矩阵，使用矩阵快速幂加速计算  

   **关键难点**：  
   - 状态矩阵需要同时维护前缀和 $s$ 和最近的 $100$ 个 $f$ 值  
   - 矩阵构造需满足 $s_i = s_{i-1} + f_i$ 与 $f_i$ 的递推关系  

   **可视化设计**：  
   - **8-bit像素风格**：  
     - 用不同颜色区分 $s$ 行（黄色）和 $f$ 行（蓝色）  
     - 矩阵乘法时高亮当前计算的行列（闪烁效果）  
   - **音效系统**：  
     - 矩阵相乘时触发电子合成音效  
     - 快速幂分解指数时播放二进制切换声效  
   - **自动演示模式**：  
     - 分步展示前 3 次矩阵乘法过程  
     - 随后自动加速演示快速幂过程  

3. **题解清单 (≥4星)**  
   | 题解作者 | 星级 | 核心亮点 |
   |---------|------|----------|
   | Engulf  | ★★★★☆ | 矩阵构造最规范，维护二维状态清晰 |
   | Lucky_dpy | ★★★★ | 详细推导前缀和与状态转移关系 |
   | QwQcOrZ | ★★★★ | 代码结构简洁，矩阵构造技巧独特 |

4. **最优思路提炼**  
   **核心技巧**：  
   - **状态压缩**：将 $s_i$ 与 $f_i,f_{i-1},...,f_{i-99}$ 压缩为状态向量  
   - **矩阵设计**：  
     ```math
     \begin{bmatrix}
     1 & t_1 & t_2 & \cdots & t_{100} \\
     0 & t_1 & t_2 & \cdots & t_{100} \\
     0 & 1   & 0   & \cdots & 0 \\
     \vdots & \vdots & \vdots & \ddots & \vdots \\
     0 & 0 & \cdots & 1 & 0
     \end{bmatrix}
     ```
   - **预处理优化**：暴力计算前 100 项，剩余部分用矩阵快速幂  

5. **同类型题目推荐**  
   - [P1939] 矩阵加速（数列）  
   - [P3990] 超级马  
   - [P2106] Sam数  

6. **代码实现核心**  
   **矩阵快速幂核心代码**：
   ```cpp
   void mul(int c[][N], int a[][N], int b[][N]) {
       int t[N][N] = {};
       for(int i=0; i<101; i++)
           for(int k=0; k<101; k++) if(a[i][k])
               for(int j=0; j<101; j++)
                   t[i][j] = (t[i][j] + 1LL*a[i][k]*b[k][j])%mod;
       memcpy(c, t, sizeof t);
   }
   ```

7. **可视化代码片段**  
   ```javascript
   // 矩阵动画演示
   class MatrixAnimator {
       constructor(canvas) {
           this.ctx = canvas.getContext('2d');
           this.cellSize = 20;
           this.highlight = {x: -1, y: -1};
       }

       drawMatrix(m, offsetX, offsetY) {
           // 绘制矩阵的像素风格实现
           for(let i=0; i<m.rows; i++) {
               for(let j=0; j<m.cols; j++) {
                   const color = (i===0 || j===0) ? '#FFD700' : '#00BFFF';
                   this.ctx.fillStyle = color;
                   this.ctx.fillRect(...);
                   // 高亮当前计算单元
                   if(i === this.highlight.y && j === this.highlight.x) {
                       this.ctx.strokeStyle = '#FF0000';
                       this.ctx.strokeRect(...);
                   }
               }
           }
       }
   }
   ```

8. **关键调试心得**  
   - **边界处理**：必须预处理 $f_0=1$，否则无法生成任何子节点  
   - **矩阵维度**：状态向量长度应为 101（1个前缀和 + 100个f值）  
   - **取模优化**：在矩阵乘法内部取模，防止整数溢出  

---

**通过将线性递推转化为矩阵幂运算，本算法将时间复杂度从 $O(x)$ 优化至 $O(100^3 \log x)$，完美处理 $x \leq 10^9$ 的极端情况。这种状态压缩与矩阵构造技巧在解决类似递推问题时具有普适性。**

---
处理用时：81.41秒