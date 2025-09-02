# Two Platforms

## 题目描述

There are $ n $ points on a plane. The $ i $ -th point has coordinates $ (x_i, y_i) $ . You have two horizontal platforms, both of length $ k $ . Each platform can be placed anywhere on a plane but it should be placed horizontally (on the same $ y $ -coordinate) and have integer borders. If the left border of the platform is $ (x, y) $ then the right border is $ (x + k, y) $ and all points between borders (including borders) belong to the platform.

Note that platforms can share common points (overlap) and it is not necessary to place both platforms on the same $ y $ -coordinate.

When you place both platforms on a plane, all points start falling down decreasing their $ y $ -coordinate. If a point collides with some platform at some moment, the point stops and is saved. Points which never collide with any platform are lost.

Your task is to find the maximum number of points you can save if you place both platforms optimally.

You have to answer $ t $ independent test cases.

For better understanding, please read the Note section below to see a picture for the first test case.

## 说明/提示

The picture corresponding to the first test case of the example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1409E/939a53d6a5db677af525f764b29caa6d8ff8f49a.png)

Blue dots represent the points, red segments represent the platforms. One of the possible ways is to place the first platform between points $ (1, -1) $ and $ (2, -1) $ and the second one between points $ (4, 3) $ and $ (5, 3) $ . Vectors represent how the points will fall down. As you can see, the only point we can't save is the point $ (3, 7) $ so it falls down infinitely and will be lost. It can be proven that we can't achieve better answer here. Also note that the point $ (5, 3) $ doesn't fall at all because it is already on the platform.

## 样例 #1

### 输入

```
4
7 1
1 5 2 3 1 5 4
1 3 6 7 2 5 4
1 1
1000000000
1000000000
5 10
10 7 5 15 8
20 199 192 219 1904
10 10
15 19 8 17 20 10 9 2 10 19
12 13 6 17 1 14 7 9 19 3```

### 输出

```
6
1
5
10```

# 题解

## 作者：Karry5307 (赞：10)

### 题意

有 $n$ 个点，分别位于 $(x_i,y_i)$，求最多能用两个长度为 $k$ 的平台接住多少个点。

$\texttt{Data Range:}n\leq 2\times 10^5,k\leq 10^9$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13736456.html)

这是 Div.3 的 E 啊，为什么你们的写法都这么繁琐啊……

这题可以不用任何数据结构，甚至双指针都可以不用的啊，而且代码还短，为什么你们都不这样写啊

注意到 $y$ 坐标没什么卵用，所以只需要考虑 $x$ 坐标即可。

同时有一个结论：在某个最优的方案中两个平台的左端点一定与某一个点的 $x$ 坐标一样。

如果不一样的话我可以将平台向右移来达到一样，右移过程中可能还会接到一些新的点，肯定不比之前的答案要差。

把所有点的 $x$ 坐标从小到大排序，并且设 $f_i$ 表示某个平台左端点为 $x_i$ 的时候能接到多少个点。

我们考虑枚举最左边平台的左端点 $x_u$，这个时候在这个平台右边 $x$ 坐标最小不能接到的点一定是第 $u+f_u$ 个。此时第二个平台的最大贡献就是 $f$ 在 $u+f_u\sim n$ 的最大值。

