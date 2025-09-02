# 题目信息

# Hometask

## 题目描述

Sergey attends lessons of the $ N $ -ish language. Each lesson he receives a hometask. This time the task is to translate some sentence to the $ N $ -ish language. Sentences of the $ N $ -ish language can be represented as strings consisting of lowercase Latin letters without spaces or punctuation marks.

Sergey totally forgot about the task until half an hour before the next lesson and hastily scribbled something down. But then he recollected that in the last lesson he learned the grammar of $ N $ -ish. The spelling rules state that $ N $ -ish contains some "forbidden" pairs of letters: such letters can never occur in a sentence next to each other. Also, the order of the letters doesn't matter (for example, if the pair of letters "ab" is forbidden, then any occurrences of substrings "ab" and "ba" are also forbidden). Also, each pair has different letters and each letter occurs in no more than one forbidden pair.

Now Sergey wants to correct his sentence so that it doesn't contain any "forbidden" pairs of letters that stand next to each other. However, he is running out of time, so he decided to simply cross out some letters from the sentence. What smallest number of letters will he have to cross out? When a letter is crossed out, it is "removed" so that the letters to its left and right (if they existed), become neighboring. For example, if we cross out the first letter from the string "aba", we get the string "ba", and if we cross out the second letter, we get "aa".

## 说明/提示

In the first sample you should remove two letters b.

In the second sample you should remove the second or the third letter. The second restriction doesn't influence the solution.

## 样例 #1

### 输入

```
ababa
1
ab
```

### 输出

```
2
```

## 样例 #2

### 输入

```
codeforces
2
do
cs
```

### 输出

```
1
```

# AI分析结果



## 中文重写题目

### 题目名称：家庭作业

#### 题目描述

Sergey在学习N语。每节课他会收到家庭作业。这次的作业是将一个句子翻译成N语。N语的句子可以表示为仅由小写拉丁字母组成的字符串，无空格或标点符号。

Sergey直到课前半小时才想起作业，匆忙写下了些内容。但他想起上节课学的N语语法：存在若干"禁止"字母对，这些字母在句子中不能相邻出现。字母对的顺序无关（例如若"ab"是禁止对，则"ab"和"ba"都不允许出现）。每个字母对包含不同字母，且每个字母最多出现在一个禁止对中。

现在Sergey要修改句子，使其不含任何禁止字母对相邻。由于时间紧迫，他决定直接删除部分字母。求最少需要删除多少个字母？删除字母后，左右字母会相邻。例如删除"aba"的第一个字母得到"ba"，删除第二个得到"aa"。

#### 输入输出样例

样例1：
输入：
```
ababa
1
ab
```
输出：
```
2
```

样例2：
输入：
```
codeforces
2
do
cs
```
输出：
```
1
```

#### 说明提示
样例1需删除两个b，样例2需删除第二个或第三个字母。

---

## 算法分类
贪心

---

## 题解分析与结论

### 各题解核心思路对比

1. **贪心策略（主流解法）**
   - 核心思路：对每个禁止对，扫描原字符串，统计连续出现的两个字符数量。当遇到其他字符或字符串结尾时，累加两个计数的较小值
   - 正确性证明：对于每个禁止对的连续段，必须全部保留其中一种字符，故删除次数为min(a,b)
   - 时间复杂度：O(nk)，n为字符串长度，k为禁止对数量

2. **动态规划解法**
   - 设f[i][j]表示前i个字符，最后保留字符j时的最大保留字符数
   - 状态转移时需考虑当前字符能否与前一字符组成合法对
   - 时间复杂度：O(n*26)，但代码复杂度较高

3. **错误解法风险**
   - 若未正确处理连续段的边界（如字符串末尾未被处理）会导致错误
   - 动态规划解法需要处理非法对判断的预处理

### 最优题解推荐

#### 1. Andy_Li（5星）
**关键亮点**：
- 简洁清晰的贪心实现
- 正确处理字符串末尾的统计
- 代码可读性极佳

核心代码：
```cpp
for(int i=0;i<s.size();i++)
    if(s[i]==c)
        cnt1++;
    else if(s[i]==cc)
        cnt2++;
    else {
        ans += min(cnt1,cnt2);
        cnt1 = cnt2 = 0;
    }
ans += min(cnt1,cnt2); // 处理末尾
```

#### 2. fuxuantong123（4星）
**亮点**：
- 使用字符串处理禁止对
- 包含条件判断优化
**代码片段**：
```cpp
if(fw[0]!=s[i] && fw[1]!=s[i]){
    if(sum1 && sum2) ans += min(sum1,sum2);
    sum1 = sum2 = 0;
}
```

---

## 最优解关键技巧
**贪心扫描法**：
1. 对每个禁止对独立处理
2. 维护两个计数器，统计当前连续段中两个字符的出现次数
3. 遇到干扰字符时，累加min值并重置计数器
4. 最终处理末尾的计数器

**思维启示**：
- 将复杂问题分解为独立子问题处理
- 利用字母对互不重叠的特性简化处理
- 注意字符串末尾的特殊情况处理

---

## 相似题目推荐
1. P1090 [NOIP2004 提高组] 合并果子（贪心策略）
2. P1106 删数问题（贪心删除策略）
3. P1565 [APIO2009] 会议中心（区间处理与贪心）

---
处理用时：69.39秒