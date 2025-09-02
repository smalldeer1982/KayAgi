# GCD Counting

## 题目描述

You are given a tree consisting of $ n $ vertices. A number is written on each vertex; the number on vertex $ i $ is equal to $ a_i $ .

Let's denote the function $ g(x, y) $ as the greatest common divisor of the numbers written on the vertices belonging to the simple path from vertex $ x $ to vertex $ y $ (including these two vertices).

For every integer from $ 1 $ to $ 2 \cdot 10^5 $ you have to count the number of pairs $ (x, y) $ $ (1 \le x \le y \le n) $ such that $ g(x, y) $ is equal to this number.

## 样例 #1

### 输入

```
3
1 2 3
1 2
2 3
```

### 输出

```
1 4
2 1
3 1
```

## 样例 #2

### 输入

```
6
1 2 4 8 16 32
1 6
6 3
3 4
4 2
6 5
```

### 输出

```
1 6
2 5
4 6
8 1
16 2
32 1
```

## 样例 #3

### 输入

```
4
9 16 144 6
1 3
2 3
4 3
```

### 输出

```
1 1
2 1
3 1
6 2
9 2
16 2
144 1
```

# 题解

## 作者：intel_core (赞：16)

直接求 $\gcd =k$ 的点对是没法快速求的，所以我们转而求 $\gcd$ 为 $k$ 倍数的点对数量。

一个最朴素的想法就是取出所有点权为 $k$ 倍数的点，然后用并查集合并，扫一遍每个连通块。

如果有 $V$ 个点的点权是 $k$ 的倍数的话，对 $k$ 求一次的复杂度是 $O(V)$ 的。

然后你写了一发这个做法，发现它很神奇地过了）

对于 $\le 2\times 10^5$ 的所有数，因数最多的是 $166320=2^4 \times 3^3 \times 5 \times 7 \times 11$， 有 $160$ 个因数。

所以对于上述做法，复杂度上界 $O(160n)$ ，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=2e5+10;
#define ll long long
int n,a[NR],flag[NR],fa[NR];
vector<int>g[NR],v[NR];
#define pb push_back

ll f[NR],size[NR];
int get(int x){
	if(fa[x]==x)return x;
	return fa[x]=get(fa[x]);
}
void merge(int x,int y){
	x=get(x);y=get(y);
	if(x==y)return;
	fa[x]=y;size[y]+=size[x];
}
void init(){
	for(int i=1;i<=n;i++)size[i]=1,fa[i]=i;
}

signed main(){
	cin>>n;init();
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		for(int j=1;j<=sqrt(a[i])+0.5;j++)
			if(a[i]%j==0){
				if(j*j==a[i])v[j].pb(i);
				else v[j].pb(i),v[a[i]/j].pb(i);
			}
	}
	for(int i=1,x,y;i<n;i++)
		scanf("%d%d",&x,&y),g[x].pb(y),g[y].pb(x);
	for(int i=1;i<=2e5;i++){
		for(int x:v[i])flag[x]=1;
		for(int x:v[i])
			for(int k:g[x])
				if(flag[k])merge(x,k);
		for(int x:v[i])
			if(fa[x]==x)f[i]+=size[x]*(size[x]+1)/2;
		for(int x:v[i])
			flag[x]=0,size[x]=1,fa[x]=x;
	}
	for(int i=2e5;i>=1;i--)
		for(int j=2;j*i<=2e5;j++)f[i]-=f[i*j];
	for(int i=1;i<=2e5;i++)
		if(f[i])printf("%d %lld\n",i,f[i]);
	return 0;
}
```

---

## 作者：LCuter (赞：9)

## CF990G 题解

##### $\text{Description}$

给定一棵点带权无根树，对于每个 $k\in[1,2\cdot 10^5]$，求出有多少个无序点对 $(x,y)$ 满足 $x$ 到 $y$ 的简单路径上的所有节点的点权的 $\gcd$ 为 $k$。

$1\le n,a_i\le 2\cdot 10^5$

##### $\text{Solution}$

为了方便，下设点权值域为 $A$。

直接统计 $\gcd$ 不大方便，考虑莫比乌斯反演一下。

记 $F(x)$ 表示当前有多少链的 $\gcd$ 为 $x$，$G(x)$ 表示当前有多少链的 $\gcd$ 包含 $x$ 这一因子，则有
$$
F(n)=\sum_{n|d}G(d)\mu(\frac{d}{n})
$$



如果能计算出 $G(x)$，则我们可以 $\mathcal O(A\log A)$ 地计算出 $F(x)$。

考虑一条链的 $\gcd$ 包含 $x$ 这一因子，意味着该链上所有点的点权都包含 $x$ 这一因子。

对于每一个 $x$，我们将所有点权不包含 $x$ 这一因子的点及其连出的边删去，$G(x)$ 即剩余各个连通块内的链个数。

暴力计算是 $\mathcal O(nA)$ 的，无法通过。注意到一个数的因子个数是 $\mathcal O(\sqrt A)$ 级别的，我们考虑开个 vector，vector 的第 $x$ 位存所有点权包含 $x$ 这一因子的点。当我们在计算 $x$ 的时候，仅枚举其对应的 vector 中的点与两端点都在该 vector 内的边即可。

时间复杂度 $\mathcal O(n\sqrt A)$，可以通过本题。

##### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define REG register
using namespace std;
inline void read(int& x){
	static char c;
	while(!isdigit(c=getchar()));x=c^48;
	while(isdigit(c=getchar()))x=(x*10)+(c^48);
}

const int N=200005;

int n;

int A[N],mu[N],Prm[N],vis[N],Pcnt;

inline void Euler(){
	mu[1]=1;
	for(REG int i=2;i<=N-5;++i){
    	if(!vis[i]) Prm[++Pcnt]=i,mu[i]=-1;
		for(REG int j=1;j<=Pcnt&&i*Prm[j]<=N-5;++j){
			vis[i*Prm[j]]=1;
			if(i%Prm[j]==0) break;
			mu[i*Prm[j]]=-mu[i];
		}
	}
}

long long F[N],G[N];

struct Edge{int v,nxt;}ed[N<<1];
int head[N],cnt;
inline void adde(int u,int v){ed[++cnt]=(Edge){v,head[u]},head[u]=cnt;}
inline void add(int u,int v){adde(u,v),adde(v,u);}

vector<int> V[N];

int gcd(int a,int b){return b?gcd(b,a%b):a;}

int tot,Vis[N];

void dfs(int now,int fa,int d){
	++tot,Vis[now]=1;
	for(REG int i=head[now];i;i=ed[i].nxt){
		int v=ed[i].v;
		if(v==fa||A[v]%d) continue;
		dfs(v,now,d);
	}
}

inline void Work(){
	Euler();
	read(n);
	for(REG int i=1;i<=n;++i) read(A[i]);
	for(REG int i=1;i<=n;++i)
		for(REG int j=1;j*j<=A[i];++j){
			if(A[i]%j) continue;
			V[j].push_back(i);
			if(j^(A[i]/j)) V[A[i]/j].push_back(i);
		}
	for(REG int i=1;i<n;++i){
		int u,v;read(u),read(v),add(u,v);
	}
	for(REG int i=1;i<=N-5;++i){
		for(REG int j=0;j<V[i].size();++j)
			if(!Vis[V[i][j]]) tot=0,dfs(V[i][j],0,i),G[i]+=1ll*tot*(tot+1)/2;
		for(REG int j=0;j<V[i].size();++j)
			Vis[V[i][j]]=0;
	}
	for(REG int i=1;i<=N-5;++i)
		for(REG int j=i;j<=N-5;j+=i)
			F[i]+=G[j]*mu[j/i];
	for(REG int i=1;i<=N-5;++i)
		if(F[i]) printf("%d %lld\n",i,F[i]);
}

int main(){Work();}
```



