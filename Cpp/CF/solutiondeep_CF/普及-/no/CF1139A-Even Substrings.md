# 题目信息

# Even Substrings

## 题目描述

You are given a string $ s=s_1s_2\dots s_n $ of length $ n $ , which only contains digits $ 1 $ , $ 2 $ , ..., $ 9 $ .

A substring $ s[l \dots r] $ of $ s $ is a string $ s_l s_{l + 1} s_{l + 2} \ldots s_r $ . A substring $ s[l \dots r] $ of $ s $ is called even if the number represented by it is even.

Find the number of even substrings of $ s $ . Note, that even if some substrings are equal as strings, but have different $ l $ and $ r $ , they are counted as different substrings.

## 说明/提示

In the first example, the $ [l, r] $ pairs corresponding to even substrings are:

- $ s[1 \dots 2] $
- $ s[2 \dots 2] $
- $ s[1 \dots 4] $
- $ s[2 \dots 4] $
- $ s[3 \dots 4] $
- $ s[4 \dots 4] $

In the second example, all $ 10 $ substrings of $ s $ are even substrings. Note, that while substrings $ s[1 \dots 1] $ and $ s[2 \dots 2] $ both define the substring "2", they are still counted as different substrings.

## 样例 #1

### 输入

```
4
1234
```

### 输出

```
6```

## 样例 #2

### 输入

```
4
2244
```

### 输出

```
10```

# AI分析结果



# Even Substrings 题解分析

**题目重述**  
给定一个仅由数字 1-9 构成的字符串 $s$，求所有数值为偶数的子串数量。子串由起始和终止位置唯一确定，即使内容相同但位置不同也视为不同子串。

**算法分类**  
字符串、数学

---

## 题解对比与结论

### 核心思路
所有题解均基于关键观察：**子串为偶数当且仅当其末位为偶数**。遍历字符串，对每个偶数字符，累加其位置索引值（从 1 开始）到答案中。例如，字符串 `1234` 中，位置 2 的 '2' 贡献 2 个子串，位置 4 的 '4' 贡献 4 个子串，总计 6 个。

### 最优题解推荐

1. **Ptilopsis_w（5 星）**  
   **亮点**：代码极简，直接逐字符判断奇偶，利用字符 ASCII 特性省去类型转换，逻辑清晰无冗余。  
   **核心代码**：
   ```cpp
   for(int i = 1; i <= n; i++) {
       char ch = getchar();
       if(ch % 2 == 0) ans += i;
   }
   ```

2. **Meteorshower_Y（4 星）**  
   **亮点**：详细解析索引转换（0-based 到 1-based），代码可读性强，适合初学者理解。  
   **核心代码**：
   ```cpp
   for(int i = 0; i < n; i++) {
       if((s[i] - '0') % 2 == 0) ans += i + 1;
   }
   ```

3. **wfycsw（4 星）**  
   **亮点**：输入处理优化（`scanf("%1d", &x)` 直接读取单数字），减少字符转换步骤。  
   **核心代码**：
   ```cpp
   scanf("%1d", &x);
   if(!(x & 1)) ans += i;
   ```

### 关键技巧总结
- **末位判断法**：利用偶数的数学特性，避免遍历所有子串，复杂度从 $O(n^2)$ 优化至 $O(n)$。
- **索引累加**：每个偶数字符贡献其位置值，直接求和。
- **字符处理优化**：直接通过 ASCII 值取模判断奇偶，省去显式类型转换。

---

## 拓展与相似题目
1. **CF1367B - Even Array**  
   链接：https://www.luogu.com.cn/problem/CF1367B  
   考察点：偶数位置与数值的匹配。

2. **P2671 [NOIP2015 普及组] 求和**  
   链接：https://www.luogu.com.cn/problem/P2671  
   考察点：位置奇偶性与数值特征的组合统计。

3. **AT1219 歴史の研究**  
   链接：https://www.luogu.com.cn/problem/AT1219  
   考察点：滑动窗口与位置贡献分析（需结合莫队算法）。

---
处理用时：55.45秒