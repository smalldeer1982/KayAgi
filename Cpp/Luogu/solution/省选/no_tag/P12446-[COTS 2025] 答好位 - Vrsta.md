# [COTS 2025] 答好位 / Vrsta

## 题目描述


**这是一道交互题。交互库是非自适应的。**

有一个隐藏的 $1\sim N$ 的排列 $p_1,\ldots,p_N$。

你可以提问交互库至多 $K$ 次，每次给定 $i,j$（$1\le i\lt j\le N$），交互库会回答 $p_{i},p_{i+1},\ldots,p_{j}$ 中次大元素的下标。

在你提问完后，交互库会向你提问 $Q$ 次，每次给定 $a,b$（$1\le a\lt b\le N$），你需要回答 $p_{a},p_{a+1},\ldots,p_{b}$ 中次大元素的下标。

请注意：在你提问完之后，才能得知交互库的提问。这 $Q$ 次交互库对你的提问一次性给出。

### 实现细节

首先读入正整数 $N$。

接下来，发起至多 $K$ 次提问：

- $\texttt{?}$ $i$ $j$：提问 $p_{i},p_{i+1},\ldots,p_{j}$ 中次大元素的下标。
    - 你需要保证 $1\le i\lt j\le N$。
- $\texttt{!}$：结束提问。

每次提问后，都需要换行并刷新缓冲区。

在结束提问后，读入正整数 $Q$，以及 $Q$ 对正整数 $a,b$，表示对交互库你的提问。交互库保证 $1\le a\lt b\le N$。

对于每个交互库的提问，输出一行一个正整数，表示次大元素的下标。

在你回答完所有询问后，你需要刷新缓冲区，然后终止程序运行。

**交互库是非自适应的**。也就是说，询问和排列在交互开始前就已经固定。


## 说明/提示


### 样例解释

样例的排列为 $p=[2,1,4,3]$。

### 数据范围

- $N\le 512$；
- $K=Q=2\, 048$。

### 子任务
子任务 $0$ 为样例。

其中，「$-$」表示「不保证」。

| 子任务编号 | $N\le$ |特殊性质 | 得分 |
| :-: | :-: |  :-: | :-: |
| $1$ | $64$ | $-$  |  $6$ |
| $2$ | $-$ | $\text{A}$ |  $10$ |
| $3$ | $-$ | $\text{B}$ |  $11$ |
| $4$ | $-$ | $\text{C}$  |  $13$ |
| $5$ | $256$ | $-$ |  $26$ |
| $6$ | $-$ |$-$ |  $34$ |


- 特殊性质 $\text{A}$：不存在 $i$ 使得 $p_i\gt \max\{p_{i-1},p_{i+1}\}$。
- 特殊性质 $\text{B}$：$p_1=N$。
- 特殊性质 $\text{C}$：不存在 $i$ 使得 $p_i\lt \min\{p_{i-1},p_{i+1}\}$。


**交互库是非自适应的**。也就是说，询问和排列在交互开始前就已经固定。




## 样例 #1

### 输入

```
4

2

1

2
1 4
2 3

```

### 输出

```

? 1 2

? 1 3

!



4
2```

# 题解

## 作者：konyakest (赞：5)

挑战最短代码。

显然，原问题等价于求出每个区间的次大值下标。于是我们可以打表观察区间次大值的结构。

例如，当 $a=[2,8,1,5,9,6,3,7,4]$ 时，我们可以打出以下表：（第 $i$ 行第 $j$ 列表示区间 $[i,j]$ 的次大值下标，若不存在则为 $0$）。

```
0 1 1 4 2 2 2 2 2
0 0 3 4 2 2 2 2 2
0 0 0 3 4 6 6 8 8
0 0 0 0 4 6 6 8 8
0 0 0 0 0 6 6 8 8
0 0 0 0 0 0 7 6 6
0 0 0 0 0 0 0 7 9
0 0 0 0 0 0 0 0 9
0 0 0 0 0 0 0 0 0
```

观察发现，每个元素最多占据两个矩形区域。下文中用 $[a,b]\times [c,d]$ 的形式表示一个矩形区域。

证明：

