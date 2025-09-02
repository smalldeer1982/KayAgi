# 题目信息

# Brand New Easy Problem

## 题目描述

A widely known among some people Belarusian sport programmer Lesha decided to make some money to buy a one square meter larger flat. To do this, he wants to make and carry out a Super Rated Match (SRM) on the site Torcoder.com. But there's a problem — a severe torcoder coordinator Ivan does not accept any Lesha's problem, calling each of them an offensive word "duped" (that is, duplicated). And one day they nearely quarrelled over yet another problem Ivan wouldn't accept.

You are invited to act as a fair judge and determine whether the problem is indeed brand new, or Ivan is right and the problem bears some resemblance to those used in the previous SRMs.

You are given the descriptions of Lesha's problem and each of Torcoder.com archive problems. The description of each problem is a sequence of words. Besides, it is guaranteed that Lesha's problem has no repeated words, while the description of an archive problem may contain any number of repeated words.

The "similarity" between Lesha's problem and some archive problem can be found as follows. Among all permutations of words in Lesha's problem we choose the one that occurs in the archive problem as a subsequence. If there are multiple such permutations, we choose the one with the smallest number of inversions. Then the "similarity" of a problem can be written as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF202B/7915a415961b72b48e6cd878bc6adf37cd6bd951.png), where $ n $ is the number of words in Lesha's problem and $ x $ is the number of inversions in the chosen permutation. Note that the "similarity" $ p $ is always a positive integer.

The problem is called brand new if there is not a single problem in Ivan's archive which contains a permutation of words from Lesha's problem as a subsequence.

Help the boys and determine whether the proposed problem is new, or specify the problem from the archive which resembles Lesha's problem the most, otherwise.

## 说明/提示

Let us remind you that the number of inversions is the number of pairs of words that follow in the permutation not in their original order. Thus, for example, if the original problem is "add two numbers", then permutation "numbers add two" contains two inversions — pairs of words "numbers" and "add", "numbers" and "two".

Sequence $ b_{1},b_{2},...,b_{k} $ is a subsequence of sequence $ a_{1},a_{2},...,a_{n} $ if there exists such a set of indices $ 1<=i_{1}&lt;i_{2}&lt;...\ &lt;i_{k}<=n $ that $ a_{ij}=b_{j} $ (in other words, if sequence $ b $ can be obtained from $ a $ by deleting some of its elements).

In the first test case the first problem contains the "find the palindrome next" permutation as a subsequence, in which the number of inversions equals 1 (words "palindrome" and "next").

In the second test case there is no problem that contains a permutation of words from Lesha's problem as a subsequence.

## 样例 #1

### 输入

```
4
find the next palindrome
1
10 find the previous palindrome or print better luck next time
```

### 输出

```
1
[:||||||:]
```

## 样例 #2

### 输入

```
3
add two numbers
3
1 add
2 two two
3 numbers numbers numbers
```

### 输出

```
Brand new problem!
```

## 样例 #3

### 输入

```
4
these papers are formulas
3
6 what are these formulas and papers
5 papers are driving me crazy
4 crazy into the night
```

### 输出

```
1
[:||||:]
```

## 样例 #4

### 输入

```
3
add two decimals
5
4 please two decimals add
5 decimals want to be added
4 two add decimals add
4 add one two three
7 one plus two plus three equals six
```

### 输出

```
3
[:|||:]
```

# AI分析结果

### 题目内容
# 全新的简单问题

## 题目描述
在某些人中广为人知的白俄罗斯体育程序员莱沙决定赚些钱，以便买一套大一平方米的公寓。为此，他想在Torcoder.com网站上制作并开展一场超级评级赛（SRM）。但有个问题——严厉的Torcoder协调员伊万不接受莱沙的任何题目，称每道题都是冒犯性的“抄袭”（即重复的）。有一天，他们又因为伊万不接受的另一道题差点吵起来。

