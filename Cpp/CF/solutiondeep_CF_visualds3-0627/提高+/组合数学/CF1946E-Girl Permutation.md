# 题目信息

# Girl Permutation

## 题目描述

Some permutation of length $ n $ is guessed.

You are given the indices of its prefix maximums and suffix maximums.

Recall that a permutation of length $ k $ is an array of size $ k $ such that each integer from $ 1 $ to $ k $ occurs exactly once.

Prefix maximums are the elements that are the maximum on the prefix ending at that element. More formally, the element $ a_i $ is a prefix maximum if $ a_i > a_j $ for every $ j < i $ .

Similarly, suffix maximums are defined, the element $ a_i $ is a suffix maximum if $ a_i > a_j $ for every $ j > i $ .

You need to output the number of different permutations that could have been guessed.

As this number can be very large, output the answer modulo $ 10^9 + 7 $ .

## 说明/提示

The following permutations are suitable for the second set of input data:

- $ [1, 4, 3, 2] $
- $ [2, 4, 3, 1] $
- $ [3, 4, 2, 1] $

The following permutations are suitable for the sixth set of input data:

- $ [2, 1, 6, 5, 3, 4] $
- $ [3, 1, 6, 5, 2, 4] $
- $ [3, 2, 6, 5, 1, 4] $
- $ [4, 1, 6, 5, 2, 3] $
- $ [4, 2, 6, 5, 1, 3] $
- $ [4, 3, 6, 5, 1, 2] $
- $ [5, 1, 6, 4, 2, 3] $
- $ [5, 2, 6, 4, 1, 3] $
- $ [5, 3, 6, 4, 1, 2] $
- $ [5, 4, 6, 3, 1, 2] $

## 样例 #1

### 输入

```
6
1 1 1
1
1
4 2 3
1 2
2 3 4
3 3 1
1 2 3
3
5 3 4
1 2 3
2 3 4 5
20 5 4
1 2 3 4 12
12 13 18 20
6 2 3
1 3
3 4 6```

### 输出

```
1
3
1
0
317580808
10```

# AI分析结果



---

## **唯一算法分类**
**组合数学**

---

## **综合分析与结论**
### **核心思路**
1. **最大值定位**：排列的最大值 `n` 必须位于前缀最大值的最后一个位置 `p[m1]` 和后缀最大值的第一个位置 `s[1]`，否则无解。
2. **分治思想**：将排列分为左半部分（`[1, p[m1]-1]`）和右半部分（`[s[1]+1, n]`），分别计算两部分内的合法排列数。
3. **组合与排列计算**：
   - **分配剩余数**：从 `n-1` 个数中选择 `p[m1]-1` 个分配给左半部分，剩余给右半部分（组合数 `C(n-1, p[m1]-1)`）。
   - **区间内部排列**：每个前缀/后缀最大值区间内，最大值必须位于指定位置，其余数自由排列（排列数 `A`）。

### **难点与解决**
- **验证无解条件**：需检查 `p[1]=1`、`s[m2]=n` 和 `p[m1]=s[1]`。
- **动态分治计算**：递归处理每个区间的最大值位置，通过组合数和排列数计算每个区间的贡献。

### **可视化设计**
1. **分步动画演示**：
   - **步骤1**：高亮 `p[m1]` 位置（红色方块），显示最大值 `n` 的放置。
   - **步骤2**：左右两侧划分，左侧显示蓝色区间，右侧显示绿色区间。
   - **步骤3**：逐步处理左半部分的前缀最大值（如 `p[i]` 到 `p[i+1]`），计算组合数和排列数，动态显示当前选择的数和排列方式。
   - **音效与颜色**：关键步骤触发音效，如组合数选择时播放“点击”声，排列完成时播放“完成”音效。
2. **复古像素风格**：
   - 使用 8-bit 像素风格网格，每个位置用不同颜色表示（前缀最大值：黄色，后缀最大值：紫色，普通数：灰色）。
   - 动态绘制组合数选择过程（如网格中闪烁可选区域）。

---

## **题解清单（≥4星）**
1. **Yharimium（5星）**  
   **亮点**：  
   - 分治思路清晰，代码结构模块化。  
   - 预处理阶乘和逆元优化组合数计算。  
   - 关键条件判断简洁（如 `p[m1] != s[1]` 直接判无解）。

2. **FBW2010（4星）**  
   **亮点**：  
   - 对称处理左右区间，逻辑对称性强。  
   - 代码中复用组合数和排列数计算函数，减少冗余。

3. **MaxBlazeResFire（4星）**  
   **亮点**：  
   - 通过外向树拓扑序计算排列数，思路新颖。  
   - 时间复杂度优化至线性，适合大数据量。