> 考虑一个元素何时成为区间次大值。
> 
> 设 $pre_i$ 表示 $i$ 前面最后一个比 $a_i$ 大的位置，$prepre_i$ 表示 $i$ 前面倒数第二个比 $a_i$ 大的位置；$nxt_i$ 表示 $i$ 后面最前一个比 $a_i$ 大的位置，$nxtnxt_i$ 表示 $i$ 后面第二个比 $a_i$ 大的位置。
> 
> 则 $i$ 成为次大值的区域为：
> $$
> [prepre_i+1,pre_i]\times [i,nxt_i-1]\cup [pre_i+1,i]\times [nxt_i,nxtnxt_i-1]
> $$

于是我们定位到每个矩形即可。

考虑递归进行这个过程。如果我们知道 $[l,r]$ 内最大值下标为 $mx$，次大值下标为 $se$，不妨令 $mx<se$。

此时我们可以提取出矩形 $[l,mx]\times [se,r]$，往 $[l,se-1],[mx+1,r]$ 递归即可。

递归时进行记忆化，则每个矩形恰好被递归一次，总递归次数为 $2n$。

除第一次外区间的最大值下标可以在递归时传下去。第一次使用 $n$ 次询问查询即可。总次数为 $3n$。

code：

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k,...) for(int i=j;i<=k;i++)
using namespace std;

const int maxn=2070;

int a[maxn],n;
int ans[maxn][maxn];

int ask(int l,int r){
	cout<<"? "<<l<<" "<<r<<endl;
	int x;
	cin>>x;
	return x;
}

bool vis[maxn][maxn];

void solve(int l,int r,int mx){
	if(l==r) return;
	if(vis[l][r]) return;
	vis[l][r]=1;
	int se=ask(l,r),x,y;
	tie(x,y)=minmax(mx,se);
	rep(i,l,x) rep(j,y,r) ans[i][j]=se;
	solve(l,y-1,x),solve(x+1,r,y);
}

