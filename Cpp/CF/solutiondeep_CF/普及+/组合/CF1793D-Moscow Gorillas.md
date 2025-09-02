# 题目信息

# Moscow Gorillas

## 题目描述

In winter, the inhabitants of the Moscow Zoo are very bored, in particular, it concerns gorillas. You decided to entertain them and brought a permutation $ p $ of length $ n $ to the zoo.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ occurs twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

The gorillas had their own permutation $ q $ of length $ n $ . They suggested that you count the number of pairs of integers $ l, r $ ( $ 1 \le l \le r \le n $ ) such that $ \operatorname{MEX}([p_l, p_{l+1}, \ldots, p_r])=\operatorname{MEX}([q_l, q_{l+1}, \ldots, q_r]) $ .

The $ \operatorname{MEX} $ of the sequence is the minimum integer positive number missing from this sequence. For example, $ \operatorname{MEX}([1, 3]) = 2 $ , $ \operatorname{MEX}([5]) = 1 $ , $ \operatorname{MEX}([3, 1, 2, 6]) = 4 $ .

You do not want to risk your health, so you will not dare to refuse the gorillas.

## 说明/提示

In the first example, two segments are correct – $ [1, 3] $ with $ \operatorname{MEX} $ equal to $ 4 $ in both arrays and $ [3, 3] $ with $ \operatorname{MEX} $ equal to $ 1 $ in both of arrays.

In the second example, for example, the segment $ [1, 4] $ is correct, and the segment $ [6, 7] $ isn't correct, because $ \operatorname{MEX}(5, 4) \neq \operatorname{MEX}(1, 4) $ .

## 样例 #1

### 输入

```
3
1 3 2
2 1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4```

### 输出

```
16```

## 样例 #3

### 输入

```
6
1 2 3 4 5 6
6 5 4 3 2 1```

### 输出

```
11```

# AI分析结果

### 题目中文重写
# 莫斯科大猩猩

## 题目描述
冬天，莫斯科动物园的居民们非常无聊，尤其是大猩猩。你决定逗逗它们，于是给动物园带去了一个长度为 $n$ 的排列 $p$。

长度为 $n$ 的排列是一个由 $n$ 个不同整数组成的数组，这些整数的范围是从 $1$ 到 $n$，顺序任意。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（数字 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（$n = 3$，但数组中出现了 $4$）。

大猩猩们有自己的长度为 $n$ 的排列 $q$。它们建议你计算满足 $\operatorname{MEX}([p_l, p_{l + 1}, \ldots, p_r]) = \operatorname{MEX}([q_l, q_{l + 1}, \ldots, q_r])$ 的整数对 $l, r$（$1 \leq l \leq r \leq n$）的数量。

序列的 $\operatorname{MEX}$ 是该序列中缺失的最小正整数。例如，$\operatorname{MEX}([1, 3]) = 2$，$\operatorname{MEX}([5]) = 1$，$\operatorname{MEX}([3, 1, 2, 6]) = 4$。

你不敢拿自己的健康冒险，所以不敢拒绝大猩猩们。

## 说明/提示
在第一个样例中，有两个合法的区间：$[1, 3]$，在两个数组中的 $\operatorname{MEX}$ 都等于 $4$；$[3, 3]$，在两个数组中的 $\operatorname{MEX}$ 都等于 $1$。

在第二个样例中，例如，区间 $[1, 4]$ 是合法的，而区间 $[6, 7]$ 不合法，因为 $\operatorname{MEX}(5, 4) \neq \operatorname{MEX}(1, 4)$。

## 样例 #1
### 输入
```
3
1 3 2
2 1 3
```
### 输出
```
2
```

## 样例 #2
### 输入
```
7
7 3 6 2 1 5 4
6 7 2 5 3 1 4
```
### 输出
```
16
```

## 样例 #3
### 输入
```
6
1 2 3 4 5 6
6 5 4 3 2 1
```
### 输出
```
11
```

### 综合分析与结论
这些题解的核心思路都是通过枚举 $\operatorname{MEX}$ 值，找出满足 $\operatorname{MEX}([p_l, p_{l + 1}, \ldots, p_r]) = \operatorname{MEX}([q_l, q_{l + 1}, \ldots, q_r])$ 的区间 $[l, r]$ 数量。具体做法是先记录每个数在两个排列中的位置，然后根据 $\operatorname{MEX}$ 的性质，确定区间左右端点的取值范围，通过排列组合计算满足条件的区间数量。

