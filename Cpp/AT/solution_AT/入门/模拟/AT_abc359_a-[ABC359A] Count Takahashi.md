# [ABC359A] Count Takahashi

## 题目描述

给定 $N$ 个字符串。

第 $i$ 个（$1\leq i\leq N$）给出的字符串 $S_i$，要么等于 `Takahashi`，要么等于 `Aoki`。

请你求出有多少个 $i$ 满足 $S_i$ 等于 `Takahashi`。

## 说明/提示

## 限制条件

- $1\leq N\leq 100$
- $N$ 是整数
- $S_i$ 要么等于 `Takahashi`，要么等于 `Aoki`（$1\leq i\leq N$）

## 样例解释 1

有 $S_2,S_3$ 这两个等于 `Takahashi`，$S_1$ 不等于。  
因此，请输出 `2`。

## 样例解释 2

也有可能不存在等于 `Takahashi` 的 $S_i$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
Aoki
Takahashi
Takahashi```

### 输出

```
2```

## 样例 #2

### 输入

```
2
Aoki
Aoki```

### 输出

```
0```

## 样例 #3

### 输入

```
20
Aoki
Takahashi
Takahashi
Aoki
Aoki
Aoki
Aoki
Takahashi
Aoki
Aoki
Aoki
Takahashi
Takahashi
Aoki
Takahashi
Aoki
Aoki
Aoki
Aoki
Takahashi```

### 输出

```
7```

