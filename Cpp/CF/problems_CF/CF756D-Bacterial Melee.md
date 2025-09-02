---
title: "Bacterial Melee"
layout: "post"
diff: 省选/NOI-
pid: CF756D
tag: []
---

# Bacterial Melee

## 题目描述

Julia is conducting an experiment in her lab. She placed several luminescent bacterial colonies in a horizontal testtube. Different types of bacteria can be distinguished by the color of light they emit. Julia marks types of bacteria with small Latin letters "a", ..., "z".

The testtube is divided into $ n $ consecutive regions. Each region is occupied by a single colony of a certain bacteria type at any given moment. Hence, the population of the testtube at any moment can be described by a string of $ n $ Latin characters.

Sometimes a colony can decide to conquer another colony in one of the adjacent regions. When that happens, the attacked colony is immediately eliminated and replaced by a colony of the same type as the attacking colony, while the attacking colony keeps its type. Note that a colony can only attack its neighbours within the boundaries of the testtube. At any moment, at most one attack can take place.

For example, consider a testtube with population "babb". There are six options for an attack that may happen next:

- the first colony attacks the second colony ( $ 1→2 $ ), the resulting population is "bbbb";
- $ 2→1 $ , the result is "aabb";
- $ 2→3 $ , the result is "baab";
- $ 3→2 $ , the result is "bbbb" (note that the result is the same as the first option);
- $ 3→4 $ or $ 4→3 $ , the population does not change.

The pattern of attacks is rather unpredictable. Julia is now wondering how many different configurations of bacteria in the testtube she can obtain after a sequence of attacks takes place (it is possible that no attacks will happen at all). Since this number can be large, find it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains an integer $ n $ — the number of regions in the testtube ( $ 1<=n<=5000 $ ).

The second line contains $ n $ small Latin letters that describe the initial population of the testtube.

## 输出格式

Print one number — the answer to the problem modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample the population can never change since all bacteria are of the same type.

In the second sample three configurations are possible: "ab" (no attacks), "aa" (the first colony conquers the second colony), and "bb" (the second colony conquers the first colony).

To get the answer for the third sample, note that more than one attack can happen.

## 样例 #1

### 输入

```
3
aaa

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
ab

```

### 输出

```
3

```

## 样例 #3

### 输入

```
4
babb

```

### 输出

```
11

```

## 样例 #4

### 输入

```
7
abacaba

```

### 输出

```
589

```

