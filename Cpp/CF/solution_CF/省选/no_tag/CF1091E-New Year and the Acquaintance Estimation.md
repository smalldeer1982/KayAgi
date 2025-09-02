# New Year and the Acquaintance Estimation

## 题目描述

Bob是社交网站`FaithBug`上的一名活跃用户。在这个网站上，人们之间的友情是相互的。这就是说，如果 $a$ 是 $b$ 的一个朋友，那么 $b$ 也是 $a$ 的一个朋友。因此，每个用户都有不小于 $0$ 个朋友。

这个早晨，一个匿名用户给Bob发送了这个链接：[graph realization problem](https://en.wikipedia.org/wiki/Graph_realization_problem)。Bob想要知道那人是谁。为了知道这件事，他首先得知道这个社交网络的形态。他查看了网站上所有其他人的个人信息，并且记下了他们的朋友数量。然而，他忘了记下自己的朋友数量！请帮他计算他可能的朋友数量。如果有多解，全部输出。

简化版：给出一个长度为 $n$ 的度数序列，问是否存在一个大小为 $n+1$ 的简单无向图，满足给定的度数序列是这个图的度数序列的前缀。

## 说明/提示

$1\leq n\leq 5\times 10^5, 0\leq a_i\leq n$


第一个样例中，唯一的可能情况是，每个人都是所有其他人的朋友。因此，Bob有三个朋友。

第二个样例中，有三种可能的非等价情况：

1. $a$ 是 $b$ 的朋友， $c$ 是 $d$ 的朋友，然而Bob没有朋友。
2. $a$ 是 $b$ 的朋友， $c$ 和 $d$ 都是Bob的朋友。
3. Bob是所有人的朋友。

第三个样例是不可能的，因为第二个人应该是所有人的朋友，然而第一个人却没有朋友。

## 样例 #1

### 输入

```
3
3 3 3
```

### 输出

```
3 
```

## 样例 #2

### 输入

```
4
1 1 1 1
```

### 输出

```
0 2 4 
```

## 样例 #3

### 输入

```
2
0 2
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
35
21 26 18 4 28 2 15 13 16 25 6 32 11 5 31 17 9 3 24 33 14 27 29 1 20 4 12 7 10 30 34 8 19 23 22
```

### 输出

```
13 15 17 19 21 
```

# 题解

## 作者：凄魉 (赞：3)

一张图每个点的度数总和是偶数……

经典问题：给定一个非负整数的序列$d$,问是否有一个简单图使得每个点的度数恰好为这个序列。可能无解。

首先如果$\sum_{i=1}^nd_i$是奇数那就铁定无解了，以下默认不会出现这种情况。

Havel-Hakimi 算法

可以贪心的构造，将所有点的度数降序排序，然后每次把度数最大的点$1$拿出来，向其他度数次大的那些点连边。

度数序列就会从$\{d_1,d_2,d_3,d_4,...,d_n\}$变到$\{d_2-1,d_3-1,...,d_{d_1+1}-1,d_{d_1+2},...,d_n\}$。

可以证明如果原来的度数序列可简单图化，那么贪心连边后的度数序列也可以简单图化，充分且必要。

Erdős–Gallai 定理

对于非递增度数序列$\{d_1,d_2,\dots,d_n\}$，如果这个序列可简单化当且仅当
$$\forall 1\le k\le n,\sum_{i=1}^kd_i\le k(k-1)+\sum_{i=k+1}^nmin(k,d_i)$$

我也只知道个必要性：右侧展示的其实是前$k$个点连边的数量上界，$k(k-1)$是前$k$个点之间连边的上界，后侧的$sigma$是前$k$个点与$n-k$个点连边的上界。

好像还有个是否有向图化的Fulkerson–Chen–Anstee定理。我也不是很懂……

$(a_i,b_i)$表示第$i$个点的出度和入度，对于一个$a_i$非递增的这个序列需要满足$\sum_{i=1}^na_i=\sum_{i=1}^nb_i$，以及
$$\forall 1\le k\le n,\sum_{i=1}^ka_i\le \sum_{i=1}^kmin(b_i,k-1)+\sum_{i=k+1}^nmin(b_i,k)$$


例题：

[CF1091E New Year and the Acquaintance Estimation](https://www.luogu.org/problemnew/show/CF1091E)

首先介绍这个题我的暴力做法……

第一步则是想到所有度数的和应该要是偶数。

判断加入一个数后这个序列还能不能简单图化，就利用上面那个E定理，这样对于一个序列我们能$O(n)$判断是否能构成一个图。这样的话我们就能枚举答案，在$O(n^2)$时间内解决这个问题了。

但注意到每次向序列中只添加一个数，这个操作对序列的影响是较小的，所以我们考虑加入一个数后序列会有什么变化，并且我们计算的式子有什么变化。

设我们当前加入的一个数为$x$，加入$x$后序列中第一个大于等于$x$的数是原序列中的第$i$大的数。我们要计算每一个$1\le k\le n+1$，上面那个式子是否成立。

那么我们分情况讨论一下：对于$k\le i$，对于这一部分我们计算的式子是
$$\sum_{i=1}^ka_i\le min(x,k)+k(k-1)+\sum_{i=k+1}^nmin(a_i,k)$$

发现式子的变化就只有一个$min$而已，注意到$k$是单调的，所以对于$k\le i$部分的计算又被分成了两部分：

$1\le k\le x$式子是$k+k(k-1)+\sum_{i=k+1}^nmin(a_i,k)-\sum_{i=1}^ka_i$是否$\ge 0$，发现这个式子与$x$无关，所以我们可以预处理这$n$个式子的值，以及前缀最小值。

$x\le k\le i$式子是$x+k(k-1)+\sum_{i=k+1}^nmin(a_i,k)-\sum_{i=1}^ka_i$是否$\ge 0$，我们处理出除去$x$部分的式子的值，我们区间查一个最小值就行了。

接下来是$i<k\le n+1$，也是预处理式子，只不过这一部分的预处理注意插入的数的位置是$i<k$的，小细节注意一下，这一部分也是查一个后缀最小值。

那就没了，具体细节看代码吧。我的复杂度瓶颈是一个区间RMQ，最后的复杂度是$O(NlogN)$，但是注意到询问的区间是$(x,i]$，应该可以从大到小枚举$x$，这样区间就单调了，也就能$O(N)$做了……

另外题解的做法是观察到合法的度数答案一定是一个区间，所以我们可以二分这个答案区间的两个端点，每次去check答案合不合法，这样的话可以很简单的利用单次$NlogN$的check（就是暴力用定理去算），做到$O(Nlog^2N)$，这个做法好写细节少，场上各位巨佬大多都是这么做的。



```
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 520230
#define ll long long
#define ls i<<1
#define rs i<<1|1
#define INF 0x3f3f3f3f3f3f3f3f
int a[N],ans[N],cc;ll sum[N],suf[N],lml[N],lmr[N],lmk[N],tree[N<<2];
bool cmp(int a,int b) {return a>b;}
void build(int i,int l,int r)
{
	if (l==r) {tree[i]=lml[l];return;}
	int mid=l+r>>1;
	build(ls,l,mid);build(rs,mid+1,r);
	tree[i]=min(tree[ls],tree[rs]);
}
ll query(int i,int l,int r,int L,int R)
{
	if (L<=l&&r<=R) return tree[i];
	int mid=l+r>>1;
	if (R<=mid) return query(ls,l,mid,L,R);
	else if (L>mid) return query(rs,mid+1,r,L,R);
	return min(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
}
inline int read(){
	int n=0;char a;bool z=false;
	while(a=getchar())
	{
		if (a>'9'||a<'0')
			if (z) break;
			else continue;
		if (!z) z=true;
		n=(n<<1)+(n<<3)+(a^48);
	}
	return n;
}
int main()
{
	int n=read();bool Z=false;
	for (int i=1;i<=n;++i) a[i]=read();
	sort(a+1,a+1+n,cmp);
	for (int i=n;i;--i) suf[i]=suf[i+1]+a[i];
	for (int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
	for (int i=1,j=n;i<=n;++i)
	{
		while(j&&a[j]<i) --j;
		if (j>i) lml[i]=1ll*(j-1)*i+suf[j+1]-sum[i];
		else lml[i]=suf[i+1]+1ll*i*(i-1)-sum[i];
		lmk[i]=lml[i]+i;
	}
	for (int i=0,j=n;i<=n;++i)
	{
		while(j&&a[j]<i+1) --j;
		if (j>i) lmr[i]=1ll*j*(i+1)-sum[i]+suf[j+1];
		else lmr[i]=suf[i+1]+1ll*i*(i+1)-sum[i];
	}
	build(1,1,n);
	lmk[0]=INF;for (int i=1;i<=n;++i) lmk[i]=min(lmk[i-1],lmk[i]);
	lmr[n+1]=INF;for (int i=n;i>=0;--i) lmr[i]=min(lmr[i],lmr[i+1]);
	for (int x=sum[n]&1,i=n;x<=n;++++x)
	{
		while(i&&x>a[i]) --i;Z=true;
		if (lmk[min(i,x)]<0) continue;
		if (x<i&&query(1,1,n,x+1,i)<-x) Z=false;
		if (!Z) continue;
		if (lmr[i]<x) Z=false;
		if (Z) ans[++cc]=x;
	}
	if (!cc) return !printf("-1");
	for (int i=1;i<=cc;++i) printf("%d ",ans[i]);
	return 0;
}

//by qlwpc
```cpp

---

## 作者：SovietPower✨ (赞：3)

$Description$

给定度数序列$d_1,...,d_n$，求$d_{n+1}$等于多少时，度数序列$d_1,d_2,...,d_{n+1}$可简单图化。输出所有可能的$d_{n+1}$。

可简单图化是指，存在一张简单无向图，使得该图点的度数可以与该度数序列一一对应。

$n\leq 5\times 10^5$。

$Solution$

~~话说只要看出是[Erdős–Gallai定理](https://www.cnblogs.com/SovietPower/p/9757651.html#erd%C5%91sgallai%E5%AE%9A%E7%90%86)然后想到二分，就是裸题么...？~~

考虑枚举$d_{n+1}$。给定一个度数序列判断其是否合法可以用[Erdős–Gallai定理](https://www.cnblogs.com/SovietPower/p/9757651.html#erd%C5%91sgallai%E5%AE%9A%E7%90%86)，复杂度$O(n)$。所以现在的复杂度是$O(n^2)$的。

根据样例我们还可以猜想并验证：

1. 由握手定理（就是无向图中所有点的度数之和为偶数），$d_{n+1}$的奇偶性可以确定。

2. 满足条件的$d_{n+1}$一定是一段连续的区间。

所以我们就可以二分了。

二分要得到的是某段区间，分别二分左右端点，但还需要讨论一下。

令$n=n+1$，写一下Erdős–Gallai定理的式子：$$\sum_{i=1}^kd_i\leq k(k-1)+\sum_{i=k+1}^n\min(d_i,k)$$

二分$n$的度数$d_n=mid$，然后$sort$一下度数序列。

从小到大枚举$k$的时候，记$left$为左式的值，$right$为右式的值。若一直有$left\leq right$，显然$mid$可行。

否则若$left>right$，我们要么减小$left$，要么增大$right$。而唯一能改变的就是$n$的度数$mid$。

所以现在若$mid\geq d_k$（影响左式），我们可以减小$mid$使得序列合法，也就是答案偏大。

若$mid<d_k$（影响右式），可以增大$mid$，也就是答案偏小。

可以确定答案偏大偏小，就可以二分出区间了。复杂度$O(n\log n)$。

[经过一些预处理也可以做到$O(n)$](http://codeforces.com/contest/1091/status/E?order=BY_CONSUMED_TIME_ASC)。

一份$O(n\log n)$的代码：

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5e5+5;

int A[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Check(const int n,const int mid)
{
	static int d[N];
	static LL sum[N];
	A[n]=-1;
	for(int i=1,p=1; i<=n; ++i) d[i]=(p==i&&mid>A[p])?mid:A[p++], sum[i]=sum[i-1]+d[i];
	LL vl,vr;
	for(int k=1,p=n; k<=n; ++k)
	{
		while(p>k && d[p]<k) --p;
		vl=sum[k], vr=1ll*k*(k-1)+1ll*(std::max(p,k)-k)*k+sum[n]-sum[std::max(p,k)];
		if(vl>vr) return mid<d[k]?-1:1;
	}
	return 0；
}

int main()
{
	int n=read(),parity=0;
	for(int i=1; i<=n; ++i) parity^=(A[i]=read())&1;
	std::sort(A+1,A+1+n,std::greater<int>());

	int l=0,r=n-parity>>1,L=0,R=-1,mid;
	while(l<=r)
		if(Check(n+1,(mid=l+r>>1)*2+parity)>=0) L=mid, r=mid-1;
		else l=mid+1;
	l=0,r=n-parity>>1;
	while(l<=r)
		if(Check(n+1,(mid=l+r>>1)*2+parity)<=0) R=mid, l=mid+1;
		else r=mid-1;

	if(L>R) puts("-1");
	else for(int i=L; i<=R; ++i) printf("%d ",i*2+parity);

	return 0;
}
```

---

## 作者：Miraik (赞：0)

无向图的度数和一定为偶数，于是我们可以得到所有答案奇偶性相同。

考虑怎么判定一个长度为 $n$ 的度数序列 $deg$ 是否合法。

先将 $deg$ 降序排序。

考虑长度为 $i$ 的前缀，考虑其度数和最大的情况，就是前 $i$ 个点两两有边，后 $n-i$ 个点 $j$ 向前面的 $\min(deg_j,i)$ 点有边，因此即为 $i(i-1)+\sum\limits_{j=i+1}^n \min(deg_j,i)$。

感性理解（大胆断言）一下，如果 $deg$ 的每个前缀都能满足这个度数和的限制 $\sum\limits_{j=1}^ideg_j \le i(i-1)+\sum\limits_{j=i+1}^n \min(deg_j,i)$，那么序列 $deg$ 必然合法。

~~然而事实上，如果你可以打开题面里的网址，你是可以找到一个 Erdos-Gallai 定理，内容即为以上。~~

由此我们也可以得到答案一定是一段区间：

+ 当未知点的度数 $X$ 小于某个界值 $L$，可能会在某个较前的 $i$，也就是 $deg_i < X$ 时已经不满足限制了，此时我们适当提高 $X$ 可以让限制变宽（即上面限制的右式变大），使其满足限制。

+ 当未知点的度数 $X$ 大于某个界值 $R$，可能会在某个较后的 $i$，也就是 $deg_i > X$ 时不再满足限制，此时我们适当降低 $X$ 可以让前缀度数和变小（即上面限制的左式变小），使其满足限制。

因此考虑二分 $L$ 和 $R$，如果在检查的过程中出现了不合法，则根据当前的 $deg_i$ 与二分值 $X$ 的关系判断将 $X$ 调小或调大。

二分出 $L$ 和 $R$ 后，再输出它们中所有奇偶性和已知点度数和相同的数即可。

总时间复杂度 $O(n \log n)$。

[code（duel 的时候没想清楚就直接写，最后写成 2log 了）](https://codeforces.com/contest/1091/submission/212790322)

---

## 作者：__Hacheylight__ (赞：0)

Codeforces 1091E New Year and the Acquaintance Estimation

【题意】

给你$n$个点的度$(d_1,d_2,...,d_n)$，然后问你第$n+1$个点的度$(d_{n+1})$的所有可能值

附上鄂尔多斯定理：$\sum\limits^{k}_{i=1}d_i\leq k(k-1)+ \sum\limits^n_{i=k+1} \min (d_i,k)$

【分析】

首先他们的点的度数和一定为偶数，那么我们就能够知道$d_{n+1}$的奇偶性。

我们观察样例2和4，发现他们的答案都是在相同奇偶性下相邻的，于是我们大胆猜测：如果$d_{n+1}=X$满足条件且$d_{n+1}=Y$满足条件，那么$X<Z<Y$且与$X,Y$奇偶性相同的$Z$也一定符合。

为什么？ 很明显，如果$X$符合，那么我们可以把前n个人中的一对$(u,v)$的还有关系拆掉，再把$u$和$v$与$n+1$构成好友关系（前提是$u$和$v$之前与$n+1$不是好友关系），这样答案就变成了$X+2$了

然后我们的问题就转化成为求出上文中的$X$和$Y$

枚举不行，我们就去思考二分答案。对于一个$d_{n+1}$，我们可以通过鄂尔多斯定理判断出这个新图是否可能。如果他不行，那么我们需要知道他是大是小。这取决于他是在不等式的左侧还是右侧。如果在左侧，那么这个$d_{n+1}$就太大了，因为如果扩大那么不等式是永远不会成立的；反之也类似。

我们发现上面的定理，如果$d$有序，后面的$min(d_i,k)$应该是分成两段：一段时间$d_i$($d_i$更小），一段时间$k$（$d_i$更大）。这个需要前缀和去维护。

于是问题就做完了。

emm 这个是O(nlogn)的吧。

然后我们发现除排序外可以优化O(n)

我们用一个差分数组cf去维护对于每一个$k$，计算哪一段$X...Y$是符合要求的，然后如果一段区间的$cf[X...Y]=n$则说明这一段通过了所有的要求，就把他加到答案里就好。

呵呵呵虽然时间复杂度依然是O(nlogn)的

【代码】

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define per(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, sum) memset(a, sum, sizeof(a))
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define enter cout << endl
#define SZ(x) ((int)x.size())
typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef vector <ll> vl ;
typedef pair <int, int> pii ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int N = 100010 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const int MOD = 1000000007 ;
void print(int x) { cout << x << endl ; exit(0) ; }
void PRINT(string x) { cout << x << endl ; exit(0) ; }
void douout(double x){ printf("%lf\n", x + 0.0000000001) ; }

int n ;

signed main(){
    scanf("%d", &n) ; vi a(n), cf(n + 2), res ; vl sum(n + 1) ;
	for (int i = 0; i < n; i++) scanf("%d", &a[i]) ;
	sort(a.begin(), a.end()) ;
	for (int i = 0; i < n; i++) sum[i + 1] = sum[i] + a[i] ;
	int j = 0 ;
	for (int k = 1; k <= n; k++) {
		ll l = sum[n] - sum[n - k], r = 1ll * k * (k - 1) ;
		while (j < n && a[j] < k) j++ ;
		int up = min(n - k, j) ;
		r += sum[up] + 1ll * k * (n - k - up) ; // 前面是那个定理
		int bound = a[n - k] ;
		{ // 分类讨论之后差分
			ll dif = l - r ;
			if (dif <= k && dif <= bound) {
				cf[max(dif, 0ll)]++ ;
				cf[bound + 1]-- ;
			}
		}
		{
			l -= a[n - k] ;
			r += min(a[n - k], k) ;
			ll dif = r - l ;
			if (dif > bound) {
				cf[bound + 1]++ ;
				cf[min(dif + 1, n + 1ll)]-- ;
			}
		}
	}
	int now = 0 ;
	for (int i = 0; i <= n; i++) {
		now += cf[i] ;
		if (now == n && (sum[n] + i) % 2 == 0) res.pb(i) ;
	}
	if (res.empty()) print(-1) ;
	for (int i = 0; i < SZ(res); i++) printf("%d ", res[i]) ; enter ;
}
```

---

## 作者：封禁用户 (赞：0)

想讲一下题意，给你n个人的好友数量，求Bob的好友数量的所有可能值（好友是双向的）

要做这道题，你得先知道给你一组数据，如何判定是某能满足这个关系，题目中有一个链接（Graph realization problem）中有一种方法（https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93Gallai_theorem）：

下面是翻译：

S可简单图化当且仅当这些数字的和为偶数，且
![](https://wikimedia.org/api/rest_v1/media/math/render/svg/febd8dee6050a0cf792cff9442935b36db434db8)对于任何1<=k<=n都成立

对前k个点分配度数，除了两两能连k(k−1)/2条边外，剩下的度数由后面点的度数补。
因为di非递增，从小到大枚举k，维护di后缀与k取min的和。就可以O(n)判断了。（这全是链接里的内容）

这道题主要的解题要点一是你要点进去看那个链接（像我考场上以为不重要就没进去看...）二是要想清楚什么时候是过大而不满足，什么时候是过小而不满足。经过推理发现，若第一个不符合不等式的k小于Bob的数量，就是过大，某则就是过小。有了这个条件，我们就可以二分这段区间O（nlogn）。

还有一种更快的做法O（n）：然后枚举k,对于每个k，根据上述不等式推出满足的好友数量的区间，最后取n个区间的交点即可，使用差分优化区间操作

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin>>n;
	vector<int>d(n);
	for(int i=0;i<n;i++)
		cin>>d[i];
	sort(d.begin(),d.end());
	vector<long long>pref(n+1);
	for(int i=0;i<n;i++)
		pref[i+1]=pref[i]+d[i];
	vector<int>bal(n+2);
	int j=0;
	for(int k=1;k<=n;k++)
	{
		long long l=pref[n]-pref[n-k];
		long long r=(long long)k*(k-1);
		while(j<n&&d[j]<k)
			j++;
		int up=min(n-k,j);
		r+=pref[up]+(long long)k*((n-k)-up);
		int bound=d[n-k];
		long long diff=l-r;
		if(diff<=k&&diff<=bound)
		{
			bal[max(diff,0LL)]++;
			bal[bound+1]--; 
		}
		l-=d[n-k];
		r+=min(d[n-k],k);
		diff=r-l;
		if(diff>=bound+1)
		{
			bal[bound+1]++;
			bal[min(diff+1,n+1LL)]--;
		} 
	}
	vector<int>res;
	int b=0;
	for(int i=0;i<=n;i++)
	{
		b+=bal[i];
		if(b==n)
			if((pref[n]+i)%2==0)
				res.push_back(i);
	}
	if(res.empty())
		cout<<-1;
	else
		for(int i=0;i<res.size();i++)
			cout<<res[i]<<' ';
	cout<<endl;
	return 0;
}

```

---

## 作者：Trimsteanima (赞：0)

给定$ｎ$个点的度数序列，再添加一个点，求添加的这个点的度数为多少时，满足这$ｎ＋１$个点可以构成简单无向图。

~~最简单的E题~~二分查找上下界，答案就是依次$-2$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=500010;
int n,a[N];
long long s2[N],s1[N],sum,Min,Max;
inline int read(){
    char ch;
    bool f=false;
    int res=0;
    while ((ch=getchar())<'0'||ch>'9');
    res=ch-'0';
    while ((ch=getchar())>='0'&&ch<='9') res=(res<<3)+(res<<1)+ch-'0';
    return res;
}
long long work(){
    for (int i=n;i>=1;i--)
        s1[i]=s1[i+1]+a[i];
    for (int i=1;i<=n;i++)
        s2[i]=s2[i-1]+a[i];
    long long x=0;
    sum=0;
    for (int i=1;i<=n;i++)
        sum+=a[i];
    for (int i=n;i;i--){
        int y=lower_bound(a+i+1,a+n+1,i,greater<int>())-a;
        long long z=(long long)i*(i-1)+(long long)(y-i-1)*i+s1[y];
        if (s2[i]-z>i){
            printf("-1\n");
            exit(0);
        }
        x=max(x,s2[i]-z);
    }
    if (sum&1){
        if (x&1);else x++;
    }
    else {
        if (x&1) x++;
    }
    return x;
}
int main(){
    n=read();
    for (int i=1;i<=n;i++)
        a[i]=read();
    sort(a+1,a+n+1,greater<int>());
    Max=work();
    reverse(a+1,a+n+1);
    for (int i=1;i<=n;i++)
        a[i]=n-a[i];
    Min=n-work();
    if (Max>Min){
        int T=Max;
        Max=Min;
        Min=T;
    }
    for (long long i=Max;i<=Min&&i<=n;i+=2)
        printf("%lld ",i);
    return 0;
}
```


---

