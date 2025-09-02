---
title: "PPBRJB - Red John is Back"
layout: "post"
diff: 难度0
pid: SP21525
tag: []
---

# PPBRJB - Red John is Back

## 题目描述

Red John 又犯了一起命案，但这一次，他没有留下标志性的红色笑脸，而是给 Patrick Jane 留下一个需要解开的谜题。他还给 Teresa Lisbon 发短信表示，如果 Patrick 解开谜题，他就会自首。这个谜题是这样的：

在受害者的房子里，有一面尺寸为 4×N 的墙。受害者家中有无限多的两种规格的砖块：尺寸为 4×1 和 1×4。墙上有一个隐藏的保险箱，只有用特定的砖块排列才能打开。每种排列方式下，砖块必须完全覆盖整面墙。保险箱中有一张写有电话号码的字条，这对案件至关重要。Gale Bertram 想知道一共有多少种不同的方式可以排列这些砖块，使得每种都是独特的新排列。他将这些方法的总数称为 M。由于 Red John 学习过高级数学，他要求 Patrick 计算 M 以下或等于 M 的素数个数（即 P）。如果 Patrick 计算出正确的 P，Teresa 就使用保险箱中的电话号码联系 Red John，他便会投降。否则，Teresa 会在一周后接到另一通与谋杀有关的电话。

你的任务是帮助 Patrick 正确解开这个谜题。

## 输入格式

输入的第一行包含一个整数 T，接下来的 T 行每行包含一个整数 N。$1 \leq T \leq 20, 1 \leq N \leq 40$

## 输出格式

对于每个测试用例，输出一行结果。结果应为小于或等于 M 的素数的个数。

**样例**

**输入**

```
2  
1  
7
```

**输出**

```
0  
3
```

**说明**

- 对于 N = 1，砖块只能以 1 种方式排列。
  小于或等于 1 的素数个数为 0，因此答案是 0。

- 对于 N = 7，砖块有 5 种排列方法，而小于或等于 5 的素数有 3 个，因此答案是 3。

来源：Hackerrank.com

比赛由 [প্রোগ্রামিং প্রবলেম (Programming Problem in Bengali)](https://www.facebook.com/groups/bengaliprogramming/) 组织。

 **本翻译由 AI 自动生成**

