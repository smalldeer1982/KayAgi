# [NERC 2020] Japanese Game

## 题目描述

Joseph 非常喜欢日本文化。去年他学习了日本传统服饰和视觉艺术，现在他正试图揭开名为 **Nonogram** 的日本游戏的秘密。

在该游戏的一维版本中，有一排 $n$ 个空单元格，其中一些需要用笔填充。游戏的解由一个称为 **profile** 的描述定义——这是一个由正整数构成的序列，表示连续填充单元格块的长度。例如，profile $[4, 3, 1]$ 表示填充的单元格块依次为 4 个、3 个和 1 个，且这些块之间至少有一个空单元格分隔。

![](https://cdn.luogu.com.cn/upload/image_hosting/7vyfivv3.png)

一个适合 $n = 12$ 且 $p = [4, 3, 1]$ 的解。

![](https://cdn.luogu.com.cn/upload/image_hosting/8lednxrh.png)

一个错误的解：前四个填充的单元格应该是连续的。

![](https://cdn.luogu.com.cn/upload/image_hosting/r2jcjjbb.png)

一个错误的解：最后一个填充的单元格之前应该至少有一个空单元格。

Joseph 发现，对于某些数字 $n$ 和 profile $p$，存在多种填充单元格的方式以满足该 profile。现在，他正在尝试解决一个由 $n$ 个单元格和 profile $p$ 构成的 nonogram 问题。他已经为 $p$ 创建了一个 **mask**——即填充了所有在 nonogram 的每个解中都必须填充的单元格。

![](https://cdn.luogu.com.cn/upload/image_hosting/io9ajtcp.png)

$n = 12$ 且 $p = [4, 3, 1]$ 的 mask：上图中所有填充的单元格在每个解中都必须填充。

休息一段时间后，他丢失了原始的 profile $p$。现在他只有 $n$ 和 mask $m$。请你帮助 Joseph 找到任意一个与 mask $m$ 匹配的 profile $p'$，或者说明不存在这样的 profile（即 Joseph 可能犯了错误）。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
__#_____ ```

### 输出

```
2
3 2```

## 样例 #2

### 输入

```
_#```

### 输出

```
-1```

## 样例 #3

### 输入

```
___ ```

### 输出

```
0```

