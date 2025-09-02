# [ABC023D] 射撃王

## 题目描述

高桥最近正在练习射击。
他参加了一个射击比赛，比赛内容是射击气球，让自己得到的分数尽量小。
气球从1到N依次编号。每个气球都有一个起始高度Hi，每个气球每秒可以升高的高度为Si。
高桥开始时可以先打掉一个气球，随后每一秒他可以射击一次。当他打掉气球后，所得的分数就是气球的高度。而最终的的得分就是这些分数中的一个最大值。
高桥想知道他自己能得到的尽量小的分数是多少，来判断自己是否真的是一个菜鸡。

## 样例 #1

### 输入

```
4
5 6
12 4
14 7
21 2```

### 输出

```
23```

## 样例 #2

### 输入

```
6
100 1
100 1
100 1
100 1
100 1
1 30```

### 输出

```
105```

# 题解

## 作者：liangbowen (赞：7)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT1330)

[更好的阅读体验？](https://www.luogu.com.cn/blog/liangbowen/solution-at1330)

这一题内部比赛时考到了，个人觉得是一道二分答案好题。

本题时间很宽松，导致 $O(n \log^2 n)$ 的代码可以跑过去。

但是，我内部比赛的时限是 $1$ 秒，这就导致需要 $O(n \log n)$ 的代码了。

## 思路一

显然是一道二分答案题目。

二分答案老套路，设 $f(x)$ 表示 $x$ 是否能作为答案，易得 $f(x)$ 单调递增。

所以，可以使用二分答案。

重点是 $\texttt{check()}$ 函数如何编写，我们可以使用**贪心**的思想。

对于每个气球，我们可以得出，打掉它的时间 $t_i$ 不得超过 $\left\lfloor\dfrac{x - h_i}{s_i}\right\rfloor$。 

我们可以对 $t$ 数组从小到大排序。

对于 $0 \le i < n$，我们从贪心的角度思考。如果 $i > t_i$，说明已经无法满足 $x$ 了。

如果全部都符合，说明 $t$ 数组的攻击方式就是一种合法的方案，那么 $x$ 这个答案是可行的。

$\texttt{check()}$ 函数代码如下。

```cpp
typedef long long LL;
int n, h[N], s[N];
LL t[N];
bool chk(LL x)
{
    for (int i = 1; i <= n; i++)
    {
        //如果时刻 0 打掉它都无法满足，立刻叉掉。
        if (x < h[i]) return false;
        t[i-1] = (x - h[i]) / s[i]; //为了方便处理，下标从 0 开始。
    }
    sort(t, t+n);
    for (int i = 0; i < n; i++)
        if (t[i] < i)
            return false;
    return true;
}
```

这里的时间复杂度是 $O(n \log n)$，加上二分的板子，需要 $O(n \log^2 n)$。

可以通过此题，但还可以优化吗？

## 思路二

时间复杂度瓶颈在于排序，如果想降到 $O(n)$，就需要使用 $O(n)$ 的排序算法。

你想到什么方法了？对，**桶排序**！

我们发现，当 $t_i \ge n$，说明任意时刻打掉它都是可行的，所以可以忽略不计。

这样，桶数组空间就符合了。

需要注意，$\texttt{check()}$ 开始前要初始化桶。

```cpp
bool chk(LL x)
{
    memset(box, 0, sizeof(box));
    for (int i = 1; i <= n; i++)
    {
        //在主程序外面保证了 x 大于等于 h[i]，就不需要担心了。
        LL t = (x - h[i]) / s[i];
        if (t < n) box[t]++;
    }
    int cur = 0;
    for (int i = 0; i < n; i++)
        for (int j = 1; j <= box[i]; j++)
        {
            if (i < cur) return false;
            cur++;
        }
    return true;
}
```

时间复杂度终于优化成了 $O(n)$。

最后，我们补全二分。

```cpp
LL FIND(LL l, LL r)
{
    //显然是模版，完全没改变。
    while (l < r)
    {
        LL mid = l + r >> 1;
        if (chk(mid)) r = mid;
        else l = mid+1;
    }
    return r;
}
int main()
{
    scanf("%d", &n);
    int maxn = -1;
    for (int i = 1; i <= n; i++) scanf("%d%d", &h[i], &s[i]), maxn = max(maxn, h[i]);
    //从 maxn 开始，保证了 chk() 函数不会出现 x < h[i] 的情况。
    //10^9 + 10^5 * 10^9 近似看成 10^15，毕竟大一点没坏处。
    printf("%lld\n", FIND(maxn, 1e15));
    return 0;
}
```

希望对大家有帮助！

---

## 作者：BqtMtsZDnlpsT (赞：3)

ABC 远古场的 D，atcoder 上的评分是 1843。

$\large\text{Solution}$

首先我们看到让分数最大值最小，于是就想到二分答案。

考虑二分最终获得的分数，即最后的最大高度。设当前二分到的答案为 $x$，在判断答案是否可行时，我们先算出每个气球在当前取值以内，至少需要在第几轮打下，设为 $p_i$，即在 $0\dots p_i$ 秒时把气球打下都符合当前条件。
具体的：$\left\{\begin{matrix}
H_i+p_i\times S_i\le x  \\ 
H_i+(p_i+1)\times S_i>x
\end{matrix}\right.$；解得 $\dfrac{x-H_i-S_i}{S_i}< p_i\le \dfrac{x-H_i}{S_i}$，因为 $p_i$ 为整数，所以 $p_i=\left \lfloor\dfrac{x-H_i}{S_i} \right \rfloor$。

算出 $p_i$ 后，我们贪心地选择（显然正确），即对于 $i (1\le i\le n)$ ，在第 $i$ 轮我们找 $p$ 中第 $i$ 大的放（未放过中最小的），如果放不了（$p$ 中第 $i$ 大的数 $>i$），那就不行，返回否。

以上过程可以开个桶，然后对桶前缀和维护，使任意时刻前缀和 $pre_i<i$（当然也可以直接找其他数据结构维护（如优先队列））。

由于题目中时间从 $0$ 开始，所以有一些细节注意一下。

代码：

```cpp
int n,q[100005];
struct N{
	int x,y;//x 表示 H_i，y 表示 S_i。
}a[100005];
bool check(int x){
	memset(q,0,sizeof q);//记得清桶
	for(int i=1;i<=n;i++){
		if(x-a[i].x<0)return 0;
		if((x-a[i].x)/a[i].y>n-1)continue;//如果 p 大于 n-1（n-1 是因为从 0 开始），那么在给定时间内一定放得下，不用考虑（也防止爆数组）
		q[(x-a[i].x)/a[i].y]++;//把每个 p 放入桶中
	}
	int s=0;
	for(int i=0;i<n;i++){
		s+=q[i];
		if(s>i+1)return 0; //如果前缀和>i+1，退出。（>i+1 是因为时间从 0 开始）
	}
	return 1;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=(N){read(),read()};
	int l=1,r=1e16,ans=-1;//其实 r 的理论最高值不是 1e16，是我太菜
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans<<'\n';
}
```

---

## 作者：Night_sea_64 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc023_d)

此题可以使用二分答案。

利用贪心的思想，一定要在 $0\sim n-1$ 秒的时候打气球，这样气球的高度也就是得分就会尽量小。同时在上述条件下，我们要把气球尽量靠后打，这样能给别的气球留出位置。

二分的时候，算出每个气球最晚要在几秒后打掉。设打掉时高度为 $x$，就是用 $\left\lfloor\dfrac{x-h_i}{s_i}\right\rfloor$。也就是用一共升高的高度除以每秒升高的高度再向下取整。

检验的时候我的方法是：用一个数组下标当作秒数，值当做算出来的秒数是这个的气球个数。但是这样会出现问题，因为可能算的秒数很大。因为要在 $0\sim n-1$ 秒时打气球，所以如果秒数 $>n-1$，那么就为 $n-1$。理论上来说把秒数 sort 一下也是可以的，但是这样慢。我就用的类似桶的方法。

我们从大到小遍历秒数，设一个 $cur$ 为当前已经有任务的秒数最小值。如果遍历到一个秒数 $x$，如果 $x<cur$，那么 $cur$ 直接变为 $x$。即把第 $x$ 秒用来打这个气球。后面遍历到的秒数也不可能比 $x$ 大了，所以 $>x$ 的没分配任务的秒数就不用考虑了。如果 $x≤cur$，那么 $cur$ 变为 $cur-1$，即，将 $cur-1$ 秒用来打这个气球。

最后如果 $cur<0$，表示秒数不够分了。否则方案就是可行的。蒟蒻语文不好，不懂的可以私信。

AC 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n;
long long h[100010],s[100010];
int cnt[100010];
bool chk(long long x)
{
	memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++)
    {
        if(x<h[i])return 0;
        cnt[min((long long)n-1,(x-h[i])/s[i])]++;
    }
    int cur=n+1;
    for(int i=n-1;i>=0;i--)
    {
    	if(!cnt[i])continue;
        cur=min(i-cnt[i]+1,cur-cnt[i]);
    }
    if(cur<0)return 0;
    return 1;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld%lld",&h[i],&s[i]);
    long long l=1,r=2e15,ans=0;
    while(l<=r)
    {
        long long m=(l+r)/2;
        if(chk(m))r=m-1,ans=m;
        else l=m+1;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

