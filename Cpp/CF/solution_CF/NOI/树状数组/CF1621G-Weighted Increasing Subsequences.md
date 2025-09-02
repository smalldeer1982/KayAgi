# Weighted Increasing Subsequences

## 题目描述

给定一个长度为 $n$ 的整数序列 $a_1, a_2, \ldots, a_n$。

长度为 $k$ 的下标序列 $i_1 < i_2 < \ldots < i_k$ 表示原序列 $a$ 的一个子序列 $a_{i_1}, a_{i_2}, \ldots, a_{i_k}$。

如果对于每个 $1 \leq j < k$ 都有 $a_{i_j} < a_{i_{j+1}}$，则称该子序列为递增子序列。

对于序列 $a$ 的长度为 $k$ 的递增子序列 $a_{i_1}, a_{i_2}, \ldots, a_{i_k}$，其权值定义为满足以下条件的 $1 \leq j \leq k$ 的个数：存在下标 $i_k < x \leq n$，且 $a_x > a_{i_j}$。

例如，若 $a = [6, 4, 8, 6, 5]$，下标序列 $i = [2, 4]$ 表示递增子序列 $[4, 6]$。该递增子序列的权值为 $1$，因为对于 $j = 1$，存在 $x = 5$ 使得 $a_5 = 5 > a_{i_1} = 4$，但对于 $j = 2$，不存在这样的 $x$。

请你求出所有递增子序列的权值之和，结果对 $10^9+7$ 取模。

## 说明/提示

在第一个测试用例中，以下递增子序列的权值不为零：

- $[a_1] = [6]$ 的权值为 $1$。
- $[a_2] = [4]$ 的权值为 $1$。
- $[a_2, a_3] = [4, 8]$ 的权值为 $1$。
- $[a_2, a_4] = [4, 6]$ 的权值为 $1$。

递增子序列的权值之和为 $4$。

在第二个测试用例中，有 $7$ 个递增子序列权值不为零：$3$ 个权值为 $1$，$3$ 个权值为 $2$，$1$ 个权值为 $3$。权值之和为 $12$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
5
6 4 8 6 5
4
1 2 3 4
3
3 2 2
4
4 5 6 5```

### 输出

```
4
12
0
6```

# 题解

## 作者：gyh20 (赞：17)

算每个序列的贡献和是不好算的，可以算每个位置有贡献的次数。

容易发现，对于一个 $x$，令 $y$ 为最大的满足 $a_y>a_x$ 的位置，容易发现，$x$ 有贡献当且仅当 $x$ 所在的这个子序列的右端点 $<y$。

我们同时可以轻易的发现，$a_y$ 是一个严格后缀最大值。

至此，我们得出一个 $O(n^2\log n)$ 的做法，枚举一个 $x$，再求出 $x\sim y-1$ 中包含 $x$ 的上升子序列的个数，用树状数组优化即可。

继续令 $y$ 为最大的满足 $a_y>a_x$ 的位置。

进一步优化需要考虑题目性质，我们先假设所有包含 $x$ 的子序列都有贡献，再减去没有贡献的情况，可以发现，没有贡献当且仅当子序列以 $y$ 结尾，因为结尾 $<y$ 一定有贡献，而结尾大于 $y$ 的话就不满足 $y$ 为最大的满足 $a_y>a_x$ 的位置。

于是我们把问题转为了计数所有以 $x$ 开头以 $y$ 结尾的上升子序列，下文称之为“询问”。

进一步发现，令 $z$ 为满足 $z>y$，且 $a_z$ 最大的位置，对于 $y$ 同一个 $y$ 对应的所有 $x$，都满足 $a_z\leq a_x<a_y$，也就是说，对于同一个 $y$，对应的 $x$ 的值域是在一个区间的，由于是上升子序列计数，不在这个区间内的数是一定没用的。

所以我们枚举一个 $y$，将所有满足 $a_z\leq a_x<a_y$ 的 $x$ 保留，计算上升子序列个数，由于每个 $x$ 只会满足一个区间的限制，总复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
const int M=1e9+7;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x){return x>=M?x-M:x;}
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
int c[200002],b[200002],N,f[200002],ans,g[200002],O[200002];
inline void addd(re int x,re int y){
	for(;x<=N;x+=x&(-x))add(c[x],y);
}
inline int ask(re int x,re int s=0){
	for(;x;x^=x&(-x))add(s,c[x]);
	return s;
}
inline void Get(vector<int>&a,re int x){
	int n=a.size()-1;N=n;
	for(re int i=1;i<=n;++i)b[i]=a[i];
	sort(b+1,b+n+1);
	for(re int i=1;i<=n;++i)a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	for(re int i=n;i;--i){
		f[i]=Mod(ask(n)-ask(a[i])+M);
		if(x==1||i==n)add(f[i],1);
		addd(a[i],f[i]),add(ans,1ll*x*f[i]%M*g[O[i]]%M);
	}
	for(re int i=1;i<=n;++i)addd(a[i],M-f[i]);
}
int t,n,m,a[200002],A,B,stk[200002],tp,v[200002],p[200002];
char s[1000002];
inline bool cmp(re int x,re int y){
	return a[x]==a[y]?x>y:a[x]<a[y];
}
int main(){
	t=read();
	while(t--){
		n=read();
		vector<int>tmp;ans=0;
		for(re int i=1;i<=n;++i)a[i]=read(),p[i]=i,v[i]=0,b[i]=a[i],O[i]=i;
		sort(b+1,b+n+1);
		for(re int i=1;i<=n;++i)a[i]=lower_bound(b+1,b+n+1,a[i])-b;
		N=n;
		for(re int i=1;i<=n;++i){
			g[i]=ask(a[i]-1),add(g[i],1);
			addd(a[i],g[i]);
		}
		for(re int i=1;i<=n;++i)addd(a[i],M-g[i]);
		for(re int i=0;i<=n;++i)tmp.push_back(a[i]);
		re int mx=0;
		for(re int i=n;i;--i){
			if(a[i]==mx)add(ans,M-g[i]);
			mx=max(mx,a[i]);
		}
		Get(tmp,1);
		tp=0;
		stk[tp=1]=n;
		for(re int i=n-1;i;--i)if(a[i]>a[stk[tp]])stk[++tp]=i;
		sort(p+1,p+n+1,cmp);
		for(re int i=1;i<=tp;++i)v[stk[i]]=1;
		for(re int i=1,j;i<=n;i=j+1){
			int tot=0;j=i;
			while(1){
				O[++tot]=p[j];
				if(v[p[j]])break;
				++j;
				if(j>n){
					break;
				}
			}
			if(j>n)break;
			tmp.clear();tmp.push_back(0);
			sort(O+1,O+tot+1);
			while(!v[O[tot]])--tot;
			for(re int k=1;k<=tot;++k)tmp.push_back(a[O[k]]);
			Get(tmp,M-1);
		}
		printf("%d\n",ans);
	}
}
 
```


---

## 作者：feecle6418 (赞：11)

~~这个标题取得好中二啊。~~

看到这种限制很奇怪而且跟大小相关的题，就想试试在逆排列里考虑。

