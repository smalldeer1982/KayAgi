# Blood Cousins

## 题目描述

### 题面描述

有一个家族关系森林，描述了 $n$（$1\leq n\leq 10 ^ 5$）人的家庭关系，成员编号为 $1$ 到 $n$ 。

如果 $a$ 是 $b$ 的父亲，那么称 $a$ 为 $b$ 的 $1$ 级祖先；如果 $b$ 有一个 $1$ 级祖先，$a$ 是 $b$ 的 $1$ 级祖先的 $k-1$ 级祖先，那么称 $a$ 为 $b$ 的 $k$ 级祖先。

家庭关系保证是一棵森林，树中的每个人都至多有一个父母，且自己不会是自己的祖先。

如果存在一个人 $z$ ，是两个人 $a$ 和 $b$ 共同的 $p$ 级祖先：那么称 $a$ 和 $b$ 为 $p$ 级表亲。

$m$（$1\leq m\leq 10 ^ 5$）次询问，每次询问给出一对整数 $v$ 和 $p$，求编号为 $v$ 的人有多少个 $p$ 级表亲。

## 样例 #1

### 输入

```
6
0 1 1 0 4 4
7
1 1
1 2
2 1
2 2
4 1
5 1
6 1
```

### 输出

```
0 0 1 0 0 1 1 
```

# 题解

## 作者：kradcigam (赞：28)

无任何高级数据结构。

本题分为两部分：

1. 一部分是求出树上 $k$ 级祖先，直接倍增跳就可以。

2. 另一部分是求出树上 $k$ 级子孙的数量，这一部分比较复杂。

    首先一个点的 $k$ 级子孙的深度显然都是一样的，因为是在同一子树内，所以，如果我们把 $dep$ 为 $x$ 的点的 dfs 序从小到大存起来就会发现它们是连续的一段区间。

    把它们存起来之后，问题就变成了统计一个单调递增的序列中数值在 $l\sim r$ 内的数的个数。这个问题我们可以二分解决，我们可以二分出小于 $r$ 的数的最大的位置，求出可行答案的右端点，再二分出左端点就可以了。

```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
template<typename T>inline void write(T x){
    unsigned long long y=0;T l=0;
    if(x<0)x=-x,putchar(45);
    if(!x){putchar(48);return;}
    while(x){y=y*10+x%10;x/=10;l++;}
    while(l){putchar(y%10+48);y/=10;l--;}
}
template<typename T>inline void writeln(T x){write(x);puts("");}
template<typename T>inline void writes(T x){write(x);putchar(32);}
const int N=1e6+10;
int fa[10][N],dep[N],cnt,l[N],r[N],h[N],a[N],t[N],tot,hd[N],nxt[N],to[N];
inline void add(int x,int y){
	to[++tot]=y;
	nxt[tot]=hd[x];
	hd[x]=tot;
}
void dfs(int x){
	l[x]=++cnt;
	a[x]=++h[dep[x]];
	for(int i=hd[x];i;i=nxt[i])dfs(to[i]);
	r[x]=cnt;
}
signed main(){
	int n=read();
	F(i,1,n){
		fa[0][i]=read();
		if(!fa[0][i]){
			dep[i]=1;
			continue;
		}
		add(fa[0][i],i);
		dep[i]=dep[fa[0][i]]+1;
		F(j,1,9)fa[j][i]=fa[j-1][fa[j-1][fa[j-1][fa[j-1][i]]]];
	}
	F(i,1,n)
		if(!fa[0][i])dfs(i);
	F(i,2,n)h[i]+=h[i-1];
	F(i,1,n)t[h[dep[i]-1]+a[i]]=l[i];
	int q=read();
	while(q--){
		int x=read(),k=read(),z=dep[x];
		DF(i,9,0){
			int z=(1<<(i<<1));
			if(k>=z)k-=z,x=fa[i][x];
			if(k>=z)k-=z,x=fa[i][x];
			if(k>=z)k-=z,x=fa[i][x];
		}
		int l=h[z-1],r=h[z]+1;
		while(l+1<r){
			int mid=(l+r)>>1;
			if(mid<0)break;
			if(t[mid]<::l[x])l=mid;
			else r=mid;
		}
		int kl=l+1,kr=h[z]+1;
		while(kl+1<kr){
			int kmid=(kl+kr)>>1;
			if(t[kmid]<=::r[x])kl=kmid;
			else kr=kmid;
		}
		writes(kl-l-1);
	}
	return 0;
}
```

---

## 作者：Farkas_W (赞：27)

$$\text{关于本题}$$

