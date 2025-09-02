---
title: "Pushing Balls"
layout: "post"
diff: 普及-
pid: CF2090B
tag: ['枚举']
---

# Pushing Balls

## 题目描述

Ecrade 有一个 $$$n \times m$$$ 的网格，初始为空。他通过多次（可能为零次）推球操作在其中放置了若干球。

每次操作时，他可以选择从某行的最左边缘或某列的最上边缘向网格内推入一个球。

当一个球朝某个方向移动时：
- 若目标位置原本没有球，则新推入的球会占据该位置并停止。
- 若目标位置已有球，则新推入的球会占据该位置，而原位置的球将继续沿相同方向移动到下一个位置。

注意：若某行或某列已满（即该行或列所有位置都有球），则不能从该行或列推入新球。

给定网格每个位置是否有球的最终状态，请判断是否存在一种推球操作序列使得最终状态可以被达成。

## 输入格式

第一行包含一个整数 $$$t$$$（$$$1 \le t \le 10\,000$$$）——测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含两个整数 $$$n$$$ 和 $$$m$$$（$$$1 \le n, m \le 50$$$）。

接下来是 $$$n$$$ 行，每行包含恰好 $$$m$$$ 个字符（仅由 0 和 1 构成），描述网格的最终状态。当且仅当输入中对应位置为 1 时，该位置存在一个球。

保证所有测试用例的 $$$n \cdot m$$$ 之和不超过 $$$10\,000$$$。

## 输出格式

对于每个测试用例，若存在合法操作序列达成最终状态则输出 "Yes"（不带引号），否则输出 "No"（不带引号）。

答案大小写不敏感（例如 "YES"、"yEs" 和 "yes" 均视为肯定回答）。


## 说明/提示

为简化描述：
- 若从第 $$$i$$$ 行的最左边缘推入球，称该操作为 $$$\text{ROW}\\ i$$$
- 若从第 $$$i$$$ 列的最上边缘推入球，称该操作为 $$$\text{COL}\\ i$$$

以下示例矩阵中的非零数字 $$$x$$$ 表示第 $$$x$$$ 次推入的球。

第一个测试用例的一个可能操作序列：
$$$\begin{pmatrix}0&0&0\\\\0&0&0\\\\0&0&0\end{pmatrix}\xrightarrow{\text{ROW}\\ 3}\xrightarrow{\text{ROW}\\ 3} \begin{pmatrix}0&0&0\\\\0&0&0\\\\2&1&0\end{pmatrix}\xrightarrow{\text{COL}\\ 3}\xrightarrow{\text{COL}\\ 3} \begin{pmatrix}0&0&4\\\\0&0&3\\\\2&1&0\end{pmatrix}$$$

第二个测试用例的一个可能操作序列：
$$$\begin{pmatrix}0&0&0\\\\0&0&0\\\\0&0&0\end{pmatrix}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 2} \begin{pmatrix}0&0&0\\\\3&2&1\\\\0&0&0\end{pmatrix}\xrightarrow{\text{COL}\\ 2}\xrightarrow{\text{COL}\\ 2} \begin{pmatrix}0&5&0\\\\3&4&1\\\\0&2&0\end{pmatrix}$$$

第三个测试用例的一个可能操作序列：
$$$\begin{pmatrix}0&0&0\\\\0&0&0\\\\0&0&0\end{pmatrix}\xrightarrow{\text{ROW}\\ 1}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 3} \begin{pmatrix}1&0&0\\\\2&0&0\\\\3&0&0\end{pmatrix}\xrightarrow{\text{COL}\\ 3}\xrightarrow{\text{COL}\\ 3}\xrightarrow{\text{COL}\\ 3} \begin{pmatrix}1&0&6\\\\2&0&5\\\\3&0&4\end{pmatrix}\xrightarrow{\text{ROW}\\ 1}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 3} \begin{pmatrix}7&1&6\\\\8&2&5\\\\9&3&4\end{pmatrix}$$$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3 3
001
001
110
3 3
010
111
010
3 3
111
111
111
3 3
000
000
000
3 3
000
000
001
```

### 输出

```
YES
YES
YES
YES
NO
```