---

## 作者：Acoipp (赞：5)

## **分析**

题意很简单，此处不再赘述。

首先看到是求 $\gcd$，而且范围只有 $2\times 10^5$，所以很自然地想到了容斥。

设 $f_i$ 表示答案为 $i$ 的倍数的点对数量，那么最后恰好为 $i$ 的点对数量可以用容斥的思想求出来。

即：

$$ans_i = f_i - \sum_{j=2}^{\lfloor \frac{n}{i} \rfloor}ans_{ij}$$

但是此处的 $i$ 必须从小到大枚举，否则容斥是错的。

对于每个枚举的 $i$，如果某条边两端都是 $i$ 的倍数，那么就将这条边两端的集合合并，最后对于并查集算有多少**不同的**点对在一个集合就可以了。

注意特判一下 $x=y$ 的情况，这样情况下的答案就是 $a_x$。

## **时间复杂度**

枚举 $i$ 需要 $2 \times 10^5$ 次循环，每次循环会枚举两端都是 $i$ 的倍数的边，这样的话每条边被遍历到的次数就是 $\operatorname{d}(\gcd(a_u,a_v))$。

因为在 $[1,2 \times 10^5]$ 中因数最多的数是 $166320$，有 $160$ 个因数，再加上并查集时间复杂度是常数级别，所以循环次数是 $2 \times 10^5 \times 160$ 级别的。

注意：此题略微卡空间。

## **代码**

```cpp
#include<bits/stdc++.h>
#define ll int
#define N 200005
using namespace std;
vector<ll> op[N];
ll n,x[N],y[N],i,j,temp,fath[N],a[N],si[N],f1,f2;
ll gf(ll x){return x==fath[x]?x:fath[x]=gf(fath[x]);}
long long ans[N];
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i],fath[i]=i,si[i]=1;
		for(j=1;j*j<=a[i];j++){
			if(a[i]%j==0){
				ans[j]++;
				if(a[i]/j!=j) ans[a[i]/j]++;
			}
		}
	}
	for(i=1;i<n;i++){
		cin>>x[i]>>y[i];
		temp = __gcd(a[x[i]],a[y[i]]);
		for(j=1;j*j<=temp;j++){
			if(temp%j==0){
				op[j].push_back(i);
				if(temp/j!=j) op[temp/j].push_back(i);
			}
		}
	}
	for(i=1;i<=2e5;i++){
		for(j=0;j<op[i].size();j++){
			f1 = gf(x[op[i][j]]),f2 = gf(y[op[i][j]]);
			if(f1!=f2){
				ans[i] -= 1ll*si[f1]*(si[f1]-1)/2+1ll*si[f2]*(si[f2]-1)/2;
				fath[f1] = f2;
				si[f2] += si[f1];
				ans[i] += 1ll*si[f2]*(si[f2]-1)/2;
			}
		}
		for(j=0;j<op[i].size();j++) fath[x[op[i][j]]]=x[op[i][j]],fath[y[op[i][j]]]=y[op[i][j]],si[x[op[i][j]]]=si[y[op[i][j]]]=1;
	}
	for(i=2e5;i>=1;i--){
		for(j=i+i;j<=2e5;j+=i) ans[i]-=ans[j];
	}
	for(i=1;i<=2e5;i++) if(ans[i]) cout<<i<<" "<<ans[i]<<endl;
}
```

