# 题目信息

# Fibonacci Strings

## 题目描述

In all schools in Buryatia, in the $ 1 $ class, everyone is told the theory of Fibonacci strings.

"A block is a subsegment of a string where all the letters are the same and are bounded on the left and right by the ends of the string or by letters other than the letters in the block. A string is called a Fibonacci string if, when it is divided into blocks, their lengths in the order they appear in the string form the Fibonacci sequence ( $ f_0 = f_1 = 1 $ , $ f_i = f_{i-2} + f_{i-1} $ ), starting from the zeroth member of this sequence. A string is called semi-Fibonacci if it possible to reorder its letters to get a Fibonacci string."

Burenka decided to enter the Buryat State University, but at the entrance exam she was given a difficult task. She was given a string consisting of the letters of the Buryat alphabet (which contains exactly $ k $ letters), and was asked if the given string is semi-Fibonacci. The string can be very long, so instead of the string, she was given the number of appearances of each letter ( $ c_i $ for the $ i $ -th letter) in that string. Unfortunately, Burenka no longer remembers the theory of Fibonacci strings, so without your help she will not pass the exam.

## 说明/提示

In the first test case, a one-character string is semi-Fibonacci, being itself a Fibonacci string.

In the second test case, a string of two different characters is Fibonacci.

In the third test case, the string "abb" (let the first of the alphabet letter be a, the second letter b) is not a semi-Fibonacci string, since no permutation of its letters ("abb", "bab", and "bba") is a Fibonacci string.

In the fourth test case, two permutations of the letters of the string "abaccac" (the first letter is a, the second letter is b, the third letter is c) are Fibonacci strings — "abaaccc" and "cbccaaa".

## 样例 #1

### 输入

```
6
1
1
2
1 1
2
1 2
3
3 1 3
2
7 5
6
26 8 3 4 13 34```

### 输出

```
YES
YES
NO
YES
NO
YES```

# AI分析结果



### 题目重述
# 斐波那契字符串

## 题目描述

在布里亚特的所有学校中，一年级学生都要学习斐波那契字符串理论。

"块是指字符串中所有字符相同且左右边界为字符串端点或不同字符的子串。当字符串被划分为块时，块的长度按出现顺序构成斐波那契数列（$f_0 = f_1 = 1$，$f_i = f_{i-2} + f_{i-1}$）时，称为斐波那契字符串。若字符串的字母可以重排为斐波那契字符串，则称其为半斐波那契字符串。"

给定包含 $k$ 种字母的字符串中各字母出现次数 $c_i$，判断其是否为半斐波那契字符串。

## 样例 #1

输入输出示例（见原文）

---

### 题解综合分析

#### 核心思路
所有正确解法均需满足两个条件：
1. **总和验证**：总字符数必须是斐波那契前缀和
2. **贪心分配**：从最大的斐波那契数开始，优先用剩余最多的字符填充，避免连续使用同一字符

#### 关键证明
- **必要性**：若总和不满足斐波那契前缀和则直接无解
- **充分性**：贪心策略的正确性基于斐波那契数列的指数增长特性，大数必须匹配大块，否则无法消耗足够字符

---

### 高分题解选评

#### 1. [happy_dengziyue] ⭐⭐⭐⭐⭐（5星）
**亮点**：
- 使用优先队列动态维护最大值
- 逆向遍历斐波那契数列确保大数优先处理
- 严格处理相邻块字符冲突

**代码核心**：
```cpp
priority_queue<long long> q;
for 每次斐波那契数 f[pos]:
    u = q.top(); q.pop();
    if (u < f[pos]) 无解;
    u -= f[pos];
    if (剩余u) 重新入队;
```

#### 2. [Alex_Wei] ⭐⭐⭐⭐⭐（5星）
**亮点**：
- 数学归纳法证明贪心正确性
- 预处理斐波那契数列至足够大项
- 排序优化减少堆操作

**核心逻辑**：
```cpp
sort(c数组);
for 从最大斐波那契数开始倒序:
    c[n] -= f[p];
    if (c[n] <0 || c[n] > c[n-1]) 无解;
    重新排序维护有序性;
```

#### 3. [YBaggio] ⭐⭐⭐⭐（4星）
**亮点**：
- 详细分析贪心策略的数学原理
- 使用带删除标记的优先队列处理相邻冲突
- 直观的测试用例解析

**代码特色**：
```cpp
struct Heap {
    priority_queue<E> q, d;
    void del(E x) { d.push(x); }
    E top() { 同步清理已删除元素 }
};
```

---

### 关键技巧总结

1. **斐波那契前缀和预处理**  
   预先生成斐波那契数列及其前缀和，使用二分查找验证总和合法性。

2. **动态最大值维护**  
   优先队列/排序数组用于快速获取当前最大可用字符数。

3. **相邻块冲突处理**  
   记录前一次使用的字符类型，通过优先队列延迟入队或动态排序避免重复选择。

4. **数学性质运用**  
   利用斐波那契数的黄金分割特性，证明大数必须优先匹配大块，否则剩余字符无法消耗。

---

### 同类题目推荐

1. [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)  
   **考察点**：斐波那契数列递推与大数运算

2. [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)  
   **考察点**：斐波那契数列与数论结合

3. [P3939 数颜色](https://www.luogu.com.cn/problem/P3939)  
   **考察点**：颜色块操作与数据结构维护

---

### 心得摘录

> **来自 [liuzhongrui]**  
> "调试时发现当总和为1时需要特判，否则会错误进入循环。斐波那契数列的边界处理至关重要。"

> **来自 [D2T1]**  
> "最初代码未考虑前缀和验证，导致对`21 1 2 8`这类数据误判。必须首先验证总和合法性，才能进行后续分配。"

> **来自 [codemap]**  
> "回溯法在k较小时可行，但大数据量必须用贪心。算法选择需结合数据规模分析。"

---
处理用时：57.29秒