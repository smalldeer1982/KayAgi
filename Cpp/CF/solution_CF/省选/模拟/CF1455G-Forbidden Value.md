# Forbidden Value

## 题目描述

### 题意简述
已知初始值$x=0$，给定下面2种命令：
1. `set` $y$ $v$，令$x=y$，或花费$v$元钱删除该命令；
2. `if` $y$ ... `end`，如果$x==y$，执行`if...end`中的命令，否则跳过该`if...end`。

你需要使用最少的花费，使得无论运行到哪里，都有$x \neq s$。

## 样例 #1

### 输入

```
5 1
set 1 10
set 2 15
if 2
set 1 7
end```

### 输出

```
17```

## 样例 #2

### 输入

```
7 2
set 3 4
if 3
set 10 4
set 2 7
set 10 1
end
set 4 2```

### 输出

```
4```

## 样例 #3

### 输入

```
9 200
if 0
set 5 5
if 5
set 100 13
end
if 100
set 200 1
end
end```

### 输出

```
1```

## 样例 #4

### 输入

```
1 10
set 1 15```

### 输出

```
0```

# 题解

## 作者：EuphoricStar (赞：9)

小清新动态开点线段树优化 dp 题。

首先题目中的 `if` 嵌套看起来就很烦，可以考虑建树，外面再套一层大的 `if 0 ... end`，这样就将本题转化成一个树上问题。

考虑树形 dp。设 $f_{u,i}$ 表示 **从结点 $u$ 出来时，$x$ 的值是 $i$ 的最少花费。**

不难转移：

- 对于 `set` 命令：

$\begin{cases} f_{u,y} \gets \min\limits_{i}{f_{u,i}} \\ f_{u,i} \gets f_{u,i} + v & i \neq y \end{cases}$

- 对于 `if` 命令：

$\begin{cases} f_{u,y} \gets f_{u,y} + f_{v,y} \\ f_{u,i} \gets \min(f_{u,i}, f_{u,y} + f_{v,i}) & i \neq y \end{cases}$

注意转移时 dp 值都是同时计算。

直接暴力转移显然是 $O(n^2)$ 的，但是我们发现对于每个结点 $u$，真正有用的状态只有 $u$ 子树内 $y$ 的取值。可以考虑对每个结点开一个动态开点线段树，存 $u$ 的所有状态。转移时只需单点修改、整体加和单点查询，对于 `if` 命令大力线段树合并即可。时间复杂度 $O(n \log n)$。

`map` + 启发式合并的做法看不懂，我太菜了。

