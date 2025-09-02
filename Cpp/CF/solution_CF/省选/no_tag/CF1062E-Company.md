# Company

## 题目描述

公司 $X$ 有 $n$ 名员工，编号从 $1$ 到 $n$。每个员工 $u$ 都有一个直属上司 $p_u$（$1 \le p_u \le n$），但员工 $1$ 没有上司。保证所有 $p_i$ 构成一棵树。若员工 $u$ 是员工 $v$ 的直属上司，或存在某个员工 $w$，使得 $w$ 负责 $v$，且 $u$ 是 $w$ 的直属上司，则称 $u$ 负责 $v$。此外，任何员工都被认为负责自己。

对于每个员工 $u$，定义其级别 $lv(u)$ 如下：

- $lv(1)=0$
- $lv(u)=lv(p_u)+1$，其中 $u \neq 1$

未来公司有 $q$ 个可能的运营方案。第 $i$ 个方案包含两个整数 $l_i$ 和 $r_i$，表示编号在区间 $[l_i, r_i]$ 内的所有员工（且仅这些员工）参与该方案。为了顺利执行方案，必须有一名项目经理，且该项目经理需要负责所有参与的员工。即，若选择员工 $u$ 作为第 $i$ 个方案的项目经理，则对于每个 $v \in [l_i, r_i]$，$u$ 必须负责 $v$。注意，$u$ 不一定在 $[l_i, r_i]$ 区间内。此外，$u$ 总是选择级别 $lv(u)$ 尽可能大的员工（级别越高，工资越低）。

在任何方案执行前，公司让 JATC 检查了他们的方案。JATC 一眼就发现，对于每个方案，都可以恰好减少一名参与员工而不影响方案的执行。公司出于节省成本的目的，询问 JATC 应该将哪位员工从方案中剔除，才能使所需项目经理的级别最大。JATC 已经知道答案，现在挑战你来解决这个问题。

## 说明/提示

例如：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1062E/4564b9c828c9be95a53a01799338a14403d69e77.png)

在第一个询问中，可以选择剔除 $4$、$5$ 或 $6$，此时项目经理为 $3$。

在第二个询问中，若剔除除 $8$ 以外的任意员工，项目经理为 $1$。若剔除 $8$，项目经理为 $3$。由于 $lv(3)=1 > lv(1)=0$，所以选择剔除 $8$ 最优。

在第三个询问中，无论剔除哪位员工，项目经理都只能是 $1$。

在第四个询问中，若剔除 $9$ 或 $10$，项目经理为 $3$；若剔除 $11$，项目经理为 $7$。由于 $lv(7)=3>lv(3)=1$，所以选择剔除 $11$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
11 5
1 1 3 3 3 4 2 7 7 6
4 6
4 8
1 11
9 11
8 11
```

### 输出

```
4 1
8 1
1 0
11 3
8 1
```

# 题解

## 作者：zhoukangyang (赞：19)

[来蒟蒻的博客园里看 /kel](https://www.cnblogs.com/zkyJuruo/p/13910393.html)

## $\texttt{Solution}$
数据结构学傻的蒟蒻来写一个新思路

这题的正解是利用多个结点的 $lca$ 是 $dfs$ 序最大的结点和 $dfs$ 序最小的结点的 $lca$。但是这里考虑如何不用这种方法。

首先用线段树合并处理出在每一个结点的子树里面的点。

答案分为两种情况：

### 1. 包含结点 $l$。
那么我们可以以 $l$ 为起点向上跳。找到第一个大小 $\ge r - l$ 的结点 $p$。然后在结点 $p$ 上面二分找到是没有选哪个结点。

### 2. 包含除了结点 $l$ 外的所有结点。

那么我们可以以 $l$ 为起点向上跳。找到第一个大小 $\ge r - l$ 的结点 $p$。这样子的答案就是 $l$。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define L(i, j, k) for(int i = (j), i##E = (k); i <= i##E; i++) 
#define R(i, j, k) for(int i = (j), i##E = (k); i >= i##E; i--) 
#define ll long long 
#define db double
#define mkp make_pair 
const int N = 2e5 + 7;
const int M = 8e6 + 7;
int n, m, fa[N], siz[N], dep[N], jp[20][N];
int head[N], edge_id;
int hd[N], sum[M], ch[M][2], tot;
struct node { int to, next; } e[N << 1];
void add_edge(int u, int v) { ++edge_id, e[edge_id].next = head[u], e[edge_id].to = v, head[u] = edge_id; }
void add(int &x, int L, int R, int wz) {
    if(!x) x = ++tot;
    sum[x]++;
    if(L == R) return;
    int mid = (L + R) / 2;
    if(wz <= mid) add(ch[x][0], L, mid, wz);
    else add(ch[x][1], mid + 1, R, wz);
}
int merge(int x, int y) {
    if(!x || !y) return x | y;
    int nw = ++tot;
    sum[nw] = sum[x] + sum[y];
    ch[nw][0] = merge(ch[x][0], ch[y][0]);
    ch[nw][1] = merge(ch[x][1], ch[y][1]);
    return nw;
}
int query(int x, int L, int R, int l, int r) {
    if(!x) return 0;
    if(l <= L && R <= r) return sum[x];
    int mid = (L + R) / 2, res = 0;
    if(l <= mid) res += query(ch[x][0], L, mid, l, r);
    if(r > mid) res += query(ch[x][1], mid + 1, R, l, r);
    return res;
}
void dfs(int x) {
    siz[x] = 1, add(hd[x], 1, n, x);
    for(int i = head[x]; i; i = e[i].next) {
        int v = e[i].to; 
        dep[v] = dep[x] + 1, dfs(v), siz[x] += siz[v];
        // cout << " ? \n";
        hd[x] = merge(hd[x], hd[v]);
        // cout << " ! \n";
    }
}
int get(int x, int l, int r, int y) {
    int nowans = query(hd[x], 1, n, l, r);
    if(nowans > y) return 0;
    if(nowans == y) return x;
    int now = x;
    R(i, 18, 0) if(jp[i][now] && query(hd[jp[i][now]], 1, n, l, r) < y) now = jp[i][now];
    now = fa[now];
    if(query(hd[now], 1, n, l, r) != y) return 0;
    return now;
}
int main() {
    scanf("%d%d", &n, &m);
    L(i, 2, n) scanf("%d", &fa[i]), add_edge(fa[i], i), jp[0][i] = fa[i];
    L(i, 1, 18) L(j, 1, n) jp[i][j] = jp[i - 1][jp[i - 1][j]];
    dfs(1);
    while(m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        int resa = get(l + 1, l + 1, r, r - l), resb = get(l, l, r, r - l);
         // 1 : not contain l
        if(dep[resa] >= dep[resb]) printf("%d %d\n", l, dep[resa]);
         // 2 : contain l
        else {
            int L = l, R = r;
            while(L < R) {
                int mid = (L + R) / 2;
                if(query(hd[resb], 1, n, L, mid) != mid - L + 1) R = mid;
                else L = mid + 1;
            }
            printf("%d %d\n", L, dep[resb]);
        }
    }
    return 0;
}
```

---

## 作者：hegm (赞：11)

### [$\texttt{Company}$](https://www.luogu.com.cn/problem/CF1062E)

区间 $\text{LCA}$ 模板题（的加强？）。

考虑区间 $\text{LCA}$。

区间 $\text{LCA}$ 等于什么捏？

我们抽象一个二叉树。

