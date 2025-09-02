# [ARC136E] Non-coprime DAG

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc136/tasks/arc136_e

$ N $ 頂点からなる有向グラフ $ G $ があり，頂点には $ 1 $ から $ N $ までの番号がついています．

二つの頂点 $ i,j $ ($ 1\ \leq\ i,j\ \leq\ N $, $ i\ \neq\ j $) の間には，以下の条件を両方満たす時，またその時のみ，辺 $ i\ \to\ j $ が存在します．

- $ i\ <\ j $
- $ \mathrm{gcd}(i,j)\ >\ 1 $

また，各頂点にはそれぞれ価値が定まっており，頂点 $ i $ の価値は $ A_i $ です．

以下の条件を満たすように頂点の集合 $ s $ を選ぶことを考えます．

- $ s $ に含まれるどの二つの異なる頂点の組 $ (x,y) $ ($ x\ <\ y $) についても，$ G $ 上で $ x $ から $ y $ には到達できない．

$ s $ に含まれる頂点の価値の総和としてあり得る最大値を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^6 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力される値はすべて整数

### Sample Explanation 1

$ s=\{1,2,3,5\} $ とすればよいです．

### Sample Explanation 2

$ s=\{1,5,6\} $ とすればよいです．

## 样例 #1

### 输入

```
6
1 1 1 1 1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
6
1 2 1 3 1 6```

### 输出

```
8```

## 样例 #3

### 输入

```
20
40 39 31 54 27 31 80 3 62 66 15 72 21 38 74 49 15 24 44 3```

### 输出

```
343```

# 题解

## 作者：tzc_wk (赞：8)

首先把 $1$ 排除在外，最后答案直接加上 $a_1$ 即可。

考虑怎样的两点 $x,y$ 可以到达。类似于 CF870F Paths，可以得到如下结论：

- 如果 $x,y$ 均为偶数，那么必然可达。
- 如果 $x$ 偶数，$y$ 奇数，那么可达的充要条件是 $x\le y-m(y)$
- 如果 $x$ 奇数，$y$ 偶数，那么可达的充要条件是 $x+m(x)\le y$。
- 如果 $x,y$ 都是奇数，那么可达的充要条件是 $x+m(x)\le y-m(y)$。

其中 $m(x)$ 表示 $x$ 的最小质因子。

考虑将这个结论换一种形式表达使其能够应用于本题的结论中。对于一个点 $x$ 而言，定义其所表示的区间 $[l(x),r(x)]$ 为：

- 如果 $x$ 是偶数，那么 $l(x)=x$，$r(x)=x$。
- 否则 $l(x)=x-m(x)+1,r(x)=x+m(x)-1$。

那么一个集合 $S$ 合法的充要条件是对于所有 $x\in S$ 而言，$[l(x),r(x)]$ 的交非空。

这样我们维护一个数组 $b$，然后对于每个 $x$，对 $b$ 中 $[l(x),r(x)]$ 区间加 $a_x$，然后输出 $b$ 数组的最大值即可。

---

## 作者：lizhous (赞：5)

首先选 $1$ 不影响答案。

反链这个东西涉及连通性，所以从生成的图的连通性来考虑。

不互质条件也不好用，但是如果比较聪明或者打了表就会发现重要条件：偶数不互质，也就是说偶数只能选一个。

思考如何处理奇数联通性。容易发现一个奇数能走到的最小的点和被走到的最大的点是偶数点。这个点是这个奇数加减最小因数，又因为是奇数所以最小因数是奇数，自然有两奇相加减得偶数。

这个条件是很强的，我们可以把一个奇数点直接挂到其他偶数点上。也就是说判断小于它的数是否能到只需要判断那个数是否能到向前挂的偶数点即可，大于反之。

解决连通性后问题就在求反链了。

容易想到枚举只选一个的偶数，这样在后面的奇数必须挂在该点前面，前面的要挂在后面，使用树状数组优化计数即可。

还可能不选偶数，显然只是把上述条件中挂在前面变成允许挂在该点上，因为这样就相当于没有选这个偶数。

---

## 作者：syzf2222 (赞：4)

考虑到 $2$ 是一个很好的传递介质，不妨考察奇偶性，考察两点 $i<j$：

设 $p(x)$ 为 $x$ 的最小的质因子。

- 若 $i$ 为奇，$j$ 为奇，当 $i+p(i)\leqslant j-p(j)$ 时可以走到。

- 若 $i$ 为奇，$j$ 为偶，当 $i+p(i)\leqslant j$ 时可以走到。

- 若 $i$ 为偶，$j$ 为奇，当 $i\leqslant j-p(j)$ 时可以走到。

