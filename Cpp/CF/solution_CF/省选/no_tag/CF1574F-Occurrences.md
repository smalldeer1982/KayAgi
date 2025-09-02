# Occurrences

## 题目描述

A subarray of array $ a $ from index $ l $ to the index $ r $ is the array $ [a_l, a_{l+1}, \dots, a_{r}] $ . The number of occurrences of the array $ b $ in the array $ a $ is the number of subarrays of $ a $ such that they are equal to $ b $ .

You are given $ n $ arrays $ A_1, A_2, \dots, A_n $ ; the elements of these arrays are integers from $ 1 $ to $ k $ . You have to build an array $ a $ consisting of $ m $ integers from $ 1 $ to $ k $ in such a way that, for every given subarray $ A_i $ , the number of occurrences of $ A_i $ in the array $ a $ is not less than the number of occurrences of each non-empty subarray of $ A_i $ in $ a $ . Note that if $ A_i $ doesn't occur in $ a $ , and no subarray of $ A_i $ occurs in $ a $ , this condition is still met for $ A_i $ .

Your task is to calculate the number of different arrays $ a $ you can build, and print it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
2 4 3
2 1 2
1 3```

### 输出

```
5```

## 样例 #2

### 输入

```
2 4 3
2 1 2
3 3 2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
1 42 1337
2 13 31```

### 输出

```
721234447```

# 题解

## 作者：harryzhr (赞：9)

# CF1574F Occurrences

## 题意

定义 $a$ 的子序列是 $[a_l,a_{l+1},\cdots,a_r]$ 构成的序列，定义 $a$ 序列在 $b$ 序列中出现的次数为 $b$ 序列中与 $a$ 相同的子序列个数。

有 $n$ 个值域在 $[1,k]$ 的数列 $A_1,A_2,\cdots,A_n$，要求构造一个长为 $m$ 的序列 $a$，满足对于所有数列 $A_i$，$A_i$ 在序列 $a$ 中的出现次数大于等于其任意一个非空子序列在 $a$ 中的出现次数。

求不同的 $a$ 的数量，答案 $\bmod 998244353$。

**数据范围**：$1\le n,m,k\le 3\times 10^5,\sum c_i\le 3\times 10^5$。

## 题解

容易发现，如果 $a$ 中包含了 $A_i$ 中的任意一个元素，一定需要把 $A_i$ 全部填完，而且必须严格按照 $A_i$ 里的顺序。也就是说，如果把相邻元素连有向边的话，我们要把 $A_i$ 构成的链全部填进去。

其次，我们填完 $A_i$ 之后，$A_i$ 中可能还包含 $A_j$ 中的元素，$A_j$ 也需要填完，而且是对位。也就是说，我们需要把 $A_i$ 的链和 $A_j$ 的链合成在一起。例如 $3\ 4\ 1\ 2 $ 和 $1\ 2\ 6$，他们会变成一条新的链：$3\ 4\ 1\ 2\ 6$。

当然，这条链上必须不能包含环，例如 $1\ 2\ 1$，$1$ 的出现永远大于 $1\ 2\ 1$ 的出现次数。这条链也不能有分支，例如 $1\ 2\ 3 $ 和 $1\ 2\ 4$，不管怎么填，总会把一条链断开，然后就不满足条件了。

所以，把图建出来之后，每个连通块分别考虑，只有该连通块是一条链的时候才能被选，所占的长度是连通块的大小（元素个数）。而不同的连通块大小最多 $O(\sqrt k)$ 个，直接做 DP，枚举所有能够转移的长度。

具体的，记 $g_i$ 表示长为 $i$ 的转移有多少个。
$$
f_i=\sum_{j=1}^{k}f_{i-k}
$$
时间复杂度 $O(m\sqrt k)$

具体的实现上，使用并查集，维护每个集合的 $size$ 和 $tag$ 表示这个集合是不是一条链。同时维护每个元素的前驱后继，合并两条链时，如果出现了与原来不同的前驱或者后继，说明这个集合的链产生了分支，不再是一条链；如果连边时两个元素已经在一个集合，那么这个集合会出现环，也不再是一条链。

可以参考代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+5,mod=998244353;
inline void Add(int &a,int b){a+=(a+b>=mod)?b-mod:b;}
int fa[N],sz[N],to[N],a[N],n,m,k,pre[N],tag[N];
int find_fa(int x){return fa[x]==x?x:fa[x]=find_fa(fa[x]);}
inline void merge(int x,int y){
	int fy=find_fa(y),fx=find_fa(x);
	if(fy==fx){tag[fx]=1;return;}
	fa[fy]=fx;
	sz[fx]+=sz[fy];
	tag[fx]|=tag[fy];
}
int buc[N],tot,g[N],f[N];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;++i)fa[i]=i,sz[i]=1;
	for(int i=1,c;i<=n;++i){
		scanf("%d",&c);
		for(int j=1;j<=c;++j){
			scanf("%d",&a[j]);
			if(j==1)continue;
			if((pre[a[j]]&&pre[a[j]]!=a[j-1])||(to[a[j-1]]&&to[a[j-1]]!=a[j])){
				merge(a[j-1],a[j]);
				tag[find_fa(a[j])]=1;
			}else if(!to[a[j-1]]){
				to[a[j-1]]=a[j];
				pre[a[j]]=a[j-1];
				merge(a[j-1],a[j]);
			}
		}
	}
	for(int i=1;i<=k;++i){
		if(find_fa(i)!=i||tag[i])continue;
		++g[sz[i]];
	}
	for(int i=1;i<=k;++i)if(g[i])buc[++tot]=i;
	f[0]=1;
	for(int i=0;i<=m;++i)
		for(int j=1;j<=tot&&i+buc[j]<=m;++j)
			f[i+buc[j]]=(f[i+buc[j]]+1ll*f[i]*g[buc[j]])%mod;
	printf("%d\n",f[m]);
	return 0;
}
```

