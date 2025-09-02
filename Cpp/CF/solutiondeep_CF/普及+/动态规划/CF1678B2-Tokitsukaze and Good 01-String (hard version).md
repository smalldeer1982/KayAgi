# 题目信息

# Tokitsukaze and Good 01-String (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is that the harder version asks additionally for a minimum number of subsegments.

Tokitsukaze has a binary string $ s $ of length $ n $ , consisting only of zeros and ones, $ n $ is even.

Now Tokitsukaze divides $ s $ into the minimum number of contiguous subsegments, and for each subsegment, all bits in each subsegment are the same. After that, $ s $ is considered good if the lengths of all subsegments are even.

For example, if $ s $ is "11001111", it will be divided into "11", "00" and "1111". Their lengths are $ 2 $ , $ 2 $ , $ 4 $ respectively, which are all even numbers, so "11001111" is good. Another example, if $ s $ is "1110011000", it will be divided into "111", "00", "11" and "000", and their lengths are $ 3 $ , $ 2 $ , $ 2 $ , $ 3 $ . Obviously, "1110011000" is not good.

Tokitsukaze wants to make $ s $ good by changing the values of some positions in $ s $ . Specifically, she can perform the operation any number of times: change the value of $ s_i $ to '0' or '1' ( $ 1 \leq i \leq n $ ). Can you tell her the minimum number of operations to make $ s $ good? Meanwhile, she also wants to know the minimum number of subsegments that $ s $ can be divided into among all solutions with the minimum number of operations.

## 说明/提示

In the first test case, one of the ways to make $ s $ good is the following.

Change $ s_3 $ , $ s_6 $ and $ s_7 $ to '0', after that $ s $ becomes "1100000000", it can be divided into "11" and "00000000", which lengths are $ 2 $ and $ 8 $ respectively, the number of subsegments of it is $ 2 $ . There are other ways to operate $ 3 $ times to make $ s $ good, such as "1111110000", "1100001100", "1111001100", the number of subsegments of them are $ 2 $ , $ 4 $ , $ 4 $ respectively. It's easy to find that the minimum number of subsegments among all solutions with the minimum number of operations is $ 2 $ .

In the second, third and fourth test cases, $ s $ is good initially, so no operation is required.

## 样例 #1

### 输入

```
5
10
1110011000
8
11001111
2
00
2
11
6
100110```

### 输出

```
3 2
0 3
0 1
0 1
3 1```

# AI分析结果

### 题目重写

**题目名称**：Tokitsukaze and Good 01-String (hard version)

**题目描述**：

Tokitsukaze有一个长度为$n$的二进制字符串$s$，由0和1组成，$n$是偶数。

现在，Tokitsukaze将$s$划分为最少数量的连续子段，每个子段中的所有字符相同。之后，如果所有子段的长度都是偶数，则$s$被认为是“好”的。

例如，如果$s$是“11001111”，它将被划分为“11”，“00”和“1111”。它们的长度分别为2、2、4，都是偶数，因此“11001111”是好的。另一个例子，如果$s$是“1110011000”，它将被划分为“111”，“00”，“11”和“000”，它们的长度分别为3、2、2、3。显然，“1110011000”不是好的。

Tokitsukaze希望通过改变$s$中某些位置的值来使$s$变好。具体来说，她可以执行任意次数的操作：将$s_i$的值改为'0'或'1'（$1 \leq i \leq n$）。你能告诉她使$s$变好的最小操作次数吗？同时，她也想知道在所有最小操作次数的解决方案中，$s$可以被划分为的最少子段数。

**说明/提示**：

在第一个测试用例中，使$s$变好的一种方法如下：

将$s_3$、$s_6$和$s_7$改为'0'，之后$s$变为“1100000000”，它可以被划分为“11”和“00000000”，长度分别为2和8，子段数为2。还有其他方法可以通过3次操作使$s$变好，例如“1111110000”，“1100001100”，“1111001100”，它们的子段数分别为2、4、4。容易发现，在所有最小操作次数的解决方案中，最少的子段数是2。

