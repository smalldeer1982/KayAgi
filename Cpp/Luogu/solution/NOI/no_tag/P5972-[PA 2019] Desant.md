# [PA 2019] Desant

## 题目描述

给定一个 $1$ 到 $n$ 的排列 $a_{1..n}$，它有 $2^n-1$ 个非空子序列。

请对于每个 $k$，找到一个长度为 $k$ 的子序列，使得这个子序列的逆序对数量最少，并输出逆序对数量最少的子序列的数量。

## 说明/提示

对于 $100\%$ 的数据，$1\le k\le n$，$1\le n\le 40$，$1\le a_i\le n,a_i\ne a_j$。

## 样例 #1

### 输入

```
5
5 3 1 4 2```

### 输出

```
0 5
0 3
1 2
3 1
7 1```

# 题解

## 作者：云浅知处 (赞：20)

好像是我初二的时候提出的一个问题，当时 u 群有人说存在 $O(n^23^{n/3})$ 做法，昨天晚上突然会做了！

考虑从前往后 DP，暴力是记录 $S$ 表示目前选择的数的集合，这样状态数仍然是 $O(2^n)$ 级别。

但我们注意到，设 $i$ 后面的数分别为 $x_1,x_2,\cdots,x_k$，我们只关心 $[1,x_1),(x_1,x_2),\cdots,(x_k,n]$ 这些每一段中选了多少个数。于是状态数不会超过每段长度 $+1$ 的乘积，由柯西不等式可以知道一定在段长相同时取到最值，直接看成连续的情况来分析，简单求导可以得到最值在 $e^{n/e}$，由于问题是离散的于是最值大约是 $3^{n/3}$。

于是直接 DP 就可以了。时间复杂度是 $O(n^23^{n/3})$，使用 `map` 或许会被卡常，手写哈希表可以稳过。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define mk make_pair
#define fi first
#define se second

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int N=41;
const int M=(1<<22);
const int P=47;
int a[N],n;

struct HashMap{

pair<int,ll>vals[M];
vector<int>havs;
vector<int>act[M];

int head[M],nxt[M],tot;
int size(){return tot;}
void clear(){
	for(int i=1;i<=tot;i++)nxt[i]=0,vector<int>().swap(act[i]);
	for(int i:havs)head[i]=0;
	vector<int>().swap(havs),tot=0;
}
void Ins(vector<int>&A,pair<int,ll>val){
	int res=0;
	for(int x:A)res=(((res*P)+x+1)&(M-1));
	
	int p=head[res];
	if(!p)p=++tot,act[p]=A,vals[p]=val,havs.emplace_back(res),head[res]=p;
	else{
		while(act[p]!=A&&p)p=nxt[p];
		if(!p)p=++tot,act[p]=A,vals[p]=val,nxt[p]=head[res],head[res]=p;
		else{
			if(vals[p].fi==val.fi)vals[p].se+=val.se;
			else if(vals[p].fi>val.fi)vals[p]=val;
		}
	}
}

};

HashMap f[2];

