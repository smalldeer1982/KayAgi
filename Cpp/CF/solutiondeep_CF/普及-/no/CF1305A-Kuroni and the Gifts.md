# 题目信息

# Kuroni and the Gifts

## 题目描述

Kuroni has $ n $ daughters. As gifts for them, he bought $ n $ necklaces and $ n $ bracelets:

- the $ i $ -th necklace has a brightness $ a_i $ , where all the $ a_i $ are pairwise distinct (i.e. all $ a_i $ are different),
- the $ i $ -th bracelet has a brightness $ b_i $ , where all the $ b_i $ are pairwise distinct (i.e. all $ b_i $ are different).

Kuroni wants to give exactly one necklace and exactly one bracelet to each of his daughters. To make sure that all of them look unique, the total brightnesses of the gifts given to each daughter should be pairwise distinct. Formally, if the $ i $ -th daughter receives a necklace with brightness $ x_i $ and a bracelet with brightness $ y_i $ , then the sums $ x_i + y_i $ should be pairwise distinct. Help Kuroni to distribute the gifts.

For example, if the brightnesses are $ a = [1, 7, 5] $ and $ b = [6, 1, 2] $ , then we may distribute the gifts as follows:

- Give the third necklace and the first bracelet to the first daughter, for a total brightness of $ a_3 + b_1 = 11 $ .
- Give the first necklace and the third bracelet to the second daughter, for a total brightness of $ a_1 + b_3 = 3 $ .
- Give the second necklace and the second bracelet to the third daughter, for a total brightness of $ a_2 + b_2 = 8 $ .

Here is an example of an invalid distribution:

- Give the first necklace and the first bracelet to the first daughter, for a total brightness of $ a_1 + b_1 = 7 $ .
- Give the second necklace and the second bracelet to the second daughter, for a total brightness of $ a_2 + b_2 = 8 $ .
- Give the third necklace and the third bracelet to the third daughter, for a total brightness of $ a_3 + b_3 = 7 $ .

This distribution is invalid, as the total brightnesses of the gifts received by the first and the third daughter are the same. Don't make them this upset!

## 说明/提示

In the first test case, it is enough to give the $ i $ -th necklace and the $ i $ -th bracelet to the $ i $ -th daughter. The corresponding sums are $ 1 + 8 = 9 $ , $ 8 + 4 = 12 $ , and $ 5 + 5 = 10 $ .

The second test case is described in the statement.

## 样例 #1

### 输入

```
2
3
1 8 5
8 4 5
3
1 7 5
6 1 2```

### 输出

```
1 8 5
8 4 5
5 1 7
6 2 1```

# AI分析结果

### 题目内容
# Kuroni和礼物

## 题目描述
Kuroni有$n$个女儿。作为给她们的礼物，他买了$n$条项链和$n$个手镯：
 - 第$i$条项链有亮度$a_i$，所有的$a_i$两两不同（即所有$a_i$都不一样）。
 - 第$i$个手镯有亮度$b_i$，所有的$b_i$两两不同（即所有$b_i$都不一样）。

Kuroni想给每个女儿恰好一条项链和一个手镯。为确保她们看起来都独特，送给每个女儿的礼物总亮度应该两两不同。 正式地说，如果第$i$个女儿收到亮度为$x_i$的项链和亮度为$y_i$的手镯，那么和$x_i + y_i$应该两两不同。 请帮助Kuroni分发礼物。

例如，如果亮度分别为$a = [1, 7, 5]$和$b = [6, 1, 2]$，那么我们可以如下分发礼物：
 - 把第三条项链和第一个手镯给第一个女儿，总亮度为$a_3 + b_1 = 11$。
 - 把第一条项链和第三个手镯给第二个女儿，总亮度为$a_1 + b_3 = 3$。
 - 把第二条项链和第二个手镯给第三个女儿，总亮度为$a_2 + b_2 = 8$。

这里有一个无效分发的例子：
 - 把第一条项链和第一个手镯给第一个女儿，总亮度为$a_1 + b_1 = 7$。
 - 把第二条项链和第二个手镯给第二个女儿，总亮度为$a_2 + b_2 = 8$。
 - 把第三条项链和第三个手镯给第三个女儿，总亮度为$a_3 + b_3 = 7$。

这种分发是无效的，因为第一个和第三个女儿收到礼物的总亮度相同。别让她们这么沮丧！

## 说明/提示
在第一个测试用例中，把第$i$条项链和第$i$个手镯给第$i$个女儿就足够了。相应的和分别是$1 + 8 = 9$，$8 + 4 = 12$，$5 + 5 = 10$。
第二个测试用例在题目描述中有说明。

## 样例 #1
### 输入
```
2
3
1 8 5
8 4 5
3
1 7 5
6 1 2
```
### 输出
```
1 8 5
8 4 5
5 1 7
6 2 1
```

### 算法分类
排序

### 综合分析与结论
所有题解思路一致，均基于已知条件，即$a_i$和$b_i$分别两两不同，通过将两个数组排序，利用不等式性质得到$a_1 + b_1 < a_2 + b_2 < \cdots < a_n + b_n$，从而满足总亮度两两不同的要求。各题解在代码实现上略有差异，主要体现在输入输出方式、代码风格及一些宏定义的使用上。整体来看，这些题解思路清晰，但在代码可读性和优化程度上没有特别突出的表现，均未达到4星标准。

### 通用建议与扩展思路
 - **通用建议**：在代码实现上，可以增加注释以提高可读性，对于输入输出部分，可以根据实际情况选择更合适的方式，避免过度使用宏定义导致代码难以理解。
 - **扩展思路**：此类题目核心在于利用给定序列的性质构造出满足条件的组合。类似的题目可能会改变序列的性质或者对组合的条件提出更复杂的要求，例如要求组合结果满足特定的数值关系，或者序列中的元素存在部分重复等情况，解题时需要根据具体条件灵活运用排序、不等式等知识进行构造。

### 相似知识点洛谷题目
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过比较不同购买方案的价格，选择最优方案，涉及简单的贪心和比较运算。
 - [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)：需要对数组元素进行操作以达到某种平衡状态，与本题通过对序列处理满足特定条件类似。
 - [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：根据给定规则对一系列操作结果进行分析，与本题根据条件构造结果思路相似。 

---
处理用时：42.99秒