### 所选题解
- **作者：TernaryTree（5星）**
    - **关键亮点**：思路清晰，通过图文结合详细阐述了枚举 $\operatorname{MEX}$ 时的分类讨论情况，代码注释详细，易于理解。
    - **个人心得**：“阳间 CF 赛时切 D 祭”，体现了赛时做出题目的喜悦。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 2e5 + 1;

int n, ans;
int p[maxn];
int q[maxn];
int s[maxn];
int t[maxn];

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        s[p[i]] = i;
    }for (int i = 1; i <= n; i++) {
        cin >> q[i];
        t[q[i]] = i;
    }
    int k1 = s[1], k2 = t[1];
    if (k1 > k2) swap(k1, k2);
    if (1 <= k1 - 1) {
        ans += k1 * (k1 - 1) / 2;
    }
    if (k2 + 1 <= n) {
        ans += (n - k2 + 1) * (n - k2) / 2;
    }
    if (k1 < k2) {
        ans += (k2 - k1 - 1) * (k2 - k1) / 2;
    }
    int l = k1, r = k2;
    for (int m = 2; m <= n; m++) {
        k1 = s[m], k2 = t[m];
        if (k1 > k2) swap(k1, k2);
        if (l <= k1 && k1 <= r || l <= k2 && k2 <= r) {
            l = min(l, k1);
            r = max(r, k2);
            continue;
        }
        if (k1 < l && k2 < l) {
            ans += (n - r + 1) * (l - k2);
        }
        if (k1 > r && k2 > r) {
            ans += (k1 - r) * l;
        }
        if (k1 < l && k2 > r) {
            ans += (l - k1) * (k2 - r);
        }
        l = min(l, k1);
        r = max(r, k2);
    }
    cout << ans+1;
    return 0;
}
```
核心实现思想：先记录每个数在两个排列中的位置，对于 $\operatorname{MEX}=1$ 的情况单独计算，然后枚举 $\operatorname{MEX}$ 从 $2$ 到 $n$，根据当前 $\operatorname{MEX}$ 在两个排列中的位置，分类讨论满足条件的区间左右端点取值范围，计算方案数并更新左右边界，最后加上 $\operatorname{MEX}=n + 1$ 的情况。

- **作者：lizhous（4星）**
    - **关键亮点**：思路清晰，对枚举 $\operatorname{MEX}$ 的过程分析详细，代码结构清晰，有辅助函数，提高了代码的可读性。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
int T,n,a[200001],b[200001],na[200001],nb[200001],l,r,ans;
int get(int l,int r) //左右端点在[l,r]内的区间计数
{
    if(l>r) return 0;
    return (r-l+2)*(r-l+1)/2;
}
int geter(int l1,int r1,int l2,int r2) //左右端点的取值范围，求出满足条件的区间个数
{
    return (r1-l1+1)*(r2-l2+1);
}
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        na[a[i]]=i; //桶存，方便后续处理
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&b[i]);
        nb[b[i]]=i;
    }
    ans=0;
    //MEX为1的区间计数
    ans+=get(1,min(na[1],nb[1])-1);
    ans+=get(min(na[1],nb[1])+1,max(na[1],nb[1])-1);
    ans+=get(max(na[1],nb[1])+1,n);
    l=min(na[1],nb[1]);//必须包含的区间处理
    r=max(na[1],nb[1]);
    for(int i=2;i<=n;i++)
    {
        int ll=min(na[i],nb[i]),rr=max(na[i],nb[i]);
        if(r<ll) //包含区间在左边点的左边
        {
            ans+=geter(1,l,r,ll-1);
        }
        if(l>ll&&r<rr) //包含区间在中间
        {
            ans+=geter(ll+1,l,r,rr-1);
        }
        if(l>rr) //包含区间在右边
        {
            ans+=geter(rr+1,l,r,n);
        }
        l=min(l,ll);
        r=max(r,rr);
    }
    cout<<ans+1; //要加上MEX为n+1的情况
}
```
核心实现思想：同样先记录每个数的位置，对于 $\operatorname{MEX}=1$ 的情况计算满足条件的区间数，然后枚举 $\operatorname{MEX}$ 从 $2$ 到 $n$，根据当前 $\operatorname{MEX}$ 位置和之前必须包含的区间位置关系，计算满足条件的区间数并更新边界，最后加上 $\operatorname{MEX}=n + 1$ 的情况。

