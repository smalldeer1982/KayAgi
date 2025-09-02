---
title: "Height to Area"
layout: "post"
diff: 普及/提高-
pid: UVA10522
tag: []
---

# Height to Area

## 题目描述

这是一个简单的几何问题。对于任意三角形 $ABC$，我们知道从点 $A$ 到直线 $BC$（或其延长线）的高为 $H _ a$，从点 $B$ 到直线 $AC$（或其延长线）的高为 $H _ b$，从点 $C$ 到直线 $AB$（或其延长线）的高为 $H _ c$。现在给定这三个值，你需要计算出 $\triangle ABC$ 的面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/825zfkxo.png)

## 输入格式

首先，输入将是一个整数 $n$，表示在输入 $n$ 个无效数据后程序将终止。接下来，每行将有三个实数，分别是$H _ a$、$H _ b$ 和 $H _ c$。

## 输出格式

对于每个输入块，应输出一行。对于有效输入，该行应包含 $\triangle ABC$ 的面积，保留小数点后 $3$ 位；对于无效输入，输出一行“$\texttt{These are invalid inputs!}$”。在 $n$ 个无效输入集合之后，程序将终止。

---

Translated and fixed the picture by User 735713.

## 样例 #1

### 输入

```
1
31.573 22.352 63.448
46.300 50.868 86.683
22.005 24.725 22.914
5.710 25.635 32.805
```

### 输出

```
1517.456
2219.941
311.804
These are invalid inputs!
```