signed main(void){

	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	
	int cur=0;
	vector<int>NaganoharaYoimiya(n+1,0);
	f[0].Ins(NaganoharaYoimiya,mk(0,1ll));

	for(int i=1;i<=n;i++){
		vector<int>x;f[cur^1].clear();
		for(int j=i;j<=n;j++)x.emplace_back(a[j]);
		sort(x.begin(),x.end());int p=0;
		for(int j=0;j<x.size();j++)if(x[j]==a[i])p=j;

		for(int _=1;_<=f[cur].tot;_++){
			auto A=f[cur].vals[_];
			int w=A.fi;ll cc=A.se;
			int nw=0;for(int j=p+1;j<f[cur].act[_].size();j++)nw+=f[cur].act[_][j];
			auto to=f[cur].act[_];int cnt=to[p]+to[p+1];
			to.erase(to.begin()+p);
			to[p]=cnt,f[cur^1].Ins(to,mk(w,cc));
			to[p]=cnt+1,f[cur^1].Ins(to,mk(w+nw,cc));
		}
		
		cur^=1;
	}

	vector<pair<int,ll> >ans(n+1);
	for(int i=1;i<=f[cur].tot;i++){
		auto vec=f[cur].act[i];auto A=f[cur].vals[i];
		assert(vec.size()==1);
		int cnt=vec[0];
		ans[cnt]=A;
	}
	
	for(int i=1;i<=n;i++)cout<<ans[i].fi<<" "<<ans[i].se<<endl;

	return 0;
}
```

---

## 作者：dengchengyu (赞：19)

# [PA2019] Desant Solution

[推销](https://www.cnblogs.com/dccy/p/18637829)。

[原题链接](https://www.luogu.com.cn/problem/P5972)。

**题目大意**：给定一个长为 $n(n\le 40)$ 的排列，对于每个 $i$ 求出长度为 $i$ 的子序列逆序对最少有多少，并且求出有多少个长度为 $i$ 的子序列逆序对最少。 

**解题思路**：首先有一个暴力的做法，设 $f_{i,S}$ 表示考虑完前 $i$ 个数，选择了集合 $S$ 的最少逆序对数、方案数。这样做至少是 $O(n2^n)$，非常不优美。我们发现我们只关心比当前位置大的数有多少个，所以我们把 $S$ 中所有数都记录下来是有些多余的。考虑优化状态。

对于考虑完了前 $i$ 个数，我们把 $i$ 以后的数排序，记为 $x_1,x_2,\cdots$，我们只需要记录 $[1,x_1),(x_2,x_3),\cdots,(x_{end},n]$ 这样每个区间内选了多少个数即可。于是我们可以设状态 $f_{i,T_1,T_2,\cdots}$，$T_i$ 表示第 $i$ 个区间内选了多少个数。

考虑计算状态的个数，我们就是求和为 $n$ 的若干个数乘积最大是多少。严谨证明我不会，~~但是根据小学奥数~~，我们只要尽可能多拆 $3$，其次拆 $2$，尽量少拆成 $1$，这是因为如果我们考虑一个大于 $3$ 的数，把它对半拆开乘积一定会更大，如 $5<2\times 3$。因此可以想到，最坏情况下，状态数是 $O(3^{\frac n 3})$，实际上这与严谨证明下的结论一致。因此状态数是可行的。

再回到状态上来，我们可以对于第 $i$ 个长度为 $len_i$ 的区间，用第 $i$ 位上的 $(len_i+1)$ 进制表示，即记 $w_i=\prod_{j=1}^{i-1}(len_j+1)$，设 $cnt_i$ 为第 $i$ 个区间选了多少个数，则 $T=\sum_{i=1}^{end}cnt_iw_i$，这样就能用整型表示状态 $f_{i,T}$，用 `vector` 连续开 $\prod (len_i+1)$ 个位置即可，比哈希快多了。

而对于转移，每次决策选或不选都会合并两个区间。暴力地拆出状态的每一位和合并状态的每一位即可。

时间复杂度 $O(n^23^\frac{n}3)$，注意方案数要开 `long long`。

AC 代码：

```cpp
int n;
const int N=45;
int a[N];
int l[N],w[N][N],c[N][N];
vector<pair<int,ll> > f[N];
int now[N];
void getmax(pair<int,ll> &x,pair<int,ll> y){
	if(x.first>y.first)x=y;
	else if(x.first==y.first)x.second+=y.second;
}
signed main(){
	read(n);
	fo(i,1,n){
		read(a[i]);
	}
	fo(i,0,n){
		fo(j,i+1,n){
			c[i][++l[i]]=a[j];
		}
		c[i][++l[i]]=n+1;
		sort(c[i]+1,c[i]+1+l[i]);
		int t=1;
		fo(j,1,l[i]){
			w[i][j]=t;
			t*=c[i][j]-c[i][j-1];
		}
		f[i]=vector<pair<int,ll>>(t,{1e9,0});
	}
	f[0][0]={0,1};
	fo(i,0,n-1){
		int at=0;
		fo(j,1,l[i])if(c[i][j]==a[i+1])at=j;
		fu(j,0,f[i].size()){
			int t=j;
			fd(k,l[i],1){
				now[k]=t/w[i][k];
				t%=w[i][k];
			}
			int cnt=0;
			fo(k,at+1,l[i])cnt+=now[k];
			int t1=0,t2=0;
			fo(k,1,at-1)t1+=now[k]*w[i+1][k];
			fo(k,at+2,l[i])t1+=now[k]*w[i+1][k-1];
			t2=t1;
			t1+=(now[at]+now[at+1])*w[i+1][at];
			t2+=(now[at]+now[at+1]+1)*w[i+1][at];
			getmax(f[i+1][t1],f[i][j]);
			getmax(f[i+1][t2],{f[i][j].first+cnt,f[i][j].second});			
		}
	}
	fo(i,1,n)write(f[n][i].first,' ',f[n][i].second,'\n');
	return 0;
}
```

---

## 作者：jockbutt (赞：16)

又没有题解，$做的好事++$，$rp++$

# START!

题目题意很明白，不需要解释。

首先，$n=40$告诉我们这道题是一个状态压缩。
#### 考虑已经确定了前$i$个，状态可以只记后面的$n-i$个点之间的$n-i+1$个间隔里的已选的数。
不过【单纯】的状态压缩是肯定不行的，$2$的$40$次方不可能跑过去。于是我就拼尽脑汁地想啊想，~~然后打开了一一篇题解~~，最终得到了一个神奇的结论：若干个和为 n 的数的乘积最大为 $O(3^{n/3})$。为什么呢，我也不知道，证明这个结论应该交给数竞班的奆佬去证明。

然后呢，我们可以把那个数拆成$x$个$3$和$k$个$2$，$k$为常数，就是主要用$3$，用$2$凑整。用三进制来存这个状态。

时间复杂度大概$O(n^23^{(n+1)/3})$——某巨佬说的。

这题的数据巨强，我的代码就算开了$O_2$也只能得$98$分 ~~（$QWQ$我连输出优化都加了你就让我过吧）~~
Code:

```
#include <bits/stdc++.h>
using namespace std;
char BUF_W[1<<22],*pp=BUF_W;
inline void WC(const char &c) {
	if (!(pp-BUF_W^(1<<22))) fwrite(BUF_W,1,1<<22,stdout),pp=BUF_W;
	*pp++=c;
}//输出优化
template <class T>
inline void WI(T x) {
	if (x<0) {
		WC('-');x=-x;
	}
	static int sta[30],tp;
	do sta[tp++]=x%10; while (x/=10);
	while (tp) WC(sta[--tp]^48);
}
inline void flush() {fwrite(BUF_W,1,pp-BUF_W,stdout);pp=BUF_W;}
const int maxn=45,INF=1e9;
int n, a[maxn];
int b[maxn],b0;
inline int read()//输入优化
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (!(ch^'-')) f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct node{
	long long w[maxn],w0;
}p,q;
inline void build(int *b,int &b0,node &p)
{
	sort(b+1,b+b0+1);
	b[0]=0,b[b0+1]=n+1;
	p.w0=b0;
	p.w[0]=1;
	for(int j=1;j<=b0+1;++j)	p.w[j]=p.w[j-1]*(b[j]-b[j-1]);
}
inline void zh(int *a,node b,int x)
{
	for(int i=0;i<=b.w0;++i)	a[i]=x%b.w[i+1]/b.w[i];
}
inline int zy(int *a,node b)
{
	int s=0;
	for(int i=0;i<=b.w0;++i)	s+=a[i]*b.w[i];
	return s;
}
struct P{
	int x;long long y;
	P(int _x=0,long long _y=0)
	{
		x=_x,y=_y;
	}
}ans[maxn];
P operator + (P a,P b)
{
	return !(a.x^b.x)?P(a.x,a.y+b.y):(a.x<b.x?a:b);
}
vector <P> f[maxn];
int c[maxn],d[maxn];
int main(){
	n=read();
	for(int i=1;i<=n;++i)		a[i]=read();
	f[0].resize(1);
	f[0][0]=P(0,1);
	int t;
	int id;
	for(int i=0;i<n;++i)
	{
		b0=0;
		for(int j=i+1;j<=n;++j)	b[++b0]=a[j];
		build(b,b0,p);
		id;
		for(int j=1;j<=b0;++j)	if(!(b[j]^a[i+1]))	id=j;
		b0=0;
		for(int j=i+2;j<=n;++j)	b[++b0]=a[j];
		build(b,b0,q);
		int m1=p.w[p.w0+1],m2=q.w[q.w0+1];
		f[i+1].resize(m2);
		for(int j=0;j<m2;++j)	f[i+1][j]=P(INF,0);
		for(int k=0;k<m1;++k)
		{
			if(f[i][k].y)
			{
				zh(c,p,k);
				for(int j=0;j<=1;++j)
				{
					P v=f[i][k];
					if(j)
					{
						for(int u=id;u<=p.w0;++u)	v.x+=c[u];
					}
					t=-1;
					for(int u=0;u<=p.w0;++u)
					{
						if(!(u^id))
						{
							d[t]+=c[u]+j;
						}
						else	d[++t]=c[u];
					}
					int nk=zy(d,q);
					f[i+1][nk]=f[i+1][nk]+v;
				}
			}
		}
	}
	for(int i=1;i<=n;++i)	ans[i]=P(INF,0);
	int size=f[n].size();
	for(int k=0;k<=size;++k)
	{
		zh(c,q,k);
		int x=0;
		for(int u=0;u<=q.w0;++u)	x+=c[u];
		ans[x]=ans[x]+f[n][k];
	}
	for(int i=1;i<=n;++i)
	{
		WI(ans[i].x);WC(' ');WI(ans[i].y);WC('\n');
		flush();
	} 
	return 0;
}
```


---

## 作者：haochengw920 (赞：10)

非常 tricky 的一道题。

## 思路

传统艺能：看数据范围猜算法。

$n\leq 40$ 一般是 meet in middle 或者乱搞优化的状压，因为左右部分也会产生贡献所以先不考虑前者。

有一个比较 work 的做法： `f[i][j]` 表示前 $i$ 个数出现情况为 $j$ 的最少逆序对个数以及方案数，转移考虑有多少个比 $i$ 大的数已经出现，从 `f[i-1][j]` 推导过来即可。

但是这样状态数是 $O(n2^n)$ ，转移还要多一个 $n$ ，肯定会炸。

## 优化

引入一个引理：和为 $n$ 的若干个数的积最大为 $e^{n/e}$ ，若规定整数的话即为 $3^{n/3}$ 。

**证明** ：首先考虑用类似均值不等式的方法证明积最大时这几个数一定相同，否则合并成一个相同的数一定更优。

设这个相等的数为 $x$ ，则积为 $f(x)=x^{n/x}$ 。发现 $n$ 取什么值对这个函数的最值位置是没有影响的，考虑 $f(x)=x^{1/x}$ 。

当 $x<0$ 时 $f(x)$ 小于 $0$ 肯定不优，于是对两边开 $\ln$ ，得到 $\ln f(x)=\ln(x)\frac{1}{x}$ 。

由于 $\ln(x)$ 是单增的，令 $g(x)=\ln(x)\frac{1}{x}$ ，一阶导 $g'(x)=\frac{1-\ln(x)}{x^2}$ ，发现它在 $x=e$ 时取 $0$ ， $x<e$ 时为正， $x>e$ 时为负，于是原函数单峰，峰为 $x=e$ 。

证明整数取 $3$ 的话其实就是比较 $2$ 到 $e$ 与 $e$ 到 $3$ 的积分嘛，分别考虑分子分母即可。



考虑怎么用这个引理来优化状态。你一开始可能会考虑把 $1$ 到 $n$ 分块，然后对于第一个块中的每一个起点跑一遍 dp ，但是实际上这是不太 work 的（和 meet in middle 同样的问题，块与块不好合并）。

想想我们第一个块中的每一个起点跑 dp 的目的：由于把出现次数存到了一个块里，对于一个不在块边界的数我们无法快速计算这个块中有多少个比它大。然后你为了不跑多次 dp 可能会考虑每个块再状压一下是否出现什么的或者二次分块…那你就走远了。

实际上，为了让逆序对的更新变得方便，我们只需要存后面有的数作为块的分界点就行了，每次转移之后再更新分界点，这样压一下进制其实状态数也是够的。

理论最差时间 $O(n^23^{n/3})$ ，空间 $O(n3^{n/3})$ ，有点小炸，但是实际上跑不满。

注意对于每个 $i$ 开动态的 `vector` ，不然会炸空间。

## Code

这题方案数要开 `long long` ，但是我懒，直接 `#define int long long` 了…