---

## 作者：dottle (赞：5)

考虑最严的限制就是每个字串的出现次数等于其单个字符的出现次数，也就是说，对于 $a\in S$，每当 $a$ 出现，则其必须是出现在 $S$ 中；换言之，每当一个 $a$ 出现，我们需要在其前后补上若干个字符，把它补成 $S$。

我们并不总能将一个 $a$ 补成 $S$，那我们现在来考虑在哪些情况下这是不能做到的；即，若以下条件满足，$a$ 和 $S$ 中出现的所有字符都不能在答案串中出现。

首先，$a$ 应当有一个后继，在补全的过程中，需要将其置于 $a$ 后。如果 $a$ 拥有了两个不同的后继，则显然不能做到。例如 $\{1,3,5\}$ 和 $\{1,2,4\}$，对于前驱也是同理。 

其次，不能出现循环，例如 $\{1,2\}$ 和 $\{2,1\}$，这样显然是补不全的。

对于前者，我们维护每个数有几个不同的前驱后继；对于后者，用一个并查集来判环即可。

最终，我们拿合法的字串来跑一个背包就可以了。注意对于长度一样的串，我们可以一次性转移，而长度不同的串是 $O(\sqrt k)$ 的。最终复杂度按同阶来算就是 $O(n\sqrt n)$。

```cpp
for(int i=1;i<=n;i++){
	cin>>ln[i]>>pr;
	for(int j=2;j<=ln[i];j++,pr=nw) {
		cin>>nw;
		if(a[pr][nw])continue;
		a[pr][nw]=1;
		l[pr]++,r[nw]++;
		int fx=gf(pr),fy=gf(nw);
		if(fx==fy||l[pr]>1||r[pr]>1||l[nw]>1||r[nw]>1)
        	fl[fy]=0;//fx==fy -> 有循环 
            		 //后面一坨 -> 前驱后继有多个
		fl[fx]&=fl[fy];
		if(fx!=fy)sz[fx]+=sz[fy],fa[fy]=fx;		
	}
}
for(int i=1;i<=k;i++)
	if(gf(i)==i&&fl[i])
		w[sz[i]]++;
for(int i=1;i<=k;i++)
	if(w[i])
		tr.push_back(i);
f[0]=1;
for(int i=0;i<=m;i++)
	for(auto k:tr)
		(f[i+k]+=f[i]*w[k])%=mod;
cout<<f[m];
```

---

## 作者：dead_X (赞：4)

## 前言
这 F 怎么比 A 还简单啊？
## 思路
首先我们发现一个序列 $a_1,a_2,\cdots,a_n$ 的意义就是对于 $i=1,2,\cdots,n-1$，答案中的 $a_1$ 后必须是 $a_2$，$a_2$ 前必须是 $a_1$。

