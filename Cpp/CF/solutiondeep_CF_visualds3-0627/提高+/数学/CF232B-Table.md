# 题目信息

# Table

## 题目描述

John Doe has an $ n×m $ table. John Doe can paint points in some table cells, not more than one point in one table cell. John Doe wants to use such operations to make each square subtable of size $ n×n $ have exactly $ k $ points.

John Doe wondered, how many distinct ways to fill the table with points are there, provided that the condition must hold. As this number can be rather large, John Doe asks to find its remainder after dividing by $ 1000000007 $ $ (10^{9}+7) $ .

You should assume that John always paints a point exactly in the center of some cell. Two ways to fill a table are considered distinct, if there exists a table cell, that has a point in one way and doesn't have it in the other.

## 说明/提示

Let's consider the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF232B/8876a3223960f71627c5d6c6a4c6ddb988dcaef6.png) The gray area belongs to both $ 5×5 $ squares. So, if it has one point, then there shouldn't be points in any other place. If one of the white areas has a point, then the other one also must have a point. Thus, there are about $ 20 $ variants, where the point lies in the gray area and $ 25 $ variants, where each of the white areas contains a point. Overall there are $ 45 $ variants.

## 样例 #1

### 输入

```
5 6 1
```

### 输出

```
45```

# AI分析结果



---

### 唯一算法分类  
**组合数学**

---

### 综合分析与结论  
**核心思路**：发现列之间的周期性（相隔 n 的列选点数必须相同），转化为前 n 列的动态规划问题。通过预处理组合数的幂次优化时间复杂度。  

**关键公式**：  
1. 第 i 列出现次数：  
   $\text{cnt}_i = \lfloor \frac{m-1}{n} \rfloor + [i \leq (m-1) \bmod n + 1]$  
2. 动态规划转移方程：  
   $f[i][j] = \sum_{t=0}^{\min(j,n)} f[i-1][j-t] \times \binom{n}{t}^{\text{cnt}_i}$  

**可视化设计**：  
- **网格动画**：  
  1. 以像素风格绘制 n×n 表格，高亮当前处理的列  
  2. 动态显示组合数 $\binom{n}{t}$ 的计算过程（如逐行展开杨辉三角）  
  3. 每次转移时，用粒子特效表示幂次计算（如 $\binom{n}{t}^{\text{cnt}_i}$ 的指数增长效果）  
- **音效触发**：  
  - 选择点数时播放 8-bit 点击声  
  - 完成一列转移时播放上升音阶  

---

### 题解清单（≥4星）  
1. **MCAdam（4.5星）**  
   - 亮点：代码简洁，预处理组合数快速幂  
   - 关键代码：  
     ```cpp
     for(int i=1;i<=n;i++)
         for(int j=0;j<=n;j++)
             fp[i][j]=power(C[n][j],(m-1)/n+(i<=(m-1)%n+1));
     ```

2. **feecle6418（4星）**  
   - 亮点：最简实现，直接嵌套预处理与转移  
   - 核心逻辑：  
     ```cpp
     for(int j=0;j<=n;j++)
         w[i][j]=Power(c[n][j],(i<=(m-1)%n+1)?(m-1)/n+1:(m-1)/n);
     ```

3. **ysl_wf（4星）**  
   - 亮点：详细解释列出现次数计算原理  
   - 关键注释：  
     ```cpp
     // 计算式推导：(m-i)/n + 1 的等价变形
     ```

---

### 最优思路/技巧提炼  
1. **周期性观察**：发现相隔 n 的列必须相同，将问题规模从 1e18 压缩到 n  
2. **快速幂预处理**：对组合数的指数运算预处理，将 O(n^4 logn) 优化为 O(n^4)  
3. **高效计数公式**：  
   ```cpp
   cnt_i = (m-1)/n + (i <= (m-1)%n + 1)  // 避免浮点运算
   ```

---

### 同类型题套路  
1. **周期性结构处理**：当数据范围出现极大值（如 1e18）时，寻找模 n 的等价类  
2. **组合数+DP**：常见于需要同时考虑排列组合与状态转移的问题  
3. **幂次预处理**：对固定底数、不同指数的幂进行预处理，优化动态规划转移  

---

### 推荐练习题  
1. **P3758** [TJOI2017]可乐（矩阵快速幂）  
2. **P3223** [HNOI2012]排队（组合数+高精度）  
3. **P2767** 组合数问题（模意义下组合数性质）

---

### 个人心得摘录  
> "当 m 达到 1e18 时，直觉应该寻找周期性或矩阵快速幂解法。本题的列等价观察让我联想到循环节压缩技巧。" —— MCAdam  
> "调试时发现 (m-1)%n 的边界处理容易出错，最终采用 (m-1)/n 形式避免整除问题。" —— ysl_wf

---

### 核心代码实现（MCAdam版）  
```cpp
// 预处理组合数快速幂
for(int i=1;i<=n;i++)
    for(int j=0;j<=n;j++)
        fp[i][j] = power(C[n][j], (m-1)/n + (i <= (m-1)%n +1));

// 动态规划转移
f[0][0] = 1;
for(int i=1;i<=n;i++)
    for(int j=0; j<=min(k,i*n); j++)
        for(int t=0; t<=min(j,n); t++)
            f[i][j] = (f[i][j] + f[i-1][j-t] * fp[i][t]) % mod;
```

---

### 复古可视化伪代码（Canvas版）  
```javascript
// 初始化 8-bit 调色板
const COLORS = ["#000000","#1A1A1A","#4A4A4A","#FFFFFF","#FF4500"];

function drawGrid(ctx) {
    // 绘制 n×n 网格，用不同颜色表示已处理/当前列
    for(let i=0; i<n; i++) {
        ctx.fillStyle = (i == currentCol) ? COLORS[4] : COLORS[2];
        ctx.fillRect(i*16, 0, 15, 15);
    }
}

function playSound(freq) {
    // Web Audio API 生成 8-bit 音效
    const osc = audioCtx.createOscillator();
    osc.frequency.value = freq;
    osc.connect(audioCtx.destination);
    osc.start(); osc.stop(0.05);
}
```

---
处理用时：80.79秒