$\quad$ $Dsu$ $on$ $Tree$模板题，没有做过的可以做做[CF600E Lomsat gelral](https://www.luogu.com.cn/problem/CF600E)，也是一道模板题，下面就简单讲讲树上启发式合并 ($DSU$ $on$ $Tree$)算法，如果有不懂的可以提出来。

$\quad$本题链接：[CF208E Blood Cousins](https://www.luogu.com.cn/problem/CF208E)

### 思路：

$\quad$这题的思路几乎和[CF570D Tree Requests](https://www.luogu.com.cn/problem/CF570D)一样，只需要稍微修改一下，因为是找一个点与多少个点拥有共同的 $K$ 级祖先，那么我们就可以先把它的 $K$ 级祖先找出来(使用倍增)，然后在找这个点有几个 $K$ 级后代，或者用深度表示成 $dep_x+k$ ，注意这个图不是连通的，每次要清空数组。

$$\text{关于树上启发式合并(Lsu)前置知识}$$

$\quad$学这个之前需要对树上操作、 $dfs$ 序和轻重链剖分等知识有一定了解，最好已经掌握了树链剖分。

$$\text{算法思想}$$

$\quad$树上启发式合并 ($DSU$ $on$ $Tree$)，是一个在 $O(nlogn)$ 时间内解决许多树上问题的有力算法，对于某些树上离线问题可以速度大于等于大部分算法且更易于理解和实现。

$\quad$先想一下暴力算法，对于每一次询问都遍历整棵子树，然后统计答案，最后再清空cnt数组，最坏情况是时间复杂度为 $O(n^2)$ ，对于 $10^5$ 的数据肯定是过不去的。

$\quad$现在考虑优化算法，暴力算法跑得慢的原因就是多次遍历，多次清空数组，一个显然的优化就是将询问同一个子树的询问放在一起处理，但这样还是没有处理到关键，最坏情况时间复杂度还是 $O(n^2)$ ，考虑到询问 $x$ 节点时， $x$ 的子树对答案有贡献，所以可以不用清空数组，先统计 $x$ 的子树中的答案，再统计 $x$ 的答案，这样就需要提前处理好 $dfs$ 序。

$\quad$然后我们可以考虑一个优化，遍历到最后一个子树时是不用清空的，因为它不会产生对其他节点影响了，根据贪心的思想我们当然要把节点数最多的子树（即重儿子形成的子树）放在最后，之后我们就有了一个看似比较快的算法，先遍历所有的轻儿子节点形成的子树，统计答案但是不保留数据，然后遍历重儿子，统计答案并且保留数据，最后再遍历轻儿子以及父节点，合并重儿子统计过的答案。

$\quad$其实树上启发式合并的基本思路就是这样，可以看一下代码理解。

```
il int check(int x)//统计答案
{
  int num=0,ret=0;
  for(re i=1;i<=n;i++)
    {
      if(cnt[i]==num){ret+=i;}
      else if(cnt[i]>num){num=cnt[i],ret=i;}
    }
  return ret;
}
il void add(int x){cnt[col[x]]++;}//单点增加
il void del(int x){cnt[col[x]]--;}//单点减少
il void raise(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)add(rev[i]);}//增加x子树的贡献
il void clear(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)del(rev[i]);}//清空x子树的贡献
il void dfs1(int x,int fa)
{
  dep[x]=dep[fa]+1;father[x]=fa;//处理深度，父亲
  seg[x]=++seg[0];rev[seg[x]]=x;size[x]=1;//子树大小，dfs序
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==fa)continue;dfs1(y,x);
      size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;//重儿子
    }
}
il void dfs2(int x,int flag)//flag表示是否为重儿子，1表示重儿子，0表示轻儿子
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x]||y==father[x])continue;
      dfs2(y,0);//先遍历轻儿子
    }
  if(son[x])dfs2(son[x],1);//再遍历重儿子
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x]||y==father[x])continue;
      raise(y);//更新轻儿子的贡献
    }add(x);//加上x结点本身的贡献
  ans[x]=check(x);//更新答案
  if(!flag)clear(x);//如果是轻儿子，就清空
}
```
$\quad$上面的只是模板的代码，此题的完整代码在下面。(附带注释)

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
#define re register int
#define int long long
#define LL long long
#define il inline
#define next nee
#define inf 1e18
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=1e5+5;
int n,m,next[N],go[N],head[N],tot,father[N][20],ans[N],dep[N],son[N],seg[N],rev[N],size[N],cnt[N];
struct node{int k,id;};
vector<node>q[N];
il int Max(int x,int y){return x>y?x:y;}//求较大值
il void Add(int x,int y)//链式前向新
{next[++tot]=head[x];head[x]=tot;go[tot]=y;}
il void add(int x){cnt[dep[x]]++;}//单点增加
il void raise(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)add(rev[i]);}//算上x子树的贡献
il void del(int x){cnt[dep[x]]=0;}//单点减少
il void clear(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)del(rev[i]);}//清空x子树
il void dfs1(int x,int fa)
{
  dep[x]=dep[fa]+1;size[x]=1;seg[x]=++seg[0];rev[seg[x]]=x;
  for(re i=1;i<=18;i++)father[x][i]=father[father[x][i-1]][i-1];//倍增
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      dfs1(y,x);size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;
    }
}
il void dfs2(int x,int flag)
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x])continue;
      dfs2(y,0);//先遍历轻儿子
    }
  if(son[x])dfs2(son[x],1);//再遍历重儿子
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {if(y==son[x])continue;raise(y);}//更新轻儿子的贡献
  add(x);//加上x结点本身的贡献
  for(re i=0;i<q[x].size();i++)
    ans[q[x][i].id]=cnt[dep[x]+q[x][i].k];//更新答案
  if(!flag)clear(x);//如果是轻儿子，就清空
}
il int find_father(int x,int y)//找x的第y级祖先
{
  for(re i=18;i>=0;i--){if(y>=(1<<i))y-=(1<<i),x=father[x][i];}
  return x;
}
signed main()
{
  n=read();
  for(re i=1,x;i<=n;i++)x=read(),father[i][0]=x,Add(x,i);
  for(re i=1;i<=n;i++)if(father[i][0]==0)dfs1(i,0);//预处理，倍增数组、dfs序等树上信息
  m=read();
  for(re i=1,x,y,z;i<=m;i++){x=read(),y=read(),z=find_father(x,y);if(z)q[z].push_back((node){y,i});}
  for(re i=1;i<=n;i++)if(father[i][0]==0)dfs2(i,0);//找每棵树的根节点，0表示轻儿子，这样不用手动清空数组
  for(re i=1;i<=m;i++)print(Max(ans[i]-1,0)),putchar(' ');//注意输出要减一，要去除询问节点
  return 0;
}
```

---

## 作者：BlankAo (赞：19)

**CF208E Blood Cousins** / **[原题链接](https://www.luogu.com.cn/problem/CF208E)** / **[更好阅读体验](https://www.cnblogs.com/BlankAo/p/13995154.html)**

---

这道题，我们可以考虑用 **线段树合并** 做。

首先，我们把询问离线存储起来，并且用**倍增**算法求出每个询问中，每个点的 $K$ 辈祖先是谁。这样，题目就转化为了 “求某个点有多少个 $K$ 辈儿子” 了，询问可以用链表或者 vector 存。

然后我们对于森林中的每一棵树分别考虑。假设某一个询问，转化后是求点 $A$ 的 $K$ 辈儿子数量，那我们只用求这棵树里有多少个点 $i$ 使得 $dep_A+K=dep_i$ 。因为只有 $A$ 的子树中才会出现合法的点 $i$ 。所以问题又转化为“某个点 $A$ 的子树中有多少个点 $i$ 使得 $dep_A+K=dep_i$ ”。

所以我们可以进行 dfs ，给每一个点建立一个线段树，其中点 $o$ 上建立的线段树中，节点 $l \sim r$ 代表点 $o$ 子树中 $dep$ 值为 $l \sim r$ 的点有多少个。故每遍历到一个点 $o$，先将 $dep_o$ 插入线段树，然后与子树的线段树合并，最后依次查询它身上的询问。

下面是代码：

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define mar(o) for(int E=fst[o];E;E=e[E].nxt)
#define v e[E].to
#define lsn tre[ tre[o].lv ]
#define rsn tre[ tre[o].rv ]
using namespace std;
const int n7=101234,m7=201234,t7=4001234;
struct dino{int to,nxt;}e[m7];
struct elep{int l,r,lv,rv,val;}tre[t7];
struct galo{int o,ned;}qq[n7];
int n,T,ecnt,fst[n7],cnt,dep[n7],fc[n7][22],ans[n7],rot[n7],rotc;
vector <int> vec[n7];

void edge(int sta,int edn){
	ecnt++;
	e[ecnt]=(dino){edn,fst[sta]};
	fst[sta]=ecnt;
}

void puhigh(int o){tre[o].val=lsn.val+rsn.val;}

void updat(int o,int num){
	if(tre[o].l==tre[o].r){tre[o].val++;return;}
	int mid=(tre[o].l+tre[o].r)>>1;
	if(num<=mid){
		if(!tre[o].lv){
			cnt++,tre[o].lv=cnt;
			tre[cnt]=(elep){tre[o].l,mid};
		}
		updat(tre[o].lv,num);
	}
	if(mid+1<=num){
		if(!tre[o].rv){
			cnt++,tre[o].rv=cnt;
			tre[cnt]=(elep){mid+1,tre[o].r};
		}
		updat(tre[o].rv,num);
	}
	puhigh(o);
}

int merge(int o1,int o2){
	if(!o2)return o1;
	if(!o1)return o2;
	if(tre[o1].l==tre[o1].r){tre[o1].val+=tre[o2].val;return o1;}
	tre[o1].lv=merge(tre[o1].lv,tre[o2].lv);
	tre[o1].rv=merge(tre[o1].rv,tre[o2].rv);
	puhigh(o1);
	return o1;
}

int query(int o,int num){
	if(!o)return 0;
	if(tre[o].l==tre[o].r)return tre[o].val;
	int mid=(tre[o].l+tre[o].r)>>1;
	if(num<=mid)  return query(tre[o].lv,num);
	if(mid+1<=num)return query(tre[o].rv,num);
}

void dfs2(int o){
	updat(o,dep[o]);
	mar(o){
		if(dep[v]<dep[o])continue;
		dep[v]=dep[o]+1;
		dfs2(v);
		merge(o,v);
	}
	int siz=vec[o].size()-1;
	rep(i,0,siz)ans[ vec[o][i] ]=query(o,qq[ vec[o][i] ].ned)-1;
}

void dfs1(int o){
	rep(i,1,17)fc[o][i]=fc[ fc[o][i-1] ][i-1];
	mar(o){
		if(dep[v])continue;
		fc[v][0]=o;
		dep[v]=dep[o]+1;
		dfs1(v);
	}
}

void fimd(int id){
	galo z=qq[id];
	per(i,17,0){
		if((1<<i)>z.ned)continue;
		z.o=fc[z.o][i];
		z.ned=z.ned-(1<<i);
	}
	qq[id].o=z.o;
	qq[id].ned=qq[id].ned+dep[z.o];
	vec[z.o].push_back(id);
}

int main(){
	scanf("%d",&n);
	rep(i,1,n)tre[i]=(elep){1,100000};
	cnt=n;
	rep(i,1,n){
		int x;scanf("%d",&x);
		if(x)edge(x,i);
		else rotc++,rot[rotc]=i;
	}
	rep(i,1,rotc){
		dep[ rot[i] ]=1,dfs1( rot[i] );
	}
	scanf("%d",&T);
	rep(i,1,T){
		scanf("%d%d",&qq[i].o,&qq[i].ned);
		fimd(i);
	}
	rep(i,1,rotc)dfs2( rot[i] );
	rep(i,1,T)printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：Rusalka (赞：14)

原题链接：[CF208E Blood Cousins](https://www.luogu.com.cn/problem/CF208E)

## 题意简述

- 给定 $n$ 个结点的森林，边权为 $1$；一共 $m$ 次询问，每次询问一个结点 $p$ 与多少个结点拥有共同的 $K$ 级祖先。

- $1 \le n, m \le 10^5$

## 思路与解答

- 首先考虑求出询问中每个结点的 $K$ 级祖先，就可以将问题转化为对于一个结点 $u$，在它的子树中有多少个与它距离为 $K$ 的结点，其中 $u$ 是对应的 $p$ 的 $K$ 级祖先。

- 每一次询问的答案就是上一步求出的答案减一（因为要去除 $p$）

- 然后可以把这道题分成两部分：第一部分是求出 $K$ 级祖先，第二部分是对于上一步中的每一个 $K$ 级祖先求出答案。

---

- 首先来看第一部分

- 这显然是一个经典的问题，运用长链剖分可以做到 $\Theta(m)$ 的时间复杂度；但是你发现这题并没有卡掉带 $\log$ 的做法，所以预处理一下，然后倍增跳祖先即可，时间复杂度 $\Theta(m \log n)$。

- 这一部分就结束啦~

---

- 然后是第二部分

- 发现这是一个子树中的统计问题，你需要统计子树中深度与 $p$ 相同的结点的数量，所以考虑 **dsu on tree**

- 如果你不知道什么是 **dsu on tree**，可以学习一下[这个视频](https://www.bilibili.com/video/BV1JE411d7tD?from=search&seid=3893625750051302378)（不是广告QAQ），我就是从~~同学的讲课和~~这里学会的。

- 考虑你需要维护什么信息，不妨~~按照套路~~开一个桶，记录当前结点的子树中深度为 $x$ 的点的数量。

- 那么对于每一个询问，在遍历到 $K$ 级祖先时，~~按照惯例~~保留重儿子的贡献、暴力统计轻儿子的贡献，然后看看和当前询问的 $p$ 的深度相同的点有多少个（这东西已经开桶维护了），只要把这个数量减一就是答案了（好像刚才已经说过了）。

- 这部分的复杂度就是 $\Theta(n \log n)$，所以总复杂度就是 $\Theta(m \log n + n \log n)$

## Code

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100010;

int n, m;

struct edge{
	int ne, to;
}e[MAXN];
int fir[MAXN], num = 0;
inline void join(int a, int b)
{
	e[++num].ne = fir[a];
	e[num].to = b;
	fir[a] = num;
}
int rt[MAXN], tot = 0;

int siz[MAXN], son[MAXN], f[MAXN][24], dep[MAXN], lg[MAXN];

void dfs1(int u)
{
	siz[u] = 1; dep[u] = dep[f[u][0]] + 1;
	for(int i=1;i<=lg[dep[u]];i++)
		f[u][i] = f[f[u][i-1]][i-1];
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		dfs1(v);
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v]) son[u] = v;
	}
}
inline int kthparent(int u, int k)
{
	for(int i=lg[dep[u]];i>=0;i--)
		if(dep[u] - dep[f[u][i]] <= k) k -= dep[u] - dep[f[u][i]], u = f[u][i];
	return u;
}

struct qrys{
	int x, k, pa, ans;
}a[MAXN];
vector<int> vp[MAXN];

int cnt[MAXN], nowson = 0;
void calc(int u, int val)
{
	cnt[dep[u]] += val;
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		if(v == nowson) continue;
		calc(v, val);
	}
}

void dfs(int u, bool is)
{
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		if(v == son[u]) continue;
		dfs(v, 0);
	}
	if(son[u]) 
	{
		dfs(son[u], 1);
		nowson = son[u];
	}
	calc(u, 1);
	nowson = 0;
	for(int i=0;i<vp[u].size();i++)
		a[vp[u][i]].ans = cnt[dep[a[vp[u][i]].x]]-1;
	if(!is) calc(u, -1);
}

int main()
{
	scanf("%d",&n);
	lg[0] = -1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&f[i][0]);
		if(f[i][0]) join(f[i][0], i);
		else rt[++tot] = i;
		lg[i] = lg[i>>1] + 1;
	}
	for(int i=1;i<=tot;i++)
		dfs1(rt[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].k);
		a[i].pa = kthparent(a[i].x, a[i].k);
		vp[a[i].pa].push_back(i);
	}
	for(int i=1;i<=tot;i++)
		dfs(rt[i], 0);
	for(int i=1;i<=m;i++)
		printf("%d%c",a[i].ans," \n"[i==m]);
	return 0;
}
```


