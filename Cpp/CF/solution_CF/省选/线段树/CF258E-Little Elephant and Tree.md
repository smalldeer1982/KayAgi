# Little Elephant and Tree

## 题目描述

小象对一棵根节点编号为$1$，节点数为$n$的有根树进行$m$次操作。

这棵树每个节点都有一个集合。

第$i$次操作给出$a_i$和$b_i$，把$i$这个数字放入$a_i$和$b_i$这两个点为根的子树里的所有集合中。（包括$a_i$和$b_i$）

在操作完后，输出$c_i$，$c_i$表示有多少个结点（不包括$i$）的集合至少与$i$结点的集合有一个公共数字。

## 样例 #1

### 输入

```
5 1
1 2
1 3
3 5
3 4
2 3
```

### 输出

```
0 3 3 3 3 ```

## 样例 #2

### 输入

```
11 3
1 2
2 3
2 4
1 5
5 6
5 7
5 8
6 9
8 10
8 11
2 9
3 6
2 8
```

### 输出

```
0 6 7 6 0 2 0 5 4 5 5 ```

# 题解

## 作者：chenxia25 (赞：5)

这题~~虽然水但是~~有好多方法，是个不可多得的好题（

> ### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF258E) & [CF 题目页面传送门](https://codeforces.com/contest/258/problem/E)

> 题意见洛谷里的翻译。

首先，容易想到的是，对于每个节点维护与它有交集的节点集合。显然，设 $subtree(x)$ 表示子树 $x$ 内的节点集合，那么第 $i$ 次操作就是将 $subtree(a_i)\cup subtree(b_i)$ 内所有节点的维护的集合并上 $subtree(a_i)\cup subtree(b_i)$。注意到，看 DFS 序的话，是两个区间，由于是静态的，可以差分，对于每个节点维护一个要并上的区间序列和一个要消除影响的序列。实际上这一步操作用树上差分更好理解？就是子树修改的话在根打个标记，然后每个节点要算上祖先贡献和，一路 DFS 下来该回溯回溯。

接下来的难点在于：如何维护一个数据结构，支持：

1. 给当前集合并上一个区间；
1. 消除以前某次操作 $1$ 的影响；
1. 查询当前不在集合内的数的数量（实际上应该是当前集合的大小，为了方便就维护这个，减一下就可以了）。

### 方法一

大家好我是 yxh，我用我最喜欢的暴力数据结构——分块 A 了这道题~~（其实并没有，她写挂了）~~

很简单，每个块内维护一个基于被插入次数的桶和整体偏移量即可。块长取 $\sqrt n$ 的时候时空复杂度皆为 $\mathrm O(n\sqrt n)$。注意，空间卡得很紧，桶要用 `short` 开。

