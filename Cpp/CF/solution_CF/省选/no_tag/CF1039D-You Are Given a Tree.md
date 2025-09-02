# You Are Given a Tree

## 题目描述

一棵树是一个无向图，其中每对顶点之间恰好有一条简单路径。我们称一组简单路径为 $k$-可行集，如果树中的每个顶点至多属于其中一条路径（包括端点），且每条路径恰好包含 $k$ 个顶点。

给定一棵有 $n$ 个顶点的树。对于每个 $k$，$1 \leq k \leq n$，求 $k$-可行简单路径集合的最大可能大小。

## 说明/提示

对于第二个样例，一种达到最优路径数量的方法如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1039D/e329fedb3b5635727a2fc3d6daa41da197dc92a6.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
1 2
2 3
3 4
4 5
5 6
6 7
```

### 输出

```
7
3
2
1
1
1
1

```

## 样例 #2

### 输入

```
6
1 2
2 3
2 4
1 5
5 6
```

### 输出

```
6
2
2
1
1
0

```

# 题解

## 作者：newbiechd (赞：23)

[蒟蒻的Blog](https://www.cnblogs.com/cj-chd/)

[LG传送门](https://www.luogu.org/problemnew/show/CF1039D)

根号分治好题。

这题可以整体二分，但我太菜了，不会。

根号分治怎么考虑呢？先想想$n^2$暴力吧。对于每一个要求的$k$，一遍dfs直接贪心，能拼成链就直接拼，正确性不用我证明吧。

考虑对于$k \le \sqrt n$，直接按照暴力去做，复杂度$O(n \sqrt n)$；对于$k$从$\sqrt n+1$到$n$的所有情况，我们发现答案只会在$\sqrt n$到$0$之间取值（$k> \sqrt n$），且是单调不升的，考虑用一个左往右移的指针来维护求解的过程，可以每次求出一段的值，具体来说是这样：先把指针$i$指向$\sqrt n+1$，然后对于每一个$i$，求出$i$的答案$t$，二分一个与它答案相同的最右边的点，并把这一段的答案更新为$t$，这样最多二分$\sqrt n$次（最多只有$\sqrt n$种答案），每次二分（算上check）的复杂度是$O(n logn)$，所以这部分的复杂度就是$O(n \sqrt n log n)$，总的复杂度也就是$O(n \sqrt n log n)$。

上面把分治的节点默认为$\sqrt n$只是为了理解起来直观，事实上复杂度还可以更优。我们发现两块的复杂度还不是很平衡，设分治的节点是$T$，那么第一块的复杂度就是$Tn$，第二块就是$\frac{n^2 log n}{T}$。要使复杂度最低，就应该取$T=\sqrt{n log n}$。这样的程序运行效率（理论结果）大概是取$T$为$\sqrt n$的两倍。

```cpp
#include<cstdio>
#include<cctype>
#include<cmath>
#define R register
#define I inline
using namespace std;
const int S=100003,N=200003;
char buf[1000000],*p1,*p2;
I char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,S,stdin),p1==p2)?EOF:*p1++;}
I int rd(){
	R int f=0; R char c=gc();
	while(c<48||c>57) c=gc();
	while(c>47&&c<58) f=f*10+(c^48),c=gc();
	return f;
}
int h[S],s[N],g[N],p[S],d[S],f[S],o[S],n,c,e;
I int max(int x,int y){return x>y?x:y;}
I void add(int x,int y){s[++c]=h[x],h[x]=c,g[c]=y;}
void dfs(int x,int f){
	for(R int i=h[x],y;i;i=s[i])
		if((y=g[i])^f)
			dfs(y,x);
	p[x]=f,d[++e]=x;
}
I int slv(int k){
	R int i,x,r=0;
	for(i=1;i<=n;++i)
		f[i]=1;
	for(i=1;i<=n;++i){
		x=d[i];
		if(p[x]&&(~f[p[x]])&&(~f[x]))
			if(f[x]+f[p[x]]>=k)
				++r,f[p[x]]=-1;
			else
				f[p[x]]=max(f[p[x]],f[x]+1);
	}
	return r;
}
int main(){
	R int q,i,j,x,y,t,l,r,m;
	n=rd(),q=sqrt(n*log(n)/log(2));
	for(i=1;i<n;++i)
		x=rd(),y=rd(),add(x,y),add(y,x);
	dfs(1,0),o[1]=n;
	for(i=2;i<=q;++i)
		o[i]=slv(i);
	for(i=q+1;i<=n;i=l+1){
		l=i,r=n,t=slv(i);
		for(;l<r;slv(m)^t?r=m-1:l=m)
			m=l+r+1>>1;
		for(j=i;j<=l;++j)
			o[j]=t;
	}
	for(i=1;i<=n;++i)
		printf("%d\n",o[i]);
	return 0;
}

```

鸣谢：@fwat julao

---

## 作者：Alex_Wei (赞：21)

> II. [CF1039D You Are Given a Tree](https://www.luogu.com.cn/problem/CF1039D)。

> 题意简述：给出一棵树，对每个 $k\in[1,n]$，求出最多能找出多少条没有公共点的至少经过 $k$ 个点的链。

> 本文选自 [根号分治专题](https://www.cnblogs.com/alex-wei/p/square_root_divide_and_conquer.html)。

---

注意到若 $k>\sqrt n$ 则答案一定不大于 $\sqrt n$。那么对于 $1\leq k\leq \sqrt n$，直接暴力树形 DP。然后再枚举 $1\leq ans\leq \sqrt n$，不过这次枚举的是**链的条数**，即答案。显然答案单调不升，于是二分出答案为 $ans$ 的 $k$ 的区间即可（实际上不需要右端点，只需要左端点）。

树形 DP 求链上经过的点 $k$ 的答案：该部分比较类似 [赛道修建](https://www.luogu.com.cn/problem/P5021)，不过也有一些区别：因为一个点只能被一条链经过（而不是赛道修建中的一条边），于是分两种情况讨论：记 $mx_1,mx_2$ 为 $i$ 的儿子所传入的最长的两条链（所经过点的个数），若 $mx_1+mx_2+1\geq k$，那么显然是将 $i$ 与它的两个儿子配成一条链，答案加 $1$；否则将 $mx_1+1$ 传上去到 $fa_i$ 即可。这样一次 DP 就是 $\mathcal{O}(n)$ 的。

因此，总时间复杂度为 $\mathcal{O}(n\sqrt n\log n)$。

卡常技巧：将每个节点的父亲预处理出来，然后按照 dfs 序排序，可以直接循环树形 DP，不需要 dfs。

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/


//#pragma GCC optimize(3)

#include <bits/stdc++.h>
using namespace std;

#define mem(x,v) memset(x,v,sizeof(x))

namespace IO{
	char buf[1<<21],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
	#ifdef __WIN32
		#define gc getchar()
	#else
		#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
	#endif
	#define pc(x) (*O++=x)
	#define flush() fwrite(obuf,O-obuf,1,stdout)

	inline int read(){
		int x=0,sign=0; char s=gc;
		while(!isdigit(s))sign|=s=='-',s=gc;
		while(isdigit(s))x=(x<<1)+(x<<3)+(s-'0'),s=gc;
		return sign?-x:x;
	}
	void print(ll x) {if(x>9)print(x/10); pc(x%10+'0');}
}

using namespace IO;

const int N=1e5+5;

int ed,ed2,hd[N],nxt[N<<1],to[N<<1];
pii nw[N];
void add(int u,int v){
	nxt[++ed]=hd[u],hd[u]=ed,to[ed]=v;
}
int n,p,cnt,ans[N];

void dfs0(int id,int f){
	for(int i=hd[id];i;i=nxt[i]){
		if(to[i]==f)continue;
		nw[++ed2]={id,to[i]},dfs0(to[i],id);
	}
}
int dfs(int id){
	int mx=0,mx2=0;
	for(int i=hd[id];i;i=nxt[i]){
		int v=dfs(to[i]);
		if(v>=p){cnt++; return 0;}
		if(v>=mx)mx2=mx,mx=v;
		else if(v>=mx2)mx2=v;
	} if(mx+mx2+1>=p){cnt++; return 0;}
	return mx+1;
} int run(int x){
	cnt=0,p=x,dfs(1);
	return cnt;
}

int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int a=read(),b=read();
		add(a,b),add(b,a);
	} int m=sqrt(n*log2(n));
	dfs0(1,0),mem(hd,0),mem(nxt,0),ed=0;
	for(int i=1;i<n;i++)add(nw[i].fi,nw[i].se);
	for(int i=1;i<=m;i++)ans[i]=run(i);
	for(int i=1,pre=n+1;i<=n/m+1;i++){
		int l=1,r=pre;
		while(l<r){
			int m=(l+r>>1)+1;
			if(run(m)>=i)l=m;
			else r=m-1;
		} for(int j=l+1;j<pre;j++)ans[j]=i-1; pre=l+1;
	} for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
	return flush(),0;
}
```

---

## 作者：Strelitzia (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/CF1039D)

前置知识：根号分治。

挺好一题吧……

基本思路，我们可以有最基本的想法，就是贪心，我们从每棵子树底遍历。

遇到能接上后长度大于 k 的，就接上，至于正确性……可以自己手玩，发现是正确的……~~贪心需要证明还叫贪心吗？？~~

可惜啊可惜，一次贪心是 $\text{O}(n)$ 的，你求 $1 ... n$ 就是 $\text O(n^2)$ 的好算法。

我们发现，随着 k 的增大，这个答案啊，是一直变小的哦。

还可以发现，在 $k > \sqrt n$，时，答案的取值也只有 $\sqrt n$ 种，挺少的。

对于 $k \leq \sqrt n$，直接来，时间复杂度是 $\text O(n\sqrt n)$ 的。

剩下的部分，我们可以二分有哪些值是相同的，最多也只需要 $\sqrt n$ 次，时间复杂度为 $\text{O}(\frac{n^2\log n}{\sqrt n})$。

总的时间复杂度就是 $\text{O}(n\sqrt n + \frac{n^2 \log n}{\sqrt n})$，但是但是，这样不是最优的。

