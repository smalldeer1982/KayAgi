# Misha and XOR

## 题目描述

After Misha's birthday he had many large numbers left, scattered across the room. Now it's time to clean up and Misha needs to put them in a basket. He ordered this task to his pet robot that agreed to complete the task at certain conditions. Before the robot puts a number $ x $ to the basket, Misha should answer the question: is it possible to choose one or multiple numbers that already are in the basket, such that their XOR sum equals $ x $ ?

If the answer is positive, you also need to give the indexes of these numbers. If there are multiple options of choosing numbers, you are allowed to choose any correct option. After Misha's answer the robot puts the number to the basket.

Initially the basket is empty. Each integer you put in the basket takes some number. The first integer you put into the basket take number $ 0 $ , the second integer takes number $ 1 $ and so on.

Misha needs to clean up the place as soon as possible but unfortunately, he isn't that good at mathematics. He asks you to help him.

## 说明/提示

The XOR sum of numbers is the result of bitwise sum of numbers modulo 2.

## 样例 #1

### 输入

```
7
7
6
5
4
3
2
1
```

### 输出

```
0
0
0
3 0 1 2
2 1 2
2 0 2
2 0 1
```

## 样例 #2

### 输入

```
2
5
5
```

### 输出

```
0
1 0
```

# 题解

## 作者：Fishing_Boat (赞：0)

线性基版题。

暴力十进制转二进制复杂度难以接受，考虑优化。

可以类似于 ``` bitset ``` 的思想进行压位，每 $55$ 位一起算。

注意这里过程中需要乘 $10$，所以压成 $60$ 位会爆 ```long long```。

此外，实现时一次性添加 $55$ 位，转成二进制后会有前导零，导致总位数可能超过 $2000$ 位。

线性基和输出方案用 ```bitset``` 实现。

$n$ 与 $\log m$ 同阶，总复杂度 $O(\frac{n^3}{w})$。[submission](https://codeforces.com/contest/504/submission/302183021)

---

## 作者：_edge_ (赞：0)

题意，给定若干个数，求它是否为前面数的一个子集的异或值。

线性基模板，注意到暴力除 $2$ 不够快，除以 $2^{55}$ 然后拆开来即可。

线性基用 bitset 实现即可。

[code](https://codeforces.com/contest/504/submission/227289323)

---

