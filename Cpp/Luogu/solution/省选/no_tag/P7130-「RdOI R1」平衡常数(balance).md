# 「RdOI R1」平衡常数(balance)

## 题目描述

给定一棵以 $1$ 为根的点带权有根树 $G=(V,E)$，第 $i$ 个节点的权值记为 
 $w_i$，以 $i$ 为根的子树的点集记为 $V_i$，求一个点集 $V'\subseteq V$，满足以下条件：

- $\forall i$，都有 $|V_i \cap V'| \le \lfloor \frac{|V_i|}{2} \rfloor$

- 最大化 $\sum _{i \in V'} w_i$

输出 $\sum _{i\in V'} w_i$ 即可，也就是选取的点的权值和。

## 说明/提示

【数据范围】

| 测试点编号 | $n\leq$ | $w_i\leq$ | 特殊性质 |
| - | - | - | - |
| $1\sim2$ | $10$ | $10^3$ | |
| $3\sim 5$ | $2 \times 10^3$ | $10^3$ | |
| $6\sim12$ | $10^5$ | $10^3$ | |
| $13\sim16$ | $5 \times 10^5$ | $10^9$ | $v=u+1$ |
| $17\sim25$ | $5 \times 10^5$ | $10^9$ | |

对于 $100\%$ 的数据，$1 \leq n \leq 5 \times 10^5$，$0 < w_i \leq 10^9$，$1 \leq u,v \leq n$。

---

【说明/提示】

- Idea From : LCuter

---

【文件读入读出】**（模拟，提交代码时不需使用）**

- 文件名：`balance.cpp`
- 读入文件名：`balance.in`
- 读出文件名：`balance.out`

## 样例 #1

### 输入

```
3
1 2 3
1 2
1 3```

### 输出

```
1```

# 题解

## 作者：ni_ju_ge (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7130)
## 思路
考虑当前已做完 $x$ 子树内的选择，到达 $x$ 时怎么操作。下面将满足一条件称为“平衡”。

发现删除原本平衡的子树内任意一个选取的点，不会破坏平衡。那么为了最大化权值和，若选取 $x$ 会破坏平衡，可以贪心地删去选取点中的最小点，再将 $x$ 选上以增大权值和（如果这样会使权值和变小，则不进行此操作）。

可以使用小根堆记录最小的权值，到 $x$ 时合并子节点的小根堆再进行操作。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int x,y,n;
long long ans,a[N];
struct node {
	int siz,qu;
	vector<int> ch;
} tr[N];
vector<int> ed[N];
struct xgd {
	int l,r;
	long long dat;
	int key;
} v[N];
int root[N],cnt;
int make(int val) {
	v[++cnt].dat=val;
	v[cnt].key=rand();
	return cnt;
}
int merge(int r1,int r2) {//堆合并
	if(!r1||!r2) return r1+r2;
	if(v[r1].dat>=v[r2].dat) {
		if(v[r1].key<=v[r2].key) v[r2].l=merge(r1,v[r2].l);
		else v[r2].r=merge(r1,v[r2].r);
		return r2;
	} else {
		if(v[r2].key<=v[r1].key) v[r1].l=merge(v[r1].l,r2);
		else v[r1].r=merge(v[r1].r,r2);
		return r1;
	}
}
void take(int loc,int val) {
	root[loc]=merge(root[loc],make(val));
}
void del(int loc) {
	root[loc]=merge(v[root[loc]].l,v[root[loc]].r);
}
void dfs1(int pos) {//建树
	tr[pos].siz=1;
	for(int i=0;i<ed[pos].size();i++) {
		int nxt=ed[pos][i];
		if(!tr[nxt].siz) {
			dfs1(nxt);
			tr[pos].ch.push_back(nxt);
			tr[pos].siz+=tr[nxt].siz;
		}
	}
}
void dfs2(int pos) {//贪心求解
	for(int i=0;i<tr[pos].ch.size();i++) {
		int nxt=tr[pos].ch[i];
		dfs2(nxt);
		tr[pos].qu+=tr[nxt].qu;
		root[pos]=merge(root[pos],root[nxt]);
	}
	if(tr[pos].siz!=1) {//注意叶子结点一定不能选
		if(tr[pos].qu>=tr[pos].siz/2&&a[pos]>v[root[pos]].dat) {
			del(pos);//删去最小值
			take(pos,a[pos]);
		}
		if(tr[pos].qu<tr[pos].siz/2) {
			take(pos,a[pos]);
			tr[pos].qu++;
		}
	}
}
void dfs3(int pos) {//计算权值和
	if(!pos) return;
	ans+=v[pos].dat;
	dfs3(v[pos].l);
	dfs3(v[pos].r);
}
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++) {
		cin>>x>>y;
		ed[x].push_back(y);
		ed[y].push_back(x);
	}
	dfs1(1);
	dfs2(1);
	dfs3(root[1]);
	cout<<ans;
}
```

---

## 作者：SSerxhs (赞：1)

链修改、链查询，可以用 LCT 做到 $O(n\log n)$。

由于树静态，可以使用全局平衡二叉树实现。

具体地，每次修改 $x$ 和 $x$ 的左子树，然后在祖先中找到第一个中序遍历在 $x$ 前面的点 $f$ 并令 $x=f$ 即可。这样操作相当于是每次在重链的二叉树上找到中序遍历比它小的所有节点。

查询同理。

官方题解是错的且数据过水，本题并没有保证 $u$ 是 $v$ 的父亲。

```cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pa;
const int N=1e6+2,M=1e6+2;
ll ans;
pa w[N];
int c[N][2],f[N],fa[N],v[N],s[N],lz[N],lj[M],nxt[M],siz[N],hc[N],fir[N],st[N];
int a[N],top[N];
int n,i,x,y,z,bs,tp,rt;
inline void read(register int &x)
{
	register int c=getchar();
	while (c<48||c>57) c=getchar();
	x=c^48;c=getchar();
	while (c>=48&&c<=57) x=x*10+(c^48),c=getchar();
}
inline void add()
{
	lj[++bs]=y;nxt[bs]=fir[x];fir[x]=bs;
	lj[++bs]=x;nxt[bs]=fir[y];fir[y]=bs;
}
inline void pushup(register int &x)
{
	s[x]=min(v[x],min(s[c[x][0]],s[c[x][1]]));
}
inline void pushdown(register int &x)
{
	if (lz[x]<0)
	{
		register int cc=c[x][0];
		if (cc)
		{
			lz[cc]+=lz[x];s[cc]+=lz[x];v[cc]+=lz[x];
		}
		cc=c[x][1];
		if (cc)
		{
			v[cc]+=lz[x];lz[cc]+=lz[x];s[cc]+=lz[x];
		}lz[x]=0;
		return;
	}
}
inline bool nroot(register int &x) {return c[f[x]][0]==x||c[f[x]][1]==x;}
inline bool cmp(register pa &o,register pa &p) {return o>p;}
void dfs1(int x)
{
	siz[x]=1;
	for (int i=fir[x];i;i=nxt[i]) if (lj[i]!=fa[x])
	{
		fa[lj[i]]=x;dfs1(lj[i]);siz[x]+=siz[lj[i]];
		if (siz[hc[x]]<siz[lj[i]]) hc[x]=lj[i];
	}
}
int build(int l,int r)
{
	if (l>r) return 0;
	if (l==r)
	{
		l=st[l];s[l]=v[l]=siz[l]>>1;
		return l;
	}
	int x=lower_bound(a+l,a+r+1,a[l]+a[r]>>1)-a,y=st[x];
	c[y][0]=build(l,x-1);
	c[y][1]=build(x+1,r);
	v[y]=siz[y]>>1;
	if (c[y][0]) f[c[y][0]]=y;
	if (c[y][1]) f[c[y][1]]=y;
	pushup(y);
	return y;
}
void dfs2(int x)
{
	if (!hc[x]) return;
	int i;
	top[hc[x]]=top[x];
	if (top[x]==x)
	{
		st[tp=1]=x;
		for (i=hc[x];i;i=hc[i]) st[++tp]=i;
		for (i=1;i<=tp;i++) a[i]=siz[st[i]]-siz[hc[st[i]]]+a[i-1];
		f[build(1,tp)]=fa[x];
	}
	dfs2(hc[x]);
	for (i=fir[x];i;i=nxt[i]) if (lj[i]!=fa[x]&&lj[i]!=hc[x]) dfs2(top[lj[i]]=lj[i]);
}
void mdf(register int x)
{
	register int y=x;
	st[tp=1]=x;
	while (y=f[y]) st[++tp]=y;y=x;
	while (tp) pushdown(st[tp--]);
	while (x)
	{
		--v[x];--lz[c[x][0]];--v[c[x][0]];--s[c[x][0]];
		while (c[f[x]][0]==x) x=f[x];x=f[x];
	}
	pushup(y);
	while (y=f[y]) pushup(y);
}
int ask(register int x)
{
	register int y=x;
	st[tp=1]=x;
	while (y=f[y]) st[++tp]=y;
	while (tp) pushdown(st[tp--]);
	register int r=v[x];
	while (x)
	{
		r=min(r,min(v[x],s[c[x][0]]));
		while (c[f[x]][0]==x) x=f[x];x=f[x];
	}
	return r;
}
signed main()
{
	read(n);s[0]=1e9;
	for (i=1;i<=n;i++) read(w[w[i].second=i].first);
	for (i=1;i<n;i++) read(x),read(y),add();
	sort(w+1,w+n+1,cmp);dfs1(1);dfs2(top[1]=1);rt=1;while (f[rt]) rt=f[rt];
	for (i=1;i<=n&&v[rt];i++) if (ask(w[i].second)) mdf(w[i].second),ans+=w[i].first;
	printf("%lld",ans);
}
```

---

## 作者：serverkiller (赞：0)

这里给出一种不知道比出题人的做法好写到哪里去的做法

考虑我们已经结束了子树中的抉择 来到了某个节点$u$的处

那么我们考虑这个节点是否选取 只需要去掉子树中的一个最小权值点 然后把这个点加入我们的答案点集中去

不难发现这样不会影响子树中的抉择情况 我们便得到了一个可撤销贪心

我们需要一个数据结构来维护这个东西 参照dsu-on-tree的想法 我们直接继承重儿子 然后暴力合并轻儿子

复杂度是$O(n\log n)$ 常数和代码复杂度都显著小于出题人的做法

顺便吐槽一句数据有点水 我赛时拿set启发式合并+两只log的垃圾做法通过数据分治过去了

---

