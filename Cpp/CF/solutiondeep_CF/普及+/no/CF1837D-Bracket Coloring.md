# 题目信息

# Bracket Coloring

## 题目描述

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example:

- the bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)");
- the bracket sequences ")(", "(" and ")" are not.

A bracket sequence is called beautiful if one of the following conditions is satisfied:

- it is a regular bracket sequence;
- if the order of the characters in this sequence is reversed, it becomes a regular bracket sequence.

For example, the bracket sequences "()()", "(())", ")))(((", "))()((" are beautiful.

You are given a bracket sequence $ s $ . You have to color it in such a way that:

- every bracket is colored into one color;
- for every color, there is at least one bracket colored into that color;
- for every color, if you write down the sequence of brackets having that color in the order they appear, you will get a beautiful bracket sequence.

Color the given bracket sequence $ s $ into the minimum number of colors according to these constraints, or report that it is impossible.

## 样例 #1

### 输入

```
4
8
((())))(
4
(())
4
))((
3
(()```

### 输出

```
2
2 2 2 1 2 2 2 1
1
1 1 1 1
1
1 1 1 1
-1```

# AI分析结果

### 题目重写
#### 括号染色

##### 题目描述

一个正则括号序列是指可以通过在原序列的字符之间插入字符“1”和“+”来转换为正确算术表达式的括号序列。例如：

- 括号序列 "()()" 和 "(())" 是正则的（转换后的表达式为："(1)+(1)" 和 "((1+1)+1)"）；
- 括号序列 ")(", "(" 和 ")" 不是正则的。

一个括号序列被称为优美的，如果满足以下条件之一：

- 它是一个正则括号序列；
- 如果将该序列的字符顺序反转，它成为一个正则括号序列。

例如，括号序列 "()()", "(())", ")))(((", "))()((" 都是优美的。

给定一个括号序列 $ s $，你需要对其进行染色，满足以下条件：

- 每个括号都被染成一种颜色；
- 每种颜色至少有一个括号被染成该颜色；
- 对于每种颜色，如果按照它们在序列中出现的顺序写下该颜色的括号，得到的序列是一个优美的括号序列。

根据这些约束，将给定的括号序列 $ s $ 染成最少数量的颜色，或者报告这是不可能的。

##### 样例 #1

###### 输入

```
4
8
((())))(
4
(())
4
))((
3
(()
```

###### 输出

```
2
2 2 2 1 2 2 2 1
1
1 1 1 1
1
1 1 1 1
-1
```

### 算法分类
贪心、字符串

### 题解分析与结论
本题的核心在于如何将括号序列划分为最少的优美子序列。各题解的主要思路是通过前缀和或栈来划分括号序列，确保每个子序列满足优美条件。以下是对各题解的要点总结：

1. **前缀和法**：通过计算前缀和，将序列划分为两组，分别满足不同的优美条件。这种方法简洁且高效，适用于大多数情况。
2. **栈法**：使用两个栈分别存储左括号和右括号，通过匹配括号来划分序列。这种方法直观且易于理解，但实现稍复杂。
3. **直接划分法**：将序列直接划分为前半部分和后半部分，分别处理。这种方法简单但不够通用，适用于特定情况。

### 高星题解
#### 题解1：igAC (5星)
**关键亮点**：
- 使用前缀和划分序列，思路清晰且代码简洁。
- 通过判断前缀和的正负来分配颜色，确保每个子序列满足优美条件。

**核心代码**：
```cpp
for(int i=1;i<=n;++i) printf((sum[i]<0 || sum[i-1]<0)?"1 ":"2 ");
```

#### 题解2：strcmp (4星)
**关键亮点**：
- 详细证明了最少子序列数不超过2，并通过前缀和划分序列。
- 提供了对划分策略的合法性证明，增强了理解。

**核心代码**：
```cpp
for(int i=1;i<=n;++i) printf((sum[i]<0 || sum[i-1]<0)?"1 ":"2 ");
```

#### 题解3：hanjinghao (4星)
**关键亮点**：
- 使用两个栈分别存储左括号和右括号，通过匹配括号来划分序列。
- 提供了对栈法的详细解释，适合理解栈的使用。

**核心代码**：
```cpp
if (s[i] == '(') {
    if (cnt[1]) ans[i] = ans[st[cnt[1]--][1]] = 2;
    else st[++cnt[0]][0] = i;
} else {
    if (cnt[0]) ans[i] = ans[st[cnt[0]--][0]] = 1;
    else st[++cnt[1]][1] = i;
}
```

### 最优关键思路
使用前缀和划分序列是最简洁高效的方法。通过计算前缀和，判断每个位置的前缀和是否小于0，从而决定将其分配到哪个组。这种方法不仅代码简洁，而且时间复杂度低，适用于大规模数据处理。

### 拓展思路
类似的问题可以通过前缀和或栈来解决，特别是在处理括号匹配、序列划分等问题时。可以尝试将这种思路应用到其他字符串处理问题中，如最长有效括号子序列等。

### 推荐题目
1. [P1042 最长有效括号](https://www.luogu.com.cn/problem/P1042)
2. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
3. [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)

---
处理用时：39.50秒