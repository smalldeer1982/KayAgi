# [ARC068E] Snuke Line

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc068/tasks/arc068_c

すぬけくんは鉄道会社を運営するゲームで遊ぶことにしました。すぬけ鉄道には $ M+1 $ 個の駅があり、 $ 0 $ から $ M $ までの番号がついています。 すぬけ鉄道の列車は駅 $ 0 $ から $ d $ 駅ごとに停車します。 例えば $ d\ =\ 3 $ のとき駅 $ 0 $,駅 $ 3 $,駅 $ 6 $,駅 $ 9 $, $ ... $ に停車します。

すぬけ鉄道が走っている地域には $ N $ 種類の名産品があり、種類 $ i $ の名産品は 駅 $ l_i $,駅 $ l_i+1 $,駅 $ l_i+2 $, $ ... $, 駅 $ r_i $ のいずれかに列車が停車したとき購入することが可能です。

列車が停車する間隔 $ d $ は $ 1,\ 2,\ 3,\ ...,\ M $ の $ M $ 種類が存在しています。 $ M $ 種類の列車それぞれについて、その列車に駅 $ 0 $ で乗車した場合に購入可能な名産品の種類数を求めなさい。 なお、列車から別の列車への乗り換えは許されないものとします。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 3\ ×\ 10^{5} $
- $ 1\ ≦\ M\ ≦\ 10^{5} $
- $ 1\ ≦\ l_i\ ≦\ r_i\ ≦\ M $

### Sample Explanation 1

\- $ 1 $ 駅ごとに停車する列車に乗った場合、種類 $ 1,2,3 $ の $ 3 $ 種類の名産品を購入することが可能です。 - $ 2 $ 駅ごとに停車する列車に乗った場合、種類 $ 1,2 $ の $ 2 $ 種類の名産品を購入することが可能です。 - $ 3 $ 駅ごとに停車する列車に乗った場合、種類 $ 2,3 $ の $ 2 $ 種類の名産品を購入することが可能です。

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 3```

### 输出

```
3
2
2```

## 样例 #2

### 输入

```
7 9
1 7
5 9
5 7
5 9
1 1
6 8
3 4```

### 输出

```
7
6
6
5
4
5
5
3
2```

# 题解

## 作者：zhouhuanyi (赞：23)

AT2300 Snuke Line

为什么你们不是主席树就是树状数组,发一个数论分块做法。

链接:https://www.luogu.com.cn/problem/AT2300

题目描述:有一趟列车有$M+1$个车站，从$0$到$M$编号。有$N$种商品，第$i$种只在编号$[li,ri]$的车站出售。一辆列车有一个预设好的系数$d$，从$0$出发，只会在$d$的倍数车站停车。对于$d$从$1$到$M$的列车，求最多能买到多少种商品。

题解:可以发现，对于一个$i$，要满足$l_{i}<=x\times d<=r_{i}$就会产生贡献。

$\qquad \qquad \qquad \qquad l_{i}<=x\times d<=r_{i}$

$\qquad \qquad \qquad \qquad \lceil \frac{l_{i}}{d} \rceil<=x<=\lfloor \frac{r_{i}}{d} \rfloor$

$\qquad \qquad \qquad \qquad \lfloor \frac{l_{i}-1}{d} \rfloor<x<=\lfloor \frac{r_{i}}{d} \rfloor$

$\qquad \qquad \qquad \qquad \lfloor \frac{l_{i}-1}{d} \rfloor<\lfloor \frac{r_{i}}{d} \rfloor$

上述式子可以数论分块，对于每一种不同的$i$，差分即可得到答案。

```
#include<iostream>
using namespace std;
int l[1000001],r[1000001],sum[1000001];
int main()
{
  int n,m,last;
  cin>>n>>m;
  for (int i=1;i<=n;++i)
    {
      cin>>l[i]>>r[i];
      l[i]--;
      for (int j=1;j<=l[i];j=last+1)
	{
	  last=min(l[i]/(l[i]/j),r[i]/(r[i]/j));
	  if (l[i]/j<r[i]/j)
	    {
	      sum[j]++;
	      sum[last+1]--;
	    }
	}
      sum[l[i]+1]++;
      sum[r[i]+1]--;
    }
  for (int i=1;i<=m;++i)
    {
      sum[i]+=sum[i-1];
      cout<<sum[i]<<endl;
    }
  return 0;
}

