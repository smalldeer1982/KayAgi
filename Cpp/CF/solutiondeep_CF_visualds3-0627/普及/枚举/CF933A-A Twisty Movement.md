# 题目信息

# A Twisty Movement

## 题目描述

A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.

A performer holding the rod low is represented by a $ 1 $ , while one holding it high is represented by a $ 2 $ . Thus, the line of performers can be represented by a sequence $ a_{1},a_{2},...,a_{n} $ .

Little Tommy is among them. He would like to choose an interval $ [l,r] $ ( $ 1<=l<=r<=n $ ), then reverse $ a_{l},a_{l+1},...,a_{r} $ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.

A non-decreasing subsequence is a sequence of indices $ p_{1},p_{2},...,p_{k} $ , such that $ p_{1}<p_{2}<...<p_{k} $ and $ a_{p1}<=a_{p2}<=...<=a_{pk} $ . The length of the subsequence is $ k $ .

## 说明/提示

In the first example, after reversing $ [2,3] $ , the array will become $ [1,1,2,2] $ , where the length of the longest non-decreasing subsequence is $ 4 $ .

In the second example, after reversing $ [3,7] $ , the array will become $ [1,1,1,1,2,2,2,2,2,1] $ , where the length of the longest non-decreasing subsequence is $ 9 $ .

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10
1 1 2 2 2 1 1 2 2 1
```

### 输出

```
9
```

# AI分析结果



---

**算法分类**：动态规划（四状态线性DP）

---

### **题解分析与结论**
**核心思路**：  
将翻转后的最长非降序列视为由四段组成：`[1...1][2...2][1...1][2...2]`，通过翻转中间两段（第二、三段），合并为`[1...1][1...1][2...2][2...2]`。动态维护四段的最大长度。

**算法要点**：
1. **四状态DP**：`f1`~`f4` 分别表示前四段的最大长度。
2. **状态转移**：
   - `f1`：仅累加当前为1的元素。
   - `f2`：取`f1`（开启第二段）或延续`f2`（当前为2）。
   - `f3`：取`f2`（开启第三段）或延续`f3`（当前为1）。
   - `f4`：取`f3`（开启第四段）或延续`f4`（当前为2）。
3. **时间复杂度**：O(n)，空间复杂度O(1)。

**解决难点**：  
将翻转操作隐式转换为四段结构的动态维护，避免显式枚举所有可能的翻转区间。

---

### **优质题解推荐 (≥4星)**
1. **浅色调 (5星)**  
   - **亮点**：简洁的四状态DP，代码极简，逻辑清晰。
2. **蒟蒻丁 (5星)**  
   - **亮点**：通过示例解释四段结构的形成，易于理解。
3. **gesong (4星)**  
   - **亮点**：详细状态转移方程推导，适合深入理解。

---

### **最优思路提炼**
**关键技巧**：
- **四段模型**：利用序列仅含1/2的特性，将翻转操作转化为四段结构的最优组合。
- **滚动更新**：用一维数组或变量维护状态，避免二维数组的空间开销。
- **转移顺序**：严格按`f1→f2→f3→f4`的顺序更新，确保逻辑正确。

---

### **类似题目推荐**
1. **CF1155D - Beautiful Array**  
   （利用分段DP处理子数组变形问题）
2. **LeetCode 376 - Wiggle Subsequence**  
   （状态机思想处理摆动序列）
3. **洛谷 P1091 合唱队形**  
   （前后缀分解求最长峰形序列）

---

### **核心代码实现**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n, x, f1 = 0, f2 = 0, f3 = 0, f4 = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        f1 += (x == 1);
        f2 = max(f1, f2 + (x == 2));
        f3 = max(f2, f3 + (x == 1));
        f4 = max(f3, f4 + (x == 2));
    }
    cout << f4;
    return 0;
}
```

---

### **可视化设计**
**动画方案**：
1. **像素风格界面**：
   - **网格布局**：每个元素显示为像素方块（1为绿色，2为黄色）。
   - **状态条**：右侧显示四段状态的长度（不同颜色：红、蓝、紫、橙）。
2. **动态更新**：
   - 处理元素时，方块闪烁，显示当前值。
   - 状态条根据转移实时增长，箭头表示转移来源。
3. **音效交互**：
   - **元素处理**：播放“哔”声。
   - **状态更新**：不同状态对应不同音调（如C大调音阶）。
4. **自动演示**：按步执行，速度可调，高亮当前操作元素及状态变化。

**交互示例**：  
![像素动画示意图](https://via.placeholder.com/400x200/000000/FFFFFF/?text=Pixel+Animation+Demo)

---

**总结**：通过四状态DP高效解决问题，结合复古像素动画与音效交互，直观展示算法核心逻辑。

---
处理用时：75.28秒