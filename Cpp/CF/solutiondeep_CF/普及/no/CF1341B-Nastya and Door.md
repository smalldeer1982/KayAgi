# 题目信息

# Nastya and Door

## 题目描述

On February 14 Denis decided to give Valentine to Nastya and did not come up with anything better than to draw a huge red heart on the door of the length $ k $ ( $ k \ge 3 $ ). Nastya was very confused by this present, so she decided to break the door, throwing it on the mountains.

Mountains are described by a sequence of heights $ a_1, a_2,       \dots, a_n $ in order from left to right ( $ k \le n $ ). It is guaranteed that neighboring heights are not equal to each other (that is, $ a_i \ne a_{i+1} $ for all $ i $ from $ 1 $ to $ n-1 $ ).

Peaks of mountains on the segment $ [l,r] $ (from $ l $ to $ r $ ) are called indexes $ i $ such that $ l < i <       r $ , $ a_{i - 1} < a_i $ and $ a_i > a_{i + 1} $ . It is worth noting that the boundary indexes $ l $ and $ r $ for the segment are not peaks. For example, if $ n=8 $ and $ a=[3,1,4,1,5,9,2,6] $ , then the segment $ [1,8] $ has only two peaks (with indexes $ 3 $ and $ 6 $ ), and there are no peaks on the segment $ [3, 6] $ .

To break the door, Nastya throws it to a segment $ [l,l+k-1] $ of consecutive mountains of length $ k $ ( $ 1 \le l \le       n-k+1 $ ). When the door touches the peaks of the mountains, it breaks into two parts, after that these parts will continue to fall in different halves and also break into pieces when touching the peaks of the mountains, and so on. Formally, the number of parts that the door will break into will be equal to $ p+1 $ , where $ p $ is the number of peaks on the segment $ [l,l+k-1] $ .

Nastya wants to break it into as many pieces as possible. Help her choose such a segment of mountains $ [l, l+k-1] $ that the number of peaks on it is maximum. If there are several optimal segments, Nastya wants to find one for which the value $ l $ is minimal.

Formally, you need to choose a segment of mountains $ [l,       l+k-1] $ that has the maximum number of peaks. Among all such segments, you need to find the segment that has the minimum possible value $ l $ .

## 说明/提示

In the first example, you need to select a segment of mountains from $ 2 $ to $ 7 $ . In this segment, the indexes $ 3 $ and $ 6 $ are peaks, so the answer is $ 3 $ (only $ 2 $ peaks, so the door will break into $ 3 $ parts). It is not difficult to notice that the mountain segments $ [1, 6] $ and $ [3, 8] $ are not suitable since they only have a $ 1 $ peak (for the first segment, the $ 6 $ index is not a peak, and for the second segment, the $ 3 $ index is not a peak).

In the second example, you need to select a segment of mountains from $ 2 $ to $ 4 $ . In this segment, the index $ 3 $ is a peak, so the answer is $ 2 $ (only $ 1 $ peak, so the door will break into $ 2 $ parts).

In the third example, you need to select a segment of mountains from $ 1 $ to $ 4 $ . In this segment, the index $ 3 $ is a peak, so the answer is $ 2 $ (only $ 1 $ peak, so the door will break into $ 2 $ parts). You can see that on the segments $ [2, 5] $ , $ [4, 7] $ and $ [5, 8] $ the number of peaks is also $ 1 $ , but these segments have a left border greater than the segment $ [1, 4] $ , so they are not the correct answer.

## 样例 #1

### 输入

```
5
8 6
1 2 4 1 2 4 1 2
5 3
3 2 3 2 1
10 4
4 3 4 3 2 3 2 1 0 1
15 7
3 7 4 8 2 3 4 5 21 2 3 4 2 1 3
7 5
1 2 3 4 5 6 1```

### 输出

```
3 2
2 2
2 1
3 1
2 3```

# AI分析结果

### 题目内容重写

#### 题目描述

在2月14日，Denis决定给Nastya送情人节礼物，他决定在长度为$k$（$k \ge 3$）的门上画一个巨大的红色心形。Nastya对这个礼物感到非常困惑，于是她决定把门扔到山上，以此来破坏它。

山脉由一系列高度$a_1, a_2, \dots, a_n$从左到右描述（$k \le n$）。保证相邻的高度不相等（即对于所有$i$从$1$到$n-1$，$a_i \ne a_{i+1}$）。

