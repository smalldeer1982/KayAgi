# [POI 2012] STU-Well

## 题目描述

Byteasar 出发沿着穿越 Byteotian 沙漠的干河旅行。不幸的是，干河已经干涸，Byteasar 的水也用完了。他唯一的希望是在干涸的河床上挖一个足够深的井。意识到情况的严重性，Byteasar 决定在实际开始挖掘之前仔细计划一切。危险在于他可能在到达水位之前耗尽体力——在这种情况下，他不太可能生存下来。他设法确定了水位的深度。他也知道自己能挖多少而不至于失去体力。他唯一担心的是可能发生的山体滑坡，这可能会活埋他。他通过卫星电话向你发送了一张河床的地形图。当然，他请求你帮助他确定应该在哪里挖掘，以便在不耗尽体力的情况下到达水源，同时尽可能保持挖掘坡度的平缓。他在等待你的建议！

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
16 15
8 7 6 5 5 5 5 5 6 6 7 8 9 7 5 5```

### 输出

```
1 2```

# 题解

## 作者：kczno1 (赞：11)

题意应为使得max{|a(i)-a(i+1)|}最小。
二分答案del，

之后从后往前扫一遍，如果a(i)-a(i+1)>del就把a(i)减掉;

再从前往后扫一遍，如果a(i)-a(i-1)>del就把a(i)减掉。

现在考虑如何使得存在a(k)=0。

假如枚举k,那么使a(k)=0后，

相当于在(k,0)往左划了一条斜率=-del的直线，直线上方的都要被减掉。

肯定是从a(k-1)开始往前往后影响，影响到a(l);

同时往右划了一条斜率=del的直线，直线上方的都要被减掉。

肯定也是从a(k+1)开始持续到一个a(r)。

如果让这条直线单调往右，那么l,r也是单调往右的。

维护这个l,r即可。

```cpp
#include<cstdio>

#define ll long long
#define N 1000100
int a0[N],a[N];ll s[N]; 
int n,i;ll m;

int ok(ll del)
{
    ll now=m,x;
    for (i=1;i<=n;++i) a[i]=a0[i];a[n+1]=-1;
    for (i=n-1;i;--i) 
    if ((x=a[i]-a[i+1]-del)>0)
    {
        a[i]-=x;now-=x;
    }
    if (now<0) return 0;
    for (i=2;i<=n;++i)
    if ((x=a[i]-a[i-1]-del)>0)
    {
        a[i]-=x;now-=x;
    }
    if (now<0) return 0;
    for (i=1;i<=n;++i) s[i]=s[i-1]+a[i];
    ll l=1,r=1;
    for (i=1;i<=n;++i)
    {
        x=a[i];a[i]=0;
        while (a[l]<del*(i-l)) ++l;
        while (a[r+1]>=del*(r+1-i)) ++r;
        a[i]=x;
        if (s[r]-s[l-1]-now<=(del*((i-l)*(i-l+1)+(r-i)*(r-i+1)>>1))) return i;    
    }
    return 0;
}