---

## **最优思路提炼**
### **关键步骤**
1. **预处理组合数工具**：  
   预处理阶乘和逆元，支持快速计算组合数 `C(n, k)` 和排列数 `A(n, k)`。
   ```cpp
   llong binomial(llong n, llong m) {
       return fac[n] * inv[m] % Mod * inv[n - m] % Mod;
   }
   ```
2. **分治计算左右区间贡献**：  
   - 左半部分从后向前遍历前缀最大值，计算每个区间的组合数和排列数。
   - 右半部分从前向后遍历后缀最大值，对称处理。
   ```cpp
   for (int i = m1 - 1; i >= 1; i--) {
       res = res * binomial(p[i+1]-2, p[i]-1) % Mod;
       res = res * fac[p[i+1]-p[i]-1] % Mod;
   }
   ```
3. **合并结果**：  
   总方案数为左半部分、右半部分和分配系数的乘积。
   ```cpp
   res = binomial(n-1, p[m1]-1) * left_ans * right_ans % Mod;
   ```

---

## **同类型题推荐**
1. **P1521 排列计数**：求满足特定逆序对数的排列数，同样涉及组合数学。
2. **P2513 逆序对数列**：动态规划与组合数结合。
3. **P3223 排队**：分治思想处理排列组合问题。

---

## **可视化与算法演示**
### **动画实现思路**
1. **HTML/CSS 结构**：
   ```html
   <canvas id="grid"></canvas>
   <div id="controls">
       <button onclick="step()">Next Step</button>
       <input type="range" id="speed" min="1" max="5">
   </div>
   <audio id="click-sound" src="click.wav"></audio>
   ```
2. **Canvas 绘制**：
   - 绘制 `n × 1` 的网格表示排列。
   - 高亮当前处理区间（如左半部分蓝色，右半部分绿色）。
3. **关键逻辑（JavaScript）**：
   ```javascript
   function drawStep(step) {
       ctx.clearRect(0, 0, width, height);
       // 绘制当前最大值位置
       ctx.fillStyle = 'red';
       ctx.fillRect(p[m1]-1 * cellSize, 0, cellSize, cellSize);
       // 绘制左右区间
       ctx.fillStyle = 'blue';
       ctx.fillRect(0, 0, (p[m1]-1)*cellSize, cellSize);
       ctx.fillStyle = 'green';
       ctx.fillRect(p[m1]*cellSize, 0, (n-p[m1])*cellSize, cellSize);
   }
   ```
4. **音效触发**：
   ```javascript
   function playSound() {
       document.getElementById('click-sound').play();
   }
   ```

---

## **代码实现（Yharimium 题解核心）**
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long llong;
const llong Mod = 1e9 + 7;
const llong N = 1e6 + 1;

llong fac[N], inv[N];

llong binomial(llong n, llong m) {
    if (n < m) return 0;
    return fac[n] * inv[m] % Mod * inv[n - m] % Mod;
}

void pretask() {
    fac[0] = fac[1] = 1;
    for (int i = 2; i < N; i++) fac[i] = fac[i-1] * i % Mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = (Mod - Mod/i) * inv[Mod%i] % Mod;
    for (int i = 2; i < N; i++) inv[i] = inv[i-1] * inv[i] % Mod;
}

int n, m1, m2;
int p[N], s[N];

void solution() {
    scanf("%d%d%d", &n, &m1, &m2);
    for (int i = 1; i <= m1; i++) scanf("%d", &p[i]);
    for (int i = 1; i <= m2; i++) scanf("%d", &s[i]);
    
    if (p[1] != 1 || s[m2] != n || p[m1] != s[1]) {
        printf("0\n");
        return;
    }
    
    llong res = binomial(n-1, p[m1]-1);
    for (int i = m1-1; i >= 1; i--) {
        res = res * binomial(p[i+1]-2, p[i]-1) % Mod;
        res = res * fac[p[i+1]-p[i]-1] % Mod;
    }
    for (int i = 2; i <= m2; i++) {
        res = res * binomial(n-s[i-1]-1, n-s[i]) % Mod;
        res = res * fac[s[i]-s[i-1]-1] % Mod;
    }
    printf("%lld\n", res);
}

int main() {
    pretask();
    int t; scanf("%d", &t);
    while (t--) solution();
    return 0;
}
```

---

## **个人心得摘录**
> **Yharimium**：  
> “分治的关键在于将大问题拆解为独立的小问题，每个区间的贡献可以独立计算，最终通过乘法原理合并。”

> **FBW2010**：  
> “调试时发现未处理 `p[m1] != s[1]` 导致 WA，务必注意边界条件。”

---

**END**

---
处理用时：85.03秒