---

## 作者：KAMIYA_KINA (赞：8)

## Tag

主席树，树链（？）剖分。

## Preface

咋清一色的离线做法？这题在线不困难吧……

## Description

给一颗一共 $n$ 个节点的森林，$m$ 次询问，求多少个节点与第 $x$ 个节点的 $k$ 级祖先相同。

$\texttt{data range:} n\leq 10^5$.

## Solution

首先很容易想到倍增的求出 $k$ 级祖先然后只处理 $k$ 级祖先的子树中有多少个与 $x$ 点相同深度的节点。

那么根据树链剖分的性质，**一颗子树的 dfs 序是连续的**，那么将 dfs 序求出来之后就可以将树上问题转化为序列的区间问题了。

想必上面的东西理解了之后后面的就很好想了，对于一个区间而言，我们只用求出这个区间有多少个权值为 $d_x$ 的点就可以了，这里的 $d_x$ 表示的是 $x$ 点的深度。

~~还不带修改，什么算法都能过去吧。~~

### 解法1

用可持久权值线段树就可以很容易做到在线的询问了。（果然还是在线的算法更加优美啊）

时间复杂度 $O(n\lg n)$.

### 解法2

如果不会可持久权值线段树的同学可以把询问离线然后用莫队查询答案就可以了。

时间复杂度 $O(n \sqrt n)$.

## Code

这里我只放一下前一种做法的代码吧……

```cpp
const int N = 1e5 + 1;

struct ChairManTree {
    int ls[N << 5], rs[N << 5], su[N << 5], cnt = 0;
    
    void bld(int &x ,int lef, int rig) {
        if(!x) x = ++cnt;
        if(lef == rig) return ;
        int mid = (lef + rig) >> 1;
        bld(ls[x], lef, mid);
        bld(rs[x], mid + 1, rig);
        return ;
    }
    
    void upd(int&x, int y, int lef, int rig, int k) {
        if(!x) x = ++cnt;
        if(lef == rig) return void(su[x] = su[y] + 1);
        int mid = (lef + rig) >> 1;
        if(k <= mid) rs[x] = rs[y], upd(ls[x] ,ls[y], lef, mid, k);
        else ls[x] = ls[y], upd(rs[x], rs[y], mid + 1, rig, k);
        return ;
    }
    
    int qry(int u, int v, int lef, int rig, int k) {
        if(lef == rig) return su[v] - su[u];
        int mid = (lef + rig) >> 1;
        if(k <= mid) return qry(ls[u], ls[v], lef, mid, k);
        else return qry(rs[u], rs[v], mid + 1, rig, k);
    }
    
} T;

int rt[N], n, m, f[N][20], d[N], sz[N], tot;
int id[N];
vector<int> e[N], stk;

inline void input() {
    n = rd;
    for(int i = 1; i <= n; i++) {
        int fa = rd;
        if(fa) e[fa].push_back(i);
        else stk.push_back(i);
    }
    return ;
}

void dfs(const int u, const int pre) {
    d[u] = d[pre] + 1, f[u][0] = pre, sz[u] = 1;
    id[u] = ++tot, T.upd(rt[tot], rt[tot - 1], 1, n, d[u]);
    for(int v : e[u]) {
        dfs(v, u);
        sz[u] += sz[v];
    }
    return ;
}

inline void init() {
    T.bld(rt[0], 1, n);
    for(int x : stk) dfs(x, 0);
    for(int j = 1; j < 20; j++)
    for(int i = 1; i <= n; i++)
    f[i][j] = f[ f[i][j - 1] ][j - 1];
    return ;
}

inline int Kfa(int x, int k) {
    for(int i = 19; ~i; i--) 
    if(d[x] - d[f[x][i]] <= k)
    k -= d[x] - d[f[x][i]], x = f[x][i];
    return x;
}

inline void work() {
    int m = rd;
    while( m-- ) {
        int x = rd, k = rd, fa = Kfa(x, k);
        int lef = id[fa], rig = id[fa] + sz[fa] - 1;
        if(fa == 0) cout << 0 << ' ';
        else cout << T.qry(rt[lef], rt[rig], 1, n, d[x]) - 1 << ' ';
    }
    
    return ;
}

inline void solve() {
    input();
    init();
    work();
    return ;
}

```



---

## 作者：Priori_Incantatem (赞：5)

#### 题目大意

给出一个 $n$ 个点构成的森林，有 $m$ 组询问  
每次询问一个点 $x$ 与多少个点拥有共同的 $k$ 级祖先

#### 题解

我们稍微转化一下题意：  
设 $y$ 为 $x$ 的树上 $k$ 级祖先，那么询问就变成了在 $y$ 的子树中有多少个点与 $y$ 的距离为 $k$。最后输出时需要减一

首先，我们dfs求出每个点的深度  
然后，给每一个点 $x$ 开一棵线段树，只需要支持单点修改和单点查询。位置 $i$ 记录 $x$ 子树中深度为 $i$ 的点的出现次数  
最后询问时，直接查询 $y$ 的子树中跟 $x$ 深度相同的节点数（记得减一）  
注意要特判 $x$ 没有 $k$ 级祖先的情况

