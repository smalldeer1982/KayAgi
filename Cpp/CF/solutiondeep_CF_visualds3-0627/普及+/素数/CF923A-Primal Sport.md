# 题目信息

# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14
```

### 输出

```
6
```

## 样例 #2

### 输入

```
20
```

### 输出

```
15
```

## 样例 #3

### 输入

```
8192
```

### 输出

```
8191
```

# AI分析结果



---

**算法分类**  
数学（质数筛法）

---

**题解思路、算法要点与解决难点**  

**核心思路**  
题目要求逆推可能的起始数 \(X_0\)，已知 \(X_2\)。关键点在于：
1. **预处理每个数的最大质因数**：通过线性筛法记录每个数的最大质因数，避免重复计算。
2. **确定 \(X_1\) 的范围**：\(X_2\) 的最大质因数 \(p_2\) 决定了 \(X_1\) 的可能范围 \([X_2 - p_2 + 1, X_2]\)。
3. **计算最小 \(X_0\)**：对于每个可能的 \(X_1\)（必须为合数），其对应的最小 \(X_0\) 为 \(X_1 - p_1 + 1\)（\(p_1\) 是 \(X_1\) 的最大质因数），取所有合法 \(X_0\) 的最小值。

**解决难点**  
- **最大质因数的预处理**：通过线性筛法在 \(O(n)\) 时间内高效记录每个数的最大质因数。
- **避免非法 \(X_0\)**：仅考虑合数的 \(X_1\)，因为质数的 \(X_0\) 会小于 3，不符合题意。

---

**题解评分 (≥4星)**  

1. **ModestCoder_**（★★★★☆）  
   - **亮点**：使用线性筛法预处理最大质因数，代码简洁高效，正确处理合数筛选。
   - **代码**：通过 `flag` 数组标记合数，避免无效计算。

2. **Patrickpwq**（★★★★☆）  
   - **亮点**：在线筛中直接记录最大质因数，逻辑清晰，预处理与枚举分离。
   - **优化**：仅枚举合法的 \(X_1\) 区间，减少计算量。

3. **cbyybccbyybc**（★★★★☆）  
   - **亮点**：预处理最大质因数的同时标记合数，确保仅处理有效 \(X_1\)。

---

**最优思路或技巧提炼**  

1. **线性筛法预处理**  
   - 在线性筛法中记录每个数的最大质因数。对于质数 \(i\)，最大质因数为自身；对于合数 \(i \times p\)，其最大质因数为 \(i\) 的最大质因数。
   - 代码片段：  
     ```cpp
     for (int i = 2; i <= n; ++i) {
         if (!flag[i]) prime[++tot] = a[i] = i;
         for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
             flag[i * prime[j]] = 1;
             a[i * prime[j]] = a[i];  // 最大质因数为 i 的最大质因数
             if (i % prime[j] == 0) break;
         }
     }
     ```

2. **逆推合法范围**  
   - \(X_1\) 的范围由 \(X_2\) 的最大质因数确定：\([X_2 - p_2 + 1, X_2]\)。
   - 仅处理合数的 \(X_1\)，确保 \(X_0 \geq 3\)。

---

**同类型题或类似算法套路**  
- **质因数分解与筛法应用**：常见于需要快速处理质数或质因数的题目，如区间质数统计、最大公约数问题。
- **逆推与范围约束**：类似动态规划中的状态转移，通过已知结果逆推初始状态。

---

**推荐相似题目**  
1. **P3383 【模板】线性筛素数**  
   - 练习线性筛法的基本应用。
2. **P1075 质因数分解**  
   - 直接求最大质因数的简化版。
3. **P1217 回文质数**  
   - 结合质数与回文数的筛法优化。

---

**可视化与算法演示**  

**核心算法流程**  
1. **筛法预处理**：动态展示每个数被标记的过程，高亮当前质数及其倍数，显示最大质因数的更新。
2. **范围枚举**：在 \(X_2\) 的区间内，用颜色区分合数与质数，仅合数可被选中。
3. **计算 \(X_0\)**：对于每个 \(X_1\)，显示其最大质因数 \(p_1\) 和对应的 \(X_0 = X_1 - p_1 + 1\)。

**复古游戏化动画**  
- **像素风格**：用 8 位色块表示数字，质数显示为红色，合数为绿色。
- **音效**：质数标记时播放“滴”声，选中合法 \(X_1\) 时播放“确认”音效。
- **自动演示**：逐步展示筛法、区间枚举、最小值更新，速度可调。

---

**代码片段**  
ModestCoder_ 的预处理与枚举逻辑：  
```cpp
#include <bits/stdc++.h>
#define maxn 1000010
using namespace std;
int n, flag[maxn], tot, a[maxn], prime[maxn];

int main(){
    scanf("%d", &n);
    flag[1] = 1;
    for (int i = 2; i <= n; ++i){
        if (!flag[i]) prime[++tot] = a[i] = i;
        for (int j = 1; j <= tot && i * prime[j] <= n; ++j){
            flag[i * prime[j]] = 1, a[i * prime[j]] = a[i];
            if (i % prime[j] == 0) break;
        }
    }
    int ans = n;
    for (int i = n - a[n] + 1; i <= n; ++i)
        if (flag[i]) ans = min(ans, i - a[i] + 1);
    printf("%d\n", ans);
    return 0;
}
```

---

**总结**  
本题通过筛法预处理和逆推范围，高效求解最小起始数。关键在于最大质因数的预处理和合法范围的筛选。线性筛法的优化和合数判断是核心技巧，适用于类似质因数分解问题。

---
处理用时：302.37秒