# [POI 2023/2024 R1] Przyciski

## 题目背景

译自 [XXXI Olimpiada Informatyczna - I etap](https://sio2.mimuw.edu.pl/c/oi31-1/dashboard/) [Przyciski](https://sio2.mimuw.edu.pl/c/oi31-1/p/prz/)。

## 题目描述

一个 $n\times n$ 的方阵，里面有 $m$ 个按钮。

你需要按下若干个（至少一个）按钮，使得每行每列被按下的按钮个数奇偶性相同。

## 说明/提示

样例一解释：$R_1=2,R_2=0,R_3=2,C_1=C_2=2,C_3=0$。

对于所有的数据，$1\leq n\leq 100000$，$1\leq m\leq\min(n^2,500000)$。

| 子任务编号 | 附加限制 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | $m\leq 20$ | 24 |
| 2 | 如果有解，保证存在偶数解 | 24 |
| 3 | 如果有解，保证存在奇数解 | 24 |
| 4 |  | 28 |

如果有解并且你指出有解但是构造错误，你能得到 $50\%$ 的分数。

## 样例 #1

### 输入

```
3 6
1 1
1 2
2 2
3 1
3 2
3 3
```

### 输出

```
TAK
4
1 2 4 5
```

## 样例 #2

### 输入

```
9 1
1 1
```

### 输出

```
NIE
```

## 样例 #3

### 输入

```
见附件```

### 输出

```
TAK
4
1 2 10 11
```

## 样例 #4

### 输入

```
见附件```

### 输出

```
TAK
4
1 2 100001 100002
```

# 题解

## 作者：mlvx (赞：7)

### 题意

一个 $n\times n$ 的方阵，里面有 $m$ 个点，选中至少一个点，使得每行每列被选中点数相同。

---

### 分析

方格中对于行与列需要满足某种特征的题面，往往可以建图来解决。

每一行，每一列，分别对应一个编号。

例如 $(u,v)$ 处有一个点，那我们就把 $u$ 和 $v+n$ 连边。

此时我们发现，这个图是个二分图，~~虽然在本题中并没有什么用~~。

现在问题就变成了找出图的一个子图，使得其中所有点的度数的奇偶性相同。

---

环上的点的度数都是偶数，故找出环即为找出偶数解的情况。

```cpp
void dfs1(int x){
	vis[x]=1;
	for(auto[y,w]:g[x])if(!Vis[w]){
		Vis[w]=1,last[y]=x,from[x]=w;
		if(vis[y]){
			int cnt=0;puts("TAK");
			for(int tmp=last[y];tmp!=y;)++cnt,tmp=last[tmp];
			cout<<cnt+1<<'\n'<<from[y]<<' ';
			for(int tmp=last[y];tmp!=y;)cout<<from[tmp]<<' ',tmp=last[tmp];
			exit(0);
		}dfs1(y);
	}
}
```

---

不难发现图中如果没有环，那么这个图就是个森林。

由于叶子的度数是 $1$，所以所有点的度数都得是奇数。

注意到想要改变度数只能改变这个节点和其父亲的连边情况，所以从叶子节点向上进行改变即可。

```cpp
void dfs2(int x){
	vis[x]=1;
	for(auto[y,w]:g[x])if(!vis[y])dfs2(y),dp[y]||(dp[x]^=1,ans[y]=w);
}
```

---

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=5e5+10;
int n,m,u,v,vis[N<<1],from[N<<1],last[N<<1],dp[N<<1],ans[N<<1],Vis[M];vector<pair<int,int>>g[N<<1];
void dfs1(int x){
	vis[x]=1;
	for(auto[y,w]:g[x])if(!Vis[w]){
		Vis[w]=1,last[y]=x,from[x]=w;
		if(vis[y]){
			int cnt=0;puts("TAK");
			for(int tmp=last[y];tmp!=y;)++cnt,tmp=last[tmp];
			cout<<cnt+1<<'\n'<<from[y]<<' ';
			for(int tmp=last[y];tmp!=y;)cout<<from[tmp]<<' ',tmp=last[tmp];
			exit(0);
		}dfs1(y);
	}
}void dfs2(int x){
	vis[x]=1;
	for(auto[y,w]:g[x])if(!vis[y])dfs2(y),dp[y]||(dp[x]^=1,ans[y]=w);
}int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>u>>v,g[u].push_back({v+n,i}),g[v+n].push_back({u,i});
	for(int i=1;i<=(n<<1);i++)if(!vis[i])dfs1(i);
	memset(vis,0,sizeof vis);
	for(int i=1;i<=(n<<1);i++)if(!vis[i]){dfs2(i);if(!dp[i])return puts("NIE"),0;}
	puts("TAK");int cnt=0;
	for(int i=1;i<=(n<<1);i++)if(ans[i])++cnt;
	cout<<cnt<<'\n';
	for(int i=1;i<=(n<<1);i++)if(ans[i])cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：honglan0301 (赞：3)

## 题目分析

首先容易把题目抽象成图论问题。考虑对每个按钮所在的行与列连边，我们只需要选出一个边集使得所有点度数的奇偶性相同。

此时有个很好的性质是，如果图中存在环，则把任意一环上的边全选即满足要求，于是我们据此分类处理。

1. 若图中存在环，则使用 $\text{dfs}$ 随便找一个环即可，时间复杂度 $O(n)$。

2. 否则该图由若干棵树构成，此时不可能存在偶数解，故要求选出使每个点度数均为奇数的边集。

	我们对于每棵树从叶子向根依次考虑，发现每条连接 $(u,fa_u)$ 的边是否选择可由点 $u$ 子树内的情况唯一确定：令 $zt_u$ 表示连接 $(u,fa_u)$ 的边是否被选择，则有 $zt_u=\neg \bigoplus\limits_{v\in son_u} zt_v$，于是类似 $\text{dp}$ 地处理即可，时间复杂度也是 $O(n)$。
    
	注意判无解。当且仅当存在一棵树的 $zt_{root}=1$ 时无解，因为选法唯一。
    
    
## 代码

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second

int n,m,u,v,vis[200005],ins[200005],top,deg[200005];
pair <int,int> stk[200005];
vector <pair<int,int>> e[200005];
vector <int> ans;

void dfs1(int x,int frm)
{
	vis[x]=1; ins[x]=1; stk[++top]=mp(x,frm);
	for(auto i:e[x])
	{
		if(i.se==frm) continue;
		if(ins[i.fi])
		{
			ans.pb(i.se); while(1) {if(stk[top].fi==i.fi) break; ans.pb(stk[top--].se);}
			cout<<"TAK"<<endl<<ans.size()<<endl;
			for(auto i:ans) cout<<i<<" "; cout<<endl; exit(0);
		}
		else if(vis[i.fi]) continue;
		dfs1(i.fi,i.se);
	}
	ins[x]=0; top--;
}
int dfs2(int x,int frm)
{
	vis[x]=1;
	for(auto i:e[x])
	{
		if(i.se==frm) continue; deg[x]^=dfs2(i.fi,i.se);
	}
	return (!deg[x])?(ans.pb(deg[x]=frm),1):0;
}

signed main()
{
	cin>>n>>m; for(int i=1;i<=m;i++) cin>>u>>v,e[u].pb(mp(v+n,i)),e[v+n].pb(mp(u,i));
	for(int i=1;i<=2*n;i++) if(!vis[i]) dfs1(i,0); memset(vis,0,sizeof(vis));
	for(int i=1;i<=2*n;i++) if(!vis[i]) dfs2(i,0);
	for(int i=1;i<=2*n;i++) if(!deg[i]) {cout<<"NIE"<<endl; return 0;}
	cout<<"TAK"<<endl<<ans.size()<<endl;
	for(auto i:ans) cout<<i<<" "; cout<<endl;
}
```


---

## 作者：未来姚班zyl (赞：3)

## 题目大意

在一个 $n\times n$ 的网格里有 $m$ 个点可以被标记，请标记至少 $1$ 个点，使得所有行和列被标记的数的个数的奇偶性相同。

## 题目分析

太水了，建议评黄。

显然可以转化为二分图（是不是二分图都无所谓），点相当于对应的行和列有边，要选出若干条边，使得每个点的度数奇偶性相等。奇偶性可以转化为 $01$ 异或，我们把这个值称为度数。

如果有环，直接把其中一个简单环找出来，这样度数都为 $0$。

否则，原图是森林，所以选出来的边也会是森林，则叶子节点的度数为 $1$。所以所有点的度数都只能为 $1$。而对于森林的每个叶子节点，只有一条边能调整它，故对于它来讲那一条边的状态是确定的，处理好后删掉这条边，继续处理，这样一直会存在叶子节点，直到没有边，最后查一下有没有矛盾即可。可以用 dfs 轻松处理。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=1e6+5,inf=(1LL<<31)-1;
const ll llf=1e18;
using namespace std;
int n=read(),m=read(),h[N],nxt[M],to[M],cnt=1,fr[N],deg[N];
inline void add(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt,deg[b]++;
}
bool vis[N];
int s[N],tp;
inline int dfs(int x){
	vis[x]=1;
	e(x)if(vis[y]){
		if(i^fr[x]^1)return s[++tp]=i/2,s[++tp]=fr[x]/2,y;
	}else {
		fr[y]=i;
		int k=dfs(y);
		if(k==0)continue;
		if(k==-1||x==k)return -1;
		s[++tp]=fr[x]/2;
		return k;
	}
	return 0;
}
bool sta[N<<1],v[N<<1];
inline void Dfs(int x,int fa){
	v[x]=1;
	e(x)if(y^fa){
		Dfs(y,x);
		if(!sta[y])s[++tp]=i/2,sta[y]=1,sta[x]^=1;
	}
}
inline void out(){
	cout <<"TAK\n";
	cout <<tp<<'\n';
	rep(i,1,tp)cout <<s[i]<<" ";
}
signed main(){
 	for(int i=1,x,y;i<=m;i++)x=read(),y=read(),add(x,y+n),add(y+n,x);   
	rep(i,1,n<<1)if(!vis[i]){
		if(dfs(i)==-1)return out(),0;
	}
	rep(i,1,n<<1)if(!v[i])Dfs(i,0);
	rep(i,1,n<<1)if(!sta[i])return cout <<"NIE",0;
	out();
	return 0;
}
```


---

## 作者：MSavannah (赞：2)

# Description
一个 $n\times n$ 的方阵，里面有 $m$ 个按钮。

你需要按下若干个（至少一个）按钮，使得每行每列被按下的按钮个数奇偶性相同。

# Solution
构造题。

考虑建图，把每个按钮的行和列之间连一条边，即若 $(i,j)$ 位置上面有一个按钮，那么就连一条 $i\to j+n$ 的边。

这样我们的操作就转换成了，选一些边，使图上点的度数奇偶性相同。

分两种情况考虑：

1. 图上有环，直接输出环就可以，因为每个点的度数一定都是偶数
2. 如果没有环，那么图就是一个森林，考虑到叶子节点的度数一定是 1，那么此时只能让所有点的度数都是奇数。发现每个节点只能通过改变它和它父亲之间相连的边的状态，来调整其度数的奇偶性，直接 dfs 从下往上调整就可以了。

[code](https://www.luogu.com.cn/record/155453622)

---

## 作者：_Kenma_ (赞：1)

## 前言

不错的二合一题。

## 思路分析

首先套路地建出二分图：对于 $(x,y)$ 的点，连 $x \to y+n$ 的无向边，这样问题转化为选出若干条边，使得所有点的度的奇偶性相同。

发现奇数解和偶数解具有不同的性质，考虑分别处理。

### 偶数解

图上有环即可。

直接 DFS 找环判断。

### 奇数解

在没有偶数解的前提下判断。

如果图上没有环，那么图一定是一个森林。

考虑一种经典的处理方式：从叶子往上选边。

具体地，我们从叶子开始选择边，因为叶子只和它的父亲相连，所以这些连接叶子的边一定要选，然后可以把叶子删去，这样有一些父亲就成了新的叶子，继续处理就行。

直接 DFS 处理就行。

如果一个点是根节点，并且它需要和父亲选边，那么一定无解。

把两种情况拼一起就做完了。

注意找环时的细节。

总体复杂度 $O(n)$。

## 代码实现

写的比较丑。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u[500005],v[500005];
int head[200005],nxt[1000005],targetx[1000005],targetw[1000005],tot=1;
void add(int x,int y,int w){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	targetx[tot]=y;
	targetw[tot]=w;
}
bool vis1[200005],vis2[200005],vis3[1000005],vis4[200005],flag;
stack<int> s;
inline void dfs1(int x,int edge){
	if(flag) return;
	vis1[x]=vis2[x]=1;
	s.push(x);
	for(int i=head[x];i;i=nxt[i]){
		int y=targetx[i],w=targetw[i]; 
		if(vis3[w]) continue;
		if(vis2[y]){
			flag=true;
			while(s.top()!=y){
				vis4[s.top()]=true;
				s.pop();
			}
			vis4[y]=1;
			vis3[w]=1;
			if(flag){
				cout<<"TAK"<<'\n';
				int cnt=0;
				for(int j=1;j<=m;j++){
					if(vis3[j] && vis4[u[j]] && vis4[v[j]+n]){
						cnt++;
					}
				}
				cout<<cnt<<'\n';
				for(int j=1;j<=m;j++){
					if(vis3[j] && vis4[u[j]] && vis4[v[j]+n]){
						cout<<j<<' ';
					}
				}
				exit(0);
		    }
		}
		if(vis1[y]) continue;
		vis3[w]=1;
		dfs1(y,w);
		vis3[w]=0;
	}
	vis2[x]=0;
	s.pop();
}
int val[200005];
inline void dfs2(int x,int fa,int edge){
	vis1[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		int y=targetx[i],w=targetw[i];
		if(y==fa) continue;
		dfs2(y,x,w); 
	}
	if(!val[x] && !fa){
		cout<<"NIE";
		exit(0);
	}
	if(!val[x]){
		val[x]^=1;
		val[fa]^=1;
		vis3[edge]=1;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		add(u[i],v[i]+n,i);
		add(v[i]+n,u[i],i); 
	}
	for(int i=1;i<=n+n;i++){
		if(!vis1[i]){
			dfs1(i,0);
		}
	}
	memset(vis3,0,sizeof(vis3));
	memset(vis1,0,sizeof(vis1));
	for(int i=1;i<=n;i++){
		if(!vis1[i]){
			dfs2(i,0,0);
		} 
	}
	cout<<"TAK"<<'\n';
	int cnt=0;
	for(int i=1;i<=m;i++){
		if(vis3[i]){
			cnt++;
		}
	}
	cout<<cnt<<'\n';
	for(int i=1;i<=m;i++){
		if(vis3[i]){
		    cout<<i<<' ';
		}
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：0)

神秘构造题。

容易想到按钮 $(u,v)$ 看成 $u$ 向 $v+n$ 连边。你现在要选择一个非空边集 $S$，使得每个点在 $S$ 中的度数奇偶性相等。

度数都为偶数时，你可以找一个环，环上所有点度数都为 $2$，合法。如果找不到环容易归纳证明度数不可能全为偶数。

度数都为奇数时，现在图没有环，是一个森林。每棵树是独立的，对一棵树进行考虑。首先叶子节点度数为 $1$，它到父亲的边必选。知道了下面的边是否选后，就可以递推出当前点到父亲的边是否选。如果最后根节点度数为偶数则无解。

```cpp
int n,m,id=1,tp,uu[N],vv[N],hd[N],vs[N],rt[N],f[N]; pii st[N]; vi as; vpii g[N];
struct EDGE {int to,w,ne;} e[N*5];
il void add(int u,int v,int w) {e[++id]={v,w,hd[u]},hd[u]=id;}
void dfs1(int u,int fr) {
	vs[u]=1,st[++tp]={u,e[fr].w};
	for(int i=hd[u],v;i;i=e[i].ne) if(i^fr^1)
		if(!vs[v=e[i].to]) g[u].pb({v,e[i].w}),dfs1(v,i);
		else {
			puts("TAK"),as.pb(e[i].w);
			for(;tp&&st[tp].fir!=v;tp--) as.pb(st[tp].sec);
			wr(as.size(),"\n"); for(int x:as) wr(x," "); puts(""),exit(0);
		}
	tp--;
}
void dfs2(int u) {
	for(auto [v,w]:g[u]) {
		dfs2(v);
		if(!f[v]) f[u]^=1,as.pb(w);
	}
}
void QwQ() {
	n=rd(),m=rd();
	for(int i=1;i<=m;i++) uu[i]=rd(),vv[i]=rd(),add(uu[i],vv[i]+n,i),add(vv[i]+n,uu[i],i);
	for(int i=1;i<=n;i++) if(!vs[i]) rt[i]=1,dfs1(i,0);
	for(int i=1;i<=n;i++) if(rt[i]) {
		dfs2(i);
		if(!f[i]) puts("NIE"),exit(0);
	}
	puts("TAK"),wr(as.size(),"\n"); for(int x:as) wr(x," "); puts("");
}
```

---

## 作者：CatFromMars (赞：0)

可爱小构造。

既然是单独要求“每行和每列的度数相同”，行和列是相对独立的，不妨按照图论的套路，将每一行和每一列分别看成一个点，每一个按钮看成“行点”和“列点”之间的连边。问题转化成：选择一个非空边集，使得 $2n$ 个点的度数的奇偶性相同。

只有两种情况：都是奇数和都是偶数。

都是偶数的情况：很显然只需要求出一个环，将环上的边都选择即可。

如果都是偶数的情况无法构造，说明图是一棵树或一个森林。此时要求每个点的度数为奇数。由于叶子节点只有一条边与之相连，这些叶子节点到父亲的边一定要保留。删除所有叶子，对于新的“叶子”，我们则需要根据它到儿子被保留的边的数量奇偶性考虑是否保留到父亲的边……以此类推。

更形式化的说，对于一棵树，假如我们已经求出来了每个点的儿子数 $d_i$，根节点为 $r$。除了 $r$ 外每个点的实际度数为 $(d_i + 1)$。按照从叶子到其它点的拓扑序，实际上就是按照在树上深度从大到小的顺序依次处理每个点 $u$。

- $u$ 是叶子。
  - 考虑 $u$ 点实际度数 $(d_u + 1)$。
  - $(d_u + 1)$ 为奇数，保留与父亲连边。
  - $(d_u + 1)$ 为偶数，删除与父亲连边，记父亲为 $f$，$d_f\gets d_u$，代表删除了这条边。

- $u = r$ 是根。
  - 考虑 $r$ 的实际度数 $d_r$。
  - $d_r$ 为偶数，无解。
  - $d_r$ 为奇数，则有解。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5, M = 5e5;
struct node {
	int to, ind;
	node(int T, int I) {
		to = T, ind = I;
	}
};
vector <node> gra[N + 10];

bool vis[N + 10], deg[N + 10];
int fat[N + 10], tf[N + 10], st = 0, ed = 0, dep[N + 10];
int extra = 0;
void dfs(int u, int fa) {
	fat[u] = fa;
	vis[u] = 1;
	dep[u] = dep[fa] + 1;
	for(int i = 0; i < gra[u].size(); i++) {
		int v = gra[u][i].to, ind = gra[u][i].ind;
		if(v == fa) continue;
		if(!vis[v]) {
			tf[v] = ind;
			deg[u] ^= 1;
			dfs(v, u);
		}
		else {
			extra = ind;
			st = u;
			ed = v;
			return ;
		}
	}
}
int n, m;
bool bri[M + 10];
struct piar {
	int x, dep;
} Q[N + 10];
bool cmp(piar &x, piar &y) {
	return x.dep > y.dep; 
}
void work() {
	for(int i = 1; i <= 2 * n; i++)
		Q[i] = (piar){i, dep[i]};
	sort(Q + 1, Q + 2 * n + 1, cmp);
	
	for(int i = 1; i <= 2 * n; i++) {
		int u = Q[i].x;
		if(!fat[u]) {
			if(deg[u]) continue;
			else {
				cout << "NIE\n";
				return ;
			}
		}
		else {
			if(!deg[u]) bri[tf[u]] = 1;
			else deg[fat[u]] ^= 1;
		}
	}
	
	int cnt = 0;
	for(int i = 1; i <= m; i++)
		cnt += bri[i];
	cout << "TAK\n" << cnt << "\n";
	for(int i = 1; i <= m; i++)
		if(bri[i]) cout << i << ' ';
} 
int main() {
	cin >> n >> m;
	for(int i = 1, x, y; i <= m; i++) {
		cin >> x >> y;
		gra[x].push_back(node(y + n, i));
		gra[y + n].push_back(node(x, i));
	}
	for(int i = 1; i <= 2 * n; i++)
		if(!vis[i]) {
			dfs(i, 0);
			if(st && ed) {
				if(dep[st] < dep[ed]) swap(st, ed);
				cout << "TAK\n" << dep[st] - dep[ed] + 1 << "\n";
				while(1) {
					if(st == ed) {
						cout << extra << ' ';
						return 0;
					}
					cout << tf[st] << ' ';
					st = fat[st];
				}
			}
		}
	
	work();
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/P9923)

**题目大意**

> 给定 $n\times n$ 网格上的 $m$ 个点，将其中一些点（至少一个）染黑，使得每行每列黑色格子数奇偶性相同。
>
> 数据范围：$n\le 10^5,m\le 5\times 10^5$。

**思路分析**

考虑将每行每列拆点建图，那么每个点可以看成两个点之间的一条边，那么我们就是要选出一个非空边集使得在这个边集中每个点的度数奇偶性都相同。

先考虑每个点度数都是偶数，那么选出的边很显然一定会形成若干个欧拉回路，由于度数为 $0$ 也合法，因此只要某个连通块能任意选出一个环即可。

剩余的情况一定是森林，此时我们要求每个点度数均为偶数，自下而上构造，用每个点到父亲的边调整，能得到唯一的方案（或得不到方案）。

时间复杂度 $\mathcal O(n+m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int n,m,fa[MAXN*2];
int hd[MAXN*2],ec=1,to[MAXN*10],lst[MAXN*10];
bool vis[MAXN*2];
void adde(int u,int v) { to[++ec]=v,lst[ec]=hd[u],hd[u]=ec; }
void dfs1(int u) {
	vis[u]=true;
	for(int i=hd[u];i;i=lst[i]) if(i!=fa[u]){
		int v=to[i];
		if(!vis[v]) fa[v]=i^1,dfs1(v);
		else {
			vector <int> wys{i};
			for(int x=u;x!=v;x=to[fa[x]]) wys.push_back(fa[x]);
			cout<<"TAK\n"<<wys.size()<<"\n";
			for(int z:wys) cout<<z/2<<" ";
			cout<<"\n";
			exit(0);
		}
	}
}
bool deg[MAXN*2];
vector <int> wys;
void dfs2(int u) {
	vis[u]=true;
	for(int i=hd[u];i;i=lst[i]) if(i^fa[u]) dfs2(to[i]);
	if(fa[u]&&!deg[u]) {
		deg[to[fa[u]]]^=1,wys.push_back(fa[u]),deg[u]^=1;
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;++i) {
		cin>>u>>v,adde(u,v+n),adde(v+n,u);
	}
	for(int i=1;i<=2*n;++i) if(!vis[i]) dfs1(i);
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=2*n;++i) if(!vis[i]) {
		dfs2(i);
		if(!deg[i]) return cout<<"NIE\n",0;
	}
	cout<<"TAK\n"<<wys.size()<<"\n";
	for(int z:wys) cout<<z/2<<" ";
	cout<<"\n";
	return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
还是比较偏套路的题。

注意到一个按钮只会改变行列坐标的次数的奇偶性，所以考虑将每一行每一列看作一个点，按钮就是两个点之间的无向边，这样就得到了 $2n$ 个点，$m$ 条边的无向图。题目意思就转化为，每次选定一些边，其他边删去，使得其每个节点的度数的奇偶性相同。

再来分别考虑度数是奇数还是偶数。

如果所有度数都是奇数的话，那么显然一个连通块内，如果节点个数为奇数个，则不可能成立。因为总度数一定为偶数，然而奇数乘以奇数为奇数，故不成立。

那么还可以证明，如果连通块节点个数为偶数个，则一定可以成立。考虑取原连通块的任意生成树，取任意点为根节点。那么所得的树中，从叶节点往上开始考虑，叶节点与父亲的边必须选取，之后再看，若一个节点与儿子连边为奇数条，则不用选取与父亲的边，反之。因为总结点数为偶数个，所以根节点度数也为奇数。

如果所有度数都是偶数的话，则必须有一个联通块中有环，这很好想。故只需选取那个环即可。

两者结合便是最后的答案。
### Code:

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,m;
vector<pair<int,int>> g[N];
bool vis[N];
bool ok=0,stop=0;
int what,dp[N];
vector<int> ans;
void dfs_odd(int x,int from){
	vis[x]=1;
	for(auto i:g[x]){
		if(i.first==from) continue;
		if(vis[i.first]) continue;
		dfs_odd(i.first,x);
		if(dp[i.first]%2==0){
			ans.push_back(i.second);
			dp[x]++;
		}
	}
}
void dfs_even(int x,int from){
	vis[x]=1;
	for(auto i:g[x]){
		if(i.first==from) continue;
		if(vis[i.first]){
			ok=1;
			what=i.first;
			ans.push_back(i.second);
			return ;
		} 
		dfs_even(i.first,x);
		if(x==what){
			stop=1;
			ans.push_back(i.second);
		} 
		if(stop) return ;
		if(ok){
			ans.push_back(i.second);
			return ;
		}
	}
}
bool odd(){
	ans.clear();
	memset(vis,0,sizeof vis);
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		dfs_odd(i,-1);
		if(dp[i]%2==0) return 0;
	}
	return 1;
}
bool even(){
	ans.clear();
	memset(vis,0,sizeof vis);
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		dfs_even(i,-1);
		if(ok) return 1;
	}
	return 0;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		g[x].push_back({y+n,i});
		g[y+n].push_back({x,i}); 
	}
	n<<=1;
	if(odd()){
		cout<<"TAK\n";
		cout<<ans.size()<<'\n';
		for(auto i:ans){
			cout<<i<<' ';
		}
		return 0;
	}
	if(even()){
		cout<<"TAK\n";
		cout<<ans.size()<<'\n';
		for(auto i:ans){
			cout<<i<<' ';
		}
		return 0;	
	}
	cout<<"NIE";
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

这个题被 ZR 出烂了，结果我还跑过去想了半天的异或哈希。有没有人教教如何分析异或哈希的错误性？？我分析后感觉错误率挺小的，但是交上去寄寄了。

考虑建立一个二分图，边 $u \to v$ 相当于 $(u,v)$ 格子上有灯泡。于是只需要选边，使得二分图每个点的度数都是奇数或者都是偶数。

如果有环，那么选这个环就搞定了。

否则是一个森林。

那么这个问题就相当典了：注意到此时顶点不可能有偶数度数（考虑叶子结点并且归纳），于是每个点只能有奇数度数。从低往上归纳的考虑，每次可以用 $u$ 和 $u$ 父亲之间连边状态调整 $u$ 度数的奇偶性。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=200000+10,MAXM=500000+10;
int n,m,vis[MAXN],fa[MAXN],op[MAXN],dep[MAXN],fid[MAXN],deg[MAXN],chk[MAXN];
vector<pair<int,int>> G[MAXN];
void dfs(int u,int f) {
	vis[u]=1,fa[u]=f,dep[u]=dep[f]+1;
	for(auto pr:G[u]) {
		int v=pr.first,id=pr.second;
		if(v==f) continue ;
		if(vis[v]&&dep[v]<dep[u]) {
			cout<<"TAK\n";
			vector<int> ans;
			int tpos=u;
			while(tpos!=v) ans.push_back(fid[tpos]),tpos=fa[tpos];
			ans.push_back(id);
			cout<<ans.size()<<'\n';
			for(auto id:ans) cout<<id<<' ';
			exit(0);
		}
		if(!vis[v]) fid[v]=id,dfs(v,u);
	}
	return ;
}
void cons(int u,int f) {
	vis[u]=1,fa[u]=f;
	for(auto pr:G[u]) {
		int v=pr.first,id=pr.second;
		if(v==f) continue ;	
		cons(v,u);
		if(deg[v]==0) deg[u]^=1,deg[v]=0,chk[v]=id;
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;ffor(i,1,m) {int x,y;cin>>x>>y,G[x].push_back({y+n,i}),G[y+n].push_back({x,i});}
	ffor(i,1,n+n) if(!vis[i]) dfs(i,0);	
	memset(vis,0,sizeof(vis));
	ffor(i,1,n+n) if(!vis[i]) {cons(i,0);if(deg[i]==0) return cout<<"NIE",0;}
	cout<<"TAK\n"; vector<int> ans;
	ffor(i,1,n+n) if(chk[i]) ans.push_back(chk[i]);
	cout<<ans.size()<<'\n';
	for(auto id:ans) cout<<id<<' '; 
	return 0;
}
```

---

