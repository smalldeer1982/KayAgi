---
title: "Flag"
layout: "post"
diff: 提高+/省选-
pid: CF1181C
tag: []
---

# Flag

## 题目描述

Innokenty works at a flea market and sells some random stuff rare items. Recently he found an old rectangular blanket. It turned out that the blanket is split in $ n \cdot m $ colored pieces that form a rectangle with $ n $ rows and $ m $ columns.

The colored pieces attracted Innokenty's attention so he immediately came up with the following business plan. If he cuts out a subrectangle consisting of three colored stripes, he can sell it as a flag of some country. Innokenty decided that a subrectangle is similar enough to a flag of some country if it consists of three stripes of equal heights placed one above another, where each stripe consists of cells of equal color. Of course, the color of the top stripe must be different from the color of the middle stripe; and the color of the middle stripe must be different from the color of the bottom stripe.

Innokenty has not yet decided what part he will cut out, but he is sure that the flag's boundaries should go along grid lines. Also, Innokenty won't rotate the blanket. Please help Innokenty and count the number of different subrectangles Innokenty can cut out and sell as a flag. Two subrectangles located in different places but forming the same flag are still considered different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/494207e7afc2afb0a92cabdbe28df74b297d7a05.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/bf1fd899ce886e9465b7b7b74a12cc65eeb4730a.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/2001580d899bd2541bc7b915c1e12a9296691f88.png)These subrectangles are flags.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/d3fe578ba6805980b83fc35618d2586cbe052eec.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/c8cccb677c4f89c97c0b93403d684ef51dc19f7b.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/f4187f8dfb60c5ca782d886e4ab9e9e44b3326c1.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/34a82b162310ca048fe08c0b6371d0f9ce92a778.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/3cd039fbd04d9723c1b3471017ca771c3642e103.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/3c32a8057cfda2e0fc99a2ef588b87496c3fffd1.png)These subrectangles are not flags.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 1\,000 $ ) — the number of rows and the number of columns on the blanket.

Each of the next $ n $ lines contains $ m $ lowercase English letters from 'a' to 'z' and describes a row of the blanket. Equal letters correspond to equal colors, different letters correspond to different colors.

## 输出格式

In the only line print the number of subrectangles which form valid flags.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/05a1643de7735bba2acb4c3894fc0301d9b8432b.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1181C/e8fe611a7e2f3e5dd18a97bf8757649395a7b53d.png)The selected subrectangles are flags in the first example.

## 样例 #1

### 输入

```
4 3
aaa
bbb
ccb
ddd

```

### 输出

```
6

```

## 样例 #2

### 输入

```
6 1
a
a
b
b
c
c

```

### 输出

```
1

```

