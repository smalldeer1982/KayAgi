# [NWRRC 2014] Combinator Expression

## 题目描述

## 题目背景

组合逻辑可以看作是一种计算模型，允许将任何可计算函数表示为从小的有限基底中选取的函数的组合。在这个问题中，我们考虑 BCKW 基底的一个受限变体，即 BCKI。

BCKI 基底中的组合表达式是一个字符串，对应于以下文法：

```plain
⟨表达式⟩ ::= ⟨表达式⟩ ⟨项⟩ | ⟨项⟩
⟨项⟩ ::= ‘(’⟨表达式⟩‘)’ | ‘B’ | ‘C’ | ‘K’ | ‘I’
```

从文法可以看出，表达式是应用树，叶子是组合子 $B, C, K$ 和 $I$。应用是左结合的。例如，$BIC$ 等价于 $(BI)C$，但不等价于 $B(IC)$。

为了便于解释，我们将使用小写英文字母 $(a \cdots z)$ 来表示子表达式。这些小写字母不会出现在实际数据中。例如，$BIC$ 可以表示为 $BxC$（即 $B\underbrace { I }_{ x }C$），$x(\underbrace {BIC}_{ x })$，$xy(\underbrace {BI}_{ x } \underbrace { C }_{ y })$，$Bxy (B\underbrace { I }_{ x }\underbrace { C }_{ y })$，但不能表示为 $Bx$。

在表达式 $pq$ 中，我们说将 $p$ 应用于 $q$。我们可以用直觉来理解，$p$ 是一个函数，而 $q$ 是它的参数。然而，求值过程与传统的计算非常不同——不是通过固定表达式树传递值，而是通过改变树结构，使得结果也是一个组合表达式。

为了求值一个表达式，我们需要选择一个子表达式，该子表达式应符合下表中的某个模式——也就是说，应该存在这样的 $x$（可能还有 $y$ 和 $z$），使得表中的模式与子表达式相等。然后我们需要将子表达式替换为表中的简化结果。

| 模式  | 简化结果 | 描述                           |
| :---: | :-------: | :-----------------------------: |
| $Bxyz$ | $x(yz)$  | 组合函数（Zusammensetzungsfunktion） |
| $Cxyz$ | $(xz)y$  | 交换函数（Vertauschungsfunktion）   |
| $Kxy$  | $x$      | 常数函数（Konstanzfunktion）       |
| $Ix$   | $x$      | 恒等函数（Identitätsfunktion）     |

替换完成后，我们必须重复这个过程，直到没有合适的子表达式为止。这个最终表达式就是原始表达式的规范形式。例如，在表达式 $CIC(CB)I$ 中，我们可以进行如下字母分配

$$\underbrace { C }_{ C }\underbrace { I }_{ x }\underbrace { C }_{ y }\underbrace {(CB)}_{ z }I$$

并看到 $CIC(CB)I ≡ (((CI)C)(CB))I ≡ (((Cx)y)z)I$ 包含了 $C$ 组合子模式，因此简化为 $((xz)y)I ≡ I(CB)CI:$

$$(\underbrace { C }_{ C }\underbrace { I }_{ x }\underbrace { C }_{ y }\underbrace { (CB) }_{ Z })I \rightarrow (\underbrace { I }_{ x } \underbrace {(CB)}_{ z }\underbrace { C }_{ y })I$$

另一个例子：$B((CK)I)IC$ 表达式。让我们先简化组合子 $B:$

$$(\underbrace { B }_{ B }\underbrace { ((CK)I) }_{ x }\underbrace { I }_{ y }\underbrace { C }_{ z } \rightarrow \underbrace { ((CK)I) }_{ x } (\underbrace { I }_{ y }\underbrace { C }_{ z }))$$

现在，让我们简化最后一个 $I:$

$$((CK)I)(\underbrace { I }_{ I } \underbrace { C }_{ x }) \rightarrow ((CK)I)C$$

最后，我们通过两次更多的简化完成求值：

$$((\underbrace { C }_{ C }\underbrace { K }_{ x }) \underbrace { I }_{ y }) \underbrace { C }_{ z } \rightarrow (\underbrace { K }_{ K }\underbrace { C }_{ x }) \underbrace { I }_{ y } \rightarrow C$$

可以证明，无论求值顺序如何，规范形式都是一样的。例如，以下求值顺序：

$$C(K(II)(\underbrace { I }_{ I }\underbrace { C }_{ x })) \rightarrow C(K(\underbrace { I }_{ I }\underbrace {  I}_{ x })(C)) \rightarrow C((\underbrace { K }_{ K }\underbrace { I }_{ x }) \underbrace { C }_{ y }) \rightarrow CI$$

和

$$C(K(\underbrace {I}_{ I }\underbrace { I }_{ x })(IC)) \rightarrow C((\underbrace { K }_{ K }\underbrace { I }_{ x })\underbrace { (IC)}_{ y }) \rightarrow CI$$

得到的结果相同。然而，如你所见，简化的次数不同：第一个情况下为 $3$ 次，第二个情况下为 $2$ 次。这提出了一个有趣的问题——找到一个给定公式所需的最小简化次数。

你的任务是编写一个程序，找到给定组合表达式求值到其规范形式所需的最小简化次数。

## 说明/提示

时间限制：1 秒，内存限制：256 MB。

## 样例 #1

### 输入

```
C(K(II)(IC))
```

### 输出

```
2
```

## 样例 #2

### 输入

```
CIBI
```

### 输出

```
3
```

## 样例 #3

### 输入

```
BBBBBCCCCCKKKKKIIIII
```

### 输出

```
15
```