[code](https://codeforces.com/contest/1455/submission/174563133)

---

## 作者：cyffff (赞：9)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1455G)

## 题意
有 $n$ 行指令，你需要依次执行这些指令。

初始时，你有一个变量 $x=0$，共有三种指令：
1. `set y v`，令 $x\gets y$，或用 $v$ 的代价删去这条指令；
2. `if y`，如果 $x=y$，则执行其范围内的指令，否则跳过其范围内的指令；
3. `end`，用于声明上一个还未声明范围的 `if` 指令的范围。

给一个数 $s$，求用最少的代价使得没有一个时刻 $x=s$。

$n\le 2\times 10^5$，$s,y\le 2\times 10^5$。
## 思路
考虑将指令看成树形结构，将每条指令看为直属的 `if` 指令的子节点。这样子是一个森林，在最外层补上 `if 0 end` 将其转成树。

考虑树形 dp，先将所有 `set` 撤销，代价挂在父节点上，令 $dp_{i,j}$ 表示执行 $i$ 子树内的指令，最终 $x=j$ 能撤销的最多代价。

直接做是很不优秀的，我们可以发现 $j$ 的取值只有 $i$ 子树内 $y$ 的取值范围，并且 $i$ 的取值范围是所有子节点取值范围的并，于是可以考虑启发式合并。

对每个结点开 `map` 和 `multiset` 分别存储 $dp$ 数组和快速修改计算 $dp_{i,k}$ 的最小值。注意在启发式合并将父节点合并到子节点时子节点的 $dp$ 值都未加上其兄弟结点的贡献，开个辅助数值记录全局加 tag 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=2e5+10;
int n,s,res,f[N],t[N],v[N],p[N];
ll d[N];//子节点撤销价格之和 
vector<int>a[N];
map<int,ll>dp[N];//可以撤销的贡献 
multiset<ll>mn[N];
inline void dfs(int x){
	mn[x].insert(dp[x][p[x]]=0);
	for(auto to:a[x]){
		if(t[to]==1){
			if(p[to]!=s){
				if(dp[x].count(p[to])){
					ll tmp=dp[x][p[to]];
					dp[x][p[to]]=(*mn[x].begin())-v[to];
					mn[x].erase(mn[x].find(tmp));
				}else{
					dp[x][p[to]]=(*mn[x].begin())-v[to];
				}
				mn[x].insert(dp[x][p[to]]);
			}
			d[x]+=v[to];
		}else if(dp[x].count(p[to])){
			dfs(to);
			ll tmp=dp[x][p[to]]+d[to];
			if(dp[to].size()<=dp[x].size()){
				for(auto it:dp[to]){
					int val=it.first;
					ll cst=it.second;
					if(!dp[x].count(val)) dp[x][val]=tmp+cst;
					else{
						mn[x].erase(mn[x].find(dp[x][val]));
						if(val==p[to]) dp[x][val]=tmp+cst;
						else dp[x][val]=min(dp[x][val],tmp+cst);
					}
					mn[x].insert(dp[x][val]);
				}
			}else{
				d[x]+=tmp;//全体 +tmp 不好处理 加在 d 上
				for(auto it:dp[x]){
					int val=it.first;
					ll cst=it.second;
					if(!dp[to].count(val)) dp[to][val]=-tmp+cst;
					else{
						mn[to].erase(mn[to].find(dp[to][val]));
						if(val!=p[to]) dp[to][val]=min(dp[to][val],-tmp+cst);
					}
					mn[to].insert(dp[to][val]);
				}
				swap(dp[x],dp[to]);
				swap(mn[x],mn[to]);
			}
		}
	}
}
int main(){
	n=read(),s=read();
	for(int i=1;i<=n;i++){
		char opt=getc();
		if(opt=='s'){
			a[res].push_back(i);
			t[i]=1,p[i]=read(),v[i]=read();
		}else if(opt=='i'){
			p[i]=read();
			a[res].push_back(i);
			t[i]=2,f[i]=res,res=i;
		}else{
			res=f[res];
			getc(),getc();
		}
	}
	dfs(0);
	write(d[0]+(*mn[0].begin()));
	flush();
}
```
再见 qwq~

---

## 作者：ywy_c_asm (赞：7)

对整个嵌套if的程序结构建树，叶子节点对应一个set语句，非叶子结点对应一个if结构（其子树为if内套的东西）。整个程序可以相当于套在一个if 0中，它是根节点。

那么我们考虑一段套在某个$if$ $x_0$中的程序（即一棵子树），这相当于一个函数，**输入是已知的，就是$x_0$**（这个性质很关键），有唯一一个输出，那么套路的令$dp[i][j]$为，只执行子树i中的程序，输出为j的最小代价。

显然这个不能直接做，不难想到可以把这个dp做到可合并的动态开点线段树里（即整体dp），下标为$j$，支持打加法标记以及取最小值。对于根的某个为$set$ $x_0$的儿子，让线段树上$x_0$处更新为整体最小值（执行这条语句），再让除了$x_0$的地方加上语句代价（不执行这条语句）。对于$if$ $x_0$的儿子，把自己原来的$dp[x_0]$整体加到儿子的线段树上（即要执行子树内的程序必须让变量为$x_0$），再与儿子的线段树合并，让对应位取min即可。$O(n\log n)$

标算用的是map启发式合并，跟线段树合并道理大概差不多。

上代码~

```cpp
#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cstdlib>
#define ll long long
#define lim 200000
#define N 200010
#define M 9000000
#define inf 1234567890987654ll
#define add_s(_a,_b) _a=min(inf,_a+_b)
#define up(_o) minn[_o]=min(minn[lef[_o]],minn[rgh[_o]])
using namespace std;
namespace ywy{
	inline int get(){
		int n=0;char c;while((c=getchar())||23333)if(c>='0'&&c<='9')break;
		n=c-'0';while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10+c-'0';else return(n);
		}
	}
	inline int sget(){
		char c;while((c=getchar())||23333)if(c>='a'&&c<='z')break;
		if(c=='s'){
			getchar();getchar();return(1);
		}if(c=='i'){
			getchar();return(2);	
		}getchar();getchar();return(3);
	}ll minn[M],adds[M];int lef[M],rgh[M],dp[N],gn=1,gtree=1;vector<int> vec[N];
	int val[N],cost[N];
	inline void down(int tree){
		ll x=adds[tree];adds[tree]=0;
		add_s(minn[lef[tree]],x);add_s(adds[lef[tree]],x);
		add_s(minn[rgh[tree]],x);add_s(adds[rgh[tree]],x);
	}
	void dopt(int l,int r,int &tree,int pt,void (*p)(int)){
		if(!tree)tree=gn,gn++,minn[tree]=inf;
		if(l==r){p(tree);return;}int mid=(l+r)>>1;down(tree);
		if(pt<=mid)dopt(l,mid,lef[tree],pt,p);else dopt(mid+1,r,rgh[tree],pt,p);up(tree);
	}
	int united(int l,int r,int a,int b){
		if(!(a&&b))return(a|b);if(l==r){
			minn[a]=min(minn[a],minn[b]);return(a);
		}down(a);down(b);int mid=(l+r)>>1;lef[a]=united(l,mid,lef[a],lef[b]);
		rgh[a]=united(mid+1,r,rgh[a],rgh[b]);up(a);return(a);
	}int danger,stk[N];ll upd;
	void none(int x){minn[x]=0;}
	void setp(int x){minn[x]=upd;}
	void update(int x){minn[x]=min(minn[x],upd);}
	ll gpt(int l,int r,int tree,int pt){
		if(l==r)return(minn[tree]);down(tree);int mid=(l+r)>>1;
		if(pt<=mid)return(gpt(l,mid,lef[tree],pt));return(gpt(mid+1,r,rgh[tree],pt));	
	}
	void dfs(int pt){
		dopt(0,lim,dp[pt],val[pt],none);
		for(register int i=0;i<vec[pt].size();i++){
			int me=vec[pt][i];if(cost[me]==-1){
				ll x=gpt(0,lim,dp[pt],val[me]);
				if(x<inf){
					dfs(me);minn[dp[me]]+=x;adds[dp[me]]+=x;
					upd=inf;dopt(0,lim,dp[pt],val[me],setp);
					dp[pt]=united(0,lim,dp[pt],dp[me]);	
				}
			}else{
				ll m=minn[dp[pt]];adds[dp[pt]]+=cost[me];minn[dp[pt]]+=cost[me];
				if(val[me]!=danger){
					upd=m;dopt(0,lim,dp[pt],val[me],update);	
				}
			}
		}
	}
	void ywymain(){
		minn[0]=inf;int n=get(),sp=1;danger=get();
		for(register int i=1;i<=n;i++){
			int op=sget();if(op==1){
				int me=gtree;gtree++;val[me]=get();cost[me]=get();
				vec[stk[sp-1]].push_back(me);
			}if(op==2){
				int me=gtree;gtree++;val[me]=get();cost[me]=-1;
				vec[stk[sp-1]].push_back(me);stk[sp]=me;sp++;
			}if(op==3)sp--;
		}dfs(0);cout<<minn[dp[0]]<<endl;
	}
}
signed main(){
	ywy::ywymain();return(0);	
}
```

---

## 作者：xfrvq (赞：1)

设 $f_{i,j}$：经过第 $i$ 行后 $x=j$ 的最小代价。

操作 `set y v`：$f_{i,y}\gets\min\{f_{i-1,*}\},f_{i,j\ne y}\gets f_{i,j}+v$

操作 `if y`：$f_{i,y}\gets f_{i-1,y},f_{i,j\ne y}\gets+\infty$

操作 `end`：设 $p$ 为**对应 `if` 操作的上一行**，$f_{i,j}\gets\min\{f_{i-1,j},f_{p,j}\}$。

直接线段树合并，每一行转移完都 $f_{i,s}\gets+\infty$。

区别于其它题解的是，用栈维护匹配的 `if` 和 `end` 操作，避免显示建树，比较方便。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 5;

int n,V,stk[N],tp;
char o[10];

#define mid ((L + R) / 2)

int rt[N],cnt; ll t[N * 50];
struct node{ int lc,rc; ll v; } T[N * 50];

void add(int &i,ll x){ if(i) t[i] += x,T[i].v += x; }

void psd(int i){ if(t[i]) add(T[i].lc,t[i]),add(T[i].rc,t[i]),t[i] = 0; }

void upd(int p,ll x,int &i,int L = 1,int R = 2e5){
	T[++cnt] = T[i],t[cnt] = t[i],i = cnt;
	if(L == R) return T[i].v = x,void();
	psd(i);
	p <= mid ? upd(p,x,T[i].lc,L,mid) : upd(p,x,T[i].rc,mid + 1,R);
	T[i].v = min(T[T[i].lc].v,T[T[i].rc].v);
}

ll qry(int p,int i,int L = 1,int R = 2e5){
	if(L == R) return T[i].v;
	psd(i);
	return p <= mid ? qry(p,T[i].lc,L,mid) : qry(p,T[i].rc,mid + 1,R);
}

int mrg(int i,int j,int L = 1,int R = 2e5){
	if(!i || !j) return i + j;
	if(L == R) return T[i].v = min(T[i].v,T[j].v),i;
	psd(i),psd(j);
	T[i].lc = mrg(T[i].lc,T[j].lc,L,mid);
	T[i].rc = mrg(T[i].rc,T[j].rc,mid + 1,R);
	return T[i].v = min(T[T[i].lc].v,T[T[i].rc].v),i;
}

int main(){
	scanf("%d%d",&n,&V),++V;
	T[0].v = 1e18,add(rt[0],1e18),upd(1,0,rt[0]);
	for(int i = 1,x,y;i <= n;++i){
		scanf("%s",o);
		if(o[0] == 's'){
			scanf("%d%d",&x,&y),++x,rt[i] = rt[i - 1];
			upd(x,T[rt[i]].v - y,rt[i]),add(rt[i],y);
		} else if(o[0] == 'i'){
			scanf("%d",&x),++x,stk[++tp] = i - 1;
			add(rt[i],1e18);
			upd(x,qry(x,rt[i - 1]),rt[i]);
			upd(x,1e18,rt[i - 1]);
		} else rt[i] = mrg(rt[i - 1],rt[stk[tp--]]);
		upd(V,1e18,rt[i]);
	}
	printf("%lld\n",T[rt[n]].v);
	return 0;
}
```

