---
title: "[GCPC 2024] Fair Fruitcake Fragmenting"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13721
tag: ['计算几何', '2024', 'Special Judge', 'ICPC', '双指针 two-pointer']
---
# [GCPC 2024] Fair Fruitcake Fragmenting
## 题目描述

Frida's birthday is just coming up, and as her best friend, you obviously baked a cake for her.
Since you know that Frida loves rotational symmetry, you thought to bake a cake that
looks the same from above when rotated by $180^\circ$.
Of course, you could have simply baked a boring round cake, but without a perfectly round cake tin, this sounds easier than done.
Therefore, you decided to bake a cake whose shape can be described by straight line segments.

![](https://cdn.luogu.com.cn/upload/image_hosting/j4oo5c4y.png)

:::align{center}

Figure F.1: Visualization of Sample Input 2. The swirly cake looking like an S can be cut into the red and blue part with a single cut.

:::

However, after you are done with your cake, you notice that you also want to cut the cake into two equal pieces, one for Frida and one for yourself.
More precisely, you wonder if it is possible to cut the cake along an infinite line such that it splits into exactly two
parts of equal weight.
You can assume that the cake has uniform density and height.
## 输入格式

The input consists of:
- One line containing an *even* integer $n$ ($4 \leq n\leq 10^5$), the number of points needed to describe the cake's shape.
- $n$ lines, each containing two integers $x$, $y$ ($0\leq x,y \leq 10^6$), the $x$ and $y$ coordinates of a point on the border of the cake's shape.

The following additional guarantees are given for the shape of the cake:
- The cake has a $180^\circ$ rotational symmetry.
- The points are given in counterclockwise order.
- No three consecutive points are collinear.
- The shape is simple (no segments intersect and only consecutive segments touch at their ends).
## 输出格式

Output two different points on the desired line as $x_1/c_1$ $y_1/d_1$ $x_2/c_2$ $y_2/d_2$, where $|x_i|$, $|y_i|$, $|c_i|$ and $|d_i|$ are integers and at most $10^9$, and $x_i/c_i$} is the first coordinate of point $i$ and $y_i/d_i$ is the second ($1\leq i\leq2$). If the denominator of a fraction is $1$ you may output only the numerator. Fractions do not have to be reduced. If there is no such line, output "$\texttt{impossible}$" instead.

It can be shown that if there is a line as desired, it is possible to represent it in the given format.
## 样例

### 样例输入 #1
```
4
0 0
2 0
2 2
0 2
```
### 样例输出 #1
```
1 1 1337/42 3141/1000
```
### 样例输入 #2
```
20
7 1
8 2
8 5
7 6
4 6
4 4
3 4
3 7
6 7
7 8
2 8
1 7
1 4
2 3
5 3
5 5
6 5
6 2
3 2
2 1
```
### 样例输出 #2
```
11 13 -2 -4
```
### 样例输入 #3
```
10
11 5
10 2
12 6
2 2
7 3
1 1
2 4
0 0
10 4
5 3
```
### 样例输出 #3
```
impossible
```


---

---
title: "「EZEC-6」造树"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7390
tag: ['贪心', '2021', 'O2优化', '排序', '构造', '双指针 two-pointer', 'Ad-hoc']
---
# 「EZEC-6」造树
## 题目背景

> 成体系的结论会产出“低猜想水平”的机械推导，但更多的题目中需要“高猜想水平”的灵感。

——command_block 《考前小贴士》

[](https://cdn.luogu.com.cn/upload/image_hosting/1m9hce9x.png)无脑选手出思维题。
## 题目描述

你要帮 djy 造一棵树，满足以下条件：

- 由 $n$ 个点组成。

- $i$ 号点的度数为 $a_i$。

定义一条边 $(i,j)$ 的价值为 $b_i\times b_j$，你要在满足上述两个条件下，使所有边的价值和最大。

保证存在这样的树。
## 输入格式

第一行一个整数 $type$，表示数据生成方式。

若 $type=0$：

第二行一个整数 $n$。

第三行 $n$ 个整数，第 $i$ 个数表示 $a_i$。

第四行 $n$ 个整数，第 $i$ 个数表示 $b_i$。

若 $type=1$：

给出一个数据生成器模板：

```cpp
int a[10000005],b[10000005];
unsigned seed;
unsigned rnd(unsigned x){
	x^=x<<13;
	x^=x>>17;
	x^=x<<5;
	return x;
}
int rad(int x,int y){
	seed=rnd(seed);
	return seed%(y-x+1)+x;
}
void init_data(){
	cin>>seed;
	for(int i=1;i<=n;i++)
		a[i]=1,b[i]=rad(1,500000);
	for(int i=1;i<=n-2;i++)
		a[rad(1,n)]++;
}
```

第二行一个整数 $n$。

之后调用 `init_data()`。

第三行一个整数 $seed$。
## 输出格式

一行一个整数 $ans$，表示最大的价值和。
## 样例

### 样例输入 #1
```
0
5
1 2 3 1 1 
5 3 1 7 9
```
### 样例输出 #1
```
42
```
### 样例输入 #2
```
1
10
114514
```
### 样例输出 #2
```
249899101316
```
## 提示

**本题采用捆绑测试。**

- Subtask0 (10 pts)：$n\le 6$，$type=0$；
- Subtask1 (20 pts)：$n\le 10^3$，$type=0$；
- Subtask2 (10 pts)：$n\le5\times10^5$，$b_i\le2$，$type=0$；
- Subtask3 (20 pts)：$n\le10^5$，$type=0$；
- Subtask4 (20 pts)：$n\le5\times10^5$，$type=0$；
- Subtask5 (20 pts)：$type=1$。

对于 $100\%$ 的数据，$2\le n\le10^7$，$1\le a_i\le n$，$1\le b_i\le5\times10^5$，$type\in\{0,1\}$，$0\le seed<2^{31}$。


---