---

## 作者：happybob (赞：4)

提供一个非常容易的做法。

还是考虑点分治，但不用莫反，也不用容斥。

考虑找出重心后深搜，找到每个点到重心的路径的点权 $\gcd$。把他们全都扔到 set 里面，直接枚举 set 里面两个数就好。

这看起来很暴力，其实是个经典套路。由于 $\gcd$ 在 $O(\log v)$ 的变化次数内就会成为 $1$，于是暴力枚举的复杂度是 $O(\log^2 v)$ 左右的，而且不太能跑满。

由于限时比较大，所以没有什么压力，复杂度应该是大约是三只 $\log$ 的？

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <numeric>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const int N = 2e5 + 5;

int n, a[N];
vector<int> G[N];
bool del[N];
unordered_map<int, int> cnt, tcnt;
unordered_set<int> st, tst;
int wc, tot;
int sz[N];
long long ans[N];
void dfs_sz(int u, int fa)
{
	sz[u] = 0;
	if (del[u]) return;
	sz[u] = 1;
	for (auto& j : G[u])
	{
		if (j != fa)
		{
			dfs_sz(j, u);
			sz[u] += sz[j];
		}
	}
}

void dfs_wc(int u, int fa)
{
	if (del[u]) return;
	int maxn = tot - sz[u];
	for (auto& j : G[u])
	{
		if (j != fa)
		{
			dfs_wc(j, u);
			maxn = max(maxn, sz[j]);
		}
	}
	if (maxn <= tot / 2) wc = u;
}

int dis[N];

void dfs_dis(int u, int d, int fa)
{
	if (del[u]) return;
	dis[u] = gcd(d, a[u]);
	ans[dis[u]]++;
	cnt[dis[u]]++;
	tcnt[dis[u]]++;
	tst.insert(dis[u]);
	st.insert(dis[u]);
	for (auto& j : G[u])
	{
		if (j != fa) dfs_dis(j, dis[u], u);
	}
}

void calc(int u)
{
	if (del[u]) return;
	cnt.clear();
	st.clear();
	wc = 0;
	tot = 0;
	dfs_sz(u, 0);
	tot = sz[u];
	dfs_wc(u, 0);
	u = wc;
	del[u] = 1;
	tcnt.clear();
	tst.clear();
	for (auto& j : G[u])
	{
		cnt.clear();
		st.clear();
		dfs_dis(j, a[u], u);
		for (auto& k1 : st)
		{
			for (auto& k2 : st)
			{
				if (k2 < k1) continue;
				if (k1 == k2)
				{
					ans[k1] -= (1LL * cnt[k1] * (cnt[k1] - 1LL) / 2LL);
				}
				else
				{
					ans[gcd(k1, k2)] -= (1LL * cnt[k1] * cnt[k2]);
				}
			}
		}
	}
	for (auto& k1 : tst)
	{
		for (auto& k2 : tst)
		{
			if (k2 < k1) continue;
			if (k1 == k2)
			{
				ans[k1] += (1LL * tcnt[k1] * (tcnt[k1] - 1LL) / 2);
			}
			else
			{
				ans[gcd(k1, k2)] += (1LL * tcnt[k1] * tcnt[k2]);
			}
		}
	}
	//cout << "\n\n";
	for (auto& j : G[u])
	{
		calc(j);
	}
	
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		ans[a[i]]++;
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	calc(1);
	for (int i = 1; i <= 200000; i++)
	{
		if (ans[i])
		{
			printf("%d %lld\n", i, ans[i]);
		}
	}
	return 0;
}
```


---

## 作者：MyukiyoMekya (赞：4)

这题还有一种复杂度并不正确的做法，但是由于开了 4.5s 的时限所以还是水过了，可能出题人就是想让这种做法过吧。

直接用 map 暴力存以 $u$ 为根的子树内不通过 $u$ 的路径种类以及个数，然后就是爆搜，暴力合并，暴力计算答案。

~~这不是暴力么，怎么能过？~~

这里可以用 dsu on tree 的思想来优化，dfs 的时候一直传重儿子的 map ，然后合并的时候就把其他轻儿子的 map 合并到重儿子的 map 上。

时间复杂度应该是 $\mathcal O(n\log^4n)$ ，但是常数实在是太大了。

~~最大一个点跑了将近 4s。~~

---

upd(2022.09.23):

两年前比较笨，啥都不懂，看到有人提出疑问了就来修一下。

`dfs_init` 用不用都无所谓，对复杂度没有影响。（上面 dsuontree 完全是在乱说）

单个点的 `dr.size()` 最大为 $\max d(A)=d=158$。

所以复杂度为 $\mathcal O(nd^2\log A)$。

或许是因为跑不满所以过了。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
// #define int long long
using namespace std;
const int MaxN=200050;
struct Edge
{
	int nxt,to;
}E[MaxN<<2];
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
int hd[MaxN],en;
int val[MaxN];
long long ans[MaxN];
int siz[MaxN],bson[MaxN];
inline void adde(int u,int v)
{
	++en;
	E[en]=(Edge){hd[u],v};
	hd[u]=en;
	return;
}
inline int gcd(int a,int b)
{
	return !b?a:gcd(b,a%b);
}
inline void dfs_init(int u,int fa)
{
	siz[u]=1;
	for(reg int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		if(v==fa)
			continue;
		dfs_init(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[bson[u]])
			bson[u]=v;
	}
	return;
}
inline void dfs(int u,int fa,map<int,long long> &dru)
{
	if(bson[u])
		dfs(bson[u],u,dru);
	for(int i=hd[u];~i;i=E[i].nxt)
	{
		reg int v=E[i].to;
		reg map<int,long long> drv;
		if(v==fa||v==bson[u])
			continue;
		dfs(v,u,drv);
	for(reg map<int,long long>::iterator iter=dru.begin();iter!=dru.end();++iter)
		for(reg map<int,long long>::iterator Iter=drv.begin();Iter!=drv.end();++Iter)
			ans[gcd(iter->first,Iter->first)]+=iter->second*Iter->second;
		for(reg map<int,long long>::iterator iter=drv.begin();iter!=drv.end();++iter)
			dru[gcd(iter->first,val[u])]+=iter->second;
	}
	dru[val[u]]+=1;
	for(reg map<int,long long>::iterator iter=dru.begin();iter!=dru.end();++iter)
		ans[iter->first]+=iter->second;
	return;
}
signed main(void)
{
	// freopen("d80.txt","r",stdin);
	// freopen("my.out","w",stdout);
	memset(hd,-1,sizeof hd);
	int n;cin>>n;
	reg int u,v;
	for(int i=1;i<=n;++i)
		read(val[i]);
	for(int i=1;i<n;++i)
	{
		read(u);read(v);
		adde(u,v);
		adde(v,u);
	}
	reg map<int,long long> baolichuqiji;
	dfs(1,0,baolichuqiji);
	for(int i=1;i<MaxN;++i)
		if(ans[i])
			printf("%d %lld\n",i,ans[i]);
	return 0;
}
   
```

