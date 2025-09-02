---
title: "ULM02 - The Sierpinski Fractal"
layout: "post"
diff: 普及-
pid: SP15728
tag: ['模拟', '递归']
---

# ULM02 - The Sierpinski Fractal

## 题目描述

Consider a regular triangular area, divide it into four equal triangles of half height and remove the one in the middle. Apply the same operation recursively to each of the three remaining triangles. If we repeated this procedure infinite times, we'd obtain something with an area of zero. The fractal that evolves this way is called the Sierpinski Triangle. Although its topological dimension is _2_, its Hausdorff-Besicovitch dimension is_log(3)/log(2)~1.58_, a fractional value (that's why it is called a fractal). By the way, the Hausdorff-Besicovitch dimension of the Norwegian coast is approximately _1.52_, its topological dimension being _1_.

For this problem, you are to outline the Sierpinski Triangle up to a certain recursion depth, using just ASCII characters. Since the drawing resolution is thus fixed, you'll need to grow the picture appropriately. Draw the smallest triangle (that is not divided any further) with two slashes, to backslashes and two underscores like this:

 /\\



---

---
title: "KUSAC - Kusac"
layout: "post"
diff: 普及-
pid: SP16244
tag: ['递归']
---

# KUSAC - Kusac

## 题目描述

Mirko has given up on the difficult coach job and switched to food tasting instead. Having skipped 

breakfast like a professional connoisseur, he is visiting a Croatian cured meat festival. The most 

renowned cook at the festival, Marijan Bajs, has prepared N equal sausages which need to be 

distributed to M tasters such that each taster gets a precisely equal amount. He will use his trusted knife 

to cut them into pieces. 

In order to elegantly divide the sausages, the number of cuts splitting individual sausages must be as 

small as possible. For instance, if there are two sausages and six tasters (the first test case below), it is 

sufficient to split each sausage into three equal parts, making a total of four cuts. On the other hand, if 

there are three sausages and four tasters (the second test case below), one possibility is cutting off three 

quarters of each sausage. Those larger parts will each go to one of the tasrers, while the fourth taster 

will get the three smaller pieces (quarters) left over. 

Mirko wants to try the famous sausages, so he volunteered to help Bajs. Help them calculate the 

minimum total number of cuts needed to carry out the desired division. 

## 输入格式

The first and only line of input contains two positive integers, N and M (1

of sausages and tasters, respectively.

## 输出格式

The first and only line of output must contain the required minimum number of cuts.

## 样例 #1

### 输入

```
2 6
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 4

```

### 输出

```
3

```



---

---
title: "ONP - Transform the Expression"
layout: "post"
diff: 普及-
pid: SP4
tag: ['模拟', '递归', '栈']
---

# ONP - Transform the Expression

## 题目描述

请你将 $n$ 个中缀表达式转换为后缀表达式。

## 输入格式

第一行一个整数 $n$ 代表中缀表达式个数。

接下来 $n$ 行代表 $n$ 个中缀表达式。

## 输出格式

$n$ 行代表每个中缀表达式转换过来的后缀表达式。

## 说明/提示

对于 $100\%$ 的数据，$n \le 100$ , 表达式长度 $\le 400$ 。

Translated by @[稀神探女](/user/85216)

## 样例 #1

### 输入

```
3

(a+(b*c))

((a+b)*(z+x))

((a+t)*((b+(a+c))^(c+d)))
```

### 输出

```
abc*+

ab+zx+*

at+bac++cd+^*
```



---