- 若 $i$ 为偶，$j$ 为偶，$i$ 可以直接走到 $j$。

容易理解以上式子的正确性，容易发现最多取一个偶数。

如果取了偶数 $pos$，则一定取右侧所有 $i-p(i)<pos$ 的和左侧所有 $i+p(i)>pos$。

否则全都是奇数，则是 $\min i+p(i)>\max i-p(i)$，可以枚举一个中间值。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
const int mod=1e9+7;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
#define ll long long
int n,m,a[maxn],p[maxn];ll ans,S[maxn<<1];
struct BIT{
	ll tr[maxn<<1];
	inline void add(int x,ll y){for(;x<=n+n;x+=x&(-x))tr[x]+=y;}
	inline ll query(int x){ll res=0;for(;x;x-=x&(-x))res+=tr[x];return res;}
}T1,T2;
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<=n;i++){
		if(p[i])continue;
		for(int j=i;j<=n;j+=i)
			if(!p[j])p[j]=i;
	}
	for(int i=3;i<=n;i+=2)
		T2.add(i-p[i]+1,a[i]);
	for(int i=2;i<=n;i++)
		if(i&1)T2.add(i-p[i]+1,-a[i]),T1.add(i+p[i],a[i]);
		else ans=max(ans,a[i]+T2.query(i)+T1.query(n+n)-T1.query(i));
	for(int i=3;i<=n;i+=2)S[i-p[i]+1]+=a[i],S[i+p[i]]-=a[i];
	for(int i=1;i<=n+n;i++)S[i]+=S[i-1],ans=max(ans,S[i]);
	printf("%lld\n",ans+a[1]);
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：Binaerbaka (赞：1)