---

## 作者：hwk0518 (赞：10)

介绍两种比较主流的做法。

一种很好想，对于每个集合中的点，从小到大排序，设为$a_1,a_2,...,a_k$。设覆盖了$a_i$，且没有覆盖$a_1,...,a_{i-1}$的区间个数为$f(i)$，则答案为$\sum_{i=1 \to k}f(i)$。容易发现，覆盖了$a_i$，且没有覆盖$a_{i-1}$的区间一定不会覆盖$a_1,...,a_{i-2}$。所以问题转化为求左端点在$[a_{i-1}+1,a_i]$,右端点在$[a_i,m]$的区间个数。主席树维护即可。

代码：(5433ms)

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const int N=3e5+5;
const int M=1e5+5;
const int T=1e7+5;
int n,m,st[M],en[M];
pair<int,int> p[N];

struct Chairman_Tree
{
	int seg_tot,rt[N];
	struct node
	{
		int lsn,rsn,cnt;
	};
	node seg[T];
	
	void update(int &rt,int las,int l,int r,int pos)
	{
		seg[rt=++seg_tot]=seg[las];
		++seg[rt].cnt;
		if(l==r) return;
		int mid=(l+r)>>1;
		if(pos<=mid) update(seg[rt].lsn,seg[las].lsn,l,mid,pos);
		else update(seg[rt].rsn,seg[las].rsn,mid+1,r,pos);
	}
	
	int query(int rt,int las,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R) return seg[rt].cnt-seg[las].cnt;
		int mid=(l+r)>>1;int ret=0;
		if(L<=mid) ret+=query(seg[rt].lsn,seg[las].lsn,l,mid,L,R);
		if(R>mid) ret+=query(seg[rt].rsn,seg[las].rsn,mid+1,r,L,R);
		return ret;
	}
};
Chairman_Tree SS;

void init()
{
	int i,now=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
		scanf("%d%d",&p[i].first,&p[i].second);
	sort(p+1,p+n+1);
	
	for(i=1;i<=m;++i)
	{
		st[i]=now+1;
		while(p[now+1].first==i) ++now;
		en[i]=now;
	}
	
	for(i=1;i<=n;++i)
		SS.update(SS.rt[i],SS.rt[i-1],1,m,p[i].second);
}

int calc(int x,int y,int l,int r)
{
	return SS.query(SS.rt[en[y]],SS.rt[st[x]-1],1,m,l,r);
}

void work()
{
	int i,j,ans=0;
	for(i=1;i<=m;++i)
	{
		ans=0;
		for(j=i;j<=m;j+=i)
			ans+=calc(j-i+1,j,j,m);
		printf("%d\n",ans);
	}
}

int main()
{
	init();work();
	return 0;
}

```

另一种容易实现但不容易想。

我们先得出一个结论：设区间的长度为$len$，则元素间距小于等于$len$的集合一定至少有一个点被覆盖，元素间距大于$len$的集合要么有一个点被覆盖，要么没有点被覆盖。所以从小到大枚举元素间距，将长度小于等于元素间距的区间加入数据结构，枚举集合中的所有点，查询覆盖每个点的区间数总和。由于已加入的区间最多覆盖一个点，所以计数不重不漏。剩下所有区间一定覆盖了至少一个点，直接加上即可。

容易看出，需要支持的操作是区间修改，单点查询，可用树状数组维护。

代码：(2399ms)

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const int N=3e5+5;
const int M=1e5+5;
int n,m,now;
pair<int,int> p[N];

struct Tree_Array
{
	int c[N];
	int lowbit(int x)
	{
		return x&(-x);
	}
	
	void update(int pos,int add)
	{
		while(pos<=m)
		{
			c[pos]+=add;
			pos+=lowbit(pos);
		}
	}
	
	int query(int pos)
	{
		int ret=0;
		while(pos)
		{
			ret+=c[pos];
			pos-=lowbit(pos);
		}
		return ret;
	}
};
Tree_Array SS;

int cmp(pair<int,int> x,pair<int,int> y)
{
	return x.second-x.first<y.second-y.first;
}
void init()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
		scanf("%d%d",&p[i].first,&p[i].second);
	sort(p+1,p+n+1,cmp);
}

void work()
{
	int i,j,ans;
	for(i=1;i<=m;++i)
	{
		ans=0;
		for(now;now<n&&p[now+1].second-p[now+1].first+1<=i;++now)
			SS.update(p[now+1].first,1),SS.update(p[now+1].second+1,-1);
		for(j=i;j<=m;j+=i) ans+=SS.query(j);
		printf("%d\n",ans+n-now);
	}
}

int main()
{
	init();work();
	return 0;
}


```

