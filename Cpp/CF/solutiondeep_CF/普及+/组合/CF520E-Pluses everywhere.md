# 题目信息

# Pluses everywhere

## 题目描述

Vasya is sitting on an extremely boring math class. To have fun, he took a piece of paper and wrote out $ n $ numbers on a single line. After that, Vasya began to write out different ways to put pluses ("+") in the line between certain digits in the line so that the result was a correct arithmetic expression; formally, no two pluses in such a partition can stand together (between any two adjacent pluses there must be at least one digit), and no plus can stand at the beginning or the end of a line. For example, in the string 100500, ways 100500 (add no pluses), 1+00+500 or 10050+0 are correct, and ways 100++500, +1+0+0+5+0+0 or 100500+ are incorrect.

The lesson was long, and Vasya has written all the correct ways to place exactly $ k $ pluses in a string of digits. At this point, he got caught having fun by a teacher and he was given the task to calculate the sum of all the resulting arithmetic expressions by the end of the lesson (when calculating the value of an expression the leading zeros should be ignored). As the answer can be large, Vasya is allowed to get only its remainder modulo $ 10^{9}+7 $ . Help him!

## 说明/提示

In the first sample the result equals $ (1+08)+(10+8)=27 $ .

In the second sample the result equals $ 1+0+8=9 $ .

## 样例 #1

### 输入

```
3 1
108
```

### 输出

```
27```

## 样例 #2

### 输入

```
3 2
108
```

### 输出

```
9```

# AI分析结果

### 题目中文重写
# 处处是加号

## 题目描述
瓦西亚正在上一节极其无聊的数学课。为了找点乐子，他拿了一张纸，在一行上写下了 $n$ 个数字。之后，瓦西亚开始在这一行数字的某些数位之间写下不同的添加加号（“+”）的方式，使得结果成为一个正确的算术表达式；形式上，在这样的划分中，任意两个加号不能相邻（任意两个相邻的加号之间必须至少有一个数字），并且加号不能位于一行的开头或结尾。例如，在字符串 100500 中，100500（不添加加号）、1+00+500 或 10050+0 是正确的方式，而 100++500、+1+0+0+5+0+0 或 100500+ 是不正确的方式。

这节课很长，瓦西亚已经写出了在一串数字中恰好放置 $k$ 个加号的所有正确方式。这时，他在玩乐时被老师抓住了，老师要求他在这节课结束前计算所有得到的算术表达式的和（在计算表达式的值时，应忽略前导零）。由于答案可能很大，允许瓦西亚只取其对 $10^{9}+7$ 取模的结果。请帮助他！

## 说明/提示
在第一个样例中，结果等于 $(1 + 08)+(10 + 8)=27$。

在第二个样例中，结果等于 $1 + 0 + 8 = 9$。

## 样例 #1
### 输入
```
3 1
108
```
### 输出
```
27
```

## 样例 #2
### 输入
```
3 2
108
```
### 输出
```
9
```

### 综合分析与结论
这些题解的核心思路都是通过单独计算每个数位的贡献来求解所有可能表达式的和。具体做法是根据每个数位后面最近的加号位置分情况讨论，结合组合数计算该数位在不同情况下的贡献，最后将所有数位的贡献累加起来。
- **算法要点**：
    - 预处理组合数及其逆元，用于计算不同位置放置加号的方案数。
    - 利用前缀和优化内层求和计算，将复杂度从 $O(n^2)$ 降低到 $O(n)$。
    - 对最后一个数位后面不能放加号的情况进行特判。
- **解决难点**：
    - 确定每个数位在不同位置放置加号时的贡献计算方式。
    - 处理最后一个数位的特殊情况，避免贡献计算遗漏。
    - 通过交换枚举顺序和前缀和优化，降低时间复杂度以通过题目。

### 所选题解
- **作者：Heartlessly（5星）**
    - **关键亮点**：思路清晰，详细推导了每个数位的贡献公式，并通过前缀和预处理优化计算，代码实现简洁明了。
    - **核心代码**：
```cpp
for (int cur = 1, i = 1; i <= n - m; ++i, cur = 1ll * cur * 10 % MOD)
    ans = (ans + 1ll * cur * (1ll * pre[n - i] * c(n - 1 - i, m - 1) % MOD + 
    1ll * a[n - i + 1] * c(n - i, m) % MOD) % MOD) % MOD;
```
核心思想是枚举 $i$ 位数产生的贡献，利用前缀和 `pre` 计算能产生 $10^i$ 贡献的数字总和，结合组合数计算每个数位的贡献并累加。
- **作者：QwQcOrZ（4星）**
    - **关键亮点**：从第 $i$ 位数在取出的数中是第 $j$ 位出现的贡献角度思考，通过分析得出出现次数与 $i$ 无关，进而将 $V$ 处理成前缀和形式，枚举 $j$ 计算贡献，思路独特且易于理解。
    - **核心代码**：
```cpp
for (ll i = 0; i < n; i++)
{
    ans = (ans + a[n - i - 1] * base[i] % p * C(k - 1, n - i - 2) % p) % p;
    ans = (ans + (a[n - i] - a[n - i - 1] + p) % p * base[i] % p * C(k, n - i - 1) % p) % p; 
} 
```
核心思想是枚举 $j$，分别计算一般情况和最后一位的特殊情况的贡献并累加。
- **作者：_Passerby_（4星）**
    - **关键亮点**：对总答案公式进行详细化简，将其拆分为两个式子分别处理，通过交换枚举顺序和前缀和优化，最终得到 $O(n)$ 的复杂度，推导过程严谨。
    - **核心代码**：
```cpp
Ans = \sum_{j = 1}^{n-k}10^{j - 1}\times((C_{n-j-1}^{k-1}\times\sum_{i = 1}^{n - j}a_i)+a_{n-j+1}\times C_{n-j}^k)
```
核心思想是通过化简后的公式，枚举 $j$，结合前缀和和组合数计算总答案。

### 最优关键思路或技巧
- **单独计算贡献**：通过单独考虑每个数位的贡献，将复杂的表达式求和问题转化为多个简单的贡献计算问题。
- **前缀和优化**：利用前缀和预处理能产生相同贡献的数字总和，将内层求和的时间复杂度从 $O(n)$ 降低到 $O(1)$，从而将整体复杂度从 $O(n^2)$ 优化到 $O(n)$。
- **组合数应用**：运用组合数计算不同位置放置加号的方案数，准确计算每个数位在不同情况下的贡献。

### 可拓展之处
同类型题目可能会改变数字的范围、加号的数量限制或取模的数值，解题思路仍然是单独计算每个元素的贡献，结合组合数和前缀和优化。类似的算法套路还可以应用于其他需要计算不同组合方案下元素贡献总和的问题，如排列组合问题、动态规划问题等。

### 推荐洛谷题目
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)：涉及组合数学和递推思想，与本题中组合数的应用有一定关联。
- [P1833 樱花](https://www.luogu.com.cn/problem/P1833)：需要对不同情况进行分类讨论和组合计算，锻炼分析问题和解决问题的能力。
- [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)：直接考察组合数的计算和应用，与本题中组合数的使用场景类似。

### 个人心得摘录与总结
- **作者：QwQcOrZ**：“祭我在考场上AC了此题”，表达了在考场上成功解决该题的喜悦，同时也提醒我们在考场上要冷静分析问题，灵活运用所学知识。
- **作者：Arcturus1350**：“ps:可能组合数一不小心打错了，请发现的大佬提出，谢谢”，体现了作者的严谨态度，在编写代码时要仔细检查，避免因小错误导致结果出错。

---
处理用时：43.44秒