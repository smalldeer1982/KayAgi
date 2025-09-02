# Digit Tree

## 题目描述

ZS the Coder has a large tree. It can be represented as an undirected connected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ n-1 $ edges between them. There is a single nonzero digit written on each edge.

One day, ZS the Coder was bored and decided to investigate some properties of the tree. He chose a positive integer $ M $ , which is coprime to $ 10 $ , i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/9b5bdec4cb6231baa1f3fcb57eb25703ae0eed8f.png).

ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting when if he would follow the shortest path from vertex $ u $ to vertex $ v $ and write down all the digits he encounters on his path in the same order, he will get a decimal representaion of an integer divisible by $ M $ .

Formally, ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting if the following states true:

- Let $ a_{1}=u,a_{2},...,a_{k}=v $ be the sequence of vertices on the shortest path from $ u $ to $ v $ in the order of encountering them;
- Let $ d_{i} $ ( $ 1<=i&lt;k $ ) be the digit written on the edge between vertices $ a_{i} $ and $ a_{i+1} $ ;
- The integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/72be647436ef167ccaba4334e08ad71c22afc6b4.png) is divisible by $ M $ .

Help ZS the Coder find the number of interesting pairs!

## 说明/提示

In the first sample case, the interesting pairs are $ (0,4),(1,2),(1,5),(3,2),(2,5),(5,2),(3,5) $ . The numbers that are formed by these pairs are $ 14,21,217,91,7,7,917 $ respectively, which are all multiples of $ 7 $ . Note that $ (2,5) $ and $ (5,2) $ are considered different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/08c05395fdf8f9a998abf43b020555e6b5471bd5.png)In the second sample case, the interesting pairs are $ (4,0),(0,4),(3,2),(2,3),(0,1),(1,0),(4,1),(1,4) $ , and $ 6 $ of these pairs give the number $ 33 $ while $ 2 $ of them give the number $ 3333 $ , which are all multiples of $ 11 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/8a71025758e81b9cf19889885872aec3ca3f5ffc.png)

## 样例 #1

### 输入

```
6 7
0 1 2
4 2 4
2 0 1
3 0 9
2 5 7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5 11
1 2 3
2 0 3
3 0 3
4 3 3
```

### 输出

```
8
```

# 题解

## 作者：orangejuice (赞：26)

# $Dsu$做法详解
### 首先 , $Dsu$原理应该不必多说 , 即取重儿子 , 将轻儿子合并
### 统计答案时 , 我们将以 当前所在点$u$ 为$LCA$的点答案进行统计
### 但是,这题用 $Dsu$ 做的难点在于储存 , 所以我们重点讲储存
------

#### 我们先暂且不考虑取模
#### 首先 , 容器是全局的 , 存的值也必然是全局的
#### 然而 , 我们所知的全局的值只有两种路径,即$u$到$1$的路径$disup$ , 以及$1$到$u$的路径$disdown$ , 在维护这两个值时,我们同时维护一个$dep$数组(这里的$dep$是从$0$开始计数的)
#### 我们得到递推式
$$ disup[v]=disup[u]+10^{dep[u]}*w$$ 
$$ disdown[v]=10 \cdot disdown[u]+w $$
#### 即将边权为w的边分别接在前后
#### ps : 因为要多次用到$10^x$,所以我们先预处理一个数组$po[x]=10^x$
#### 所以预处理代码如下     
```cpp
void pre_dfs(int u,int f) {
    for(int i=head[u]; ~i; i=e[i].nxt)if(e[i].to!=f) {
            int v=e[i].to,w=e[i].w;
            disup[v]=disup[u]+po[dep[u]]*w;
            disdown[v]=10*disdown[u]+w;
            dep[v]=dep[u]+1;
            pre_dfs(v,u);
        }
}
```
#### 维护答案时 , 对于一个点,我们先要将其到$LCA$的路径表示出来
#### 设这两段路径为$up,down$即
$$ up= \frac {disup[u]-disup[lca]}{10^{dep[lca]}} $$
$$ down=disdown[u]-disdown[lca]\cdot 10^{dep[u]-dep[lca]} $$
#### 在维护答案时,我们显然是要为一段$up$的路径找到一段$down$的路径与其匹配
#### 设我们所求的一段路径起始点为$begin$,结束点为$end$,则满足条件的路径满足等式
$$ up \ \cdot \ 10^{dep[end]-dep[lca]} \ + \ down \equiv \ 0 \pmod{m}$$
#### 我们将$up$和$down$的表达式带入
$$  \frac {(disup[begin]-disup[lca]) \cdot 10^{dep[end]} }{10^{2 \cdot dep[lca]}} + \frac {disdown[end]-disdown[lca]\cdot 10^{dep[end]}} {10^{dep[lca]}} $$
##### ~~(有那么一点长)~~

-----------
#### 现在我们考虑存储
#### 对于存入$up$ , 存入时 , 其实我们只知道 $disup[begin]$ 这一个值 , 所以我们存下这个值 , 将上式变形  
$$ disup[begin] = disdown[lca] \cdot 10^{dep[lca]} - \frac{disdown[end] \cdot 10^{2 \cdot dep[lca]} }{10^{dep[end]}}+disup[lca]$$
#### 所以访问答案时 , 我们用上式访问即可

#### 对于存入$down$,存入时,我们所知的量有$disdown[end],dep[end]$ , 我们再次变换上式 , 将这两个量提出
$$ \frac{disdown[end]}{10^{dep[end]}} = \frac {disdown[lca]}{10^{dep[lca]}} - \frac {disup[begin]-disup[lca]}{10^{2 \cdot dep[lca]}} $$
#### 这两个值都用$map$访问即可
#### 现在我们考虑到取模 , 上式中每次运算都加以取模 
#### 但是显然模运算之后是不能直接除的 , 所以我们用模逆元
#### 嗯 , 模逆元我用的是扩欧
#### (惊奇得发现分母都是$10^{x}$类型的)
#### (这就是为什么题目给出$gcd(m,10)=1$)
#### 以上是储存的过程
-----
### 还有一个点 , 即如何将轻儿子的值合并
### 我们要避免儿子自己的信息和自己合并 , 所以要对于每个轻儿子 , 先算一次答案 , 再添加信息
### 再访问完儿子后 , 再将自己信息加入即可

----

整体代码
---------
```cpp
#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int N=2e5+100;
typedef long long ll;
int n,m;
void Exgcd(ll a,ll b,ll &x,ll &y) {
    if(!b)x=1,y=0;
    else Exgcd(b,a%b,y,x),y-=a/b*x;
}
ll Inv(ll a) {
    ll x,y;
    Exgcd(a,m,x,y);
    x=(x%m+m)%m;
    return x;
}
int po[N]= {1};
struct Edge {
    int to,nxt,w;
} e[N<<1];
int head[N],ecnt;
inline void AddEdge(int u,int v,int w) {
    e[++ecnt].nxt=head[u];
    e[ecnt].to=v;
    e[ecnt].w=w;
    head[u]=ecnt;
}
int cnt[N],son[N],dep[N];
ll disup[N],disdown[N];
void pre_dfs(int u,int f) {
    cnt[u]=1;
    for(int i=head[u]; ~i; i=e[i].nxt)if(e[i].to!=f) {
            int v=e[i].to,w=e[i].w;
            disup[v]=(disup[u]+1ll*po[dep[u]]%m*w)%m;
            disdown[v]=(10ll*disdown[u]%m+w)%m;
            dep[v]=dep[u]+1;
            pre_dfs(v,u);
            cnt[u]+=cnt[v];
            if(cnt[son[u]]<cnt[v])son[u]=v;
        }
}

map<int,int> U,D;
ll ans;
void Calc(int u,int LCA) {
    ll Ub=disup[u],pl=po[dep[LCA]],pe=po[dep[u]],Dl=disdown[LCA],De=disdown[u],Ul=disup[LCA];
    ll x = ((1ll*Dl* pl %m -1ll* De *pl %m* pl %m *Inv(pe) %m+1ll*Ul)%m+m)%m;
    x=(x+m)%m;
    ll y =(1ll* Dl * Inv(pl) %m+1ll*(Ul-Ub)*Inv(pl)%m*Inv(pl)%m)%m;
    y=(y+m)%m;
    ans+=U[x];
    ans+=D[y];
}
void Add(int u) {
    ll x=disup[u],y=1ll*disdown[u]*Inv(po[dep[u]])%m;
    U[x]++,D[y]++;
}
void Upd(int u,int f,int LCA,int k) {
//	cout<<"Now in"<<' '<<u<<' '<<up<<' '<<down<<endl;
//	cout<<"U"<<u<<endl;
    if(k)Calc(u,LCA);
    else Add(u);
//	cout<<"Upd"<<' '<<x<<' '<<y<<' '<<k<<endl;
    for(int i=head[u]; ~i; i=e[i].nxt) {
        int v=e[i].to;
        if(v==f)continue;
        Upd(v,u,LCA,k);
    }
//	Add(u);
//	s+=k*2;
}

void dfs_getans(int u,int f,int h) {
    for(int i=head[u]; ~i; i=e[i].nxt)
        if(e[i].to!=f&&e[i].to!=son[u])
            dfs_getans(e[i].to,u,0);
    if(son[u])dfs_getans(son[u],u,1);
//	int lst=ans;
    for(int i=head[u]; ~i; i=e[i].nxt) if(e[i].to!=f&&e[i].to!=son[u]) {
            Upd(e[i].to,u,u,1);
            Upd(e[i].to,u,u,0);
        }
    Calc(u,u);
    Add(u);
    if(!h)U.clear(),D.clear();
}


int main() {
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof head);
    for(int i=1; i<=n+3; i++)po[i]=1LL*po[i-1]*10%m;
    for(int i=2,u,v,w; i<=n; i++) {
        scanf("%d%d%d",&u,&v,&w);
        u++,v++;
        AddEdge(u,v,w);
        AddEdge(v,u,w);
    }
//	dep[1]=1;
    pre_dfs(1,0);
    dfs_getans(1,0,1);
    printf("%lld\n",ans);
    return 0;
}
```






