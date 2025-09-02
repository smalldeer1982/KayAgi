# Journey

## 题目描述

One day, Pak Chanek who is already bored of being alone at home decided to go traveling. While looking for an appropriate place, he found that Londonesia has an interesting structure.

According to the information gathered by Pak Chanek, there are $ N $ cities numbered from $ 1 $ to $ N $ . The cities are connected to each other with $ N-1 $ two-directional roads, with the $ i $ -th road connecting cities $ U_i $ and $ V_i $ , and taking a time of $ W_i $ hours to be traversed. In other words, Londonesia's structure forms a tree.

Pak Chanek wants to go on a journey in Londonesia starting and ending in any city (not necessarily the same city) such that each city is visited at least once with the least time possible. In order for the journey to end quicker, Pak Chanek also carries an instant teleportation device for moving from one city to any city that can only be used at most once. Help Pak Chanek for finding the minimum time needed.

Notes:

- Pak Chanek only needs to visit each city at least once. Pak Chanek does not have to traverse each road.
- In the journey, a city or a road can be visited more than once.

## 说明/提示

In the first example, the journey that has the minimum time is $ 2 → 1 \xrightarrow{\text{teleport}} 4 → 3 $ .

In the second example, the journey that has the minimum time is $ 3 → 1 → 4 → 1 → 2 \xrightarrow{\text{teleport}} 5 $ .

## 样例 #1

### 输入

```
4
1 2 4
2 3 5
3 4 4```

### 输出

```
8```

## 样例 #2

### 输入

```
5
1 2 45
1 3 50
1 4 10
1 5 65```

### 输出

```
115```

# 题解

## 作者：E1_de5truct0r (赞：6)

不带传送就是典题，答案是所有边权和 $\times\,2\, -$ 直径长度。

带上传送了，那么 $a \rightarrow b$ 的传送操作明显就是又把一条链省去了。因此这个时候需要在一棵树里选两条链使结果最小。

因为是取并集，显然不能直接做，可以考虑 DP。

但是直接这么做也没啥头绪，尝试找找性质之类的。

性质：两个链分成两种情况：