---

## 作者：pitiless0514 (赞：1)

## Statement

题目写的很清楚了，看题目的翻译吧。

## Solution

考虑 `if` 指令形成了一个嵌套关系，是一个层层包含的过程。

于是可以将每个 `if` 指令与被他包含的指令之间连边，然后在开头加上一个指令 `if 0`，这样，我们就将题目所示的关系建成了一颗树。

我们现在希望的是，删除某些 `set` 操作，然后使得最终遍历这个树并执行对应的操作后，任意时刻都不会使 $x= s$。

不难发现，从任意一棵树开始执行操作，最终从这个树中操作结束后，得到的值 $x$，一定为子树中的某个 `set y v` 的 $v$。

注意到最后得到某个数 $j$ 且中途不出现 $x = s$ 代表着操作的结束，根据这个在树上做一个 dp，设 $dp_{i,j}$ 表示在 $i$ 的子树中，删除若干操作后最后得到的 $x = j$ 的最小代价。

每次假如在树上碰到了叶子节点也就是 `set y v` 操作的时候，对于 $j \neq y$ 的全部都要加上值 $v$，对于 $y$ 在特判一下 $y \neq s$，如果 $y$ 等于 $s$ 的话，将其设为 $\infty$，否则选择 $j \neq y$ 的最小的一个值 $dp_{i,j}$ 然后更新 $dp_{i,y}$ 即可。

