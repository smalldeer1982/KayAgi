# [GCPC 2023] Freestyle Masonry

## 题目描述

Fred 得到了一个简单的任务，他只需要建造一堵 $w\times h$ 的墙。

![](https://cdn.luogu.com.cn/upload/image_hosting/jdfpt5uu.png)

:::align{center}
一种有趣的砖块布局，照片来自 [Bobo Boom](https://commons.wikimedia.org/wiki/File:Intricate_patterns_in_brick-laying_(29947248771).jpg)
:::

为了让任务更简单，他得到了足够多的 $2\times1$ 砖块，以及一些 $1\times1$ 砖块来完成这堵墙。
Fred 觉得这任务应该不难，于是就开始动手建造，没有太多考虑设计。
直到他用完了所有的 $1\times1$ 砖块，Fred 才意识到这可能是个糟糕的决定……

:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/f5wolnfs.png)

图 F.1：样例输入 2 的可视化。红色的砖块已经被 Fred 放置。蓝色的砖块仍需放置以完成墙体（在这种情况下只有这一种可能的设计）。
:::

也许他本该在开始前先做个计划，但现在已经太晚了。
Fred 现在只剩下一堆 $2\times1$ 砖块，他想用这些砖块完成墙体。
他还能只用剩下的 $2\times1$ 砖块完成这堵墙吗？
注意，建造的墙必须恰好宽 $w$ 个单位，高 $h$ 个单位。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
0 0 1```

### 输出

```
possible```

## 样例 #2

### 输入

```
6 3
1 0 1 1 0 1```

### 输出

```
possible```

## 样例 #3

### 输入

```
6 2
1 0 1 1 0 1```

### 输出

```
impossible```

## 样例 #4

### 输入

```
5 2
1 2 3 2 2```

### 输出

```
impossible```

