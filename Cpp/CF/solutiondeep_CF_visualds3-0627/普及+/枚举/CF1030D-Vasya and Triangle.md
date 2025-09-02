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



---

### 算法分类
**数论与构造**

---

### 题解思路与核心难点
**核心思路**  
构造以原点、x轴点、y轴点形成的直角三角形，面积公式为 $\frac{1}{2}xy = \frac{nm}{k}$，转化为 $xy = \frac{2nm}{k}$。需满足 $x \leq n$ 且 $y \leq m$。

**解决难点**  
1. **因数分配**：分解 $k$ 的质因数，将其合理分配到 $x$ 和 $y$ 的约束范围内。
2. **奇偶性处理**：当 $k$ 为奇数时，需确保 $\frac{2nm}{k}$ 为整数，并调整 $x$ 或 $y$ 乘以2以满足约束。

---

### 题解评分（≥4星）
1. **da32s1da（5星）**  
   - **亮点**：直接利用最大公约数快速分配因数，通过调整策略解决溢出问题，代码简洁高效。
2. **DJRzjl（4星）**  
   - **亮点**：分奇偶讨论，系统化质因数分解，逻辑清晰。
3. **chen_hx（4星）**  
   - **亮点**：几何构造思路新颖，通过调整斜边坐标点实现面积要求。

---

### 最优思路提炼
1. **判断无解条件**：若 $2nm \bmod k \neq 0$，直接输出 `NO`。
2. **因数分解与调整**：  
   - 计算 $g = \gcd(2n, k)$，初始 $x = \frac{2n}{g}$，$y = \frac{m}{k/g}$。  
   - 若 $x > n$，则 $x \gets x/2$，$y \gets 2y$，确保 $x \leq n$ 且 $y \leq m$。
3. **输出构造点**：以 $(0,0)$ 为原点，$(x,0)$ 和 $(0,y)$ 为另两点。

---

### 类似题目推荐
1. **CF448E**（Divisors）：因数分解与构造。
2. **P1516**（青蛙的约会）：扩展欧几里得算法应用。
3. **AT_abc108C**（Triangular Relationship）：数论条件判断与构造。

---

### 代码实现（核心逻辑）
```cpp
#include <cstdio>
typedef long long LL;

LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

int main() {
    LL n, m, k;
    scanf("%lld%lld%lld", &n, &m, &k);
    if (2 * n * m % k != 0) {
        puts("NO");
        return 0;
    }
    LL g = gcd(2 * n, k);
    LL x = (2 * n) / g;
    k /= g;
    LL y = m / k;
    if (x > n) {
        x /= 2;
        y *= 2;
    }
    puts("YES");
    printf("0 0\n%lld 0\n0 %lld\n", x, y);
    return 0;
}
```

---

### 可视化设计
**复古像素动画方案**  
1. **画面布局**：  
   - **左侧**：8-bit 风格的网格坐标系，显示矩形范围 $[0, n] \times [0, m]$。  
   - **右侧**：动态展示因数分解过程，用像素块表示 $k$ 的质因数分配到 $x$ 或 $y$。  
2. **动画流程**：  
   - **Step 1**：显示初始 $n, m, k$ 值，计算 $2nm/k$，高亮红色若无法整除。  
   - **Step 2**：分解 $k$ 的质因数，像素块从左到右分配至 $x$ 或 $y$ 的槽位。  
   - **Step 3**：若 $x$ 越界，触发“调整动画”：$x$ 减半（像素收缩），$y$ 翻倍（像素扩展）。  
3. **音效与交互**：  
   - **分配成功**：8-bit 上升音效。  
   - **调整触发**：经典“金币”音效。  
   - **失败/无解**：低音“错误”音效。  

---

### 个人心得
- **调试陷阱**：长整型溢出需用 `LL`，如 `2 * n * m` 可能超出 `int` 范围。  
- **思维突破**：直角三角形的构造极大简化了问题，避免复杂坐标计算。

---
处理用时：144.15秒