---

## 作者：MikukuOvO (赞：10)

考虑什么样的路径能满足条件，我们考虑点分治，如果存在两条路径，一条自下而上连城的数字为$d_1$，另一条自上而下连成的数字为$d_2$,并且满足$d_1\times 10^{dep_2}+d_2=0(mod~m)$，考虑将这个式子变形，发现也就是求有多少对$d_1$和$-d_2\times 10^{-dep}$相等，我们将$d_1$插入$map$中，然后枚举$-d_2\times 10^{-dep}$统计即可。

[$code$](https://pastebin.com/NsMd3JuG)

---

## 作者：xfrvq (赞：9)

[$\tt Link$](/problem/CF715C)。

沝黑。

首先这种统计路径的问题一般联想点分治，然后考虑如何处理经过一个点 $u$ 的路径。

考虑有一个点 $p\in u$ 的子树，然后记录路径 $p\to u$ 和路径 $u\to p$ 的答案。前者放入一个映射统计，后者存在数组 $S$ 里面。

最后整体统计，枚举 $x\in S$，设 $x\lt M$，统计映射的 $M-x$ 位置的结果，求一个和。

但是这样可能会有一条路径，从 $u$ 的一个儿子 $v$ 的子树来，又到 $v$ 的子树去。

于是我们考虑分开对每个儿子做一次上述统计子树的算法，然后让 $u$ 子树的总和减去每个 $v$ 子树的总和即可。

中间会有把一个多位数和一个数字拼起来的情况，考虑记录下原数的位数，预处理 $10$ 的次幂以及逆元。

对了，$M$ 不一定是质数，所以不能用 $x^{mod-2}$ 的方法求逆元，而是要用 $\tt exgcd$。

对了，`unordered_map` 会被卡，`map` 已经很够了。

[$\tt code$](https://codeforces.com/contest/715/submission/168379648)。

---

## 作者：whiteqwq (赞：6)

[CF715C Digit Tree](https://www.luogu.com.cn/problem/CF715C)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1787188)

## 题意

给定一颗$n$个点的带边权$w_i$的树，给定$m$，求树上有多少条路径从左往右连成的数为$m$的倍数。（$(x,y)$与$(y,x)$为不同的点对）

$1\leqslant n\leqslant 10^5,1\leqslant m,w_i\leqslant 10^9,\gcd(10,m)=1$。

## 分析

这道题告诉我们，只要肯推式子，很多静态的树上路径计数问题树上启发式合并（dsu on tree）是可以胜任的（如果不会树上启发式合并可以练习一下[CF246E Blood Cousins Return](https://www.luogu.com.cn/problem/CF246E)）。

首先不难发现树上的路径形成的数是高精度也存不下的，因此我们考虑把是$m$的倍数转化为对$m$取模，那么我们就只需要在$m$的同余系下运算了。

很容易预处理出来$dis1_x$表示$1$到$x$路径的值，$dis2_x$表示$x$到$1$路径的值，$dep_x$表示$x$的深度（根节点深度为$1$）。

那么我们也可以很方便的计算出来$x$到$y$路径上的值（设$z=\text{lca}(x,y)$）：

$$val(x,y)=\frac{dis2_x-dis2_z}{10^{dep_z}}\times 10^{dep_y-dep_z}+dis1_y-dis1_z\times 10^{dep_y-dep_z}$$

题目要求的就是$val(x,y)$的$(x,y)$对数，看到静态树上路径计数，我们可以考虑用树上启发式合并进行计算：

> 树上启发式合并具体步骤：对于节点$x$，先计算所有轻儿子的贡献（统计贡献用全局的桶），每统计完一个轻儿子暴力消除贡献，之后统计重儿子的贡献（不清空桶），最后再把轻儿子的贡献加上并计算路径的$\text{lca}$为$x$的贡献。
如果删除和添加节点贡献复杂度为$O(1)$，那么树上启发式合并的复杂度为$O(n\log n)$。

不难发现添加节点的时候仅知道路径的一端，所以我们可以对上面的$val(x,y)\equiv 0\pmod m$的式子进行变形（上面的式子代表$x$是左端点，下面的式子代表$x$是右端点）：

$$dis2_x\equiv dis2_z-\frac{dis1_y\times 10^{2dep_z}}{10^{dep_y}}+dis1_z\times 10^{dep_z}\pmod m$$

$$\frac{dis1_y}{10^{dep_y}}\equiv \frac{dis1_z}{ 10^{dep_z}}-\frac{dis2_x-dis2_z}{10^{2dep_z}}\pmod m$$

那么我们就直接用$\text{map}$存一下左边的值，然后讨论一下就好了（注意这里$\text{map}$不能存右边的值的原因是$dep_z$在重儿子遍历完的时候改变）。

## 代码

两个要注意的地方：节点编号从$0$开始；$m$不是质数，需要用扩展欧几里得求逆元。

dsu要注意实现的细节

```
#include<stdio.h>
#include<map>
using namespace std;
const int maxn=100005,maxm=maxn<<1;
int n,m,e,dfns,inv10;
long long ans;
int start[maxn],to[maxm],then[maxm],worth[maxm],size[maxn],iptson[maxn],L[maxn],R[maxn],id[maxn],pow10[maxn<<1],powinv[maxn<<1],dep[maxn],dis1[maxn],dis2[maxn];//dis1[x]:1->x dis2[x]:x->1
map<int,int>mapx,mapy;
inline void add(int x,int y,int z){
	then[++e]=start[x],start[x]=e,to[e]=y,worth[e]=z;
}
int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	int res=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return res;
}
int getinv(int a,int mod){
	int x,y;
	exgcd(a,mod,x,y);
	return (x%mod+mod)%mod;
}
void dfs1(int x,int last){
	L[x]=++dfns,id[dfns]=x,size[x]=1,iptson[x]=-1,dep[x]=dep[last]+1;
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(y==last)
			continue;
		dis1[y]=(10ll*dis1[x]%m+worth[i])%m,dis2[y]=(dis2[x]+1ll*pow10[dep[x]]*worth[i]%m)%m;
		dfs1(y,x),size[x]+=size[y];
		if(iptson[x]==-1||size[iptson[x]]<size[y])
			iptson[x]=y;
	}
	R[x]=dfns;
}
inline void calc(int x,int z){
	ans+=mapx[(dis2[z]-1ll*dis1[x]*pow10[dep[z]*2]%m*powinv[dep[x]]%m+1ll*dis1[z]*pow10[dep[z]]%m+m)%m];
	ans+=mapy[(1ll*dis1[z]*powinv[dep[z]]%m-1ll*(dis2[x]-dis2[z]+m)%m*powinv[dep[z]*2]%m+m)%m];
}
void dfs2(int x,int last){
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(y==last||y==iptson[x])
			continue;
		dfs2(y,x),mapx.clear(),mapy.clear();
	}
	if(iptson[x]!=-1)
		dfs2(iptson[x],x);
	calc(x,x);
	mapx[dis2[x]]++,mapy[1ll*dis1[x]*powinv[dep[x]]%m]++;
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(y==last||y==iptson[x])
			continue;
		for(int j=L[y];j<=R[y];j++)
			calc(id[j],x);
		for(int j=L[y];j<=R[y];j++)
			mapx[dis2[id[j]]]++,mapy[1ll*dis1[id[j]]*powinv[dep[id[j]]]%m]++;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	if(m==1){
		printf("%lld\n",1ll*n*(n-1));
		return 0;
	}
	inv10=getinv(10,m),pow10[0]=powinv[0]=1;
	for(int i=1;i<=n*2;i++)
		pow10[i]=pow10[i-1]*10ll%m,powinv[i]=1ll*powinv[i-1]*inv10%m;
	for(int i=1;i<n;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		x++,y++,add(x,y,z),add(y,x,z);
	}
	dfs1(1,0),dfs2(1,0);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Register_int (赞：5)

首先将路径分成两类，一类是不经过根 $u$ 的，一类是经过 $u$ 的。  
对于第二种情况，预处理出 $u$ 子树中所有点 $v$ 的两条路径 $v\rightarrow u$（一类）和 $u\rightarrow v$（二类），记录时保存点 $v$ 深度 $dep_v$。那么设两条路径的值分别为 $x,y$，则可以正确匹配的条件是：
$$x\times10^{dep_v}+y\mid m$$
因为 $m\ \bot\ 10$，所以将原式除以 $10^{dep_v}$，得到：
$$x+y\times10^{-dep_v}\mid m$$
所以
$$x\equiv -y\times10^{-dep_v}\pmod m$$
我们把所有的一类路径塞进桶里，用二类路径去匹配，就可以得到答案了。不过这里统计的路径有可能在同一棵 $u$ 的其中一个儿子的子树内，所以还需要分别统计 $u$ 的所有儿子的答案并减去。最后，逆元要用拓欧求。  
到这里题就做完了，用 dsu on tree 和淀粉质都可以。这里我用的是淀粉质。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;

int mod;

void exgcd(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, void();
	exgcd(b, a % b, y, x), y -= a / b * x;
}

inline 
ll inv(ll k) {
	ll x, y;
	return exgcd(k, mod, x, y), (x % mod + mod) % mod; 
}

struct node {
	int v, w, nxt;
} e[MAXN << 1];

int head[MAXN], tot;

inline 
void add(int u, int v, int w) {
	e[++tot] = { v, w, head[u] }, head[u] = tot;
}

int size[MAXN], son[MAXN], rt;

bool vis[MAXN];

void getrt(int u, int f, int sum) {
	size[u] = 1, son[u] = 0;
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v;
		if (v == f || vis[v]) continue;
		getrt(v, u, sum), size[u] += size[v];
		son[u] = max(son[u], size[v]);
	}
	son[u] = max(son[u], sum - size[u]);
	if (son[rt] > son[u]) rt = u;
}

ll pw[MAXN], dis[MAXN], dep[MAXN]; int cnt;
map<ll, ll> mp;

void getdis(int u, int f, ll x, ll y, int d) {
	if (d) mp[x]++, dis[++cnt] = y, dep[cnt] = d;
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v;
		if (v == f || vis[v]) continue;
		getdis(v, u, (x + pw[d] * e[i].w % mod) % mod, (y * 10 + e[i].w) % mod, d + 1);
	}
}

inline 
ll calc(int u, int d) {
	ll res = 0, t; mp.clear(), cnt = 0;
	getdis(u, 0, d % mod, d % mod, d ? 1 : 0);
	for (int i = 1; i <= cnt; i++) {
		t = (mod - dis[i]) * inv(pw[dep[i]]) % mod;
		res += mp[t] + (!d && !dis[i]);
	}
	return d ? res : res + mp[0];
}

ll ans;

void solve(int u) {
	vis[u] = 1, ans += calc(u, 0);
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v;
		if (vis[v]) continue;
		ans -= calc(v, e[i].w), rt = 0;
		getrt(v, u, size[v]), solve(rt);
	}
}

int n;

int main() {
	scanf("%d%d", &n, &mod), *son = n, *pw = 1;
	for (int i = 1, u, v, w; i < n; i++) {
		scanf("%d%d%d", &u, &v, &w), u++, v++;
		add(u, v, w), add(v, u, w);
	}
	for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * 10 % mod;
	getrt(1, 0, n), solve(rt);
	printf("%lld", ans);
}
```

---

## 作者：SoyTony (赞：4)


设 $S(u,v)$ 表示 $(u,v)$ 路径上数字顺次拼接而成的数，$D(u,v)$ 表示 $(u,v)$ 路径上数字个数，那么在 $\mathrm{LCA}$ 位置统计答案，即要求：

$$S(u,\mathrm{LCA})\times 10^{D(\mathrm{LCA},v)}+S(\mathrm{LCA},v)\equiv 0\pmod m$$

由于保证存在 $10$ 的逆元，移项可以得到：

$$S(u,\mathrm{LCA})\equiv -\dfrac{S(\mathrm{LCA},v)}{10^{D(\mathrm{LCA},v)}}\pmod m$$

这样“拼数字”的意义就转成了模意义下的加减乘除。

简单做法是点分治分别维护。

DSU on Tree 做法比较复杂。

考虑用 `map` 分别维护 $S(u,\mathrm{LCA})$ 以及 $\frac{S(\mathrm{LCA},u)}{10^{D(\mathrm{LCA},u)}}$，第一次 DFS 可以预处理到根路径上数字正序倒序得到的数字，可以快速得到一段祖先关系的路径上数字拼出的结果。

重点是考虑继承重儿子，即加入一条边 $(u,v,w)$ 影响，不妨维护 $tagcnt,tagsum$ 表示当前实际值 $S'$ 与 `map` 中存储值 $S''$ 的关系为 $S'=S''\times 10^{tagcnt}+tagsum$。

对于维护 $S(u,\mathrm{LCA})$ 的 `map`，增加一条边使得 $S=S'\times 10+w$，于是得到 $S=S''\times 10^{tagcnt+1}+(tagsum\times 10+w)$，可以得到两个标记的变化。

对于维护 $\frac{S(\mathrm{LCA},u)}{10^{D(\mathrm{LCA},u)}}$ 的 `map`，发现维护的值实际上是把拼出来的数作为小数部分，那么增加一个 $w$ 就是在个位增加再向前移动小数点，于是 $S=\frac{1}{10}\times (S'+w)$，得到 $S=S'\times 10^{tagcnt-1}+\frac{1}{10}\times (tagsum+w)$。

得到两个标记的变化后可以轻松计算答案。

---

## 作者：封禁用户 (赞：3)

首先$\gcd\left ( M,10 \right ) =1$，意味着 $10$ 可以求关于模 $M$ 意义下的逆元，所以对于每个点，我们可以考虑以它作为 $LCA$ 的合法路径条数。

对于每一个点 $x$，我们记为 $disup\left [ x \right ] ,disdown\left [ x \right ] ,dep\left [ x \right ]$，其中 $disup$ 为该点到根的路径从下到上连成的数对 $M$ 取模后的结果，$disdown$ 表示从根到该点从上到下连成的数对 $M$ 取模后的结果。

考虑函数 $up\left ( a \right )= \left ( u,lca \right ),down\left ( b \right )=\left ( lca,b \right ) $，则可以推出：

$up\left ( a \right ) \times 10^{dep[b]-dep[lca]}+down\left ( b \right ) \equiv 0 \pmod{M}$，设为①式。

$$up\left ( a \right ) = \left ( disup[a] -disup[lca]\right ) \times 10^{-dep[lca]}$$

$$down\left ( b \right )=disdown[b]-disdown[lca] \times 10^{dep[b]-dep[lca]} $$

把函数代入①式可得：

$$disdown[b] \times 10^{-dep[b]}=\left ( disup[lca]-disup[a] \right ) \times 10^{-2dep[lca]}+disdown[lca] \times 10^{-dep[lca]} $$

$$disup[a]=disdown[lca] \times 10^{dep[lca]}-disdown[b] \times 10^{2dep[lca]-dep[b]}+disup[lca]$$

现在我们就很容易发现，等式左边只与 $a$ 和 $b$ 有关，于是我们可以维护两个 $\text{map}$，分别存储 $disdown[x] \times 10^{-dep[x]}$ 与 $disup[x]$，维护它们出现的次数，然后用 $\text{dsu}$ 把重儿子的子树中已经在 $\text{map}$ 里的信息保留，计算时就可以只枚举轻儿子及其子树就行了，复杂度 $O\left ( n\log^{2}n \right ) $。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){//快读 
    ll x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){
    	if(c=='-')f=-1;
    	c=getchar();
	}
	while(isdigit(c)){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
const int N=1e5+100;
struct Node{//邻接表 
	int v,w,nxt;
	Node(){}
	Node(int _v,int _w,int _nxt){
		v=_v,w=_w,nxt=_nxt;
	}
}e[N<<1];
int head[N],ne;
int expr[N*2+10];
inline void add_edge(int u,int v,int w){//双向建边 
    e[ne]=Node(v,w,head[u]);
	head[u]=ne++;
    e[ne]=Node(u,w,head[v]);
	head[v]=ne++;
}
map<int,int> mp1,mp2; //map记录当前状态 
int sz[N],son[N],n,p;
int disup[N],disdown[N],dep[N];
ll ans=0;
ll qpow(int x,int k){//快速幂取余 
    ll ans=1;
    while(k){
        if(k&1)ans=1LL*ans*x%p;
        x=1LL*x*x%p;
        k>>=1;
    }
    return ans%p;
}
void init(){//逆元 
    int x=p,phi=x;
    for(int i=2;i*i<=x;i++){
        if(x%i==0)phi-=phi/i;
        while(x%i==0)x/=i;
    }
    if(x!=1)phi-=phi/x;
    ll inv=qpow(10,phi-1);
    expr[N]=1;
    for(int i=1;i<=n;i++){
    	expr[i+N]=1LL*expr[i-1+N]*10%p;
	}
    for(int i=-1;i>=-n;i--){
    	expr[i+N]=1LL*expr[i+1+N]*inv%p;
	}
}
int exp(int x){
	return expr[x+N];
}
void dfs(int u,int f){
    sz[u]=1;
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v,w=e[i].w;
        if(v==f)continue;
        disdown[v]=(10LL*disdown[u]%p+w)%p;
        disup[v]=(disup[u]+1LL*w*exp(dep[u])%p)%p;
        dep[v]=dep[u]+1;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]])son[u]=v;
    }
}
void calc(int x,int lca){
	int res;
    res=(disup[lca]+1LL*disdown[lca]*exp(dep[lca])%p-1LL*disdown[x]*exp(2*dep[lca]-dep[x])%p)%p;
    res=(res+p)%p;
	ans+=mp1[res];
    res=(1LL*disdown[lca]*exp(-dep[lca])%p+1LL*(disup[lca]-disup[x])*exp(-dep[lca])%p*exp(-dep[lca])%p)%p;
    res=(res+p)%p;
	ans+=mp2[res];
}
void add(int x){
    mp1[disup[x]]++;
    mp2[1LL*disdown[x]*exp(-dep[x])%p]++;
}
void work(int u,int f,int lca,int type){
    if(type)calc(u,lca);
    else add(u);
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v;
        if(v==f)continue;
        work(v,u,lca,type);
    }
}
void solve(int u,int f){
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v;
        if(v==f||v==son[u])continue;
        solve(v,u);
		mp1.clear();
		mp2.clear();
    }
    if(son[u])solve(son[u],u);
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v;
        if(v==f||v==son[u])continue;
        work(v,u,u,1);
        work(v,u,u,0);
    }
    calc(u,u);
    add(u);
}
int main(){
    n=read(),p=read();
    init();
    if(p==1){
		cout<<1LL*n*(n-1)<<endl;
		return 0;
	}
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n-1;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        u++,v++;
        add_edge(u,v,w);
    }
    dfs(1,0);
    solve(1,0);
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：tzc_wk (赞：3)