---

## 作者：RuSun (赞：8)

[更好的阅读体验](https://rusunoi.github.io/2021/12/07/AT2300/)

[LuoGu: AT2300 [ARC068C] Snuke Line](https://www.luogu.com.cn/problem/AT2300)

[AT: E - Snuke Line](https://atcoder.jp/contests/arc068/tasks/arc068_c)

考虑每一个商品对列车 $d$ 的贡献。对于一个商品在 $l...r$ 区间售卖，如果一个列车可以经过，则存在 $k$ ，使得：
$$
\begin {aligned}
&l \le kd \le r\\
\Longrightarrow & \frac l d \le k \le \frac r d\\
\Longrightarrow & \frac {l - 1} d < k \le \frac r d\\
\end {aligned}
$$
即
$$
\frac {l - 1} d <  \frac r d
$$


- 在 $1...l  - 1$ 区间的列车，可以用数论分块。对于一段区间的每个数 $x$ ，如果每个 $\frac {l - 1} x$ 和 $\frac r d$ 都相等，则这段区间的答案都加 $1$ ，可以用差分维护。
- 对于 $d > r$ 的区间，一定不会有答案。
- 在 $l...r$ 的区间一定有答案，直接在差分数组上加即可。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int n, m, c[N];
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= n; i++)
	{
		scanf("%d%d", &x, &y);
		c[x]++;
		c[y + 1]--;
		x--;
		for (int l = 1, r; l <= x; l = r + 1)
		{
			r = min(x / (x / l), y / (y / l));
			if (x / l < y / l)
			{
				c[l]++;
				c[r + 1]--;
			}
		}
	}
	for (int i = 1, s = c[1]; i <= m; i++, s += c[i])
		printf("%d\n", s);
	return 0;
}
```

---

## 作者：Lynkcat (赞：4)

这里有一种不需要脑子 $O(n\ln n \log n)$ 的做法。

首先枚举 $d$ ，然后抠出所有 $d$ 的倍数以及 $n$：$a_1,a_2,a_3……,a_k,a_{k+1}=n$。

考虑容斥，去算买不到的商品数，那么就是求 

$$\sum_{i=1}^{k}\sum_{j=1}^m 1[a_i<l_j\leq r_j<a_{i+1}]$$

裸的二维数点问题，转化成矩形内求点数直接扫描线拆成四个点做就好了。

有个 $4$ 的常数，不过还是很轻易的通过了本题。而且贼好写。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define IOS ios::sync_with_stdio(false)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
#define int ll
#define N 300005
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,q,s[N],s1[N],sum,x,c[N];
int l,r;
struct node
{
	int id,x,fh;
};
vector<node>G[N];
vector<int>S[N];
int a[N];
inline void update(int x,int y)
{
	while (x<=n) 
	{
		c[x]+=y;
		x+=(x&-x);
	}
}
inline int query(int x)
{
	int res=0;
	while (x)
	{
		res+=c[x];
		x-=(x&-x);
	}
	return res;
}

signed main()
{
	n=read(),q=read();
	swap(n,q);
	for (int i=1;i<=q;i++)
	{
		int l=read(),r=read();
		s[r]++;
		s1[l]++;
		S[l].push_back(r);
	}
	for (int i=1;i<=n;i++) s[i]+=s[i-1],s1[i]+=s1[i-1],a[i]=q;
	writeln(q);
	for (int i=2;i<=n;i++)
	{
		for (int j=0;j<=n;j+=i)
		{
			l=j+1,r=min(n,j+i-1);
			G[l-1].push_back({i,r,-1});
			G[l-1].push_back({i,l-1,1});
			G[r].push_back({i,r,1});
			G[r].push_back({i,l-1,-1});
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (auto u:S[i])
		{
			update(u,1);
		}
		for (auto u:G[i])
		{
			a[u.id]-=u.fh*query(u.x);
		}
	}
	for (int i=2;i<=n;i++) writeln(a[i]);
}
/*
*/



---

## 作者：yzy1 (赞：3)

为啥你们不是主席树、树状数组就是数论分块，发个根号分治做法。

## 简要思路

以 $\sqrt n$ 为分界点进行分治。对于 $d \le \lfloor \sqrt n \rfloor$ 的列车，直接暴力判断每个商品是否能买到。时间复杂度 $O(m\sqrt n)$。对于 $d \ge \lfloor \sqrt n \rfloor$ 的列车，我们可以对于每个商品，判断它能被那些 $d$ 的列车买到。

可以发现，范围在 $[l,r]$ 的商品，可以被 $d \in [l,r] \cup [\lceil l/2 \rceil, \lfloor r/2 \rfloor]\cup [\lceil l/3 \rceil, \lfloor r/3 \rfloor]\cup \cdots \cup [\lceil l/n \rceil, \lfloor r/n \rfloor]$ 的列车买到。由于 $d \le \lfloor \sqrt n \rfloor$ 的列车的答案已在第一部分计算完成，我们仅需计算到 $[l/\lceil \sqrt n \rceil,r/\lceil \sqrt n \rceil]$ 即可。用差分数组记录下每个列车能买到多少种商品，最后统计答案即可。这一部分的时间复杂度同样为 $O(m \sqrt n)$。

## 代码参考

```cpp
int n,m,cnt[N],cf[N],lim,cf[N];

inline void Main(){
  cin>>m>>n;
  lim=sqrt(n);
  while(m--){
    int l,r;cin>>l>>r;
    re(i,lim)cnt[i]+=bool(r/i-(l-1)/i);
    int R=r;
    re(i,n){
      int L=l/i;if(l%i)++L;
      up(L,lim+1),down(R,r/i);
      if(R<lim)break;
      if(L>R)continue;
      ++cf[L],--cf[R+1];
      down(R,L-1);
    }
  }
  re(i,n)cf[i]+=cf[i-1],cnt[i]+=cf[i],cout<<cnt[i]<<'\n';
}
```

---

## 作者：tuliwei (赞：3)

这是一篇平凡的树状数组题解

首先我们发现一个性质：若一个区间的长度大于等于d，那它一定会包含一个d的倍数。  

于是我们把区间按长度排序，设有一个集合S1一开始包含所有区间，从小到大枚举d，如果对于新的一个d，某个区间长度小于d了，就把它从S1中拿出来放在另一个集合S2中。显然S2中的区间只可能包含一个d的倍数。  

考虑建一个树状数组，记录每个数被S2中的区间覆盖了多少次。用树状数组查询所有d的倍数，显然查询结果之和就是S2中包含d的倍数的区间数（因为既不会算重，也不会算漏）将这个值加上S的大小就是最终答案了。

代码
```cpp
#include <bits/stdc++.h>
//#define inf 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define inv(x) Power(x, mod - 2)
#define fi first
#define se second
#define MP make_pair
#define PB push_back
#define N 300005

using namespace std;
typedef pair<int,int> Pair;
typedef long long ll;

const long double Pi = 3.14159265358979323846l;
const int mod = 1e9 + 7;
inline int add(int x, int y) { return (x += y) - (x >= mod ? mod : 0); }
inline void inc(int &x, int y) { (x += y) -= (x >= mod ? mod : 0); }
inline int mul(int x, int y) { return 1ll * x * y % mod; }
inline int Power(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1) res = mul(res, x);
		x = mul(x, x), y >>= 1;
	} return res;
}

