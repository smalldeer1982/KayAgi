# 题目信息

# Game with String

## 题目描述

Vasya and Kolya play a game with a string, using the following rules. Initially, Kolya creates a string $ s $ , consisting of small English letters, and uniformly at random chooses an integer $ k $ from a segment $ [0,len(s)-1] $ . He tells Vasya this string $ s $ , and then shifts it $ k $ letters to the left, i. e. creates a new string $ t=s_{k+1}s_{k+2}...\ s_{n}s_{1}s_{2}...\ s_{k} $ . Vasya does not know the integer $ k $ nor the string $ t $ , but he wants to guess the integer $ k $ . To do this, he asks Kolya to tell him the first letter of the new string, and then, after he sees it, open one more letter on some position, which Vasya can choose.

Vasya understands, that he can't guarantee that he will win, but he wants to know the probability of winning, if he plays optimally. He wants you to compute this probability.

Note that Vasya wants to know the value of $ k $ uniquely, it means, that if there are at least two cyclic shifts of $ s $ that fit the information Vasya knowns, Vasya loses. Of course, at any moment of the game Vasya wants to maximize the probability of his win.

## 说明/提示

In the first example Vasya can always open the second letter after opening the first letter, and the cyclic shift is always determined uniquely.

In the second example if the first opened letter of $ t $ is "t" or "c", then Vasya can't guess the shift by opening only one other letter. On the other hand, if the first letter is "i" or "a", then he can open the fourth letter and determine the shift uniquely.

## 样例 #1

### 输入

```
technocup
```

### 输出

```
1.000000000000000
```

## 样例 #2

### 输入

```
tictictactac
```

### 输出

```
0.333333333333333
```

## 样例 #3

### 输入

```
bbaabaabbb
```

### 输出

```
0.100000000000000
```

# AI分析结果



【题目翻译】
# 字符串游戏

## 题目描述

Vasya和Kolya用字符串玩一个游戏，规则如下。最初Kolya创建一个由小写字母组成的字符串$s$，并均匀随机地从区间$[0,len(s)-1]$中选择一个整数$k$。他将这个字符串$s$告诉Vasya，然后将字符串左移$k$次生成新字符串$t$（即$t = s_{k+1}s_{k+2}...s_ns_1s_2...s_k$）。Vasya不知道$k$和$t$，但他想猜出$k$。为此，他先让Kolya告诉他新字符串的第一个字母，然后根据这个信息选择再查看某个位置的另一个字母。

Vasya知道他不能保证必胜，但想知道以最优策略获胜的概率。你需要计算这个概率。

注意：若存在多个可能的$k$符合已知信息，Vasya即失败。Vasya在任何时刻都采取最大化胜率的策略。

## 说明/提示

第一个样例中，Vasya总能通过查看第二个字母唯一确定循环移位。

第二个样例中，当首字母是"t"或"c"时，Vasya无法通过再查看一个字母确定移位；当首字母是"i"或"a"时，查看第四个字母即可唯一确定。

## 样例 #1

### 输入
```
technocup
```

### 输出
```
1.000000000000000
```

## 样例 #2

### 输入
```
tictictactac
```

### 输出
```
0.333333333333333
```

【算法分类】概率论

【题解对比与结论】
各题解均采用核心思路：按首字母分组，枚举可能查看的位置，统计唯一性最大的情况。核心差异在于实现方式：

1. **高效索引处理**：DPair和anonymous_Y将字符串拼接为两倍长度，避免模运算，直接通过索引访问循环移位后的字符。
2. **概率计算模型**：通过`首字母出现概率 × 该字母最优位置唯一率`的加权和计算总概率。
3. **时间复杂度控制**：均实现O(n²)解法，适用于n≤5000的约束。

【高星题解精选】
1. **DPair（5星）**
   - 亮点：代码结构清晰，通过预存各字母出现位置优化统计效率，拼接字符串处理循环移位巧妙。
   - 关键代码解析：
     ```cpp
     a = a + a; // 拼接字符串处理循环移位
     for 每个字母c：
         for 每个可能查看的位置d（1≤d<len）：
             统计所有c开头的字符串在位置d的字符频次
             计算唯一字符数，维护最大值
     ans += (最大唯一数/c出现次数) * c的概率
     ```

2. **anonymous_Y（4星）**
   - 亮点：思路表述直观，代码与DPair相似但变量命名更简洁。
   - 个人心得：强调字符组合唯一性的判断标准，帮助理解问题本质。

【最优思路提炼】
1. **首字母分组**：将所有循环移位按首字母分组处理。
2. **位置唯一性扫描**：对每个首字母组，扫描每个可能查看的位置d，统计该位置字符的频次，计算能唯一确定移位的最大数量。
3. **概率加权求和**：将每个字母的最优概率按出现频率加权累加。

【拓展思路】
- 类似问题可拓展到多位置查询场景，需考虑组合唯一性的统计。
- 循环移位类问题常用拼接字符串技巧简化索引计算。

【相似题目推荐】
1. P1368 [最小表示法](https://www.luogu.com.cn/problem/P1368)（循环同构串处理）
2. P3966 [单词](https://www.luogu.com.cn/problem/P3966)（循环移位统计）
3. P1224 [向量内积](https://www.luogu.com.cn/problem/P1224)（统计特征组合唯一性）

---
处理用时：71.31秒