我们设分治的点是 $T$，时间复杂度为$\text{O}(nT + \frac{n^2 \log n}{T})$

对于这两项，他们乘起来是定值，可以用基本不等式来搞，时间复杂度最小为 $2 \times \sqrt{n^3 \log n}$。

也就是 $nT = \frac{n ^ 2 \log n}{T}$ 时，可解得 $T = \sqrt{n \log n}$，这算个根号分治的小优化吧。


代码如下：

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;

int nxt[N << 1],ver[N << 1],head[N],tot;
void addEdge(int u,int v) {nxt[++ tot] = head[u];ver[tot] = v;head[u] = tot;}

int tim,n;
int fa[N],dfn[N],ans[N],f[N];

void dfs(int u,int pre) {
	fa[u] = pre;
	for (int e = head[u] ; e ; e = nxt[e]) {
		int v = ver[e];
		if (v == pre)
			continue;
		dfs(v,u);
	}
	dfn[++ tim] = u;
}

int solve(int k) {
	int res = 0;
	for (int i = 1 ; i <= n ; ++ i)
		f[i] = 1;
	for (int i = 1 ; i <= n ; ++ i) {
		int u = dfn[i];
		int fath = fa[u];
		if (fath && f[u] != -1 && f[fath] != -1) {
			if (f[u] + f[fath] >= k)
				res ++,f[fath] = -1;
			else
				f[fath] = max(f[fath],f[u] + 1);
		}
	}
	return res;
}

int main () {
	scanf("%d",&n);
	int u,v;
	int p = sqrt(n * log2(n));
	for (int i = 1 ; i < n ; ++ i) {
		scanf("%d %d",&u,&v);
		addEdge(u,v);addEdge(v,u);
	}
	dfs(1,0);
	ans[1] = n;
	for (int i = 2 ; i <= p ; ++ i)
		ans[i] = solve(i);
	for (int i = p + 1 ; i <= n ; ++ i) {
		int tmp = solve(i);
		int l = i,r = n,ass = i;
		while (l < r - 1) {
			int mid = l + r >> 1;
			if (solve(mid) == tmp)
				l = mid,ass = max(ass,mid);
			else
				r = mid;
		}
		for (; i <= ass ; ++ i)
			ans[i] = tmp;
		-- i;
	}
	for (int i = 1 ; i <= n ; ++ i)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：CarroT1212 (赞：7)

根号分治神仙题。

+ 有一棵 $n$ 个节点的树。
+ 其中一个简单路径的集合被称为 $k$ 合法当且仅当：树的每个节点至多属于其中一条路径，且每条路径恰好包含 $k$ 个点。
+ 对于 $k\in [1,n]$，求出 $k$ 合法路径集合的最多路径。即：设 $k$ 合法路径集合为 $S$，求最大的 $|S|$。
+ $n \leq 10^5$。**7s**。

首先考虑如果 $k$ 是定值，能不能快速求出答案。一眼感觉挺像树形 DP，实际上不完全是。

假设现在位于 $p$ 点，则路径的选取有两种可能：选一个儿子接到 $p$ 上形成一条长度加 $1$ 的链，继续往上接；选两个儿子和 $p$ 接起来形成一条长度为两个儿子下面接的链的长度加上 $1$ 的链，上面重新开一条新链。

如果是第一种情况的话显然取子树里那条最长的链往上连是最优的，更容易出现长度足够的路径。

考虑什么时候用第二种情况。设它的儿子所在的最长、次长链分别为 $a,b$。首先直接取 $a,b$ 来配是最容易出现长度达到 $k$ 的新路径的。

然后猜有这么个结论：如果 $a,b$ 配起来长度达到 $k$，那么先把 $a,b$ 放到一起配成新路径是肯定不会比单独取 $a$ 往上连的结果要劣的。当然如果配不上就不得不选第一种情况了。

发现大概是可以证明的。设最长、次长链分别为 $a,b$，且 $a+b+1\ge k$。

+ 如果把 $a$ 继续往上连也找不到长度达到 $k$ 的方式，那么你显然亏了。
+ 如果 $a$ 往上连，它自身长度达到了 $k$ 或是与另一条链组合达到了 $k$，即存在一种让这条链达到 $k$ 的方式，
	+ 那么如果你在这里把 $a,b$ 连起来，重开一条链往上走，还是有可能存在另一种使这条链长度达到 $k$ 的方式，这样你不连的话依然亏了。
	+ 当然也可能确实重开之后就没有办法达到 $k$ 了，不幸损失一条路径，但是同时下面 $a,b$ 又连成了一条新路径，这样也仅仅是不亏不赚而已，没有什么影响。

有种循环论证的美，不咋严谨，感性理解。

于是我们获得了一个 $O(n^2)$ 的过不了做法。

发现 $k$ 与答案的乘积不会超过 $n$，启动根号分治。

当 $k\le \sqrt{n}$ 的时候，直接按上面方法贪心预处理求出每一个点在每一个 $k$ 下的答案即可。

当 $k>\sqrt{n}$ 的时候，答案不会超过 $\sqrt{n}$。考虑反过来枚举答案，求有哪些 $k$ 是这个答案。意识到答案随 $k$ 的增大而减小，于是答案相等的 $k$ 一定在一段区间内，二分跑 $\log n$ 次树形 DP 求出每个答案第一次被取到的 $k$ 即可。

于是我们获得了一个 $O(n\sqrt{n}\log n)$ 的理论能过做法。

然而实践发现被卡常了，所以有几个小优化：

+ 可以把 dfs 序和每个点的祖先预处理出来再按顺序跑，除掉递归的常数。到这里 6s。
+ 每次二分的时候并不需要对整个 $[1,n]$ 都找一遍。如果从小到大枚举答案的话，你已经确定了前面答案所在的区间，位于整个 $[1,N]$ 的尾部，那把二分右端点放在上一个答案的前一位跑就够了。到这里 3s。
+ 注意到按 $\sqrt{n}$ 分割的话两部分做法时间复杂度并不统一，理论上取 $\sqrt{n\log n}$ 才是最优的。到这里 2s。

```cpp
int n,m,ans[N];
int co[N],cnn,fa[N];
int len[N],mx[N],cx[N];
vector<int> e[N];
void dfs(int p,int f) {
	co[++cnn]=p;
	for (int i:e[p]) if (i!=f) dfs(i,p),fa[i]=p;
}
int calc(int k) {
	int p,f,res=0;
	for (int j=n;j;j--) {
		p=co[j],f=fa[p];
		if (mx[p]+cx[p]+1>=k) res++,len[p]=0;
		else len[p]=mx[p]+1;
		if (len[p]>mx[f]) cx[f]=mx[f],mx[f]=len[p];
		else if (len[p]>cx[f]) cx[f]=len[p];
		mx[p]=cx[p]=0;
	}
	return res;
}
int main() {
	memset(ans,-1,sizeof(ans));
	scanf("%d",&n),m=sqrt(n*(ll)log2(n));
	for (int i=1,x,y;i<n;i++) scanf("%d%d",&x,&y),e[x].pb(y),e[y].pb(x);
	dfs(1,0);
	for (int i=1;i<=m;i++) ans[i]=calc(i);
	for (int i=0,lst=n;i*m<=n;i++) {
		int l=1,r=lst,mid,res=1;
		while (l<=r) {
			mid=l+r>>1;
			if (calc(mid)<=i) r=mid-1,res=mid;
			else l=mid+1;
		}
		if (calc(res)==i) ans[res]=i,lst=res;
	}
	for (int i=1;i<=n;i++) {
		if (ans[i]==-1) ans[i]=ans[i-1];
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：evenbao (赞：6)

设f( i )表示i条路径的答案

首先考虑一棵n个节点的树 ， 当它是一条链时 ， 能分成最多不相交路径 ， 所以有 : 
f( i ) <= n / i


观察到f是不增的 ， 并且相同的f值至少sqrt(n)段 ， 所以我们可以像数论分块那样对每一段分别求解

考虑如何计算f( i ) , 设dpi表示以i为根的节点最多能分成多少条路径 ， 简单转移即可

复杂度是O(n * sqrt(n) * log(n))的 ， 由于常数较大 ， dp时要先预处理这棵树的DFS序 ， 按DFS序从下往上dp

代码 :

```cpp
#include<bits/stdc++.h>
using namespace std;

#ifndef LOCAL
	#define eprintf(...) fprintf(stderr , _VA_ARGS)
#else
	#define eprintf(...) 42
#endif

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int , int> pii;
#define MP make_pair
#define fi first
#define se second
const int N = 2e5 + 10;

struct edge {
	int to , nxt;
} e[N << 1];

int n , tot , timer;
int head[N] , dp[N] , max_1[N] , max_2[N] , rem[N] , dfn[N] , pm[N] , ans[N] , fa[N];
 
template <typename T> inline void chkmin(T &x , T y) { x = min(x , y); }
template <typename T> inline void chkmax(T &x , T y) { x = max(x , y); }
template <typename T> inline void read(T &x) {
   T f = 1; x = 0;
   char c = getchar();
   for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
   for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - '0';
   x *= f;
}
inline void dfs(int u , int par) {
	dfn[u] = ++timer; pm[u] = u;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == par) continue;
		fa[v] = u;
		dfs(v , u);
	} 
}
inline void addedge(int u , int v) {
	++tot;
	e[tot] = (edge){v , head[u]};
	head[u] = tot;
}
inline bool cmp(int x , int y) {
	return dfn[x] > dfn[y];
}
inline void solve(int K) {
	memset(dp , 0 , sizeof(dp));
	memset(rem , 0 , sizeof(rem));
	memset(max_1 , 0 , sizeof(max_1));
	memset(max_2 , 0 , sizeof(max_2));
	for (int i = 1; i <= n; ++i) {
		int u = pm[i];
		if (max_1[u] + max_2[u] + 1 >= K) {
			++dp[u];
			rem[u] = 0;
		} else rem[u] = max_1[u] + 1;
		int father = fa[u];
		dp[father] += dp[u];
		if (rem[u] > max_1[father]) {
			max_2[father] = max_1[father];
			max_1[father] = rem[u];
		} else if (rem[u] > max_2[father]) max_2[father] = rem[u];
	}
	ans[K] = dp[1];
	return;
}