被卡常的宝宝或者 dalao 们可以试试开 `int` ，实测快一倍左右。

```cpp
#include<cstdio>
#include<cctype>
#include<vector>
#include<utility>
#include<algorithm>
#define fir first
#define sec second
#define int long long
#define mkp make_pair
#define Pii pair<int, int>
#define INF (0x3f3f3f3f3f3f3f3f)
using namespace std;

char buf[1000000], *p1 = buf, *p2 = buf, obuf[1000000], *p3 = obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++)
#define putchar(x) (p3-obuf<1000000?*p3++=x:(fwrite(obuf,1,p3-obuf,stdout),p3=obuf,*p3++=x))
inline int read() {
	int x = 0; char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x;
}
inline void write(int x) {
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}

const int MAXN = 45;

int n, a[MAXN];
int b0, b[MAXN];

struct node {
	int w0, w[MAXN];
}p, q;
inline void Build(int b0, int b[], node &p) {
	sort(b + 1, b + b0 + 1);
	b[0] = 0, b[b0 + 1] = n + 1;
	p.w0 = b0 + 1; p.w[0] = 1;
	for (int i = 1; i <= p.w0; ++ i)
		p.w[i] = p.w[i - 1] * (b[i] - b[i - 1]);
}
inline void Chg(int a[], node &b, int x) {
	for (int i = 0; i < b.w0; ++ i)
		a[i] = x % b.w[i + 1] / b.w[i];
}
inline int IChg(int a[], node &b) {
	int res = 0;
	for (int i = 0; i < b.w0; ++ i)
		res += a[i] * b.w[i];
	return res;
}

int ct[MAXN], d[MAXN];
vector<Pii>f[MAXN];
Pii ans[MAXN]; 
inline Pii Merge(Pii &x, Pii &y) {
	return (x.fir ^ y.fir) ? (x.fir < y.fir ? x : y) : mkp(x.fir, x.sec + y.sec);
}
inline void DP() {
	f[0].emplace_back(mkp(0, 1));
	for (int i = 1; i <= n; ++ i) {
		int id = 0; b0 = 0;
		for (int j = i; j <= n; ++ j)
			b[++ b0] = a[j];
		Build(b0, b, p);
		for (int j = 1; j <= b0; ++ j)
			if (b[j] == a[i]) id = j;
		b0 = 0;
		for (int j = i + 1; j <= n; ++ j)
			b[++ b0] = a[j];
		Build(b0, b, q);
		// 预处理进制 
		int m1 = p.w[p.w0], m2 = q.w[q.w0];
		f[i].resize(m2);
		for (Pii &x : f[i]) x = mkp(INF, 0);
		for (int k = 0; k < m1; ++ k) {
			if (!f[i - 1][k].sec) continue;
			Chg(ct, p, k);
			for (int fg = 0; fg <= 1; ++ fg) {
				Pii v = f[i - 1][k];
				if (fg) {
					for (int j = id; j < p.w0; ++ j)
						v.fir += ct[j];
				}
				int t = -1;
				// 由于第一个是 1 ，所以不会有下标越界的问题
				for (int j = 0; j < p.w0; ++ j)
					if (j ^ id) d[++ t] = ct[j];
					else d[t] += ct[j] + fg;
				int nk = IChg(d, q);
				f[i][nk] = Merge(f[i][nk], v);
			}
		}
	}
	for (int i = 1; i <= n; ++ i) ans[i] = mkp(INF, 0);
	int siz = f[n].size(), x;
	for (int k = 0; k < siz; ++ k) {
		Chg(ct, q, k); x = 0;
		for (int j = 0; j < q.w0; ++ j)
			x += ct[j];
		ans[x] = Merge(ans[x], f[n][k]);
	}
}

signed main()
{
	n = read();
	for (int i = 1; i <= n; ++ i) a[i] = read();
	DP();
	for (int i = 1; i <= n; ++ i)
		write(ans[i].fir), putchar(' '), write(ans[i].sec), putchar('\n');
	return fwrite(obuf,1,p3-obuf,stdout), 0;
}
```

