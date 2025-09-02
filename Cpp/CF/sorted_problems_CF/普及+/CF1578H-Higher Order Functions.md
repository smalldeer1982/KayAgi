---
title: "Higher Order Functions"
layout: "post"
diff: 普及+/提高
pid: CF1578H
tag: []
---

# Higher Order Functions

## 题目描述

Helen studies functional programming and she is fascinated with a concept of higher order functions — functions that are taking other functions as parameters. She decides to generalize the concept of the function order and to test it on some examples.

For her study, she defines a simple grammar of types. In her grammar, a type non-terminal $ T $ is defined as one of the following grammar productions, together with $ \textrm{order}(T) $ , defining an order of the corresponding type:

- "()" is a unit type, $ \textrm{order}(\textrm{"}\texttt{()}\textrm{"}) = 0 $ .
- "(" $ T $ ")" is a parenthesized type, $ \textrm{order}(\textrm{"}\texttt{(}\textrm{"}\,T\,\textrm{"}\texttt{)}\textrm{"}) = \textrm{order}(T) $ .
- $ T_1 $ "-&gt;" $ T_2 $ is a functional type, $ \textrm{order}(T_1\,\textrm{"}\texttt{->}\textrm{"}\,T_2) = max(\textrm{order}(T_1) + 1, \textrm{order}(T_2)) $ . The function constructor $ T_1 $ "-&gt;" $ T_2 $ is right-to-left associative, so the type "()-&gt;()-&gt;()" is the same as the type "()-&gt;(()-&gt;())" of a function returning a function, and it has an order of $ 1 $ . While "(()-&gt;())-&gt;()" is a function that has an order-1 type "(()-&gt;())" as a parameter, and it has an order of $ 2 $ .

Helen asks for your help in writing a program that computes an order of the given type.

## 输入格式

The single line of the input contains a string consisting of characters '(', ')', '-', and '&gt;' that describes a type that is valid according to the grammar from the problem statement. The length of the line is at most $ 10^4 $ characters.

## 输出格式

Print a single integer — the order of the given type.

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