int main() {
	
	read(n);
	for (int i = 1; i < n; ++i) {
		int u , v;
		read(u); read(v);
		addedge(u , v);
		addedge(v , u);
	}
	dfs(1 , 0);
	sort(pm + 1 , pm + n + 1 , cmp);
	for (int i = 1; i <= n; ++i) 
		ans[i] = -1;
	ans[1] = n;
	int L , R;
	ans[1] = n;
	for (L = 2; L <= n; L = R + 1) {
		if (ans[L] == -1) solve(L);
		int l = L , r = n , res = L;
		while (l <= r) {
			int mid = l + r >> 1;
			if (ans[mid] == -1) solve(mid);
			if (ans[mid] == ans[L]) {
				res = mid;
				l = mid + 1;
			} else r = mid - 1;
		} 	
		R = res;
		for (int i = L; i <= R; ++i)
			ans[i] = ans[L];
	}
	for (int i = 1; i <= n; ++i)
		printf("%d\n" , ans[i]);
		
    return 0;
}
```



---

## 作者：DengDuck (赞：5)

咋都在写根号分治，这题为啥要根号分治啊。

首先考虑对于固定的 $k$ 咋求，发现有一个 $\mathcal O(n)$ 的贪心，就是直接深搜，搜到一个 $k$ 的链直接选。

为啥是对的呢？因为在我这里可以构成链，下面就不能构成，能构成链已经选了，而如果这时候不选留到上面合并并不优，顶多达成平手。

然后我们发现答案不会超过 $\lfloor\dfrac n k\rfloor$，根据我们的认识，答案不会超过 $2\sqrt n$ 种，也就是说大量的答案是重复的。

同时我们发现答案单调不升，这一点显然，所以相同的答案应该是一个连续的区间。

考虑用二分求出这个端点，给整个区间打标记，然后我们只需要求解这个区间后面的 $k$ 就行了。

时间复杂度显然为 $\mathcal O(n\sqrt n\log n)$。

但是为什么要根号分治呢？根号分治也是这个时间复杂度吧，我这份代码踩了很多坑，比如用 `vector`，但是还是可以过啊，而且并不比根号分治的慢多少啊（我不会优化常数，有兴趣的大佬可以自己试试）。

需要注意有两个关键优化，一个是求过的值要记忆化下来，一个是这题略卡常，朴素的深搜贪心过不了，要用 DFS 序保存下来跑。
```cpp
#include<bits/stdc++.h>
#define LL int
using namespace std;
const LL N=1e5+5;
vector<LL>v[N];
LL n,x,y,ans[N],f[N],tot,dfn[N],dad[N];
inline LL read() 
{
	char c = getchar();
	LL sum = 0;
	while (c < '0' || c > '9') c = getchar();
	do 
	{
		sum = (sum << 3) + (sum << 1) + c - '0';
		c = getchar();
	} while (c >= '0' && c <= '9');
	return sum;
}
void dfs(LL x,LL fa)
{	
	dad[x]=fa;
	dfn[++tot]=x;
	for(LL i:v[x])
	{
		if(i==fa)continue;
		dfs(i,x);
	}
	return;
}
LL work(LL x)
{
	if(ans[x]!=-1)return ans[x];
	for(int i=1;i<=n;i++)f[i]=1;
	LL cnt=0;
	for(int i=n;i>=1;i--)
	{
		LL t=dfn[i];
		if(f[t]>=x)
		{
			f[t]=-1;
			cnt++;
		}
		if(f[dad[t]]+f[t]>=x&&f[t]!=-1&&f[dad[t]]!=-1&&dad[t])
		{
			f[dad[t]]=-1;
			cnt++;
		}
		else if(f[dad[t]]!=-1)f[dad[t]]=max(f[dad[t]],f[t]+1);
	}
	return cnt;
}
int main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		x=read(),y=read();
		v[x].push_back(y);
		v[y].push_back(x);
	}	
	for(int i=1;i<=n;i++)ans[i]=-1;
	LL t=1;
	dfs(1,0);
	while(t<=n)
	{
		LL l=t,r=n,pos=0,k=work(t);
		while(l<=r)
		{
			LL mid=(l+r)/2;
			LL t=work(mid);
			ans[mid]=t;
			if(t==k)l=mid+1,pos=mid;
			else r=mid-1;
		}
		ans[pos]=k;
		t=pos+1;
	}

	for(int i=n-1;i>=1;i--)
	{
		ans[i]=max(ans[i],ans[i+1]);
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d\n",ans[i]);
	}
}
```

---

## 作者：james1BadCreeper (赞：5)

如果 $k$ 给定，那么考虑 $O(n)$ 树形 DP（因为只要能选一定不劣）就可解决。

发现答案的取值比较少。考虑根号分治，对于小于等于 $B$ 的部分可以直接 $O(n)$ 树形 DP 解决（需要卡常，考虑转到 DFS 序上 DP）。

大于阈值的部分发现答案只有 $\dfrac{n}{B}$ 种，考虑二分哪些部分的答案是一样的，只会进行 $\dfrac n B$ 次二分，时间复杂度为 $O(\dfrac n B n\log n)$。

取 $B=\sqrt{n\log n}$，理论最优时间复杂度为 $O(n\sqrt{n\log n})$。


```cpp
#include <bits/stdc++.h>
using namespace std; 
const int BLOCK_SIZE = 600; 

int n, ans[100005]; 
int fa[100005], num, idx[100005]; 
int f[100005]; 
vector<int> G[100005]; 

void dfs(int x, int fa) {
	::fa[x] = fa; 
	for (int y : G[x]) if (y != fa) dfs(y, x); 
	idx[++num] = x; 
}
int solve(int k) {
	int res = 0; f[0] = -1; 
	for (int i = 1; i <= n; ++i) f[i] = 1;  
	for (int i = 1; i <= n; ++i) {
		int x = idx[i]; 
		if (f[fa[x]] != -1 && f[x] != -1) {
			if (f[x] + f[fa[x]] >= k) ++res, f[fa[x]] = -1; 
			else f[fa[x]] = max(f[fa[x]], f[x] + 1); 
		}
	}
	return res; 
}

