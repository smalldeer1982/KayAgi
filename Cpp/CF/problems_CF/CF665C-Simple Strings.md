---
title: "Simple Strings"
layout: "post"
diff: 普及-
pid: CF665C
tag: []
---

# Simple Strings

## 题目描述

zscoder loves simple strings! A string $ t $ is called simple if every pair of adjacent characters are distinct. For example ab, aba, zscoder are simple whereas aa, add are not simple.

zscoder is given a string $ s $ . He wants to change a minimum number of characters so that the string $ s $ becomes simple. Help him with this task!

## 输入格式

The only line contains the string $ s $ ( $ 1<=|s|<=2·10^{5} $ ) — the string given to zscoder. The string $ s $ consists of only lowercase English letters.

## 输出格式

Print the simple string $ s' $ — the string $ s $ after the minimal number of changes. If there are multiple solutions, you may output any of them.

Note that the string $ s' $ should also consist of only lowercase English letters.

## 样例 #1

### 输入

```
aab

```

### 输出

```
bab

```

## 样例 #2

### 输入

```
caaab

```

### 输出

```
cabab

```

## 样例 #3

### 输入

```
zscoder

```

### 输出

```
zscoder

```

