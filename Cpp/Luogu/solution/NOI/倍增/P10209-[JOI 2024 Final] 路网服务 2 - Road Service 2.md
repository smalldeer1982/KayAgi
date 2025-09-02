# [JOI 2024 Final] 路网服务 2 / Road Service 2

## 题目描述

JOI 市有一个由 $H$ 条东西向的无限长道路和 $W$ 条南北向的道路组成的网格状道路网。从北边数第 $i\ (1 \leq i \leq H)$ 条的东西向的道路和从西边数第 $j\ (1 \leq j \leq W)$ 条的南北向的道路相交的地方称作交叉点 $(i, j)$。

现在，由于道路年久失修，一部分道路被封锁了。具体的封锁情况如下：

- 如果 $A_{i, j}=0\ (1 \leq i \leq H,1 \leq j \leq W-1)$，则从北边数第 $i$ 条的东西向的道路的，交叉点 $(i, j)$ 和交叉点 $(i, j+1)$ 之间的部分就是封锁的；如果 $A_{i, j}=1$ 则是可以通行的。
- 如果 $B_{i, j}=0\ (1 \leq j \leq W,1 \leq i \leq H-1)$ 从西边数第 $j$ 条的南北向的道路的，交叉点 $(i, j)$ 和交叉点 $(i+1, j)$ 之间的部分就是封锁的；如果 $B_{i, j}=1$ 就是可以通行的。
- 道路的其他部分，即 $H \times W$ 个交叉点外面的部分都是封锁的。

JOI 市的市长 K 理事长决定制定一个道路维修计划。维修计划由大于等于 $0$ 次维修构成。一次维修时选择一个满足的整数 $i\ (1 \leq i \leq H)$，然后进行以下的操作：


对于**所有**满足 $1 \leq j \leq W-1$ 的整数 $j$，如果从北边数第 $i$ 条的东西向的道路的，交叉点 $(i, j)$ 和交叉点 $(i, j+1)$ 之间的部分是封锁的话，将其变成可以通行的。这个过程总共需要 $C_{i}$ 天。其中，$C_{i}$ 为 $1$ 或 $2$。

维修计划里包含的多次维修不能同时进行。因此，维修计划的执行所需要的天数是维修计划里包含的所有维修所需要的天数的总和。

为了让市里的重要设施之间能够互相通行，K 理事长向你提出了 $Q$ 个问题。第 $k\ (1 \leq k \leq Q)$ 个问题是这样的：

是否存在一个维修计划，能够让 $T_{k}$ 个交叉点 $(X_{k, 1}, Y_{k, 1}),(X_{k, 2}, Y_{k, 2}), \ldots ,(X_{k, T_{k}}, Y_{k, T_{k}})$ 之间，只通过可以通行的道路互相通行。如果存在的话，执行这样的维修计划最少需要多少天。

给定道路网的封锁情况，各条道路的维修所需要的天数，K 理事长的问题的内容，编写一个程序来回答 K 理事长的所有问题。

## 说明/提示

对于所有输入数据，满足：

- $2 \leq H$
- $2 \leq W$
- $H \times W \leq 10^6$
- $1 \leq Q \leq 10^5$
- $A_{i, j}$ 为 $0$ 或 $1\ (1 \leq i \leq H, 1 \leq j \leq W-1)$
- $B_{i, j}$ 为 $0$ 或 $1\ (1 \leq i \leq H-1,1 \leq j \leq W)$
- $C_{i}$ 为 $1$ 或 $2\ (1 \leq i \leq H)$
- $2 \leq T_{k}\ (1 \leq k \leq Q)$
- $T_{1}+T_{2}+\cdots+T_{Q} \leq 2\times 10^5$
- $1 \leq X_{k, l} \leq H\ (1 \leq k \leq Q, 1 \leq l \leq T_{k})$
- $1 \leq Y_{k, l} \leq W\ (1 \leq k \leq Q, 1 \leq l \leq T_{k})$
- $(X_{k, 1}, Y_{k, 1}),(X_{k, 2}, Y_{k, 2}), \ldots,(X_{k, T_{k}}, Y_{k, T_{k}})$ 各不相同 $(1 \leq k \leq Q)$

详细子任务附加限制及分值如下表所示。