int main(void) {
	scanf("%d", &n); 
	for (int i = 1; i < n; ++i) {
		int u, v; scanf("%d%d", &u, &v); 
		G[u].emplace_back(v); G[v].emplace_back(u); 
	} ans[1] = n; dfs(1, 0); 
	for (int k = 2; k <= BLOCK_SIZE; ++k) ans[k] = solve(k); 
	for (int k = BLOCK_SIZE + 1; k <= n; ) {
		int L = k - 1, R = n + 1, res = solve(k); 
		while (L + 1 != R) {
			int mid = L + R >> 1; 
			if (res == solve(mid)) L = mid; 
			else R = mid; 
		}
		for (int i = k; i <= L; ++i) ans[i] = res; 
		k = R; 
	}
	for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]); 
	return 0; 
}
```


---

## 作者：int_R (赞：4)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/18415137/CF1039D)

咋其他题解都带根号？根号是坏文明，这里是俩 $\log$ 做法，能够跑到 $300$ ms 以内。

首先考虑暴力贪心，从叶子向根合并，可以取出一条链的时候就取出来，否则就连一条尽可能长的链往上合并。

具体的设 $f_{x,i}$ 为当 $k=i$ 时，在 $x$ 处能取出的最长链。那么也就是从 $f_{y,i},y\in son(x)$ 中选出最大值和次大值，如果连起来长度 $\geq i$，那么答案加一，将 $f_{x,i}$ 置为 $0$；否则 $f_{x,i}$ 等于儿子中最大值加一。这东西肯定是 $O(n^2)$ 的，考虑优化。

----

记 $siz_x$ 是 $x$ 及其子树大小，$d_x$ 为 $x$ 子树中最深点与 $x$ 的距离加一。

有一个比较常见的 trick 是树剖，然后直接继承重儿子的 $f$ 值，从这点上看这个做法可能类似 dsu on tree。

那么现在操作变成了，继承时对全局加一，然后在轻儿子中找到最大值和次大值，进行更新。

首先不难发现，子树中选出一条最长链的长度是不超过子树大小的，换句话来说，当 $i>siz_x$，$f_{x,i}=d_x$。

那么也就意味着，我们记 $MS(x)$ 为 $x$ 的轻儿子中 $siz$ 最大值，那么对所有 $i>MS(x)$ 的更新都是相同的。

然后我们发现，经典结论所有轻儿子的 $siz$ 和是 $O(n\log n)$ 级别的；所有长度的答案和是调和级数，是 $O(n\ln n)$ 级别的。

如果我们可以对 $i>MS(x)$ 的修改打包，每次只暴力更新 $i\leq MS(x)$ 的位置和所有可以贡献到答案的位置，时间复杂度就是对的。

而由于我们需要找出一段区间中所有满足一定条件的位置，所以考虑线段树。

----

首先一条链的线段树的大小是 $siz_{top}$ 的（$top$ 表示这条链的链头），这个东西的和自然也是 $O(n\log n)$ 级别的。

我们可以在线段树上维护区间 $f_{x,i}-i$ 最大值，具体的怎么判断是否可以贡献到答案就是三条链里取两条长的，不多说了。

$i\leq MS(x)$ 的部分就直接先暴力把所有轻儿子的线段树上维护的值取出来，然后预处理取完 $\max$ 后再暴力递归到当前线段树的叶子节点修改。

$i> MS(x)$ 打包修改的部分就相当于如果区间中有可以贡献到答案的位置就继续递归，否则打一个区间加、区间取 $\max$ 的 tag，值得注意的是我们先前维护的 $f_{x,i}-i$ 最大值可能可以被区间取的 $\max$ 影响，比方说区间 $\max$ 是 $s$ 的话，那个最大值是要和 $s-l$（$l$ 是区间的左端点）取 $\max$ 的。

那么总时间复杂度就是 $O(n\log^2 n)$ 的，实际上你修改都是一起修改的，所以大概常数还很小，薄纱一众根号做法。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#define ll long long
using namespace std;
const int MAXN=1e5+10;
int n,d[MAXN],siz[MAXN],h[MAXN],top[MAXN],ans[MAXN];
vector <int> v[MAXN];typedef pair<int,int> P;P f[MAXN];
inline void max(P &x,int y)
{
    if(y>x.first) swap(y,x.first);
    if(y>x.second) x.second=y;
}
inline void max(P &x,P y)
    {max(x,y.first),max(x,y.second);}
namespace segment_tree
{
    #define LS t[t[p].ls]
    #define RS t[t[p].rs]
    int R[MAXN],tot;queue <int> q;
    struct node{int num,add,s,ls,rs,l;}t[MAXN<<5];
    inline int N()
    {
        if(q.empty()) return ++tot;
        int x=q.front();q.pop();return x;
    }
    inline void add(int p,int c,int z)
    {
        t[p].add+=c,t[p].s=max(t[p].s+c,z);
        t[p].num=max(t[p].num+c,t[p].s-t[p].l);
    }
    inline void push_up(int p)
        {t[p].num=max(LS.num,RS.num);}
    inline void push_down(int p)
    {
        add(t[p].ls,t[p].add,t[p].s);
        add(t[p].rs,t[p].add,t[p].s);
        t[p].add=t[p].s=0;return ;
    }
    void build(int l,int r,int p)
    {
        t[p].l=l;if(l==r){t[p].num=-l+1;return ;}
        int mid=(l+r)>>1;
        build(l,mid,t[p].ls=N());
        build(mid+1,r,t[p].rs=N());
        push_up(p);return ;
    }
    void get(int l,int r,int p)
    {
        if(l==r)
        {
            max(f[l],t[p].num+l);
            t[p]={},q.push(p);return ;
        }
        int mid=(l+r)>>1;push_down(p);
        if(t[p].ls) get(l,mid,t[p].ls);
        if(t[p].rs) get(mid+1,r,t[p].rs);
        t[p]={},q.push(p);return ;
    }
    void upd(int l,int r,int p,int x,int S,int D)
    {
        if(l>x&&S<l&&t[p].num+D+1<0)
            {add(p,1,D+1);return ;}
        if(l==r)
        {
            t[p].s=0;if(l<=x)
            {
                int S=f[l].first+max(f[l].second,t[p].num+l)+1;
                if(S>=l) ++ans[l],t[p].num=-l;
                else t[p].num=max(t[p].num,f[l].first-l)+1;
            }
            else ++ans[l],t[p].num=-l;return ;
        }
        int mid=(l+r)>>1;push_down(p);
        upd(l,mid,t[p].ls,x,S,D);
        upd(mid+1,r,t[p].rs,x,S,D);
        push_up(p);return ;
    }
};using namespace segment_tree;
void dfs(int x,int fa=0)
{
    P D={0,0};siz[x]=1;
    for(int y:v[x])
    {
        if(y==fa) continue;
        dfs(y,x),max(D,d[y]),siz[x]+=siz[y];
        if(siz[y]>siz[h[x]]) h[x]=y; 
    }
    d[x]=D.first+1;
}
void calc(int x,int fa=0)
{
    if(!h[x])
    {
        if(siz[top[x]]>=2)
            build(2,siz[top[x]],R[x]=N());
        return ;
    }
    top[h[x]]=top[x],calc(h[x],x),R[x]=R[h[x]];
    for(int y:v[x])
        if(y!=fa&&y!=h[x]) top[y]=y,calc(y,x);
    P MD={0,0};int MS=0;
    for(int y:v[x])
    {
        if(y==fa||y==h[x]) continue;
        max(MD,d[y]),MS=max(MS,siz[y]);
        max(f[siz[y]+1],d[y]);
    }
    for(int i=2;i<=MS;++i) max(f[i],f[i-1]);
    for(int y:v[x])
        if(y!=fa&&y!=h[x]&&siz[y]>=2) get(2,siz[y],R[y]);
    int D=MD.first,S=MD.first+MD.second+1;
    upd(2,siz[top[x]],R[x],MS,S,D);
    for(int i=2;i<=MS+1;++i) f[i]={0,0};return ;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n;for(int i=1,x,y;i<n;++i)
        cin>>x>>y,v[x].push_back(y),v[y].push_back(x); 
    dfs(1),top[1]=1,calc(1),ans[1]=n;
    for(int i=1;i<=n;++i) cout<<ans[i]<<'\n';
    return 0;
}
```

---

## 作者：Doubeecat (赞：4)

