# 题目信息

# Lucky Chains

## 题目描述

Let's name a pair of positive integers $ (x, y) $ lucky if the greatest common divisor of them is equal to $ 1 $ ( $ \gcd(x, y) = 1 $ ).

Let's define a chain induced by $ (x, y) $ as a sequence of pairs $ (x, y) $ , $ (x + 1, y + 1) $ , $ (x + 2, y + 2) $ , $ \dots $ , $ (x + k, y + k) $ for some integer $ k \ge 0 $ . The length of the chain is the number of pairs it consists of, or $ (k + 1) $ .

Let's name such chain lucky if all pairs in the chain are lucky.

You are given $ n $ pairs $ (x_i, y_i) $ . Calculate for each pair the length of the longest lucky chain induced by this pair. Note that if $ (x_i, y_i) $ is not lucky itself, the chain will have the length $ 0 $ .

## 说明/提示

In the first test case, $ \gcd(5, 15) = 5 > 1 $ , so it's already not lucky, so the length of the lucky chain is $ 0 $ .

In the second test case, $ \gcd(13 + 1, 37 + 1) = \gcd(14, 38) = 2 $ . So, the lucky chain consists of the single pair $ (13, 37) $ .

## 样例 #1

### 输入

```
4
5 15
13 37
8 9
10009 20000```

### 输出

```
0
1
-1
79```

# AI分析结果



## **唯一算法分类**  
数论（质因数分解与GCD性质应用）

---

## **综合分析与结论**  
### **核心思路**  
题目要求找到最长的连续互质链。利用 **GCD 的差分性质** $\gcd(x+k, y+k) = \gcd(x+k, y-x)$，将问题转化为：找到最小的 $k$ 使得 $\gcd(x+k, d) \neq 1$（其中 $d = y-x$）。通过枚举 $d$ 的质因数 $p$，计算 $k = p - (x \bmod p)$，取所有 $k$ 的最小值即为答案。

### **难点与解决**  
1. **质因数分解的高效性**：直接枚举 $d$ 的所有因数会超时。通过预处理每个数的最小质因数，可在 $O(\log d)$ 时间内分解质因数。  
2. **边界条件处理**：需特判初始不互质（输出 0）和 $d=1$（输出 -1）的情况。  
3. **时间复杂度优化**：预处理最小质因数的线性筛法，使得分解质因数的复杂度为 $O(\log d)$，总时间复杂度为 $O(n \log d)$。

### **可视化设计思路**  
- **动画方案**：展示如何分解 $d$ 的质因数，并用颜色高亮当前操作的质因数。例如，将 $d$ 分解为 $p_1 \times p_2 \times \dots$，每个质因数 $p_i$ 对应一个 $k_i$，取最小值。  
- **像素风格**：用 8 位像素风格表示质因数分解过程，每个质因数显示为不同颜色的方块，计算 $k_i$ 时触发音效。  
- **交互控制**：允许步进分解过程，调节速度观察质因数分解和 $k$ 值计算。

---

## **题解清单 (≥4星)**  
1. **Alex_Wei 题解（5星）**  
   - **亮点**：简洁的质因数分解逻辑，利用线性筛预处理最小质因数，代码高效且可读性强。  
   - **核心代码**：  
     ```cpp  
     while (d > 1) {
         int p = minp[d];
         ans = min(ans, p - x % p);
         d /= p;
     }
     ```

2. **Exp10re 题解（4.5星）**  
   - **亮点**：详细解释了质因数分解的优化思路，代码中加入了调试注释，适合理解思维过程。  
   - **核心代码**：  
     ```cpp  
     for (int i = 1; p[i] <= b / p[i]; ++i) {
         int t = p[i];
         if (b % t) continue;
         res = Min(res, t - a % t);
     }
     ```

3. **ABookCD 题解（4星）**  
   - **亮点**：使用埃氏筛预处理每个数的质因数，代码简短，适合快速实现。  
   - **核心代码**：  
     ```cpp  
     for (int i = 2; i < maxn; i += 2) a[i] = 2;
     for (int i = 3; i < maxn; i += 2) {
         if (a[i] != i) continue;
         for (int j = 3; i*j < maxn; j += 2) a[i*j] = i;
     }
     ```

---

## **最优思路或技巧提炼**  
1. **质因数分解的预处理**：通过线性筛预处理每个数的最小质因数，分解时只需不断除以最小质因数。  
2. **利用 GCD 差分性质**：将 $\gcd(x+k, y+k)$ 转化为 $\gcd(x+k, y-x)$，避免直接处理变量 $k$。  
3. **边界特判优化**：在代码开头处理 $d=1$ 和初始不互质的情况，减少后续计算。

---

## **同类型题与算法套路**  
- **通用数论问题**：涉及质因数分解、GCD 性质、筛法预处理。  
- **类似题目**：  
  - **洛谷 P1029**：最大公约数与最小公倍数问题。  
  - **洛谷 P1072**：Hankson 的趣味题（利用质因数分解求条件解）。  
  - **Codeforces 1514B**：AND 0, Sum Big（质因数分解与组合数学）。

---

## **推荐洛谷题目**  
1. **P1029**：最大公约数和最小公倍数问题。  
2. **P1072**：Hankson 的趣味题。  
3. **P1414**：又是毕业季II（质因数分解应用）。

---

## **个人心得摘录**  
- **Erinyes 题解**提到因 `#define int long long` 导致 TLE，强调变量类型选择的重要性。  
- **Kreado 题解**指出“合因子的答案一定不优于质因子”，避免无效枚举。

---

## **代码实现（核心逻辑）**  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 5;

int minp[MAXN]; // 存储每个数的最小质因数

void init() {
    for (int i = 2; i < MAXN; i++) {
        if (!minp[i]) {
            for (int j = i; j < MAXN; j += i) {
                if (!minp[j]) minp[j] = i;
            }
        }
    }
}

int solve(int x, int y) {
    if (__gcd(x, y) != 1) return 0;
    int d = y - x;
    if (d == 1) return -1;
    int ans = INT_MAX;
    while (d > 1) {
        int p = minp[d];
        ans = min(ans, p - x % p);
        d /= p;
    }
    return ans;
}

int main() {
    init();
    int T; scanf("%d", &T);
    while (T--) {
        int x, y; scanf("%d%d", &x, &y);
        printf("%d\n", solve(x, y));
    }
    return 0;
}
```

---

## **可视化与算法演示**  
### **动画方案**  
1. **质因数分解过程**：  
   - 将 $d$ 显示为一个大方块，逐步分解为多个质因数方块（如 $d=12$ → $2 \times 2 \times 3$）。  
   - 每个质因数方块颜色不同，计算对应 $k$ 时闪烁。  
2. **音效设计**：  
   - 分解出质因数时播放“滴”声，找到最小 $k$ 时播放成功音效。  
3. **交互控制**：  
   - 支持暂停/继续，拖动进度条观察分解步骤。  

### **像素风格实现**  
- **Canvas 绘制**：用 16x16 像素块表示数字，质因数分解时动态拆分方块。  
- **颜色编码**：质数用亮色（如红色），合数用暗色（如灰色）。  

---

**END**

---
处理用时：91.63秒