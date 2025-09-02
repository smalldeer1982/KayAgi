# 题目信息

# Dreamoon and Stairs

## 题目描述

Dreamoon wants to climb up a stair of $ n $ steps. He can climb $ 1 $ or $ 2 $ steps at each move. Dreamoon wants the number of moves to be a multiple of an integer $ m $ .

What is the minimal number of moves making him climb to the top of the stairs that satisfies his condition?

## 说明/提示

For the first sample, Dreamoon could climb in 6 moves with following sequence of steps: {2, 2, 2, 2, 1, 1}.

For the second sample, there are only three valid sequence of steps {2, 1}, {1, 2}, {1, 1, 1} with 2, 2, and 3 steps respectively. All these numbers are not multiples of 5.

## 样例 #1

### 输入

```
10 2
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 5
```

### 输出

```
-1
```

# AI分析结果



---

**唯一算法分类**：暴力枚举

---

### **综合分析与结论**

**核心思路**  
1. **确定步数范围**：  
   - **最小值**：尽可能多走2步，最小步数为 $\lceil \frac{n}{2} \rceil$（n为偶数时为 $\frac{n}{2}$，奇数时为 $\frac{n}{2} + 1$）。  
   - **最大值**：每次走1步，总步数为 $n$。  
2. **暴力枚举**：在区间 $[\lceil \frac{n}{2} \rceil, n]$ 内，从小到大遍历每个整数，检查是否满足 $x \% m = 0$，找到第一个合法解即输出，否则输出 $-1$。  

**难点与解决**  
- **确定合法区间**：通过数学推导得出步数的最小值和最大值，确保所有可能的步数均在此区间内。  
- **暴力效率**：由于 $n \le 10^4$（题目未明确给出，但实际合理数据范围），暴力枚举的复杂度为 $\mathcal{O}(n)$，完全可接受。  

**可视化设计思路**  
1. **动画流程**：  
   - 绘制台阶图示，用像素方块表示当前步数检查（如红色方块表示当前检查的步数，绿色表示合法解）。  
   - 动态显示从最小步数开始逐个尝试，高亮当前步数并标记是否被 $m$ 整除。  
2. **复古游戏化**：  
   - **像素风格**：使用 8-bit 像素风格，台阶用不同颜色块表示，步数变化时伴随经典音效。  
   - **音效提示**：成功时播放上扬音效，失败时播放低沉音效，背景音乐为循环的 8-bit 旋律。  
   - **自动演示**：模拟“贪吃蛇 AI”逐步检查步数，自动播放时可调节速度。  

---

### **题解清单 (≥4星)**

1. **作者：ahawzlc（★★★★☆）**  
   - **亮点**：  
     - 逻辑清晰，直接通过奇偶性计算最小步数，避免浮点运算。  
     - 代码简洁，循环遍历区间，无冗余操作。  
   - **代码片段**：  
     ```cpp
     int mn = n / 2 + (n % 2); // 最小步数
     for (int i = mn; i <= n; i++) {
         if (i % m == 0) {
             cout << i << endl;
             return 0;
         }
     }
     ```

2. **作者：Register（★★★★☆）**  
   - **亮点**：  
     - 自定义 `ceil2` 函数处理向上取整，避免依赖数学库。  
     - 代码结构简洁，直接枚举区间。  
   - **代码片段**：  
     ```cpp
     int ceil2(int x) { return x % 2 ? x / 2 + 1 : x / 2; }
     for (int i = ceil2(n); i <= n; i++) {
         if (i % m == 0) { cout << i << endl; return 0; }
     }
     ```

3. **作者：西宋太祖（★★★★☆）**  
   - **亮点**：  
     - 显式处理奇偶性，代码可读性强。  
     - 注释详细，便于理解边界条件。  
   - **代码片段**：  
     ```cpp
     if (n % 2 == 1) f++; // 处理奇数情况
     for (i = f; i <= n; i++) { ... }
     ```

---

### **最优思路或技巧提炼**

1. **数学推导最小步数**：  
   - 通过奇偶性判断，用整数运算替代浮点运算，避免精度问题。  
   - 公式：$\lceil \frac{n}{2} \rceil = \frac{n + 1}{2}$（位运算实现为 `(n + 1) >> 1`）。  

2. **暴力枚举优化**：  
   - 从小到大遍历区间，找到第一个解即终止，保证最小解。  

---

### **同类型题与算法套路**

- **通用解法**：  
  当问题需要寻找满足特定条件的最小整数时，若数据范围允许，暴力枚举是直接有效的方法。  

- **类似题目**：  
  1. **洛谷 P1217** [回文质数](https://www.luogu.com.cn/problem/P1217)：枚举区间内的数，检查回文和质数条件。  
  2. **洛谷 P1088** [火星人](https://www.luogu.com.cn/problem/P1088)：暴力枚举排列。  
  3. **洛谷 P1149** [火柴棒等式](https://www.luogu.com.cn/problem/P1149)：枚举所有可能的数字组合。  

---

### **个人心得摘录**

- **调试教训**：  
  > “注意 `ceil(double(n)/2)` 在 C++ 中需要显式类型转换，否则整数除法会直接截断。” —— Nt_Tsumiki  
- **优化技巧**：  
  > “用位运算 `(n + 1) >> 1` 替代浮点运算，提升效率。” —— 「已注销」  

---

### **核心代码实现**

```cpp
#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int min_steps = (n + 1) / 2; // 计算最小步数
    for (int i = min_steps; i <= n; ++i) {
        if (i % m == 0) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
```

---

### **可视化与算法演示**

**动画方案**：  
1. **像素化台阶**：用 8-bit 风格绘制台阶，当前检查的步数以闪烁方块标记。  
2. **步进高亮**：每步检查时，高亮当前步数并显示余数计算过程（如 `i % m`）。  
3. **音效反馈**：  
   - **合法解**：播放胜利音效（8-bit 上升音阶）。  
   - **无解**：播放失败音效（低沉嗡鸣）。  

**交互设计**：  
- **控制面板**：支持暂停/继续、调整动画速度（快/中/慢）。  
- **自动模式**：AI 自动遍历步数，模拟“寻找最优解”过程。  

**代码片段（JS 伪代码）**：  
```javascript
function visualize(n, m) {
    let current = Math.ceil(n / 2);
    const max = n;
    while (current <= max) {
        highlight(current); // 高亮当前步数
        playSound("step");
        if (current % m === 0) {
            playSound("success");
            return current;
        }
        current++;
    }
    playSound("fail");
    return -1;
}
```

---
处理用时：92.56秒