# 题目信息

# Relatively Prime Powers

## 题目描述

Consider some positive integer $ x $ . Its prime factorization will be of form $ x = 2^{k_1} \cdot 3^{k_2} \cdot 5^{k_3} \cdot \dots $

Let's call $ x $ elegant if the greatest common divisor of the sequence $ k_1, k_2, \dots $ is equal to $ 1 $ . For example, numbers $ 5 = 5^1 $ , $ 12 = 2^2 \cdot 3 $ , $ 72 = 2^3 \cdot 3^2 $ are elegant and numbers $ 8 = 2^3 $ ( $ GCD = 3 $ ), $ 2500 = 2^2 \cdot 5^4 $ ( $ GCD = 2 $ ) are not.

Count the number of elegant integers from $ 2 $ to $ n $ .

Each testcase contains several values of $ n $ , for each of them you are required to solve the problem separately.

## 说明/提示

Here is the list of non-elegant numbers up to $ 10 $ :

- $ 4 = 2^2, GCD = 2 $ ;
- $ 8 = 2^3, GCD = 3 $ ;
- $ 9 = 3^2, GCD = 2 $ .

The rest have $ GCD = 1 $ .

## 样例 #1

### 输入

```
4
4
2
72
10
```

### 输出

```
2
1
61
6
```

# AI分析结果



## 算法分类  
莫比乌斯反演

---

## 综合分析与结论  

### 核心思路  
问题转化为统计非优雅数，即能表示为某个整数的高次幂的数。通过莫比乌斯函数进行容斥，计算所有可能的幂次方数（需排除重复统计）。数学推导为：  
`答案 = Σ μ(d) * (⌊n^(1/d)⌋ - 1)`，其中 μ 为莫比乌斯函数，d 遍历所有可能幂次。

### 难点与解决方案  
1. **精度处理**：计算高次根时，浮点运算存在误差。通过快速幂验证并调整结果（如 `pow` 计算后 ±2 微调）。  
2. **重复统计**：莫比乌斯函数 μ 的符号自动处理重复情况（如平方与立方数的交集通过 μ(6)=1 修正）。  
3. **时间复杂度**：d 最大取 60（因 2^60 ≈1e18），可线性筛预处理 μ 函数。

### 可视化设计  
- **动画流程**：  
  1. 左侧显示当前 d 值和 μ 系数，右侧展示数轴 [2, n]。  
  2. 高亮 d 次方数（如 2^2=4，3^3=27），不同颜色区分 μ 正负（绿色+，红色-）。  
  3. 动态累加结果，突出当前操作对总答案的影响。  
- **复古像素效果**：  
  - 用 8-bit 风格显示 d 值，每次计算时播放短音效（如“哔”声）。  
  - 数轴以方格表示，已统计的幂次方数闪烁后变灰。  

---

## 题解清单（≥4星）  

### 1. Echidna（5星）  
- **亮点**：严谨的数学推导，快速幂验证根值，代码简洁高效。  
- **代码片段**：  
  ```cpp  
  while(qpow(temp, i) > n) temp--;  // 调整精度  
  ans += mu[i] * (temp - 1);  
  ```

### 2. teylnol_evteyl（4星）  
- **亮点**：递归容斥思路新颖，记忆化优化加速重复计算。  
- **心得**：通过预处理小范围结果降低递归深度。  

### 3. cosf（4星）  
- **亮点**：详细注释 μ 计算过程，独立实现快速幂调整根值。  

---

## 核心代码实现  

### 关键逻辑（Echidna 题解）  
```cpp  
ll solve(int k, LL n) {  
    LL q = (LL)pow(n, 1.0L / k) + 2;  
    while(ksm(q, k) > n) q--;  // 调整至精确值  
    return q - 1;  
}  
```

### 完整代码（Echidna 题解）  
```cpp  
#include <iostream>  
#include <cmath>  
using namespace std;  
typedef long long LL;  
typedef long double LD;  

int mu[100];  
// ...（预处理 μ 函数）  

LD qpow(LD a, LL b) { /* 快速幂 */ }  

int main() {  
    init_mu();  
    LL n; cin >> n;  
    LL ans = 0;  
    for(int d=1; d<=60; d++) {  
        LL temp = pow(n, 1.0/d) + 2;  
        while(qpow(temp, d) > n) temp--;  
        ans += mu[d] * (temp -1);  
    }  
    cout << ans << endl;  
}  
```

---

## 同类型题目与套路  
1. **套路**：容斥 + 数论函数（μ, φ）处理区间统计问题。  
2. **相似题**：  
   - [P4318] 完全平方数（莫比乌斯求第 k 个无平方因子数）  
   - [P2424] 约数和（分块+数论技巧）  
   - [CF1225D] Power Products（因数分解+哈希统计）  

---

## 可视化与游戏化设计  
- **Canvas 动画**：  
  - **网格数轴**：每个整数用 16x16 像素块表示，点击显示其质因数分解。  
  - **自动模式**：AI 按 d=1→60 顺序计算，显示当前 μ 值和统计结果。  
- **音效设计**：  
  - 正贡献（μ=+1）：高音“叮”；负贡献（μ=-1）：低音“咚”。  
  - 背景音乐：8-bit 风格循环旋律。  

---

## 个人心得摘录  
- **调试教训**：直接使用 `pow(8,1/3.0)` 可能返回 2.999，需循环调整至 2。  
- **优化技巧**：预处理 μ 函数时，注意线性筛的终止条件（i*primes[j] ≤ n）。  

--- 

## 推荐练习题  
1. **P4318** - 完全平方数  
2. **CF1225D** - Power Products  
3. **P2257** - YY的GCD（莫比乌斯反演经典题）

---
处理用时：74.97秒