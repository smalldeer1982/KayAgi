---
title: "Main Sequence"
layout: "post"
diff: 普及/提高-
pid: CF286C
tag: []
---

# Main Sequence

## 题目描述

As you know, Vova has recently become a new shaman in the city of Ultima Thule. So, he has received the shaman knowledge about the correct bracket sequences. The shamans of Ultima Thule have been using lots of different types of brackets since prehistoric times. A bracket type is a positive integer. The shamans define a correct bracket sequence as follows:

- An empty sequence is a correct bracket sequence.
- If $ {a_{1},a_{2},...,a_{l}} $ and $ {b_{1},b_{2},...,b_{k}} $ are correct bracket sequences, then sequence $ {a_{1},a_{2},...,a_{l},b_{1},b_{2},...,b_{k}} $ (their concatenation) also is a correct bracket sequence.
- If $ {a_{1},a_{2},...,a_{l}} $ — is a correct bracket sequence, then sequence ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF286C/b33e2eedc865caf6f8fa1a0ee5d1acc87a898f62.png) also is a correct bracket sequence, where $ v $ $ (v&gt;0) $ is an integer.

For example, sequences $ {1,1,-1,2,-2,-1} $ and $ {3,-3} $ are correct bracket sequences, and $ {2,-3} $ is not.

Moreover, after Vova became a shaman, he learned the most important correct bracket sequence $ {x_{1},x_{2},...,x_{n}} $ , consisting of $ n $ integers. As sequence $ x $ is the most important, Vova decided to encrypt it just in case.

Encrypting consists of two sequences. The first sequence $ {p_{1},p_{2},...,p_{n}} $ contains types of brackets, that is, $ p_{i}=|x_{i}| $ ( $ 1<=i<=n $ ). The second sequence $ {q_{1},q_{2},...,q_{t}} $ contains $ t $ integers — some positions (possibly, not all of them), which had negative numbers in sequence $ {x_{1},x_{2},...,x_{n}} $ .

Unfortunately, Vova forgot the main sequence. But he was lucky enough to keep the encryption: sequences $ {p_{1},p_{2},...,p_{n}} $ and $ {q_{1},q_{2},...,q_{t}} $ . Help Vova restore sequence $ x $ by the encryption. If there are multiple sequences that correspond to the encryption, restore any of them. If there are no such sequences, you should tell so.

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=10^{6} $ ). The second line contains $ n $ integers: $ p_{1},p_{2},...,p_{n} $ $ (1<=p_{i}<=10^{9}) $ .

The third line contains integer $ t $ ( $ 0<=t<=n $ ), followed by $ t $ distinct integers $ q_{1},q_{2},...,q_{t} $ $ (1<=q_{i}<=n) $ .

The numbers in each line are separated by spaces.

## 输出格式

Print a single string "NO" (without the quotes) if Vova is mistaken and a suitable sequence $ {x_{1},x_{2},...,x_{n}} $ doesn't exist.

Otherwise, in the first line print "YES" (without the quotes) and in the second line print $ n $ integers $ x_{1},x_{2},...,x_{n} $ $ (|x_{i}|=p_{i}; x_{qj}&lt;0) $ . If there are multiple sequences that correspond to the encrypting, you are allowed to print any of them.

## 样例 #1

### 输入

```
2
1 1
0

```

### 输出

```
YES
1 -1

```

## 样例 #2

### 输入

```
4
1 1 1 1
1 3

```

### 输出

```
YES
1 1 -1 -1

```

## 样例 #3

### 输入

```
3
1 1 1
0

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
4
1 2 2 1
2 3 4

```

### 输出

```
YES
1 2 -2 -1

```

