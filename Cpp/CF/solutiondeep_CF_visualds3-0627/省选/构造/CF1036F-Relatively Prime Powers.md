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



**唯一算法分类**：莫比乌斯函数与容斥原理  

---

### **题解思路与核心难点**  
**核心思路**：  
- 合法数满足质因数指数 GCD=1，反转为计算非法数（GCD>1）。非法数可表示为某个数的幂次（如 $k^i$）。  
- 利用莫比乌斯函数 $\mu(d)$ 进行容斥：$\text{ans} = \sum_{d=1}^{\log_2 n} \mu(d) \cdot (\lfloor \sqrt[d]{n} \rfloor - 1)$，其中 $\lfloor \sqrt[d]{n} \rfloor -1$ 是 $d$ 次方数的数量。  

**难点与解决方案**：  
1. **精度调整**：计算 $\sqrt[d]{n}$ 时需避免浮点误差，通过快速幂验证调整结果。  
2. **莫比乌斯函数预处理**：筛法生成 $\mu(d)$，用于加权求和。  
3. **时间复杂度**：仅需遍历 $d \leq 60$，单次查询 $O(60)$，适合大范围数据。  

---

### **题解评分 (≥4星)**  
1. **Echidna (★★★★★)**  
   - 思路清晰，直接应用莫比乌斯反演公式。  
   - 代码简洁，快速幂调整精度，适合教学与扩展。  
2. **teylnol_evteyl (★★★★☆)**  
   - 明确解释容斥逻辑，提供快速幂验证方法。  
   - 代码包含详细注释，适合理解实现细节。  
3. **codwarm (★★★★☆)**  
   - 纯容斥递归思路，展示另一种实现角度。  
   - 记忆化优化递归过程，适合理解容斥本质。  

---

### **最优思路提炼**  
1. **莫比乌斯容斥**：  
   - 非法数的幂次形式 $\rightarrow$ 转化为 $d$ 次方数计数。  
   - 通过 $\mu(d)$ 符号调整容斥项，避免重复/遗漏。  
2. **快速幂精度校准**：  
   - 使用 `pow` 初步估算，再通过快速幂微调确保准确性。  

---

### **同类型题与算法套路**  
- **通用解法**：涉及数论计数的容斥问题（如平方数、立方数统计）。  
- **类似题目**：  
  - **洛谷 P2567**（统计区间内的幸运数，需容斥排除倍数）。  
  - **洛谷 P2424**（约数和问题，结合分块与预处理）。  
  - **洛谷 P2158**（欧拉函数求可见点数，类似互质计数）。  

---

### **核心代码实现**  
**关键逻辑**：快速幂调整与莫比乌斯求和  
```cpp
// Echidna 题解核心代码
double qpow(double a, ll b) { // 快速幂验证
    if (b == 1) return a;
    if (b % 2 == 1) return qpow(a, b - 1) * a;
    double temp = pow(a, b / 2);
    return temp * temp;
}

ll solve(ll n) {
    ll ans = 0;
    for (int d = 1; d <= 60; d++) {
        ll temp = (ll)(pow(n, 1.0 / d)) + 1;
        while (qpow(temp, d) > n) temp--;
        ans += mu[d] * (temp - 1);
    }
    return ans;
}
```

---

### **可视化设计思路**  
**动画方案**：  
1. **数轴展示**：  
   - 在 Canvas 上绘制数轴，标记 $n$ 的位置。  
   - 不同颜色方块表示各 $d$ 次方数（如红色块为平方数，蓝色为立方数）。  
2. **动态计算**：  
   - 高亮当前计算的 $d$ 值，显示 $\mu(d)$ 符号（正/负）。  
   - 逐步累加/减少对应颜色的方块，体现容斥过程。  
3. **像素风格**：  
   - 使用 8-bit 音效：每次调整精度时播放“滴”声，计算完成播放胜利音效。  
   - 背景为网格，方块像素化，数值以复古字体显示。  

**交互功能**：  
- **步进控制**：暂停观察每个 $d$ 的贡献，点击方块查看具体数值。  
- **自动演示**：AI 模式自动遍历 $d=1\to60$，速度可调。  

---

### **个人心得摘录**  
- **精度陷阱**：直接使用 `pow` 函数可能导致结果偏大，必须通过快速幂回推验证。  
- **莫比乌斯符号**：容斥时 $\mu(d)$ 的符号决定加减，需注意预处理时的筛法正确性。  

--- 

**推荐题目**：  
1. [洛谷 P2567](https://www.luogu.com.cn/problem/P2567)  
2. [洛谷 P2424](https://www.luogu.com.cn/problem/P2424)  
3. [洛谷 P2158](https://www.luogu.com.cn/problem/P2158)

---
处理用时：67.54秒