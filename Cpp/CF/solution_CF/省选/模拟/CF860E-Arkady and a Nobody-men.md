# Arkady and a Nobody-men

## 题目描述

Arkady words in a large company. There are $ n $ employees working in a system of a strict hierarchy. Namely, each employee, with an exception of the CEO, has exactly one immediate manager. The CEO is a manager (through a chain of immediate managers) of all employees.

Each employee has an integer rank. The CEO has rank equal to $ 1 $ , each other employee has rank equal to the rank of his immediate manager plus $ 1 $ .

Arkady has a good post in the company, however, he feels that he is nobody in the company's structure, and there are a lot of people who can replace him. He introduced the value of replaceability. Consider an employee $ a $ and an employee $ b $ , the latter being manager of $ a $ (not necessarily immediate). Then the replaceability $ r(a,b) $ of $ a $ with respect to $ b $ is the number of subordinates (not necessarily immediate) of the manager $ b $ , whose rank is not greater than the rank of $ a $ . Apart from replaceability, Arkady introduced the value of negligibility. The negligibility $ z_{a} $ of employee $ a $ equals the sum of his replaceabilities with respect to all his managers, i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF860E/505bc2ce43f8c1ae79d55147b7d11673e92ab6e4.png), where the sum is taken over all his managers $ b $ .

Arkady is interested not only in negligibility of himself, but also in negligibility of all employees in the company. Find the negligibility of each employee for Arkady.

## 说明/提示

Consider the first example:

- The CEO has no managers, thus $ z_{1}=0 $ .
- $ r(2,1)=2 $ (employees $ 2 $ and $ 4 $ suit the conditions, employee $ 3 $ has too large rank). Thus $ z_{2}=r(2,1)=2 $ .
- Similarly, $ z_{4}=r(4,1)=2 $ .
- $ r(3,2)=1 $ (employee $ 3 $ is a subordinate of $ 2 $ and has suitable rank). $ r(3,1)=3 $ (employees $ 2 $ , $ 3 $ , $ 4 $ suit the conditions). Thus $ z_{3}=r(3,2)+r(3,1)=4 $ .

## 样例 #1

### 输入

```
4
0 1 2 1
```

### 输出

```
0 2 4 2 
```

## 样例 #2

### 输入

```
5
2 3 4 5 0
```

### 输出

```
10 6 3 1 0 
```

## 样例 #3

### 输入

```
5
0 1 1 1 3
```

### 输出

```
0 3 3 3 5 
```

# 题解

## 作者：SIGSEGV (赞：6)

长链剖分的玄学题目。重链剖分要$O(N\log^2 N)$的时间复杂度,LCA+单调栈也要$O(N\log N)$。但是长链剖分珂以$O(N)$。

具体做法: 

观察到$ans_v=ans_{fa(v)}+dep_{fa(v)}+ans'_v$，其中$dep$为深度(根的深度为1)，$ans$为答案，$ans'_v$为除了$v$外所有深度为$dep_v$的点对$v$产生的贡献。$dep_v$在这个柿子中的含义是$v$的所有祖先(不包含自己)。

