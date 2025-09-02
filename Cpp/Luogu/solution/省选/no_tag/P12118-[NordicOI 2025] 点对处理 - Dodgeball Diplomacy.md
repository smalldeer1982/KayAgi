# [NordicOI 2025] 点对处理 / Dodgeball Diplomacy

## 题目背景


Python / Java（很）可能无法通过本题。不建议不使用 C/C++。

## 题目描述

**这是一道交互题**。我们利用交互来让你强制在线回答询问。

有 $N$ 个点，编号从 $1$ 到 $N$，你需要解决如下 $Q$ 个询问：

- $\texttt{a u v p}$，在 $u$ 和 $v$ 之间添加长度为 $p$ 的无向边。

- $\texttt{r}$，删除当前图中最长的无向边。

- $\texttt{d}$，把当前图中连通块两两配对（如果连通块数量为奇数，那就选择一个连通块和大小为 $0$ 的连通块配对），记为 $(A_i,B_i)$。

	设有 $k$ 个连通块，令连通块 $A$ 的点数为 $|A|$，最小化 $\displaystyle \sum_{1\le i\le k}||A_i|-|B_i||$。只需要输出最小化后的这个值。

## 说明/提示

【样例解释】

注意以下解释只按顺序解释类型为 $\texttt{d}$ 的查询。

- 对于样例 $1$，第一次查询，连通块为 $(1,2,3)$，答案为 $3$，第二次查询，连通块为 $(1,2)$ 和 $(3)$，答案为 $1$。

- 对于样例 $2$，在第一次查询，有一个大小为 $4$ 的连通块和两个大小为 $1$ 的连通块，总不公平分数为 $4$；在第二次查询中，有两个大小为 $2$ 的连通块和两个大小为 $1$ 的连通块，答案为 $0$；在第三次查询，有三个大小为 $2$ 的联盟，答案为 $2$。


【数据规模与约定】

对于所有数据，满足：

$1 \leq N \leq 100000,1 \leq Q \leq 500000,1 \leq p \leq 10^{9},1 \leq u \leq N,1 \leq v \leq N$。 

对于类型 $\texttt{a}$ 的查询，$u \neq v$，添加无向边时，$u$ 和 $v$ 之间不存在无向边，且所有 $p$ 均唯一。

详细子任务附加限制及分值如下表所示：


|子任务编号  | 分值 | 附加限制 |
| :-----------: |:-----------: | :-----------: |
|$1$  | $9$ | $N \le 10,Q \le 20$ |
| $2$ | $10$ | $N \le 2000,Q\le 4000$ |
|$3$  | $6$ | 类型 $\texttt{d}$ 的查询不超过 $10$ 次 |
| $4$ | $17$ | 类型 $\texttt{a}$ 的查询，满足 $u+1=v$  |
| $5$ | $14$ | 满足随着边的建立，$p$ 递增 |
| $6$ | $26$ | 满足随着边的建立，$p$ 递减  |
| $7$ | $18$ | 无附加限制 |


## 样例 #1

### 输入

```
3 5
a 1 2 1
a 2 3 2
d
r
d
```

### 输出

```
3
1
```

## 样例 #2

### 输入

```
6 10
a 2 3 10
a 1 2 5
a 3 4 8
d
r
d
a 4 5 1
a 3 6 7
r
d
```

### 输出

```
4
0
2
```

# 题解

## 作者：Purslane (赞：1)

# Solution

假设你知道了所有连通块的大小 $s_i$，怎么计算答案。

容易发现，将 $s$ 从大到小排序，那么 $\sum_{i} (-1)^{i-1} s_i$ 就是答案。

唉所以你只需要动态维护 $s$。而显然任意一次修改只会对 $O(1)$ 个 $s$ 产生影响，所以我们只需要把修改做出来就行了。

这是动态图连通性问题，很难（注意不是不可以）在线的去做。

但是删的边是有特点的！考虑维护每个时刻的最小生成树。

如果一个点不在最小生成树上，说明存在一个一组边，他们的连通性可以替代这条边，但是权值都更小。因此这条边永远不会对连通性产生影响，直接删掉就好了。

