# [ARC183E] Ascendant Descendant

## 题目描述

有一棵包含编号为 $1$ 到 $N$ 的 $N$ 个顶点的根树，根是顶点 $1$，对于每个顶点 $i$ ($2 \leq i \leq N$)，其父节点是顶点 $P_i$ ($P_i < i$)。

同时，给定两个长度为 $M$ 的整数序列 $A=(A_1, A_2, \cdots, A_M)$ 和 $B=(B_1, B_2, \cdots, B_M)$，其元素均为 $1$ 到 $N$ 之间的整数。

定义序列 $A$ 是 **good** 的，当且仅当对每个 $i$，顶点 $A_i$ 是顶点 $B_i$ 的祖先，或者 $A_i = B_i$。

初始时，序列 $A$ 是 good 的。

我们考虑对序列 $A$ 进行以下操作：

- 选择一个整数 $i$ ($1 \leq i \leq M-1$)，交换 $A_i$ 和 $A_{i+1}$ 的值。操作后，序列 $A$ 仍必须是 good 的。

请计算，经过 $0$ 次或多次操作后，可能得到的不同序列的个数，并输出该结果对 $998244353$ 取模的值。

## 说明/提示

- $2 \leq N \leq 250000$
- $2 \leq M \leq 250000$
- $1 \leq P_i < i$
- $1 \leq A_i \leq B_i \leq N$
- 对于每个 $i$，顶点 $A_i$ 是顶点 $B_i$ 的祖先，或者 $A_i = B_i$

### 样例解释

考虑选择 $i = 1$ 进行操作，操作后序列 $A=(2,1,1)$ 不是 good 的，因此该操作不可行。  

再考虑选择 $i = 2$ 进行操作，操作后序列 $A=(1,1,2)$ 是 good 的，因此该操作可行。  
可能得到的不同序列有 $A=(1,2,1)$ 和 $A=(1,1,2)$，因此答案是 $2$。

Translate by 宋怡芃

## 样例 #1

### 输入

```
3 3
1 2
1 2 1
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
4 3
1 1 1
2 3 4
2 3 4```

### 输出

```
1```

## 样例 #3

### 输入

```
8 13
1 2 2 3 4 4 3
5 3 2 5 4 6 2 8 2 6 7 4 7
5 5 8 5 6 6 5 8 3 6 7 4 7```

### 输出

```
8```

## 样例 #4

### 输入

```
30 27
1 2 1 1 5 1 7 1 5 10 1 12 12 13 15 16 12 18 19 18 21 21 23 13 18 18 27 27 13
1 18 1 5 11 12 1 1 1 12 1 12 1 15 1 1 21 1 12 10 2 8 3 1 1 30 12
14 27 30 5 11 17 1 18 24 27 29 27 19 15 28 5 21 21 29 11 2 8 3 4 10 30 22```

### 输出

```
60```

# 题解

## 作者：Hanghang (赞：2)

$\text{ARC183E}$

这凭啥放 $E$ 的位置啊。

首先你可以预处理出每个点 $i$ 能移动到的位置所在区间 $[l_i,r_i]$，需满足 $a_i$ 是区间中的每个 $b_j$ 的祖先。 

一个重要的观察是所有区间形成树形结构，即不存在两个区间有交集但不是包含关系，反证法易证。

实际上一个点的移动范围并不一定是 $[l_i,r_i]$，因为考虑把这些区间的树形结构建出来，对于某个 $i$，若其子树中一个 $j$ 满足 $j$ 的子树大小恰好是 $r_j-l_j+1$，那么相当于说这个区间的内的位置恰好被 $j$ 的子树覆盖，那么 $i$ 这个点就不可能从 $<l_j$ 的位置移动到 $>r_j$ 的位置。

