# 题目信息

# Vile Grasshoppers

## 题目描述

The weather is fine today and hence it's high time to climb the nearby pine and enjoy the landscape.

The pine's trunk includes several branches, located one above another and numbered from $ 2 $ to $ y $ . Some of them (more precise, from $ 2 $ to $ p $ ) are occupied by tiny vile grasshoppers which you're at war with. These grasshoppers are known for their awesome jumping skills: the grasshopper at branch $ x $ can jump to branches ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF937B/e256171e16de0ce2bc4667496d6c5befd611ffc8.png).

Keeping this in mind, you wisely decided to choose such a branch that none of the grasshoppers could interrupt you. At the same time you wanna settle as high as possible since the view from up there is simply breathtaking.

In other words, your goal is to find the highest branch that cannot be reached by any of the grasshoppers or report that it's impossible.

## 说明/提示

In the first sample case grasshopper from branch $ 2 $ reaches branches $ 2 $ , $ 4 $ and $ 6 $ while branch $ 3 $ is initially settled by another grasshopper. Therefore the answer is $ 5 $ .

It immediately follows that there are no valid branches in second sample case.

## 样例 #1

### 输入

```
3 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 4
```

### 输出

```
-1
```

# AI分析结果



**唯一算法分类**：枚举优化/数学

---

### **题解思路、算法要点与解决难点**

1. **核心思路**  
   所有题解均采用**逆序枚举**从 `y` 到 `p+1` 的每个数 `i`，判断是否存在 `2 ≤ j ≤ min(p, sqrt(i))` 使得 `j` 整除 `i`。若不存在，则 `i` 为答案。

2. **算法要点**  
   - **逆序枚举**：从 `y` 开始向下遍历，确保找到第一个符合条件的数即为最大值。  
   - **因数检查范围优化**：对每个 `i`，只需检查 `2` 到 `min(p, sqrt(i))` 的因数，而非全范围。  
   - **质数间隙理论**：若 `i` 是质数，其与下一个质数的间隔较小（如题解中提到的约300），保证时间复杂度可行。

3. **解决难点**  
   - **时间复杂度**：直接暴力检查 `y` 到 `p+1` 的每个数会超时。通过限制因数检查范围 (`sqrt(i)`) 和利用质数间隙特性，将复杂度优化至 `O(300 * sqrt(y))`。  
   - **边界条件**：需处理 `i ≤ p` 的情况（无解）和 `i` 是质数的特殊情况。

---

### **题解评分 (≥4星)**

1. **作者：hu1029282594 (★★★★☆)**  
   - **亮点**：明确解释质数间隙优化思路，代码简洁，注释清晰。  
   - **代码**：逆序检查+因数范围优化，关键变量 `ok` 标记状态。

2. **作者：Jasper08 (★★★★☆)**  
   - **亮点**：预处理质数（线性筛法），提高检查效率，时间复杂度更优。  
   - **代码**：使用 `bitset` 优化空间，适用于大范围质数预处理。

3. **作者：E1_de5truct0r (★★★★☆)**  
   - **亮点**：详细数学分析（质数间隔、时间复杂度计算），代码逻辑清晰。  
   - **代码**：封装判断函数 `pd`，增强可读性。

---

### **最优思路或技巧提炼**

1. **逆序枚举**：从 `y` 向下遍历，保证找到第一个解即为最大值。  
2. **因数检查优化**：仅检查 `2` 到 `min(p, sqrt(i))` 的因数，减少冗余计算。  
3. **质数间隙理论**：实际运行中，相邻质数的间隔远小于理论最大值，确保时间效率。  
4. **预处理质数**：先筛出 `2` 到 `sqrt(y)` 的质数，加速后续检查（如Jasper08的解法）。

---

### **同类型题或类似算法套路**

1. **最大不可达数**：如[CF1228C](https://codeforces.com/problemset/problem/1228/C)（质因数分解+容斥）。  
2. **质数判断优化**：如洛谷P3383（线性筛法模板题）。  
3. **因数分解优化**：如LeetCode 952（基于因数分解的并查集）。

---

### **推荐洛谷题目**

1. **P3383** 【模板】线性筛素数  
   - 练习质数筛法，理解预处理优化。  
2. **P1217** [USACO1.5]回文质数  
   - 结合质数判断与回文数生成，强化枚举优化能力。  
3. **P3912** 素数个数  
   - 大范围质数统计，需使用筛法优化。

---

### **可视化与算法演示**

1. **核心逻辑动画**：  
   - **Canvas 网格**：显示当前检查的数值 `i`（红色方块），逐步左移（`i--`）。  
   - **因数检查**：对每个 `i`，遍历 `j`（绿色方块，范围 `2` 到 `sqrt(i)`），若 `i%j==0`，标记 `i` 为黄色（无效），否则保持红色。  
   - **找到解**：当 `i` 未被标记，变为绿色并闪烁，播放成功音效。  

2. **复古像素风格**：  
   - **颜色**：16色调色板（红色：`#FF0000`，绿色：`#00FF00`，黄色：`#FFFF00`）。  
   - **音效**：使用 `Web Audio API` 播放8位音效（检查因数时短促“滴”声，成功时播放“胜利”旋律）。  

3. **交互设计**：  
   - **步进控制**：按钮支持暂停/继续/单步执行。  
   - **参数输入**：允许用户自定义 `p` 和 `y`，观察算法行为变化。  

---

### **代码片段（核心逻辑）**

```cpp
// 逆序检查 + 因数范围优化（作者：hu1029282594）
for(int i = y; i > p; i--) {
    bool valid = true;
    for(int j = 2; j*j <= i && j <= p; j++) {
        if(i % j == 0) {
            valid = false;
            break;
        }
    }
    if(valid) {
        cout << i;
        return 0;
    }
}
cout << -1;
```

---

### **总结**

本题核心在于通过逆序枚举和数学优化降低时间复杂度，结合质数间隙理论确保实际运行效率。预处理质数（如线性筛法）可进一步提升性能，但非必需。可视化设计需突出关键步骤（因数检查、状态标记），复古像素风格和音效增强学习趣味性。

---
处理用时：68.30秒