---

## 作者：大菜鸡fks (赞：3)

由于gcd具有收敛性，所以直接map暴力统计是对的

那就是最裸的点分（网上很多点分写法都有点问题。这是我的写法，不知道对不对。。）

```cpp
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll; 
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(ll x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(ll x){write(x); puts("");}
const int N=2e5+5;
int n,val[N],tot,head[N],Max;
struct edge{
	int link,next;
}e[N<<1];
inline void add_edge(int u,int v){
	e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void insert(int u,int v){
	add_edge(u,v); add_edge(v,u);
}
inline void init(){
	n=read();
	for (int i=1;i<=n;i++) val[i]=read(),Max=max(Max,val[i]);
	for (int i=1;i<n;i++){
		insert(read(),read());
	}
} 
ll ans[N];
int pa[N],All,sz[N],root,rt,mx[N];
bool mark[N];
void getroot(int u,int fa){
	sz[u]=1; mx[u]=0; pa[u]=fa;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=fa&&!mark[v]){
			getroot(v,u);
			sz[u]+=sz[v];
			mx[u]=max(mx[u],sz[v]);
		}
	}
	mx[u]=max(mx[u],All-sz[u]);
	if (!rt||mx[rt]>mx[u]) rt=u;
}
int gcd(int x,int y){return (!y)?x:gcd(y,x%y);}
map<int ,int >mp1,mp2;
void dfs(int u,int fa,int x){
	mp2[x]++;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=fa&&!mark[v]){
			dfs(v,u,gcd(x,val[v]));
		}
	}
}
map<int ,int >::iterator it1,it2;
inline void work(int u){
	mp1.clear(); mp1[val[u]]++; ans[val[u]]++;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (!mark[v]){
			mp2.clear(); dfs(v,u,gcd(val[u],val[v]));
			for (it1=mp1.begin();it1!=mp1.end();it1++){
				for (it2=mp2.begin();it2!=mp2.end();it2++){
					int t=gcd((*it1).first,(*it2).first);
					ans[t]+=1ll*(*it1).second*(*it2).second;
				}
			}
			for (it1=mp2.begin();it1!=mp2.end();it1++){
				mp1[(*it1).first]+=(*it1).second;
			} 
		}
	}
}
void divide(int u,int al){
	mark[u]=1; work(u);
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (!mark[v]){
			rt=0; All=(v==pa[u])?al-sz[u]:sz[v];
			getroot(v,0);
			divide(rt,All);
		}
	}
}
inline void solve(){
	All=n; rt=0;
	getroot(1,0);
	divide(rt,n);
	for (int i=1;i<=Max;i++){
		if (ans[i]){
			write(i); putchar(' '); writeln(ans[i]);
		}
	}
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

## 作者：tder (赞：1)

烂题，卡我空间。

---

对于一条链 $(d_1=u)\to d_2\to\cdots\to d_{m-1}\to(d_m=v)$，若其 $\gcd$ 为 $k$，则显然的 $a_{d_i}$ 均为 $k$ 的倍数。

我们不妨先预处理出每个 $g_k=\{i~|~(k~|~a_i)\}$，很容易想到可以枚举 $a_i$ 的因数反向处理。

我们枚举每个 $k$，则每个 $i\in g_k$ 是显然可取的。对于一条边 $u\to v$，若 $u\in g_k$ 且 $v\in g_k$，则这条边可取。由于给定的树，不难想到用并查集维护，将每条可取的边的两个节点合并即可。

我们最终会得到若干个连通块，接下来考虑如何统计答案。

对于一个大小为 $m$ 的连通块，即一条长度为 $m$ 的链 $(d_1=u)\to d_2\to\cdots\to d_{m-1}\to(d_m=v)$，我们取其一个子链，有 $\dfrac{m(m+1)}2$ 种方案。具体的，以 $d_1$ 为起点的共 $m$ 条，以 $d_2$ 为起点的共 $m-1$ 条，依次类推，则最终共 $\displaystyle\left(\sum_{i=1}^mi\right)=\frac{m(m+1)}2$ 种。特别需要注意，单个点也是满足条件的链。

于是我们便愉快的做完了，举个例子形象说明一下。

这是一棵树，此处直接用点权代替节点编号。

![](https://cdn.luogu.com.cn/upload/image_hosting/mru1nryc.png)

对于 $k=2$ 时，我们预处理的 $g_k=\{2,4,6,8,10,12,14,16\}$。

那么，不难发现我们可以有可取的链 $2\to6\to4\to8\to16$，其贡献为 $15$，以及 $10\to12$ 贡献为 $3$，和单独成链的 $14$ 贡献为 $1$。于是答案为 $15+3+1=19$。

最后分析一下复杂度，我们忽略并查集操作复杂度中的 $\alpha(n)$ 不计，复杂度为 $\displaystyle O\left(\sum\tau(a_i)\right)$。对于 $a_i\le2\times10^5$，$\tau(a_i)$ 不超过 $160$，因此极限复杂度大概是 $O(3.2\times10^7)$，甚至更少，显然可过。

---

## 作者：Hisaishi_Kanade (赞：1)

$\gcd=k$ 不是很好做，但是考虑一个性质：$k\mid x\wedge k\mid y\iff k\mid \gcd(x,y)$。也就是说，只要一条 $x\to y$ 的路径上的权值全是 $k$ 的倍数，$k\mid g(x,y)$。

这个的统计是不难的，我们通过并查集维护，对于每个极大的连通块的大小 $siz$，其贡献是 $siz(siz-1)$，即其中任意两个不相同的点之间的简单路径。

考虑合并大小分别为 $x,y$ 的连通块，显然由于合并的两个并非极大连通块，所以先减去先前计算的两者的贡献 $\dfrac {x(x-1)} 2+\dfrac{y(y-1)} 2$，再将合并后的贡献算出来 $\dfrac {(x+y)(x+y-1)} 2$。所以合并的贡献即为 $\dfrac {(x+y)(x+y-1)-x(x-1)} 2$，小学数学得到为 $xy$。

好，现在我们设 $d(i)$ 表示 $i\mid g(x,y)$ 的简单路径 $x\to y$ 方案数。
考虑求出答案 $f(i)$ 表示 $i= g(x,y)$ 的简单路径 $x\to y$ 方案数。

容斥解决，$f(i)=d(i)-\sum\limits_{k=2}^{\lfloor\frac n i\rfloor} f(ki)$。这样我们倒序枚举 $i$，可以保证右侧的 $\sum$ 内 $f$ 均被计算过。

```cpp 
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
static const int Buf_size=1<<25;
static char _c; static int _x;
static const signed int base_10=10, zero(48), nine(57), flag_signed(45);
static char buf[Buf_size], *p1=buf, *p2=buf;
#define digit() (zero<=_c&&_c<=nine)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Buf_size,stdin),p1==p2)?EOF:*p1++)
inline int read(){_x=0;_c=getchar();while(!digit()){_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return _x;}
const int N=3e5+5, V=2e5, inf=2e9;
const ll illf=1e18;
int a[N], u[N], v[N];
int qt, n, i, j, k, g, x, y;
vector<int> q[N];
int f[N]; ll ans[N], siz[N];
inline int find(int x) {while(x!=f[x]) x=f[x]=f[f[x]]; return x;}
int main()
{
	rep(i, 1, V) ans[i]=0;
	n=read(); rep(i, 1, n) a[i]=read(); rep(i, 2, n) u[i]=read(), v[i]=read(); rep(i, 1, n) f[i]=i;
	rep(i, 1, n)
	{
		g=a[i];
		for(j=1; j*j<g; ++j) if(g%j==0) ++ans[j], ++ans[g/j];
		if(j*j==g) ++ans[j];
	}
	rep(i, 2, n)
	{
		g=gcd(a[u[i]], a[v[i]]);
		for(j=1; j*j<g; ++j)
			if(g%j==0)
			{
				q[j].emplace_back(i);
				q[g/j].emplace_back(i);
			}
		if(j*j==g) q[j].emplace_back(i);
	}
	rep(i, 1, n) siz[i]=1; rep(i, 1, V)
	{
		if(q[i].empty()) continue;
		for(auto rh : q[i])
		{
			x=find(u[rh]); y=find(v[rh]);
			if(x==y) continue;
			ans[i]+=siz[x]*siz[y];
			f[x]=y;
			siz[y]+=siz[x];
		}
		for(auto rh : q[i]) f[u[rh]]=u[rh], f[v[rh]]=v[rh], siz[u[rh]]=siz[v[rh]]=1;
	}
	req(i, V, 1) {j=2; while(i*j<=V) ans[i]-=ans[i*j++];}
	rep(i, 1, V) if(ans[i]) printf("%d %lld\n", i, ans[i]);
}
```

---

## 作者：Missa (赞：1)

不用莫反，不用并查集，不用点分治。

首先恰好显然不好做，统计其倍数，然后一一减掉。

即，如果 $d$ 的答案是 $f_d$，现在的 $f_d$ 事实上是 $\sum_{d | x} f_x$，其中的 $f$ 就是所求答案，则

```cpp
for (int i = m; i >= 1; i--) {
  for (int j = i + i; j <= m; j += i) 
    f[i] -= f[j];
}
```

即可。

下一步是统计答案。显然统计各连通块大小就行了。你寻思怎么才能保证复杂度，一拍脑门想到一个点的父亲是唯一的，那不就把一个点贡献给父亲就行了。为了保证一个点的贡献被计算完才会给贡献，把点按深度从大到小排个序不就行了。

综上，只用一点简单的算法，这题做完了。这个做法的复杂度是 $O(\sum d(a_i)\log n)$，瓶颈排序，但较难卡满。

按理说会好写多的，但是只比点分治少了 0.5k，怎么会是呢？

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int M = 3e5 + 5;
int a[M], fa[M];
LL f[M], g[M];
int n, dep[M], siz[M], m = 2e5;
vector<int> e[M], fac[M], d[M];
bool in[M], vis[M];
void pre(int n = 2e5) {
  for (int i = 1; i <= n; i++) 
    for (int j = i; j <= n; j += i)
      fac[j].push_back(i);
}
int main() {
  scanf("%d", &n); pre();
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    for (auto x : fac[a[i]]) d[x].push_back(i);
  }
  for (int i = 1; i < n; i++) {
    int u, v; scanf("%d %d", &u, &v);
    e[u].push_back(v), e[v].push_back(u);
  }
  auto dfs = [&](auto self, int u, int f) -> void {
    fa[u] = f, dep[u] = dep[f] + 1;
    for (auto v : e[u]) {
      if (v == f) continue;
      self(self, v, u);
    }
  } ;
  dfs(dfs, 1, 0);
  for (int i = 1; i <= m; i++) {
    for (auto u : d[i]) in[u] = 1, siz[u] = 1;
    sort(d[i].begin(), d[i].end(), [&](int u, int v) -> bool { return dep[u] > dep[v]; });
    for (auto u : d[i]) 
      if (in[fa[u]]) siz[fa[u]] += siz[u], siz[u] = 0;
    for (auto u : d[i])
      f[i] += 1ll * siz[u] * (siz[u] + 1) / 2;
    for (auto u : d[i]) in[u] = 0, siz[u] = 0;
  }
  for (int i = m; i >= 1; i--) {
    for (int j = i + i; j <= m; j += i) 
      f[i] -= f[j];
  }
  for (int i = 1; i <= m; i++) if (f[i] > 0)
    printf("%d %lld\n", i, f[i]);
}
```

---

## 作者：Echidna (赞：1)

这题是一道莫比乌斯反演好题，让我见识到了更多的莫反玩法。

首先题目让我们求的是一个函数

$$f(x)=\sum_{i=1}^n\sum_{j=i}^n\left[\operatorname{d}(i,j)=i\right]$$

这个函数十分难求，但是我们可以考虑求下面这个函数，这个函数很容易求：

$$f(x)=\sum_{i=1}^n\sum_{j=i}^n\left[x|\operatorname{d}(i,j)\right]$$

并且函数 $f$ 和函数 $g$ 之间有如下关系：

$$g(x)=\sum_{x|d}f(x)$$

于是根据莫比乌斯反演的第二种形式，我们可以做转换：

$$g(x)=\sum_{x|d}f(x)\ \to\ f(x)=\sum_{x|d}\mu(\frac{d}{x})g(d)$$

~~这个形式可能有些人不知道，顺便说一下吧~~

那么现在我们只要知道 $g$ 函数在所有位置上的取值就可以在 $O(n\log n)$ 时间复杂度内求出 $f$ 函数在所有位置上的取值了。

我们假设最大的一个节点的点权为 $V$ ，那么很容易得到任意一个节点的点权的因子个数为 $O(\sqrt{V})$ 。

于是我们只需要先对每一个点的点权求出它的所有因子，之后对于每一个因子 $d$ 都建一张图，这张图上只存在点权能被 $d$ 整除的点和它们之间连接的边。

在这张图上，我们很容易发现一个大小为 $s$ 的联通块对 $g(d)$ 的贡献为 $\dfrac{s(s+1)}{2}$ ，于是我们建好图之后只需要统计一下里面联通块的大小即可。

虽然会建 $O(V)$ 次图，但是这些图的总点数为 $O(V\sqrt{V})$ ，所以计算出 $g$ 函数在所有位置的取值的时间复杂度也就是 $O(V\sqrt{V})$ 。

于是我们就可以在 $O(V\sqrt{V} + V \log V)$ 的时间复杂度内得到答案了。

Code:

```cpp
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
const int N=1e6;
vector<int> vec[N];
struct side{
    int t,n;
}ss[N];
int head[N];
int cnt=0;
void add(int f,int t){
    ss[++cnt].t=t;
    ss[cnt].n=head[f];
    head[f]=cnt;
}
#define FOR(x) for(int nxt=head[x];nxt;nxt=ss[nxt].n)
#define TP ss[nxt].t
bool vis[N];
bool ce[N];
int dfs(int x){
    int ans=1;
    vis[x]=1;
    FOR(x){
        if(!vis[TP]&&ce[TP])
        ans+=dfs(TP);
    }
    return ans;
}
int mu[N];
bool isprime[N];
int prime[N];
int pc=0;
void sieve(int n){
    memset(isprime,1,sizeof(isprime));
    mu[1]=1,isprime[1]=0;
    for(int i=2;i<=n;i++){
        if(isprime[i])
            prime[++pc]=i,mu[i]=-1;
        for(int j=1;j<=pc&&i*prime[j]<=n;j++){
            isprime[i*prime[j]]=0;
            if(i%prime[j]==0)break;
            mu[i*prime[j]]=-mu[i];
        }
    }
}
int n;
int a[N];
long long g[N];
int read(){
    int x=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c))x=x*10+c-'0',c=getchar();
    return x*f;
}
int main(){
    n=read();
    sieve(2e5);
    int ma=0;
    for(int i=1;i<=n;i++){
        a[i]=read(),ma=max(ma,a[i]);
        for(int j=1;j*j<=a[i];j++)
            if(j*j==a[i])vec[j].push_back(i);
            else if(a[i]%j==0)vec[j].push_back(i),vec[a[i]/j].push_back(i);
    }
    for(int f,t,i=1;i<n;i++){
        f=read(),t=read();
        add(f,t);
        add(t,f);
    }
    for(int i=1;i<=ma;i++){
        if(vec[i].empty())continue;
        for(auto k:vec[i])
            ce[k]=1;
        for(auto st:vec[i])
            if(!vis[st]){
                int temp=dfs(st);
                g[i]+=1ll*temp*(temp+1)/2;
            }
        for(auto k:vec[i])
            ce[k]=0,vis[k]=0;
    }
    for(int i=1;i<=ma;i++){
        long long ans=0;
        for(int j=1;i*j<=ma;j++)
            ans+=mu[j]*g[i*j];
        if(ans==0)continue;
        else {
            printf("%d %lld\n",i,ans);
        }
    }
}
```


---

## 作者：LJQ0808 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF990G)
# 题解
我们发现此题是关于合法路径对数，于是我们可以朝点分治的方向考虑。

假设当前的分治到的重心为 $x$，很显然，经过 $x$ 的那些合法的链，肯定链中每个数都含有起码一个相同的$a_x$ 的质因子，因为 $num∣a_x$。把 $a_x$ 分解质因数，然后对每个质因子 $p$，都做一次 dfs，求出质因数路径的个数。

注意，单独一个点也算进答案。

AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define pii pair<int,int>
#define fi first
#define se second
const int N=2e5+5;
int n;
int a[N];
vector<int> g[N];
void add_edge(int u,int v){
	g[u].push_back(v);
}
void add_und_edge(int u,int v){
	add_edge(u,v);add_edge(v,u);
}
bool vis[N];
int sz[N];
void dfs_sz(int u,int f){
	sz[u]=1;
	for(int v:g[u]){
		if(v!=f && !vis[v]){
			dfs_sz(v,u);
			sz[u]+=sz[v];
		}
	}
}
int dfs_hea(int u,int f,int siz){
	for(int v:g[u]){
		if(v!=f && !vis[v] && 2*sz[v]>siz){
			return dfs_hea(v,u,siz);
		}
	}
	return u;
}
ll ans[N];
unordered_map<int,int> mp,tmp;
void dfs_dis(int u,int f,int val){
	val=__gcd(val,a[u]);
	for(pii P:mp){
		ans[__gcd(val,P.fi)]+=P.se;
	}
	tmp[val]++;ans[val]++;
	for(int v:g[u]){
		if(v!=f && !vis[v]){
			dfs_dis(v,u,__gcd(val,a[v]));
		}
	}
}
void work(int u){
	for(int v:g[u]){
		if(!vis[v]){
			dfs_dis(v,u,a[u]);
			for(pii P:tmp){
				mp[P.fi]+=P.se;//合并。 
			}
			tmp.clear();
		}
	}
	mp.clear();
} 
void build(int u){
	vis[u]=1;
	work(u);
	for(int v:g[u]){
		if(!vis[v]){
			dfs_sz(v,0);
			int rt=dfs_hea(v,0,sz[v]);
			build(rt);
		}
	}
}
signed main(){
	//HAPPY!
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		add_und_edge(x,y);
	}
	{
		dfs_sz(1,0);
		int rt=dfs_hea(1,0,sz[1]);
		build(rt);//点分治。 
	}
	for(int i=1;i<=n;i++){
		ans[a[i]]++;//单独一个点也算。 
	}
	for(int i=1;i<=2e5;i++){
		if(ans[i]){
			cout<<i<<" "<<ans[i]<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：To_our_starry_sea (赞：0)

### solution

简单树上数数题。注意下文中 $\gcd(x, y)$ 表示从点 $x$ 到点 $y$ 的链上的 $a_i$ 的 $\gcd$ 值。

首先考虑 $\gcd(x, y) = k$ 这一条件不容易刻画，所以我们很自然的想到 $k \mid \gcd(x, y) $ 的情况，即 $k$ 为 $\gcd(x, y)$ 的因子。注意到对于 $a_i \le 2 \times 10^5$，$\max(d(a_i)) = 160$，所以我们可以先筛出所有 $a_i$ 的因子，在从依序处理每一个 $k$ 的情况，由于 $d(x)$ 在 $O(\sqrt{x})$ 级别，因此这么做的复杂度为 $O(n \sqrt{A})$，其中 $A = 2 \times 10^5$。

接着，我们考虑每一个 $k$，设 $f_k$ 表示满足 $ k \mid \gcd(x, y) $ 的 $x$ 和 $y$ 的对数。我们将所有满足 $  k \mid a_i$ 的 $i$ 加入一个集合中，并用并查集维护该集合中点的连通性。对于其中一个大小为 $S$ 的联通快，其对 $f_k$ 的贡献为 $\frac{S(S + 1)}{2}$，注意 $x$ 可以与 $y$ 相等。

接下来我们如何利用已知的 $f_k$ 算出最终的答案呢？设 $ans_k$ 表示满足 $\gcd(x, y) = k$ 的对数，我们有两种方法。

第一种容斥，考虑 $f_k = \sum_{k \mid n} ans_n$，即 $f_k$ 等于所有大于等于 $k$ 且是 $k$ 的倍数的 $ans_n$ 之和，从而我们可以从大到小处理 $ans_n$，按上述方法减去重复计算的值即可。

第二种莫比乌斯反演，由数论知识不难得出以下的式子：

$$
ans_n = \sum_{n \mid d}f_d\mu(\frac{d}{n})
$$

从而可以求出 $ans_n$ 的值。

代码实现使用的是第一种方法。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 200005;
int n, cnt = 0, head[MAXN], a[MAXN], fa[MAXN], par[MAXN], sum[MAXN];
bool vis[MAXN];
ll ans[MAXN];
struct edge {
	int to, next;
} e[MAXN << 1];
vector<int> p[MAXN], w[MAXN];
inline void add(int u, int v) {
	cnt++;
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;
}
inline int find(int k) {
	if (fa[k] == k) return k;
	else return fa[k] = find(fa[k]);
}
inline void dfs(int u, int pre) {
	par[u] = pre;
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].to;
		if (v == pre) continue;
		dfs(v, u);
	}
}
inline int read() { 
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
		   f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
int main() {
	n = read();
	int maxn = 0;
	for (int i = 1; i <= n; i++) a[i] = read(), maxn = max(maxn, a[i]), fa[i] = i, sum[i] = 1;
	for (int i = 1; i <= n - 1; i++) {
		int u = read(), v = read();
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	for (int i = 1; i <= maxn; i++) {
		for (int j = i; j <= maxn; j += i) p[j].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		for (auto v : p[a[i]]) w[v].push_back(i);
	}
	for (int i = 1; i <= maxn; i++) {
		if (!w[i].size()) continue;
		for (auto v : w[i]) vis[v] = 1;
		for (auto v : w[i]) {
			if (vis[par[v]]) {
				int fx = find(par[v]), fy = find(v);
				if (fx != fy) fa[fy] = fx, sum[fx] += sum[fy], sum[fy] = 0;
			}
		}
		for (auto v : w[i]) {
			int fx = find(v);
			if (v == fx) ans[i] += 1ll * sum[fx] * (sum[fx] - 1) / 2 + sum[fx];
		}
		for (auto v : w[i]) vis[v] = 0, fa[v] = v, sum[v] = 1;
	}
	for (int i = maxn; i >= 1; i--) {
		for (int j = 2 * i; j <= maxn; j += i) ans[i] -= ans[j];
	}
	for (int i = 1; i <= maxn; i++) {
		if (ans[i]) printf("%d %lld\n", i, ans[i]);
	}
	return 0;
}
```

---

## 作者：cirnovsky (赞：0)

构造函数 $ans(x)$，$f(x)$ 分别表示 $\gcd$ 为 $x$ 的链数和链 $\gcd$ 有 $x$ 因子的链数，于是 $f(x)=\sum\limits_{d\mid x}ans(d)$，由莫比乌斯反演得 $ans(x)=\sum\limits_{x|d}f(d)\mu(\frac{d}{x})$。

把每一个点权为 $x$ 的倍数的点拉出来，跑出各连通块大小可以平凡算出 $f(x)$。

但是 $ans(x)$ 的计算一定需要莫反么？

[代码给出的是容斥做法，via cqbzly。](https://paste.ubuntu.com/p/M4jTRPnC5q/)

---

