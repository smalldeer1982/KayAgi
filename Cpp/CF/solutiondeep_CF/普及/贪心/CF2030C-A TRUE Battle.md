# 题目信息

# A TRUE Battle

## 题目描述

Alice and Bob are playing a game. There is a list of $ n $ booleans, each of which is either true or false, given as a binary string $ ^{\text{∗}} $ of length $ n $ (where $ \texttt{1} $ represents true, and $ \texttt{0} $ represents false). Initially, there are no operators between the booleans.

Alice and Bob will take alternate turns placing and or or between the booleans, with Alice going first. Thus, the game will consist of $ n-1 $ turns since there are $ n $ booleans. Alice aims for the final statement to evaluate to true, while Bob aims for it to evaluate to false. Given the list of boolean values, determine whether Alice will win if both players play optimally.

To evaluate the final expression, repeatedly perform the following steps until the statement consists of a single true or false:

- If the statement contains an and operator, choose any one and replace the subexpression surrounding it with its evaluation.
- Otherwise, the statement contains an or operator. Choose any one and replace the subexpression surrounding the or with its evaluation.

 For example, the expression true or false and false is evaluated as true or (false and false) $ = $ true or false $ = $ true. It can be shown that the result of any compound statement is unique. $ ^{\text{∗}} $ A binary string is a string that only consists of characters $ \texttt{0} $ and $ \texttt{1} $

## 说明/提示

In the first testcase, Alice can place and between the two booleans. The game ends as there are no other places to place operators, and Alice wins because true and true is true.

In the second testcase, Alice can place or between the middle true and the left false. Bob can place and between the middle true and the right false. The statement false or true and false is false.

Note that these examples may not be the best strategies for either Alice or Bob.

## 样例 #1

### 输入

```
5
2
11
3
010
12
101111111100
10
0111111011
8
01000010```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果

### 题目内容重写

#### 题目描述

Alice和Bob正在玩一个游戏。游戏开始时，有一个长度为$n$的布尔值列表，每个布尔值为真或假，用一个长度为$n$的二进制字符串表示（其中`1`表示真，`0`表示假）。初始时，布尔值之间没有运算符。

Alice和Bob轮流在布尔值之间放置`and`或`or`运算符，Alice先手。因此，游戏将进行$n-1$轮，因为有$n$个布尔值。Alice的目标是让最终的表达式计算结果为真，而Bob的目标是让结果为假。给定布尔值列表，判断如果双方都采取最优策略，Alice是否能获胜。

为了计算最终表达式的结果，重复执行以下步骤，直到表达式只剩下一个真或假值：

- 如果表达式中包含`and`运算符，选择任意一个并将其周围的子表达式替换为其计算结果。
- 否则，表达式中包含`or`运算符，选择任意一个并将其周围的子表达式替换为其计算结果。

例如，表达式`true or false and false`的计算过程为`true or (false and false) = true or false = true`。可以证明，任何复合表达式的结果都是唯一的。

#### 说明/提示

在第一个测试用例中，Alice可以在两个布尔值之间放置`and`运算符。游戏结束时，没有其他位置可以放置运算符，Alice获胜，因为`true and true`的结果为真。

在第二个测试用例中，Alice可以在中间的`true`和左边的`false`之间放置`or`运算符。Bob可以在中间的`true`和右边的`false`之间放置`and`运算符。表达式`false or true and false`的结果为假。

注意，这些例子可能不是Alice或Bob的最佳策略。

#### 样例 #1

##### 输入

```
5
2
11
3
010
12
101111111100
10
0111111011
8
01000010
```

##### 输出

```
YES
NO
YES
YES
NO
```

### 题解分析与结论

#### 综合分析

本题的核心在于理解`and`和`or`运算符的优先级，并利用博弈论的思想分析Alice和Bob的最优策略。所有题解都围绕以下几点展开：

1. **运算符优先级**：`and`的优先级高于`or`，这意味着在表达式中，`and`会先被计算。
2. **Alice和Bob的策略**：Alice会尽可能使用`or`运算符，因为`or`可以更容易地使表达式结果为真；Bob则会尽可能使用`and`运算符，因为`and`可以更容易地使表达式结果为假。
3. **必胜条件**：如果字符串的首尾有`1`，或者字符串中有连续的`1`，Alice可以通过放置`or`运算符确保最终结果为真。

#### 最优关键思路

1. **首尾有`1`的情况**：Alice可以在首尾的`1`旁边放置`or`运算符，确保最终结果为真。
2. **连续`1`的情况**：如果字符串中有连续的`1`，Alice可以在它们之间放置`or`运算符，确保最终结果为真。
3. **其他情况**：如果字符串中没有首尾`1`且没有连续`1`，Bob可以通过放置`and`运算符确保最终结果为假。

#### 推荐题解

1. **作者：jubaoyi2011 (★★★★★)**
   - **关键亮点**：清晰地分析了`and`和`or`的优先级，并详细解释了Alice和Bob的最优策略。代码简洁且高效。
   - **代码核心**：
     ```cpp
     if(ch[1]=='1'||ch[n]=='1'){
         puts("YES");
         continue;
     }
     for(int i=1;i<n;i++){
         if(ch[i]=='1'&&ch[i+1]=='1'){
             f=1;
             break;
         }
     }
     if(f) puts("YES");
     else puts("NO");
     ```

2. **作者：Yxy7952 (★★★★)**
   - **关键亮点**：详细解释了Alice和Bob的策略，并通过例子说明了必胜条件。代码可读性强。
   - **代码核心**：
     ```cpp
     if(s[0]=='1'||s[n-1]=='1'){
         cout<<"YES\n";
         continue;
     }
     for(int i=1;i<n;i++){
         if(s[i]=='1'&&s[i-1]=='1'){
             cout<<"YES\n";
             f=1;
             break;
         }
     }
     if(!f) cout<<"NO\n";
     ```

3. **作者：Sakura_Emilia (★★★★)**
   - **关键亮点**：通过分析`and`和`or`的优先级，得出了Alice的必胜条件，并提供了简洁的代码实现。
   - **代码核心**：
     ```cpp
     if(zeroNum == 0 || oneNum >= 2 || s[0] == '1' || s[n-1] == '1')
         cout << "YES" << endl;
     else
         cout << "NO" << endl;
     ```

#### 拓展思路

1. **类似题目**：可以扩展到更复杂的表达式计算问题，例如包含多个运算符的表达式计算。
2. **博弈论应用**：本题是博弈论中的简单问题，可以进一步研究更复杂的博弈论问题，如Nim游戏等。

#### 推荐题目

1. **洛谷 P1005 矩阵取数游戏**：考察博弈论和动态规划的结合。
2. **洛谷 P1048 取石子游戏**：经典的博弈论问题，考察Nim游戏。
3. **洛谷 P1052 过河**：博弈论与动态规划的结合，考察如何优化策略。

#### 个人心得摘录

- **调试经历**：部分题解提到在测试过程中发现了一些边界条件的问题，如字符串长度为1的情况，需要特别注意。
- **顿悟感想**：通过分析`and`和`or`的优先级，理解了Alice和Bob的最优策略，从而简化了问题的解决思路。

---
处理用时：43.55秒