在区间$[l,r]$（从$l$到$r$）内的山峰被称为索引$i$，满足$l < i < r$，$a_{i - 1} < a_i$且$a_i > a_{i + 1}$。值得注意的是，区间的边界索引$l$和$r$不是山峰。例如，如果$n=8$且$a=[3,1,4,1,5,9,2,6]$，那么区间$[1,8]$只有两个山峰（索引$3$和$6$），而区间$[3, 6]$没有山峰。

为了破坏门，Nastya将它扔到长度为$k$的连续山脉区间$[l,l+k-1]$上（$1 \le l \le n-k+1$）。当门碰到山峰时，它会分成两部分，之后这些部分会继续落在不同的半部分，并在碰到山峰时再次分裂，依此类推。形式上，门分裂成的部分数等于$p+1$，其中$p$是区间$[l,l+k-1]$内的山峰数。

Nastya希望门分裂成尽可能多的部分。帮助她选择一个山脉区间$[l, l+k-1]$，使得该区间内的山峰数最大。如果有多个最优区间，Nastya希望找到$l$值最小的那个。

形式上，你需要选择一个山脉区间$[l, l+k-1]$，使得该区间内的山峰数最大。在所有这样的区间中，你需要找到$l$值最小的那个。

### 算法分类
前缀和

### 题解分析与结论

所有题解都采用了相似的核心思路：首先标记出所有山峰的位置，然后使用前缀和来快速计算任意区间内的山峰数量，最后通过枚举所有可能的区间来找到山峰数最多的区间。难点在于如何高效地计算区间内的山峰数量，以及如何处理边界条件（区间两端的山峰不计入总数）。

### 精选题解

#### 题解1：作者：tangber (赞：8)
**星级：4.5**
**关键亮点：**
- 使用前缀和快速计算区间内的山峰数量。
- 代码简洁，逻辑清晰。
- 处理边界条件的方法明确。

**核心代码：**
```cpp
for(int i=2;i<=n-1;i++) if(a[i-1]<=a[i] and a[i]>=a[i+1]) flag[i]=1;
for(int i=2;i<=n;i++) feng[i]=feng[i-1]+flag[i];
for(int i=1;i<=n-k+1;i++) {
    int anss=feng[i+k-2]-feng[i]+1;
    if(anss>ans) {
        q=i;
        ans=anss;
    }
}
```

#### 题解2：作者：Stars_visitor_tyw (赞：2)
**星级：4**
**关键亮点：**
- 使用前缀和计算山峰数量，逻辑清晰。
- 代码结构合理，易于理解。
- 处理边界条件的方法明确。

**核心代码：**
```cpp
for(int i=2;i<n;i++) {
    if(a[i]>=a[i-1]&&a[i]>=a[i+1]) x[i]=1;
}
for(int i=1;i<=n;i++) sum[i]=sum[i-1]+x[i];
for(int i=1;i<=n-k+1;i++) {
    int p=sum[i+k-2]-sum[i]+1;
    if(p>ans) {
        l=i;
        ans=p;
    }
}
```

#### 题解3：作者：HEzzz (赞：0)
**星级：4**
**关键亮点：**
- 使用前缀和计算山峰数量，逻辑清晰。
- 代码简洁，易于理解。
- 处理边界条件的方法明确。

**核心代码：**
```cpp
_rep(i,1,n) if(a[i-1]<=a[i]&&a[i]>=a[i+1]) f[i]=1;
_rep(i,1,n) f[i]+=f[i-1];
_rep(i,1,n-k+1) {
    int cnt=f[i+k-2]-f[i]+1;
    if(cnt>ans) ans=cnt,beg=i;
}
```

### 最优关键思路或技巧
1. **前缀和的应用**：通过前缀和快速计算任意区间内的山峰数量，时间复杂度为$O(1)$。
2. **边界处理**：区间两端的山峰不计入总数，因此在计算区间内的山峰数量时，区间需要向内缩1。
3. **枚举所有可能的区间**：通过枚举所有可能的区间，找到山峰数最多的区间，时间复杂度为$O(n)$。

### 可拓展之处
- **类似算法套路**：前缀和的应用广泛，可以用于解决区间求和、区间最大值等问题。
- **同类型题**：可以尝试解决其他需要快速计算区间内特定元素数量的问题。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)

### 个人心得摘录
- **调试经历**：在处理边界条件时，容易忽略区间两端的山峰不计入总数的问题，导致结果错误。通过仔细检查代码逻辑，最终解决了这个问题。
- **顿悟感想**：前缀和的应用可以大大简化区间计算问题，提高代码效率。

---
处理用时：40.82秒