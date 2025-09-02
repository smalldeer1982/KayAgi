---
title: "A Perfectly Balanced String?"
layout: "post"
diff: 普及/提高-
pid: CF1673B
tag: []
---

# A Perfectly Balanced String?

## 题目描述

我们称字符串 $s$ **完美平衡** 当且仅当对于它的所有子串 $t$，不存在两个字符 $u, v$ 其中 $u, v\in s$，使得在 $t$ 中 $u$ 的出现次数与 $t$ 中 $v$ 的出现次数差大于 $1$。

例如，字符串 `aba` 和 `abc` 是完美平衡的，但 `abb` 却不是，因为对于它的字串 `bb` 有 `b` 出现次数为 $2$，而 `a` 出现次数为 $0$，$2 - 0 > 1$。

给出一个字符串，判断它是否完美对称。

**本题有多组数据。**

## 输入格式

第一行，一个整数 $t\ (1 \leq t \leq 10^4)$，表示数据的组数。

接下来 $t$ 行，每行一个字符串 $s\ (1 \leq \lvert s \rvert \leq 2\times 10^5)$。

对于所有测试用例，所有字符串长度之和 $\sum s \leq 2\times 10^5$。

## 输出格式

共 $t$ 行，每行一个字符串 `YES` 或 `NO`，表示 $s$ 是否完美平衡。注意评测机对大小写不敏感，也就是说，若答案为 `YES`，则 `YES` `yes` `Yes` `yEs` 都会被判定为正确。

## 样例 #1

### 输入

```
5
aba
abb
abc
aaaaa
abcba
```

### 输出

```
YES
NO
YES
YES
NO
```

