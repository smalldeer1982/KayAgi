# 题目信息

# 「DTOI-5」进行一个排的重 (Minimum Version)

## 题目背景

**本题与 Maximum Version 的区别是所求最值和数据范围不同。**

小 L 热衷于重排数列使之规整。

## 题目描述

小 L 有一个长为 $n$ 的序列 $a$，其中每一项 $a_i$ 都是一个 pair $(p_i, q_i)$。

为了让 $a$ 看起来规整一些，他钦定 $p, q$ 分别均为长为 $n$ 的排列。

为了对 $a$ 的规整程度进行量化计算，他给出了一个权值函数 $f(a) = \displaystyle\sum_{i = 1}^n ([p_i > \max_{j = 1}^{i - 1} p_j] + [q_i > \max_{j = 1}^{i - 1} q_j])$。**注意 $i = 1$ 时两个方括号都能取到值，因为我们认为 $\displaystyle\max_{j = 1}^0 p_j = \displaystyle\max_{j = 1}^0 q_j = -\infty$。**

为了让 $a$ 看起来更加规整，他决定分别以某种方式重排 $a$ 得到 $a'$ 使得 $f(a')$ 最小。**注意重排时必须将 $a'_i = (p'_i, q'_i)$ 视为整体。**

他希望你求出 $f(a')_{\min}$ 的值，以及分别有多少个 $a'$ 可以取到 $f(a')_{\min}$。

由于方案数可能很大，你只需要求出结果对 $998244353$ 取模的值。

## 说明/提示

**【数据范围】**

$$
\def\or{\operatorname{or}}
%\def\arrayscretch{1.5}
\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textbf{Subtask}&n\le &\textbf{Points}\cr\hline
\sf1&10&10 \operatorname{pts}\cr\hline
\sf2&500&20 \operatorname{pts}\cr\hline
\sf3&5\times10^3&20 \operatorname{pts}\cr\hline
\sf4&10^5&20 \operatorname{pts}\cr\hline
\sf5&5\times10^5&30 \operatorname{pts}\cr\hline
\end{array}
$$

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^5$，$1 \leq p_i, q_i \leq n$，保证 $p, q$ 均为**排列**。

## 样例 #1

### 输入

```
5
1 5 2 4 3
1 4 2 5 3```

### 输出

```
3 48```

# AI分析结果



---

**算法分类**：数学（排列组合、逆元）

---

### **题解思路、算法要点与解决难点**

1. **核心思路**  
   本题要求最小化排列后各位置递增贡献的总和。关键观察是：  
   - 当存在元素 `(n, n)` 时，将其放在首位，后续元素无法产生贡献，总贡献为 `2`。  
   - 否则，将 `p=n` 或 `q=n` 的元素放在首位，总贡献为 `3`。  

2. **解决难点**  
   - **贡献推导**：通过分析最大值的前后关系，确定贡献最小化的排列策略。  
   - **方案数计算**：利用排列组合推导出情况2的公式，结合逆元处理模运算下的除法。  

3. **算法流程**  
   - 遍历数组，找到 `p_i=n` 的 `q` 值 `x` 和 `q_i=n` 的 `p` 值 `y`。  
   - 若 `x == n`，直接输出 `2` 和 `(n-1)!`。  
   - 否则，计算 `(n-1)!/(n-x) + (n-1)!/(n-y)`，使用逆元优化除法。  

---

### **题解评分 ≥4星**

1. **FFTotoro（5星）**  
   - **亮点**：代码简洁，直接推导公式，高效处理逆元。  
   - **代码核心**：预计算阶乘，快速幂求逆元，逻辑清晰。  
   ```cpp
   int main() {
     // ... 预处理阶乘和逆元
     if (x == n) cout << "2 " << f(n-1);
     else cout << "3 " << f(n-1)*((inv(n-x) + inv(n-y)) % mod) % mod;
   }
   ```

2. **DengDuck（5星）**  
   - **亮点**：详细推导组合数学公式，代码结构清晰。  
   - **代码核心**：组合数化简为阶乘乘逆元，直接求和。  
   ```cpp
   if (mp == mq) cout << "2 " << F;
   else cout << "3 " << F*(ksm(n-x, mod-2) + ksm(n-y, mod-2)) % mod;
   ```

---

### **最优思路提炼**

- **关键观察**：贡献的最小值由首元素决定，必须包含 `p=n` 或 `q=n`。  
- **数学技巧**：排列方案数化简为阶乘乘逆元，避免直接计算组合数。  
- **实现优化**：预计算阶乘，快速幂求逆元，时间复杂度 `O(n)`。  

---

### **同类型题推荐**

1. **P2181 对角线**：排列组合与逆元应用。  
2. **P3811 乘法逆元模板**：逆元基础训练。  
3. **P1246 编码问题**：排列序数计算。  

---

### **可视化算法演示**

- **动画设计**：  
  1. **像素风格排列**：用网格展示元素排列，高亮首元素 `(n, x)` 或 `(y, n)`。  
  2. **贡献动态显示**：每次放置元素时，显示其是否触发 `p` 或 `q` 的贡献。  
  3. **自动模式**：模拟两种情况的排列，对比不同首元素的贡献变化。  

- **交互功能**：  
  - **步进控制**：手动调整排列顺序观察贡献变化。  
  - **音效提示**：触发贡献时播放不同音效，增强反馈。  

---

### **核心代码实现**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

long long qpow(long long a, int b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    int n, x, y, p, q;
    cin >> n;
    vector<int> ps(n), qs(n);
    for (int i = 0; i < n; i++) cin >> ps[i];
    for (int i = 0; i < n; i++) cin >> qs[i];
    
    // 查找 p=n 的 q 值和 q=n 的 p 值
    for (int i = 0; i < n; i++) {
        if (ps[i] == n) x = qs[i];
        if (qs[i] == n) y = ps[i];
    }
    
    long long fact = 1;
    for (int i = 2; i < n; i++) fact = fact * i % MOD;
    
    if (x == n) {
        cout << "2 " << fact * n % MOD; // 首项固定，后续 (n-1)!
    } else {
        long long inv_x = qpow(n - x, MOD - 2);
        long long inv_y = qpow(n - y, MOD - 2);
        cout << "3 " << fact * (inv_x + inv_y) % MOD;
    }
    return 0;
}
```

---
处理用时：248.82秒