template <class T> inline T	input() {
	T x; char ch; while (!isdigit(ch = getchar()));
	for (x = ch ^ 48; isdigit(ch = getchar()); x = x * 10 + (ch ^ 48));
	return x;
}

template <class T> inline void chkmin(T &x, T y) { x = x < y ? x : y; }
template <class T> inline void chkmax(T &x, T y) { x = x > y ? x : y; }

struct {
	inline operator int () { return input<int>(); }
	inline operator long long () { return input<long long>(); }
	template <class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

int n, m;
int l[N], r[N], now;
Pair a[N];

inline bool cmp(Pair x, Pair y) {
	return (x.se - x.fi) > (y.se - y.fi);
}

struct BIT {
	int cnt[N];
	void Add(int x, int val) { for (; x < N; x += x & -x) cnt[x] += val; }
	int query(int x) { int res = 0; for (; x; x ^= x & -x) res += cnt[x]; return res; }
	void add(int l, int r) { Add(l, 1), Add(r + 1, -1); }
}bit;

int main() {

	read(n, m);
	for (int i = 1, l, r; i <= n; ++i)
		read(l, r), a[i] = make_pair(l, r);

	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; ++i)
		l[i] = a[i].fi, r[i] = a[i].se;
	now = n;

	for (int d = 1; d <= m; ++d) {
		while (now && r[now] - l[now] + 1 < d)
			bit.add(l[now], r[now]), --now;
		int ans = now;
		for (int i = 0; i <= m; i += d)
			ans += bit.query(i);
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：zjc5 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT_arc068_c)

**思路：**

如果要保证区间 $[l_i,r_i]$ 只有不超过一个 $d$ 的倍数，那么区间长度 $r_i-l_i+1$ 要小于 $d$。

如果 $r_i-l_i+1$ 要大于 $d$，那么其中一定有一个 $d$ 的倍数。

那么对于每个 $d$，只要保证所有 $r_i-l_i+1\leqslant d$ 的区间已经打好标记，然后把每一个 $d$ 的倍数位置上的数求和，再加上一定包含 $d$ 的倍数的区间个数就好了。

所以把所有区间按 $r_i-l_i+1$ 从小到大排序，依次枚举出所有 $r_i-l_i+1\leqslant d$ 的区间（不重复），打好标记。

给区间打标记，用到区间修改；查找所有 $d$ 的倍数位置上的数，用到单点查询。于是这题就可以用树状数组来解决。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sum,j=1;
int f[100010],c[100010];
int lowbit(int x){
	return (x&(-x));
}
int que(int q){
	int tmp=0;
	while(q){
		tmp+=c[q];
		q-=lowbit(q);
	}
	return tmp;
}
void add(int q,int x){
	while(q<=m){
		c[q]+=x;
		q+=lowbit(q);
	}
}
struct node{
	int l,r;
}a[300010];
bool cmp(node a,node b){
	return a.r-a.l<b.r-b.l;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].l,&a[i].r);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=m;i++){
		for(;j<=n&&a[j].r-a[j].l+1<i;j++){
			add(a[j].l,1);
			add(a[j].r+1,-1);
		}
		sum=0;
		for(int k=i;k<=m;k+=i)
			sum+=que(k);
		printf("%d\n",sum+n-j+1);//因为j在循环的最后多加了1，所以在这里加回去。
	}
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：1)

