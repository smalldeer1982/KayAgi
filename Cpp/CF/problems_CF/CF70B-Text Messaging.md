---
title: "Text Messaging"
layout: "post"
diff: 普及/提高-
pid: CF70B
tag: []
---

# Text Messaging

## 题目描述

Fangy the little walrus, as all the modern walruses, loves to communicate via text messaging. One day he faced the following problem: When he sends large texts, they are split into parts each containing $ n $ characters (which is the size of one text message). Thus, whole sentences and words get split!

Fangy did not like it, so he faced the task of breaking the text into minimal messages on his own so that no sentence were broken into pieces when it is sent and the number of text messages to be sent would be minimal. If two consecutive sentences are in different messages, the space between them can be ignored (Fangy does not write this space).

The little walrus's text looks in the following manner:

```
TEXT ::= SENTENCE | SENTENCE SPACE TEXT
SENTENCE ::= WORD SPACE SENTENCE | WORD END
END ::= {'.', '?', '!'}
WORD ::= LETTER | LETTER WORD
LETTER ::= {'a'..'z', 'A'..'Z'}
SPACE ::= ' '
```

SPACE stands for the symbol of a space.

So, how many messages did Fangy send?

## 输入格式

The first line contains an integer $ n $ , which is the size of one message ( $ 2<=n<=255 $ ). The second line contains the text. The length of the text does not exceed $ 10^{4} $ characters. It is guaranteed that the text satisfies the above described format. Specifically, this implies that the text is not empty.

## 输出格式

On the first and only line print the number of text messages Fangy will need. If it is impossible to split the text, print "Impossible" without the quotes.

## 说明/提示

Let's take a look at the third sample. The text will be split into three messages: "Hello!", "Do you like fish?" and "Why?".

## 样例 #1

### 输入

```
25
Hello. I am a little walrus.

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2
How are you?

```

### 输出

```
Impossible

```

## 样例 #3

### 输入

```
19
Hello! Do you like fish? Why?

```

### 输出

```
3

```