然后我们就可以注意到，如果一个数的后继或者前驱有 $>1$ 个就不能选了，如果一个数的若干前驱和后继中有一个不能选，这个数也不能选。如果上述条件都不满足，那么这个数就能选了。

显然，能选的部分一定是若干条链。所以实现上，我们可以把这些关系作为一张无向图存储（注意重边需要去重，自环要被直接排除），然后把每一个连通块遍历一次判断是否为链。

然后我们就得到了所有的合法序列片段，答案序列就是由若干个片段拼接而成的。

想到序列拼接，注意到数据范围并不大，我们直接用 GF 解决。

设长度为 $i$ 的序列片段数量为 $a_i$，我们直接记 $F(x)=\sum\limits_{i=1}a_ix^i$，求 $G(x)=\sum\limits_{i=0}F(x)^i=\frac{1}{1-F(x)}$ 即可。

时间复杂度 $O(n\log n)$。

## 代码
赛时写的，非常丑。

```cpp
// Problem: F. Occurrences
// Contest: Codeforces - Educational Codeforces Round 114 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1574/problem/F
// Memory Limit: 512 MB
// Time Limit: 7000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
//And in that light,I find deliverance.
#include<bits/stdc++.h>
using namespace std;
namespace getinv
{
	const long long p=998244353;
	long long qp(long long x,int y)
	{
	    long long res=1;
	    for(long long now=x; y; now=now*now%p,y>>=1)
	     if(y&1) res=res*now%p;
	    return res;
	}
	long long A[1<<22],B[1<<22],ans[2][1<<22];
	int rev[1<<22],N,M;
	void init()
	{
	    int d=N>>1;
	    rev[0]=0,rev[1]=N>>1;
	    for(int i=2; i<=N; i<<=1)
	    {
	        d>>=1;
	        for(int j=0; j<i; ++j) rev[i+j]=rev[j]|d;
	    }
	    return ;
	}
	void NTT(long long* F,int op)
	{
	    for(int i=0; i<N; ++i) if(rev[i]>i) swap(F[i],F[rev[i]]);
	    for(int len=2,M=1; len<=N; len<<=1,M<<=1)
	    {
	        long long w=qp(op?3:332748118,998244352/len);
	        //omega(m,1)
	        for(int l=0,r=len-1; l<=N; l+=len,r+=len)
	        {
	            long long w0=1;
	            for(int i=l; i<l+M; ++i)
	            {
	                long long x=(F[i]+w0*F[i+M]%p)%p,y=(F[i]+p-w0*F[i+M]%p)%p;
	                F[i]=x,F[i+M]=y,w0=w0*w%p;
	            }
	        }
	    }
	}
	void getinv(long long* BB,int len)
	{
		int t=1;
	    ans[0][0]=qp(BB[0],998244351);
	    for(N=2,M=1; M<(len<<1); t^=1)
	    {
	        init();
	        for(int i=0; i<M; ++i) ans[t][i]=(ans[t^1][i]<<1)%p;
	        for(int i=0; i<M; ++i) A[i]=BB[i];
	        NTT(ans[t^1],1),NTT(A,1);
	        for(int i=0; i<N; ++i) ans[t^1][i]=ans[t^1][i]*ans[t^1][i]%p*A[i]%p;
	        NTT(ans[t^1],0);
	        long long inv=qp(N,998244351);
	        for(int i=0; i<N; ++i) ans[t^1][i]=ans[t^1][i]*inv%p;  
	        for(int i=0; i<M; ++i) ans[t][i]=(ans[t][i]+p-ans[t^1][i])%p;
	        N<<=1,M<<=1;      
	    }
	    memset(A,0,sizeof(A));
	    for(int i=0; i<1048576; ++i) A[i]=ans[t^1][i];
	    return ;
	}
	long long cnt[1<<22];
	void main(vector<long long>&Q,int MMM)
	{
		for(int i:Q) if(i<=MMM) ++cnt[i];
		int M=1;
		for(;M<=MMM;M<<=1);
		cnt[0]=1;
		for(int i=1; i<M; ++i) cnt[i]=(p-cnt[i])%p;
		getinv(cnt,M);
		printf("%lld\n",A[MMM]%p);
	}
};
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p) if(y&1) res=res*t%p;
	return res;
}
vector<int> a[300003];
vector<int> Q;
int sz[1000003];
vector<int> e[1000003];
int in[1000003],out[1000003];
map<pair<int,int>,bool> mp;
void add(int x,int y)
{
	if(mp[make_pair(x,y)]) return ;
	e[x].push_back(y);
	e[y].push_back(x);
	++in[y],++out[x];
	mp[make_pair(x,y)]=1;
	return ;
}
int res=1;
bool vis1[1000003],vis2[1000003];
int gg=0,sss=0;
void dfs1(int x)
{
	if(vis1[x]) return ;
	vis1[x]=1;++gg;
	if(!in[x]) sss|=1;
	if(!out[x]) sss|=2;
	if(in[x]>1||out[x]>1) res=0;
	for(int i:e[x]) dfs1(i);
	return ;
}
void dfs2(int x)
{
	if(vis2[x]) return ;
	vis2[x]=1;sz[x]=gg;
	for(int i:e[x]) dfs2(i);
	return ;
}
signed main()
{
	int n=read(),m=read(),k=read();
	for(int i=1; i<=k; ++i) sz[i]=1;
	for(int i=1; i<=n; ++i)
	{
		int T=read();
		a[i].resize(T);
		for(int j=0; j<T; ++j) a[i][j]=read();
		for(int j=0; j+1<T; ++j) 
			add(a[i][j],a[i][j+1]);
	}
	for(int i=1; i<=k; ++i) if(!vis1[i]) 
	{
		res=1;gg=0;sss=0;
		dfs1(i);
		if(sss!=3) res=0;
		if(res) dfs2(i);
	}
	for(int i=1; i<=k; ++i) if(!in[i]&&vis2[i])
	Q.push_back(sz[i]); 
	getinv::main(Q,m);
	return 0;
}
```

