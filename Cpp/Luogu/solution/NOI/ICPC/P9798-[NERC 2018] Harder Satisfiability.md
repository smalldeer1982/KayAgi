# [NERC 2018] Harder Satisfiability

## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) H 题。

## 题目描述

我们定义一个“完全量化的布尔类型的 2-CNF 公式”（下简称 2-CNF）是以 $Q_1 x_1 \ldots Q_n x_n F(x_1,\ldots x_n)$ 构成的，$Q_i$ 只有两种，一种是“通用量词” $\forall$，另一种是“存在量词” $\exists$。然后 $F$ 是一个 $m$ 子句的 $s \lor t$（$\mathtt{OR}$ 运算） 的连词（$\mathtt{AND}$ 运算），其中 $s$ 和 $t$ 不一定不同且不一定是否定（为 $\texttt{false}$）。由于 2-CNF 公式是给定的，所以并没有自由变量（即答案固定为 $\texttt{true}$ 或 $\texttt{false}$）。

至于计算 2-CNF 公式的值，我们可以使用一个简单的递归算法来求：

- 如果没有量词（即 $\forall$ 或 $\exists$ ），则返回剩余表达式的返回值。

- 否则，我们使用递归计算公式：$F_z = Q_2x_2 \ldots Q_nx_n F(z,x_2,\ldots,x_n)$，此处 $z = 0,1$。

- 如果当前符号为 $\exists$，则返回 $F_0 \lor F_1$（$\mathtt{OR}$ 运算）。否则符号为 $\forall$ 返回 $F_0 \land F_1$。


## 说明/提示

数据保证 $1 \leq t \leq 10^5$，$1 \leq n,m \leq 10^5$，$-n \leq u_i,v_i \leq n$。

第一个 2-CNF 公式可以化简为 $\forall x_1 \exists x_2(x_1 \lor \overline{x_2}) \land (\overline{x_1} \lor x_2) = \forall x_1 \exists x_2 x_1 \oplus x_2$，对于任意的 $x_1$ 都存在 $x_2 = \overline{x_1}$ 使得答案为真。

第二个 2-CNF 改变了公式的顺序，对于任意的 $x_1$，都可以选择 $x_2 = x_1$，使得表达式为 `FALSE`。

第三个表达式是 $\forall x_1 \exists x_2 \forall x_3 (x_1 \lor \overline{x_2}) \land (\overline{x_1} \lor \overline{x_3})$，如果令 $x_1 = 1$，$x_3 = 1$，则没有 $x_2$ 的值可以使得句子赋值为真，所以公式为假。

## 样例 #1

### 输入

```
3
2 2
AE
1 -2
-1 2
2 2
EA
1 -2
-1 2
3 2
AEA
1 -2
-1 -3
```

### 输出

```
TRUE
FALSE
FALSE
```