一道 *2700 的 D1C，也被我自己想出来了（

我们定义 $a_u$ 为根节点到 $u$ 路径上所遇到的数连在一起形成的数 $\bmod m$，再定义 $b_u$ 为 $u$ 到根节点路径上所遇到的数连在一起形成的数 $\bmod m$，$a_u,b_u$ 显然可以一遍 DFS 求出。

考虑两点 $u,v$，假设它们的 LCA 为 $w$，那么 $u\to v$ 路径上形成的数连在一起就是 $\dfrac{a_u-a_w}{10^{d_w}}·10^{d_v-d_w}+b_v-b_w·10^{d_v-d_w}$，其中 $d_u$ 为 $u$ 的深度，稍微化简一下即可得到 $10^{d_v}·(\dfrac{a_u-a_w}{10^{2d_w}}+\dfrac{b_v}{10^{d_v}}-\dfrac{b_w}{10^{d_w}})$，而由于 $10^{d_v}\perp m$，故 $10^{d_v}·(\dfrac{a_u-a_w}{10^{2d_w}}+\dfrac{b_v}{10^{d_v}}-\dfrac{b_w}{10^{d_w}})\equiv 0\pmod{m}\leftrightarrow \dfrac{a_u-a_w}{10^{2d_w}}+\dfrac{b_v}{10^{d_v}}-\dfrac{b_w}{10^{d_w}}\pmod{m}$ 即 $\dfrac{a_u}{10^{2d_w}}+\dfrac{b_v}{10^{d_v}}\equiv \dfrac{a_w}{10^{2d_w}}+\dfrac{b_w}{10^{d_w}}$，考虑枚举 $w$ 并按照上一题的套路进行 dsu on tree，然后开两个桶 $c1,c2$，$c1_i$ 实时维护 $a_u=i$ 的 $u$ 的个数，$c2_i$ 实时维护 $\dfrac{b_v}{10^{d_v}}=i$ 的 $v$ 的个数，这个贡献显然可以通过调用桶里的值求出。至于桶怎么开……哈希表可以搞定，不过由于 `map` 能过就没管那么多了，时间复杂度 $n\log^2n$，如果用哈希表可以少一个 $\log$。