假如碰到了一个非叶子节点也就是 `if y` 操作的时候，首先需要判断一下是否能执行 $y$ 操作，如果能的话，首先递归处理儿子子树内的答案，之后对儿子 $dp_{to,j}$ 全体加上 $dp_{i,j}$ 表示执行的前置代价，再将 $dp_{i, y}$ 的值设为 $dp_{to, y}$，因为此时会要考虑子节点的贡献，之后对于其他的 $j$，将 $dp_{i,j}$ 与 $dp_{to, j}$ 对应取 $\min$ 即可。

不难发现这个是一个整体 $dp$ 的过程，于是可以考虑对每个点开一颗动态开点值域线段树进行优化，然后算子节点对父节点的贡献的时候直接线段树合并即可，复杂度 $O(n \log n)$。

当然，也可以考虑使用启发式合并计算子节点对父节点的贡献，因为中途递归子节点的时候需要给子节点全局加上某个值 $val$，此时需要在合并中对连通块维护懒惰标记来存储 $val$，然后合并的时候如果是当前节点大，那么儿子直接暴力加 $val$，不用管了，如果是当前儿子大，那么对于当前节点中每个点先 $-dp_{i,j}$，然后全局加上一个 $dp_{i,j}$ 就好了，而其他查询最小的值，额外再开一个 `multiset` 即可维护，复杂度 $O(n\log^2 n)$。

代码实现的是整体 $dp$ 的代码。