容易看出 $f$ 可以直接指针扫就好了，而那个最大值其实就是后缀最大值，除去排序部分 $O(n)$ 完事。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll test,n,kk,r,res;
ll x[MAXN],f[MAXN],mx[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void solve()
{
	n=read(),kk=read();
	for(register int i=1;i<=n;i++)
	{
		x[i]=read();
	}
	for(register int i=1;i<=n;i++)
	{
		read();
	}
	sort(x+1,x+n+1),r=1,res=0,f[n+1]=mx[n+1]=0;
	for(register int i=1;i<=n;i++)
	{
		while(r<n&&x[r+1]-x[i]<=kk)
		{
			r++;
		}
		f[i]=r-i+1;
	}
	for(register int i=n;i;i--)
	{
		mx[i]=max(mx[i+1],f[i]);
	}
	for(register int i=1;i<=n;i++)
	{
		res=max(res,f[i]+mx[i+f[i]]);
	}
	printf("%d\n",res);
}
int main()
{
	test=read();
	for(register int i=0;i<test;i++)
	{
		solve();
	}
}
```

---

## 作者：MagicalSheep (赞：2)

# 分析

这是一道简单的线性 DP。

首先通过观察，可知点的纵坐标 $y$ 是不起作用的（我们可以将平台放置于纵坐标负无穷的位置）。通过对剩下的横坐标 $x$ 进行排序，我们在 $x$ 轴上得到了一系列有序的点，这些有序的点就是线性 DP 的处理线索。

让我们先将问题简化，只使用一个平台，求所能接住的点的最大数量。此时，可作为状态的信息有：`x 轴上有序的点`、`平台所能接住的点的数量`；而后者为题目所求，故状态设置呼之欲出——

$f(i)$ 表示处理到第 $i$ 个点时，平台所能接住的点的最大数量。

如何进行状态转移呢？想象一个平台在 $x$ 轴上从左往右滑动，总是试图接住第 $i$ 个点。让我们设这个已接住了第 $i$ 个点的平台此时一共接住了 `cnt` 个点，那么我们可以得到状态转移方程：

$f(i)=\max\{f(i-1),cnt\}$

现在我们需要放置两个平台，于是可以作为状态的信息增加了一个`已放置平台的个数`，于是本题的状态设置为——

$f(i,j)$ 表示处理到第 $i$ 个点，已放置了 $j$ 个平台时，所能接住的点的最大数量。（当然，$j$ 可以取 $0$ 和 $1$ 来分别代表放置了 $1$ 和 $2$ 个平台）

让我们设这个已接住了第 $i$ 个点的平台此时一共接住了 `cnt` 个点，接住的第一个点是 $x$ 轴上从左往右的第 `k` 个点，那么我们可以得到状态转移方程：

$\begin{cases}f(i,0)=\max\{f(i-1,0),cnt\}\\f(i,1)=\max\{f(i-1,1),f(k-1,0)+cnt\}\end{cases}$

如何求得 `cnt` 与 `k` 呢？可以参考滑动窗口的处理方式，从第一个点开始作为平台的左端点，由于长度确定，此时平台右端点也被确定，平台所能接住点的范围也就确定了。每加入一个点 $i$ ，如果在平台所能接住点的范围内，`cnt` 就加一；如果在范围外，就右移平台（左端点更改为下一个点），每右移一次 `cnt` 便减去一，直到点 $i$ 能够被平台接住。`k` 就是平台左端点。

# AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;

int t, n, k, x[MAXN], f[MAXN][2];

int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++)
            scanf("%d", &x[i]);
        for (int i = 1; i <= n; i++)
            scanf("%*d");
        sort(x + 1, x + 1 + n);
        for (int i = 1, j = 1, cnt = 1; i <= n; i++)
        {
            while (x[j] + k < x[i])
                ++j, --cnt;
            f[i][0] = max(f[i - 1][0], cnt);
            f[i][1] = max(f[i - 1][1], f[j - 1][0] + cnt);
            ++cnt;
        }
        printf("%d\n", f[n][1]);
    }
    return 0;
}
```

---

## 作者：_HwH_ (赞：2)

### [传送门](https://www.luogu.com.cn/problem/CF1409E)

## 分析
本题的两个平台能否接住水滴仅与水滴的横坐标有关，所以纵坐标可以直接扔掉不管


小贪心：对于每一个水珠，显然，两个平台必须不能重合（ 除非两个平台的总长度大于 $n$ ），而且，平台若想要最大化接住的水滴数，显然平台的一个端点必然要接到至少一个水珠


那么，本题的解法就显然易见了：我们可以直接枚举每一个水珠的横坐标，计算以该水珠为起点的一个平台长度内一共能接到多少水珠，最后输出两个互不重合的平台能接到的水珠总数的最大值



## Solution
显然，如果单纯的枚举与判断是至少要 $O(nk)$ 的，会 T 得飞起，所以，我们考虑优化


我们要做的是找到区间长度为 $k$ 内的数的个数，并不用计算数值大小，那么，我们可以进行离散化处理


对于每一段长度为 $k$ 的区间，我们可以用利用前缀和预处理得到

如：
```cpp
sort(a+1,a+n+1);
m=unique(a+1,a+n+1)-a-1;
for(int i=1;i<=n;i++)
{
      b[lower_bound(a+1,a+m+1,x[i])-a]++;//正常离散化
}
for(int i=1;i<=n;i++)
{
      pre[i]=pre[i-1]+b[i];//记录前缀和
}
for(int i=1;i<=n;i++)
{
      fg[i]=pre[upper_bound(a+i+1,a+m+1,a[i]+k)-a-1]-pre[i-1];
      //设平台起点横坐标为 i ，查找最后一个横坐标小于 i+k 的水珠的位置，利用前缀和做差快速求出该区间内一共有多少水珠
}
```

所以，我们可以再利用线段树，将另一块平台所能接到的最大水珠数量求出

```cpp
node *rot=New(1,n);
for(int i=1;i<=m;i++)
{
      ans=max(ans,rot->qry(upper_bound(a+i+1,a+m+1,a[i]+k)-a,m)+fg[i]);
      //这里的fg[i]表示了点第一块平台所能接到的最大水珠数量
      //用线段树查询该平台末端以后的区间内，另一块平台所能覆盖到的最大水珠数量
}
```

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<math.h>
#define ll long long
using namespace std;

const ll maxn=2e5+10;
ll t,n,m,k,ans;
ll x[maxn],y[maxn],a[maxn],b[maxn],pre[maxn],fg[maxn];

struct node
{
	ll v,l,r;
	node *ls,*rs;
	
	inline void pushup()
	{
		v=max(max(v,ls->v),rs->v);
	}
	inline bool inrange(ll L,ll R)
	{
		return (L<=l)&&(r<=R);
	}
	inline bool outofrange(ll L,ll R)
	{
		return (l>R)||(r<L);
	}
	inline ll qry(ll L,ll R)
	{
		if(inrange(L,R)) return v;
		if(outofrange(L,R)) return 0;
		
		return max(ls->qry(L,R),rs->qry(L,R));
	}
};

node Mem[maxn<<1];
node *pool=Mem;

inline node *New(ll L,ll R)
{
	node *u=pool++;
	u->l=L;
	u->r=R;
	
	if(L==R)
	{
		u->v=fg[L];
		u->ls=u->rs=NULL;
	}
	else
	{
		ll M=(L+R)>>1;
		u->ls=New(L,M);
		u->rs=New(M+1,R);
		u->pushup();
	}
	return u;
}

int main(void)
{
	scanf("%lld",&t);
	
	while(t--)
	{	
		ans=0;
		
		scanf("%lld%lld",&n,&k);
		
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&x[i]);
			a[i]=x[i];
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&y[i]);
		}
		
		memset(b,0,sizeof(b));
        memset(pre,0,sizeof(pre));
        memset(fg,0,sizeof(fg));
		sort(a+1,a+n+1);
		m=unique(a+1,a+n+1)-a-1;
		for(int i=1;i<=n;i++)
		{
			b[lower_bound(a+1,a+m+1,x[i])-a]++;
		}
		for(int i=1;i<=n;i++)
		{
			pre[i]=pre[i-1]+b[i];
		}
		for(int i=1;i<=n;i++)
		{
			fg[i]=pre[upper_bound(a+i+1,a+m+1,a[i]+k)-a-1]-pre[i-1];
		}
		
		node *rot=New(1,n);
			
		for(int i=1;i<=m;i++)
		{
			ans=max(ans,rot->qry(upper_bound(a+i+1,a+m+1,a[i]+k)-a,m)+fg[i]);
		}
		
		printf("%lld\n",ans);
	}
	
	return 0;
}
```
另外，要注意 $lower\_bound$ 与 $upper\_bound$ 的使用

---

## 作者：二gou子 (赞：2)

## 思路

首先显而易见的是，纵坐标并没有什么用，那个平台放在那里就一直在那里不会动，所以根本不用考虑纵坐标。

那么下面开始考虑如何接住尽可能多的点，首先一个小贪心能够证明，当平台的边缘刚好能接住一个点的时候一定是最优的放法，所以先用两层循环套起来，枚举每个点，用数组来记录以当前点结尾的平台最多能接住几个点。但是一看数据范围，不允许我们两层循环，于是想到二分查找。找到那一个刚好能接住的点，然后右端点-左端点+1就是端点个数。此处复杂度是$O(nlogn)$。

一开始我想了一个错的贪心，把能接住最多点的那个平台先放入答案，然后从剩下的平台中找最大值，但这显然是不对的，有可能两边较长的平台接住的点比一个最多的和一个较小的多，最后一组数据就是反例。想了一会，先打了个两层暴力，枚举每个点，然后算出两个平台的点和，找最大值，~~我怀着梦想提交，然后$T$飞了~~。

接着想怎么优化。发现两个平台如果有重合出现那么一定不是最优解，所以说我们可以一层循环来枚举，然后找剩下两段分别的最大值再进行比较即可。而区间最大值查询又让我想到了$ST$表这个神奇的数据结构，但是打完$ST$我又想到了一个问题：我每次用一个平台把剩下的部分分成两段，而我$ST$表只能维护以这个数结尾的最大值，这就导致了我无法准确定位后面的区间范围的起点到底从哪里开始不会与当前平台重复。但是我第二个$ST$表打完一半恍然大悟，我直接倒着循环就不用管右边那一段了，因为如果取右边那一段就相当于是我用右边那一段去找左边那一段，而左边那一段我知道具体的区间，这样问题就迎刃而解了，总时间复杂度应该是$O(nlogn)$。

## 题目翻译的是n的范围而不是n的和，让我白想了一万年更加高效的算法

## 代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<cstdlib>
#include<ctime>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int t,ans,maxx,n,k;
int x[200005],y[200005],maxn[200005][25];
int qry(int l,int r){
	if(l>r) return 0;//这里有个细节，可能会出现左端点大于右端点的情况，这时候要返回0
	int k=log(r-l+1)/log(2);
	return max(maxn[l][k],maxn[r-(1<<k)+1][k]);
}
struct F{
	int sum,front,tail;
}f[200005];
int main()
{
	t=read();
	while(t--){
		maxx=0;
		n=read();
		k=read();
		for(int i=1;i<=n;i++){
			x[i]=read();
		}
		sort(x+1,x+1+n);
		for(int i=1;i<=n;i++){
			y[i]=read();
		}
		for(int i=1;i<=n;i++){
			int l=1,r=i,now;
			while(l<=r){
				int mid=(r+l)>>1;
				if(x[i]-x[mid]>k){
					l=mid+1;
				}
				else{
					r=mid-1;
					now=mid;
				}
			}
			f[i].sum=i-now+1;
			f[i].front=now;
			f[i].tail=i;//用结构体记录所需要的变量
		}
		for(int i=1;i<=n;i++){
			maxx=max(maxx,f[i].sum);
			maxn[i][0]=f[i].sum;
		}
		for(int j=1;j<=20;j++){
			for(int i=1;i+(1<<j)-1<=n;i++){
				maxn[i][j]=max(maxn[i][j-1],maxn[i+(1<<(j-1))][j-1]);
			}
		}
		for(int i=n;i>=1;i--){
			maxx=max(maxx,f[i].sum+qry(1,f[i].front-1));//左边区间的起始点就是1，而结束的就是当前平台的起点再-1
		}
		printf("%d\n",maxx);
	}
	return 0;
}
```

