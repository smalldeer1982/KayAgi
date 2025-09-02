# 题目信息

# Vasya and Triangle

## 题目描述

Vasya has got three integers $ n $ , $ m $ and $ k $ . He'd like to find three integer points $ (x_1, y_1) $ , $ (x_2, y_2) $ , $ (x_3, y_3) $ , such that $ 0 \le x_1, x_2, x_3 \le n $ , $ 0 \le y_1, y_2, y_3 \le m $ and the area of the triangle formed by these points is equal to $ \frac{nm}{k} $ .

Help Vasya! Find such points (if it's possible). If there are multiple solutions, print any of them.

## 说明/提示

In the first example area of the triangle should be equal to $ \frac{nm}{k} = 4 $ . The triangle mentioned in the output is pictured below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030D/7ee3f0a3ce75449bbc8ed199a32a394763a46df2.png)In the second example there is no triangle with area $ \frac{nm}{k} = \frac{16}{7} $ .

## 样例 #1

### 输入

```
4 3 3
```

### 输出

```
YES
1 0
2 3
4 1
```

## 样例 #2

### 输入

```
4 4 7
```

### 输出

```
NO
```

# AI分析结果



1. **算法分类**  
   **数论/构造**

---

### 题解思路与核心难点

#### 核心思路
所有题解均围绕以下关键点展开：
1. **面积特性**：整点三角形面积的两倍必须是整数 → 若 `2nm % k ≠ 0` 则无解。
2. **构造直角顶点**：以 `(0,0)` 为直角顶点，另外两个顶点在坐标轴上，构造直角三角形，面积公式为 `xy/2`。
3. **因数分解与调整**：将 `k` 分解为两个数的乘积，分别调整 `n` 和 `m` 的值，确保 `x ≤ n` 且 `y ≤ m`。

#### 难点对比
- **da32s1da**：通过 `gcd(2n, k)` 快速确定 `x` 的初值，若超限则调整 `x` 和 `m` 的倍数关系。代码简洁高效。
- **DJRzjl**：分 `k` 为奇偶处理，奇数时需额外调整 `2` 的分配，逻辑严谨但实现稍复杂。
- **chen_hx**：通过几何变形处理 `x > n` 的情况，利用斜边动态调整顶点坐标，思路独特但实现难度较高。

---

### 题解评分（≥4星）

1. **da32s1da（4.5星）**  
   - 亮点：代码简洁，利用 `gcd` 快速分解因数，调整逻辑清晰。
   - 代码片段：
     ```cpp
     X = (2 * n) / gcd(2 * n, k);
     if (X > n) X /= 2, m *= 2;
     ```

2. **DJRzjl（4星）**  
   - 亮点：奇偶分治逻辑严密，质因数分解实现通用性强。
   - 代码片段：
     ```cpp
     if (k % 2 == 0) res = solve(k / 2, n, m);
     else { res = solve(k, n, m); ... }
     ```

3. **wjyyy（4星）**  
   - 亮点：详细证明面积特性，枚举约数时优化上下界。
   - 代码片段：
     ```cpp
     for (int i = (n / tt) ? (n / tt) : 1; i <= up; ++i)
         if (n % i == 0 && n / i <= t) { ... }
     ```

---

### 最优思路提炼
- **关键技巧**：利用 `gcd(2n, k)` 分解 `k`，快速计算初始 `x` 和 `y`，再通过倍数调整确保不超限。
- **代码实现**：
  ```cpp
  LL x = (2 * n) / gcd(2 * n, k);
  LL y = m / (k / gcd(2 * n, k));
  if (x > n) x /= 2, y *= 2;
  ```

---

### 相似题目推荐
1. **P1516 青蛙的约会**（扩展欧几里得算法）  
2. **P1447 能量采集**（数论应用，二维因数分解）  
3. **P3951 小凯的疑惑**（数论构造与最大不可表数）

---

### 可视化与动画设计
**像素风格算法演示**  
1. **初始化**：在 `Canvas` 绘制 `n×m` 网格，原点 `(0,0)` 高亮显示。  
2. **因数分解动画**：动态显示 `k` 分解为 `gcd(2n, k)` 的过程，质因数以像素块下坠效果呈现。  
3. **坐标调整**：若 `x` 超过 `n`，播放缩放动画（`x` 减半，`y` 倍增），配 8-bit 音效。  
4. **成功/失败提示**：找到解时显示绿色三角形，失败时红色闪烁，背景音乐随结果切换。

**交互设计**  
- **步进控制**：按空格键逐步执行分解、调整、验证步骤。  
- **自动模式**：AI 自动运行，模拟“贪吃蛇”路径式演示解题流程。

---

### 代码实现（核心逻辑）
```cpp
#include <cstdio>
typedef long long LL;
LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

int main() {
    LL n, m, k;
    scanf("%lld%lld%lld", &n, &m, &k);
    if (2LL * n * m % k != 0) return puts("NO"), 0;

    LL g = gcd(2 * n, k);
    LL x = (2 * n) / g;
    k /= g;
    LL y = m / k;

    if (x > n) x /= 2, y *= 2;
    puts("YES\n0 0");
    printf("%lld 0\n0 %lld\n", x, y);
    return 0;
}
```

---

### 个人心得摘录
- **da32s1da**：强调构造直角坐标系顶点的重要性，避免复杂计算。  
- **wjyyy**：调试时发现枚举约数需优化上下界，否则会 TLE。

---
处理用时：84.74秒