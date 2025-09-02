# 题目信息

# Increasing Subsequence (easy version)

## 题目描述

The only difference between problems C1 and C2 is that all values in input of problem C1 are distinct (this condition may be false for problem C2).

You are given a sequence $ a $ consisting of $ n $ integers. All these integers are distinct, each value from $ 1 $ to $ n $ appears in the sequence exactly once.

You are making a sequence of moves. During each move you must take either the leftmost element of the sequence or the rightmost element of the sequence, write it down and remove it from the sequence. Your task is to write down a strictly increasing sequence, and among all such sequences you should take the longest (the length of the sequence is the number of elements in it).

For example, for the sequence $ [2, 1, 5, 4, 3] $ the answer is $ 4 $ (you take $ 2 $ and the sequence becomes $ [1, 5, 4, 3] $ , then you take the rightmost element $ 3 $ and the sequence becomes $ [1, 5, 4] $ , then you take $ 4 $ and the sequence becomes $ [1, 5] $ and then you take $ 5 $ and the sequence becomes $ [1] $ , the obtained increasing sequence is $ [2, 3, 4, 5] $ ).

## 说明/提示

The first example is described in the problem statement.

## 样例 #1

### 输入

```
5
2 1 5 4 3
```

### 输出

```
4
LRRR
```

## 样例 #2

### 输入

```
7
1 3 5 6 7 4 2
```

### 输出

```
7
LRLRLLL
```

## 样例 #3

### 输入

```
3
1 2 3
```

### 输出

```
3
LLL
```

## 样例 #4

### 输入

```
4
1 2 4 3
```

### 输出

```
4
LLRL
```

# AI分析结果

### 题目内容翻译

# 递增子序列（简单版）

## 题目描述

问题C1和C2的唯一区别在于，C1的输入中的所有值都是不同的（这个条件在C2中可能不成立）。

给定一个由$n$个整数组成的序列$a$。所有这些整数都是不同的，从$1$到$n$的每个值在序列中恰好出现一次。

你进行一系列操作。每次操作时，你必须取序列的最左侧元素或最右侧元素，将其写下并从序列中移除。你的任务是写下一个严格递增的序列，并且在所有这样的序列中，你应该选择最长的序列（序列的长度是其中的元素数量）。

例如，对于序列$[2, 1, 5, 4, 3]$，答案是$4$（你取$2$，序列变为$[1, 5, 4, 3]$，然后你取最右侧的元素$3$，序列变为$[1, 5, 4]$，然后你取$4$，序列变为$[1, 5]$，然后你取$5$，序列变为$[1]$，得到的递增序列是$[2, 3, 4, 5]$）。

## 说明/提示

第一个例子在题目描述中已经给出。

## 样例 #1

### 输入

```
5
2 1 5 4 3
```

### 输出

```
4
LRRR
```

## 样例 #2

### 输入

```
7
1 3 5 6 7 4 2
```

### 输出

```
7
LRLRLLL
```

## 样例 #3

### 输入

```
3
1 2 3
```

### 输出

```
3
LLL
```

## 样例 #4

### 输入

```
4
1 2 4 3
```

### 输出

```
4
LLRL
```

### 算法分类
贪心

### 题解分析与结论

该题的核心思想是通过贪心策略，每次选择当前序列的最左或最右元素，使得最终形成的序列尽可能长且严格递增。难点在于如何处理当左右两端的元素相等时的情况，此时需要分别从左右两端向内扫描，选择能够形成更长递增序列的一端。

### 所选高分题解

#### 题解1：作者：L______ (赞：7)
- **星级**：5星
- **关键亮点**：详细解释了贪心策略，并提供了处理左右元素相等时的具体方法。代码实现清晰，逻辑严谨。
- **核心代码**：
```cpp
while(1){
    if((a[l]<=tmp && a[r]<=tmp) || r<l) break;
    if(a[l]<a[r]){
        if(a[l]>tmp){
            tmp=a[l];
            ans[++cnt]='L';
            l++;
        }
        else{
            tmp=a[r];
            ans[++cnt]='R';
            r--;
        }
    }
    else if(a[l]>a[r]){
        if(a[r]>tmp){
            tmp=a[r];
            ans[++cnt]='R';
            r--;
        }
        else{
            tmp=a[l];
            ans[++cnt]='L';
            l++;
        }
    }
    else{
        int tot1=0;
        for(int i=l+1;i<=r;i++){
            if(a[i]>a[i-1]) tot1++;
            else break;
        }
        int tot2=0;
        for(int i=r-1;i>=l;i--){
            if(a[i]>a[i+1]) tot2++;
            else break;
        }
        if(tot1>tot2){
            for(int i=l;i<=l+tot1;i++){
                ans[++cnt]='L';
            }
        }
        else{
            for(int i=r;i>=r-tot2;i--){
                ans[++cnt]='R';
            }
        }
        break;
    }
}
```

#### 题解2：作者：Mosher (赞：3)
- **星级**：4星
- **关键亮点**：简洁明了地描述了贪心策略，代码实现较为简洁，适合初学者理解。
- **核心代码**：
```cpp
while(1){
    if((a[tail]-last<0&&a[head]-last<0)||tail<head||ans==n) break;
    else if(a[tail]-last<0&&a[head]-last>=0){
        last=a[head];
        head++;
        s[ans++]='L';
    }
    else if(a[head]-last<0&&a[tail]-last>=0){
        last=a[tail];
        tail--;
        s[ans++]='R';
    }
    else if(a[tail]<a[head]){
        last=a[tail];
        tail--;
        s[ans++]='R';
    }
    else{
        last=a[head];
        head++;
        s[ans++]='L';
    }
}
```

#### 题解3：作者：Shanganze (赞：1)
- **星级**：4星
- **关键亮点**：详细分析了贪心策略的正确性，代码实现较为清晰，适合进阶学习者。
- **核心代码**：
```cpp
while(l<=r){
    if(x[l]<last&&x[r]<last)break;
    ans++;
    if(x[r]<last&&x[l]>=last){
        a+='L';
        l++;
        last=x[l-1];
    }
    else if(x[l]<last&&x[r]>=last){
        a+='R';
        r--;
        last=x[r+1];
    }
    else if(x[l]<=x[r]){
        l++;
        a+='L';
        last=x[l-1];
    }
    else{
        r--;
        a+='R';
        last=x[r+1];
    }
}
```

### 最优关键思路与技巧
- **贪心策略**：每次选择当前序列的最左或最右元素，使得最终形成的序列尽可能长且严格递增。
- **处理相等元素**：当左右两端的元素相等时，分别从左右两端向内扫描，选择能够形成更长递增序列的一端。

### 可拓展之处
- 类似的问题可以扩展到处理不严格递增的序列，或者允许重复元素的情况。
- 可以进一步优化扫描相等元素时的算法，减少时间复杂度。

### 推荐题目
1. [CF1157C2 - Increasing Subsequence (hard version)](https://www.luogu.org/problem/CF1157C2)
2. [P1090 合并果子](https://www.luogu.org/problem/P1090)
3. [P1168 中位数](https://www.luogu.org/problem/P1168)

---
处理用时：47.42秒