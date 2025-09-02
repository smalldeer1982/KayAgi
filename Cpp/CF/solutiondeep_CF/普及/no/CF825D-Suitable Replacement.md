# 题目信息

# Suitable Replacement

## 题目描述

You are given two strings $ s $ and $ t $ consisting of small Latin letters, string $ s $ can also contain '?' characters.

Suitability of string $ s $ is calculated by following metric:

Any two letters can be swapped positions, these operations can be performed arbitrary number of times over any pair of positions. Among all resulting strings $ s $ , you choose the one with the largest number of non-intersecting occurrences of string $ t $ . Suitability is this number of occurrences.

You should replace all '?' characters with small Latin letters in such a way that the suitability of string $ s $ is maximal.

## 说明/提示

In the first example string "baab" can be transformed to "abab" with swaps, this one has suitability of 2. That means that string "baab" also has suitability of 2.

In the second example maximal suitability you can achieve is 1 and there are several dozens of such strings, "azbz" is just one of them.

In the third example there are no '?' characters and the suitability of the string is 0.

## 样例 #1

### 输入

```
?aa?
ab
```

### 输出

```
baab
```

## 样例 #2

### 输入

```
??b?
za
```

### 输出

```
azbz
```

## 样例 #3

### 输入

```
abcd
abacaba
```

### 输出

```
abcd
```

# AI分析结果



### 题目内容中文重写
#### 题目名称：合适替换

**题目描述**  
给定两个由小写拉丁字母组成的字符串 $s$ 和 $t$，其中 $s$ 可能包含字符 '?'。  
字符串 $s$ 的适配度定义为：通过任意次交换字符位置后，能够得到的非重叠子串 $t$ 的最大数量。你的任务是将所有 '?' 替换为小写字母，使得适配度最大化。  

**样例与提示**  
- 样例1说明：替换后的 "baab" 可调整为 "abab"，适配度为2。  
- 样例2说明：最大适配度为1，如替换为 "azbz"。  
- 样例3说明：无 '?' 且适配度为0。  

---

### 算法分类
**二分**

---

### 题解分析与结论
#### 核心思路对比
1. **二分法（RE_Prince、_liuyi_）**  
   - **核心步骤**：  
     - 统计 $s$ 中各字符数量（排除 '?'）和 '?' 的总数。  
     - 统计 $t$ 中各字符的需求量。  
     - 二分查找最大可能的适配度 $x$，检查替换后的字符是否满足 $x$ 倍的需求。  
     - 构造答案时，优先填补缺口最大的字符。  
   - **亮点**：  
     - 通过二分确定最大可行 $x$，确保全局最优。  
     - 构造时按需填充，避免浪费 '?'。  

2. **贪心法（luo_shen）**  
   - **思路**：每次将 '?' 替换为当前最缺的字符（根据字符需求比例）。  
   - **问题**：无法保证全局最优，例如当多个字符需求平衡时，局部贪心可能失效。  

---

### 高星题解推荐
#### 1. RE_Prince 的题解（4.5星）
**亮点**  
- 使用 `unordered_map` 统计字符，代码直观。  
- 二分边界优化（初始右边界设为 $\lceil 10^6/|t| \rceil$），提升效率。  

**核心代码**  
```cpp
bool check(int x) {
    int ret = cnt; // cnt为'?'总数
    for (char c = 'a'; c <= 'z'; c++) {
        int need = mp[c] * x; // mp为t中各字符的需求量
        if (p2[c] < need) ret -= (need - p2[c]);
        if (ret < 0) return false;
    }
    return true;
}
// 构造答案时，遍历并填补缺口字符
```

#### 2. _liuyi_ 的题解（4.5星）
**亮点**  
- 数组存储字符统计，提高效率。  
- 代码简洁，直接计算缺口后构造答案。  

**核心代码**  
```cpp
bool check(int x) {
    ll tmp = cnt;
    for (int i = 0; i < 26; i++) {
        tmp -= max(pos[i] * x - num[i], 0LL);
    }
    return tmp >= 0;
}
// 构造答案时按需填充剩余缺口
```

---

### 关键思路与技巧
1. **二分法的应用**：  
   - 当问题满足单调性（若 $x$ 可行，则所有 $x' \leq x$ 均可行）时，二分是高效工具。  
   - 通过统计字符缺口，将问题转化为可行性判断。  

2. **构造策略**：  
   - 替换 '?' 时优先填补缺口最大的字符，确保每个字符的实际数量满足需求。  

---

### 类似题目推荐
1. **P4344 [SHOI2015] 脑洞治疗仪**（二分答案）  
2. **P2218 [HAOI2007] 覆盖问题**（二分+几何覆盖判断）  
3. **CF371C Hamburgers**（二分确定最大汉堡数量）  

---

### 题解中的个人心得
- **RE_Prince**：通过优化二分边界减少无效计算。  
- **_liuyi_**：强调 `long long` 的使用，避免整数溢出。  
- **luo_shen**：尝试通过动态调整缺口但未考虑全局平衡，提醒需谨慎验证贪心策略的正确性。

---
处理用时：290.74秒