考虑使用 $\text{set}$ 实时维护每一段的区间还剩下多少个位置。按照区间长度从小到大加入点 $i$，从 $i$ 向左右扩张，扩张到一个区间被恰好覆盖或者超过了 $l_i/r_i$，类似颜色段均摊的写法，再把中间的段删了，插入新的段即可。

最后你注意到算的是有多少种不同的 $a$ 序列，那么再把判下重复除以对应的系数即可。

默认 $n,m$ 同阶，处理 $l_i,r_i$ 的时候使用 $O(n\log n)-O(1)$ 的最近公共祖先。

总复杂度为 $O(n\log n)$

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N=2.5e5+3,M=20,H=998244353;
int n,m,tim,a[N],b[N],fa[N],pos[N],sta[N],st[M][N],f[M][N];
ll ans=1,iv[N],ij[N];
struct Seg
{
	int l,r,v;
	friend bool operator <(Seg A,Seg B){return A.l!=B.l?A.l<B.l:A.r!=B.r?A.r<B.r:A.v<B.v;}
}c[N];
set<Seg>S;
map<Seg,int>mp;
vector<int>ve[N];
bool Cmp(Seg A,Seg B){return A.r-A.l!=B.r-B.l?A.r-A.l<B.r-B.l:A.l<B.l;}
int Get(int x,int y){return pos[x]<pos[y]?x:y;}
void Dfs(int x)
{
	pos[x]=++tim;st[0][tim]=fa[x];
	for(int y:ve[x])Dfs(y);
}
int Lca(int x,int y)
{
	if(x==y)return x;
	if((x=pos[x])>(y=pos[y]))swap(x,y);
	int d=__lg(y-x++);
	return Get(st[d][x],st[d][y-(1<<d)+1]);
}
void Init()
{
	Dfs(1);
	for(int j=1;j<M;j++)for(int i=1;i+(1<<j)-1<=n;i++)
	    st[j][i]=Get(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	for(int i=1;i<=m;i++)f[0][i]=b[i];
	for(int j=1;j<M;j++)for(int i=1;i+(1<<j)-1<=m;i++)
	    f[j][i]=Lca(f[j-1][i],f[j-1][i+(1<<(j-1))]);
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0); 
	cin>>n>>m;
	for(int i=2;i<=n;i++)cin>>fa[i],ve[fa[i]].push_back(i);
	for(int i=1;i<=m;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	Init();
	for(int i=1;i<=m;i++)
	{
		int l=i-1,r=i+1;
		for(int j=M-1;j>=0;j--)if(r+(1<<j)-1<=m&&Lca(a[i],f[j][r])==a[i])r+=1<<j;
		for(int j=M-1;j>=0;j--)if(l-(1<<j)+1>=1&&Lca(a[i],f[j][l-(1<<j)+1])==a[i])l-=1<<j;
		c[i]={l+1,r-1,i};
	}
	sort(c+1,c+m+1,Cmp);iv[0]=iv[1]=ij[0]=1;
	for(int i=2;i<=m;i++)iv[i]=H-H/i*iv[H%i]%H;
	for(int i=1;i<=m;i++)S.insert({i,i,1}),ij[i]=ij[i-1]*iv[i]%H;
	for(int i=1;i<=m;i++)
	{
		auto it=--S.lower_bound({c[i].v+1,0,0});
		int l=it->l,r=it->r,v=it->v;it=S.erase(it);
		while(it!=S.end()&&it->r<=c[i].r&&it->v)r=it->r,v+=it->v,it=S.erase(it);
		while(it!=S.begin()&&(--it)->l>=c[i].l&&it->v)l=it->l,v+=it->v,it=S.erase(it);
		ans=ans*v%H;S.insert({l,r,v-1});mp[(Seg){l,r,a[c[i].v]}]++;
	}
	for(auto t:mp)ans=ans*ij[t.second]%H;
	cout<<ans;
}
```

---

## 作者：syzf2222 (赞：2)

前言：由于没有资格参加口语测试，晚上没事干，于是决定 vp 一场 arc。首先 A 题就做了很久，其次被 B 卡了，决定跳掉看 C，又瞪了好久才会。不想回去看 B，开 D，觉得莫名其妙，开 E，哎，好像不太难的样子。于是过了。蛮兴奋的。

注意到，设 $[l_i,r_i]$ 为 $a_i$ 能够走到的区间（不妨先看作是与 $i$ 相邻的且其中的 $b$ 都在 $a_i$ 子树中的极大区间），则区间之间要么不交要么包含。这是因为若有交，则二者之间必有祖先关系，则一定包含。其形成树形结构，我们相当于在区间中可以随便选点填上，一个简单的乘法原理即可。

但有时候可能填着填着会把路堵住，比如一个位置本来就走不动，但另一个位置的区间可能跨过此位置。对此我的处理方式为，类似拓扑排序地依次处理，若区间内填满了就打上标记，每次算区间的时候不得经过标记的位置。

于是我们得到了一个 $O(n\log n)$ 的做法，个人认为关键在于发现区间形成树状结构。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
const int mod=998244353;
#define inf 1e9
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,P[maxn],cd[maxn],a[maxn],b[maxn];
vector<int>G[maxn],pos[maxn];
#define pb push_back
queue<int>Q;int ban[maxn],S[maxn],ans=1;
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
int dfn[maxn],siz[maxn],ti,fac[maxn],inv[maxn],ifc[maxn];
inline int com(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return 1ll*fac[x]*ifc[y]%mod*ifc[x-y]%mod;
}
inline void dfs(int x){
	dfn[x]=++ti;siz[x]=1;
	for(auto t:G[x])
		dfs(t),siz[x]+=siz[t];
}
inline bool chk(int x,int y){
	return dfn[y]>=dfn[x]&&dfn[y]<dfn[x]+siz[x];
}
int tr[maxn];set<int>B;
set<int>::iterator it;
inline void add(int x,int y){for(;x<=m;x+=x&(-x))tr[x]+=y;}
inline int query(int x){int res=0;for(;x;x-=x&(-x))res+=tr[x];return res;}
int Mn[maxn][20],Mx[maxn][20],lg[maxn];
inline int Min(int l,int r){
	int k=lg[r-l+1];
	return min(Mn[l][k],Mn[r-(1<<k)+1][k]);
}
inline int Max(int l,int r){
	int k=lg[r-l+1];
	return max(Mx[l][k],Mx[r-(1<<k)+1][k]);
}
inline bool Chk(int l,int r,int x){
	return Min(l,r)>=dfn[x]&&Max(l,r)<=dfn[x]+siz[x]-1;
}
int main(){
	n=read(),m=read();
	for(int i=2;i<=n;i++)
		P[i]=read(),G[P[i]].pb(i),cd[P[i]]++;dfs(1);
	for(int i=1;i<=m;i++)a[i]=read(),pos[a[i]].pb(i);
	for(int i=1;i<=m;i++)b[i]=read();
	for(int i=1;i<=n;i++)if(!cd[i])Q.push(i);
	fac[0]=ifc[0]=inv[1]=1;lg[0]=-1;
	for(int i=1;i<=m;i++)fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=m;i++)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=m;i++)ifc[i]=1ll*ifc[i-1]*inv[i]%mod;
	for(int i=1;i<=m;i++)lg[i]=lg[i>>1]+1,Mn[i][0]=Mx[i][0]=dfn[b[i]];
	for(int i=1;i<=19;i++)
		for(int j=1;j+(1<<i)-1<=m;j++){
			Mn[j][i]=min(Mn[j][i-1],Mn[j+(1<<i-1)][i-1]);
			Mx[j][i]=max(Mx[j][i-1],Mx[j+(1<<i-1)][i-1]);
		}
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		cd[P[x]]--;
		if(!cd[P[x]])Q.push(P[x]);
		for(int j=0;j<pos[x].size();j++){
			int t=pos[x][j],L,R,l,r,cnt=1;
			L=1,R=t-1,l=t;
			while(L<=R){
				int mid=(L+R)>>1;
				if(Chk(mid,t,x))l=mid,R=mid-1;
				else L=mid+1;
			}L=t+1,R=m,r=t;
			while(L<=R){
				int mid=(L+R)>>1;
				if(Chk(t,mid,x))r=mid,L=mid+1;
				else R=mid-1;
			}
			it=B.lower_bound(t);
			if(it!=B.end())r=min(r,(*it)-1);
			if(it!=B.begin())--it,l=max(l,(*it)+1);
			while(j+1<pos[x].size()&&pos[x][j+1]<=r)++j,++cnt;
			add(l,cnt);int sum=query(r)-query(l-1);
			if(sum==r-l+1)B.insert(l),B.insert(r);
			ans=1ll*ans*com(r-l+1-(sum-cnt),cnt)%mod;
		}
	}printf("%d\n",ans);
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：WrongAnswer_90 (赞：1)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18382019)

### [[ARC183E] Ascendant Descendant](https://www.luogu.com.cn/problem/AT_arc183_e)

一个直接的想法是求出 $L_i,R_i$ 表示极大的区间 $[L_i,R_i]$ 满足 $\forall j\in[L_i,R_i],b_j\in \text{subtree}(a_i)$。由于树的性质，$[L_i,R_i]$ 之间要么相离，要么包含。

但是 $L_i,R_i$ 并不是 $i$ 能真正到达的点。因为 $i$ 只能一个一个交换过去，中途可能会有一些点阻碍着 $i$ 的交换。具体的，把 $[L_i,R_i]$ 构成的树形结构建出来，会阻碍交换的点就是满足 $siz_i=R_i-L_i+1$ 的整棵子树。必要性和充分性都比较显然。（但是想不到啊）

求 $[L_i,R_i]$ 是平凡的，一个 $\mathcal O(1)$ LCA 和线段树或者 ST 表就能在 $\mathcal O(m\log m)$ 的时间里求出来。后半部分实现的时候可以按照区间长度排序，拿一个 BIT 维护区间和，每次是区间内任选一个点单点加一即可。再用一个 'set' 维护删掉的点。总复杂度 $\mathcal O(n\log n)$。

```cpp
int n,m,L,R,mid,tot,fr[250010],a[250010],l[250010],r[250010];
int F[18][250010],G[18][250010],dfn[250010];
vi T[250010];
tup c[250010];
inline int get(int x,int y){return dfn[x]<dfn[y]?x:y;}
inline bool cmp(tup x,tup y){return (x.y-x.x)<(y.y-y.x)||((x.y-x.x)==(y.y-y.x)&&a[x.z]<a[y.z]);}
void dfs(int x,int fa=0){F[0][dfn[x]=++tot]=fa;for(auto to:T[x])dfs(to,x);}
inline int LCA(int x,int y)
{
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int k=__lg(y-x++);
	return get(F[k][x],F[k][y-(1<<k)+1]);
}
inline int ask(int l,int r){int k=__lg(r-l+1);return LCA(G[k][l],G[k][r-(1<<k)+1]);}
namespace BIT
{
	int t[250010];
	inline void add(int x){for(;x<=m;x+=x&-x)++t[x];}
	inline int ask(int x){int s=0;for(;x;x-=x&-x)s+=t[x];return s;}
}
using namespace BIT;
set<int> st;
map<pii,int> hash;
inline void mian()
{
	read(n,m),fr[0]=1;int x,ans=1;
	for(int i=1;i<=m;++i)fr[i]=Cmul(fr[i-1],i);
	for(int i=2;i<=n;++i)read(x),T[x].eb(i);
	dfs(1);
	for(int i=1;i<18;++i)for(int j=1;j+(1<<i)-1<=n;++j)
	F[i][j]=get(F[i-1][j],F[i-1][j+(1<<(i-1))]);
	for(int i=1;i<=m;++i)read(a[i]);
	for(int i=1;i<=m;++i)read(G[0][i]);
	for(int i=1;i<18;++i)for(int j=1;j+(1<<i)-1<=m;++j)
	G[i][j]=LCA(G[i-1][j],G[i-1][j+(1<<(i-1))]);
	for(int i=1;i<=m;++i)
	{
		L=1,R=i;
		while(L<R)
		{
			mid=L+((R-L)>>1); 
			if(LCA(ask(mid,i),a[i])==a[i])R=mid;
			else L=mid+1;
		}
		c[i].x=L,L=i,R=m;
		while(L<R)
		{
			mid=L+((R-L+1)>>1);
			if(LCA(ask(i,mid),a[i])==a[i])L=mid;
			else R=mid-1;
		}
		c[i].y=L,c[i].z=i;
	}
	sort(c+1,c+1+m,cmp),st.insert(0),st.insert(m+1);
	for(int i=1;i<=m;++i)
	{
		int xx=c[i].x,yy=c[i].y;
		Mmax(c[i].x,(*(--st.lower_bound(c[i].z)))+1);
		Mmin(c[i].y,(*st.lower_bound(c[i].z))-1);
		int v=c[i].y-c[i].x+1-(ask(c[i].y)-ask(c[i].x-1));
		Mmul(ans,v),add(c[i].z);
		hash[mp(c[i].x*m+c[i].y,a[c[i].z])]++;
		if(ask(yy)-ask(xx-1)==yy-xx+1)st.insert(xx),st.insert(yy);
	}
	for(auto [x,y]:hash)Mmul(ans,power(fr[y],MOD-2));
	write(ans);
}
```

---

## 作者：vegetable_king (赞：0)

[可能更好的阅读体验](https://yjh965.github.io/post/arc183e-ascendant-descendant-ti-jie/)

开赛的时候看了一眼，时限 7s 模数还是 $998244353$ 就以为是 poly 没碰，结果被 B 杀了 1h，最后 20min 才有时间读题（因为看到了最后一个样例答案是个 $60$，像若干个数的乘积），结果发现这个是唐题，蚌埠住了。

---

首先显然可以对每个点求出（不考虑其他点的限制时）他能呆的位置集合，因为每次操作是交换相邻两个，所以每个点的移动都是连续的，所以上述位置集合是一个区间。

然后发现一个很显然的结论是，上述区间两两要么包含要么不交。证明也是显然的，考虑一个树上的节点 $u$，$u$ 子树中的节点在 $b$ 序列中构成了若干极长段。若有一个 $p$ 满足 $a_p = u$，则 $a_p$ 能呆的位置集合就是 $p$ 所在的那个极长段。对于一个节点 $u$，对应的极长段两两不交，所以对于所有 $u$ 的极长段们构成的区间集合也有两两包含或不交。

但是实际上一个点移动到某个位置的时候可能会影响其他点，比如说一个点根本无法移动，那么其他点移动的时候也无法跨过该点。

考虑推广该限制，即建出区间的树形结构后，若一个节点能呆的位置集合恰好等于其子树大小，那么其他节点无法跨过它的位置集合。必要性证明考虑如果要经过该位置集合，一定会把一个子树内的点从该位置集合中换出来。而子树内的点的位置集合都被该位置集合包含，所以这样一定不合法。

所以我们将能呆的位置集合按照上述过程收缩到不包含任何一个实际上不合法的位置，即为实际能到的位置集合。注意到后者也是一个区间，且同样满足两两要么包含要么不交的限制，所以答案确实是类似这样的。注意题目要求的是求本质不同的序列个数，所以有些时候可能要除掉一些东西。

上述过程都可以用数据结构简单维护，具体见[代码](https://atcoder.jp/contests/arc183/submissions/57221540)。

---

