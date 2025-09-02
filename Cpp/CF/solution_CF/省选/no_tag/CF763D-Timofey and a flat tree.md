# Timofey and a flat tree

## 题目描述

### 题目大意
给你一棵$n$个节点的无根树， 现在要你定一个根节点， 满足其不同构的子树的数量最大。

## 样例 #1

### 输入

```
3
1 2
2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
1 2
4 2
2 3
5 6
6 7
3 7
```

### 输出

```
1
```

## 样例 #3

### 输入

```
10
1 7
1 8
9 4
5 1
9 2
3 5
10 6
10 9
5 10
```

### 输出

```
2
```

# 题解

## 作者：素质玩家孙1超 (赞：9)

发个题解记录一下我自己乱搞出来但 $99 \%$ 前人已经用过的一个对于一类换根dp题目的做法。

---

$ \texttt{题意}:$ 给你一棵 $n$个节点的无根树， 现在要你定一个根节点， 满足其不同构的子树的数量最大。

注：其中子树的是否同构是根据有根树来判断的。

---

$ \texttt{解}:$ 因为是有根树，所以我们只要把一个点为根的所有节点的 hash 值算出来，然后去重一下，就可以算出有多少不同构的子树。

这里的 hash 值是和根有关的，可以用树形dp从儿子节点转移，由于这个 hash 对于本文不是重点，所以我直接**借鉴**了另一篇题解 @xiaolilsq 的 hash 函数：

$$dp_x = size _x \times \sum _{y \in son_x} dp_y + size_x^2$$ 

接下来就是考虑这个东西在怎么用换根dp转移。

其实有一类换根dp题的节点的dp值都只和这个节点的儿子集合有关，比如 P2018 （但是这个题支持 $O(n^2 \log n)$ ）。由于数的性质，对于一个节点，他的儿子集合就是他的父亲对于他的邻居集合的补集。即我们可以纪录一个节点和它的父亲节点来代替这个节点的儿子们，即搞一个 $dp[x][father_x]$ 来代表 $x$ 这个节点在以 $father_x$ 作为父亲节点的dp值。

$dp[x][father_x]$ 这个状态显然可以优化成 $dp[edge_{father_x \to x}]$ 即用父亲节点到这个点的边的编号来代替原来的二维状态。

~~（什么？你说你用的是 `vector` 存的图，那你自己想办法吧）~~

显然有了dp数组，换根dp的部分就只要

```cpp
for(int k=First[pos];k;k=Next[k])
{
    if(to[k]==father) continue;
    Delete(dp[k]);
    insert(dp[k^1]);
    if(now>ans1){ans1=now;ans2=to[k];}
    dp1(to[k],pos,k);
    Delete(dp[k^1]);
    insert(dp[k]);
}
// k^1 为 k 这条单向边的反向边。
//Delete 和 insert 表示计算加入/删除这个边的贡献
```

就好了。

现在的重点是如何 $O(n)$ 来求出dp数组。

有一个简单错误的思路：直接对于每个点开跑一个树形dp然后相信玄学的记忆化可以把时间复杂度变得正确。

我一开始就是这么干的，这个方法对于随机图来说时间复杂度没问题，但是若是菊花图则会退化到 $O(n^2)$ ，所以不可取。

正确的方式是像第一次一样，对于每个点搞一遍反向边的树形dp，具体是对于每个点，枚举所有出边的反向边，计算出这个边作为 $edge_{father_x \to x}$ 的dp值，然后处理好一个点的所有邻边后，可以dfs下去处理下一个相邻节点，显然这样做是严格 $O(n)$ 不用证明，直接看代码实现就一目了然。


---

