# 题目信息

# PAGAIN - Prime Again

## 题目描述

[English](/problems/PAGAIN/en/) [Vietnamese](/problems/PAGAIN/vn/)In this problem, you have to find the nearest prime number smaller than N. (3 <= N <= 2^32)

## 样例 #1

### 输入

```
3

5 

10

17```

### 输出

```
3

7

13```

# AI分析结果



## 唯一算法分类
**数论 - 质数判定与预处理**

---

## 综合分析与结论

### 核心思路与难点
**题目核心**：快速找到小于给定数 N 的最大质数。  
**关键难点**：N 的范围极大（最大 2^32），直接暴力枚举或传统试除法均不可行。  

**解决方案**：  
1. **预处理小范围质数**：通过欧拉筛法预处理 1e5~1e7 范围内的质数，小数值直接查表返回。  
2. **Miller-Rabin 高效判质**：对大数从 N-1 向下逐个测试，利用 Miller-Rabin 算法（基于费马小定理和二次探测）快速判断质数。  
3. **大数运算优化**：使用 `__int128` 或龟速乘防止快速幂运算溢出。

### 可视化设计思路
- **动画流程**：  
  - **预处理阶段**：展示欧拉筛法的动态过程，高亮筛去的合数。  
  - **质数判定阶段**：从 N-1 开始逐数下探，用不同颜色标记当前测试数、Miller-Rabin 的测试基数和结果。  
  - **成功判定**：找到质数时触发像素爆炸特效，并播放成功音效。  
- **复古风格**：  
  - **像素网格**：用 16 色块表示数字，筛法过程类似“扫雷”清除合数。  
  - **音效设计**：每次 Miller-Rabin 测试播放 8-bit 音效，成功时播放经典 FC 过关音效。  
- **交互控制**：支持暂停/步进，查看当前测试的基数和幂次结果。

---

## 题解清单（≥4星）

### 1. ioker（5星）
- **亮点**：预处理到 1e7 大幅减少后续测试次数；代码结构清晰，Miller-Rabin 实现高效。  
- **核心代码**：  
  ```cpp
  inline int ans(int n) {
    if (n < N) return prime[phi[n]]; // 查表
    for (int i = n;; i--) // 向下枚举
      if (pri(i)) return i; // Miller-Rabin 测试
  }
  ```

### 2. Leasier（4星）
- **亮点**：使用 OI-Wiki 推荐的测试基数 [2,7,61]，确保 2^32 内绝对正确。  
- **优化点**：预处理 1e7 质数，代码简洁易移植。

### 3. EXR_FAL（4星）
- **亮点**：完整注释与复古风格代码，包含龟速乘防止溢出；预处理与测试逻辑分离清晰。  
- **个人心得**：强调 `__int128` 的必要性，避免快速幂溢出。

---

## 最优思路提炼

### 关键技巧
1. **分块处理**：小范围欧拉筛预处理，大范围 Miller-Rabin 暴力枚举。  
2. **测试基数选择**：针对 N ≤ 2^32，使用 [2,7,61] 或 [2,7,63] 确保 100% 正确。  
3. **运算优化**：  
   - 快速幂与龟速乘结合，使用 `__int128` 处理大数乘法。  
   - 预处理质数表范围需权衡内存与查询效率（推荐 1e7）。

---

## 相似题目推荐
1. **SP288 (PON)**：Miller-Rabin 模板题，直接判断大数是否为质数。  
2. **P3383 【模板】线性筛素数**：练习欧拉筛预处理。  
3. **P3912 质数统计**：大数据范围统计质数个数，需结合筛法与 Miller-Rabin。

---

## 个人心得摘录
- **调试教训**：未使用 `__int128` 导致快速幂溢出，测试时出现假阴性错误。  
- **优化经验**：预处理范围从 1e5 调整到 1e7 后，平均查询时间减少 40%。  
- **思维突破**：Miller-Rabin 的二次探测是避免误判的关键，而非单纯依赖费马小定理。

---

## 代码核心实现

### Miller-Rabin 实现（ioker 版）
```cpp
inline int power(int n, int m, int p) {
    int ans = 1;
    while (m) {
        if (m & 1) ans = (__int128)ans * n % p; // 防溢出
        n = (__int128)n * n % p;
        m >>= 1;
    }
    return ans;
}

inline bool millerrabin(int n, int m) {
    int k = n - 1;
    while (k) {
        int a = power(m, k, n);
        if (a != n-1 && a != 1) return 0; // 二次探测失败
        if (k & 1 || a == n-1) return 1;
        k >>= 1;
    }
    return 1;
}
```

---

## 可视化代码片段（Canvas 动画）

```javascript
// 模拟 Miller-Rabin 测试步骤
function drawMillerRabinStep(n, a) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    drawNumber(n); // 绘制当前测试数
    let k = n - 1, t = 0;
    while (k % 2 === 0) { k /= 2; t++; }
    let x = modularPow(a, k, n); // 计算 a^k % n
    highlightStep(`a=${a}, k=${k}, x=${x}`); // 高亮当前参数
    if (x === 1 || x === n-1) return true;
    for (let i = 0; i < t; i++) {
        x = (x * x) % n;
        if (x === n-1) return true;
    }
    return false;
}
```

---
处理用时：86.68秒