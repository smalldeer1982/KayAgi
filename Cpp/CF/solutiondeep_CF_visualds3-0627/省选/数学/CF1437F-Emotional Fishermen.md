# 题目信息

# Emotional Fishermen

## 题目描述

$ n $ fishermen have just returned from a fishing vacation. The $ i $ -th fisherman has caught a fish of weight $ a_i $ .

Fishermen are going to show off the fish they caught to each other. To do so, they firstly choose an order in which they show their fish (each fisherman shows his fish exactly once, so, formally, the order of showing fish is a permutation of integers from $ 1 $ to $ n $ ). Then they show the fish they caught according to the chosen order. When a fisherman shows his fish, he might either become happy, become sad, or stay content.

Suppose a fisherman shows a fish of weight $ x $ , and the maximum weight of a previously shown fish is $ y $ ( $ y = 0 $ if that fisherman is the first to show his fish). Then:

- if $ x \ge 2y $ , the fisherman becomes happy;
- if $ 2x \le y $ , the fisherman becomes sad;
- if none of these two conditions is met, the fisherman stays content.

Let's call an order in which the fishermen show their fish emotional if, after all fishermen show their fish according to this order, each fisherman becomes either happy or sad. Calculate the number of emotional orders modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
1 1 4 9```

### 输出

```
20```

## 样例 #2

### 输入

```
4
4 3 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
3
4 2 1```

### 输出

```
6```

## 样例 #4

### 输入

```
8
42 1337 13 37 420 666 616 97```

### 输出

```
19200```

# AI分析结果



# 题解分析：Emotional Fishermen

## 唯一算法分类
**组合数学**

---

## 综合分析与结论

### 核心思路
1. **排序预处理**：将数组排序后，每个元素的前驱（即最大的满足 `2*a[j] ≤ a[i]` 的 j）可通过双指针快速计算。
2. **动态规划定义**：`dp[i]` 表示以 `a[i]` 为当前最大值的合法排列数，转移时需保证所有已选元素满足条件。
3. **排列数计算**：剩余元素的排列方式通过阶乘和逆元预处理加速，避免重复计算。

### 关键公式
- **前驱定义**：`lim[i] = max{j | 2*a[j] ≤ a[i]}`
- **转移方程**：  
  `dp[i] = Σ (dp[j] * A(n - lim[j] - 2, lim[i] - lim[j] - 1))`  
  其中 `A(n, m)` 表示排列数 `n!/(n-m)!`。

### 可视化设计
1. **动画步骤**：
   - **排序阶段**：显示数组排序后每个元素的 `lim[i]`，用颜色标记前驱范围。
   - **DP转移**：动态绘制 `dp[i]` 的累加过程，高亮当前 `j` 和对应的排列数计算。
   - **排列填充**：用网格展示剩余位置的排列，逐步填充元素。
2. **像素风格**：
   - 使用 8-bit 颜色区分已选元素、当前元素和未处理部分。
   - 音效触发：完成前驱计算时播放“滴”声，转移成功时播放上扬音效。

---

## 题解清单 (4星及以上)

### 1. LightningUZ（4星）
- **亮点**：详细推导状态转移方程，利用阶乘逆元优化排列数计算，代码简洁高效。
- **代码片段**：
  ```cpp
  f[i] = (f[i] + fi[n - len[i]] * sum[mx] % mod) % mod;
  sum[i] = (sum[i-1] + fc[n-1 - len[i]] * f[i] % mod) % mod;
  ```

### 2. George1123（4星）
- **亮点**：清晰解释合法排列的结构，强调前缀最大值序列的构造，代码注释明确。
- **代码片段**：
  ```cpp
  f[i] = (f[i] + 1ll * f[j] * A(n - 2 - lim[j], lim[i] - lim[j] - 1)) % mod;
  ```

### 3. Alex_Wei（4星）
- **亮点**：代码简洁，预处理阶乘逆元，逻辑清晰，适合快速理解核心逻辑。
- **代码片段**：
  ```cpp
  f[i] = (f[i] + 1ll * f[j] * A(n - 2 - p[j], p[i] - p[j] - 1)) % mod;
  ```

---

## 核心实现代码

### 关键逻辑（LightningUZ）
```cpp
sort(a+1,a+n+1);
for(int i=1; i<=n; i++) {
    while(2*a[mx] <= a[i]) mx++;
    len[i] = mx; // len[i] = lim[i] + 1
    f[i] = fi[n - len[i]] * sum[mx] % mod;
    sum[i] = sum[i-1] + fc[n-1 - len[i]] * f[i] % mod;
}
```

---

## 同类型题与套路

### 常见套路
- **排序预处理**：将无序数据转化为有序，便于限制条件处理。
- **组合数学+DP**：通过动态规划累加组合数或排列数，常见于计数问题。

### 推荐题目
1. **P1754**（球迷购票问题）：组合数递推。
2. **P1655**（小朋友的球）：斯特林数与动态规划。
3. **P3223**（排队）：排列组合与容斥原理。

---

## 个人心得摘录
- **排序必要性**：不排序无法高效处理前驱关系，排序后问题结构更清晰。
- **转移优化**：将排列数拆分为阶乘和逆元的乘积，显著减少计算量。

---

## 可视化与复古动画

### 动画方案
1. **初始化**：Canvas绘制排序后的数组，灰色方块表示元素，红色标记 `lim[i]`。
2. **DP步骤**：
   - **高亮当前 `a[i]`**：黄色闪烁。
   - **显示转移来源 `j`**：绿色方块连线至 `i`，下方显示排列数公式。
3. **音效触发**：
   - **计算完成**：8-bit“完成”音效。
   - **错误处理**：低音“哔”声。

### 代码片段（伪代码）
```javascript
// 绘制排序数组
ctx.fillStyle = '#888';
sortedArray.forEach((val, idx) => {
    ctx.fillRect(idx * 10, 100, 8, val * 2);
});

// DP转移动画
function animateStep(i, j) {
    highlightElement(i, 'yellow');
    drawArrow(j, i, 'green');
    playSound('blip');
}
```

---
处理用时：67.83秒