首先把输入转化为排列，离散化，如果有相同的，认为后面的更小（因为要求严格上升）。

**关键步骤**：对于这个排列 $p$，设其逆排列为 $q$。

然后把贡献的条件重新说一遍。

- “$p$ 的上升子序列”，一一对应 $q$ 的上升子序列。
- “存在 $j$ 在这个上升子序列的最后一个元素 $k$ 之后，$a_j>a_i$”，对应，存在 $q_{a_j}>q_{a_k}$，$a_j>a_i$。直接在 $q$ 里考虑，就是存在 $q_{j}>q_{k}$，$j>i$。显然，这等价于 $k$ 不是 $q$ 的后缀最大值。

我们再把题目说一遍：

- 对于 $q$ 中的第 $i$ 个值，他在某个上升子序列里面有贡献，当且仅当这个上升子序列的结尾 $k$ 不是 $q$ 的后缀最大值。

做法就很显然了，枚举每个后缀最大值把它管辖的东西减掉即可。

可以发现，这个做法完全没有观察任何性质，仅仅凭着“在逆排列上考虑”，然后复述一遍问题就把问题转化得很可做。

---

## 作者：FZzzz (赞：6)

首先离散化，对于相等的位置要保证后面比前面小，这样将序列转化为排列。

显然考虑每个位置对答案的贡献次数，即在多少个上升子序列中可以作为题面中的 $i_j$。设当前位置为 $x$，最后一个比它大的位置为 $y$，那么 $x$ 能贡献到的上升子序列要包含 $x$，且最后一个位置在 $y$ 之前。

这即是以 $x$ 结尾的上升子序列个数乘上以 $x$ 开头且结尾在 $y$ 之前的上升子序列个数。前者直接 dp 求出，后者考虑到 $y$ 之后的所有位置都比 $x$ 小，则等于以 $x$ 开头不以 $y$ 结尾的上升子序列个数。正难则反，考虑求以 $x$ 开头以 $y$ 结尾的上升子序列个数。

