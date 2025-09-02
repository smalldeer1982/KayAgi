# [POI 2020/2021 R2] 收拾背包 / Pakowanie plecaka

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/4829)。

## 题目描述

**题目译自 [XXVIII Olimpiada Informatyczna – II etap](https://sio2.mimuw.edu.pl/c/oi28-2/dashboard/) [Pakowanie plecaka](https://szkopul.edu.pl/problemset/problem/tFYVKjavLmyczkxMH7WFewXe/statement/)**

Bajtazar 准备骑自行车去 Bajtocji 旅游。他现在在考虑要带什么有用的东西在背包里。可惜的是，他没有多少时间，所以他把可能需要的装备按照重要性从高到低排列了一下。他的做法很简单：按顺序检查每个物品，只要不超过背包的承重（当然，要算上之前放进去的物品），就带上它。

还有一个关键的问题：要带什么样的背包呢？Bajtazar 觉得只要带上至少 $k$ 个物品，他就能在旅途中应付得来。可是他还不确定 $k$ 到底是多少。那么，他的背包的承重至少应该是多少，才能保证他带上至少 $k$ 个物品呢？

## 说明/提示

**样例 1 解释**

输出的第二个数是 $13$。如果背包的承重是 $13$，那么 Bajtazar 会带上第一个物品（重量为 $10$），不会带上第二个物品（因为他只剩下 $3$ 的承重，而物品重量为 $8$），然后会带上重量为 $3$ 的物品。总共他会带上正好需要的两个物品。

**附加样例**
1. 该样例满足 $n=20$，奇数位置的物品重量为 $10^{8}$，偶数位置的物品重量为 $10^{9}$。
2. 该样例满足 $n=200, w_{i}=(i \bmod 47)+1$。
3. 该样例满足 $n=5000$，物品的重量是从区间 $\left[1,10^{9}\right]$ 随机选取的。
4. 该样例满足 $n=5\cdot 10^5, w_{i}=\left\lfloor\frac{(i \bmod 200)}{100}\right\rfloor+1$。
5. 该样例满足 $n=5\cdot 10^5, w_{i}=\left(F_{i} \bmod 100\right)+1$，其中 $F_{0}=0, F_{1}=1, F_{i+2}=F_{i}+F_{i+1}$。
6. 该样例满足 $n=5\cdot 10^5$，物品的重量是从区间 $[1,10^{9}]$ 随机选取的。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$ | $n \leq 20$ | $8$ |
| $2$ | $n \leq 200$ | $10$ |
| $3$ | $n \leq 5000$ | $20$ |
| $4$ | $w_{i} \leq 2$ | $8$ |
| $5$ | $w_{i} \leq 100$ | $20$ |
| $6$ | 无附加限制 | $34$ |

## 样例 #1

### 输入

```
6
10 8 3 30 5 10```

### 输出

```
3 13 21 26 36 66```

# 题解

## 作者：Iniaugoty (赞：12)

不妨考虑一个 DP。设 $f _ {i, j}$ 表示依次考虑 $[i, n]$ 中的物品，带上了 $j$ 个，最小代价。由于是正扫，能加就加，因此倒着 DP。

~~观察大样例~~不难发现 $f _ i$ 是单调的，带的物品越多，最小代价越大。

考虑转移。

钦定 $f _ {i, 0} = 0$，这是有道理的。

设 $k$ 满足 $f _ {i + 1, k} < w _ i$，并且最大。

- 对于 $j \le k$，$f _ {i, j}$ 可以直接继承 $f _ {i + 1, j}$ 的值（也就是不选取 $i$），并且这是最优的，因为如果选取 $i$ 的话代价一定大于 $w _ i$。

- 对于 $j > k$，是不可以不选取 $i$ 直接继承的，因为 $f _ {i + 1, j} \ge w _ i$，从前往后扫到 $i$，能拿就直接拿了，所以 $f _ {i, j} \gets f _ {i + 1, j - 1} + w _ i$。

直接做是 $O(n ^ 2)$ 的。

第一部分转移就是保持不变；第二部分，形如先对 $[k + 1, n - i]$ 区间加 $w _ i$，然后在第 $k + 1$ 个数前插入 $f _ k + w _ i$。

容易数据结构优化，用平衡树维护区间加和单点插入即可，$k$ 这个位置可以在平衡树上二分找到（或者 FHQ-treap 这种树，直接按权值分裂）。

时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, LL> pii;
const int N = 5e5 + 5;

int n, w[N];

int rt, ls[N], rs[N], rnd[N]; LL val[N], tag[N];
static mt19937 Rand;
uniform_int_distribution<int> rng(1, 1e9);
void Maketag(int u, LL k) { val[u] += k, tag[u] += k; }
void Pushdown(int u) {
  if (ls[u]) Maketag(ls[u], tag[u]);
  if (rs[u]) Maketag(rs[u], tag[u]);
  tag[u] = 0;
}
int Merge(int u, int v) {
  if (!u || !v) return u | v;
  Pushdown(u), Pushdown(v);
	if (rnd[u] >= rnd[v]) return rs[u] = Merge(rs[u], v), u;
	else return ls[v] = Merge(u, ls[v]), v;
}
void Split(LL k, int &x, int &y, int u) {
	if (!u) return x = y = 0, void();
  Pushdown(u);
	if (val[u] <= k) Split(k, rs[x = u], y, rs[u]);
	else Split(k, x, ls[y = u], ls[u]);
}
int Query(int u) {
  if (!u) return 0;
  while (rs[u]) Pushdown(u), u = rs[u];
  return val[u];
}
void Newnode(int u, int k) { val[u] = k, tag[u] = 0, rnd[u] = rng(Rand); }
void Solve(int u) {
  Pushdown(u);
  if (ls[u]) Solve(ls[u]);
  cout << val[u] << " ";
  if (rs[u]) Solve(rs[u]);
}

int main() {
  // freopen("zyq.in", "r", stdin);
  // freopen("zyq.out", "w", stdout);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  F(i, 1, n) cin >> w[i];
  Newnode(rt = n, w[n]);
  dF(i, n - 1, 1) {
    int u = 0, v = 0; Split(w[i] - 1, u, v, rt);
    Newnode(i, Query(u) + w[i]), Maketag(v, w[i]);
    rt = Merge(Merge(u, i), v);
  }
  Solve(rt);
  return 0;
}
```

---

## 作者：Lysea (赞：6)

### Solution

令 $s_i=\sum\limits_{j=1}^{i}{a_j}$，容易发现取走 $n$ 件物品时答案必为 $s_n$，这启发我们倒序处理，每次少取走一件物品并更新答案。

令初始承重为 $c$，考虑 $a_i$ 何时满足在剩余物品中，仅有 $a_i$ 无法被取：

- $s_{i-1}\le c$（$1$ 至 $i-1$ 物品能被取）

- $s_i>c$（$i$ 物品无法被取）

- $s_n-a_i\le c$（$i+1$ 至 $n$ 物品能被取）

容易发现 $s_n-a_i>s_{i-1}$，也就是第三条限制严于第一条，至此我们得到：$s_n-a_i\le c<s_i$。

由此推出 $i$ 的限制：$s_n-s_i-a_i<0$。

题目要求出 $c_{\min}$，也就是 $\min\limits_{s_n-s_i-a_i<0}\{s_n-a_i\}=s_n-\max\limits_{s_n-s_i-a_i<0}\{a_i\}$。

在取走对应的 $i$ 号物品后，$s$ 数组要进行更改，具体表现为两点：

- 对于 $j\in[1,i-1]$ 的 $s_n-s_j-a_j$ 降低 $a_i$，满足 $s_n-s_i-a_i<0$ 的决策集合扩大。

- $s_n\leftarrow s_n-a_i$（用于计算 $c_{\min}$）。

题意转化完毕，现在考虑怎么维护这个东西。

对于 $c_{\min}$ 的求解，可以直接使用一个大根堆，将合法的 $i$ 对应的贡献塞到里面即可。

删除操作则可以考虑使用平衡树或者线段树维护 $s_n-s_i-a_i$ 的值。假设处于堆顶的位置为 $t$，$[1,t-1]$ 的区间减去 $a_t$ 前，先查询区间内是否存在值小于 $a_t$，这代表着此位置在执行此次操作后会被加入决策中。

若存在，则将此位置加入堆中，并将此位置的 $s_n-s_i-a_i$ 设为一个极大值，避免影响后续判断。重复此操作直至区间内不存在值小于 $a_t$，最后再执行区间减操作。

每个数最多加入堆 $1$ 次，均摊下来是 $O(n\log n)$ 的，线段树的部分同理。

总体时间复杂度 $O(n \log n)$。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1e18
#define N 1000005
using namespace std;
struct tree{
	int lz,v,vp;
}t[N<<1];
struct node{
	int val,id;
	bool operator<(const node& a)const{
		return val<a.val;
	}
};
int n,a[N],s[N],ans[N],tot;
priority_queue<node>q;
void push_up(int p){
	if(t[p<<1].v<t[p<<1|1].v) t[p].v=t[p<<1].v,t[p].vp=t[p<<1].vp;
	else t[p].v=t[p<<1|1].v,t[p].vp=t[p<<1|1].vp;
}
void push_down(int p){
	t[p<<1].v+=t[p].lz,t[p<<1].lz+=t[p].lz;
	t[p<<1|1].v+=t[p].lz,t[p<<1|1].lz+=t[p].lz;
	t[p].lz=0;
}
void add(int p,int l,int r,int L,int R,int v){
	if(L<=l&&r<=R){
		t[p].lz+=v,t[p].v+=v;
		if(l==r) t[p].vp=l;
		return;
	}
	push_down(p);
	int mid=l+r>>1;
	if(L<=mid) add(p<<1,l,mid,L,R,v);
	if(R>mid) add(p<<1|1,mid+1,r,L,R,v);
	push_up(p);
}
tree query(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R) return t[p];
	push_down(p);
	int mid=l+r>>1; tree ls,rs,res;
	if(L<=mid) ls=query(p<<1,l,mid,L,R);
	if(R>mid) rs=query(p<<1|1,mid+1,r,L,R);
	if(L>mid) return rs;
	if(R<=mid) return ls;
	if(ls.v<rs.v) res.v=ls.v,res.vp=ls.vp;
	else res.v=rs.v,res.vp=rs.vp;
	return res;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n,tot=n;
	for(int i=1;i<=n;i++) cin>>a[i],s[i]=s[i-1]+a[i];
	ans[tot]=s[n];
	for(int i=1,tmp;i<=n;i++){
		tmp=s[n]-s[i]-a[i];
		if(tmp<0) q.push(node{a[i],i}),add(1,1,n,i,i,INF);
		else add(1,1,n,i,i,tmp);
	}
	while(tot!=1){
		node g=q.top(); q.pop();
		tot--,ans[tot]=ans[tot+1]-g.val;
		while(true){
			tree tmp=query(1,1,n,1,g.id);
			if(tmp.v>=g.val) break;
			q.push(node{a[tmp.vp],tmp.vp});
			add(1,1,n,tmp.vp,tmp.vp,INF);
		}
		add(1,1,n,1,g.id,-g.val);
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：fzitb7912 (赞：0)

## 分析

正着不好做。倒着来呢？首先 $res_n=\sum\limits_{i=1}^{n}w_i$。假设我们现在有一些点，如果能够删去第 $i$ 个点使得 $k \to k-1$，那么有：$\sum\limits_{i=1}^{k}w_i - w_x -\sum\limits_{i=1}^{x-1}w_i < w_x$。也就是 $\sum\limits_{i=x+1}^{k}w_i < w_x$。显然的，我们删掉之后一定能将背包填满。所以我们需要找到最大的 $w_x$，满足 $w_x > \sum\limits_{i=x+1}^{k}w_i$。注意到 $n \le 5\times 10^5$，给了 $4s$。还有很显然的一点，满足条件 $w_x > \sum\limits_{i=x+1}^{k}w_i$ 的 $x$ 一定会在某个时刻后就一直满足，直到被删掉。那么我们用线段树维护区间 $w_x -\sum\limits_{i=x+1}^{k}w_i$ 的最大值，只要这个最大值 $>0$，就说明区间内存在满足的数。我们将这一轮新出现的满足的数全拿出来，放到大根堆里面。然后每次取堆顶删掉。由于一个数最多会被从线段树上拿一次，从堆里面删一次，所以时间复杂度 $O(n\log n)$。线段树需要支持区间求最大值，区间加。

## 代码

```cpp
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

const int N=5e5+10,inf=1e18;
int n;
int w[N],s[N];
struct Tree{
	int l,r,mx,tag;
}tr[N<<2];
priority_queue<pii> qu;
int res[N];

il void up(int u){tr[u].mx=max(tr[ls(u)].mx,tr[rs(u)].mx);}
il void down(int u){
	tr[ls(u)].tag+=tr[u].tag,tr[rs(u)].tag+=tr[u].tag;
	tr[ls(u)].mx+=tr[u].tag,tr[rs(u)].mx+=tr[u].tag;
	return tr[u].tag=0,void(0);
}
il void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r;
	if(l==r) return tr[u].mx=w[l]-s[l+1],void(0);
	int mid=l+r>>1;
	build(ls(u),l,mid),build(rs(u),mid+1,r);
	return up(u),void(0);
}
il void modify(int u,int l,int r,int x){
	if(l>r) return ;
	if(tr[u].l>=l&&tr[u].r<=r){
		tr[u].tag+=x,
		tr[u].mx+=x;
		return ;
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify(ls(u),l,r,x);
	if(mid< r) modify(rs(u),l,r,x);
	return up(u),void(0);
}
il void work(int u){
	if(tr[u].l==tr[u].r){
		if(tr[u].mx>0){
			qu.push({w[tr[u].l],tr[u].l});
			tr[u].mx=-inf;
		}
		return ;
	}
	down(u);
	if(tr[ls(u)].mx>0) work(ls(u));
	if(tr[rs(u)].mx>0) work(rs(u));
	return up(u),void(0);
}

il void solve(){
	n=rd;
	for(re int i=1;i<=n;++i) w[i]=rd;
	for(re int i=n;i>=1;--i) s[i]=s[i+1]+w[i];
	build(1,1,n),res[n]=s[1];
	for(re int i=n-1;i>=1;--i){
		work(1);
		pii u=qu.top();qu.pop();
		res[i]=res[i+1]-u.x;
		modify(1,1,u.y-1,u.x);
	}
	for(re int i=1;i<=n;++i) cout<<res[i]<<" ";
    return ;
}
```

---

## 作者：R_shuffle (赞：0)

正着加入是比较难直接搞的，所以考虑倒着删除。

如果 $k=n$ 那么就一定会全选。

设 $s_n=\sum\limits_{i=1}^na_i$。

不妨先考虑删去一个的方案。一个物品能被删除，当且仅当这个物品后面被选的所有物品的重量加起来不超过这个物品自身。形式化的，不妨设此时背包的容量为 $c$，且这个物品为 $i$，那么就要满足 $s_n-s_i<a_i$。此时背包的容量的限制为 $s_n-a_i\leq c<a_i$。由于需要求最小值，所以需要 $\min(s_n-a_i)=s_n-\max\limits_{s_n-s_i<a_i}a_i$。那么删掉一个物品显然就会对 $s$ 造成影响。直接找一个数据结构维护一下这玩意。然后再用一个堆来维护最值即可。

时间复杂度 $O(n\log n)$。

---

## 作者：Acit (赞：0)

**思路**

正着不好做，那就倒着考虑。

$w_i$ 能被移出背包当且仅当此时 $\sum_{j=i+1}^{k} w_j < w_i$（$w$ 为此时剩余的数组）。这就启发我们维护后缀和数组。

记 $s_i=\sum_{j=i+1}^{n}w_j$，$d_i=s_i-w_i$，我们每次应选出最大的满足 $w_i>s_i$ （即 $d_i<0$）的 $w_i$ 并将其移出数组（贪心的正确性不难证明）。

取出 $w_i$ 后我们应对 $d_1$ 到 $d_{i-1}$ 做区间减，如果某个 $d_j<0$，则将对应的 $w_j$ 加入备选答案。

由于每个 $d_i$ 只会在某一次操作后小于 $0$，所以总时间复杂度为 $O(n\log n)$。

**Code**


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define forr(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
const int N=5e5+10,INF=LLONG_MAX/2,T=1e9+1;
int n;
int a[N],sum[N],ans[N];
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
int tag[N<<2],mn[N<<2],mx[N<<2];
void mt(int k){
	mn[k]=min(mn[ls],mn[rs]);
	mx[k]=max(mx[ls],mx[rs]);
}
void build(int k,int l,int r){
	if(l==r){
		if(a[l]>sum[l]){
			mx[k]=a[l];
			mn[k]=INF;
		}else{
			mn[k]=sum[l]-a[l];
		}
		return ;
	}
	build(ls,l,mid);build(rs,mid+1,r);
	mt(k);
}
void pd(int k){
	if(tag[k]>0){
		tag[ls]+=tag[k];tag[rs]+=tag[k];
		mn[ls]-=tag[k];mn[rs]-=tag[k];
		tag[k]=0;
	}
}
void update(int k,int l,int r,int x,int y,int d){
	if(l>y||r<x)return ;
	if(x<=l&&r<=y){
		if(mn[k]>=d){
			tag[k]+=d;
			mn[k]-=d;
			return ;
		}
		if(l==r){
			mn[k]=INF;
			mx[k]=a[l];
			return ;
		}
	}
	pd(k);
	update(ls,l,mid,x,y,d);
	update(rs,mid+1,r,x,y,d);
	mt(k);
}
pair<int,int> getans(int k,int l,int r){
	if(l==r)return {a[l],l};
	if(mx[ls]>mx[rs])return getans(ls,l,mid);
	return getans(rs,mid+1,r);
}
void cl(int k,int l,int r,int x){
	if(l>x||r<x)return ;
	if(l==r){
		mn[k]=INF;mx[k]=0;return ;
	}
	pd(k);
	cl(ls,l,mid,x);cl(rs,mid+1,r,x);
	mt(k);
}
signed main() {
	ios::sync_with_stdio(0);
//	freopen("trr.in","r",stdin);
//	freopen("trr.out","w",stdout);
	cin>>n;
	forr(i,1,n)cin>>a[i],ans[n]+=a[i];
	roff(i,n-1,1)sum[i]=sum[i+1]+a[i+1];
	build(1,1,n);
	roff(i,n-1,1){
		pair<int,int> dd=getans(1,1,n);
		ans[i]=ans[i+1]-dd.first;
		update(1,1,n,1,dd.second-1,dd.first);
		cl(1,1,n,dd.second);
	}
	forr(i,1,n){
		cout<<ans[i]<<' ';
	}
	return 0;
}
/*

*/
```

---

