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



---

## 唯一算法分类  
**数论（最大公约数/裴蜀定理应用）**

---

## 综合分析与结论  
### 核心思路与难点  
题目要求确定所有可能的模 `k` 余数 `d`，使得用给定的无限数量纸币组合出的总金额在 `k` 进制下末位为 `d`。关键步骤如下：  

1. **裴蜀定理应用**：所有可能的组合总和是数组 `a` 的最大公约数 `g` 的倍数。  
2. **模运算转化**：设 `d = gcd(g, k)`，则余数必须是 `d` 的倍数，共有 `k/d` 种可能（`0, d, 2d, ..., (k/d-1)d`）。  

**难点**在于如何将组合问题转化为数论问题：  
- 通过分析线性组合的数学性质，将问题转化为求 `gcd` 的倍数。  
- 正确推导出余数必须是 `gcd(g, k)` 的倍数，而非直接使用数组元素的 `gcd`。  

### 可视化设计  
- **动画流程**：  
  1. 展示数组元素逐步计算 `gcd` 的过程（像素风格数值变化）。  
  2. 计算 `gcd(g, k)` 并生成余数列表，用动态网格高亮每个有效余数。  
  3. 以步进方式显示余数生成逻辑（如 `0 → d → 2d → ...`）。  
- **复古元素**：  
  - 8-bit 音效：计算 `gcd` 时播放短促音效，生成余数时播放上扬音调。  
  - Canvas 网格展示余数分布，用不同颜色标记已确定的有效余数。  

---

## 题解清单（≥4星）  
1. **Otue（5星）**  
   - 代码极简，直接使用 `__gcd` 函数，逻辑清晰。  
   - 关键亮点：初始 `ans = k` 巧妙合并了后续 `gcd` 计算。  
   - 代码可读性强，适合快速理解核心逻辑。  

2. **残阳如血（5星）**  
   - 详细数学推导，结合扩展裴蜀定理，解释清晰。  
   - 代码规范，变量命名明确，便于教学使用。  

3. **Infinity_Fantasy（4星）**  
   - 思路简明，代码简短，直接输出倍数序列。  
   - 代码中 `ans` 递增生成结果，直观体现余数生成过程。  

---

## 最优思路与技巧提炼  
**核心实现逻辑**：  
```cpp  
int d = k;  
for (int x : a) d = gcd(d, x);  
int count = k / d;  
for (int i = 0; i < count; i++) cout << i * d << " ";  
```  
**技巧总结**：  
- **初始值优化**：将 `d` 初始化为 `k`，通过遍历数组直接计算 `gcd(gcd(a), k)`。  
- **倍数生成**：直接输出 `0, d, 2d, ...` 避免复杂数学运算，保证结果有序且唯一。  

---

## 同类型题与算法套路  
**类似题目特征**：  
- 涉及线性组合的可能结果（如硬币问题、数论余数问题）。  
- 需要利用 `gcd` 或裴蜀定理分析解的数学性质。  

**通用解法**：  
1. 将问题转化为求线性组合的数学性质（如模余、最小正解）。  
2. 计算相关数的 `gcd` 并推导解的分布规律。  

---

## 推荐相似题目  
1. **P3951 小凯的疑惑**：求无法用两个互质数组合的最大正整数。  
2. **P4549 裴蜀定理**：直接应用裴蜀定理的模板题。  
3. **CF577B Modulo Sum**：动态规划与模运算组合问题。  

---

## 个人心得摘录  
- **BLUESKY007**：提到小凯的疑惑问题，启发将组合问题与 `gcd` 关联。  
- **hzoi_Shadow**：强调 `exgcd` 的扩展应用，深化对模方程的理解。  

---

## 代码实现（核心逻辑）  
```cpp  
#include <bits/stdc++.h>  
using namespace std;  

int main() {  
    int n, k;  
    cin >> n >> k;  
    int d = k;  
    for (int i = 0; i < n; i++) {  
        int x;  
        cin >> x;  
        d = __gcd(d, x);  
    }  
    cout << k / d << "\n";  
    for (int i = 0; i < k / d; i++) {  
        cout << i * d << " ";  
    }  
    return 0;  
}  
```  

---

## 可视化与复古游戏化设计  
**像素动画流程**：  
1. **初始化阶段**：  
   - Canvas 绘制 `k` 进制轮盘，初始全灰。  
   - 数组元素以像素方块形式排列，点击后显示计算 `gcd` 过程。  
2. **计算阶段**：  
   - 每次计算 `gcd(d, a[i])` 时，高亮当前元素并播放 "beep" 音效。  
   - 动态更新轮盘上的有效余数，用绿色方块填充。  
3. **结果展示**：  
   - 所有有效余数以闪烁效果标记，背景播放 8-bit 胜利音乐。  

**交互功能**：  
- **速度调节**：滑动条控制计算步频（慢速观察或快速完成）。  
- **AI 模式**：自动按最优路径生成结果，模拟“AI解题”过程。  

**音效设计**：  
- `gcd` 计算成功：短促 "beep"。  
- 余数生成：音调递增（类似超级马里奥金币声）。  
- 完成所有计算：经典 FC 过关音乐。

---
处理用时：99.92秒