---

## 作者：hhhqx (赞：3)

无耻求赞 QwQ



---



$O(2^n)$ 做法很显然，状态数太多了，mid in middle 也不行，考虑减少状态。

假设为对于 $1,\cdots,i$ 的子集都已经计算完了，加下来转移，只需要保留 $[1,x_{i+1}),(x_{i+1},x_{i+2}),\cdots,(x_n,n]$ 这些区间中出现次数。

每个位置接下来的状态数是 $\prod{L_i}$，每个位置最大状态是是平均分配，所以最大 $(\frac{n}{n-i+1})^{n-i}$。那么总状态数是 $\sum\limits_{i=1}^{n}{(\frac{n}{n-i+1})^{n-i}}$，$n=40$ 时大概是 $2 \cdot 10^7$ 大小。

复杂度 $O(n\sum\limits_{i=1}^{n}{(\frac{n}{n-i+1})^{n-i}} \times 一些根据实现的东西)$。可以使用哈希表，那复杂度 $O(n^2 \sum\limits_{i=1}^{n}{(\frac{n}{n-i+1})^{n-i}})$。

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using PII = pair<int, LL>;

int n, a[43];
PII dp[int(1e7)], tmp[int(1e7)];

vector<int> L[2];

vector<int> Get1(int x, int o){
	vector<int> vt;
	for(int i = 1; i < L[o].size(); i++){
		vt.push_back(x % L[o][i]), x /= L[o][i];
	}
	return vt;
}
int Get2(vector<int> vt, int o){
	int x = 0;
	for(int i = L[o].size() - 1; i >= 1; i--){
		x = x * L[o][i] + vt.back(), vt.pop_back();
	}
	return x;
}