---

## 作者：FrozenDream (赞：2)

### 前言：
学校 test 压轴题！！！
### 题目大意（感觉翻译不对劲）：
给 $n$ 个长度小于 $m$，值域为 $[1,k]$ 的序列 $A_1$ ~ $A_n$ ，问你有多少个长度为 $m$，值域为 $[1,k]$ 的序列 $B$，使得任意 $A_i$ 在序列 $B$ 中的出现次数等于其任意一个非空 **子串** 在 $B$ 中的出现次数。答案对 $998244353$ 取模。

定义 $A$ 在 $B$ 中出现次数为：
 $$ \sum_{l=1}^{m}\sum_{r=l+1}^{m}[B[l,r]=A] $$ 
### 思路：
因为要使得任意 $A_i$ 在序列 $B$ 中的出现次数等于其任意一个非空 **子串** 在 $B$ 中的出现次数，也就是说这个 $A_i$ 里的数字不能重复，要是重复了的话，就会出现这样的情况：$\verb!1231!$ 有两个 $\verb!1!$，然后我们就要再加一个 $\verb!1231!$，就又多了一个 $\verb!1!$，然后无限循环下去。

其次，假如有两个串：$\verb!1234!$ 和 $\verb!1237!$，假如我们选了 $\verb!1234!$，那么我们就不能选 $\verb!1237!$，因为 $\verb!123!$ 这个子串只出现了一次，所以我们只能二选一，但是这样做也是不合法的，因为 $\verb!123!$ 也是 $\verb!1237!$ 的子串，$\verb!1237!$ 应该也要出现一次，所以两个都不能选。

从以上两个结论，我们不难看出每一个数前后两个数是固定的，也可以说它们是绑定在一起的，就是一条链，所以原问题就简化成了求在一个图中，有多少条链，然后把它们填在这个长度为 $m$ 的 $B$ 串里面。

