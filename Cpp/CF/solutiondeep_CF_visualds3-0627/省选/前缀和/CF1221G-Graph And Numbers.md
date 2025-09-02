# 题目信息

# Graph And Numbers

## 题目描述

You are given an undirected graph with $ n $ vertices and $ m $ edges. You have to write a number on each vertex of this graph, each number should be either $ 0 $ or $ 1 $ . After that, you write a number on each edge equal to the sum of numbers on vertices incident to that edge.

You have to choose the numbers you will write on the vertices so that there is at least one edge with $ 0 $ written on it, at least one edge with $ 1 $ and at least one edge with $ 2 $ . How many ways are there to do it? Two ways to choose numbers are different if there exists at least one vertex which has different numbers written on it in these two ways.

## 样例 #1

### 输入

```
6 5
1 2
2 3
3 4
4 5
5 1
```

### 输出

```
20
```

## 样例 #2

### 输入

```
4 4
1 2
2 3
3 4
4 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
35 29
1 2
2 3
3 1
4 1
4 2
3 4
7 8
8 9
9 10
10 7
11 12
12 13
13 14
14 15
15 16
16 17
17 18
18 19
19 20
20 21
21 22
22 23
23 24
24 25
25 26
26 27
27 28
28 29
29 30
```

### 输出

```
34201047040
```

# AI分析结果



### 算法分类
**容斥原理 + 折半搜索 (Meet-in-the-Middle) + 高维前缀和**

---

### 综合分析与结论
#### 核心思路与难点
1. **容斥框架**  
   将问题转化为计算总方案数减去不满足条件的方案数。通过容斥公式：
   ```
   ans = 总方案 - 无0边方案 - 无1边方案 - 无2边方案 
         + 无01边方案 + 无02边方案 + 无12边方案 
         - 无012边方案
   ```
   其中大部分项可直接计算（如连通块计数、二分图判定），难点在于处理**无0边方案**（等价于独立集计数）。

2. **独立集计数优化**  
   - **折半搜索**：将点集分为两半，枚举左半合法状态，统计右半满足约束的子集。
   - **高维前缀和**：预处理右半部分合法状态，快速计算左半状态对应的右半合法子集数。

3. **其他关键点**  
   - 孤立点贡献需单独统计。
   - 二分图判定用于计算某些容斥项。

#### 可视化设计
1. **动画流程**  
   - **分屏展示**：左侧显示左半点集枚举过程，右侧显示高维前缀和统计。
   - **颜色标记**：红色表示当前枚举的左半状态，蓝色表示对应的右半合法区域，绿色表示已统计的合法子集。
   - **动态更新**：当左半选中一个点时，自动禁用右半相邻点，并更新右半合法区域。

2. **复古像素风格示例**  
   - **Canvas网格**：用8位像素风格绘制点阵图，每个点用16x16像素方块表示。
   - **音效设计**：枚举时播放“滴”声，合法状态统计时播放“叮”声，容斥项计算错误时播放“哔”声。
   - **自动演示**：初始自动运行，用户可暂停后手动调整分界线位置（如将n=40分为20+20或17+23）。

---

### 题解评分（≥4星）
1. **AThousandSuns（5星）**  
   - **亮点**：代码简洁，高维前缀和实现高效，时间复杂度最优（O(2^{n/2}n)）。
   - **代码片段**：
     ```cpp
     void dfs1(int dep, ll st, ll used) { // 预处理左半合法状态
         if (dep == bar) return void(val[(~st) & (lim-1)]++);
         dfs1(dep-1, st, used);
         if (!((st >> dep) & 1)) dfs1(dep-1, st | e[dep], used | (1 << dep));
     }
     ```

2. **Alex_Wei（5星）**  
   - **亮点**：逻辑清晰，详细拆解各容斥项，独立集计数模块化。
   - **代码片段**：
     ```cpp
     for (int i = 0; i < Rs; i++) if (check_r(i)) 
         ans -= 2ll * sum[solve(i)]; // 高维前缀和统计
     ```

3. **Fish_ht（4星）**  
   - **亮点**：详细注释，分步解释容斥项计算，适合教学。
   - **代码片段**：
     ```cpp
     ll NoAdj() { // 折半搜索独立集计数
         B = n * log2(3) / log2(6);
         // ...预处理左半状态，高维前缀和统计右半
     }
     ```

---

### 最优思路与技巧
1. **容斥框架与独立集优化**  
   将复杂约束分解为多个可计算项，通过折半搜索将指数级复杂度降为 O(2^{n/2}n)。

2. **高维前缀和加速**  
   对右半合法状态预处理，利用位运算快速统计子集和。

3. **连通块与孤立点处理**  
   利用并查集快速统计连通块数和孤立点贡献。

---

### 相似题目推荐
1. **洛谷 P3067 [USACO12OPEN]Balanced Cow Subsets**  
   - 折半搜索 + 双指针统计子集和。
2. **洛谷 P2396 yyy loves Maths VII**  
   - 容斥 + 状态压缩动态规划。
3. **洛谷 P2831 [NOIP2016 提高组] 愤怒的小鸟**  
   - 状压DP + 抛物线的预处理。

---

### 可视化代码片段（像素风格动画）
```javascript
// Canvas绘制点阵图（简化示例）
const ctx = canvas.getContext('2d');
const colors = { left: '#FF0000', right: '#00FF00', disabled: '#444444' };

function drawGrid(leftMask, rightValid) {
    ctx.clearRect(0, 0, 640, 640);
    // 绘制左半部分
    for (let i = 0; i < leftSize; i++) {
        const x = (i % 20) * 32, y = Math.floor(i / 20) * 32;
        ctx.fillStyle = (leftMask & (1 << i)) ? colors.left : '#FFFFFF';
        ctx.fillRect(x, y, 32, 32);
    }
    // 绘制右半合法区域
    for (let i = 0; i < rightSize; i++) {
        const valid = (rightValid & (1 << i));
        ctx.fillStyle = valid ? colors.right : colors.disabled;
        ctx.fillRect(320 + (i % 20)*32, Math.floor(i/20)*32, 32, 32);
    }
}
```

---

### 个人心得摘录
- **AThousandSuns**：  
  “折半搜索的关键在于将问题分为两半，使得合并两半结果的复杂度可控。高维前缀和在此处巧妙地将 O(3^n) 暴力优化为 O(n2^n)。”
  
- **Fish_ht**：  
  “独立集计数的难点在于高效枚举，选择度数最大的点进行分治，能显著减少递归次数。”

---
处理用时：89.98秒