---
title: "UQAS - Universal Question Answering System"
layout: "post"
diff: 难度0
pid: SP9690
tag: []
---

# UQAS - Universal Question Answering System

## 题目描述

每个学生在学习新知识的过程中，通常需要通过提问来获得帮助。调查显示，有些相似的问题会频繁重复地被提出。因此，开发一个自动问答系统来解答这些常见问题将会非常有益。这个系统不需要任何预先的知识，但它必须能够读取句子并记忆其中提到的事实。每当查询到这些事实时，系统应给出正确的回答。

## 输入格式

输入由多个对话组成。

第一行是一个正整数 $T$，表示接下来的对话数量（$T \le 500$，但请注意，其中 95% 的对话相对较小）。每个对话由一行或多行组成。每行包含一个句子：要么是陈述句，要么是疑问句。陈述句以句号（.）结尾，而疑问句则以问号（?）结尾。每个对话之后还有一行以感叹号（!）结尾的空行。这些陈述句和疑问句的具体定义将在后面详细说明。

句子由单词、空格及标点符号构成。所有单词仅由拉丁字母组成，并区分大小写。**与通常的英语书写规则不同，除非句子的第一个词本身需要大写，否则句子的首字母应该保持小写。** 单词之间没有多余的空格。每个单词最长不超过 10 个字符。每个对话最多可以有 1000 行。

**陈述句**

每个陈述句有以下形式之一：

```
noun_phrase are noun_phrase.
noun_phrase can verb_phrase.
everything which can verb_phrase can verb_phrase.
everything which can verb_phrase are noun_phrase.
```

**名词短语和动词短语都是单个词。** 这些形式的意思是：

- `A are B`：如果 X 是 A，那么 X 是 B。
- `A can B`：如果 X 是 A，那么 X 能够做 B。
- `everything which can A can B`：如果 X 能做到 A，那么 X 也能做到 B。
- `everything which can A are B`：如果 X 能做到 A，那么 X 是 B。

**疑问句**

每个疑问句对应上述的陈述句形式，分别如下：

```
are noun_phrase noun_phrase?
can noun_phrase verb_phrase?
can everything which can verb_phrase verb_phrase?
are everything which can verb_phrase noun_phrase?
```

在每个测试用例中，不同的名词短语数量不超过 100；不同的动词短语数量也不超过 100。

## 输出格式

对于每个测试用例，输出两行。第一行为测试用例编号，从 1 开始计数，第二行包含若干字符，每个问题对应一个字符。字符要么是 **Y**（表示逻辑上能够得出该事实），要么是 **M**（表示不能得出该事实）。请参见示例。

## 说明/提示

在每组数据中，不同的名词短语数量不会超过 100，不同的动词短语数量也不会超过 100。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1
flies can fly.
flies are insects.
everything which can fly are animals.
are everything which can fly insects?
are flies animals?
can flies eat?
everything which can fly can eat.
can flies eat?
Bye!
```

### 输出

```
Case #1:
MYMY
```

