# 题目信息

# Serious Business

## 题目描述

Dima is taking part in a show organized by his friend Peter. In this show Dima is required to cross a $ 3 \times n $ rectangular field. Rows are numbered from $ 1 $ to $ 3 $ and columns are numbered from $ 1 $ to $ n $ .

The cell in the intersection of the $ i $ -th row and the $ j $ -th column of the field contains an integer $ a_{i,j} $ . Initially Dima's score equals zero, and whenever Dima reaches a cell in the row $ i $ and the column $ j $ , his score changes by $ a_{i,j} $ . Note that the score can become negative.

Initially all cells in the first and the third row are marked as available, and all cells in the second row are marked as unavailable. However, Peter offered Dima some help: there are $ q $ special offers in the show, the $ i $ -th special offer allows Dima to mark cells in the second row between $ l_i $ and $ r_i $ as available, though Dima's score reduces by $ k_i $ whenever he accepts a special offer. Dima is allowed to use as many special offers as he wants, and might mark the same cell as available multiple times.

Dima starts his journey in the cell $ (1, 1) $ and would like to reach the cell $ (3, n) $ . He can move either down to the next row or right to the next column (meaning he could increase the current row or column by 1), thus making $ n + 1 $ moves in total, out of which exactly $ n - 1 $ would be horizontal and $ 2 $ would be vertical.

Peter promised Dima to pay him based on his final score, so the sum of all numbers of all visited cells minus the cost of all special offers used. Please help Dima to maximize his final score.

## 说明/提示

In the first example, it is optimal to use Peter's second offer of $ 4 $ rubles and go through the cells $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ , $ (3, 3) $ , $ (3, 4) $ , earning $ 1 + 0 + 2 + 9 + 4 + 1 - 4 = 13 $ rubles in total.

In the second example, it is optimal to use Peter's second and third offers of $ 2 $ and $ 3 $ rubles, respectively, and go through the cells $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (3, 4) $ , $ (3, 5) $ , earning $ -20 + 1 + 3 + 3 + 6 + 6 + 2 - 2 - 3= -4 $ rubles.

## 样例 #1

### 输入

```
4 3
1 0 2 -1
-3 1 9 2
3 2 4 1
1 2 5
2 3 4
1 4 14```

### 输出

```
13```

## 样例 #2

### 输入

```
5 4
-20 -10 -11 -10 1
1 3 3 6 3
14 -20 3 6 2
1 5 13
1 2 2
3 5 3
2 3 1```

### 输出

```
-4```

# AI分析结果



0. **题目翻译**  
   
   ## 严肃生意  
   
   ### 题目描述  
   
   Dima 正在参加朋友 Peter 组织的节目。在这个节目中，Dima 需要穿过一个 $3 \times n$ 的矩形场地。行从 $1$ 到 $3$ 编号，列从 $1$ 到 $n$ 编号。  
   
   场地中第 $i$ 行第 $j$ 列的格子包含整数 $a_{i,j}$。初始时，Dima 的得分为零，每当他到达 $(i,j)$ 时，得分会根据 $a_{i,j}$ 变化（得分可能为负数）。  
   
   初始时，第一行和第三行的所有格子可用，第二行的所有格子不可用。Peter 提供了 $q$ 个特殊提议：第 $i$ 个提议允许 Dima 将第二行 $[l_i,r_i]$ 区间的格子标记为可用，但接受该提议会使总分扣除 $k_i$ 点。  
   
   Dima 需要从 $(1,1)$ 移动到 $(3,n)$，每次只能向下或向右移动（总共 $n+1$ 次移动，其中 $n-1$ 次横向移动，2 次纵向移动）。请帮他计算最大净得分（经过格子的总和减去所有使用提议的代价）。  
   
   ### 输入输出样例  
   见原题描述。  

---

1. **唯一算法分类**  
   线性DP

---

