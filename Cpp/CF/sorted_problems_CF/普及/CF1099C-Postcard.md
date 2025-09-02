---
title: "Postcard"
layout: "post"
diff: 普及/提高-
pid: CF1099C
tag: []
---

# Postcard

## 题目描述

Andrey received a postcard from Irina. It contained only the words "Hello, Andrey!", and a strange string consisting of lowercase Latin letters, snowflakes and candy canes. Andrey thought that this string is an encrypted message, and decided to decrypt it.

Andrey noticed that snowflakes and candy canes always stand after the letters, so he supposed that the message was encrypted as follows. Candy cane means that the letter before it can be removed, or can be left. A snowflake means that the letter before it can be removed, left, or repeated several times.

For example, consider the following string:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1099C/29c2aaaec4bcea3ed5c1b5a1ebd8cbd0c6df45f2.png)This string can encode the message «happynewyear». For this, candy canes and snowflakes should be used as follows:

- candy cane 1: remove the letter w,
- snowflake 1: repeat the letter p twice,
- candy cane 2: leave the letter n,
- snowflake 2: remove the letter w,
- snowflake 3: leave the letter e.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1099C/26482915a1d9df0d76c8d735f29de9bbb88caf58.png)Please note that the same string can encode different messages. For example, the string above can encode «hayewyar», «happpppynewwwwwyear», and other messages.

Andrey knows that messages from Irina usually have a length of $ k $ letters. Help him to find out if a given string can encode a message of $ k $ letters, and if so, give an example of such a message.

## 输入格式

The first line contains the string received in the postcard. The string consists only of lowercase Latin letters, as well as the characters «\*» and «?», meaning snowflake and candy cone, respectively. These characters can only appear immediately after the letter. The length of the string does not exceed $ 200 $ .

The second line contains an integer number $ k $ ( $ 1 \leq k \leq 200 $ ), the required message length.

## 输出格式

Print any message of length $ k $ that the given string can encode, or «Impossible» if such a message does not exist.

## 样例 #1

### 输入

```
hw?ap*yn?eww*ye*ar
12

```

### 输出

```
happynewyear

```

## 样例 #2

### 输入

```
ab?a
2

```

### 输出

```
aa
```

## 样例 #3

### 输入

```
ab?a
3

```

### 输出

```
aba
```

## 样例 #4

### 输入

```
ababb
5

```

### 输出

```
ababb
```

## 样例 #5

### 输入

```
ab?a
1

```

### 输出

```
Impossible
```

