---
title: "Valera and Number"
layout: "post"
diff: 省选/NOI-
pid: CF441E
tag: []
---

# Valera and Number

## 题目描述

Valera is a coder. Recently he wrote a funny program. The pseudo code for this program is given below:

```plain
//input: integers x, k, p
a = x;
for(step = 1; step <= k; step = step + 1){
    rnd = [random integer from 1 to 100];
    if(rnd <= p)
        a = a * 2;
    else
        a = a + 1;
}

s = 0;

while(remainder after dividing a by 2 equals 0){
    a = a / 2;
    s = s + 1;
}
```

Now Valera wonders: given the values $ x $ , $ k $ and $ p $ , what is the expected value of the resulting number $ s $ ?

## 输入格式

The first line of the input contains three integers $ x,k,p $ ( $ 1<=x<=10^{9}; 1<=k<=200; 0<=p<=100 $ ).

## 输出格式

Print the required expected value. Your answer will be considered correct if the absolute or relative error doesn't exceed $ 10^{-6} $ .

## 说明/提示

If the concept of expected value is new to you, you can read about it by the link:

http://en.wikipedia.org/wiki/Expected\_value

## 样例 #1

### 输入

```
1 1 50

```

### 输出

```
1.0000000000000

```

## 样例 #2

### 输入

```
5 3 0

```

### 输出

```
3.0000000000000

```

## 样例 #3

### 输入

```
5 3 25

```

### 输出

```
1.9218750000000

```

