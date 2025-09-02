---
title: "Different String"
layout: "post"
diff: 入门
pid: CF1971B
tag: ['模拟']
---

# Different String

## 题目描述

给定一个以小写字母构成的字符串 $s$。

现在你的任务是，重新排列 $s$ 的字符以形成一个不等于 $s$ 的新字符串 $r$。

## 输入格式

**本题单个测试点内包含多组测试数据。**

第一行包含一个整数 $t$（$1\leq t\leq 1000$），表示测试数据组数。

每个测试用例的唯一一行包含一个字符串 $s$，长度最多为 $10$，由小写英文字母组成。

## 输出格式

对于每个测试用例，如果不存在语句中描述的字符串 $r$，则输出`NO`。

否则，输出`YES`。然后，输出一行一个字符串 $r$，由字符串 $s$ 的字母组成。

你可以以任何大小写形式输出`YES`和`NO`。

如果可以有多个答案，则可以输出其中任何一个。

## 样例 #1

### 输入

```
8
codeforces
aaaaa
xxxxy
co
d
nutdealer
mwistht
hhhhhhhhhh
```

### 输出

```
YES
forcodesec
NO
YES
xxyxx
YES
oc
NO
YES
undertale
YES
thtsiwm
NO
```

