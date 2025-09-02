# 题目信息

# Expected Median

## 题目描述

Arul has a binary array $ ^{\text{∗}} $ $ a $ of length $ n $ .

He will take all subsequences $ ^{\text{†}} $ of length $ k $ ( $ k $ is odd) of this array and find their median. $ ^{\text{‡}} $

What is the sum of all these values?

As this sum can be very large, output it modulo $ 10^9 + 7 $ . In other words, print the remainder of this sum when divided by $ 10^9 + 7 $ .

 $ ^{\text{∗}} $ A binary array is an array consisting only of zeros and ones.

 $ ^{\text{†}} $ An array $ b $ is a subsequence of an array $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements. Subsequences don't have to be contiguous.

 $ ^{\text{‡}} $ The median of an array of odd length $ k $ is the $ \frac{k+1}{2} $ -th element when sorted.

## 说明/提示

In the first test case, there are four subsequences of $ [1,0,0,1] $ with length $ k=3 $ :

- $ [1,0,0] $ : median $ = 0 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [0,0,1] $ : median $ = 0 $ .

 The sum of the results is $ 0+1+1+0=2 $ .In the second test case, all subsequences of length $ 1 $ have median $ 1 $ , so the answer is $ 5 $ .

## 样例 #1

### 输入

```
8
4 3
1 0 0 1
5 1
1 1 1 1 1
5 5
0 1 0 1 0
6 3
1 0 1 0 1 1
4 3
1 0 1 1
5 3
1 0 1 1 0
2 1
0 0
34 17
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
2
5
0
16
4
7
0
333606206```

# AI分析结果



**唯一算法分类**：组合数学

---

### **题解思路与核心分析**

**题目核心**：统计所有长度为k的子序列的中位数之和。由于数组元素为0或1，中位数为1的条件是子序列中1的数量≥m（m=(k+1)/2）。将问题转化为计算符合条件的子序列数量之和。

**关键步骤**：
1. **预处理组合数**：通过阶乘和逆元预处理，快速计算组合数C(n, k)。
2. **枚举1的个数**：对每个可能的1的个数i（m ≤ i ≤k），计算对应的组合数C(c, i)（选i个1）和C(n-c, k-i)（选k-i个0），累加乘积。

**解决难点**：
- **组合数的高效计算**：通过预处理阶乘和逆元，将组合数计算优化至O(1)。
- **边界条件处理**：如当i超过原数组中的1的总数或k-i超过0的总数时，组合数函数返回0，避免无效计算。

---

### **题解评分（≥4星）**

1. **aeiouaoeiu（5星）**
   - **亮点**：代码简洁高效，预处理阶乘和逆元方式清晰，逻辑直接，边界处理完善。
   - **代码可读性**：变量命名明确，结构紧凑，组合数函数处理了非法输入。

2. **cjh20090318（4.5星）**
   - **亮点**：明确问题转化思路，代码中组合数计算优化到位，注释清晰。
   - **优化点**：代码结构稍显复杂，但核心逻辑与高效预处理一致。

3. **Super_Cube（4星）**
   - **亮点**：代码简洁，直接枚举有效范围，组合数预处理正确。
   - **改进点**：变量命名较简略，但核心算法与思路正确。

---

### **最优思路提炼**

- **组合数学转化**：将中位数条件转化为组合数问题，统计满足条件的子序列数目。
- **预处理优化**：线性预处理阶乘和逆元数组，实现组合数O(1)查询。
- **边界处理技巧**：在组合数函数中自动处理无效情况（如n < m时返回0），简化主逻辑。

---

### **同类型题与算法套路**

- **通用解法**：涉及统计满足特定条件的子集/子序列数量时，常通过组合数学公式直接计算，而非暴力枚举。
- **类似题目**：
  1. **洛谷P1771**（组合数问题）：预处理组合数并处理模运算。
  2. **洛谷P1630**（二进制数组统计）：统计特定条件下的子集和。
  3. **洛谷P3807**（卢卡斯定理）：组合数计算的扩展应用。

---

### **代码片段（核心逻辑）**

```cpp
// 预处理阶乘和逆元
const int MOD = 1e9+7, N = 2e5+5;
ll frac[N], inv[N];
void init() {
    frac[0] = 1;
    for (int i=1; i<N; i++) frac[i] = frac[i-1] * i % MOD;
    inv[N-1] = qpow(frac[N-1], MOD-2, MOD);
    for (int i=N-2; i>=0; i--) inv[i] = inv[i+1] * (i+1) % MOD;
}

// 组合数计算
ll C(ll a, ll b) {
    if (a < b || b < 0) return 0;
    return frac[a] * inv[b] % MOD * inv[a - b] % MOD;
}

// 主逻辑
ll solve(int n, int k, int c) {
    ll ans = 0;
    int m = (k + 1) / 2;
    for (int i = m; i <= k; i++) {
        ans = (ans + C(c, i) * C(n - c, k - i)) % MOD;
    }
    return ans;
}
```

---

### **可视化设计（像素风格演示）**

**动画设计**：
- **像素网格**：原数组以像素块表示，1为绿色，0为灰色。
- **选择过程**：动态高亮选中的1和0，颜色区分（黄色为选中1，红色为选中0）。
- **组合数更新**：右侧面板显示当前i值、组合数计算式及累加结果。

**交互功能**：
- **步进控制**：支持逐帧查看i从m到k的遍历过程。
- **音效**：选中元素时播放8-bit音效，累加成功时音调上扬。

**复古元素**：
- **调色板**：使用16色复古风格，如NES的绿色、灰色、黄色。
- **背景音乐**：循环播放低比特率芯片音乐，增强沉浸感。

---

### **个人心得摘录**

- **调试教训**：初始未处理组合数边界条件（如k-i超过0的数量），导致错误累加，通过添加组合数函数的非法判断解决。
- **优化感悟**：预处理逆元的递推法相比逐个计算逆元，大幅减少时间复杂度。

---
处理用时：108.76秒