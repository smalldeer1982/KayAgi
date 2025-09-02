# 题目信息

# [ABC366F] Maximum Composition

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc366/tasks/abc366_f

$ N $ 個の一次関数 $ f_1,f_2,\ldots,f_N $ が与えられます。$ f_i(x)=A_i\ x+B_i $ です。

$ 1 $ 以上 $ N $ 以下の**相異なる** $ K $ 個の整数からなる長さ $ K $ の数列 $ p=(p_1,p_2,\ \ldots\ p_K) $ について、$ f_{p_1}(f_{p_2}(\ldots\ f_{p_K}(1)\ldots\ )) $ としてありえる最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ K\ \leq\ \text{min}(N,10) $
- $ 1\ \leq\ A_i,B_i\ \leq\ 50 $ $ (1\ \leq\ i\ \leq\ N) $
- 入力はすべて整数

### Sample Explanation 1

ありえるすべての $ p $ とそれに対応する $ f_{p_1}(f_{p_2}(1)) $ の値は以下の通りです。 - $ p=\ (\ 1,2\ ) $ : $ f_1(f_2(1))=15 $ - $ p=\ (\ 1,3\ ) $ : $ f_1(f_3(1))=15 $ - $ p=\ (\ 2,1\ ) $ : $ f_2(f_1(1))=10 $ - $ p=\ (\ 2,3\ ) $ : $ f_2(f_3(1))=11 $ - $ p=\ (\ 3,1\ ) $ : $ f_3(f_1(1))=22 $ - $ p=\ (\ 3,2\ ) $ : $ f_3(f_2(1))=26 $ よって、 $ 26 $ と出力します。

## 样例 #1

### 输入

```
3 2
2 3
1 5
4 2```

### 输出

```
26```

## 样例 #2

### 输入

```
10 3
48 40
34 22
24 37
45 40
48 31
49 44
45 40
44 6
35 22
39 28```

### 输出

```
216223```

# AI分析结果



# 题目重写

## [ABC366F] Maximum Composition

### 题目描述

给定 $N$ 个一次函数 $f_1,f_2,\ldots,f_N$，其中 $f_i(x)=A_i x+B_i$。

请你从 $1$ 到 $N$ 的整数中选出 **互不相同** 的 $K$ 个元素，构成长度为 $K$ 的数列 $p=(p_1,p_2,\ldots,p_K)$。求 $f_{p_1}(f_{p_2}(\ldots f_{p_K}(1)\ldots ))$ 可能达到的最大值。

### 输入格式

第一行包含两个整数 $N$ 和 $K$。  
接下来 $N$ 行每行两个整数 $A_i$ 和 $B_i$。

### 输出格式

输出计算结果的最大值。

### 样例 #1

#### 输入
```
3 2
2 3
1 5
4 2
```

#### 输出
```
26
```

### 提示

#### 数据范围
- $1 \leq N \leq 2 \times 10^5$
- $1 \leq K \leq \min(N,10)$
- $1 \leq A_i,B_i \leq 50$

#### 样例解释
所有可能的 $p$ 及其计算结果：
- $p=(1,2)$ → $f_1(f_2(1))=15$
- $p=(1,3)$ → $f_1(f_3(1))=15$
- $p=(2,1)$ → $f_2(f_1(1))=10$
- $p=(2,3)$ → $f_2(f_3(1))=11$
- $p=(3,1)$ → $f_3(f_1(1))=22$
- $p=(3,2)$ → $f_3(f_2(1))=26$

---

## 唯一算法分类：线性DP

---

## 综合分析与结论

### 核心思路
1. **排序规则推导**  
   通过比较相邻函数的嵌套顺序，得出最优排列规则：当 $A_iB_j+B_i < A_jB_i+B_j$ 时，函数 $j$ 应该放在函数 $i$ 外层。等价于按 $\frac{A_i-1}{B_i}$ 降序排序。

2. **动态规划设计**  
   - **状态定义**：$dp[i][j]$ 表示前 $i$ 个排序后的函数中选 $j$ 个的最大值
   - **转移方程**：$dp[i][j] = \max(dp[i-1][j], A_i \cdot dp[i-1][j-1] + B_i)$
   - **空间优化**：使用滚动数组或前缀最大值优化，将空间复杂度降至 $O(K)$

3. **可视化设计**  
   采用像素风格动画展示 DP 矩阵更新过程：
   - **网格绘制**：用 Canvas 绘制 $N \times K$ 的网格，每个单元格代表 $dp[i][j]$
   - **颜色标记**：黄色高亮当前处理的 $(i,j)$，绿色标记被更新的单元格
   - **音效触发**：在状态转移时播放 8-bit 点击音效，找到新最优值时播放升级音效
   - **自动演示**：以 500ms/步的速度自动填充矩阵，支持暂停/步进

