# 题目信息

# Odd Sum Segments

## 题目描述

You are given an array $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . You want to split it into exactly $ k $ non-empty non-intersecting subsegments such that each subsegment has odd sum (i. e. for each subsegment, the sum of all elements that belong to this subsegment is odd). It is impossible to rearrange (shuffle) the elements of a given array. Each of the $ n $ elements of the array $ a $ must belong to exactly one of the $ k $ subsegments.

Let's see some examples of dividing the array of length $ 5 $ into $ 3 $ subsegments (not necessarily with odd sums): $ [1, 2, 3, 4, 5] $ is the initial array, then all possible ways to divide it into $ 3 $ non-empty non-intersecting subsegments are described below:

- $ [1], [2], [3, 4, 5] $ ;
- $ [1], [2, 3], [4, 5] $ ;
- $ [1], [2, 3, 4], [5] $ ;
- $ [1, 2], [3], [4, 5] $ ;
- $ [1, 2], [3, 4], [5] $ ;
- $ [1, 2, 3], [4], [5] $ .

Of course, it can be impossible to divide the initial array into exactly $ k $ subsegments in such a way that each of them will have odd sum of elements. In this case print "NO". Otherwise, print "YES" and any possible division of the array. See the output format for the detailed explanation.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
3
5 3
7 18 3 14 1
5 4
1 2 3 4 5
6 2
1 2 8 4 10 2
```

### 输出

```
YES
1 3 5
NO
NO
```

# AI分析结果

### 题目翻译
# 奇数和子段

## 题目描述
给定一个由 $n$ 个整数 $a_1, a_2, \dots, a_n$ 组成的数组 $a$。你需要将其恰好分割成 $k$ 个非空且不相交的子段，使得每个子段的元素和为奇数。数组元素的顺序不能重新排列（打乱），数组 $a$ 中的每个元素都必须恰好属于 $k$ 个子段中的一个。

让我们来看一个将长度为 $5$ 的数组分割成 $3$ 个子段（不一定元素和为奇数）的例子：$[1, 2, 3, 4, 5]$ 是初始数组，那么将其分割成 $3$ 个非空且不相交子段的所有可能方式如下：
- $[1], [2], [3, 4, 5]$；
- $[1], [2, 3], [4, 5]$；
- $[1], [2, 3, 4], [5]$；
- $[1, 2], [3], [4, 5]$；
- $[1, 2], [3, 4], [5]$；
- $[1, 2, 3], [4], [5]$。

当然，可能无法将初始数组恰好分割成 $k$ 个子段，使得每个子段的元素和为奇数。在这种情况下，输出 "NO"。否则，输出 "YES" 以及任意一种可能的分割方式。具体输出格式见下文。

你需要回答 $q$ 个独立的查询。

## 样例 #1
### 输入
```
3
5 3
7 18 3 14 1
5 4
1 2 3 4 5
6 2
1 2 8 4 10 2
```
### 输出
```
YES
1 3 5
NO
NO
```

### 综合分析与结论
这些题解的核心思路都是围绕将数组分成 $k$ 个和为奇数的子段展开。部分题解利用奇数相加的特性，只关注奇数的个数和位置；部分题解采用贪心策略，尽量让前面的子段长度短。
- **思路对比**：HoshizoraZ 和 j1ANGFeng 的思路类似，采用贪心策略，优先让前面子段和为奇数且尽量短；__shadow__、xh001、lygmh 和 xukuan 则聚焦于奇数的个数和位置，通过判断奇数个数是否满足条件来确定是否有解。
- **算法要点**：使用前缀和可快速计算区间和；只统计奇数位置能简化问题。
- **解决难点**：关键在于判断能否分成 $k$ 个和为奇数的子段，以及在有解时确定分割方案。

### 所选题解
- **作者：HoshizoraZ（4星）**
    - **关键亮点**：思路清晰，使用前缀和优化区间和的计算，代码可读性高。
    - **核心代码**：
```cpp
#include <cstdio>
typedef long long ll;
 
ll q, n, k, a, ans[200010], sum[200010], cnt, last;
 
int main(){
    scanf("%lld", &q);
    while(q--){
        cnt = last = 0;
        scanf("%lld%lld", &n, &k);
        for(ll i=1; i<=n; i++){
            scanf("%lld", &a);
            sum[i] = sum[i - 1] + a;
        }
        for(ll i=1; i<=n; i++){
            if(cnt + 1 == k) break;
            if((sum[i] - sum[last]) & 1){
                ans[++cnt] = i;
                last = i;
            } 
        }
        if(cnt + 1 == k && ((sum[n] - sum[last]) & 1)){
            puts("YES");
            for(ll i=1; i<=cnt; i++)	
                printf("%lld ", ans[i]);
            printf("%lld\n", n);
        }
        else puts("NO");
    }
    return 0;
}
```
    - **核心思想**：先预处理前缀和，然后遍历数组，一遇到和为奇数的区间就划分成一个子段，分 $k - 1$ 个子段后停止，最后判断剩余部分和是否为奇数。

- **作者：__shadow__（4星）**
    - **关键亮点**：思路巧妙，利用奇数相加的规律，只关注奇数位置，简化判断过程。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<stdio.h>
#include<cstdio>
#include<queue>
using namespace std;
const int N = 2 * 1e5;
int a[N];
int n, k, t, sum;
int main()
{
    int Q;
    scanf ("%d", &Q);
    while (Q--)
    {
        sum = 0;
        scanf ("%d%d", &n, &k);
        for (int i = 1;i <= n; i++)
        {
            scanf ("%d", &t);
            if (t % 2!= 0)
                a[++sum] = i;
        }
        if (sum < k || (sum - k) % 2!= 0)
        {
            printf ("NO\n");
            continue;
        }
        printf ("YES\n");
        for (int i = 1;i <= k - 1; i++)
            printf ("%d ", a[i]);
        printf ("%d\n", n);
    }
    return 0;
}
```
    - **核心思想**：统计奇数的个数和位置，若奇数个数不少于 $k$ 且比 $k$ 多的个数为偶数，则有解，输出前 $k - 1$ 个奇数的位置和 $n$。

### 最优关键思路或技巧
- 利用奇数相加的特性，只关注奇数的个数和位置，可大大简化问题。
- 使用前缀和预处理，能在 $O(1)$ 时间内计算区间和。

### 拓展思路
同类型题目可能会改变分割条件，如要求子段和为偶数，或对子段长度有要求。解题时仍可从数字的奇偶性和贪心策略入手。

### 洛谷推荐题目
- P1115 最大子段和
- P2671 [NOIP2015 普及组] 求和
- P1719 最大加权矩形

### 个人心得摘录与总结
- **作者：lygmh**：第一眼想爆搜，第二眼发现是水题。总结：做题时不要急于用复杂算法，先分析题目特性，可能有简单解法。 

---
处理用时：34.07秒