发现 $y$ 必定是后缀最大值。设后缀最大值有 $k$ 个，从后往前是 $s_1$ 到 $s_k$，且 $y=s_i$，那么 $y$ 可以在 $s$ 中二分求出。并且我们知道，$a_{s_{i-1}}<a_x<a_{s_i}$，那么上述上升子序列中的所有数一定都在 $(a_{s_{i-1}},a_{s_i})$。我们可以对于每个 $i$ 将这些数拿出来单独 dp，总时间复杂度即为 $O(n\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=2e5+5;
int n,a[maxn],ord[maxn],s[maxn],tp;
const ll mod=1e9+7;
ll c[maxn];
inline int lowbit(int x){
	return x&-x;
}
void modify(int x,ll k){
	while(x<=n){
		c[x]=(c[x]+k)%mod;
		x+=lowbit(x);
	}
}
ll query(int x){
	ll s=0;
	while(x){
		s=(s+c[x])%mod;
		x-=lowbit(x);
	}
	return s;
}
ll f[maxn],g[maxn],h[maxn];
vector<int> vec[maxn];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	int T=readint();
	while(T--){
		n=readint();
		for(int i=1;i<=n;i++) a[i]=readint();
		for(int i=1;i<=n;i++) ord[i]=i;
		sort(ord+1,ord+n+1,[](int x,int y){
			if(a[x]!=a[y]) return a[x]<a[y];
			return x>y;
		});
		for(int i=1;i<=n;i++) a[ord[i]]=i;
		tp=0;
		for(int i=n;i>0;i--)
			if(a[i]>a[s[tp]]) s[++tp]=i;
		for(int i=1;i<=n;i++){
			f[i]=(query(a[i])+1)%mod;
			modify(a[i],f[i]);
		}
		for(int i=1;i<=n;i++) c[i]=0;
		for(int i=n;i>0;i--){
			g[i]=(query(n-a[i]+1)+1)%mod;
			modify(n-a[i]+1,g[i]);
		}
		for(int i=1;i<=n;i++) c[i]=0;
		for(int i=1;i<=tp;i++)
			vector<int>().swap(vec[i]);
		for(int i=n;i>0;i--){
			int l=1,r=tp;
			while(l<r){
				int mid=l+(r-l)/2;
				if(a[i]<=a[s[mid]]) r=mid;
				else l=mid+1;
			}
			if(s[r]!=i) vec[r].push_back(i);
		}
		for(int i=1;i<=tp;i++){
			modify(n-a[s[i]]+1,h[s[i]]=1);
			for(int j:vec[i]){
				h[j]=query(n-a[j]+1);
				modify(n-a[j]+1,h[j]);
			}
			for(int j:vec[i])
				modify(n-a[j]+1,(mod-h[j])%mod);
			modify(n-a[s[i]]+1,mod-1);
		}
		ll ans=0;
		for(int i=1;i<=n;i++)
			ans=(ans+(g[i]-h[i]+mod)%mod*f[i]%mod)%mod;
		printf("%lld\n",ans);
	}
	#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
	#endif
	return 0;
}
```

---

## 作者：D_F_S (赞：3)

## Solution：
考虑有哪些点能成为题意中的 $x$，且无法被更优的替代。易知一定是那些取到后缀 $\max$ 的位置，将这些点称为关键点，可用这些点将原序列按权值分层转移。
![](https://cdn.luogu.com.cn/upload/image_hosting/xa1458rr.png)
(图中横坐标为点的编号，纵坐标为权值）

对于一个关键点 $x$ 与关键点 $y$ 之间的非关键点 $u$，$u$ 能对包含它的一条 上升子序列 产生 1 的权值当且仅当 上升子序列 不以 $x$ 结尾。

设 $f_u$ 表示以 $u$ 为开头的 上升子序列 的个数，$g_u$ 表示以 $u$ 为开头的 上升子序列 的总权值。$f$ 的转移是简单的：
$$
f_u=1+\sum_{i>u,a_i>a_u}f_i
$$
按权值从大到小排序后用树状数组维护横坐标为下标的后缀和即可。

考虑 $g$ 的转移，若没有不能以 $x$ 结尾的限制，则直接是：
$$
g_u=f_u+\sum_{i>u,a_i>a_u}g_i
$$
把 $x$ 的限制考虑进来，只需要不把 $f_x$ 与 $g_x$ 加入树状数组，就不会统计以 $x$ 结尾的子序列了。

总结一下，对于 $x$ 与 $y$ 之间的所有点，进行两次从上到下的转移，第一次不加入 $x$，算出正确的 $g$，第二次加入 $x$，算出正确的 $f$，$x$ 上面的点则一直在树状数组当中，总复杂度为 $O(n\log n)$。

*p.s. 注意各种权值相等时的细节处理。*

## Code：
```cpp
#include<bits/stdc++.h>
#define inl inline
using namespace std;
const int N=2e5+5,P=1e9+7;
inl int Ad(int x,int y) {return x+y>=P?x+y-P:x+y; }
struct A
{
	int x,y;
	inl A operator +(A t) {return {Ad(x,t.x),Ad(y,t.y)}; }
}a[N],b[N],f[N],sz[N];
int n,m;
inl int Read()
{
	int s=0; char c; while(!isdigit(c=getchar()));
	for(;isdigit(c);c=getchar()) s=s*10+c-'0'; return s;
}
inl A Ask(int p) {A t={0,0}; for(;p<=n;p+=p&-p) t=t+sz[p]; return t; }
inl void Add(int p,A t) {for(;p;p-=p&-p) sz[p]=sz[p]+t; }
int main()
{
	for(int T=Read();T--;)
	{
		n=Read(); m=0;
		for(int i=1;i<=n;++i) a[i]={i,Read()}, sz[i]={0,0};
		for(int i=n;i>=1;--i) if(a[i].y>=b[m].y) b[++m]=a[i];	// 关键点 
		sort(a+1,a+n+1,[](A x,A y)->bool{return x.y==y.y?x.x<y.x:x.y>y.y; });
		for(int i=m,l=2,r=1;i;--i,l=r+2)
		{
			while(r<n&&a[r+1].x!=b[i-1].x) ++r;		// 分层，l ~ r 均为非关键点 
			for(int j=l;j<=r;++j)
			{
				f[j]=Ask(a[j].x+1);
				++f[j].x;
				f[j].y=Ad(f[j].y,f[j].x);		// 第一次转移出 g 
				Add(a[j].x,f[j]);
			}
			for(int j=l;j<=r;++j) Add(a[j].x,{P-f[j].x,0});	// 撤销 
			Add(b[i].x,{1,0});		// 加入 x 
			for(int j=l;j<=r;++j)
			{
				f[j].x=Ask(a[j].x+1).x+1;		// 第二次转移出 f 
				Add(a[j].x,{f[j].x,0});
			}
		}
		printf("%d\n",Ask(1).y);
	}
	return 0;
}
```


---

## 作者：CXY07 (赞：3)

> 题目链接：[CF1621G Weighted Increasing Subsequences](https://www.luogu.com.cn/problem/CF1621G)

> **本题解同步发布于 [My Blog](http://www.cxy07.blog/index.php/archives/443/)**

题意：

> 给定长度为 $n$ 的序列 $\{a_n\}$，对于其一个长度为 $k$ 的上升子序列 $a_{i_1},a_{i_2}\cdots a_{i_k}$ 定义其权值为满足 $j\in[1,k]$，存在一个 $x\in(i_k,n]$ 使得 $a_x>a_{i_j}$ 的 $j$ 的个数。

> 计算所有上升子序列的权值和。

> $1\le n\le 2\times 10^5, 1\le a_i\le 10^9$。

首先将序列离散化，计算每个上升子序列的权值是困难的，我们考虑每个位置 $a_p$ 的贡献。

对于一个 $a_p$，$i_k$ 最远可以到哪里，使得存在一个 $x\in(i_k,n]$ 满足 $a_x>a_i$？容易发现，若设 $r_p$ 表示最靠右的满足 $a_{r_p}>a_p$ 的下标，则 $i_k<r_p$。注意到 $a_{r_p}$ 必然在后缀单调栈上。

于是，对于每一个 $p$，我们需要计算 “经过 $p$，且最后一个元素在 $r_p$ 之前” 的上升子序列个数。容斥成 “经过 $p$，且最后一个元素下标 $\in[r_p,n]$” 的上升子序列个数。

本人做到这里的时候被卡住了，“经过定点，结尾在一段后缀的上升子序列个数” 看起来不是很可做。

继续观察性质，注意到我们设 $r_p$ 是**最靠右**的满足 $a_{r_p}>a_p$ 的位置，这意味着 $\forall i\in(r_p, n],\ a_i\le a_p$。说明，任意经过 $p$ 的上升子序列，都不可能在 $(r_p, n]$ 结束。

于是 “经过 $p$，且最后一个元素下标 $\in[r_p,n]$” 的限制就转变成了 “经过 $p$，且最后一个元素下标 $=r_p$”，相当于钦定了一个定点，钦定了结尾元素。

如何计算这样的子序列个数？首先肯定要把子序列拆成 $p$ 之前、之后。前面是好算的，$p$ 之后的部分，就相当于：

“第一个元素下标是 $p$，最后一个元素下标是 $r_p$” 的上升子序列个数。

接下来我的处理和官方的题解有一些区别：由于 $r_p$ 是最靠右的满足条件的下标，所以任意从 $p$ 开始延申的上升子序列，其结尾下标必然 $\le r_p$。

于是，我们只需要维护 “从 $p$ 开始，以最远的可行位置结尾” 的方案数即可，容易使用树状数组维护。

时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
//Code By CXY07 - It's My Fiesta.
#include<bits/stdc++.h>
using namespace std;

//#define FILE
//#define int long long
#define randint(l, r) (rand() % ((r) - (l) + 1) + (l))
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define popc(x) __builtin_popcount(x)
#define inv(x) qpow((x), mod - 2)
#define lowbit(x) ((x) & (-(x)))
#define ull unsigned long long
#define pii pair<int, int>
#define LL long long
#define mp make_pair
#define pb push_back
#define scd second
#define vec vector
#define fst first
#define endl '\n'
#define y1 _y1

const int MAXN = 2e5 + 10;
const int INF = 2e9;
const double eps = 1e-6;
const double PI = acos(-1);
const int mod = 1e9 + 7;
//const int mod = 998244353;
//const int G = 3;
//const int base = 131;

int T, n, m;
int a[MAXN], FT[MAXN], pre[MAXN], suf[MAXN];
int mx[MAXN], mxv[MAXN];
LL Ans;
vec<int> v;

template<typename T> inline bool read(T &a) {
	a = 0; char c = getchar(); int f = 1;
	while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
	while(c >= '0' && c <= '9') { a = a * 10 + (c ^ 48); c = getchar(); }
	return a *= f, true;
}

template<typename A, typename ...B>
inline bool read(A &x, B &...y) { return read(x) && read(y...); }

void add1(int x, int v) { for(; x <= n; x += lowbit(x)) (FT[x] += v) %= mod; }
int ask1(int x) { int res = 0; { for(; x; x -= lowbit(x)) (res += FT[x]) %= mod; } return res; }

void add2(int x, pii v) {
	for(; x; x -= lowbit(x)) {
		if(mx[x] < v.fst) mx[x] = v.fst, mxv[x] = 0;
		if(mx[x] == v.fst) (mxv[x] += v.scd) %= mod;
	}
}

pii ask2(int x) {
	int _mx = 0, _mxv = 0;
	for(; x <= n; x += lowbit(x)) {
		if(_mx < mx[x]) _mx = mx[x], _mxv = 0;
		if(_mx == mx[x]) (_mxv += mxv[x]) %= mod;
	}
	return mp(_mx, _mxv);
}

void solve() {
	read(n); v.clear(); Ans = 0;
	for(int i = 1; i <= n; ++i) read(a[i]), v.pb(a[i]);
	for(int i = 1; i <= n; ++i) FT[i] = mx[i] = mxv[i] = 0;
	sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
	for(int i = 1; i <= n; ++i) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
	for(int i = 1; i <= n; ++i) add1(a[i], pre[i] = ask1(a[i] - 1) + 1);
	for(int i = 1; i <= n; ++i) FT[i] = 0;
	for(int i = n; i >= 1; --i) {
		add1(n - a[i] + 1, suf[i] = ask1(n - a[i]) + 1);
		pii cur = ask2(a[i] + 1);
		if(!cur.scd) cur = mp(i, 1);
		(suf[i] -= cur.scd) %= mod; add2(a[i], cur);
	}
	for(int i = 1; i <= n; ++i) (Ans += 1ll * pre[i] * suf[i]) %= mod;
	Ans = (Ans + mod) % mod;
	printf("%lld\n", Ans);
}

signed main () {
#ifdef FILE
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
	read(T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：pldzy (赞：2)

[CF 传送门](https://codeforc.es/contest/1621/problem/G) | [LG 传送门](https://www.luogu.com.cn/problem/CF1621G) | [Read in my blog](https://www.cnblogs.com/gsn531/p/17522332.html)。

优化树状数组+反向处理。

## Solution

- 发现直接做不好下手。难点主要在求出所有的上升子序列并计算它们分别的贡献。
	所以需要反向考虑每个单点在什么情况下产生贡献。一个单点会产生多少贡献。
- 一个单点产生贡献的条件很容易得到。一个是在一个上升子序列中；一个是它小于该序列后面的最大值。
	发现第二个条件是可以转化为一个“一般化”的限制的：对于每个点 $i$ 都能找到 $r_i$ 表示最后一个大于它的项。
	所以能让 $i$ 产生贡献的一定是结尾在 $r_i$ 前、包含 $i$ 的上升子序列。
- 然后考虑能使 $i$ 产生贡献的上升子序列个数。
	根据乘法分配律，这个个数为：以 $i$ 结尾的上升子序列个数 $\times$ 以 $i$ 开头结尾在 $r_i$ 前的上升序列个数。
- 前者可以直接使用树状数组 $O(n\log n)$ 得到。
	后者可以转化一下。使用同样的方法求出以 $i$ 为开头的上升子序列个数 $-$ 以 $i$ 开头且 $r_i$ 结尾的上升序列个数。
	显然 $r_i$ 之后的数对上升序列不会产生任何贡献影响。
- 如果直接暴力求“以 $i$ 开头且 $r_i$ 结尾的上升序列个数”，那么复杂度将是 $O(n^2\log n)$ 的。
	考虑优化。考虑省去一些无用的转移——即转移项对 $i$ 的上升序列不会产生贡献。
- 考虑什么样的项会对“以 $i$ 开头 $r_i$ 结尾的上升序列”产生贡献。
	不妨设这样的项下标为 $j$，那么：$a_i<a_j<a_{r_i}$。所以显然 $r_j=r_i$。
	设 $r_i=x$。
	所以对于一个 $x$，所有能对以它结尾的上升序列产生影响的项 $i$，$r_i=x$。
	所以只需要在所有 $r_i=x$ 的项 $i$ 考虑上升序列的方案数，一起考虑它们“以自身开头以 $x$ 结尾的上升序列”的个数即可。那么对这些项遍历用树状数组求一遍即可。
- 因为每个 $i$ 只会有一个对应的 $r_i$，所以单次询问复杂度是 $O(n\log n)$ 的。

## Code

````cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define per(i, a, b) for(int i = a; i >= b; --i) 
#define init rep(i, 1, n) t[i] = 0
const int maxn = 2e5 + 5, mod = 1e9 + 7;
int n, a[maxn], id[maxn];
int t[maxn], pre[maxn], suf[maxn], f[maxn];
int s[maxn], tp;
vector<int> d[maxn];

inline int lb(int x){ return x & (-x);}
inline void add(int x, int k){
	for(int i = x; i <= n; i += lb(i)) (t[i] += k) %= mod;
}
inline int qry(int x){ int res = 0;
	for(int i = x; i; i -= lb(i)) (res += t[i]) %= mod;
	return res;
}

inline bool cmp(int x, int y){
	return a[x] == a[y] ? x > y : a[x] < a[y];
}
inline void slv(){
	scanf("%lld", &n), tp = 0;
	rep(i, 1, n) d[i].clear();
	rep(i, 1, n) scanf("%lld", &a[i]), id[i] = i;
	sort(id + 1, id + n + 1, cmp); rep(i, 1, n) a[id[i]] = i;//离散化 
	init; rep(i, 1, n) add(a[i], pre[i] = qry(a[i] - 1) + 1);
	init; per(i, n, 1) add(n - a[i] + 1, suf[i] = qry(n - a[i]) + 1);//nlogn 求上升序列个数 
	per(i, n, 1) if(a[i] > a[s[tp]]) s[++tp] = i;
	per(i, n, 1){ int l = 1, r = tp, pos;
		while(l <= r){ 
			int mid = (l + r) >> 1;
			if(a[i] <= a[s[mid]]) r = mid - 1, pos = mid;
			else l = mid + 1;
		}
		if(i != s[pos]) d[s[pos]].push_back(i);
	} init;
	rep(i, 1, tp){
		add(n - a[s[i]] + 1, f[s[i]] = 1);
		for(int v : d[s[i]]) add(n - a[v] + 1, f[v] = qry(n - a[v]));
		for(int v : d[s[i]]) add(n - a[v] + 1, -f[v]);
		add(n - a[s[i]] + 1, -1);
	}
	int ans = 0;
	rep(i, 1, n) (ans += 1ll * (suf[i] - f[i] + mod) % mod * pre[i] % mod) %= mod;
	printf("%lld\n", ans);
}

signed main(){
	int T; scanf("%lld", &T);
	while(T--) slv();
	return 0;
}
````

------------

Thanks for reading.

---

## 作者：cirnovsky (赞：2)

一个 dp（拜谢 ly）和切入点都略有不同的做法，并不需要观察啥性质。

原问题针对子序列进行规划，自然地想到转而对前缀进行规划。接下来我们考虑一个前缀 $[1, i]$ 以及一个 $j \in [1, i]$ 对答案的贡献，可以写出 $\displaystyle \textit{cont}(j \text{ to } [1, i]) = [\max_{i < k} a_k > a_j] \times \text{the number of LISs containing } j \text{ indexed in } [1, i]$。

这个可以做两个 dp 解决，第一个好解决的静态 dp，即结束在 $j$ 的 LIS 方案数；第二个 dp 有些烦：$j$ 在动，我们考虑的前缀 $[1, i]$ 也在移动。

到这里其实换一下着手点第二个 dp 就变成静态的了，即考虑位置 $j$，直接算 $(j, i)$ 的贡献即可，其中 $i$ 是「满足 $a_i > a_j$ 的最大的 $i$」。于是我们的第二个 dp 就可以被描述为从 $j$ 开始，结束在 $i$ 之前（不包括，因为要保证 $\max_{i < k} a_k > a_j$）的 LIS 方案数。答案即 $\displaystyle \sum_{i=1}^n dp_i \times dp'_i$。

第二个 dp 的具体实现，还需要一个辅助的 dp，其定义是第二个 dp 的定义中去掉贡献范围上界（即 $i$），转移画画图就能理解了。

用下 Fenwick Tree 啥的就能 $O(n \log_2 n)$ 了。

```cpp
using modint = modint1000000007;
int n, a[200100], pos[200100], id[200100];
modint dp[200100], dp2[200100], dp3[200100], bit[200100], bit2[200100];
void cng(int x, modint w) {
    for (; x<=n; x+=x&-x) {
        bit[x] += w;
    }
}
modint qry(int x) {
    modint res = 0;
    for (; x; x-=x&-x) {
        res += bit[x];
    }
    return res;
}
void cng2(int x, modint w) {
    for (; x<=n; x+=x&-x) {
        bit2[x] += w;
    }
}
modint qry2(int x) {
    modint res = 0;
    for (; x; x-=x&-x) {
        res += bit2[x];
    }
    return res;
}
void solve() {
    cin >> n;
    bastr<int> dsc;
    for (int i=1; i<=n; ++i) {
        cin >> a[i];
        dsc += a[i];
    }
    sort(dsc.begin(), dsc.end());
    dsc.erase(unique(dsc.begin(), dsc.end()), dsc.end());
    for (int i=1; i<=n; ++i) {
        a[i] = lower_bound(dsc.begin(), dsc.end(), a[i])-dsc.begin()+1;
    }
    iota(id+1, id+n+1, 1);
    sort(id+1, id+n+1, [&](int x, int y) {
        return a[x] < a[y];
    });
    for (int i=1,now=n; i<=n; ++i) {
        while (now >= 1 && a[now] <= a[id[i]]) {
            now--;
        }
        pos[id[i]] = now;
    }
    for (int i=1; i<=n; ++i) {
        bit[i] = 0;
    }
    for (int i=1; i<=n; ++i) {
        dp[i] = qry(a[i]-1)+1;
        cng(a[i], dp[i]);
    }
    for (int i=1; i<=n; ++i) {
        bit[i] = bit2[i] = 0;
    }
    modint ans = 0;
    for (int i=n; i>=1; --i) {
        dp2[i] = qry(cs(dsc)-a[i])+1;
        cng(cs(dsc)-a[i]+1, dp2[i]);
        if (pos[i] > i) {
            dp3[i] = qry(cs(dsc)-a[pos[i]]+1)+qry2(a[pos[i]]-1)-qry2(a[i]);
            cng2(a[i], dp3[i]);
        }
        else {
            dp3[i] = 0;
        }
        ans += dp[i]*dp3[i];
    }
    cout << ans.val() << "\n";
}
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言
好厉害的题目！我被卡在了第二步转化上。