signed main(){
	cin>>n;
	int x=ask(1,n),l=x,r=x;
	while(r!=n&&ask(l,r+1)!=x) r++;
	while(l!=1&&ask(l-1,r)!=x) l--;
	int pos=(l==1? r+1: l-1);
	solve(1,n,pos);
	cout<<"!"<<endl;
	int q;
	cin>>q;
	while(q--){
		int l,r;
		cin>>l>>r;
		cout<<ans[l][r]<<endl;
	}
}
```

---

## 作者：__ycx2010__ (赞：3)

## solution

先考虑如何找到最大值，找到区间次大位置 $mid$ 后，若 $ask(l,mid)=mid$，则最大在左侧，否则在右侧,查询次数极限为 $n$。

找到最大值之后，建一棵笛卡尔树，当我们知道区间 $[l,r]$ 的最大值位置 $mid$ 后，$[l,mid]$ 的最大值位置只需要查询 $ask(l,mid)$，同理得到右侧最大值位置，于是我们可以得到笛卡尔树的形态，查询次数也是 $n$。

对于一个 $\text{LCA}$ 为 $u$ 的两个点 $a$，$b$，$c$ 为 $u$ 的左儿子子树中最靠右的点，$d$ 为 $u$ 的右儿子子树中最靠左的点，$a'$ 为 $a$，$c$ 的 $\text{LCA}$，$b'$ 同样为 $b$，$d$ 的 $\text{LCA}$。查询 $ask(a,b)$ 的结果为 $a'$,$b'$ 中的较大值，所以我们只需要将链 $(u,c)$ 和 $(u,d)$ 归并排序一下就能得到所有答案，查询次数为 $2n$。

总查询次数为 $4n$。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1000;
int P[N], qq;

int ask(int l, int r) {
	if (l < r) {
		++ qq;
		cout << "?" << ' ' << l << ' ' << r << endl;
		// priority_queue<pair<int, int>> H;
		// for (int i = l; i <= r; i ++) H.push({P[i], i});
		// H.pop();
		// cout << H.top().second <<endl;
		// return H.top().second;
		int x;
		cin >> x;
		return x;
	} else {
		return 0;
	}
}

int findmax(int l, int r) {
	if (l == r) return l;
	int mid = ask(l, r);
    if (mid == l) return find(mid + 1, r);
    if (mid == r) return find(l, mid - 1);
	if (ask(l, mid) == mid) return findmax(l, mid - 1);
	else return findmax(mid + 1, r);
}

int tot;
int Lw[N], Rw[N], g[N], ls[N], rs[N];
int f[N][N];

void build(int x, int l, int r) {
	if (l > r) return;
	Lw[x] = ++ tot;
	g[tot] = x;
	ls[x] = ask(l, x);
	rs[x] = ask(x, r);
	build(ls[x], l, x - 1);
	build(rs[x], x + 1, r);
	Rw[x] = tot;
}

vector<int> in(int x) {
	vector<int> a;
	if (!x) return a;
	for (int i = Lw[x]; i <= Rw[x]; i ++ ) a.push_back(g[i]);
	return a;
}

void solve(int u) {
	if (!u) return;
	solve(ls[u]);
	solve(rs[u]);
	vector<int> L, R;
	int tl = ls[u], tr = rs[u];
	L.push_back(tl);
	R.push_back(tr);
	if (tl) {
		vector<int> A = in(ls[tl]);
		A.push_back(tl);
		for (int i : A) f[i][u] = tl;
	}
	if (tr) {
		vector<int> B = in(rs[tr]);
		B.push_back(tr);
		for (int i : B) f[u][i] = tr;
	}
	while (rs[tl]) {
		tl = rs[tl], L.push_back(tl);
		vector<int> a = in(ls[tl]);
		a.push_back(tl);
		for (int i : a) f[i][u] = tl;
	}
	while (ls[tr]) {
		tr = ls[tr], R.push_back(tr);
		vector<int> b = in(rs[tr]);
		b.push_back(tr);
		for (int i : b) f[u][i] = tr;
	}
	int i = 0, j = 0;
	if (!ls[u] || !rs[u]) return;
	while (i < L.size() && j < R.size()) {
		if (ask(L[i], R[j]) == L[i]) {
			for (int k = j; k < R.size(); k ++ ) {
				vector<int> a = in(ls[L[i]]);
				a.push_back(L[i]);
				vector<int> b = in(rs[R[k]]);
				b.push_back(R[k]);
				for (int p : a) for (int q : b) f[p][q] = L[i];
			}
			i ++ ;
		} else {
			for (int k = i; k < L.size(); k ++ ) {
				vector<int> a = in(ls[L[k]]);
				a.push_back(L[k]);
				vector<int> b = in(rs[R[j]]);
				b.push_back(R[j]);		
				for (int p : a) for (int q : b) f[p][q] = R[j];
			}
			j ++ ;
		}
	}

}

int main() {
	//srand(time(0));
	int n;
	cin >> n;
	// P[1] = n;
	// for (int i = 2; i <= n; i ++ ) P[i] = i - 1;
	// int T = 1000;
	// while (T -- ) {
	// 	int a = rand() % n + 1, b = rand() % n +1;
	// 	swap(P[a], P[b]);
	// }
	int x = findmax(1, n);
	build(x, 1, n);
	solve(x);
	cout << "!" << endl;
	int Q;
	cin >> Q;
	while (Q -- ) {
		int l, r;
		cin >> l >> r;
		cout << f[l][r] << endl;
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：1)

构式交互题，很难啊我觉得。

考虑我们如何获得区间 $[1,n]$ 的最大值位置：我们只需要按照次大值分治下去造笛卡尔树就行了，使用询问 $[l,mid]$ 或者 $[mid,r]$ 的方式，判断下标是否是 $mid$ 就能简单地获得最大值的方向，回溯上来就行。

然后考虑对最大值再造一次笛卡尔树，问题是我们又怎么获得新的区间的最大值。考虑一个聪明的办法，询问区间 $[l,mid]$ 获得的直接就是 $[l,mid)$ 的次大值，右侧同理，于是我们又可以造出最大值笛卡尔树。

现在我们已经花费了 $2n$（笛卡尔树一个 $n$，获得最大值是每个点两次询问，至多 $\frac{n}{2}$ 个点），考虑查询 $[a,b]$ 怎么办。可以发现整个问题几乎是不可合并的，所以我们不能用笛卡尔树的朴素合并办法来查次大值。考虑笛卡尔树的性质：$[a,b]$ 的最大值就在 $a,b$ 这两个点的 LCA 上。那么考虑次大值其实就是 $[a,mid)$ 和 $(mid,b]$ 中的最大值的最大值。显然这个值也一定在 $mid-1$ 和 $mid+1$ 到这里的路径上。所以我们的操作指南应该是把询问“挂”在 $mid$ 上（实际上是预处理所有询问的答案），然后查询的时候直接查表。

考虑这种“挂”的操作需要我们求出 $mid-1$ 和 $mid+1$ 到 $mid$ 这两条路径的序关系，这样我们查询的时候可以直接查序上第一个在 $[a,b]$ 区间中的位置。显然考虑归并两条链。

考虑怎么查询两条路径两个元素 $x,y(p_x<p_y)$ 之间的大小关系。容易发现，若 $[x,y]$ 中存在一个数介于 $p_x,p_y$ 之间，那么一定有一方不在到 $mid-1$ 或 $mid+1$ 的路径上，因为这两个点和 $mid$ 贴死，如果中间有一个数更大，那么我们一定会经过那个数，并从那个数向中间靠拢，而不是分开；若 $[x,y]$ 中存在一个数比 $p_x,p_y$ 都大就更不合理了。

于是我们只需直接查询 $[x,y]$ 就能获得次大值，即两者中较大的一个。

然后考虑证明归并排序的询问次数正确。因为归并排序本身是 $\mathcal O(n)$ 的，我们只需考虑所有归并排序的链的长度和。显然每个点至多在它左右第一个比它大的点作为根产生的链中产生贡献，所以链的长度和是 $2n$。

总次数刚好 $4n$，实际上显然完全跑不满。

用单调栈可以更简单地理解。

实现时注意到 $mid-1$ 一定是 $mid$ 的前驱，$mid+1$ 一定是 $mid$ 的后继，可以把找路径写得更方便。

```cpp
int n;
int a[N];
int getcm(int l,int r){
	if(l>=r) return 0;
	cout<<"? "<<l<<" "<<r<<endl;
	int x;
	cin>>x;
	return x;
}
int getmax(int l,int r){
	if(l==r) return l;
	int cm=getcm(l,r);
	int lcm=getcm(l,cm);
	if(cm==lcm) return getmax(l,cm-1);
	else return getmax(cm+1,r);
}
int mx[N],ls[N],rs[N];
int f[N];
int rt;
int tot;
int dir[N];
int lf[N];
int q;
void build(int &p,int l,int r){
	if(l>r) return;
	if(!p) tot++,p=tot;
	lf[mx[p]]=tot;
	if(l==r) return;
	mx[tot+1]=getcm(l,mx[p]);
	build(ls[p],l,mx[p]-1);
	mx[tot+1]=getcm(mx[p],r);
	build(rs[p],mx[p]+1,r);
	dir[p]=(!ls[p]||!rs[p]?(ls[p]|rs[p]):getcm(mx[ls[p]],mx[rs[p]]));
	f[ls[p]]=f[rs[p]]=p;
}
vector <int> srt[N];
int LCA(int u,int v){
	u=lf[u],v=lf[v];
	vector <int> p1,p2;
	do{
		p1.pb(u);
		u=f[u];
	}while(u);
	do{
		p2.pb(v);
		v=f[v];
	}while(v);
	int ans;
	do{
		ans=p1.back();
		p1.pop_back(),p2.pop_back();
	}while((!p1.empty()&&!p2.empty())&&p1.back()==p2.back());
	return ans;
}
void init(int x){
	vector <int> lp,rp;
	int r=ls[x];
	while(r){
		lp.pb(r);
		r=rs[r];
	}
	int l=rs[x];
	while(l){
		rp.pb(l);
		l=ls[l];
	}
	int lpo=0,rpo=0;
	while(lpo!=lp.size()&&rpo!=rp.size()){
		if(getcm(mx[lp[lpo]],mx[rp[rpo]])==mx[lp[lpo]]){
			srt[x].pb(lp[lpo]);
			lpo++;
		}
		else{
			srt[x].pb(rp[rpo]);
			rpo++;
		}
	}
	while(lpo<lp.size()) srt[x].pb(lp[lpo]),lpo++;
	while(rpo<rp.size()) srt[x].pb(rp[rpo]),rpo++;
}
int main(){
#ifdef Shun
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	cin>>n;
	int md=getmax(1,n);
	mx[1]=md;
	build(rt,1,n);
	fr1(i,1,n) init(i);
	cout<<"!"<<endl;
	cin>>q;
	while(q--){
		int u,v;
		cin>>u>>v;
		int lca=LCA(u,v);
		for(auto i:srt[lca]){
			if(u<=mx[i]&&mx[i]<=v){
				cout<<mx[i]<<endl;
				break;
			}
		}
	}
	ET;
}
//ALL FOR Zhang Junhao.
```

---

## 作者：Purslane (赞：1)

# Solution

交互题真下头。

考虑建出笛卡尔树。显然查询的时候我们会找到 $l$ 和 $r$ 的 $\rm LCA$，然后询问两边的“单调栈”中最靠外的两个元素的相对大小关系。如图所示：

![](https://s21.ax1x.com/2025/05/13/pEXzs81.png)

如果能建出笛卡尔树，我们就可以归并求出他们的相对大小关系。而归并所用操作次数一定小于等于 $2n$（原因是，每比较一次一定会决策一个位置。而一个位置只会被决策 $2$ 次，分别是其左右第一个比他大的数处）。

那怎么建笛卡尔树呢。发现我们能用 $\log n$ 次询问得出最大值和次大值的位置。知道最大值之后可以直接递归求解。每次求解的问题形如：建立区间 $[l,r]$ 的笛卡尔树，已经知道 $l-1$ 或者 $r+1$ 大于区间内所有数。

这样询问一下就可以知道区间最大值在哪里。

总的询问次数为 $3n + \log n$，小于题目 $4n$ 的限制。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=610;
int n,q,dep[MAXN],ls[MAXN],rs[MAXN],fa[MAXN];
int query(int l,int r) {
	if(l==r) return -1;
	cout<<"? "<<l<<' '<<r<<endl,cout.flush();
	int pos;
	return cin>>pos,pos;
}

int build(int l,int r,int op) {
	if(l>r) return 0;
	if(l==r) return l;
	int rt;
	if(op==0) rt=query(l,r+1);
	else rt=query(l-1,r);
	ls[rt]=build(l,rt-1,0),rs[rt]=build(rt+1,r,1);
	return rt;	
}
vector<int> chain[MAXN];
void dfs(int u,int f) {
	fa[u]=f,dep[u]=dep[f]+1;
	if(ls[u]) dfs(ls[u],u);
	if(rs[u]) dfs(rs[u],u);
	return ;
}
int lca(int u,int v) {
	while(u!=v) {
		if(dep[u]>dep[v]) u=fa[u];
		else v=fa[v];
	}
	return u;
}
void init(int rt) {
	vector<int> lc,rc;
	int tmp=ls[rt];
	while(tmp) lc.push_back(tmp),tmp=rs[tmp];
	tmp=rs[rt];
	while(tmp) rc.push_back(tmp),tmp=ls[tmp];
	int lpos=0,rpos=0;
	while(lpos<lc.size()&&rpos<rc.size()) {
		if(query(lc[lpos],rc[rpos])==lc[lpos]) chain[rt].push_back(lc[lpos]),lpos++;
		else chain[rt].push_back(rc[rpos]),rpos++;
	}
	while(lpos<lc.size()) chain[rt].push_back(lc[lpos]),lpos++;
	while(rpos<rc.size()) chain[rt].push_back(rc[rpos]),rpos++;
	return ;
}
int main() {
	cin>>n;
	int srt=query(1,n),rt;
	if(query(1,srt)==srt) {
		int lp=1,rp=srt-1;
		while(lp<=rp) {
			int mid=(lp+rp>>1);
			if(query(mid,srt)==srt) rt=mid,lp=mid+1;
			else rp=mid-1;
		}
		rs[rt]=srt;
		ls[rt]=build(1,rt-1,0);
		ls[srt]=build(rt+1,srt-1,0);
		rs[srt]=build(srt+1,n,1);
	}
	else {
		int lp=srt+1,rp=n;
		while(lp<=rp) {
			int mid=(lp+rp>>1);
			if(query(srt,mid)==srt) rt=mid,rp=mid-1;
			else lp=mid+1;
		}
		ls[rt]=srt;
		rs[rt]=build(rt+1,n,1);
		ls[srt]=build(1,srt-1,0);
		rs[srt]=build(srt+1,rt-1,1);
	}
	ffor(i,1,n) init(i);
	cout<<"!"<<endl,cout.flush();
	dfs(rt,0);
	cin>>q;
	ffor(i,1,q) {
		int l,r;
		cin>>l>>r;
		int u=lca(l,r);
		assert(l<=u&&u<=r);
		if(l!=u) for(auto id:chain[u]) if(l<=id&&id<=u) {l=id;break ;}
		if(r!=u) for(auto id:chain[u]) if(u<=id&&id<=r) {r=id;break ;}
		int ans=-1;
		for(auto id:chain[u]) {
			if(id==l) {ans=id;break ;}
			if(id==r) {ans=id;break ;}	
		}
		cout<<ans<<endl,cout.flush();
	}
	return 0;
}
```

