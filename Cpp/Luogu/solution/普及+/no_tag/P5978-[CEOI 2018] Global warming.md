# [CEOI 2018] Global warming

## 题目描述

给定 $n$，你可以将任意 $a_l$ 至 $a_r$($1\le l\le r\le n$)每一个元素加上一个 $d$($-x\le d\le x$), 求 $a$ 数组的最大严格上升子序列长度。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 2\times 10^5$。

## 样例 #1

### 输入

```
8 10
7 3 5 12 2 7 3 4```

### 输出

```
5```

# 题解

## 作者：lnwhl (赞：6)

目前的[最优解](https://www.luogu.com.cn/record/list?pid=P5978&orderBy=1&status=&page=1)。
## Description
给定长度为 $n$ 的数组 $a$ ，你可以将任意一段区间 $[l,r]$ 中的每一个元素 $+d$，其中 $-x\le d\le x$，问一次操作后的最长上升子序列长度。
## Solution
如果将 $[l,r]$ 区间内的元素都减小，可以增加 $[l,r]$ 与 $[r+1,n]$ 连接的 LIS 长度。但这有可能减小 $[l,r]$ 与 $[1,l-1]$ 这段的 LIS，所以我们可以贪心的想到，**对于 $d<0$ 的情况，选择 $[1,r]$ 区间一定会比 $[l,r]$ 区间更优**。

对于 $d>0$ 的情况也同理。因为区间内相对大小不变，所以不难发现将 $[i+1,n]$ 加一个值的效果和 $[1,i]$ 区间减一个值的效果是相同的，所以只需要考虑 $d<0$ 的情况。

我们进一步分析，**可以发现将 $[1,i]$ 区间减的值越大一定更优**。所以原问题就变成了**求 $[1,i]$ 区间内的元素都减去 $x$ 后，最长上升子序列的长度最大为多少**。

暴力修改 + LIS 的复杂度是 $O(n^2\log n)$ 的，需要优化。考虑到修改过后区间内部相对大小不变，可以预先求出 $[1,i]$ 区间以 $a_i$ 结尾的 LIS 长度，为 $L_i$，设修改过后 $[i,n]$ 区间以 $a_i$ 开头的 LIS 长度为 $R_i$，答案即为 $\max\limits_{i=1}^nL_i+R_i-1$。复杂度是 $O(n\log n)$ 的，轻松最优解。

当然，你也可以离散化后用树状数组求最大值，复杂度不变，只是代码复杂一些，欢迎读者思考。
## Code
```cpp
#include <bits/stdc++.h>
#define Rint register int
using namespace std;
const int N=2e5+5;
int n,x,a[N],lis[N],L[N],R[N],ans;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int main()
{
	n=read(),x=read();
	for(Rint i=1;i<=n;++i)a[i]=read();
	memset(lis,0x7f,sizeof(lis));
	for(Rint i=1;i<=n;++i)
	{
		int j=lower_bound(lis,lis+n,a[i])-lis;
		lis[j]=a[i];L[i]=j+1;ans=max(ans,L[i]);
	}
	memset(lis,0x7f,sizeof(lis));
	for(Rint i=n;i>=1;--i)
	{
		int j=lower_bound(lis,lis+n,-a[i]+x)-lis;
		int jj=lower_bound(lis,lis+n,-a[i])-lis;
		lis[jj]=-a[i];ans=max(ans,L[i]+j);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Hoks (赞：3)

## 前言
[题目链接](https://www.luogu.com.cn/problem/P5978)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-p5978)内食用更佳。

~~模拟赛题+1。~~
## 思路分析
首先这题求最长上升子序列，首先我们想到了[导弹拦截](https://www.luogu.com.cn/problem/P1020)这道题。那我们首先得出如果处理最长上升子序列的话效率便是 $O(n\log n)$。

接着我们来考虑修改问题。

如果我们修改的是 $l\sim r$ 的区间都加上一个正数 $d$，那这肯定不如给 $l\sim n$ 的区间都加上一个正数 $d$。（可以视作下面的我也顺便修改了，用不着就一样，用的着就更大。）

而对于 $l\sim r$ 的区间都加上一个负数 $d$，同理那这肯定不如给 $l\sim n$ 的区间都加上一个负数 $d$ 了。

又观察得到 $1\sim i$ 这个区间全部减去正数 $d$ 与 $i+1\sim n$ 这个区间全部加上正数 $d$ 的效果是一样的。所以我们只需要考虑减去正数 $d$ 的 $1\sim i$ 的区间情况。

这时暴力修改计算的时间复杂度便是 $O(n^2\log n)$。

考虑优化，可以先预处理出 $1\sim i$ 以 $a_i$ 结尾的最长上升子序列长度，然后再计算出更改后的 $i\sim n$ 的最长上升子序列的长度，要求的答案便是前后拼起来的序列的两个值之和去掉 $i$ 这个位置重复的最大值。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x;
int a[200010],f[200010],l[200010];
int ans;
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
signed main()
{
	n=read(),x=read();
	for(int i=1;i<=n;++i)a[i]=read();
	memset(f,0x7f,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		int pos=lower_bound(f,f+n,a[i])-f;
		f[pos]=a[i];l[i]=pos+1;ans=max(ans,l[i]);
	}
	memset(f,0x7f,sizeof(f));
	for(int i=n;i>=1;i--)
	{
		int pos=lower_bound(f,f+n,-a[i]+x)-f,poss=lower_bound(f,f+n,-a[i])-f;
		f[poss]=-a[i];ans=max(ans,l[i]+pos);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：ETHANK (赞：3)

# P5978 [CEOI2018]Global warming 题解

题意：给定长度为 $n$ 的数组 $a$ ，你可以将任意一段区间 $[l,r]$ 中的每一个元素 $+d$ ，其中 $-x\le d\le x$ ，问一次操作后的最长上升子序列长度。

数据范围：$1\le n\le 2\times 10^5$。

思路：如果把 $[l,r]$ 区间的数变小，可能会增加到这一段区间和后面 $[r+1,n]$ 接上的 LCS 长度，但同时可能减少 $[1,r]$ 这段的 LCS 长度。不难发现，对于同样的 $d<0$ ，操作 $[1,r]$ 这个区间一定比操作 $[l,r]$ 区间更优。

同时，由于操作过后元素的相对大小不变， $[1,r]$ 减小 $d$ 和 $[r+1,n]$ 增加 $d$ 这两个操作本质上是一样的。因为前缀中元素的相对大小不变，为了 LCS 更长，显然 $d=x$ 时最优。于是题目就转化成了：考虑对前缀 $[1,r]$ 中的元素 $-x$ ，问操作后最长的 LCS 长度。暴力+ LCS 可以做到 $O(n^2\log n)$ ，但这不是我们想要的。

操作了一段前缀并不会影响这段前缀内部的 LCS ，于是我们可以求出$[1,i]$ 这段前缀以 $a_i$ 为终点的 LCS 长度，记为 $L_i$ 。设 $R_i$ 为在 $[1,i]$ 区间修改过后，以 $a_i$ 为起点的 LCS ，那么答案就是两个 LCS 的合并：

$$\max_{i=1}^n L_i+R_i-1$$

时间复杂度：$O(n\log n)$。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=2e5+5;
int n,x,a[N],lis[N],L[N],R[N],ans;
int main(){
    n=read(),x=read();
    rep(i,1,n)a[i]=read();
    memset(lis,0x3f,sizeof(lis));
    rep(i,1,n){//计算[1,i]的LIS
        int j=lower_bound(lis,lis+n,a[i])-lis;
        lis[j]=a[i];
        L[i]=j+1;
        ans=max(ans,L[i]);
    }
    memset(lis,0x3f,sizeof(lis));
    per(i,n,1){//计算后缀的下降子序列=以i为起点的上升子序列
        int j=lower_bound(lis,lis+n,-a[i]+x)-lis;
        int jj=lower_bound(lis,lis+n,-a[i])-lis;
        lis[jj]=-a[i];
        ans=max(ans,L[i]+j);
    }
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：licn (赞：3)

这是一道 DP 题，我们很容易想到暴力递推的做法：有两个状态分别用 $0$ 和 $1$ 表示，$0$ 代表不加 $x$,$1$ 代表加 $x$。

状态转移方程就是:当 $a_j<a_i$ 时：$f_{i,k}=\max(f_{i,k},f_{j,k}+1)$ 和当 $k=0$ 且 $a_j<a_i+x$ 时：$f_{i,k}=\max(f_{i,k},f_{j,k+1}+1)$。复杂度为 $O(n^2)$，肯定超时，先看暴力代码。

## 暴力代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,d,a[N],f[N][2],ans;
int main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		f[i][0]=1,f[i][1]=1;
		for(int j=1;j<i;j++)
		{
			for(int k=0;k<=1;k++)
			{
				if(a[i]>a[j])f[i][k]=max(f[i][k],f[j][k]+1);
				else if(a[i]+d>a[j]&&k==0)f[i][k]=max(f[i][k],f[j][k+1]+1);
			}
		}
		ans=max(f[i][0],max(f[i][1],ans));
	}
	cout<<ans;
	return 0;
}
```
你可以拿到 $28$ 分，显然不是正确的做法。

___
___
我们再来分析题意，我们先考虑 $d>0$ 时：$l<r<n$ 那么显然 $(l,n)$ 要优于 $(l,r)$。同理，当 $d<0$ 时：$(1,r)$ 要优于 $(l,r)$。通过暴力枚举 $r$ 的值，复杂度为 $O(n^2\log n)$ 显然不行，我们需要对其进行预处理。

我们分别枚举 $r$ 的值，通过二分求出以 $a_r$ 为结尾时的最长上升子序和以 $a_r$ 为开头的最长上升子序。当然要使用一个容器并用二分找答案。

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,d,a[N],f[N],f2[N],num,num2,p[N],p2[N],ans;
int main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		if(a[i]>f[num])f[++num]=a[i],p[i]=num;
		else
		{
			p[i]=lower_bound(f+1,f+1+num,a[i])-f;
			f[p[i]]=a[i];
		}
	}
	f2[0]=1e9;
	for(int i=n;i>0;i--)
	{
		p2[i]=lower_bound(f2+1,f2+1+num2,a[i]-d,greater<int>())-f2;
		if(a[i]<f2[num2])f2[++num2]=a[i],p2[i]=num2;
		else *lower_bound(f2+1,f2+1+num2,a[i],greater<int>())=a[i];
	}
	for(int i=1;i<=n;i++)ans=max(ans,p[i]+p2[i]-1);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：DengDuck (赞：1)