# Part 2：正文
统计所有的上升子序列不好做，那么套路的转化成对每个位置考虑其对答案的贡献次数。接下来去找充要条件。通过一些简单的观察，我们发现对于每个位置 $x$，其是否有贡献仅取决于其所处的上升子序列的右端点和满足 $a_y>a_x$ 的最大的 $y$ 的位置。那么现在问题转化成了对于右端点在区间 $[1,y)$ 中，包含 $x$ 的上升子序列个数。至此我们可以有一个多项式做法，具体来说是枚举一个位置 $x$，然后直接去 dp 经过 $x$ 的上升子序列个数。这个东西有一个常规的树状数组优化做法。至此我们已经能够做到 $O(n^2\log n)$。

然后我被卡在这里了/cf。

下面是一步我没看出来的容斥。我们把经过 $p$ 且右端点在 $[p,y)$ 中容斥为右端点在 $[y,n]$ 中的。更近一步考虑，我们发现右端点只会在 $y$ 处，这是因为如果存在一个右端点 $z>y$，则一定有 $a_z>a_y$，与假设 $y$ 是最大的不符。再观察一下，我们发现对于 $[1,x)$ 的处理我们是可以直接做的，最后把系数乘进去即可。

现在问题转化成了经过两个定点的上升子序列个数。但太棒了，这个我不会做。