int main()
{
    freopen("1.in","r",stdin);
    scanf("%d%lld",&n,&m);
    for (i=1;i<=n;++i) scanf("%d",a0+i);
    if (ok(0)) {printf("%d %d",ok(0),0);return 0;}
    int l=0,r=1e9+1;
    while (l+1!=r)//l is false r is ok
    {
        int mid=l+r>>1;
        if (ok(mid)) r=mid;
        else l=mid;
    }
    printf("%d %d",ok(r),r);
}
```

---

## 作者：Alex_Wei (赞：6)

> *[P3534 [POI2012]STU-Well](https://www.luogu.com.cn/problem/P3534)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

二分答案。对于固定的 $z$，首先考虑没有 $x_k=0$ 的限制。

因为 $|x_i-x_{i+1}|\leq z$ 可写成 $x_i\leq x_{i-1}+z\ (2\leq i\leq n)$ 以及 $x_i\leq x_{i+1}+z\ (1\leq i<n)$ ，故我们只需从左往右扫一遍 $x_i\gets \min(x_i,x_{i-1}+z)$，从右往左扫一遍 $x_i\gets\min(x_i,x_{i+1}+z)$，然后求出原 $x_i$ 与新 $x'_i$ 之间的差 $d=\sum_{i=1}^n x_i-x'_i$。

正确性（分为合法性与最小性）证明：

- 合法性：因为 $x_{i-1}+z$ 操作进行完毕后满足 $x_i\leq x_{i-1}+z$，而 $x_{i+1}+z$ 操作后满足 $x_i\leq x_{i+1}+z$，**且不会破环 $x_i\leq x_{i-1}+z$ 的性质（因为 $z$ 非负）**，得证。
- 最小性：对于 $x_{i-1}+z$ 操作，若 $x_i> x_{i-1}+z$，我们不得不用 $x_i-x_{i-1}-z$ 的代价填平 $i$ 这个位置，否则不满足条件。$x_{i+1}+z$ 同理。

接下来考虑 $x_k=0$ 的限制，显然还要用 $z\times |i-k|$ 更新 $x_i$，但我们没有足够的时间对每个 $k$ 都这样暴力计算。稍作转化，我们就是要找到所有这样的 $p$ 使得 $x_p > z\times |k - p|$，然后将代价加上 $x_p - z\times |k - p|$。

考虑 $k$ 变为 $k+1$ 的过程，$k$ 左边的位置 $i$ 的 $z\times (k-i)$ 会增加，即限制放宽，那么第一个 $x_i > z\times (k-i)$ 的位置 $l$ 会向右移动。同理，对于 $k$ 右边的位置 $i$，**最后一个** $x_i > z\times (i-k)$ 的位置 $r$ 也会向右移动（因为限制变严格了）。

同时，我们知道 $l\sim r$ 的区间内所有位置都有 $x_i > z\times (k-i)$，以及区间外的位置都有 $x_i\leq z\times (k-i)$（否则会出现相邻两个数之差的绝对值大于 $z$ 的情况，因为我们是用斜率绝对值为 $k$ 的直线去切这个 “山峰”，而任意位置的斜率绝对值不超过 $k$，故切到的一定是一段区间），所以可以用前缀和与等差数列求和公式快速计算 $k$ 处的答案。时间复杂度 $\mathcal{O}(n\log x)$。

```cpp
const int N = 1e6 + 5;
ll m, s[N];
int n, k, l, r = 1e9, x[N], y[N];
int check(int d) {
	ll tot = 0; cpy(y, x, n + 1);
	for(int i = 2; i <= n; i++) cmin(y[i], y[i - 1] + d);
	for(int i = n - 1; i; i--) cmin(y[i], y[i + 1] + d);
	for(int i = 1; i <= n; i++) tot += x[i] - y[i], s[i] = s[i - 1] + y[i];
	for(ll i = 1, l = 1, r = 1; i <= n; i++) {
		while(l < i && y[l] <= 1ll * (i - l) * d) l++;
		while(r < n && y[r + 1] > 1ll * (r - i + 1) * d) r++;
		if(tot + s[r] - s[l - 1] - d * (((i - l) * (i - l + 1) / 2) + (r - i) * (r - i + 1) / 2) <= m) return i;
	} return 0;
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) x[i] = read();
	while(l < r) {
		int m = l + r >> 1, v = check(m);
		v ? (k = v, r = m) : l = m + 1;
	} cout << k << " " << l << endl;
	return flush(), 0;
}
```

---

## 作者：zjjws (赞：4)

[P3534 [POI2012]STU-Well](https://www.luogu.com.cn/problem/P3534)

题目大意：

一段区间，修改m次，每次单个-1

使（至少一个点变为0） && （所有相邻点的最大差值z最小）

---

求最大的最小值，就是显而易见的二分答案

那么怎么检验每个差值是否能达到呢？

首先我们可以先把问题简化，如果没有至少一个点变成零的条件如何维护相邻的差值

将高度反映到数轴上，是由若干个非严格的递增和递减区间构成的（不一定像图中是线段的形式，只是懒得画）
![](https://cdn.luogu.com.cn/upload/image_hosting/d5lx6sst.png)

那么只需要左右各跑一遍，分别维护递增区间和递减区间就行了
```cpp
for(int i=2;i<=n;i++)
if(a[i]-a[i-1]>z)
a[i]=a[i-1]+z;