---

## 作者：奇米 (赞：2)

# 题解- $\mathrm{CF1409E}$

## 题目意思

[题目传送门](https://www.luogu.com.cn/problem/CF1409E)

## $\mathrm{Sol}$

真就我用数据结构做这道题目？？！

我们首先对坐标离散化一下然后计算出以 $i$ 开头的平台 $[i,i+k]$ 能落下几个小球记做 $s_i$ 。我们对 $s_i$ 建一颗线段树维护区间最大值。

于是我们枚举第一个平台的起点 $st$ ，那么这次的贡献即为 $s_{st}+\max\limits_{j=st+1}^{n}(s_j)$，直接线段树算一下就好了。

时间复杂度 $O(n \log n)$

## $\mathrm{Code}$

```cpp
int n,m,Q,x[N],y[N],a[N],gs[N],pre[N],s[N],mx[N<<2],ans;

inline void build(int x,int l,int r)
{
	if(l==r)
	{
		mx[x]=s[l];
		return;
	}
	int mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	mx[x]=max(mx[x<<1],mx[x<<1|1]);
}

inline int ask(int x,int l,int r,int ll,int rr)
{
	if(ll>r||rr<l) return 0;
	if(ll<=l&&r<=rr) return mx[x];
	int mid=l+r>>1,ans=0;
	ans=max(ask(x<<1,l,mid,ll,rr),ask(x<<1|1,mid+1,r,ll,rr));
	return ans;
}

int main()
{
	io.read(Q);
	for (;Q--;)
	{
		io.read(n),io.read(m);
		For(i,0,n) gs[i]=0,pre[i]=s[i]=0;
		For(i,1,n) io.read(x[i]),a[i]=x[i];
		For(i,1,n) io.read(y[i]);
		sort(a+1,a+n+1);
		int tot=unique(a+1,a+n+1)-a-1;
		For(i,1,n) gs[lower_bound(a+1,a+tot+1,x[i])-a]++;
		For(i,1,n) pre[i]=pre[i-1]+gs[i];
		For(i,1,n) s[i]=pre[upper_bound(a+i+1,a+tot+1,a[i]+m)-a-1]-pre[i-1];
		build(1,1,tot);
		For(i,1,tot) ans=max(ans,s[i]+ask(1,1,tot,upper_bound(a+i+1,a+tot+1,a[i]+m)-a,tot));
		io.write(ans),puts(""),ans=0;
	}
	return 0;
}
		
```


---

## 作者：EternalEpic (赞：2)

仔细阅读题目可发现纵坐标不影响答案，于是只要考虑横坐标。

将横坐标按升序排序，预处理出 $lpos$ 和 $rpos$ 两个数组。

$lpos(i)$ 表示在区间 $[1, i]$ 中放第一块板可以得到的最大答案。

$rpos(i)$ 表示在区间 $[i, n]$ 中放第二块板可以得到的最大答案。

这两个数组都可以用指针扫描一遍得到，最后在将每一项加起来得到答案。

时间复杂度 $O(nlog_{2}{n})$ 。

```cpp
const int Maxn = 2e5 + 5;
int T, n, k, a[Maxn], b[Maxn];
int lpos[Maxn], rpos[Maxn];

signed main(void) {
//	file("");
	for (read(T); T; T--) {
		read(n), read(k);
		for (int i = 1; i <= n; i++) read(a[i]);
		for (int i = 1; i <= n; i++) read(b[i]);
		sort(a + 1, a + n + 1);
		if (a[n] - a[1] <= k << 1) { writeln(n); continue; }
		
		for (int i = 1, pos = 1; i <= n; i++) {
			while (pos < n && a[pos + 1] - a[i] <= k) ++pos;
			rpos[i] = pos - i + 1;
		} for (int i = n - 1; i >= 1; i--) chkmax(rpos[i], rpos[i + 1]);
		
		for (int i = n, pos = n; i >= 1; i--) {
			while (pos > 1 && a[i] - a[pos - 1] <= k) --pos;
			lpos[i] = i - pos + 1; 
		} for (int i = 2; i <= n; i++) chkmax(lpos[i], lpos[i - 1]);
		
		int ans = 0;
		for (int i = 1; i < n; i++) chkmax(ans, lpos[i] + rpos[i + 1]);
		writeln(ans);
	}
//	fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}
```



---

## 作者：SSerxhs (赞：1)

显然 $y$ 没用

把点按照 $x$ 排序，可以通过双指针或二分找到以每个点为左/右端点的线段可以覆盖到左/右侧哪个点，记为 pre 和 nxt。再预处理出在每个点左/右侧放置一条线段最多可以覆盖多少个点（这个可以通过预处理的数组处理实现），记为 z 和 y。显然令答案线段没有**有长度的重合**不劣，则枚举答案线段的中间分界点，可以发现答案为 $\max\{z_i+y_{i+1}\}$

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+2;
int x[N],nxt[N],pre[N],f[N][2],z[N],y[N];
int t,n,m,i,j,c;
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
int main()
{
	read(t);
	while (t--)
	{
		read(n);read(m);
		for (i=1;i<=n;i++) read(x[i]);
		sort(x+1,x+n+1);
		for (i=1;i<=n;i++) read(j);
		pre[1]=1;
		for (i=j=1;i<=n;i++)
		{
			f[i][0]=f[i][1]=0;
			while ((j<n)&&(x[j+1]<=x[i]+m)) pre[++j]=i;
			nxt[i]=j;
		}y[n+1]=0;
		for (i=1;i<=n;i++) z[i]=max(z[i-1],i-pre[i]+1);
		for (i=n;i;i--) y[i]=max(y[i+1],nxt[i]-i+1);c=0;
		for (i=1;i<=n;i++) c=max(c,z[i]+y[i+1]);printf("%d\n",c);
	}
}
```

---

## 作者：超级玛丽王子 (赞：0)

[在本蒟蒻的博客食用更佳](https://www.luogu.com.cn/blog/LXLDuliu-IAKIOI/solution-cf1409e)

### 下面简单描述一下题意。**（请注意题意有转义）**。

一条直线上有若干个点，以及两条长度都为 $k$ 的线段。可以在直线的任意位置放置线段，但是线段的起止点必须都是整点（即横坐标为整数的点）。请求出这两条线段最多能覆盖多少个点。


### 接下来讲讲正解。

从上面的描述可以看出，本题的解决跟点的纵坐标**一点关系也没有**。我们需要做的是首先将横坐标从小到大排序，然后从左往右依次处理每个点。

在处理第 $i$ 个点时：
1. 向右搜索第一个横坐标大于 $x_i+k$ 的点，也就是第一个从第 $i$ 个点向右放板装不下的点，并计算这个点到 $i$ 能装下多少个点。**请注意：搜索到的那个点不包括在装下的点里**
2. 向左搜索第一个横坐标大于等于 $x_{i-1}-k$ 的点，也就是第一个从第 $i-1$ 个点向左放板装下的点，并计算这个点到 $i-1$ 能装下多少个点。**请注意：**
	1. **当处理到第 $1$ 个点的时候再开始向左搜索；**
    2. **搜索到的点一定要包括在装下的点里。**
3. 维护 max 值，即比对一下。**注意向右搜索的和向左搜索的要分开记录**


做到这些就可以AC啦！

AC Code: 
```cpp
/*
	Author: 我爱Chtholly
	Date: 2020/09/05
	Problem: CF1409E Two Platforms 
    Time: 2.01s
    Memory: 4.80MB
*/
#include<bits/stdc++.h>
#define re register
//小小卡个常 
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
using namespace std;
typedef long long ll ;
const int N = 2e5 + 9 ;
int x[N],t,n,k;
//以下全部都是快读快输的内容 
char buf[1 << 21], * p1 = buf, * p2 = buf;
inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
	}
