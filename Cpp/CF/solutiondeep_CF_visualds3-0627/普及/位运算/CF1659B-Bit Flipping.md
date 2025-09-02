# 题目信息

# Bit Flipping

## 题目描述

You are given a binary string of length $ n $ . You have exactly $ k $ moves. In one move, you must select a single bit. The state of all bits except that bit will get flipped ( $ 0 $ becomes $ 1 $ , $ 1 $ becomes $ 0 $ ). You need to output the lexicographically largest string that you can get after using all $ k $ moves. Also, output the number of times you will select each bit. If there are multiple ways to do this, you may output any of them.

A binary string $ a $ is lexicographically larger than a binary string $ b $ of the same length, if and only if the following holds:

- in the first position where $ a $ and $ b $ differ, the string $ a $ contains a $ 1 $ , and the string $ b $ contains a $ 0 $ .

## 说明/提示

Here is the explanation for the first testcase. Each step shows how the binary string changes in a move.

- Choose bit $ 1 $ : $ \color{red}{\underline{1}00001} \rightarrow \color{red}{\underline{1}}\color{blue}{11110} $ .
- Choose bit $ 4 $ : $ \color{red}{111\underline{1}10} \rightarrow \color{blue}{000}\color{red}{\underline{1}}\color{blue}{01} $ .
- Choose bit $ 4 $ : $ \color{red}{000\underline{1}01} \rightarrow \color{blue}{111}\color{red}{\underline{1}}\color{blue}{10} $ .

 The final string is $ 111110 $ and this is the lexicographically largest string we can get.

## 样例 #1

### 输入

```
6
6 3
100001
6 4
100011
6 0
000000
6 1
111001
6 11
101100
6 12
001110```

### 输出

```
111110
1 0 0 2 0 0 
111110
0 1 1 1 0 1 
000000
0 0 0 0 0 0 
100110
1 0 0 0 0 0 
111111
1 2 1 3 0 4 
111110
1 1 4 2 0 4```

# AI分析结果



---

## 算法分类
**贪心算法**

---

## 题解分析

### 核心思路与难点
- **核心目标**：构造字典序最大的二进制字符串，每次操作选中一位，其余位翻转。
- **关键观察**：  
  - 两次操作选中两个不同位等价于仅翻转这两个位（其余位翻转两次后复原）。
  - 当 `k` 为奇数时，需预处理一次操作，使剩余操作次数为偶数，再按偶数策略处理。
- **贪心策略**：  
  1. **预处理奇数次操作**：选中最左侧的 `1`，使其保留，其他位翻转，确保高位尽可能多 `1`。
  2. **偶数次操作**：从左到右将 `0` 变为 `1`，每次操作消耗一次 `k`。
  3. **剩余操作**：所有剩余次数作用于最后一位，不影响字典序。

### 题解对比
1. **World_Creater（⭐⭐⭐⭐⭐）**  
   - **亮点**：代码清晰，直接处理奇偶转换，剩余次数集中处理末位。
   - **关键代码**：预处理奇数次后，遍历修改 `0`，剩余次数累加至末位。
2. **Tx_Lcy（⭐⭐⭐⭐）**  
   - **亮点**：动态判断每位是否需要翻转，逻辑紧凑。
   - **关键代码**：根据 `k` 奇偶性逐位决策，剩余次数累加至末位。
3. **Wsy_flying_forever（⭐⭐⭐）**  
   - **亮点**：使用 `flag` 跟踪翻转次数奇偶性，动态维护状态。
   - **关键代码**：结合 `flag` 和 `k` 奇偶性调整每位状态。

---

## 最优思路提炼
1. **奇偶预处理**：若 `k` 为奇数，优先选中最左侧 `1`，确保高位稳定为 `1`。
2. **贪心修改**：从左到右将 `0` 转为 `1`，每次操作消耗 `k`。
3. **剩余处理**：剩余操作次数作用于末位，不影响字典序。

---

## 同类型题推荐
1. **CF 1527C** - 字符串操作与贪心构造。
2. **LeetCode 670. Maximum Swap** - 贪心选择最大字典序。
3. **CF 1373D** - 奇偶性处理与翻转策略。

---

## 可视化设计
### 动画方案
- **颜色标记**：  
  - 红色：当前选中位。  
  - 蓝色：被翻转的位。  
  - 绿色：已处理为 `1` 的高位。
- **像素风格**：  
  - 使用 8-bit 像素字体和网格布局，展示字符串变化。  
  - 每次操作后更新字符串，高亮当前位和翻转位。
- **音效与交互**：  
  - 关键操作触发“哔”声，成功时播放胜利音效。  
  - 支持暂停/步进，速度调节观察细节。

---

## 核心代码（World_Creater）
```cpp
if (k & 1) { // 奇数预处理
    int fi = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            fi = i; ans[i]++; k--; break;
        }
    }
    if (fi == -1) { // 全0时选末位
        ans[n-1]++; k--; fi = n-1;
    }
    for (int i = 0; i < n; i++) { // 翻转其他位
        if (i != fi) s[i] = '1' - s[i] + '0';
    }
}
for (int i = 0; i < n && k > 0; i++) { // 贪心处理0
    if (s[i] == '0') {
        ans[i]++; k--; s[i] = '1';
    }
}
ans[n-1] += k; // 剩余次数给末位
```

---

## 个人心得
- **调试经验**：处理全 `0` 字符串时需特殊处理，确保预处理有效。
- **关键顿悟**：奇数次操作转换为偶数次后，剩余操作可统一处理，简化逻辑。

---
处理用时：175.81秒