|子任务|	附加限制|	分值|
| :-: | :-: | :-:|
|1|	$C_{i}=1\ (1 \leq i \leq H), Q \leq 5, T_{k}=2\ (1 \leq k \leq Q), A_{i, j}=0\ (1 \leq i \leq H, 1 \leq j \leq W-1)$|	$10$|
|2|$	C_{i}=1\ (1 \leq i \leq H), Q \leq 5, T_{k}=2\ (1 \leq k \leq Q)$|	$6$
|3|	$C_{i}=1\ (1 \leq i \leq H), Q \leq 5$|	$15$|
|4|	$C_{i}=1\ (1 \leq i \leq H), T_{k}=2\ (1 \leq k \leq Q)$|	$11$|
|5|	$C_{i}=1\ (1 \leq i \leq H)$|	$6$|
|6|	$Q \leq 5$|	$12$|
|7|	$T_{k}=2\ (1 \leq k \leq Q)$|	$26$|
|8|	无附加限制	|$14$|

## 样例 #1

### 输入

```
4 3 4
00
00
00
00
100
001
000
1 1 1 1
2
1 1
3 3
2
3 1
1 2
2
2 3
3 3
2
4 2
3 2```

### 输出

```
1
3
0
-1```

## 样例 #2

### 输入

```
4 4 4
100
110
011
010
0010
1001
0101
1 1 1 1
2
1 2
3 1
2
1 4
4 1
2
3 2
1 2
2
4 3
1 1```

### 输出

```
1
3
2
2```

## 样例 #3

### 输入

```
7 3 3
10
00
00
10
00
01
00
110
101
011
001
110
100
1 1 1 1 1 1 1
3
7 2
3 1
3 2
3
3 1
6 3
2 3
7
2 2
1 3
7 3
5 2
1 2
7 2
3 1```

### 输出

```
3
2
4```

## 样例 #4

### 输入

```
4 3 3
00
00
10
00
110
011
001
1 2 2 2
2
1 1
3 1
2
4 3
2 1
2
4 1
1 3```

### 输出

```
1
2
5```

## 样例 #5

### 输入

```
7 3 2
01
00
00
00
00
10
01
100
110
011
001
101
001
1 1 2 1 1 2 2
3
7 2
1 3
5 1
5
1 1
2 2
3 1
2 3
4 2```

### 输出

```
4
1```

# 题解

## 作者：Rainbow_qwq (赞：6)

首先把每个点对应到各自的连通块，将每个连通块对应到一个区间。则问题转化为：

- 初始有若干个区间。你需要选择一些点 $x$，两个区间有边当且仅当他们都包含一个选了的点 $x$。
- 询问为：给出若干个区间，需要选择一些点使它们联通，最小化点集权值和。（注意其他区间也参与连边）


首先判掉不需要撒点的情况，然后对询问的区间做缩减操作：若两个区间 $[l_1,r_1]$ 和 $[l_2,r_2]$ 满足 $[l_1,r_1]\subseteq [l_2,r_2]$，则可以舍弃 $[l_2,r_2]$ 的限制，因为此时 $[l_1,r_1]$ 中至少撒一个点，一定会连通。

缩减完后，此时的区间没有包含关系，可以从左到右排序。

特判掉缩减完后只剩一个区间的情况，此时答案为 在区间内选一个权值最小的点。

考虑权值均为 $1$ 的情况。

选点的方案是从左到右贪心的过程。从最左的 $[l_1,r_1]$ 开始，假设当前连通的区间（**所有**）中，最右的右端点是 $R$，而下一个没被连通的区间（仅限**询问区间**）是 $[l_t,r_t]$，则：

若 $r_t>R$，则选择 $R$；否则选择 $r_t$。

对于选择 $r_t$ 的情况，相当于把 $t$ 这个区间消耗掉了；

对于 $r_t>R$ 选择 $R$ 的情况：会先选择 $R$，每次选的下一个点是当前连通的最右一个点，再将 $R$ 更新，直到某次 $r_t\le R$。这个过程可以用倍增跳来计算，预处理 $f_{i,j}$ 表示从 $i$ 开始选，选 $2^j$ 步跳到哪个点。

如果当前所有**询问区间**都被连通，则过程结束。