搬到了校内当打卡题被辱骂素质低下呜呜呜。

显然，如果我修改了区间 $[l,r]$，那么全局的 LIS 应该由三部分组成：

![](https://cdn.luogu.com.cn/upload/image_hosting/t3s9fky8.png)

上图中表示了答案 LIS 的组成，黄色表示的是区间减一个值的情况，蓝色表示的是区间加一个值的情况。

直接统计似乎很麻烦，我们观察两种情况能否转化:

![](https://cdn.luogu.com.cn/upload/image_hosting/qglloy1w.png)

由上图（注意箭头表示数值的增减）可以知道：

- 当区间是减一个值的时候，让整个前缀一起减去这个值一定不劣。
- 当区间是加一个值的时候，让整个后缀一起加去这个值一定不劣。显然这也等价于让前缀减去一个值。

所以我们只需要考虑让一个前缀减去一个值即可，由于我们希望两个 LIS 更好的对接，所以我们肯定是狠狠地减满 $x$。

因此可以直接树状数组，维护 $F_{i,0/1}$ 表示当前处理到第 $i$ 项，当前是否使用了减操作，情况下的 LIS。

代码很好写，我好像也就八百字节。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e5+5;
LL n,x,A[N],Ans;
struct BIT
{
	LL t[N*2];
	inline int LB(int x){return x&-x;}
	inline LL Qry(int x){LL Ans=0;for(int i=x;i;i-=LB(i))Ans=max(Ans,t[i]);return Ans;}
	inline void Upd(int x,LL k){for(int i=x;i<N*2;i+=LB(i))t[i]=max(t[i],k);}
}T0,T1;
vector<LL>Lsh;
inline int Gt(LL x)
{
	return lower_bound(Lsh.begin(),Lsh.end(),x)-Lsh.begin()+1;
}
#define pb push_back
int main()
{
	scanf("%lld%lld",&n,&x);
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]),Lsh.pb(A[i]),Lsh.pb(A[i]+x);
	sort(Lsh.begin(),Lsh.end());
	Lsh.erase(unique(Lsh.begin(),Lsh.end()),Lsh.end());
	for(int i=1;i<=n;i++)
	{
		int t0=Gt(A[i]),t1=Gt(A[i]+x);
		LL K0=T0.Qry(t0-1)+1,K1=max(T0.Qry(t1-1),T1.Qry(t0-1))+1;
		T0.Upd(t0,K0),T1.Upd(t0,K1);
		Ans=max({Ans,K0,K1});
	}
	printf("%lld",Ans);
}
```

---

## 作者：Add_Catalyst (赞：1)

# P5978 [CEOI2018] Global warming 题解

---

## 题意分析

给定长度为 $n$ 的数组 $\{ a_i \}$ 和一个值 $x$，可以将某一段连续区间加上一个值 $d \in[-x,x]$，求最大严格上升子序列长度。

---

## 思路分析

一个显然的贪心：要么把 $a_i,\forall i \in [1,r]$ 全部减去 $x$，要么把 $a_i,\forall i \in [l,n]$ 全部加上 $x$，再求最大严格上升子序列长度，因为这样肯定保证不劣于从中间加或减。

那么只需要正向来一次直接的不带修改的 DP，再从反向来一次带修改的 DP（加 $x$），把两次答案加一下再减一求最大值即可。

---

## CODE

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define tomax(a,b) ((a)=max((a),(b)))
#define tomin(a,b) ((a)=min((a),(b)))
#define RCL(a,b,c,d) memset((a),(b),sizeof(c)*(d))
#define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
#define DOR(i,a,b) for(register int i=(a);i>=(b);--i)
#define EDGE(g,i,u,x) for(register int (i)=(g).h[(u)],(x)=(g).v[(i)];(i);(i)=(g).nxt[(i)],(x)=(g).v[(i)])
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;
template<class T1,class T2>auto max(T1 a,T2 b){
	return a>b?a:b;
}
constexpr int N=2e5+10;
int n,X,ans;
int a[N],f[N],h[N];
signed main(){
	cin>>n>>X;
	FOR(i,1,n)cin>>a[i];
	RCL(h+1,INF,int,n);
	FOR(i,1,n)h[f[i]=lower_bound(h+1,h+n+1,a[i])-h]=a[i],tomax(ans,f[i]);
	RCL(h+1,INF,int,n);
	DOR(i,n,1)tomax(ans,f[i]+(lower_bound(h+1,h+n+1,-a[i]+X)-h-1)),h[lower_bound(h+1,h+n+1,-a[i])-h]=-a[i];
	cout<<ans<<endl;
	return 0;
}
```

