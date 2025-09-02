---
title: "MATRMUL0 - Matrix Multiplication 2K"
layout: "post"
diff: 难度0
pid: SP31374
tag: []
---

# MATRMUL0 - Matrix Multiplication 2K

## 题目描述

Consider the following C++ code, it constructs n×n matrices A,B and vector V from matrix C=A×B which you need to calculate.

 ```
uint32_t n, i, j, d1, p1, r1, m1, d2, p2, m2, A[n][n], B[n][n];
uint64_t C[n][n], V[n];
//here you need to read n, p1, d1, r1, m1, p2, d2, r2, m2 from input.
for (i=0; i<n; ++i)
    for (j=0; j<n; ++j) {
        d1 = d1 * p1 + r1;
        d2 = d2 * p2 + r2;
        A[i][j] = d1 >> (32 - m1);
        B[i][j] = d2 >> (32 - m2);
    }
//here you need to calculate C=A*B
for (i=0; i<n; ++i) {
    V[i] = 0;
    for (j=0; j<n; ++j)
        V[i] ^= C[i][j];
}
//here you need to output V[0], V[1], ..., V[n-1], separated by spaces.
```

## 输入格式

You are given integers n, p1, d1, r1, m1, p2, d2, r2, m2, separated by spaces.

1, 1

## 输出格式

You need to output V\[0\], ..., V\[n-1\], separated by spaces.

## 样例 #1

### 输入

```
4 1664525 0 1013904223 26 1664525 1 1013904223 26
```

### 输出

```
3929555766216722 770418013451752 7738542081270672 4286515685761206
```