# 题目大意

有一趟列车有 $m+1$ 个车站，从 $0$ 到 $m$ 编号。有 $n$ 种商品，第 $i$ 种只在编号 $[l_i,r_i]$ 的车站出售。一辆列车有一个预设好的系数 $d$，从 $0$ 出发，只会在 $d$ 的倍数车站停车。对于 $d$ 从 $1$ 到 $M$ 的列车，求最多能买到多少种商品。

# 题目分析

设当前系数为 $d$，则可以发现:

+ 一类区间：对于所有满足 $r_i-l_i+1\gt d$ 的区间，列车都至少会经过一次。

+ 二类区间：对于所有满足 $r_i-l_i+1\le d$ 的区间，列车至多只会经过一次。

我们将所有区间按照区间长度由小到大排序，用一个树状数组记录每一个位置被二类区间覆盖了多少次（差分即可），答案即为所有 $d\cdot k$ 位置的前缀和之和。

# 代码

```cpp
//2022/4/25
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 3e5 + 5;
struct Node {
	int l,r;
} node[N];
int n,m,idx;
struct BIT {
	int tr[N];
	#define lowbit(x) (x & -x)
	inline void update(int x,int k) {
		for (;x <= m;x += lowbit(x)) tr[x] += k;
	}
	inline int query(int x) {
		int res = 0;
		for (;x;x -= lowbit(x)) res += tr[x];
		return res;
	}
	#undef lowbit
} bit;
inline bool cmp(Node x,Node y) {
	return x.r - x.l < y.r - y.l;
}
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	n = read(),m = read();
	for (register int i = 1;i <= n; ++ i) {
		node[i].l = read(),node[i].r = read();
	}
	std::sort(node + 1,node + n + 1,cmp);//按区间长度从小到大排序
	idx = 1;
	for (register int i = 1;i <= m; ++ i) {
		while (idx <= n && node[idx].r - node[idx].l + 1 <= i) {
			bit.update(node[idx].l,1),bit.update(node[idx].r + 1,-1);
			idx ++;
		}
		int sum = 0;
		for (register int j = i;j <= m;j += i) {
			sum += bit.query(j);
		}
		printf("%d\n",sum + n - idx + 1);
	}
	
	return 0;
}
```

