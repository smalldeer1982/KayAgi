# 题目信息

# Subtle Substring Subtraction

## 题目描述

Alice and Bob are playing a game with strings. There will be $ t $ rounds in the game. In each round, there will be a string $ s $ consisting of lowercase English letters.

Alice moves first and both the players take alternate turns. Alice is allowed to remove any substring of even length (possibly empty) and Bob is allowed to remove any substring of odd length from $ s $ .

More formally, if there was a string $ s = s_1s_2 \ldots s_k $ the player can choose a substring $ s_ls_{l+1} \ldots s_{r-1}s_r $ with length of corresponding parity and remove it. After that the string will become $ s = s_1 \ldots s_{l-1}s_{r+1} \ldots s_k $ .

After the string becomes empty, the round ends and each player calculates his/her score for this round. The score of a player is the sum of values of all characters removed by him/her. The value of $ \texttt{a} $ is $ 1 $ , the value of $ \texttt{b} $ is $ 2 $ , the value of $ \texttt{c} $ is $ 3 $ , $ \ldots $ , and the value of $ \texttt{z} $ is $ 26 $ . The player with higher score wins the round. For each round, determine the winner and the difference between winner's and loser's scores. Assume that both players play optimally to maximize their score. It can be proved that a draw is impossible.

## 说明/提示