在第二、第三和第四个测试用例中，$s$最初就是好的，因此不需要操作。

**样例输入**：

```
5
10
1110011000
8
11001111
2
00
2
11
6
100110
```

**样例输出**：

```
3 2
0 3
0 1
0 1
3 1
```

### 题解分析与结论

#### 综合分析与结论

本题的核心在于如何通过最少的操作次数将字符串$s$变为“好”的，并且在所有最小操作次数的解决方案中，找到最少的子段数。题解中主要采用了贪心和动态规划（DP）两种思路。

1. **贪心思路**：通过两个两个地处理字符串中的字符，统计需要修改的次数，并根据相邻子段的相同情况来统计子段数。贪心思路的优势在于简单直观，易于实现。
2. **动态规划思路**：通过状态转移方程来记录每一步的最小操作次数和子段数。DP思路的优势在于可以更系统地处理复杂情况，但实现起来相对复杂。

#### 所选高星题解

1. **作者：jasonliujiahua (4星)**
   - **关键亮点**：通过贪心思路，简洁地解决了问题。代码清晰，逻辑明确。
   - **核心代码**：
     ```cpp
     for(int i=0;i+1<n;i+=2) {
         if(s[i]!=s[i+1]) ans++; // 第一问
     }
     for(int i=0;i+1<n;i+=2) {
         if(s[i]==s[i+1]) { // 第二问 第一种情况
             if(la==0 || a[la]!=s[i]-'0') // 颜色一样只算一次
                 a[++la]=s[i]-'0';
         }
     }
     ```
   - **个人心得**：通过忽略第二种情况，简化了子段数的统计，代码实现简洁高效。

2. **作者：Tx_Lcy (3星)**
   - **关键亮点**：提供了贪心和DP两种思路，代码实现较为完整。
   - **核心代码**：
     ```cpp
     for (int i=1;i<=n;i+=2)
         if (s[i]==s[i+1]) {
             if (la!=(s[i]-'0')) ++ans,la=(s[i]-'0');
         } else {
             s[i]=char(la+'0'),
             s[i+1]=s[i],++sum;
         }
     ```
   - **个人心得**：通过贪心思路，简化了问题的处理，代码实现较为直观。

3. **作者：ttq012 (3星)**
   - **关键亮点**：通过贪心思路，简洁地解决了问题，代码实现清晰。
   - **核心代码**：
     ```python
     for i in range(0, n // 2):
         j1 = i * 2
         j2 = i * 2 + 1
         if (s[j1] == s[j2] and x1 != int(s[j1])):
             y += 1
             x1 = int(s[j1])
         elif (s[j1] != s[j2]):
             x += 1
             f = 1
     ```
   - **个人心得**：通过贪心思路，简化了问题的处理，代码实现较为直观。

### 最优关键思路与技巧

1. **贪心策略**：通过两个两个地处理字符串中的字符，统计需要修改的次数，并根据相邻子段的相同情况来统计子段数。贪心策略的优势在于简单直观，易于实现。
2. **动态规划**：通过状态转移方程来记录每一步的最小操作次数和子段数。DP思路的优势在于可以更系统地处理复杂情况，但实现起来相对复杂。

### 可拓展之处

1. **类似问题**：可以扩展到更复杂的字符串处理问题，如处理多字符字符串或更复杂的规则。
2. **算法套路**：贪心和动态规划是解决类似问题的常见套路，可以应用到其他字符串处理或序列问题中。

### 推荐题目

1. **洛谷P1003 铺地毯**：考察贪心算法的应用。
2. **洛谷P1049 装箱问题**：考察动态规划的应用。
3. **洛谷P1057 传球游戏**：考察动态规划的应用。

---
处理用时：53.91秒