---

## 作者：Prean (赞：1)

两种做法都说一说吧。。。

题意很明确。

## 1.数论分块

对于一个 $ d $ 和给定的 $ (l,r) $，$ (l,r) $ 对其造成贡献的条件很明显是 $ \lfloor \frac {l-1} d \rfloor \ne \lfloor \frac r d \rfloor $。

然后一个数论分块就没了。

只跑了 4s 还是挺离谱的，应该吊打了大部分数论分块。
```cpp
#include<cstdio>
#include<cctype>
typedef unsigned ui;
const ui M=1e5+5;
ui n,m,s[M];double inv[M];
inline void write(ui n){
	static char s[10];ui top(0);while(s[++top]=n%10^48,n/=10);while(putchar(s[top--]),top);
}
inline ui read(){
	ui n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;
}
inline ui min(const ui&a,const ui&b){
	return a>b?b:a;
}
signed main(){
	ui i,L,R,l,r,x,y;m=read();n=read();
	for(i=1;i<=n;++i)inv[i]=1./i+1e-15;
	while(m--){
		l=read()-1;r=read();
		for(L=1;L*L<=r&&L<=l;++L)if(ui(l*inv[L])^ui(r*inv[L]))++s[L],--s[L+1];
		for(x=l*inv[L],y=r*inv[L];L<=l;L=R+1){
			if(x*L>l)--x;if(y*L>r)--y;R=min(ui(l*inv[x]),ui(r*inv[y]));
			if(x^y)++s[L],--s[R+1];
		}
		++s[l+1];--s[r+1];
	}
	for(i=1;i<=n;++i)write(s[i]+=s[i-1]),putchar(10);
}
```
## 2.树状数组
只能说这个数据分类实在是太妙了 Orz

数据分类。

1. 区间长度不小于 $ d $

贡献很明显是 $ 1 $。

2. 区间长度小于 $ d $

我们直接对这些区间进行区间修改，然后直接查询 $ d $ 的倍数，每个区间只可能对答案贡献最多一次。
```cpp
#include<algorithm>
#include<cstdio>
#include<cctype>
typedef unsigned ui;
const ui M=1e5+5;
ui n,m,s[M],CB[M],id[M*3],l[M*3],r[M*3],d[M*3],BIT[M*3];double inv[M];
inline void write(ui n){
	static char s[10];ui top(0);while(s[++top]=n%10^48,n/=10);while(putchar(s[top--]),top);
}
inline ui read(){
	ui n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;
}
inline void Add(ui x,const ui&val){
	while(x<=n)BIT[x]+=val,x+=x&-x;
}
inline ui Query(ui x){
	ui ans(0);
	while(x>=1)ans+=BIT[x],x^=x&-x;
	return ans;
}
signed main(){
	ui i,j,ans,now;m=read();n=read();now=m;
	for(i=1;i<=m;++i)l[i]=read(),r[i]=read(),++CB[d[i]=r[i]-l[i]+1],id[i]=i;
	for(i=n;i>=1;--i)CB[i]+=CB[i+1];for(i=m;i>=1;--i)id[CB[d[i]]--]=i;
	for(i=1;i<=n;++i){
		while(d[id[now]]<i&&now)Add(l[id[now]],1),Add(r[id[now]]+1,-1),--now;ans=now;
		for(j=i;j<=n;j+=i)ans+=Query(j);write(ans);putchar(10);
	}
}
```
成功杀到最优解。

---

## 作者：2016gdgzoi581 (赞：1)

对于某个$d$，考虑何时一个区间能够存在$d$的倍数,易得对于区间$[l ,r]$,若$\lfloor \frac{l-1}{d} \rfloor<\lfloor \frac{r}{d} \rfloor$,则该区间存在$d$的倍数

