# 题目信息

# Congruence Equation

## 题目描述

Given an integer $ x $ . Your task is to find out how many positive integers $ n $ ( $ 1<=n<=x $ ) satisfy

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF919E/02717f82c41ef4ed609db5d967f659c9784212e1.png) where $ a,b,p $ are all known constants.

## 说明/提示

In the first sample, we can see that $ n=2 $ and $ n=8 $ are possible answers.

## 样例 #1

### 输入

```
2 3 5 8
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 6 7 13
```

### 输出

```
1
```

## 样例 #3

### 输入

```
233 233 10007 1
```

### 输出

```
1
```

# AI分析结果



---

## 算法分类
**数论同余问题（费马小定理+中国剩余定理）**

---

## 题解思路与算法要点

### 核心思路
1. **费马小定理应用**：因 `p` 是质数，`a^(p-1) ≡ 1 (mod p)`，故指数部分 `a^n` 的循环节为 `p-1`。
2. **分解变量**：将 `n` 拆分为 `n = k*(p-1) + r`（`0 ≤ r < p-1`），代入方程后化简为 `(r - k) * a^r ≡ b (mod p)`。
3. **枚举求解**：枚举所有可能的 `r`，计算对应的 `k`，验证 `n` 是否在范围内，并统计循环节内的解数。

### 解决难点
- **循环节推导**：正确利用费马小定理将指数部分与系数 `n` 的周期性结合，得出循环节为 `p*(p-1)`。
- **同余方程转化**：将原方程转化为关于 `k` 的线性同余方程，通过枚举 `r` 解出 `k` 的可能值。
- **高效逆元计算**：使用快速幂预处理 `a^r` 的逆元，降低时间复杂度至 `O(p log p)`。

---

## 题解评分（≥4星）

### [Acc_Robin（⭐⭐⭐⭐⭐）]
- **亮点**：思路清晰，代码简洁，直接枚举 `r` 并快速幂求逆元，利用循环节公式高效统计答案。
- **代码片段**：
  ```cpp
  for (int r=0; r<p-1; r++) {
    f = b * qpow(qpow(a, r)) % p;
    k = (r - f + p) % p;
    now = k*(p-1) + r;
    ans += (x - now) / (p*(p-1)) + 1;  // 统计解数
  }
  ```

### [interestingLSY（⭐⭐⭐⭐）]
- **亮点**：明确拆分为两个同余方程并用中国剩余定理合并，解释详细。
- **关键步骤**：
  ```cpp
  // 解方程n ≡ i (mod p-1) 且 n ≡ b/(a^i) (mod p)
  ll correctn = (p-1)*Mod(n-now,p) + n;  // 合并解
  ```

### [mydcwfy（⭐⭐⭐⭐）]
- **亮点**：预处理逆元加速计算，代码高效，数学推导严谨。
- **核心代码**：
  ```cpp
  for (ll modp1=0; modp1<Mod-1; modp1++) {
    mx = (modp1 - now + (Mod-1)) % (Mod-1) * Mod + now;  // 最小解
    ans += (x - mx + lim) / lim;  // 统计循环节内解数
  }
  ```

---

## 最优思路提炼
1. **分解变量**：将 `n` 表示为 `k*(p-1) + r`，利用费马小定理化简方程。
2. **枚举余数**：对每个 `r` 计算 `k`，得到初始解 `n0 = k*(p-1) + r`。
3. **循环节统计**：所有解的形式为 `n0 + m*p*(p-1)`，统计 `[1, x]` 内的解数。

---

## 同类题型推荐
1. **P1082** [同余方程](https://www.luogu.com.cn/problem/P1082)：求解线性同余方程。
2. **P3868** [猜数字](https://www.luogu.com.cn/problem/P3868)：中国剩余定理基础应用。
3. **P2485** [计算器](https://www.luogu.com.cn/problem/P2485)：快速幂+同余综合题。

---

## 可视化算法演示
### 动画设计
1. **像素风格界面**：用16色网格展示 `r` 的枚举过程，每个 `r` 对应不同颜色。
2. **关键步骤高亮**：
   - **Step 1**：显示当前 `r`，计算 `a^r` 和逆元。
   - **Step 2**：解方程 `k ≡ r - b*a^{-r} (mod p)`，显示 `k` 值。
   - **Step 3**：绘制 `n = k*(p-1)+r`，若 `n ≤ x` 则标记为绿色。
3. **循环节展示**：用流动的箭头表示解 `n` 的周期性出现，颜色渐变表示不同循环周期。

### 交互功能
- **速度调节**：滑动条控制枚举速度（100ms~2s）。
- **音效**：成功找到解时播放8-bit音效，错误时短促提示。

---

## 核心代码实现（Acc_Robin版）
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a, b, p, x, ans;

int qpow(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = a*a%p)
        if (b & 1) res = res*a%p;
    return res;
}

signed main() {
    cin >> a >> b >> p >> x;
    for (int r = 0; r < p-1; ++r) {
        int inv_ar = qpow(qpow(a, r), p-2); // 计算a^r的逆元
        int f = b * inv_ar % p;
        int k = (r - f + p) % p;
        int n0 = k*(p-1) + r;
        if (n0 > x) continue;
        ans += (x - n0) / (p*(p-1)) + 1;
    }
    cout << ans;
}
```

---

## 个人心得摘录
- **Acc_Robin**：注意 `k` 的取模运算可能导致负数，需加上 `p` 再取模。
- **mydcwfy**：预处理逆元显著减少计算时间，避免重复调用快速幂。

---

**可视化与算法分析完结**

---
处理用时：103.90秒