不妨令`dfs(v)`返回一个vector,其中vector的第$d$项是一个三元组$(ans'_x,x,cnt_x)$，分别表示仅考虑$x$在$v$的子树内的$dep$相同的点时的$ans'_x$,子树内深度为$d$的任意一点$x$和子树内深度为$d$的点的个数。

考虑怎么合并$v$的两个儿子的vector。显然对应的深度的三元组才能合并。然后考虑如何合并$(ans'_x,x,cnt_x)$和$(ans'_y,y,cnt_y)$。我们只要令$ans'_x+=dep_v\times cnt_y$,$ans'_y+=dep_v\times cnt_x$,然后返回$(ans'_x,x,cnt_x+cnt_y)$。但是这个$ans'_y$的值显然不能扔着不管。观察到接下来的过程中所有$dep$与$x$,$y$相同的点都会同时对$ans'_x$和$ans'_y$产生贡献，也就是$ans'_y-ans'_x$的值已经确定。在一张新图上从$x$向$y$连一条边权为$ans'_y-ans'_x$的边即可，最后结束后珂以用这张图还原。

在实现时，因为$v$的vector的第$d$项在$d< dep_v$时都是无意义的，所以珂以用一种支持`push_front`操作的数据结构(邻接表）代替vector。

要跑四遍dfs...(第一遍LPD,第二遍如上，第三遍还原$ans'$,第四步计算$ans$)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 500005;
using ll = long long;
int n;ll ans[N];
vector<int> e[N];
vector<pair<int,int>> g[N];
int a[N],dep[N],lson[N],lv[N];
int head[N],v[N],w[N],nxt[N],ptr;
inline void add_edge(int uu,int vv,int ww)
{v[ptr] = vv;w[ptr] = ww;nxt[ptr] = head[uu];head[uu] = ptr++;}
void dfs1(int pos)
{
    for (auto &i : e[pos])
    {   
        dep[i] = dep[pos] + 1;dfs1(i);
        if (lv[pos] < lv[i] + 1) lson[pos] = i,lv[pos] = lv[i] + 1;
    }
}
void dfs2(int pos)
{
    if (lson[pos]) dfs2(lson[pos]),head[pos] = head[lson[pos]];
    for (auto &i : e[pos])
    {   
        if (i == lson[pos]) continue;
        dfs2(i);
        int j = head[pos],k = head[i];
        while (k != -1)
        {
            ans[w[k]] += dep[pos] * v[j];ans[w[j]] += dep[pos] * v[k];
            g[w[j]].push_back({w[k],ans[w[k]] - ans[w[j]]});v[j] += v[k];
            j = nxt[j];k = nxt[k];
        }
    }
    add_edge(pos,1,pos);
}
void dfs3(int pos,bool rt = 1)
{
    if (rt && lson[pos]) dfs3(lson[pos]);
    for (auto &i : g[pos]) ans[i.first] = ans[pos] + i.second,dfs3(i.first,0);
}
void dfs4(int pos)
{
    for (auto &i : e[pos]) ans[i] += dep[pos] + ans[pos],dfs4(i);
}
int main ()
{
    ios::sync_with_stdio(false);
    cin >> n;int t1,rt = 0;
    for (int i = 1;i <= n;i++)
    {
        cin >> t1;if (t1) e[t1].push_back(i);else rt = i;
    }
    memset(head,-1,sizeof(head));memset(nxt,-1,sizeof(nxt));
    dep[rt] = 1;dfs1(rt);dfs2(rt);dfs3(rt);dfs4(rt);
    for (int i = 1;i <= n;i++) cout << ans[i] << ' ';
    return 0;
}
```

---

## 作者：Durant_Lee (赞：5)

又来水题解了。。。
[欢迎来我的blog逛逛~](https://blog.csdn.net/dream_lolita)

给定一棵$n$个节点的有根树，定义$f(x,y)$（其中$y$是$x$的祖先）表示$y$后代中除$x$以外深度不大于$x$的节点数。定义$g(x)=\sum f(x,y)$。求所有$g(x)$。$n\leq 5\times 10^5$

一个比较$\text{naive}$的思路就是将节点按深度排序后一层一层做，用树链剖分解决这个东西可以做到$O(n\log^2 n)$，但是需要一定卡常技巧。我们可以考虑优化这个过程。

我们要求的东西可以表示成这个：
$$g(x)=\sum_{dep(y)\leq dep(x)} dep(lca(x,y))-dep(x)$$
等价于：
$$g(fa(x))+\sum_{dep(y)=dep(x)}dep(lca(x,y))-dep)(x)$$
观察到，如果我们先将这些节点按$dfs$序排序，对于第$i$个节点，它前面的节点与它的$lca$的深度是单调不降的。

那么我们可以维护一个单调栈，若相邻节点与当前节点的$lca$相同可以将相邻节点合并，因为显然之后它们的$lca$也是相同的，同样也不存在栈中间会合并的情况。这样每个深度下总的合并次数就是$O(点数)$的了。

总复杂度就是$O(n\log n)$，$\log$来自于求$lca$

因为求$lca$的次数比较多，如果使用$O(n\log n)$预处理，$O(1)$询问的欧拉序$lca$应该会更优秀。~~不过观察到空间比较紧就没搞了。~~

【参考代码】
```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

typedef long long ll;
const int N=5e5+10;
int n,rt,fc[20],Log[N];
ll ans[N];

namespace IO
{
	int read()
	{
		int ret=0;char c=getchar();
		while(!isdigit(c)) c=getchar();
		while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
		return ret;
	}
	void write(ll x){if(x>9)write(x/10);putchar(x%10^48);}
	void writesp(ll x){write(x);putchar(' ');}
}
using namespace IO;

namespace Tree
{
	int tot,ind;
	int head[N],dep[N],pos[N],fa[20][N];
	vector<int>st[N];
	struct Tway{int v,nex;}e[N<<1];
	void add(int u,int v)
	{
		e[++tot]=(Tway){v,head[u]};head[u]=tot;
		e[++tot]=(Tway){u,head[v]};head[v]=tot;
	}
	void dfs(int x)
	{
		pos[x]=++ind;
		for(int i=1;fc[i]<=dep[x];++i) fa[i][x]=fa[i-1][fa[i-1][x]];
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(v==fa[0][x]) continue;
			dep[v]=dep[x]+1;fa[0][v]=x;st[dep[v]].pb(v);dfs(v);
		}
	}
	int lca(int x,int y)
	{
		if(dep[x]<dep[y])swap(x,y);
		for(int i=0,t=dep[x]-dep[y];i<20;++i) 
			if(t&fc[i]) x=fa[i][x];
		for(int i=19;~i;--i) if(fa[i][x]^fa[i][y])
			x=fa[i][x],y=fa[i][y];
		return x==y?x:fa[0][x];
	}
}
using namespace Tree;

namespace DreamLolita
{
	struct Stack
	{
		int len,a[N],b[N],c[N];//a=id,b=dep,c=pos
		void clear(){len=0;}
		void push(int x,int y,int z){++len;a[len]=x;b[len]=y;c[len]=z;}
		void pop(){--len;}
		int topa(){return a[len];}
		int topb(){return b[len];}
		ll calctop(){return (ll)b[len]*(c[len]-c[len-1]);}
	}S;
	void initsomething()
	{
		fc[0]=1;for(int i=1;i<20;++i)fc[i]=fc[i-1]<<1;
		for(int i=2;i<N;++i)Log[i]=Log[i>>1]+1;
	}
	bool cmp(int x,int y){return pos[x]<pos[y];}
	void calc(const vector<int> &a)
	{
		ll res=0;S.clear();
		for(int i=0;i<(int)a.size();++i)
		{
			int x=a[i];
			if(!i) S.push(x,0,0);
			else
			{
				for(;;)
				{
					int y=lca(S.topa(),x);
					if(S.topb()<=dep[y]){S.push(x,dep[y]+1,i);break;}
					res-=S.calctop();S.pop();
				}
				res+=S.calctop();
			}
			ans[x]+=res;
		}
	}
	void solve()
	{
		n=read();
		for(int i=1,x;i<=n;++i) 
		{
			x=read();
			if(x) add(i,x); else rt=i;
		}
		initsomething();dfs(rt);
		for(int d=1;d<=n;++d)
		{
			sort(st[d].begin(),st[d].end(),cmp);
			for(int i=0;i<(int)st[d].size();++i) ans[st[d][i]]+=ans[fa[0][st[d][i]]]+d;
			calc(st[d]);reverse(st[d].begin(),st[d].end());calc(st[d]);
		}
		for(int i=1;i<=n;++i) writesp(ans[i]);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("CF860E.in","r",stdin);
	freopen("CF860E.out","w",stdout);
#endif
	DreamLolita::solve();
	return 0;
}
```

---

## 作者：ningago (赞：2)

令 $S_x$ 表示 $x$ 的子树：

$$g(x)=\sum_{x\in S_p,p\ne x}\sum_{y\in S_p,y\ne x}[dep_y\leq dep_x]$$

考虑对于每个点计算贡献次数，即：

$$g(x)=\sum_{y\ne x}[dep_y\leq dep_x]dep_{lca(x,y)}$$

关于 $dep,lca$ 的问题可以用长链剖分解决。

令 $v_{x, i}$ 表示 $x$ 对应长链内深度为 $i$ 的点构成的**集合**，则合并 $k$ 的两条子链 $x,y$ 相当于：

- 对 $v_{x,i}$ 中所有点的答案加上 $dep_k\cdot \sum_{j=dep_k+1}^i |v_{y,j}|$。
- $y$ 对 $x$ 的贡献同理。
- 合并 $v_{x,i},v_{y,i}$。

合并集合可以用类似 Kruskal 重构树的数据结构来实现，集合加相当于在重构树上打标记。

令 $l_x,l_y(l_x\geq l_y)$ 表示两条链的长度。现在唯一的问题是 $i>l_y$ 时的贡献不能直接遍历计算：

![](https://cdn.luogu.com.cn/upload/image_hosting/sglkjbxv.png)

此时可以对每条链维护一个懒标记集合 $lazy_{x,i}$，表示 $x$ 这条长链中，深度 $\geq i$ 的集合有 $lazy_{x,i}$ 的懒标记。每次合并链时，对需要合并的（$\leq l_y$ 的）集合进行标记下放即可。

由于合并时无法处理祖父之间的贡献，需要特殊计算。这是平凡的。

复杂度 $O(n)$。

```cpp
#define N 1200010
int n, root;
int h[N], e[N << 1], ne[N << 1], idx = -1;
void add_edge(int x, int y) { ne[++idx] = h[x], h[x] = idx, e[idx] = y; }
int tag[N], ls[N], rs[N], sz[N];
int dep[N], mxdep[N];
int ans[N]; bool vis[N];
std::vector <int> vec[N], dt[N];
int nodecnt;
int merge(int x, int y)
{
	int k = ++nodecnt;
	ls[k] = x, rs[k] = y;
	sz[k] = sz[x] + sz[y];
	return k;
}

void vecpushdown(int x, int tot)
{
	int sz = vec[x].size(), suf = 0;
	for(int i = sz - 1; i >= sz - tot; i--)
	{
		suf += dt[x][i];
		tag[vec[x][i]] += suf;
		dt[x][i] = 0;
	}
	if(sz != tot) dt[x][sz - tot - 1] += suf;
}

void dfs(int k, int sum)
{
	ans[k] += sum;
	sum += dep[k];
	mxdep[k] = dep[k]; int hson = 0;
	for(int i = h[k]; ~i; i = ne[i])
	{
		int nx = e[i]; dep[nx] = dep[k] + 1;
		dfs(nx, sum); if(!hson || mxdep[nx] > mxdep[hson]) hson = nx;
		ckmax(mxdep[k], mxdep[nx]);
	}
	if(!hson) { vec[k].push_back(k), dt[k].push_back(0); return; }
	std::swap(vec[k], vec[hson]); std::swap(dt[k], dt[hson]);
	for(int _ = h[k]; ~_; _ = ne[_])
	{
		int nx = e[_]; if(nx == hson) continue;
		int szl = vec[k].size(), szr = vec[nx].size();
		vecpushdown(nx, szr);
		vecpushdown(k , szr);
		for(int i = szr - 1, j = szl - 1, sufl = 0, sufr = 0; ~i; i--, j--)
		{
			int x = vec[k][j], y = vec[nx][i];
			sufl += sz[x]; sufr += sz[y];
			tag[x] += sufr * dep[k], tag[y] += sufl * dep[k];
			vec[k][j] = merge(x, y);
			if(!i && j) dt[k][j - 1] += sufr * dep[k];
		}
	}
	vec[k].push_back(k), dt[k].push_back(0);
}

void pd(int k)
{
	if(!ls[k] && !rs[k]) ans[k] += tag[k];
	if(ls[k]) tag[ls[k]] += tag[k], pd(ls[k]);
	if(rs[k]) tag[rs[k]] += tag[k], pd(rs[k]);
}

void solve()
{
	memset(h, idx = -1, sizeof(h));
	nodecnt = n = read();
	for(int i = 1, x; i <= n; i++)
	{
		x = read();
		sz[i] = 1;
		if(x) add_edge(x, i);
		else root = i;
	}
	dep[root] = 1; dfs(root, 0);
	vecpushdown(root, vec[root].size());
	for(auto t : vec[root]) pd(t);
	for(int i = 1; i <= n; i++) print(ans[i], ' '); putc('\n');
}

```

---

## 作者：Hoks (赞：2)

## 前言
注意此题解给出的解不优，如果有机会我会补长剖做法的（现在还不太会长剖喵）。

顺手宣传手[树剖博客](https://www.luogu.com.cn/blog/Hok/cute-tree-decomposition)。
## 思路分析
这题还是挺一眼的吧。

因为深度更深的点对深度更浅的点不会有贡献，所以很自然的想到先算深的点。

所以直接上 bfs 把深度相同的一层点剥下来。

至于计数方面的问题，只需要像 P4211 一样 $1\rightarrow u$ 路径 $+1$ 即可。

复杂度 $O(n\log^2n)$，略卡常。
## 代码
```cpp
#include <bits/stdc++.h>
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=500010;
struct node
{int v,nxt;}e[N<<1];
int n,m,tot,cnt,rt,cur;
int head[N],top[N],dfn[N],id[N],ed[N];
int fa[N],si[N],son[N],dep[N],ans[N];
int t[N<<2],lz[N<<2];
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void){
    int u(0),t(1);char fc(getchar());
    while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
    while(isdigit(fc)) u=(u<<1)+(u<<3)+(fc^48),fc=getchar();
    return u*t;
}
inline void print(int u)
{
	if(u<0) putchar('-'),u=-u;
	if(u>9) print(u/10);
	putchar(u%10+'0');
}
inline bool cmp(pair<int,int> x,pair<int,int> y){return x.first>y.first;}
inline void add(int u,int v){if(u==0) return;e[++tot].v=v,e[tot].nxt=head[u],head[u]=tot;}
inline void dfs1(int u,int ff)
{
	dep[u]=dep[ff]+1,si[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==ff) continue;
		dfs1(v,u);si[u]+=si[v];
		if(si[v]>si[son[u]]) son[u]=v;
	}
}
inline void dfs2(int u,int topf)
{
	top[u]=topf,dfn[u]=++cnt,id[cnt]=u;
	if(son[u]) dfs2(son[u],topf);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==son[u]||v==fa[u]) continue;
		dfs2(v,v);
	}ed[u]=cnt;
}
inline void pushdown(int p,int l,int r)
{
	lz[ls]+=lz[p],lz[rs]+=lz[p];
	t[ls]+=(mid-l+1)*lz[p],t[rs]+=(r-mid)*lz[p];lz[p]=0;
}
inline void modify(int p,int l,int r,int s,int e)
{
	if(l>=s&&r<=e) return lz[p]++,t[p]+=r-l+1,void();
	pushdown(p,l,r);
	if(mid>=s) modify(ls,l,mid,s,e);
	if(mid<e) modify(rs,mid+1,r,s,e);
	t[p]=t[ls]+t[rs];
}
inline int query(int p,int l,int r,int s,int e)
{
	if(l>=s&&r<=e) return t[p];
	pushdown(p,l,r);int res=0;
	if(mid>=s) res=query(ls,l,mid,s,e);
	if(mid<e) res+=query(rs,mid+1,r,s,e);
	return res;
}
inline void modify(int u){while(u) modify(1,1,n,dfn[top[u]],dfn[u]),u=fa[top[u]];}
inline int query(int u){int res=0;u=fa[u];while(u) res+=query(1,1,n,dfn[top[u]],dfn[u])-dfn[u]+dfn[top[u]]-1,u=fa[top[u]];return res;}
inline void bfs()
{
	queue<int>q;q.push(rt);
	while(!q.empty())
	{
		queue<int>g;cur++;
    	while(!q.empty())
        {
        	if(dep[q.front()]!=cur) break;
            int u=q.front();q.pop();g.push(u);
            for(int i=head[u];i;i=e[i].nxt) q.push(e[i].v);
            modify(u);
        }
        while(!g.empty()) ans[g.front()]=query(g.front()),g.pop();
	}
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) fa[i]=read(),rt=fa[i]==0?i:rt,add(fa[i],i);
	dfs1(rt,0),dfs2(rt,rt);bfs();
	for(int i=1;i<=n;i++) print(ans[i]),putchar(' ');
	return 0;
}
```


---

## 作者：nofind (赞：2)

## [题意](https://www.luogu.com.cn/problem/CF860E)

首先$g(x)=\sum\limits_{dep_y\leqslant dep_x,y\not =x}dep_{lca(x,y)}=g(fa_x)+dep_{fa_x}+\sum\limits_{dep_y=dep_x,y\not= x}dep_{lca(x,y)}$。

于是我们有个$O(n\log^2 n)$的做法：每次处理同深度的点，用[$LNOI2014\ LCA$](https://www.luogu.com.cn/blog/nofind/p4211-lnoi2014lca-shu-shang-ci-fen-li-xian-post)的树剖做法解决。

虽然上面的方法能过，但是并没有用到处理的节点的深度相同这样的性质，我们可以进一步观察：  
如果我们将节点按照$dfs$序进行排序，那么对于一个点$x$，其与之前的点的$lca$的深度是单调不降的，这个画个图就很显然，不证明了。 

于是我们从左往右和从右往左扫一遍，求出点$a_x$的答案，中途维护一个栈。栈中存的是一段点，这些点与上个点$a_{x-1}$的$lca$都相同，我们选最靠后的点作为代表点并记录与$a_{x-1}$的$lca$的深度。

如果栈顶的点与$a_x$的$lca$（设为$y$）的深度小于栈顶存的深度，那么我们要弹栈，一直到不能弹为止，此时弹掉的点与$a_x$的$lca$都为$y$，我们向栈中新加入一个点即可。

弹栈的中途维护答案即可算出对$a_x$答案的贡献。

code:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e5+10;
int n,root;
int ans[maxn];
inline int read()
{
    char c=getchar();int res=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
    return res*f;
}
int cnt_edge;
int head[maxn];
struct edge{int to,nxt;}e[maxn<<1];
inline void add_edge(int u,int v)
{
	e[++cnt_edge]=(edge){v,head[u]};
	head[u]=cnt_edge;
}
int size[maxn],son[maxn],pre[maxn],dep[maxn];
vector<int>ve[maxn];
void dfs1(int x,int fa)
{
	size[x]=1;
	ve[dep[x]=dep[pre[x]=fa]+1].push_back(x);
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==fa)continue;
		dfs1(y,x);size[x]+=size[y];
		if(size[son[x]]<size[y])son[x]=y;
	}
}
int tim;
int dfn[maxn],pos[maxn],top[maxn];
void dfs2(int x,int tp)
{
	top[x]=tp;
	pos[dfn[x]=++tim]=x;
	if(son[x])dfs2(son[x],tp);
	for(int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==pre[x]||y==son[x])continue;
		dfs2(y,y);
	}
}
inline int lca(int x,int y)
{
	while(top[x]!=top[y])
		if(dep[top[x]]>dep[top[y]])x=pre[top[x]];
		else y=pre[top[y]];
	return dep[x]<dep[y]?x:y;
}
int tp;
struct node
{
	int x,d,pos;
}sta[maxn];
inline int calc()
{
	if(!tp)return 0;
	return (sta[tp].pos-sta[tp-1].pos)*sta[tp].d;
}
inline void solve(vector<int> ve)
{
	tp=0;
	int res=0;
	for(unsigned int i=0;i<ve.size();i++)
	{
		int x=ve[i];
		if(!i)sta[++tp]=(node){x,0,0};
		else
		{
			while(2333)
			{
				int y=lca(sta[tp].x,x);
				if(dep[y]>=sta[tp].d){sta[++tp]=(node){x,dep[y],i};break;}
				res-=calc();
				tp--;
			}
			res+=calc();
		}
		ans[x]+=res;
	}
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		int x=read();
		if(x)add_edge(x,i),add_edge(i,x);
		else root=i;
	} 
	dfs1(root,0),dfs2(root,root);
	for(int d=1;d<=n;d++)
	{
		for(unsigned int i=0;i<ve[d].size();i++)ans[ve[d][i]]+=ans[pre[ve[d][i]]]+d-1;
		solve(ve[d]);
		reverse(ve[d].begin(),ve[d].end());
		solve(ve[d]);
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
	return 0;
}
```


