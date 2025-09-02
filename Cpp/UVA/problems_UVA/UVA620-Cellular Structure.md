---
title: "Cellular Structure"
layout: "post"
diff: 难度0
pid: UVA620
tag: []
---

# Cellular Structure

## 题目描述

一个只由A和B构成的字符串（不为空，默认初始的字符串为A）有以下的变换方式：

- SIMPLE: 在串的末尾增加一个字符A
- FULLY-GROWN: 在串的末尾增加串AB
- MUTAGENIC: 在串的开头增加字符B，末尾增加字符A
- MUTANT: 其他变换方式

题目要求给你n个字符串，判断它经历的最后一次变换是什么。如果有多种情况，按照上表中的先后顺序选取最先出现的输出。

## 输入格式

第一行一个正整数n，表示字符串的个数。
之后的n行每行一个字符串。

## 输出格式

针对每一行的字符串，输出它经历的最后一次变换，并换行。

#### 样例输入
```
4
A
AAB
BAAB
BAABA
```

#### 样例输出
```
SIMPLE
FULLY-GROWN
MUTANT
MUTAGENIC
```

## 说明/提示

- 第一个：就是A。。。
- 第二个：A->AAB(FULLY-GROWN)
- 第三个：MUTANT
- 第四个：A->AAB->BAABA(MUTAGENIC)

感谢@水手hwy 提供的翻译

## 样例 #1

### 输入

```
4
A
AAB
BAAB
BAABA
```

### 输出

```
SIMPLE
FULLY-GROWN
MUTANT
MUTAGENIC
```