朴素复杂度 $\operatorname{O}(n^2)$  
线段树合并复杂度 $\operatorname{O}(n\log n)$

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int Maxn=100000+10;
const int Maxm=5000000+10;
const int inf=0x3f3f3f3f;
int root[Maxn],head[Maxn];
int nxt[Maxn<<1],to[Maxn<<1];
int f[Maxn][23],c[Maxn];
int sum[Maxm],d[Maxn];
int ls[Maxm],rs[Maxm];
int n,m,edgecnt,idcnt,cnt;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
inline void add(int x,int y)
{
	++edgecnt;
	nxt[edgecnt]=head[x];
	to[edgecnt]=y;
	head[x]=edgecnt;
}
inline void push_up(int x)
{
	sum[x]=sum[ls[x]]+sum[rs[x]];
}
inline void modify(int &x,int l,int r,int pos,int v)
{
	if(!x)x=++idcnt;
	if(l==r)
	{
		sum[x]+=v;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)modify(ls[x],l,mid,pos,v);
	else modify(rs[x],mid+1,r,pos,v);
	push_up(x);
}
int merge(int x,int y)
{
	if(!x || !y)return x|y;
	int cur=++idcnt;
	sum[cur]=sum[x]+sum[y];
	ls[cur]=merge(ls[x],ls[y]);
	rs[cur]=merge(rs[x],rs[y]);
	return cur;
}
int query(int x,int l,int r,int pos)
{
	if(!x)return 0;
	if(l==r)return sum[x];
	int mid=(l+r)>>1;
	if(pos<=mid)return query(ls[x],l,mid,pos);
	else return query(rs[x],mid+1,r,pos);
}
void dfs(int x,int fa)
{
	f[x][0]=fa,d[x]=d[fa]+1;
	for(int i=1;i<=17;++i)
	f[x][i]=f[f[x][i-1]][i-1];
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==fa)continue;
		dfs(y,x);
		root[x]=merge(root[x],root[y]);
	}
	modify(root[x],1,n,d[x],1);
}
int find(int x,int k)
{
	for(int i=17;i>=0;--i)
	if(k & (1<<i))x=f[x][i];
	return x;
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read();
	for(int i=1;i<=n;++i)
	{
		int x=read();
		if(!x)c[++cnt]=i;
		else add(i,x),add(x,i);
	}
	for(int i=1;i<=cnt;++i)
	dfs(c[i],0);
	m=read();
	while(m--)
	{
		int x=read(),k=read();
		int pos=find(x,k);
		if(!pos)printf("0 ");
		else printf("%d ",query(root[pos],1,n,d[x])-1);
	}
	return 0;
}
```


---

## 作者：Alkaid_Star (赞：3)


Updated On 2021.10.20：修改了部分 $\LaTeX$ 格式与代码。

### 题目大意

> 给你一片 $n$ 个点的森林，$m$ 次询问，每次询问一个点 $v_i$ 与多少个点拥有共同的 $p_i$ 级祖先。
>
> $1 \le n,m \le 10^5, 1 \le v_i,p_i \le n$。

### 解题思路

直接求一个节点的 $k$ 级兄弟肯定不好做，我们考虑把询问转化成一个祖先有多少个 $k$ 级儿子，只要求出 $k$ 级儿子个数再 $-1$ 就是答案了。

因此我们先倍增预处理，然后每次读入询问，用倍增跳  $k$ 级祖先，把询问挂到祖先上。

完成问题的转化后，我们直接以深度建立线段树合并维护每个深度的儿子出现几个，每次如果发现当前节点 $x$ 有被挂询问就单点查询深度为 $dep_x+k$ 的有几个。

于是就做完......了？

确实做完了，不过我们还可以优化！

首先我们倍增求 $k$ 级祖先显然不太彳亍。时间复杂度问题倒是不大，但是空间复杂度 $O(n \log⁡ n)$ 却是比较大的，考虑进行优化。我们知道 LCA 除了倍增也可以用**树剖**求。那我们考虑用树剖求 $k$ 级祖先。每次跳一条重链，就把 $k$ 减去这条重链的长度，也就是 $dfn_x-dfn_{top_x}$（这里不用 $+1$是因为我们这条重链之后跳的是 $fa_{top_x}$，具体细节还是写代码的时候结合样例琢磨亿下）。如果发现 $k$ 已经不到这条重链的长度了，我们直接返回这条重链上从下往上的第 $k$ 个点（具体细节还是自己定），因为**重链上的节点编号是连续**的。 时间复杂度显然是预处理 $O(n)$ ，单次处理 $O(\log⁡ n)$ 的，空间复杂度大常数 $O(n)$。

不过树剖的两遍 dfs 需要很多数组！我们可以使用**离线 dfs** 来整体 $O(n)$ 解决这个问题。只需要使用一个栈，维护从根节点到当前节点的路径，对于一个询问，直接在栈中找到栈顶向下的第 $k$ 个值即可。

这也是一个冷门的套路，不过非常好用，而且只需要一个数组！

然后考虑优化线段树合并，我们**按照 $siz$ 从大到小遍历孩子并合并，每次在合并线段树后把旧的线段树的无用节点回收**即可。这样可以把空间复杂度优化一些。

### Code

这里提供最朴实的倍增做法的代码，以及其他两种做法的部分代码。

朴实做法：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005,LogN=20;

bool St;

struct Edge{
	int vet,nxt;
}e[N<<1];

struct Ques{
	int val,ord;
};

struct Node{
	int lson,rson;
	int cnt;
}tree[N*LogN];

int n,m,edge=0,logN=0,head[N];
int fa[N][LogN],dep[N];
int ans[N],rt[N],cntNode=0;
bool isrt[N];
vector <Ques> q[N];

inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)){ if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)){ x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

inline void addedge(int x,int y){
	e[++edge].vet=y;
	e[edge].nxt=head[x];
	head[x]=edge;
}

inline void dfs(int x,int fath){
	fa[x][0]=fath; dep[x]=dep[fath]+1;
	for (int i=1;i<=logN;++i)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].vet;
		if (v==fath) continue;
		dfs(v,x);
	}
}

inline int jump(int x,int k){
	for (int i=logN;i>=0;--i)
		if ((1<<i)<=k)
			k-=(1<<i),x=fa[x][i];
	return x;
}

#define lid (tree[id].lson)
#define rid (tree[id].rson)

inline void pushup(int id){
	tree[id].cnt=tree[lid].cnt+tree[rid].cnt;
}

inline void Insert(int& id,int l,int r,int val){
	if (!id) id=++cntNode;
	if (l==r){
		// printf("Ins dep=%d\n",l);
		++tree[id].cnt;
		return void();
	}
	int mid=(l+r)>>1;
	if (val<=mid) Insert(lid,l,mid,val);
	else Insert(rid,mid+1,r,val);
	pushup(id);
}

inline int Merge(int x,int y,int l,int r){
	if (!x) return y;
	if (!y) return x;
	if (l==r){
		tree[x].cnt+=tree[y].cnt;
		return x;
	}
	int mid=(l+r)>>1;
	tree[x].lson=Merge(tree[x].lson,tree[y].lson,l,mid);
	tree[x].rson=Merge(tree[x].rson,tree[y].rson,mid+1,r);
	pushup(x);
	return x;
}

inline int Query(int id,int l,int r,int val){
	if (!id) return 0;
	if (l>r) return 0;
	if (l==r){
 		// printf("Qry dep=%d\n",l);
		return tree[id].cnt;
	}
	int mid=(l+r)>>1;
	if (val<=mid) return Query(lid,l,mid,val);
	else return Query(rid,mid+1,r,val);
}

inline void Dfs(int x,int fath){
	// printf("x=%d fath=%d dep[x]=%d\n",x,fath,dep[x]);
	rt[x]=++cntNode;
	Insert(rt[x],1,n+1,dep[x]);
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].vet;
		if (v==fath) continue;
		Dfs(v,x);
		rt[x]=Merge(rt[x],rt[v],1,n+1);
	}
	for (auto it : q[x]){
		ans[it.ord]=Query(rt[x],1,n+1,it.val);
		// printf("%d : Query(%d)\n",x,it.val);
	}
}

int main(){
	//freopen("CF208E.in","r",stdin);
	//freopen("CF208E.out","w",stdout);
	n=read(); logN=(int)(log2(n)+1);
	for (int i=1;i<=n;++i){
		int x=read();
		if (x==0){ isrt[i]=true; continue; }
		addedge(x,i);
		addedge(i,x);
	}
	m=read();
	for (int i=1;i<=n;++i)
		if (isrt[i]) dfs(i,0);
	for (int i=1;i<=m;++i){
		int x=read(),y=read();
		// printf("jump(%d,%d)=%d\n",x,y,jump(x,y));
		int anc=jump(x,y);
		if (anc) q[anc].push_back((Ques){dep[x],i});
	}
	for (int i=1;i<=n;++i)
		if (isrt[i]) Dfs(i,0);
	for (int i=1;i<=m;++i)
		printf("%d ",max(ans[i]-1,0));
	printf("\n");
	bool Ed; cerr<<"MemoryUsed:"<<1.0*(&St-&Ed)/1024/1024<<endl;
	return 0;
}
```

树剖求 $k$ 级祖先：

```cpp
namespace TCP{

	int son[N],newid[N],top[N],rev[N],timer=0;
	
	inline void dfs1(int x){
		son[x]=0;
		for (int i=head[x];i;i=e[i].nxt){
			int v=e[i].vet;
			dfs1(v);
			if (siz[v]>siz[son[x]]) son[x]=v;
		}
	}

	inline void dfs2(int x,int tp){
		top[x]=tp; newid[x]=++timer;
		rev[timer]=x;
		if (son[x]) dfs2(son[x],tp);
		for (int i=head[x];i;i=e[i].nxt){
			int v=e[i].vet;
			if ((v==fa[x]) || (v==son[x])) continue;
			dfs2(v,v);
		}
	}

	inline int jump(int x,int k){
		int len=0;
		while (true){
			if (!x) return x;
			len+=newid[x]-newid[top[x]];
			// printf("x=%d len=%d k=%d return %d\n",x,len,k,rev[newid[top[x]]+(len-k)]);
			if (len>=k) return rev[newid[top[x]]+(len-k)];
			x=fa[top[x]]; ++len;
		}
	}
}
```

离线 dfs 求 $k$ 级祖先：

```cpp
namespace k_fath{
	void dfss(int x){
		sta[++top]=x;
		for (int i=Hed[x];i;i=Q[i].nxt){
			int k=Q[i].val,ord=Q[i].ord;
			int anc=(k>=top) ? (0) : (sta[top-k]);
			if (anc) addquery(anc,dep[x],Q[i].ord);
		}
		for (int i=head[x];i;i=e[i].nxt)
			dfss(e[i].vet);
		--top;
	}
}
```