坑点：虽然 $m\perp 10$，但由于 $m$ 不是质数，逆元需通过 `exgcd` 求出，而不能使用费马小定理（看来我数论白学了/ll/dk）

```cpp
const int MAXN=1e5;
int n,mod,hd[MAXN+5],to[MAXN*2+5],num[MAXN*2+5],nxt[MAXN*2+5],ec=0;
void exgcd(int a,int b,int &x,int &y){
	if(!b){x=1;y=0;return;}
	exgcd(b,a%b,x,y);int tmp=x;x=y;y=tmp-a/b*y;
}
int inv(int x){
	int a,b;exgcd(x,mod,a,b);
	return (a+mod)%mod;
}
void adde(int u,int v,int w){to[++ec]=v;num[ec]=w;nxt[ec]=hd[u];hd[u]=ec;}
int pw[MAXN*2+5],ipw[MAXN*2+5];
int a[MAXN+5],b[MAXN+5],dep[MAXN+5];
int siz[MAXN+5],wson[MAXN+5];
void dfs(int x=1,int f=0){
	siz[x]=1;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e],z=num[e];if(y==f) continue;
		a[y]=(a[x]+1ll*pw[dep[x]]*z%mod)%mod;
		b[y]=(10ll*b[x]+z)%mod;dep[y]=dep[x]+1;dfs(y,x);
		if(siz[y]>siz[wson[x]]) wson[x]=y;siz[x]+=siz[y];
	}
}
map<int,int> mp_a,mp_b;
ll ans=0;int seq[MAXN+5],seq_num=0;
void add(int x,int f){
	seq[++seq_num]=x;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;
		add(y,x);
	}
}
void calc(int x=1,int f=0){
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||y==wson[x]) continue;
		calc(y,x);mp_a.clear();mp_b.clear();
	} int val=(1ll*a[x]*ipw[dep[x]<<1]+b[x])%mod;
	if(wson[x]) calc(wson[x],x);
	ans+=mp_a[a[x]];ans+=mp_b[b[x]];
	mp_a[a[x]]++;mp_b[b[x]]++;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||y==wson[x]) continue;
		seq_num=0;add(y,x);
		for(int i=1,u;i<=seq_num;i++){
			u=seq[i];
			ans+=mp_a[1ll*(val-b[u]+mod)*pw[dep[x]<<1]%mod];
			ans+=mp_b[(val-1ll*a[u]*ipw[dep[x]<<1]%mod+mod)%mod];
		}
		for(int i=1;i<=seq_num;i++) mp_a[a[seq[i]]]++,mp_b[b[seq[i]]]++;
	}
}
int main(){
	scanf("%d%d",&n,&mod);
	if(mod==1) return printf("%lld\n",1ll*n*(n-1)),0;
	for(int i=1,u,v,w;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		++u;++v;adde(u,v,w);adde(v,u,w);
	} pw[0]=1;
	for(int i=1;i<=(n<<1);i++) pw[i]=10ll*pw[i-1]%mod;
	ipw[n<<1]=inv(pw[n<<1]);
	for(int i=(n<<1)-1;~i;i--) ipw[i]=10ll*ipw[i+1]%mod;
	dfs();for(int i=1;i<=n;i++) b[i]=1ll*b[i]*ipw[dep[i]]%mod;
//	for(int i=1;i<=n;i++) printf("%d %d\n",a[i],b[i]);
	calc();printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：xgzc (赞：3)

### [题面](http://codeforces.com/problemset/problem/715/C)

### 题解

树上求点对数目的题大多都是点分治解决

路径统计中有一个问题，如果现在求出从上到下的链长$a$，从下到上的链长$b$和深度$c$，

则：

$$a \times10^c + b\equiv0(mod\;m)$$

两边同除以$c$，得

$$a + b\times10^{-c}\equiv0(mod\;m)\;\;(\because gcd(10,\;m) = 1)$$

于是可以很好维护了。

### 代码

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<map>
#define RG register
#define file(x) freopen(#x".in", "r", stdin);freopen(#x".out", "w", stdout);
#define clear(x, y) memset(x, y, sizeof(x))

inline int read()
{
	int data = 0, w = 1; char ch = getchar();
	while(ch != '-' && (!isdigit(ch))) ch = getchar();
	if(ch == '-') w = -1, ch = getchar();
	while(isdigit(ch)) data = data * 10 + (ch ^ 48), ch = getchar();
	return data * w;
}

const int maxn(1e5 + 10);
struct edge { int next, to, dis; } e[maxn << 1];
int head[maxn], e_num, n, m, size[maxn], root;
int Size, min, vis[maxn], Pow[maxn], cnt;

inline void Init()
{
	clear(head, 0); e_num = 0, Pow[0] = 1;
	for(RG int i = 1; i <= n; i++) Pow[i] = 10ll * Pow[i - 1] % m;
}

#undef clear

inline void add_edge(int from, int to, int dis)
{
	e[++e_num] = (edge) {head[from], to, dis};
	head[from] = e_num;
}

std::pair<int, int> digit[maxn << 1];
std::map<int, long long> tong;
void getRoot(int x, int fa)
{
	size[x] = 1;
	int tot = 0;
	for(RG int i = head[x]; i; i = e[i].next)
	{
		int to = e[i].to;
		if(to == fa || vis[to]) continue;
		getRoot(to, x); tot = std::max(tot, size[to]);
		size[x] += size[to];
	}
	tot = std::max(tot, Size - size[x]);
	if(tot < min) min = tot, root = x;
}

void getDep(int x, int fa, long long d1, long long d2, int dep)
{
	if(dep >= 0) ++tong[d1], digit[++cnt] = std::make_pair(d2, dep);
	for(RG int i = head[x]; i; i = e[i].next)
	{
		int to = e[i].to, dis = e[i].dis; if(to == fa || vis[to]) continue;
		getDep(to, x, (d1 + 1ll * Pow[dep + 1] * dis) % m,
				(d2 * 10 + dis) % m, dep + 1);
	}
}

void exgcd(long long a, long long b, long long &gcd, long long &x, long long &y)
{
	!b ? gcd = a, x = 1, y = 0 : (exgcd(b, a % b, gcd, y, x), y -= x * (a / b));
}

inline long long Inv(int a, int Mod)
{
	long long d, x, y; exgcd(a, Mod, d, x, y);
	return d == 1 ? (x % Mod + Mod) % Mod : -1;
}

long long calc(int x, int d)
{
	long long ans = 0; tong.clear(), cnt = 0;
	if(d) getDep(x, 0, d % m, d % m, 0);
	else getDep(x, 0, 0, 0, -1);
	for(RG int i = 1; i <= cnt; i++)
	{
		long long tmp = (-digit[i].first * 1ll *
		Inv(Pow[digit[i].second + 1], m) % m + m) % m;
		if(tong.find(tmp) != tong.end()) ans += tong[tmp];
		if(!d) ans += (digit[i].first == 0);
	}
	if(d == 0) ans += tong[0];
	return ans;
}

long long ans;
void dfs(int x)
{
	ans += calc(x, 0);
	vis[x] = true;
	for(RG int i = head[x]; i; i = e[i].next)
	{
		int to = e[i].to;
		if(vis[to]) continue;
		ans -= calc(to, e[i].dis);
		min = n, Size = size[to];
		getRoot(to, x); dfs(root);
	}
}

int main()
{
	while(~scanf("%d%d", &n, &m))
	{
		Init(); Size = min = n;
		for(RG int i = 1, a, b, c; i < n; i++)
			a = read() + 1, b = read() + 1, c = read(),
			  add_edge(a, b, c), add_edge(b, a, c);
		ans = 0; memset(vis, 0, sizeof(vis));
		getRoot(1, 0); dfs(root);
		printf("%I64d\n", ans);
	}
	return 0;
}
```