再次回顾性质，我们发现 $y$ 是 $x$ 能到达的最远点！那么我们只需要倒序维护一下每个数字的最远点在哪，然后把值塞进一个另一个树状数组。每次求到一个值的时候，把最大的 $z$ 满足 $a_z>a_x$ 的 dp 值拉出来减去即可。

时间复杂度 $O(n\log n)$。


# Part 3：代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
const int N=2e5+7,mod=1e9+7;
int T,n,a[N],f[N],g[N];
vector<int>buc;
void inc(int &x,int y){x+=y-mod,x+=x>>31&mod;}
struct Bitf{
#define lowbit(i) ((i)&(-i))
	int arr[N];
	void add(int p,int v){for(;p<=n;p+=lowbit(p))inc(arr[p],v);}
	int ask(int p){
		int res=0;
		for(;p;p-=lowbit(p))inc(res,arr[p]);
		return res;
	}
	void clr(){fill(arr+1,arr+n+1,0);}
#undef lowbit
};
struct Bitg{
#define lowbit(i) ((i)&(-i))
	int val[N],cnt[N];
	void upd(int &_val,int &_cnt,int v,int c){
		if(v>_val)_val=v,_cnt=c;
		else if(v==_val)inc(_cnt,c);
	}
	void add(int p,int v,int c){for(;p<=n;p+=lowbit(p))upd(val[p],cnt[p],v,c);}
	pair<int,int>ask(int p){
		int resv=0,resc=0;
		for(;p;p-=lowbit(p))upd(resv,resc,val[p],cnt[p]);
		return make_pair(resv,resc);
	}
	void clr(){fill(val+1,val+n+1,0);fill(cnt+1,cnt+n+1,0);}
#undef lowbit
};
Bitf bitf;
Bitg bitg;
void solve(){
	read(n);buc.clear();bitf.clr(),bitg.clr();
	for(int i=1;i<=n;i++)read(a[i]),buc.eb(a[i]);
	sort(buc.begin(),buc.end());buc.erase(unique(buc.begin(),buc.end()),buc.end());
	for(int i=1;i<=n;i++)a[i]=lower_bound(buc.begin(),buc.end(),a[i])-buc.begin()+1;
	for(int i=1;i<=n;i++){
		inc(f[i]=bitf.ask(a[i]-1),1);
		bitf.add(a[i],f[i]);
	}
	// for(int i=1;i<=n;i++)Debug("%d ",f[i]);
	// Debug("\n");
	bitf.clr();
	for(int i=n;i>=1;i--){
		g[i]=bitf.ask(n-a[i])+1;
		bitf.add(n-a[i]+1,g[i]);
		auto [v,c]=bitg.ask(n-a[i]);
		if(!c)v=i,c=1;
		inc(g[i],mod-c);
		bitg.add(n-a[i]+1,v,c);
	}
	// for(int i=1;i<=n;i++)Debug("%d ",g[i]);
	// Debug("\n");
	int ans=0;
	for(int i=1;i<=n;i++)inc(ans,(ll)f[i]*g[i]%mod);
	printf("%d\n",ans);
}
int main(){
	read(T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：cwfxlh (赞：1)

## [CF1621G](https://www.luogu.com.cn/problem/CF1621G)   
首先转化成每个位置的贡献。    

对于一个位置 $x$，不妨找到最后一个大于 $a_x$ 的 $a_y$（没有直接不统计），则所有包含 $x$ 的，且 $end<y$ 的上升子序列都会为答案做贡献。发现，如果一个包含 $x$ 的上升子序列，其结尾比 $y$ 大，则不符合 $a_y$ 是最后一个比 $a_x$ 大的数的性质，所以不满足条件的上升子序列一定是结尾为 $y$ 的子序列。    

于是我们可以先算出对于每一个 $x$，所有包含它的上升子序列个数，再减去对于每一个 $i$，以 $y_i$ 为结尾的上升子序列个数。    

对于第二种，我们可以做一个转化，令 $pre_i$ 表示以 $i$ 结尾的上升子序列个数，则我们只需要计算对于每一个 $i$，以 $i$ 为开头，$y_i$ 为结尾的上升子序列个数，再乘上 $pre_i$ 并减掉即可。    

把每一个 $i$ 挂到其所对应的 $y_i$ 中，遍历 $y_i$，把它本身和挂在它下面的询问取出来变成序列，跑一边上升子序列计数即可。    

至于为什么这样是成立的，原因就在于如果 $i$ 与 $j$ 的 $y$ 值不同，二者是不会互相做贡献的，具体证明可以根据 $y$ 的定义证得，比较简单但有点长，所以就不写了。    
代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 1000000007
using namespace std;
int t,n,a[500003],suf[500003],ans,CrsSeq[500003],TreeAr[500003],stSeq[500003];
int l,r,mid;
map<int,int>mp;
int lowbit(int X){return (X&(-X));}
int getval(int wz){register int ret=0;for(int i=wz;i;i-=lowbit(i))ret=(ret+TreeAr[i])%MOD;return ret;}
void add(int wz,int val){for(int i=wz;i<=n+2;i+=lowbit(i))TreeAr[i]=(TreeAr[i]+val)%MOD;return;}
struct Que{
	int X;
	int Y;
	int val;
}Q[500003];
int totQ;
bool comp(Que X,Que Y){if(X.Y!=Y.Y)return X.Y<Y.Y;return X.X<Y.X;}
int k1,k2,k3,k4,k5,k6,k7,k8,k9;
int dp[500003];
int stk[500003],tot;
signed main(){
	scanf("%lld",&t);
	while(t--){
		ans=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		mp.clear();
		tot=0;
		for(int i=1;i<=n;i++){
			if(mp[a[i]]==0){
				mp[a[i]]=1;
				stk[++tot]=a[i];
			}
		}
		sort(stk+1,stk+tot+1);
		for(int i=1;i<=tot;i++)mp[stk[i]]=i;
		for(int i=1;i<=n;i++)a[i]=mp[a[i]];
		suf[n+1]=0;
		for(int i=n;i>0;i--)suf[i]=max(a[i],suf[i+1]);
		for(int i=1;i<=n+2;i++)TreeAr[i]=0;
		for(int i=1;i<=n;i++)add(a[i],CrsSeq[i]=1+getval(a[i]-1));
		for(int i=1;i<=n+2;i++)TreeAr[i]=0;
		for(int i=n;i>0;i--)add(n+2-a[i],stSeq[i]=1+getval(n+1-a[i]));
		totQ=0;
		for(int i=1;i<=n;i++){
			if(suf[i+1]<=a[i])continue;
			ans=(ans+CrsSeq[i]*stSeq[i])%MOD;
			l=i+1;
			r=n;
			while(l<r){
				mid=((l+r)>>1)+1;
				if(suf[mid]<=a[i])r=mid-1;
				else l=mid;
			}
			Q[++totQ].X=i;
			Q[totQ].Y=l;
			Q[totQ].val=-CrsSeq[i];
		}
		sort(Q+1,Q+totQ+1,comp);
		for(int i=1;i<=n+2;i++)TreeAr[i]=0;
		for(int i=1;i<=totQ;i++){
			k1=i;
			while(k1<totQ&&Q[k1+1].Y==Q[i].Y)k1++;
			tot=0;
			for(int j=i;j<=k1;j++)stk[++tot]=Q[j].X;
			stk[++tot]=Q[i].Y;
			add(n+2-a[stk[tot]],dp[tot]=1);
			for(int j=tot-1;j>0;j--)add(n+2-a[stk[j]],dp[j]=getval(n+1-a[stk[j]]));
			for(int j=1;j<tot;j++)ans=(ans+dp[j]*Q[j+i-1].val)%MOD;
			for(int j=tot;j>0;j--)add(n+2-a[stk[j]],-dp[j]);
			i=k1;
		}
		ans+=MOD;
		ans%=MOD;
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Tyyyyyy (赞：1)

# CF1621G

### 题目分析
考虑对每个位置分别算它对答案的贡献，即它计入答案的次数。

对于一个固定的 $i$，设 $j$ 是满足 $a_i<a_j$ 的最大的 $j$，则 $i$ 有贡献，当且仅当其所在上升子序列的最后一个位置小于 $j$。因为如果上升子序列的最后一个位置大于或等于 $j$，后面就没有数比 $a_i$ 大了。

所以我们维护后缀最大值，枚举 $i,j$，即可 $O(n^2)$ 求解。

要进一步优化，不妨用所有情况减去不合法的情况。显然，没有贡献当且仅当这个子序列恰好结束于 $a_j$。因为如果结尾大于 $j$，则不满足上面的假设；如果结尾小于 $j$，则一定有贡献（至少有一个 $a_i<a_j$）。

所以我们现在只需要解决这个简化后的问题：给定一个序列，求开始位置和结束位置一定的上升子序列的个数。

考虑设一个 $k$ 为 $j+1$ 位置的后缀最大值，当 $j$ 固定时，显然对于所有的 $i$ 都满足 $a_k\leq a_i<a_j$。所以对于一个 $j$，有效的 $a_i$ 属于一个固定的区间 $[a_k,a_j)$。

于是我们枚举 $j$，用树状数组记录 $a_i$ 的数量，即可做到 $O(n\log n)$。因为每个 $i$ 只会在一个区间里，所以复杂度是对的。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,mod=1e9+7;
int t,n,a[N],v[N],dp_ed[N],dp_st[N];
struct BIT
{
	int c[N];
	void add(int x,int y){for(;x<=n;x+=x&(-x))c[x]=(c[x]+y)%mod;}
	void clear(int x){for(;x<=n;x+=x&(-x))c[x]=0;}
	int ask(int x)
	{
		int res=0;
		for(;x;x-=x&(-x))res=(res+c[x])%mod;
		return res;
	}
}tr;
struct node
{
	int val,id;
	bool operator < (node d) const
	{
		if(val!=d.val)return val>d.val;
		return id<d.id;
	}
}b[N];
bool bigger[N];
int suf[N];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),v[i]=a[i];
		sort(v+1,v+n+1);
		int tot=unique(v+1,v+n+1)-(v+1);
		for(int i=1;i<=n;i++)a[i]=lower_bound(v+1,v+tot+1,a[i])-v;
		for(int i=1;i<=n;i++)
		{
			dp_ed[i]=(tr.ask(a[i]-1)+1)%mod;
			tr.add(a[i],dp_ed[i]);
		}
		for(int i=1;i<=n;i++)tr.c[i]=0;
		for(int i=n;i>=1;i--)
			dp_st[i]=(tr.ask(n)-tr.ask(a[i])+1+mod)%mod,tr.add(a[i],dp_st[i]);
		for(int i=1;i<=n;i++)tr.c[i]=0;
		int mx=0;
		for(int i=n;i>=1;i--)
		{
			if(a[i]>mx)bigger[i]=1,mx=a[i];
			b[i]=(node){a[i],i};
			suf[i]=mx;
		}
		sort(b+1,b+n+1);
		queue<int>q;
		for(int i=1;i<=n;i++)tr.c[i]=0;
		for(int i=1;i<=n;i++)
		{
			if(bigger[b[i].id])
			{
				while(!q.empty())tr.clear(q.front()),q.pop();
				q.push(b[i].id);
				tr.add(b[i].id,1);
			}
			else
			{
				q.push(b[i].id);
				int tmp=(tr.ask(n)-tr.ask(b[i].id)+mod)%mod;
				dp_st[b[i].id]=(dp_st[b[i].id]-tmp+mod)%mod;
				tr.add(b[i].id,tmp);
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++)
			if(a[i]<suf[i])ans=(ans+1ll*dp_ed[i]*dp_st[i]%mod)%mod;
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)tr.c[i]=0,bigger[i]=0;
	}
	return 0;
}


---

## 作者：UKE_Automation (赞：0)

### CF1621G Weighted Increasing Subsequences

[$\text{Link}$](https://codeforces.com/problemset/problem/1621/G)

首先可以想到的是直接对序列计数太困难，所以考虑对每个数单独计算其对答案的贡献。

考虑一个位置 $x$ 在什么时候有贡献，显然是一个上升子序列包含它且结尾后面有 $>a_x$ 的数才行。那么我们令 $ps_x$ 表示最后一个 $>a_x$ 的数，这个可以简单二分找到，则这个包含 $x$ 的上升子序列的结尾必须要 $<ps_x$ 才行。

此时直接计数还是比较困难。再转化一下，考虑正难则反，我们用所有包含 $x$ 的上升子序列减去结尾 $\ge ps_x$ 的上升子序列。前者用树状数组预处理一下前缀和后缀子序列个数即可；后面这个看上去没有变简单多少，实际上我们思考一下会发现，$ps_x$ 已经是最后一个 $>a_x$ 的数了，所以结尾不可能比它还大，所以实际上后面计算的就是结尾为 $ps_x$ 的子序列个数。

那么现在我们对于每个 $x$ 需要求出包含它的以 $ps_x$ 为结尾的上升子序列个数，实际上只要求出以 $x$ 为开头、$ps_x$ 为结尾的上升子序列个数即可。这个好像还是很难求，不过观察一下可以发现，此时以 $x$ 为开头的子序列中的所有数的 $ps$ 一定也是 $ps_x$，那么我们把所有数按照其 $ps$ 分成若干类，在每一类里面再跑一遍 dp 即可。如此我们就可以在 $O(n\log n)$ 的复杂度内解决这个问题。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 2e9;
const int Mod = 1e9 + 7;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod : x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int max(int x, int y) {return x >= y ? x : y;} il void chkmax(int &x, int y) {x = (x >= y ? x : y);}
il int min(int x, int y) {return x <= y ? x : y;} il void chkmin(int &x, int y) {x = (x <= y ? x : y);}
il int qpow(int a, int b) {int res = 1; for(; b; a = 1ll * a * a % Mod, b >>= 1) if(b & 1) res = 1ll * res * a % Mod; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : x;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}

int T, n, a[Maxn];
int t[Maxn], tot;
int mx[Maxn], pos[Maxn];
vector <int> V[Maxn];
int f[Maxn], g[Maxn], h[Maxn];

namespace BIT1 {
	int c[Maxn];
	il void init() {for(int i = 1; i <= n; i++) c[i] = 0;}
	il int lowbit(int x) {return x & (-x);}
	il void mdf(int x, int val) {for(int i = x; i <= n; i += lowbit(i)) pls(c[i], val);}
	il int query(int x) {int sum = 0; for(int i = x; i; i -= lowbit(i)) pls(sum, c[i]); return sum;}
}
namespace BIT2 {
	int c[Maxn];
	il void init() {for(int i = 1; i <= n; i++) c[i] = 0;}
	il int lowbit(int x) {return x & (-x);}
	il void mdf(int x, int val) {for(int i = x; i; i -= lowbit(i)) pls(c[i], val);}
	il int query(int x) {int sum = 0; for(int i = x; i <= n; i += lowbit(i)) pls(sum, c[i]); return sum;}
}

void work(vector <int> &v) {
	int m = v.size() - 1; 
	h[v[m]] = 1, BIT2::mdf(a[v[m]], 1);
	for(int i = m - 1, x; i >= 0; i--) x = v[i], h[x] = BIT2::query(a[x] + 1), BIT2::mdf(a[x], h[x]);
	for(int i = 0, x; i <= m; i++) x = v[i], BIT2::mdf(a[x], Mod - h[x]); 
}

il void solve() {
	for(int i = 1; i <= n; i++) V[i].clear();
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]), t[i] = a[i];
	sort(t + 1, t + n + 1); tot = unique(t + 1, t + n + 1) - t - 1;
	for(int i = 1; i <= n; i++) a[i] = lower_bound(t + 1, t + n + 1, a[i]) - t;
	mx[n + 1] = 0;
	for(int i = n; i >= 1; i--) mx[i] = max(a[i], mx[i + 1]);
	for(int i = 1; i <= n; i++) {
		pos[i] = max(lower_bound(mx + i, mx + n + 1, a[i], greater<int>()) - mx - 1, i);
		V[pos[i]].push_back(i);
	}
	int ans = 0;
	BIT1::init(), BIT2::init();
	for(int i = 1; i <= n; i++) f[i] = BIT1::query(a[i] - 1) + 1, BIT1::mdf(a[i], f[i]);
	for(int i = n; i >= 1; i--) g[i] = BIT2::query(a[i] + 1) + 1, BIT2::mdf(a[i], g[i]);
	for(int i = 1; i <= n; i++) pls(ans, 1ll * f[i] * g[i] % Mod);
	BIT2::init();
	for(int i = 1; i <= n; i++) {
		if(!V[i].size()) continue;
		work(V[i]);
	}
	for(int i = 1; i <= n; i++) sub(ans, 1ll * f[i] * h[i] % Mod);
	write(ans);
}