---

## 作者：gxy001 (赞：3)

这题的在线做法好少啊，我来贡献个可持久化线段树的题解吧。

## 前置知识
- [可持久化数组](https://www.luogu.com.cn/problem/P3919)；
- [树上 k 级祖先](https://www.luogu.com.cn/problem/P5903)，不用会长链剖分的解法，这题倍增够用了；
- 获得一棵树的 dfs 序。

## 进入正题
拿到森林后，我们先通过一遍 dfs 处理出倍增数组并得到 dfs 序，在 dfs 序上建立主席树，主席树内存每个点的深度。

dfs 序的性质：一颗子树的 dfs 序连续。

通过这个性质，在我们找到 k 级祖先后，我们可以将原问题转化为，在一棵子树内，有多少点深度与询问点相同。显然，主席树完全可以胜任，懒得写主席树的可以写分块，也能过。

## 代码
思路讲的很清楚了，上代码：
```cpp
#include<cstdio>
int n,m,rt[100010],head[100010],to[200010],nxt[200010],cnt,dfn[100010],rk[100010],f[100010][22],d[100010],bel[100010],sz[100010];
void add(int const &x,int const &y){
	to[++cnt]=y,nxt[cnt]=head[x],head[x]=cnt;
}
void dfs(int const &x,int const &fa){
	bel[x]=bel[fa],dfn[x]=++cnt,sz[x]=1,d[x]=d[fa]+1,f[x][0]=fa,rk[cnt]=x;
	for(int i=1;i<=20;i++)f[x][i]=f[f[x][i-1]][i-1];
	for(int i=head[x];i;i=nxt[i])
		if(to[i]!=fa)
			dfs(to[i],x),sz[x]+=sz[to[i]];
}
struct node{
	int v,ls,rs;
}tr[4000010];
inline void clone(int &x){tr[++cnt]=tr[x],x=cnt;}
void update(int const &p,int &x,int const &l=1,int const &r=n){
	clone(x);
	tr[x].v++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(p<=mid) update(p,tr[x].ls,l,mid);
	else update(p,tr[x].rs,mid+1,r);
}
int query(int const &p,int const &x1,int const &x2,int const &l=1,int const &r=n){
	if(l==r) return tr[x1].v-tr[x2].v;
	int mid=(l+r)>>1;
	if(p<=mid) return query(p,tr[x1].ls,tr[x2].ls,l,mid);
	else return query(p,tr[x1].rs,tr[x2].rs,mid+1,r);
}
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)scanf("%d",&x),add(x,i);
	cnt=0;
	for(int i=1;i<=n;i++)if(!bel[i])bel[0]=i,dfs(i,0);
	bel[0]=cnt=0;
	for(int i=1;i<=n;i++)update(d[rk[i]],rt[i]=rt[i-1]);
	scanf("%d",&m);
	while(m--){
		int x,k,p;
		scanf("%d%d",&x,&k);
		if(d[x]<=k){printf("0 ");continue;}
		p=d[x];
		for(int i=20;~i;i--)
			if(d[f[x][i]]>=p-k)
				x=f[x][i];
		printf("%d ",query(p,rt[dfn[x]+sz[x]-1],rt[dfn[x]-1])-1);
	}
	return 0;
}
```

---

## 作者：Leap_Frog (赞：2)

### P.S.
这里提供一个 DSU （不是并查集）的做法。  
虽然好像被重剖吊打，不过好像适用性广？  
### Problem.
求一个点的子树中有多少个 dep 为给定值的节点。  
（你直接找到询问的 K 级祖先，再把答案减一就好了。  
~~不过如果您看到这个简化题意您应该已经切掉了~~
### Solution.
显然可以长剖，不过笔者已经基本忘光了。  
所以笔者写了比长剖多只 log 的树上按秩合并。  
如果你不会 DSU，安利一下笔者的[总结](https://www.luogu.com.cn/blog/daniu/chang-lian-pou-fen)  
然后你就发现这题做完了（（（  
比模板还模板的 DSU（（（  
注意一些细节，已经标在代码中了。（可以 Ctrl+F Mark  
如果看不懂还有注释，用的倍增求 K 级祖先。  
### Coding.
```cpp
//愿你和你重要的人能够重逢！
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x,1:1;
}
struct edge{int to,nxt;}e[200005];int et,head[100005],f[100005][20],dep[100005],dfn[100005],dt;
int Q,n,T[100005],rs[100005],sz[100005],sn[100005];vector<pair<int,int> >p[100005];char avd[100005];
inline void adde(int x,int y) {e[++et]=(edge){y,head[x]},head[x]=et;}
inline void dfs0(int x,int fa)
{//初始化，预处理倍增数组/深度/每个结点的重儿子
	f[x][0]=fa,dep[x]=dep[fa]+1,sz[x]=1,dfn[x]=++dt;
	for(int i=1;i<20;i++) f[x][i]=f[f[x][i-1]][i-1];
	for(int i=head[x];i;i=e[i].nxt)
	{
		dfs0(e[i].to,x),sz[x]+=sz[e[i].to];
		if(sz[e[i].to]>=sz[sn[x]]) sn[x]=e[i].to;
	}
}
inline int getk(int x,int k) {for(int i=0;i<20;i++) if((k>>i)&1) x=f[x][i];return x;}
//求 K 级祖先（反正总复杂度一直log，就不写 O(n) 了（（（
inline void baoli(int x,int tg) {T[dep[x]]+=tg;for(int i=head[x];i;i=e[i].nxt) if(!avd[e[i].to]) baoli(e[i].to,tg);}
//暴力加上/减去贡献，对于轻儿子的暴力
inline void dfs1(int x,char isw)//is weight son?
{
	for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=sn[x]) dfs1(e[i].to,0);
	if(sn[x]) dfs1(sn[x],1),avd[sn[x]]=1;else;baoli(x,1),avd[sn[x]]=0;
	//重儿子的直接继承信息
	//printf("%d : ",x);for(int i=1;i<=n;i++) printf("%d%c",T[i],i==n?'\n':' ');
	for(int i=0;i<(int)p[x].size();i++) rs[p[x][i].second]=T[p[x][i].first+dep[x]]-1;
	//Mark 1，答案需要减一，因为自己显然不是自己的堂弟（
	if(!isw) baoli(x,-1);//如果是轻儿子，需要撤销贡献
}
int main()
{
	//我直接把全部点的标号++，这样1号节点是一个虚节点，不代表任何人
	read(n),++n;for(int i=2,x;i<=n;i++) read(x),adde(++x,i);
	dfs0(1,0),read(Q);for(int i=1,x,l;i<=Q;i++)
	{
		read(x),read(l);int fp=getk(++x,l);
		if(fp>1) p[fp].push_back(make_pair(l,i));
		//Mark 2，如果是虚节点，那它的答案也必须为0
	}
	dfs1(1,0);for(int i=1;i<=Q;i++) printf("%d%c",rs[i],i==Q?'\n':' ');
	return 0;
}
```

---

## 作者：chihik (赞：2)

和 $u$ 拥有共同的 $k$ 级祖先的点数就是 $u$ 的 $k$ 级祖先的 $k$ 级儿子的数量 $-1$.

再转换一下就是以 $u$ 的 $k$ 级祖先为根的子树内深度为 $dep_u+k$ 的点的个数$-1$。

然后用 $cnt_d$ 表示深度为 $d$ 的点数，直接 $\text{dsu~on~tree}$ 即可。

```cpp
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;

const int MAXN = 1e5 , MAXK = 20;
int n , m , col[ MAXN + 5 ];
struct Query{ int id , dep; };
vector< Query > Qry[ MAXN + 5 ];
vector< int > Graph[ MAXN + 5 ];

int dep[ MAXN + 5 ] , Size[ MAXN + 5 ] , Son[ MAXN + 5 ];
int Anc[ MAXN + 5 ][ MAXK + 5 ];
void dfs1( int u , int fa ) {
	dep[ u ] = dep[ fa ] + 1 , Size[ u ] = 1;
	Anc[ u ][ 0 ] = fa;
	for( int i = 1 ; i <= MAXK ; i ++ ) Anc[ u ][ i ] = Anc[ Anc[ u ][ i - 1 ] ][ i - 1 ];
	for( int i = 0 ; i < Graph[ u ].size() ; i ++ ) {
		int v = Graph[ u ][ i ];
		if( v == fa ) continue;
		dfs1( v , u ); Size[ u ] += Size[ v ];
		if( Size[ Son[ u ] ] < Size[ v ] ) Son[ u ] = v;
	}
}

int Cnt[ MAXN + 5 ];
int Ans[ MAXN + 5 ] , Sonu;
void Count( int u , int fa , int val ) {
	Cnt[ dep[ u ] ] += val;
	
	for( int i = 0 ; i < Graph[ u ].size() ; i ++ ) {
		int v = Graph[ u ][ i ];
		if( v == fa || v == Sonu ) continue;
		Count( v , u , val );
	} 
}
bool vis[ MAXN + 5 ];
void dfs2( int u , int fa , bool is_hs ) {
	vis[ u ] = 1;
	for( int i = 0 ; i < Graph[ u ].size() ; i ++ ) {
		int v = Graph[ u ][ i ];
		if( v == fa || v == Son[ u ] ) continue;
		dfs2( v , u , 0 );
	}
	if( Son[ u ] ) dfs2( Son[ u ] , u , 1 );
	Sonu = Son[ u ]; Count( u , fa , 1 ); Sonu = 0;
	for( int i = 0 ; i < Qry[ u ].size() ; i ++ ) Ans[ Qry[ u ][ i ].id ] = Cnt[ dep[ u ] + Qry[ u ][ i ].dep ] - 1;
	if( !is_hs ) Count( u , fa , -1 );
}

int main( ) {
	scanf("%d",&n);
	for( int i = 1 , fa ; i <= n ; i ++ ) {
		scanf("%d",&fa);
		Graph[ fa ].push_back( i );
	}
	
	for( int i = 1 ; i <= n ; i ++ )
		if( !dep[ i ] ) dfs1( i , 0 );
	
	scanf("%d",&m);
	for( int i = 1 , rt , k ; i <= m ; i ++ ) {
		scanf("%d %d",&rt,&k);
		for( int i = 0 ; i <= MAXK ; i ++ ) if( ( k >> i ) & 1 ) rt = Anc[ rt ][ i ];
		Qry[ rt ].push_back( { i , k } );
	}
	
	for( int i = 1 ; i <= n ; i ++ )
		if( !vis[ i ] ) dfs2( i , 0 , 0 );
	
	for( int i = 1 ; i <= m ; i ++ )
		printf("%d ", Ans[ i ] );
	return 0;
} 
```

再说说这道题的加强版 [P5384 [Cnoi2019]雪松果树](https://www.luogu.com.cn/problem/P5384)。

出题人卡了空间，正常写法只有 40 pts。

首先倍增数组太占空间，考虑离线求出 $k$ 级祖先。

$\text{dfs}$ 时可以用栈维护根到当前节点的路径上的点。

那么它的 $k$ 级祖先就应该是栈中的第 $k+1$ 个元素。

~~然后你就多得了 4 pts 了。~~

将 $\text{vector}$ 改成链表，再卡卡常就可以过了。

~~虽然正解是长链剖分~~


---

## 作者：TEoS (赞：2)

一个奇奇怪怪的复杂度很垃圾的线段树合并解法

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/12977020.html)

------------


通过分析可以发现，要找$x$的$k$辈兄弟，只需要找到$x$的$k$辈祖先，然后查找以该祖先为根的子树中和$x$深度相同的节点个数$-1$即可。也就是说，询问只与深度有关，与具体是哪个节点无关。

具体怎么实现呢？想到dfs处理，显然在遍历过$x$后会回溯到$x$的$k$辈祖先，因此有一个想法，就是在回溯到$x$的$k$辈祖先时执行查询对应的查询就可以了，这样是一个离线的做法。目前的问题就是，如何能在$x$的$k$辈祖先时执行查询。

有一个做法就是提前处理出$x$的祖先，然后把询问插入到$x$的$k$辈祖先处，等到回溯到的时候进行查询；另一种就是一种比较奇奇怪怪的做法，利用大根堆维护询问，把祖先节点的深度作为关键字，当遍历到一个节点时，处理深度相同的询问。具体询问用线段树合并就可以处理了。

还有一个可以优化的地方，如果有祖先节点和查询节点的深度都相同的询问，答案相同，不需要重复查询。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int N=1e5+100;
struct Seg
{
	int lson,rson,sum;
	#define lson(i) t[i].lson
	#define rson(i) t[i].rson
	#define sum(i) t[i].sum
}t[5000000];
struct Que
{
	int fa,son,id;//祖先深度，查询节点深度，询问编号
};
int n,m,tot,cnt;
int head[N],ver[N],Next[N];
int r[N],ans[N];
bool v[N];
priority_queue<Que> q;//维护询问
vector<pair<int,int> > query[N];//存储询问
bool operator<(const Que &a,const Que &b)
{
	return a.fa==b.fa?a.son<b.son:a.fa<b.fa;//注意是小于号
}//大根堆
void add(int x,int y)
{
	ver[++tot]=y,Next[tot]=head[x],head[x]=tot;
}
int merge(int x,int y)
{
	if(!x)
		return y;
	if(!y)
		return x;
	sum(x)+=sum(y);
	lson(x)=merge(lson(x),lson(y));
	rson(x)=merge(rson(x),rson(y));
	return x;
}//线段树合并
int ask(int &p,int l,int r,int k)
{
	if(!p)
		p=++cnt;
	if(l==r)
		return sum(p);
	int mid=(l+r)>>1;
	if(k<=mid)
		return ask(lson(p),l,mid,k);
	else
		return ask(rson(p),mid+1,r,k);
}//查询
void change(int &p,int l,int r,int k)
{
	if(!p)
		p=++cnt;
	if(l==r)
	{
		sum(p)++;
		return ;
	}
	int mid=(l+r)>>1;
	if(k<=mid)
		change(lson(p),l,mid,k);
	else
		change(rson(p),mid+1,r,k);
}//修改
void solve(int x,int d)
{
	v[x]=1;//访问数组
	for(int i=head[x];i;i=Next[i])
	{
		int y=ver[i];
		solve(y,d+1);
		r[x]=merge(r[x],r[y]);//子节点合并
	}
	while(q.size() && q.top().fa==d)//处理深度相同的询问
	{
		int y=q.top().son,id=q.top().id;q.pop();
		ans[id]=ask(r[x],1,1e5,y)-1;//查询
		while(q.size() && q.top().fa==d && q.top().son==y)
		{
			ans[q.top().id]=ans[id];
			q.pop();
		}//询问等价不用重复查询
	}
	change(r[x],1,1e5,d);//修改
	for(int i=0;i<query[x].size();i++)
		if(d-query[x][i].first>0)//保证询问合法
		{
			Que now;
			now.fa=d-query[x][i].first;
			now.son=d;
			now.id=query[x][i].second;
			q.push(now);
		}//将询问插入大根堆
}
int main()
{
	scanf("%d",&n);cnt=n;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);r[i]=i;
		if(x)
			add(x,i);
	}
	scanf("%d",&m);
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		query[x].push_back(make_pair(y,i));//插入询问
	}
	for(int i=1;i<=n;i++)
		if(!v[i])
			solve(i,1);
	for(int i=1;i<=m;i++)
		printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：feicheng (赞：1)

## Description

给定含有 $n$ 个点的森林，$m$ 次询问，每次询问包含两个参数 $v,p$，求有多少个节点与节点 $v$ 含有相同的 $p$ 级祖先。

$1\le n\le 10^5$

## Solution

看到线段树合并的题解那么少，就来补一篇吧。

### 前置知识

- 线段树合并

### 解法

我们考虑将问题转换一下：首先对于每个询问，求出其 $p$ 级祖先，记作点 $u$，问题实际上转化为了点 $u$ 的 $p$ 级子孙数量。

然后考虑点 $c$ 若能成为 $u$ 的 $p$ 级子孙，$c$ 实际上要满足如下两个条件：

-  在 $u$ 的子树内
- $\operatorname{dep}_c=\operatorname{dep}_u+p$ 

于是问题转化为 $u$ 子树内有多少个点满足 $\operatorname{dep}_c=\operatorname{dep}_u+p$ ，考虑使用线段树合并解决该问题。

对询问离线，挂在每个点上（这个过程可以用 `vector` ），这里指的是求出了 $p$ 级祖先之后的询问。

使用动态开点权值线段树，设节点 $x$ 的区间为 $[l,r]$，则节点 $x$ 维护当前有多少个点满足 $\operatorname{dep}$ 在 $[l,r]$ 之间。

进行一次 dfs，首先添加点 $u$ 的信息，然后再将其子树的线段树与其进行合并，最后对挂在该点的询问进行查询即可。

时间复杂度：$\mathcal O(n\log n)$。 

## Code 

```cpp
constexpr int N = 1e5 + 5 ;

int n,tot,m;
int fa[N][20],dep[N],ans[N],head[N],to[N << 1],nxt[N << 1],srt[N],rt[N]; 

std::vector<std::pair<int,int> > q[N] ;
//first k,second id

inline void add(int u,int v) {
    static int cnt = 0 ;

    to[++cnt] = v,nxt[cnt] = head[u],head[u] = cnt ;
}

void dfs1(int x,int f) {
    dep[x] = dep[f] + 1,fa[x][0] = f ;

    for (int i = 1; i < 20; ++i) 
        fa[x][i] = fa[fa[x][i - 1]][i - 1] ;

    for (int i = head[x]; i; i = nxt[i]) 
        if (int v = to[i]; v != f) 
            dfs1(v,x);
}

inline int jump(int x,int k) {
    for (int i = 19; ~i; --i)
        if (k & (1 << i)) 
            x = fa[x][i] ;
        
    return x ;
}

namespace seg {

#define mid ((l + r) >> 1)

constexpr int MAX_NODE = N << 5 ;

int cnt = 0 ;
int ls[MAX_NODE],rs[MAX_NODE],sum[MAX_NODE] ;

void check(int x,int l,int r) {
    if (!x) 
        return ;
    
    //std::cout << "sum " << l << "~"  << r << " = " <<  sum[x] << '\n' ;
    check(ls[x],l,mid),check(rs[x],mid + 1,r) ; 
}

inline void pushup(int x) {
    sum[x] = sum[ls[x]] + sum[rs[x]] ;
}

inline void change(int &x,int l,int r,int pos) {
    x = !x ? ++cnt : x ;

    if (l == r) 
        return ++sum[x],void() ;
    
    if (pos <= mid) 
        change(ls[x],l,mid,pos) ;
    else 
        change(rs[x],mid + 1,r,pos) ;
    
    pushup(x) ;
}

int merge(int x,int y,int l,int r) {
    if (!x || !y) 
        return x | y ;

    if (l == r) 
        return sum[x] += sum[y],x ;
    
    return ls[x] = merge(ls[x],ls[y],l,mid),rs[x] = merge(rs[x],rs[y],mid + 1,r),pushup(x),x ;
}

int query(int x,int l,int r,int pos) {
    if (l == r) 
        return sum[x] ;
    
    if (pos <= mid) 
        return query(ls[x],l,mid,pos) ;
    else 
        return query(rs[x],mid + 1,r,pos) ;
}



}

void dfs2(int x) {
    seg::change(srt[x],1,n,dep[x]) ;
    
    //std::cout << "x = " << x << '\n' ;
    //seg::check(srt[x],1,n) ;
    
    for (int i = head[x]; i; i = nxt[i]) 
        if (int v = to[i]; v != fa[x][0]) 
            dfs2(v),srt[x] = seg::merge(srt[x],srt[v],1,n);
     
    for (auto it : q[x]) 
        ans[it.second] = seg::query(srt[x],1,n,it.first) - 1;
}

int main(int argc, const char **argv) {
#ifdef helios
    freopen("std.in", "r", stdin);
    freopen("std.ans", "w", stdout);
#endif
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    in(n) ;

    for (int i = 1,x; i <= n; ++i) {
        in(x) ;

        if (x) 
            add(x,i),add(i,x) ;
        else 
            rt[++tot] = i ;
    }

    for (int i = 1; i <= tot; ++i) 
        dep[rt[i]] = 1,dfs1(rt[i],0) ; 

    in(m) ;

    for (int i = 1,x,k; i <= m; ++i) {
        in(x,k) ;

        int ac = jump(x,k) ;

        if (ac == 0) {
            ans[i] = 0 ;
            continue ;
        }

        q[ac].push_back(std::make_pair(k + dep[ac],i)) ;
    }

    for (int i = 1; i <= tot; ++i) 
        dfs2(rt[i]) ;

    for (int i = 1; i <= m; ++i) 
        out(' ',ans[i]) ;

    seg::check(srt[1],1,n) ;

    std::cerr << "This program costs " << clock() << " ms" ;
    return 0 ;
}
```

对代码有疑问可以私信我。

---

## 作者：RuntimeErr (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF208E)

给你一片森林，每次询问一个点与多少个点拥有共同的 $k$ 级祖先。

首先我们来转化一下题意，我们可以将询问变为询问一个点的 $k$ 级祖先所在子树内离该祖先距离为 $k$ 的结点个数，最后将答案减一。

到这里就可以用 dsu on tree 求解了，我们将询问中的点倍增求 $k$ 级祖先，将询问离线下来就可以了。

### Code：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
template <typename T>
inline void read(T& r) {
	r=0;bool w=0; 
	char ch=getchar();
	while(ch<'0'||ch>'9') w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9') r=(r<<3)+(r<<1)+(ch^48), ch=getchar();
	r=w?-r:r;	
}

const int N=1e5+10;

int n,m,fa[N],cnt[N];
vector<int>e[N];
int anc[N][20],size[N],son[N],dep[N],flag;
struct node{
	int id,kth;
	node(int i,int k):id(i),kth(k){}
};
vector<node>q[N];int ans[N];

void dfs1(int u,int fa){
	dep[u]=dep[fa]+1,anc[u][0]=fa;size[u]=1;
	for(int i=1;i<=17;++i)anc[u][i]=anc[anc[u][i-1]][i-1];
	for(int v:e[u]){
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])son[u]=v;
	}
}
void calc(int u,int rtdep,bool type){
	type?++cnt[dep[u]]:cnt[dep[u]]=0;
	for(int v:e[u])if(v^flag)calc(v,rtdep,type);
}
void dfs2(int u,bool keep){
	for(int v:e[u])if(v^son[u])dfs2(v,0);
	if(son[u])dfs2(son[u],1);
	flag=son[u];calc(u,dep[u],1);flag=0;
	for(node qwq:q[u])ans[qwq.id]=cnt[dep[u]+qwq.kth];
	if(!keep)calc(u,dep[u],0);
}
int getkth(int u,int k){
	for(int i=17;~i;--i)if((1<<i)<=k)u=anc[u][i],k-=1<<i;
	return u;
}