inline void ADD(PII &x, PII y){
	if(x.first == y.first){
		x.second += y.second;
		return;
	}
	x = min(x, y);
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	L[1].push_back(1);
	for(int i = 1; i <= n + 1; i++) L[1].push_back(1);
	dp[0] = {0, 1};
	for(int i = 1; i <= n; i++){
		swap(L[0], L[1]), L[1].clear(), L[1].push_back(1);
		vector<int> p;
		for(int j = i + 1; j <= n; j++) p.push_back(a[j]);
		p.push_back(0), p.push_back(n + 1), sort(p.begin(), p.end());
		for(int j = 1, len; j < p.size(); j++) len = p[j] - p[j - 1], L[1][0] *= len, L[1].push_back(len);
		p.push_back(a[i]), sort(p.begin(), p.end());
		int pos = 0;
		for(int j = 1; j < p.size(); j++) if(p[j] == a[i]) pos = j;
		
		for(int s = 0; s < L[0][0]; s++) tmp[s] = dp[s];
		for(int s = 0; s < L[1][0]; s++) dp[s] = {int(1e9), 1};
		for(int s = 0; s < L[0][0]; s++){
			vector<int> vt = Get1(s, 0), _vt = vt;
			vt[pos - 1] += vt[pos], vt.erase(vt.begin() + pos);
			ADD(dp[Get2(vt, 1)], tmp[s]);
			int cnt = 0;
			for(int j = pos; j < _vt.size(); j++) cnt += _vt[j];
			vt[pos - 1]++;
			ADD(dp[Get2(vt, 1)], PII(tmp[s].first + cnt, tmp[s].second));
		}
	}
	for(int i = 1; i <= n; i++){
		cout << dp[i].first << " " << dp[i].second << "\n";
	}
	return 0;
}	
```

---

## 作者：_fairytale_ (赞：2)

>漫无目的跟随我在树荫里穿行
>
>我信手拨弄身边花草 随口道着它们的名
>
>手中相机端持久久不敢按下快门 怕唐突这宁静
>
>请让这一切暂停

状态数很少。

朴素 DP 要记前面选了哪些数，状态数是 $2^n$ 级别的。考虑能不能合并一些状态，把“选了哪些”转化成“选了几个”。

假如我们考虑到前 $i$ 个数，那么我们只关心 $a_i\dots a_n$ 这 $(n-i+1)$ 个数组成的间隔中选了几个数。假如第 $j$ 个间隔的长度为 $L_j$，状态数为 $\prod(L_j+1)$。因为 $\sum L_j=n$，由均值不等式得知取等的时候积取到最大值。所以总状态数最多为 $\sum_{i=1}^n(\dfrac{n}{n-i+1})^{n-i+1}$，$n=40$ 时这个数约等于 $23573116$，可以接受。

设 $f_{i,S}$ 表示考虑到前 $i$ 个数，$a_i\dots a_n$ 组成的间隔中分别有多少个数表示为 $S$ 时逆序对数的最小值即可。

用 `map/unordered_map/gp_hash_table/cc_hash_table` 都卡不过去，所以抄了云浅老师的哈希表/ll

```cpp
#include<bits/stdc++.h>
bool Mst;
#define ll long long
#define pii pair<int,ll>
#define fi first
#define se second
#define rep(x,qwq,qaq) for(int x=(qwq);x<=(qaq);++x)
#define per(x,qwq,qaq) for(int x=(qwq);x>=(qaq);--x)
using namespace std;
template<typename T1,typename T2>
ostream& operator <<(ostream &os,const pair<T1,T2>&t) {
	return os<<t.fi<<" "<<t.se,os;
}
const int M=(1<<22);
const int P=47;
struct HashMap {
	pair<int,ll>vals[M];
	vector<int>havs;
	vector<int>act[M];
	int head[M],nxt[M],tot;
	int size() {
		return tot;
	}
	void clear() {
		for(int i=1; i<=tot; i++)nxt[i]=0,vector<int>().swap(act[i]);
		for(int i:havs)head[i]=0;
		vector<int>().swap(havs),tot=0;
	}
	void Ins(vector<int>&A,pii val) {
		int res=0;
		for(int x:A)res=(((res*P)+x+1)&(M-1));

		int p=head[res];
		if(!p)p=++tot,act[p]=A,vals[p]=val,havs.emplace_back(res),head[res]=p;
		else {
			while(act[p]!=A&&p)p=nxt[p];
			if(!p)p=++tot,act[p]=A,vals[p]=val,nxt[p]=head[res],head[res]=p;
			else {
				if(vals[p].fi==val.fi)vals[p].se+=val.se;
				else if(vals[p].fi>val.fi)vals[p]=val;
			}
		}
	}
};
HashMap f[2];
#define maxn 42
int n,m,k;
int a[maxn];
pii ans[maxn];
vector<int>pre[maxn];
#define inf 0x3f3f3f3f
bool Med;
signed main() {
	cerr<<(&Mst-&Med)/1024.0/1024.0<<" MB\n";
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	rep(i,1,n)ans[i]= {inf,0};
	rep(i,1,n)cin>>a[i];
	vector<int>tmp(n);
	rep(i,1,n)tmp[i-1]=i;
	pre[0]=tmp;
	rep(i,1,n) {
		auto it=find(tmp.begin(),tmp.end(),a[i]);
		if(it!=tmp.begin())tmp.erase(it);
		pre[i]=tmp;
	}
	vector<int> z(n);
	rep(i,1,n)z[i-1]=0;
	f[0].Ins(z,{0,1});
	rep(i,1,n) {
		auto &g=f[i&1],&F=f[~i&1];
		rep(_,1,F.tot) {
			pii &t=F.vals[_];
			int sum=t.fi,delta=0;
			ll cnt=t.se;
			vector<int> &S=F.act[_],&P=pre[i-1];
			for(int j=(int)P.size()-1;; --j) {
				assert(j>=0);
				delta+=S[j];
				if(P[j]==a[i]) {
					if(j!=0) {
						S[j-1]+=S[j];
						S.erase(S.begin()+j);
						g.Ins(S,{sum,cnt});
						++S[j-1];
					} else {
						g.Ins(S,{sum,cnt});
						++S[j];
					}
					g.Ins(S,{sum+delta,cnt});
					break;
				}
			}
		}
		F.clear();
	}
	rep(_,1,f[n&1].tot) {
		pii &t=f[n&1].vals[_];
		int k=0;
		for(int x:f[n&1].act[_])k+=x;
		if(ans[k].fi>t.fi)ans[k]=t;
		else if(ans[k].fi==t.fi)ans[k].se+=t.se;
	}
	rep(i,1,n)cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：masterhuang (赞：1)

> 给定一个 $1$ 到 $n$ 的**排列** $a_1,a_2,\cdots ,a_n$，它有 $2^n-1$ 个非空子序列。
>
> 请对于每个 $k$，找到一个长度为 $k$ 的子序列，使得这个子序列的逆序对数量最少，并输出逆序对数量最少的子序列的数量。
>
> $1\le k,a_i\le n\le 40$。

- 依然是状态压缩的思想，注意到很多状态是等价的。

考虑从前往后 **DP**，暴力是记录 $S$ 表示目前选择的数的集合，这样状态数仍然是 $O(2^n)$ 级别。

但我们注意到，设 $i$ 后面的数分别为 $x_1, x_2, \cdots, x_k$，我们只关心 $[1, x_1), (x_1, x_2), \cdots, (x_k, n]$ 这些每一段中选了多少个数。

于是状态数不会超过每段长度 $+1$ 的乘积，由柯西不等式可以知道一定在段长相同时取到最小值，直接看成连续的情况来分析，简单求导可以得到最小值在 $e^{n/e}$, 由于问题是离散的于是最小值大约是 $3^{n/3}$​。

于是直接 **DP** 就可以了。时间复杂度是 $O(n^2 3^{n/3})$，使用 `map` 或许会被卡常, 手写哈希表可以稳过。

### 变进制状态存储（虽然我觉得你们都会）

考虑第一位 $[0,a_1]$，第二位在 $[0,a_2]$，...，第 $k$ 位在 $[0,a_k]$​ 的向量如何存储。

记 $p_i=\prod\limits_{j=1}^i (a_i+1)$，然后考虑对向量 $b_1,\cdots ,b_k$，存储为 $\sum\limits_{i=1}^k p_{i-1}b_i$ 即可，能空间 $\prod(a_i+1)$​ 精准存储，且不需要 `map`。

---

于是这题，对于每个  $i$，对 $i$ 后面的 $x_1, x_2, \cdots, x_k$ 使用变进制存储即可。转移的时候多算算状态。

类似题目：[CF1552G](https://www.luogu.com.cn/problem/CF1552G)，[P10360](https://www.luogu.com.cn/problem/P10360)

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define P pair<int,LL>
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=45;
int n,a[N],c[N][N],ml[N][N],d[N],C[N],o[N];
vector<P>f,g;
inline void upd(P &x,P y){
	auto& [u,v]=x;auto [p,q]=y;
	if(p<u) x=y;else if(p==u) v+=q;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=0;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++) c[i][++d[i]]=a[j];
		sort(c[i]+1,c[i]+1+d[i]);c[i][++d[i]]=n+1;int s=1;
		for(int j=1;j<=d[i];j++) ml[i][j]=s,s*=c[i][j]-c[i][j-1];
		ml[i][d[i]+1]=s;
	}f={{0,1}};
	for(int i=1;i<=n;i++)
	{
		g=vector<P>(ml[i][d[i]+1],{999,0});
		int w=find(c[i-1],c[i-1]+n+1,a[i])-c[i-1];int S=0;
		for(auto [u,v]:f)
		{
			for(int j=d[i-1],x=S;j;j--) o[j]=x/ml[i-1][j],x%=ml[i-1][j];
			fill(C,C+d[i]+1,0);int ad=0;
			for(int j=1;j<=w;j++) C[j]=o[j];
			for(int j=w+1;j<=d[i-1];j++) C[j-1]+=o[j],ad+=o[j];
			auto calc=[&](){
				int s=0;
				for(int j=1;j<=d[i];j++) s+=ml[i][j]*C[j];
				return s;
			};
			upd(g[calc()],{u,v});C[w]++;
			upd(g[calc()],{u+ad,v});S++;
		}swap(f,g);
	}
	for(int i=1;i<=n;i++) cout<<f[i].first<<" "<<f[i].second<<"\n";
	return 0;
}
```

---

## 作者：KazamaRuri (赞：1)

## 题意

给定一个 $1$ 到 $n$ 的排列 $a_{1 \dots n}$，它有 $2^n-1$ 个非空子序列。

请对于每个 $k$，找到一个长度为 $k$ 的子序列，使得这个子序列的逆序对数量最少，并输出逆序对数量最少的子序列的数量。

## 分析

感觉有点 Ad-hoc 了。

容易想到 $O(n2^n)$ 的做法。

考虑新加入了 $w$ 到子序列末尾，对逆序对的贡献即为在子序列里的数 $\ge w$ 的数量。区别于 $O(n2^n)$ 直接维护在子序列里的数，我们试着直接维护 $\ge w$ 的数量。

发现对于前 $i$ 个数的状态，可能的 $\ge w$ 的询问会是 $w=a_{i+1},a_{i+2},\cdots,a_n$。

若把这些数排序，那就会把值域划分成了 $O(n)$ 段。

把每一段内有多少个数存到状态里，决策 $i$ 时就合并 $i$ 的左右两块。这种做法状态数是 $O(n3^{\frac n 3})$ 的，总时间复杂度为 $O(n^23^{\frac n 3})$。

非常神奇是吧。

简略证明下: 因为值域总为 $n$，若以 $x$ 分一段，根据乘法原理得到方案数 $f(x)=x^{\frac n x}$。$n$ 次方不影响极值，先忽略。然后取 $\ln$ 后求导得到最大值是 $e^{\frac n e}$，整数范围内是 $3^{\frac n 3}$。

## 代码

有点卡常。

实现上为了方便存状态用进制把序列 hash 成了一个数。

在赛场上猜了几个的结论能 $O(ans)$，都假了。

组题人把最难的放 T1 是想怎样呢。


```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define int ll
#define inf (ll)1e16
#define lim(i) (B[i].w[B[i].k])
using namespace std;
using ll=long long;
using pii=pair<int,ll>;
const int N=45;
int n,a[N],id[N]; ll c[N];
vector<pii>f[N]; pii ans[N];
struct basic{ int k,w[N]; }B[N];
inline void encode(const basic &b,ll v){
	for(int i=0;i<b.k;i++)
		c[i]=v%b.w[i+1]/b.w[i];
}
inline ll decode(const basic &b){
	ll res=0;
	for(int i=0;i<b.k;i++)
		res+=c[i]*b.w[i];
	return res;
}
inline void chkmin(pii &x,pii &y){
	if(x.fi>y.fi) x.fi=y.fi,x.se=0;
	if(x.fi==y.fi) x.se+=y.se;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i);
	set<int>s; s.insert(0),s.insert(n+1);
	B[n+1].w[B[n+1].k=B[n+1].w[0]=1]=n+1;
	for(int i=n;i;i--){
		s.insert(a[i]),id[i]=0,B[i].k=n-i+2;
		int t=1,lst=0; B[i].w[0]=1;
		for(auto it=++s.begin();it!=s.end();it++){
			B[i].w[t]=B[i].w[t-1]*(*it-lst);
			if(*it==a[i]) id[i]=t; lst=*it,++t;
		}
	}
	f[0].push_back({0,1});
	for(int i=1;i<=n;i++){
		f[i].resize(lim(i+1));
		for(auto &x:f[i]) x={inf,0};
		for(int k=0;k<lim(i);k++){
			if(!f[i-1][k].se) continue;
			encode(B[i],k); pii w=f[i-1][k]; ll suf=0;
			for(int j=id[i];j<B[i].k;j++) suf+=c[j];
			if(id[i]) c[id[i]-1]+=c[id[i]];
			for(int j=id[i]+1;j<B[i].k;j++) c[j-1]=c[j];
			ll v=decode(B[i+1]); chkmin(f[i][v],w);
			if(id[i]) v+=B[i+1].w[id[i]-1];
			w.fi+=suf,chkmin(f[i][v],w);
		}
	}
	for(int i=1;i<=n;i++) ans[i]={inf,0};
	for(int i=0;i<=lim(n+1);i++) encode(B[n+1],i),chkmin(ans[c[0]],f[n][i]);
	for(int i=1;i<=n;i++) printf("%lld %lld\n",ans[i].first,ans[i].second);
	return 0;
}
```

---

## 作者：shiruoyu114514 (赞：1)

首先容易想到 $O(n2^n)$ 的 DP：令 $dp_{i,S}$ 为考虑到第 $i$ 个数，选数集合为 $S$ 的答案。

事实上我们知道的太多了：我们只需要知道选的数与后面数的大小关系，但是我们却多知道了选了哪些数。能不能想办法去掉这些冗余信息呢？

看起来还是没什么思路。事实上，如果你的思维是僵化的，认为对于第一维的每一个 $i$，其 $S$ 的集合都是固定的话就似了。

我们在此使用一种动态变化的状态来解决问题。

定义 $dp_{i,S}$ 为：

考虑完第 $1$ 到 $i$ 个数；令 $m$ 为 $n-i$，设其之后的所有点的值域集合为 $p_0$ 到 $p_{m+1}$（$p_0=0$ 与 $p_{m+1}=n+1$），则对于每一个 $i \in [1,m+1]$，$S$ 存储 $ (p_{i-1},p_i)$ 范围内有多少个已经选过的数时，最少逆序对数及方案数是多少。

转移时枚举 $i+1$ 选不选，并从状态信息里得到逆序对会加多少，转移到对应的状态即可。

对于每一个点 $i$，其对应的 $S$ 一共有 $\prod (p_i-p_{i-1}+1)$ 个，而 $\sum (p_i-p_{i-1}+1) = n+1$，当这些值全取 $3$ 时，其值最大，为 $3^{\frac{n+1}{3}}$。时间复杂度 $O(n^23^{\frac{n+1}{3}})$，实际上根本跑不满。

实现时可以使用变进制数维护，参照代码。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void chkmax(pair<int,ll>& a,pair<int,ll> b){
	if(a.first>b.first){
		a=b;
	}
	else if(a.first==b.first){
		a.second+=b.second;
	}
}

const int maxn=40;
const int inf=1e9;

int a[maxn+5];
int nxt[maxn+5][maxn+5];
int bse[maxn+5][maxn+5];
int cnt[maxn+5];
vector<pair<int,ll>> ans[maxn+5];
int n;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	a[n+1]=n+1;
	for(int i=0;i<=n;i++){
		for(int j=i+1;j<=n+1;j++){
			nxt[i][j]=a[j];
		}
		sort(nxt[i]+i+1,nxt[i]+n+2);//nxt 即为文中所述 p 数组 
		int sze=1;
		for(int j=i+1;j<=n+1;j++){
			bse[i][j]=sze;
			sze*=nxt[i][j]-nxt[i][j-1];//处理变进制数所使用的各个位上的进制，并统计对于 i，S 的大小 
		}
		ans[i].resize(sze,make_pair(inf,0ll));
	}
	ans[0][0]=make_pair(0,1);
	for(int i=0;i<n;i++){
		int res=-1;
		for(int j=i+1;j<=n;j++){
			if(nxt[i][j]==a[i+1]){
				res=j;//找出 a[i+1] 所对应的那个 p。 
				break;
			}
		}
		for(int j=0;j<ans[i].size();j++){
			int tmp=j;
			for(int k=n+1;k>=i+1;k--){
				cnt[k]=tmp/bse[i][k];//将十进制数转化为变进制数 
				tmp%=bse[i][k];
			}
			int add=0;
			for(int k=res+1;k<=n+1;k++){
				add+=cnt[k];
			}
			int to0=0,to1=0;
			//to0 为不选 i+1 时转移的状态，to1 为选时转移的状态 
			for(int k=i+1;k<=n+1;k++){
				if(k<res){
					to0+=cnt[k]*bse[i+1][k+1];
					to1+=cnt[k]*bse[i+1][k+1];
				}
				else if(k==res){
					continue;
				}
				else if(k==res+1){
					to0+=(cnt[k]+cnt[k-1])*bse[i+1][k];
					to1+=(cnt[k]+cnt[k-1]+1)*bse[i+1][k];
				}
				else{
					to0+=(cnt[k])*bse[i+1][k];
					to1+=(cnt[k])*bse[i+1][k];
				}
			}
			chkmax(ans[i+1][to0],make_pair(ans[i][j].first,ans[i][j].second));
			chkmax(ans[i+1][to1],make_pair(ans[i][j].first+add,ans[i][j].second));
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[n][i].first<<" "<<ans[n][i].second<<"\n";
	}
}
```

---

## 作者：happybob (赞：0)

考虑目前已经确定了 $[1,i]$ 的结果，记什么状态能刻画后面的数被选时逆序对的增量。

$[i+1,n]$ 把值域分为了 $n-i+1$ 段，只需要记录每段内选入子序列的数量即可。

容易发现这个东西的最大状态数肯定是每段内数量尽可能平分，状态数为每段数量 $+1$ 的乘积，总状态数不超过 $\sum \limits_{i=1}^n \left(\dfrac{i}{n-i+1}+1\right)^{n-i+1}$，这个状态数是可以接受的，然后就过了。

---