---

## 作者：Unnamed114514 (赞：0)

来点虚树。

翻译一下题意：

$$ans_u=\sum\limits_{u\in Son_v}\sum\limits_{p\in Son_v}[dep_p\le dep_u]-dep_u$$

显然这个不等号的约束太丑陋了，容易发现在题目的限制下 $dep_p\le dep_u$，因此 $u$ 到根的贡献会多算一次。

转化为求每个点的贡献，下面处理式子的时候 $dep_u$ 省掉，最后减去即可。

$$ans_u=\sum\limits_{dep_v\le dep_u} dep_{LCA(u,v)}$$

我们会发现，对于 $dep_v<dep_u$ 的点，它们都会对 $fa_u$ 造成贡献，并且 $LCA(v,fa_u)=LCA(v,u)$，那么我们可以只用求深度和它相等的点了。

$$ans_u=ans_{fa_u}+\sum\limits_{dep_v=dep_u} dep_{LCA(u,v)}$$

剩下的就非常套路了，对于每个深度，把虚树建出来，简单换根处理一下就行了。

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=5e5+5;
int n,m,tot,root,dfn[N],dep[N],a[N<<1],ans[N],siz[N],son[N],top[N],p[N],f[N];
vector<int> G[N],d[N],g[N];
void dfs1(int u){
	siz[u]=1;
	d[dep[u]].emplace_back(u);
	for(auto v:G[u]){
		dep[v]=dep[u]+1;
		dfs1(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int t){
	dfn[u]=++tot,top[u]=t;
	if(son[u]) dfs2(son[u],t);
	for(auto v:G[u]){
		if(v==son[u]) continue;
		dfs2(v,v);
	}
}
int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]) swap(u,v);
		v=p[top[v]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	return u;
}
void dfs(int u){
	for(auto v:G[u]){
		ans[v]+=ans[u];
		dfs(v);
	}
}
bool cmp(int a,int b){ return dfn[a]<dfn[b]; }
void dp(int u){
	if(dep[u]==m) f[u]=1;
	for(auto v:g[u]){ 
		dp(v);
		f[u]+=f[v];
	}
}
void solve(int u,int s){
	if(dep[u]==m) ans[u]+=(s+dep[u]);
	for(auto v:g[u]) solve(v,s+(f[u]-f[v])*dep[u]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>p[i];
		if(!p[i]) root=i;
		else G[p[i]].emplace_back(i);
	}
	dep[root]=1,dfs1(root),dfs2(root,root);
	for(int i=1;i<=n;++i){
		if(d[i].empty()) continue;
		m=i;
		tot=0;
		for(auto p:d[i]) a[++tot]=p;
		sort(a+1,a+tot+1,cmp);
		for(int j=1;j<d[i].size();++j) a[++tot]=LCA(a[j],a[j+1]);
		sort(a+1,a+tot+1,cmp);
		tot=unique(a+1,a+tot+1)-a-1;
		for(int j=2;j<=tot;++j) g[LCA(a[j-1],a[j])].emplace_back(a[j]);
		dp(a[1]);
		solve(a[1],0);
		for(int j=1;j<=tot;++j){
			f[a[j]]=0;
			g[a[j]].clear(),g[a[j]].shrink_to_fit();
		}
	}
	dfs(root);
	for(int i=1;i<=n;++i) cout<<ans[i]-dep[i]<<' ';
	cout<<endl;
	return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

## 前言

学生 15 min 写完 $O(n \log^2 n)$ 树剖，但是用 35 min 疯狂卡常怎么说。

## 思路分析

不知道怎么说起……感觉这道题小时候抱过我。

首先要看懂题，要求的是 $x$ 的每棵祖先子树中，不在 $x$ 子树中的深度比 $x$ 小的点个数之和，一个点可以被重复计算多次。

然后就可以 bfs 时按深度做 $1 \to x$ 的树链加和树链求和。

可能有点卡常。最后卡成了这样：[here.](https://codeforces.com/contest/860/submission/302569269)

### 代码实现

```cpp
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void){
    int u(0),t(1);char fc(getchar());
    while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
    while(isdigit(fc)) u=(u<<1)+(u<<3)+(fc^48),fc=getchar();
    return u*t;
}
inline void print(long long u){
	if(u<0) putchar('-'),u=-u;
	if(u>9) print(u/10);
	putchar(u%10+'0');
}
using namespace std;
int n,x,rt,rot,ord[500005];
long long ans[500005];
int head[500005],nxt[500005],target[500005],tot;
inline void add(int x,int y){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	target[tot]=y;
}
int siz[500005],dfn[500005],rnk[500005],f[500005],top[500005],hson[500005],dep[500005],cnt;
inline void dfs1(int x,int fa){
	siz[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		int y=target[i];
		if(y==fa) continue;
		f[y]=x;
		dep[y]=dep[x]+1;
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[hson[x]]<siz[y]) hson[x]=y;
	}
}
inline void dfs2(int x,int t){
	top[x]=t;
	cnt++;
	dfn[x]=cnt;
	rnk[cnt]=x;
	if(!hson[x]) return;
	dfs2(hson[x],t);
	for(int i=head[x];i;i=nxt[i]){
		int y=target[i];
		if(y==f[x] || y==hson[x]) continue;
		dfs2(y,y);
	}
}
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
long long val[2000005];
int ls[2000005],rs[2000005],tag[2000005];
inline void modify(int l,int r,int ql,int qr,int k,int x){
	if(ql<=l && r<=qr){
		val[x]+=1ll*(r-l+1)*k;
		tag[x]+=k;
		return;
	}
	int mid=(l+r)>>1;
	if(tag[x]){
		val[ls(x)]+=1ll*(mid-l+1)*tag[x];
		val[rs(x)]+=1ll*(r-mid)*tag[x];
		tag[ls(x)]+=tag[x];
		tag[rs(x)]+=tag[x];
		tag[x]=0;
	}
	if(ql<=mid) modify(l,mid,ql,qr,k,ls(x));
	if(qr>=mid+1) modify(mid+1,r,ql,qr,k,rs(x));
	val[x]=val[ls(x)]+val[rs(x)];
}
inline long long query(int l,int r,int ql,int qr,int x){
	if(ql<=l && r<=qr) return val[x];
	int mid=(l+r)>>1;
	if(tag[x]){
		val[ls(x)]+=1ll*(mid-l+1)*tag[x];
		val[rs(x)]+=1ll*(r-mid)*tag[x];
		tag[ls(x)]+=tag[x];
		tag[rs(x)]+=tag[x];
		tag[x]=0;
	}
	long long ans(0);
	if(ql<=mid) ans+=query(l,mid,ql,qr,ls(x));
	if(qr>=mid+1) ans+=query(mid+1,r,ql,qr,rs(x));
	return ans;
}
inline void modify_line(int x){
	while(x){
		modify(1,n,dfn[top[x]],dfn[x],1,rt);
		x=f[top[x]];
	}
}
inline long long query_line(int x){
	long long ans(0);
	while(x){
		ans+=query(1,n,dfn[top[x]],dfn[x],rt);
		x=f[top[x]];
	}
	return ans;
}
int cur;
inline void bfs(){
	queue<int> q;
	q.push(rot);
	while(!q.empty()){
		queue<int> p;
		cur++;
    	while(!q.empty()){
        	if(dep[q.front()]!=cur) break;
            int x=q.front();
            q.pop();
            p.push(x);
            for(int i=head[x];i;i=nxt[i]){
            	q.push(target[i]);
            }
            modify_line(x);
        }
        while(!p.empty()){
        	ans[p.front()]=query_line(p.front())-dep[p.front()];
        	p.pop();
        }
	}
}
signed main(){
	n=read();
	for(register int i=1;i<=n;i++){
		x=read();
		if(!x) rot=i;
		else add(x,i);
	}
	dfs1(rot,0);
	dfs2(rot,rot);
	rt=1;
	for(int i=1;i<=n;i++){
		dep[i]++;
		ord[i]=i;
	}
	bfs();
	for(int i=1;i<=n;i++){
		print(ans[i]);
		putchar(' ');
	}
	return 0;
}
```

---

## 作者：letitdown (赞：0)

转化一下题意：

$f(x,y)$ 表示 $y$ 子树中深度小于等于 $x$ 的有多少个点（包括 $x$ ）；

$g(x)$ 表示 $x$ 的所有祖先节点的儿子节点中深度小于等于 $x$ 的点有多少个（这些点可以重复）。

于是我们发现如果一个点不大于另一个点的深度，那么这个点对另一个点的贡献就是这两个点从自己到根节点路径上有多少个点是相同的，即有多少个共同祖先。

那么我们就可以把贡献累加到祖先身上，查询一个点的答案就是这个点所有祖先之前被累加的贡献之和。

那么还有一个问题，如何使深度小的点优先造成贡献？

我们把点按照深度排序，利用树链剖分依次将贡献累加到祖先节点上即可。

如果使用线段树，常数较大，会出现 TLE 的情况（~~其实只有我自己常数大吧~~）

那么我们可以使用常数较小的树状数组实现区间加，区间求和（有兴趣的同学可以去看胡小兔 julao 的博客 orz ）

那么此题就完美解决了~

（不要在意我奇怪的变量名，因为一开始用的线段树所以懒得改名字了）

## Code
```cpp
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
namespace EMT{
	typedef long long ll;typedef double db;//(double)clock() / (double)CLOCKS_PER_SEC;
	#define pf printf
	#define F(i,a,b) for(int i=a;i<=b;i++)
	#define D(i,a,b) for(int i=a;i>=b;i--)
	inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
	inline void file(){auto it=freopen("in.in","r",stdin);it=freopen("my.out","w",stdout);it++;}
	inline int max(int a,int b){return a>b?a:b;}inline int min(int a,int b){return a<b?a:b;}
	inline void pi(ll x){pf("%lld ",x);}inline void pn(){pf("\n");}
	const int N=5e5+10;
	int rt,co,head[N],n,dfn[N],siz[N],p[N],ti,fa[N],deep[N],top[N],son[N];ll ans[N];
	struct node{int next,to;}e[N];
	inline void add(int next,int to){e[++co]=(node){head[next],to},head[next]=co;}
	inline void dfs1(int k,int fa){
		siz[k]=1;
		for(int i=head[k],j;i;i=e[i].next)if((j=e[i].to)!=fa){
			deep[j]=deep[k]+1;
			dfs1(j,k);siz[k]+=siz[j];
			if(siz[son[k]]<siz[j])son[k]=j;
		}
	}
	inline void dfs2(int k,int tp){
		top[k]=tp;dfn[k]=++ti;
		if(!son[k])return;
		dfs2(son[k],tp);
		for(int i=head[k];i;i=e[i].next)
			if(e[i].to!=son[k]&&e[i].to!=fa[k])
				dfs2(e[i].to,e[i].to);
	}
	struct seg{
		ll sum1[N],sum2[N];
		inline void add(int x,int v){for(int i=x;i<=n;i+=i&-i)sum1[i]+=v,sum2[i]+=v*x;}
		inline void change(int l,int r){add(l,1),add(r+1,-1);}
		inline ll ask(int x){ll ans=0;for(int i=x;i;i-=i&-i)ans+=1ll*(x+1)*sum1[i]-sum2[i];return ans;}
		inline ll ask(int l,int r){return ask(r)-ask(l-1);}
	}segm;
	inline void change(int x){
		while(x)segm.change(dfn[top[x]],dfn[x]),x=fa[top[x]];
	}
	inline ll ask(int x){
		ll ans=0;
		while(x)ans+=segm.ask(dfn[top[x]],dfn[x]),x=fa[top[x]];
		return ans;
	}
	inline short main(){
		n=read();
		F(i,1,n){
			fa[i]=read();
			if(!fa[i])rt=i;else add(fa[i],i);
		}dfs1(rt,0);dfs2(rt,rt);
		F(i,1,n)p[i]=i;
		std::sort(p+1,p+n+1,[](int i,int j){return deep[i]<deep[j];});
		int last=2;
		F(i,2,n){
			change(fa[p[i]]);
			if(deep[p[i]]!=deep[p[i+1]]){
				while(deep[p[last]]==deep[p[i]])ans[p[last]]=ask(fa[p[last]]),last++;
			}
		}
		F(i,1,n)pi(ans[i]);
		return 0;
	}
}
signed main(){return EMT::main();}

```

---

## 作者：Logey (赞：0)

可以发现，对点 $u$ 的，只需要考虑那些深度小于等于 $deep_u$ 的点对它的贡献，并且每个点 $v$ 的贡献是使得 $father_v$ 到 $root$ 这条路径上的点的 $f$ 函数 $+1$，同时查询一个点的答案就是到根节点的路径求和。  
所以我们可以拿树剖来维护，按照深度一层一层加点（这里使用BFS就可以过，而直接对深度排序是过不去的），这样的时间复杂度是 $O(n \log^2 n)$ 的，稍微卡一卡常就可以通过。  

```cpp
 
typedef long long ll;
 
const int MAXN = 5e5 + 7;
 
struct Node;
struct Edge { int t, next; } edge[MAXN << 1];

int n, head[MAXN], cnt, dfn[MAXN], top[MAXN], deep[MAXN], ro, f[MAXN], size[MAXN], son[MAXN], q[MAXN], h, t = -1, g[MAXN];
ll val[MAXN];
char ch;

Node *newNode(int l, int r, Node *lc, Node *rc);

struct Node {
	int l, r, mid;
	Node *lc, *rc;
	ll sum; int tag;
	
	static Node *build(int l, int r) {
		if (l == r) return newNode(l, r, NULL, NULL);
		int mid = l + (r - l) / 2;
		return newNode(l, r, build(l, mid), build(mid + 1, r));
	}
	
	void add(int le, int ri) {
		if (le == l && ri == r) {
			tag++; sum += r - l + 1;
			return;
		}
		pushDown();
		if (ri <= mid) lc->add(le, ri);
		else if (le > mid) rc->add(le, ri);
		else lc->add(le, mid), rc->add(mid + 1, ri);
		sum = lc->sum + rc->sum;
	}
	
	void plus(ll d) {
		sum += 1ll * (r - l + 1ll) * d, tag += d; 
	}
	
	void pushDown() {
		if (tag) lc->plus(tag), rc->plus(tag), tag = 0;
	}
	
	ll query(int le, int ri) {
		if (le == l && r == ri) return sum;
		pushDown();
		if (ri <= mid) return lc->query(le, ri);
		else if (le > mid) return rc->query(le, ri);
		else return lc->query(le, mid) + rc->query(mid + 1, ri);
	}
} *root, pool[MAXN << 1], *tail = pool;

Node *newNode(int l, int r, Node *lc, Node *rc) {
	Node *ret = ++tail;
	ret->l = l, ret->r = r, ret->mid = l + (r - l) / 2;
	ret->lc = lc, ret->rc = rc;
	ret->sum = ret->tag = 0;
	return ret;
}
 
inline void add(int u, int v) {
	edge[++cnt] = (Edge){v, head[u]}; head[u] = cnt;
}
 
inline void init(int u, int pre) {
	f[u] = pre;
	deep[u] = deep[pre] + 1;
	size[u] = 1;
	int v;
	PE(e, u) {
		v = edge[e].t;
		init(v, u);
		size[u] += size[v];
		if (size[v] > size[son[u]]) son[u] = v;
	}
}
 
inline void split(int u, int tip) {
	top[u] = tip;
	static int ts = 0;
	dfn[u] = ++ts;
	if (son[u]) split(son[u], tip);
	int v;
	PE(e, u) {
		v = edge[e].t;
		if (v == son[u]) continue;
		split(v, v);
	}
}
 
inline char nc(){
    #define SIZE 300000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}
 
inline void read(int &x){
    ch = nc();x = 0;
    while(!isdigit(ch)) ch = nc();
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = nc();
}
 
inline void write(ll x) {
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
int main() {
	read(n);
	
	int u;
	
	rep(i, 1, n) {
		read(u);
		if (!u) ro = i;
		else add(u, i);
	}
	
	init(ro, 0);
	split(ro, ro);
	root = Node::build(1, n);
	
	int now = 0, tail, v;
	q[++t] = ro;
	
	while (h <= t) {
		now++;
		tail = 0;
		
		while (deep[q[h]] == now) {
			u = q[h]; h++;
			g[++tail] = u;
			
			PE(e, u) {
				v = edge[e].t;
				q[++t] = v;
			}
			
			v = f[u];
			for (;v; v = f[top[v]]) root->add(dfn[top[v]], dfn[v]);
		}
		
		rep(i, 1, tail) {
			u = v = g[i];
			for (;v;v = f[top[v]]) val[u] += root->query(dfn[top[v]], dfn[v]);
		}
	}
	
	rep(i, 1, n) write(val[i]), putchar(' ');
	return 0;
}
```

---

## 作者：ywh666 (赞：0)

树剖加上各种奇奇怪怪的卡常技巧居然A掉了这题。。。

由浅入深每次加入同一深度所有点，再用树剖统计。

区间修改区间查询。

毒瘤无比的代码


```#include <bits/stdc++.h>
using namespace std;
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
template <class T> void read(T &x){ x = 0; int f = 1; char ch = getchar(); while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); } while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar(); x *= f; }
const int maxn=1000005;
int n,tid[maxn],top[maxn],ran[maxn],son[maxn],cnt,head[maxn],root,siz[maxn],idx,dep[maxn],fa[maxn];
long long ans[maxn],tree[maxn<<2],lazy[maxn<<2];
queue<int>q;
struct edge{int to,next;
}e[maxn<<1];
void dfs1(int u,int pre)
{
    dep[u]=dep[pre]+1;
    siz[u]=1;
    fa[u]=pre;
    for(int i=head[u];i;i=e[i].next)
    {
        if(e[i].to==pre)continue;
        dfs1(e[i].to,u);
        siz[u]+=siz[e[i].to];
        if(son[u]==-1||siz[e[i].to]>siz[son[u]])
        {
            son[u]=e[i].to;
        }
    }
}
void dfs2(int u,int t)
{
    top[u]=t;
    tid[u]=++idx;
    ran[idx]=u;
    if(son[u]==-1)return ;
    dfs2(son[u],t);
    for(int i=head[u];i;i=e[i].next)
    {
        if(e[i].to==fa[u]||e[i].to==son[u])continue;
        dfs2(e[i].to,e[i].to);
    }
}
void add(int a,int b)
{
    e[cnt].to=b;
    e[cnt].next=head[a];
    head[a]=cnt++;
}
void pushdown(int l,int r,int rt)
{
    if(!lazy[rt])return ;
    int mid=(l+r)>>1;
    tree[rt<<1]+=(long long)lazy[rt]*(mid-l+1);
    tree[rt<<1|1]+=(long long)lazy[rt]*(r-mid);
    lazy[rt<<1]+=lazy[rt];
    lazy[rt<<1|1]+=lazy[rt];
    lazy[rt]=0;
}
void update(int L,int R,int l,int r,int rt)
{
    if(L<=l&&R>=r)
    {
        tree[rt]+=(r-l+1);
        lazy[rt]++;
        return ;
    }
    pushdown(l,r,rt);
    int mid=(l+r)>>1;
    if(L<=mid)update(L,R,lson);
    if(R>mid)update(L,R,rson);
    tree[rt]=tree[rt<<1]+tree[rt<<1|1];
}
void change(int u)
{
    while(u)
    {
        update(tid[top[u]],tid[u],1,n,1);
        u=fa[top[u]];
    }
}
long long query(int L,int R,int l,int r,int rt)
{
    if(L<=l&&R>=r)return tree[rt];
    pushdown(l,r,rt);
    int mid=(l+r)>>1;
    long long as=0;
    if(L<=mid)as+=query(L,R,lson);
    if(R>mid)as+=query(L,R,rson);
    return as;
}
void getans(int u)
{
    int x=u;
    u=fa[u];
    while(u)
    {
        ans[x]+=query(tid[top[u]],tid[u],1,n,1);
        ans[x]-=(tid[u]-tid[top[u]]+1);
        u=fa[top[u]];
    }
}
void write(long long x)
{
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
int main()
{
    memset(son,-1,sizeof(son));
    read(n);cnt=1;idx=0;
    int a;
    for(int i=1;i<=n;++i)
    {
        read(a);
        if(a==0){root=i;}
        else add(a,i);
    }if(n==1){puts("0");return 0;
		}
    dfs1(root,0);
    dfs2(root,root);
    q.push(root);
    int nowdep=0;
    while(!q.empty())
    {
        queue<int>g;
        nowdep++;
        while(dep[q.front()]==nowdep)
        {
            int u=q.front();q.pop();g.push(u);
            for(int i=head[u];i;i=e[i].next)
            {
                q.push(e[i].to);
            }
            change(u);
        }
        while(!g.empty())
        {
            int u=g.front();g.pop();
            getans(u);
        }
    }
    for(int i=1;i<=n;++i)write(ans[i]),putchar(' ');
}
//不过听说好像有nlogn的解法才是正解。。。

---

