# Middle Duplication

## 题目描述

A binary tree of $ n $ nodes is given. Nodes of the tree are numbered from $ 1 $ to $ n $ and the root is the node $ 1 $ . Each node can have no child, only one left child, only one right child, or both children. For convenience, let's denote $ l_u $ and $ r_u $ as the left and the right child of the node $ u $ respectively, $ l_u = 0 $ if $ u $ does not have the left child, and $ r_u = 0 $ if the node $ u $ does not have the right child.

Each node has a string label, initially is a single character $ c_u $ . Let's define the string representation of the binary tree as the concatenation of the labels of the nodes in the in-order. Formally, let $ f(u) $ be the string representation of the tree rooted at the node $ u $ . $ f(u) $ is defined as follows: $ $$$ f(u) = \begin{cases} \texttt{<empty string>}, & \text{if }u = 0; \\ f(l_u) + c_u + f(r_u) & \text{otherwise}, \end{cases}  $ $  where  $ + $  denotes the string concatenation operation.</p><p>This way, the string representation of the tree is  $ f(1) $ .</p><p>For each node, we can <span class="tex-font-style-it">duplicate</span> its label <span class="tex-font-style-bf">at most once</span>, that is, assign  $ c\_u $  with  $ c\_u + c\_u $ , but only if  $ u $  is the root of the tree, or if its parent also has its label duplicated.</p><p>You are given the tree and an integer  $ k $ . What is the lexicographically smallest string representation of the tree, if we can duplicate labels of at most  $ k $  nodes?</p><p>A string  $ a $  is lexicographically smaller than a string  $ b $  if and only if one of the following holds: </p><ul> <li>  $ a $  is a prefix of  $ b $ , but  $ a \\ne b $ ; </li><li> in the first position where  $ a $  and  $ b $  differ, the string  $ a $  has a letter that appears earlier in the alphabet than the corresponding letter in  $ b$$$.

## 说明/提示

The images below present the tree for the examples. The number in each node is the node number, while the subscripted letter is its label. To the right is the string representation of the tree, with each letter having the same color as the corresponding node.

