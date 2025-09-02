# 题目信息

# Higher Order Functions

## 题目描述

Helen studies functional programming and she is fascinated with a concept of higher order functions — functions that are taking other functions as parameters. She decides to generalize the concept of the function order and to test it on some examples.

For her study, she defines a simple grammar of types. In her grammar, a type non-terminal $ T $ is defined as one of the following grammar productions, together with $ \textrm{order}(T) $ , defining an order of the corresponding type:

- "()" is a unit type, $ \textrm{order}(\textrm{"}\texttt{()}\textrm{"}) = 0 $ .
- "(" $ T $ ")" is a parenthesized type, $ \textrm{order}(\textrm{"}\texttt{(}\textrm{"}\,T\,\textrm{"}\texttt{)}\textrm{"}) = \textrm{order}(T) $ .
- $ T_1 $ "-&gt;" $ T_2 $ is a functional type, $ \textrm{order}(T_1\,\textrm{"}\texttt{->}\textrm{"}\,T_2) = max(\textrm{order}(T_1) + 1, \textrm{order}(T_2)) $ . The function constructor $ T_1 $ "-&gt;" $ T_2 $ is right-to-left associative, so the type "()-&gt;()-&gt;()" is the same as the type "()-&gt;(()-&gt;())" of a function returning a function, and it has an order of $ 1 $ . While "(()-&gt;())-&gt;()" is a function that has an order-1 type "(()-&gt;())" as a parameter, and it has an order of $ 2 $ .

Helen asks for your help in writing a program that computes an order of the given type.

## 样例 #1

### 输入

```
()```

### 输出

```
0```

## 样例 #2

### 输入

```
()->()```

### 输出

```
1```

## 样例 #3

### 输入

```
()->()->()```

### 输出

```
1```

## 样例 #4

### 输入

```
(()->())->()```

### 输出

```
2```

## 样例 #5

### 输入

```
()->(((()->())->()->())->())```

### 输出

```
3```

# AI分析结果

### 题目翻译
# 高阶函数

## 题目描述
海伦正在学习函数式编程，她对高阶函数的概念非常着迷，高阶函数是指那些将其他函数作为参数的函数。她决定对函数阶的概念进行推广，并通过一些例子来进行测试。

为了进行研究，她定义了一种简单的类型语法。在她的语法中，类型非终结符 $T$ 由以下语法产生式之一定义，同时定义了相应类型的阶 $\textrm{order}(T)$：
- "()" 是单位类型，$\textrm{order}(\textrm{"}\texttt{()}\textrm{"}) = 0$。
- "(" $T$ ")" 是带括号的类型，$\textrm{order}(\textrm{"}\texttt{(}\textrm{"}\,T\,\textrm{"}\texttt{)}\textrm{"}) = \textrm{order}(T)$。
- $T_1$ "-&gt;" $T_2$ 是函数类型，$\textrm{order}(T_1\,\textrm{"}\texttt{->}\textrm{"}\,T_2) = \max(\textrm{order}(T_1) + 1, \textrm{order}(T_2))$。函数构造符 $T_1$ "-&gt;" $T_2$ 是右结合的，因此类型 "()-&gt;()-&gt;()" 与类型 "()-&gt;(()-&gt;())" 相同，即一个返回函数的函数，其阶为 $1$。而 "(()-&gt;())-&gt;()" 是一个以阶为 $1$ 的类型 "(()-&gt;())" 作为参数的函数，其阶为 $2$。

海伦请求你帮助她编写一个程序，用于计算给定类型的阶。

## 样例 #1
### 输入
```
()
```
### 输出
```
0
```

## 样例 #2
### 输入
```
()->()
```
### 输出
```
1
```

## 样例 #3
### 输入
```
()->()->()
```
### 输出
```
1
```

## 样例 #4
### 输入
```
(()->())->()
```
### 输出
```
2
```

## 样例 #5
### 输入
```
()->(((()->())->()->())->())
```
### 输出
```
3
```

### 算法分类
递归

### 综合分析与结论
这些题解主要围绕递归和表达式计算两种思路来解决计算给定类型阶的问题。
- **递归思路**：根据题目中给出的类型阶的定义，通过递归函数对输入字符串进行处理。当遇到 "->" 时，递归计算左右子串的阶，然后根据规则取最大值；当遇到括号时，去掉括号继续递归。
- **表达式计算思路**：将输入的字符串进行转换，把 "()" 替换为 "0"，把 "->" 替换为 "+"，然后使用栈来进行表达式的计算。

### 通用建议与扩展思路
对于此类根据规则递归计算的题目，关键在于准确理解规则并将其转化为递归逻辑。在实现递归函数时，要注意边界条件的处理。对于表达式计算的思路，可以学习栈的使用，栈在处理括号匹配和表达式计算等问题中非常有用。同类型题可能会有更复杂的规则，例如更多的运算符或嵌套规则，解题时可以先分析规则，再选择合适的方法（递归或表达式计算）来解决。

### 推荐洛谷题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)：考察递归和组合数学的知识。
2. [P1217 [USACO1.5] 回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：需要递归生成回文数并判断质数。
3. [P1028 [NOIP2001 普及组] 数的计算](https://www.luogu.com.cn/problem/P1028)：典型的递归问题，根据给定规则计算满足条件的数的个数。

---
处理用时：31.06秒