inline int read() {
	int ret = 0, f = 0;
	char ch = getc();
	while (!isdigit(ch)) {
		if (ch == '-')
			f = 1;
		ch = getc();
	}
	while (isdigit(ch)) {
		ret = ret * 10 + ch - 48;
		ch = getc();
	}
	return f ? -ret : ret;
}
char Buf[1 << 21], out[20];
int P, Size = -1;
inline void flush() {
	fwrite(Buf, 1, Size + 1, stdout);
	Size = -1;
}
inline void write(int x, char ch) {
	if (Size > 1 << 20) flush();
	if (x < 0) Buf[++Size] = 45, x = -x;
	do {
		out[++P] = x % 10 + 48;
	} while (x /= 10);
	do {
		Buf[++Size] = out[P];
	} while (--P);
	Buf[++Size] = ch;
}
//快读快输结束 
inline int max(int a, int b) {
    return a>b?a:b;
}
int main()
{
    t=read();
    while(t--){
        n=read(),k=read();
        for(re int i = 0 ; i < n ; i++) *(x+i)=read();
        for(re int i = 0 ; i < n ; i++) read();   //以上都是读入 
        sort(x , x + n); 
        int maxi = 0 , opt = 0 , fans = 0;
        for(re int i = 0 ; i < n ; i++){
            int curr = upper_bound(x + i, x + n , *(x+i) + k)  - x - i;  //从第i个点向右二分最多能装下的点数 
            if(i) opt = x + i - lower_bound(x , x + i - 1 , *(x+i-1) - k); //从上一个点向左二分另一块板最多能装下的点数 
            maxi = max(maxi , opt); 
            curr+=maxi;
            fans = max(fans , curr);  //以上维护max 
        }
        write(fans, '\n');
    }
    flush();  //千万别忘了刷新fwrite的缓冲区 
    return 0;
}
```

~~不加那一堆卡常1.99s来的~~

## 看我写的这么详细，不点个赞再走嘛QAQ

---

## 作者：kradcigam (赞：0)

写篇题解庆祝我第 $1$ 次参加 $div3$，而且还 $AK$ 了

我们发现 $y$ 坐标越低越好，所以答案与 $y$ 坐标无关。

现在问题等价于一条数轴上有 $n$ 个点，求 $2$ 条线段覆盖尽可能多的点.

我们考虑类似于[双子序列最大和](https://www.luogu.com.cn/problem/P2642)一样的[做法](https://www.luogu.com.cn/blog/180242/solution-p2642)

首先，有 $2$ 个结论：
- $2$ 条线段重叠明显是不优的，我们就需要让这两条无重叠。
- 线段的至少 $1$ 的端点要是 $n$ 个点当中的一个，这样显然会比线段 $2$ 段都不是 $n$ 个中的一个的要优。

这样就可以了

代码：
```cpp
int work(){
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	memset(k,0,sizeof(k));
	int n,k;read(n);read(k);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)read(b[i]);
	sort(a+1,a+n+1);//不要忘了排序
	for(int i=1;i<=n;i++)f[i]=i-(lower_bound(a+1,a+n+1,a[i]-k)-a)+1;//以第i个点为左端点
	for(int i=n;i;i--)p[i]=upper_bound(a+1,a+n+1,a[i]+k)-a-i;//以第i个点为右端点
	for(int i=1;i<=n;i++)g[i]=max(g[i-1],f[i]);
	for(int i=n;i;i--)::k[i]=max(::k[i+1],p[i]);
	int ans=0;
	for(int i=1;i<=n+1;i++)ans=max(ans,g[i-1]+::k[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ShuYuMo (赞：0)

跟这道题非常相似 [https://www.luogu.com.cn/problem/P3143](https://www.luogu.com.cn/problem/P3143) 可以一并 `AC` 这道题。

`two-pointer`问题， 利用数组的单调性。 

因为是要寻找两个合法的子序列，可以考虑使用两个数组维护答案：

 - `InL[i]`表示区间全部在`i`前面的最大区间。 
 - `InR[i]`表示区间全部在`i`后面的最大区间。 
 
最后枚举一个中间点统计答案即可。

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <climits>
#include <algorithm>
#include <map>
inline int read() { char c = getchar(); int sign = 1; int x = 0; while(c > '9' || c < '0') { if(c=='-')sign = -1; c = getchar(); } while(c <= '9' && c >= '0') { x *= 10; x += c - '0'; c = getchar(); } return x * sign; }
using namespace std;
const int _ = 2e5 + 100;
int n, k;
int A[_];
int B[_];
int W[_];
int InL[_];
int InR[_];
map<int, int > M;
void doit(){
    n = read(), k = read();
    for(int i = 1; i <= n; i++) B[i] = read();
    for(int i = 1; i <= n; i++) read();
    for(int i = 1; i <= n; i++) ++M[B[i]];
    memcpy(A, B, sizeof(A));
    sort(A + 1, A + 1 + n);
    n = unique(A + 1, A + 1 + n) - A - 1;
    for(int i = 1; i <= n; i++) W[i] = M[A[i]];
    int L = 1;
    int sum = 0;
    for(int R = 1; R <= n; R++){
        sum += W[R];
        while(A[R] - A[L] > k) sum -= W[L], L++;
        InL[R] = sum;
    }
    int R = n;
    sum = 0;
    for(int L = n; L >= 1; L--){
        sum += W[L];
        while(A[R] - A[L] > k) sum -= W[R], R--;
        InR[L] = sum;
    }
    for(int i = 1; i <= n; i++) InL[i] = max(InL[i - 1], InL[i]);
    for(int i = n; i >= 1; i--) InR[i] = max(InR[i + 1], InR[i]);
    int ans = 0;
    for(int i = 0; i <= n; i++){
        ans = max(ans, InL[i] + InR[i + 1]);
    }
    if(A[n] - A[1] <= k + k) {
        ans = 0;
        for(int i = 1; i <= n; i++) ans += W[i];
    }
    printf("%d\n", ans);
    for(int i = 0; i <= n + 2; i++) A[i] = B[i] = W[i] = InL[i] = InR[i] = 0;
    M.clear();
}

int main(){
    int T = read();
    while(T--) doit();
    return 0;
}
```

---