2. **综合分析与结论**  
   **核心思路**：  
   - 状态设计：$f[i]$ 表示到达第二行第 $i$ 列的最大收益  
   - 转移方程：  
     $$f[i] = \max\left( \text{来自上方}\ f[l-1] + \text{区间收益},\ \text{来自左侧}\ \max_{k \in [l,i]} (pre1_k + \text{区间收益}) \right)$$  
   - 使用线段树维护区间最大值，支持两种操作：  
     1. 区间查询 $\max(f[l..r])$  
     2. 区间更新 $\max(pre1[k] - cost)$  

   **可视化设计**：  
   - **动画方案**：  
     - 动态展示 DP 数组的更新过程，用颜色梯度表示数值大小  
     - 线段树节点高亮显示当前被查询/更新的区间  
     - 使用箭头标注转移来源（上方转移用↑，左侧转移用←）  
   - **复古像素风格**：  
     - 将 DP 数组渲染为 8x8 像素块，每个像素块用不同颜色表示数值区间  
     - 线段树采用经典俄罗斯方块风格的分层结构  
     - 音效：状态更新时播放 FC 风格的「叮」声，最优解更新时播放金币音效  

---

3. **题解清单（≥4星）**  
   **gyh20（4.5星）**  
   - 亮点：首创线段树维护两类转移（延伸转移和直接转移）  
   - 代码实现：通过两个线段树分别处理不同情况的转移  

   **lzqy_（4.2星）**  
   - 亮点：将转移拆解为独立的两部分，通过前缀和优化  
   - 关键代码：  
     ```cpp  
     f[i] = max(Query1(区间), Query2(区间)) + 前缀和  
     ```  

   **GaryH（4.0星）**  
   - 亮点：将问题转化为图论最短路模型，CDQ分治优化  
   - 创新点：用红黑树维护动态区间最大值  

---

4. **核心代码实现**  
   ```cpp
   // 线段树维护最大值（简化版）
   struct SEG {
       ll mx[N<<2], tag[N<<2];
       void pushup(int p) { mx[p] = max(mx[p<<1], mx[p<<1|1]); }
       void update(int p, int L, int R, ll val) {
           if(覆盖区间) mx[p] = max(mx[p], val);
           else {
               pushdown(p);
               update(左儿子);
               update(右儿子);
               pushup(p);
           }
       }
       ll query(int p, int L, int R) { /* 区间查询逻辑 */ }
   } T1, T2;

   // DP主逻辑
   for(int i=1; i<=n; i++) {
       for(auto offer : 覆盖i的提议) {
           ll case1 = T1.query(offer.l-1, i-1) - k; // 延伸转移
           ll case2 = T2.query(offer.l, i) - k;     // 直接转移
           f[i] = max(f[i], max(case1, case2) + sum2[i]);
       }
       T1.update(i, f[i] - sum2[i]); // 更新线段树
       T2.update(i, pre1[i] - sum2[i-1]);
   }
   ```

---

5. **类似题目推荐**  
   - P1541 乌龟棋（线性DP+多维状态）  
   - P4095 [HEOI2013]Eden的新背包问题（多重背包+线段树优化）  
   - P5490 【模板】扫描线（线段树处理区间覆盖）

---

6. **可视化代码片段**  
   ```javascript
   // Canvas绘制DP数组（伪代码）
   function drawDPGrid() {
       ctx.fillStyle = '#2D2D2D'; // 复古深灰背景
       for(let i=0; i<n; i++) {
           const val = dp[i];
           const color = getColorByValue(val); // 根据数值映射到8位色
           ctx.fillRect(i*8, 0, 8, 8, color);
       }
   }

   // 音效触发
   function playSound(type) {
       const sfx = {
           update: [0.5, , 0.02,, 0.02, 0.3, , 0.3], // 8位音效参数
           optimal: [1, , 0.02, , 0.3, 0.7, , 0.5]
       };
       synth.trigger(sfx[type]);
   }
   ```

---
处理用时：72.22秒