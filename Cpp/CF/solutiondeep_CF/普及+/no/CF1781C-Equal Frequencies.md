# 题目信息

# Equal Frequencies

## 题目描述

Let's call a string balanced if all characters that are present in it appear the same number of times. For example, "coder", "appall", and "ttttttt" are balanced, while "wowwow" and "codeforces" are not.

You are given a string $ s $ of length $ n $ consisting of lowercase English letters. Find a balanced string $ t $ of the same length $ n $ consisting of lowercase English letters that is different from the string $ s $ in as few positions as possible. In other words, the number of indices $ i $ such that $ s_i \ne t_i $ should be as small as possible.

## 说明/提示

In the first test case, the given string "hello" is not balanced: letters 'h', 'e', and 'o' appear in it once, while letter 'l' appears twice. On the other hand, string "helno" is balanced: five distinct letters are present in it, and each of them appears exactly once. Strings "hello" and "helno" differ in just one position: the fourth character. Other solutions are possible too.

In the second test case, string "codefofced" is balanced since only letters 'c', 'o', 'd', 'e', and 'f' are present in it, and each of them appears exactly twice.

In the third test case, string "eeeee" is balanced since only letter 'e' is present in it.

In the fourth test case, the given string "appall" is already balanced.

## 样例 #1

### 输入

```
4
5
hello
10
codeforces
5
eevee
6
appall```

### 输出

```
1
helno
2
codefofced
1
eeeee
0
appall```

# AI分析结果

### 题目翻译
# 相等频率

## 题目描述

如果一个字符串中所有出现的字符出现的次数相同，则称该字符串是平衡的。例如，"coder"、"appall"和"ttttttt"是平衡的，而"wowwow"和"codeforces"则不是。

给定一个长度为 $n$ 的字符串 $s$，由小写英文字母组成。请找到一个长度为 $n$ 的平衡字符串 $t$，由小写英文字母组成，且与字符串 $s$ 在尽可能少的位置上不同。换句话说，满足 $s_i \ne t_i$ 的索引 $i$ 的数量应尽可能小。

## 说明/提示

在第一个测试用例中，给定的字符串 "hello" 不是平衡的：字母 'h'、'e' 和 'o' 各出现一次，而字母 'l' 出现两次。另一方面，字符串 "helno" 是平衡的：其中出现了五个不同的字母，每个字母恰好出现一次。字符串 "hello" 和 "helno" 仅在一个位置上不同：第四个字符。其他解决方案也是可能的。

在第二个测试用例中，字符串 "codefofced" 是平衡的，因为只有字母 'c'、'o'、'd'、'e' 和 'f' 出现在其中，且每个字母恰好出现两次。

在第三个测试用例中，字符串 "eeeee" 是平衡的，因为只有字母 'e' 出现在其中。

在第四个测试用例中，给定的字符串 "appall" 已经是平衡的。

## 样例 #1

### 输入

```
4
5
hello
10
codeforces
5
eevee
6
appall```

### 输出

```
1
helno
2
codefofced
1
eeeee
0
appall```

### 算法分类
构造、贪心

### 题解分析与结论
该题的核心是通过修改尽可能少的字符，使得字符串中每个字符的出现次数相同。题解主要通过枚举可能的字符种类数，并计算每种情况下需要修改的字符数，最终选择最优解。

### 所选题解
1. **作者：daiarineko (赞：11)**
   - **星级：5**
   - **关键亮点**：通过枚举字符种类数，计算每种情况下的修改次数，并选择最优解。代码清晰，思路明确，且通过排序和贪心策略高效地解决了问题。
   - **核心代码**：
     ```cpp
     for (int used = 1; used <= 26; ++used) {
         if (n % used != 0) continue;
         int m = n / used;
         int now = 0;
         for (int i = 0; i < used; ++i) now += abs(v[i].cnt - m);
         for (int i = used; i < 26; ++i) now += v[i].cnt;
         now /= 2;
         ans = min(ans, now);
         if (ans == now) ansid = used;
     }
     ```
   - **个人心得**：通过枚举和贪心策略，有效地减少了问题的复杂度，且代码实现简洁明了。

2. **作者：ZLCT (赞：0)**
   - **星级：4**
   - **关键亮点**：通过枚举字符种类数，并计算每种情况下的修改次数，最终选择最优解。代码结构清晰，且通过排序和贪心策略高效地解决了问题。
   - **核心代码**：
     ```cpp
     int getans(int x) {
         int res = 0;
         int numone = n / x;
         for (int i = 25; i > 25 - x; --i) {
             if (num[i].times < numone) res += numone - num[i].times;
             else res += num[i].times - numone;
         }
         for (int i = 25 - x; i >= 0; --i) res += num[i].times;
         return res / 2;
     }
     ```
   - **个人心得**：通过枚举和贪心策略，有效地减少了问题的复杂度，且代码实现简洁明了。

### 最优关键思路
1. **枚举字符种类数**：通过枚举可能的字符种类数，计算每种情况下需要修改的字符数，最终选择最优解。
2. **贪心策略**：在每种情况下，保留出现次数最多的字符，并将多余的字符分配给其他字符，以减少修改次数。

### 可拓展之处
该题的思路可以拓展到其他需要平衡或均匀分配的问题，如资源分配、任务调度等。类似的题目可以通过枚举和贪心策略来解决。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：37.50秒