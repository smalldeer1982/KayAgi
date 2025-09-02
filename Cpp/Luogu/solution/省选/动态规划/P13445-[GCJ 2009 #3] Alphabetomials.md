# [GCJ 2009 #3] Alphabetomials

## 题目描述

众所周知，$4$ 次多项式与 $5$ 次多项式之间有着很大的区别。关于一般 $5$ 次多项式根不存在求根公式的问题，催生了著名的**Galois 理论**，不过据作者所知，这与我们这里的问题并无关系。

我们只考虑至多 $4$ 次的多元多项式，变量为 $26$ 个小写英文字母。例如，下面是一个这样的多项式：

$\text{aber} + \text{aab} + \text{c}$

给定一个字符串 $S$，我们可以用它来计算该多项式的值 $p(S)$，具体方法如下：将每个变量替换为该字母在 $S$ 中出现的次数。例如，对于上述多项式，若 $S = \text{"abracadabra edgar"}$，则其中有 $6$ 个 a，$2$ 个 b，$1$ 个 c，$1$ 个 e，$3$ 个 r。因此，

$$
p(S) = 6 \times 2 \times 1 \times 3 + 6 \times 6 \times 2 + 1 = 109。
$$

给定一个只包含小写字母且各不相同的单词字典，我们称一个字符串 $S$ 为 $d$-短语（$d$-phrase），如果

$$
S = "S_1\ S_2\ S_3\ \ldots\ S_d"
$$

其中 $S_i$ 是字典中的任意单词，$1 \leqslant i \leqslant d$。也就是说，$S$ 是由 $d$ 个字典单词用空格隔开拼成的。给定一个 $K \leqslant 10$，请你对每个 $1 \leqslant d \leqslant K$，计算所有 $d$-短语的 $p(S)$ 之和。由于答案可能很大，请输出对 $10009$ 取余后的结果。

## 说明/提示

**限制条件**

- $1 \leqslant T \leqslant 100$。
- 字符串 $p$ 由一个或多个项用加号连接，不以加号开头或结尾。每个 $p$ 最多有 $5$ 项。每项至少 $1$ 个、至多 $4$ 个小写字母，且字母按非递减字典序排列。同一多项式内不会有重复项。
- 每个单词非空，仅含小写英文字母，长度不超过 $50$。同一测试用例中不会有重复单词。

**小数据集**

- 时间限制：3 秒
- $1 \leqslant n \leqslant 20$
- $1 \leqslant K \leqslant 5$

**大数据集**

- 时间限制：6 秒
- $1 \leqslant n \leqslant 100$
- $1 \leqslant K \leqslant 10$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
2
ehw+hwww 5
6
where
when
what
whether
who
whose
a+e+i+o+u 3
4
apple
orange
watermelon
banana```

### 输出

```
Case #1: 15 1032 7522 6864 253
Case #2: 12 96 576```

