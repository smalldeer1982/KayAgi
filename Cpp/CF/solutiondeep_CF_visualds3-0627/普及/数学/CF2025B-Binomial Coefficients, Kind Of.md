# 题目信息

# Binomial Coefficients, Kind Of

## 题目描述

Recently, akshiM met a task that needed binomial coefficients to solve. He wrote a code he usually does that looked like this:

```
<pre class="verbatim">    for (int n = 0; n < N; n++) { // loop over n from 0 to N-1 (inclusive)<br></br>        C[n][0] = 1;<br></br>        C[n][n] = 1;<br></br>        for (int k = 1; k < n; k++) // loop over k from 1 to n-1 (inclusive)<br></br>            C[n][k] = C[n][k - 1] + C[n - 1][k - 1];<br></br>    }<br></br>
```

Unfortunately, he made an error, since the right formula is the following:

```
<pre class="verbatim">            C[n][k] = C[n - 1][k] + C[n - 1][k - 1]<br></br>
```

But his team member keblidA is interested in values that were produced using the wrong formula. Please help him to calculate these coefficients for $ t $ various pairs $ (n_i, k_i) $ . Note that they should be calculated according to the first (wrong) formula.

Since values $ C[n_i][k_i] $ may be too large, print them modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
7
2 5 5 100000 100000 100000 100000
1 2 3 1 33333 66666 99999```

### 输出

```
2
4
8
2
326186014
984426998
303861760```

# AI分析结果



### **唯一算法分类**
组合数学

---

### **题解思路、算法要点与解决难点**
**核心思路**：错误递推式导致结果与正确二项式系数不同。通过观察或数学归纳法发现，当 `k < n` 时，错误计算的 `C[n][k]` 值为 `2^k`。  
**关键推导**：
1. **初始条件**：`C[n][0] = 1`, `C[n][n] = 1`  
2. **递推分析**：`C[n][k] = C[n][k-1] + C[n-1][k-1]`  
   若假设 `C[n][k-1] = 2^{k-1}` 且 `C[n-1][k-1] = 2^{k-1}`，则 `C[n][k] = 2^{k-1} + 2^{k-1} = 2^k`  
3. **归纳结论**：所有 `k < n` 的情况均满足 `C[n][k] = 2^k`  

**解决难点**：  
- **发现规律**：需通过打表或递推观察出与 `n` 无关的幂次规律。  
- **数学证明**：使用数学归纳法严谨验证猜想。  

**优化手段**：预处理 `2^k` 的模值，实现 `O(1)` 查询。

---

### **题解评分 (≥4星)**
1. **Chenyanxi0829 (5星)**  
   - **亮点**：简洁预处理 `2^k`，时间复杂度 `O(N + T)`，代码高效。  
   - **代码**：预处理数组 `a[i]` 存储 `2^i % mod`。  

2. **sherry_lover (4星)**  
   - **亮点**：详细数学归纳证明，表格展示规律，逻辑清晰。  
   - **代码**：预处理 `Pow` 数组，直接输出 `Pow[k]`。  

3. **DragonForge (4星)**  
   - **亮点**：分步骤推导递推式，结合样例观察，强调 `long long` 防溢出。  
   - **代码**：预处理 `f` 数组，输出 `f[k]`。  

---

### **最优思路或技巧提炼**
1. **观察打表**：通过小规模数据表格（如 `n=5, k=5`）发现 `C[n][k] = 2^k`。  
2. **数学归纳**：基于递推式 `C[n][k] = C[n][k-1] + C[n-1][k-1]`，假设前项成立，推导当前项。  
3. **预处理优化**：预先计算 `2^k % mod`，避免重复计算。  

---

### **同类型题或类似算法套路**
- **通用思路**：  
  - 递推式变形：通过改写递推式寻找简化规律（如线性递推、等比数列）。  
  - 组合数学归纳：利用数学归纳法证明递推结果。  
- **常见题型**：  
  - 快速幂计算（如 `a^b % mod`）。  
  - 组合数递推（如杨辉三角变形）。  

---

### **推荐相似题目**
1. **P3811 【模板】乘法逆元**（快速计算逆元预处理）  
2. **P1303 A*B Problem**（高精度快速幂）  
3. **P1029 最大公约数和最小公倍数问题**（数论递推）  

---

### **个人心得摘录**
- **Sherry_lover**：强调“打表找规律”是解决递推问题的利器。  
- **DragonForge**：提醒注意数据范围，避免 `int` 溢出，使用 `long long`。  
- **lhc0707**：通过拆解递推式发现系数与杨辉三角的关系，最终导出 `2^k`。  

---

### **可视化与算法演示**
**动画方案**：  
1. **网格填充**：  
   - 绘制 `n x k` 网格，动态填充每个 `C[n][k]` 的值。  
   - **颜色标记**：当前计算的格子高亮为黄色，依赖的前两项（`C[n][k-1]` 和 `C[n-1][k-1]`）标记为蓝色。  
   - **数值更新**：显示 `C[n][k] = 2^k` 的推导过程。  

2. **步进控制**：  
   - **单步执行**：逐步展示从 `k=1` 到 `k=5` 的计算流程。  
   - **自动演示**：自动填充表格，速度可调。  

3. **复古像素风格**：  
   - **8位音效**：每次计算成功播放“哔”声，完成一行播放胜利音效。  
   - **Canvas 绘制**：用像素块表示数值，不同颜色区分当前操作和结果。  

**代码片段**（JavaScript 伪代码）：  
```javascript
// 初始化 Canvas 和音效
const grid = initGrid(n, k); 
const beepSound = loadSound('8bit-beep.wav');

function animateStep(n, k) {
    highlightCell(n, k, 'yellow'); // 高亮当前格子
    playSound(beepSound);
    setTimeout(() => {
        updateCellValue(n, k, pow(2, k)); // 显示 2^k
        resetColor(n, k);
    }, 500);
}
```

---

### **代码实现（核心逻辑）**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int MAX_K = 1e5 + 10;

int main() {
    vector<int> pow2(MAX_K, 1);
    for (int i = 1; i < MAX_K; ++i) 
        pow2[i] = (pow2[i-1] * 2LL) % mod;
    
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        cout << pow2[k] << '\n';
    }
    return 0;
}
```

---
处理用时：72.32秒