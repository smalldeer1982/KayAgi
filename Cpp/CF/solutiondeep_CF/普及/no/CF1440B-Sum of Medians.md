# 题目信息

# Sum of Medians

## 题目描述

A median of an array of integers of length $ n $ is the number standing on the $ \lceil {\frac{n}{2}} \rceil $ (rounding up) position in the non-decreasing ordering of its elements. Positions are numbered starting with $ 1 $ . For example, a median of the array $ [2, 6, 4, 1, 3, 5] $ is equal to $ 3 $ . There exist some other definitions of the median, but in this problem, we will use the described one.

Given two integers $ n $ and $ k $ and non-decreasing array of $ nk $ integers. Divide all numbers into $ k $ arrays of size $ n $ , such that each number belongs to exactly one array.

You want the sum of medians of all $ k $ arrays to be the maximum possible. Find this maximum possible sum.

## 说明/提示

The examples of possible divisions into arrays for all test cases of the first test:

Test case $ 1 $ : $ [0, 24], [34, 58], [62, 64], [69, 78] $ . The medians are $ 0, 34, 62, 69 $ . Their sum is $ 165 $ .

Test case $ 2 $ : $ [27, 61], [81, 91] $ . The medians are $ 27, 81 $ . Their sum is $ 108 $ .

Test case $ 3 $ : $ [2, 91, 92, 95], [4, 36, 53, 82], [16, 18, 21, 27] $ . The medians are $ 91, 36, 18 $ . Their sum is $ 145 $ .

Test case $ 4 $ : $ [3, 33, 35], [11, 94, 99], [12, 38, 67], [22, 69, 71] $ . The medians are $ 33, 94, 38, 69 $ . Their sum is $ 234 $ .

Test case $ 5 $ : $ [11, 41] $ . The median is $ 11 $ . The sum of the only median is $ 11 $ .

Test case $ 6 $ : $ [1, 1, 1], [1, 1, 1], [1, 1, 1] $ . The medians are $ 1, 1, 1 $ . Their sum is $ 3 $ .

## 样例 #1

### 输入

```
6
2 4
0 24 34 58 62 64 69 78
2 2
27 61 81 91
4 3
2 4 16 18 21 27 36 53 82 91 92 95
3 4
3 11 12 22 33 35 38 67 69 71 94 99
2 1
11 41
3 3
1 1 1 1 1 1 1 1 1```

### 输出

```
165
108
145
234
11
3```

# AI分析结果

### 题目内容重写

#### 题目描述

一个长度为 $n$ 的整数数组的中位数是数组元素按非递减顺序排列后第 $\lceil \frac{n}{2} \rceil$（向上取整）个位置的数。位置编号从 $1$ 开始。例如，数组 $[2, 6, 4, 1, 3, 5]$ 的中位数是 $3$。在本题中，我们使用这个定义。

给定两个整数 $n$ 和 $k$，以及一个长度为 $nk$ 的非递减整数数组。将所有数分成 $k$ 个大小为 $n$ 的数组，每个数恰好属于一个数组。

你需要使所有 $k$ 个数组的中位数之和尽可能大。求这个最大可能和。

#### 说明/提示

以下是所有测试用例的示例划分：

测试用例 $1$：$[0, 24], [34, 58], [62, 64], [69, 78]$。中位数分别为 $0, 34, 62, 69$。它们的和为 $165$。

测试用例 $2$：$[27, 61], [81, 91]$。中位数分别为 $27, 81$。它们的和为 $108$。

测试用例 $3$：$[2, 91, 92, 95], [4, 36, 53, 82], [16, 18, 21, 27]$。中位数分别为 $91, 36, 18$。它们的和为 $145$。

测试用例 $4$：$[3, 33, 35], [11, 94, 99], [12, 38, 67], [22, 69, 71]$。中位数分别为 $33, 94, 38, 69$。它们的和为 $234$。

测试用例 $5$：$[11, 41]$。中位数为 $11$。唯一的中位数和为 $11$。

测试用例 $6$：$[1, 1, 1], [1, 1, 1], [1, 1, 1]$。中位数分别为 $1, 1, 1$。它们的和为 $3$。

#### 样例 #1

##### 输入

```
6
2 4
0 24 34 58 62 64 69 78
2 2
27 61 81 91
4 3
2 4 16 18 21 27 36 53 82 91 92 95
3 4
3 11 12 22 33 35 38 67 69 71 94 99
2 1
11 41
3 3
1 1 1 1 1 1 1 1 1
```

##### 输出

```
165
108
145
234
11
3
```

### 算法分类
贪心

### 题解分析与结论

本题的核心思路是通过贪心策略最大化每组中位数的和。具体来说，先将数组排序，然后从后向前选取每组的中位数，确保每组的中位数尽可能大。通过这种方式，可以保证每组的中位数之和最大化。

### 所选高分题解

#### 题解1：作者：Retired_lvmao (赞：4)

**星级：5星**

**关键亮点：**
- 思路清晰，直接通过排序和贪心策略解决问题。
- 代码简洁，逻辑明确，易于理解。
- 时间复杂度为 $O(p \log p)$，其中 $p = n \times k$，效率较高。

**代码核心实现：**
```cpp
sort(s+1,s+n*k+1); 
int hd=1,tl=n*k;
while(hd<=tl)
{
    if(n&1)
    {
        hd+=n/2;
        tl-=n/2+1;
        tot+=s[tl+1];
    }
    else
    {
        hd+=n/2-1;
        tl-=n/2+1;
        tot+=s[tl+1];
    }
}
```

#### 题解2：作者：nytyq (赞：0)

**星级：4星**

**关键亮点：**
- 通过逆向思维，从后向前选取中位数，确保每组中位数尽可能大。
- 代码简洁，逻辑清晰，易于理解。

**代码核心实现：**
```cpp
sort(a+1,a+1+L);
int h=1,t=L;
int sum=0;
while(h<=t){
    if(n%2==1){
        h+=n/2;
        t-=n/2+1;
        sum+=a[t+1];
    }
    else{
        h+=n/2-1;
        t-=n/2+1;
        sum+=a[t+1];
    }
}
```

#### 题解3：作者：charleshe (赞：0)

**星级：4星**

**关键亮点：**
- 通过排序和贪心策略，确保每组中位数尽可能大。
- 代码简洁，逻辑清晰，易于理解。

**代码核心实现：**
```cpp
sort(a+1,a+n+1);
int hd=1,tl=p;
int ans=0;
int c,d;
if(n%2==0) c=n/2+1,d=n/2-1;
else c=n/2+1,d=n/2;
for(int i=1;i<=k;i++){
    hd+=d;
    tl-=c;
    ans+=a[tl+1];
}
```

### 最优关键思路与技巧

1. **排序与贪心策略**：先将数组排序，然后通过贪心策略从后向前选取每组的中位数，确保每组的中位数尽可能大。
2. **时间复杂度优化**：通过排序和贪心策略，时间复杂度为 $O(p \log p)$，其中 $p = n \times k$，效率较高。

### 可拓展之处

- 类似的问题可以通过贪心策略和排序来解决，例如在分组问题中最大化或最小化某些指标。
- 可以扩展到多维数组或更复杂的分组问题中。

### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：43.95秒