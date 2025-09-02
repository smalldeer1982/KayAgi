---
title: "KSMALL - K-th smallest number"
layout: "post"
diff: 普及/提高-
pid: SP18939
tag: []
---

# KSMALL - K-th smallest number

## 题目描述

给定由下面的C ++函数生成的（伪）随机数的数组，您的任务是找到所有数字的第K个最小数。
```cpp

unsigned array[5000000];

void randomize(unsigned a,unsigned b,unsigned mod)
{
    for( int i=0 ; i<5000000 ; i++ )
    {
        a = 31014 * (a & 65535) + (a >> 16);
        b = 17508 * (b & 65535) + (b >> 16);
        array[i] = ((a << 16) + b) % mod;
    }
}
```
请注意，计算可能会溢出，但我们只关心每个结果的最后32位，因此无关紧要。

## 输入格式

一行4个数字（a，b，mod，K）用空格分隔。
```
0<a，b<65535
2<mod<2^32
1<K<5x10^6 
```

## 输出格式

所有生成数字的第K个最小数。

## 样例 #1

### 输入

```
2 3 100000007 23
```

### 输出

```
434
```

