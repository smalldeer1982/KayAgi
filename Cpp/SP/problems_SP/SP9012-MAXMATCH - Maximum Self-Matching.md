---
title: "MAXMATCH - Maximum Self-Matching"
layout: "post"
diff: 难度0
pid: SP9012
tag: []
---

# MAXMATCH - Maximum Self-Matching

## 题目描述

给定一个仅包含字母 'a'、'b' 和 'c' 的字符串 **s**。

定义一个匹配函数 m $_{s}$(i)，表示字符串 **s** 和它自身向右平移 i 位后的字符串中，字符对齐匹配的数量。具体来说，m $_{s}$(i) 是指在 **s** 的第 0 个字符与其副本的第 i 个字符对齐时，两个字符串中相同字符的个数。

你的任务是计算 m $_{s}$(i) 的最大值，其中 i 的范围是 1 ≤ i ≤ |**s**|。并且，你还需要输出所有能使 m $_{s}$(i) 达到最大值的 i，要求这些 i 按从小到大的顺序排列。

## 输入格式

输入为一个字符串 **s**，其中 2 ≤ |**s**| ≤ 10$^5$。

## 输出格式

输出包含两行：
- 第一行输出最大匹配数 m $_{s}$(i) 的值。
- 第二行输出所有能够达到这个最大值的位移 i，并按升序排列。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
caccacaa
```

### 输出

```
4\n3\n\nExplanation:\n\ncaccacaa\n   caccacaa\n\n\n The bold characters indicate the ones that match when shift = 3.\n\n
```

