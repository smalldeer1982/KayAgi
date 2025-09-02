# [COTS 2016] 搜索树 Jelka

## 题目背景

译自 [Izborne Pripreme 2016 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2016/) D2T1。$\texttt{1s,0.5G}$。


## 题目描述


给定一棵 $n$ 个点的二叉树，点有点权，其中 $1$ 号点为根节点。

$m$ 次操作修改某个点的点权。在每次修改后询问：这棵树上有多少个节点的子树（包含自身）是二叉搜索树（BST）？

我们给定 BST 的定义：

- 含有一个节点的树是 BST。
- 对于大于一个节点的树，它是 BST 当且仅当：
	- 根节点的左子树为空，或者左子树是二叉搜索树，且左子树内所有点的点权均**不大于**根节点的点权；
   - 根节点的右子树为空，或者右子树是二叉搜索树，且右子树内所有点的点权均**不小于**根节点的点权。



## 说明/提示


#### 样例解释

样例 $1$ 解释如图所示。

其中节点内的数字表示 BST 权值，节点外的数字表示节点编号。

![](https://cdn.luogu.com.cn/upload/image_hosting/yabnaj75.png)

#### 数据范围

对于 $100\%$ 的数据，保证：
- $1\le n,m\le 2\times 10^5$；
- $0\le a_i,v\le 10^9$；
- 操作和树的形态均合法。


| 子任务编号 | $n,m\le  $ | 特殊性质 | 得分 |  
| :--: | :--: | :--: | :--: |
| $ 1 $    | $ 5\, 000$    |  | $ 16 $   |  
| $ 2 $    | $ 2\times 10^5 $   | A |  $ 24 $   |  
| $ 3 $    | $ 2\times 10^5$ | | $ 60 $   |  

特殊性质 A：$\forall 1\le i\le n$，$l_i=0\lor r_i=0$。



## 样例 #1

### 输入

```
6 5
2 3
4 0
5 6
0 0
0 0
0 0
4 1 3 2 2 5
3 3
2 2
3 5
5 4
6 1```

### 输出

```
4
5
5
6
4```

## 样例 #2

### 输入

```
8 10
4 5
8 0
0 0
3 7
0 6
0 0
2 0
0 0
7 0 9 3 6 0 6 2
3 0
4 0
8 2
2 3
7 6
1 6
5 7
6 9
1 1
1 7```

### 输出

```
3
3
3
6
6
6
6
8
7
8```

# 题解

## 作者：_Spectator_ (赞：4)

[可能更好的食用体验](/article/zu44899n) $|$ 
[题目传送门](/problem/P11306) $|$ 
[我的其他题解](/user/523641#article.2)

% 你赛题，水篇题解（逃

------------

### ${\color{#00CD00}\text{思路}}$

两条性质：
- 一棵二叉树是 BST 当且仅当这棵树的中序遍历是单调不降的。
- 一个子树的中序遍历是整颗树的中序遍历中连续的一段。

先跑一遍 dfs，求出整颗树的中序遍历，同时记录下每个结点的子树的中序遍历在整颗树的中序遍历中的位置。这样判断一个子树是否是 BST 就只需要用树状数组维护对应的区间内不满足 $a_i \le a_{i+1}$ 的数量。

考虑如何修改。发现每次修改只会影响这个结点到根结点的路径。树上倍增更新答案即可。

时间复杂度为 $O(n\log^2n)$。实现细节见代码。

------------

### ${\color{#00CD00}\text{代码}}$

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i=a; i<=b; i++)
using namespace std;
const int N = 2e5 + 5;
long long n, q, ans;
int a[N], f[N][20];
int dfn;
struct Node{
	int ls, rs, val;
	int pos, l, r;
}t[N];
void dfs(int _u){
	if(!_u) return;
	Node &u = t[_u];
	u.l = dfn + 1, dfs(u.ls);
	u.pos = ++dfn, a[u.pos] = u.val;
	dfs(u.rs), u.r = dfn;
}
struct BIT{
	int c[N], lowbit(int x){return x & -x;}
	void update(int x, int k){while(x <= n) c[x] += k, x += lowbit(x);}
	int query(int x){int s = 0; while(x) s += c[x], x -= lowbit(x); return s;}
}bit;
void upd(int k, int x){
	if(k < n && a[k] > a[k+1]) bit.update(k, x);
	if(k > 1 && a[k-1] > a[k]) bit.update(k-1, x);
}
bool check(int x){
	return bit.query(t[x].r-1) - bit.query(t[x].l-1) == 0;
}
int solve(int x){
	if(!check(x)) return 0;
	int res = 1;
	for(int i=19; i>=0; i--){
		if(f[x][i] && check(f[x][i])){
			x = f[x][i], res += 1 << i;
		}
	}
	return res;
}
signed main(){
	cin.tie(nullptr) -> sync_with_stdio(false);
	cin >> n >> q;
	rep(i, 1, n){
		cin >> t[i].ls >> t[i].rs;
		if(t[i].ls) f[t[i].ls][0] = i;
		if(t[i].rs) f[t[i].rs][0] = i;
	}
	rep(i, 1, n) cin >> t[i].val;
	rep(j, 1, 19) rep(i, 1, n) f[i][j] = f[f[i][j-1]][j-1];
	dfs(1);
	rep(i, 1, n-1) bit.update(i, a[i] > a[i+1]);
	rep(i, 1, n) if(check(i)) ans++;
	while(q --> 0){
		int k, x; cin >> k >> x;
		ans -= solve(k);
		upd(t[k].pos, -1);
		a[t[k].pos] = x;
		upd(t[k].pos, 1);
		ans += solve(k);
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：2)

考虑一下判定一个子树 $u$ 合法的充要条件。

首先 $u$ 子树内所有点都应该合法。

然后 $a_u$ 应该大于等于 $u$ 左子树内最大值，小于等于 $u$ 右子树内最小值。这里的最大最小是理论上的，也就是从左子树根一直向右走走到的点与从右子树根一直向左走走到的点。

结合两个判定法则，我们给出 $vis_u$ 在 $a_u$ 满足其大于等于 $u$ 左子树内最大值，小于等于 $u$ 右子树内最小值时为 $1$，否则为 $0$。那么一个子树合法等价于 $\sum_{v \in sub_u} vis_v = sz_u$。

再次注意到，一个点 $v$ 至多作为两个 $u$ 的左子树最大值或右子树最小值，因为一个点只会贡献到其父亲与其向上的极长同向链顶的父亲。

剩下的是简单的，不妨 $val_u = sz_u - \sum_{v \in sub_u} vis_v$，那么一个点 $u$ 合法（$vis_u = 1$）产生的影响就是其到祖先链上所有点 $val_u \gets val_u - 1$，修改时把会影响到的点（根据上文的分析至多只有 $3$ 个）的贡献暴力踢掉修改完再加回来，查询就是查询最小值是否为 $0$ 以及最小值个数，容易在树剖结构上维护以上信息，于是做到了 $O((n+m) \log^2 n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+115;
int n,m;
int lsmx[maxn],rsmi[maxn];
vector<int> jump[maxn];
int ls[maxn],rs[maxn];
int fa[maxn];
int dfn[maxn],dfncnt,node[maxn];
int sz[maxn],son[maxn];
int top[maxn];
int a[maxn];
pair<int,int> tr[maxn<<2];//(val,cnt)
int tag[maxn<<2];
bool chk(int u){
	if(lsmx[u]!=0){
		if(a[lsmx[u]]>a[u]) return false;
	}
	if(rsmi[u]!=0){
		if(a[rsmi[u]]<a[u]) return false;
	}
	return true;
}
void pushdown(int cur){
	if(tag[cur]!=0){
		tr[cur<<1].first+=tag[cur];
		tag[cur<<1]+=tag[cur];
		tr[cur<<1|1].first+=tag[cur];
		tag[cur<<1|1]+=tag[cur];
		tag[cur]=0;	
	}
}
void pushup(int cur){
	if(tr[cur<<1].first!=tr[cur<<1|1].first) tr[cur]=min(tr[cur<<1],tr[cur<<1|1]);
	else{
		tr[cur].first=tr[cur<<1].first;
		tr[cur].second=tr[cur<<1].second+tr[cur<<1|1].second;
	}
}
void build(int cur,int lt,int rt){
	if(lt==rt){
		tr[cur]=make_pair(sz[node[lt]],1);
		return ;
	}
	int mid=(lt+rt)>>1;
	build(cur<<1,lt,mid);
	build(cur<<1|1,mid+1,rt);
	pushup(cur);
}
void add(int cur,int lt,int rt,int l,int r,int c){
	if(rt<l||r<lt) return ;
	if(l<=lt&&rt<=r){
		tr[cur].first+=c;
		tag[cur]+=c;
		return ;
	}
	int mid=(lt+rt)>>1;
	pushdown(cur);
	add(cur<<1,lt,mid,l,r,c);
	add(cur<<1|1,mid+1,rt,l,r,c);
	pushup(cur);
}
void addlist(int u,int c){
	while(top[u]!=0){
		add(1,1,n,dfn[top[u]],dfn[u],c);
		u=fa[top[u]];
	}
}
void dfs1(int u){
	sz[u]=1;
	if(ls[u]!=0){
		dfs1(ls[u]);
		fa[ls[u]]=u;
		if(sz[ls[u]]>sz[son[u]]) son[u]=ls[u];
		sz[u]+=sz[ls[u]];
	}
	if(rs[u]!=0){
		dfs1(rs[u]);
		fa[rs[u]]=u;
		if(sz[rs[u]]>sz[son[u]]) son[u]=rs[u];
		sz[u]+=sz[rs[u]];
	}
	if(ls[u]!=0){
		lsmx[u]=ls[u];
		while(rs[lsmx[u]]!=0) lsmx[u]=rs[lsmx[u]];
		jump[lsmx[u]].push_back(u);
	}	
	if(rs[u]!=0){
		rsmi[u]=rs[u];
		while(ls[rsmi[u]]!=0) rsmi[u]=ls[rsmi[u]];
		jump[rsmi[u]].push_back(u);
	}
}
void dfs2(int u,int tp){
	top[u]=tp;
	dfn[u]=++dfncnt;
	node[dfncnt]=u;
	if(son[u]!=0) dfs2(son[u],tp);
	if(ls[u]!=0&&ls[u]!=son[u]) dfs2(ls[u],ls[u]);
	if(rs[u]!=0&&rs[u]!=son[u]) dfs2(rs[u],rs[u]);
}
void Ins(int u){
	if(chk(u)==true) addlist(u,-1);
}
void Del(int u){
	if(chk(u)==true) addlist(u,1);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>ls[i]>>rs[i];
	for(int i=1;i<=n;i++) cin>>a[i];
	dfs1(1);
	dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=n;i++) Ins(i);
	while(m--){
		int x,v;
		cin>>x>>v;
		Del(x);
		for(int y:jump[x]) Del(y);
		a[x]=v;
		Ins(x);
		for(int y:jump[x]) Ins(y);
		cout<<(tr[1].first!=0?0:tr[1].second)<<'\n';
	}
	return 0;
}
```

---

## 作者：_AyachiNene (赞：2)

# 思路：
首先众所周知的一件事是，bst 的中序遍历是单调不降的。画个图观察一下，还可已发现一件事，一个点的子树的中序遍历是一个连续的区间。观察到这两个性质就很好做了，维护一下 $a_i>a_{i+1}$ 的位置就可以快速判断一个子树是不是 bst。对于修改，考虑维护增量。一次修改显然只和它的祖先有关，并且发现是有单调性的，直接用倍增去找分界点就行了。
# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){x="";char ch=getch();while(!(ch>='a'&&ch<='z')&&!(ch>='A'&&ch<='Z'))ch=getch();while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);putch(' ');write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using IO::read;using IO::write;using IO::putch;
int n,m;
int ch[200005][2];
int a[200005],b[200005];
namespace Nene
{
	int t[200005];
	inline int lowbit(int x){return x&-x;}
	inline void add(int x,int v){for(;x<=n;x+=lowbit(x))t[x]+=v;}
	inline int Query(int x){int res=0;for(;x;x-=lowbit(x))res+=t[x];return res;}
	inline int query(int x,int y){return Query(y)-Query(x);}
}using namespace Nene;
int f[200005][20];
int L[200005],R[200005],dfn[200005],cnt;
void dfs(int u,int fa)
{
	f[u][0]=fa;
	for(int i=1;i<20;i++) f[u][i]=f[f[u][i-1]][i-1];
	L[u]=cnt+1;
	if(ch[u][0]) dfs(ch[u][0],u);
	dfn[u]=++cnt;
	if(ch[u][1]) dfs(ch[u][1],u);
	R[u]=cnt;
}
inline int solve(int u)
{
	if(query(L[u],R[u])) return 0;
	int res=0;
	for(int i=19;~i;i--) if(f[u][i]&&query(L[f[u][i]],R[f[u][i]])==0) res+=(1<<i),u=f[u][i];
	return res+1;
}
int ans;
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	for(int i=1;i<=n;i++) read(ch[i][0],ch[i][1]);
	for(int i=1;i<=n;i++) read(b[i]);
	dfs(1,0);
	for(int i=1;i<=n;i++) a[dfn[i]]=b[i];
	for(int i=2;i<=n;i++) if(a[i]<a[i-1]) add(i,1);
	for(int i=1;i<=n;i++) if(query(L[i],R[i])==0) ++ans;
	a[n+1]=1e9;
	while(m--)
	{
		int u,x;read(u,x);
		ans-=solve(u);
		if(a[dfn[u]-1]>a[dfn[u]]) add(dfn[u],-1);
		if(a[dfn[u]+1]<a[dfn[u]]) add(dfn[u]+1,-1);
		a[dfn[u]]=x;
		if(a[dfn[u]-1]>a[dfn[u]]) add(dfn[u],1);
		if(a[dfn[u]+1]<a[dfn[u]]) add(dfn[u]+1,1);
		ans+=solve(u);
		write(ans),putch('\n');
	}
	IO::flush();
	return 0;
}
```

---

## 作者：Jorisy (赞：1)

几周前被扔到了模拟赛 T2，然后被爆了 /ll。

下面记 $\text{dfn}_i$ 表示节点 $i$ 的先序遍历序，$\text{mdn}_i$ 表示节点 $i$ 的中序遍历序，$\text{imdn}_i$ 表示中序遍历序为 $i$ 的节点编号。

对于 BST 内节点 $\text{imdn}_i$ 的权值 $a_{\text{imdn}_i}$，其有最严格的区间限制 $[a_{\text{imdn}_i-1},a_{\text{imdn}_i+1}]$。

就是说如果 $a_{\text{imdn}_{i-1}}>a_{\text{imdn}_i}$，那么 $t=\text{LCA}(\text{imdn}_{i-1},\text{imdn}_{i})$ 及其祖先为根的子树当然都不合法（另一种情况同理），这里 $t$ 给予的贡献就是其深度。

考虑用 set 维护这些不合法的 $t$ 到链的节点并，以 $\text{dfn}_t$ 为关键字。

当要新加入 $t$ 时，在 set 里二分出最大的 $l$，最小的 $r$，满足 $\text{dfn}_l<\text{dfn}_t<\text{dfn}_r$，利用 $l,t,r$ 两两的 LCA 计算贡献即可。删除 $t$ 是同理的。

时间复杂度 $O(n\log^2n+m\log^2n)$。
```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;

struct node{
    int lc,rc,x;
}tr[N];
struct info{
    int x;
};
set<info>st;
int n,m,dep[N],fa[N][25],tot,dfn[N],totm,mdn[N],imdn[N],ans,c[N];

bool operator<(info x,info y)
{
    return dfn[x.x]<dfn[y.x];
}

void dfs(int x,int lst=0)
{
    fa[x][0]=lst;
    dep[x]=dep[lst]+1;
    dfn[x]=++tot;
    if(tr[x].lc) dfs(tr[x].lc,x);
    mdn[x]=++totm;
    imdn[totm]=x;
    if(tr[x].rc) dfs(tr[x].rc,x);
}

int lca(int u,int v)
{
    if(dep[u]<dep[v]) swap(u,v);
    for(int i=20;~i;i--)
    {
        if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
    }
    if(u==v) return u;
    for(int i=20;~i;i--)
    {
        if(fa[u][i]!=fa[v][i])
        {
            u=fa[u][i];
            v=fa[v][i];
        }
    }
    return fa[u][0];
}

void upd(int x,int d)
{
    if(d==-1) c[x]--;
    if(c[x])
    {
        if(d==1) c[x]++;
        return;
    }
    if(d==1) c[x]++;
    ans+=dep[x]*d;
    if(d==-1) st.erase({x});
    auto p=st.lower_bound({x});
    int r=p==st.end()?0:(*p).x,l=p==st.begin()?0:(*--p).x;
    if(l) ans-=dep[lca(l,x)]*d;
    if(r) ans-=dep[lca(r,x)]*d;
    if(l&&r) ans+=dep[lca(l,r)]*d;
    if(d==1) st.insert({x});
}

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",&tr[i].lc,&tr[i].rc);
    dfs(1);
    for(int j=1;j<=20;j++)
    {
        for(int i=1;i<=n;i++)
        {
            fa[i][j]=fa[fa[i][j-1]][j-1];
        }
    }
    for(int i=1;i<=n;i++) scanf("%d",&tr[mdn[i]].x);
    for(int i=1;i<n;i++)
    {
        if(tr[i].x>tr[i+1].x) upd(lca(imdn[i],imdn[i+1]),1);
    }
    while(m--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        x=mdn[x];
        if(x>1&&tr[x-1].x>tr[x].x) upd(lca(imdn[x-1],imdn[x]),-1);
        if(x<n&&tr[x].x>tr[x+1].x) upd(lca(imdn[x],imdn[x+1]),-1);
        tr[x].x=y;
        if(x>1&&tr[x-1].x>tr[x].x) upd(lca(imdn[x-1],imdn[x]),1);
        if(x<n&&tr[x].x>tr[x+1].x) upd(lca(imdn[x],imdn[x+1]),1);
        printf("%d\n",n-ans);
    }
	return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：1)

某机构 CSP-S 摸你赛 T2，赛时没有场切。

这里提供一个 BIT + 倍增做法。

首先，由原题 BST 的限制我们可以想到~~平衡树~~中序遍历。

这里记节点 $u$ 的中序遍历编号为 $d_u$，以 $u$ 为根的子树对应的 $d$ 值构成区间 $[l_u,r_u]$，$v_u$ 表示 $d$ 值为 $u$ 的结点的权值。

这时，以 $u$ 为根的子树是 BST 当且仅当区间 $[l_u,r_u]$ 的 $v$ 值不降。

这部分可以用 BIT 维护，维护 $v_i$ 是否大于 $v_{i+1}$，限制被转化为在 BIT 上区间 $[l_u,r_u)$ 的和为 $0$。

此时，单点修改只会在 BIT 上影响位置 $i-1$，$i$，直接暴力改即可。

接下来就只需要统计答案了。

发现如果以 $u$ 为根的子树是 BST，则以 $u$ 的子节点为根的子树也是 BST，同时修改 $u$ 的点权相当于更新 $u$ 到根的路径上的点是否是 BST。

依此，我们可以通过倍增找到 $u$ 到根的路径上离根最近，且满足以该节点为根的子树是 BST 的节点 $v$。

这样就可以维护 ans，初始的 ans 可以 $O(n)$ 预处理，每次修改时先清空从 $x$ 到根的路径上的贡献（上文 $u$，$v$ 距离），然后更新 BIT，最后加上从 $x$ 到根的路径上的贡献即可。

复杂度 $O(n+q\log^2n)$。

NOIP 2024 RP++

代码：


```cpp
#include<bits/stdc++.h>
#define gc getchar
using namespace std;
const int N=2e5+10;
int mx[N],mn[N];bool isb[N];
struct tree{
    int ls,rs,fa,vl;
}T[N];
int n,q;
void pu(int x){
    mx[x]=T[x].vl;mn[x]=T[x].vl;
    mx[x]=max(mx[x],max(mx[T[x].ls],mx[T[x].rs]));
    mn[x]=min(mn[x],min(mn[T[x].ls],mn[T[x].rs]));
}int cnt=0,tot=0;
void dete(int x){
    if(isb[x]) cnt--;isb[x]=0;
    if(mx[T[x].ls]<=T[x].vl&&T[x].vl<=mn[T[x].rs]&&isb[T[x].ls]&&isb[T[x].rs]) cnt++,isb[x]=1;
}int dfn[N],val[N],lp[N],rp[N],fa[N][22];
void dfs(int x){
    if(!x) return ;
    fa[x][0]=T[x].fa;
    for(int i=1;i<=18;i++){
        fa[x][i]=fa[fa[x][i-1]][i-1];
        //cout<<x<<' '<<i<<' '<<fa[x][i]<<endl;
    }
    lp[x]=tot+1;
    dfs(T[x].ls);
    dfn[x]=++tot;
    dfs(T[x].rs);
    rp[x]=tot;
    pu(x);dete(x);
}struct BIT{
    int T[N];
    #define lb(x) (x&(-x))
    void upd(int x,int v){
        for(int i=x;i<=n;i+=lb(i)) T[i]+=v;
    }int qry(int x){
        int res=0;
        for(int i=x;i>0;i-=lb(i)) res+=T[i];
        return res;
    }
    #undef lb
}bit;
bool chk(int x){
    if(x==0) return 0;
    if(bit.qry(rp[x]-1)-bit.qry(lp[x]-1)>0) return 0;
    else return 1;
}void upd(int x,int op){
    int res=0;
    if(!chk(x)) return ;
    res++;
    for(int i=18;i>=0;i--){
        if(chk(fa[x][i])){
            x=fa[x][i];res+=1<<i;
        }
    }if(op==0) cnt-=res;else cnt+=res;
}inline int read(){
    int t=0,f=1;char ch=gc();
    while(!(ch>='0'&&ch<='9')){
        if(ch=='-') f=-1;ch=gc();
    }while(ch>='0'&&ch<='9') t=t*10+ch-'0',ch=gc();
    return t*f;
}
int main(){
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        int l=read(),r=read();
        T[i].ls=l;T[i].rs=r;
        if(l!=0) T[l].fa=i;
        if(r!=0) T[r].fa=i;
    }for(int i=1;i<=n;i++) T[i].vl=read();
    mn[0]=0x3f3f3f3f,mx[0]=0;isb[0]=1;
    dfs(1);
    for(int i=1;i<=n;i++) val[dfn[i]]=T[i].vl;
    for(int i=1;i<n;i++) if(val[i]>val[i+1]) bit.upd(i,1);
    while(q--){
        int x=read(),v=read();
        T[x].vl=v;upd(x,0);
        //for(int i=1;i<=n;i++) cout<<val[i]<<' ';cout<<endl;
        //for(int i=1;i<n;i++) cout<<(bit.qry(i)-bit.qry(i-1))<<' ';cout<<endl;
        //cout<<cnt<<endl;
        val[dfn[x]]=v;
        if(dfn[x]>1){
            if(bit.qry(dfn[x]-1)-bit.qry(dfn[x]-2)>0){
                bit.upd(dfn[x]-1,-1);
            }if(val[dfn[x]-1]>val[dfn[x]]) bit.upd(dfn[x]-1,1);
        }if(dfn[x]+1<=n){
            if(bit.qry(dfn[x])-bit.qry(dfn[x]-1)>0){
                bit.upd(dfn[x],-1);
            }if(val[dfn[x]]>val[dfn[x]+1]) bit.upd(dfn[x],1);
        }
        int now=x;upd(x,1);
        //for(int i=1;i<=n;i++) cout<<isb[i]<<' ';
        printf("%d\n",cnt);
    }
    return 0;
}
```

---

## 作者：Reunite (赞：1)

在线 $O(n\log n)$ 题解。先膜拜 ke。

考虑二叉搜索树的性质：中序遍历升序。所以考虑先拉出中序遍历，显然只需考虑相邻逆序的情况。如果有 $u,v$ 在中序遍历上相邻逆序，那么他们不能在同一个点的子树内，也就是 ban 掉了 $lca(u,v)$ 到根链上的所有点。现在我们提取出 $O(n)$ 个点，希望求出他们到根链的并。

有经典结论：若干个点到根链的并，等于把他们按照 $dfn$ 序升序排序，用 $\sum dep$ 减去两两相邻 $lca$ 的 $dep$ 和。这是方便用一个 set 维护的，但是这题里面，可能有不同的限制点对 $(u,v)$ 的 $lca$ 相同，因此不能直接做而要在每个点第一次被加入和最后一次被删除的时候统计贡献。

修改仅需动态修改 $O(1)$ 个信息，每次先撤销再加入贡献即可。为了方便使用了 map，复杂度 $O((n+m)\log n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

int n,m,t,tm,s;
int a[200005];
int b[200005];
int it[200005];
int ti[200005];
int lg[200005];
int dep[200005];
int dfn[200005];
int ch[200005][2];
int mi[20][200005];
map <pair <int,int>,int> mp;

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline int get(int x,int y){return dfn[x]<dfn[y]?x:y;}

inline void dfs(int u,int fa){
	if(!u) return ;
	dep[u]=dep[fa]+1;
	mi[0][dfn[u]=++tm]=fa;
	dfs(ch[u][0],u);
	t++;
	it[u]=t,ti[t]=u,b[t]=a[u];
	dfs(ch[u][1],u);
	return ;
}

inline int LCA(int u,int v){
	if(u==v) return u;
	if((u=dfn[u])>(v=dfn[v])) swap(u,v);
	int d=lg[v-u++];
	return get(mi[d][u],mi[d][v-(1<<d)+1]);
}

inline void add(int u){
	mp[{dfn[u],u}]++;
	if(mp[{dfn[u],u}]>1) return ;
	s+=dep[u];
	if(mp.size()==1) return ;
	auto it=mp.find({dfn[u],u});
	if(next(it)==mp.end()){
		s-=dep[LCA(u,(*prev(it)).first.second)];
		return ;
	}
	if(it==mp.begin()){
		s-=dep[LCA(u,(*next(it)).first.second)];
		return ;
	}
	int lf=(*prev(it)).first.second,rt=(*next(it)).first.second;
	s+=dep[LCA(lf,rt)];
	s-=dep[LCA(lf,u)]+dep[LCA(rt,u)];

	return ;
}

inline void del(int u){
	mp[{dfn[u],u}]--;
	if(mp[{dfn[u],u}]) return ;
	s-=dep[u];
	if(mp.size()==1){mp.clear();return ;}
	auto it=mp.find({dfn[u],u});
	if(next(it)==mp.end()){
		s+=dep[LCA(u,(*prev(it)).first.second)];
		mp.erase({dfn[u],u});
		return ;
	}
	if(it==mp.begin()){
		s+=dep[LCA(u,(*next(it)).first.second)];
		mp.erase({dfn[u],u});
		return ;
	}
	int lf=(*prev(it)).first.second,rt=(*next(it)).first.second;
	s-=dep[LCA(lf,rt)];
	s+=dep[LCA(lf,u)]+dep[LCA(rt,u)];
	mp.erase({dfn[u],u});

	return ;
}

int main(){
	in(n),in(m);
	for(int i=1;i<=n;i++) in(ch[i][0]),in(ch[i][1]);
	for(int i=1;i<=n;i++) in(a[i]);
	dfs(1,0);
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int j=1;j<=lg[n];j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			mi[j][i]=get(mi[j-1][i],mi[j-1][i+(1<<(j-1))]);
	b[n+1]=2e9;
	for(int i=1;i<=n;i++) 
		if(a[i]>b[it[i]+1]){
			int x=LCA(i,ti[it[i]+1]);
			mp[{dfn[x],x}]++;
		}
	auto itt=mp.begin();
	while(itt!=mp.end()){
		s+=dep[(*itt).first.second];
		if(next(itt)!=mp.end())
			s-=dep[LCA((*itt).first.second,(*next(itt)).first.second)];
		itt++;
	}
	while(m--){
		int u,x;
		in(u),in(x);
		if(it[u]!=1&&a[u]<b[it[u]-1]) del(LCA(u,ti[it[u]-1]));
		if(it[u]!=n&&a[u]>b[it[u]+1]) del(LCA(u,ti[it[u]+1]));
		a[u]=x,b[it[u]]=x;
		if(it[u]!=1&&a[u]<b[it[u]-1]) add(LCA(u,ti[it[u]-1]));
		if(it[u]!=n&&a[u]>b[it[u]+1]) add(LCA(u,ti[it[u]+1]));
		printf("%d\n",n-s);
	}

	return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

一棵二叉树是 BST 的充要条件是中序遍历的权值升序。

$O(n \log^2 n)$ 的做法是显然的，因为每次修改只会影响这个点到根的路径的答案，倍增更新一下就好。

考虑 $O(n \log n)$ 做法，发现不满足要求的点是若干条到根的路径取并集。

这个东西是很套路化的，把所有点按 $dfn$ 排序后，求出 $(\sum \text{dep}_u) - (\sum \text{dep}_{lca(s_i,s_{i+1})})$，这个拿个 set 动态维护贡献就好。

总时间 $O(n\log n)$，空间线性。

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑一个 $u$ 子树是 BST 的充分条件是什么：

- 对于 $u$ 子树内的任意一个点 $v$，$v$ 子树都是 BST。

- $a_u$ 大于等于左子树内的任意一个点，即大于等于左子树内最大值。

- $a_u$ 小于等于右子树内的任意一个点，即小于等于左子树内最小值。

动态维护子树最大值是 hard 的~~至少对于我这个数据结构蒟蒻来说~~。

考虑在条件 $1$ 满足的情况下（即子树内所有子树均为 SBT），故左子树的最大值的位置是左儿子右链底端，右子树的最小值的位置是右儿子左链底端；设起分别为 $L_u, R_u$。

故设 $u$ 是好的当且仅当 $a_{L_u} \le a_u \le a_{R_u}$；一个子树 BST 当且仅当子树内所有点都是好的。

故我们考虑维护每个点是否**不是好的**，即维护区间**不是好的**的点的个数；则一个子树是是好的需要满足**不是好的**的点的个数为 $0$。

那么相当于查询全局 $0$ 的个数（也即最小值的个数），需要维护到根节点的路径加，全局最小值出现次数；使用树链剖分即可。

时间复杂度为 $O(N \log^2 N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, q, x, y;
int a[N], L[N], R[N];
int lson[N], rson[N];
vector<int> E[N], G[N];
inline bool check(int x){
	return (a[L[x]] <= a[x]) && (a[x] <= a[R[x]]);
}
inline void add(int u, int v){
	E[u].push_back(v);
}
namespace Tree{
	int cnt = 0;
	int id[N], dfn[N], top[N], siz[N], dep[N], son[N], fa[N];
	inline void dfs1(int u, int f){
		siz[u] = 1;
		for(auto v : E[u]){
			if(v == f)
			  continue;
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs1(v, u);
			siz[u] += siz[v];
			if(siz[v] > siz[son[u]])
			  son[u] = v;
		}
	}
	inline void dfs2(int u, int k){
		++cnt;
		dfn[u] = cnt;
		id[cnt] = u;
		top[u] = k;
		if(!son[u])
		  return ;
		dfs2(son[u], k);
		for(auto v : E[u]){
			if(v == son[u] || v == fa[u])
			  continue;
			dfs2(v, v);
		}
	}
	namespace Seg{
		struct Node{
			int l, r;
			int Min;
			int sum;
			int tag;
		}X[N << 2];
		inline void pushup(int k){
			X[k].sum = 0;
			X[k].Min = min(X[k << 1].Min, X[k << 1 | 1].Min);
			if(X[k].Min == X[k << 1].Min)
			  X[k].sum += X[k << 1].sum;
			if(X[k].Min == X[k << 1 | 1].Min)
			  X[k].sum += X[k << 1 | 1].sum;
		}
		inline void add(int k, int v){
			X[k].Min += v;
			X[k].tag += v;
		}
		inline void push_down(int k){
			if(X[k].tag){
				add(k << 1, X[k].tag);
				add(k << 1 | 1, X[k].tag);
				X[k].tag = 0;
			}
		}
		inline void build(int k, int l, int r){
			X[k].l = l, X[k].r = r;
			if(l == r){
				X[k].sum = 1;
				return ;
			}
			int mid = (l + r) >> 1;
			build(k << 1, l, mid);
			build(k << 1 | 1, mid + 1, r);
			pushup(k);
		}
		inline void update(int k, int l, int r, int v){
			if(X[k].l == l && r == X[k].r){
				add(k, v);
				return ;
			}
			push_down(k);
			int mid = (X[k].l + X[k].r) >> 1;
			if(r <= mid)
			  update(k << 1, l, r, v);
			else if(l > mid)
			  update(k << 1 | 1, l, r, v);
			else{
				update(k << 1, l, mid, v);
				update(k << 1 | 1, mid + 1, r, v);
			}
			pushup(k);
		}
	};
	inline void update(int x, int y, int v){
		while(top[x] != top[y]){
			if(dep[top[x]] < dep[top[y]])
			  swap(x, y);
			Seg::update(1, dfn[top[x]], dfn[x], v);
			x = fa[top[x]];
		}
		if(dep[x] > dep[y])
		  swap(x, y);
		Seg::update(1, dfn[x], dfn[y], v);
	}
	inline void init(int rt = 1){
		dfs1(rt, rt);
		dfs2(rt, rt);
		Seg::build(1, 1, n);
	}
	inline int get(){
		if(Seg::X[1].Min)
		  return 0;
		return Seg::X[1].sum;
	}
};
bool End;
int main(){
	n = read(), q = read();
	for(int i = 1; i <= n; ++i){
		lson[i] = read(), rson[i] = read();
		if(lson[i])
		  add(i, lson[i]);
		if(rson[i])
		  add(i, rson[i]);
	}
	for(int i = 1; i <= n; ++i)
	  a[i] = read();
	a[n + 1] = 1e9;
	for(int i = 1; i <= n; ++i){
		x = lson[i];
		while(rson[x])
		  x = rson[x];
		L[i] = x;
		x = rson[i];
		while(lson[x])
		  x = lson[x];
		if(!x)
		  x = n + 1;
		R[i] = x;
		G[L[i]].push_back(i);
		G[R[i]].push_back(i);
	}
	Tree::init();
	for(int i = 1; i <= n; ++i)
	  if(!check(i))
	    Tree::update(1, i, 1);
	while(q--){
		x = read(), y = read();
		if(check(x))
		  Tree::update(1, x, 1);
		for(auto v : G[x])
		  if(check(v))
		    Tree::update(1, v, 1);
		a[x] = y;
		if(check(x))
		  Tree::update(1, x, -1);
		for(auto v : G[x])
		  if(check(v))
		    Tree::update(1, v, -1);	
		write(Tree::get());
		putchar('\n');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：Rem_CandleFire (赞：0)

PS：校内模拟赛 T2。

显然只需要考虑每次修改的点 $x$ 对答案的影响，那么首先得到不修改时有多少个点满足条件，这是简单的。

考虑二叉搜索树的性质，发现若一棵树是二叉搜索树，那么其中序遍历应当不降。于是中序遍历树得到点 $u$ 为根的子树的区间 $[L_u,R_u]$。用树状数组维护中序遍历序列 $a$，把所有 $a_i> a_{i+1}$ 的位置 $i$ 加入树状数组。那么查询某点 $u$ 是否合法，只需要看 $[L_u,R_u]$ 的值是否等于 $0$。而且点权只会影响该点到根的路径，合法的点一定连续，于是树上倍增即可。

具体的对于每次修改 $x,v$，撤销 $x$ 的影响，修改树状数组，加入新的点权的影响。时间复杂度 $O(n\log^2n)$。

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,tim,ans;
struct Treearray
{
	int val[N];
	void Add(int x,int v) { for(;x<=n;x+=x&-x) val[x]+=v; }
	int Query(int x) 
	{
		int ret=0;
		for(;x;x-=x&-x) ret+=val[x];
		return ret;
	}
} T;
struct node { int val,ls,rs; } tr[N];
int L[N],R[N],ok[N],mx[N],mn[N],dfn[N],val[N];
int fa[25][N];
void Dfs(int u)
{
	if(!u) return ;
	L[u]=tim+1; Dfs(tr[u].ls); 
	dfn[u]=++tim; val[tim]=tr[u].val;
	Dfs(tr[u].rs); R[u]=tim; 
	mx[u]=mn[u]=tr[u].val;
	ok[u]=1;
	if(tr[u].ls)
	{
		ok[u]&=ok[tr[u].ls];
		if(mx[tr[u].ls]>tr[u].val) ok[u]=0;
		mx[u]=max(mx[u],mx[tr[u].ls]);
		mn[u]=min(mn[u],mn[tr[u].ls]);
		fa[0][tr[u].ls]=u;
	}
	if(tr[u].rs)
	{
		ok[u]&=ok[tr[u].rs];
		if(mn[tr[u].rs]<tr[u].val) ok[u]=0;
		mx[u]=max(mx[u],mx[tr[u].rs]);
		mn[u]=min(mn[u],mn[tr[u].rs]);
		fa[0][tr[u].rs]=u;
	}
	ans+=ok[u];
}
bool Check(int x) { return T.Query(R[x]-1)-T.Query(L[x]-1)==0; }
int Calc(int x)
{
	if(!Check(x)) return 0;
	int ret=1;
	for(int i=20;i>=0;i--)
		if(fa[i][x]&&Check(fa[i][x]))
			x=fa[i][x],ret+=1<<i;
	return ret;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&tr[i].ls,&tr[i].rs);
	for(int i=1;i<=n;i++) scanf("%d",&tr[i].val);
	Dfs(1);
	for(int i=1;i<n;i++) if(val[i]>val[i+1]) T.Add(i,1);
	for(int i=1;i<=20;i++)
		for(int j=1;j<=n;j++)
			fa[i][j]=fa[i-1][fa[i-1][j]];
	for(int x,v;m>=1;m--)
	{
		scanf("%d%d",&x,&v); int p=dfn[x];
		ans-=Calc(x);
		if(p<n&&val[p]>val[p+1]) T.Add(p,-1);
		if(p>1&&val[p]<val[p-1]) T.Add(p-1,-1);
		val[p]=v;
		if(p<n&&val[p]>val[p+1]) T.Add(p,1);
		if(p>1&&val[p]<val[p-1]) T.Add(p-1,1);
		ans+=Calc(x);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
剖剖剖！

感觉克罗地亚出题人好强啊。

广告：[『从入门到入土』树链剖分学习笔记](https://www.luogu.com.cn/article/56o68hfu)。
## 思路分析
判断是否为 BST，貌似不是很常见。

不常见的东西肯定还是常见的做法，先建模转化。

BST 的判定无非也就是对于点 $u$ 而言：
1. 要**不小于**左子树里的点权。
2. 要**不大于**右子树里的点权。

把点 $u$ 和子树里的点对比显然是愚蠢的，我们考虑合并了子树信息再和 $u$ 对比。

具体的其实就是很显然的转化为：
1. **不小于**左子树里的**最大**点权。
2. **不大于**右子树里的**最小**点权。

动态改点权维护子树最值还是太 hard 了，找找性质。

注意到如果点 $u$ 是 BST，那么他的左右子树也都是 BST。

同理可以递归出任意一个子树都是 BST。

那么这里也就很显然了，左子树里的**最大**点权就是左儿子的右链底的叶子点权，右子树则同理了。

那么对于点 $u$ 的判定就转移到了两个叶子上去。

那么我们的修改对于单点的影响就是 O(1) 的了。

然后考虑推广到整个树上去。

我们不妨对每个点维护出其子树内不合法点个数，那么就是全局数 $0$ 个数。

修改就是很简单的 3 个链改，直接线段树即可。
## 代码

```cpp
#include <bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=3e5+10,V=131072,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f,lim=19;
int n,m,cnt,l[N],r[N],a[N];vector<int>e[N],c[N];
int si[N],son[N],fa[N],dep[N];
int dfn[N],id[N],top[N];
int t[N<<2],g[N<<2],lz[N<<2];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void dfs1(int u,int ff)
{
    if(!u) return ;si[u]=1;fa[u]=ff;dep[u]=dep[ff]+1;
    for(auto v:e[u]) if(v!=ff)
    {
        dfs1(v,u);si[u]+=si[v];
        if(si[v]>si[son[u]]) son[u]=v;
    }
}
inline void dfs2(int u,int topf)
{
    if(!u) return ;top[u]=topf;dfn[u]=++cnt;id[cnt]=u;
    if(son[u]) dfs2(son[u],topf);
    for(auto v:e[u]) if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
}
inline void pushup(int p)
{
    t[p]=t[ls];g[p]=g[ls];
    if(t[p]>t[rs]) t[p]=t[rs],g[p]=g[rs];
    else if(t[p]==t[rs]) g[p]+=g[rs];
}
inline void build(int p,int l,int r)
{
    if(l==r) return t[p]=si[id[l]],g[p]=1,void();
    build(ls,l,mid);build(rs,mid+1,r);pushup(p);
}
inline void pushson(int p,int w){t[p]+=w;lz[p]+=w;}
inline void pushdown(int p){pushson(ls,lz[p]);pushson(rs,lz[p]);lz[p]=0;}
inline void modify(int p,int l,int r,int s,int e,int w)
{
    if(s>e) return;
    if(l>=s&&r<=e) return pushson(p,w);pushdown(p);
    if(mid>=s) modify(ls,l,mid,s,e,w);
    if(mid<e) modify(rs,mid+1,r,s,e,w);pushup(p);
}
inline void modify(int u,int w){while(top[u]) modify(1,1,n,dfn[top[u]],dfn[u],w),u=fa[top[u]];}
inline bool check(int u){return a[u]>=a[l[u]]&&a[u]<=a[r[u]];}
inline void solve()
{
    n=read(),m=read();for(int i=1;i<=n;i++) e[i].emplace_back(read()),e[i].emplace_back(read());
    dfs1(1,0);dfs2(1,1);build(1,1,n);a[n+1]=INF;e[0].emplace_back(0),e[0].emplace_back(0);
    for(int i=1,x;i<=n;i++)
    {
        x=e[i][0];while(e[x][1]) x=e[x][1];l[i]=x;
        c[x].emplace_back(i);x=e[i][1];while(e[x][0]) x=e[x][0];r[i]=x;
        c[x].emplace_back(i);if(!r[i]) r[i]=n+1;a[i]=read();
    }for(int i=1;i<=n;i++) if(check(i)) modify(i,-1);
    for(int i=1,x;i<=m;i++)
    {
        x=read();if(check(x)) modify(x,1);
        for(auto f:c[x]) if(check(f)) modify(f,1);a[x]=read();
        if(check(x)) modify(x,-1);
        for(auto f:c[x]) if(check(f)) modify(f,-1);
        print(t[1]!=0?0:g[1]);put('\n');
    }
}
signed main()
{
    int T=1;
    // T=read();
    while(T--) solve();
    flush();return 0;
}
```

---

## 作者：happybob (赞：0)

两个 $\log$ 做法很简单，容易注意到一个点为根子树若不是 BST，则祖先为根的子树也不是。每次倍增即可。

我们来考虑复杂度更优的做法。

我们直接取出整棵树的中序遍历，显然每个点子树的中序遍历是一段区间。问题变成初始给定若干区间，序列单点修改，询问有多少给定区间不降排序。类似 ODT，我们维护若干极长不降连续段，每次单点修改是 $O(1)$ 个段的分裂合并，每个段内的答案是二维数点，在线主席树或离线树状数组都可以做到 $O(n\log n)$。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long

using ll = long long;

const int N = 2e5 + 5, MOD = 1e9 + 7, HSMOD = 1610612741, HSMOD2 = 998244353; // Remember to change

int n, q, ls[N],rs[N];
int a[N],ra[N];

int id[N],sz[N],idx,minn[N],maxn[N];

void dfs(int u)
{
	minn[u]=(int)1e9,maxn[u]=0;
	sz[u]=1;
	if(ls[u]) dfs(ls[u]),minn[u]=minn[ls[u]],maxn[u]=maxn[ls[u]];
	id[u]=++idx;
	ra[idx]=a[u];
	minn[u]=min(minn[u],idx);
	maxn[u]=max(maxn[u],idx);
	if(rs[u]) dfs(rs[u]),minn[u]=min(minn[u],minn[rs[u]]),maxn[u]=max(maxn[u],maxn[rs[u]]);
}

class SegmentTree
{
public:
	struct Node
	{
		int ls,rs,sum;
	}tr[N*80];
	int idx;
	int ins(int p,int x, int l,int r)
	{
		int u=++idx;
		tr[u]=tr[p];
		if(l==r)
		{
			tr[u].sum++;
			return u;
		}
		int mid=l+r>>1;
		if(x<=mid)tr[u].ls=ins(tr[p].ls,x,l,mid);
		else tr[u].rs=ins(tr[p].rs,x,mid+1,r);
		tr[u].sum=tr[tr[u].ls].sum+tr[tr[u].rs].sum;
		return u;
	}
	int query(int p,int q,int l,int r,int nl,int nr)
	{
		if(nl>=l&&nr<=r) 
		{
			return tr[q].sum-tr[p].sum;
		}
		int mid=nl+nr>>1,res=0;
		if(l<=mid) res=query(tr[p].ls,tr[q].ls,l,r,nl,mid);
		if(r>mid) res+=query(tr[p].rs,tr[q].rs,l,r,mid+1,nr);
		return res;
	}
}sgt;

int fa[N],rt[N];
vector<int> L[N];

inline int qlr(int l,int r)
{
	if(l>r||l<0) return 0;
	return sgt.query(rt[l-1],rt[r],l,r,1,n);
}

int main()
{
	//freopen("D:\\模拟赛\\MX NOIP13 连测\\2024.8.4\\additional_file_1216_2\\3.in", "r", stdin);
	//freopen("D:\\模拟赛\\MX NOIP13 连测\\2024.8.4\\additional_file_1216_2\\3.ans", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>ls[i]>>rs[i];
		if(ls[i]) fa[ls[i]]=i;
		if(rs[i]) fa[rs[i]]=i;
	}
	for(int i=1;i<=n;i++) cin>>a[i];
	dfs(1);
	for(int i=1;i<=n;i++)
	{
		L[maxn[i]].emplace_back(minn[i]);
	} 
	for(int i=1;i<=n;i++)
	{
		int lst=rt[i-1];
		for(auto&j:L[i])
		{
			lst=sgt.ins(lst,j,1,n);
		}
		rt[i]=lst;
	}
	set<pair<int, int>> st;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n+1;j++)
		{
			if(j==n+1||ra[j-1]>ra[j])
			{
				st.insert(make_pair(i,j-1));
				ans+=qlr(i,j-1);
				i=j-1;
				break;
			}
		}
	}
	auto add=[&](int l,int r)
	{
		if(l>r) return;
		ans+=qlr(l,r);
		st.insert(make_pair(l,r));
	};
	auto del=[&](int l,int r)
	{
		if(l>r||!st.count(make_pair(l,r))) return;
		ans-=qlr(l,r);
		st.erase(make_pair(l,r));
	};
	while(q--)
	{
		int k,x;
		cin>>k>>x;
		k=id[k];
		auto it=st.upper_bound(make_pair(k,(int)1e9));
		--it;
		int l=it->first,r=it->second;
		int prel=-1,prer=-1;
		int nxtl=-1,nxtr=-1;
		if(it!=st.begin())
		{
			--it;
			prel=it->first,prer=it->second;
			++it;
		}
		if(it!=--st.end())
		{
			++it;
			nxtl=it->first,nxtr=it->second;
			--it;
		}
		ans-=qlr(l,r)+qlr(prel,prer)+qlr(nxtl,nxtr);
		st.erase(it);
		if(st.count(make_pair(prel,prer))) st.erase(make_pair(prel,prer));
		if(st.count(make_pair(nxtl,nxtr))) st.erase(make_pair(nxtl,nxtr));
		ra[k]=x;
		if(prer!=-1&&ra[prer+1]>=ra[prer])
		{
			if(nxtl!=-1&&ra[nxtl-1]<=ra[nxtl])
			{
				add(prel,nxtr);
			}
			else
			{
				if(ra[k]<=ra[k+1]||k==r)
				{
					add(prel,r);
					add(nxtl,nxtr);
				}
				else
				{
					add(prel,l),add(l+1,r),add(nxtl,nxtr);
				}
			}
		}
		else if(nxtl!=-1&&ra[nxtl-1]<=ra[nxtl])
		{
			if(ra[k-1]<=ra[k])
			{
				add(prel,prer);
				add(l,nxtr);
			}
			else
			{
				add(prel,prer);
				add(l,r-1);
				add(r,nxtr);
			}
		}
		else
		{
			if(k==l&&k==r)
			{
				add(l,r);
				add(prel,prer);
				add(nxtl,nxtr);
			}
			else
			{
				if(k==l)
				{
					if(ra[k]<=ra[k+1])
					{
						add(prel,prer);
						add(l,r);
						add(nxtl,nxtr);
					}
					else
					{
						add(prel,prer);
						add(l,l);
						add(l+1,r);
						add(nxtl,nxtr);
					}
				}
				else if(k==r)
				{
					if(ra[k-1]<=ra[k])
					{
						add(prel,prer);
						add(l,r);
						add(nxtl,nxtr);
					}
					else
					{
						add(prel,prer);
						add(l,r-1);
						add(r,r);
						add(nxtl,nxtr);
					}
				}
				else
				{
					bool lt=(ra[k-1]<=ra[k]),rt=(ra[k]<=ra[k+1]);
					if(lt&&rt)
					{
						add(prel,prer);
						add(l,r);
						add(nxtl,nxtr);
					}
					else if(lt&&!rt)
					{
						add(prel,prer);
						add(l,k);
						add(k+1,r);
						add(nxtl,nxtr);
					}
					else if(rt&&!lt)
					{
						add(prel,prer);
						add(l,k-1);
						add(k,r);
						add(nxtl,nxtr);
					}
					else
					{
						add(prel,prer);
						add(l,k-1);
						add(k,k);
						add(k+1,r);
						add(nxtl,nxtr);
					}
				}
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

