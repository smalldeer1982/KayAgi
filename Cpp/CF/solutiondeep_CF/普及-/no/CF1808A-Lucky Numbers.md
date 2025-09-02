# 题目信息

# Lucky Numbers

## 题目描述

Olympus City recently launched the production of personal starships. Now everyone on Mars can buy one and fly to other planets inexpensively.

Each starship has a number —some positive integer $ x $ . Let's define the luckiness of a number $ x $ as the difference between the largest and smallest digits of that number. For example, $ 142857 $ has $ 8 $ as its largest digit and $ 1 $ as its smallest digit, so its luckiness is $ 8-1=7 $ . And the number $ 111 $ has all digits equal to $ 1 $ , so its luckiness is zero.

Hateehc is a famous Martian blogger who often flies to different corners of the solar system. To release interesting videos even faster, he decided to buy himself a starship. When he came to the store, he saw starships with numbers from $ l $ to $ r $ inclusively. While in the store, Hateehc wanted to find a starship with the luckiest number.

Since there are a lot of starships in the store, and Hateehc can't program, you have to help the blogger and write a program that answers his question.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1808A/e10cd9aa8c24a123d5e125320e42ed0d55b601c6.png)

## 说明/提示

Let's look at two test examples:

- the luckiness of the number $ 59 $ is $ 9 - 5 = 4 $ ;
- the luckiness of $ 60 $ equals $ 6 - 0 = 6 $ ;
- the luckiness of $ 61 $ equals $ 6 - 1 = 5 $ ;
- the luckiness of $ 62 $ equals $ 6 - 2 = 4 $ ;
- the luckiness of $ 63 $ is $ 6 - 3 = 3 $ .

 Thus, the luckiest number is $ 60 $ .In the fifth test example, the luckiest number is $ 90 $ .

## 样例 #1

### 输入

```
5
59 63
42 49
15 15
53 57
1 100```

### 输出

```
60
49
15
57
90```

# AI分析结果

### 题目内容
# 幸运数

## 题目描述
奥林匹斯城最近开始生产个人星际飞船。现在火星上的每个人都可以购买一艘，并以低廉的价格飞往其他星球。

每艘星际飞船都有一个编号——某个正整数 $x$ 。我们将数字 $x$ 的幸运程度定义为该数字中最大数字与最小数字的差值。例如，$142857$ 的最大数字是 $8$ ，最小数字是 $1$ ，所以它的幸运程度是 $8 - 1 = 7$ 。而数字 $111$ 的所有数字都等于 $1$ ，所以它的幸运程度为零。

Hateehc 是一位著名的火星博主，他经常飞往太阳系的不同角落。为了更快地发布有趣的视频，他决定给自己买一艘星际飞船。当他来到商店时，他看到了编号从 $l$ 到 $r$ （包括 $l$ 和 $r$ ）的星际飞船。在商店里时，Hateehc 想找到一艘编号最幸运的星际飞船。

由于商店里有很多星际飞船，而且 Hateehc 不会编程，你必须帮助这位博主并编写一个程序来回答他的问题。

## 说明/提示
让我们看两个测试示例：
 - 数字 $59$ 的幸运程度是 $9 - 5 = 4$ ；
 - 数字 $60$ 的幸运程度等于 $6 - 0 = 6$ ；
 - 数字 $61$ 的幸运程度等于 $6 - 1 = 5$ ；
 - 数字 $62$ 的幸运程度等于 $6 - 2 = 4$ ；
 - 数字 $63$ 的幸运程度是 $6 - 3 = 3$ 。

 因此，最幸运的数字是 $60$ 。在第五个测试示例中，最幸运的数字是 $90$ 。

## 样例 #1
### 输入
```
5
59 63
42 49
15 15
53 57
1 100
```
### 输出
```
60
49
15
57
90
```
### 算法分类
枚举

### 综合分析与结论
题目要求在给定的数字区间内找出幸运程度最高的数字，幸运程度定义为数字中最大数字与最小数字的差值。由于数据范围未明确提及，但从题目性质来看，直接对区间内每个数字进行枚举并计算其幸运程度，然后找出最大值是一种可行的方法。因为没有题解，以下给出通用思路：
1. 遍历区间 $[l, r]$ 内的每一个整数。
2. 对于每个整数，分别找出其最大和最小数字，计算差值得到幸运程度。
3. 记录幸运程度最大的数字。

### 扩展思路
对于此类题目，若数据范围较大，可考虑优化枚举方式，例如根据数字特征进行剪枝。例如，若已知数字的位数，可通过一些数学关系提前判断某些数字不可能是幸运程度最大的，从而减少枚举量。另外，也可以考虑将数字按一定规则分组，分别在组内进行枚举和比较。

### 洛谷相似题目推荐
1. P1036 [NOIP2002 普及组] 选数：同样涉及对给定范围内数字的筛选与计算，通过枚举不同组合来求解满足条件的结果。
2. P1164 小A点菜：本质是在一定的限制条件下对所有可能的点菜组合进行枚举，与本题枚举数字找最值思路类似。
3. P1219 [USACO1.5]八皇后 Checker Challenge：通过枚举八皇后在棋盘上的不同摆放位置，来寻找满足条件的方案，也是典型的枚举类题目。 

---
处理用时：26.12秒