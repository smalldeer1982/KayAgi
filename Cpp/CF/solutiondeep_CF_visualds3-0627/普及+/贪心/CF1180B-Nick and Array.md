# 题目信息

# Nick and Array

## 题目描述

Nick had received an awesome array of integers $ a=[a_1, a_2, \dots, a_n] $ as a gift for his $ 5 $ birthday from his mother. He was already going to explore its various properties but after unpacking he was disappointed a lot because the product $ a_1 \cdot a_2 \cdot \dots a_n $ of its elements seemed to him not large enough.

He was ready to throw out the array, but his mother reassured him. She told him, that array would not be spoiled after the following operation: choose any index $ i $ ( $ 1 \le i \le n $ ) and do $ a_i := -a_i - 1 $ .

For example, he can change array $ [3, -1, -4, 1] $ to an array $ [-4, -1, 3, 1] $ after applying this operation to elements with indices $ i=1 $ and $ i=3 $ .

Kolya had immediately understood that sometimes it's possible to increase the product of integers of the array a lot. Now he has decided that he wants to get an array with the maximal possible product of integers using only this operation with its elements (possibly zero, one or more times, as many as he wants), it is not forbidden to do this operation several times for the same index.

Help Kolya and print the array with the maximal possible product of elements $ a_1 \cdot a_2 \cdot \dots a_n $ which can be received using only this operation in some order.

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
4
2 2 2 2
```

### 输出

```
-3 -3 -3 -3 ```

## 样例 #2

### 输入

```
1
0
```

### 输出

```
0 ```

## 样例 #3

### 输入

```
3
-3 -3 2
```

### 输出

```
-3 -3 2 ```

# AI分析结果



### 综合分析与结论

**题目核心**：通过操作将数组元素转换为最大乘积形式。关键在于贪心策略选择每个元素的最优状态（操作0/1次）以最大化绝对值的乘积，并处理奇偶性带来的符号问题。

**核心贪心策略**：
1. **绝对值最大化**：将所有正数转换为负数（操作后绝对值更大）。
2. **符号修正**：当元素个数为奇数时，将绝对值最小的负数转换回正数（减少乘积损失）。

**解决难点**：
- 操作两次等价于不操作，因此每个元素只能选择操作0或1次。
- 奇偶性处理：当n为奇数时需牺牲一个元素的绝对值以换取正乘积。

---

### 题解评分（≥4星）

| 题解作者       | 评分 | 关键亮点                                                                 |
|----------------|------|--------------------------------------------------------------------------|
| wucstdio       | ★★★★★ | 代码简洁，逻辑清晰，直接处理奇偶性，正确记录最小值。                      |
| Fislett        | ★★★★☆ | 思路明确，变量命名稍差（`minn`初始化需注意），但整体逻辑正确。            |
| _Album_        | ★★★★☆ | 详细分析贪心策略，代码可读性高，附带样例推导。                            |

---

### 最优思路与技巧提炼

**关键贪心步骤**：
1. **全部转负数**：对每个正数应用操作，使其绝对值最大化。
2. **奇偶修正**：
   - 若n为偶数，直接输出（偶数个负数乘积为正）。
   - 若n为奇数，将绝对值最大的负数（即最小的`a[i]`）转换回正数。

**实现技巧**：
- **遍历时记录最小值**：在转换后的数组中记录最小值，其绝对值最大。
- **仅转换一次**：在奇数情况下，仅修改一个元素即可最大化整体乘积。

---

### 同类型题与算法套路

**通用贪心模式**：
1. **绝对值最大化优先**：在允许符号调整时优先选择绝对值更大的形式。
2. **奇偶性修正**：通过调整一个元素修正符号问题（如乘积最大化、子数组和优化）。

**类似题目**：
1. **LeetCode 319. Bulb Switcher**：奇偶性影响最终结果。
2. **CF 1343D. Constant Palindrome Sum**：通过调整元素最大化/最小化特定值。
3. **LeetCode 1007. Minimum Domino Rotations**：贪心选择两种可能的最优解。

---

### 推荐练习题

1. **CF 1343D**：调整数组元素使满足条件，涉及奇偶性处理。
2. **LeetCode 1354. Construct Target Array**：逆向贪心与奇偶调整。
3. **Luogu P1106 删数问题**：贪心选择删除策略使剩余数最大。

---

### 个人心得摘录

- **初始值陷阱**：`minn`需初始化为极大负数（如题解Fislett的`minn`初始值应为`INT_MAX`的负数）。
- **转换次数控制**：操作两次等于无操作，因此只需考虑单次操作的可能。
- **样例验证**：样例3的输入处理后保持原样，验证了奇数情况下的正确性。

---

### 核心代码实现

```cpp
// 核心逻辑片段（基于wucstdio的代码）
for (int i = 1; i <= n; i++) {
    if (a[i] >= 0) a[i] = -a[i] - 1; // 转负数
    maxx = min(maxx, a[i]);          // 记录最小值（绝对值最大）
}
if (n & 1) {
    for (int i = 1; i <= n; i++) {
        if (a[i] == maxx) {
            a[i] = -a[i] - 1; // 修正奇数为正数
            break;
        }
    }
}
```

---

### 可视化与算法演示设计

**动画方案**：
1. **像素网格展示**：用Canvas绘制数组元素，正数绿色，负数红色，操作后闪烁显示。
2. **贪心过程**：
   - **步骤1**：所有正数变为负数，颜色由绿转红，播放“转换”音效。
   - **步骤2**：若n为奇数，高亮绝对值最大的负数（颜色加深），转换后变为蓝色，播放“修正”音效。
3. **交互控制**：允许调整n的值，自动生成数组并演示不同情况。

**复古游戏化设计**：
- **8位音效**：转换时播放类似FC游戏的“点击”声，修正时播放升级音效。
- **积分系统**：正确完成贪心步骤获得积分，错误操作扣分。

**AI自动演示**：
- 自动按步骤执行转换，用户可暂停观察中间状态，通过速度滑块控制演示快慢。

---

**可视化示例（伪代码）**：
```javascript
// 模拟贪心过程
function visualizeGreedy(arr) {
    arr.forEach((num, i) => {
        if (num >= 0) {
            highlight(i, 'green');
            playSound('convert');
            arr[i] = -num - 1;
        }
    });
    if (arr.length % 2 === 1) {
        let target = Math.min(...arr);
        let idx = arr.indexOf(target);
        highlight(idx, 'red');
        playSound('adjust');
        arr[idx] = -arr[idx] - 1;
    }
}
```

---
处理用时：70.47秒