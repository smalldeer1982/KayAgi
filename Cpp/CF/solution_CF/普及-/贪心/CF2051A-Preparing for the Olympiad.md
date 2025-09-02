# Preparing for the Olympiad

## 题目描述

Monocarp 和 Stereocarp正在准备奥林匹克。现在仅剩 $ n $ 天奥林匹克就要开始了。在这第 $ i $天，如果Monocarp 准备训练，那么他将完成$ a_i $题，同样的，如果Stereocarp也在这天准备训练，那么他将完成$ b_i $题。

Monocarp 可以在任意一天进行训练，然而，Stereocarp在观察他，并且学习他的计划：如果Monocarp在第$ i $（$ i<n $）天进行训练,那么Stereocarp将在第（$i+1$）天进行训练。

Monocarp想要制定一个计划使得他与Stereocarp的训练题目量相差最大。形式化的：Monocarp想要使（$m-s$）的值最大，其中$m$表示他完成的题目量，$s$表示Stereocarp完成的题目量s是立体果解决的问题数。帮助Monocarp确定他们之间解决问题数量的最大可能差。

## 说明/提示

在第一个测试用例中，Monocarp最好两天都训练；然后Stereocarp将在第二天训练

在第二个测试用例中，Monocarp最好在唯一一天训练，Stereocarp根本不会训练。

在第三个测试用例中，Monocarp最好在最后一天训练（而且只在当天）。

在第四个测试用例中，Monocarp最好在几天内训练1,3,4,6; 然后Stereocarp将训练2,4,5天

## 样例 #1

### 输入

```
4
2
3 2
2 1
1
5
8
3
1 1 1
2 2 2
6
8 2 5 6 2 6
8 2 7 4 3 4```

### 输出

```
4
5
1
16```