这不就是一个完全背包吗！但是时间复杂度为 $O(nm)$ 要超时，所以我们可以再优化一下，子串的长度肯定有相同的，它们的贡献都是相同的，所以我们就可以计算相同子串的数量，最后再把它们在计算贡献的时候乘上去就行了，因为长度为 $n$ 的序列中子串的长度最多有 $\sqrt n$ 种，所以我们就可以把时间复杂度优化成 $O(\sqrt nm)$。
### Code:
```
#include <bits/stdc++.h>
using namespace std;
inline int read() {
    register int s = 0, f = 1;
    register char ch = getchar();
    while (!isdigit(ch)) { if (ch == '-') f = -f; ch = getchar(); }
    while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
    return s * f;
}

const int N = 3e5 + 10; 
const int P = 998244353;
int n, m, k, par[N], sz[N], to[N], a[N], pre[N], tag[N];
void upd(int &x, int y) { x += y; if(x >= P) x -= P; }
int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
inline void merge(int x,int y){
	x = find(x), y = find(y);
	if(x == y) { tag[x] = 1; return; }
	par[y] = x;
	sz[x] += sz[y];
	tag[x] |= tag[y];
}

int g[N], sum[N], f[N], cnt;
signed main() {
	//freopen("sequence.in", "r", stdin);
	//freopen("sequence.out", "w", stdout);
	n = read(), m = read(), k = read();
	for (int i = 1; i <= k; i++) par[i] = i, sz[i] = 1;
	for (int i = 1; i <= n; i++) {
		int c = read();
		for (int j = 1; j <= c; j++) a[j] = read(); 
		for (int j = 2; j <= c; j++) {
			if ((pre[a[j]] && pre[a[j]] != a[j - 1]) || (to[a[j - 1]] && to[a[j - 1]] != a[j])) {
				merge(a[j - 1], a[j]);
				tag[find(a[j])] = 1;
			} else if (!to[a[j - 1]]) {
				to[a[j - 1]] = a[j];
				pre[a[j]] = a[j - 1];
				merge(a[j - 1], a[j]);
			}
		}
	}
	for (int i = 1; i <= k; i++) {
		if(find(i) != i || tag[i]) continue;
		g[sz[i]]++;
	}
	for (int i = 1; i <= k; i++) if(g[i]) sum[++cnt] = i;
	f[0] = 1;
	for (int i = 0; i <= m; i++) {
		for (int j = 1; j <= cnt && i + sum[j] <= m; j++) {
			upd(f[i + sum[j]], 1ll * f[i] * g[sum[j]] % P);
		}
	}
	cout << f[m];
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：1)

限制太抽象，考虑转化。

先考察单个数组。

对于任意子串满足要求是多余的，不难发现等价于对于所有元素满足。

于是可以得到相邻两个元素同时出现，数组中不能有重复元素。

考察两个有重复元素的数组。

容易发现这两个数组必须重叠拼接。也就是说形如 `ABC`，其中 `AB` 为前一个数组，`BC` 为后一个。

考虑对于相邻位置建图，只有得到是链的一整条才是符合要求的一个连续子串。

于是，我们可以得到若干种合法的连续子串。

考虑朴素 $dp_i$ 表示填完 $i$ 个的方案数。

枚举一个长度转移即可。不难发现不同长度是 $\sqrt{\sum c_i}$ 的。总复杂度 $O(n\sqrt{\sum c_i})$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1) 
#pragma GCC optimize(2,3,"Ofast","inline")
using namespace std;
const int mod=998244353;
int c[300005],ind[300005],outd[300005],vis[300005],to[300005],cnt[300005],dp[300005];
vector<pair<int,int>> vc;
int siz=0,ok=1;
void dfs(int now){
	vis[now]=1;
	siz++;
	if(!outd[now]) return ;
	if((outd[to[now]]>1)||(ind[to[now]]>1)){
		ok=0;
		return ;
	}
	dfs(to[now]);
}
signed main(){
	int n,m,k; cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		int lst; cin>>lst;
		for(int j=2;j<=c[i];j++){
			int a; cin>>a;
			if(lst==a) ind[lst]=outd[lst]=114514;
			if(to[lst]!=a) ind[a]++,outd[lst]++;
			to[lst]=a;
			lst=a;
		}
	}
	for(int i=1;i<=k;i++){
		if(ind[i]==0&&outd[i]==0) vis[i]=1,cnt[1]++;
		if(ind[i]==0&&outd[i]==1){
			siz=0; ok=1;
			dfs(i);
			if(ok) cnt[siz]++;
		}
	}
	for(int i=1;i<=m;i++) if(cnt[i]) vc.push_back(make_pair(i,cnt[i])); 
	dp[0]=1;
	for(int i=1;i<=m;i++){
		for(auto v:vc){
			if(i-v.first<0) continue;
			(dp[i]+=dp[i-v.first]*v.second)%=mod;
		}
	}
	cout<<dp[m];
	return 0;
}

```

