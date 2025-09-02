# 题目信息

# [ABC178C] Ubiquity

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc178/tasks/abc178_c

長さ $ N $ の整数の列 $ A_1,A_2,\ldots,A_N $ であって以下の条件をすべて満たすものはいくつありますか。

- $ 0\ \leq\ A_i\ \leq\ 9 $
- $ A_i=0 $ なる $ i $ が存在する。
- $ A_i=9 $ なる $ i $ が存在する。

ただし、答えはとても大きくなる可能性があるので、$ 10^9+7 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^6 $
- $ N $ は整数

### Sample Explanation 1

数列$ \{0,9\} $,$ \{9,0\} $の $ 2 $ つが条件をすべて満たします。

## 样例 #1

### 输入

```
2```

### 输出

```
2```

## 样例 #2

### 输入

```
1```

### 输出

```
0```

## 样例 #3

### 输入

```
869121```

### 输出

```
2511445```

# AI分析结果



**唯一算法分类**  
数学（容斥原理）

---

**综合分析与结论**  
题目要求计算包含至少一个0和9的序列总数。通过容斥原理，总数为所有可能序列减去不含0或9的序列，再加上同时不含0和9的序列。公式为：  
`ans = (10^n - 2*9^n + 8^n) % MOD`  
核心难点在于正确应用容斥并处理大数幂运算。使用快速幂计算各幂次取模，并注意减法后取模可能为负数的情况。

**可视化设计要点**：  
- **步骤分解**：动画展示三个项的贡献（10^n、-2*9^n、+8^n），用不同颜色区分。  
- **快速幂过程**：分治二进制分解指数，动态显示幂次计算步骤。  
- **复古像素风格**：用8位像素方块表示数值变化，音效提示每一步计算完成。

---

**题解清单 (≥4星)**  
1. **容斥快速幂法（5星）**  
   - 思路清晰，直接推导公式，快速幂高效处理大数。  
   - 代码简洁，可读性强，无冗余步骤。  
   - 关键代码：  
     ```cpp
     const int MOD = 1e9 + 7;
     ll mod_pow(ll a, ll b) {
         ll res = 1;
         while (b) {
             if (b & 1) res = res * a % MOD;
             a = a * a % MOD;
             b >>= 1;
         }
         return res;
     }
     int main() {
         int n; cin >> n;
         ll a = mod_pow(10, n);
         ll b = 2 * mod_pow(9, n) % MOD;
         ll c = mod_pow(8, n);
         ll ans = (a - b + MOD) % MOD;
         ans = (ans + c) % MOD;
         cout << ans;
     }
     ```

---

**最优思路提炼**  
1. **容斥思想**：通过“总情况-非法情况+重复扣除”简化计数。  
2. **快速幂优化**：O(logN)时间计算大数幂次模值。  
3. **负数取模处理**：`(a - b + MOD) % MOD`确保结果非负。

---

**同类型题推荐**  
1. **组合数取模**：洛谷P3197 [HNOI2008]越狱  
2. **容斥原理应用**：Atcoder ABC156D Bouquet  
3. **快速幂模运算**：LeetCode 50. Pow(x, n)

---

**个人心得摘录**  
- **调试教训**：初始忘记处理负数模，导致样例错误。修正后必须显式加MOD再取模。  
- **顿悟点**：容斥中的加回8^n是关键，避免重复扣除不含0和9的序列。

---

**可视化与算法演示**  
```javascript
// 快速幂动画示例（伪代码）
function animatePow(a, b) {
  let step = 0, res = 1;
  while (b > 0) {
    highlight(`Step ${step}: a=${a}, b=${b}`);
    if (b % 2 === 1) {
      res = (res * a) % MOD;
      playSound('power');
    }
    a = (a * a) % MOD;
    b = Math.floor(b / 2);
    step++;
  }
  return res;
}
// 复古像素风格：Canvas绘制三个项的变化
drawTerm('10^n', colorRed, valueA);
drawTerm('-2*9^n', colorBlue, -valueB);
drawTerm('+8^n', colorGreen, valueC);
updateTotal(ans); // 显示最终结果
```

---

**代码实现**  
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

ll mod_pow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b % 2 == 1) res = res * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    ll a = mod_pow(10, n);
    ll b = (2 * mod_pow(9, n)) % MOD;
    ll c = mod_pow(8, n);
    ll ans = (a - b + MOD) % MOD;
    ans = (ans + c) % MOD;
    cout << ans << endl;
    return 0;
}
```

---
处理用时：83.77秒