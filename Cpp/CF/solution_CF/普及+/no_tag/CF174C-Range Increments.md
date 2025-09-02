# Range Increments

## 题目描述

Polycarpus is an amateur programmer. Now he is analyzing a friend's program. He has already found there the function rangeIncrement(l, r), that adds 1 to each element of some array $ a $ for all indexes in the segment $ [l,r] $ . In other words, this function does the following:

`<br></br>function rangeIncrement(l, r)<br></br>    for i := l .. r do<br></br>        a[i] = a[i] + 1<br></br>`Polycarpus knows the state of the array $ a $ after a series of function calls. He wants to determine the minimum number of function calls that lead to such state. In addition, he wants to find what function calls are needed in this case. It is guaranteed that the required number of calls does not exceed $ 10^{5} $ .

Before calls of function rangeIncrement(l, r) all array elements equal zero.

## 说明/提示

The first sample requires a call for the entire array, and four additional calls:

- one for the segment \[2,2\] (i.e. the second element of the array),
- three for the segment \[5,5\] (i.e. the fifth element of the array).

## 样例 #1

### 输入

```
6
1 2 1 1 4 1
```

### 输出

```
5
2 2
5 5
5 5
5 5
1 6
```

## 样例 #2

### 输入

```
5
1 0 1 0 1
```

### 输出

```
3
1 1
3 3
5 5
```

# 题解

## 作者：__stick (赞：1)

# 题意

给出一个长度为 $n$ 的数组 $ a[1...\ n] $，给出一个全部为零的数组 $b$，可以将数组 $b$ 区间 $l$ 到 $r$ 之间的数全部加 $1$，问最少几次操作才能使这两个数组完全相同

# 想法

由于加减法是互逆的，我们完全可以理解为将给出的数组进行区间减一操作，直到最后全部为零，这样我们看看能否贪心，我们将给出的数组画成柱状图的样子，只要能一起减，就一起减（俄罗斯方块？），比如样例就长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/i4v8ff28.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

显然只要 $5$ 次那如何实现呢？只要使用一个单调栈即可，我们依次扫描数组，如果当前元素大于上一个元素，那当前元素就需要多减几次，我们将它入栈即可，如果当前元素小于上一个元素，那上一个元素现在就一定要减掉，因为现在不减以后还是要减掉的，所以可以现在就剪掉。就像上图中的第二个元素，如果现在不剪掉，最后还是要单独减掉，我们将它与栈顶元素一起组成区间，一次性减掉即可。

[代码](https://www.luogu.com.cn/paste/6g94wp07)

---

## 作者：AstaSunch_ (赞：0)

# 题目思路
这道有点像[洛谷 P5019 铺设道路](https://www.luogu.com.cn/problem/P5019)。

我们把题目稍微转化一下：给出一个长度为 $n$ 的数组 $ a[1...\ n] $，可以将数组 $a$ 区间 $l$ 到 $r$ 之间的数全部减 $1$ ，问最少需要多少次操作才能使数组元素全为 $0$。

如样例，可以进行以下操作：
```
1 2 1 1 4 1
0 1 0 0 3 0
0 0 0 0 3 0
0 0 0 0 2 0
0 0 0 0 1 0
0 0 0 0 0 0
```
不难得到贪心策略：若 $a_i>a_{i-1},\text{sum}\gets \text{sum}+(a_i-a_{i-1})$;

假设 $a_i$ 和 $a_{i-1}$ 都不为 $0$，则将其同时减 $1$，继续操作下去，那么较小的数肯定会在处理较大的数的过程中变为 $0$。

较大的数也会减少 $a_i-a_{i-1}$。

思路很清晰了，输出过程模拟即可。

---

