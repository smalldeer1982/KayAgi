# 题目信息

# Array

## 题目描述

Chris the Rabbit has been interested in arrays ever since he was a child. At the moment he is researching arrays with the length of $ n $ , containing only integers from $ 1 $ to $ n $ . He is not good at math, that's why some simple things drive him crazy. For example, yesterday he grew keen on counting how many different beautiful arrays there are. Chris thinks that an array is beautiful if it meets one of the two conditions:

- each elements, starting from the second one, is no more than the preceding one
- each element, starting from the second one, is no less than the preceding one

Having got absolutely mad at himself and at math, Chris came to Stewie and Brian to ask them for help. However, they only laughed at him and said that the answer is too simple and not interesting. Help Chris the Rabbit to find the answer at last.

## 样例 #1

### 输入

```
2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
```

### 输出

```
17
```

# AI分析结果



# 【答案】

## 算法分类
**组合数学**

---

## 题解思路与核心分析

### 关键公式推导
1. **问题转化**：将数组转化为元素出现次数的集合，转化为**隔板模型**。  
   - 每个数出现次数之和为 `n`，相当于将 `n` 个元素分割为 `n` 个区间，对应组合数 `C(2n-1, n)`。  
   - 单调不降和单调不增对称，总方案为 `2 * C(2n-1, n)`，减去重复的 `n` 种全相同情况，得最终公式 `2C(2n-1, n) - n`。

2. **动态规划与杨辉三角关系**：  
   - 设 `dp[i][j]` 表示长度为 `i` 且末尾为 `j` 的单调不降序列数量，递推发现 `dp` 数组与组合数 `C(2n-1, n)` 等价。

### 解决难点对比
- **组合模型转化**：难点在于如何将数组结构映射到隔板问题（需理解元素出现次数与隔板位置的对应关系）。
- **动态规划优化**：需发现状态转移方程与杨辉三角的关联，推导至组合数公式。

---

## 题解评分（≥4星）

### Prurite（★★★★☆）
- **亮点**：通过隔板模型直观转化问题，代码简洁高效。
- **代码**：预处理阶乘和逆元，公式直接计算。

### pufanyi（★★★★☆）
- **亮点**：动态规划打表发现杨辉三角规律，推导严谨。
- **代码**：利用费马小定理求逆元，时间复杂度 `O(n)`。

### nueryim（★★★★☆）
- **亮点**：详细分析差分数组与插板法等价性，公式推导清晰。
- **代码**：直接计算组合数并处理重复情况。

---

## 最优思路提炼
**组合数隔板模型**：  
1. 将数组元素出现次数映射为 `n` 个元素与 `n-1` 个隔板的排列，总排列数为 `C(2n-1, n)`。  
2. 利用对称性合并单调不降/不增情况，减去重复的全相同序列。

---

## 同类型题套路
- **组合数问题**：将序列约束转化为元素分配问题（如隔板法、插空法）。  
- **逆元优化**：大数组合数取模时，预处理阶乘与逆元加速计算。

---

## 推荐题目
1. **P3811**：线性求逆元（组合数计算基础）。  
2. **P1044**：卡特兰数（隔板模型扩展）。  
3. **P2822**：组合数性质与递推优化。

---

## 可视化设计（像素风格演示）
### 动画流程
1. **隔板模型构建**：  
   - **像素块**：蓝色方块代表元素，红色竖线为隔板。  
   - **步进演示**：动态插入隔板，统计元素区间数量（如 `n=3` → `[1,1,1 | | 3]`）。  
   - **音效**：插入隔板时播放“滴”声，完成时播放上升音阶。

2. **组合数计算**：  
   - **像素字体**：显示 `C(2n-1, n)` 计算过程，逐步高亮阶乘项。  
   - **逆元步骤**：红色闪烁标记快速幂求逆元步骤。

### 代码片段（JavaScript）
```javascript
// 计算组合数 C(a, b) mod 1e9+7
function comb(a, b) {
    let numerator = 1, denominator = 1;
    for (let i = 0; i < b; i++) {
        numerator = (numerator * (a - i)) % mod;
        denominator = (denominator * (i + 1)) % mod;
    }
    return numerator * powMod(denominator, mod - 2) % mod;
}
```

---

## 代码实现（核心逻辑）
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
typedef long long ll;

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    int n; cin >> n;
    ll ans = 1;
    // 计算 C(2n-1, n)
    for (int i = 1; i <= n; i++) 
        ans = ans * (2*n - i) % mod * qpow(i, mod-2) % mod;
    cout << (2 * ans - n + mod) % mod;
    return 0;
}
```

---
处理用时：63.34秒