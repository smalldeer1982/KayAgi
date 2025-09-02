# 题目信息

# Replace by MEX

## 题目描述

You're given an array of $ n $ integers between $ 0 $ and $ n $ inclusive.

In one operation, you can choose any element of the array and replace it by the MEX of the elements of the array (which may change after the operation).

For example, if the current array is $ [0, 2, 2, 1, 4] $ , you can choose the second element and replace it by the MEX of the present elements — $ 3 $ . Array will become $ [0, 3, 2, 1, 4] $ .

You must make the array non-decreasing, using at most $ 2n $ operations.

It can be proven that it is always possible. Please note that you do not have to minimize the number of operations. If there are many solutions, you can print any of them.

 –

An array $ b[1 \ldots n] $ is non-decreasing if and only if $ b_1 \le b_2 \le \ldots \le b_n $ .

The MEX (minimum excluded) of an array is the smallest non-negative integer that does not belong to the array. For instance:

- The MEX of $ [2, 2, 1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3, 1, 0, 1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0, 3, 1, 2] $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the array, but $ 4 $ does not.

It's worth mentioning that the MEX of an array of length $ n $ is always between $ 0 $ and $ n $ inclusive.

## 说明/提示

In the first test case, the array is already non-decreasing ( $ 2       \le 2 \le 3 $ ).

Explanation of the second test case (the element modified by each operation is colored in red):

- $ a = [2, 1, 0] $ ; the initial MEX is $ 3 $ .
- $ a = [2, 1, {\color{red}{3}}] $ ; the new MEX is $ 0 $ .
- $ a = [ {\color{red}{0}} , 1, 3] $ ; the new MEX is $ 2 $ .
- The final array is non-decreasing: $ 0 \le 1 \le 3 $ .

Explanation of the third test case:

- $ a = [0, 7, 3, 1, 3, 7, 7] $ ; the initial MEX is $ 2 $ .
- $ a = [0, {\color{red}{2}}, 3, 1, 3, 7, 7] $ ; the new MEX is $ 4 $ .
- $ a = [0, 2, 3, 1, {\color{red}{4}}, 7, 7] $ ; the new MEX is $ 5 $ .
- $ a = [0, 2, 3, 1, {\color{red}{5}}, 7, 7] $ ; the new MEX is $ 4 $ .
- $ a = [0, 2, 3, {\color{red}{4}}, 5, 7, 7] $ ; the new MEX is $ 1 $ .
- The final array is non-decreasing: $ 0 \le 2 \le 3 \le 4 \le         5 \le 7 \le 7 $ .

## 样例 #1

### 输入

```
5
3
2 2 3
3
2 1 0
7
0 7 3 1 3 7 7
9
2 0 1 1 2 4 4 2 0
9
8 4 7 6 1 2 3 0 5```

### 输出

```
0

2
3 1
4
2 5 5 4
11
3 8 9 7 8 5 9 6 4 1 2
10
1 8 1 9 5 2 4 6 3 7```

# AI分析结果



**唯一算法分类**：构造

---

### **综合分析与结论**

**核心思路**：构造目标数组为 `0,1,2,...,n-1`，通过反复替换 MEX 值实现。每次操作分为两种情况：
1. **MEX ≠ n**：将 `a[MEX]` 设为 MEX，固定该位置。
2. **MEX = n**：破坏当前全包含 `0~n-1` 的状态，将第一个不符合条件的元素替换为 n，触发后续调整。

**解决难点**：
- **操作次数控制**：每个元素最多被修改两次（一次替换为 n，一次修复为正确值），总操作次数 ≤ 2n。
- **MEX= n 的处理**：通过替换一个元素打破僵局，后续通过环状调整修复错误位置。

**可视化设计**：
- **动画方案**：用网格展示数组，每次操作时：
  - 高亮被替换的位置（红色）。
  - 显示当前 MEX 值（蓝色）。
  - 步进显示替换后的数组状态。
- **复古风格**：采用 8-bit 像素风，每次操作播放“滴”声，完成修复时播放胜利音效。
- **交互控制**：允许暂停、单步执行，速度可调，展示 MEX 计算过程和替换逻辑。

---

### **题解清单 (≥4星)**

1. **xxgirlxx（5星）**  
   - **亮点**：分两阶段处理，第一步确保数在 `0~n-1`，第二步环状调整顺序。复杂度 O(n)，清晰高效。
   - **心得**：“每个环多一次操作，但被第一阶段的优化抵消”是核心证明点。

2. **Little_x_starTYJ（4星）**  
   - **亮点**：直接构造目标数组，代码简洁。通过暴力求 MEX 和分类处理实现。
   - **不足**：复杂度 O(n²)，但对小数据足够。

3. **Hisaishi_Kanade（4星）**  
   - **亮点**：代码简洁，逻辑与主流解法一致，适合快速实现。

---

### **核心代码实现**

```cpp
// 示例代码（基于xxgirlxx的思路）
vector<int> solve(vector<int> a) {
    int n = a.size();
    vector<int> ops;
    bool changed = true;
    while (changed) {
        changed = false;
        int mex = computeMex(a); // 计算当前MEX
        if (mex == n) {
            for (int i = 0; i < n; i++) {
                if (a[i] != i) {
                    a[i] = mex;
                    ops.push_back(i+1);
                    changed = true;
                    break;
                }
            }
        } else {
            if (a[mex] != mex) {
                a[mex] = mex;
                ops.push_back(mex+1);
                changed = true;
            }
        }
    }
    return ops;
}
```

---

### **同类型题与算法套路**

- **构造型问题**：通过特定规则构造解，如 CF1348D（构造递增序列）、CF1391D（二进制矩阵调整）。
- **MEX 性质应用**：如 LeetCode 2003 小数组的缺失数。

---

### **推荐题目**

1. **CF1348D** - 构造递增的细菌数量。
2. **CF1391D** - 调整二进制矩阵使其满足条件。
3. **LeetCode 2003** - 利用 MEX 解决子树问题。

---

### **个人心得摘录**

- **xxgirlxx**：“赛时因担心操作次数过多放弃正确思路，教训是仔细证明边界条件。”
- **BzhH**：“环状替换的每个环多一次操作，但总次数仍为线性。”

---

### **可视化与复古游戏化设计**

1. **像素动画**：用 Canvas 绘制数组，每个元素为 16x16 像素块，替换时闪烁红色。
2. **音效**：替换时播放 8-bit “滴”声，完成时播放胜利旋律。
3. **自动演示**：AI 模式逐步执行操作，用户可调整速度或单步观察。
4. **关卡积分**：每完成 n 次操作解锁新关卡，积分根据剩余操作次数计算。

**示例代码（JS 伪代码）**：
```javascript
function drawArray(ctx, a, highlightIdx) {
    a.forEach((num, i) => {
        ctx.fillStyle = (i === highlightIdx) ? '#FF0000' : '#00FF00';
        ctx.fillRect(i*20, 0, 18, 18);
        ctx.fillText(num, i*20 + 5, 12);
    });
}
// 音效触发
function playSound(effect) {
    const audio = new Audio(`sfx/${effect}.wav`);
    audio.play();
}
``` 

---

**总结**：通过构造目标数组和巧妙利用 MEX 性质，结合分阶段处理，可在 2n 次操作内解决问题。可视化设计增强理解，复古风格提升趣味性。

---
处理用时：70.77秒