两个操作加起来只有 询问区间个数 次，于是复杂度为 $O(\sum T_k \log n)$。

接下来考虑权值为 $1,2$ 怎么做。

事实上只需要稍微改变一下状态。维护当前的答案 $ans$，设 $dp_{0/1}$ 表示当前跳的代价为 $ans-1$ 或 $ans$ 步，能达到的右端点最大值。

将倍增数组也改变状态，设 $f_{i,j,0/1}$ 从 $i$ 开始选，经过代价为 $2^k-1$ 或 $2^k$ 步，能达到的右端点最大值。

接下来同上述倍增过程一样做即可：

- 如果 $dp_{0/1}$ 两个位置都不在询问区间内，就要用倍增数组跳过一整个空挡。每次尝试 $ans\to ans+2^k$，由于倍增处理的是跳 $2^k-1,2^k$ 代价达到的最远 $R$，可以求出此时跳到的端点，判断端点是否已经超过下一个区间。
- 否则，将 $ans\to ans+1$，并计算 $ans+1$ 对应的位置，可以从 $dp_{0/1}$ 转移。

[loj submission](https://loj.ac/s/2034530)

```cpp
// what is matter? never mind. 
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2") 
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
#define ll long long
//#define int long long
#define ull unsigned long long
#define SZ(x) ((int)((x).size()))
#define ALL(x) (x).begin(),(x).end()
using namespace std;

#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int,int>pii;
typedef vector<int>vi;

#define maxn 1000005
#define inf 0x3f3f3f3f

int n,m,Q,fa[maxn];

int P(int i,int j){
	return (i-1)*m+j;
}
int gf(int x){
	while(x!=fa[x])x=fa[x]=fa[fa[x]];
	return x;
}
void mg(int u,int v){
	fa[gf(u)]=gf(v);
}

int id[maxn];
pii to[maxn];
int k;
int nxt2[maxn],ban[maxn];
int wei[maxn],pre1[maxn];

int f[20][500005][2];

void get(vector<pii>&o){
	vector<pii>s;
	sort(ALL(o),[&](pii x,pii y){
		if(x.fi!=y.fi) return x.fi<y.fi;
		return x.se>y.se;
	});
	for(auto [l,r]:o){
		while(s.size() && s.back().se>=r) s.pop_back();
		s.pb(mkp(l,r));
	}
	o=s;
}

int solve()
{
	int q=read();
	vi o(q);
	For(i,0,q-1){
		int a=read(),b=read();
		o[i]=gf(P(a,b));
		o[i]=id[o[i]];
	}
	sort(ALL(o)),o.erase(unique(ALL(o)),o.end());
	if(o.size()==1) return 0;
	
	vector<pii>a;
	for(auto x:o) a.pb(to[x]);//cout<<"x: "<<x<<" "<<to[x].fi<<" "<<to[x].se<<"\n";
	get(a);
	
	int l=inf,r=-inf;
	for(auto [tl,tr]:a) l=min(l,tr),r=max(r,tl);
//	cout<<"l,r "<<l<<" "<<r<<"\n";
	if(ban[r]!=ban[l]) return -1;
	
//	for(auto [tl,tr]:a)cout<<"LR "<<tl<<" "<<tr<<"\n"; 
	
	auto in=[&](int x){
		if(x==-1)return 1;
		auto it=upper_bound(ALL(a),mkp(x,inf));
		if(it!=a.begin()){
			--it;
			if((it->fi)<=x && x<=(it->se)) return 1;
		}
		return 0;
	};
	
	auto getnxt=[&](int x){
		if(x==0) return l;
		int res=nxt2[x];
		auto it=upper_bound(ALL(a),mkp(x,inf));
		if(it!=a.end()) res=min(res,(it->se));
		return res;
	};
	
	int res=1;
	int dp[2]={0,pre1[l]};
//	cout<<"res1 "<<1<<" "<<dp[0]<<" "<<dp[1]<<"\n";
	
	while(dp[1]<r){
		if(!in(dp[0]) && !in(dp[1])){
			int lim=r;
			auto it=upper_bound(ALL(a),mkp(dp[1],inf));
			if(it!=a.end()) lim=min(lim,(it->fi));
			
			Rep(i,19,0){
				int tdp[2];
				tdp[0]=max(f[i][dp[0]][1],f[i][dp[1]][0]);
				int R=(dp[0]==0?l:nxt2[dp[0]]);
				tdp[1]=max(f[i][dp[1]][1],f[i][R][0]);
				tdp[1]=max(tdp[1],tdp[0]);
				if(tdp[1]<lim){
					dp[0]=tdp[0],dp[1]=tdp[1];
					res+=(1<<i);
				}
			}
			if(dp[1]>=r) break;
		}
		int nx=max(getnxt(dp[0]),pre1[getnxt(dp[1])]);
	//	cout<<"nxt "<<dp[1]<<" "<<getnxt(dp[1])<<" "<<pre1[2]<<" "<<pre1[getnxt(dp[1])]<<"\n";
		dp[0]=dp[1],dp[1]=nx;
		++res;
	//	cout<<"res "<<res<<" "<<dp[0]<<" "<<dp[1]<<"\n";
	}
	return res;
}

signed main()
{
	n=read(),m=read(),Q=read();
	For(i,0,n*m) fa[i]=i;
	For(i,1,n){
		string s;cin>>s;
		For(j,1,m-1) if(s[j-1]&1) mg(P(i,j),P(i,j+1));
	}
	For(i,1,n-1){
		string s;cin>>s;
		For(j,1,m) if(s[j-1]&1) mg(P(i,j),P(i+1,j));
	}
	For(i,0,n*m) to[i]=mkp(inf,-inf);
	For(i,1,n) For(j,1,m) {
		int x=gf(P(i,j));
		to[x].fi=min(to[x].fi,i);
		to[x].se=max(to[x].se,i);
	}
	For(i,1,n*m) 
		if(gf(i)==i) id[i]=++k,to[k]=to[i];
	
	For(i,1,k) nxt2[to[i].fi]=max(nxt2[to[i].fi],to[i].se);
	For(i,2,n) nxt2[i]=max(nxt2[i],nxt2[i-1]);
	For(i,1,n) ban[i]=ban[i-1]+(nxt2[i-1]<=i-1);
	
//	For(i,1,n)cout<<ban[i]<<" " ; cout<<" ban\n";
	
	For(i,1,n){
		wei[i]=read();
		if(wei[i]==1)pre1[i]=i;
		else pre1[i]=pre1[i-1];
	}
	
//	For(i,1,n) cout<<pre1[i]<<' '; cout<<"pre1\n";
//	For(i,1,n) cout<<nxt2[i]<<" "; cout<<"nxt2\n";
	
	For(i,1,n){
		f[0][i][0]=i;
		f[0][i][1]=max(i,pre1[nxt2[i]]);
	}
	
	For(j,1,19){
		auto F=[&](int i,int k){
			return f[j-1][i][k];
		};
		For(i,1,n){
			f[j][i][0]=max(F(F(i,1),0),F(F(i,0),1));
			f[j][i][1]=max(f[j][i][0],F(F(i,1),1));
			int x=F(i,0); x=max(x,nxt2[x]); x=F(x,0);
			f[j][i][1]=max(f[j][i][1],x);
		}
	}
	
	For(_,1,Q)printf("%d\n",solve());
	return 0;
}
/*
4 3 3
00
00
10
00
110
011
001
1 2 2 2
2
4 3
2 1
*/
```

---

## 作者：是青白呀 (赞：5)

略有一点毒瘤的细节题。

观察到我们每次只能横向打通所有街道，纵向的道路是无法打通的。于是我们对于初始状态的每一个连通块，根据其能到达的最北和最南的路口，将其对应到一个区间 $[l_i,r_i]$ 上。这样问题转变为，给你若干多个目标区间，你可以用 $C_i$ 的时间打通一个点，使所有该点上的区间合并，每次询问将所有目标区间合并的最小时间。

首先考虑 $C=1$ 的单次询问。首先将对询问区间去重，对于有包含关系的区间，可去掉外侧的一个。然后将区间排序，预处理出 $nxt_i$ 表示打通 $i$ 之后，通过 $i$ 处的**任意区间**能到的最右的坐标。然后设当前打通的位置为 $i$，则每次贪心地找到 $i$ 之后的首个**询问区间**的右端点 $r_x$，则下一次打通的位置应当为 $\min(nxt_i,r_x)$。对于有多次询问的情况，不难发现打通 $r_x$ 的操作最多执行询问区间数那么多次，于是对于中途连续跳转 $nxt_i$ 的部分（也即 $i$ 不在任意一个询问区间内）用倍增维护即可。

$C=1$ 或 $2$ 的情况，可以在上述贪心做法下扩展。此时由于 $C=2$ 的点存在，我们需要同时维护多个代价。设 $dp_i$ 表示花费代价 $i$，能**打通**的最靠右的位置。设 $nxtp_i$ 表示打通 $i$ 后，下一次应当打通的位置，也即上一段中的 $\min(nxt_i,r_x)$；设 $pre_i$ 表示 $i$ 及 $i$ 以前的首个 $C=1$ 的位置，则每次有转移 $dp_{i}=\max(nxtp_{dp_{i-2}},pre_{nxtp_{dp_{i-1}}})$，不难发现转移只与前两位有关，可以滚动一下。这个解法同样可以倍增优化。最简单的想法是直接维护 $f_{i,j}$ 表示从打通的 $i$ 开始，花费 $2^j$ 能**打通**的最右侧的位置，但你会发现形如 $2^{j}-1\to2^j+1$ 的代价变化是无法表示的。这种情况显然只会在代价为 $2^j-1$ 时出现，于是预处理 $f_{i,j,0/1}$ 表示从打通的 $i$ 开始，花费为 $2^j-1$，或 $2^j$ 能**打通**的最右侧的点。显然有边界 $f_{i,0,0}=i$，$f_{i,0,1}=\max(i,pre_{nxt_i})$，于是有下面两种转移：

- $f_{i,j,0}=\max (f_{f_{i,j-1,0},j-1,1},f_{f_{i,j-1,1},j-1,0})$；
- $f_{i,j,1}=\max (f_{f_{i,j-1,1},j-1,1},f_{nxt_{f_{i,j-1,0},j-1,0}})$。

当 $dp_i$ 和 $dp_{i-1}$ 均不在任意一个询问区间内时，倍增转移即可。倍增的终点是恰好停在某个询问区间之外，再下一步就进入询问区间了（我们希望首次进入询问区间就停下来，做 $r_x$ 的转移）。这样，我们倍增的总次数仍然是 $\sum T_Q$ 级别的。枚举每一次倍增的幂次 $j$，转移式为：

- $dp_{i-1}=\max (f_{dp_{i-2^j},j,0},f_{dp_{i-2^j-1},j,1})$；
- $dp_i=\max(f_{dp_{i-2^j},j,1},f_{nxt_{dp_{i-2^j-1}},j,0})$。

设首个询问区间的右端点为 $r_1$，最后一个询问区间的左端点为 $l_m$，则初始状态为 $dp_0=0$，$dp_1=pre_{r_1}$。当存在一个 $dp$ 值大于等于 $l_m$ 时就找到答案了。不难发现在 $dp$ 转移过程中，有效的位置永远只有 $2$ 个，所以我们可以只维护当前的两个有效位置及其值。注意需要提前判断无解（即 $r_1$ 和 $l_m$ 中间有无线端覆盖的位置）的情况，维护空隙个数的前缀和即可。最后的答案可能在 $dp_{i}$ 或 $dp_{i-1}$ 的位置取到，两边同时判断即可。

实现时细节较多。时间复杂度 $O(\alpha(HW)+\sum T_Q\log H)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define qingbai 666
using namespace std;
const int N=1e6+5,S=(1<<20)+5,mo1=1e9+9,base1=19491001,mo2=998244353,base2=19260817,inf=1e9+7;
typedef long long ll;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,m,q;
int c[N],nxt[N],pre[N],f[N][22][2],dp[2],cntl,id[N],emp[N];
pii l[N];
int getp(int x,int y){
	return (x-1)*m+y;
}
struct bcj{
	int fa[N];
	void init(){
		rep(i,1,n*m)
		    fa[i]=i;
	}
	int find(int x){
		if(fa[x]==x)return x;
		return fa[x]=find(fa[x]);
	}
	void merge(int x,int y){
		int fx=find(x),fy=find(y);
		if(fx!=fy)fa[fx]=fy;
	}
}B;
bool cmpl(pii x,pii y){
	if(x.fir==y.fir)return x.sec>y.sec;
	return x.fir<y.fir;
}
void solve(){
	int t;
	read(t);
	vector<int>s;
	vector<pii>nl,ql;
	rep(i,1,t){
		int x,y;
		read(x),read(y),s.push_back(id[B.find(getp(x,y))]);
    }
    sort(s.begin(),s.end()),s.erase(unique(s.begin(),s.end()),s.end());
    if(s.size()==1){
    	puts("0");
    	return;
    }
    for(auto i:s)
	    nl.push_back(l[i]);
	sort(nl.begin(),nl.end(),cmpl);
	for(auto i:nl){
		while(ql.size()&&ql.back().fir<=i.fir&&ql.back().sec>=i.sec)
		    ql.pop_back();
		ql.push_back(i);
	}
	int maxl=0,minr=inf;
	for(auto i:ql)
	    maxl=max(maxl,i.fir),minr=min(minr,i.sec);
	if(emp[maxl]-emp[minr]>0){
		puts("-1");
		return;
	}
	int ans=1;
	dp[0]=0,dp[1]=pre[minr],nxt[0]=minr;
	while(dp[1]<maxl&&dp[0]<maxl){
		int lim1=upper_bound(ql.begin(),ql.end(),mp(dp[1],inf))-ql.begin();	    
		int lim0=upper_bound(ql.begin(),ql.end(),mp(dp[0],inf))-ql.begin();
		repp(i,21,0){
		    //注意倍增过程中一定不能进入询问区间内，因为我们希望首次跳到询问区间就停下来.
			int nwv[2];
			nwv[0]=max(f[dp[1]][i][0],f[dp[0]][i][1]);
			nwv[1]=max(f[dp[1]][i][1],f[nxt[dp[0]]][i][0]);
			if(nwv[1]<ql[lim1].fir&&nwv[0]<ql[lim0].fir)dp[0]=nwv[0],dp[1]=nwv[1],ans+=1<<i; 
		}
	    //倍增结束后做一次单独的dp转移即可 
	    int pre0=dp[0],pre1=dp[1];
		dp[0]=pre1,dp[1]=max(min(nxt[pre0],ql[lim0].sec),pre[min(nxt[pre1],ql[lim1].sec)]),ans++;
	}
	if(dp[0]>=maxl)printf("%d\n",ans-1);
	else printf("%d\n",ans);
	return;
}
int main(){
	read(n),read(m),read(q);
	B.init();
	rep(i,1,n){
		string s;
		cin>>s;
		rep(j,1,m-1)
		    if(s[j-1]-'0'==1)B.merge(getp(i,j),getp(i,j+1));
	}
	rep(i,1,n-1){
		string s;
		cin>>s;
		rep(j,1,m)
		    if(s[j-1]-'0'==1)B.merge(getp(i,j),getp(i+1,j));
	}
	rep(i,1,n){
		read(c[i]);
		if(c[i]==1)pre[i]=i;
		else pre[i]=pre[i-1];
	}
	rep(i,1,n*m)
	    l[i]=mp(inf,0);
	rep(i,1,n){
		rep(j,1,m){
			int nwf=B.find(getp(i,j));
			l[nwf]=mp(min(l[nwf].fir,i),max(l[nwf].sec,i));
		}
	}
	rep(i,1,n*m)
		if(B.fa[i]==i)l[++cntl]=l[i],id[i]=cntl;
	rep(i,1,cntl)
	    nxt[l[i].fir]=max(nxt[l[i].fir],l[i].sec);
	rep(i,1,n)
	    nxt[i]=max(nxt[i],nxt[i-1]),emp[i]=emp[i-1]+(nxt[i-1]<i);
	rep(i,1,n)
	    f[i][0][0]=i,f[i][0][1]=max(i,pre[nxt[i]]);
	rep(j,1,21){
		rep(i,1,n){
			f[i][j][0]=max(f[f[i][j-1][0]][j-1][1],f[f[i][j-1][1]][j-1][0]);
			f[i][j][1]=max(f[f[i][j-1][1]][j-1][1],f[nxt[f[i][j-1][0]]][j-1][0]);
		}
    }
	while(q--)
	    solve();
	return 0;
}
```

---