![xqTYk9.png](https://s1.ax1x.com/2022/11/04/xqTYk9.png)

假如让你求 $8,9,10,11$ 的 $\text{LCA}$，你会怎么求那。

通过观察，我们发现，他们的 $\text{LCA}$，等效于 $8,11$ 的 $\text{LCA}$，那么这样有什么性质哪？

我们假定给他们一个横坐标，那么 $8$ 是横坐标最小的点， $11$ 是横坐标最大的点。

这样的话他们的 $\text{LCA}$ 就会最高。

毫无疑问最高的——两点 $\text{LCA}$，就是区间的 $\text{LCA}$。

![xqTsTH.png](https://s1.ax1x.com/2022/11/04/xqTsTH.png)

那么问题就来了，如何求出横坐标最小和最大的两个点哪？

我们考虑对树进行 $\text{dfs}$。那么 $dfn$ 最小的一定是最左侧的吗？

但是遗憾的是，$dfn$ 最小的不一定是最左侧的。（区间 $4-8$，$dfn$ 最小的是 $4$ 而不是 $8$）。

但是没有关系，因为 $dfn$ 最小的点($4$) 一定是最左端点的祖先($8$)。

根据 $\text{LCA}$ 的本质，求两点间的 $\text{LCA}$ 就是一步一步的向上跳，那么起点从 $8\to4$ 相当于我们提前跳了一步，同时保证不会跳过头（因为 $4$ 也在要求的区间内，我们求 $4$ 和 $11$ 的 $\text{LCA}$ 一定不会超过答案）。
右侧依然同理。

然后就可以用你喜欢的方式维护区间最大最小 $dfn$ 序啦![](//啧.tk/qq)


以上即为求区间 $\text{LCA}$ 的方法，现在的问题是删除一个点，使得他们的 $\text{LCA}$ 最深，根据上面的性质，我们知道只有 $dfn$ 最大最小的点才会造成贡献，那么我们考虑删掉一个，让最大和次小，次大和最小求出 $\text{LCA}$，两者取一下 $\max deep$ 就好啦。

### $\text{CODE}$
```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,q,tot,head[N],dep[N],dfn[N],fa[N][20],cnt,mx[N][20],smx[N][20],mn[N][20],smn[N][20],len[20],t[N];
struct node
{
	int from,to,next;
}k[N];
void add(int from,int to)
{
	k[++tot].to=to;
	k[tot].from=from;
	k[tot].next=head[from];
	head[from]=tot;
}
void dfs(int now,int f)
{
	dep[now]=dep[f]+1;
	fa[now][0]=f;
	dfn[now]=++cnt;
	t[cnt]=now;
	for(int i=1;i<=19;i++)fa[now][i]=fa[fa[now][i-1]][i-1];
	for(int i=head[now];i;i=k[i].next)dfs(k[i].to,now);
}
int lca(int a,int b)
{
	a=t[a],b=t[b];
	if(dep[a]<dep[b])swap(a,b);
	for(int i=19;i>=0;i--)if(dep[fa[a][i]]>=dep[b])a=fa[a][i];
	if(a==b)return dep[a];
	for(int i=19;i>=0;i--)if(fa[a][i]!=fa[b][i])a=fa[a][i],b=fa[b][i];
	return dep[fa[a][0]];
}
int main()
{
	n=read();q=read();
	len[0]=1;
	for(int i=1;i<=19;i++)len[i]=2*len[i-1];
	for(int i=2,x;i<=n;i++)
	{
		x=read();
		add(x,i); 
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		mx[i][0]=dfn[i];
		mn[i][0]=dfn[i];
		smx[i][0]=0;
		smn[i][0]=10000000;
	}
	for(int j=1;j<=19;j++)
	{
		for(int i=1;i+len[j]-1<=n;i++)
		{
			mx[i][j]=max(mx[i][j-1],mx[i+len[j-1]][j-1]);
			mn[i][j]=min(mn[i][j-1],mn[i+len[j-1]][j-1]);
			smx[i][j]=max(min(mx[i][j-1],mx[i+len[j-1]][j-1]),max(smx[i][j-1],smx[i+len[j-1]][j-1]));
			smn[i][j]=min(max(mn[i][j-1],mn[i+len[j-1]][j-1]),min(smn[i][j-1],smn[i+len[j-1]][j-1]));
		}
	}
	while(q--)
	{
		int l=read(),r=read(),a=log2(r-l+1);
		int nmx=max(mx[l][a],mx[r-len[a]+1][a]),nmn=min(mn[l][a],mn[r-len[a]+1][a]);
		int nsx=max(smx[l][a],smx[r-len[a]+1][a]),nsn=min(smn[l][a],smn[r-len[a]+1][a]);
		if(mx[r-len[a]+1][a]!=mx[l][a])nsx=max(nsx,min(mx[l][a],mx[r-len[a]+1][a]));
		if(mn[l][a]!=mn[r-len[a]+1][a])nsn=min(nsn,max(mn[l][a],mn[r-len[a]+1][a]));
		int ans1=lca(nmx,nsn),ans2=lca(nsx,nmn);
		if(ans1>ans2)cout<<t[nmn]<<" "<<ans1-1<<"\n";
		else cout<<t[nmx]<<" "<<ans2-1<<"\n";
	}
	return 0;
}
```

这里用的 $\text{ST}$ 表维护的，写麻了![](//啧.tk/kun)

---

## 作者：wgyhm (赞：8)

# 【Tree 记录】 CF1062E Company

## Description

给定一颗树，有若干个询问，每个询问给出 $l$ ,$r$，要求编号在 $[l,r]$ 中的点任意删去一个之后剩余点的 LCA 深度最大，输出删去点的编号和 LCA 的最大深度。

$1\le n,m\le 10^5$，时限 $3s$。

## Solution

考虑删掉一个点后，LCA 为 $x$，那么剩下的点一定在 $x$ 的子树内，也就是 $\text{dfn}$ 一定在 $[\text{dfn}_x,\text{dfn}_x+\text{size}_x-1]$ 。

如果删掉点后改变 $x$ ，也就是删掉的点的 $dfn$ 不在 $[\text{dfn}_x,\text{dfn}_x+\text{size}_x-1]$，所以只需要删掉 $\text{dfn}$ 最大或者最小的，比较一下就好了。

区间 LCA 用 ST 表维护，复杂度：$O(n\log^2n+m\log n)$。

## Code

```cpp
#define maxn 100005
int dfn[maxn],times,lg[maxn];
int h[maxn],head=1,n,m;
struct yyy{
	int to,z;
	inline void add(int x,int y){
		to=y;z=h[x];h[x]=head;
	}
}a[maxn*2];
namespace LCA{
    int fa[maxn][21],deep[maxn];
    inline void dfs(int x,int pre){
    	rg int i;deep[x]=deep[pre]+1;fa[x][0]=pre;dfn[x]=++times;
    	for (i=1;i<=lg[deep[x]];i++) fa[x][i]=fa[fa[x][i-1]][i-1];
    	for (i=h[x];i;i=a[i].z) if (a[i].to^pre) dfs(a[i].to,x);
	}
	inline void init(void){
		rg int i;for (i=2;i<=n;i++) lg[i]=lg[i/2]+1;
		dfs(1,0);
	}
	inline int lca(int x,int y){
		if (!x||!y) return max(x,y);
		if (deep[x]<deep[y]) swap(x,y);
		while (deep[x]>deep[y]) x=fa[x][lg[deep[x]-deep[y]]];
		if (x==y) return x;
		for (rg int i=lg[deep[x]];i>=0;i--) 
		    if (fa[x][i]^fa[y][i]) x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
}
using namespace LCA;
namespace Segment{
    struct yyy{
    	int Min,Max,id1,id2;
    	yyy(int x=1e9,int y=0,int a=0,int b=0){
    		Min=x;Max=y;id1=a;id2=b;
		}
		yyy operator +(const yyy &x) const{
		    yyy ans;
		    if (Min<x.Min) ans.Min=Min,ans.id1=id1;else ans.Min=x.Min,ans.id1=x.id1;
		    if (Max>x.Max) ans.Max=Max,ans.id2=id2;else ans.Max=x.Max,ans.id2=x.id2;
		    return ans;
		}
	}f[maxn<<2],tmp;
	inline void Build(int l,int r,int rt){
		if (l==r) {f[rt].Min=f[rt].Max=dfn[l];f[rt].id1=f[rt].id2=l;return;}
		int mid=l+r>>1;
		Build(l,mid,rt<<1);
		Build(mid+1,r,rt<<1|1);
		f[rt]=f[rt<<1]+f[rt<<1|1];
	}
	inline yyy Query(int l,int r,int rt,int head,int tail){
	    if (head<=l&&r<=tail) return f[rt];
	    int mid=l+r>>1;
	    if (head<=mid&&mid<tail){
	    	yyy tmp1=Query(l,mid,rt<<1,head,tail),tmp2=Query(mid+1,r,rt<<1|1,head,tail);
	    	return tmp1+tmp2;
		}
		else if (head<=mid) return Query(l,mid,rt<<1,head,tail);
		else return Query(mid+1,r,rt<<1|1,head,tail);
	}
}
namespace ST{
    int f[maxn][21];
    inline void init(void){
    	rg int i,j;
    	for (i=1;i<=n;i++) f[i][0]=i;
    	for (j=1;j<=20;j++)
    	    for (i=1;i+(1<<j)-1<=n;i++)
    	        f[i][j]=lca(f[i][j-1],f[i+(1<<j-1)][j-1]);
	}
	inline int query(int l,int r){
		if (l>r) return 0;
		int z=lg[r-l+1];
		return lca(f[l][z],f[r-(1<<z)+1][z]);
	}
}
signed main(){
    rg int i,x,y,l,r,sum1,sum2,tmp1,tmp2;
    read(n);read(m);
    for (i=2;i<=n;i++) read(x),a[++head].add(x,i),a[++head].add(y,i); 
    LCA::init();
    Segment::Build(1,n,1);
    ST::init();
    while (m--){
    	read(l);read(r);
    	Segment::tmp=Segment::Query(1,n,1,l,r);
    	tmp1=Segment::tmp.id1;tmp2=Segment::tmp.id2;
    	sum1=lca(ST::query(l,tmp1-1),ST::query(tmp1+1,r));
		sum2=lca(ST::query(l,tmp2-1),ST::query(tmp2+1,r));
    	if (deep[sum1]>deep[sum2]) printf("%d %d\n",tmp1,deep[sum1]-1);
    	else printf("%d %d\n",tmp2,deep[sum2]-1);
	}
    return 0;
}
```





---

## 作者：lzyqwq (赞：5)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17809069.html)**

来一个小丑做法，不用观察太多性质，符合像我这样 DS 学魔怔的蒟蒻体质，目前题解区没有看到，麻烦管理再单独开一下题解通道。

**[洛谷](https://www.luogu.com.cn/problem/CF1062E) [CF](https://codeforces.com/problemset/problem/1062/E)**

> - 给出一棵 $n$ 个点的有根树以及 $q$ 次询问，每次询问给出 $l,r$，你要去掉 $[l,r]$ 中的一个点，使得剩余点 $\text{LCA}$ 的深度最大。
>
> - $n,q\le 10^5$。

我们考虑怎样的点可以成为 $\text{LCA}$，显然它一定在 $l$ 到根的路径、$r$ 到根的路径的并集中。因为只能删去一个点，所以最终的 $\text{LCA}$ 一定是 $l,r$ 中至少一个点的祖先。

称点 $u$ 向上走 $k$ 条边到达的点为 $u$ 的 $k$ 级祖先，不难发现答案具有单调性。即，若 $u$ 的 $k$ 级祖先能成为**公共祖先**，则 $u$ 的 $k+1$ 级祖先也可以成为公共祖先。

考虑对两条根链分别二分出最近的祖先。一个点 $u$ 能成为剩余点的祖先，当且仅当其子树中 $[l,r]$ 内的点个数 $\ge r-l$。若个数 $=r-l+1$，则删去任意一个点。若个数 $=r-l$，则删去那个缺失的点。否则，我若任意删除 $[l,r]$ 内的一个点，剩余点中都存在一个点，使得 $u$ 不是它的祖先。

所以判定可以转化为子树数点，用 dfs 序拍平上主席树维护即可。

二分出来两个级别后，选择深度较大的 $k$ 级祖先即可。

但是这题还要输出删除哪个点。我们记选择的祖先为 $anc$。若 $anc$ 子树内包含了 $[l,r]$ 的所有点，则任意输出一个即可。否则考虑找到那个没出现的点。

这个问题等价于在区间内找到给定值域内最小的未出现的数。设它为 $x$，则 $x$ 一定是一个最小的数，满足 $[l,x]$ 内的数没有全部出现过。同样具有单调性，可以二分再使用主席树判定，复杂度瓶颈不变，但是常数太大了，会[被卡](https://codeforces.com/contest/1062/submission/231266408)。

所以我们在主席树上带边界地二分，这样单次找数的时间复杂度为 $\mathcal{O}(\log n)$。瓶颈的常数会除以 $2$。

但是这样你还是会[在最后一个点被卡](https://codeforces.com/contest/1062/submission/231266732)。

我们发现最后一个点是链，因此直接特判链的情况即可。

由于 CF 特殊的构造链的方式（点 $i$ 的父亲是 $i-1$），可以方便我们的判断，以及回答的时候直接输出两个 $l$ 即可。

若链构造得更加一般，就 dfs 判定每个点是否只有一个儿子，回答的时候删去深度最小的点，$\text{LCA}$ 的深度为深度次小的点，用一棵线段树维护。笔者没有实现过，这部分有错还希望能够提出来。

然后就可以配合卡常通过此题。时间复杂度为 $\mathcal{O}(n\log  ^2 n)$，空间复杂度为 $\mathcal{O}(n\log n)$。

**[提交记录（含代码）](https://codeforces.com/contest/1062/submission/231266972)**

---

## 作者：ywy_c_asm (赞：3)

~~md真降智了……删dfn最小或最大的点就行了……~~

那我就来个数据结构学傻了的代码6个多K的辣鸡做法吧……

首先，我们可以知道$[l,r]$的$LCA$，这个由于$LCA$是可合并的拿个线段树可以维护（需要用$O(1)LCA$）。如果这个$LCA\in [l,r]$那肯定删的就是$LCA$，否则假设我们知道$[l,r]$构成的极大连通块（和虚树的区别就是包含所有经过的点）$T$，考虑$LCA$在$T$上的儿子，如果它有多于2个儿子那显然不管删哪个点得到的都还是这个$LCA$。否则的话，它一定有两个儿子$a$和$b$，考虑它们的子树，那肯定是要删子树内只有一个点在$[l,r]$内的那个点才会使答案改变，讨论一下即可。

考虑上述操作怎么实现，首先我们可以用线段树合并知道子树内$[l,r]$的点的信息，并且如果只有一个点的话可以线段树上二分找到这个点。然后考虑怎么处理$LCA$在$T$上的儿子，我们肯定不能每次暴力扫一遍儿子，这会被菊花卡。然而，我们知道如果把树树链剖分一下的话一个点最多只有一个重儿子（这个可以直接特判），而轻儿子是可以支持动态维护的，那么就有了一个做法：离线把询问存在右端点上，然后扫描线，我们希望知道$LCA$有哪些轻儿子满足在子树里存在$[l,r]$内的点，那么我们令每个轻儿子的点权是子树内$<=$当前右端点的最大值（这样如果$>=l$就说明子树内存在$[l,r]$的点），我们每扫到一个$r$就跳链把所有重链链顶的点权改成$r$即可，然后我们只要在$LCA$处维护点权最大的2个或3个即可，这可以在每个点开个支持修改的可删堆维护轻儿子。然后就$O(n\log^2n)$做完了，瓶颈在于链剖维护轻儿子。

上代码~（格式化后有10K……）

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define N 100011
#define ls(_o) (_o << 1)
#define rs(_o) ((_o << 1) | 1)
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	typedef struct _b {
	    int dest;
	    int nxt;
	} bian;
	bian memchi[1000001];
	int gn = 1, heads[N], dfn[N], fan[N], size[N], zhongson[N], st[N * 2][18], lg[N * 2], gdfn = 1;
	inline void add(int s, int t) {
	    memchi[gn].dest = t;
	    memchi[gn].nxt = heads[s];
	    heads[s] = gn;
	    gn++;
	}
	int early[N], late[N], top[N], gstp = 1, rt[N], lef[10000001], rgh[10000001], data[10000001], gseg = 1;
	inline int lca(int a, int b) {
	    if (!(a && b))
	        return (a | b);
	    if (dfn[a] > dfn[b])
	        swap(a, b);
	    a = early[a];
	    b = late[b];
	    int g = lg[b - a + 1];
	    return (fan[min(st[a][g], st[b - (1 << g) + 1][g])]);
	}
	int lcas[1000001];
	void build(int l, int r, int tree) {
	    if (l == r) {
	        lcas[tree] = l;
	        return;
	    }
	    int mid = (l + r) >> 1;
	    build(l, mid, ls(tree));
	    build(mid + 1, r, rs(tree));
	    lcas[tree] = lca(lcas[ls(tree)], lcas[rs(tree)]);
	}
	int query(int rl, int rr, int l, int r, int tree) {
	    if (rl > rr)
	        return (0);
	    if (rl == l && rr == r)
	        return (lcas[tree]);
	    int mid = (l + r) >> 1;
	    if (rl > mid)
	        return (query(rl, rr, mid + 1, r, rs(tree)));
	    if (rr <= mid)
	        return (query(rl, rr, l, mid, ls(tree)));
	    return (lca(query(rl, mid, l, mid, ls(tree)), query(mid + 1, rr, mid + 1, r, rs(tree))));
	}
	void insert(int l, int r, int &tree, int pt) {
	    if (!tree)
	        tree = gseg, gseg++;
	    data[tree]++;
	    if (l == r)
	        return;
	    int mid = (l + r) >> 1;
	    if (pt <= mid)
	        insert(l, mid, lef[tree], pt);
	    else
	        insert(mid + 1, r, rgh[tree], pt);
	}
	int qdat(int rl, int rr, int l, int r, int tree) {
	    if (!data[tree])
	        return (0);
	    if (rl == l && rr == r)
	        return (data[tree]);
	    int mid = (l + r) >> 1;
	    if (rl > mid)
	        return (qdat(rl, rr, mid + 1, r, rgh[tree]));
	    if (rr <= mid)
	        return (qdat(rl, rr, l, mid, lef[tree]));
	    return (qdat(rl, mid, l, mid, lef[tree]) + qdat(mid + 1, rr, mid + 1, r, rgh[tree]));
	}
	int united(int a, int b) {
	    if (!(a && b))
	        return (a | b);
	    int me = gseg;
	    gseg++;
	    data[me] = data[a] + data[b];
	    lef[me] = united(lef[a], lef[b]);
	    rgh[me] = united(rgh[a], rgh[b]);
	    return (me);
	}
	int qfirst(int rl, int rr, int l, int r, int tree) {
	    if (!data[tree])
	        return (0);
	    if (l == r)
	        return (l);
	    int mid = (l + r) >> 1;
	    if (rl == l && rr == r) {
	        if (data[lef[tree]])
	            return (qfirst(l, mid, l, mid, lef[tree]));
	        return (qfirst(mid + 1, r, mid + 1, r, rgh[tree]));
	    }
	    if (rl > mid)
	        return (qfirst(rl, rr, mid + 1, r, rgh[tree]));
	    if (rr <= mid)
	        return (qfirst(rl, rr, l, mid, lef[tree]));
	    int cjr = qfirst(rl, mid, l, mid, lef[tree]);
	    if (cjr)
	        return (cjr);
	    return (qfirst(mid + 1, rr, mid + 1, r, rgh[tree]));
	}
	typedef struct _p {
	    int a;
	    int b;
	    _p(int i, int j) {
	        a = i;
	        b = j;
	    }
	    friend bool operator<(const _p &a, const _p &b) {
	        if (a.b != b.b)
	            return (a.b < b.b);
	        return (a.a < b.a);
	    }
	    friend bool operator==(const _p &a, const _p &b) { return (a.a == b.a && a.b == b.b); }
	} pair;
	typedef struct _heap {
	    priority_queue<pair> me, del;
	    inline void wh() {
	        while (!me.empty() && !del.empty() && me.top() == del.top()) me.pop(), del.pop();
	    }
	    inline void push(pair x) { me.push(x); }
	    inline int size() { return (me.size() - del.size()); }
	    inline pair top() {
	        wh();
	        return (me.top());
	    }
	    inline void erase(pair x) { del.push(x); }
	    inline void pop() {
	        wh();
	        me.pop();
	    }
	} heap;
	heap chs[100001];
	int n;
	int deep[N];
	int lst[N], fa[N];
	void dfs(int pt, int baba) {
	    size[pt] = 1;
	    int mx = 0, best = 0;
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        deep[memchi[i].dest] = deep[pt] + 1;
	        dfs(memchi[i].dest, pt);
	        size[pt] += size[memchi[i].dest];
	        rt[pt] = united(rt[pt], rt[memchi[i].dest]);
	        if (size[memchi[i].dest] > mx)
	            mx = size[memchi[i].dest], best = memchi[i].dest;
	    }
	    insert(1, n, rt[pt], pt);
	    top[pt] = pt;
	    zhongson[pt] = best;
	    lst[pt] = -1;
	}
	int anspt[N], anss[N];
	void efs(int pt, int baba) {
	    if (zhongson[pt])
	        top[zhongson[pt]] = top[pt], efs(zhongson[pt], pt);
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba || zhongson[pt] == memchi[i].dest)
	            continue;
	        efs(memchi[i].dest, pt);
	    }
	}
	vector<pair> vec[N];  // a->l,b->id
	void ffs(int pt, int baba) {
	    dfn[pt] = gdfn;
	    fan[gdfn] = pt;
	    gdfn++;
	    st[gstp][0] = dfn[pt];
	    gstp++;
	    early[pt] = late[pt] = gstp - 1;
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (memchi[i].dest == baba)
	            continue;
	        ffs(memchi[i].dest, pt);
	        st[gstp][0] = dfn[pt];
	        late[pt] = gstp;
	        gstp++;
	    }
	}
	inline int calc(int l, int r, int x) { return (lca(query(l, x - 1, 1, n, 1), query(x + 1, r, 1, n, 1))); }
	vector<int> tmp;
	inline void clear(vector<int> &v) {
	    vector<int> ff;
	    v = ff;
	}
	void ywymain() {
	    n = get();
	    int q = get();
	    for (register int i = 2; i <= n; i++) add(fa[i] = get(), i);
	    ffs(1, 0);
	    gstp--;
	    lg[0] = -1;
	    for (register int i = 1; i <= gstp; i++) lg[i] = lg[i - 1] + (i == (i & -i));
	    for (register int i = 1; i <= lg[gstp]; i++) {
	        for (register int j = 1; j <= gstp - (1 << i) + 1; j++)
	            st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
	    }
	    build(1, n, 1);
	    dfs(1, 0);
	    efs(1, 0);
	    for (register int i = 1; i <= q; i++) {
	        int l = get(), r = get();
	        vec[r].push_back(_p(l, i));
	    }
	    for (register int i = 1; i <= n; i++) {
	        int cur = top[i];
	        while (fa[cur]) {
	            if (lst[cur] != -1)
	                chs[fa[cur]].erase(_p(cur, lst[cur]));
	            chs[fa[cur]].push(_p(cur, lst[cur] = i));
	            cur = top[fa[cur]];
	        }
	        for (register int j = 0; j < vec[i].size(); j++) {
	            int ance = query(vec[i][j].a, i, 1, n, 1);
	            if (ance >= vec[i][j].a && ance <= i) {
	                anspt[vec[i][j].b] = ance;
	                anss[vec[i][j].b] = deep[calc(vec[i][j].a, i, ance)];
	                continue;
	            }
	            clear(tmp);
	            if (zhongson[ance]) {
	                if (qdat(vec[i][j].a, i, 1, n, rt[zhongson[ance]]))
	                    tmp.push_back(zhongson[ance]);
	            }
	            if (chs[ance].size() >= 1) {
	                pair cjr = chs[ance].top();
	                chs[ance].pop();
	                if (cjr.b >= vec[i][j].a) {
	                    tmp.push_back(cjr.a);
	                    if (chs[ance].size() >= 1) {
	                        pair a = chs[ance].top();
	                        chs[ance].pop();
	                        if (a.b >= vec[i][j].a) {
	                            tmp.push_back(a.a);
	                            if (chs[ance].size() >= 1) {
	                                pair b = chs[ance].top();
	                                chs[ance].pop();
	                                if (b.b >= vec[i][j].a) {
	                                    tmp.push_back(b.a);
	                                }
	                                chs[ance].push(b);
	                            }
	                        }
	                        chs[ance].push(a);
	                    }
	                }
	                chs[ance].push(cjr);
	            }
	            if (tmp.size() >= 3) {
	                anss[vec[i][j].b] = deep[ance];
	                anspt[vec[i][j].b] = i;
	                continue;
	            }
	            anspt[vec[i][j].b] = i;
	            anss[vec[i][j].b] = deep[ance];
	            for (register int k = 0; k < 2; k++) {
	                if (qdat(vec[i][j].a, i, 1, n, rt[tmp[k]]) == 1) {
	                    int best = qfirst(vec[i][j].a, i, 1, n, rt[tmp[k]]),
	                        res = deep[calc(vec[i][j].a, i, best)];
	                    if (res > anss[vec[i][j].b])
	                        anss[vec[i][j].b] = res, anspt[vec[i][j].b] = best;
	                }
	            }
	        }
	    }
	    for (register int i = 1; i <= q; i++) printf("%d %d\n", anspt[i], anss[i]);
	}
}
int main() {
    ywy::ywymain();
    return (0);
}

```

---

## 作者：wcyQwQ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1062E)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/11/02/CF1062E%20Company/)

## 前言

感觉是个挺牛逼的 trick，写篇题解记录一下。

### 前置芝士

LCA，线段树。


## 分析

观察到这题出现了多个点的 LCA，我们并不是很熟悉，所以尝试对其进行转化。

接下来就有一个最关键的结论，对于一个点集 $S$，令 $u$ 为 $S$ 中 dfs 序最大的节点， $v$ 为 $S$ 中 dfs 序最小的节点，那么有 $LCA(S) = LCA(u, v)$。

证明的过程相当简单，我们设这个点集的 $LCA$ 为 $p$，那么显然有 $S \subseteq subtree(p)$，而由 dfs 序的知识得到 $subtree$ 中子节点的 dfs 序都在 $[dfn_p,  dfn_p + size_p - 1]$ 中，所以我们有 $\forall i \in S，dfn_i \in [dfn_p, dfn_p + sisze_p - 1]$，所以说我们如果把 dfs 序排在中间的点忽略，并不会对 $[dfn_p, dfn_p + size_p - 1]$ 这个范围产生影响，所以我们可以得到 LCA 只和 $u, v$ 有关，即 $LCA(S) = LCA(u, v)$。

知道了这个结论，这道题就变成了一个区间 LCA 的板子，我们可以用各种 RMQ 求出来 $[l, r]$ 中最大/最小的 dfs 序，然后比较一下删去的 LCA 深度，那么这题就做完了。具体做法是，如果当前删掉了点 $x$，那么后来的 LCA 就是 $LCA(LCA(l, x - 1), LCA(x + 1, r))$，区间 LCA 用 线段树或 st表进行维护，我写的是线段树，时间复杂度 $O(m\log^2n)$。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int h[N], e[N << 1], ne[N << 1], idx;
int dep[N], f[N][25], dfn[N], rk[N], tt;
struct node
{
    int l, r, max, min, lca;
} t[N << 2];

inline int read()
{
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

inline void dfs(int u, int p)
{
    dep[u] = dep[p] + 1, f[u][0] = p, dfn[u] = ++tt, rk[tt] = u;
    for (int i = 1; i <= 20; i++)
        f[u][i] = f[f[u][i - 1]][i - 1];
    for (int i = h[u]; ~i; i = ne[i])
    {
        int v = e[i];
        if (v == p) continue;
        dfs(v, u);
    }
}

inline int lca(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 20; i >= 0; i--)
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    if (x == y) return x;
    for (int i = 20; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}

inline void pushup(int p)
{
    t[p].lca = lca(t[p << 1].lca, t[p << 1 | 1].lca);
    t[p].max = max(t[p << 1].max, t[p << 1 | 1].max);
    t[p].min = min(t[p << 1].min, t[p << 1 | 1].min);
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if (l == r)
    {
        t[p].max = t[p].min = dfn[l];
        t[p].lca = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline int query_lca(int p, int l, int r)
{
    if (l <= t[p].l && t[p].r <= r) return t[p].lca;
    int mid = (t[p].l + t[p].r) >> 1;
    if (l > mid) return query_lca(p << 1 | 1, l, r);
    if (r <= mid) return query_lca(p << 1, l, r);
    else return lca(query_lca(p << 1, l, r), query_lca(p << 1 | 1, l, r));
}

inline int query_max(int p, int l, int r)
{
    if (l <= t[p].l && t[p].r <= r) return t[p].max;
    int mid = (t[p].l + t[p].r) >> 1, res = 0;
    if (l <= mid) res = max(res, query_max(p << 1, l, r));
    if (r > mid) res = max(res, query_max(p << 1 | 1, l, r));
    return res;
}

inline int query_min(int p, int l, int r)
{
    if (l <= t[p].l && t[p].r <= r) return t[p].min;
    int mid = (t[p].l + t[p].r) >> 1, res = 1 << 30;
    if (l <= mid) res = min(res, query_min(p << 1, l, r));
    if (r > mid) res = min(res, query_min(p << 1 | 1, l, r));
    return res;
}

int main()
{
    memset(h, -1, sizeof h);
    int n = read(), m = read();
    for (int i = 2; i <= n; i++)
    {
        int x = read();
        add(x, i);
        add(i, x);
    }
    dfs(1, 0);
    build(1, 1, n);
    while (m--)
    {
        int l = read(), r = read();
        int maxx = query_max(1, l, r), minn = query_min(1, l, r);
        int lca_max = rk[maxx] == l ? query_lca(1, l + 1, r) : (rk[maxx] == r ? query_lca(1, l, r - 1) : lca(query_lca(1, l, rk[maxx] - 1), query_lca(1, rk[maxx] + 1, r)));
        int lca_min = rk[minn] == l ? query_lca(1, l + 1, r) : (rk[minn] == r ? query_lca(1, l, r - 1) : lca(query_lca(1, l, rk[minn] - 1), query_lca(1, rk[minn] + 1, r)));
        printf("%d %d\n", dep[lca_max] > dep[lca_min] ? rk[maxx] : rk[minn], max(dep[lca_max], dep[lca_min]) - 1);
    }
    return 0;
}
```



---

## 作者：Liveddd (赞：2)

~~来一发码风较为正常的题解qwq~~

先尝试找性质。假设某一点 $u$ 为某一段节点的 LCA，那么其子树的节点 $dfn$ 序一定在 $[dfn_{u},dfn_{u}+size_{u}-1]$ 之间。很明显删去**中间**的点一定不能使答案更优，只能删去 $dfn$ 序**最小**或**最大**的点才可能使 LCA 下移。并且查找区间 LCA 也只需要求 $dfn$ 序**最小**或**最大**的点的 LCA 即可。也算是较为经典套路了。

使用一棵线段树来维护区间**最小**与**最大** $dfn$ 值，每次考虑将其删去。中间使用 ST表 来查找区间 LCA 即可。中间还有一些小细节和 trick （见注释）。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=2e5+10,K=25,INF=1e9;
template <class T>
inline void read(T &x)
{
    x=0;int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f)x=~x+1;
}
template <class T,class ...T1>
inline void read(T &x,T1 &...x1)
{
    read(x);
    read(x1...);
}

struct Node
{
    int l,r;
    int minx,maxx;    
}tr[N<<2];
int n,q;
int tot,head[N],ver[N<<1],ne[N<<1];
int cnt,d[N],dfn[N],st[N<<1][K];
int Log[N<<1];

void add(int u,int v)
{
    ver[++tot]=v;
    ne[tot]=head[u];
    head[u]=tot;
}
void dfs(int x,int fa)
{
    st[++cnt][0]=x;
    d[x]=d[fa]+1;
    dfn[x]=cnt;//注意这里使用欧拉序来代替dfs序，对于之后求区间LCA等操作很方便（见下方）
    for(int i=head[x];i;i=ne[i])
    {
        // if(ver[i]==fa)continue;
        dfs(ver[i],x);
        st[++cnt][0]=x;
    }
}
int dmin(int x,int y)
{
    return d[x]<d[y]?x:y;
}
void build_st()
{
    for(int i=2;i<=cnt;i++)
        Log[i]=Log[i>>1]+1;
    for(int j=1;j<=Log[cnt];j++)
        for(int i=1;i+(1<<j)-1<=cnt;i++)
            st[i][j]=dmin(st[i][j-1],st[i+(1<<j-1)][j-1]);
}
int LCA(int x,int y)
{
    // x=dfn[x],y=dfn[y];
    if(x>y)swap(x,y);
    int k=Log[y-x+1];
    return dmin(st[x][k],st[y-(1<<k)+1][k]);
}//ST表

void pushup(int x)
{
    tr[x].minx=min(tr[x<<1].minx,tr[x<<1|1].minx);
    tr[x].maxx=max(tr[x<<1].maxx,tr[x<<1|1].maxx);
}
void build(int x,int l,int r)
{
    tr[x].l=l,tr[x].r=r;
    if(l==r)
    {
        tr[x].minx=tr[x].maxx=dfn[l];
        return ;
    }
    int mid=l+r>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}
int QueryMin(int x,int l,int r)
{
    if(tr[x].l>=l&&tr[x].r<=r)
        return tr[x].minx;
    int mid=tr[x].l+tr[x].r>>1,res=INF;
    if(l<=mid)res=min(res,QueryMin(x<<1,l,r));
    if(r>mid)res=min(res,QueryMin(x<<1|1,l,r));
    return res;
}
int QueryMax(int x,int l,int r)
{
    if(tr[x].l>=l&&tr[x].r<=r)
        return tr[x].maxx;
    int mid=tr[x].l+tr[x].r>>1,res=0;
    if(l<=mid)res=max(res,QueryMax(x<<1,l,r));
    if(r>mid)res=max(res,QueryMax(x<<1|1,l,r));
    return res;
}
void modify(int x,int pos,int k)
{
    if(tr[x].l==tr[x].r)
    {
        tr[x].minx=tr[x].maxx=k;
        return ;
    }
    int mid=tr[x].l+tr[x].r>>1;
    if(pos<=mid)modify(x<<1,pos,k);
    else modify(x<<1|1,pos,k);
    pushup(x);
}//SegmentTree
int main()
{
    read(n,q);
    for(int i=2;i<=n;i++)
    {
        int fa;
        read(fa);
        add(fa,i);
    }
    dfs(1,0);
    build_st();
    build(1,1,n);
    for(int i=1;i<=q;i++)
    {
        int l,r;
        read(l,r);
        int ans1=QueryMin(1,l,r),ans2=QueryMax(1,l,r);
        int res1,res2,lca1,lca2;
        //注意分清楚是欧拉序还是节点本身序号
        modify(1,st[ans1][0],INF);
        res1=QueryMin(1,l,r);
        modify(1,st[ans1][0],ans1);
        lca1=LCA(res1,ans2);
        //将该点删去，然后求区间LCA，最后还原，下面同理
        modify(1,st[ans2][0],0);
        res2=QueryMax(1,l,r);
        modify(1,st[ans2][0],ans2);
        lca2=LCA(res2,ans1);

        if(d[lca1]>=d[lca2])
            printf("%d %d\n",st[ans1][0],d[lca1]-1);
        else printf("%d %d\n",st[ans2][0],d[lca2]-1);
    }
    return 0;
}
```


---

## 作者：alecli (赞：2)


## 思考

最重要的问题在于，我们删去哪个点后，剩下点的公共 $LCA$ 深度最大，即如何确定这个点。我们感性的观察和理性的分析之后，发现和点的 $dfn$ 序有关系，要么删去当前区间点 $dfn$ 最大的，要么删最小的。

如果得出上面那个结论就好办了，拿个线段树维护区间 $dfn$ 的最大和最小值，选择是删 $dfn$ 最大的点还是最小的点即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ls(pos) pos << 1
#define rs(pos) pos << 1 | 1
using namespace std;
const int N = 100010;
const int M = 100010;
struct node{
    int nxt, to;
}edge[M << 1];
int head[N], num;
void build(int from, int to){
    edge[++num].nxt = head[from];
    edge[num].to = to;
    head[from] = num;
}
int dfn[N], cnt, f[N][20], rev[N], d[N], n, q;
namespace Seg{
    int Max[N << 2], Min[N << 2];
    void pushup(int pos){
        Max[pos] = max( Max[ls(pos)], Max[rs(pos)] );
        Min[pos] = min( Min[ls(pos)], Min[rs(pos)] );
    }
    void build(int pos, int l, int r){
        if(l == r){
            Max[pos] = Min[pos] = dfn[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(pos), l, mid);
        build(rs(pos), mid+1, r);
        pushup(pos);
    }
    void modify(int pos, int l, int r, int x, int v){
        if(l == r && l == x){
            Max[pos] = max(Max[pos], v);
            Min[pos] = min(Min[pos], v);
            return;
        }
        int mid = (l + r) >> 1;
        if(x <= mid) modify(ls(pos), l, mid, x, v);
        else modify(rs(pos), mid+1, r, x, v);
        pushup(pos);
    }
    int QMAX(int pos, int l, int r, int x, int y){
        int ans = 0;
        if(l > y || r < x) return 0;
        if(x <= l && r <= y) return Max[pos];
        int mid = (l + r) >> 1;
        if(x <= mid) ans = max(ans, QMAX(ls(pos), l, mid, x, y));
        if(y > mid) ans = max(ans, QMAX(rs(pos), mid+1, r, x, y));
        return ans;
    }
    int QMIN(int pos, int l, int r, int x, int y){
        int ans = 0x3f3f3f3f;
        if(l > y || r < x) return 0x3f3f3f3f;
        if(x <= l && r <= y) return Min[pos];
        int mid = (l + r) >> 1;
        if(x <= mid) ans = min(ans, QMIN(ls(pos), l, mid, x, y));
        if(y > mid) ans = min(ans, QMIN(rs(pos), mid+1, r, x, y));
        return ans;
    }
}
using namespace Seg;
void dfs(int u, int fa){
    dfn[u] = ++cnt; rev[cnt] = u;
    for(int i=head[u]; i; i=edge[i].nxt){
        int v = edge[i].to;
        if(v == fa) continue;
        d[v] = d[u] + 1;
        f[v][0] = u;
        dfs(v, u);
    }
}
int lca(int u, int v){
    if(d[u] < d[v]) swap(u, v);
    for(int i=18; i>=0; i--) if(d[f[u][i]] >= d[v]) u = f[u][i];
    if(u == v) return u;
    for(int i=18; i>=0; i--) if(f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
    return f[u][0];
}
int main(){
    cin >> n >> q;
    for(int i=2; i<=n; i++){
        int v; cin >> v;
        build(i, v); build(v, i);
    }
    d[1] = 1;
    dfs(1, 0);
    build(1, 1, n);
    for(int j=1; j<=18; j++)
        for(int i=1; i<=n; i++) f[i][j] = f[f[i][j-1]][j-1];
    while(q --){
        int l, r, L, Lu, R, Ru, L2, L2u, R2, R2u, LCA1, LCA2;
        int flag = 0;
        cin >> l >> r;
        L = QMIN(1, 1, n, l, r), R = QMAX(1, 1, n, l, r);
        Lu = rev[L], Ru = rev[R];
        L2 = min(QMIN(1, 1, n, l, Lu - 1), QMIN(1, 1, n, Lu + 1, r));
        R2 = max(QMAX(1, 1, n, l, Ru - 1), QMAX(1, 1, n, Ru + 1, r));
        L2u = rev[L2], R2u = rev[R2];
        LCA1 = lca(Lu, R2u); LCA2 = lca(L2u, Ru);
        if(d[LCA1] > d[LCA2]) flag = 1;
        else flag = 0;
        if(flag){
            cout << Ru << " " << d[LCA1] - 1 << endl;
        }
        else cout << Lu << " " << d[LCA2] - 1 << endl;
    }
    return 0;
}
```

大概猜出第一个结论就好做了。




---

## 作者：AIskeleton (赞：0)

[博客园查看](https://www.cnblogs.com/AIskeleton/p/16825856.html)

$* \text{Defficulty:} \color{Gold}{2300}$

## Description

给定一棵 $n$ 个节点的树，有 $q$ 个询问，每次询问给出一个区间 $[l,r]$。

要求在编号在 $[l,r]$ 范围内的点内删掉一个点后剩余点的 LCA 深度最大。

求删掉点的编号和此时 LCA 的最大深度。

## Solution

首先，要做这题有一个很重要的性质：一部分节点的 LCA 一定是其中 dfs 序最大和最小的点的 LCA。

### proof

设点 $i$ 的 dfs 序为 $id_i$，$id'_u=\max{id_v}$，某个区间的 dfs 序最值所在点分别为 $u,v$，其 LCA 为 $l$。

显然有 $id_l \le id_v \le id_u \le id'_l$。

对于 $\forall x \in [l,r]$，$id_v \le id_x \le id_u \implies id_l \le id_x \le id'_r \implies l$ 是点 $x$ 的祖先。

所以，被删去的节点要么是 $u$，要么是 $v$。

Q.E.D

-----

所以，我们可以枚举删去的节点是 $u$ 和 $v$ 的情况下的 LCA，取其中更大的值即可。

区间的 dfs 序最值，可以用数据结构维护，比如线段树，ST 表等。

假设删去了节点 $u$，查询就会被分成 $[l,u-1]$ 和 $[u+1,r]$ 两部分。

那就分别求出这两部分的 LCA，再取这两部分的 LCA 的 LCA 作为删去 $u$ 时的答案，$v$ 也同理。

注意这里要特判一下，如果 $u,v$ 刚好就是 $l$ 或 $r$，就只剩一个部分，直接返回其 LCA 即可。

求 LCA 可以用除了暴力外的所有方法，因为此题要用到 dfs 序，所以笔者使用了比较冷门的 dfs 序求 LCA。

具体细节参照代码。

**时间复杂度：**$O((n+q) \log_2 n)$

## code

```cpp
/*******************************
| Author:  A.I.skeleton
| Problem: E. Company
| Contest: Codeforces Round #520 (Div. 2)
| URL:     https://codeforces.com/contest/1062/problem/E
| When:    2022-10-25 14:25:10
| 
| Memory:  256 MB
| Time:    2000 ms
*******************************/
#include <bits/stdc++.h>
using namespace std;
#define lc p<<1
#define rc p<<1|1
#define F(i) (i).first
#define S(i) (i).second
#define pb push_back
#define vi vector<int>
#define pi pair<int,int>
#define L(i,j,k) for(int (i)=(j);i<=(k);(i)++)
#define R(i,j,k) for(int (i)=(j);i>=(k);(i)--)
#define FST ios::sync_with_stdio(0);cin.tie(0);

const int N=1e5+100,INF=1e9;
int n,q,p,lg[N],cn,id[N],d[N]={-1},st[19][N];
vi g[N];int si[N],h[N],t[N],l,r;

struct se{int l,r;pi ma,mi;}s[N<<2];
void pp(int p){
  s[p].ma=max(s[lc].ma,s[rc].ma);
  s[p].mi=min(s[lc].mi,s[rc].mi);
}void build(int p,int l,int r){
  s[p].l=l;s[p].r=r;
  if(l==r) return ;
  int m=(l+r)>>1;build(lc,l,m);build(rc,m+1,r);
}void change(int p,int x,int k){
  if(s[p].l>x||x>s[p].r) return;
  if(s[p].l==s[p].r){
    S(s[p].mi)=S(s[p].ma)=s[p].l;
    F(s[p].mi)=F(s[p].ma)=k;return ;
  }int m=(s[p].l+s[p].r)>>1;
  change(lc,x,k);change(rc,x,k);pp(p);
}pi askmi(int p,int l,int r){
  if(s[p].l>r||l>s[p].r) return {INF,0};
  if(l<=s[p].l&&s[p].r<=r) return s[p].mi;
  return min(askmi(lc,l,r),askmi(rc,l,r));
}pi askma(int p,int l,int r){
  if(s[p].l>r||l>s[p].r) return {-INF,0};
  if(l<=s[p].l&&s[p].r<=r) return s[p].ma;
  return max(askma(lc,l,r),askma(rc,l,r));
}int get(int x,int y){return d[x]<d[y]?x:y;}
void dfs(int u,int f){
  st[0][id[u]=++cn]=f;change(1,u,id[u]);
  d[u]=d[f]+1;for(int v:g[u]) if(v^f) dfs(v,u);
}int lca(int u,int v){
  if(u==v) return u;if((u=id[u])>(v=id[v])) swap(u,v);
  int d=lg[v-u++];return get(st[d][u],st[d][v-(1<<d)+1]);
}int sol(int l,int r,int cnt){
  if(cnt==l) return lca(S(askma(1,l+1,r)),S(askmi(1,l+1,r)));
  else if(cnt==r) return lca(S(askma(1,l,r-1)),S(askmi(1,l,r-1)));
  else return lca(lca(S(askma(1,l,cnt-1)),S(askmi(1,l,cnt-1))),
        lca(S(askma(1,cnt+1,r)),S(askmi(1,cnt+1,r))));
}int main(){
  FST;cin>>n>>q;L(i,2,n) lg[i]=lg[i>>1]+1;build(1,1,n);
  L(i,2,n) cin>>p,g[p].pb(i),g[i].pb(p);dfs(1,0);
  L(i,1,lg[n]) L(j,1,(n+1-(1<<i)))
    st[i][j]=get(st[i-1][j],st[i-1][j+(1<<i-1)]);
  L(i,1,q){
    cin>>l>>r;
    pi t1=askma(1,l,r),t2=askmi(1,l,r);
    int l1=sol(l,r,S(t1)),l2=sol(l,r,S(t2));
    if(d[l1]>d[l2]) cout<<S(t1)<<' '<<d[l1]<<'\n';
    else cout<<S(t2)<<' '<<d[l2]<<'\n';
  }
}
```

目前是洛谷最优解。


---

## 作者：SaoFish (赞：0)

~~**1遍A超开心的**（大雾）~~

第一眼看到这道题毫无头绪，觉得是用线段树维护区间lca，然后在用线段树合并？

然而并没有试过（滑稽）。

但仔细找找，还是能找到一些性质的
![](https://s1.ax1x.com/2018/11/23/FiBGoq.png)

对于这么的一棵树，当区间为**[3,6]**时，**dfs序最小的点为3，最大的点为4**，它们的lca为2。可以发现，**当删除5号点或6号点时，这个区间的lca时不变的**，因为它们都在**3和4的lca的子树中**。

当我再找了几个区间之后，发现都是这样的，然后我就产生了一个想法，**一个区间的lca**就是**区间dfs序最小的点和dfs最大的点的lca**。

然后我发现这个性质可以用**打表**或者用**rmq和lca问题之间的转化**来找到

我们先想想我们是怎么**把lca转化成rmq问题**的。（会的同学可以跳过）

假设我们要求树上结点x和y的lca。

- 1.求出每个点的**欧拉序**和**深度**。

- 2.记录结点u在欧拉序列中**第一次出现的位置为pos(u)**

- 3.根据dfs的性质，对于两结点u、v，从**pos(u)遍历到pos(v)的过程中经过LCA(u,v)有且仅有一次**，且深度是**深度序列dep[pos(u)…pos(v)]中最小的**。

- 4.求出pos(x)到pos(y)这段区间中最小的深度的位置。

如果我们要求**[l,r]这段区间的lca**，找到**欧拉序最小的点x**和**欧拉序最大的点y**

那么这两个点的lca就是**pos(x)到pos(y)中最小深度的位置**。

那我们再在[l,r]这段区间中任意找一对点(x',y')，就可以发现

**pos(x)≤pos(x')且pos(y')≥pos(y)**，也就是说**[pos(x'),pos(y')]**这段区间，被之前的**[pos(x),pos(y)]**这段区间**完全包含**了。

既然完全包含，那么显然**dep[lca(x,y)]一定小于等于dep[lca(x',y')]**，再仔细想想，就可以发现**lca(x',y')在lca(x,y)的子树中**。

所以，要删除点，就要删**会对区间lca产生影响的点**，也就是**dfs序最大的点和dfs序最小的点**。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for (register int i=(x);i<=(y);i++)
#define drp(i,x,y) for (register int i=(x);i>=(y);i--)
#define travel(i,x) for (register int i=head[x];i;i=e[i].nxt)
inline char read(){
	static const int IN_LEN=1000000;
	static char buf[IN_LEN],*s,*t;
	return (s==t?t=(s=buf)+fread(buf,1,IN_LEN,stdin),(s==t?-1:*s++):*s++);
}
template<class T>
inline void read(T &x){
	static bool iosig;
	static char c;
	for (iosig=false,c=read();!isdigit(c);c=read()){
		if (c=='-') iosig=true;
		if (c==-1) return;
	}
	for (x=0;isdigit(c);c=read()) x=((x+(x<<2))<<1)+(c^'0');
	if (iosig) x=-x;
}
const int OUT_LEN=10000000;
char obuf[OUT_LEN],*ooh=obuf;
inline void print(char c){
	if (ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;
	*ooh++=c;
}
template<class T>
inline void print(T x){
	static int buf[30],cnt;
	if (x==0) print('0');
	else{
		if (x<0) print('-'),x=-x;
		for (cnt=0;x;x/=10) buf[++cnt]=x%10+48;
		while (cnt) print((char)buf[cnt--]);
	}
}
inline void flush(){
	fwrite(obuf,1,ooh-obuf,stdout);
}
void judge(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
}
const int N=110000;
int n,Q,dfn[N],dep[N],f[20][N],mxpos[20][N],Max[20][N],alb[N],cnt,Min[20][N],mnpos[20][N];
struct info{
	int to,nxt;
}e[N<<1];
int head[N],opt;
void add(int x,int y){
	e[++opt]=(info){y,head[x]};
	head[x]=opt;
}
void dfs(int u){
	dfn[u]=++cnt; dep[u]=dep[f[0][u]]+1;
	travel(i,u){
		int k=e[i].to;
		if (k==f[0][u]) continue;
		f[0][k]=u; dfs(k);
	}
}
int lca(int x,int y){
	if (dep[x]<dep[y]) swap(x,y);
	drp(i,18,0) if (dep[f[i][x]]>=dep[y]) x=f[i][x];
	if (x==y) return dep[x];
	drp(i,18,0) if (f[i][x]!=f[i][y]){
		x=f[i][x]; y=f[i][y];
	}
	return dep[f[0][x]];
}
void init(){
	rep(i,2,n) alb[i]=alb[i>>1]+1;
	rep(i,1,18) rep(j,1,n) f[i][j]=f[i-1][f[i-1][j]];
	rep(i,1,n) Max[0][i]=Min[0][i]=dfn[i],mxpos[0][i]=mnpos[0][i]=i;
	rep(i,1,18){
		for (int j=1;j+(1<<i)-1<=n;j++){
			Max[i][j]=max(Max[i-1][j],Max[i-1][j+(1<<(i-1))]);
			if (Max[i-1][j]>Max[i-1][j+(1<<(i-1))]) mxpos[i][j]=mxpos[i-1][j];
			else mxpos[i][j]=mxpos[i-1][j+(1<<(i-1))];
			Min[i][j]=min(Min[i-1][j],Min[i-1][j+(1<<(i-1))]);
			if (Min[i-1][j]<Min[i-1][j+(1<<(i-1))]) mnpos[i][j]=mnpos[i-1][j];
			else mnpos[i][j]=mnpos[i-1][j+(1<<(i-1))];
		}
	}
}
#define pii pair<int,int>
#define mk make_pair
#define fi first
#define se second
const int inf=1<<30;
pii find_Max(int x,int y){
	if (x>y) return pii(-1,-1);
	int k=alb[y-x+1];
	int val=max(Max[k][x],Max[k][y-(1<<k)+1]),loc;
	if (Max[k][x]>Max[k][y-(1<<k)+1]) loc=mxpos[k][x];
	else loc=mxpos[k][y-(1<<k)+1];
	return pii(val,loc);
}
pii find_Min(int x,int y){
	if (x>y) return pii(inf,-1);
	int k=alb[y-x+1];
	int val=min(Min[k][x],Min[k][y-(1<<k)+1]),loc;
	if (Min[k][x]<Min[k][y-(1<<k)+1]) loc=mnpos[k][x];
	else loc=mnpos[k][y-(1<<k)+1];
	return pii(val,loc);
}
int main(){
	judge();
	read(n),read(Q);
	rep(i,2,n){
		int x; read(x);
		add(i,x),add(x,i);
	}
	dfs(1); init();
	rep(i,1,Q){
		int id,l,r,ans1,ans2; read(l),read(r);
		pii t=find_Max(l,r),tt=find_Min(l,r);
		pii t1=find_Max(l,t.se-1),t2=find_Max(t.se+1,r);
		if (t1.fi>t2.fi) id=t1.se;
		else id=t2.se;
		ans1=t.se; ans2=lca(id,tt.se);
		t=find_Min(l,r),tt=find_Max(l,r);
		t1=find_Min(l,t.se-1),t2=find_Min(t.se+1,r);
		if (t1.fi<t2.fi) id=t1.se;
		else id=t2.se;
		if (lca(id,tt.se)>ans2) ans1=t.se,ans2=lca(id,tt.se);
		print(ans1),print(' '),print(ans2-1),print('\n');
	}
	return flush(),0;
}
```

---