---

## 作者：min_inf (赞：1)

考虑如果需要回答的是最大怎么做。维护一个单调栈，加入一个点的时候询问当前栈顶 $j$ 到新元素 $i$ 这段区间，如果 $p_j<p_i$ 那么次大就应该是 $j$（因为他原来是最大），遇到第一个 $p_j>p_i$ 次大就变成 $i$ 了，存下每个位置的单调栈就可以用 $2n$ 次询问回答出最大的问题。

然后考虑拓展一下这个单调栈，把所有会更新次大的元素也加入。称更新最大的元素为第一类，更新次大的为第二类。

考虑加入 $i$ 时单调栈怎么变化：设 $p$ 为左侧第一个大于 $i$ 的，$p$ 右侧的第一类元素全部变为第二类，第二类元素全都删掉，然后删除 $p$ 到左边下一个第一类元素之间第二类元素的一个后缀，最后加入第一类元素 $i$。

$p$ 右边的部分和最大的做法一样，左边的部分显然也可以直接查次小是不是左端点来检查。每个元素最多被弹栈两次，每次加入最多在边界浪费两次询问，所以不会超过 $4n$ 次询问。

```cpp
cin>>n;
vector<pair<int,bool>> stk;
stk.emplace_back(1,0);
rep(i,2,n){
    vector<int> rm;
    while(!stk.empty()){
        if(stk.back().sec){
            stk.pop_back();
            continue;
        }
        if(ask(stk.back().fir,i)==i)break;
        rm.push_back(stk.back().fir);
        stk.pop_back();
    }
    if(!stk.empty()){
        int p=stk.back().fir;
        stk.pop_back();
        while(!stk.empty()&&stk.back().sec&&ask(stk.back().fir,i)!=stk.back().fir)
            stk.pop_back();
        stk.emplace_back(p,0);
    }
    reverse(allc(rm));
    for(auto p:rm)stk.emplace_back(p,1);
    stk.emplace_back(i,0);
    rs[i]=stk;
}
cout<<'!'<<endl;
cin>>m;
while(m--){
    int l,r;cin>>l>>r;
    stk=rs[r];
    int p=0,q=0;
    while(!stk.empty()&&stk.back().fir>=l){
        auto [x,tp]=stk.back();stk.pop_back();
        if(tp)q=x;else q=p,p=x;
    }
    cout<<q<<'\n';
}
```

