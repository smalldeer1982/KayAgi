# 题目信息

# Interview

## 题目描述

This is an interactive problem. If you are unsure how interactive problems work, then it is recommended to read [the guide for participants](https://codeforces.com/blog/entry/45307).

Before the last stage of the exam, the director conducted an interview. He gave Gon $ n $ piles of stones, the $ i $ -th pile having $ a_i $ stones.

Each stone is identical and weighs $ 1 $ grams, except for one special stone that is part of an unknown pile and weighs $ 2 $ grams.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1807E/47dd63211ca258927e8a8d0a66d052f86ba7c589.png) A picture of the first test case. Pile $ 2 $ has the special stone. The piles have weights of $ 1,3,3,4,5 $ , respectively.Gon can only ask the director questions of one kind: he can choose $ k $ piles, and the director will tell him the total weight of the piles chosen. More formally, Gon can choose an integer $ k $ ( $ 1 \leq k \leq n $ ) and $ k $ unique piles $ p_1, p_2, \dots, p_k $ ( $ 1 \leq p_i \leq n $ ), and the director will return the total weight $ m_{p_1} + m_{p_2} + \dots + m_{p_k} $ , where $ m_i $ denotes the weight of pile $ i $ .

Gon is tasked with finding the pile that contains the special stone. However, the director is busy. Help Gon find this pile in at most $ \mathbf{30} $ queries.

## 说明/提示

In the first test case, the stone with weight two is located in pile $ 2 $ , as shown in the picture. We perform the following interaction:

- $ \texttt{? 4 1 2 3 4} $ — ask the total weight of piles $ 1 $ , $ 2 $ , $ 3 $ , and $ 4 $ . The total weight we receive back is $ 1+3+3+4=11 $ .
- $ \texttt{? 2 2 3} $ — ask the total weight of piles $ 2 $ and $ 3 $ . The total weight we receive back is $ 3+3=6 $ .
- $ \texttt{? 1 2} $ — ask the total weight of pile $ 2 $ . The total weight we receive back is $ 3 $ .
- $ \texttt{! 2} $ — we have figured out that pile $ 2 $ contains the special stone, so we output it and move on to the next test case.

In the second test case, the stone with weight two is located on index $ 7 $ . We perform the following interaction:

- $ \texttt{? 4 2 3 5 6} $ — ask the total weight of piles $ 2 $ , $ 3 $ , $ 5 $ , and $ 6 $ . The total weight we receive back is $ 2+3+3+4=12 $ .
- $ \texttt{? 2 1 4} $ — ask the total weight of piles $ 1 $ and $ 4 $ . The total weight we receive back is $ 1+5=6 $ .
- $ \texttt{! 7} $ — we have somehow figured out that pile $ 7 $ contains the special stone, so we output it and end the interaction.

## 样例 #1

### 输入

```
2
5
1 2 3 4 5

11

6

3

7
1 2 3 5 3 4 2

12

6```

### 输出

```
? 4 1 2 3 4

? 2 2 3

? 1 2

! 2

? 4 2 3 5 6

? 2 1 4

! 7```

# AI分析结果

### 题目内容翻译

在考试的最后阶段，考官进行了一次面试。他给了 Gon $n$ 堆石头，第 $i$ 堆有 $a_i$ 块石头。

每块石头的重量都是 $1$ 克，除了一块特殊的石头，它位于未知的某一堆中，重量为 $2$ 克。

Gon 只能向考官提出一种问题：他可以选择 $k$ 堆石头，考官会告诉他所选堆的总重量。更正式地说，Gon 可以选择一个整数 $k$（$1 \leq k \leq n$）和 $k$ 个唯一的堆 $p_1, p_2, \dots, p_k$（$1 \leq p_i \leq n$），考官会返回总重量 $m_{p_1} + m_{p_2} + \dots + m_{p_k}$，其中 $m_i$ 表示第 $i$ 堆的重量。

