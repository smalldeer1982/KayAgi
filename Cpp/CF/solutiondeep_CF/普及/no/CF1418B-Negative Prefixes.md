# 题目信息

# Negative Prefixes

## 题目描述

You are given an array $ a $ , consisting of $ n $ integers.

Each position $ i $ ( $ 1 \le i \le n $ ) of the array is either locked or unlocked. You can take the values on the unlocked positions, rearrange them in any order and place them back into the unlocked positions. You are not allowed to remove any values, add the new ones or rearrange the values on the locked positions. You are allowed to leave the values in the same order as they were.

For example, let $ a = [-1, 1, \underline{3}, 2, \underline{-2}, 1, -4, \underline{0}] $ , the underlined positions are locked. You can obtain the following arrays:

- $ [-1, 1, \underline{3}, 2, \underline{-2}, 1, -4, \underline{0}] $ ;
- $ [-4, -1, \underline{3}, 2, \underline{-2}, 1, 1, \underline{0}] $ ;
- $ [1, -1, \underline{3}, 2, \underline{-2}, 1, -4, \underline{0}] $ ;
- $ [1, 2, \underline{3}, -1, \underline{-2}, -4, 1, \underline{0}] $ ;
- and some others.

Let $ p $ be a sequence of prefix sums of the array $ a $ after the rearrangement. So $ p_1 = a_1 $ , $ p_2 = a_1 + a_2 $ , $ p_3 = a_1 + a_2 + a_3 $ , $ \dots $ , $ p_n = a_1 + a_2 + \dots + a_n $ .

Let $ k $ be the maximum $ j $ ( $ 1 \le j \le n $ ) such that $ p_j < 0 $ . If there are no $ j $ such that $ p_j < 0 $ , then $ k = 0 $ .

Your goal is to rearrange the values in such a way that $ k $ is minimum possible.

Output the array $ a $ after the rearrangement such that the value $ k $ for it is minimum possible. If there are multiple answers then print any of them.

## 说明/提示

In the first testcase you can rearrange all values however you want but any arrangement will result in $ k = 0 $ . For example, for an arrangement $ [1, 2, 3] $ , $ p=[1, 3, 6] $ , so there are no $ j $ such that $ p_j < 0 $ . Thus, $ k = 0 $ .

In the second testcase you are not allowed to rearrange any elements. Thus, the printed array should be exactly the same as the initial one.

In the third testcase the prefix sums for the printed array are $ p = [-8, -14, -13, -9, -5, 2, 0] $ . The maximum $ j $ is $ 5 $ , thus $ k = 5 $ . There are no arrangements such that $ k < 5 $ .

In the fourth testcase $ p = [-4, -4, -3, 3, 6] $ .

In the fifth testcase $ p = [-1, 3, 10, 2, 12, 11] $ .

## 样例 #1

### 输入

```
5
3
1 3 2
0 0 0
4
2 -3 4 -1
1 1 1 1
7
-8 4 -2 -6 4 7 1
1 0 0 0 1 1 0
5
0 1 -4 6 3
0 0 0 1 1
6
-1 7 10 4 -8 -1
1 0 0 0 0 1```

### 输出

```
1 2 3
2 -3 4 -1
-8 -6 1 4 4 7 -2
-4 0 1 6 3
-1 4 7 -8 10 -1```

# AI分析结果

### 题目重写
#### 题目描述
给定一个由 $n$ 个整数组成的数组 $a$。

数组中的每个位置 $i$（$1 \le i \le n$）要么被锁定，要么未被锁定。你可以将未被锁定位置上的值进行任意重排，并将它们放回未被锁定的位置。你不能删除任何值、添加新值或重排被锁定位置上的值。你可以选择保持这些值的顺序不变。

例如，设 $a = [-1, 1, \underline{3}, 2, \underline{-2}, 1, -4, \underline{0}]$，下划线位置表示被锁定。你可以得到以下数组：

- $[-1, 1, \underline{3}, 2, \underline{-2}, 1, -4, \underline{0}]$；
- $[-4, -1, \underline{3}, 2, \underline{-2}, 1, 1, \underline{0}]$；
- $[1, -1, \underline{3}, 2, \underline{-2}, 1, -4, \underline{0}]$；
- $[1, 2, \underline{3}, -1, \underline{-2}, -4, 1, \underline{0}]$；
- 以及其他一些排列。

设 $p$ 为数组 $a$ 重排后的前缀和序列。即 $p_1 = a_1$，$p_2 = a_1 + a_2$，$p_3 = a_1 + a_2 + a_3$，$\dots$，$p_n = a_1 + a_2 + \dots + a_n$。

设 $k$ 为最大的 $j$（$1 \le j \le n$）使得 $p_j < 0$。如果不存在这样的 $j$，则 $k = 0$。

你的目标是重排数组中的值，使得 $k$ 尽可能小。输出重排后的数组 $a$，使得 $k$ 最小。如果有多个答案，输出任意一个即可。

### 算法分类
贪心

### 题解分析与结论
所有题解都采用了贪心策略，即将未被锁定的数从大到小排序，然后依次放回未被锁定的位置。这种策略的目的是尽可能使前缀和快速变为正数，从而最小化 $k$。

### 所选高星题解
#### 题解1：KSToki (3星)
**关键亮点**：代码简洁，思路清晰，直接使用贪心策略，将未被锁定的数从大到小排序后放回原数组。
**核心代码**：
```cpp
sort(t+1,t+cnt+1,cmp);
for(register int i=1,j=1;i<=n;++i)
{
    if(l[i])
        printf("%d ",a[i]);
    else
    {
        printf("%d ",t[j]);
        ++j;
    }
}
```

#### 题解2：Wide_Master (3星)
**关键亮点**：代码结构清晰，使用了 `greater<int>()` 进行排序，逻辑简单明了。
**核心代码**：
```cpp
sort(c+1,c+1+cnt,greater<int>());
cnt=0;
for(int i=1;i<=n;i++){
    if(b[i])cout<<a[i]<<" ";
    else cout<<c[++cnt]<<" ";
}
```

#### 题解3：czh___ (3星)
**关键亮点**：代码逻辑清晰，使用了 `stable_sort` 进行排序，确保排序的稳定性。
**核心代码**：
```cpp
stable_sort(b,b+j,cmp);
i=0;
j=0;
while(i<n){
    if(c[i]==0)
        cout<< b[j++]<<" ";
    else
        cout<<a[i]<<" ";
    i++;
}
```

### 最优关键思路
将所有未被锁定的数从大到小排序，然后依次放回未被锁定的位置。这种贪心策略能够确保前缀和尽快变为正数，从而最小化 $k$。

### 可拓展之处
类似的问题可以通过贪心策略解决，尤其是在需要优化某种序列性质（如前缀和、后缀和等）时，贪心策略往往能够提供有效的解决方案。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得总结
在解决类似问题时，贪心策略往往能够提供简洁且有效的解决方案。关键在于如何确定贪心的策略，确保每一步的选择都是最优的。

---
处理用时：31.15秒