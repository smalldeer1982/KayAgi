# 题目信息

# Nikita and string

## 题目描述

One day Nikita found the string containing letters "a" and "b" only.

Nikita thinks that string is beautiful if it can be cut into $ 3 $ strings (possibly empty) without changing the order of the letters, where the $ 1 $ -st and the $ 3 $ -rd one contain only letters "a" and the $ 2 $ -nd contains only letters "b".

Nikita wants to make the string beautiful by removing some (possibly none) of its characters, but without changing their order. What is the maximum length of the string he can get?

## 说明/提示

It the first sample the string is already beautiful.

In the second sample he needs to delete one of "b" to make it beautiful.

## 样例 #1

### 输入

```
abba
```

### 输出

```
4```

## 样例 #2

### 输入

```
bab
```

### 输出

```
2```

# AI分析结果



### 题目中文翻译
#### 题目名称：Nikita 和字符串

**题目描述**  
某天，Nikita 发现了一个仅包含字母 "a" 和 "b" 的字符串。  
Nikita 认为，一个字符串是美丽的，当且仅当它可以被切割为 3 个字符串（可以是空的）且不改变原有字母顺序，其中第 1 个和第 3 个字符串仅包含 "a"，第 2 个仅包含 "b"。  
Nikita 希望通过删除一些字符（可以不删除）使得字符串变得美丽，同时保留原有字符顺序。求能得到的美丽字符串的最大长度。

**说明/提示**  
第一个样例中字符串已经是美丽的。  
第二个样例需要删除一个 "b" 使其美丽。

**样例 #1**  
输入：`abba`  
输出：`4`

**样例 #2**  
输入：`bab`  
输出：`2`

---

### 算法分类  
动态规划

---

### 题解分析与结论  

#### 核心思路  
所有题解均采用动态规划思想，通过维护多个状态表示字符串分割到不同阶段时的最大长度。状态设计的关键在于：  
- **状态划分**：将字符串分割为三段（全a段、全b段、全a段），每个状态表示当前处于哪个阶段。  
- **状态转移**：根据当前字符是 'a' 或 'b'，决定是否能延长当前阶段或转移到下一阶段。  
- **空间优化**：通过滚动数组或变量复用，将空间复杂度优化至 O(1)。

#### 最优解法关键技巧  
1. **三状态变量法**：维护三个变量 `a, ab, aba`（或 `dp0, dp1, dp2`），分别表示：  
   - `a`：仅包含第一段（全a）的最大长度。  
   - `ab`：包含第一段和第二段（全a+全b）的最大长度。  
   - `aba`：完整三段（全a+全b+全a）的最大长度。  
2. **转移顺序调整**：更新状态时需按 `aba → ab → a` 的逆序进行，避免覆盖未更新的前状态。  
3. **条件叠加**：遇到 'a' 时可同时更新第一段和第三段，遇到 'b' 时更新第二段。

---

### 精选题解  

#### 题解作者：Harry_Hedwig（4星）  
**关键亮点**：  
- 清晰的状态定义与转移方程，详细解释了滚动数组优化时的更新顺序问题。  
- 提供错误代码对比，强调状态依赖顺序的重要性。  
**代码核心**：  
```cpp
int d[5]; // 滚动数组
for(int i=1; i<=n; i++) {
    d[3] = max(d[1], max(d[2], d[3])) + (s[i] == 'a');
    d[2] = max(d[1], d[2]) + (s[i] == 'b');
    d[1] = d[1] + (s[i] == 'a');
}
```

#### 题解作者：Liynw（4星）  
**关键亮点**：  
- 直观的状态命名（`dp0, dp1, dp2`），代码简洁易读。  
- 详细注释说明每个状态的含义及转移逻辑。  
**代码核心**：  
```cpp
int dp[3] = {0}; // dp0, dp1, dp2
for (char c : s) {
    if (c == 'a') {
        dp2 = max({dp0, dp1, dp2}) + 1;
        dp0++;
    } else {
        dp1 = max(dp0, dp1) + 1;
    }
}
```

#### 题解作者：Super_Cube（4星）  
**关键亮点**：  
- 明确状态划分（全a、a+b、a+b+a），提供未优化与滚动数组优化双版本代码。  
- 强调状态转移中的最大值选取逻辑。  
**代码核心**：  
```cpp
int a=0, b=0, c=0;
for (char ch : s) {
    if (ch == 'a') {
        c = max({a, b, c}) + 1;
        a++;
    } else {
        b = max(a, b) + 1;
    }
}
```

---

### 相似题目推荐  
1. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)（动态规划分段处理）  
2. [P1868 饥饿的奶牛](https://www.luogu.com.cn/problem/P1868)（区间选择与状态转移）  
3. [P1944 最长括号匹配](https://www.luogu.com.cn/problem/P1944)（结构化字符串处理）

---
处理用时：72.96秒