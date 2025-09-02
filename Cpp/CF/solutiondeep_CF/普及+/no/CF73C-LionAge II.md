# 题目信息

# LionAge II

## 题目描述

Vasya plays the LionAge II. He was bored of playing with a stupid computer, so he installed this popular MMORPG, to fight with his friends. Vasya came up with the name of his character — non-empty string $ s $ , consisting of a lowercase Latin letters. However, in order not to put up a front of friends, Vasya has decided to change no more than $ k $ letters of the character name so that the new name sounded as good as possible. Euphony of the line is defined as follows: for each pair of adjacent letters $ x $ and $ y $ ( $ x $ immediately precedes $ y $ ) the bonus $ c(x,y) $ is added to the result. Your task is to determine what the greatest Euphony can be obtained by changing at most $ k $ letters in the name of the Vasya's character.

## 说明/提示

In the first example the most euphony name will be $ looser $ . It is easy to calculate that its euphony is 36.

## 样例 #1

### 输入

```
winner 4
4
s e 7
o s 8
l o 13
o o 8
```

### 输出

```
36```

## 样例 #2

### 输入

```
abcdef 1
5
a b -10
b c 5
c d 5
d e 5
e f 5
```

### 输出

```
20```

# AI分析结果

### 题目内容
# LionAge II

## 题目描述
瓦夏在玩《LionAge II》。他玩腻了和笨电脑对战，所以安装了这款流行的大型多人在线角色扮演游戏（MMORPG），以便和朋友们对战。瓦夏为他的角色想出了一个名字——由小写拉丁字母组成的非空字符串 $s$。然而，为了不在朋友面前装样子，瓦夏决定更改角色名字中不超过 $k$ 个字母，以使新名字听起来尽可能好听。字符串的悦耳度定义如下：对于每一对相邻字母 $x$ 和 $y$（$x$ 紧跟在 $y$ 之前），将奖励值 $c(x,y)$ 加到结果中。你的任务是确定通过更改瓦夏角色名字中最多 $k$ 个字母，能获得的最大悦耳度是多少。

## 说明/提示
在第一个示例中，最悦耳的名字将是“looser”。很容易计算出它的悦耳度是36。

## 样例 #1
### 输入
```
winner 4
4
s e 7
o s 8
l o 13
o o 8
```
### 输出
```
36```

## 样例 #2
### 输入
```
abcdef 1
5
a b -10
b c 5
c d 5
d e 5
e f 5
```
### 输出
```
20```

### 算法分类
动态规划

### 题解综合分析与结论
这几道题解思路基本一致，均采用动态规划算法。核心思路是通过定义三维状态 $dp[i][j][k]$（不同作者变量名有别），分别表示处理到字符串第 $i$ 位、修改了 $j$ 次、当前位字符为 $k$ 时的最大悦耳度。难点在于状态转移方程的推导，要根据当前位是否修改来确定从之前状态的转移方式。各题解在代码实现上有些许差异，如初始化方式、循环顺序等，但本质都是基于动态规划的思想来解决问题。

### 通用建议与扩展思路
对于此类动态规划问题，关键在于准确分析状态和状态转移。在实现时，要注意边界条件的处理以及数组的初始化。扩展思路上，可以考虑增加更多的限制条件，比如限制某些字符不能修改，或者修改字符有不同的代价等，以加深对动态规划应用的理解。

### 洛谷相似题目推荐
1. P1048 [NOIP2005 普及组] 采药：同样是动态规划问题，通过合理定义状态和状态转移方程解决背包类问题。
2. P1280 尼克的任务：也是动态规划，在时间序列上进行状态转移，与本题类似。
3. P1880 [NOIP2012 提高组] 尼克的任务：同样是动态规划，在时间轴上根据不同条件进行状态转移。 

---
处理用时：27.23秒