> [CF1039D You Are Given a Tree](https://www.luogu.com.cn/problem/CF1039D)
>
> - 有一棵 $n$ 个节点的树。
>
> - 其中一个简单路径的集合被称为 $k$ 合法当且仅当：
>
> - 树的每个节点至多属于其中一条路径，且每条路径恰好包含 $k$ 个点。
>
> - 对于 $k\in [1,n]$，求出 $k$ 合法路径集合的最多路径数
> - 即：设 $k$ 合法路径集合为 $S$，求最大的 $|S|$。
>
> $n \leq 10^5$

<!--more-->

## 解题思路：

分治（整体二分）

首先可以观察一下这个问题的一些性质，很显然，我们考虑对于这个合法路径的答案取值其实最多只有 $\sqrt{n}$ 种并且**具有单调性**，这个的证明非常显然，类似数论分块的证明。

接下来想下暴力怎么做，我们对于单独的一个 $k$ 来考虑。首先，每个点最多只可能在一条链中，这给我们贪心提供了一个正确性的保证。对于一个点，如果当前点**有一条拐弯的最长链**长度大于等于 $k$，我们就贪心划分成一条答案所需要的链。

![image-20220310144247767](https://s2.loli.net/2022/03/10/HQAk6CWbDltmZuv.png)

如图，红色圈起来的就是一条拐弯的最长链。

否则，我们这个节点保存一个**不拐弯的最长链**长度 $f_x$ 以供接下来使用。

![image-20220310144401233](https://s2.loli.net/2022/03/10/D7zH4RohuGlOMIb.png)

如图，红色圈起来的就是一条不拐弯的最长链。

接下来考虑分治，有点类似**整体二分**（其实我个人是按整体二分来理解的，但是被机房学长纠正说不是整体二分），在分治过程中，我们对于 $k \in [L,R]$ ，答案属于 $[l,r]$ 的询问进行分治。每次选取 $mid = \lfloor \frac{L+R}{2}\rfloor$ 进行 dfs，得出的答案记为 $tmp$，那么对于 $k \in [L,mid]$ 来说，答案属于 $[l,tmp]$，对于 $k \in [mid + 1,R]$ 来说，答案属于 $[tmp,r]$ ，当 $l = r$ 时，我们就将 $[L,R]$ 的答案全部赋为 $l$。

这样，我们的时间复杂度就做到了 $\mathcal{O}(n \sqrt{n} \log n)$，这个复杂度感性理解即可（因为我也不会证是机房学长告诉我的orz，如果有dalao会证也可以在评论区，目前的想法是分治树有 $\log n$ 层，答案有 $\sqrt{n}$ 个，分治的过程就是 $n \log n \times \sqrt{n}$）

注意这个东西常数非常大……你需要一些卡常技巧，这里提供一个亲测能过的。首先把原图存下来，然后 dfs 一遍，确定每个点的父子关系，然后**只保存从父亲到儿子**的边，能快一半以上，具体可以看代码。

## 代码：

```cpp
const int N = 1e5 + 10;

int n,ans[N],f[N],cnt;
vector <int> G[N];
int hd[N],nxt[N<<1],to[N<<1],tot;

inline void addedge(int u,int v) {
	to[++tot] = v;nxt[tot] = hd[u];hd[u] = tot;
}

void dfs(int x,int fa,int k) {
    f[x] = 0;
    int maxx = 0,secmax = 0;
    for (int i = hd[x];i;i = nxt[i]) {
        int y= to[i];
        if (y != fa) {
            dfs(y,x,k);
            if (f[y] > maxx) {
                secmax = maxx;
                maxx = f[y];
            } else {
                secmax = max(secmax,f[y]);
            }
        }
    }
    if (maxx + secmax + 1 >= k) ++cnt,f[x] = 0;
    else f[x] = maxx + 1;
}

void solve(int l,int r,int L,int R) {
    if (l > r || L > R) return ;
    if (L == R) {
        for (int i = l;i <= r;++i) {
            ans[i] = L;
        }//sqrtn
        return ;
    }
    int mid = (l + r) >> 1;
    cnt = 0;
    dfs(1,0,mid);
    ans[mid] = cnt;
    solve(l,mid - 1,cnt,R);//越短越多.
    solve(mid + 1,r,L,cnt);
}

void prework(int x,int fa) {
    for (auto y : G[x]) {
        if (y != fa) {
            addedge(x,y);
            prework(y,x);
        }
    }
}

signed main() {
    read(n);
    for (int i = 1;i < n;++i) {
        int x,y;read(x);read(y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    prework(1,0);
    solve(1,n,0,n);
    for (int i = 1;i <= n;++i) writeln(ans[i]);
}
```


---

## 作者：1saunoya (赞：4)

考虑到 $ans_{i+1} \leq ans_i$
且 $ans_{i} \leq \frac{n}{i}$

然后胡乱分析一波，考虑根号分治，一部分暴力，一部分按根号的性质来，考虑到块取成 $q$，一部分暴力的复杂度是 $nq$，然后你发现剩下的值域仅仅是 $[0,\frac{n}{q}]$，由于这个部分你需要一个二分，所以复杂度带个 $\log$，考虑到每个块，然后剩下的部分复杂度就是 $\frac{n}{q} n \log n$，所以把两部分搞起来，理论复杂度是 $nq+\frac{n}{q} n \log n$

$nq+\frac{n}{q} n \log n = n(q + \frac{n}{q}\log n)$，发现 $q = \sqrt {n \log n}$ 的时候取到最优复杂度，显然实际上不是这样的，因为每个不可能都取到 $\frac{n}{i}$，所以需要把块搞小一点233，200左右就够了

```cpp
// powered by c++11
// by Isaunoya
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize( \
	"inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2,-ffast-math,-fsched-spec,unroll-loops,-falign-jumps,-falign-loops,-falign-labels,-fdevirtualize,-fcaller-saves,-fcrossjumping,-fthread-jumps,-funroll-loops,-freorder-blocks,-fschedule-insns,inline-functions,-ftree-tail-merge,-fschedule-insns2,-fstrict-aliasing,-fstrict-overflow,-falign-functions,-fcse-follow-jumps,-fsched-interblock,-fpartial-inlining,no-stack-protector,-freorder-functions,-findirect-inlining,-fhoist-adjacent-loads,-frerun-cse-after-loop,inline-small-functions,-finline-small-functions,-ftree-switch-conversion,-foptimize-sibling-calls,-fexpensive-optimizations,inline-functions-called-once,-fdelete-null-pointer-checks")
#include <bits/stdc++.h>
#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)
using namespace std;
using db = double;
using ll = long long;
using uint = unsigned int;
#define Tp template
using pii = pair<int, int>;
#define fir first
#define sec second
Tp<class T> void cmax(T& x, const T& y) {if (x < y) x = y;} Tp<class T> void cmin(T& x, const T& y) {if (x > y) x = y;}
#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back
Tp<class T> void sort(vector<T>& v) { sort(all(v)); } Tp<class T> void reverse(vector<T>& v) { reverse(all(v)); }
Tp<class T> void unique(vector<T>& v) { sort(all(v)), v.erase(unique(all(v)), v.end()); }
const int SZ = 1 << 23 | 233;
struct FILEIN { char qwq[SZ], *S = qwq, *T = qwq, ch;
#ifdef __WIN64
#define GETC getchar
#else
  char GETC() { return (S == T) && (T = (S = qwq) + fread(qwq, 1, SZ, stdin), S == T) ? EOF : *S++; }
#endif
  FILEIN& operator>>(char& c) {while (isspace(c = GETC()));return *this;}
  FILEIN& operator>>(string& s) {while (isspace(ch = GETC())); s = ch;while (!isspace(ch = GETC())) s += ch;return *this;}
  Tp<class T> void read(T& x) { bool sign = 0;while ((ch = GETC()) < 48) sign ^= (ch == 45); x = (ch ^ 48);
    while ((ch = GETC()) > 47) x = (x << 1) + (x << 3) + (ch ^ 48); x = sign ? -x : x;
  }FILEIN& operator>>(int& x) { return read(x), *this; } FILEIN& operator>>(ll& x) { return read(x), *this; }
} in;
struct FILEOUT {const static int LIMIT = 1 << 22 ;char quq[SZ], ST[233];int sz, O;
  ~FILEOUT() { flush() ; }void flush() {fwrite(quq, 1, O, stdout); fflush(stdout);O = 0;}
  FILEOUT& operator<<(char c) {return quq[O++] = c, *this;}
  FILEOUT& operator<<(string str) {if (O > LIMIT) flush();for (char c : str) quq[O++] = c;return *this;}
  Tp<class T> void write(T x) {if (O > LIMIT) flush();if (x < 0) {quq[O++] = 45;x = -x;}
		do {ST[++sz] = x % 10 ^ 48;x /= 10;} while (x);while (sz) quq[O++] = ST[sz--];
  }FILEOUT& operator<<(int x) { return write(x), *this; } FILEOUT& operator<<(ll x) { return write(x), *this; }
} out;

int n ;
const int maxn = 1e5 + 51 ;
vector < int > g[maxn] ;
int rev[maxn] , fa[maxn] , idx = 0 ;

void dfs(int u , int f) {
	for(int v : g[u]) 
		if(v != f) dfs(v , u) ;
	fa[u] = f , rev[++ idx] = u ;
}

int f[maxn] ;
int ans[maxn] ;
int solve(int x) {
	if(ans[x]) return ans[x] ;
	int cnt = 0 ;
	rep(i , 1 , n) f[i] = 1 ;
	rep(i , 1 , n) {
		int qwq = rev[i] ;
		if(fa[qwq] && (~ f[fa[qwq]]) && (~ f[qwq])) {
			if(f[qwq] + f[fa[qwq]] >= x) ++ cnt , f[fa[qwq]] = -1 ;
			else cmax(f[fa[qwq]] , f[qwq] + 1) ;
		}
	}
	return ans[x] = cnt ;
}

signed main() {
  // code begin.
	in >> n ;
	rep(i , 2 , n) { int u , v ; in >> u >> v ; g[u].pb(v) , g[v].pb(u) ; }
	dfs(1 , 0) ; int q = min(n , 200) ;
	ans[1] = n ; rep(i , 2 , q) ans[i] = solve(i) ;
	int Ans ;
	for(int i = q + 1 ; i <= n ; i = Ans + 1) {
		int l = i , r = n ;
		int qwq = solve(l) ;
		while(l <= r) {
			int mid = l + r >> 1 ;
			if(solve(mid) ^ qwq) r = mid - 1 ;
			else l = (Ans = mid) + 1 ;
		}
		for(int p = i ; p <= Ans ; p ++) ans[p] = qwq ;
	}
	rep(i , 1 , n) out << ans[i] << '\n' ;
	return 0;
  // code end.
}
```

---

## 作者：Minakami_Yuki (赞：4)

神仙题，写了一上午

# 题目链接

[CF1039D You Are Given a Tree](https://www.luogu.org/problem/CF1039D)

# 题意简述

给你一棵树，分别求出划分成包含点数$k\in[1,n]$的链时最大的链的个数。

# 解题思想

感谢小粉兔教我这道题QwQ，~~还有那个码风奇怪的老哥的题解~~

OwenOwl说要整体二分，~~那是啥~~

首先考虑暴力怎么打，对于每一个$k$，可以**贪心地**去做，一直找能连接的点，直到长度**第一次**$\geq k$，这时`链数++`，继续找下一段。时间复杂度为$O(n ^ 2)$

然后分析一波样例，我们发现对于$k\in(\sqrt n, n]$，答案是**单减**的，并且与**整除分块**相似，中间的某一段答案是一样的，所以我们可以二分找到一个段的右端点，然后暴力`check()`，更新整段的答案。这里的复杂度是$O(n\sqrt n \log n)$（log二分，根号区间，O(n)check）。

所以我们对于剩下的区间$[1, \sqrt n]$，直接暴力做，复杂度也是$O(n\sqrt n)$的，不会拖后腿。

总复杂度为$O(n\sqrt n\log n)$

这个复杂度已经可以过了

但是我们发现分治的两个区间复杂度并不均衡，所以考虑通过分配不同的分治范围来均衡掉两个不同的操作时间。

我们发现，对于大段区间，二分的复杂度是$O(\log n)$的，而暴力部分区间是$O(n)$的，于是我们可以通过设置区块分界点为$O(\sqrt{(n \times \log n)}) = O(\sqrt{n \log n})$来均衡两个复杂度。

`60`个点一共快了`10s`。。。

[根号nlogn断点](https://www.luogu.org/record/23329587)

[根号n断点](https://www.luogu.org/record/23329370)

# 参考代码

```c++
#include <cstdio>
#include <cctype>
#include <cmath>

namespace FastIO{
	inline int read() {
		char ch = getchar(); int r = 0, w = 1;
		while(!isdigit(ch)) {if(ch == '-') w = -1; ch = getchar();}
		while(isdigit(ch)) {r = r * 10 + ch - '0', ch = getchar();}
		return r * w;
	}
	
	void _write(int x) {
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) _write(x / 10);
		putchar(x % 10 + '0');
	}
	
	inline void write(int x) {
		_write(x);
		puts("");
	}
}

using namespace FastIO;

const int N = 100010;
const int M = N << 1;

template <typename T> inline T max(T a, T b) {return a > b ? a : b;}

int n, size;
int head[N], ver[M], nxt[M], cnt;
int fa[N], ptn[N], idx;
int d[N], ans[N];

inline void add(int x, int y) {
	ver[++cnt] = y, nxt[cnt] = head[x], head[x] = cnt;
	ver[++cnt] = x, nxt[cnt] = head[y], head[y] = cnt;
}

void dfs(int x) {
	for(register int i = head[x]; i; i = nxt[i]) {
		int y = ver[i];
		if(y == fa[x]) continue;
		fa[y] = x;
		dfs(y);
	}
	ptn[++idx] = x;
}

inline int find(int k) {
	int ans = 0;
	for(register int i = 1; i <= n; i++) d[i] = 1;
	for(register int i = 1; i <= n; i++) {
		int x = ptn[i];
		if(fa[x] && (~d[fa[x]]) && (~d[x])) {
			if(d[x] + d[fa[x]] >= k) {
				ans++;
				d[fa[x]] = -1;
			}
			else {
				d[fa[x]] = max(d[fa[x]], d[x] + 1);
			}
		}
	}
	return ans;
}

int main() {
	n = read();
	size = sqrt(n * (log(n) / log(2)));
	for(register int i = 1; i < n; i++) {
		int x = read(), y = read();
		add(x, y);
	}
	dfs(1);
	ans[1] = n;
	for(register int i = 2; i <= size; i++) {
		ans[i] = find(i);
	}
	for(register int i = size + 1, l, r, k; i <= n; i = l + 1) {
		l = i, r = n, k = find(i);
		while(l + 1 < r) {
			int mid = (l + r) >> 1;
			if(find(mid) == k) l = mid;
			else r = mid;
		}
		for(register int j = i; j <= l; j++) ans[j] = k;
	}
	for(register int i = 1; i <= n; i++) {
		write(ans[i]);
	}
	return 0;
}
```



---

## 作者：WrongAnswer_90 (赞：1)

[CF1039D You Are Given a Tree](https://www.luogu.com.cn/problem/CF1039D)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17803955.html)

一种神奇套路：对答案根分，根分的依据是链的长度和答案大致是一个成反比的关系。

考虑确定了 $k$ 怎么做。因为一个点只能在一条链里，所以 dfs 的时候如果能拼成一条链就一定会拼成一条链，不然就把贡献传给父亲继续尝试。

对于 $k$ 比较小的时候可以暴力计算。对于 $k$ 较大的情况，发现答案一定非严格单减，并且递减的幅度越来越小。所以对于 $k$ 比较大的情况，可以通过枚举答案，二分找出答案对应的区间。

设块长为 $B$，对于 $k\leq B$ 暴力计算，$k>B$ 枚举答案不会超过 $\dfrac{n}{B}$，复杂度 $\mathcal O(Bn+\dfrac{n^2}{B}\log n)$，块长取 $1000$ 可以通过此题。

一点卡常技巧：dfs 的次数非常多，所以可以先 dfs 一遍，之后按照 dfn 序扫一遍即可。

```cpp
	int n,cnt,ans,bl,len,tot,maxn[100010],maxm[100010],up[100010],a[100010],fin[100010],head[100010],to[200010],nex[200010];
	inline void add(int x,int y){to[++cnt]=y,nex[cnt]=head[x],head[x]=cnt;}
	void dfs0(int k,int fa)
	{
		a[++tot]=k,up[k]=fa;
		for(int i=head[k];i;i=nex[i])if(to[i]!=fa)dfs0(to[i],k); 
	}
	void dfs()
	{
		for(int i=n;i>=1;--i)
		{
			int now=a[i];maxn[now]=maxm[now]=0;
			for(int j=head[now];j;j=nex[j])
			{
				if(to[j]==up[now])continue;
				int t=maxn[to[j]];
				if(t>=maxn[now])maxm[now]=maxn[now],maxn[now]=t;
				else Mmax(maxm[now],t);
			}
			if(maxn[now]+maxm[now]+1>=len)++ans,maxn[now]=0;
			else ++maxn[now];
		}
	}
    inline void mian()
    {
    	read(n),bl=1000;int x,y;
    	for(int i=1;i<n;++i)read(x,y),add(x,y),add(y,x);
    	dfs0(1,0);
    	for(int i=1;i<=bl;++i)len=i,ans=0,dfs(),fin[i]=ans;
    	int tt=ans;
    	for(int i=0,last=n+1;i<=tt;++i)
    	{
    		int l=bl+1,r=last,mid;
    		while(l<r)
    		{
    			len=mid=l+((r-l)>>1),ans=0,dfs();
    			if(ans>i)l=mid+1;
    			else r=mid;
			}
			for(int j=l;j<last;++j)fin[j]=i;
			last=l;
		}
		for(int i=1;i<=n;++i)write(fin[i],'\n');
	}
```

---

## 作者：ybe2007 (赞：1)

一道**根号分治**~~的毒瘤~~题。

这题和之前写过的[CF786C Till I Collapse](https://www.luogu.com.cn/problem/CF786C)是同一类型的题目，那题题解好像写在某天比赛的总结里了。

这类题最显著的特征有两个：

1. 答案的单调性。观察样例便容易发现这一结论，再稍加思考即可证明其正确性。

2. 对于每一个位置的答案，最大不超过 $n\div k$，这样一来，对于 $\gt \sqrt n$ 的 $k$，答案就不会多于 $\sqrt n$ 个，于是就可以采用二分同一答案的最右端，然后一起输出。

此题的另一个问题在于暴力的写法。这里有一个显然的贪心，即 如果该点能与下面的两最大儿子组成 $\geq k$ 的链，那就优先考虑组链，不行的话就取最大值更新链长。

另外：此题卡常！！优化方式主要有如下几点：

1. 快读快写。

2. 使用内联函数 inline。

3. 将所有结点预先按照 dfs序排好，这样计算时就不需递归以达到优化目的。（这点最重要！）

4. 块长的处理，取 $\sqrt {nlogn}$ 时最优，具体证明可以参考其它题解。（这点也很重要！）

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n;
int tot,ver[N<<1],nxt[N<<1],head[N];
inline void add_E(int x,int y){ver[++tot]=y,nxt[tot]=head[x],head[x]=tot;}
int mx[N],dfn[N],fa[N];
struct F{int id,dfn;}a[N];
bool cmp(F a,F b){return a.dfn>b.dfn;}
inline int read()
{
	int x=0;char c=getchar();bool f=0;
	while(!isdigit(c)){if(c=='-') f=1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+c-48;c=getchar();}
	if(f) x=-x;return x;
}
inline void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
void dfs(int x)
{
	a[x].id=x;
	a[x].dfn=++tot;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=ver[i];
		if(y==fa[x]) continue;
		fa[y]=x;
		dfs(y);
	}
}
inline int calc(int w)
{
	int res=0;
	for(int i=1;i<=n;i++)
	{
		int x=a[i].id,mx1=0,mx2=0;
		for(int j=head[x];j;j=nxt[j])
		{
			int y=ver[j];
			if(y==fa[x]) continue;
			if(mx[y]>mx1) mx2=mx1,mx1=mx[y];
			else if(mx[y]>mx2) mx2=mx[y];
		}
		if(mx1+mx2+1>=w) res++,mx[x]=0;
		else mx[x]=mx1+1;
	}
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		x=read(),y=read();
		add_E(x,y),add_E(y,x);
	}
	tot=0,dfs(1);
	sort(a+1,a+1+n,cmp);
	int B=sqrt(n*log2(n));
	for(int i=1;i<=B;i++) write(calc(i)),puts("");
	int x=B+1;
	while(x<=n)
	{
//		printf("x=%d\n",x);
		int now=calc(x);
		int l=x+1,r=n,res=x;
		while(l<=r)
		{
			int mid=l+r>>1;
			if(calc(mid)==now) l=mid+1,res=mid;
			else r=mid-1;
		}
		for(int i=1;i<=res-x+1;i++) write(now),puts("");
		x=res+1;
	}
}
```

~~我的代码最慢的第8个点跑了3.54s，十分的蒻~~

---

## 作者：JoaoFelix (赞：1)

首先讲一讲O(N^2)的做法

O(N^2)就是枚举每个k，然后O(N)判断

怎么判断呢？

遇到树上的覆盖问题，往往都是贪心！

我们可以dfs贪心判断，具体的就是每个点维护一个往下扩展的最长和次长的距离，(不包括当前的点)记为Mx1,Mx2

我们定义Mx1所在的节点为所有在Mx1记录的这条链上的点，Mx2同理！

如果Mx1+Mx2+1>=k那么我们就把这条链提出来，这肯定是最优的，否则Mx2所在的节点将不被覆盖，并且还要覆盖Mx1所在的节点和当且节点和当前节点的fa，但是如果覆盖就只会覆盖Mx1所在的节点和Mx2所在的节点和当前节点，比上述更优！

这个判断类似于noip2018的赛道修建！

给出核心代码：
```cpp
inline void dfs(int x, int Fa) {
	int Mx1 = 0, Mx2 = 0;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = to[i];
		if (y != Fa) {
			dfs(y, x);
			if (dp[y] > Mx1) Mx2 = Mx1, Mx1 = dp[y]; else if (dp[y] > Mx2) Mx2 = dp[y];
		}
	}
	if (Mx1 + Mx2 + 1 >= cur) dp[x] = 0, cnt++; else dp[x] = Mx1 + 1;
}
```


剩下的我们考虑怎么优化！

O(N)的判断显然不太可以优化，我们要考虑优化枚举k的过程

我们发现k递增的情况下答案单调不增！

既然答案有单调性，我们有发现这个过程其实和整数分块的过程很像！

答案的取值是O(sqrt(N))种

对于k<=sqrt(N)的我们可以暴力枚举

k>sqrt(N)的答案显然只有<=sqrt(N)的，我们枚举答案，求出答案覆盖的k分别是从Lk-Rk的，就可以了！

但是发现直接按照上述过程模拟，码量稍大，并且要带一个log，于是我们可以考虑写一个整体二分，但是这个整体二分并不是log的复杂度，而是O(N*sqrt(N))的

其实我们只是写了一个O(N^2)的整体二分，但是利用上述性质在优化，最终复杂度是O(N*sqrt(N))的，并且代码非常短！

以下是整体二分的核心代码：
```cpp
inline void solve(int l, int r, int L, int R) {
	if (l > r || L > R) return;
	if (L == R) {
		for (int i = l; i <= r; i++) ans[i] = L; return;
	}
	int mid = (l + r) >> 1;
	cur = mid; cnt = 0; dfs(1, 0); ans[mid] = cnt;
	solve(l, mid - 1, cnt, R); solve(mid + 1, r, L, cnt);
}
```


---

## 作者：Mooncrying (赞：1)

挺喜欢这道题的，，，这是一道根号分治好题。

### 题目大意

- 给出一棵 $n$ 个节点的树，对于 $k \in [1, n]$，求出该树能被分成包括 $k$ 个节点的路径的最大条数。每条路径不能重叠。

- $n \le 10 ^ 5$。

### 分析

- 我们先想想暴力怎么做。

- 可以想到用树形 dp 从叶子节点往上扫，遇到能接在一起路径的就贪心地直接接在一起，经过多次手玩发现是正确的。一次 dfs 的复杂度为 $O(n)$，$n$ 次的话就是 $O(n^2)$ 了。

	```cpp
	void dfs(int u, int fa, int k) 
	{
		f[u] = 0;
   		int firmax = 0, secmax = 0;
    	for(int p = head[u]; p; p = nxt[p]) 
    	{
       		int v = to[p];
       		if(v == fa) continue;
       	 	dfs(v, u, k);
        	if(f[y] > firmax) secmax = firmax, firmax = f[v];
        	else secmax = max(secmax, f[v]);
    	}
    	if(firmax + secmax + 1 >= k) ++cnt, f[x] = 0;
    	else f[x] = maxx + 1;
	}
	```
- 接下来考虑怎么优化。

	显然 dfs 部分的 $O(n)$ 已经不具备再优化的条件了。
    
   我们发现，答案从 $1$ 到 $n$ 具有单调不升性，这是一个突破口，所以我们从答案下手。
   
   考虑一下答案的数值分布。设 阈值 $B$，我们发现，当 $k$ 的值大于 $B$ 时，答案的值一定小于 $\frac{n}{B}$。
   
   那我们就根号分治。
   
   1. 对于 $k \le B$，我们直接用树形 dp 算出答案，总的时间复杂度为 $O(B \cdot n)$ 级别的。
   
   2. 而对于 $k > B$ 的情况，我们直接二分答案，二分出与左边界答案相同的最右边界，然后右移左边界即可。dfs 求解 $O(n)$，二分 $O(\log n)$，答案数最多有 $n / B$ 个，该部分总的时间复杂度为 $O(\frac{n ^ 2 \log n}{B})$ 级别。
   
  总的时间复杂度为 $O(B \cdot n + \frac{n ^ 2 \log n}{B})$，由基本不等式可得 $B = \sqrt{n \log n}$ 时复杂度最低，为 $O(2n \sqrt{n \log n})$。
  
### 一点优化

- 写完之后发现过不了这个题，会 TLE，可能常数太大了，然后就试着卡常。

- dfs 慢得很（虽然我也不太清楚为什么），就预处理出了 dfs 序和节点的父亲节点，然后直接在 dfs 序上跑的，然后就过了。

- 快读快写直接安排上。

- 二分答案的 Solve 函数里边写个记忆化，之前求过的 $k$ 的答案就直接输出就行了。

- 如果还是过不了可以参考一下其他题解，蒟蒻太弱，实在是没什么能帮得上的了。我感觉最主要的还是 dfs 好慢。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int head[N], nxt[N << 1], to[N << 1], fa[N], dfn[N], T, B, f[N], Ans[N], cnt, ans, n;
void read(int &x)
{
	int f = 1; x = 0; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch =  getchar(); }
	x *= f;
}
void write(int x, char ch)
{
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10, 0);
	putchar(x % 10  + '0');
	if(ch == '\n') putchar('\n');
}
void add(int u, int v)
{
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}
void dfs(int u, int f)
{
	for(int p = head[u]; p; p = nxt[p])
	{
		int v = to[p];
		if(v == f) continue;
		fa[v] = u;
		dfs(v, u);
	}
	dfn[++T] = u;//预处理出 dfs 序
}
int Solve(int k)
{
	if(Ans[k] != -1) return Ans[k];// 记忆化
	ans = 0;
	for(int i = 1; i <= n; ++i) f[i] = 1;
	for(int i = 1; i <= n; ++i)
	{
		int x = dfn[i];
		if(fa[x] && f[fa[x]] != -1 && f[x] != -1)
		{
			if(f[x] + f[fa[x]]>= k) ans++, f[fa[x]] = -1;
			else f[fa[x]] = max(f[fa[x]], f[x] + 1);
		}
	}
	return ans;
}//求解
int main()
{
	read(n); B = sqrt(n * log(n));//别忘了设阈值
	memset(Ans, -1, sizeof(Ans));
	for(int i = 1, u, v; i < n; ++i)
		read(u), read(v), add(u, v), add(v, u);
	dfs(1, 0); Ans[1] = n;//小小小优化
	for(int i = 2; i <= B; ++i) Ans[i] = Solve(i);
	for(int i = B + 1, l, r; i <= n; i = l + 1)
	{
		l = i, r = n; int k = Solve(l);
		while(l + 1 < r)
		{
			int mid = (l + r) >> 1;
			if(Solve(mid) == k) l = mid;
			else r = mid - 1;
		}
		for(int j = i; j <= l; ++j) Ans[j] = k;//二分答案
	}
	for(int i = 1; i <= n; ++i) write(Ans[i], '\n');
	return 0;
}
```
完结撒花~

---

## 作者：Acee (赞：0)

模板。

暴力显然，可直接贪心，维护最长链与次长链即可。

设阈值为 $B$。

当 $k \leq B$ 时，可以这样做，因为只有 $\sqrt n$ 个，可以暴力做，用树形动态规划，贪心维护最长链与次长链即可。

重点是在 $k > B$ 时，发现有单调性，而且答案最多为 $\sqrt n$ 个，可以加上二分相同答案连续段即可，还是用树形动态规划做，没有问题。

在 $B = \sqrt {n \log n}$ 时，复杂度最优。

时间复杂度：$O(n \sqrt {n \log n})$。

调阈值的话，可以把 $\log$ 调根号里面去。

代码好写，不想放了，想要私信。

---

## 作者：masonpop (赞：0)

很好的根号分治。

首先考虑 $O(nk)$ 做法。这个可以直接贪心，能选必选，最后把自己能贡献出的最长链传上去。有点类似 P5021。

最后考虑 $k$ 很大的情况。此时答案只有 $O(\frac{n}{B})$ 种，$B$ 是阈值。对每种答案分别二分其出现区间即可。

注意这里的 $B$ 并非取 $\sqrt n$ 最优，因为 $\min\{nB+\frac{n^2\log n}{B}\}=n\sqrt {n\log n}$，当 $B=\sqrt {n\log n}$ 时最优。

可能需要一点点卡常，比如去掉 dfs 改为在 dfn 序上 dp，能大幅优化常数。[代码](https://codeforces.com/contest/1039/submission/250472838)。

---

## 作者：_Vix_ (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF1039D)

---

~~才 才不是来水题解的呢~~

## 分析

考虑对于一个给定 $k$，如何求出答案。我们贪心地将当前点的最长链和次长链拼成答案，这样做是 $O(n)$ 的。得出朴素做法总时间复杂度就是 $O(n^2)$ 的。
 
考虑根号分治的 trick。设定阈值 $B$，对于 $k \le B$ 的可以用朴素做法直接求，这部分是 $O(nB)$ 的；对于 $k > B$，答案小于 $\dfrac{n}{B}$，用二分求出答案一样的连续区间，这部分是 $O(\dfrac{n^2 \log n}{B})$ 的。当 $B$ 取 $\sqrt{n \log n}$ 时，总时间复杂度最优，是 $O(n \sqrt{n \log n})$ 的。

这道题比较卡常卡常。考虑将树拍成出栈序以及记忆化。记忆化是保留每次二分的答案。

## Code
```cpp
#include <bits/stdc++.h>
#define gc getchar
using namespace std;

inline int read() {
	int x = 0; bool flag = 0; char ch = gc();
	for (;!isdigit(ch); ch = gc()) flag |= ch == '-';
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return flag ? ~(x - 1) : x;
}

const int N = 1e5 + 11;
int h[N], e[N << 1], ne[N << 1], idx;
int now, cnt, fa[N], lg[N], d[N], rnk[N], tsp;
int n, B, f[N], ans[N];

inline void add(int u, int v) {
	e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

void dfs(int u, int f) {
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == f) continue;
		fa[v] = u;
		dfs(v, u);
	}
	rnk[++tsp] = u;
}

inline void init() {
	memset(h, -1, sizeof h);
	memset(f, -1, sizeof f);
	n = read();
	for (int i = 1; i < n; i++) {
		int u = read(), v = read();
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	lg[0] = -1; for (int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
}

inline int solve(int k) {
	if (~f[k]) return f[k];
	int res = 0;
	for (int i = 1; i <= n; i++) d[i] = 1;
	for (int i = 1; i <= n; i++) {
		int u = rnk[i];
		if (fa[u] && d[u] != -1 && d[fa[u]] != -1) {
			if (d[u] + d[fa[u]] >= k) res++, d[fa[u]] = -1;
			else d[fa[u]] = max(d[fa[u]], d[u] + 1);
		}
	}
	return f[k] = res;
}

int main() {
	init();
	B = sqrt(n * lg[n]);
	ans[1] = f[1] = n;
	for (int i = 2; i <= B; i++) ans[i] = solve(i);
	for (int i = ans[B], lst = B; ~i; i--) {
		int l = lst + 1, r = n;
		if (solve(l) != i) continue;
		while (l < r) {
			int mid = l + r + 1 >> 1;
			if (solve(mid) >= i) l = mid;
			else r = mid - 1;
		}
		for (int j = lst + 1; j <= l; j++) ans[j] = i;
		lst = l;
	}
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
```


---

## 作者：happybob (赞：0)

考虑根号分治。

若 $k$ 固定，怎么做？

容易发现我们可以从树的叶子节点开始往上走，每走到一条合法的链就拼起来，贪心即可，复杂度 $O(n)$。

此外，我们还发现，令 $ans_i$ 为 $k=i$ 时的答案，那么由于每条链不相交，所以 $ans_i \leq \lfloor \dfrac{n}{k}\rfloor$。

同时，随着 $i$ 增大，$ans_i$ 单调不增。

于是我们考虑根号分治，假设阈值为 $p$，对于 $1 \leq i \leq p$，我们暴力计算，复杂度 $O(np)$。

对于 $p < i \leq n$，其不同的答案个数的量级为 $O(\dfrac{n}{p})$，由于单调性，所以每个答案的出现位置都是一个区间，可以做到 $O(\dfrac{n}{p} \log n \times n) = O(\dfrac{n^2 \log n}{p})$。当 $p = \sqrt{n \log n}$ 时取得最小值。当然直接取 $\sqrt{n}$ 或者类似的常数也可以。

此外，如果实现不好，可能会被卡，考虑将树上的点按照 `dfn` 序从大到小排，直接在序列上 DP，可以避免递归。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, blo, k;
vector<int> G[N];
pair<int, int> dp[N];
int fa[N];

int ans[N];
int e[N], h[N], ne[N], idx, ids;

struct Node
{
	int u, id;
	Node(int _u, int _i): u(_u), id(_i){}
	Node(){}
	bool operator<(const Node& g) const
	{
		return id > g.id;
	}
}p[N];

void predfs(int u, int f)
{
	p[u].u = u, p[u].id = ++ids;
	fa[u] = f;
	for (int i = h[u]; ~i; i = ne[i])
	{
		int j = e[i];
		if (j != f) predfs(j, u);
	}
}

void dfs(int u, int fa)
{
	dp[u] = make_pair(0, 1);
	int maxn1 = -1, maxn2 = -1;
	for (int i = h[u]; ~i; i = ne[i])
	{
		int j = e[i];
		if (j == fa) continue;
		dfs(j, u);
		dp[u].first += dp[j].first;
		if (dp[j].second > maxn1)
		{
			maxn2 = maxn1;
			maxn1 = dp[j].second;
		}
		else if (dp[j].second > maxn2) maxn2 = dp[j].second;
	}
	if (maxn1 == -1 && maxn2 == -1)
	{
		return;
	}
	if (maxn2 == -1)
	{
		if (maxn1 + 1 >= k) 
		{
			dp[u].first++, dp[u].second = 0;
		}
		else
		{
			dp[u].second += maxn1;
		}
	}
	else
	{
		if (maxn1 + maxn2 + 1 >= k)
		{
			dp[u].first++;
			dp[u].second = 0;
		}
		else
		{
			dp[u].second = maxn1 + 1;
		}
	}
}

int g[N];
int resse[N];
int m1[N], m2[N];
int getres(int x)
{
	k = x;
	for (int i = 1; i <= n; i++) m1[i] = m2[i] = -1, dp[i] = make_pair(0, 1);
	for (int i = 1; i <= n; i++)
	{
		int u = p[i].u;
		int maxn1 = m1[u], maxn2 = m2[u];
		if (maxn1 == -1 && maxn2 == -1)
		{
			dp[fa[u]].first += dp[u].first;
			if (dp[u].second > m1[fa[u]]) m2[fa[u]] = m1[fa[u]], m1[fa[u]] = dp[u].second;
			else if (dp[u].second > m2[fa[u]]) m2[fa[u]] = dp[u].second;
			continue;
		}
		if (maxn2 == -1)
		{
			if (maxn1 + 1 >= k) 
			{
				dp[u].first++, dp[u].second = 0;
			}
			else
			{
				dp[u].second += maxn1;
			}
		}
		else
		{
			if (maxn1 + maxn2 + 1 >= k)
			{
				dp[u].first++;
				dp[u].second = 0;
			}
			else
			{
				dp[u].second = maxn1 + 1;
			}
		}
		dp[fa[u]].first += dp[u].first;
		if (dp[u].second > m1[fa[u]]) m2[fa[u]] = m1[fa[u]], m1[fa[u]] = dp[u].second;
		else if (dp[u].second > m2[fa[u]]) m2[fa[u]] = dp[u].second;
	}
	return dp[1].first;
}

inline int read()
{
	char ch(getchar());
	int x(0);
	while (ch < '0' || ch > '9')
	{
		ch = getchar(); 
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x;
}

int main()
{
	memset(h, -1, sizeof h);
	memset(resse, -1, sizeof resse);
	n = read();
	for (int i = 1; i < n; i++)
	{
		int u, v;
		u = read(), v = read();
		e[idx] = v, ne[idx] = h[u], h[u] = idx++;
		e[idx] = u, ne[idx] = h[v], h[v] = idx++;
	}
	predfs(1, 0);
	sort(p + 1, p + n + 1);
	blo = min(n, 230);
	for (int i = 1; i <= blo; i++)
	{
		ans[i] = getres(i);
		if (i == 1) ans[i] = n;
	}
	for (int j = 0; j <= n / blo; j++)
	{
		int l = blo + 1, r = n, res = 0;
		while (l <= r)
		{
			int mid = l + r >> 1;
			int gf;
			if (resse[mid] != -1) gf = resse[mid];
			else
			{
				gf = resse[mid] = getres(mid);	
			}
			if (gf >= j)
			{
				res = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		g[j] = res;
	}
	for (int i = 0; i <= n / blo; i++)
	{
		if (g[i] && !g[i + 1])
		{
			for (int j = blo + 1; j <= g[i]; j++) ans[j] = i;
			break;
		}
		else if (!g[i]) break;
		else
		{
			if (g[i] == g[i + 1]) continue;
			for (int j = g[i + 1] + 1; j <= g[i]; j++) ans[j] = i;
		}
	}
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
```



---

## 作者：I_am_Accepted (赞：0)

### Preface

人傻常数大，以后绝对不乱加 GCC 优化。

### Analysis

根号分治：长度 $len\ge\sqrt{n}$ 的路径最大数量一定 $\le\sqrt{n}$。

对于固定的路径长度 $len$，我们可以很轻松地树形 DP 搞定答案，由于过分简单，不再赘述。

然后我们选定分治点 $B$。$len\le B$ 直接暴力求；$len>B$ 时答案最多不超过 $\frac{n}{B}$，而且答案随 $len$ 递增而非升，我们对于每一种答案 $x$，二分最大的 $len$ 使得答案为 $x$ 即可。

时间为：

$$O(B+\frac{n\log n}{B})$$

$B$ 取 $\sqrt{n\log n}$ 最优。

### Optimize

~~其实这常数优化才是重点。~~

![](https://cdn.luogu.com.cn/upload/image_hosting/v8wmi9tz.png)

不要乱开 GCC 优化！不要乱开 GCC 优化！不要乱开 GCC 优化！

CF 上提交了 $33$ 次（头秃），证实了每次 DFS 递归求解绝对过不了，~~如果你过了我请你抽烟~~。

「那咋办呢？」

我们将树提前做好 DFS 序，之后在数组上非递归求解快不少。

「当然，快读快写是必要的……」

### Code

[My Fastest:1325 ms](https://codeforces.com/contest/1039/submission/149086644)

---

## 作者：LinkyChristian (赞：0)

审核大大求过

考虑 $dp$ ，设 $dp_i$ 为从 $i$ 的子树里延伸到 $i$ 的最长的链的长度。

对于每个节点，记下子节点里 $dp$ 值的最大值和次大值，如果这两个值合并后 大于等于我们需要的长度 $k$ ，就将其合并，并将 $dp_i$ 清零（因为记录的是一端为 $i$ 的链的长度）可以证明这一定是最优的。

性感的证明：

发现如果在一个地方能够合并的一定会立刻合并，因此还保留在 $dp_i$ 里的一定是还不可以合并的，因此在第一个可以合并的点马上合并一定是最优的。

~~证明了和没证明一样~~

然后我们有两条路子：

1. 根号分治

首先把 $k \le \sqrt{n}$ 的直接 $O(n)$ 处理掉，发现之后 $k$ 大于 $\sqrt{n}$ 的部分答案都小于 $\sqrt{n}$， 因此通过二分找出答案相同的一段区间直接赋值，复杂度为 $O(n\sqrt{n}\log n)$

2. 整体二分

发现随着 $k$ 的增大答案减小，因此对于一个询问区间，先求出区间中点 $mid$ 的答案 $tot$ ，然后左半边的答案范围就在 $tot \sim n$ ，右半边的答案范围就在 $0 \sim tot$ ，当答案范围缩小到一个数后直接赋值即可。

但这玩意的复杂度好像是假的（我证不出来，如果有大佬证出来可以评论一下打脸我），因此复杂度正确的做法还是和前一种一样，先暴力算出 $k \le \sqrt{n}$ 的答案，然后在 $\sqrt{n}+1$ 到 $n$ 的部分整体二分，因为答案只有 $\sqrt{n}$ 个，分治树只有 $log n$ 层，所以复杂度还是 $O(n\sqrt{n}\log n)$ 。 ~~本质相同~~

大概就是这么多，算是很典的题了。

---

## 作者：Light_snow (赞：0)

本文同步于[CF1039D You Are Given a Tree](https://www.cnblogs.com/dixiao/p/14761858.html)

这个题好像贪心做法就不太会。/wq

果然是因为自己太菜了。这是一个根号分治的题目，不过好像也可以整体二分，整体二分还在学，如果学了会回来再做一遍这个题。

先考虑写出一个贪心，考虑如果有能拼起来大于 $k$ 的链，我们就拼起来，那么这样一次操作是 $O(n)$ 的。

如果我们对所有答案都进行操作的话，是一个 $O(n ^ 2)$的复杂度。

我们考虑如果我们把 $k <= T$ 的操作直接暴力做，那这是一个 $O(nT)$ 的东西。

我们考虑对于 $k$ 来说，他的答案是有单调性的，我们对 $k >= T$ 考虑二分，二分到最右边那个答案一样的点，那这是一个 $O(\frac{n^2logn}{T})$ 的东西。

依均值不等式，取 $T = \sqrt{(nlogn)}$ 较优。

二分之后往需要的那一边扩展是我的一个习惯，害怕有些地方二分会挂掉，毕竟不同的二分的话，和正确答案的差别不超过$2$左右，所以其实没有慢多少。


```
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
#define N 100005

ll n;

ll head[N],cnt;

struct P{
	int to,next;
}e[N * 2];

inline void add(int x,int y){
	e[++cnt].to = y;
	e[cnt].next = head[x];
	head[x] = cnt;
}

ll fa[N],dfn[N],dfncnt;

inline void dfs(int u,int f){
	fa[u] = f;
	for(int i = head[u];i;i = e[i].next){
		int v = e[i].to;
		if(v == f)
		continue;
		dfs(v,u);
	}
	dfn[++dfncnt] = u;
}

ll f[N];//该点下最长有多少链 

inline ll solve(int k){
	ll ans = 0;
	for(int i = 1;i <= n;++i)
	f[i] = 1;
	for(int i = 1;i <= n;++i){
		int u = dfn[i];
		int fi = fa[u];
		if(fi && f[u] != -1 && f[fi] != -1)
		if(f[u] + f[fi] >= k)
		ans ++ ,f[fi] = -1;
		else
		f[fi] = std::max(f[fi],f[u] + 1);
	}
	return ans;
}

ll ans[N];

int main(){
	scanf("%lld",&n);
	for(int i = 1;i < n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	ll s = std::sqrt(n * log2(n));
	ans[1] = n;//这里因为不用和父亲链，所以直接solve可能会出事。 
	for(int i = 2;i <= s;++i)
	ans[i] = solve(i);
	for(int i = s + 1;i <= n;++i){
		ans[i] = solve(i);
		int l = i,r = n,to = i;
		while(l <= r){
			ll mid = (l + r) >> 1;
			if(solve(mid) == ans[i])
			l = mid + 1,to = mid;
			else
			r = mid - 1;
//			std::cout<<l<<" "<<r<<std::endl;
		}
		to -= 1;//用一点时间换答案正确。 
		while(solve(to + 1) == ans[i] && to <= n)
		to ++ ;
		for(int j = i + 1;j <= to;++j)
		ans[j] = ans[i];
		i = to; 
	}
	for(int i = 1;i <= n;++i)
	std::cout<<ans[i]<<std::endl;
}
```


---

