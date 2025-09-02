---
title: "a-Good String"
layout: "post"
diff: 普及/提高-
pid: CF1385D
tag: ['分治']
---

# a-Good String

## 题目描述

You are given a string $ s[1 \dots n] $ consisting of lowercase Latin letters. It is guaranteed that $ n = 2^k $ for some integer $ k \ge 0 $ .

The string $ s[1 \dots n] $ is called  $ c $ -good if at least one of the following three conditions is satisfied:

- The length of $ s $ is $ 1 $ , and it consists of the character $ c $ (i.e. $ s_1=c $ );
- The length of $ s $ is greater than $ 1 $ , the first half of the string consists of only the character $ c $ (i.e. $ s_1=s_2=\dots=s_{\frac{n}{2}}=c $ ) and the second half of the string (i.e. the string $ s_{\frac{n}{2} + 1}s_{\frac{n}{2}         + 2} \dots s_n $ ) is a  $ (c+1) $ -good string;
- The length of $ s $ is greater than $ 1 $ , the second half of the string consists of only the character $ c $ (i.e. $ s_{\frac{n}{2} + 1}=s_{\frac{n}{2} + 2}=\dots=s_n=c $ ) and the first half of the string (i.e. the string $ s_1s_2 \dots         s_{\frac{n}{2}} $ ) is a  $ (c+1) $ -good string.

For example: "aabc" is 'a'-good, "ffgheeee" is 'e'-good.

In one move, you can choose one index $ i $ from $ 1 $ to $ n $ and replace $ s_i $ with any lowercase Latin letter (any character from 'a' to 'z').

Your task is to find the minimum number of moves required to obtain an 'a'-good string from $ s $ (i.e.  $ c $ -good string for $ c= $ 'a'). It is guaranteed that the answer always exists.

You have to answer $ t $ independent test cases.

Another example of an 'a'-good string is as follows. Consider the string $ s =  $ "cdbbaaaa". It is an 'a'-good string, because:

- the second half of the string ("aaaa") consists of only the character 'a';
- the first half of the string ("cdbb") is 'b'-good string, because: 
  - the second half of the string ("bb") consists of only the character 'b';
  - the first half of the string ("cd") is 'c'-good string, because: 
      - the first half of the string ("c") consists of only the character 'c';
      - the second half of the string ("d") is 'd'-good string.

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1       \le t \le 2 \cdot 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

The first line of the test case contains one integer $ n $ ( $ 1 \le n \le 131~072 $ ) — the length of $ s $ . It is guaranteed that $ n = 2^k $ for some integer $ k \ge 0 $ . The second line of the test case contains the string $ s $ consisting of $ n $ lowercase Latin letters.

It is guaranteed that the sum of $ n $ does not exceed $ 2       \cdot 10^5 $ ( $ \sum n \le 2 \cdot 10^5 $ ).

## 输出格式

For each test case, print the answer — the minimum number of moves required to obtain an 'a'-good string from $ s $ (i.e.  $ c $ -good string with $ c = $ 'a'). It is guaranteed that the answer exists.

## 样例 #1

### 输入

```
6
8
bbdcaaaa
8
asdfghjk
8
ceaaaabb
8
bbaaddcc
1
z
2
ac
```

### 输出

```
0
7
4
5
1
1
```



---

---
title: "Bewitching Stargazer"
layout: "post"
diff: 普及/提高-
pid: CF2053C
tag: ['递归', '分治']
---

# Bewitching Stargazer

## 题目描述

「我祈祷能拥有一颗透明的心，以及一双满含泪水的眼睛...」

—— 逃跑计划，《夜空中最亮的星》

Iris 仰望星空时，脑海中产生了一个有趣的问题。她希望你能帮忙解决这个问题，据说这样能引发一场流星雨。

夜空中有 $n$ 颗星星，排列成一行。Iris 拿着望远镜来观察这些星星。

最初，她观察整个区间 $[1, n]$，此时她的幸运值为 $0$。为了找到每个观察区间 $[l, r]$ 中的中间星星，Iris 开始了以下的递归过程：

- 首先，她计算中点位置 $m = \left\lfloor \frac{l+r}{2} \right\rfloor$。
- 如果区间长度（即 $r - l + 1$）是偶数，则她将该区间分成两个长度相等的子区间 $[l, m]$ 和 $[m+1, r]$，继续观察。
- 如果是奇数，则她会将望远镜对准第 $m$ 颗星星，幸运值增加 $m$；之后，如果 $l \neq r$，她会继续观察新产生的两个区间 $[l, m-1]$ 和 $[m+1, r]$。

Iris 有点懒，并以一个整数 $k$ 表示她的懒惰阈值：在观察过程中，任何长度严格小于 $k$ 的区间 $[l, r]$ 她都不会再继续观察。请你预测她最终的幸运值会是多少。

## 输入格式

输入包含多组测试用例。第一行是一个整数 $t$（$1 \leq t \leq 10^5$），代表测试用例的数量。接下来每组测试用例每行包括两个整数 $n$ 和 $k$（$1 \leq k \leq n \leq 2 \cdot 10^9$）。

## 输出格式

对每一个测试用例，输出一个整数，表示最终的幸运值。

## 说明/提示

在第一个测试用例中，初始观察区间是 $[1, 7]$。由于该区间长度为奇数，Iris 聚焦于第 $4$ 颗星星，幸运值增加 $4$。然后她将观察区间分成 $[1, 3]$ 和 $[5, 7]$。$[1, 3]$ 再次是奇数，于是她观察第 $2$ 颗星星，幸运值再增 $2$。此后其被分为 $[1, 1]$ 和 $[3, 3]$，因其长度都小于 $2$，所以不再观察。区间 $[5, 7]$ 的过程类似，最终幸运值增加 $6$。所以最终的幸运值为 $4 + 2 + 6 = 12$。

在最后一个测试用例中，Iris 最终观察到了所有星星，其最终幸运值为 $1 + 2 + \cdots + 8\,765\,432 = 38\,416\,403\,456\,028$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6
7 2
11 3
55 13
5801 6
8919 64
8765432 1
```

### 输出

```
12
18
196
1975581
958900
38416403456028
```



---

