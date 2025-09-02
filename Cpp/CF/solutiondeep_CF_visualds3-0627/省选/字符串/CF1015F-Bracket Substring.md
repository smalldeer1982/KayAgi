# 题目信息

# Bracket Substring

## 题目描述

You are given a bracket sequence $ s $ (not necessarily a regular one). A bracket sequence is a string containing only characters '(' and ')'.

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters '1' and '+' between the original characters of the sequence. For example, bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)"), and ")(", "(" and ")" are not.

Your problem is to calculate the number of regular bracket sequences of length $ 2n $ containing the given bracket sequence $ s $ as a substring (consecutive sequence of characters) modulo $ 10^9+7 $ ( $ 1000000007 $ ).

## 说明/提示

All regular bracket sequences satisfying the conditions above for the first example:

- "(((()))())";
- "((()()))()";
- "((()))()()";
- "(()(()))()";
- "()((()))()".

All regular bracket sequences satisfying the conditions above for the second example:

- "((()))";
- "(()())";
- "(())()";
- "()(())".

And there is no regular bracket sequences of length $ 4 $ containing "(((" as a substring in the third example.

## 样例 #1

### 输入

```
5
()))()
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3
(()
```

### 输出

```
4
```

## 样例 #3

### 输入

```
2
(((
```

### 输出

```
0
```

# AI分析结果



### 唯一算法分类
**动态规划（DP）结合 KMP 字符串匹配**

---

### 题解思路与算法要点

#### 核心思路
1. **状态设计**：使用三维动态规划 `dp[i][j][k]` 表示：
   - `i`：已填充的括号数量
   - `j`：当前括号平衡值（左括号数 - 右括号数）
   - `k`：当前与目标字符串 `s` 的匹配进度（即已匹配到 `s` 的第 `k` 位）
2. **转移逻辑**：每次填充一个括号（'(' 或 ')'），根据 KMP 预处理结果更新匹配进度 `k`，并确保括号平衡值始终非负。
3. **KMP 预处理**：利用 KMP 的 `next` 数组预处理每个匹配位置 `k` 在填入新字符后的转移位置，避免暴力回溯。

#### 解决难点
- **子串匹配的高效处理**：通过 KMP 预处理 `g[k][0/1]`（`0` 表示填入')'，`1` 表示填入'('），快速确定新的匹配进度。
- **合法序列的保证**：在 DP 转移时，维护括号平衡值 `j` 始终非负，且最终为 0。

---

### 最优思路提炼
1. **KMP 预处理**：预计算每个匹配位置 `k` 在填入不同字符后的转移位置，时间复杂度 O(m)。
2. **状态压缩**：通过三维 DP 状态，将字符串匹配进度与括号合法性统一维护。
3. **边界处理**：当完全匹配 `s` 后，后续填充不影响匹配状态（直接保持 `k = m`）。

---

### 关键代码实现（以题解1为例）
```cpp
// KMP预处理转移数组
void KMP() {
    int j = nxt[1] = 0;
    for (int i = 2; i <= m; i++) {
        while (j && s[i] != s[j+1]) j = nxt[j];
        if (s[i] == s[j+1]) j++;
        nxt[i] = j;
    }
    for (int i = 0; i < m; i++) {
        int k = i, p = i;
        while (k && s[k+1] != '(') k = nxt[k];
        while (p && s[p+1] != ')') p = nxt[p];
        if (s[k+1] == '(') k++;
        if (s[p+1] == ')') p++;
        g[i][1] = k, g[i][0] = p;
    }
}

// DP转移核心
for (int i = 0; i < al; i++) {
    for (int j = 0; j <= n; j++) {
        for (int k = 0; k <= m; k++) {
            ll t = f[i][j][k];
            if (j) add(f[i+1][j-1][g[k][0]], t); // 填入')'
            add(f[i+1][j+1][g[k][1]], t);        // 填入'('
        }
    }
}
```

---

### 可视化设计要点
1. **动态规划状态转移动画**：
   - **网格视图**：将三维状态 `(i, j, k)` 投影到 2D 网格，横轴为 `i`，纵轴为 `j`，颜色表示 `k`。
   - **高亮转移路径**：用箭头表示从 `(i,j,k)` 到 `(i+1,j±1, new_k)` 的转移，颜色区分'('和')'。
   - **实时数值显示**：在状态格中显示当前 `dp` 值，颜色深浅表示数值大小。

2. **KMP 回溯过程演示**：
   - **字符流高亮**：展示 `s` 字符串，当前匹配位置 `k` 用红色框标记。
   - **Next 指针跳动**：当匹配失败时，用绿色箭头表示回溯到 `next[k]` 的过程。

3. **复古像素风格**：
   - **8-bit 音效**：每次状态转移时播放 "beep" 音效，完全匹配 `s` 时播放胜利音效。
   - **像素动画**：用 16x16 像素块表示括号，'('为绿色方块，')'为红色方块，组成流动的括号序列。

---

### 类似题目推荐
1. **P3193 [HNOI2008]GT考试**  
   （KMP + DP 统计不包含特定子串的字符串数量）
2. **P3973 [TJOI2015]棋盘**  
   （状态压缩 DP 结合自动机转移）
3. **P4052 [JSOI2007]文本生成器**  
   （AC 自动机 + DP 统计包含至少一个模式串的字符串数）

---

### 个人心得摘录
- **调试陷阱**：完全匹配 `s` 后需保持 `k = m`，否则会重复计数（如题解1中 `g[m][0/1] = m` 的设计）。
- **优化技巧**：预处理所有 `k` 的转移，避免在 DP 转移时实时计算 KMP，显著提升效率。

---

### 算法演示（伪代码）
```javascript
// 初始化Canvas和像素风格
const canvas = initCanvas('retro-style');
const dpGrid = drawGrid(2*n, n); // 行:i, 列:j, 颜色:k

// 自动演示循环
function autoPlay() {
    for (let i = 0; i < 2*n; i++) {
        for (let j = 0; j <= n; j++) {
            for (let k = 0; k <= m; k++) {
                // 高亮当前状态格子
                dpGrid.highlight(i, j, k);
                playSound('beep1'); // 8-bit音效
                // 模拟填入'('和')'的转移
                simulateTransfer(i, j, k, '(');
                simulateTransfer(i, j, k, ')');
            }
        }
    }
}
```

---
处理用时：79.39秒