Gon 的任务是找到包含特殊石头的堆。然而，考官很忙。帮助 Gon 在最多 $\mathbf{30}$ 次询问内找到这个堆。

### 算法分类
二分

### 题解分析与结论

本题的核心思路是通过二分查找来定位包含特殊石头的堆。由于每次询问可以将搜索范围缩小一半，因此最多需要 $\log_2 n$ 次询问，完全满足题目要求的 30 次限制。

#### 关键思路：
1. **前缀和预处理**：首先计算每堆石头的前缀和，方便后续快速计算任意区间的石头总数。
2. **二分查找**：通过二分法逐步缩小搜索范围，每次询问区间的前半部分，根据返回的总重量判断特殊石头是否在该区间内。
3. **交互处理**：注意每次询问后需要刷新输出缓冲区，确保交互顺利进行。

#### 最优技巧：
- **二分查找与前缀和的结合**：通过前缀和快速计算区间和，结合二分查找的高效性，能够在 $\log_2 n$ 次询问内找到目标堆。

### 评分较高的题解

#### 1. 作者：Larryyu (★★★★★)
**关键亮点**：
- 思路清晰，代码简洁，使用了前缀和和二分查找的结合，逻辑严密。
- 代码中明确处理了多组数据的情况，适合大规模测试。

**核心代码**：
```cpp
int l=1,r=n;
while(l<r){
    int mid=l+r>>1;
    cout<<"? "<<mid-l+1;
    for(int i=l;i<=mid;i++) cout<<" "<<i;
    cout<<endl;
    fflush(stdout);
    int get=read();
    if(sum[mid]-sum[l-1]!=get) r=mid;
    else l=mid+1;
}
cout<<"! "<<r<<endl;
fflush(stdout);
```

#### 2. 作者：arrow_king (★★★★☆)
**关键亮点**：
- 代码结构清晰，使用了前缀和和二分查找，逻辑明确。
- 代码中使用了 `printf` 和 `fflush(stdout)` 进行交互处理，适合 C++ 用户。

**核心代码**：
```cpp
int l=1,r=n;
while(l<r){
    int mid=(l+r)>>1;
    printf("? %d ",mid-l+1);
    for(int i=l;i<=mid;i++) printf("%d ",i);
    putchar('\n');
    fflush(stdout);
    int tmp=read();
    if(tmp!=sum[mid]-sum[l-1]) r=mid;
    else l=mid+1;
}
printf("! %d\n",l);
fflush(stdout);
```

#### 3. 作者：_299817_ (★★★★☆)
**关键亮点**：
- 代码结构清晰，使用了前缀和和二分查找，逻辑明确。
- 代码中使用了 `cout` 和 `fflush(stdout)` 进行交互处理，适合 C++ 用户。

**核心代码**：
```cpp
int l=1,r=n;
while(l<r){
    int mid=(l+r)>>1;
    cout<<"? "<<mid-l+1<<" ";
    for(int i=l;i<=mid;i++) cout<<i<<" ";
    cout<<endl;
    int k;
    cin>>k;
    if(sum[mid]-sum[l-1]==k) l=mid+1;
    else r=mid;
}
cout<<"! "<<l<<endl;
```

### 可拓展之处
- 类似的问题可以扩展到多块特殊石头的情况，或者石头的重量分布更复杂的情况。
- 二分查找与前缀和的结合可以应用于其他需要快速定位区间的问题，如区间和的查询、区间最大最小值等。

### 推荐题目
1. [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
3. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)

### 个人心得摘录
- **Larryyu**：强调了多组数据的处理，适合大规模测试，代码简洁明了。
- **arrow_king**：使用了 `printf` 和 `fflush(stdout)`，适合 C++ 用户，代码结构清晰。
- **_299817_**：使用了 `cout` 和 `fflush(stdout)`，代码结构清晰，逻辑明确。

---
处理用时：36.62秒