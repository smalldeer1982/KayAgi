---
title: "Text Formalization"
layout: "post"
diff: 难度0
pid: UVA10584
tag: []
---

# Text Formalization

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1525

[PDF](https://uva.onlinejudge.org/external/105/p10584.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10584/6e6aaf9c4ca6ed2d8919a5ab63976cb759d9d1bf.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10584/ff85feb1042b09892a062c2517fa0c520e86f480.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10584/ea37ac27aa8ca7130d60f593d1513112d1bc9c39.png)

## 样例 #1

### 输入

```
3 2
"doesn’t" -&gt; "does not"
"isn’t" -&gt; "is not"
"can’t" -&gt; "cannot"
"ACM" -&gt; "Association for Computing Machinery"
"CS" -&gt; "Computing Science"
The ACM can’t solve
all the problems in CS. Though large and having
many resources at its disposal, the ACM doesn’t use magic. Magic isn’t
part of science, and hence not part of CS. Thank you for your
suggestions.
Signed,
ACM
#
The ACM doesn’t like magic.
It’s not that the ACM won’t use it, it’s
just that the ACM doesn’t understand magic.
#
```

### 输出

```
The Association for Computing Machinery (ACM) cannot solve
all the problems in Computing Science (CS). Though large and having
many resources at its disposal, the ACM does not use magic. Magic is not
part of science, and hence not part of CS. Thank you for your
suggestions.
Signed,
ACM
#
The Association for Computing Machinery (ACM) does not like magic.
It’s not that the ACM won’t use it, it’s
just that the ACM does not understand magic.
#
```

