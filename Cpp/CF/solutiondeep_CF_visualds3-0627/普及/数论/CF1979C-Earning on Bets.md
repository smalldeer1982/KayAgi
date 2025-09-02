# 题目信息

# Earning on Bets

## 题目描述

You have been offered to play a game. In this game, there are $ n $ possible outcomes, and for each of them, you must bet a certain integer amount of coins. In the event that the $ i $ -th outcome turns out to be winning, you will receive back the amount of coins equal to your bet on that outcome, multiplied by $ k_i $ . Note that exactly one of the $ n $ outcomes will be winning.

Your task is to determine how to distribute the coins in such a way that you will come out ahead in the event of any winning outcome. More formally, the total amount of coins you bet on all outcomes must be strictly less than the number of coins received back for each possible winning outcome.

## 说明/提示

In the first test case, the coins can be distributed as follows: $ 27 $ coins on the first outcome, $ 41 $ coins on the second outcome, $ 12 $ coins on the third outcome. Then the total amount of coins bet on all outcomes is $ 27 + 41 + 12 = 80 $ coins. If the first outcome turns out to be winning, you will receive back $ 3 \cdot 27 = 81 $ coins, if the second outcome turns out to be winning, you will receive back $ 2 \cdot 41 = 82 $ coins, if the third outcome turns out to be winning, you will receive back $ 7 \cdot 12 = 84 $ coins. All these values are strictly greater than $ 80 $ .

In the second test case, one way is to bet one coin on each of the outcomes.

## 样例 #1

### 输入

```
6
3
3 2 7
2
3 3
5
5 5 5 5 5
6
7 9 3 17 9 13
3
6 3 2
5
9 4 6 8 3```

### 输出

```
27 41 12 
1 1 
-1
1989 1547 4641 819 1547 1071 
-1
8 18 12 9 24```

# AI分析结果



# Earning on Bets 题解分析

## 算法分类
**数学构造/数论**

---

## 题解思路与核心难点

### 问题核心
要求构造整数数组 $x_i$，使得 $\forall i, k_i \cdot x_i > \sum x_j$，且 $\sum x_j$ 最小。

### 核心思路
1. **数学条件推导**：  
   由 $k_i x_i > S$（$S$ 为总和），得 $S < \frac{x_i k_i}{1}$。  
   所有不等式相加得 $S < \sum \frac{x_i k_i}{k_i-1}$，但更简洁的条件是：$\sum \frac{1}{k_i} < 1$。  
   当 $\sum \frac{1}{k_i} \geq 1$ 时无解，否则构造 $x_i = \frac{\text{LCM}(k_1, \dots, k_n)}{k_i}$。

2. **最小公倍数构造法**：  
   - 计算所有 $k_i$ 的最小公倍数 $L$。  
   - 令 $x_i = L / k_i$，总和 $S = \sum x_i = L \cdot \sum \frac{1}{k_i} < L$。  
   - 每个 $k_i x_i = L > S$，满足条件。

### 解决难点
- **整数构造**：需确保 $x_i$ 为整数且总和严格小于每个 $k_i x_i$。
- **数学验证**：通过 $\sum \frac{1}{k_i} < 1$ 的判定，避免了复杂遍历。

---

## 题解评分 (≥4星)

### 1. Just_A_Sentence（★★★★☆）
- **亮点**：直接利用 LCM 构造，代码简洁高效。
- **代码**：计算 LCM 并验证总和，时间复杂度 $O(n \log k_i)$。

### 2. DDF_（★★★★☆）
- **亮点**：明确数学推导，代码清晰。
- **代码**：与核心思路完全一致，验证逻辑严谨。

### 3. freoepn（★★★★☆）
- **亮点**：简洁的数学解释，正确性明确。
- **代码**：直接构造并验证，无冗余步骤。

---

## 最优思路与技巧

### 关键思路
1. **条件转换**：将原问题转化为 $\sum \frac{1}{k_i} < 1$。
2. **LCM 构造**：利用 LCM 保证 $x_i$ 为整数，且总和自动满足约束。

### 实现技巧
- **避免浮点运算**：通过整数运算处理，避免精度问题。
- **快速求 LCM**：使用递归求 GCD，迭代计算 LCM。

---

## 同类型题推荐
1. **CF1979C**：本题的原题，直接应用上述思路。
2. **洛谷 P1082**：求解同余方程，涉及数论构造。
3. **CF1325B**：数组元素唯一性构造，需数学分析。

---

## 可视化设计

### 核心流程演示
1. **输入与预处理**：展示输入数组 $k_i$，高亮当前处理的元素。
2. **LCM 计算**：逐步显示每对数的 GCD 和 LCM，颜色标记变化。
3. **验证条件**：动态计算 $\sum \frac{1}{k_i}$，若 ≥1 则显示红色警示。

### 复古像素风格
- **颜色方案**：8-bit 风格，绿色表示有效步骤，红色表示失败。
- **音效**：成功时播放 8-bit 胜利音效，失败时短促蜂鸣。

### 交互演示
- **步进控制**：允许单步执行 LCM 计算和验证。
- **自动模式**：AI 自动运行，模拟不同测试用例的解题过程。

---

## 代码实现（核心片段）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<ll> k(n);
        for (auto &x : k) cin >> x;
        
        ll lcm = 1;
        double sum_reciprocal = 0;
        for (auto x : k) {
            lcm = lcm * x / gcd(lcm, x);
            sum_reciprocal += 1.0 / x;
            if (sum_reciprocal >= 1) break;
        }
        
        if (sum_reciprocal >= 1) {
            cout << "-1\n";
            continue;
        }
        
        ll total = 0;
        vector<ll> ans;
        for (auto x : k) {
            ll val = lcm / x;
            ans.push_back(val);
            total += val;
        }
        
        if (total >= lcm) cout << "-1\n";
        else {
            for (auto x : ans) cout << x << ' ';
            cout << '\n';
        }
    }
    return 0;
}
```

---

## 个人心得
- **精度陷阱**：计算 $\sum \frac{1}{k_i}$ 时需用浮点数，但判定应避免浮点误差（如使用 `sum_reciprocal >= 1 - 1e-9`）。
- **大数处理**：LCM 可能极大，需使用 `long long` 并预判溢出。

---
处理用时：188.95秒