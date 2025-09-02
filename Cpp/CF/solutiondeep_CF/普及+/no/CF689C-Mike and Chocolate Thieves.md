# 题目信息

# Mike and Chocolate Thieves

## 题目描述

Bad news came to Mike's village, some thieves stole a bunch of chocolates from the local factory! Horrible!

Aside from loving sweet things, thieves from this area are known to be very greedy. So after a thief takes his number of chocolates for himself, the next thief will take exactly $ k $ times more than the previous one. The value of $ k $ ( $ k&gt;1 $ ) is a secret integer known only to them. It is also known that each thief's bag can carry at most $ n $ chocolates (if they intend to take more, the deal is cancelled) and that there were exactly four thieves involved.

Sadly, only the thieves know the value of $ n $ , but rumours say that the numbers of ways they could have taken the chocolates (for a fixed $ n $ , but not fixed $ k $ ) is $ m $ . Two ways are considered different if one of the thieves (they should be numbered in the order they take chocolates) took different number of chocolates in them.

Mike want to track the thieves down, so he wants to know what their bags are and value of $ n $ will help him in that. Please find the smallest possible value of $ n $ or tell him that the rumors are false and there is no such $ n $ .

## 说明/提示

In the first sample case the smallest $ n $ that leads to exactly one way of stealing chocolates is $ n=8 $ , whereas the amounts of stealed chocolates are $ (1,2,4,8) $ (the number of chocolates stolen by each of the thieves).

In the second sample case the smallest $ n $ that leads to exactly $ 8 $ ways is $ n=54 $ with the possibilities: $ (1,2,4,8), (1,3,9,27), (2,4,8,16), (2,6,18,54), (3,6,12,24), (4,8,16,32), (5,10,20,40), (6,12,24,48) $ .

There is no $ n $ leading to exactly $ 10 $ ways of stealing chocolates in the third sample case.

## 样例 #1

### 输入

```
1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
8
```

### 输出

```
54
```

## 样例 #3

### 输入

```
10
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# Mike和巧克力小偷

## 题目描述
坏消息传到了Mike的村庄，一些小偷从当地工厂偷走了一堆巧克力！太可怕了！

除了爱吃甜食，这个地区的小偷还以贪婪著称。所以在一个小偷为自己拿走一定数量的巧克力后，下一个小偷拿走的巧克力数量将恰好是前一个小偷的 $k$ 倍。$k$（$k > 1$）的值是只有他们知道的一个秘密整数。还已知每个小偷的袋子最多能装 $n$ 块巧克力（如果他们想拿更多，交易就取消），并且恰好有四个小偷参与其中。

遗憾的是，只有小偷知道 $n$ 的值，但有传言说他们拿走巧克力的方式数量（对于固定的 $n$，但 $k$ 不固定）是 $m$。如果其中一个小偷（他们应该按照拿巧克力的顺序编号）在两种方式中拿走的巧克力数量不同，则认为这两种方式不同。

Mike 想追踪小偷，所以他想知道他们的袋子情况，而 $n$ 的值将对他有所帮助。请找出 $n$ 的最小可能值，或者告诉他传言是假的，不存在这样的 $n$。

## 说明/提示
在第一个样例中，导致恰好有一种偷巧克力方式的最小 $n$ 是 $n = 8$，而偷得的巧克力数量分别是 $(1, 2, 4, 8)$（每个小偷偷的巧克力数量）。

在第二个样例中，导致恰好有 $8$ 种方式的最小 $n$ 是 $n = 54$，可能的情况有：$(1, 2, 4, 8), (1, 3, 9, 27), (2, 4, 8, 16), (2, 6, 18, 54), (3, 6, 12, 24), (4, 8, 16, 32), (5, 10, 20, 40), (6, 12, 24, 48)$。

在第三个样例中，不存在导致恰好有 $10$ 种偷巧克力方式的 $n$。

## 样例 #1
### 输入
```
1
```
### 输出
```
8
```

## 样例 #2
### 输入
```
8
```
### 输出
```
54
```

## 样例 #3
### 输入
```
10
```
### 输出
```
-1
```

### 算法分类
二分

### 综合分析与结论
所有题解思路核心均为利用二分查找来解决问题。要点在于通过分析发现满足条件的等比数列数量随 $n$ 的增大而增多，具有单调性，从而二分 $n$。难点在于计算对于给定的 $n$，满足条件的等比数列的数量，各题解均通过枚举公比 $q$，利用公式 $\lfloor \frac{n}{q^3} \rfloor$ 累加得到数量。整体上各题解思路相近，质量差异主要体现在代码的清晰程度、注释的详细程度等方面。

### 通用建议与扩展思路
解决此类问题，关键在于敏锐发现数据的单调性从而使用二分。可拓展到其他需要寻找满足特定数量条件的最值问题，同样从分析单调性入手，确定二分的范围和判断条件。在实现时，注意数据范围，合理选择数据类型避免精度问题。

### 相似知识点洛谷题目
1. [P2249 查找 P1](https://www.luogu.com.cn/problem/P2249)：基础二分查找应用。
2. [P1873 砍树](https://www.luogu.com.cn/problem/P1873)：通过二分查找满足条件的最优解。
3. [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：利用二分查找解决最值判定问题。 

---
处理用时：31.99秒