# 题面
[link](https://www.luogu.com.cn/problem/AT_arc136_e)

给出 $n$ 个点，当 $i<j$ 时，且 $\gcd(i,j)>1$ 时两点有边。

我们需要求出一个 $ \forall x \in S$ 且 $ \forall y \in S$ 都无法直接到达时， $S$ 集合内权值最大值。

# 过程

考虑如何判断两点是否有边，当且仅当两点编号因数全互质时，$\gcd(x,y)=1$ ，可以跟据最小质数 $2$ 的性质来分类讨论。
 
## 讨论
定义 $\operatorname{f(x)}$ 是 $x$ 的最小质因数
 - 若 $x$ 是偶数 $y$ 也是偶数时
 
 $x$ 与 $y$ 此时必定有边 无需讨论
 
 - 若 $x$ 不是偶数 $y$ 是偶数时 可能无法直接连边 则需要考虑间接边
 
 因为 $x$ 非偶 所以它的最小质因数必定是奇数，所以 $x+\operatorname{f(x)}$ 必定是偶数 且 $x$ 与 $x+\operatorname{f(x)}$ 必定有边。 所以当 $x+\operatorname{f(x)} \le y$ 时 $x$ 与 $y$ 必定有间接边。
 
 - 若 $x$ 是偶数 $y$ 不是偶数时
 
 因为 $y$ 非偶 所以它的最小质因数必定是奇数，所以 $y-\operatorname{f(y)}$ 必定是偶数 且 $y$ 与 $y-f(y)$ 必定有边。 所以当 $y-\operatorname{f(y)} \ge x$ 时 $x$ 与 $y$ 必定有间接边。
 
 
 - 若 $x$ 不是偶数 $y$ 也不是偶数时
 
 考虑 $x$ 对 $x+\operatorname{f(x)}$ 建边， $y$ 对 $y-\operatorname{f(y)}$ 建边。当 $x+\operatorname{f(x)} \le y-\operatorname{f(y)}$ 时 两点有边。
 
 那么如何利用这些结论呢？则只需要实现他们的否命题即可。
 
 ## 结论
 
 1. $S$ 内只能容纳一个偶数点，任意两个偶数点都会有边。
 
 2. $\forall x \in S$ 只要小于 $y+\operatorname{f(y)}$ 或 大于 $y-\operatorname{f(y)}$ 时候，可以考虑权值贡献。

 之后对贡献范围做一下差分，再做前缀和求原数组最大值即为答案所求。
 
 # Code
 ```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+5;
const int inf=2147483647;
int n,a[maxn];
int p[maxn],cnt,np[maxn];
int ans[maxn],sum;
void init(){//处理素数 
	for(int i=2;i<maxn;i++){
		if(np[i]==0)np[i]=i,p[++cnt]=i;
		for(int j=1;j<=cnt&&i*p[j]<maxn;j++){
			np[i*p[j]]=p[j];
			if(i%p[j]==0)break;
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	init();
	for(int i=1;i<=n;i++)cin>>a[i];
	ans[1]+=a[1];
	for(int i=2;i<=n;i++){
		if(i%2==0)ans[i]+=a[i],ans[i+1]-=a[i];//对答案范围做差分
		else ans[i-np[i]+1]+=a[i],ans[i+np[i]]-=a[i];//np是当前i的最小质因子 
	}
	//当它是偶数时 只能选取一个
	//当它是奇数时 考虑其答案贡献范围做差分
	for(int i=1;i<=n;i++){
		ans[i]+=ans[i-1];//前缀和
		sum=max(sum,ans[i]);
	}
	cout<<sum;
	return 0;
}
```

 
 
 
 
 
 
 

---

## 作者：Inui_Sana (赞：0)

很有趣的小清新题！

首先既然要求反链，那么就肯定要关心一个问题：如何判断 $i$ 能否到达 $j(i<j)$？

若 $i,j$ 均为偶数，显然 $i,j$ 间就有边。否则，考虑 $i$ 为奇数，那么考虑 $i$ 的一条出边能到达的点 $u$，记 $i$ 的最小质因数为 $f_i$，则显然有 $\min u=i+f_i$。对于 $j$ 的入边，入点为 $v$ 时也是一样，$\max v=i-f_i$。

同时发现，这样的 $v$ 一定是偶数，原因显然。也就是说，若此时 $u\le v$，则 $i$ 一定可以到达 $j$。于是设 $L_i=\begin{cases}i-f_i&i\bmod 2=1\\i&i\bmod 2=0\end{cases},R_i=\begin{cases}i+f_i&i\bmod 2=1\\i&i\bmod 2=0\end{cases}$。则 $i$ 可以到达 $j$ 当且仅当 $R_i\le L_j$。再把 $L_i,R_i$ 看作若干个区间 $(L_i,R_i)$，则一个点集 $S$ 构成反链当且仅当 $S$ 中的区间交集不为空。

当然你会发现这个 $(L_i,R_i)$ 在 $i\bmod 2=0$ 的时候有问题，不过事实上你不能同时选两个这样的 $i$，于是后面特判一下。

这个问题是简单的，考虑枚举这些区间的交一定包含 $(i,i+1)$ 这段区间，问题就变成了有多少区间包含 $(i,i+1)$，差分即可。还有可能要选 $i\bmod 2=0$ 的 $i$，则此时区间的交一定包含 $i$ 这个点，也是统计有多少包含点 $i$ 的区间即可。

最后 $1$ 一定是能选的，加上即可。$O(n)$ 解决。

code：

```cpp
int n,m,a[N],pm[N],f[N];
bool vis[N];
ll g[N],h[N];
void Yorushika(){
	read(n);
	rep(i,2,n){
		if(!vis[i]){
			pm[++m]=i,f[i]=i;
		}
		rep(j,1,m){
			if(pm[j]>n/i){
				break;
			}
			vis[i*pm[j]]=1;
			f[i*pm[j]]=pm[j];
			if(i%pm[j]==0){
				break;
			}
		}
	}
	rep(i,1,n){
		read(a[i]);
		if(i>1&&i%2==1){
			g[i-f[i]]+=a[i],h[i+f[i]]+=a[i];
		}
	}
	ll s=0,ans=0;
	rep(i,0,n*2){
		s-=h[i];
		if(i&&i%2==0){
			ans=max(ans,s+a[i]);
		}
		s+=g[i];
		ans=max(ans,s);
	}
	printf("%lld\n",ans+a[1]);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：under_the_time (赞：0)

## 题意
> ~~题目翻译够简洁了。~~
## 解法
对于点 $i$，记 $p(i)$ 表示 $i$ 的最小质因子；它能走到的最小点和能被走到的最大点为 $i\pm p(i)$；这两个点显然一定是偶数，而偶数间两两可达，于是对于 $(i,j)$（$i<j$）：

- 若 $i,j$ 为偶数，那么 $i$ 可以走到 $j$；
- 若 $i$ 为偶数 $j$ 为奇数，那么当 $i\le j-p(j)$ 时 $i$ 能走到 $j$；
- 若 $i$ 为奇数 $j$ 为偶数，那么当 $i+p(i)\le j$ 时 $i$ 能走到 $j$；
- 若 $i,j$ 为奇数，那么当 $i+p(i)\le j-p(j)$ 时 $i$ 能走到 $j$；
- 其余情况 $i$ 均不能到达 $j$。

这里我们都以偶数可达的性质做了判断。于是我们将每个点视为一个区间，对于点 $i$，若 $i$ 为偶数那么它对应的区间为 $[i,i]$，否则为 $[i-p(i)+1,i+p(i)-1]$；最终要求选出若干区间，使得它们的交集不是空集；若是空集则说明存在一对可达的点。我们将每个区间做一次区间 $+A_i$，最后求一次全局 $\max$ 即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define open(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define abs(x) (((x) > (0)) ? (x) : (-(x)))
#define print(x) printf("%d %d\n", x.first, x.second)
const int maxn = 1e6 + 5;
int p[maxn], a[maxn], n;
namespace Sieve {
	int prm[maxn >> 2], pcnt = 0; bool is[maxn];
	void work() {
		p[1] = 1;
		for (int i = 2; i <= n; i ++) {
			if (!is[i]) p[i] = i, is[prm[++ pcnt] = i] = 1;
			for (int j = 1; 1ll * i * prm[j] <= n && j <= pcnt; j ++) {
				is[i * prm[j]] = 1, p[i * prm[j]] = prm[j];
				if (i % prm[j] == 0) continue;
			}
		}
	}
}
namespace SegmentTree {
	struct TreeNode {
		ll mx, delta; int Ls, Rs;
		TreeNode(ll m0 = 0, ll d0 = 0, int l0 = 0, int r0 = 0) { mx = m0, delta = d0, Ls = l0, Rs = r0; }
	} T[maxn << 2];
	int ncnt = 0, root = 0;
	void update(int rt) { T[rt].mx = T[rt].delta + max(T[T[rt].Ls].mx, T[T[rt].Rs].mx); }
	#define lson l, mid, T[rt].Ls
	#define rson mid + 1, r, T[rt].Rs
	void modify(int l, int r, int &rt, int k, int nowl, int nowr) {
		if (rt == 0) rt = ++ ncnt;
		if (nowl <= l && r <= nowr) return T[rt].delta += k, T[rt].mx += k, void(0);
		int mid = (l + r) >> 1;
		if (nowl <= mid) modify(lson, k, nowl, nowr);
		if (mid < nowr) modify(rson, k, nowl, nowr);
		update(rt);
	}
} using namespace SegmentTree;
int main() {
	scanf("%d", &n), Sieve :: work();
	for (int i = 1; i <= n; i ++) {
		scanf("%d", &a[i]); 
		if (i == 1) continue;
		if (i % 2 == 0) modify(1, 2e6, root, a[i], i, i);
		else modify(1, 2e6, root, a[i], i - p[i] + 1, i + p[i] - 1);
	} // cout << T[root].Ls << ' ' << T[root].Rs << '\n';
	printf("%lld\n", a[1] + T[root].mx);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc136_e)

**题目大意**

> 构造一个 DAG，点集 $1\sim n$，$x\to y\in E$ 当且仅当 $x<y$ 且 $\gcd(x,y)>1$，求最大带权反链。
>
> 数据范围：$n\le 10^6$。

 **思路分析**

注意到任意两个偶数之间都有连边，因此一个奇数 $x$ 可以走到一个偶数 $y$ 只需要把 $x$ 移动到最接近的偶数上，两个奇数只要分别走到最近的偶数上即可。

形式化来说，$x$ 能走到 $y$ 当且仅当：

- $x,y$ 均为偶数，一定可以。
- $x$ 为奇数，$y$ 为偶数，$x+p_x\le y$。
- $x$ 为偶数，$y$ 为奇数，$x\le y-p_y$.
- $x$ 为奇数，$y$ 为奇数，$x+p_x\le y-p_y$。

其中 $p_x$ 是 $x$ 的最小质因子。

可以把限制统一看成 $r_x<l_y$ 的形式，其中对于偶数 $x$，$l_x=r_x=x$，对于奇数 $x$，$l_x=x-p_x+1,r_x=x+p_x-1$，特判 $x=1$。

那么一组反链就是若干个 $[l_x,r_x]$ 有交的 $x$ 构成的，对每个 $i$ 计算 $i\in[l_x,r_x]$ 的所有 $x$ 的权值和即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e6+5;
int n,m,a[MAXN],p[MAXN],d[MAXN];
bool isc[MAXN];
ll f[MAXN],ans=0;
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=2;i<=n;++i) {
		if(!isc[i]) p[++m]=i,d[i]=i;
		for(int j=1;j<=m&&i*p[j]<=n;++j) {
			isc[i*p[j]]=true,d[i*p[j]]=p[j];
			if(i%p[j]==0) break;
		}
	}
	f[1]+=a[1];
	for(int i=2;i<=n;++i) {
		if(i&1) f[i-d[i]+1]+=a[i],f[i+d[i]]-=a[i];
		else f[i]+=a[i],f[i+1]-=a[i];
	}
	for(int i=1;i<=2*n;++i) f[i]+=f[i-1],ans=max(ans,f[i]);
	printf("%lld",ans);
	return 0;
}
```

---