于是我们可以将区间按$l$排序,对于每个$d$,枚举$t=\lfloor \frac{l-1}{d} \rfloor$,用倍增求出可能合法区间的下标范围，再用可持久化线段树求出实际合法区间的数量(即$d \times (t+1) \le r_i \le d \times (t+2) -1$ )

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,ind;
struct node{
    int ls,rs,sum;
}tr[20500010];
void pushup(int o){
    tr[o].sum=tr[tr[o].ls].sum+tr[tr[o].rs].sum;
}
void build(int &o,int l,int r){
    o=++ind;
    if(r==l)return;
    build(tr[o].ls,l,(l+r)/2);
    build(tr[o].rs,(l+r)/2+1,r);
}
void update(int &_new,int old,int l,int r,int pos){
    _new=++ind;
    tr[_new]=tr[old];
    tr[_new].sum++;
    if(l==r)return;
    int mid=(l+r)/2;
    if(pos<=mid)update(tr[_new].ls,tr[old].ls,l,mid,pos);
    else update(tr[_new].rs,tr[old].rs,mid+1,r,pos);
    pushup(_new);
}
int query(int _new,int old,int l,int r,int x,int y){
    if(x>r||y<l)return 0;
    if(x<=l&&y>=r)return tr[_new].sum-tr[old].sum;
    int mid=(l+r)/2;
    if(y<=mid)return query(tr[_new].ls,tr[old].ls,l,mid,x,y);
    else if(x>mid)return query(tr[_new].rs,tr[old].rs,mid+1,r,x,y);
    else return query(tr[_new].ls,tr[old].ls,l,mid,x,mid)+query(tr[_new].rs,tr[old].rs,mid+1,r,mid+1,y);
}
int rt[551000];
struct data{
    int l,r;
    friend bool operator <(data a,data b){
        return a.l==b.l?a.r<b.r:a.l<b.l;
    }
}item[300100];
void solve(int d){
    int res=0,now=0,pre=0;
    for(int i=1;i*d<=m;++i){
        int k=0;
        for(int j=18;j>=0;--j){
            if((1<<j)>n)continue;
            if((k+(1<<j))<=n&&(item[k+(1<<j)].l-1)/d<i)k+=(1<<j);
        }
        now=k;
        if(now>n)now=n;
        int t=(item[now].l-1)/d;
        res+=query(rt[now],rt[pre],1,m,d*(t+1),m);
        pre=now;
    }
    printf("%d\n",res);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%d%d",&item[i].l,&item[i].r);
    }
    sort(item+1,item+n+1);
    build(rt[0],1,n);
    for(int i=1;i<=n;++i){
        update(rt[i],rt[i-1],1,m,item[i].r);
    }
    for(int d=1;d<=m;++d){
        solve(d);
    }
}
```
~~常数极大qwq~~

---

## 作者：小木虫 (赞：1)

### Preface  
其实我认为这道题的主要难点是找到一个看似暴力的好解法...  
### Problem  
有 $n$ 个区间，从 0 开始的 $m+1$ 个连续车站，有 $m$ 列列车，第 $i$ 列列车只在 $i$ 的倍数处停留，问 $m$ 列列车分别能沾到多少个区间？  
### Solution  
拿到这题其实我们非常的不解，因为统计真的太难了，毕竟直接暴力模拟列车和列车走过的车站的复杂度太高了....吗？  
其实我们还不是很清楚，这个东西其实看上去很大，但实际上是很小的。  
形式化地说，暴力枚举列车行驶的复杂度是：  

$\sum _{i=1}^m \frac{n}{i}$  

具体的我是不会证的，但是你拿程序跑一下去计算会发现这个数字是 $n \log n$ 级别的玩意，是支持暴力枚举的。  

那么接下来我们终于可以放心地去解决这个问题了，我们发现难点在于一个区间可能会被统计多次，但是实际上区间大小大于目前列车的速度的区间都会且仅会被统计一次，其它的区间仅可能被统计 0 或 1 次，于是我们把所有的区间按大小排序，然后顺序加入区间，没有被加入的就是固定的 1 次统计。  

接下来我们要写一个数据结构支持区间加，单点查，老样子我们不想写线段树，这个时候我们掏出了法宝：树状数组维护差分数组！然后树状数组就支持了区间加单点查。  

code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,m;int tree[N];
struct Line{int l,r;}Q[N];
bool cmp(Line a,Line b){return (a.r-a.l)<(b.r-b.l);}
int lowbit(int x){return x&-x;}int res[N];
void update(int x,int y){while(x<=m){tree[x]+=y;x+=lowbit(x);}}
int query(int x){int res=0;while(x!=0){res+=tree[x];x-=lowbit(x);}return res;}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m;for(int i=1;i<=n;i++)cin>>Q[i].l>>Q[i].r;
	sort(Q+1,Q+1+n,cmp);int now=n;int p=0;
	for(int i=1;i<=m;i++){
		while(p<n&&(Q[p+1].r-Q[p+1].l+1)<=i){p++;update(Q[p].l,1);update(Q[p].r+1,-1);}
		res[i]+=n-p;for(int j=0;j<=m;j+=i)res[i]+=query(j);
	}
	for(int i=1;i<=m;i++)cout<<res[i]<<endl;
	return 0;
}
```