Here is the tree for the first example. Here we duplicated the labels of nodes $ 1 $ and $ 3 $ . We should not duplicate the label of node $ 2 $ because it would give us the string "bbaaab", which is lexicographically greater than "baaaab".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/8e9bc3e39a0385947c6f1b7db86d59f03e67d645.png)In the second example, we can duplicate the labels of nodes $ 1 $ and $ 2 $ . Note that only duplicating the label of the root will produce a worse result than the initial string.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/dca73cc51ea6acbb902f1315cd4594d96b4d3160.png)In the third example, we should not duplicate any character at all. Even though we would want to duplicate the label of the node $ 3 $ , by duplicating it we must also duplicate the label of the node $ 2 $ , which produces a worse result.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1623E/967abfb10aaf17f05381c2a0e362eea9288d9011.png)There is no way to produce string "darkkcyan" from a tree with the initial string representation "darkcyan" :(.

## 样例 #1

### 输入

```
4 3
abab
2 3
0 0
0 4
0 0```

### 输出

```
baaaab```

## 样例 #2

### 输入

```
8 2
kadracyn
2 5
3 4
0 0
0 0
6 8
0 7
0 0
0 0```

### 输出

```
daarkkcyan```

## 样例 #3

### 输入

```
8 3
kdaracyn
2 5
0 3
0 4
0 0
6 8
0 7
0 0
0 0```

### 输出

```
darkcyan```

# 题解

## 作者：Tyyyyyy (赞：10)

# CF1623E

 _Note：赛场上想的正解没敢写...麻了。_
 
### 题意简述
给定一棵 $n$ 个节点的**二叉树**，根为 $1$ 号节点。每个节点上有一个字符 $c_i$。

定义这棵二叉树的**字符表示**是以它的中序遍历访问的顺序拼接得到的字符串。

形式化地，设 $f(u)$ 表示以 $u$ 为根的子树的字符表示，则：

$$f(u)=\begin{cases}\texttt{<empty string>}& \text{if }u = 0 \\ f(l_u) + c_u + f(r_u) & \text{otherwise} \end{cases}$$
  
现在，你可以复制一些节点上的字符（即将该节点上的字符 $c_u$ 变为字符串 $c_u+c_u$），规则如下：
  
- 每个节点最多被复制一次。
- 一个节点能够被复制，当且仅当它是根节点，或者它的父节点被复制。
- 最多复制 $k$ 个节点。

现在，请你给出在最多 $k$ 次复制后，该二叉树的字典序最小的字符表示。

$1\leq k\leq n\leq 2\times 10^5,0\leq l_i,r_i\leq n$。

### 题目分析
我们首先进行一次中序遍历，找到每个节点在中序遍历中所处的位置。

接下来，我们能知道每个节点被复制是否会让字典序更小。只需要对比它和在中序遍历中的下一个和它不同的字符的大小即可。
  
显然，我们会在能让字典序变小的节点中尽量选择靠前的，即左子树比右子树优先。同时，不难证明：
  
- 如果当前节点被复制不会使答案更优，则它的右子树一定不会被复制。
- 在左右子树都能使答案更优的前提下，优先复制左子树。

因此，我们可以执行一个 dfs 框架：
  
- 假设当前访问的节点为 $u$，复制该节点的代价为 $cost$。
- 若 $u=0$ 或 $cost>k$，返回。
- 访问当前节点的左儿子 $l_u$，同时将 $cost\gets cost+1$。
- 如果 $l_u$ 需要被复制，则 $u$ 需要被复制。
- 否则，在 $l_u$ 不需要被复制的情况下，如果 $u$ 被复制能让答案更优，则 $u$ 也需要被复制，且 $k\gets k-cost$。
- 如果当前节点需要被复制，访问当前节点的右儿子 $r_u$，并将 $cost\gets 1$。
  
这样，我们就找到了每个节点是否需要被复制。时间复杂度 $O(n)$。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,l[200010],r[200010],pos[200010];
char c[200010];
vector<int>seq;
void precalc(int u)
{
	if(l[u])precalc(l[u]);
	seq.push_back(u);
	if(r[u])precalc(r[u]);
}
bool good[200010],isDup[200010];
void dfs(int u,int cost)
{
	if(!u||cost>k)return;
	dfs(l[u],cost+1);
	if(isDup[l[u]])isDup[u]=1;
	else if(good[u])isDup[u]=1,k-=cost;
	if(isDup[u])dfs(r[u],1);
}
int main()
{
	scanf("%d%d",&n,&k);
	scanf("%s",c+1);
	for(int i=1;i<=n;i++)scanf("%d%d",&l[i],&r[i]);
	precalc(1);
	char lst=c[seq.back()];
	for(int i=n-2;i>=0;i--)
	{
		int u=seq[i],v=seq[i+1];
		if(c[u]!=c[v])lst=c[v];
		if(c[u]<lst)good[u]=1;
	}
	dfs(1,1);
	for(auto u:seq)
	{
		putchar(c[u]);
		if(isDup[u])putchar(c[u]);
	}
	return 0;
}
```

---

## 作者：Legitimity (赞：7)

来个不用动脑子的树剖维护做法


------------

按中序遍历将树推平得到字符串 $s$，从前向后遍历该字符串，设 $nex_i$ 表示满足 $s_i\neq s_j$ 且 $i<j$ 的最小位置 $j$。若 $s_i<s_{nex_i}$，则要尽量满足复制当前的节点，查询该节点到根的路径中有没复制的节点个数 $v$，若 $v\leq k$，则复制当前节点，并将到根路径上的节点全部标记为已复制：否则复制不优，直接跳到 $nex_i$ 继续操作。

但这样做会有个问题。如果 $i<j,s_{i}>s_{nex_i},s_j<s_{nex_j}$ 且 $i$ 是 $j$ 的祖先，按照上面操作会在复制 $j$ 时把 $i$ 复制，这样做则不优，所以当发现当前节点 $s_i>s_{nex_i}$ 时，要扫描 $i\leq k<nex_i$，若 $k$ 还没有被标记复制（若被标记复制，则有 $k1<i$ 的节点复制更优，满足字典序更小），则 ban 掉 $k$ 的子树（让 $k$ 的子树的节点以后扫描到时不能复制），然后再跳转。

以上操作可以用树剖维护，时间复杂度为 $O(n\log^2 n)$。



------------


代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define ll long long
#define ull unsigned ll
#define inf 0x3f3f3f3f
#define djq 1000000007
#define lowbit(x) (x&(-x))
const double alpha=0.73;
inline void file(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
char buf[1<<21],*p1=buf,*p2=buf;
inline int getc(){
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	rg int ret=0,f=0;char ch=getchar();
    while(!isdigit(ch)){if(ch==EOF)exit(0);if(ch=='-')f=1;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-48;ch=getchar();}
    return f?-ret:ret;
}
int n,k,son[200005][2];
char s[200005];
int as[200005];
int a[200005],id,nex[200005];
int dep[200005],fa[200005],hson[200005],siz[200005],dfn[200005],top[200005],tim;
struct solve{
	void dfs1(int x,int f){
		if(!x) return; 
		fa[x]=f; dep[x]=dep[f]+1; siz[x]=1;
		dfs1(son[x][0],x); siz[x]+=siz[son[x][0]];
		if(siz[son[x][0]]>siz[hson[x]]) hson[x]=son[x][0];
		a[++id]=x; as[id]=s[x]-'a'+1;
		dfs1(son[x][1],x); siz[x]+=siz[son[x][1]];
		if(siz[son[x][1]]>siz[hson[x]]) hson[x]=son[x][1];
	}
	void dfs2(int x,int topth){
		if(!x) return;
		top[x]=topth;
		dfn[x]=++tim;
		if(hson[x]) dfs2(hson[x],topth);
		for(rg int i=0;i<2;++i){
			const int y=son[x][i];
			if(y==fa[x]||y==hson[x]) continue;
			dfs2(y,y);
		}
	}
	struct node{
		int l,r,val;
		bool tag,ban;
	}t[200005<<3];
	inline void up(int x){ t[x].val=t[x<<1].val+t[x<<1|1].val; }
	inline void down(int x){
		if(t[x].tag){
			t[x<<1].val=t[x<<1|1].val=0;
			t[x<<1].tag=t[x<<1|1].tag=1;
			t[x].tag=0;
		}
	}
	void build(int x,int l,int r){
		t[x].l=l,t[x].r=r,t[x].tag=0,t[x].ban=0;
		if(l==r) return t[x].val=1,void();
		const int mid=l+r>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		up(x);
	}
	void modify1(int x,int sl,int sr){
		if(sl<=t[x].l&&sr>=t[x].r) return t[x].val=0,t[x].tag=1,void();
		const int mid=t[x].l+t[x].r>>1; down(x);
		if(sl<=mid) modify1(x<<1,sl,sr);
		if(sr>mid) modify1(x<<1|1,sl,sr);
		up(x);
	}
	void modify2(int x,int sl,int sr){
		if(sl<=t[x].l&&sr>=t[x].r) return t[x].ban=1,void();
		const int mid=t[x].l+t[x].r>>1; down(x);
		if(sl<=mid) modify2(x<<1,sl,sr);
		if(sr>mid) modify2(x<<1|1,sl,sr);
		up(x);
	}
	int query(int x,int sl,int sr){
		if(sl<=t[x].l&&sr>=t[x].r) return t[x].val;
		const int mid=t[x].l+t[x].r>>1; down(x);
		int ret=0;
		if(sl<=mid) ret+=query(x<<1,sl,sr);
		if(sr>mid) ret+=query(x<<1|1,sl,sr);
		return ret;
	}
	int ban(int x,int y){
		if(t[x].l==t[x].r) return t[x].ban;
		const int mid=t[x].l+t[x].r>>1; int ret=t[x].ban;
		if(y<=mid) ret=max(ret,ban(x<<1,y));
		else ret=max(ret,ban(x<<1|1,y));
		return ret;
	}
	void d1(int x){ while(x) modify1(1,dfn[top[x]],dfn[x]),x=fa[top[x]]; }
	void d2(int x){ modify2(1,dfn[x],dfn[x]+siz[x]-1); }
	int q(int x){
		int ret=0;
		while(x) ret+=query(1,dfn[top[x]],dfn[x]),x=fa[top[x]];
		return ret;
	}
}ww;
inline void work(){
	n=read(),k=read();
	scanf("%s",s+1);
	for(rg int i=1;i<=n;++i) son[i][0]=read(),son[i][1]=read();
	ww.dfs1(1,0),ww.dfs2(1,1),ww.build(1,1,n);
	int las=n+1;
	for(rg int i=n;i>=1;--i){
		if(as[i]!=as[i+1]) las=i+1;
		nex[i]=las;
	}//处理 nex。 
	for(rg int i=1;i<=n;){
		if(as[i]>as[nex[i]]){  //若复制不优 。 
			for(rg int j=i;j<nex[i];++j) 
				if(ww.query(1,dfn[a[j]],dfn[a[j]])) 
					ww.d2(a[j]);  //ban 掉子树。 
			i=nex[i]; continue;
		}
		if(ww.ban(1,dfn[a[i]])==1){  //若被祖先 ban 掉，则不能复制。 
			++i; continue;
		}
		const int nv=ww.q(a[i]);
		if(nv<=k){   //复制。 
			k-=nv;
			ww.d1(a[i]);
		}
		++i;
	}
	for(rg int i=1;i<=n;++i){
		printf("%c",as[i]-1+'a');
		if(ww.query(1,dfn[a[i]],dfn[a[i]])==0) printf("%c",as[i]-1+'a');
	}//输出。 
}
signed main(){
    //file();
	work();
	return 0;
}
/*
*/
```


---

## 作者：Richard_Whr (赞：1)

无需动脑线段树做法。

直接在中序遍历上从前往后扫。

如果一个点后面一个比他大，那肯定能复制就复制。

直接在树上暴力把到根链还没覆盖过的覆盖了就行，且实时维护所有点到根链还没被覆盖过的长度。

反之，如果这个点之前已经被覆盖了，说明他为之前字典序做出了牺牲，不管了。否则，他一定不能被复制，直接把他的所有儿子复制的代价变成 $+\infty$ 就行了。

注意如果有一个区间的颜色相同，也可以视为一个点，只不过每次需要找区间代价最小值。

上述操作形如：区间加，区间求最小值及位置。

可以用线段树解决，复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls u*2
#define rs u*2+1 
using namespace std;
const int N=2e5+10,Inf=1e9;
typedef pair<int,int> PII;
int L[N],R[N];
int Ls[N],Rs[N],rk[N],seq[N],fa[N],ts;
int dep[N];
bool st[N];
int n,m;
char s[N];
struct Tree
{
	int l,r;
	PII minv;
	int tag;
}tr[N*4];

void Dfs(int u,int d)
{
	dep[u]=d;
	if(Ls[u]) Dfs(Ls[u],d+1),fa[Ls[u]]=u;
	rk[u]=++ts,seq[ts]=u,L[u]=R[u]=ts;
	if(Rs[u]) Dfs(Rs[u],d+1),fa[Rs[u]]=u; 
	if(Ls[u]) L[u]=min(L[u],L[Ls[u]]),R[u]=max(R[u],R[Ls[u]]);
	if(Rs[u]) L[u]=min(L[u],L[Rs[u]]),R[u]=max(R[u],R[Rs[u]]);
}


void Add(int u,int c)
{
	tr[u].minv.first+=c,tr[u].tag+=c;
}

void pushup(int u)
{
	tr[u].minv=min(tr[ls].minv,tr[rs].minv);
}

void pushdown(int u)
{
	if(!tr[u].tag) return;
	Add(ls,tr[u].tag),Add(rs,tr[u].tag);
	tr[u].tag=0;
}

void build(int u,int l,int r)
{
	tr[u].l=l,tr[u].r=r,tr[u].tag=0;
	if(l==r) tr[u].minv={dep[seq[l]],seq[l]};
	else
	{
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(u);
	}
}

void modify(int u,int l,int r,int c)
{
	if(tr[u].l>=l && tr[u].r<=r) Add(u,c);
	else
	{
		pushdown(u);
		int mid=tr[u].l+tr[u].r>>1;
		if(l<=mid) modify(ls,l,r,c);
		if(r>mid) modify(rs,l,r,c);
		pushup(u);
	}
}

auto qmin(int u,int l,int r)
{
	if(tr[u].l>=l && tr[u].r<=r) return tr[u].minv;
	else
	{
		pushdown(u);
		int mid=tr[u].l+tr[u].r>>1;
		if(r<=mid) return qmin(ls,l,r);
		if(l>mid) return qmin(rs,l,r);
		return min(qmin(ls,l,r),qmin(rs,l,r));
	}
}

void Mark(int u)
{
	while(!st[u] && u)
	{
		st[u]=true;
		modify(1,L[u],R[u],-1);
		modify(1,rk[u],rk[u],Inf);
		u=fa[u];
	}
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m;
	cin>>(s+1);
	
	for(int i=1;i<=n;i++) cin>>Ls[i]>>Rs[i];
	
	Dfs(1,1);
	
	build(1,1,n);
	
	for(int l=1,r;l<=n;l=r+1)
	{
		r=l;
		while(r+1<=n && s[seq[l]]==s[seq[r+1]]) r++;
		if(r==n) continue;
		if(s[seq[r+1]]<s[seq[l]])//绝对不能改 
		{
			for(int i=l;i<=r;i++) 
			{
				int u=seq[i];
				if(st[u]) continue;
				modify(1,L[u],R[u],Inf);
			}
		}
		else//尝试着改 
		{
			auto it=qmin(1,l,r);
			while(it.first<=m)
			{
				Mark(it.second);
				m-=it.first;
				it=qmin(1,l,r);
			}
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		int u=seq[i];
		if(st[u]) cout<<s[u]<<s[u];
		else cout<<s[u];
	}
	cout<<"\n";
	
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

~~按照题意模拟即可。~~

数据结构写不动了，来写点 `*2500` 的唐题。

在中序遍历的过程中，确定每个数是否复制。

这个点复制是值得的，当且仅当**在中序遍历下他后面第一个和它不同的字符比他小**（如果没有，默认比他大）。同样的，要把他所有未复制的祖先节点变为复制（这一部分用倍增很好维护）。

注意如果一个点复制是不值得的，那么**我们将不确定它右子树中任何一个节点是否复制**。因为它的右子树每个节点都比他更靠后，如果要复制它们就必须复制当前节点，会使得字典序变大。

复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,k,lson[MAXN],rson[MAXN],nxt[MAXN],flg[MAXN],dep[MAXN],fa[MAXN][20];
vector<int> mid_ord;
string S,T="&";
void get_mrd(int u) {
	ffor(i,1,19) fa[u][i]=fa[fa[u][i-1]][i-1];
	if(lson[u]) fa[lson[u]][0]=u,dep[lson[u]]=dep[u]+1,get_mrd(lson[u]);
	mid_ord.push_back(u),T+=S[u];
	if(rson[u]) fa[rson[u]][0]=u,dep[rson[u]]=dep[u]+1,get_mrd(rson[u]);
	return ;
}
int find(int u) {
	//找到 u 第一个被标记的祖先 
	roff(i,19,0) if(fa[u][i]&&!flg[fa[u][i]]) u=fa[u][i];
	return fa[u][0];
}
void solve(int u) {
	if(lson[u]) solve(lson[u]);
	if(!flg[u]&&nxt[u]) {
		int anc=find(u);
		if(dep[u]-dep[anc]<=k) {
			int tpos=u;
			while(tpos!=anc) k--,flg[tpos]=1,tpos=fa[tpos][0];
		}
	}
	if(flg[u]) if(rson[u]) solve(rson[u]);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k>>S,S="&"+S,dep[1]=1;
	ffor(i,1,n) cin>>lson[i]>>rson[i];
	get_mrd(1);
	nxt[mid_ord[n-1]]=0;
	roff(i,n-2,0) if(S[mid_ord[i]]==S[mid_ord[i+1]]) nxt[mid_ord[i]]=nxt[mid_ord[i+1]];
	else nxt[mid_ord[i]]=(S[mid_ord[i]]<S[mid_ord[i+1]]);
	solve(1);
	ffor(i,1,n) if(flg[mid_ord[i-1]]) cout<<S[mid_ord[i-1]]<<S[mid_ord[i-1]];
	else cout<<S[mid_ord[i-1]];
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

很喵喵的喵喵题

## 题目简述

- 一颗字符串二叉树，有 $m$ 次复制机会（可以不全使用）每次可以给节点 $u$ 上的字符 $c$ 变成 $cc$。当 $u$ 是根节点或者其父亲也复制了才可以使用复制操作。
- 求中序遍历得到字典序最小的字符串。
- $n,m\leq2\times 10^5$。

## 解题思路

我们用 $val_i$ 记录复制 $p$ 节点会不会让得到的字符串字典序变小。

显然，一个节点 $u$ 的左儿子 $l_u$ 复制以后字典序会更小这时候 $u$ 就必须复制，这是因为 $u$ 的左儿子在整个字符串中占权更大。

注意左儿子 $l_u$ 复制以后字典序会更小这里不一定是 $val_{l_u}$ 因为可能 $l_u$ 的左儿子复制后更小，那么 $l_u$ 也是值得复制的。

如果 $u$ 值得复制，那么我们再遍历 $r_u$，否则 $r_u$ 占权比 $u$ 小，所以不可能让 $r_u$ 也复制。

这样就完成力思路。

## 参考代码

```cpp
#include<iostream>
using namespace std;
const int MAXN=2e5+5;
char c[MAXN],d[MAXN<<1];int res=0,tmp=0; 
string s;
bool val[MAXN],cho[MAXN];//单个是否值得复制；是否选择复制
int n,m;
int l[MAXN],r[MAXN];
void dfs1(int p){
	if(!p) return;
	dfs1(l[p]);
	c[++res]=s[p];
	dfs1(r[p]);
}//得到中序遍历字符串 c
void dfs2(int p,int k){//k:选择消耗的操作数
	if(!p) return;
	dfs2(l[p],k+1);//l[p] 占比比 p 大，先遍历 l[p]
	++res;
	d[++tmp]=s[p];
	if(cho[l[p]]) cho[p]=true,d[++tmp]=s[p],dfs2(r[p],1);//l[p] 选择 p 必须选
	else if(val[res]&&k<=m) cho[p]=true,d[++tmp]=s[p],m-=k,dfs2(r[p],1);//左儿子不选但自己值得就选
	else dfs2(r[p],1e9);//不可能选 r[p]，但是更新 d 和 res
}
int main(){
	cin>>n>>m>>s;
	s=" "+s;
	for(int i=1;i<=n;i++)
		cin>>l[i]>>r[i];
	dfs1(1);
	for(int i=n-1;i>=1;i--)
		val[i]=(c[i]==c[i+1])?val[i+1]:c[i]<c[i+1];
	res=0;dfs2(1,1);
	for(int i=1;i<=tmp;i++)
		cout<<d[i];
	return 0; 
} 
```


---

## 作者：PosVII (赞：0)

[CF1623系列](https://www.luogu.com.cn/blog/271260/cf1623-bi-sai-ji-lu)

差几分钟就过了。发现自己的方法和最后一篇题解出奇的一致，所以就当个拓展吧。

显然，这个字符串就是树的中序遍历。因此如果左子树翻倍会使字典序更小的话就一定要翻倍。

因此先遍历一遍这棵树找到原来的字符串，然后再对每一位处理其翻倍后是否能减小字符串（即去掉这个字符串后面与它相同的字符后的第一个字符是否大于它本身）。

然后再中序遍历一遍这棵树，对于每个根节点，它的左子树如果被取了就意味着它也被取了，否则看看自己是否可以翻倍，如果可以就减去自己到上一个被翻倍过的祖先的深度，如果自己被翻倍了再看右子树，否则直接退出（根在右子树前面，但取右子树一点要先取根节点）。

最后遍历一遍树输出即可。

时间复杂度 $\mathbin{\mathrm{O(n)}}$。

[Code](https://codeforces.com/contest/1623/submission/146893359)

---

## 作者：IdnadRev (赞：0)

赛时做法和正解很接近了，可惜细节没编完善。

## 题意

给定一个二叉树，每个结点有一个字母，你可以选择给一个结点的字母复制一份或不复制，但复制的前提是结点时根或者父亲已被复制，复制的结点数不能超过 $k$，求最小化先序遍历拼接出的字符串的字典序。

$1\leqslant k\leqslant n\leqslant 2\times 10^5$

## 分析

很容易想到 $O(n^2)$ 的暴力贪心，这里不赘述了。

我们先预处理一个 $ok_i$ 表示单独地将 $i$ 翻倍后是否能减小字符串的字典序，把中序遍历搜出来就好了。

然后就是一个比较有细节的贪心。

我们考虑处理出来每个点翻倍的代价（即需要翻倍的点数）$cst_x$，然后：

- 令 $cst_{lson}=cst_x+1$，遍历 $lson$；
- 若 $lson$ 被翻倍，则翻倍当前点；若 $lson$ 未被翻倍，但是 $ok_x$ 为真，那么花费代价翻倍当前点；
- 若当前点被翻倍，则令 $cst_{rson}=1$，遍历 $rson$。

不难证明上述贪心的正确性，时间复杂度 $O(n)$。

注意不需要遍历 $cst_x>k$ 的 $x$。

## 代码
```
#include<stdio.h>
#include<iostream>
using namespace std;
const int maxn=200005;
int n,k,ss,dfns;
int l[maxn],r[maxn],cst[maxn],vis[maxn],st[maxn],ok[maxn];
string s;
void dfs(int x) {
	if(x==0)
		return ;
	dfs(l[x]),st[++ss]=x,dfs(r[x]);
}
void down(int x) {
	if(x==0)
		return ;
	if(cst[x]>k)
		return ;
	cst[l[x]]=cst[x]+1,down(l[x]);
	if(vis[l[x]])
		vis[x]=1;
	else if(ok[x])
		k-=cst[x],vis[x]=1;
	if(vis[x])
		cst[r[x]]=1,down(r[x]);
}
int main() {
	scanf("%d%d",&n,&k),cin>>s,s=" "+s;
	for(int i=1; i<=n; i++)
		scanf("%d%d",&l[i],&r[i]);
	dfs(1);
	for(int i=n-1; i>=1; i--) {
		ok[st[i]]=ok[st[i+1]];
		if(s[st[i]]>s[st[i+1]])
			ok[st[i]]=0;
		if(s[st[i]]<s[st[i+1]])
			ok[st[i]]=1;
	}
	cst[1]=1,down(1);
	for(int i=1; i<=n; i++) {
		putchar(s[st[i]]);
		if(vis[st[i]])
			putchar(s[st[i]]);
	}
	return 0;
}
```

---

