# Not a Substring

## 题目描述

A bracket sequence is a string consisting of characters '(' and/or ')'. A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters '1' and '+' between the original characters of the sequence. For example:

- bracket sequences "()()" and "(())" are regular (they can be transformed into "(1)+(1)" and "((1+1)+1)", respectively);
- bracket sequences ")(", "(" and ")" are not regular.

You are given a bracket sequence $ s $ ; let's define its length as $ n $ . Your task is to find a regular bracket sequence $ t $ of length $ 2n $ such that $ s $ does not occur in $ t $ as a contiguous substring, or report that there is no such sequence.

## 样例 #1

### 输入

```
4
)(
(()
()
))()```

### 输出

```
YES
(())
YES
()()()
NO
YES
()(()())```

