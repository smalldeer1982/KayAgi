---
title: "Binary Blocks"
layout: "post"
diff: 普及+/提高
pid: CF838A
tag: []
---

# Binary Blocks

## 题目描述

You are given an image, that can be represented with a $ 2 $ -d $ n $ by $ m $ grid of pixels. Each pixel of the image is either on or off, denoted by the characters "0" or "1", respectively. You would like to compress this image. You want to choose an integer $ k&gt;1 $ and split the image into $ k $ by $ k $ blocks. If $ n $ and $ m $ are not divisible by $ k $ , the image is padded with only zeros on the right and bottom so that they are divisible by $ k $ . Each pixel in each individual block must have the same value. The given image may not be compressible in its current state. Find the minimum number of pixels you need to toggle (after padding) in order for the image to be compressible for some $ k $ . More specifically, the steps are to first choose $ k $ , then the image is padded with zeros, then, we can toggle the pixels so it is compressible for this $ k $ . The image must be compressible in that state.

## 输入格式

The first line of input will contain two integers $ n,m $ ( $ 2<=n,m<=2500 $ ), the dimensions of the image.

The next $ n $ lines of input will contain a binary string with exactly $ m $ characters, representing the image.

## 输出格式

Print a single integer, the minimum number of pixels needed to toggle to make the image compressible.

## 说明/提示

We first choose $ k=2 $ .

The image is padded as follows:

`<br></br>001000<br></br>101100<br></br>110010<br></br>000000<br></br>`We can toggle the image to look as follows:

`<br></br>001100<br></br>001100<br></br>000000<br></br>000000<br></br>`We can see that this image is compressible for $ k=2 $ .

## 样例 #1

### 输入

```
3 5
00100
10110
11001

```

### 输出

```
5

```