- **作者：寻逍遥2006（4星）**
    - **关键亮点**：思路简洁明了，代码简洁，通过简单的分类讨论实现了枚举 $\operatorname{MEX}$ 的过程。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int Qread()
{
    int x=0;bool f=false;char ch=getchar();
    while(ch<'0'||ch>'9') f|=('-'==ch),ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
    return f?-x:x; 
}
int n,l,r,L,R;
long long ans;
int p[200010],q[200010];
int locp[200010],locq[200010];
int main()
{
    n=Qread();
    for(int i=1;i<=n;i++) locp[p[i]=Qread()]=i;
    for(int i=1;i<=n;i++) locq[q[i]=Qread()]=i;
    l=min(locp[1],locq[1]),r=max(locp[1],locq[1]);
    ans=1ll*l*(l-1)/2+1ll*(n-r)*(n-r+1)/2+1ll*(r-l-1)*(r-l)/2;
    for(int i=2;i<=n;i++)
    {
        L=min(locp[i],locq[i]),R=max(locp[i],locq[i]);
        if(L<l&&r<R) ans+=1ll*(l-L)*(R-r);
        else if(R<l) ans+=1ll*(l-R)*(n-r+1);
        else if(r<L) ans+=1ll*l*(L-r);
        l=min(l,L),r=max(r,R);
    }
    ans+=1;
    printf("%lld\n",ans);
    return 0;
}
```
核心实现思想：先记录每个数的位置，计算 $\operatorname{MEX}=1$ 时的区间数，然后枚举 $\operatorname{MEX}$ 从 $2$ 到 $n$，根据当前 $\operatorname{MEX}$ 位置和之前边界的关系分类计算满足条件的区间数并更新边界，最后加上 $\operatorname{MEX}=n + 1$ 的情况。

### 最优关键思路或技巧
- **枚举 $\operatorname{MEX}$**：通过枚举 $\operatorname{MEX}$ 值，将复杂的 $\operatorname{MEX}$ 计算问题转化为确定区间左右端点取值范围的问题，降低了问题的复杂度。
- **记录位置**：使用数组记录每个数在两个排列中的位置，方便后续根据 $\operatorname{MEX}$ 的位置进行分类讨论。
- **分类讨论**：根据当前 $\operatorname{MEX}$ 的位置和之前必须包含的区间位置关系，进行分类讨论，确定满足条件的区间左右端点取值范围，进而计算方案数。

### 拓展思路
同类型题目可能会改变排列的条件，或者改变 $\operatorname{MEX}$ 的计算规则，例如给定的不是排列而是普通数组，或者 $\operatorname{MEX}$ 计算的是负数或其他范围的数。类似算法套路可以应用于其他需要枚举某个值并根据条件确定区间的问题，如枚举区间长度、枚举某个元素的出现次数等。

### 洛谷推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：本题需要枚举区间端点，计算区间和并找出最大值，与本题枚举区间的思路有相似之处。
- [P2004 领地选择](https://www.luogu.com.cn/problem/P2004)：需要枚举矩形的左上角和右下角，计算矩形内元素的和，与本题确定区间范围的思路类似。
- [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)：同样是枚举矩形的边界，计算矩形内元素的加权和，和本题枚举区间并计算相关值的思路相符。

### 个人心得摘录与总结
- **TernaryTree**：“阳间 CF 赛时切 D 祭”，表达了在比赛中做出题目后的喜悦和成就感。
- **Feyn**：“考场上脑瘫了交了 N 发”，体现了在考场上可能会因为紧张或思路不清晰而多次提交错误代码，提醒我们在考试中要保持冷静，理清思路。
- **_Fatalis_**：“最近的状态真的需要调整。做题的感觉需要重新找回，希望今年能不再遗憾 归终。2 月份，6 月中考，10 - 11 月 CSP。两年的遗憾，我理应拿回属于我的自豪。”，表达了对自己状态的反思和对未来考试的期望，提醒我们要关注自己的学习状态，不断调整和提高。 

---
处理用时：68.20秒