---

## 作者：Undead2008 (赞：1)

[COTS 2025 题解合集](https://www.luogu.com.cn/article/dupadkce)

写了一坨思路自己都读不懂，不如直接说做法：

先搞个单调栈求出每个元素左边第一个比它大的元素和右边第一个比他大的元素，具体步骤如代码所示：

```cpp
int Ask(int u,int v){
	cout<<"? "<<u<<' '<<v<<endl;
	int I;
	cin>>I;
	return I;
}
{//下面是单调栈
  for(int i=1;i<=n;i++){
    while(Tp&&Ask(St[Tp],i)==St[Tp])
      Ne[St[Tp]]=i,Tp--;
    La[i]=St[Tp],St[++Tp]=i;
  }
}
```

知道这些就建大根笛卡尔树，询问区间的最大值 $x$ 直接求出。

询问的次大值一定是 $x$ 前驱的祖先或者 $x$ 后继的祖先，考虑到要求出这两条链上元素的一个完整的序，就归并这两条链，比较第一条链的元素 $L$ 和第二条链的元素 $R$ 的时候只需要询问 $(L,R)$ 即可得知 $L$ 和 $R$ 的相对大小。

这题就做完了，总询问次数为 $4n$。

贴一下代码：

```cpp
#include"bits/stdc++.h"
#ifdef REANI
	#include"windows.h"
	using namespace std;
	void SetMemoryLimit(SIZE_T MB){
		HANDLE job=CreateJobObject(NULL,NULL);
		assert(job!=NULL);
		JOBOBJECT_EXTENDED_LIMIT_INFORMATION info={0};
		info.BasicLimitInformation.LimitFlags=JOB_OBJECT_LIMIT_PROCESS_MEMORY;
		info.ProcessMemoryLimit=MB;
		assert(SetInformationJobObject(job,JobObjectExtendedLimitInformation,&info,sizeof(info))&&AssignProcessToJobObject(job,GetCurrentProcess()));
	}
#else
	using namespace std;
#endif
const int maxn = 600;
int n,q,a[maxn];
int St[maxn],Tp;
int La[maxn],Ne[maxn],De[maxn],E[maxn][maxn];
int Ask(int u,int v){
	#ifdef REANI
		assert(u<v);
		int Mx=-1,dMx=-1;
		for(int i=u;i<=v;i++)
			if(Mx==-1||a[Mx]<a[i])
				Mx=i;
		for(int i=u;i<=v;i++)
			if(i!=Mx&&(dMx==-1||a[dMx]<a[i]))
				dMx=i;
		return dMx;
	#else
		cout<<"? "<<u<<' '<<v<<endl;
		int IndI;
		cin>>IndI;
		return IndI;
	#endif
}
void Mark(int l,int r,int Dep){
	int p=-1;
	for(int i=l;i<=r;i++)
		if(La[i]<l&&Ne[i]>r)
			p=i;
	int u=p-1,v=p+1;
	vector<int>Tu(1,u),Tv(1,v);
	assert(Tu.size()==1&&Tv.size()==1);
	while(La[p]<u&&v<Ne[p]){
		int K=Ask(u,v);
		if(K==v){
			for(auto Fu:Tu)
				E[Fu][v]=v;
			u=La[u];
			if(La[p]<u){
				Tu.push_back(u);
				for(auto Fv:Tv)
					if(Fv!=v)
						E[u][Fv]=u;
			}
		}else{
			for(auto Fv:Tv)
				E[u][Fv]=u;
			v=Ne[v];
			if(v<Ne[p]){
				Tv.push_back(v);
				for(auto Fu:Tu)
					if(Fu!=u)
						E[Fu][v]=v;
			}
		}
	}
	while(La[p]<u){
		for(auto Fv:Tv)
			E[u][Fv]=u;
		u=La[u];
	}
	while(v<Ne[p]){
		for(auto Fu:Tu)
			E[Fu][v]=v;
		v=Ne[v];
	}
	De[p]=Dep;
	if(l<p)Mark(l,p-1,Dep+1);
	if(p<r)Mark(p+1,r,Dep+1);
}
int main(){
	#ifdef REANI
		SetMemoryLimit(512*1048576);
	#endif
	cin>>n,memset(E,-1,sizeof(E));
	#ifdef REANI
		for(int i=1;i<=n;i++)
			cin>>a[i];
	#endif
	for(int i=1;i<=n;i++){
		while(Tp&&Ask(St[Tp],i)==St[Tp])
			Ne[St[Tp]]=i,Tp--;
		La[i]=St[Tp],St[++Tp]=i;
	}
	for(int i=1;i<=Tp;i++)Ne[St[i]]=n+1;
	Mark(1,n,1);
	#ifndef REANI
		cout<<"!"<<endl;
	#endif
	cin>>q;
	for(int i=1,l,r,p;i<=q;i++){
		cin>>l>>r,p=-1;
		for(int j=l;j<=r;j++)
			if(p==-1||De[j]<De[p])
				p=j;
		int Ld=p==l?-1:p-1,Rd=p==r?-1:p+1;
		while(Ld!=-1&&La[Ld]>=l)Ld=La[Ld];
		while(Rd!=-1&&Ne[Rd]<=r)Rd=Ne[Rd];
		assert(Ld!=-1||Rd!=-1);
		int As=-1;
		if(Ld==-1)cout<<(As=Rd)<<endl;
		else if(Rd==-1)cout<<(As=Ld)<<endl;
		else assert(E[Ld][Rd]!=-1),cout<<(As=E[Ld][Rd])<<endl;
		#ifdef REANI
			assert(As==Ask(l,r));
		#endif
	}
}
```

---

## 作者：gcx12012 (赞：0)

### 前言
场切了，但是浪费掉了很多时间，菜还得多练。
### Solution
详细讲一下本人的赛时思路。

考虑到询问次数上限是 $4n$，于是直接排除分治等询问次数为单 $\log$ 的做法。

一开始容易想到将整个排列 $p$ 求出来再处理交互库的询问，但是我们只能获取区间次大值的信息，因此这是困难的。

然后考虑一下从特殊性质 B 入手：$p_1=n$。我们设 $pos_i$ 为数字 $i$ 在排列中出现的下标，此时 $pos_{n-1}$ 是好求的，用一次询问即可解决。

这时候我们设已知的 $pos_i$ 和 $0$ 和 $n+1$ 作为断点，并引入时间戳 $tim_i$ 表示位置 $i$ 的断点在什么时候确定。显然 $tim_i$ 越小，该数越大。

假设我们已经确定了若干断点，我们不知道某个区间的次大值，当且仅当区间内包含 $<2$ 个断点。考虑求出两个**相邻**断点内的区间最大值，这是好求的，直接将该区间加上其中一个断点询问即可。然后相邻两个最大值的大小关系也是好求的，将两个最大值所在下标作为区间的两个端点查询即可，因为隔在它们中间的断点的数一定比它们两个都大。如果两个最大值不相邻则它们的大小关系不影响区间次大值的结果。此时先加的断点一定是比较大的那个数。

我们确定了这样的偏序关系之后，任取一个不被其它位置约束的点作为新添加的断点，就这样一直加到所有断点/时间戳确定为止，然后直接对 $tim$ 求区间次小值即可。这样的询问次数大约是 $2n$。

考虑正解，发现只比特殊性质 B 多一个确定 $pos_n$，这也是好做的，直接以 $pos_{n-1}$ 作为区间的其中一个端点查询即可。

总的查询次数大约是 $3n$，对询问加上记忆化完全可以通过。

赛时写的代码有点丑。
```
int n,q;

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int a[N][N],b[N],tot=0,to[N];
int tim[N],cnt=2;
vector<int >pos;
int ask(int x,int y){
	if(x>y) swap(x,y);
	if(a[x][y]) return a[x][y];
	cout<<"? "<<x<<' '<<y<<endl;
	int z;
	cin>>z;
	a[x][y]=z;
	return z;
}

int main()
{
    //freopen("gcx.in","r",stdin);
    //freopen("gcx.out","w",stdout);
    cin>>n;
    pos.pb(0);
    pos.pb(n+1);
    int p1=ask(1,n),p2=-1;
    tim[p1]=2,pos.pb(p1);
    Rof(i,p1-1,1){
    	if(ask(i,p1)==p1){
    		p2=i;
    		break;
    	}
    }
    if(p2==-1){
    	For(i,p1+1,n){
    		if(ask(i,p1)==p1){
    			p2=i;
    			break;
    		}
    	}
    }
    pos.pb(p2);
    tim[p2]=1;
    sort(pos.begin(),pos.end());
    while(pos.size()<n+2){
    	tot=0;
    	memset(to,0,sizeof(to));
    	for(int i=1;i<pos.size();i++){
    		if(pos[i]-pos[i-1]<=1) continue;
    		int now=(pos[i-1]==0?ask(1,pos[i]):ask(pos[i-1],pos[i]-1));
    		b[++tot]=now;
    		to[now]=i;
    	}
    	For(i,1,tot){
    		For(j,i+1,tot){
    			if(abs(to[b[i]]-to[b[j]])>1) continue;
    			if(!a[b[i]][b[j]]) a[b[i]][b[j]]=a[b[j]][b[i]]=ask(b[i],b[j]);
    			if(a[b[i]][b[j]]==b[j]) swap(b[i],b[j]);
    		}
    	}
    	For(i,1,1) tim[b[i]]=++cnt,pos.pb(b[i]);
    	sort(pos.begin(),pos.end());
    }
    For(i,1,n) if(!tim[i]) tim[i]=++cnt;
    cout<<"!"<<endl;
    cin>>q;
    while(q--){
    	int x,y;
    	cin>>x>>y;
    	int mx=1e5,mx2=1e5;
    	For(i,x,y) mx=min(mx,tim[i]);
    	For(i,x,y) if(tim[i]!=mx) mx2=min(mx2,tim[i]);
    	For(i,x,y){
    		if(tim[i]==mx2){
    			cout<<i<<endl;
    			break;
    		}
    	}
    }
   	return 0;
}
```

---

