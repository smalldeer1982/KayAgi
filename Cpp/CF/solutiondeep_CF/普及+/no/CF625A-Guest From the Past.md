# 题目信息

# Guest From the Past

## 题目描述

Kolya Gerasimov loves kefir very much. He lives in year 1984 and knows all the details of buying this delicious drink. One day, as you probably know, he found himself in year 2084, and buying kefir there is much more complicated.

Kolya is hungry, so he went to the nearest milk shop. In 2084 you may buy kefir in a plastic liter bottle, that costs $ a $ rubles, or in glass liter bottle, that costs $ b $ rubles. Also, you may return empty glass bottle and get $ c $ ( $ c&lt;b $ ) rubles back, but you cannot return plastic bottles.

Kolya has $ n $ rubles and he is really hungry, so he wants to drink as much kefir as possible. There were no plastic bottles in his 1984, so Kolya doesn't know how to act optimally and asks for your help.

## 说明/提示

In the first sample, Kolya can buy one glass bottle, then return it and buy one more glass bottle. Thus he will drink $ 2 $ liters of kefir.

In the second sample, Kolya can buy two plastic bottle and get two liters of kefir, or he can buy one liter glass bottle, then return it and buy one plastic bottle. In both cases he will drink two liters of kefir.

## 样例 #1

### 输入

```
10
11
9
8
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10
5
6
1
```

### 输出

```
2
```

# AI分析结果

### 题目内容
# 来自过去的客人

## 题目描述
科利亚·格拉西莫夫非常喜欢喝克菲尔（一种发酵乳饮品）。他生活在1984年，熟知购买这种美味饮品的所有细节。有一天，正如你可能知道的，他发现自己来到了2084年，而在那里购买克菲尔要复杂得多。

科利亚饿了，所以他去了最近的牛奶店。在2084年，你可以花\(a\)卢布买一升装的塑料瓶克菲尔，或者花\(b\)卢布买一升装的玻璃瓶克菲尔。此外，你可以退还空玻璃瓶并得到\(c\)（\(c < b\)）卢布，但你不能退还塑料瓶。

科利亚有\(n\)卢布，他真的很饿，所以他想尽可能多地喝克菲尔。1984年没有塑料瓶，所以科利亚不知道如何做出最优选择，于是向你求助。

## 说明/提示
在第一个样例中，科利亚可以买一个玻璃瓶克菲尔，然后退还瓶子，再买一个玻璃瓶克菲尔。这样他就能喝到\(2\)升克菲尔。

在第二个样例中，科利亚可以买两个塑料瓶克菲尔，得到两升克菲尔；或者他可以买一升玻璃瓶克菲尔，退还瓶子，然后买一个塑料瓶克菲尔。在这两种情况下，他都能喝到两升克菲尔。

## 样例 #1
### 输入
```
10
11
9
8
```
### 输出
```
2
```

## 样例 #2
### 输入
```
10
5
6
1
```
### 输出
```
2
```

### 算法分类
贪心

### 综合分析与结论
所有题解都采用贪心算法，核心思路是比较购买塑料瓶克菲尔的单价\(a\)和购买玻璃瓶克菲尔的实际单价\(b - c\)，优先选择单价低的购买。难点在于当玻璃瓶克菲尔实际单价更低时，需保证手中有足够钱\(b\)来购买第一瓶，后续购买则按实际单价\(b - c\)计算。各题解在思路和算法要点上基本一致，主要差异在代码实现方式，如输入输出方式、变量定义、函数封装等。

### 通用建议与扩展思路
通用建议：在实现贪心算法时，要清晰判断贪心的策略和边界条件，注意数据范围，合理选择数据类型避免溢出。代码实现时，可注重代码结构和可读性。
扩展思路：类似题目可以改变物品种类和购买、返还规则，如增加多种不同价格及返还策略的商品，或者改变返还条件等，解题时同样需分析每种商品实际成本，按贪心策略选择。

### 洛谷相似题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) 

---
处理用时：29.37秒