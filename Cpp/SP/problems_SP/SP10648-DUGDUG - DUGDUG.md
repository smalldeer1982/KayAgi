---
title: "DUGDUG - DUGDUG"
layout: "post"
diff: 难度0
pid: SP10648
tag: []
---

# DUGDUG - DUGDUG

## 题目描述

Dug Dug 是一个甜美可爱的小女孩，她非常喜欢我送给她的甜食和巧克力。一天，我对她说：「DUG DUG，你很甜美，也很喜欢甜食。」我告诉她，我会给她很多甜食，但她得告诉我，在不改变句子意思的前提下，有多少种方法可以交换这个句子中的单词。这里允许同时交换一个或多个成对的单词，但这些成对的单词必须是彼此不同的单词。Dug Dug 对此感到困惑，生气地说如果想给甜食就快给，不然就快走。我说：「我，我会的，我我我会给。」她得到了巧克力，不过你可没这么容易。

你的任务是找出一个句子中可以在不改变意义的前提下进行单词交换的所有可能方法。记住，你可以同时交换一个或多个成对的单词，但这些成对的单词必须是不同的。

## 输入格式

输入由多行组成，每行是一个长度不超过 5000 个字符的句子。

## 输出格式

对每一行输入，输出一个整数，表示该句子中可以进行的单词交换方式的数量。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
DUG DUG you are sweet and also like sweet\nI i will , i i i will give\nOk done you will get what you want\nDone !!!!!!!!\n\n
```

### 输出

```
3\n13\n1\n0\n\nExplaination: \nFor the first sentence "DUG DUG you are sweet and also like sweet" there are three ways - \n1) You can change the first "DUG" with second "DUG"\n2) You can change the first "sweet" with second "sweet"\n3) You can change the first "DUG" with second "DUG" and first "sweet" with second "sweet".
```