```cpp
// 德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱
// 德丽莎的可爱在于德丽莎很可爱，德丽莎为什么很可爱呢，这是因为德丽莎很可爱！
// 没有力量的理想是戏言，没有理想的力量是空虚
#include <bits/stdc++.h>
#define LL long long
#define int long long
using namespace std;
char ibuf[1 << 15], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 1 << 15, stdin), p1==p2) ? EOF : *p1++)
inline int read() {
  char ch = getchar();  int x = 0, f = 1;
  while (ch < '0' || ch > '9')  {  if (ch == '-')  f = -1;  ch = getchar();  }
  while (ch >= '0' && ch <= '9')  x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  return x * f;
}
void print(LL x) {
  if (x > 9)  print(x / 10);
  putchar(x % 10 + '0');
}
template<class T> bool chkmin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool chkmax(T &a, T b) { return a < b ? (a = b, true) : false; }
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define repd(i, l, r) for (int i = (l); i >= (r); i--)
#define REP(i, l, r)  for (int i = (l); i < (r); i++)
bool o1;
const int N = 2e5 + 5, lim = 2e5, inf = 2e17;
int n, S, num, nex[N], first[N], v[N];
int st[N], tp;
struct node {  int id, x, y;  } a[N];
vector <int> ver[N];
int rt[N * 19], lc[N * 19], rc[N * 19], s[N * 19], tot, tag[N * 19];
void pushup(int p) {
  s[p] = min(s[lc[p]], s[rc[p]]);
}
void gettag(int p,int val) {
  s[p] += val;
  tag[p] += val;
}
void pushdown(int p) {
  if (!tag[p])  return;
  if (lc[p])  s[lc[p]] += tag[p], tag[lc[p]] += tag[p];
  if (rc[p])  s[rc[p]] += tag[p], tag[rc[p]] += tag[p];
  tag[p] = 0;
}
void change(int &p,int l,int r,int pos,int val) {
  if (!p)  p = ++tot;
  if (l == r) { s[p] = val;  return;   }
  pushdown(p);
  int mid = (l + r) >> 1;
  if (pos <= mid)  change(lc[p], l, mid, pos, val);
  else  change(rc[p], mid + 1, r, pos, val);
  pushup(p);
}
int ask(int p,int l,int r,int pos) {
  if (!p)  return inf;
  if (l == r)  return s[p];
  pushdown(p);
  int mid = (l + r) >> 1;
  if (pos <= mid)  return ask(lc[p], l, mid, pos);
  else  return ask(rc[p], mid + 1, r, pos);
}
int merge(int x,int y,int a,int b) {
  if (!x || !y)  return x + y;
  int nowrt = ++tot;
  if (a == b) {
    s[nowrt] = min(s[x], s[y]);
    return nowrt;
  }
  pushdown(x);
  pushdown(y);
  int mid = (a + b) >> 1;
  lc[nowrt] = merge(lc[x], lc[y], a, mid);
  rc[nowrt] = merge(rc[x], rc[y], mid + 1, b);
  pushup(nowrt);
  return nowrt;
}
int cnt = 0;
void dfs(int x) {
  change(rt[x], 0, lim, a[x].x, 0);
  for (auto to : ver[x]) {
    if (a[to].id == 1) {
      int now = s[rt[x]];
      gettag(rt[x], a[to].y);
      if (a[to].x != S)  change(rt[x], 0, lim, a[to].x, now);
      else  change(rt[x], 0, lim, a[to].x, inf);
    } else if (a[to].id == 2) {
      int val = ask(rt[x], 0, lim, a[to].x);
      if (val != inf) {
        dfs(to);
        gettag(rt[to], val);
        change(rt[x], 0, lim, a[to].x, inf);
        rt[x] = merge(rt[x], rt[to], 0, lim);
      }
    }
  }
}
bool o2;
void solve() {
  // cout << (&o2 - &o1) * 1.0 / 1024 / 1024 << "\n";
  cin >> n >> S;
  st[0] = n + 1;
  rep (i, 1, n) {
    string it ; 
    cin >> it;
    if (it == "set") {
      a[i].id = 1;
      cin >> a[i].x >> a[i].y;
      ver[st[tp]].push_back(i);
    } else if (it == "if") {
      a[i].id = 2;
      cin >> a[i].x;
      ver[st[tp]].push_back(i);
      st[++tp] = i;
    } else if (it == "end") {
      tp--;
    }
  }
  s[0] = inf;
  dfs(n + 1);
  cout << s[rt[n + 1]] << "\n";
}
signed main () {
#ifdef LOCAL_DEFINE
  freopen("1.in", "r", stdin);
  freopen("1.ans", "w", stdout);
#endif
  ios :: sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T = 1;  while (T--)  solve();
#ifdef LOCAL_DEFINE
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
  return 0;
}
```

---