for(int i=n-1;i>=1;i--)
if(a[i]-a[i+1]>z)
a[i]=a[i+1]+z;
```
（这里没写计算操作次数）

正确性：

先处理递增区间（先递减也是一样的）

递增区间和递减区间的相交处分别是“山顶”和“山谷”。对于“山谷”，我们是不可能去修改它的；对于“山顶”，一种情况是它仍然是山顶，不会对它下一个的递减区间造成负面影响

如果修改完以后“山顶”变成下一个点了

因为处理递增是从左往右的，所以也不会有问题，当前点和下一个点的差值也会在下一步被处理好，只不过这个递增区间长度增加，向右扩展了
![](https://cdn.luogu.com.cn/upload/image_hosting/t1pt8vu9.png)

---
在维护完之后，就需要寻找一个可以为零的点了

我们知道，因为有最大差值的存在，把一个点$ai$变成零以后，会影响左右点的高度（减小）。但是这个影响是有范围的，如果我们知道左边第一个和右边第一个不受影响的点，就可以把这一段受影响的区间先挖空，再从$i$开始左右每次增加z。利用前缀和+数学方法运算就可以$O(1)$算出所需要的操作次数

周所周知，求左边（or右边）第一个什么什么的就是单调栈的用处，并且这题的左右不受影响点确实是随$i$的递增而递增的(可以结合下面的公式思考这句话)

具体公式的话：

假设我们挖空的那个点为$i$，此时二分出来的最大差值为$z$

用数组$h$表示维护之后的各点高度

左右第一个不受影响点分别为$l,r$，

满足$(i-l)*z>=h(l),(r-i)*z>=h(r)$

$O(N)$求就好了

```
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAX=1e6+3;
LL s_a[MAX];
LL a[MAX];
LL l[MAX];
LL r[MAX];
LL add[MAX];
LL n,m;
LL nam;
inline bool cheak(LL mid)
{
	LL sum=m;
	for(int i=2;i<=n;i++)if(a[i]-a[i-1]>mid)sum-=a[i]-a[i-1]-mid,a[i]=a[i-1]+mid;
	for(int i=n-1;i>=1;i--)if(a[i]-a[i+1]>mid)sum-=a[i]-a[i+1]-mid,a[i]=a[i+1]+mid;
	if(sum<0)return false;
	add[0]=0;for(int i=1;i<=n;i++)add[i]=add[i-1]+a[i];;
	for(int i=1,j=1;i<=n;i++){for(;mid*(i-j)>a[j];j++);l[i]=j;}
	for(int i=n,j=n;i>=1;i--){for(;mid*(j-i)>a[j];j--);r[i]=j;}
	for(int i=1;i<=n;i++)
	{
		LL i_s=add[r[i]]-add[l[i]-1];
		i_s-=(i-l[i]+1)*((i-l[i])*mid)/2;
		i_s-=(r[i]-i+1)*((r[i]-i)*mid)/2;
		if(i_s<=sum){nam=i;return true;}
	}
	return false;
}
LL rin()
{
	LL s=0;
	char c=getchar();
	bool bj=false;
	for(;(c>'9'||c<'0')&&c!='-';c=getchar());
	if(c=='-')bj=true,c=getchar();
	for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
	if(bj)return -s;
	return s;
}
int main()
{
	int i,j;
	n=rin();m=rin();
	LL l=0,r=0;
	s_a[1]=rin();for(i=2;i<=n;i++)s_a[i]=rin(),r=max(r,s_a[i]);
	
	LL ans=0;
	LL ans_2=0;
	for(;l<=r;)
	{
		for(i=1;i<=n;i++)a[i]=s_a[i];
		LL mid=(l+r)>>1;
		if(cheak(mid))ans=mid,ans_2=nam,r=mid-1;
		else l=mid+1;
	}
	printf("%lld %lld",ans_2,ans);
	return 0;
}
```

---

## 作者：Richard_Whr (赞：2)

更自然的做法。

总体上还是二分，目标就是 check 相邻两项的绝对值 $\le x$ ，且某个位置为 $0$ 能否实现。

考虑 dp 解决这个问题，设 $f_{i,j}$ 表示第 $i$ 个数为 $j$ 的时候，最小的代价。

应该比较容易就列出转移：

$$f_{i,j} = \min\limits_{k=j-x}^{j+x}\{f_{i-1,k}+a_i-j\}$$。

看到这个 $k \in [j-x,j+x]$ 和整体加一次函数感觉像是凸优化（slope trick)。

考虑归纳证明一定是一段下凸的函数：

第一开始函数是 $x$ 轴正半轴，每次操作相当于：

先向左平移 $x$ 单位，然后把最小值延长为 $2\times x$ 个单位的横线，没有改变凸性。（注意一个细节是当函数长度不足 $x$ 的时候位移长度要取 $\min$）。 

然后将函数 $>a_i$ 的部分截去，没有改变凸性。

最后加了一个斜率为 $-1$，截距为 $a_i$ 的一次函数，没改变凸性。

因此一直是凸函数，证毕。

如何求答案？可以发现如果要求 $a_i=0$ 的话就是最左侧直线的截距，正着扫一遍倒着扫一遍拼合前后缀的答案。 

以上操作可以用最左侧的直线 $(kl,bl)$，最右侧的直线 $(kr,br)$ ，位移标记和截取标记 $[L,R]$，以及斜率变化集合 $\{(x,\Delta)\}$ 维护，具体实现可以看代码。

总复杂度 $O(n\log V)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=1e6+10,Inf=2e9;
typedef pair<int,int> PII;
int L,R;
int kl,kr,bl,br;
PII q[N];
int hh,tt;
int n,m,mx;
int a[N];
int f[N],g[N];

inline void Init()
{
	L=0,R=Inf;
	kl=kr=bl=br=0;
	hh=0,tt=-1;	
}

inline void shift(int d)
{
	int l=L;
	L=min(L+d,R);
	while(hh<=tt && q[hh].x<=L)
	{
		int x=q[hh].x,y=q[hh].y;hh++;
		bl-=(x-l)*y;
		kl-=y;
	}
	bl-=(L-l)*kl;
	br-=(L-l)*kr;
}

inline void Cut(int Lim)
{
	int r=R;
	R=min(R,Lim+L);
	while(hh<=tt && q[tt].x>=R) 
	{
		int x=q[tt].x,y=q[tt].y;tt--;
		br+=(x-L)*y;
		kr+=y;
	}
}

inline void extend(int d)
{
	if(kr)
	{
		q[++tt]={R,kr};
		br-=(R-L)*kr;
		kr=0;
	}
	R+=d;
	Cut(Inf);
}


inline void Add(int A)
{
	bl+=A,br+=A;
	kl++,kr++;
}

int check(int x)
{
	Init();
	for(int i=1;i<=n;i++)
	{
		int sz=R-L;
		shift(x);
		extend(min(sz,x)+x);
		Cut(a[i]);
		Add(a[i]);
		f[i]=bl;
	}
	Init();
	for(int i=n;i>=1;i--)
	{
		int sz=R-L;
		shift(x);
		extend(min(sz,x)+x);
		Cut(a[i]);
		Add(a[i]);
		g[i]=bl;
	}
	for(int i=1;i<=n;i++)
	{
		int cost=f[i]+g[i]-a[i];
		if(cost<=m) return i;
	}
	return -1;
} 

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],mx=max(mx,a[i]);
	
	int l=0,r=mx,ans=-1,p=-1;
	while(l<=r)
	{
		int mid=(l+r)/2;
		int x=check(mid);
		if(x!=-1) ans=mid,p=x,r=mid-1;
		else l=mid+1;
	}
	
	cout<<p<<" "<<ans<<"\n";
	return 0;
}
```