---

---

## 作者：xuyunao (赞：0)

# P5978 [CEOI 2018] Global warming 题解

[题目传送门](https://www.luogu.com.cn/problem/P5978)

考虑对于一个区间加上或减去一个正整数会对整个序列的 LIS 产生怎样的影响。

假设我们对于区间 $[l,r]$ 减去一个正整数，一个显然的结论是，区间 $[l,r]$ 对 $[r + 1,n]$ 造成的贡献会增加（或不变），而 $[1,l - 1]$ 对 $[l,r]$ 造成的贡献会减少。

因此如果想要对一个区间减少一个正整数值 $x$，我们希望尽量将 $l$ 向前移动，因此如果选择对一个区间减去一个正整数，那么选择 $[1,r]$ 一定是相对于 $[l,r]$ 不劣的。

我们再来考虑对区间进行加法，使用同样的办法分析，不难发现，对于一个区间 $[l,r]$ 加上 $x$ 和对区间 $[1,l -  1]$ 减去 $x$ 是等价的，因此我们可以简化题意，也就变成了，我们可以对区间 $[l,r]$ 减去一个值 $x$，求序列最长上升子序列长度。

还有一个需要分析的点是，减去的正整数值 $x$ 应该更大还是更小，不难发现，$x$ 的值更大显然是更优的，因此相当于我们需要对于一个 $i$，将区间 $[1,i]$ 全部减 $x$，随后求序列最长上升子序列长度。

我们考虑如何去做这件事情，暴力修改并求 LIS 的时间复杂度是 $O(n^2 \log n)$ 的，因此我们要考虑如何优化。

发现对区间 $[1,i]$ 进行修改，对这段区间内的 LIS 是没有影响的，因此我们可以把序列拆为 $[1,i]$ 和 $[i + 1,n]$ 两部分，我们分别求出上升子序列长度，随后合并更新答案即可，时间复杂度 $O(n \log n)$。

贴代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn = 2e5 + 10;

int a[maxn];
int f[maxn],l[maxn];

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int ans = 0;
    memset(f,0x3f,sizeof(f));
    int n,x;
	cin >> n >> x;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n;i++)
	{
		int nowx = lower_bound(f,f + n,a[i]) - f;
		f[nowx] = a[i];
        l[i] = nowx + 1;
        ans = max(ans,l[i]);
	}
	memset(f,0x3f,sizeof(f));
	for(int i = n;i >= 1;i--)
	{
		int nowx = lower_bound(f,f + n,-a[i] + x) - f;
        int nowl = lower_bound(f,f + n,-a[i]) - f;
		f[nowl] = -a[i];
        ans = max(ans,l[i] + nowx);
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：reductt (赞：0)

我们考虑先考虑 $d \geq 0$ 的情况，显然序列就被我们分成了 $[1,l-1],[l,r],[r+1,n]$ 三个区间，如果我们对 $[l,r]$ 加上 $d$，那么对于 $[r+1,n]$ 也加上 $d$ 显然是不会更劣的，就相当于我们直接对一段后缀 $[l,n]$ 加上 $d$，然后又会发现，把 $d$ 加满对于 $[1,l-1],[l,n]$ 肯定更容易满足严格小于的性质，所以直接把 $d$ 加满。

而 $d \leq 0$ 呢？其实在相对关系上，前面的减去 $d$ 就相当于后面的加上 $d$，所以只用考虑 $d \geq 0$。

然后就可以枚举那个 $l$ 了，暴力修改，然后 $O(n \log n)$ 地求[最长上升子序列](https://www.luogu.com.cn/problem/B3637)。时间复杂度就是 $O(n^2 \log n)$。

然后再加上一个小的优化：我们可以对 $i$ 先求出再这个前缀里以 $a_i$ 结尾的最长子序列长度，然后再倒着做一遍，求出 $[i,n]$ 这个后缀里面以 $a_i$ 开头的最长子序列长度，答案就是这两个长度之和减一的最大值。时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define FOR_(i,a,b) for(int i=b;i>=a;i--)
#define fir first
#define sec second
#define pb push_back
namespace FastIO{
	int buf[100]={0},p=0;
	int rd(){
		int x=0,f=1;char c=getchar();
		while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
		while('0'<=c&&c<='9')x=x*10+c-'0',c=getchar();
		return x*f;
	}void write(int x,char c='#'){
		if(!x)putchar('0');
		else{
			if(x<0)putchar('-'),x*=-1;
			while(x)buf[++p]=x%10,x/=10;
			while(p)putchar(buf[p--]+'0');
		}
		if(c!='#')putchar(c);
	}
};
#define rd FastIO::rd
#define write FastIO::write
typedef __int128 u128;
typedef unsigned long long ull;
typedef pair<int,int> pii;
const int N=2e5+10;
int n,L,a[N],d[N],f[N],len,ans;
signed main(){
	n=rd(),L=rd();
	FOR(i,1,n)a[i]=rd();
	memset(d,0x3f,sizeof(d));
	FOR(i,1,n){
		int j=lower_bound(d,d+n,a[i])-d;
		d[j]=a[i],f[i]=j+1,ans=max(ans,f[i]);
	}
	memset(d,0x3f,sizeof(d));
	FOR_(i,1,n){
		//倒过来就相当于求严格下降子序列，相当于把a[i]取负后做严格上升子序列
		int j1=lower_bound(d,d+n,-a[i]+L)-d;//j1是找-a[i]+L能配对上什么长度
		int j2=lower_bound(d,d+n,-a[i])-d;//j2是正常的维护d数组
		d[j2]=-a[i],ans=max(ans,f[i]+j1);
	}
	write(ans,'\n');
	return 0;
}
```

---

## 作者：Infter (赞：0)

给一个比较显然的做法。

结论：一定是存在分界点 $k$ 使得让 $[k+1,n]$ 增加 $d$ 使得其是最优解。

考虑反证，若右端点不是 $n$ 那展到 $n$ 一定不劣。

我们回到最原始的转移方程。

$$
f_i=\max^{i-1}_{j=1} [a_j < a_i]f_j + 1
$$

我们拓展一下，令 $f_i$ 为尚未经过 $k$ 的最优解，$g_i$ 为经过了 $k$ 的最优解则易得：

$$
f_i=\max^{i-1}_{j=1} [a_j < a_i]f_j + 1
\\
g_i=\max \left\{ \max^{i-1}_{j=1} [a_j < a_i + d]f_j + 1, \max^{i-1}_{j=1} [a_j < a_i]g_j + 1\right\}
$$

我们使用权值树状数组维护之即可 AC，注意要离散化。

具体就是维护两个树状数组然后维护每一个小于 $a_i$ 的最大 $f_i$ 或 $g_i$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 5e5 + 5;

int n, x;
int a[MAXN];
struct Fenwick {
    int c[MAXN];

    int lowbit(int x) {
        return x & (-x);
    }

    int mx(int x) {
        int s = 0;
        for (int i = x; i >= 1; i -= lowbit(i)) {
            s = max(s, c[i]);
        }
        return s;
    }

    void upd(int x, int v) {
        for (int i = x; i <= n * 2; i += lowbit(i)) {
            c[i] = max(v, c[i]);
        }
    }
} fenwick1, fenwick2;

int b[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> x;
    for (int i = 1; i <= n; i++)
        cin >> a[i], b[i] = a[i];
    for (int i = 1; i <= n; i++)
        a[i + n] = a[i] + x, b[i + n] = a[i + n];
    sort(b + 1, b + 2 * n + 1);
    int tot = unique(b + 1, b + 2 * n + 1) - b - 1;
    for (int i = 1; i <= 2 * n; i++) {
        a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
        // cerr << a[i] << endl;
    }

    // cerr << "OK" << endl;

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int tmp = max(fenwick2.mx(a[i + n] - 1), fenwick1.mx(a[i + n] - 1)) + 1;
        fenwick2.upd(a[i + n], tmp);
        fenwick1.upd(a[i], fenwick1.mx(a[i] - 1) + 1);
        ans = max(ans, tmp);
        // cerr << tmp << endl;
    }
    cout << ans << endl;

    return 0;
}
```

---

