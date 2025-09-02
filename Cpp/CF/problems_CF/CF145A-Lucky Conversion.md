---
title: "Lucky Conversion"
layout: "post"
diff: 普及-
pid: CF145A
tag: []
---

# Lucky Conversion

## 题目描述

Petya loves lucky numbers very much. Everybody knows that lucky numbers are positive integers whose decimal record contains only the lucky digits 4 and 7. For example, numbers 47, 744, 4 are lucky and 5, 17, 467 are not.

Petya has two strings $ a $ and $ b $ of the same length $ n $ . The strings consist only of lucky digits. Petya can perform operations of two types:

- replace any one digit from string $ a $ by its opposite (i.e., replace $ 4 $ by $ 7 $ and $ 7 $ by $ 4 $ );
- swap any pair of digits in string $ a $ .

Petya is interested in the minimum number of operations that are needed to make string $ a $ equal to string $ b $ . Help him with the task.

## 输入格式

The first and the second line contains strings $ a $ and $ b $ , correspondingly. Strings $ a $ and $ b $ have equal lengths and contain only lucky digits. The strings are not empty, their length does not exceed $ 10^{5} $ .

## 输出格式

Print on the single line the single number — the minimum number of operations needed to convert string $ a $ into string $ b $ .

## 说明/提示

In the first sample it is enough simply to swap the first and the second digit.

In the second sample we should replace the second digit with its opposite.

In the third number we should replace all three digits with their opposites.

## 样例 #1

### 输入

```
47
74

```

### 输出

```
1

```

## 样例 #2

### 输入

```
774
744

```

### 输出

```
1

```

## 样例 #3

### 输入

```
777
444

```

### 输出

```
3

```

