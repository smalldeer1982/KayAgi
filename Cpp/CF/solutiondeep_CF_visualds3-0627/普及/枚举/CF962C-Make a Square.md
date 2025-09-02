# 题目信息

# Make a Square

## 题目描述

You are given a positive integer $ n $ , written without leading zeroes (for example, the number 04 is incorrect).

In one operation you can delete any digit of the given integer so that the result remains a positive integer without leading zeros.

Determine the minimum number of operations that you need to consistently apply to the given integer $ n $ to make from it the square of some positive integer or report that it is impossible.

An integer $ x $ is the square of some positive integer if and only if $ x=y^2 $ for some positive integer $ y $ .

## 说明/提示

In the first example we should delete from $ 8314 $ the digits $ 3 $ and $ 4 $ . After that $ 8314 $ become equals to $ 81 $ , which is the square of the integer $ 9 $ .

In the second example the given $ 625 $ is the square of the integer $ 25 $ , so you should not delete anything.

In the third example it is impossible to make the square from $ 333 $ , so the answer is -1.

## 样例 #1

### 输入

```
8314
```

### 输出

```
2
```

## 样例 #2

### 输入

```
625
```

### 输出

```
0
```

## 样例 #3

### 输入

```
333
```

### 输出

```
-1
```

# AI分析结果



# 算法分类  
**枚举与子序列匹配**

---

# 题解思路与难点分析  

## 核心算法流程  
所有题解围绕两个核心方向：  
1. **正向枚举可能的平方数**：从最大可能的平方数开始，检查原数字是否包含该平方数的子序列  
2. **反向生成子序列**：通过 DFS 或全排列生成所有可能的子序列，判断是否为平方数  

### 关键步骤对比  
| 题解方法 | 核心逻辑 | 时间复杂度 | 解决难点 |  
|----------|----------|------------|----------|  
| **GusyNight** | 逆序存储原数字，倒序枚举平方数，双指针匹配子序列 | O(√n × logn) | 逆序存储保证子序列顺序匹配 |  
| **Andy_Li** | DFS 生成所有子序列，剪枝前导零 | O(2^n) | 处理前导零与剪枝优化 |  
| **QianianXY** | 字符串递归生成子序列，避免数值溢出 | O(2^n) | 用字符串代替整型计算 |  

---

# 题解评分  

## ⭐⭐⭐⭐⭐ GusyNight 题解  
- **思路清晰度**：直接枚举平方数，逻辑简洁  
- **代码可读性**：逆序存储与双指针匹配实现高效  
- **优化程度**：时间复杂度最低，适合大范围数据  

## ⭐⭐⭐⭐ ChenJr 题解  
- **思路清晰度**：数位 DFS 思路明确  
- **实践操作**：反转数组处理位数顺序  
- **缺点**：未完全处理前导零边界条件  

## ⭐⭐⭐ RNBWT 题解  
- **亮点**：用数组标记可行位数，避免重复计算  
- **缺点**：代码中部分变量命名不清晰  

---

# 最优思路提炼  
**逆向枚举平方数 + 子序列双指针匹配**  
1. **逆序存储原数字**：将原数字的每一位逆序存入数组（如 8314 → [4,1,3,8]）  
2. **倒序枚举平方数**：从 sqrt(n) 向下枚举 i，计算 i² 并逆序存储其每一位  
3. **双指针匹配**：检查原数字数组是否能按顺序包含平方数的所有位  

---

# 同类型题推荐  
1. **CF914B：Consecutive Subsequence**（最长连续子序列）  
2. **LeetCode 392：Is Subsequence**（基础子序列判断）  
3. **洛谷 P1106：删数问题**（贪心删数策略）  

---

# 可视化算法演示  

## 核心动画设计  
![枚举平方数与双指针匹配](https://i.imgur.com/5lW6yHc.gif)  
1. **原数字分解**：将输入数字按位展开为可拖动的像素方块（如 8,3,1,4）  
2. **平方数枚举**：右侧动态生成当前枚举的平方数（如 9²=81 → 8,1）  
3. **匹配过程**：  
   - 红色高亮原数字当前比较位  
   - 绿色标记已匹配的平方数位  
   - 自动播放时，AI 模拟双指针移动逻辑  

## 复古像素风格实现  
```javascript  
// Canvas 绘制数字方块  
function drawPixelBlock(x, y, value, color) {  
  ctx.fillStyle = color;  
  ctx.fillRect(x*30, y*30, 28, 28);  
  ctx.fillStyle = "#000";  
  ctx.fillText(value, x*30 + 10, y*30 + 20);  
}  

// 音效触发（Web Audio API）  
function playSound(effect) {  
  const osc = audioCtx.createOscillator();  
  osc.frequency.value = effect === 'match' ? 440 : 220;  
  osc.connect(audioCtx.destination);  
  osc.start();  
  osc.stop(audioCtx.currentTime + 0.1);  
}  
```

---

# 关键代码片段  
**GusyNight 题解核心逻辑**  
```cpp  
// 逆序存储原数字  
while(m) a[cnt1++] = m%10, m /= 10;  

// 枚举平方数并匹配  
for(int i = sqrt(n); i >=1; i--){  
    long long x = i*i;  
    // 逆序存储平方数  
    while(x) b[cnt2++] = x%10, x /= 10;  
    // 双指针检查子序列  
    int l = 0;  
    for(int j=0; j<cnt1; j++){  
        if(a[j] == b[l]) l++;  
        if(l == cnt2) break;  
    }  
    if(l == cnt2) return cout << cnt1 - l;  
}  
```

---

# 个人心得摘录  
> "DFS 处理前导零时，若第一个保留的数字为 0 必须跳过。WA 多次后才意识到需要显式判断 `dig[0] == 0`" —— **QianianXY**  
> "逆序存储平方数的位后，双指针只需顺序扫描原数字，无需考虑顺序混乱" —— **GusyNight**  

---

通过结合逆向枚举与子序列匹配的高效性，以及像素化动画的直观演示，学习者可深入理解如何通过预处理和双指针优化解决此类子序列问题。

---
处理用时：86.54秒