# 题目信息

# Robin Hood in Town

## 题目描述

In Sherwood, we judge a man not by his wealth, but by his merit.



Look around, the rich are getting richer, and the poor are getting poorer. We need to take from the rich and give to the poor. We need Robin Hood!

There are $ n $ people living in the town. Just now, the wealth of the $ i $ -th person was $ a_i $ gold. But guess what? The richest person has found an extra pot of gold!

More formally, find an $ a_j=max(a_1, a_2, \dots, a_n) $ , change $ a_j $ to $ a_j+x $ , where $ x $ is a non-negative integer number of gold found in the pot. If there are multiple maxima, it can be any one of them.

A person is unhappy if their wealth is strictly less than half of the average wealth $ ^{\text{∗}} $ .

If strictly more than half of the total population $ n $ are unhappy, Robin Hood will appear by popular demand.

Determine the minimum value of $ x $ for Robin Hood to appear, or output $ -1 $ if it is impossible.

 $ ^{\text{∗}} $ The average wealth is defined as the total wealth divided by the total population $ n $ , that is, $ \frac{\sum a_i}{n} $ , the result is a real number.

## 说明/提示

In the first test case, it is impossible for a single person to be unhappy.

In the second test case, there is always $ 1 $ happy person (the richest).

In the third test case, no additional gold are required, so the answer is $ 0 $ .

In the fourth test case, after adding $ 15 $ gold, the average wealth becomes $ \frac{25}{4} $ , and half of this average is $ \frac{25}{8} $ , resulting in $ 3 $ people being unhappy.

In the fifth test case, after adding $ 16 $ gold, the average wealth becomes $ \frac{31}{5} $ , resulting in $ 3 $ people being unhappy.

## 样例 #1

### 输入

```
6
1
2
2
2 19
3
1 3 20
4
1 2 3 4
5
1 2 3 4 5
6
1 2 1 1 1 25```

### 输出

```
-1
-1
0
15
16
0```

# AI分析结果

### 题目内容重写

在舍伍德，我们不以财富评判一个人，而是以他的品德。

看看周围，富人越来越富，穷人越来越穷。我们需要劫富济贫。我们需要罗宾汉！

镇上有 $n$ 个人。现在，第 $i$ 个人的财富是 $a_i$ 金币。但你知道吗？最富有的人发现了一罐额外的金币！

更正式地说，找到一个 $a_j=\max(a_1, a_2, \dots, a_n)$，将 $a_j$ 改为 $a_j+x$，其中 $x$ 是从罐子里找到的非负整数金币。如果有多个最大值，可以任选其中一个。

如果一个人的财富严格低于平均财富的一半，那么他会感到不幸福。

如果超过一半的人口感到不幸福，罗宾汉就会应大家的要求出现。

确定让罗宾汉出现的最小 $x$ 值，或者输出 $-1$ 如果这不可能。

$^{\text{∗}}$ 平均财富定义为总财富除以总人口 $n$，即 $\frac{\sum a_i}{n}$，结果是一个实数。

### 题解分析与结论

#### 综合分析与结论

本题的核心是找到一个最小的 $x$，使得在将最富有的人的财富增加 $x$ 后，超过一半的人的财富严格低于平均财富的一半。大多数题解采用了排序和二分查找的思路，部分题解通过数学推导直接计算了 $x$ 的值。

#### 最优关键思路与技巧

1. **排序与二分查找**：通过排序数组，可以快速找到中位数，并结合二分查找来确定最小的 $x$。
2. **数学推导**：通过计算中位数与总和的关系，直接推导出 $x$ 的值，避免了复杂的计算。
3. **特判处理**：对于 $n \leq 2$ 的情况，直接输出 $-1$，因为不可能满足条件。

#### 可拓展之处

- **类似问题**：类似的问题可以通过排序和二分查找来解决，尤其是在需要找到满足特定条件的最小值或最大值时。
- **优化思路**：可以考虑使用更高效的排序算法或优化二分查找的实现，以提高代码的效率。

#### 推荐题目

1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

### 所选高分题解

#### 题解1：Temp113 (5星)

**关键亮点**：
- 使用了二分查找的思路，结合排序和验证函数，确保了算法的正确性和高效性。
- 代码结构清晰，易于理解和实现。

**核心代码**：
```cpp
bool check(int aa){
    tmp = a[n];
    a[n] += aa;
    s = 0;
    tot = 0;
    for(int i = 1; i <= n; i++) s += a[i];
    d = ((double) s) / n / 2;
    for(int i = 1; i <= n; i++) if(a[i] < d) tot++;
    a[n] = tmp;
    if(tot > ((double) n) / 2) return 1;
    else return 0;   
}
```

#### 题解2：Karieciation (4星)

**关键亮点**：
- 通过数学推导直接计算了 $x$ 的值，避免了复杂的计算过程。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
if(n<3)
{
    puts("-1");continue;
}
sort(a+1,a+1+n);
ll v=(ll)a[n+2>>1]*n<<1;
if(sum>v)
    puts("0");
else
    printf("%lld\n",v-sum+1);
```

#### 题解3：Super_Cube (4星)

**关键亮点**：
- 使用了二分查找的思路，结合排序和验证函数，确保了算法的正确性和高效性。
- 代码结构清晰，易于理解和实现。

**核心代码**：
```cpp
while(l<=r){
    long long mid=l+r>>1;
    a[n]+=mid;
    if(std::lower_bound(a+1,a+n+1,(s+mid)/2.0/n)-a-1>(n>>1))ans=mid,r=mid-1;
    else l=mid+1;
    a[n]-=mid;
}
```

---
处理用时：34.11秒