For the first round, $ \texttt{"aba"}\xrightarrow{\texttt{Alice}}\texttt{"}{\color{red}{\texttt{ab}}}\texttt{a"}\xrightarrow{} \texttt{"a"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{a}}}\texttt{"}\xrightarrow{}\texttt{""} $ . Alice's total score is $ 1+2=3 $ . Bob's total score is $ 1 $ .

For the second round, $ \texttt{"abc"}\xrightarrow{\texttt{Alice}}\texttt{"a}{\color{red}{\texttt{bc}}}\texttt{"}\xrightarrow{} \texttt{"a"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{a}}}\texttt{"}\xrightarrow{}\texttt{""} $ . Alice's total score is $ 2+3=5 $ . Bob's total score is $ 1 $ .

For the third round, $ \texttt{"cba"}\xrightarrow{\texttt{Alice}}\texttt{"}{\color{red}{\texttt{cb}}}\texttt{a"}\xrightarrow{} \texttt{"a"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{a}}}\texttt{"}\xrightarrow{}\texttt{""} $ . Alice's total score is $ 3+2=5 $ . Bob's total score is $ 1 $ .

For the fourth round, $ \texttt{"n"}\xrightarrow{\texttt{Alice}}\texttt{"n"}\xrightarrow{} \texttt{"n"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{n}}}\texttt{"}\xrightarrow{}\texttt{""} $ . Alice's total score is $ 0 $ . Bob's total score is $ 14 $ .

For the fifth round, $ \texttt{"codeforces"}\xrightarrow{\texttt{Alice}}\texttt{"}{\color{red}{\texttt{codeforces}}}\texttt{"}\xrightarrow{} \texttt{""} $ . Alice's total score is $ 3+15+4+5+6+15+18+3+5+19=93 $ . Bob's total score is $ 0 $ .

## 样例 #1

### 输入

```
5
aba
abc
cba
n
codeforces```

### 输出

```
Alice 2
Alice 4
Alice 4
Bob 14
Alice 93```

# AI分析结果

### 题目内容
# 微妙的子串减法

## 题目描述
爱丽丝（Alice）和鲍勃（Bob）正在玩一个字符串游戏。游戏共有 $t$ 轮。在每一轮中，会给出一个由小写英文字母组成的字符串 $s$。

爱丽丝先行动，然后双方轮流进行操作。爱丽丝可以移除任意长度为偶数（可能为空）的子串，鲍勃可以移除任意长度为奇数的子串。

更正式地说，如果有一个字符串 $s = s_1s_2 \ldots s_k$，玩家可以选择一个具有相应奇偶性长度的子串 $s_ls_{l + 1} \ldots s_{r - 1}s_r$ 并将其移除。之后，字符串将变为 $s = s_1 \ldots s_{l - 1}s_{r + 1} \ldots s_k$。

当字符串变为空时，本轮结束，每个玩家计算自己在本轮的得分。玩家的得分是他/她移除的所有字符的值的总和。字母 $\texttt{a}$ 的值为 $1$，字母 $\texttt{b}$ 的值为 $2$，字母 $\texttt{c}$ 的值为 $3$，依此类推，字母 $\texttt{z}$ 的值为 $26$。得分较高的玩家赢得本轮。对于每一轮，确定获胜者以及获胜者与失败者得分之间的差值。假设双方都采取最优策略来最大化自己的得分。可以证明平局是不可能的。

## 说明/提示
对于第一轮，$\texttt{"aba"}\xrightarrow{\texttt{Alice}}\texttt{"}{\color{red}{\texttt{ab}}}\texttt{a"}\xrightarrow{} \texttt{"a"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{a}}}\texttt{"}\xrightarrow{}\texttt{""} $。爱丽丝的总得分是 $1 + 2 = 3$。鲍勃的总得分是 $1$。

对于第二轮，$\texttt{"abc"}\xrightarrow{\texttt{Alice}}\texttt{"a}{\color{red}{\texttt{bc}}}\texttt{"}\xrightarrow{} \texttt{"a"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{a}}}\texttt{"}\xrightarrow{}\texttt{""} $。爱丽丝的总得分是 $2 + 3 = 5$。鲍勃的总得分是 $1$。

对于第三轮，$\texttt{"cba"}\xrightarrow{\texttt{Alice}}\texttt{"}{\color{red}{\texttt{cb}}}\texttt{a"}\xrightarrow{} \texttt{"a"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{a}}}\texttt{"}\xrightarrow{}\texttt{""} $。爱丽丝的总得分是 $3 + 2 = 5$。鲍勃的总得分是 $1$。

对于第四轮，$\texttt{"n"}\xrightarrow{\texttt{Alice}}\texttt{"n"}\xrightarrow{} \texttt{"n"}\xrightarrow{\texttt{Bob}}\texttt{"}{\color{red}{\texttt{n}}}\texttt{"}\xrightarrow{}\texttt{""} $。爱丽丝的总得分是 $0$。鲍勃的总得分是 $14$。

对于第五轮，$\texttt{"codeforces"}\xrightarrow{\texttt{Alice}}\texttt{"}{\color{red}{\texttt{codeforces}}}\texttt{"}\xrightarrow{} \texttt{""} $。爱丽丝的总得分是 $3 + 15 + 4 + 5 + 6 + 15 + 18 + 3 + 5 + 19 = 93$。鲍勃的总得分是 $0$。

## 样例 #1
### 输入
```
5
aba
abc
cba
n
codeforces
```
### 输出
```
Alice 2
Alice 4
Alice 4
Bob 14
Alice 93
```

### 算法分类
贪心

### 综合分析与结论
这几道题解的核心思路都是基于对游戏规则的分析，利用先手优势进行贪心策略。由于爱丽丝先手且能取偶数长度子串，所以当字符串长度为偶数时，爱丽丝可直接取走整个字符串获胜；当字符串长度为奇数且不为1时，爱丽丝会舍弃开头或结尾字典序最小（分值最小）的字符，让鲍勃取走这个字符，自己拿走其余字符，从而使自己得分最大化；当字符串长度为1时，爱丽丝无法操作，鲍勃拿走唯一字符获胜。各题解在实现细节上略有不同，但整体思路一致。

### 通用建议与扩展思路
在解决此类博弈问题时，关键在于分析双方的操作限制和先后手优势，通过合理的贪心策略来确定最优解。对于类似题目，可以考虑改变操作规则（如可选择子串的条件、得分计算方式等），或者增加游戏轮次、字符串数量等条件来拓展。

### 洛谷题目推荐
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过合理排序实现贪心策略，与本题通过分析操作规则确定贪心策略类似。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据接水时间进行排序贪心，锻炼对贪心策略的应用。
3. [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：博弈类型题目，需要分析双方策略，与本题有相似的思考方向。 

---
处理用时：38.82秒