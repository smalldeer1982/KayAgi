# 题目信息

# Lecture Sleep

## 题目描述

Your friend Mishka and you attend a calculus lecture. Lecture lasts $ n $ minutes. Lecturer tells $ a_{i} $ theorems during the $ i $ -th minute.

Mishka is really interested in calculus, though it is so hard to stay awake for all the time of lecture. You are given an array $ t $ of Mishka's behavior. If Mishka is asleep during the $ i $ -th minute of the lecture then $ t_{i} $ will be equal to $ 0 $ , otherwise it will be equal to $ 1 $ . When Mishka is awake he writes down all the theorems he is being told — $ a_{i} $ during the $ i $ -th minute. Otherwise he writes nothing.

You know some secret technique to keep Mishka awake for $ k $ minutes straight. However you can use it only once. You can start using it at the beginning of any minute between $ 1 $ and $ n-k+1 $ . If you use it on some minute $ i $ then Mishka will be awake during minutes $ j $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961B/74a70105e36a7144196883409708a1b859a35796.png) and will write down all the theorems lecturer tells.

You task is to calculate the maximum number of theorems Mishka will be able to write down if you use your technique only once to wake him up.

## 说明/提示

In the sample case the better way is to use the secret technique at the beginning of the third minute. Then the number of theorems Mishka will be able to write down will be equal to $ 16 $ .

## 样例 #1

### 输入

```
6 3
1 3 5 2 5 4
1 1 0 1 0 0
```

### 输出

```
16
```

# AI分析结果

### 题目翻译
你的朋友米什卡（Mishka）和你一起参加一场微积分讲座。讲座持续 $n$ 分钟，讲师在第 $i$ 分钟会讲解 $a_{i}$ 个定理。

米什卡对微积分非常感兴趣，然而在整个讲座过程中保持清醒是很困难的。给定一个数组 $t$ 来表示米什卡的状态，如果米什卡在第 $i$ 分钟睡着了，那么 $t_{i}$ 等于 $0$，否则 $t_{i}$ 等于 $1$。当米什卡清醒时，他会记录下讲师在该分钟所讲的所有定理（即第 $i$ 分钟的 $a_{i}$ 个定理），睡着时则什么都不记录。

你知道一种能让米什卡保持清醒 $k$ 分钟的秘密技巧，但只能使用一次。你可以在第 $1$ 到第 $n - k + 1$ 分钟的任意一分钟开始时使用这个技巧。如果你在第 $i$ 分钟使用该技巧，那么米什卡在满足 $i\leq j\leq i + k - 1$ 的所有分钟 $j$ 都会保持清醒，并记录下讲师讲解的所有定理。

你的任务是计算出，如果你仅使用一次这个技巧来让米什卡保持清醒，他最多能记录下多少个定理。

### 算法分类
枚举

### 综合分析与结论
这些题解主要围绕如何计算在使用一次使米什卡保持清醒 $k$ 分钟的技巧后，他能记录的最多定理数。不同题解采用了不同的算法思路，包括暴力枚举、双指针、前缀和等。

暴力枚举思路简单直接，但时间复杂度较高，容易超时。双指针和前缀和的方法则是通过对相邻区间的关系进行分析，避免了重复计算，从而优化了时间复杂度。

### 所选题解
- **爬行者小郑（4星）**
  - **关键亮点**：思路清晰，先介绍了双指针的基本思想，再应用到本题中，通过双指针维护区间和，避免了重复计算，代码可读性高。
  - **核心代码**：
```cpp
#include <iostream>
using namespace std;
int n,k;
int sum;
int a[100005],t[100005];
int ans;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>t[i];
    int r=k;
    for(int i=1;i<=k;i++)
    {
        sum+=a[i];
    }
    for(int i=k+1;i<=n;i++)sum+=a[i]*t[i];
    for(int l=1;l<=n-k+1;l++)
    {
        ans=max(ans,sum);
        if(!t[l])sum-=a[l];
        if(!t[r+1])sum+=a[r+1];
        r++;
    }
    cout<<ans<<endl;
    return 0;
}
```
  - **核心实现思想**：先初始化第一个长度为 $k$ 的区间的和，再计算后面未受影响部分的和。然后通过双指针枚举左端点，根据 $t$ 数组的值更新区间和，同时更新最大值。

- **yuangq（4星）**
  - **关键亮点**：提供了两种方法，一种是暴力枚举，另一种是通过分析相邻区间的变化来优化，代码简洁明了。
  - **核心代码（法二）**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,maxs=-2147483647;
long long a[100005],t[100005];
int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>t[i];
    }
    long long s=0;
    for(int i=0;i<n;i++)
    {
        if(i<k)
        {
            s=s+a[i];
        }
        else
        {
            s=s+a[i]*t[i]; 
        }
    }
    maxs=s;
    for(int i=1;i<n-k+1;i++)
    {
        s=s-a[i-1];
        s=s+a[i-1]*t[i-1];
        s=s-a[i+k-1]*t[i+k-1];
        s=s+a[i+k-1];
        maxs=max(maxs,s);
    }
    cout<<maxs;
    return 0;
}
```
  - **核心实现思想**：先计算初始区间的和，然后通过减去左端点的值，加上左端点原本的贡献，减去右端点原本的贡献，加上右端点的值，来更新相邻区间的和，同时更新最大值。

- **tribool4_in（4星）**
  - **关键亮点**：思路清晰，先指出暴力枚举的复杂度问题，再给出优化方法，通过利用上一次的结果来计算当前区间的值，降低了时间复杂度。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
long long n, k, maxn = -2147483647;
long long a[N], t[N];
int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> t[i];
    long long tmp = 0;
    for (int i = 0; i < n; i++) {
        if (i < k) {
            tmp = tmp + a[i];
        } else {
            tmp = tmp + a[i] * t[i];
        }
    }
    maxn = tmp;
    for (int i = 1; i < n - k + 1; i++) {
        tmp = tmp - a[i - 1];
        tmp = tmp + a[i - 1] * t[i - 1];
        tmp = tmp - a[i + k - 1] * t[i + k - 1];
        tmp = tmp + a[i + k - 1];
        maxn = max(maxn, tmp);
    }
    cout << maxn << endl;
    return 0;
}
```
  - **核心实现思想**：先计算初始区间的和，然后通过更新相邻区间的端点值来更新区间和，同时更新最大值。

### 最优关键思路或技巧
- **双指针思想**：通过维护左右指针，利用相邻区间的重叠部分，避免重复计算，将时间复杂度从 $O(n^2)$ 优化到 $O(n)$。
- **前缀和思想**：通过预处理前缀和数组，可以快速计算区间和，减少重复计算。

### 可拓展之处
同类型题或类似算法套路：
- 滑动窗口问题：在一个数组中维护一个固定长度的窗口，通过移动窗口来计算区间的相关信息。
- 区间修改问题：给定一个数组和若干区间修改操作，求经过操作后数组的某些信息。

### 推荐题目
- P1886 滑动窗口 /【模板】单调队列
- P1115 最大子段和
- P2036 [COCI2008-2009#2] PERKET

### 个人心得摘录与总结
- **smallfang**：指出暴力枚举会超时的原因是进行了重复操作，通过分析相邻区间的变化，只看头尾两个数，避免了重复计算。
- **hgoicjl**：提到暴力枚举会 TLE，通过分析发现可以在读入时直接处理相关数据，避免了 $O(n^2)$ 的时间复杂度，从而成功 AC。 

---
处理用时：53.98秒