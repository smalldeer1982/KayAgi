# 题目信息

# Two Divisors

## 题目描述

A certain number $ 1 \le x \le 10^9 $ is chosen. You are given two integers $ a $ and $ b $ , which are the two largest divisors of the number $ x $ . At the same time, the condition $ 1 \le a < b < x $ is satisfied.

For the given numbers $ a $ , $ b $ , you need to find the value of $ x $ .

 $ ^{\dagger} $ The number $ y $ is a divisor of the number $ x $ if there is an integer $ k $ such that $ x = y \cdot k $ .

## 说明/提示

For the first test case, all divisors less than $ 6 $ are equal to $ [1, 2, 3] $ , among them the two largest will be $ 2 $ and $ 3 $ .

For the third test case, all divisors less than $ 33 $ are equal to $ [1, 3, 11] $ , among them the two largest will be $ 3 $ and $ 11 $ .

For the fifth test case, all divisors less than $ 20 $ are equal to $ [1, 2, 4, 5, 10] $ , among them the two largest will be $ 5 $ and $ 10 $ .

For the sixth test case, all divisors less than $ 12 $ are equal to $ [1, 2, 3, 4, 6] $ , among them the two largest will be $ 4 $ and $ 6 $ .

## 样例 #1

### 输入

```
8
2 3
1 2
3 11
1 5
5 10
4 6
3 9
250000000 500000000```

### 输出

```
6
4
33
25
20
12
27
1000000000```

# AI分析结果



---

## 算法分类  
**数学（数论）**

---

## 综合分析与结论  
### 核心思路  
题目要求根据给定的两个最大因数 `a` 和 `b`，求出原数 `x`。核心思路分为两种情况：  
1. **当 `b` 是 `a` 的倍数时**：`x` 的最小质因子为 `b/a`，此时 `x = b² / a`。  
2. **当 `b` 不是 `a` 的倍数时**：`x` 的最小公倍数（LCM）即为答案，即 `x = a*b / gcd(a, b)`。  

### 解决难点  
- **关键推导**：通过 `gcd` 和 `lcm` 的性质，结合因数的大小关系，确定 `x` 的表达式。  
- **数学验证**：需证明两种情况的唯一性，确保其他可能的 `x` 值不满足题目条件。  

### 可视化设计  
1. **动画流程**：  
   - **步骤1**：输入 `a` 和 `b`，计算 `gcd(a, b)`。  
   - **步骤2**：判断 `b % a == 0`（高亮条件分支）。  
   - **步骤3**：根据条件计算 `x`（显示公式和结果）。  
2. **复古像素风格**：  
   - **颜色标记**：`a` 和 `b` 用不同颜色方块表示，`gcd` 和 `lcm` 计算步骤用动态网格显示。  
   - **音效**：成功计算时播放 8-bit 成功音效，条件判断时播放点击音效。  
3. **交互功能**：支持单步执行，调节动画速度观察计算细节。  

---

## 题解清单（≥4星）  
### 五星题解  
1. **Crazyouth**  
   - **亮点**：直接分类讨论，代码极简，时间复杂度 `O(log b)`。  
   - **代码**：  
     ```cpp  
     if (b%a == 0) cout << b*b/a;  
     else cout << a*b/__gcd(a, b);  
     ```  

2. **Luzhuoyuan**  
   - **亮点**：结合最小质因子分析，代码与思路完全对应。  
   - **代码**：  
     ```cpp  
     if (y%x) printf("%lld\n", x*y/__gcd(x, y));  
     else printf("%lld\n", y*y/x);  
     ```  

### 四星题解  
1. **One_JuRuo**  
   - **亮点**：通过分解 `gcd` 后的变量简化问题，数学推导严谨。  
   - **代码**：  
     ```cpp  
     a /= gc, b /= gc;  
     if (a == 1) b *= b;  
     printf("%lld\n", b * gc);  
     ```  

---

## 最优思路提炼  
1. **分情况讨论**：根据 `b` 是否为 `a` 的倍数，选择不同公式。  
2. **数学性质**：利用 `gcd` 和 `lcm` 快速计算，避免遍历或复杂分解。  
3. **代码优化**：直接调用 `__gcd` 函数，无需预处理或复杂结构。  

---

## 类似题目推荐  
1. **CF1350B**（因数与递推关系）  
2. **P1029**（最大公约数与最小公倍数）  
3. **P1414**（因数分解与贪心）  

---

## 核心代码实现  
```cpp  
#include <bits/stdc++.h>  
using namespace std;  
int main() {  
    int t; cin >> t;  
    while (t--) {  
        long long a, b;  
        cin >> a >> b;  
        if (b % a == 0) cout << b * b / a << "\n";  
        else cout << a * b / __gcd(a, b) << "\n";  
    }  
    return 0;  
}  
```  

---

## 可视化算法演示（伪代码）  
```javascript  
// 伪代码：Canvas 绘制与音效  
function drawStep(a, b) {  
    ctx.fillStyle = "#8B0000"; // 复古红  
    drawBox(a);  
    ctx.fillStyle = "#00008B"; // 复古蓝  
    drawBox(b);  
    if (b % a === 0) {  
        playSound("success.wav");  
        drawFormula(`b²/a = ${b*b/a}`);  
    } else {  
        playSound("click.wav");  
        drawFormula(`LCM(a,b) = ${a*b/gcd(a,b)}`);  
    }  
}  
```  

---

## 个人心得摘录  
> “**UncleSam_Died**：预处理素数反而增加了复杂度，直接分两类更高效。”  
> **启示**：避免过度设计，数学题常可通过性质直接简化。

---
处理用时：178.00秒