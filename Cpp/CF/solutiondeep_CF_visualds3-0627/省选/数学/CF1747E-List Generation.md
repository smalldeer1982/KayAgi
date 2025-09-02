# 题目信息

# List Generation

## 题目描述

For given integers $ n $ and $ m $ , let's call a pair of arrays $ a $ and $ b $ of integers good, if they satisfy the following conditions:

- $ a $ and $ b $ have the same length, let their length be $ k $ .
- $ k \ge 2 $ and $ a_1 = 0, a_k = n, b_1 = 0, b_k = m $ .
- For each $ 1 < i \le k $ the following holds: $ a_i \geq a_{i - 1} $ , $ b_i \geq b_{i - 1} $ , and $ a_i + b_i \neq a_{i - 1} + b_{i - 1} $ .

Find the sum of $ |a| $ over all good pairs of arrays $ (a,b) $ . Since the answer can be very large, output it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first testcase, the good pairs of arrays are

- $ ([0, 1], [0, 1]) $ , length = $ 2 $ .
- $ ([0, 1, 1], [0, 0, 1]) $ , length = $ 3 $ .
- $ ([0, 0, 1], [0, 1, 1]) $ , length = $ 3 $ .

Hence the sum of the lengths would be $ {2 + 3 + 3} = 8 $ .

## 样例 #1

### 输入

```
4
1 1
1 2
2 2
100 100```

### 输出

```
8
26
101
886336572```

# AI分析结果



### 唯一算法分类
**组合数学**

### 综合分析与结论
本题要求计算满足特定递增条件的数组对长度之和，核心是组合数学中的路径模型与容斥原理。关键思路是将问题转化为网格路径中的拐点枚举，通过组合数计算合法点集数目，并利用容斥处理相邻位置不能同时为零的条件。难点在于高效处理组合数求和与二项式反演。

**可视化设计思路**：  
- 在像素风格的网格中展示从 (0,0) 到 (n,m) 的路径，红色标记拐点，蓝色标记可选点。  
- 动态显示每一步的拐点选择（如先右后下），计算组合数并叠加贡献。  
- 音效在关键计算步骤触发，如拐点确认或贡献累加时播放 8-bit 音效。  
- 右侧面板实时显示当前拐点数目、组合数值及贡献公式推导过程。

### 题解清单（≥4星）
1. **EuphoricStar（4.5星）**  
   - **亮点**：直观的路径模型与拐点枚举，利用组合数与幂次求和快速计算贡献。  
   - **关键公式**：$\sum \binom{n}{i}\binom{m}{i} \left[(i+2)2^{n+m-i-1} + (n+m-i-1)2^{n+m-i-2}\right]$。  
   - **代码**：预处理阶乘后直接计算，逻辑清晰。

2. **5ab_juruo（4.5星）**  
   - **亮点**：通过二项式反演和递推优化，将复杂度降至线性。  
   - **技巧**：递推式 $G(i) = 2G(i+1) + \text{修正项}$，避免重复计算组合数。  
   - **代码**：高效预处理阶乘，递推过程简洁。

3. **Sampson_YW（4星）**  
   - **亮点**：差分数组模型结合容斥，生成函数思路清晰。  
   - **公式**：合法方案数 $F(k) = \sum (-1)^{k-i} \binom{k-1}{i-1} G(i)$。  
   - **实现**：预处理组合数后直接求和，适合小范围数据。

### 最优思路或技巧提炼
1. **路径拐点模型**：将数组对的生成视为网格路径，拐点决定点集结构，避免重复计数。  
2. **容斥与递推**：通过二项式反演处理非法情况，递推优化组合数求和。  
3. **组合数恒等式**：$\sum_{j=0}^s \binom{s}{j}j = s2^{s-1}$，简化贡献计算。

### 同类型题与常见套路
- **常见套路**：容斥处理相邻约束，路径模型转化，组合数快速求和。  
- **相似题目**：  
  - P8558 黑暗（二项式反演与递推）  
  - P3223 排列计数（容斥与组合数）  
  - P2767 网格路径计数（拐点模型与组合数）

### 推荐题目
1. **CF1188B**（路径计数与容斥）  
2. **洛谷 P6672**（组合数与递推优化）  
3. **AT_abc211_e**（网格路径与容斥原理）

### 核心代码片段（EuphoricStar思路）
```cpp
const int mod = 1e9 + 7, max_n = 5e6;
mint fac[max_n * 3], ifac[max_n * 3];

mint C(int a, int b) { return fac[a] * ifac[b] * ifac[a - b]; }

signed main() {
    // 预处理阶乘和逆元
    fac[0] = 1;
    for (int i = 1; i < max_fs; i++) fac[i] = fac[i - 1] * i;
    ifac[max_fs - 1] = fac[max_fs - 1].inv();
    for (int i = max_fs - 1; i > 0; i--) ifac[i - 1] = ifac[i] * i;

    int n, m; 
    mint ans = 0, G = F(n + m, 0);
    for (int i = n + m; i >= 1; i--) {
        ans += G * (i + 1) * C(n + i - 1, i - 1) * C(m + i - 1, i - 1);
        if (i > 1) G = G * 2 - F(i, n + m - i) + F(i - 1, n + m - i + 1);
    }
    cout << ans << "\n";
}
```

### 可视化实现要点（JavaScript伪代码）
```javascript
class GridAnimation {
    constructor(n, m) {
        this.canvas = document.getElementById("grid-canvas"); 
        this.ctx = this.canvas.getContext('2d');
        this.n = n; this.m = m;
        this.path = []; // 当前路径拐点
        this.speed = 1000; // 动画速度
        this.currentI = 0; // 当前拐点数
    }

    drawGrid() {
        // 绘制n x m网格，起点(0,0)到(n,m)
    }

    highlightPoints(i) {
        // 绘制i个拐点，红色标记先右后下，蓝色先下后右
    }

    async animate() {
        for (let i = 0; i <= Math.min(this.n, this.m); i++) {
            this.currentI = i;
            this.drawGrid();
            this.highlightPoints(i);
            await this.delay(this.speed);
            // 计算组合数并叠加贡献
            const comb = C(n, i) * C(m, i);
            const s = n + m - i - 1;
            const term = comb * ((i + 2) * (1 << s) + s * (1 << (s - 1)));
            total += term;
            // 更新右侧公式显示
        }
    }
}
```

---
处理用时：97.08秒