---

## 作者：happybob (赞：0)

简单题。

限制比较奇怪，但是仔细思考一下发现，对于第 $i$ 个序列 $A_i$，限制等价于 $A_i$ 中所有数每一次在序列 $a$ 中出现，都是与 $A_i$ 一起出现的。同时可以发现如果 $A_i$ 中有重复数字，那么 $A_i$ 必然不能出现在 $a$ 中。

然后考虑如果所有序列两两数字不同怎么做。此时序列 $a$ 本质上就是若干个给定序列以及不存在于序列中的数拼接而成。直接 DP 是 $O(m^2)$ 的，但是注意到本质不同长度只有 $O(\sqrt{\sum c_i})$ 个即可做到 $O(m\sqrt{\sum c_i})$。

进一步地，考虑序列之间可能有重复数字。容易发现两个序列如果后缀前缀相同可以拼接。建立有向图，对于每个序列，连接相邻两个数。图中的所有链就是可以被用来拼接的。于是问题解决。

[Submission Link.](https://codeforces.com/contest/1574/submission/293337695)

---

## 作者：迟暮天复明 (赞：0)

首先每个串都是整个出现的。

然后显然如果多个串中有同一个数字的话，必须要全部串在一起。

于是考虑前后连边，如果有分叉或者有环，那么整个块都没得选。否则一定是整条链选。这个东西可以并查集维护。

观察到不同长度的链的数量不会超过根号种，那就直接大力 DP 即可，时间复杂度 $O(m\sqrt k)$。

---

## 作者：peterwuyihong (赞：0)

题意：给 $n$ 个值域为 $[1,k]$，长度都小于 $m$ 的序列 $A_i$，问你有多少个长度为 $m$ 的序列 $a$，值域为 $[1,k]$，任意 $A_i$ 在序列 $a$ 中的出现次数大于等于其任意一个非空**子段**在 $a$ 中的出现次数。定义 $a$ 在 $b$ 中出现次数为 

$$\sum_{l=1}^n\sum_{r=l+1}^n[b[l,r]=a]$$

前置芝士：分清 subarray 和 subsequence

很妙的一道题。

显然 $A_i$ 的一个数在 $a$ 中出现，那么 $A_i$ 的下一个数必须跟着它啊！

那么形象化的表达，把相邻的数前面向后面连边，可能会出现重边和自环。

出现环即出现相同元素，必然排除了，出现分岔就二者不可得兼，也 G 了，这种时候，就剩下了若干个链（**点也算链啊**

设链长度的可重集为 $S$，你一下子捏出一个生成函数 $f(x)=\sum_{siz\in S}x^{siz}$，枚举选的链的条数 $i$，则答案为 $[x^m]1+f(x)+f(x)^2+\ldots=(1-f(x))^{-1}$。

判链直接按照出入度判就行了，爽啊

```cpp
signed main(){
  int n,m,k;
  cin>>n>>m>>k;
  vector<vector<int> >g(k);
  vector<int>fa(k),in(k),out(k);
  iota(all(fa),0);
  map<pair<int,int>,int>M;
  function<int(int)>get=[&](int x){
    if(x==fa[x])return x;
    return fa[x]=get(fa[x]);
  };
  auto Add=[&](int x,int y){
    if(M[{x,y}])return;
    M[{x,y}]=1;
    g[x].push_back(y);
    fa[get(x)]=get(y);
    in[y]++,out[x]++;
  };
  while(n--){
    int c,lst;
    cin>>c>>lst;
    while(--c){
      int u;cin>>u;
      Add(lst-1,u-1);lst=u;
    }
  }
  vector<vector<int> >faset(k);
  vector<bool>vis(k);
  rep(i,0,k-1)faset[get(i)].push_back(i);
  vector<int>S;
  for(auto j:faset)if(j.size()){
    int u=0;
    for(int i:j)u+=in[i];
    bool gg=u!=j.size()-1;
    for(int i:j)gg|=in[i]>1||out[i]>1;
    if(gg)continue;
    S.push_back(j.size());
  }
  poly a(m+1);
  for(int i:S)if(i<=m)a[i]++;
  a=-a;
  add(a[0],1);
  cout<<Inv(a)[m]<<endl;
}
```

---

