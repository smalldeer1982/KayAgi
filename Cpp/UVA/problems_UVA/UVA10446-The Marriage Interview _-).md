---
title: "The Marriage Interview :-)"
layout: "post"
diff: 难度0
pid: UVA10446
tag: []
---

# The Marriage Interview :-)

## 题目描述

让我们观看一片代码：

```cpp
/*
__int64 is a 64-bit integer data type in Visual C++. So the
following code was written in Visual C++.
*/
typedef unsigned __int64 datatype;
datatype count;

datatype trib(int n,unsigned int back){
    datatype sum=0;
    int i;
    count++;
    if(n<=0) return 0;
    if(n==1) return 1;
    for(i=1;i<=back;i++)
        sum+=trib(n-i,back);
    return sum;
}
void main(void){
    count=0;
    trib(5,5);
    printf(" %I64\n",count);
}
```

你的任务是对于多组数据，给出代码的输出。

## 输入格式

多组数据，每组数据包含两个整数 $n,{back}$。

## 输出格式

每次代码的输出结果。

## 样例 #1

### 输入

```
3 3
4 4
5 5
6 6
7 7
8 8
9 9
61 61
```

### 输出

```
Case 1: 7
Case 2: 17
Case 3: 41
Case 4: 97
Case 5: 225
Case 6: 513
Case 7: 1153
```