### 关键难点
- **数学推导排序规则**：需要发现嵌套顺序与 $x$ 无关的特性，通过比较固定项得到排序依据
- **处理大规模数据**：在 $N=2e5$ 时需确保 $O(NK)$ 时间复杂度的可行性
- **空间优化**：通过滚动数组或前缀最大值处理，避免存储完整二维数组

---

## 题解评分（≥4星）

### 1. 作者：lzyqwq（★★★★☆）
**关键亮点**  
- 完整数学推导证明排序规则  
- 使用前缀最大值优化空间  
- 代码简洁高效（55ms）  
**核心代码**  
```cpp
sort(a + 1, a + n + 1, [](Line x, Line y) {
    return x.b * (y.a - 1) > y.b * (x.a - 1);
});
for(int i=1; i<=n; i++)
    for(int j=k; j>=1; j--)
        dp[j] = max(dp[j], a[i].a * dp[j-1] + a[i].b);
```

### 2. 作者：cancan123456（★★★★☆）
**关键亮点**  
- 提供正统解法与贪心解法对比  
- 数学表达式转换清晰  
- 代码包含详细注释  
**核心公式**  
$$
\frac{B_i}{A_i-1} > \frac{B_j}{A_j-1} \Rightarrow (A_i-1)B_j < (A_j-1)B_i
$$

### 3. 作者：wly09（★★★★☆）
**关键亮点**  
- 空间优化至一维数组  
- 状态转移方向明确  
- 代码风格简洁  
**状态转移**  
```cpp
for(int i=1; i<=n; i++)
    for(int j=k; j; --j)
        maxx[j] = max(maxx[j], a[i].a * maxx[j-1] + a[i].b);
```

---

## 最优思路提炼

### 核心技巧
1. **邻项交换法**  
   通过比较相邻元素交换后的结果推导排序规则：
   ```math
   \frac{(A_i-1)}{B_i} > \frac{(A_j-1)}{B_j} \Rightarrow 优先内层嵌套
   ```

2. **滚动数组优化**  
   逆向枚举维度避免状态覆盖：
   ```cpp
   for(int j=k; j>=1; j--)  // 逆向枚举保证使用旧状态
   ```

3. **前缀最大值预处理**  
   维护前缀最大值避免重复计算：
   ```cpp
   prefix_max[i] = max(prefix_max[i-1], dp[i])
   ```

---

## 相似题目推荐

1. **P1776 宝物筛选**（多重背包+单调队列优化）
2. **P1064 金明的预算方案**（依赖背包+分组决策） 
3. **P1541 乌龟棋**（多维线性DP+状态压缩）

---

## 可视化代码片段（JavaScript）

```javascript
// Canvas初始化
const canvas = document.getElementById('dp-grid');
const ctx = canvas.getContext('2d');
const CELL_SIZE = 40;

// 绘制DP网格
function drawGrid(n, k) {
    for(let i=0; i<=n; i++) {
        for(let j=0; j<=k; j++) {
            ctx.strokeRect(j*CELL_SIZE, i*CELL_SIZE, CELL_SIZE, CELL_SIZE);
        }
    }
}

// 更新单元格
function updateCell(i, j, value, isNewMax) {
    ctx.fillStyle = isNewMax ? '#90EE90' : '#FFFF00';
    ctx.fillRect(j*CELL_SIZE, i*CELL_SIZE, CELL_SIZE, CELL_SIZE);
    ctx.fillStyle = 'black';
    ctx.fillText(value, j*CELL_SIZE+5, i*CELL_SIZE+20);
    playSound(isNewMax ? 'upgrade' : 'click');
}

// 音效管理
const audio = {
    click: new Audio('data:audio/wav;base64,UklGRl9...'),
    upgrade: new Audio('data:audio/wav;base64,UklGRk9...')
};
function playSound(type) {
    audio[type].cloneNode(true).play();
}
```

---

## 个人心得摘录

> **作者：lzyqwq**  
> "当发现排序规则后，意识到最优解必然是排序序列的子序列，这瞬间将指数级复杂度降为多项式级。调试时通过小样例验证数学推导的正确性至关重要。"

> **作者：JuRuoOIer**  
> "贪心解法虽然能AC，但意识到其局限性后，改用DP的正统解法，深刻理解到数学证明才是算法基石。"

---
处理用时：96.04秒