代码（具体用的是map来实现去重和统计的操作）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long 
const int Mo=1e9+7;
const int Maxn=1e5+5;
inline int R()
{
    char c;int res,sign=1;
    while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';
    while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
    return res*sign;
}
int n,m,First[Maxn],to[Maxn*2],Next[Maxn*2],cnt=1,dp[Maxn*2],size[Maxn*2],now,ans1,ans2;
inline void add(int z,int y)
{
    Next[++cnt]=First[z];
    First[z]=cnt;
    to[cnt]=y;
}
unordered_map<int,int>mp;
void insert(int x){if(mp[x]++==0) ++now;}
void Delete(int x){if(--mp[x]==0) --now;}
int dfs(int pos,int father,int fr)//第一遍的树形dp处理一半的单向边 
{
    size[fr]=1;//这里的size数组我也用了如图dp数组类似的方式存储 
    for(int k=First[pos];k;k=Next[k])
    {
        if(to[k]==father) continue;
        dp[fr]=(dp[fr]+dfs(to[k],pos,k))%Mo;
        size[fr]+=size[k];
    }
    dp[fr]=((dp[fr])*size[fr]+size[fr]*size[fr])%Mo;
    insert(dp[fr]);
    return dp[fr];
}
void deal(int pos,int father)//第二遍树形dp处理另一半的单向边 
{
	int Sum=0;
	for(int k=First[pos];k;k=Next[k])Sum=(Sum+dp[k])%Mo; 
	for(int k=First[pos];k;k=Next[k])
	{
		size[k^1]=n-size[k];
		dp[k^1]=(n-size[k])*(Sum-dp[k]+Mo)%Mo+(n-size[k])*(n-size[k]);
		dp[k^1]%=Mo;
		if(to[k]==father) continue;
    	deal(to[k],pos);
	}
}
void dp1(int pos,int father,int fr)//换根dp，ans1纪录最大值，ans2纪录位置 
{
	for(int k=First[pos];k;k=Next[k])
	{
	    if(to[k]==father) continue;
	    Delete(dp[k]);
	    insert(dp[k^1]);
	    if(now>ans1){ans1=now;ans2=to[k];}
	    dp1(to[k],pos,k);
	    Delete(dp[k^1]);
	    insert(dp[k]);
	}
}
signed main()
{
    n=R();
    int x,y;
    for(int i=1;i<n;i++)
    {
        x=R();y=R();
        add(x,y);
        add(y,x);
    }
    dfs(1,0,0);
    ans1=now;ans2=1;
	deal(1,0); 
    dp1(1,0,0);
	cout<<ans2;	
}
```


---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2900}$
---
### 解题思路：

因为涉及到树同构的问题而且数据范围比较大，考虑树哈希。于是问题就变成了快速求出以每一个点为根节点所有子树中不同的哈希值的数量。

明显直接枚举每一个根节点重新计算哈希值完全行不通，于是考虑利用之前的信息进行换根。

---
笔者使用了双哈希提高准确性，这两个随便瞎写的哈希函数分别是 $f_i=size_i\sum f_{son_i}+1$ 和 $g_i=size_i\sum g_{son_i}^2+size_i^2$。其中 $size_i$ 表示以 $i$ 为顶点的子树的大小。

然后为了适应换根，不能简单地用节点为顶点代表状态，这里将边作为状态，也就是 $f_{u\rightarrow v}$ 表示 $v$ 以 $u$ 为父亲的时候的 $f$ 函数哈希值，对于 $g$ 也类似。

---
在具体考虑如何进行换根求答案之前需要将所有边的 $f$ 和 $g$ 计算出来。

容易得出，有一半的边是可以直接通过第一遍 $\text{dfs}$ 直接得出的，这一部分直接通过正常的公式计算即可。这一部分计算前一半的边对应代码中的 $\text{dfs1}$ 函数。

然后考虑如何计算这些正向边的反边，可以发现，即使再某一条边取反之后，对于当前被考虑的节点而言绝大多数的子树任然是子树，只有两个位置发生了变化：原来的父亲进而现在的父亲。那么直接清除之前父亲的影响，加入新父亲的影响即可。

具体实现的时候可以对于每一个节点先行计算出所有所有指向当前节点的边，也就是当前节点作为儿子的所有情况。这样递归儿子计算的时候就可以直接利用刚才计算出的信息清除父亲影响了。这一部分计算剩下的一半边对应代码中的 $\text{dfs2}$ 部分。

---
最后考虑如何换根。

一开始“奠基”的过程是以任意一个节点为根节点统计所有的子树。在换根的时候，产生变动的也只有两个子树，以原根节点为 $u$ 节点，需要换到相邻的 $v$ 节点为例，$f_{u\rightarrow v}$ 消失，$f_{v\rightarrow u}$ 出现。

然后这里用 $\text{map}$ 进行一下统计就行。

换根计算部分对应了代码中的 $\text{dfs3}$ 函数。

---
### 代码：
```cpp
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=500005,MOD=1000000007;
int n,m,head[MAXN],nxt[MAXN],num[MAXN],tot=1,x,y,cnt,ans_cnt,ans_pos;
int f1[MAXN],f2[MAXN],size[MAXN];
map <pair<int,int>,int> mp;
void ins(int num1,int num2){
	mp[make_pair(num1,num2)]++;
	if(mp[make_pair(num1,num2)]==1)cnt++;
}
void del(int num1,int num2){
	mp[make_pair(num1,num2)]--;
	if(mp[make_pair(num1,num2)]==0)cnt--;
}
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
void dfs1(int now,int fa,int fr){
	size[fr]=1;
	for(int i=head[now];i;i=nxt[i]){
		if(num[i]==fa)continue;
		dfs1(num[i],now,i);
		size[fr]+=size[i];
		f1[fr]=(f1[fr]+f1[i])%MOD;
		f2[fr]=(f2[fr]+f2[i]*f2[i])%MOD;
	}
	f1[fr]=(size[fr]*f1[fr]%MOD+1)%MOD;
	f2[fr]=(size[fr]*f2[fr]%MOD+size[fr]*size[fr])%MOD;
	ins(f1[fr],f2[fr]);
}
void dfs2(int now,int fa,int fr){
	int sum1=0,sum2=0;
	for(int i=head[now];i;i=nxt[i]){
		sum1+=f1[i];
		sum2+=f2[i]*f2[i];
	}
	for(int i=head[now];i;i=nxt[i]){
		if(num[i]==fa)continue;
		size[i^1]=n-size[i];
		f1[i^1]=((n-size[i])*((sum1-f1[i]+MOD)%MOD)%MOD+1)%MOD;
		f2[i^1]=((n-size[i])*((sum2-f2[i]*f2[i])%MOD+MOD)%MOD+size[i^1]*size[i^1]%MOD)%MOD;
		dfs2(num[i],now,i);
	}
}
void dfs3(int now,int fa){
	for(int i=head[now];i;i=nxt[i]){
		if(num[i]==fa)continue;
		del(f1[i],f2[i]);
		ins(f1[i^1],f2[i^1]);
		if(cnt>ans_cnt){
			ans_cnt=cnt;
			ans_pos=num[i];
		}
		dfs3(num[i],now);
		del(f1[i^1],f2[i^1]);
		ins(f1[i],f2[i]);
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		scanf("%lld%lld",&x,&y);
		add(x,y);add(y,x);
	}
	dfs1(1,0,0);
	ans_cnt=cnt;
	ans_pos=1;
	dfs2(1,0,0);
	dfs3(1,0);
	printf("%lld",ans_pos);
	return 0;
}
```


---

## 作者：shao0320 (赞：1)

#### CF763D Timofey and a flat tree

比较有意思的题目。

首先对于同一棵点数为$n$的树内，子树的数量只有$2\times(n-1)$棵，（每个边对应两颗）。

考虑换根$dp$,这题关键点在于如何快速判断两棵子树是不是相同。

这是一个树$Hash$的问题，就是让同构的树哈希值一样，从而通过判断哈希值判断两棵树是否一样，本质上和字符串哈希是一样的，都是单向加密的思想。

而由于这是在同一棵树中，又由上边的性质，可以想到给每种子树安排一个编号，而一个结点的哈希值可以简单的表示为其所有子树权值的和。

那么这个权值怎么搞呢，直接随机即可。

而由于哈希值的定义，我们可以发现，换根的时候，从父亲到儿子只需要减掉儿子的权值即可。

以$1$号节点为根先预处理出每条边一个子树的所有值，然后换根$dfs$顺便统计答案即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#include<cstdlib>
#define N 200005
#define int unsigned long long
#define ull unsigned long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,fa[N],now[N],ans,maxn,cnt,p;
ull val[N],f[N];
vector<int>G[N];
map<ull,int>mp;
ull get_rnd(){return (ull)(rand()+1)*2333+(ull)(rand()+1)*19260817+(ull)((rand()+1231)<<28);}
void ins(int x){if(!now[x])++ans;++now[x];}
void del(int x){--now[x];if(!now[x])--ans;}
int get(ull x){if(mp[x])return mp[x];mp[x]=++cnt;return mp[x];}
void dfs1(int x,int fa)
{
	int siz=G[x].size();ull Hash=0;
	for(int i=0;i<siz;i++)
	{
		int v=G[x][i];
		if(v!=fa)dfs1(v,x),Hash+=val[f[v]];
	}
	f[x]=get(Hash);ins(f[x]);
}
void dfs2(int x,int fa,int ffa)
{
	del(f[x]);
	if(ans+1>maxn)maxn=ans+1,p=x;
	int siz=G[x].size();ull Hash=0;
	for(int i=0;i<siz;i++)if(G[x][i]!=fa)Hash+=val[f[G[x][i]]];
	Hash+=val[ffa];
	for(int i=0;i<siz;i++)
	{
		int v=G[x][i];
		if(v==fa)continue;
		int s=Hash-val[f[v]];//ids=get(s);
		ins(get(s));dfs2(v,x,get(s));del(get(s));
	}
	ins(f[x]);
}
signed main()
{
	n=read();
	for(int i=1;i<=n*2;i++)val[i]=get_rnd();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs1(1,0);dfs2(1,0,0);
	cout<<p<<endl;
	return 0;
}
```





