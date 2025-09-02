---
title: "Translation"
layout: "post"
diff: 入门
pid: CF41A
tag: ['模拟', '字符串']
---

# Translation

## 题目描述

### 题面描述

Berland 和 Birland 两地均有各自的语言，Berlandish 和 Birlandish。V 是一个翻译员，负责将 Berlandish 翻译成 Birlandish。将 Berlandish 翻译成 Birlandish 其实非常简单，只需把这个单词倒过来。比如单词`code`翻译过来就是`edoc`。但是粗心的 V 还是会犯一些错误。现在请你帮她判断一下他翻译的是否正确。

## 输入格式

两行，分别是一个 Berlandish 单词和 V 翻译的 Birlandish 单词。单词中所有字母均为小写拉丁字母（其实就是英文字母）;单词长度均不超过 $100$ 字符，单词中不包含任何多余空格。

## 输出格式

一行，如果 V 的翻译是正确的，输出`YES`。否则输出`NO`。

## 样例 #1

### 输入

```
code
edoc

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
abb
aba

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
code
code

```

### 输出

```
NO

```