而动态维护最小生成树是可做的，直接上 LCT 即可。

复杂度均摊单 log。只要会写 LCT 就不难！

但是我不会写 LCT，调到了夜里一点。 /fn

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e6+10;
int n,q;
namespace LCT {
	struct Node {
		int s[2],val,fa,flp,sze,lsze;
		pair<int,int> mx;	
	}t[MAXN];
	void sswap(int u) {return t[u].flp^=1,swap(t[u].s[0],t[u].s[1]),void();}
	void push_down(int u) {if(t[u].flp) sswap(t[u].s[0]),sswap(t[u].s[1]);return t[u].flp=0,void();}
	void push_up(int u) {
		t[u].mx={t[u].val,u},t[u].sze=(u<=n)+t[u].lsze;
		if(t[u].s[0]) t[u].mx=max(t[u].mx,t[t[u].s[0]].mx),t[u].sze+=t[t[u].s[0]].sze;
		if(t[u].s[1]) t[u].mx=max(t[u].mx,t[t[u].s[1]].mx),t[u].sze+=t[t[u].s[1]].sze;
		return ;
	}
	int is_root(int u) {return u!=t[t[u].fa].s[0]&&u!=t[t[u].fa].s[1];}
	int get(int u) {return u==t[t[u].fa].s[1];}
	void update(int u) {if(!is_root(u)) update(t[u].fa);return push_down(u),void();}
	void rotate(int u) {
		int fa=t[u].fa,s=get(u),op=get(fa);
		if(!is_root(fa)) t[t[fa].fa].s[op]=u;t[u].fa=t[fa].fa;
		t[t[u].s[s^1]].fa=fa,t[fa].fa=u,t[fa].s[s]=t[u].s[s^1],t[u].s[s^1]=fa;
		return push_up(fa),push_up(u),void();
	}
	void splay(int u) {update(u); for(int f=t[u].fa;f=t[u].fa,!is_root(u);rotate(u)) if(!is_root(f)) rotate(get(f)==get(u)?f:u);return ;}
	int access(int u) {int lst=0; while(u) splay(u),t[u].lsze-=t[lst].sze,t[u].lsze+=t[t[u].s[1]].sze,t[u].s[1]=lst,push_up(u),lst=u,u=t[u].fa;return lst;}
	int get_root(int u) {int rt=access(u);while(t[rt].s[0]) push_down(rt),rt=t[rt].s[0];return splay(rt),rt;}
	void make_root(int u) {return sswap(access(u)),void();}
	void link(int u,int v) {return make_root(v),splay(v),access(u),splay(u),assert(t[v].s[0]==0),t[v].fa=u,t[u].lsze+=t[v].sze,push_up(u),void();}
	int split(int u,int v) {return make_root(u),access(v);}
	void cut(int u,int v) {return make_root(u),access(v),splay(u),t[u].sze-=t[v].sze,t[u].s[1]=t[v].fa=0,push_up(u),void();}
	pair<int,int> find_mx(int u,int v) {return make_root(u),t[access(v)].mx;}
}
int len[MAXN],u[MAXN],v[MAXN],vis[MAXN];
mt19937 myrand(time(NULL));
priority_queue<pair<int,int>> qq;
namespace FHQ {
	struct Node {int sze,ls,rs,key,val,ans;}t[MAXN];
	void push_up(int u) {
		t[u].sze=t[t[u].ls].sze+t[t[u].rs].sze+1;
		t[u].ans=t[t[u].rs].ans+(t[u].val-t[t[u].ls].ans)*(1-2*(t[t[u].rs].sze&1));
		return ;
	}
	void split(int u,int v,int &p,int &q) {
		if(!u) return p=q=0,void();
		if(t[u].val>=v) return q=u,split(t[u].ls,v,p,t[u].ls),push_up(u),void();
		return p=u,split(t[u].rs,v,t[u].rs,q),push_up(u),void();
	}
	int merge(int u,int v) {
		if(!u||!v) return u|v;
		if(t[u].key<=t[v].key) return t[u].rs=merge(t[u].rs,v),push_up(u),u;
		return t[v].ls=merge(u,t[v].ls),push_up(v),v;	
	}
	queue<int> bin;
	int tot,rt;
	int get_node(int v) {int ans=0;if(!bin.empty()) ans=bin.front(),bin.pop();else ans=++tot;return t[ans]={1,0,0,myrand(),v,v},ans;}
	void del(int v) {int A,B,C;split(rt,v,A,B),split(B,v+1,B,C);return bin.push(B),rt=merge(merge(A,t[B].ls),merge(t[B].rs,C)),void();}
	void ins(int v) {int A,B;split(rt,v,A,B);return rt=merge(merge(A,get_node(v)),B),void();}
	int gans(void) {return t[rt].ans;}
};
int main() {
	scanf("%d %d",&n,&q);
	ffor(i,1,n) LCT::t[i].val=-1,LCT::t[i].sze=1,LCT::t[i].mx={-1,i};
	ffor(i,1,n) FHQ::ins(1);
	int tot=n;
	ffor(i,1,q) {
		char op;
		cin>>op;
		if(op=='a') {
			++tot;
			scanf("%d %d %d",&u[tot],&v[tot],&len[tot]);
			LCT::t[tot].val=len[tot],LCT::t[tot].mx={len[tot],tot};
			int id1=LCT::get_root(u[tot]),id2=LCT::get_root(v[tot]);
			if(id1!=id2) vis[tot]=1,FHQ::del(LCT::t[id1].sze),FHQ::del(LCT::t[id2].sze),FHQ::ins(LCT::t[id1].sze+LCT::t[id2].sze),LCT::link(u[tot],tot),LCT::link(v[tot],tot);
			else {
				auto pr=LCT::find_mx(u[tot],v[tot]);
				if(pr.first>len[tot]) {
					int del=pr.second;
					vis[del]=0,vis[tot]=1;
					LCT::cut(del,u[del]),LCT::cut(del,v[del]);
					LCT::link(u[tot],tot),LCT::link(v[tot],tot);
				}
			}
			qq.push({len[tot],tot});
		}
		else if(op=='r') {
			auto pr=qq.top(); qq.pop();
			if(vis[pr.second]) {
				int del=pr.second,id=LCT::get_root(del);
				FHQ::del(LCT::t[id].sze);
				LCT::cut(del,u[del]),LCT::cut(del,v[del]);
				int id1=LCT::get_root(u[del]),id2=LCT::get_root(v[del]);
				FHQ::ins(LCT::t[id1].sze),FHQ::ins(LCT::t[id2].sze);
			}
		}
		else {
			printf("%d\n",FHQ::gans());
			fflush(stdout);	
		}
	}
	return 0;
}
```

怎么跑的这么慢啊，难过了。

---

## 作者：gdf_yhm (赞：1)

[P12118](https://www.luogu.com.cn/problem/P12118)

会了 $O(q\sqrt n\log n)$ 后以为过不了就去晚自习了！不过不同的手法还是有巨大差别的。

### 思路

强制在线。删边分裂是最大的问题，考虑根号重构。

最开始想的是按时间分块，每 $B$ 个操作一块。每进入一块之前重构整个图。重构时，并查集加入部分之前的边，但不加入之前的边中前 $B$ 大的。加入删除时，不修改并查集，这样就算删边也删不到在图中的边。询问时，加入剩下的边，查询，再撤销，需要可撤销并查集。常数有点爆炸，口胡完就下播了。

后来又想到更好的重构方式。重构时，按边从小到大排序加入并查集。加入时，把新边加入一个 set 中，不修改并查集。删除时，要么删 set 中一个元素，要么撤销最后一次并查集加边。当 set 中元素个数 $\ge B$ 时，把边重新排序，重构，至多 $\frac{q}{B}$ 次。

至于处理答案，即把连通块大小排序后两两配对，在并查集操作时修改每个并查集大小的数量。一开始想用权值线段树维护区间的 $(val,num)$，被卡常了。注意到只有 $O(\sqrt n)$ 种本质不同的 $siz$，直接维护是哪些数即可。

复杂度 $O(q\log n+q(B\log n+\sqrt n\log n)+\frac{q}{B}n\log n)$。

### code

```cpp
int n,q;
int t[maxn],id[maxn],pos[maxn],idx,tmp[maxn];
void upd(int p,int w){
	t[p]+=w;
	if(t[p]==w)id[++idx]=p,pos[p]=idx;
	if(t[p]==0)pos[id[idx]]=pos[p],id[pos[p]]=id[idx],idx--;
}
void clr(){
	while(idx)t[id[idx]]=0,idx--;
}
int calc(){
	for(int i=1;i<=idx;i++)tmp[i]=id[i];
	sort(tmp+1,tmp+idx+1);
	int ans=0;
	for(int i=idx,op=0;i;i--)if(t[tmp[i]]&1)ans+=tmp[i]*(!op?1:-1),op^=1;
	return ans;
}
int f[maxn],siz[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return fd(f[x]);
}
int st[maxm],tp;
void merge(int u,int v){
	u=fd(u),v=fd(v);
	if(u==v){st[++tp]=0;return ;}
	if(siz[u]<siz[v])swap(u,v);
	upd(siz[u],-1),upd(siz[v],-1);
	st[++tp]=v;f[v]=u,siz[u]+=siz[v];
	upd(siz[u],1);
}
void del(){
	int v=st[tp],u=f[st[tp]];tp--;
	if(!v)return ;
	upd(siz[u],-1);
	f[v]=v,siz[u]-=siz[v];
	upd(siz[u],1),upd(siz[v],1);
}
tuple<int,int,int> e[maxm],e1[maxm],e2[maxm];int m,m1,m2;
set<tuple<int,int,int>> s;
void init(){
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;tp=0;
	clr();upd(1,n);
}
void rebuild(){
	m1=0;for(auto p:s)e1[++m1]=p;
	m2=0;for(int i=1;i<=m;i++)e2[++m2]=e[i];
	s.clear();
	int p=1,q=1;m=0;
	while(p<=m1&&q<=m2){
		if(e1[p]<=e2[q])e[++m]=e1[p++];
		else e[++m]=e2[q++];
	}
	while(p<=m1)e[++m]=e1[p++];
	while(q<=m2)e[++m]=e2[q++];
	init();
	for(int i=1;i<=m;i++)merge(get<1>(e[i]),get<2>(e[i]));
}
void work(){
	n=read();q=read();init();
	while(q--){
		char op=readc();
		if(op=='a'){
			int u=read(),v=read(),w=read();
			s.insert({w,u,v});
		}
		if(op=='r'){
			if(!s.size()||(*--s.end())<=e[m])del(),m--;
			else s.erase(--s.end());
		}
		if(op=='d'){
			if(s.size()>B)rebuild();
			int lst=tp;
			for(auto[w,u,v]:s)merge(u,v);
			printf("%d\n",calc());fflush(stdout);
			while(tp>lst)del();
		}
	}
}
```

---

## 作者：luogu_gza (赞：1)

糖糖糖题。

假设 $n,q$ 同阶。

首先我们想一下单次怎么做，我们维护一个序列 $S$ 表示当前每个连通块的大小，然后每次查询，就输出这个序列排序后的 $\sum_{i=1}^{n}[i\bmod 2=1]|a_{i+1}-a_i|$，如果 $n$ 未奇数就在开头补零。

容易发现这个计数方式天然支持 $O(\log n)$ 的增删改（单点），所以我们尝试去维护连通性。

我们将时间轴分 $\sqrt n$ 块，假设当前已经处理完了前 $i$ 个块，我们把刚刚处理完第 $i$ 个块时候的边集按照边权从小到大拉出来，然后跑启发式合并的并查集（这样的话删最大边等价于撤销），以及序列 $S$。在跑这一个块的时候，我们同样维护当前块 **所加入的边（不要求排好序）** 的集合。

加边：直接往当前块边集里面加。

删最大边：如果是删之前的块里面的边，在前 $i$ 个块的并查集里面撤销掉最大的边，如果是在当前块里面就直接删。

查询：用前 $i$ 个块的并查集处理出当前时刻的并查集和序列 $S$，由于当前块的边数不超过 $\sqrt n$，所以复杂度是对的。

总复杂度 $O(n \sqrt n \log n)$，代码还没写。

---

