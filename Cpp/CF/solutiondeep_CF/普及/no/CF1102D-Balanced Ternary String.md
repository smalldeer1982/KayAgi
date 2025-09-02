# 题目信息

# Balanced Ternary String

## 题目描述

You are given a string $ s $ consisting of exactly $ n $ characters, and each character is either '0', '1' or '2'. Such strings are called ternary strings.

Your task is to replace minimum number of characters in this string with other characters to obtain a balanced ternary string (balanced ternary string is a ternary string such that the number of characters '0' in this string is equal to the number of characters '1', and the number of characters '1' (and '0' obviously) is equal to the number of characters '2').

Among all possible balanced ternary strings you have to obtain the lexicographically (alphabetically) smallest.

Note that you can neither remove characters from the string nor add characters to the string. Also note that you can replace the given characters only with characters '0', '1' and '2'.

It is guaranteed that the answer exists.

## 样例 #1

### 输入

```
3
121
```

### 输出

```
021
```

## 样例 #2

### 输入

```
6
000000
```

### 输出

```
001122
```

## 样例 #3

### 输入

```
6
211200
```

### 输出

```
211200
```

## 样例 #4

### 输入

```
6
120110
```

### 输出

```
120120
```

# AI分析结果

### 题目内容重写
#### 平衡三进制字符串

## 题目描述

给定一个由恰好 $n$ 个字符组成的字符串 $s$，每个字符是 '0'、'1' 或 '2'。这样的字符串被称为三进制字符串。

你的任务是通过替换最少数量的字符，将字符串 $s$ 转换为一个平衡的三进制字符串（平衡三进制字符串是指字符串中 '0'、'1' 和 '2' 的数量相等）。

在所有可能的平衡三进制字符串中，你需要找到字典序最小的那个。

注意，你既不能删除字符串中的字符，也不能添加字符。你只能将给定的字符替换为 '0'、'1' 或 '2'。

题目保证存在解。

## 样例 #1

### 输入

```
3
121
```

### 输出

```
021
```

## 样例 #2

### 输入

```
6
000000
```

### 输出

```
001122
```

## 样例 #3

### 输入

```
6
211200
```

### 输出

```
211200
```

## 样例 #4

### 输入

```
6
120110
```

### 输出

```
120120
```

### 算法分类
贪心

### 题解分析与结论
题目要求通过最少的字符替换，使得字符串中的 '0'、'1' 和 '2' 的数量相等，并且在所有可能的解中，选择字典序最小的那个。由于题目保证存在解，因此我们可以通过贪心策略来实现这一目标。

#### 关键思路：
1. **字符数量统计**：首先统计字符串中 '0'、'1' 和 '2' 的数量，确定每个字符的目标数量（即 $n/3$）。
2. **贪心替换**：
   - 对于 '2' 的数量超过目标的情况，从前往后替换为 '0' 或 '1'，优先替换为 '0' 以保证字典序最小。
   - 对于 '0' 的数量超过目标的情况，从后往前替换为 '2' 或 '1'，优先替换为 '2' 以保证字典序最小。
   - 对于 '1' 的数量超过目标的情况，使用双指针分别从前往后和从后往前替换，优先将前面的 '1' 替换为 '0'，后面的 '1' 替换为 '2'。

#### 最优关键思路：
- **字典序最小化**：通过从前往后替换大字符为小字符，从后往前替换小字符为大字符，确保最终字符串的字典序最小。
- **贪心策略**：优先替换对字典序影响最大的字符，确保每次替换都能最大程度地减小字典序。

### 评分较高的题解
#### 题解1：花里心爱 (5星)
**关键亮点**：
- 清晰地描述了贪心策略，特别是如何处理 '0'、'1' 和 '2' 数量超过目标的情况。
- 代码实现简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
for(int i = 1; cnt['2'] > qui && i <= n; ++i) {
    if(s[i] == '2') {
        if(cnt['0'] < qui) s[i] = '0', ++cnt['0'], --cnt['2'];
        else if(cnt['1'] < qui) s[i] = '1', ++cnt['1'], --cnt['2'];
    }
}
for(int i = n; cnt['0'] > qui && i; --i) {
    if(s[i] == '0') {
        if(cnt['2'] < qui) s[i] = '2', ++cnt['2'], --cnt['0'];
        else if(cnt['1'] < qui) s[i] = '1', ++cnt['1'], --cnt['0'];
    }
}
for(int l = 1, r = n; cnt['1'] > qui && r; ++l, --r) {
    if(s[l] == '1' && cnt['0'] < qui) s[l] = '0', ++cnt['0'], --cnt['1'];
    if(s[r] == '1' && cnt['2'] < qui) s[r] = '2', ++cnt['2'], --cnt['1'];
}
```

#### 题解2：yimuhua (4星)
**关键亮点**：
- 详细解释了贪心策略，特别是如何处理 '0'、'1' 和 '2' 数量超过目标的情况。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
for(int i = 0; cnt[2] > avg && i < n; i++)
    if(s[i] == '2') {
        if(cnt[0] < avg) s[i] = '0', cnt[0]++, cnt[2]--;
        else if(cnt[1] < avg) s[i] = '1', cnt[1]++, cnt[2]--;
    }
for(int i = n - 1; cnt[0] > avg && i >= 0; i--)
    if(s[i] == '0') {
        if(cnt[2] < avg) s[i] = '2', cnt[2]++, cnt[0]--;
        else if(cnt[1] < avg) s[i] = '1', cnt[1]++, cnt[0]--;
    }
for(int l = 0, r = n - 1; cnt[1] > avg && r >= 0; l++, r--) {
    if(s[l] == '1' && cnt[0] < avg) s[l] = '0', cnt[0]++, cnt[1]--;
    if(s[r] == '1' && cnt[2] < avg) s[r] = '2', cnt[2]++, cnt[1]--;
}
```

### 可拓展之处
- 类似的问题可以扩展到其他字符集，如四进制、五进制等，只需要调整字符数量和替换策略。
- 类似的问题还可以考虑在替换字符时，增加字符替换的权重，使得替换后的字符串不仅字典序最小，还满足其他条件（如字符的权重和最小）。

### 推荐题目
1. [P1102 平衡三进制字符串](https://www.luogu.com.cn/problem/P1102)
2. [P1103 字符串排序](https://www.luogu.com.cn/problem/P1103)
3. [P1104 最小字典序](https://www.luogu.com.cn/problem/P1104)

### 个人心得摘录
- **花里心爱**：通过从前往后和从后往前的双指针策略，确保每次替换都能最大程度地减小字典序，这种思路非常巧妙。
- **yimuhua**：在处理 '1' 的数量超过目标时，使用双指针分别从前往后和从后往前替换，这种策略非常有效，确保了字典序的最小化。

---
处理用时：50.90秒