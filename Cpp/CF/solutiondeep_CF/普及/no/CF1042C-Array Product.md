# 题目信息

# Array Product

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You can perform the following operations with it:

1. Choose some positions $ i $ and $ j $ ( $ 1 \le i, j \le n, i \ne j $ ), write the value of $ a_i \cdot a_j $ into the $ j $ -th cell and remove the number from the $ i $ -th cell;
2. Choose some position $ i $ and remove the number from the $ i $ -th cell (this operation can be performed no more than once and at any point of time, not necessarily in the beginning).

The number of elements decreases by one after each operation. However, the indexing of positions stays the same. Deleted numbers can't be used in the later operations.

Your task is to perform exactly $ n - 1 $ operations with the array in such a way that the only number that remains in the array is maximum possible. This number can be rather large, so instead of printing it you need to print any sequence of operations which leads to this maximum number. Read the output format to understand what exactly you need to print.

## 说明/提示

Let X be the removed number in the array. Let's take a look at all the examples:

The first example has, for example, the following sequence of transformations of the array: $ [5, -2, 0, 1, -3] \to [5, -2, X, 1, -3] \to [X, -10, X, 1, -3] \to $ $ [X, X, X, -10, -3] \to [X, X, X, X, 30] $ . Thus, the maximum answer is $ 30 $ . Note, that other sequences that lead to the answer $ 30 $ are also correct.

The second example has, for example, the following sequence of transformations of the array: $ [5, 2, 0, 4, 0] \to [5, 2, X, 4, 0] \to [5, 2, X, 4, X] \to [X, 10, X, 4, X] \to $ $ [X, X, X, 40, X] $ . The following answer is also allowed:

`<br></br>1 5 3<br></br>1 4 2<br></br>1 2 1<br></br>2 3<br></br>`Then the sequence of transformations of the array will look like this: $ [5, 2, 0, 4, 0] \to [5, 2, 0, 4, X] \to [5, 8, 0, X, X] \to [40, X, 0, X, X] \to $ $ [40, X, X, X, X] $ .

The third example can have the following sequence of transformations of the array: $ [2, -1] \to [2, X] $ .

The fourth example can have the following sequence of transformations of the array: $ [0, -10, 0, 0] \to [X, 0, 0, 0] \to [X, X, 0, 0] \to [X, X, X, 0] $ .

The fifth example can have the following sequence of transformations of the array: $ [0, 0, 0, 0] \to [X, 0, 0, 0] \to [X, X, 0, 0] \to [X, X, X, 0] $ .

## 样例 #1

### 输入

```
5
5 -2 0 1 -3
```

### 输出

```
2 3
1 1 2
1 2 4
1 4 5
```

## 样例 #2

### 输入

```
5
5 2 0 4 0
```

### 输出

```
1 3 5
2 5
1 1 2
1 2 4
```

## 样例 #3

### 输入

```
2
2 -1
```

### 输出

```
2 2
```

## 样例 #4

### 输入

```
4
0 -10 0 0
```

### 输出

```
1 1 2
1 2 3
1 3 4
```

## 样例 #5

### 输入

```
4
0 0 0 0
```

### 输出

```
1 1 2
1 2 3
1 3 4
```

# AI分析结果

### 题目内容重写

#### 数组乘积

##### 题目描述

给定一个由 $n$ 个整数组成的数组 $a$。你可以对其进行以下操作：

1. 选择两个位置 $i$ 和 $j$（$1 \le i, j \le n, i \ne j$），将 $a_i \cdot a_j$ 的值写入第 $j$ 个单元格，并删除第 $i$ 个单元格中的数；
2. 选择某个位置 $i$，删除第 $i$ 个单元格中的数（此操作最多只能执行一次，且可以在任何时候执行，不一定在开始时）。

每次操作后，数组中的元素数量减少一个。然而，位置的索引保持不变。删除的数不能在后续操作中使用。

你的任务是执行恰好 $n - 1$ 次操作，使得数组中仅剩的一个数尽可能大。由于这个数可能非常大，因此你不需要打印它，而是需要打印任何能够达到这个最大数的操作序列。请阅读输出格式以了解你需要打印的内容。

##### 说明/提示

设 $X$ 为数组中删除的数。我们来看所有示例：

第一个示例的数组变换序列如下：$[5, -2, 0, 1, -3] \to [5, -2, X, 1, -3] \to [X, -10, X, 1, -3] \to [X, X, X, -10, -3] \to [X, X, X, X, 30]$。因此，最大答案为 $30$。注意，其他导致答案 $30$ 的序列也是正确的。