int main(){
	#ifdef LOCAL
		freopen("std.in","r",stdin);
		freopen("my.out","w",stdout);
	#endif
	read(n);
	for(int i=1,x;i<=n;++i){
		read(x);fa[i]=x;
		if(x)e[x].push_back(i);
	}
	for(int i=1;i<=n;++i)if(!fa[i])dfs1(i,0);
	read(m);
	for(int i=1,u,k;i<=m;++i){
		read(u),read(k);
		q[getkth(u,k)].push_back(node(i,k));
	}
	for(int i=1;i<=n;++i)if(!fa[i])dfs2(i,0);
	for(int i=1;i<=m;++i)printf("%d ",max(ans[i]-1,0));
	return 0;
}
```


---

## 作者：foreverlasting (赞：1)

[题面](https://www.luogu.org/problemnew/show/CF208E)

dsu on tree.

对于每一个询问，直接倍增求出它的第$k$级的祖先。然后遍历一遍森林，只要统计深度相同的点的个数就好了。

code:
```
//2018.10.25 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=1e5+10;
namespace MAIN{
	int n;
	int rt[N],rtx;
	struct E{
		int next,to;
		E() {}
		E(res next,res to):next(next),to(to) {}
	}edge[N];
	int head[N],cnt;
	inline void addedge(const res &u,const res &v){
		edge[++cnt]=E(head[u],v),head[u]=cnt;
	}
	int dep[N],F[N][21],siz[N],fa[N],son[N];
	void Dfs(const res &x,const res &fax,const res &depx){
		dep[x]=depx,fa[x]=fax,F[x][0]=fax,siz[x]=1;
		for(res i=1;i<=20;i++)F[x][i]=F[F[x][i-1]][i-1];
		for(res i=head[x];~i;i=edge[i].next){
			res tox=edge[i].to;
			if(tox==fax)continue;
			Dfs(tox,x,depx+1);
			siz[x]+=siz[tox];
			if(siz[son[x]]<siz[tox])son[x]=tox;
		}
	}
	typedef pair<int,int> Pair;
#define mp make_pair	
#define fi first
#define se second
	vector<Pair> vec[N];
#define pb push_back	
	int m;
	int tot[N],ans[N];
	bool vis[N];
	void update(const res &x,const res &va){
		tot[dep[x]]+=va;
		for(res i=head[x];~i;i=edge[i].next){
			res tox=edge[i].to;
			if(tox==fa[x]||vis[tox])continue;
			update(tox,va);
		}
	}
	void dfs(const res &x,const res &flag){
		for(res i=head[x];~i;i=edge[i].next){
			res tox=edge[i].to;
			if(tox==fa[x]||tox==son[x])continue;
			dfs(tox,0);
		}
		if(son[x])dfs(son[x],1),vis[son[x]]=1;
		update(x,1);for(res i=0,siz=vec[x].size();i<siz;i++)ans[vec[x][i].fi]=tot[vec[x][i].se]-1;vis[son[x]]=0;
		if(!flag)update(x,-1);
	}
	inline void MAIN(){
		memset(head,-1,sizeof(head));
		n=read();
		for(res i=1;i<=n;i++){
			res fa=read();
			if(!fa)rt[++rtx]=i;
			else addedge(fa,i);
		}
		for(res i=1;i<=rtx;i++)Dfs(rt[i],0,1);
		m=read();
		for(res t=1;t<=m;t++){
			res x=read(),k=read(),d=dep[x];
			for(res i=20;~i;i--)if(k&(1<<i))x=F[x][i];
			vec[x].pb(mp(t,d));
		}
		for(res i=1;i<=rtx;i++)dfs(rt[i],0);
		for(res i=1;i<=m;i++)printf("%d ",ans[i]);
	}
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

个人感觉这道题还是有点稍难的。  
主要是往离线这方面想……  
首先我们发现这道题直接查询很难处理，于是刚开始我就卡在怎么查询，然后想了一会儿……  
不久就发现当我们知道一个点知道它距祖先的距离不久可以算出来他要查询的祖先节点是谁了吗？  
于是这道题就变得简单起来了。  
开一个 $cnt[x]$ 数组记录一下在当前 $DFS$ 查询中深度为 $x$ 的节点有多少个。  
$add$函数就没什么好参考的了：  
```cpp
void Add(int x,int val)
{
	cnt[dep[x]] += val;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == Son) continue;
		Add(to , val);
	}
}
```
 $dfs1$ 就在中间跑一下倍增LCA，其余的也是板子。  
因为之前的工作都做好了， $dfs2$ 也可以直接跑。  
所以这道题只要离线把每个询问~~爬树~~处理一下即可，也不是特别恶心。  
由于原图是森林，我们就顺便预处理一波所有的 $root$ 就可以了。(找 $fa 为 0 的点$ )  
于是这道题就完了……  
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
const int Len = 1e5 + 5;
int n,m,head[Len],cnts,cnt[Len << 2],dep[Len],siz[Len],son[Len],dp[Len][30],Son,ans[Len];
bool vis[Len];
vector<int> root;
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnts].to = to;
	edge[cnts].next = head[from];
	head[from] = cnts;
}
struct Node
{
	int depth,idx;
};
vector<Node> G[Len];
void Add(int x,int val)
{
	cnt[dep[x]] += val;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == Son) continue;
		Add(to , val);
	}
}
void dfs1(int x,int f)
{
	dep[x] = dep[f] + 1;
	siz[x] = 1;
	dp[x][0] =  f;
	vis[x] = true;
	int maxson = -1;
	for(int i = 1 ; (1 << i) <= dep[x] ; i ++) dp[x][i] = dp[dp[x][i - 1]][i - 1];
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		dfs1(to , x);
		siz[x] += siz[to];
		if(maxson < siz[to]) maxson = siz[to] , son[x] = to;
	}
}
int Find(int x,int k)//爬树 
{
	for(int i = 20 ; i >= 0 ; i --) if((1 << i) <= k) k -= (1 << i) , x = dp[x][i];
	return x;
}
void dfs2(int x,int f,int opt)
{
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == son[x]) continue;
		dfs2(to , x , 0);
	}	
	if(son[x]) dfs2(son[x] , x , 1) , Son = son[x];
	Add(x , 1) , Son = 0;
	for(int e = 0 ; e < G[x].size() ; e ++) ans[G[x][e].idx] = cnt[dep[x] + G[x][e].depth] - 1;
	if(!opt) Add(x , -1);
} 
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)
	{
		int x;
		scanf("%d",&x);
		if(x == 0) root.push_back(i);
		else add(x , i);
	}
	for(int i = 0 ; i < root.size() ; i ++) dfs1(root[i] , 0);
	scanf("%d",&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		int Fa = Find(x , y);
		if(Fa == 0) ans[i] = 0;
		else 
		{
			Node opt;
			opt.depth = y , opt.idx = i;
			G[Fa].push_back(opt);
		}
	}
	for(int i = 0 ; i < root.size() ; i ++) dfs2(root[i] , 0 , 0);
	for(int i = 1 ; i <= m ; i ++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：decoqwq (赞：0)

题意：给定一个 $n$ 个点的森林，每次询问与点 $x$ 有同一个 $k$ 级祖先的点个数

将询问离线，对于每个询问，显然可以转化为 $x$ 的 $k$ 级祖先的子树中深度与 $x$ 相同的点个数，统计子树内答案显然可以树上启发式合并，加上一开始跳祖先时的倍增，时间复杂度 $O(nlogn)$，空间复杂度 $O(nlogn)$

```cpp
/*  Never Island  */
/*deco loves Chino*/
#include <bits/stdc++.h>
using namespace std;
int n,f[100010][20],dep[100010],vis[100010],lg2[100010],q;
vector<int> vc[100010],Q[100010],ans[100010];
int belong[100010],top[100010],sum[100010],siz[100010],son[100010];
void dfs(int u)
{
	siz[u]=1;
	for(int i=0;i<vc[u].size();i++)
	{
		int v=vc[u][i];
		dep[v]=dep[u]+1;
		dfs(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])
		{
			son[u]=v;
		}
	}
}
void calc(int u,int fa,int c)
{
	sum[dep[u]]+=c;
	for(int i=0;i<vc[u].size();i++)
	{
		int v=vc[u][i];
		if(vis[v])
		{
			continue; 
		} 
		calc(v,u,c);
	}
}
/*启发式合并*/
void gans(int u,int fa,int keep)
{
	for(int i=0;i<vc[u].size();i++)
	{
		int v=vc[u][i];
		if(v==son[u])
		{
			continue;
		}
		gans(v,u,0);//do not keep the answer
	}
	if(son[u])
	{
		gans(son[u],u,1);
		vis[son[u]]=1;
	}
	calc(u,fa,1);
	if(son[u])
	{
		vis[son[u]]=0;
	}
	for(int i=0;i<Q[u].size();i++)
	{
		ans[u].push_back(sum[Q[u][i]]);
	}
	if(!keep)
	{
		calc(u,fa,-1);//clear
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&f[i][0]);
		vc[f[i][0]].push_back(i);
	}
	for(int i=1;i<=18;i++)
	{
		for(int j=1;j<=n;j++)
		{
			f[j][i]=f[f[j][i-1]][i-1];
		}
	}
	for(int i=2;i<=n;i++)
	{
		lg2[i]=lg2[i>>1]+1;
	}
	dfs(0);
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(y>=dep[x])
		{
			belong[i]=0;
		}
		else
		{
			int qwq=dep[x];
			while(y)
			{
				x=f[x][lg2[y]];
				y-=(1<<lg2[y]);
			}
			Q[x].push_back(qwq);
			belong[i]=x;
		}
	}
	gans(0,-1,1);
	for(int i=1;i<=q;i++)
	{
		if(belong[i]==0)
		{
			cout<<0<<" ";
			continue;
		}
		cout<<ans[belong[i]][top[belong[i]]++]-1<<" ";
	}
	return 0;
}

```

---

## 作者：localhost (赞：0)

倍增找$k$级祖先+~~dsu on tree~~静态链分治

设当前节点为$x$

如果$d_x < k$,那么答案当然为$0$
可以找到第$k$级祖先，然后在$k$级祖先上添加一组询问(求它子树中深度为$d_x$的节点数)

因为这个还算上了$x$本身，所以把结果-1就是答案了

统计区间中各个深度的点有多少个就直接$tot[d_x]+=(1\text{或}-1)$就可以了


上代码：
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define il inline
#define rg register
#define Fur(i,x,y) for(register int i=x;i<=y;++i)
#define fl(i,x) for(register int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
#define clr(x,y) memset(x,y,sizeof(x))
#define fin(s) freopen(s".in","r",stdin)
#define l2(n) ((int)(log2(n)))
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 100011
int n,m,cnt=0,head[N],CNT=0,HEAD[N],tt=0,RT[N];
struct edge{
    int to,nxt;
}e[N],E[N];
il void add(int x,int y){
    e[++cnt].to=y;e[cnt].nxt=head[x];head[x]=cnt;
}
il void pb(int x,int y){
    E[++CNT].to=y;E[CNT].nxt=HEAD[x];HEAD[x]=CNT;
}
int f[17][N],d[N],siz[N],son[N],T[N],L[N],R[N],dfn=0;
il void dfs(int x){
    siz[x]=1;T[L[x]=++dfn]=x;
    fl(i,x){
        f[0][to]=x;d[to]=d[x]+1;
        dfs(to);siz[x]+=siz[to];
        if(siz[to]>siz[son[x]])son[x]=to;
    }
    R[x]=dfn;
}
il void st(){
    int k=l2(n);
    Fur(j,1,k)
        Fur(i,1,n)
        if(~f[j-1][i])f[j][i]=f[j-1][f[j-1][i]];
}
il int get(int x,int k){
    int t=0;
    while(k){
        if(k&1){
            x=f[t][x];
            if(!(~x))return -1;
        }
        k>>=1;++t;
    }
    return x;
}
struct que{int d,id;}q[N];
int ANS[N];
int tot[N];
il void Add(int x,int v){
    tot[d[x]]+=v;
}
il void upd(int x,int v){
    Fur(i,L[x],R[x])Add(T[i],v);
}
il void sol(int x){
    fl(i,x)if(to!=son[x]){
        sol(to);
        upd(to,-1);
    }
    if(son[x])sol(son[x]);
    Add(x,1);
    fl(i,x)if(to!=son[x])upd(to,1);
    for(register int i=HEAD[x],to;to=E[i].to,i;i=E[i].nxt)ANS[q[to].id]=tot[q[to].d]-1;
}
int main(){
    in>>n;
    register int x,k;
    Fur(i,1,n){
        in>>x;
        if(!x)RT[++RT[0]]=i;
        else add(x,i);
    }
    clr(f,-1);
    Fur(i,1,RT[0])dfs(RT[i]);
    st();
    in>>m;
    Fur(i,1,m){
        in>>x>>k;
        if(d[x]>=k)q[++tt]=que{d[x],i},pb(get(x,k),tt);
        else ANS[i]=0;
    }
    Fur(i,1,RT[0])sol(RT[i]),upd(RT[i],-1);
    Fur(i,1,m)out<<ANS[i]<<" ";
}
```

---