int main() {
	read(T);
	while(T--) solve();
	return 0;
}

```

---

## 作者：Tx_Lcy (赞：0)

## 思路

首先离散化一下，把 $a$ 变成一个排列，如果有权值相同的我们钦定先出现的位置值比较大。

然后考虑一个上升子序列中的数 $x$ 什么时候的权值为 $0$，设 $y$ 为上升子序列中最后的位置，当且仅当 $[y+1,n]$ 中没有大于 $a_x$ 的数，也就是 $y$ 是最后一个大于 $x$ 的数，我们设 $ed_x$ 表示 $x$ 后面最后一个大于 $x$ 的数的位置。

由于对“权值为 $0$”的限制比较强，所以考虑容斥，先假设上升子序列中的数权值都为 $1$，这个的方案数可以简单 DP 算出，然后考虑计算令 $x$ 的权值为 $0$ 的方案数。

直接做复杂度是 $\Theta(n^2 \log n)$ 的，但是若我们将 $ed_x$ 相同的 $x$ 放在一起处理，这些 $x$ 的权值构成了一个区间。

因此直接扫描 $ed_x$ 的值 $y$，然后把 $ed_x=y$ 的那些 $x$ 的权值设为 $1$，则我们想要求的是所有以 $y$ 结尾的上升子序列的权值和，可以直接按照权值从小往大扫描 $x$，然后树状数组优化 DP 即可。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive.
#include<bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
int const N=2e5+10,mod=1e9+7;
int n,a[N],g[N],lf[N],rg[N],vl[N],f[N],fa[N],ed[N],tong[N];
inline int find(int x){return (x==fa[x])?(x):(fa[x]=find(fa[x]));}
struct Tree_Array{
	#define lowbit(x) (x&(-x))
	int c[N];
	inline int query(int x){int res=0;while (x) res+=c[x],res%=mod,x-=lowbit(x);return res;}
	inline void update(int x,int v){while (x<N) c[x]+=v,c[x]%=mod,x+=lowbit(x);}
}T,T_;
inline void solve(){
	cin>>n;
	vector< pair<int,int> >V;
	rep(i,1,n) cin>>a[i],V.push_back({a[i],-i});
	sort(all(V));
	rep(i,1,n) a[-V[i-1].second]=i;
	rep(i,1,n)
		f[i]=(T.query(a[i]-1)+1)%mod,
		T.update(a[i],f[i]),
		g[i]=(f[i]+T_.query(a[i]-1))%mod,
		T_.update(a[i],g[i]);
	rep(i,1,n)
		T.update(a[i],mod-f[i]),
		T_.update(a[i],mod-g[i]);
	int ans=0;
	rep(i,1,n) ans+=g[i],ans%=mod;//假设所有数的权值都为 1
	rep(i,1,n) fa[i]=i,tong[i]=lf[i]=rg[i]=0;
	per(i,n,1){
		ed[i]=tong[a[i]];
		int x=find(a[i]-1);
		while (x) tong[x]=i,fa[x]=x-1,x=find(x);
	}//处理 ed
	rep(i,1,n)
		if (ed[i]<i){ans+=mod-f[i],ans%=mod;continue;}
		else if (!lf[ed[i]]) lf[ed[i]]=rg[ed[i]]=a[i];
		else lf[ed[i]]=min(lf[ed[i]],a[i]),rg[ed[i]]=max(rg[ed[i]],a[i]);
	per(i,n,1){
		if (!lf[i]) continue;//扫描 ed 的值
		rep(j,lf[i],rg[i]){
			int pl=-V[j-1].second;//按照值从小往大扫描 x
			if (ed[pl]<pl);
			else{
				vl[pl]=(T.query(pl-1)+f[pl])%mod;
				T.update(pl,vl[pl]),ans+=mod-vl[pl],ans%=mod;
			}
		}
		rep(j,lf[i],rg[i]){
			int pl=-V[j-1].second;
			if (ed[pl]<pl);
			else T.update(pl,mod-vl[pl]);
		}
	}
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：zcxxnqwq (赞：0)


考虑每个位置 $i$ 被记入贡献的次数，即 $i$ 所在上升子序列末尾位置 $+1$ 的后缀最大值大于 $a_i$ 的方案数怎么计算。记满足 $a_j>a_i$ 的最大 $j$ 所在位置为 $p$，这个 $p$ 一定不能在上升子序列里，那么贡献就是含有 $i$ 且不含有 $p$ 的上升子序列数。

含有 $i$ 的限制很好计算，设 $f[i]$ 为以 $i$ 为结尾的上升子序列数，$g[i]$ 为以 $i$ 为开头的上升子序列数，树状数组维护 dp 一下就行。

对于不含 $p$ 的限制考虑正难则反，问题转化为计算以 $i$ 开头以 $p$ 结尾的上升子序列数。

显然所有 $p$ 都是严格后缀最大值，把它们提出来称为序列 $b$，那么 $b_i$ 管辖的就是 $a_j\in(b_{i+1},b_i]$ 的所有 $j$。那么把 $a$ 从大到小排序，每找到一个 $b$ 中的元素就把树状数组清空重新做即可。

具体实现可以看代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define rep(i,s,e) for(int i=(s);i<=(e);++i)
#define Rep(i,s,e) for(int i=(e);i>=(s);--i)
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=2e5+5,mod=1e9+7;
int n,a[N],b[N],m,suf[N],tag[N];
int f[N],g[N];
inline void add(int &x,int y){x+=y;if(x>=mod) x-=mod;}
struct BIT{
    int t[N];
    inline void clear(){rep(i,1,n) t[i]=0;}
    inline int lowbit(int x){return x&(-x);}
    inline void del(int x){
        for(int i=x;i<=n;i+=lowbit(i)) t[i]=0;
    }
    inline void upd(int x,int v){
        for(int i=x;i<=n;i+=lowbit(i)) add(t[i],v);
    }
    inline int query(int x){
        int res=0;
        for(int i=x;i;i-=lowbit(i)) add(res,t[i]);
        return res;
    }
}t;
struct qwq{
    int v,p;
    bool operator < (const qwq &a) const{
        if(v!=a.v) return v>a.v;
        return p<a.p;
    }
}q[N];
inline void solve(){
    n=read();
    rep(i,1,n) a[i]=b[i]=read();
    sort(b+1,b+n+1),m=unique(b+1,b+n+1)-b-1;
    rep(i,1,n) a[i]=lower_bound(b+1,b+m+1,a[i])-b,q[i]={a[i],i};
    suf[n+1]=0;
    Rep(i,1,n) suf[i]=max(suf[i+1],a[i]),tag[i]=suf[i]>suf[i+1];
    t.clear();
    rep(i,1,n) f[i]=t.query(a[i]-1)+1,t.upd(a[i],f[i]);
    // cerr<<"f";rep(i,1,n) cerr<<f[i]<<' ';cerr<<endl;
    t.clear();
    Rep(i,1,n) g[i]=(t.query(n)-t.query(a[i])+1+mod)%mod,t.upd(a[i],g[i]);
    // cerr<<"g";rep(i,1,n) cerr<<g[i]<<' ';cerr<<endl;
    t.clear();
    sort(q+1,q+n+1);
    vector<int> ve;
    rep(i,1,n){
        if(tag[q[i].p]){
            for(int tmp:ve) t.del(tmp);
            ve.clear(),ve.pb(q[i].p),t.upd(q[i].p,1);
        }
        else{
            ve.pb(q[i].p);
            int cnt=(t.query(n)-t.query(q[i].p)+mod)%mod;
            g[q[i].p]=(g[q[i].p]-cnt+mod)%mod,t.upd(q[i].p,cnt);
        }
    }
    int ans=0;
    rep(i,1,n) if(a[i]<suf[i]) add(ans,1ll*f[i]*g[i]%mod);
    printf("%d\n",ans);
}
signed main(){
    int T=read();
    while(T--) solve();
}
```

---