- 相交在一点：

	![](https://cdn.luogu.com.cn/upload/image_hosting/lob49a9x.png)
    
	直接对这个交点进行考虑。
    
- 不相交：

	![](https://cdn.luogu.com.cn/upload/image_hosting/0gqdg3t8.png)
    
    由于两条链中，有一条是有去无回的 ，中间会漏掉一些点，所以必须让它们最后走到两个相邻的点结束。
    
    两条链之间的这条边不被经过，所以我们可以考虑把每个边定为“儿子 -> 父亲”中，儿子对应的边，然后进行考虑。

相交在一点的情况：

- 考虑换根 DP。无非就是求两个过这个点的最长链的长度之和罢了。

	考虑 $dp_{u,0/1/2/3/4}$ 记录从 $u$ 出发，向下的最长 / 次长 / 第三长 / 第四长的链，以及从 $u$ 向上走的最长链。那么求过 $u$ 的两个最长链，就是选四个最大的拼起来罢了。同时我们要记录这些链的来的方向是哪些儿子，方便后面转移用。
    
    转移：$dp_{u,0/1/2/3}$ 的实质就是打擂台；$dp_{u,4}=\max dp_{fa,0 \sim 4}+W(u,fa)$。
    
    答案统计就是 $\max\limits_{i=1}^{n} \left(\sum\limits_{j \in [0,4]} dp_{i,j}-\min\limits_{j \in [0,4]}dp_{i,j}\right)$。
    
两个链不相交的情况：

- 依然是换根 DP。记录的内容和上面相同，但是这次答案统计不太一样，我们需要求出 $u$ 子树内的直径和子树外的直径。

	$u$ 子树内直径是可以直接求得；子树外的直径 $exc_u$ 也需要换根：
    
    1. 子树外的直径在 $u$ 的父亲 $fa_u$ 的子树外：$exc_u=\max\{exc_u,exc_{fa_u}\}$。
    
    2. 子树外的直径过 $fa_u$：选取 $fa_u$ 的最长的两个不经过 $u$ 的链拼起来。
    
    3. 子树外的直径在 $fa_u$ 的子树内：选取 $fa_u$ 子树内的、不在 $u$ 子树内的最长直径。
    
上述所有内容可以使用三次 dfs 解决。
    
复杂度 $O(n)$。
    
[Code & Submission](https://codeforces.com/contest/1725/submission/211711671)

---

## 作者：_•́へ•́╬_ (赞：6)

赛时漏了一种情况。。。寄

## 思路

不考虑传送，这就是一道原题。

先讲人话：设 $a[i]$ 表示从 $i$ 出发走遍子树再回到 $i$ 的答案，$b[i]$ 表示从 $i$ 出发走遍子树不用回到 $i$ 的答案，$c[i]$ 表示从子树内任何一点出发不用回到 $i$ 的答案。

---------

下面就都不讲人话了。

不讲是因为这个问题等价于挑一条链走一次，其他边走两次。

刚刚的人话翻译一下： 设 $a[i]$ 表示链的两端都是 $i$（链退化成点）的答案，$b[i]$ 表示 $i$ 是链的一个端点的答案，$c[i]$ 表示没有任何限制的答案。

----------------------

下面我们面对传送：

有了传送，我们就要挑两条链了。

这两条链会长啥样？

1. 两条链没有交点。

   此时这两条链必须有两个点相邻，不然就会漏点。而这两个点之间的边一次都不会被经过。

   我们依靠这两个相邻的点统计答案。

2. 两条链有交点。

   就像一个点放射出去四条一样。

   我们依靠这一个点统计答案。

   因为是四条，所以上面的 abc 不够用（只能处理两条），要用 abcde。/mgx

## code

`up` 是换根时从父到子的 dp 数组。

`pfx` `sfx` 是当前节点转移到子节点时用的。因为信息不可减，采用一个前缀一个后缀拼起来。

代码很长。

```cpp
#include<stdio.h>
#define N 100005
#define int long long
#define min(x,y) ((x)<(y)?(x):(y))
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,h[N],e1[N<<1],e2[N<<1],nxt[N<<1];
int a[N],b[N],c[N],upa[N],upb[N],upc[N],ans=1ll<<60;
int sz,pfxa[N],pfxb[N],pfxc[N],sfxa[N],sfxb[N],sfxc[N];
inline void dfs1(const int&i,const int&f)
{
	for(int j=h[i];j;j=nxt[j])if(e1[j]^f)
	{
		dfs1(e1[j],i);
		c[i]=min(min(a[i]+c[e1[j]]+(e2[j]<<1),b[i]+b[e1[j]]+e2[j]),
			c[i]+a[e1[j]]+(e2[j]<<1));
		b[i]=min(b[i]+a[e1[j]]+(e2[j]<<1),a[i]+b[e1[j]]+e2[j]);
		a[i]+=a[e1[j]]+(e2[j]<<1);
	}
}
inline void dfs2(const int&i,const int&f)
{
	sz=1;
	for(int j=h[i];j;j=nxt[j])if(e1[j]^f)
		pfxa[sz]=sfxa[sz]=a[e1[j]]+(e2[j]<<1),
		pfxb[sz]=sfxb[sz]=b[e1[j]]+e2[j],
		pfxc[sz]=sfxc[sz]=c[e1[j]]+(e2[j]<<1),
		++sz;
	pfxa[0]=pfxb[0]=pfxc[0]=0;
	sfxa[sz]=sfxb[sz]=sfxc[sz]=0;
	for(int j=1;j<sz;++j)//前缀
		pfxc[j]=min(min(pfxa[j-1]+pfxc[j],pfxb[j-1]+pfxb[j]),
			pfxc[j-1]+pfxa[j]),
		pfxb[j]=min(pfxa[j-1]+pfxb[j],pfxb[j-1]+pfxa[j]),
		pfxa[j]+=pfxa[j-1];
	for(int j=sz-1;j;--j)//后缀
		sfxc[j]=min(min(sfxa[j+1]+sfxc[j],sfxb[j+1]+sfxb[j]),
			sfxc[j+1]+sfxa[j]),
		sfxb[j]=min(sfxa[j+1]+sfxb[j],sfxb[j+1]+sfxa[j]),
		sfxa[j]+=sfxa[j+1];
	int tmpa,tmpb,tmpc,tmpd,tmpe;
	for(int j=h[i],k=1;j;j=nxt[j])if(e1[j]^f)
	{//处理第一种情况
		tmpa=upa[i];
		tmpb=upb[i];
		tmpc=upc[i];
		tmpc=min(min(tmpa+pfxc[k-1],tmpb+pfxb[k-1]),tmpc+pfxa[k-1]);
		tmpb=min(tmpa+pfxb[k-1],tmpb+pfxa[k-1]);
		tmpa+=pfxa[k-1];
		tmpc=min(min(tmpa+sfxc[k+1],tmpb+sfxb[k+1]),tmpc+sfxa[k+1]);
		tmpb=min(tmpa+sfxb[k+1],tmpb+sfxa[k+1]);
		tmpa+=sfxa[k+1];
		// printf("%d %d %d %d\n",i,e1[j],tmpc,c[e1[j]]);
		ans=min(ans,min(tmpc,min(tmpb,tmpa))+
			min(c[e1[j]],min(b[e1[j]],a[e1[j]])));
		upa[e1[j]]=tmpa+(e2[j]<<1);
		upb[e1[j]]=tmpb+e2[j];
		upc[e1[j]]=tmpc+(e2[j]<<1);
		++k;
	}
	tmpa=upa[i];
	tmpb=upb[i];
	tmpc=tmpd=tmpe=upc[i];
	for(int j=h[i];j;j=nxt[j])if(e1[j]^f)
		tmpe=min(tmpc+c[e1[j]]+(e2[j]<<1),min(tmpd+b[e1[j]]+e2[j],
			tmpe+a[e1[j]]+(e2[j]<<1))),
		tmpd=min(tmpb+c[e1[j]]+(e2[j]<<1),min(tmpc+b[e1[j]]+e2[j],
			tmpd+a[e1[j]]+(e2[j]<<1))),
		tmpc=min(tmpa+c[e1[j]]+(e2[j]<<1),min(tmpb+b[e1[j]]+e2[j],
			tmpc+a[e1[j]]+(e2[j]<<1))),
		tmpb=min(tmpa+b[e1[j]]+e2[j],tmpb+a[e1[j]]+(e2[j]<<1)),
		tmpa+=a[e1[j]]+(e2[j]<<1);
	ans=min(ans,tmpe);//处理第二种情况
	for(int j=h[i];j;j=nxt[j])if(e1[j]^f)dfs2(e1[j],i);
}
main()
{
	read(n);
	for(int i=1,u,v,w;i<n;++i)
	{
		read(u);read(v);read(w);--u;--v;
		e1[i]=v;e2[i]=w;nxt[i]=h[u];h[u]=i;
		e1[i+n]=u;e2[i+n]=w;nxt[i+n]=h[v];h[v]=i+n;
	}
	dfs1(0,0);
	ans=c[0];
	dfs2(0,0);
	printf("%lld",ans);
}
/*a[i] i出发再回到i
 *b[i] i出发不用回到i
 *c[i] 任何一个点出发到任何一个点
 */
```

## 优化

上面那个是按原题意写的。太屎山了。

按转化后的题意，即找两条链使边权和最大，比较好写。

## code

```cpp
#include<stdio.h>
#define N 100005
#define int long long
#define max(x,y) ((x)>(y)?(x):(y))
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,h[N],e1[N<<1],e2[N<<1],nxt[N<<1],a[N],b[N],upa[N],upb[N],ans,sz,sfx[N];
int son[N];
inline void dfs1(const int&i,const int&f)
{
	for(int j=h[i];j;j=nxt[j])if(e1[j]^f)
	{
		dfs1(e1[j],i);
		b[i]=max(b[i],max(b[e1[j]],a[i]+a[e1[j]]+e2[j]));
		a[i]=max(a[i],a[e1[j]]+e2[j]);
	}
}
inline void dfs2(const int&i,const int&f)
{
	sz=1;
	for(int j=h[i];j;j=nxt[j])if(e1[j]^f)son[sz]=j,sfx[sz++]=a[e1[j]]+e2[j];
	sfx[sz]=0;for(int j=sz-1;j;sfx[j]=max(sfx[j+1],sfx[j]),--j);
	int tmpa,tmpb,tmpc,tmpd;
	tmpc=0;tmpa=tmpb=tmpd=upa[i];
	/*a 链，i为链的一端
	 *b 经过i的链
	 *c 不经过i的链
	 *d 不经过i的链 + 链，i为链的一端
	 */
	for(int j=h[i],k=1;j;j=nxt[j])if(e1[j]^f)
	{
		ans=max(ans,max(tmpd,tmpc+sfx[k+1])+a[e1[j]]+e2[j]);
		ans=max(ans,max(max(tmpb,tmpa+sfx[k+1]),upb[i])+b[e1[j]]+(e2[j]<<1));
		tmpd=max(tmpd,max(tmpa+b[e1[j]]+(e2[j]<<1),tmpc+a[e1[j]]+e2[j]));
		tmpc=max(tmpc,b[e1[j]]+(e2[j]<<1));
		upb[e1[j]]=max(upb[i],max(tmpb,tmpa+sfx[k+1]));
		tmpb=max(tmpb,tmpa+a[e1[j]]+e2[j]);
		upa[e1[j]]=max(tmpa,sfx[k+1])+e2[j];
		tmpa=max(tmpa,a[e1[j]]+e2[j]);++k;
	}
	tmpc=0;
	for(int i=1;i<sz;++i)
		upb[e1[son[i]]]=max(upb[e1[son[i]]],tmpc),
		ans=max(ans,tmpc+b[e1[son[i]]]+(e2[son[i]]<<1)),
		tmpc=max(tmpc,b[e1[son[i]]]);
	tmpb=tmpc=0;
	for(int i=sz-1;i;--i)
		upb[e1[son[i]]]=max(upb[e1[son[i]]],max(tmpb,tmpc)),
		ans=max(ans,tmpc+b[e1[son[i]]]+(e2[son[i]]<<1)),
		tmpb=max(tmpb,sfx[i+1]+a[e1[son[i]]]+e2[son[i]]),
		tmpc=max(tmpc,b[e1[son[i]]]);
	tmpa=tmpb=upa[i];
	for(int j=h[i],k=1;j;j=nxt[j])if(e1[j]^f)
	{
		ans=max(ans,tmpb+a[e1[j]]+e2[j]+sfx[k+1]);
		tmpb=max(tmpb,tmpa+a[e1[j]]+e2[j]);
		tmpa=max(tmpa,a[e1[j]]+e2[j]);++k;
	}
	for(int j=h[i];j;j=nxt[j])if(e1[j]^f)dfs2(e1[j],i);
}
main()
{
	read(n);
	for(int i=1,u,v,w;i<n;++i)
	{
		read(u);read(v);read(w);--u;--v;
		e1[i]=v;e2[i]=w;nxt[i]=h[u];h[u]=i;
		e1[i+n]=u;e2[i+n]=w;nxt[i+n]=h[v];h[v]=i+n;
	}
	dfs1(0,0);ans=b[0];dfs2(0,0);
	ans=-ans;for(int i=1;i<n;ans+=e2[i++]<<1);
	printf("%lld",ans);
}
/*a[i] i为链的一端
 *b[i] i子树内的链
 *upa[i] i为链的一端，但是子树外
 *upb[i] 经过i的链，但是子树外
 */
```

---

## 作者：MatrixCascade (赞：5)

赛时听了队友的转换题意就去写了，结果发现一直 WA on 23/ll。赛后才发现是少考虑了一种情况/ll。

首先如果没有这个瞬移操作的话，那么答案显然就是所有边权之和 *2-直径长度。

然后考虑带上瞬移的话。

第一种情况就是两个路径没有交点的情况。选择一个点，先对这个点的子树做一遍没有瞬移的算法，再对整棵树去除掉这棵子树剩下的树做一次没有瞬移的算法，我们保证可以瞬移到一个合适的位置使得剩下的子树可以用无瞬移的算法来做。这部分的答案就是 $all\times 2-d1-d2-2e$，$all$ 是边权总和，$d1$ 是这个点子树的直径，$d2$ 是整棵树去除这个点的子树的直径，$e$ 是这个点和他父亲那条边的边权。

然后就是第二种情况，就是两条路径有交点，显然只能有一个交点。枚举整个交点，这里答案就很显然了，为 $all\times 2-sum4_x$（$sum4_x$ 是以 $x$ 为端点的前 $4$ 长链）

然后可以换根 dp 解决这个问题。设 $f_{x,0/1/2/3},g_{x,0/1/2/3}$ 表示 $x$ 点开始，**子树内**的前四条链长度以及是 $x$ 的哪一个儿子。$up_x$ 表示 $x$ 点开始，第一步向上走的最长链长度。$p_{x,0/1},q_{x,0/1}$ 表示 $x$ 的前 $2$ 大直径的子树以及是哪一个子树。$d_x$ 表示 $x$ 子树的直径。每次按照定义直接转移即可。

这样讲可能有点抽象，[代码](https://codeforces.com/contest/1725/submission/170934763)。（感觉还算清晰）

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

给定一颗边带长度的树，你需要从一个点出发，沿着树上的边遍历所有点，中途有一次直接从点 $x$ 瞬移到点 $y$ 的机会（$x,y$ 任意取），求经过边长度之和的最小值。

## 题目分析

拿到这种题，可以用很标准的思路来思考，具体如下。

- 标准思路第一步：题目增加了一个操作，则考虑如果没有这个操作，题目该怎么做。

如果没有瞬移操作，则我们可以考虑枚举起点 $x$，将其做为根，然后考虑策略。

显然，走的过程一定是从 $x$ 出发，走到一个儿子，遍历那个儿子的子树，然后回到 $x$，继续遍历下一个儿子的子树，再回到 $x$，只有最后一个子树不需要回到 $x$。

对于点 $i$，如果要从 $i$ 出发，遍历子树内所有节点后回到 $i$，可以递归考虑：$i$ 走到某个儿子，花费边权，走完儿子的子树后，返回 $i$，再花费这个边权。这样总花费就是 $i$ 的子树的边权和的两倍。

所以“最后一个子树不需要回到 $x$”就是将最后一个儿子与 $x$ 的连边的边权省掉了，然后递归处理那个儿子的子树。

最终被省掉的边集构成一条链，我们自然要选择直径省去。

- 标准思路第二步：考虑这种分析的本质，并思考操作对其的影响。

显然以起点为根，则相当于起点附带了一个标记，可以使得省掉一条与儿子相连的边的边权，并把这个标记下传到这个儿子。

瞬移操作则相当于刷新了这个标记。

这样我们就有如下策略：

- 将树分为两个连通块，跑完一个连通块，瞬移到另一个连通块，两个连通块分别找直径，效果是连接两个连通块的边完全不用走。

- 选择两条链，它们交于一点，两条链都可以省掉。

如果有其它策略的话，都可以转换为以上策略。

这些信息都可以换根 $O(n)$ 处理。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N=2e5+5;
int n,h[N],to[N<<1],nxt[N<<1],cnt,w[N<<1],sum,f[N],mx[N],dep[N],ans;
inline void add_(int a,int b,int c){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,w[cnt]=c;
}
inline void dfs(int x,int fa){
	mx[x]=dep[x];
	e(x)if(y^fa)dep[y]=dep[x]+w[i],dfs(y,x),f[x]=max({f[x],f[y],mx[x]+mx[y]-dep[x]*2}),mx[x]=max(mx[x],mx[y]);
}
inline void Dfs(int x,int fa,int Mx,int Dep){
	vector<int>p,q,mxp,mxs,dp,ds;
	p.pb(0),q.pb(0);
	e(x)if(y^fa)p.pb(y),q.pb(w[i]);
	p.pb(0),q.pb(0);
	int siz=p.size();mxp.resize(siz+1),mxs.resize(siz+1);
	dp.resize(siz+1),ds.resize(siz+1);
	siz-=2,mxp[0]=mxs[siz+1]=Mx,dp[0]=ds[siz+1]=0;
	int mmx=Dep,se=0,th=0,ft=0;
	rep(i,1,siz){
		int y=p[i],d=mx[y]-dep[x];
		mxp[i]=max({mxp[i-1],dp[i-1]+d,f[y],Dep+d});
		dp[i]=max(dp[i-1],d);
		if(d>=mmx)ft=th,th=se,se=mmx,mmx=d;
		else if(d>=se)ft=th,th=se,se=d;
		else if(d>=th)ft=th,th=d;
		else ft=max(ft,d);
	}
	per(i,siz,1){
		int y=p[i];
		mxs[i]=max({mxs[i+1],ds[i+1]+mx[y]-dep[x],f[y],Dep+mx[y]-dep[x]});
		ds[i]=max(ds[i+1],mx[y]-dep[x]);
	}
	ans=min(ans,sum-mmx-se-th-ft);
	rep(i,1,siz){
		int y=p[i],L=max({Dep,dp[i-1],ds[i+1]})+q[i],len=max({mxp[i-1],mxs[i+1],dp[i-1]+ds[i+1]});
		ans=min(ans,sum-len-f[y]-q[i]*2);
		Dfs(y,x,max(len,L),L);
	}
}
signed main(){
	n=read();
	rep(i,2,n){
		int x=read(),y=read(),w=read();
		add_(x,y,w),add_(y,x,w),sum+=w*2;
	}
	ans=sum-f[1],dfs(1,0),Dfs(1,0,0,0),cout <<ans;
	return 0;
}
```

---