现邀请你作为公正的裁判，判断这道题是否真的全新，还是伊万是对的，这道题与之前SRM中使用的题目有相似之处。

你会得到莱沙的题目描述以及Torcoder.com存档中每道题目的描述。每道题目的描述都是一个单词序列。此外，保证莱沙的题目中没有重复单词，而存档题目的描述可能包含任意数量的重复单词。

莱沙的题目与某个存档题目之间的“相似度”可以通过以下方式找到。在莱沙题目中单词的所有排列中，我们选择在存档题目中作为子序列出现的那个排列。如果有多个这样的排列，我们选择逆序对数量最少的那个。然后，题目的“相似度”可以写成$p=\frac{n}{x + 1}$，其中$n$是莱沙题目中的单词数量，$x$是所选排列中的逆序对数量。注意，“相似度”$p$始终是一个正整数。

如果伊万的存档中没有一道题包含莱沙题目中单词的排列作为子序列，那么这道题就被称为全新的。

帮助这两个男孩，判断所提议的题目是否是新的，否则指出存档中与莱沙的题目最相似的题目。

## 说明/提示
提醒一下，逆序对的数量是指在排列中不按原始顺序出现的单词对的数量。例如，如果原始题目是“add two numbers”，那么排列“numbers add two”包含两个逆序对——单词“numbers”与“add”，以及“numbers”与“two”。

序列$b_{1},b_{2},\cdots,b_{k}$是序列$a_{1},a_{2},\cdots,a_{n}$的子序列，如果存在这样一组索引$1\leq i_{1}<i_{2}<\cdots <i_{k}\leq n$，使得$a_{ij}=b_{j}$（换句话说，如果序列$b$可以通过删除序列$a$的一些元素得到）。

在第一个测试用例中，第一个存档题目包含“find the palindrome next”这个排列作为子序列，其中逆序对的数量等于1（单词“palindrome”和“next”）。

在第二个测试用例中，没有存档题目包含莱沙题目中单词的排列作为子序列。

## 样例 #1
### 输入
```
4
find the next palindrome
1
10 find the previous palindrome or print better luck next time
```
### 输出
```
1
[:||||||:]
```
## 样例 #2
### 输入
```
3
add two numbers
3
1 add
2 two two
3 numbers numbers numbers
```
### 输出
```
Brand new problem!
```
## 样例 #3
### 输入
```
4
these papers are formulas
3
6 what are these formulas and papers
5 papers are driving me crazy
4 crazy into the night
```
### 输出
```
1
[:||||:]
```
## 样例 #4
### 输入
```
3
add two decimals
5
4 please two decimals add
5 decimals want to be added
4 two add decimals add
4 add one two three
7 one plus two plus three equals six
```
### 输出
```
3
[:|||:]
```

### 算法分类
搜索

### 综合分析与结论
题目要求判断莱沙的题目是否全新，若不是则找出最相似的存档题目，关键在于在存档题目中搜索莱沙题目单词的排列作为子序列，并找出逆序对最少的情况计算相似度。由于暂无题解，通用建议是先考虑如何生成莱沙题目单词的所有排列，然后对每个排列在存档题目中进行子序列搜索，可使用暴力搜索或者优化的字符串匹配算法。在实现过程中，生成排列和子序列匹配是主要难点，可通过回溯法生成排列，利用双指针法等优化子序列匹配过程。扩展思路上，类似题目可能会在子序列匹配条件、相似度计算方式等方面进行变化，可进一步研究不同字符串匹配算法的应用场景和优化方向。

### 通用建议与扩展思路
1. 对于生成单词排列，可以使用回溯算法，在生成每个排列时，记录其逆序对数量。
2. 在存档题目中搜索子序列时，可采用双指针法优化搜索过程，提高效率。
3. 相似题目可能会改变子序列匹配的规则，如要求严格连续匹配等，或者改变相似度的计算方式，应灵活运用字符串匹配和排列组合相关知识。 

---
处理用时：34.19秒