代码（现场，下面 $3$ 种代码都是这个版本魔改的）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const int N=100000,M=100000,DB_SZ=333;
int n,m; 
vector<int> nei[N+1];
int dfn[N+1],mxdfn[N+1],mng[N+1],nowdfn;
void dfs(int x=1,int fa=0){
	mng[dfn[x]=mxdfn[x]=++nowdfn]=x;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		dfs(y,x);
		mxdfn[x]=mxdfn[y];
	}
}
int d[N+2];
struct dvdblk{
	int sz,sz1;
	int a[N+1];
	struct block{int l,r,added;short cnt[2*M+1];}blk[DB_SZ];
	#define l(p) blk[p].l
	#define r(p) blk[p].r
	#define cnt(p) blk[p].cnt
	#define added(p) blk[p].added
	void bld(int p,int l,int r){
		l(p)=l;r(p)=r;
		memset(cnt(p),0,sizeof(cnt(p)));
		cnt(p)[m]=r-l+1;
		added(p)=0;
	}
	void init(){
		sz1=sqrt(n);
		sz=(n+sz1-1)/sz1;
		for(int i=1;i<=sz;i++)bld(i,(i-1)*sz1+1,min(i*sz1,n));
	}
	void add(int l,int r,int v){
		int pl=(l+sz1-1)/sz1,pr=(r+sz1-1)/sz1;
		if(pl==pr){
			for(int i=l;i<=r;i++)cnt(pl)[a[i]+m]--,cnt(pl)[(a[i]+=v)+m]++;
			return;
		}
		add(l,r(pl),v),add(l(pr),r,v);
		for(int i=pl+1;i<pr;i++)added(i)+=v;
	}
	int zero(){
		int res=0;
		for(int i=1;i<=sz;i++)res+=cnt(i)[m-added(i)];
		return res;
	}
}db;
vector<pair<pair<int,int>,int> > add[N+2];
int ans[N+1];
int main(){
	freopen("b.in","r",stdin);freopen("b.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		nei[x].pb(y);nei[y].pb(x);
	}
	dfs();
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		d[dfn[x]]++,d[mxdfn[x]+1]--,d[dfn[y]]++,d[mxdfn[y]+1]--;
		if(dfn[x]<=dfn[y]&&mxdfn[y]<=mxdfn[x]){
			add[dfn[x]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
		}
		else if(dfn[y]<=dfn[x]&&mxdfn[x]<=mxdfn[y]){
			add[dfn[y]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
		}
		else{
			add[dfn[x]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
			add[dfn[y]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
			add[dfn[x]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
			add[dfn[y]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
		}
	}
	for(int i=1;i<=n;i++)d[i]+=d[i-1];
	db.init();
	for(int i=1;i<=n;i++){
		for(int j=0;j<add[i].size();j++){
			int l=add[i][j].X.X,r=add[i][j].X.Y,v=add[i][j].Y;
			db.add(l,r,v);
		}
//		cout<<db.zero()<<"!\n";
		ans[mng[i]]=n-db.zero()-!!d[i];
	}
	for(int i=1;i<=n;i++)printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}
```

### 方法二

不难发现刚刚那个分块算法其实是远强于这题的需要的。追求更低的复杂度，尝试用线段树解决。一样维护每个数的插入次数，然后每个节点内维护当前区间内 $0$ 的数量。

注意到这题相比于分块这个强算法的特殊性质：永远查询 $0$ 的数量，而 $0$ 是值域里的最小值。

注意到有区间修改，尝试懒标记。然后发现，要加的话，显然根据性质，当前区间就没有 $0$ 了；但如果要减的话，哦吼，你猜不到答案了。

于是尝试标记永久化。哦吼，可以了！修改时在树中经过的节点，用上传更新它们。考虑如何作用当前节点的标记的贡献：若为 $0$，相当于没有贡献，直接上传两个儿子；若 $>0$，则 $0$ 的数量为 $0$；由于每次减法是对之前加法的消除，所以标记恒非负。

时间 $\mathrm O(m\log n)$，空间 $\mathrm O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const int N=100000,M=100000,DB_SZ=333;
int n,m; 
vector<int> nei[N+1];
int dfn[N+1],mxdfn[N+1],mng[N+1],nowdfn;
void dfs(int x=1,int fa=0){
	mng[dfn[x]=mxdfn[x]=++nowdfn]=x;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		dfs(y,x);
		mxdfn[x]=mxdfn[y];
	}
}
int d[N+2];
struct segtree{
	struct node{int l,r,cnt,lz;}nd[N<<2];
	#define l(p) nd[p].l
	#define r(p) nd[p].r
	#define cnt(p) nd[p].cnt
	#define lz(p) nd[p].lz
	void bld(int l=1,int r=n,int p=1){
		l(p)=l;r(p)=r;lz(p)=0;cnt(p)=r-l+1;
		if(l==r)return;
		int mid=l+r>>1;
		bld(l,mid,p<<1);bld(mid+1,r,p<<1|1);
	}
	void init(){bld();}
	void sprup(int p){
		if(l(p)==r(p))cnt(p)=!lz(p);
		else cnt(p)=lz(p)?0:cnt(p<<1)+cnt(p<<1|1);
	}
	void add(int l,int r,int v,int p=1){
		if(l<=l(p)&&r>=r(p))return lz(p)+=v,sprup(p);
		int mid=l(p)+r(p)>>1;
		if(l<=mid)add(l,r,v,p<<1);
		if(r>mid)add(l,r,v,p<<1|1);
		sprup(p);
	}
	int zero(){return cnt(1);}
}segt;
vector<pair<pair<int,int>,int> > add[N+2];
int ans[N+1];
int main(){
	freopen("b.in","r",stdin);freopen("b.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		nei[x].pb(y);nei[y].pb(x);
	}
	dfs();
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		d[dfn[x]]++,d[mxdfn[x]+1]--,d[dfn[y]]++,d[mxdfn[y]+1]--;
		if(dfn[x]<=dfn[y]&&mxdfn[y]<=mxdfn[x]){
			add[dfn[x]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
		}
		else if(dfn[y]<=dfn[x]&&mxdfn[x]<=mxdfn[y]){
			add[dfn[y]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
		}
		else{
			add[dfn[x]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
			add[dfn[y]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
			add[dfn[x]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
			add[dfn[y]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
		}
	}
	for(int i=1;i<=n;i++)d[i]+=d[i-1];
	segt.init();
	for(int i=1;i<=n;i++){
		for(int j=0;j<add[i].size();j++){
			int l=add[i][j].X.X,r=add[i][j].X.Y,v=add[i][j].Y;
			segt.add(l,r,v);
		}
		ans[mng[i]]=n-segt.zero()-!!d[i];
	}
	for(int i=1;i<=n;i++)printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}
```

### 方法三

这是 rng 的一个很巧妙的方法。

继续使用上面那个性质。于是我们只要知道，最小值是多少，最小值有几个即可，判断最小值是否为 $0$ 即可。

于是维护这两个信息，然后你会发现这是可以轻松懒标记和上传的。上传的时候，如果两边最小值不同就取小的，否则合并。

复杂度跟上面一个方法一样。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const int N=100000,M=100000,DB_SZ=333;
int n,m; 
vector<int> nei[N+1];
int dfn[N+1],mxdfn[N+1],mng[N+1],nowdfn;
void dfs(int x=1,int fa=0){
	mng[dfn[x]=mxdfn[x]=++nowdfn]=x;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		dfs(y,x);
		mxdfn[x]=mxdfn[y];
	}
}
int d[N+2];
struct segtree{
	struct node{int l,r,mn,cnt,lz;}nd[N<<2];
	#define l(p) nd[p].l
	#define r(p) nd[p].r
	#define mn(p) nd[p].mn
	#define cnt(p) nd[p].cnt
	#define lz(p) nd[p].lz
	void bld(int l=1,int r=n,int p=1){
		l(p)=l;r(p)=r;mn(p)=lz(p)=0;cnt(p)=r-l+1;
		if(l==r)return;
		int mid=l+r>>1;
		bld(l,mid,p<<1);bld(mid+1,r,p<<1|1);
	}
	void init(){bld();}
	void sprup(int p){
		if(mn(p<<1)==mn(p<<1|1))mn(p)=mn(p<<1),cnt(p)=cnt(p<<1)+cnt(p<<1|1);
		else{
			if(mn(p<<1)<mn(p<<1|1))mn(p)=mn(p<<1),cnt(p)=cnt(p<<1);
			else mn(p)=mn(p<<1|1),cnt(p)=cnt(p<<1|1);
		}
	}
	void tag(int p,int v){
		mn(p)+=v;
		lz(p)+=v;
	}
	void sprdwn(int p){
		tag(p<<1,lz(p));tag(p<<1|1,lz(p));
		lz(p)=0;
	}
	void add(int l,int r,int v,int p=1){
		if(l<=l(p)&&r>=r(p))return tag(p,v);
		sprdwn(p);
		int mid=l(p)+r(p)>>1;
		if(l<=mid)add(l,r,v,p<<1);
		if(r>mid)add(l,r,v,p<<1|1);
		sprup(p);
	}
	int zero(){return mn(1)==0?cnt(1):0;}
}segt;
vector<pair<pair<int,int>,int> > add[N+2];
int ans[N+1];
int main(){
	freopen("b.in","r",stdin);freopen("b.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		nei[x].pb(y);nei[y].pb(x);
	}
	dfs();
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		d[dfn[x]]++,d[mxdfn[x]+1]--,d[dfn[y]]++,d[mxdfn[y]+1]--;
		if(dfn[x]<=dfn[y]&&mxdfn[y]<=mxdfn[x]){
			add[dfn[x]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
		}
		else if(dfn[y]<=dfn[x]&&mxdfn[x]<=mxdfn[y]){
			add[dfn[y]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
		}
		else{
			add[dfn[x]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
			add[dfn[y]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
			add[dfn[x]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
			add[dfn[y]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
		}
	}
	for(int i=1;i<=n;i++)d[i]+=d[i-1];
	segt.init();
	for(int i=1;i<=n;i++){
		for(int j=0;j<add[i].size();j++){
			int l=add[i][j].X.X,r=add[i][j].X.Y,v=add[i][j].Y;
			segt.add(l,r,v);
		}
		ans[mng[i]]=n-segt.zero()-!!d[i];
	}
	for(int i=1;i<=n;i++)printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}
```

### 方法四

不难发现这题还有另一个关于操作时效性的性质：由于树可以表示成括号序列，所以任意一次减法（即对加法的消除影响）都是撤销操作。

ymx 傻乎乎的维护了一个主席树，区间赋 $1$、回到历史版本、区间求和。其实根本不需要~~（只是我不会写的说）~~，用我自己发明的「可撤销线段树」即可。这个东西思想很简单，跟可撤销并查集一样，每一次操作在栈中压入一个修改序列，把所有有修改的节点的原样给记录下来，撤销的时候就还原就可以了。

不难发现，这样空间跟主席树一样，是 $\mathrm O(m\log n)$ 的（捂脸

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const int N=100000,M=100000,DB_SZ=333;
int n,m; 
vector<int> nei[N+1];
int dfn[N+1],mxdfn[N+1],mng[N+1],nowdfn;
void dfs(int x=1,int fa=0){
	mng[dfn[x]=mxdfn[x]=++nowdfn]=x;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(y==fa)continue;
		dfs(y,x);
		mxdfn[x]=mxdfn[y];
	}
}
int d[N+2];
struct segtree{
	struct node{int l,r,sum;bool lz;}nd[N<<2];
	#define l(p) nd[p].l
	#define r(p) nd[p].r
	#define sum(p) nd[p].sum
	#define lz(p) nd[p].lz
	stack<stack<pair<int,node> > > stk;
	void bld(int l=1,int r=n,int p=1){
		l(p)=l;r(p)=r;sum(p)=r-l+1;lz(p)=0;
		if(l==r)return;
		int mid=l+r>>1;
		bld(l,mid,p<<1);bld(mid+1,r,p<<1|1);
	}
	void init(){bld();}
	void sprup(int p){
		stk.top().push(mp(p,nd[p]));
		sum(p)=sum(p<<1)+sum(p<<1|1);
	}
	void tag(int p){
		stk.top().push(mp(p,nd[p]));
		sum(p)=0;lz(p)=true;
	}
	void sprdwn(int p){
		stk.top().push(mp(p,nd[p]));
		if(lz(p))tag(p<<1),tag(p<<1|1),lz(p)=false;
	}
	void chg(int l,int r,int p=1){
		if(p==1)stk.push(stack<pair<int,node> >());
		if(l<=l(p)&&r>=r(p))return tag(p);
		sprdwn(p);
		int mid=l(p)+r(p)>>1;
		if(l<=mid)chg(l,r,p<<1);
		if(r>mid)chg(l,r,p<<1|1);
		sprup(p);
	}
	int zero(){return sum(1);}
	void cancel(){
		stack<pair<int,node> > s=stk.top();
		stk.pop();
		while(s.size())nd[s.top().X]=s.top().Y,s.pop();
	}
}segt;
vector<pair<pair<int,int>,int> > add[N+2];
int ans[N+1];
int main(){
	freopen("b.in","r",stdin);freopen("b.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		nei[x].pb(y);nei[y].pb(x);
	}
	dfs();
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		d[dfn[x]]++,d[mxdfn[x]+1]--,d[dfn[y]]++,d[mxdfn[y]+1]--;
		if(dfn[x]<=dfn[y]&&mxdfn[y]<=mxdfn[x]){
			add[dfn[x]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
		}
		else if(dfn[y]<=dfn[x]&&mxdfn[x]<=mxdfn[y]){
			add[dfn[y]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
		}
		else{
			add[dfn[x]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
			add[dfn[y]].pb(mp(mp(dfn[x],mxdfn[x]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[x],mxdfn[x]),-1));
			add[dfn[x]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[x]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
			add[dfn[y]].pb(mp(mp(dfn[y],mxdfn[y]),1));
			add[mxdfn[y]+1].pb(mp(mp(dfn[y],mxdfn[y]),-1));
		}
	}
	for(int i=1;i<=n;i++)d[i]+=d[i-1];
	segt.init();
	for(int i=1;i<=n;i++){
		for(int j=0;j<add[i].size();j++){
			int v=add[i][j].Y;
			if(v==-1)segt.cancel();
		}
		for(int j=0;j<add[i].size();j++){
			int l=add[i][j].X.X,r=add[i][j].X.Y,v=add[i][j].Y;
			if(v==1)segt.chg(l,r);
		}
		ans[mng[i]]=n-segt.zero()-!!d[i];
	}
	for(int i=1;i<=n;i++)printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}
```

### 对比

![](https://s1.ax1x.com/2020/08/26/dWdM6I.png)

中间那次 WA 的不管，从下到上分别是第 $1\sim4$ 种方法。

可见，分块复杂度大，劣是正常的；中间两种方法比较好也是理所当然的；而最后一种「我发明」的数据结构，虽然复杂度要优于分块，但是时空却被其他三种方法全方位吊打，说明我是 sb！！！

---

## 作者：little_sun (赞：4)

### 题目大意

你有一棵有 $n$ 个节点的有根（根为 $1$ ）树，你要对对其进行 $m$ 次操作。

每次操作给出两个数 $a_i, b_i$，你要往以 $a_i, b_i$ 为根的子树内每个点的集合里加入数 $i$。

问最后对于每个点有多少个点（不包括自己）的集合与其交集非空。

$1 \leq n, m \leq 10^5$

### 题目分析

将树按照 $\texttt{DFS}$ 序遍历，则子树对应于一段连续的区间。

现在的操作就相当于 给出两个区间 $[a,b],[l,r]$，这两个区间并集内的所有节点都变得两两关联。 

关联关系的定义中涉及两个节点，因此考虑两维，第一维表示关联定义中的 第一个节点，而第二维表示关联定义中的第二个节点，两维考虑的范围都是树上 所有的节点，那么操作就相当于说，使得第一维当中的所有编号$[a,b],[l,r]$ 中 的点与第二维中所有编号为 $[a,b],[l,r]$ 中的点互相关联。

这个问题可以将每个操作拆成 $4$ 个矩形，使用矩形面积并的方式用扫描线$+$线段树解决。

### 代码

``` cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)
#define meow(cat...) fprintf(stderr, cat)

const int MaxN = 2e5 + 10;

struct edge
{
    int next, to;
} e[MaxN << 1];

struct node
{
    int l, r;
    int sum, len;
};

struct query
{
    int pos, l, r, c;
} Q[MaxN << 2];

int n, m, q, cnt, now, dfscnt, ans[MaxN];
int head[MaxN], dfn[MaxN], siz[MaxN];

struct SegmentTree
{
    node t[MaxN << 2];
    void build(int id, int l, int r)
    {
        t[id].l = l, t[id].r = r;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void pushup(int id)
    {
        int l = t[id].l, r = t[id].r;
        if (t[id].sum) t[id].len = r - l + 1;
        else
            t[id].len = t[id << 1].len + t[id << 1 | 1].len;
    }
    void modify(int id, int l, int r, int val)
    {
        if (t[id].r < l || r < t[id].l)
            return;
        if (l <= t[id].l && t[id].r <= r)
        {
            t[id].sum += val, pushup(id);
            return;
        }
        modify(id << 1, l, r, val);
        modify(id << 1 | 1, l, r, val), pushup(id);
    }
} T;

int cmp(query a, query b) { return a.pos < b.pos; }

void add(int a, int b, int l, int r)
{
    Q[++q] = (query){a, l, r, 1};
    Q[++q] = (query){b + 1, l, r, -1};
    // meow("$ %d %d %d %d\n", a, b, l, r);
}

void add_edge(int u, int v)
{
    ++cnt;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

inline int read()
{
    int x = 0;
    char ch = getchar();
    while(ch > '9' || ch < '0')
        ch = getchar();
    while(ch <= '9' && ch >= '0') 
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}


void dfs(int u, int fa)
{
    dfn[u] = ++dfscnt, siz[u] = 1;
    for(int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if(v == fa) continue;
        dfs(v, u), siz[u] += siz[v];
    }
}

signed main()
{   
    n = read(), m = read(), T.build(1, 1, n);
    for(int i = 1; i < n; i++)
    {
        int u = read(), v = read();
        add_edge(u, v), add_edge(v, u);
    }
    dfs(1, 0);
    for(int i = 1; i <= m; i++)
    {
        int a, b, l, r;
        a = read(), b = dfn[a] + siz[a] - 1, a = dfn[a];
        l = read(), r = dfn[l] + siz[l] - 1, l = dfn[l];
        add(a, b, a, b), add(a, b, l, r);
        add(l, r, a, b), add(l, r, l, r);
    }
    std::sort(Q + 1, Q + q + 1, cmp), now = 1;
    for(int i = 1; i <= n; i++)
    {
        while(now <= q && Q[now].pos == i)
            T.modify(1, Q[now].l, Q[now].r, Q[now].c), ++now;
        ans[i] = T.t[1].len, ans[i] ? --ans[i] : 0;
    }
    for(int i = 1; i <= n; i++)
        printf("%d ", ans[dfn[i]]);
    return 0;
}
```





---

## 作者：MCAdam (赞：3)

[题目](https://www.luogu.com.cn/problem/CF258E)

~~看到没啥人写水发题解~~

一开始的想法：

假如每次操作都是一个节点，那么只需要在根节点打上标记，然后一遍$dfs$下来就好了。这提醒我们，把信息记录在根上，然后一路传递下来

对于节点$a$，设和它关联的节点为$\{b_1,b_2,...,b_k\}$

很显然的，$b_i$的深度越小，子树的大小就越大

那直接取$b_i$中深度最小的吗？不一定，因为$b_i,b_j$的子树可能没有交集

然后就想，只要把有交集的$b$保留深度最大的，然后剩下的$b_i$的子树大小的和就是$a$的答案（还要加上从他祖先传递下来的）

那怎么判断有没有交集呢？交集肯定是放在区间上啊，还是看子树，那直接求个$dfs$序不就转变为区间上的问题了吗

准备开始码的时候，想到：判断一个点$b$是否和前面的有交集，就直接在维护$dfs$序的线段树上单点查询，如果有查到，再判断深度大小，如果当前这个深度更浅就要把上一个去掉，好麻烦QWQ

如果没有交集，线段树上当然可以直接加；如果有交集的话，为什么不能直接加呢？既然都有一颗线段树了，为什么还要去维护没有交集的$\{b\}$呢？每次区间修改，区间询问有多少个不为$0$的数不就好了吗

因为计算完$p$以及其子树答案后，回溯到父亲时，$p$及其子树的信息肯定是要去掉的

所以线段树要支持的操作：区间$+1/-1$以及询问整个区间有多少个不为$0$的数

注意到$+1,-1$操作一定是成对存在的，所以可以直接写成标记永久化

细节：

1、如果当前节点$p$有关联的节点，除了修改关联节点子树内的，还有$p$子树内的

2、每个节点在$dfs$序上是有两个的，所以最后答案是不为$0$的数除以$2$再减$1$（不包括自己）

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int N=1e6+10;
int tot,cnt;
int fir[N],dfn[N][2],ans[N];
vector<int>opt[N];
struct edge
{
	int to;
	int nxt;
}e[2*N];
inline void add(int x,int y)
{
	e[++tot].to=y; e[tot].nxt=fir[x]; fir[x]=tot;
	e[++tot].to=x; e[tot].nxt=fir[y]; fir[y]=tot;
}
struct tree
{
	int left,right;
	int val,cnt;
}t[8*N];
inline void build(int p,int l,int r)
{
	t[p].left=l,t[p].right=r;
	if(l==r) return;
	int mid=(t[p].left+t[p].right)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
}
inline void pushup(int p)
{
	if(t[p].val>0) t[p].cnt=t[p].right-t[p].left+1;
	else t[p].cnt=t[p*2].cnt+t[p*2+1].cnt;
}
inline void change(int p,int l,int r,int c)
{
	if(l<=t[p].left&&r>=t[p].right)
	{
		t[p].val+=c;
		pushup(p);
		return;
	}
	int mid=(t[p].left+t[p].right)/2;
	if(l<=mid) change(p*2,l,r,c);
	if(r>mid) change(p*2+1,l,r,c);
	pushup(p);
}
inline void dfs1(int p,int fa)
{
	dfn[p][0]=++cnt;
	for(int i=fir[p];i;i=e[i].nxt)
		if(e[i].to!=fa) dfs1(e[i].to,p);
	dfn[p][1]=++cnt;
}
inline void dfs2(int p,int fa)
{
	if(opt[p].size()) change(1,dfn[p][0],dfn[p][1],1);
	for(int i=0;i<opt[p].size();i++)
		change(1,dfn[opt[p][i]][0],dfn[opt[p][i]][1],1);
	if(t[1].cnt) ans[p]=t[1].cnt/2-1;
	for(int i=fir[p];i;i=e[i].nxt)
		if(e[i].to!=fa) dfs2(e[i].to,p);
	if(opt[p].size()) change(1,dfn[p][0],dfn[p][1],-1);
	for(int i=0;i<opt[p].size();i++)
		change(1,dfn[opt[p][i]][0],dfn[opt[p][i]][1],-1);
}
int main()
{
	int n,m,a,b;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	dfs1(1,0);
	build(1,1,2*n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		opt[a].push_back(b);
		opt[b].push_back(a);	
	}
	dfs2(1,0);
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：Code_星云 (赞：1)

水题。

看见放集合很容易想到标记永久化，然后这题就在树上做永久化就可以了。具体的就是在其欧拉序上修改。然后维护哪些点的颜色重合时可以用扫描线来维护。

```cpp
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
#define pb push_back
#define lc (x << 1)
#define rc (x << 1 | 1)

const int N = 200005;
int n, m, idx, bg[N], ed[N], ret[N], ans[N];
vector<int> g[N], v[N];

namespace sgtree{
	struct segtree{
		int l, r, add, sum;
		#define l(x) tree[x].l
		#define r(x) tree[x].r
		#define add(x) tree[x].add
		#define sum(x) tree[x].sum
	};
	segtree tree[N << 2];
	void pushup(int x){
		if(add(x)) sum(x) = r(x) - l(x) + 1;
		else sum(x) = sum(lc) + sum(rc);
	}
	void build(int x, int l, int r){
		l(x) = l; r(x) = r; sum(x) = add(x) = 0;
		if(l == r) return; int mid = (l + r) >> 1;
		build(lc, l, mid); build(rc, mid + 1, r);
		pushup(x);
	}
	void modify(int x, int l, int r, int val){
		if(l <= l(x) && r(x) <= r){add(x) += val; pushup(x); return;}
		int mid = (l(x) + r(x)) >> 1;
		if(l <= mid) modify(lc, l, r, val);
		if(r > mid) modify(rc, l, r, val);
		pushup(x);
	}
};
using namespace sgtree;

void dfs(int u, int fa){
	ret[bg[u] = ++ idx] = u;
	for(auto v: g[u]) if(v != fa) dfs(v, u);
	ed[u] = idx;
}
void work(int u, int fa){
	if(v[u].size()) modify(1, bg[u], ed[u], 1);
	for(auto k: v[u]) modify(1, bg[k], ed[k], 1);
	ans[u] = sum(1) - (sum(1) ? 1 : 0);
	for(auto v: g[u]) if(v != fa) work(v, u);
	if(v[u].size()) modify(1, bg[u], ed[u], - 1);
	for(auto k: v[u]) modify(1, bg[k], ed[k], - 1);
}
signed main(){
	scanf("%lld %lld", &n, &m);
	for(int i = 1; i < n; i ++){
		int u, v; scanf("%lld %lld", &u, &v);
		g[u].pb(v); g[v].pb(u);
	}
	for(int i = 1; i <= m; i ++){
		int x, y; scanf("%lld %lld", &x, &y);
		v[x].pb(y); v[y].pb(x);
	}
	build(1, 1, n); dfs(1, 0); work(1, 0);
	for(int i = 1; i <= n; i ++) printf("%lld ", ans[i]);
	puts(""); return 0;
}
```


---

## 作者：daniEl_lElE (赞：1)

主席树。

对于所有 $a_i,b_i$，相当于是：

* 让 $a_i$ 与 $a_i$ 的子树可产生贡献。
* 让 $a_i$ 与 $b_i$ 的子树可产生贡献。
* 让 $b_i$ 与 $a_i$ 的子树可产生贡献。
* 让 $b_i$ 与 $b_i$ 的子树可产生贡献。

考虑对于每个节点维护一个线段树，这样的话相当于就是要实现一个区间赋值为 $1$ 的操作。

容易发现每个点还要继承父亲的线段树，于是主席树即可。

```cpp
#include <bits/stdc++.h>
//#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
vector<int> vc[100005];
vector<int> addp[100005];
int ind[100005],outd[100005],cnt,rt[100005],ans[100005];
void dfs1(int now,int fa){
	ind[now]=++cnt;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs1(v,now);
	}
	outd[now]=cnt;
}
struct sgt{
	int f[20000005],L[20000005],R[20000005],cnt;
	void pushdown(int i,int l,int r){
		if(f[i]==r-l+1){
			if(!L[i]) L[i]=++cnt;
			if(!R[i]) R[i]=++cnt;
			f[L[i]]=mid-l+1;
			f[R[i]]=r-mid;
		}
		if(cnt>20000000) exit(0);
	}
	int add(int i1,int l,int r,int ql,int qr){
		int i2=++cnt;
		if(cnt>20000000) exit(0);
		if(ql<=l&&r<=qr){
			f[i2]=r-l+1;
			return i2;
		}
		pushdown(i1,l,r);
		if(ql>mid) L[i2]=L[i1];
		else L[i2]=add(L[i1],l,mid,ql,qr);
		if(qr<=mid) R[i2]=R[i1];
		else R[i2]=add(R[i1],mid+1,r,ql,qr);
		f[i2]=f[L[i2]]+f[R[i2]];
		return i2;
	}
	int qry(int i,int l,int r,int pos){
		if(l==r) return f[i];
		pushdown(i,l,r);
		if(pos<=mid) return qry(L[i],l,mid,pos);
		if(pos>mid) return qry(R[i],mid+1,r,pos);
	}
}tree;
void dfs2(int now,int fa){
//	cout<<now<<" ";
	rt[now]=rt[fa];
	for(auto v:addp[now]){
		rt[now]=tree.add(rt[now],1,100000,ind[v],outd[v]);
	}
	ans[now]=tree.f[rt[now]]-tree.qry(rt[now],1,100000,ind[now]);
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs2(v,now);
	}
}
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	dfs1(1,0);
	for(int i=1;i<=m;i++){
		int a,b; cin>>a>>b;
		addp[a].push_back(a);
		addp[a].push_back(b); 
		addp[b].push_back(a);
		addp[b].push_back(b); 
	}
	dfs2(1,0);
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}

```

---

## 作者：shinzanmono (赞：1)

一道数据结构思维的好题。

定义 $[subtree(u)]$ 表示 $u$ 的子树所对应的 DFN 区间。$[l,r][a,b]$ 表示横坐标在 $[l,r]$ 纵坐标在 $[a,b]$ 的矩形。

我们先转化问题，定义 $f[i][j]$ 表示 $i$ 和 $j$ 是否拥有相同的颜色，每增加一个数字就相当于在 $[subtree(a)][subtree(a)]$，$[subtree(a)][subtree(b)]$，$[subtree(b)][subtree(a)]$，$[subtree(b)][subtree(b)]$ 四个矩形全部赋值为 $1$。

于是，我们进行降维，把形如 $[l,r][a,b]$ 的操作转化为在 $l$ 将 $[a,b]$ 所对应的区间等价一份贡献，在 $r+1$ 将 $[a,b]$ 所对应的区间减少一份贡献。

接下来我们考虑如何求出非零位的个数。

由于区间总长度固定，所以非零位个数 $=$ 区间长度 $-$ 零位个数。

由于只有无颜色的时候点的权值才为 $0$，所以 $0$ 是最小值，我们只需要统计最小值个数并判断是否为 $0$ 即可。

具体实现看代码。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
const int sz=1e5+10;
struct ST{
    struct node{
        int min,cnt;
        node operator+(const node &a)const{
            if(min==a.min)return node{min,cnt+a.cnt};
            else if(min<a.min)return node{min,cnt};
            else return node{a.min,a.cnt};
        }
    }tree[sz<<2];
    int lazy[sz<<2];
    void build(int p,int ln,int rn){
        if(ln==rn)return tree[p].cnt=rn-ln+1,void();
        int mid=ln+rn>>1;
        build(p<<1,ln,mid);
        build(p<<1|1,mid+1,rn);
        tree[p]=tree[p<<1]+tree[p<<1|1];
    }
    void pushdown(int p,int ln,int rn){
        if(lazy[p]!=0){
            tree[p<<1].min+=lazy[p];
            tree[p<<1|1].min+=lazy[p];
            lazy[p<<1]+=lazy[p];
            lazy[p<<1|1]+=lazy[p];
            lazy[p]=0;
        }
    }
    void add(int p,int ln,int rn,int l,int r,int val){
        if(ln>=l&&rn<=r)return tree[p].min+=val,lazy[p]+=val,void();
        int mid=ln+rn>>1;
        pushdown(p,ln,rn);
        if(l<=mid)add(p<<1,ln,mid,l,r,val);
        if(r>mid)add(p<<1|1,mid+1,rn,l,r,val);
        tree[p]=tree[p<<1]+tree[p<<1|1];
    }
}st;
std::vector<int>graph[sz];
int dfn[sz],size[sz],dpp,rnk[sz],ans[sz];
void dfs(int u,int fau){
    dfn[u]=++dpp,rnk[dpp]=u,size[u]=1;
    for(int v:graph[u]){
        if(v==fau)continue;
        dfs(v,u);
        size[u]+=size[v];
    }
}
struct Query{
    int l,r,val;
};
std::vector<Query>que[sz];
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,q;
    std::cin>>n>>q;
    for(int i=1,u,v;i<n;i++)
        std::cin>>u>>v,graph[u].push_back(v),graph[v].push_back(u);
    dfs(1,0);
    st.build(1,1,n);
    while(q--){
        int a,b;
        std::cin>>a>>b;
        que[dfn[a]].push_back(Query{dfn[a],dfn[a]+size[a]-1,1});
        que[dfn[a]].push_back(Query{dfn[b],dfn[b]+size[b]-1,1});
        que[dfn[a]+size[a]].push_back(Query{dfn[a],dfn[a]+size[a]-1,-1});
        que[dfn[a]+size[a]].push_back(Query{dfn[b],dfn[b]+size[b]-1,-1});
        que[dfn[b]].push_back(Query{dfn[a],dfn[a]+size[a]-1,1});
        que[dfn[b]].push_back(Query{dfn[b],dfn[b]+size[b]-1,1});
        que[dfn[b]+size[b]].push_back(Query{dfn[a],dfn[a]+size[a]-1,-1});
        que[dfn[b]+size[b]].push_back(Query{dfn[b],dfn[b]+size[b]-1,-1});
    }
    for(int i=1;i<=n;i++){
        for(auto qq:que[i])st.add(1,1,n,qq.l,qq.r,qq.val);
        if(st.tree[1].min!=0)ans[rnk[i]]=n;
        else ans[rnk[i]]=n-st.tree[1].cnt;
    }
    for(int i=1;i<=n;i++){
        if(ans[i]==0)std::cout<<ans[i]<<" ";
        else std::cout<<ans[i]-1<<" ";
    }
    std::cout<<"\n";
    return 0;
}
```

---

## 作者：redegg (赞：1)

1.如何将树处理，处理成数，方便进行线段树操作？

2.如何快速且正确地找到对于任何一个点，他有交集的其他点？

对于疑问1，我们可以用dfn来做，因为深度优先序可以让我们知道对于任何一个点，他的子树是哪些（其子树dfn一定连续的，而且大于父亲节点的）。

对于疑问2，我们可以将题目给出的操作（a，b）存储下来，然后存入vector，方便以后进行线段树操作，比如给出操作（2，3），在后面的过程里，我们访问到点2，就知道对点2和点3的子树同时更新。

我们把所有操作存储后，从根节点开始再次dfs，对于现在做到的点x，我们可以从vector中知道他对应的操作（x，y1）（x，y2）......(x,yn)。此时用线段树，对x的子树，y1，y2，y3......yn的子树分别加1，此时继续利用线段树访问全部点，找到>0的点有多少个，这就是点x答案了。

处理出x的答案，就继续向x的儿子节点dfs重复以上操作，在儿子节点做完操作后，返回x的父亲节点前，将原来+1过的线段树区间全部-1，这样就不会对父亲节点和其它和自己同层的子节点造成影响了。

为何一定是正确的呢？因为我们做到x点时，x的儿子节点的操作与答案x无关，只有x的祖先节点才会影响到x（因为每个点更新，其子树也会更新），所以在返回的时候一定要去除掉子树的更新。

其次就是如何求出>0的点的个数了，这个代码中给出了，自己理解（强行为自己口述不清找借口）。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[6000000];
int t[6000000];
int lazy[6000000];
int c[6000000];
int k[6000000];

int n,m,op;

int w[600006];
int dis[600006];
vector<int> q[600005];
vector<int> p[600005];

void down(int l,int r,int id)
{
    int mid=(l+r)/2;
    lazy[id*2]+=lazy[id];
    lazy[id*2+1]+=lazy[id];
    t[id*2]+=(mid-l+1)*lazy[id];
    t[id*2+1]+=(r-mid)*lazy[id];
    lazy[id]=0;
}

void update(int l,int r,int z,int y,int v,int id)
{
    if(l==z&&r==y)
    {
        t[id]+=(r-l+1)*v;
        c[id]+=v;
        lazy[id]+=v;
        if(c[id]>0)k[id]=(r-l+1);
        else k[id]=k[id*2]+k[id*2+1];
        return ;
    }
    down(l,r,id);
    int mid=(l+r)/2;
    if(mid>=y)update(l,mid,z,y,v,id*2);
    else if(mid<z)update(mid+1,r,z,y,v,id*2+1);
    else
    {
        update(l,mid,z,mid,v,id*2);
        update(mid+1,r,mid+1,y,v,id*2+1);
    }
    t[id]=t[id*2]+t[id*2+1];
    if(c[id]>0)k[id]=(r-l+1);
    else
        k[id]=k[id*2]+k[id*2+1];
}

int cck(int l,int r,int x,int id)
{
    if(l==r&&l==x)
    {
        if(t[id]>0)
            return 1;
        else return 0;
    }
    down(l,r,id);
    int mid=(l+r)/2;
    if(mid>=x)return cck(l,mid,x,id*2);
    else return cck(mid+1,r,x,id*2+1);
}

void dfs(int x,int last)
{
    op++;
    dis[x]=op;
    for(int i=0;i<q[x].size();i++)
    {
        int nx=q[x][i];
        if(nx==last)continue;
        dfs(nx,x);
        w[x]+=w[nx];
    }
    w[x]+=1;
}

int ans[600000];

void dd(int x,int last)
{
    for(int i=0;i<p[x].size();i++)
    {
        int nx=p[x][i];
        update(1,op,dis[x],dis[x]+w[x]-1,1,1);
        update(1,op,dis[nx],dis[nx]+w[nx]-1,1,1);
    }
    ans[x]=k[1]-cck(1,op,dis[x],1);
    for(int i=0;i<q[x].size();i++)
    {
        int nx=q[x][i];
        if(nx==last)continue;
        dd(nx,x);
    }
    for(int i=0;i<p[x].size();i++)
    {
        int nx=p[x][i];
        update(1,op,dis[x],dis[x]+w[x]-1,-1,1);
        update(1,op,dis[nx],dis[nx]+w[nx]-1,-1,1);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        q[x].push_back(y);
        q[y].push_back(x);
    }
    dfs(1,1);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        p[x].push_back(y);
        p[y].push_back(x);
    }
    dd(1,1);
    for(int i=1;i<=n;i++)
    {
        printf("%d ",ans[i]);
    }
    printf("\n");
    return 0;
}

```

---

## 作者：wangif424 (赞：0)

被加进模拟赛，然后第一次场切紫题。

根据题面描述，每次的操作会使两棵子树之间产生交集。

朴素的想法是给每个节点打上标记 $i$，表示集合里有数字 $i$，但显然这样没法判断两个集合有无交集。

于是考虑将有交集的点作为标记，考虑到这样每次操作最多加 $O(n)$ 个点，于是需要高效的加点方式。回忆起听树上问题时的“多想想...欧拉序...”，于是答案呼之欲出。

- 对于一次操作 $a_i,b_i$，给两个点分别打上 $[in_{a_i},out_{a_i}],[in_{b_i},out_{b_i}]$ 的标记。

- 然后遍历整棵树，遍历到节点 $u$ 时，我们将 $u$ 的标记作为左右端点区间加 $1$，求区间内非零的数的个数除以二再减去自身作为答案，再遍历子树，最后退出当前点时做区间减 $1$。

- 以上的区间操作可以使用线段树维护区间最小值以及区间最小值的个数解决，时间复杂度 $O(m\log n)$。

## AC 代码
```cpp
#include <bits/stdc++.h>
#define R(x) x = read()
#define ENDL push('\n');
#define SPACE push(' ');
#define int long long
#define pii pair<int,int>
using namespace std;
char pbuf[1<<20], *pp=pbuf;
inline void push(const char &c) {
	if(pp - pbuf == 1<<20)fwrite(pbuf, 1, 1<<20, stdout),pp = pbuf;
	*pp++ = c;
}
class io {public:~io() {fwrite(pbuf, 1, pp - pbuf, stdout);}} _;
inline void write(int x) {
	if (x<0)x=-x,push('-');
	int sta[35],top=0;
	do {
		sta[top++]=x%10,x/=10;
	} while (x);
	while(top)push(sta[--top]^'0');
}
#ifndef LOCAL
	char buf[1<<23],*p1=buf,*p2=buf;
	#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
    return x*f;
}
int n,m;
struct edge{
	int to,nxt;
}v[200100];
int len,fir[100100];
void add(int x,int y){
	++len;
	v[len]=edge{y,fir[x]};
	fir[x]=len;
}
int in[100100],out[100100],tot;
void dfs1(int u,int fa){
	in[u]=++tot;
	for(int i=fir[u];i;i=v[i].nxt){
		if(v[i].to==fa)continue;
		dfs1(v[i].to,u);
	}
	out[u]=++tot;
}
vector<pii > s[100100];
struct node{
	int ls,rs,mn,ms,lzy;
}t[400100];
int siz=1;
void pd(int i){
	t[t[i].ls].lzy+=t[i].lzy;
	t[t[i].rs].lzy+=t[i].lzy;
	t[t[i].ls].mn+=t[i].lzy;
	t[t[i].rs].mn+=t[i].lzy;
	t[i].lzy=0;
}
void pup(int i){
	t[i].mn=min(t[t[i].ls].mn,t[t[i].rs].mn);
	t[i].ms=t[t[i].ls].ms*(t[i].mn==t[t[i].ls].mn)+t[t[i].rs].ms*(t[i].mn==t[t[i].rs].mn);
}
void build(int i,int l,int r){
	if(l==r)return t[i].ms=1,void();
	int mid=(l+r)>>1;
	t[i].ls=++siz;
	t[i].rs=++siz;
	build(t[i].ls,l,mid);
	build(t[i].rs,mid+1,r);
	pup(i);
}
void upd(int i,int l,int r,int ll,int rr,int k){
	if(ll<=l&&r<=rr){
		t[i].lzy+=k;
		t[i].mn+=k;
		return;
	}
	int mid=(l+r)>>1;
	pd(i);
	if(ll<=mid)upd(t[i].ls,l,mid,ll,rr,k);
	if(rr>mid)upd(t[i].rs,mid+1,r,ll,rr,k);
	pup(i);
}
int ask(){
	if(t[1].mn==0)return n-t[1].ms/2;
	return n;
}
int ans[100100];
void dfs(int u,int fa){
	for(auto i:s[u]){
		int l,r;tie(l,r)=i;
		upd(1,1,n+n,l,r,1);
	}
	ans[u]=ask();
	ans[u]-=!!ans[u];
	for(int i=fir[u];i;i=v[i].nxt){
		if(v[i].to==fa)continue;
		dfs(v[i].to,u);
	}
	for(auto i:s[u]){
		int l,r;tie(l,r)=i;
		upd(1,1,n+n,l,r,-1);
	}
}
signed main(){
	R(n);R(m);
	for(int i=1;i^n;i++){
		int R(x),R(y);
		add(x,y);add(y,x);
	}
	dfs1(1,0);
	while(m--){
		int R(a),R(b);
		s[a].push_back(pii(in[a],out[a]));
		s[b].push_back(pii(in[a],out[a]));
		s[a].push_back(pii(in[b],out[b]));
		s[b].push_back(pii(in[b],out[b]));
	}
	build(1,1,n*2);
	dfs(1,0);
	for(int i=1;i<=n;i++)write(ans[i]),push(' ');
    return 0;
}
```

---

## 作者：OtterZ (赞：0)

# 题意
对一棵 $n$ 个点的树作 $m$ 次操作，每次操作对两个子树打一个新标记，问对于每个点，有多少个点与这个节点有过同一个标记。
# 朴素枚举
对于每个操作，可以将一个点对应记录另一个点，条件是两个点都在操作范围内，但这么做代码复杂，时间也慢。
# 树上问题->区间问题
据个人经验，区间问题打标记通常简单，又知道 `dfs` 序使得子树对应到一个连续的区间，故而我们可以考虑把 `dfs` 序求出来，再考虑下一步。

```cpp
//先求dfs
int n,dfs[100009],dfscnt,ot[100009],ots[100009];
vector<int>e[100009];//树边
void tree_srh(int nk,int l){
	dfs[nk]=++dfscnt;
	for(int i=0;i<e[nk].size();i++){
		if(e[nk][i]==l)continue;//去父节点 
		tree_srh(e[nk][i],nk);//搜 
	}
	ot[nk]=ots[dfs[nk]]=dfscnt;//右界 
} 
```
接下来，我们要应对的问题是：  
**已知一个长度为 $n$ 的区间，每个元素对应一个区间右界，$m$ 次操作会将两个区间打上新标记，问对每个元素有多少个元素含有这个元素拥有的标记。**
# 线段树分治
对于这种标记方式，我们发现即使是应对区间的用于打标记的诸多数据结构，也很难直接操作，这时我们可以想到对于这道题有一个类似的问题：  
已知对 $n$ 个点，有 $m$ 条边，每条边有个存在时间，问对于每个时刻这个图是不是二分图？  
也就是[这道题](https://www.luogu.com.cn/problem/P5787)。   
我们同样发现诸多数据结构很难对边这个特殊标记直接处理，这个时候我们使用了线段树分治。  
类比到这道题，我们一样可以用线段树分治处理标记，遍历得到答案。
接下来，我们就要处理单点得到答案。
# 最后处理答案
我们可以发现，标记区间只有**相离和包含**两种状态，所以可以用 `multiset` 解决，即进行五步操作：

1. 设 $u=1$；
2. 找到开头 $l \ge u$ 且 $l$ 最小的区间 $l,r$；
3. 计算答案；
4. 将 $u$ 改为 $r+1$；
5. 回到第一步。

具体看代码：

```cpp
int tamp(){//算答案 
	int u=1,ats=0;
	while(u<=n){
		multiset<int>::iterator it=s.lower_bound(u);
		if(it==s.end())break;
		ats+=ots[*it]-*it+1;
		u=ots[*it]+1;
	}
	return ats;
}
```
# 注意事项

1. 线段树数组大小不宜过小；
2. 线段树分治处理顺序对应 `dfs` 序而非节点顺序。

# 代码

```cpp
#include<cstdio>
#include<set>
#include<vector>
using namespace std;
//先求dfs
int n,dfs[100009],dfscnt,ot[100009],ots[100009];
vector<int>e[100009];//树边
void tree_srh(int nk,int l){
	dfs[nk]=++dfscnt;
	for(int i=0;i<e[nk].size();i++){
		if(e[nk][i]==l)continue;//去父节点 
		tree_srh(e[nk][i],nk);//搜 
	}
	ot[nk]=ots[dfs[nk]]=dfscnt;//右界 
} 
//线段树分治
vector<int>seg_tree[(1<<21)];//线段树超长空间
int m,a,b;//记录线段树大小没那么重要 
multiset<int>s;//算答案用
int ans[100009];//答案存储 
void add(int k,int l,int r,const int lq,const int rq,const int n_val){//加入元素 
//printf("%d %d %d %d %d\n",k,l,r,lq,rq);
	if(l>rq||r<lq)return;//不涉及 
	if(l>=lq&&r<=rq){//加变量
		seg_tree[k].push_back(n_val); 
		return;
	}
	int m=(l+r)>>1;
	add((k<<1),l,m,lq,rq,n_val);
	add((k<<1)|1,m+1,r,lq,rq,n_val);
} 
int tamp(){//算答案 
	int u=1,ats=0;
	while(u<=n){
		multiset<int>::iterator it=s.lower_bound(u);
		if(it==s.end())break;
		ats+=ots[*it]-*it+1;
		u=ots[*it]+1;
	}
	return ats;
}
void solve(int k,int l,int r){//统一处理
	//printf("%d %d %d\n",k,l,r); 
	for(int i=0;i<seg_tree[k].size();i++)s.insert(seg_tree[k][i]);
	if(l==r){
		ans[l]=tamp();
		if(!s.empty())ans[l]--;//去掉自己 
	} 
	else{
		int m=(l+r)>>1;
		solve((k<<1),l,m);
		solve((k<<1)|1,m+1,r);
	}
	for(int i=0;i<seg_tree[k].size();i++)s.erase(s.find(seg_tree[k][i]));
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<n;i++){
		scanf("%d %d",&a,&b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	tree_srh(1,0);
	/*for(int i=1;i<=n;i++){
		printf("%d ",dfs[i]);
	}
	putchar('\n');*/
	for(int i=1;i<=m;i++){
		scanf("%d %d",&a,&b);
		add(1,1,n,dfs[a],ot[a],dfs[a]);
		add(1,1,n,dfs[a],ot[a],dfs[b]);
		add(1,1,n,dfs[b],ot[b],dfs[a]);
		add(1,1,n,dfs[b],ot[b],dfs[b]);
	}
	solve(1,1,n);
	for(int i=1;i<=n;i++){
		printf("%d ",ans[dfs[i]]);//注意是按dfs序处理和存储答案的 
	}
	return 0;
}
```
# 后续
![](https://cdn.luogu.com.cn/upload/image_hosting/agzq5k7a.png)
代码虽然 `AC` 了，但是后来感觉时间复杂度有点假，欢迎大家提供时间复杂度证明或 `hack`。
# 整改
- 2023/11/3：修改一处细节问题。
- 2023/11/5：格式整改。

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2400}$
---
### 解题思路：

一眼扫描线。

操作是对于一整个子树进行的，先将编号转化成 $\text{dfn}$ 序，得到一个连续的编号。

接着考虑具体操作，由于每一次操作加入的数是不一样的，发现操作和操作之间不会干扰。更进一步地，每一次操作都是将两个区间内的点之间相互关联，关联多次的点不会产生额外贡献。

由此想到这其实是一个矩形的面积并，令 $(i,j)$ 点表示第 $i$ 个点和第 $j$ 个点是否关联，若关联区间 $[l_1,r_1]$ 和 $[l_2,r_2]$，也就相当于对于左下角为 $(l_1,l_1)$ 右上角为 $(r_1,r_1)$，左下角为 $(l_1,l_2)$ 右上角为 $(r_1,r_2)$，左下角为 $(l_2,l_1)$ 右上角为 $(r_2,r_1)$，左下角为 $(l_2,l_2)$ 右上角为 $(r_2,r_2)$ 四个矩形进行覆盖。

特殊地，为了方便最后操作，对于每一个位置 $(i,i)$ 单独覆盖。

最终每一个位置 $i$ 的答案即为横坐标（或者使用对称地纵坐标）为 $i$ 的点被染色的数量。

复杂度 $O((n+m)\log n)$。

---
### 代码：

---