第二个示例的数组变换序列如下：$[5, 2, 0, 4, 0] \to [5, 2, X, 4, 0] \to [5, 2, X, 4, X] \to [X, 10, X, 4, X] \to [X, X, X, 40, X]$。以下答案也是允许的：

`<br></br>1 5 3<br></br>1 4 2<br></br>1 2 1<br></br>2 3<br></br>` 然后数组的变换序列如下：$[5, 2, 0, 4, 0] \to [5, 2, 0, 4, X] \to [5, 8, 0, X, X] \to [40, X, 0, X, X] \to [40, X, X, X, X]$。

第三个示例的数组变换序列如下：$[2, -1] \to [2, X]$。

第四个示例的数组变换序列如下：$[0, -10, 0, 0] \to [X, 0, 0, 0] \to [X, X, 0, 0] \to [X, X, X, 0]$。

第五个示例的数组变换序列如下：$[0, 0, 0, 0] \to [X, 0, 0, 0] \to [X, X, 0, 0] \to [X, X, X, 0]$。

##### 样例 #1

###### 输入

```
5
5 -2 0 1 -3
```

###### 输出

```
2 3
1 1 2
1 2 4
1 4 5
```

##### 样例 #2

###### 输入

```
5
5 2 0 4 0
```

###### 输出

```
1 3 5
2 5
1 1 2
1 2 4
```

##### 样例 #3

###### 输入

```
2
2 -1
```

###### 输出

```
2 2
```

##### 样例 #4

###### 输入

```
4
0 -10 0 0
```

###### 输出

```
1 1 2
1 2 3
1 3 4
```

##### 样例 #5

###### 输入

```
4
0 0 0 0
```

###### 输出

```
1 1 2
1 2 3
1 3 4
```

### 算法分类
贪心

### 题解分析与结论

该题的核心在于通过贪心策略，最大化最终数组中的唯一数。具体来说，需要考虑以下几点：

1. **负数的处理**：如果负数的个数为奇数，则需要删除一个绝对值最小的负数，以确保最终乘积为正数且最大。
2. **零的处理**：如果数组中存在零，需要将所有零合并后再删除，以避免乘积变为零。
3. **操作顺序**：优先处理零和负数，最后将所有正数相乘。

### 所选高分题解

#### 题解1：lygmh（4星）

**关键亮点**：
- 详细分类讨论了负数和零的处理方式。
- 代码结构清晰，逻辑严谨。
- 通过排序和索引处理，确保操作顺序正确。

**核心代码**：
```cpp
if(zero>0){
    for(int i=zero;i>1;i--) printf("1 %d %d\n",s2[i],s2[i-1]);
    if(negative&1){
        printf("1 %d %d\n",s3[negative],s2[1]);
        negative--;
    } 
    if(positive>0||negative>0) printf("2 %d\n",s2[1]);
}else{
    if(negative&1){
        printf("2 %d\n",s3[negative]);
        negative--;
    } 
}
```

#### 题解2：VenusM1nT（4星）

**关键亮点**：
- 简洁明了地处理了负数和零的情况。
- 通过标记删除的元素，避免了重复操作。
- 代码简洁，易于理解。

**核心代码**：
```cpp
if(sum&1){
    int maxn=-2e9;
    for(int i=1;i<=n;i++){
        if(a[i]<0 && a[i]>maxn){
            maxn=a[i];
            del=i;
        }
    }
}
```

#### 题解3：ztz11（4星）

**关键亮点**：
- 通过排序和标记处理，确保删除的元素正确。
- 详细处理了全零和全负数的情况。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
if(cnt%2==1){
    bj[wz]=1;
    bnt++;
    zero[bnt]=wz;
}
sort(zero+1,zero+bnt+1);
int pre=zero[1];
for(int i=2;i<=bnt;i++){
    printf("1 %d %d\n",pre,zero[i]);
    pre=zero[i]; 
}
```

### 最优关键思路与技巧

1. **贪心策略**：优先处理负数和零，确保最终乘积为正数且最大。
2. **标记与排序**：通过标记删除的元素和排序，确保操作顺序正确。
3. **分类讨论**：详细讨论不同情况（如全零、全负数等），确保代码的鲁棒性。

### 拓展思路

类似的问题可以通过贪心策略和分类讨论来解决，尤其是在处理数组中的负数、零和正数时。可以进一步拓展到处理更复杂的数组操作问题，如动态规划或分治算法。

### 推荐题目

1. [P1007 最大乘积](https://www.luogu.com.cn/problem/P1007)
2. [P1012 最大子段和](https://www.luogu.com.cn/problem/P1012)
3. [P1013 最大子矩阵](https://www.luogu.com.cn/problem/P1013)

---
处理用时：52.93秒