---

## 作者：_Vix_ (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_arc068_c)

---

## 分析

我们考虑，对于每一种商品，它对哪些车站有贡献。于是有：

$$l_i \le kd \le r_i \iff \dfrac{l_i-1}{d} < \dfrac{r_i}{d}$$

转化为整除分块，并且用差分数组维护一下，可以 $O(N \sqrt M)$ 解决问题。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, m, l, r, d[N];

void work(int n, int m) {
	for (int l = 1, r; l <= n; l = r + 1) {
		r = min(n / (n / l), m / (m / l));
		if (n / r < m / r) d[l]++, d[r + 1]--;
	}
	d[n + 1]++, d[m + 1]--;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &l, &r);
		work(l - 1, r);
	}
	for (int i = 1; i <= m; i++) d[i] += d[i - 1];
	for (int i = 1; i <= m; i++) printf("%d\n", d[i]);
	return 0;
}
```


---

## 作者：mmdxmakioi (赞：0)

简单题。

对线段按左端点排序，然后从 $1$ 到 $m$，对于每一个点加入左端点是这个点的线段，把他们都插入进主席树。

然后典中典的结论就是调和级数是 $\log$ 级别的。

考虑直接扫加算。

假设当前列车标号为 $i$，那么我们发现对于一个点 $j$ 算有几条线段覆盖他不会算重复的方法就是把左端点在这个点前，然后右端点在 $j$ 到 $j+i-1$ 的线段算一遍。

时间复杂度是 $O(m \log m \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
int n,m;
int cnt;
vector<int> G[N];
int num;
int p2[N];
int p[N]; 
struct node
{
	int lc,rc,val;
}tree[N*100];
int build(int l,int r)
{
	int rt=++cnt;
	tree[rt].val=0;
	if(l==r)return rt;
	int mid=(l+r)/2;
	tree[rt].lc=build(l,mid);
	tree[rt].rc=build(mid+1,r);
	return rt;
}
int update(int pre,int l,int r,int x,int y)
{
	int rt=++cnt;
	tree[rt]=tree[pre];
	tree[rt].val+=y;
	if(l==r)return rt;
	int mid=(l+r)/2;
	if(x<=mid)
	tree[rt].lc=update(tree[pre].lc,l,mid,x,y);
	else
	tree[rt].rc=update(tree[pre].rc,mid+1,r,x,y);
	return rt; 
}
int query(int u,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
	{
		return tree[u].val;
	}
	int rt=0;
	int mid=(l+r)/2;
	if(x<=mid)
	rt+=query(tree[u].lc,l,mid,x,y);
	if(mid<y)
	rt+=query(tree[u].rc,mid+1,r,x,y);
	return rt;
}
int main()
{
	int i,j;
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		int l,r;
		cin>>l>>r;
		G[l].push_back(r);
	}
	p2[0]=build(1,m);
	p[0]=p2[0];
	for(i=1;i<=m;i++)
	{
		vector<int>::iterator it;
		for(it=G[i].begin();it!=G[i].end();it++)
		{
			p2[num+1]=update(p2[num],1,m,*it,1);
			++num;
		}
		p[i]=p2[num];
	}
	for(i=1;i<=m;i++)
	{
		int dq=0;
		for(j=i;j<=m;j+=i)
		{
			dq+=query(p[j],1,m,j,min(j+i-1,m));
		}
		cout<<dq<<'\n';
	}
}
```


---