---

## 作者：xiaolilsq (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF763D)

[可能更好的阅读体验](https://www.cnblogs.com/lsq147/p/13736401.html)

## 题目分析

先考虑对于一个点 $u$ 如何求不同构的子树数量，这个是很好求的，直接以 $u$ 为根 dfs 一遍，树 hash 就可以得到答案，不会树 hash 的可以看[这里](https://oi-wiki.org/graph/tree-hash/)。

我选取的 hash 函数是（ $v$ 是 $u$ 的儿子， $s_u$ 表示 $u$ 子树大小）：

$$
f_u=s_u\times\sum_{v}f_v+s_u^2
$$

这样子做一次是 $\mathcal O(n)$ 的，显然不可以枚举，所以考虑使用换根的思想，如果根从 $u$ 变成 $v$ ，并且 $u,v$ 有直接连边，那么最多只会有 $u,v$ 两个位置的 hash 值改变，所以我们可以维护一个集合，其中保存的是所有位置的 hash 值，然后直接换根就可以找到以每个点为根 hash 值不同的次数，然后就可以求答案了。

这里的换根还是很简单的，就不具体写了。

我在实现的时候，为了减小常数，就先把所有 hash 值离散化了一遍，然后用数组求答案，当然也可以使用`set`之类的 STL 实现。

## 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ch() getchar()
#define pc(x) putchar(x)
using namespace std;
template<typename T>void read(T&x){
	static char c;static int f;
	for(c=ch(),f=1;c<'0'||c>'9';c=ch())if(c=='-')f=-f;
	for(x=0;c>='0'&&c<='9';c=ch())x=x*10+(c&15);x*=f;
}
template<typename T>void write(T x){
	static char q[65];int cnt=0;
	if(x<0)pc('-'),x=-x;
	q[++cnt]=x%10,x/=10;
	while(x)
		q[++cnt]=x%10,x/=10;
	while(cnt)pc(q[cnt--]+'0');
}
const int mod=1000000007,maxn=100005;
int mo(const int x){
	return x>=mod?x-mod:x;
}
int power(int a,int x){
	int re=1;
	while(x){
		if(x&1)re=1ll*re*a%mod;
		a=1ll*a*a%mod,x>>=1;
	}
	return re;
}
struct Edge{
	int v,nt;
	Edge(int v=0,int nt=0):
		v(v),nt(nt){}
}e[maxn*2];
int hd[maxn],num;
void qwq(int u,int v){
	e[++num]=Edge(v,hd[u]),hd[u]=num;
}
int sz[maxn],ha[maxn],pri[maxn];
void dfs0(int u,int fa){
	sz[u]=1;ha[u]=0;
	for(int i=hd[u];i;i=e[i].nt){
		int v=e[i].v;
		if(v==fa)continue;
		dfs0(v,u);sz[u]+=sz[v];
		ha[u]=mo(ha[u]+ha[v]);
	}
	ha[u]=mo(1ll*ha[u]*sz[u]%mod+pri[sz[u]]);
}
int I[maxn][4];
void dfs1(int u,int fa){
	int hu=ha[u],su=sz[u];
	for(int i=hd[u];i;i=e[i].nt){
		int v=e[i].v;
		if(v==fa)continue;
		I[v][0]=ha[u];I[v][1]=ha[v];
		ha[u]=mo(mod-ha[v]+1ll*mo(mod-pri[sz[u]]+ha[u])*power(sz[u],mod-2)%mod);
		sz[u]-=sz[v];ha[u]=mo(1ll*ha[u]*sz[u]%mod+pri[sz[u]]);
		ha[v]=1ll*mo(mod-pri[sz[v]]+ha[v])*power(sz[v],mod-2)%mod;
		sz[v]+=sz[u];ha[v]=mo(1ll*mo(ha[v]+ha[u])*sz[v]%mod+pri[sz[v]]);
		I[v][2]=ha[u];I[v][3]=ha[v];
		dfs1(v,u);ha[u]=hu,sz[u]=su;
	}
}
int ox[maxn*5],sum[maxn*5],cnt;
int no,mx,ans;
void add(int pos){
	no+=!(sum[pos]++);
}
void del(int pos){
	no-=!(--sum[pos]);
}
void dfs2(int u,int fa){
	if(fa){
		del(lower_bound(ox,ox+cnt,I[u][0])-ox);
		del(lower_bound(ox,ox+cnt,I[u][1])-ox);
		add(lower_bound(ox,ox+cnt,I[u][2])-ox);
		add(lower_bound(ox,ox+cnt,I[u][3])-ox);
	}
	if(no>mx)mx=no,ans=u;
	for(int i=hd[u];i;i=e[i].nt){
		int v=e[i].v;
		if(v==fa)continue;
		dfs2(v,u);
	}
	if(fa){
		add(lower_bound(ox,ox+cnt,I[u][0])-ox);
		add(lower_bound(ox,ox+cnt,I[u][1])-ox);
		del(lower_bound(ox,ox+cnt,I[u][2])-ox);
		del(lower_bound(ox,ox+cnt,I[u][3])-ox);
	}
}
int cp[maxn];
int main(){
	int n;read(n);
	for(int i=1;i<=n;++i)
		pri[i]=1ll*i*i%mod;
	for(int i=1;i<n;++i){
		int u,v;
		read(u),read(v);
		qwq(u,v);qwq(v,u);
	}
	dfs0(1,0);
	for(int i=1;i<=n;++i)
		ox[cnt++]=cp[i]=ha[i];
	dfs1(1,0);
	for(int i=1;i<=n;++i)
		for(int t=0;t<4;++t)
			ox[cnt++]=I[i][t];
	sort(ox,ox+cnt);
	cnt=unique(ox,ox+cnt)-ox;
	for(int i=1;i<=n;++i)
		add(lower_bound(ox,ox+cnt,cp[i])-ox);
	dfs2(1,0);
	write(ans),pc('\n');
	return 0;
}

```

---

## 作者：Flandres (赞：0)

树哈希水题。

我采用的是 [oiwiki](https://oi-wiki.org//graph/tree-hash/) 上的树哈希方法:

$$f_u=1+\sum_{v\in son_u} g(f_v)$$

其中 $f_u$ 表示以 $u$ 为根的子树的哈希值，$g$ 为整数到整数的映射，这里选用的 xorshift，也可以用其他的函数。

然后显然可以换根 dp 直接做。根转移到相邻的节点子树哈希值变动的只有这两个节点，直接哈希值相加减就行。

我们可以开桶记录哈希值，在 dfs 的时候维护树以当前节点为根有多少种不同的哈希值，记录下种类最多的即可，不要忘记回溯的时候清除贡献。

总体时间复杂度为 $O(n)$。


详见代码：

```cpp
#include<bits/stdc++.h>
using ull=unsigned long long;
const ull mask=std::chrono::steady_clock::now().time_since_epoch().count();
inline ull shift(ull x){x^=mask;x^=x<<13;x^=x>>17;x^=x<<5;x^=mask;return x;}
int n;ull h[100005],p[100005];
std::vector<int> g[100005];
std::map<ull,int> b;
void dfs1(int x,int f){
	h[x]=1;
	for(auto &y:g[x]){
		if(y==f)continue;
		dfs1(y,x);
		h[x]+=shift(h[y]);
	}
	b[h[x]]++;
}
int mx,now,pos;
void dfs2(int x,int f){
	for(auto &y:g[x]){
		if(y==f)continue;
		p[y]=h[y]+shift(p[x]-shift(h[y]));
		now-=!--b[p[x]];now-=!--b[h[y]];
		now+=!b[p[x]-shift(h[y])]++;
		now+=!b[h[y]+shift(p[x]-shift(h[y]))]++;
		if(mx<now)mx=now,pos=y;assert(mx<=n);
		dfs2(y,x);
		now+=!b[p[x]]++;now+=!b[h[y]]++;
		now-=!--b[p[x]-shift(h[y])];
		now-=!--b[h[y]+shift(p[x]-shift(h[y]))];
	}
}
int main(){
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cin>>n;for(int i=1,u,v;i<n;++i)std::cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	dfs1(1,0);p[1]=h[1],mx=now=(int)b.size(),pos=1;dfs2(1,0);
	std::cout<<pos;
}
```



---

