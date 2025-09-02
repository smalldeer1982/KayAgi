# 题目信息

# Border

## 题目描述

Astronaut Natasha arrived on Mars. She knows that the Martians are very poor aliens. To ensure a better life for the Mars citizens, their emperor decided to take tax from every tourist who visited the planet. Natasha is the inhabitant of Earth, therefore she had to pay the tax to enter the territory of Mars.

There are $ n $ banknote denominations on Mars: the value of $ i $ -th banknote is $ a_i $ . Natasha has an infinite number of banknotes of each denomination.

Martians have $ k $ fingers on their hands, so they use a number system with base $ k $ . In addition, the Martians consider the digit $ d $ (in the number system with base $ k $ ) divine. Thus, if the last digit in Natasha's tax amount written in the number system with the base $ k $ is $ d $ , the Martians will be happy. Unfortunately, Natasha does not know the Martians' divine digit yet.

Determine for which values $ d $ Natasha can make the Martians happy.

Natasha can use only her banknotes. Martians don't give her change.

## 说明/提示

Consider the first test case. It uses the octal number system.

If you take one banknote with the value of $ 12 $ , you will get $ 14_8 $ in octal system. The last digit is $ 4_8 $ .

If you take one banknote with the value of $ 12 $ and one banknote with the value of $ 20 $ , the total value will be $ 32 $ . In the octal system, it is $ 40_8 $ . The last digit is $ 0_8 $ .

If you take two banknotes with the value of $ 20 $ , the total value will be $ 40 $ , this is $ 50_8 $ in the octal system. The last digit is $ 0_8 $ .

No other digits other than $ 0_8 $ and $ 4_8 $ can be obtained. Digits $ 0_8 $ and $ 4_8 $ could also be obtained in other ways.

The second test case uses the decimal number system. The nominals of all banknotes end with zero, so Natasha can give the Martians only the amount whose decimal notation also ends with zero.

## 样例 #1

### 输入

```
2 8
12 20
```

### 输出

```
2
0 4 ```

## 样例 #2

### 输入

```
3 10
10 20 30
```

### 输出

```
1
0 ```

# AI分析结果



# 算法分类  
**数论**

---

## 题解思路与核心算法  
### 核心思路  
所有可能金额的末位数字由两个关键因素决定：  
1. 所有纸币面值的最大公约数 `d = gcd(a₁, a₂, ..., aₙ)`  
2. 数制基数 `k` 的公约数 `g = gcd(d, k)`  

根据裴蜀定理，可能的末位数字必须是 `g` 的倍数。总共有 `k/g` 种可能的余数值，按 `0, g, 2g, ..., (k/g-1)g` 排列。

### 解决难点  
1. **问题转化**：将末位数字问题转化为模 `k` 余数问题，发现余数必须满足 `dx ≡ c (mod k)`。  
2. **双重GCD计算**：需先后计算纸币面值的GCD和其与 `k` 的GCD。  
3. **数学证明**：通过裴蜀定理证明余数必须是 `g` 的倍数。

---

## 题解评分（≥4星）  
1. **Otue（5星）**  
   - 代码极简，直接使用 `__gcd` 函数链式求解。  
   - 思路清晰，数学推导一步到位。  
   - 关键代码：`ans = __gcd(ans, a[i])` 实现双重GCD计算。  

2. **残阳如血（4.5星）**  
   - 代码模块化，注释详细。  
   - 明确将 `k` 加入GCD计算，逻辑更直观。  
   - 关键代码：`d = std::__gcd(d, a[i])`。  

3. **Infinity_Fantasy（4星）**  
   - 代码简洁，变量命名明确。  
   - 使用 `gd = __gcd(gd, a)` 逐步计算。  

---

## 最优技巧提炼  
1. **双重GCD链式计算**  
   ```cpp  
   int g = k;  
   for (int a : nums) g = __gcd(g, a);  
   ```  
   初始 `g` 设为 `k`，逐步与每个面值计算GCD。  

2. **余数生成模式**  
   ```cpp  
   for (int i=0; i<k/g; i++) cout << i*g << ' ';  
   ```  
   直接按步长 `g` 生成所有合法余数。

---

## 同类题目推荐  
1. **P3951 小凯的疑惑**（裴蜀定理应用）  
2. **P4549 裴蜀定理**（模板题）  
3. **P1516 青蛙的约会**（扩展欧几里得算法）

---

## 可视化与算法演示  
### 动画设计  
1. **初始状态**：  
   - 屏幕左侧显示纸币面值，右侧显示 `k` 和初始 `g=k`。  
   - 颜色标记当前计算的面值（黄色）、当前 `g`（绿色）。  

2. **计算GCD过程**：  
   - 每个面值依次与当前 `g` 计算GCD，数值变化时播放“滴”音效。  
   - 用箭头动画展示 `g = gcd(g, a_i)` 的更新过程。  

3. **余数生成**：  
   - 最终 `g` 显示为红色，下方生成余数序列，逐个弹出并高亮。  

### 复古像素风格  
- **颜色方案**：8-bit 风格，纸币用蓝/绿方块，数值用白色像素字体。  
- **音效**：  
  - 计算GCD时播放 `NES-跳跃音效`。  
  - 生成余数时播放 `FC-金币收集音效`。  
- **背景音乐**：8-bit 循环版《超级玛丽》地下关BGM。  

### 交互控制  
- **步进控制**：按空格暂停/继续，方向键单步执行。  
- **速度调节**：滑块控制动画速度（1x~5x）。  

---

## 核心代码实现  
```cpp  
#include <bits/stdc++.h>  
using namespace std;  

int main() {  
    int n, k, g;  
    cin >> n >> k;  
    g = k;  
    for (int i=0, a; i<n; i++) {  
        cin >> a;  
        g = __gcd(g, a);  
    }  
    cout << k/g << '\n';  
    for (int i=0; i<k/g; i++)  
        cout << i*g << ' ';  
    return 0;  
}  
```  

---

## 个人心得摘录  
> "初始将 `g` 设为 `k` 是关键，这样后续计算自然包含 `k` 的影响，无需额外处理。" —— Otue  
> "调试时发现必须将 `k` 纳入GCD计算，否则无法覆盖所有情况。" —— 残阳如血  

---

## 扩展思考  
若纸币数量有限（非无限），问题将转化为背包问题，需使用动态规划或BFS求解。

---
处理用时：76.84秒