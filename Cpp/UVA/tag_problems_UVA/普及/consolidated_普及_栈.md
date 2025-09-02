---
title: "The Blocks Problem"
layout: "post"
diff: 普及/提高-
pid: UVA101
tag: ['模拟', '递归', '栈']
---

# The Blocks Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=37

[PDF](https://uva.onlinejudge.org/external/1/p101.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/4657c698576c8c299dbbf5655d7dbe63bf148978.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/0a0a9b4a15235d9e81d83d5d31ee89ce48870fed.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA101/ca24bcd0ff3af9dc6c1fcefd73c87532e9e05bd4.png)

## 样例 #1

### 输入

```
10
move 9 onto 1
move 8 over 1
move 7 over 1
move 6 over 1
pile 8 over 6
pile 8 over 5
move 2 over 1
move 4 over 9
quit
```

### 输出

```
0: 0
1: 1 9 2 4
2:
3: 3
4:
5: 5 8 7 6
6:
7:
8:
9:
```



---

---
title: "I Can Guess the Data Structure!"
layout: "post"
diff: 普及/提高-
pid: UVA11995
tag: ['模拟', '栈', '队列']
---

# I Can Guess the Data Structure!

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3146

[PDF](https://uva.onlinejudge.org/external/119/p11995.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/55cb8a2c5cf1532ff4a8dff640c7538c0998c78c.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/85c08a1b2399e94d2f430010d18cb8c7c42d2ddd.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11995/ca430d6d3039e2b5f45d99cd031ba66a1656ade0.png)

## 样例 #1

### 输入

```
6
1 1
1 2
1 3
2 1
2 2
2 3
6
1 1
1 2
1 3
2 3
2 2
2 1
2
1 1
2 2
4
1 2
1 1
2 1
2 2
7
1 2
1 5
1 1
1 3
2 5
1 4
2 4
```

### 输出

```
queue
not sure
impossible
stack
priority queue
```



---

---
title: "矩阵链乘 Matrix Chain Multiplication"
layout: "post"
diff: 普及/提高-
pid: UVA442
tag: ['字符串', '栈', '构造']
---

# 矩阵链乘 Matrix Chain Multiplication

## 题目描述

## 矩阵链乘


​  假设你必须评估一种表达形如 A*B*C*D*E，其中 A,B,C,D,E是矩阵。既然矩阵乘法是关联的，那么乘法的顺序是任意的。然而，链乘的元素数量必须由你选择的赋值顺序决定。

​  例如，A，B，C分别是 50 * 10 ，10 * 20 和 20 * 5 的矩阵。现在有两种方案计算 A * B * C ,即（A * B) * C 和 A*(B * C)。  
   第一个要进行15000次基本乘法，而第二个只进行3500次。

​  你的任务就是写出一个程序判定以给定的方式相乘需要多少次基本乘法计算。

## 输入格式

​  输入包含两个部分：矩阵和表达式。 
   输入文件的第一行包含了一个整数 n(1  $\leq$  n  $\leq$  26), 代表矩阵的个数。接下来的n行每一行都包含了一个大写字母，说明矩阵的名称，以及两个整数，说明行与列的个数。  
   第二个部分严格遵守以下的语法：

SecondPart = Line {  Line  } <EOF>
Line       = Expression <CR>
Expression = Matrix | "(" Expression Expression ")"
Matrix     = "A" | "B" | "C" | ... | "X" | "Y" | "Z"

## 输出格式

​  对于每一个表达式，如果乘法无法进行就输出 " error "。否则就输出一行包含计算所需的乘法次数。 

感谢@onceagain 提供翻译

## 样例 #1

### 输入

```
9
A 50 10
B 10 20
C 20 5
D 30 35
E 35 15
F 15 5
G 5 10
H 10 20
I 20 25
A
B
C
(AA)
(AB)
(AC)
(A(BC))
((AB)C)
(((((DE)F)G)H)I)
(D(E(F(G(HI)))))
((D(EF))((GH)I))
```

### 输出

```
0
0
0
error
10000
error
3500
15000
40500
47500
15125
```



---