---

## 作者：傅思维666 (赞：2)

## 题解：

首先看到最大值最小就考虑二分答案。

直接二分的就是最大斜率最小值。我们进行扫描，如果碰到比当前二分到的答案大的就把它变小，然后递减操作次数。因为是绝对值，所以要正反扫两遍。

之后我们考虑如何挑一个k使之得0。

我们发现，对于我们目前二分到的答案，如果有一个位置$(k,0)$，那么其可行区间一定是过这个点，斜率为二分到的答案的下面的部分。如果有点在上面，肯定是不符合题意的，要减下来。我们又发现，这样的点一定是连续的分布在当前枚举到的K的两侧。所以可以用一个类似于滑动窗口的东西来维护这里。碰到第一个符合题意的就跳出。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=1e6+6;
int n,m,ans;
int a[maxn],b[maxn],sum[maxn];
int check(int x)
{
    int tot=0;
    for(int i=1;i<=n;i++)
        b[i]=a[i];
    b[n+1]=-1;
    for(int i=2;i<=n;i++)
        if(b[i]-b[i-1]>x)
        {
            tot+=(b[i]-b[i-1]-x);
            b[i]=b[i-1]+x;
        }
    if(tot>m)
        return 0;
    for(int i=n-1;i>=1;i--)
        if(b[i]-b[i+1]>x)
        {
            tot+=(b[i]-b[i+1]-x);
            b[i]=b[i+1]+x;
        }
    if(tot>m)
        return 0;
    for(int i=1;i<=n;i++)
        sum[i]=sum[i-1]+b[i];
    int l=1,r=1;
    for(int i=1;i<=n;i++)
    {
        int tmp=b[i];
        b[i]=0;
        while(b[l]<x*(i-l))
            l++;
        while(b[r+1]>=x*(r-i+1))
            r++;
        b[i]=tmp;
        int all=(1ll*x*((1ll*(i-l)*(i-l+1)+1ll*(r-i)*(r-i+1))/2));
        if(m-tot>=(sum[r]-sum[l-1])-all)
            return i;
    }
    return 0;
}
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    if(check(0))
    {
        printf("%lld %lld\n",check(0),0);
        return 0;
    }
    int l=0,r=1e9;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(check(mid))
            r=mid;
        else
            l=mid+1;
    }
    printf("%lld %lld\n",check(r),r);
    return 0;
}
```



---

