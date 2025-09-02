# 题目信息

# Curiosity Has No Limits

## 题目描述

When Masha came to math classes today, she saw two integer sequences of length $ n - 1 $ on the blackboard. Let's denote the elements of the first sequence as $ a_i $ ( $ 0 \le a_i \le 3 $ ), and the elements of the second sequence as $ b_i $ ( $ 0 \le b_i \le 3 $ ).

Masha became interested if or not there is an integer sequence of length $ n $ , which elements we will denote as $ t_i $ ( $ 0 \le t_i \le 3 $ ), so that for every $ i $ ( $ 1 \le i \le n - 1 $ ) the following is true:

- $ a_i = t_i | t_{i + 1} $ (where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR)) and
- $ b_i = t_i \& t_{i + 1} $ (where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND)).

The question appeared to be too difficult for Masha, so now she asked you to check whether such a sequence $ t_i $ of length $ n $ exists. If it exists, find such a sequence. If there are multiple such sequences, find any of them.

## 说明/提示

In the first example it's easy to see that the sequence from output satisfies the given conditions:

- $ t_1 | t_2 = (01_2) | (11_2) = (11_2) = 3 = a_1 $ and $ t_1 \& t_2 = (01_2) \& (11_2) = (01_2) = 1 = b_1 $ ;
- $ t_2 | t_3 = (11_2) | (10_2) = (11_2) = 3 = a_2 $ and $ t_2 \& t_3 = (11_2) \& (10_2) = (10_2) = 2 = b_2 $ ;
- $ t_3 | t_4 = (10_2) | (00_2) = (10_2) = 2 = a_3 $ and $ t_3 \& t_4 = (10_2) \& (00_2) = (00_2) = 0 = b_3 $ .

In the second example there is no such sequence.

## 样例 #1

### 输入

```
4
3 3 2
1 2 0
```

### 输出

```
YES
1 3 2 0 ```

## 样例 #2

### 输入

```
3
1 3
3 2
```

### 输出

```
NO```

# AI分析结果



---

**算法分类**：枚举 + 位运算性质

---

### **题解思路与核心难点**

#### **关键思路**
1. **数学推导**：利用 `a_i + b_i = t_i + t_{i+1}`（因为 `a|b + a&b = a + b`），通过已知的 `a` 和 `b` 快速计算后续 `t` 的可能值。
2. **枚举初始值**：`t_1` 的取值只有 `0~3`，枚举每个值并推导整个序列。
3. **条件验证**：即使数学推导出的 `t` 在 `0~3` 范围内，仍需验证 `OR` 和 `AND` 是否与原序列匹配。

#### **解决难点**
- **递推冲突**：推导出的 `t` 可能中途出现矛盾（如 `t_i` 超出范围或验证失败）。
- **剪枝优化**：一旦发现矛盾，立即终止当前枚举，避免无效计算。

---

### **题解评分（≥4星）**

1. **Karry5307 (4.5星)**  
   - **亮点**：利用数学公式快速推导，代码简洁高效，时间复杂度严格 `O(n)`。
   - **代码**：直接计算 `t[j] = a[j] + b[j] - t[j-1]`，验证条件。

2. **StudyingFather (4星)**  
   - **亮点**：与 Karry5307 思路一致，但变量命名更清晰，可读性更强。
   - **代码**：使用布尔标记 `flag` 简化逻辑。

3. **DarkShadow (4星)**  
   - **亮点**：普适性强，未依赖数学推导，直接枚举所有可能的 `t_i`。
   - **缺点**：每个位置需循环 4 次，常数稍大，但可通过时间限制。

---

### **最优思路提炼**
1. **数学公式加速**：利用 `a_i + b_i = t_i + t_{i+1}` 快速推导 `t_{i+1}`。
2. **递推验证法**：枚举初始值，线性推导后续元素，遇到矛盾立即终止。
3. **位运算性质**：`OR` 和 `AND` 的二进制特性限制了 `t` 的取值，使得枚举可行。

---

### **同类型题目**
- **构造相邻约束序列**：如 [CF1294F](https://www.luogu.com.cn/problem/CF1294F)（构造路径约束）。
- **位运算递推**：如 [CF959D](https://www.luogu.com.cn/problem/CF959D)（质因子分解与位运算结合）。
- **枚举初始值**：如 [CF978E](https://www.luogu.com.cn/problem/CF978E)（公交车上的人数约束）。

---

### **代码核心实现**
```cpp
// 以 Karry5307 的代码为例
for (int i=0; i<=3; i++) { // 枚举 t[1]
    t[1] = i;
    bool valid = true;
    for (int j=2; j<=n; j++) {
        t[j] = a[j-1] + b[j-1] - t[j-1]; // 数学推导
        if (t[j]<0 || t[j]>3 || (t[j]|t[j-1])!=a[j-1] || (t[j]&t[j-1])!=b[j-1]) {
            valid = false; break; // 验证失败
        }
    }
    if (valid) { /* 输出答案 */ }
}
```

---

### **可视化与算法演示**
#### **动画设计**
1. **像素风格界面**：用 8-bit 网格显示 `t` 序列，每个单元格显示当前 `t_i` 的值（0~3）。
2. **颜色标记**：
   - **绿色**：已确认正确的 `t_i`。
   - **红色**：当前验证失败的 `t_i`。
   - **黄色**：正在枚举的 `t_1`。
3. **音效**：
   - **成功**：轻快的 8-bit 音效。
   - **失败**：短促的“哔”声。

#### **交互功能**
- **步进控制**：手动点击推进每个 `t_i` 的推导。
- **自动模式**：按固定速度演示所有枚举过程，遇矛盾时自动切换初始值。

---

### **个人心得摘录**
- **Karry5307**：  
  > “比较一眼吧。” —— 强调数学公式的直觉性应用。
- **5G信号塔报装**：  
  > “调试记录：(3) 输出了多次答案，应只需输出一次。” —— 注意输出条件中的“任意解”要求。

---

**总结**：本题通过枚举初始值+数学推导递推，结合位运算验证，高效解决了构造问题。核心在于利用 `OR` 和 `AND` 的数学性质减少枚举量。

---
处理用时：68.94秒