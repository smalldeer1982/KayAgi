# 题目信息

# MUH and Cube Walls

## 题目描述

Polar bears Menshykov and Uslada from the zoo of St. Petersburg and elephant Horace from the zoo of Kiev got hold of lots of wooden cubes somewhere. They started making cube towers by placing the cubes one on top of the other. They defined multiple towers standing in a line as a wall. A wall can consist of towers of different heights.

Horace was the first to finish making his wall. He called his wall an elephant. The wall consists of $ w $ towers. The bears also finished making their wall but they didn't give it a name. Their wall consists of $ n $ towers. Horace looked at the bears' tower and wondered: in how many parts of the wall can he "see an elephant"? He can "see an elephant" on a segment of $ w $ contiguous towers if the heights of the towers on the segment match as a sequence the heights of the towers in Horace's wall. In order to see as many elephants as possible, Horace can raise and lower his wall. He even can lower the wall below the ground level (see the pictures to the samples for clarification).

Your task is to count the number of segments where Horace can "see an elephant".

## 说明/提示

The picture to the left shows Horace's wall from the sample, the picture to the right shows the bears' wall. The segments where Horace can "see an elephant" are in gray.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF471D/4bab2ce5008bc40c15cf28d8ffc04197c7f77d57.png)

## 样例 #1

### 输入

```
13 5
2 4 5 5 4 3 2 2 2 3 3 2 1
3 4 4 3 2
```

### 输出

```
2```

# AI分析结果

### 题目内容
# MUH和魔方墙
## 题目描述
来自圣彼得堡动物园的北极熊Menshykov和Uslada，以及来自基辅动物园的大象Horace，不知从何处搞到了大量的木制立方体。他们开始将立方体一个叠一个地摆放，搭建立方塔。他们把排成一排的多个塔定义为一堵墙。一堵墙可以由不同高度的塔组成。

Horace是第一个完成搭建他的墙的。他把自己的墙叫做“大象”。这堵墙由$w$个塔组成。北极熊们也完成了他们的墙，但没有给它命名。他们的墙由$n$个塔组成。Horace看着北极熊们的墙，心想：在这堵墙的多少部分他能“看到一头大象”呢？如果在一段连续的$w$个塔上，这些塔的高度序列与Horace的墙中塔的高度序列相匹配，那么他就能在这一段上“看到一头大象”。为了尽可能多地看到大象，Horace可以升高和降低他的墙。他甚至可以把墙降到地面以下（详见示例图片以获得更清晰的理解）。

你的任务是计算Horace能“看到大象”的片段数量。
## 说明/提示
左边的图片展示了示例中Horace的墙，右边的图片展示了北极熊们的墙。Horace能“看到大象”的片段用灰色表示。
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF471D/4bab2ce5008bc40c15cf28d8ffc04197c7f77d57.png)
## 样例 #1
### 输入
```
13 5
2 4 5 5 4 3 2 2 2 3 3 2 1
3 4 4 3 2
```
### 输出
```
2
```

### 算法分类
字符串（基于KMP算法的字符串匹配结合差分思想）

### 题解综合分析与结论
所有题解的核心思路都是通过差分将原问题转化为差分数组的子串匹配问题，然后使用KMP算法求解。不同题解在实现细节上略有差异，例如差分数组的构建方式、KMP算法中数组的处理以及特判条件的写法等，但整体思路和核心算法一致。

### 通用建议与扩展思路
解决此类问题的关键在于敏锐地发现通过差分能将原问题简化为经典的字符串匹配问题，进而利用KMP算法高效求解。对于类似题目，可以思考能否通过某种变换将复杂问题转化为已知的经典算法可解决的形式。在实现过程中，要注意边界条件和特殊情况的处理，像本题中$b$串长度为1时的特判。

### 拓展题目
1. **P3375 【模板】KMP字符串匹配**：经典的KMP算法模板题，可用于巩固KMP算法的理解和实现。
2. **P5788 [模板] 最长公共子序列**：虽然是求最长公共子序列，但也涉及到序列匹配相关知识，与本题在处理序列关系上有相似之处。
3. **P1308 统计单词数**：字符串匹配相关题目，通过解决本题可以进一步加深对字符串匹配问题的多种处理方式的理解。 

---
处理用时：31.69秒