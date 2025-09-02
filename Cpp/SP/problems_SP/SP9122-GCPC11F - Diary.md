---
title: "GCPC11F - Diary"
layout: "post"
diff: 难度0
pid: SP9122
tag: []
---

# GCPC11F - Diary

## 题目描述

现代人习惯用像 RSA 这样的非对称加密算法来确保通信安全。不过，我的哥哥在写他的日记时却偏爱使用一种简单的替换密码。他的方法很简单：将明文中的每个字母用字母表中固定距离的另一个字母替换。如果我们把这个距离 $d$ 设为 5，那 A 就会被替换成 F，B 变成 G，C 变成 H，如此类推，到 Y 会被替换成 D，Z 则换为 E。

如果我们知道距离 $d$，解密是很简单的。然而，哥哥每次写日记都会随机选一个不同的距离。我要解开他的日记，就得先猜测每条记录所用的 $d$。为此，我利用了一个被广泛认识的英文特点：字母 E 的出现频率通常最高。你能帮我写个程序，根据加密文本中最常见的字母被映射为明文中的字母 E 来算出加密的距离 $d$ 吗？当然，我也想要阅读解密后的内容。

## 输入格式

输入包括多个测试用例 $c$ ($1 \leq c \leq 100$)。每一行是一个日记条目，条目中只包含大写字母（A-Z）与空格。所有条目总共最多包含 1000 个字符（包括空格）。

## 输出格式

对每个测试用例，输出一行，显示可能的最小距离 $d$ ($0 \leq d \leq 25$) 及其对应的解密文本。如果因为多种距离都满足条件而导致无法确定具体解密方式，请输出 `NOT POSSIBLE`。注意，空格不参与加密。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
RD TQIJW GWTYMJWX INFWD JSYWNJX ZXJ F XNRUQJ JSHWDUYNTS YJHMSNVZJ
THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG
XVIDRE TFCCVXZRKV GIFXIRDDZEX TFEKVJK UVTIPGKZFE
XVIDRE TFCCVXZRKV GIFXIRDDZEX TFEKVJK
```

### 输出

```
5 MY OLDER BROTHERS DIARY ENTRIES USE A SIMPLE ENCRYPTION TECHNIQUE
10 JXU GKYSA RHEMD VEN ZKCFI ELUH JXU BQPO TEW
17 GERMAN COLLEGIATE PROGRAMMING CONTEST DECRYPTION
NOT POSSIBLE
```