---

## 作者：L_M_ (赞：3)

## # 点分治好题啊qwq！！！！


~~北京市第三交委提醒您：做题不long long,亲人两行泪~~

好的咱们回到题目，我们令val(x,y)为路径x->的边权连在一起形成的数字，假设我们现在分治到重心rt,令此时d(x)为x->rt形成的数字，那么对于两个在子树内的节点x,y，可以有：

```
val(x,y) = d(y) * 10 ^ dep[y] +d(x)

```
~~我懒得写取模~~

移项，有：
```
d(y) * 10 ^ dep[y] = -d(x)

```
那么我们只要考虑对于每个右侧的二元组，有多少个左式和它相等

可以将左面用pair存（开两个数组也没问题），右面用一个map维护s[i]:d(i)的出现次数，这样就可以做了

一些细节：
	1.形如0000这样的数也是符合条件的，所以得特判s[0]
    
   2.记得开long long！！！！（最好别define int long long）
    
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
#define LM qwq
#define mp make_pair
typedef long long ll;
inline ll read()
{
	ll ans = 0,op = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		(ans *= 10) += ch - '0';
		 ch = getchar();
	}
	return ans * op;
}
const int maxn = 1e5 + 5;
ll mod;
ll p[maxn];
void exgcd(ll a, ll b, ll &x, ll &y) 
{
    if (!b) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll inv(ll a) 
{
    ll x, y;
    exgcd (a,mod,x, y);
    x = (x % mod + mod) % mod;
    return x;
}
ll n;
struct edge
{
	int to,next,cost;
}e[maxn << 1];
int fir[maxn],alloc;
void adde(int u,int v,int w)
{
	e[++alloc].next = fir[u];
	fir[u] = alloc;
	e[alloc].to = v;
	e[alloc].cost = w;
	swap(u,v);
	e[++alloc].next = fir[u];
	fir[u] = alloc;
	e[alloc].to = v;
	e[alloc].cost = w;
}
ll sz[maxn],maxp[maxn],rt;
bool vis[maxn];
ll sum;
ll ans;
map<ll,ll> s;
pair<ll,ll> dig[maxn];
ll num;
void getrt(ll u,ll fa)
{
	sz[u] = 1,maxp[u] = 0;
	for(int i = fir[u];i;i = e[i].next)
	{
		int v = e[i].to;
		if(v == fa || vis[v]) continue;
		getrt(v,u);
		sz[u] += sz[v];
		maxp[u] = max(maxp[u],sz[v]);
	}
	maxp[u] = max(maxp[u],sum - sz[u]);
	if(maxp[u] < maxp[rt]) rt = u;
}
void getd(ll u,ll fa,ll d1,ll d2,ll d)//d1：正;d2:反 
{
	//printf("%d %d %d %d %d\n",u,fa,d1,d2,d);
	if(d >= 0) s[d1]++,dig[++num] = mp(d2,d);
	for(int i = fir[u];i;i = e[i].next)
	{
		int v = e[i].to,w = e[i].cost;
		if(v == fa || vis[v]) continue;
		int d3 = (d1 + w * p[d + 1]) % mod;
		int d4 = (d2 * 10 + w) % mod;
		getd(v,u,d3,d4,d + 1);
	}
}
ll calc(ll u,ll d)
{
	s.clear();
	ll res = 0;
	num = 0;
	if(!d) getd(u,0,0,0,-1);
	else getd(u,0,d % mod,d % mod,0);
	for(int i = 1;i <= num;i++) //枚举二元组
	{
		ll tp = (-dig[i].first * inv(p[dig[i].second + 1]) % mod + mod) %mod;
		if(s.find(tp) != s.end()) res += s[tp];
		if(!d && !dig[i].first) res++;
	}
	if(!d) res += s[0];
	return res;
}
void solve(int u)
{
	vis[u] = 1; ans += calc(u,0); 
	for(int i = fir[u];i;i = e[i].next)
	{
		int v = e[i].to,w = e[i].cost;
		if(vis[v]) continue;
		ans -= calc(v,w);
		sum = sz[v],maxp[rt = 0] = n;
		getrt(v,0);
		solve(rt);
	}
}
int main()
{
	n = read(),mod = read();
	for(int i = 1;i < n;i++)
	{
		ll u = read(),v = read(),w = read();
		adde(u + 1,v + 1,w);
	}
	p[0] = 1;for(int i = 1;i <= n;i++) p[i] = p[i - 1] * 10 % mod;
	maxp[rt] = sum = n;
	getrt(1,0);
	solve(rt);
	printf("%lld",ans);
}
```

---

## 作者：封禁用户 (赞：2)

点分治。

设根为 $p$，将路径分为两类：经过 $p$ 与不经过 $p$。

后者分治求解，考虑如何求解第一类。

设 $s_u$ 表示点 $u$ 到根节点的数字组成的数字，$t_u$ 表示根节点到点 $u$ 的数字组成的数字。$dep_u$ 表示点 $u$ 到根节点有多少条**边**，等价于 $u$ 的深度。

则题目要求的就是有多少个点对 $(x,y)$ 使得 $s_x+t_y\times 10^{dep_x}\equiv  0\pmod M$，其实就是将两个数拼起来，因为边权只有一位所以相对比较好表示。

即 $t_y\equiv -s_x\times 10^{-dep_x}\pmod M$。

这个可以用桶直接计算，即存一个查另一个。但超出值域所以用 map。

重复部分按套路容斥就完了。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 1e9
#define linf 1e18
#define db double
#define ldb long double
#define sd std::
#define il inline
#define MAX(x,y) (x>y?x:y)
#define MIN(x,y) (x<y?x:y)
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define umap(x,y) sd unorded_map<x,y>
#define pque(x) sd priority_queue<x>
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<":"<<x<<"\n"
#define pii sd pair<int,int>
#define X first
#define Y second
#define me(x,y) memset(x,y,sizeof x)
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),x=-x;printt(x);}
il void printk(int x){print(x);kg;}
il void put(int x){print(x);puts("");}
const int N=1e5+10;
int n,mod;
int p10[N];//预处理10次幂 
int exgcd(int a,int b,int &x,int &y)//exgcd求逆元 
{
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    int gcd=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return gcd;
}
il int inv(int a)
{
    int x,y;
    exgcd(a,mod,x,y);
    return (x%mod+mod)%mod;
}
struct node
{
	int nex;
	int to;
	int dis;
}a[N<<1];
int head[N],tot;
void add(int u,int v,int w)
{
	a[++tot].nex=head[u];
	head[u]=tot;
	a[tot].to=v;
	a[tot].dis=w;
}
int siz[N],root,vis[N],weigh[N];
void dfs1(int u,int fa,int sum)
{
	weigh[u]=0;siz[u]=1;
	for(int i=head[u];i;i=a[i].nex)
	{
		int v=a[i].to;
		if(vis[v]||v==fa) continue;
		dfs1(v,u,sum);
		siz[u]+=siz[v];
		weigh[u]=MAX(weigh[u],siz[v]);
	}
	weigh[u]=MAX(weigh[u],sum-siz[u]);
	if(weigh[u]<weigh[root]) root=u;
}
sd map<int,int> mp;
int dis[N],dep[N],cnt,ans;
void dfs2(int u,int fa,int x,int y,int d)//x即根节点到u组成的数字，计算答案时把x存进map中查找y,d为深度 
{
	if(d) mp[x]++,dis[++cnt]=y,dep[cnt]=d;
	for(int i=head[u];i;i=a[i].nex)
	{
		int v=a[i].to;
		if(fa==v||vis[v]) continue;
		dfs2(v,u,(x+p10[d]*a[i].dis%mod)%mod,(y*10+a[i].dis)%mod,d+1);//一个是接后面，一个是接前面 
	}
}
void get_ans(int u,int val,int num,int d)//d为深度,num为此时的dis[u] 
{
	int res=0;
	mp.clear();
	cnt=0;
	dfs2(u,0,num%mod,num%mod,d);
	F(i,1,cnt)
	{
		int t=((-dis[i]*inv(p10[dep[i]]))%mod+mod)%mod;
		res+=mp[t];//查找-s[x]*10^(-dep[x]) 
		if(d==0&&!dis[i]) res++;
	}
	ans+=res*val;
}
void gat_ans(int u)//点分治 
{
	vis[u]=1;
	get_ans(u,1,0,0);
	ans+=mp[0];
	for(int i=head[u];i;i=a[i].nex)
	{
		int v=a[i].to;
		if(vis[v]) continue;
		get_ans(v,-1,a[i].dis,1);
		root=0;
		dfs1(v,u,siz[v]);
		gat_ans(root);
 	}
}
il void solve()
{
	n=read(),mod=read();
	weigh[0]=n;
	p10[0]=1;F(i,1,n) p10[i]=(p10[i-1]*10)%mod;//预处理10次幂 
	F(i,1,n-1)
	{
		int x=read()+1,y=read()+1,z=read(); 
		add(x,y,z);
		add(y,x,z);
	}
	root=0;
	dfs1(1,0,n);
	gat_ans(root);
	put(ans);
}
signed main()
{
	int T=1;
//	T=read();
	while(T--) solve();
	return 0; 
}
```

---

## 作者：huhangqi (赞：1)

首先观察题目，要求我们通过求一段树上最短路径其中边的权值按顺序组成的数字可以被 $M$ 整除的最短路径数。

这其实就是一个匹配的问题，我们比较容易想到的一种简单做法就是使用树上启发式合并，记录下每一个点到目前节点的数字，再跑一个点的时候通过路径权值找到对应的另外一个节点路径值，加上即为答案。

那么看起来这个问题已经很明确了，就是需要找到用哪个值对应当前的值，可以被我们转移过来。

先做一个简单的操作，把所有节点的编号加上一，这样会比较方便处理。

首先设我们当前节点为 $p$ 节点，其父亲为 $fa$，两节点之间边的权值为 $w$，那么我们可以得到从 $p$ 到 $1$ 所形成的数字和从 $1$ 到 $p$ 所形成的数字转移为：

$$$
up_p=up_{fa}+10^{dep_{fa}}\times w\\down_p=10\times down_{fa}+w
$$$
其中 $up_p$ 表示的就是从 $p$ 到 $1$ 所形成的数字，$down_p$ 表示的就是从 $1$ 到 $p$ 所形成的数字，$dep_u$ 表示节点深度，以根节点为 $0$ 记，下同。

那么我们明显就可以先一次 dfs 跑出来这些值了，记得需要取模。

然后就来到了最难的匹配问题了。

我们先看看怎样的点满足条件。

我们假设我们枚举到了 $p$ 点，我们在这个点的两个不同子树中枚举了 $u$ 和 $v$ 两点，那么 $p$ 就是这两个点的最近公共祖先，假设从 $u$ 到 $v$ 组成的简单路径满足答案，则必须有：

$$$
UP_{u,p}\times 10^{dep_v-dep_p}+DOWN_{p,v}=0
$$$

注意这是在已经进行了取模操作下的结果。

其中 $UP_{i,j}$ 表示从 $i$ 到祖先 $j$ 形成的数字，$DOWN_{i,j}$ 表示从祖先 $i$ 到子孙 $j$ 所形成的的数字。

那么我们可以得到关系式：

$$$
UP_{i,j}=\frac{up_i-up_j}{10^{dep_j}}\\DOWN_{i,j}=down_j-down_i\times10^{dep_j-dep_i}
$$$

那么我们再把这两条关系式中，我们在做启发式合并时，已经知道了 $p$ 和 $u$ 或者 $p$ 和 $v$，我们需要将式子一边全部转化为已知量，一边全部转化成未知量。

那么我们可以进行如下转化：

$$$
UP_{u,p}\times 10^{dep_v-dep_p}+DOWN_{p,v}=0\\
\frac{up_u-up_p}{10^{dep_p}}\times10^{dep_v-dep_p}+down_v-down_p\times10^{dep_v-dep_p}=0\\
$$$

我们先把和 $v$ 有关的移动到一边：

$$$
\frac{down_v}{10^{dep_v}}=\frac{down_p}{10^{dep_p}}-\frac{up_u-up_p}{10^{2dep_p}}
$$$

这样我们就可以通过一个 map 记录下节点 $v$，并且通过已知的 $u$ 和 $p$ 得到匹配的 $v$。

顺带一提，题目所给的模数并非质数，而根据题目所给的条件，需要使用拓展欧几里得来求逆元。

然后我们再考虑将 $u$ 有关的转化到式子的一边：

$$$
up_u=10^{dep_p}\times down_p-\frac{down_v\times {10^{2dep_p}}}{10^{dep_v}}+up_p
$$$

那么同样可以再开一个 map 来记录答案。

在具体实现树上启发式合并时，我们需要先将点的贡献统计进去，再把点加入进去，避免出现同一子树的点相互匹配的情况。

综上，我们只需要在进行树上启发式合并时，维护两个 map，将节点信息加入其中，在匹配时通过需要匹配的节点和当前枚举到的节点计算得到结果，并且找到匹配的数量。

那么这样就没有什么其它细节了，可以直接写啦！

代码：
```cpp
#include<bits/stdc++.h>
#define int long long//坏习惯 
using namespace std;
const int N=2e5+5;
int n,mod,pw[N],dep[N],up[N],down[N],siz[N],son[N],ans,inv[N],L[N],R[N],w[N],cnt;
vector<pair<int,int>> e[N];
map<int,int> Up,Down;
void exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
}
int getinv(int p){
	int x,y;
	exgcd(p,mod,x,y);
	x=(x%mod+mod)%mod;
	return x;
}
void dfs(int p,int fa){
	L[p]=++cnt;
	w[cnt]=p;
	siz[p]=1;
	for(auto tmp:e[p]){
		int i=tmp.first,w=tmp.second;
		if(i==fa)continue;
		dep[i]=dep[p]+1;
		up[i]=(up[p]+pw[dep[p]]*w%mod)%mod;
		down[i]=(10*down[p]%mod+w)%mod;
		dfs(i,p);
		siz[p]+=siz[i];
		if(siz[i]>siz[son[p]])son[p]=i;
	}
	R[p]=cnt;
}
void calc(int u,int v){
	int uu=up[u],uv=up[v],dv=down[v],du=down[u],pv=pw[dep[v]];
    int x=((dv*pv%mod-du*pv%mod*pv%mod*inv[dep[u]]%mod+uv)%mod+mod)%mod;
    x=(x+mod)%mod;
    int y=(dv*inv[dep[v]]%mod+(uv-uu)*inv[dep[v]]%mod*inv[dep[v]]%mod)%mod;
    y=(y+mod)%mod;
    ans+=Up[x]+Down[y];
}
void add(int p){
	int x=up[p],y=down[p]*inv[dep[p]]%mod;
	Up[x]++,Down[y]++;
}
void dfs2(int p,int fa,bool op){
	for(auto tmp:e[p]){
		int i=tmp.first;
		if(i==fa||i==son[p])continue;
		dfs2(i,p,1);
	}
	if(son[p])dfs2(son[p],p,0);
	calc(p,p);
	add(p);
	for(auto tmp:e[p]){
		int i=tmp.first;
		if(i==fa||i==son[p])continue;
		for(int j=L[i];j<=R[i];j++)calc(w[j],p);
		for(int j=L[i];j<=R[i];j++)add(w[j]);
	}
	if(op)Up.clear(),Down.clear();
}
signed main(){
	scanf("%lld%lld",&n,&mod);
	pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=(pw[i-1]*10)%mod;
	for(int i=0;i<=n;i++)inv[i]=getinv(pw[i]);
	for(int i=1,u,v,w;i<n;i++){
		scanf("%lld%lld%lld",&u,&v,&w);
		u++,v++;
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	dfs(1,0);
	dfs2(1,0,0);
	cout<<ans;
	return 0;
}
``````

---

## 作者：Super_Cube (赞：1)

# Solution

树上一条路径 $x\rightarrow y$，一定会经过 lca 节点 $p$，即 $x\rightarrow p$ 的上升段，和 $p\rightarrow y$ 的下降段。

把 $x\rightarrow p$ 上升段拼出来的整数记为 $d_1$，$p\rightarrow y$ 下降段拼出来的整数记为 $d_2$，经过的边数量记为 $l$。那么路径 $x\rightarrow y$ 合法就需要满足 $d_1\times 10^{l}+d_2 \equiv 0\pmod M$。

树上的路径统计问题，考虑点分治。把上式移项得到 $d_1\equiv -d_2\times 10^{-l}\pmod M$。在点分治时，当前重心下的 $d_1$，$d_2$ 与 $l$ 都是好统计的。计算答案的时候，把 $d_1$ 放入桶中，用 $-d_2\times 10^{-l}$ 查询桶累加，这个过程用 `map` 能简易的实现。

别用普通的 `unordered_map`，会 TLE on test 119。

现有的点分治题解都是用容斥来算的，我不会这技巧。但是用朴素的方法，在当前子树查询之前子树的桶，然后把当前子树的值放进去也是可以做的，不过要正反跑两遍。在点分治里面要特殊处理每个点到当前重心的答案。

# Code

```cpp
#include <bits/stdc++.h>
int mod;
int base[100005], inv[100005];
inline void Exgcd(int a, int b, int& x, int& y) {
    if (!b)
        return x = 1, y = 0, void();
    Exgcd(b, a % b, y, x);
    y -= a / b * x;
}
std::vector<std::pair<int, int> > v[100005];
bool vis[100005];
int siz[100005];
int rt, all;
void dfs(int p, int dad) {
    siz[p] = 1;
    int w = 0;
    for (const auto& i : v[p])
        if (!vis[i.first] && i.first != dad)
            dfs(i.first, p), siz[p] += siz[i.first], w = std::max(w, siz[i.first]);
    w = std::max(w, all - siz[p]);
    if ((w << 1) <= all)
        rt = p;
}
std::vector<std::tuple<int, int, int> > g;
void get(int p, int dad, int dep, int dis1, int dis2) {
    g.emplace_back(dep, dis1, dis2);
    for (const auto& i : v[p])
        if (!vis[i.first] && i.first != dad)
            get(i.first, p, dep + 1, (dis1 * 10ll + i.second) % mod,
                (dis2 + 1ll * base[dep] * i.second) % mod);
}
std::map<int, int> mp;
long long ans;
void solve(int p) {
    mp.clear();
    ++mp[0];
    for (const auto& i : v[p]) {
        if (vis[i.first])
            continue;
        g.clear();
        get(i.first, p, 1, i.second, i.second);
        for (const auto& j : g)
            if (mp.count((mod - 1ll * std::get<1>(j) * inv[std::get<0>(j)] % mod) % mod))
                ans += mp[(mod - 1ll * std::get<1>(j) * inv[std::get<0>(j)] % mod) % mod];
        for (const auto& j : g) ++mp[std::get<2>(j)];
    }
    ans += mp[0] - 1;
    std::reverse(v[p].begin(), v[p].end());
    mp.clear();
    for (const auto& i : v[p]) {
        if (vis[i.first])
            continue;
        g.clear();
        get(i.first, p, 1, i.second, i.second);
        for (const auto& j : g)
            if (mp.count((mod - 1ll * std::get<1>(j) * inv[std::get<0>(j)] % mod) % mod))
                ans += mp[(mod - 1ll * std::get<1>(j) * inv[std::get<0>(j)] % mod) % mod];
        for (const auto& j : g) ++mp[std::get<2>(j)];
    }
    vis[p] = true;
    dfs(p, 0);
    for (const auto& i : v[p]) {
        if (vis[i.first])
            continue;
        all = siz[i.first];
        dfs(i.first, p);
        solve(rt);
    }
}
int n;
int main() {
    scanf("%d%d", &n, &mod);
    base[0] = 1;
    for (int i = 1; i <= n; ++i) base[i] = base[i - 1] * 10ll % mod;
    Exgcd(10, mod, inv[1], inv[0]), inv[1] = (inv[1] % mod + mod) % mod;
    inv[0] = 1;
    for (int i = 2; i <= n; ++i) inv[i] = 1ll * inv[i - 1] * inv[1] % mod;
    for (int i = 1, x, y, z; i < n; ++i)
        scanf("%d%d%d", &x, &y, &z), ++x, ++y, z %= mod, v[x].emplace_back(y, z), v[y].emplace_back(x, z);
    all = n;
    dfs(1, 0);
    solve(rt);
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：luckydrawbox (赞：1)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF715C)

看到题解区的大佬都用 $\text{map}$，蒟蒻表示只会 $\text{sort}$，于是这里给出一个不用 $\text{map}$ 的**点分治**做法。

## 前置知识

- [树的重心](https://oi-wiki.org/graph/tree-centroid/)。
- [点分治](https://oi-wiki.org/graph/tree-divide/)。
- [乘法逆元](https://oi-wiki.org/math/number-theory/inverse/)。

## 题意

给定一棵 $n$ 个点的树，任意边权 $w$ 满足 $1 \leq w\leq 9$。给定一个数 $m$，保证 $\gcd(m,10)=1$。

对于一对不同的点对 $(u,v)$（$(u,v)$ 和 $(v,u)$ 也是不同的），将 $u$ 到 $v$ 的最短路 $u\Rightarrow v$ 经过的边的边权连接起来，得到一个数字 $x$，若满足 $x\equiv0\pmod m$，则称 $(u,v)$ 是有趣的点对。

求这颗树上有多少对有趣的点对？

$n≤10^5,m\leq 10^9$。

## 分析

统计树上满足要求的点对个数常常要用点分治，这题也不例外。

提前预处理 $10$ 的幂及逆元。 

接下来我们考虑如何计算一棵树中经过重心 $center$ 的点对个数。

首先，预处理出每个点的层数 $d_i$ 和重心到第 $i$ 个点**返往**分别形成的数 $num1_i,num2_i$，此时，$(u,v)$ 的 $x$ 等于 $num2_u\times 10^{d_v}+num1_v$，即 $num2_u\times 10^{d_v}+num1_v\equiv0\pmod m$，因为 $\gcd(m,10)=1$，所以 $num2_u\equiv-num1_v\times 10^{-d_v}\pmod m$，枚举每个 $num1_v$，找出相应的 $num2_u$ 的个数即可。

如何求呢？在预处理层数的同时，我们记录每个节点属于 $center$ 的哪个子节点节点，也就是 $i$ 的颜色 $c_i$，我们把每个 $num2_i$ 存入数组 $a_{c_i}$ 中（$a_{c_i}$ 表示以 $center$ 的子节点 $c_i$ 为根的子树的 $num2_i$ 集合），存入数组 $a2$ 中（$a2$ 表示的是以 $center$ 为根的树中的 $num2_i$ 集合），同时把每个 $\text{pair}$ 对 $(num1_i,i)$ 存入数组 $a1$ 中（$a1$ 表示以 $center$ 为根的树中的 $num1_i$ 集合）。

接下来把 $a_i,a1,a2$ 数组排序，枚举 $a1$ 里的元素 $(num1_i,i)$ ，此时我们要找的数 $need\equiv-num1_i\times 10^{-d_i}\pmod m$，我们需要的是子树 $c_i$ 外的 $need$ 的个数，根据容斥原理，子树 $c_i$ 外的 $need$ 的个数等于以 $center$ 为根的树减去在子树 $c_i$ 内 $need$ 的个数，这两个部分可以通过 $a_i,a1,a2$ 在二分查找得到。注意，如果某个 $num1_i$  或 $num2_i$ 的是 $m$ 的倍数，说明 $i\Rightarrow center$ 或 $i\Leftarrow center$ 这条链的端点本身就是有趣的点对，直接让答案增加 $1$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e5+10;
int n,s[N],t,c[N];
ll m,ans,d[N],num1[N],num2[N],m10[N],nim10[N];
vector<int>e[N],a[N],a2;
vector<ll>w[N];
vector<pair<ll,int> >a1;
pair<ll,int> gg;
bool v1[N],v2[N];
long long exgcd(long long a,long long b,long long &x,long long &y){
    if(!b){
        x=1;y=0;
        return a;
    }
    long long d=exgcd(b,a%b,x,y);
    long long z=x;x=y;y=z-y*(a/b);
    return d;
}
long long qni_ol(long long a,long long p){
    long long x,y;
    exgcd(a,p,x,y);
    return x;
}
void add(int u,int v,ll W){
	e[u].push_back(v);
	w[u].push_back(W);
}
struct Tree_Center{
	int sum;
	int size[N],weight[N];
	int center;
	void dfs(int x,int fa){
		size[x]=1;
		weight[x]=0;
		for(int i=0;i<e[x].size();i++){
			if(e[x][i]==fa||v2[e[x][i]])
				continue;
			dfs(e[x][i],x);
			size[x]+=size[e[x][i]];
			weight[x]=max(weight[x],size[e[x][i]]);
		}
		weight[x]=max(weight[x],sum-size[x]);
		if(weight[x]<weight[center])
			center=x;
	}
	void ask(int root,int n){
		sum=n;
		weight[center=0]=1e9;
		dfs(root,0);
	}
}tree;
void dfs(int x,int fa,int col){
	s[x]=1;
	d[x]=d[fa]+1;
	for(int i=0;i<e[x].size();i++){
		if(e[x][i]==fa||v2[e[x][i]])
			continue;
		num1[e[x][i]]=(num1[x]*10%m+w[x][i])%m;
		num2[e[x][i]]=(num2[x]+w[x][i]*m10[d[x]]%m)%m;
		c[e[x][i]]=col;
		a[col].push_back(num2[e[x][i]]);
		gg.first=num1[e[x][i]];gg.second=e[x][i];
		a1.push_back(gg);
		a2.push_back(num2[e[x][i]]);
		dfs(e[x][i],x,col);
		s[x]+=s[e[x][i]];
	}
}
ll get(int col,ll need){
	return upper_bound(a[col].begin(),a[col].end(),need)-
	lower_bound(a[col].begin(),a[col].end(),need);
}
void calc(int x){
	d[x]=0;
	while(a1.size())
		a1.pop_back();
	while(a2.size())
		a2.pop_back();
	for(int i=0;i<e[x].size();i++){
		if(v2[e[x][i]])
			continue;
		while(a[e[x][i]].size())
			a[e[x][i]].pop_back();
		num1[e[x][i]]=num2[e[x][i]]=w[x][i]%m;
		c[e[x][i]]=e[x][i];
		a[e[x][i]].push_back(num2[e[x][i]]);
		gg.first=num1[e[x][i]];gg.second=e[x][i];
		a1.push_back(gg);
		a2.push_back(num2[e[x][i]]);
		dfs(e[x][i],x,e[x][i]);
		sort(a[e[x][i]].begin(),a[e[x][i]].end());
	}
	sort(a1.begin(),a1.end());
	sort(a2.begin(),a2.end());
	ll need;
	for(int i=0;i<a1.size();i++){
		if(!a1[i].first)
			ans++;
		need=(m-a1[i].first*nim10[d[a1[i].second]]%m)%m;
		ans+=upper_bound(a2.begin(),a2.end(),need)-
		lower_bound(a2.begin(),a2.end(),need)-get(c[a1[i].second],need);
	}
	for(int i=0;i<a2.size();i++)
		if(!a2[i])
			ans++;
}
void DFZ(int x,int sum){
	tree.ask(x,sum);
	int center=tree.center;
	calc(center);
	v2[center]=1;
	for(int i=0;i<e[center].size();i++){
		if(v2[e[center][i]])
			continue;
		DFZ(e[center][i],s[e[center][i]]);
	}
}
int main(){
	n=read();m=read();
	m10[0]=1;
	for(int i=1;i<=n;i++){
		m10[i]=m10[i-1]*10%m;
		nim10[i]=qni_ol(m10[i],m);
	}
	int u,v,w;
	for(int i=1;i<n;i++){
		u=read()+1;v=read()+1;w=read();
		add(u,v,w);add(v,u,w);
	}
	DFZ(1,n);
	write(ans);
	return 0;
}
```


---

## 作者：NightDiver (赞：1)

统计路径数量，考虑点分治试试。那么问题就转化为对于每一个点 $u$，给定四个点集，第一组与第二组考虑贡献，第三组与第四组考虑贡献。考虑 $A,B$ 集合之间的贡献即计数二元组 $(a,b) a \in A,b \in B$ 满足 $d_a + D_b \times 10^{\text{dis}(u,a)} \equiv 0 \pmod {m}$，也就是 $d_a \times (10^{\text{dis}(u,a)})^{-1} \equiv D_b \pmod {m}$。注意正反都要考虑，这也是有四个点集的原因。

[代码在这里](https://www.cnblogs.com/TongKa/p/18387243)

---

## 作者：Genius_Star (赞：0)

### 思路：

这种树上路径问题一般使用点分治。

为了方便令 $(x,y)$ 表示从 $x$ 到 $y$ 的路径上的边权组成的数。

令当前点分治的分治重心为 $rt$，设 $dis_{u,0/1}$ 表示从 $(rt,u)$ 和 $(u,rt)$，转移方程为：

$$dis_{u,0} = dis_{fa,0} \times 10 + w$$

$$dis_{u,1} = dis_{fa,0} + 10^{dep_{fa}} \times w$$

那么：

$$(u,v) = dis_{u,1} \times 10^{dep_v} + dis_{v,0}$$

则我们需要：

$$dis_{u,1} \times 10^{dep_v} + dis_{v,0} \equiv 0 \pmod M$$

即：

$$dis_{u,1} \times 10^{dep_v} \equiv - dis_{v,0} \pmod M$$

可以化为：

$$dis_{u,1} \equiv - \frac{dis_{v,0}}{10^{dep_v}} \pmod M$$

则可以开两个桶分别记录一下即可，对于 $10^{x}$ 或 $10^{-x}$ 的值要在刚开始就预处理出来。

时间复杂度为 $O(N \log^2 N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef long long ll;
const ll N=2e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,sum,cnt,Max,root,ans,mod;
ll p[N],inv[N],d[N],siz[N],dep[N],dis[2][N];
bool del[N];
vector<pair<ll,ll>> E[N];
map<ll,ll> f1,f2;
void Exgcd(ll a,ll b,ll &x,ll &y){
    if(!b)
	  x=1,y=0;
    else{
    	Exgcd(b,a%b,y,x);
		y-=a/b*x;
	}
}
ll Inv(ll a){
    ll x,y;
    Exgcd(a,mod,x,y);
    x=(x%mod+mod)%mod;
    return x;
}
void add(ll u,ll v,ll w){
	E[u].push_back({v,w});
	E[v].push_back({u,w});
}
void init(){
	p[0]=1;
	for(int i=1;i<N;i++)
	  p[i]=(p[i-1]*10ll)%mod;
	inv[N-1]=Inv(p[N-1]);
	for(int i=N-2;i>=0;i--)
	  inv[i]=inv[i+1]*10ll%mod;
}
void getroot(ll u,ll fa){
	ll s=0;
	siz[u]=1;
	for(auto t:E[u]){
		ll v=t.first;
		if(v==fa||del[v])
		  continue;
		getroot(v,u);
		siz[u]+=siz[v];
		s=max(s,siz[v]);
	}
	s=max(s,sum-siz[u]);
	if(s<Max){
		Max=s;
		root=u;
	}
}
void Get(ll u,ll s){
	root=0;
	sum=Max=s;
	getroot(u,0);
	getroot(root,0);
}
void getdis(ll u,ll fa){
	d[++cnt]=u;
	for(auto t:E[u]){
		ll v=t.first,w=t.second;
		if(v==fa||del[v])
		  continue;
		dep[v]=dep[u]+1;
		dis[0][v]=(dis[0][u]*10ll+w)%mod;
		dis[1][v]=(dis[1][u]+p[dep[u]]*w)%mod;
		getdis(v,u);
	}
}
void calc(ll u){
	dep[u]=0;
	for(auto t:E[u]){
		ll v=t.first,w=t.second;
		if(del[v])
		  continue;
		dis[0][v]=dis[1][v]=w;
		dep[v]=1;
		cnt=0;
		getdis(v,u);
		for(int i=1;i<=cnt;i++){
			ans+=f1[dis[1][d[i]]];
			ans+=f2[(mod-dis[0][d[i]]*inv[dep[d[i]]]%mod)%mod];
//			cerr<<d[i]<<' '<<dis[1][d[i]]<<' '<<dis[0][d[i]]*inv[dep[d[i]]-dep[u]]%mod<<'\n';
		}
		for(int i=1;i<=cnt;i++){
			f1[(mod-dis[0][d[i]]*inv[dep[d[i]]]%mod)%mod]++;
			f2[dis[1][d[i]]]++;
			if(!dis[0][d[i]])
			  ans++;
			if(!dis[1][d[i]])
			  ans++;
		}
	}
	f1.clear(),f2.clear();
}
void solve(ll u){
	calc(u);
	del[u]=1;
	for(auto t:E[u]){
		ll v=t.first;
		if(del[v])
		  continue;
		Get(v,siz[v]);
		solve(root);
	}
}
int main(){
	n=read(),mod=read();
	for(int u,v,w,i=1;i<n;i++){
		u=read(),v=read(),w=read()%mod;
		add(u+1,v+1,w);
	}
	init();
	Get(1,n);
	solve(root);
	write(ans);
	return 0;
}
```

---

## 作者：Corzica (赞：0)

这种路径问题，一眼点分治。

我们对于点分治到的每一个点，维护从分治中心到这个点顺着读和反着读两个数，以及这个点的深度。

统计答案时，有 $a+b\times10^{d} \equiv  0\pmod m$。

所以，$ b\equiv \frac{-a}{10^d}\pmod m $。

可以开一个 map 把所有反向的 $b$ 存进去，再遍历每一个正向的 $a$ 及其对应的 $d$，直接统计即可。

时间复杂度 $n\log^2n$。

偶对，因为 $m$ 不一定是素数，所以要用 exgcd 来求逆元。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#pragma GCC optimize(2)
using namespace std;
int n, mod, head[200005], nxt[200005], to[200005], w[200005], ccnt, ans, jie[100005], siz[100005], vis[100005], minn, zd, zx, x, y, tx, inv[100005];
void exgcd(int p, int q) {
	if (q == 0) {
		x = 1;
		y = 0;
		return;
	}
	exgcd(q, p % q);
	tx = x;
	x = y;
	y = tx - p / q * y;
}
inline int ksm(int p, int q = mod - 2) {
	int base = 1;
	while (q) {
		if (q & 1) base = base * p % mod;
		q >>= 1;
		p = p * p % mod;
	}
	return base;
}
inline void add(int p, int q, int ww) {
	nxt[++ccnt] = head[p];
	to[ccnt] = q;
	w[ccnt] = ww;
	head[p] = ccnt;
}
void dfs_zx(int p, int fa) {
	siz[p] = 1;
	int cnt = 0;
	for (int i = head[p]; i; i = nxt[i]) {
		if (to[i] != fa && !vis[to[i]]) {
			dfs_zx(to[i], p);
			siz[p] += siz[to[i]];
			cnt = max(cnt, siz[to[i]]);
		}
	}
	cnt = max(cnt, zd - siz[p]);
	if (cnt < minn) {
		minn = cnt;
		zx = p;
	}
}
void dfs_all(int p, int fa) {
	for (int i = head[p]; i; i = nxt[i]) {
		if (to[i] != fa && !vis[to[i]]) {
			dfs_all(to[i], p);
		}
	}
	zd++;
}
struct node {
	int suma, sumb, dep, ffa;
} b[100005];
inline void dfs(int p, int suma, int sumb, int dep, int q, int ffa) {
	if (suma == 0) ans++;
	if (sumb == 0) ans++;
	b[ ++ ccnt] = node{suma, sumb, dep, ffa};
	for (int i = head[p]; i; i = nxt[i]) {
		if (to[i] != q && !vis[to[i]]) {
			dfs(to[i], (suma * 10 + w[i]) % mod, (sumb + w[i]*jie[dep] % mod) % mod, dep + 1, p, ffa);
		}
	}
}
inline bool comp1(node p, node q) {
	return p.ffa < q.ffa;
}
inline void calc(int l, int r, int op) {
	map<int, int> ma;
	ma.clear();
	for (int i = l; i <= r; i++) {
		ma[b[i].sumb] += 1;
	}
	int u;
	for (int i = l; i <= r; i++) {
		u = (mod - b[i].suma) % mod;
		u = u * inv[b[i].dep] % mod;
		if (ma.find(u) != ma.end()) {
			ans += op * ma[u];
		}
	}
}
inline void solve(int p) {
	minn = 0x3f3f3f3f, zx = -1;
	zd = 0;
	dfs_all(p, -1);
	dfs_zx(p, -1);
	p = zx;
	vis[p] = 1;
	ccnt = 0;
	for (int i = head[p]; i; i = nxt[i]) {
		if (!vis[to[i]]) {
			dfs(to[i], w[i] % mod, w[i] % mod, 1, p, to[i]);
		}
	}
	calc(1, ccnt, 1);
	sort(b + 1, b + ccnt + 1, comp1);
	int lst = 1;
	for (int i = 2; i <= ccnt; i++) {
		if (b[i].ffa != b[i - 1].ffa) {
			calc(lst, i - 1, - 1);
			lst = i;
		}
	}
	calc(lst, ccnt,  - 1);
	for (int i = head[p]; i; i = nxt[i]) {
		if (!vis[to[i]]) solve(to[i]);
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> mod;
	int p, q, ww;
	for (int i = 1; i < n; i++) {
		cin >> p >> q >> ww;
		p++, q++;
		add(p, q, ww), add(q, p, ww);
	}
	jie[0] = 1;
	for (int i = 1; i <= n; i++) {
		jie[i] = jie[i - 1] * 10 % mod;
	}
	inv[0] = 1;
	exgcd(mod, 10);
	y = (y % mod + mod) % mod;
	inv[1] = y ;
	for (int i = 2; i <= n; i++) {
		inv[i] = inv[i - 1] * inv[1] % mod;
	}
	solve(1);
	cout << ans;
}
```

---

