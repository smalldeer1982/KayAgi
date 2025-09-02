# Campus

## 题目描述

Oscolcovo city has a campus consisting of $ n $ student dormitories, $ n $ universities and $ n $ military offices. Initially, the $ i $ -th dormitory belongs to the $ i $ -th university and is assigned to the $ i $ -th military office.

Life goes on and the campus is continuously going through some changes. The changes can be of four types:

1. University $ a_{j} $ merges with university $ b_{j} $ . After that all the dormitories that belonged to university $ b_{j} $ are assigned to to university $ a_{j} $ , and university $ b_{j} $ disappears.
2. Military office $ c_{j} $ merges with military office $ d_{j} $ . After that all the dormitories that were assigned to military office $ d_{j} $ , are assigned to military office $ c_{j} $ , and military office $ d_{j} $ disappears.
3. Students of university $ x_{j} $ move in dormitories. Lets $ k_{xj} $ is the number of dormitories that belong to this university at the time when the students move in. Then the number of students in each dormitory of university $ x_{j} $ increases by $ k_{xj} $ (note that the more dormitories belong to the university, the more students move in each dormitory of the university).
4. Military office number $ y_{j} $ conducts raids on all the dormitories assigned to it and takes all students from there.

Thus, at each moment of time each dormitory is assigned to exactly one university and one military office. Initially, all the dormitory are empty.

Your task is to process the changes that take place in the campus and answer the queries, how many people currently live in dormitory $ q_{j} $ .

## 说明/提示

Consider the first sample test:

- In the first query university 1 owns only dormitory 1, so after the query dormitory 1 will have 1 student.
- After the third query university 1 owns dormitories 1 and 2.
- The fourth query increases by 2 the number of students living in dormitories 1 and 2 that belong to university number 1. After that 3 students live in the first dormitory and 2 students live in the second dormitory.
- At the fifth query the number of students living in dormitory 1, assigned to the military office 1, becomes zero.

## 样例 #1

### 输入

```
2 7
A 1
Q 1
U 1 2
A 1
Z 1
Q 1
Q 2
```

### 输出

```
1
0
2
```

## 样例 #2

### 输入

```
5 12
U 1 2
M 4 5
A 1
Q 1
A 3
A 4
Q 3
Q 4
Z 4
Q 4
A 5
Q 5
```

### 输出

```
2
1
1
0
1
```

# 题解

## 作者：hs_black (赞：28)

# CF571D Campus

[blog](https://www.cnblogs.com/Hs-black/p/12549222.html)内获得更佳体验

一翻题解, 都是建虚点的离线做法, 这里提供一个更好想也更好写的在线做法(雾

一看涉及到合并, 就想到了并查集, 但有一些加啊, 赋值啊, 所以不可路径压缩, 那就按秩合并呗

按秩合并就是通过合并时把较小的联通块叫较大的连通块爸爸莱保证严格log的时间复杂度, 同时, 一个连通块的高度也是log的

按秩合并的好处就是它的内部形态不会变, 如果打标记回比较方便

回到本题, 建立两颗按秩合并的并查集$f，g$， $f$每个点维护一个$vector$<$pair$<$t, add$>>表示在$t$时间内加了$add$的三操作标记，这里是前缀和的形式，方便后面二分查找时间$t$以后的$add$值之和

* 一二操作：除了正常合并还要维护合并的时间
* 三操作：直接把树根$push\_back$(时间， $siz + sum$)
* 四操作：直接把树根清除时间更改为$t$

**较为困难的五操作**

之前维护的那么多都是为五操作服务的（废话

树高是$log$的， 所以可以从一个点暴力向上跳，先去跳$g$，找出x点最近一次清零的时刻t，注意一个细节：如果$x$的父亲和$x$相连时刻比标记的时间大，则标记对$x$是无效的， 这点对$add$标记同理

然后跳$f$，在从$x$到根的每个点上二分查找大于清零时间和相连时间的标记和， 最后加起来就是答案

时间复杂度$\Theta(nlog^2n)$，二分在随机情况下跑不满，事实上跑的挺快的

```cpp
const int N = 500500;
int gs[N], fs[N], n, m;
int f[N], g[N], ft[N], gt[N];
char opt[5];

int find(int *f, int x) { while (x ^ f[x]) x = f[x]; return x; }
inline void merge(int *f, int *siz, int *t, int x, int y, int k) {
	x = find(f, x), y = find(f, y);
	if (siz[x] < siz[y]) swap(x, y);
	siz[x] += siz[y], f[y] = x, t[y] = k;
}

int cls[N];
vector<pair<int, ll> > add[N];
#define MP make_pair

int main() {
	read(n), read(m);
	for (int i = 1;i <= n; i++) fs[f[i] = g[i] = i] = gs[i] = 1, add[i].push_back(MP(-1, 0));
	for (int i = 1;i <= m; i++) {
		scanf ("%s", opt); int x, y; read(x);
		switch (opt[0]) {
			case 'U' : read(y), merge(f, fs, ft, x, y, i); break;
			case 'M' : read(y), merge(g, gs, gt, x, y, i); break;
			case 'A' : { int k = find(f, x); add[k].push_back(MP(i, fs[k] + add[k].back().second)); break; }
			case 'Z' : { int k = find(g, x); cls[k] = i; break; }
			case 'Q' : {
				int fx = x, tag = cls[x];
				while (g[fx] != fx) {
					if (cls[g[fx]] > gt[fx]) tag = max(tag, cls[g[fx]]);
					fx = g[fx];
				}
				fx = x;  int l = lower_bound(add[x].begin(), add[x].end(), MP(tag, 0ll)) - add[x].begin();
				ll ans = add[x].back().second - add[x][l-1].second;
				while (f[fx] != fx) {
					int tf = f[fx];
					l = lower_bound(add[tf].begin(), add[tf].end(), MP(max(tag, ft[fx]), 0ll)) - add[tf].begin();
					ans += add[tf].back().second - add[tf][l-1].second; fx = f[fx];
				}
				printf ("%lld\n", ans);
			}
		}
	}
	return 0;
}
```



---

## 作者：jiangly (赞：15)

#### 题意

维护两个大小为 $n$ 的森林，初始时所有节点单独为一棵树，支持合并两棵树、第一个森林子树加、第二个森林子树赋 $0$ 和查询一个点的值（两个森林中编号相同的为同一个点），共 $m$ 次操作。

#### 限制

$1\le n,m\le 5\cdot10^5$。

#### 题解

合并时新建一个虚点，先离线把森林建出来，问题就转化为了两个森林分别的子树加、子树赋值。而如果我们求出了每次询问前最后一次赋值的时间，询问的答案就变成了区间求和。

于是先后对两个森林进行 DFS，树状数组维护即可。

时间复杂度：$O(n + m\log m)$。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 500000;
struct Tree {
    int n;
    vector<int> parent, lc, rc, id;
    vector<vector<int>> mod;
    Tree(int n) {
        parent.assign(2 * n - 1, -1);
        lc.assign(2 * n - 1, -1);
        rc.assign(2 * n - 1, -1);
        id.resize(n);
        iota(id.begin(), id.end(), 0);
        mod.resize(2 * n - 1);
    }
};
long long fen[N + 1];
void add(int x, int y) {
    for (int i = x + 1; i <= N; i += i & -i)
        fen[i] += y;
}
long long sum(int x) {
    long long res = 0;
    for (int i = x; i > 0; i -= i & -i)
        res += fen[i];
    return res;
}
long long sum(int l, int r) {return sum(r) - sum(l);}
int getLeft(int x) {
    int s = sum(x);
    x = 0;
    for (int i = 1 << 18; i > 0; i /= 2) {
        if (x + i <= N && fen[x + i] < s) {
            x += i;
            s -= fen[x];
        }
    }
    return x;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Tree t1(n), t2(n);
    vector<vector<int>> query(n);
    vector<int> lb(m), sz(2 * n - 1, 1);
    vector<long long> ans(m, -1);
    int c1 = 0, c2 = 0;
    for (int i = 0; i < m; ++i) {
        char op;
        cin >> op;
        if (op == 'U') {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
            int p = n + (c1++);
            t1.parent[t1.id[a]] = t1.parent[t1.id[b]] = p;
            t1.lc[p] = t1.id[a];
            t1.rc[p] = t1.id[b];
            t1.id[a] = p;
            sz[p] = sz[t1.lc[p]] + sz[t1.rc[p]];
        } else if (op == 'M') {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
            int p = n + (c2++);
            t2.parent[t2.id[a]] = t2.parent[t2.id[b]] = p;
            t2.lc[p] = t2.id[a];
            t2.rc[p] = t2.id[b];
            t2.id[a] = p;
        } else if (op == 'A') {
            int x;
            cin >> x;
            --x;
            t1.mod[t1.id[x]].push_back(i);
        } else if (op == 'Z') {
            int x;
            cin >> x;
            --x;
            t2.mod[t2.id[x]].push_back(i);
        } else {
            int x;
            cin >> x;
            --x;
            query[x].push_back(i);
        }
    }
    function<void(int)> dfs1 = [&](int u) {
        for (int i : t2.mod[u])
            add(i, 1);
        if (u < n) {
            for (int i : query[u])
                lb[i] = getLeft(i);
        } else {
            dfs1(t2.lc[u]);
            dfs1(t2.rc[u]);
        }
        for (int i : t2.mod[u])
            add(i, -1);
    };
    function<void(int)> dfs2 = [&](int u) {
        for (int i : t1.mod[u])
            add(i, sz[u]);
        if (u < n) {
            for (int i : query[u])
                ans[i] = sum(lb[i], i);
        } else {
            dfs2(t1.lc[u]);
            dfs2(t1.rc[u]);
        }
        for (int i : t1.mod[u])
            add(i, -sz[u]);
    };
    for (int i = 0; i < n + c2; ++i)
        if (t2.parent[i] == -1)
            dfs1(i);
    for (int i = 0; i < n + c1; ++i)
        if (t1.parent[i] == -1)
            dfs2(i);
    for (int i = 0; i < m; ++i)
        if (ans[i] != -1)
            cout << ans[i] << "\n";
    return 0;
}
```



---

## 作者：tzc_wk (赞：7)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/571/problem/D) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF571D)

看到集合的合并，可以本能地想到并查集。

不过这题的操作与传统意义上的并查集不太一样，传统意义上的并查集一般是用来判断连通性的，而此题还需支持赋值、集合内整体加等操作，似乎就有些难处理。

我们不妨考虑此题的弱化版：没有第二类集合的版本。也就是要求支持合并两个集合，集合整体加某个数 $x$，单点查询三个操作。

很明显集合整体加某个数 $x$ 就相当于在并查集根节点处打一个 $+x$ 的标记，查询就暴力跳父亲求出待询问点到根节点路径上所有点的标记之和。不过稍微想想就知道这个做法是假的，因为如果直接采用按秩合并会导致标记加的点集出现问题，举个例子，比方说我们要合并 $x,y$ 两个集合，其中 $x$ 为父亲，我们假设原本 $x$ 点上有一个 $+v$ 的标记，显然这个标记所管辖的点的集合是原本 $x$ 所在的连通块，但经过我们这么一合并，我们默认每个标记管辖的点的集合是其子树，这也就意味着原本 $y$ 所在的集合也被错误地打上了 $+v$ 的标记，这样显然会出问题。我们考虑换个合并的思路，每次合并建立一个虚点 $z$，并让 $x,y$ 的父亲都为 $z$，这样就能保证每次标记管辖的点集是正确的了。但这样还会导致一个问题，那就是树的深度可能很大，暴力条父亲会 TLE。故考虑把操作离线下来，先建出最后的森林出来并求出 DFS 序，每次修改用线段树在待修改点的子树内整体加 $v$，查询就执行一次线段树上的单点查询即可，很明显森林里的点数最多为 $n+q$，故总复杂度 $(n+q)\log(n+q)$。

接下来考虑有第二类集合的版本，这个子树清空貌似维护起来有些困难，不过我们考虑换个思路，使用差分的思想，询问某个点 $x$ 的值可以转化为此时 $x$ 点的权值减去上一次 $x$ 点被清空前 $x$ 点的权值。故我们只用求出每次询问，带询问点上一次被清空的时间即可。那么这个东西怎么求呢？其实与弱化版维护的思路大同小异，先离线建出第二类集合的森林出来，每次清空一个节点 $x$ 就相当于在 $x$ 子树内所有点赋值 $t$（其中 $t$ 为此次操作的时间），表示这些点上一次被清空是时间 $t$，这个可以用区间赋值、单点查询的线段树维护。

到这里题目基本上已经做完了，不妨理理思路。我们先将询问离线下来，建出两类集合并查集所形成的森林，并对两个森林各进行一遍 DFS 求出每个点的 DFS 序，第二次扫描全部与第二类集合有关的操作，对于区间清空的操作就在子树对应 DFS 序的区间内执行区间赋值操作，如果遇到询问就进行一遍线段树上的单点查询，记录下待询问点上一次被清空的时间。第三次扫描全部与第一类集合有关的操作，对于区间加的操作就在子树对应 DFS 序的区间内执行区间加操作，如果遇到询问就进行一遍线段树上的单点查询，这样就可以求出答案了。

时间复杂度 $(n+q)\log(n+q)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=5e5;
int n,qu;
struct solver{
	int bel[MAXN+5],siz[MAXN*2+5],tot;
	void init(){
		for(int i=1;i<=n;i++) bel[i]=i,siz[i]=1;
		tot=n;
	}
	int hd[MAXN*2+5],nxt[MAXN*2+5],to[MAXN*2+5],ec=0;
	void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
	void merge(int x,int y){
		tot++;adde(tot,bel[x]);adde(tot,bel[y]);
		siz[x]+=siz[y];siz[y]=0;bel[y]=0;bel[x]=tot;
	}
	int dfn[MAXN*2+5],sz[MAXN*2+5],tim=0;
	void dfs(int x){
		dfn[x]=++tim;sz[x]=1;
		for(int e=hd[x];e;e=nxt[e]) dfs(to[e]),sz[x]+=sz[to[e]];
	}
} s1,s2;
struct event{int opt,x,y;} q[MAXN+5];
vector<int> clr[MAXN+5];
ll res[MAXN+5];
struct seg1{
	struct node{int l,r;ll v,lz;} s[MAXN*8+5];
	void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;if(l==r) return;
		int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	}
	void pushdown(int k){
		if(s[k].lz){
			s[k<<1].v+=s[k].lz*(s[k<<1].r-s[k<<1].l+1);
			s[k<<1].lz+=s[k].lz;
			s[k<<1|1].v+=s[k].lz*(s[k<<1|1].r-s[k<<1|1].l+1);
			s[k<<1|1].lz+=s[k].lz;
			s[k].lz=0;
		}
	}
	void modify(int k,int l,int r,int x){
		if(l<=s[k].l&&s[k].r<=r){
			s[k].v+=1ll*x*(s[k].r-s[k].l+1);s[k].lz+=x;
			return;
		} pushdown(k);int mid=s[k].l+s[k].r>>1;
		if(r<=mid) modify(k<<1,l,r,x);
		else if(l>mid) modify(k<<1|1,l,r,x);
		else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
		s[k].v=s[k<<1].v+s[k<<1|1].v;
	}
	ll query(int k,int x){
		if(s[k].l==s[k].r) return s[k].v;
		pushdown(k);int mid=s[k].l+s[k].r>>1;
		if(x<=mid) return query(k<<1,x);
		else return query(k<<1|1,x);
	}
} st1;
struct seg2{
	struct node{int l,r,tag;} s[MAXN*8+5];
	void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;if(l==r) return;
		int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	}
	void pushdown(int k){
		if(s[k].tag){
			s[k<<1].tag=s[k].tag;s[k<<1|1].tag=s[k].tag;
			s[k].tag=0;
		}
	}
	void modify(int k,int l,int r,int x){
		if(l<=s[k].l&&s[k].r<=r){s[k].tag=x;return;}
		pushdown(k);int mid=s[k].l+s[k].r>>1;
		if(r<=mid) modify(k<<1,l,r,x);
		else if(l>mid) modify(k<<1|1,l,r,x);
		else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	}
	int query(int k,int x){
		if(s[k].l==s[k].r) return s[k].tag;
		pushdown(k);int mid=s[k].l+s[k].r>>1;
		if(x<=mid) return query(k<<1,x);
		else return query(k<<1|1,x);
	}
} st2;
int main(){
	scanf("%d%d",&n,&qu);s1.init();s2.init();
	for(int i=1;i<=qu;i++){
		char opt[5];scanf("%s",opt+1);
		if(opt[1]=='U'){
			int x,y;scanf("%d%d",&x,&y);s1.merge(x,y);
			q[i].opt=1;q[i].x=x;q[i].y=y;
		} else if(opt[1]=='M'){
			int x,y;scanf("%d%d",&x,&y);s2.merge(x,y);
			q[i].opt=2;q[i].x=x;q[i].y=y;
		} else if(opt[1]=='A'){
			int x;scanf("%d",&x);
			q[i].opt=3;q[i].x=s1.bel[x];q[i].y=s1.siz[x];
		} else if(opt[1]=='Z'){
			int x;scanf("%d",&x);
			q[i].opt=4;q[i].x=s2.bel[x];
		} else{
			int x;scanf("%d",&x);
			q[i].opt=5;q[i].x=x;
		}
	}
	s1.tot++;for(int i=1;i<=n;i++) if(s1.siz[i]) s1.adde(s1.tot,s1.bel[i]);
	s2.tot++;for(int i=1;i<=n;i++) if(s2.siz[i]) s2.adde(s2.tot,s2.bel[i]);
	s1.dfs(s1.tot);s2.dfs(s2.tot);
	st1.build(1,1,s1.tot);st2.build(1,1,s2.tot);
	for(int i=1;i<=qu;i++){
		if(q[i].opt==4) st2.modify(1,s2.dfn[q[i].x],s2.dfn[q[i].x]+s2.sz[q[i].x]-1,i);
		if(q[i].opt==5){
			int tmp=st2.query(1,s2.dfn[q[i].x]);
			if(tmp) clr[tmp].pb(i);
		}
	}
	for(int i=1;i<=qu;i++){
		if(q[i].opt==3) st1.modify(1,s1.dfn[q[i].x],s1.dfn[q[i].x]+s1.sz[q[i].x]-1,q[i].y);
		if(q[i].opt==4){
			for(int j=0;j<clr[i].size();j++){
				int id=clr[i][j];
				res[id]-=st1.query(1,s1.dfn[q[id].x]);
			}
		}
		if(q[i].opt==5){
			res[i]+=st1.query(1,s1.dfn[q[i].x]);
			printf("%lld\n",res[i]);
		}
	}
	return 0;
}
```



---

## 作者：xht (赞：7)

> [CF571D Campus](https://codeforces.com/contest/571/problem/D)

## 题意

- 有一个长度为 $n$ 的序列，初始全为 $0$。
- 有两类对下标的集合，初始时每一类各有 $n$ 个集合，编号为 $i$ 的集合里有下标 $i$。
- 一共有 $m$ 个操作，操作有五种：
  1. `U x y` 将第一类编号为 $y$ 的集合合并到编号为 $x$ 的集合里。
  2. `M x y` 将第二类编号为 $y$ 的集合合并到编号为 $x$ 的集合里。
  3. `A x` 将第一类编号为 $x$ 的集合中的所有下标在序列中对应的数加上 $x$ 的集合大小。
  4. `Z x` 将第二类编号为 $x$ 的集合中的所有下标在序列中对应的数设为 $0$。
  5. `Q x` 询问序列中下标为 $x$ 的位置上的数。
- $n,m \le 5 \times 10^5$。

## 题解

如果我们能够利用 `M` 和 `Z` 操作求出对于每个询问的位置上次清零的时刻 $t$，那么这个询问的答案就应该是只保留 `U` 和 `A` 操作的情况下此时的值减去 $t$ 时刻的值。

那么我们要解决的问题可以分为两步：

1. 利用 `M` 和 `Z` 操作求出对于每个询问的位置上次清零的时刻 $t$。
2. 利用 `U` 和 `A` 操作求出对于每个询问的位置当前和时刻 $t$ 的值。

将询问离线后，建立 kruskal 重构树，那么这两步就分别相当于在 dfs 序上进行区间赋值和区间加，询问则相当于单点查询，线段树维护即可。

设 $n,m$ 同阶，时间复杂度为 $\mathcal O(n \log n)$。

## 代码

```cpp
const int N = 5e5 + 7;
int n, m, a[N];
char s[N], c[3];
vector<pi> q[N];
ll ans[N];

struct kruskal0 {
	int f[N*2], l[N*2], r[N*2], num, tot;
	vi e[N*2];
	struct T {
		int l, r, s;
	} t[N*8];
	inline void init() {
		for (int i = 1; i <= n; i++) f[i] = i;
		tot = n;
	}
	int get(int x) {
		return x == f[x] ? x : (f[x] = get(f[x]));
	}
	inline int add(int x, int y) {
		e[++tot].pb(x = get(x)), e[tot].pb(y = get(y));
		return f[x] = f[y] = f[tot] = tot;
	}
	void dfs(int x) {
		l[x] = ++num;
		for (auto y : e[x]) dfs(y);
		r[x] = num;
	}
	void build(int p, int l, int r) {
		t[p].l = l, t[p].r = r;
		if (l == r) return;
		build(ls, l, md), build(rs, md + 1, r);
	}
	inline void prework() {
		for (int i = 1; i <= tot; i++) if (get(i) == i) dfs(i);
		build(1, 1, tot);
	}
	inline void spd(int p) {
		if (t[p].s) t[ls].s = t[rs].s = t[p].s, t[p].s = 0;
	}
	void set(int p, int l, int r, int x) {
		if (t[p].l >= l && t[p].r <= r) return t[p].s = x, void();
		spd(p);
		if (l <= md) set(ls, l, r, x);
		if (r > md) set(rs, l, r, x);
	}
	inline void set(int i) {
		set(1, l[a[i]], r[a[i]], i);
	}
	int asks(int p, int x) {
		if (t[p].l == t[p].r) return t[p].s;
		spd(p);
		return asks(x <= md ? ls : rs, x);
	}
	inline int asks(int i) {
		return asks(1, l[a[i]]);
	}
} t0;

struct kruskal1 {
	int f[N*2], s[N*2], l[N*2], r[N*2], num, tot;
	vi e[N*2];
	struct T {
		int l, r;
		ll a;
	} t[N*8];
	inline void init() {
		for (int i = 1; i <= n; i++) f[i] = i;
		tot = n;
	}
	int get(int x) {
		return x == f[x] ? x : (f[x] = get(f[x]));
	}
	inline int add(int x, int y) {
		e[++tot].pb(x = get(x)), e[tot].pb(y = get(y));
		return f[x] = f[y] = f[tot] = tot;
	}
	void dfs(int x) {
		l[x] = ++num, s[x] = x <= n;
		for (auto y : e[x]) dfs(y), s[x] += s[y];
		r[x] = num;
	}
	void build(int p, int l, int r) {
		t[p].l = l, t[p].r = r;
		if (l == r) return;
		build(ls, l, md), build(rs, md + 1, r);
	}
	inline void prework() {
		for (int i = 1; i <= tot; i++) if (get(i) == i) dfs(i);
		build(1, 1, tot);
	}
	inline void spd(int p) {
		if (t[p].a) t[ls].a += t[p].a, t[rs].a += t[p].a, t[p].a = 0;
	}
	void add(int p, int l, int r, int x) {
		if (t[p].l >= l && t[p].r <= r) return t[p].a += x, void();
		spd(p);
		if (l <= md) add(ls, l, r, x);
		if (r > md) add(rs, l, r, x);
	}
	inline void add(int x) {
		add(1, l[x], r[x], s[x]);
	}
	ll aska(int p, int x) {
		if (t[p].l == t[p].r) return t[p].a;
		spd(p);
		return aska(x <= md ? ls : rs, x);
	}
	inline ll aska(int x) {
		return aska(1, l[x]);
	}
} t1;

int main() {
	rd(n), rd(m), t1.init(), t0.init();
	for (int i = 1, x; i <= m; i++) {
		rds(c, x), s[i] = c[1], rd(a[i]);
		switch (s[i]) {
			case 'U' : rd(x), a[i] = t1.add(a[i], x); break;
			case 'M' : rd(x), a[i] = t0.add(a[i], x); break;
			case 'A' : a[i] = t1.get(a[i]); break;
			case 'Z' : a[i] = t0.get(a[i]); break;
		}
	}
	t1.prework(), t0.prework();
	for (int i = 1; i <= m; i++)
		switch (s[i]) {
			case 'Z' : t0.set(i); break;
			case 'Q' : q[t0.asks(i)].pb(mp(a[i], i)); break;
		}
	for (int i = 1; i <= m; i++)
		switch (s[i]) {
			case 'A' : t1.add(a[i]); break;
			case 'Z' : for (pi o : q[i]) ans[o.se] -= t1.aska(o.fi); break;
			case 'Q' : ans[i] += t1.aska(a[i]); break;
		}
	for (int i = 1; i <= m; i++) if (s[i] == 'Q') print(ans[i]);
	return 0;
}
```

---

## 作者：幻影星坚强 (赞：4)

假如没有第二个和第四个操作，那么就可以离线将最后的合并树求出，把操作看成在对应的树上的dfn序进行加操作直接使用线段树。

加上二和四操作，我们可以可以不把它当成清零操作，而是让这些节点以后的答案都减去当前节点的答案。因为只有单点查询，所以我们可以将前面的线段树改成可持久化线段树，并用新的一棵线段树来记录这些节点需要减去的时间，查询时直接查询出需要减去的时间，用当前答案减去查询得到的时间所对应的答案即可，时间复杂度 $O(nlogn)$ 。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const long long N = 5e5 + 10;
long long n, m;
struct bian
{
	long long from, to;
};
struct tree
{
	bian eg[N << 2];
	long long num, front[N << 1];
	long long zong;
	long long fa[N << 1], siz[N << 1];
	void add(long long x, long long y)
	{
		eg[++ num].to = y;
		eg[num].from = front[x];
		front[x] = num;
	}
	void init()
	{
		zong = n;
		for (long long i = 1; i <= zong; ++ i)
		fa[i] = i, siz[i] = 1;
	}
	long long find(long long x)
	{
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
	long long tot, now;
	long long son[N << 4][2];
	unsigned long long tag[N << 4];
	long long root[N];
	void merge(long long x, long long y)
	{
		long long d1 = find(x), d2 = find(y);
		fa[++ zong] = zong;
		add(zong, d1);
		add(zong, d2);
		siz[zong] = siz[find(x)] + siz[find(y)];
		fa[d1] = zong;
		fa[d2] = zong;
	}
	long long ll[N << 1], rr[N << 1], ids[N], p;
	void dfs(long long o)
	{
		if(o <= n)
		{
			ids[o] = ++ p;
			ll[o] = rr[o] = ids[o];
			return;
		}
		ll[o] = 1e9;
		for (long long i = front[o]; i; i = eg[i].from)
		{
			long long to = eg[i].to;
			dfs(to);
			ll[o] = min(ll[o], ll[to]);
			rr[o] = max(rr[o], rr[to]);
		}
	}
	void opt1(long long be, long long &o, long long l, long long r, long long L, long long R, long long w)
	{
		if(o == 0)o = ++ tot;
		tag[o] = tag[be]; 
		if(L <= l && r <= R)
		{
			tag[o] += w;
			son[o][0] = son[be][0];
			son[o][1] = son[be][1];
			return;
		}
		long long mid = (l + r) >> 1;
		if(mid >= L)opt1(son[be][0], son[o][0], l, mid, L, R, w);else son[o][0] = son[be][0];
		if(mid < R)opt1(son[be][1], son[o][1], mid + 1, r, L, R, w);else son[o][1] = son[be][1];
	}
	unsigned long long opt2(long long o, long long l, long long r, long long i, unsigned long long now)
	{
		if(o == 0)return now;
		if(l == r)
			return now + tag[o];
		long long mid = (l + r) >> 1;
		if(mid >= i)return opt2(son[o][0], l, mid, i, now + tag[o]);
		else return opt2(son[o][1], mid + 1, r, i, now + tag[o]);
	}
}T1;
struct tree_
{
	bian eg[N << 2];
	long long num, front[N << 1];
	long long zong;
	long long fa[N << 1];
	void add(long long x, long long y)
	{
		eg[++ num].to = y;
		eg[num].from = front[x];
		front[x] = num;
	}
	void init()
	{
		zong = n;
		for (long long i = 1; i <= zong; ++ i)
		fa[i] = i;
	}
	long long find(long long x)
	{
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
	void merge(long long x, long long y)
	{
		long long d1 = find(x), d2 = find(y);
		fa[++ zong] = zong;
		add(zong, d1);
		add(zong, d2);
		fa[d1] = zong;
		fa[d2] = zong;
	}
	long long ll[N << 1], rr[N << 1], ids[N], p;
	void dfs(long long o)
	{
		if(o <= n)
		{
			ids[o] = ++ p;
			ll[o] = rr[o] = ids[o];
			return;
		}
		ll[o] = 1e9;
		for (long long i = front[o]; i; i = eg[i].from)
		{
			long long to = eg[i].to;
			dfs(to);
			ll[o] = min(ll[o], ll[to]);
			rr[o] = max(rr[o], rr[to]);
		}
	}
	long long col[N << 2];
	void opt3(long long o, long long l, long long r, long long L, long long R, long long w)
	{
		if(L <= l && r <= R)
		{
			col[o] = w;
			return;
		}
		long long mid = (l + r) >> 1;
		if(col[o])
		{
			col[o << 1] = col[o << 1 | 1] = col[o];
			col[o] = 0;
		}
		if(mid >= L) opt3(o << 1, l, mid, L, R, w);
		if(mid < R) opt3(o << 1 | 1, mid + 1, r, L, R, w);
	}
	long long opt4(long long o, long long l, long long r, long long i)
	{
		if(l == r)
		return col[o];
		long long mid = (l + r) >> 1;
		if(col[o])
		{
			col[o << 1] = col[o << 1 | 1] = col[o];
			col[o] = 0;
		}
		if(mid >= i)return opt4(o << 1, l, mid, i);
		else return opt4(o << 1 | 1, mid + 1, r, i);
	}
	
}T2;
long long que[N][3];
struct b
{
	long long fa[N << 1], zong;
	void init()
	{
		zong = n;
		for (long long i = 1; i <= n; ++ i)
		fa[i] = i;
	}
	long long find(long long o)
	{
		return fa[o] == o ? o : fa[o] = find(fa[o]);
	}
	void merge(long long x, long long y)
	{
		long long d1 = find(x), d2 = find(y);
		fa[++ zong] = zong;
		fa[d1] = zong;
		fa[d2] = zong;
	}
}B1, B2;
long long main()
{
	scanf("%d%d", &n, &m);
	T1.init();
	T2.init();
	for (long long i = 1; i <= m; ++ i)
	{
		char s[10];
		scanf("%s", s);
		if(s[0] == 'U')
		{
			long long x, y;
			scanf("%d%d", &x, &y);
			que[i][0] = 1;
			que[i][1] = x;
			que[i][2] = y;
			T1.merge(x, y);
		}
		if(s[0] == 'M')
		{
			long long x, y;
			scanf("%d%d", &x, &y);
			que[i][0] = 2;
			que[i][1] = x;
			que[i][2] = y;
			T2.merge(x, y);
		}
		if(s[0] == 'A')
		{
			long long x;
			scanf("%d", &x);
			que[i][0] = 3;
			que[i][1] = x;
		}
		if(s[0] == 'Z')
		{
			long long x;
			scanf("%d", &x);
			que[i][0] = 4;
			que[i][1] = x;
		}
		if(s[0] == 'Q')
		{
			long long x;
			scanf("%d", &x);
			que[i][0] = 5;
			que[i][1] = x;
		}
	}
	for (long long i = 1; i <= T1.zong; ++ i)
	if(T1.find(i) == i)
	T1.dfs(i);
	for (long long i = 1; i <= T2.zong; ++ i)
	if(T2.find(i) == i)
	T2.dfs(i);
	B1.init();
	B2.init();
	for (long long i = 1; i <= m; ++ i)
	{
		if(que[i][0] == 1)
		{
			B1.merge(que[i][1], que[i][2]);
		}
		if(que[i][0] == 2)
		{
			B2.merge(que[i][1], que[i][2]);
		}
		if(que[i][0] == 3)
		{
			++ T1.now;
			T1.opt1(T1.root[T1.now - 1], T1.root[T1.now], 1, n, T1.ll[B1.find(que[i][1])], T1.rr[B1.find(que[i][1])], T1.siz[B1.find(que[i][1])]);
		}
		if(que[i][0] == 4)
		{
//			printf("%d %d %d %d\n", B2.find(que[i][1]), T2.ll[B2.find(que[i][1])], T2.rr[B2.find(que[i][1])], T1.now);
			T2.opt3(1, 1, n, T2.ll[B2.find(que[i][1])], T2.rr[B2.find(que[i][1])], T1.now);
		}
		if(que[i][0] == 5)
		{
//			printf("%d\n", T1.ids[que[i][1]]);
			printf("%lld\n", T1.opt2(T1.root[T1.now], 1, n, T1.ids[que[i][1]], 0) - T1.opt2(T1.root[T2.opt4(1, 1, n, T2.ids[que[i][1]])], 1, n, T1.ids[que[i][1]], 0));
		}
	}
}
```


---

## 作者：xtx1092515503 (赞：1)

~~冬令营，没听懂，水题解~~

这个中文翻译十分精妙，使用的是**集合**的**合并**这种表达。

集合的合并要用什么？**~~冰茶姬~~并查集**。

我们尝试切换到冰茶姬的视角看一下各个操作的具体效果：

```U x y```：在集合$A$中将$y$并入$x$；

```M x y```：在集合$B$中将$y$并入$x$；

```A x```：在集合$A$中进行**子树加**；

```Z x```：在集合$B$中进行**子树清空**；

```Q x```：询问。

```A```操作，可以被看作是打子树加的tag；```Z```操作，可以被看作是打子树清空的tag。

考虑**扫描线/二维数点**等等东西的思想，我们可以不再真实地执行清空子树的操作，转而将答案看作是：当前这个节点的值，减去它上一次被清空时这个节点的值。

具体的做法，我们可以将操作离散下来，第一遍建出合并的树出来（冰茶姬的树形结构），然后用dfs序将子树操作拍扁；

第二遍关于每次询问，找到上一次清空的时间（具体操作是，在清空时，我们用线段树给子树打上此次清空的tag；然后在询问时，直接在线段树上询问）。

第三遍维护子树加的操作，仿照二维数点等等做法，同时统计答案并输出。

需要注意的是，这题关于操作我们要建出虚点，然后把两个集合全都并到虚点上（而不是传统冰茶姬意义上的直接合并）。并且，因为这题我们要的主要是那棵树，因此甚至连冰茶姬都不需要，直接建出操作树就行了。至于为什么要建虚点，是为了确保在每次子树加时加的位置正确（有可能一些子树是在子树加后再并进来的，但子树加是离线的，因此我们必须确保每次子树加只加到了当前在子树内的点上）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1)
int n,m,lim1,lim2;
ll res[500100];
struct qwq{
	int head[1001000],cnt,dfn[1001000],sz[1001000],bel[500100],tot,cmp,bsz[5001000];
	struct node{
		int to,next;
	}edge[2001000];
	void ae(int u,int v){
		edge[cnt].next=head[u],edge[cnt].to=v,head[u]=cnt++;
	}
	void merge1(int x,int y){//merge x into y
		tot++,bsz[y]+=bsz[x],bsz[x]=0;
		ae(tot,bel[x]),ae(tot,bel[y]),bel[y]=tot;
	}
	void merge2(int x,int y){bsz[y]+=bsz[x],bsz[x]=0,bel[y]=++tot;}
	void dfs(int x){
		sz[x]=1,dfn[x]=++cmp;
		for(int i=head[x];i!=-1;i=edge[i].next)dfs(edge[i].to),sz[x]+=sz[edge[i].to];
	}
	void ini(){
		tot=n;
		for(int i=1;i<=n;i++)bel[i]=i,bsz[i]=1;
	}
}cam,pol;
struct st1{
	ll tag[4001000];
	void pushdown(int x){
		tag[lson]+=tag[x],tag[rson]+=tag[x],tag[x]=0;
	}
	void add(int x,int l,int r,int L,int R,int val){
		if(l>R||r<L)return;
		if(L<=l&&r<=R){tag[x]+=val;return;}
		pushdown(x),add(lson,l,mid,L,R,val),add(rson,mid+1,r,L,R,val);
	}
	ll query(int x,int l,int r,int P){
		if(l>P||r<P)return 0;
		if(l==r)return tag[x];
		pushdown(x);
		return query(lson,l,mid,P)+query(rson,mid+1,r,P);
	}
}s1;
struct st2{
	ll tag[4001000];
	void pushdown(int x){
		if(tag[x])tag[lson]=tag[x],tag[rson]=tag[x],tag[x]=0;
	}
	void cg(int x,int l,int r,int L,int R,int val){
		if(l>R||r<L)return;
		if(L<=l&&r<=R){tag[x]=val;return;}
		pushdown(x),cg(lson,l,mid,L,R,val),cg(rson,mid+1,r,L,R,val);
	}
	ll query(int x,int l,int r,int P){
		if(l>P||r<P)return 0;
		if(l==r)return tag[x];
		pushdown(x);
		return query(lson,l,mid,P)+query(rson,mid+1,r,P);
	}
}s2;
struct opt{
	int tp,a,b;
	vector<int>v;
}q[500100];
int main(){
	scanf("%d%d",&n,&m),memset(cam.head,-1,sizeof(cam.head)),memset(pol.head,-1,sizeof(pol.head));
	cam.ini(),pol.ini();
	for(int i=1;i<=m;i++){
		char s[10];
		scanf("%s",s);
		if(s[0]=='U')q[i].tp=1,scanf("%d%d",&q[i].b,&q[i].a),cam.merge1(q[i].a,q[i].b);
		if(s[0]=='M')q[i].tp=2,scanf("%d%d",&q[i].b,&q[i].a),pol.merge1(q[i].a,q[i].b);
		if(s[0]=='A')q[i].tp=3,scanf("%d",&q[i].a);
		if(s[0]=='Z')q[i].tp=4,scanf("%d",&q[i].a);
		if(s[0]=='Q')q[i].tp=5,scanf("%d",&q[i].a);
	}
	cam.tot++,pol.tot++;
	for(int i=1;i<=n;i++){
		if(cam.bsz[i])cam.ae(cam.tot,cam.bel[i]);
		if(pol.bsz[i])pol.ae(pol.tot,pol.bel[i]);
	}
	cam.dfs(cam.tot),pol.dfs(pol.tot);
	lim1=cam.tot,lim2=pol.tot;
	cam.ini(),pol.ini();
//	for(int i=1;i<=lim1;i++)printf("A:%d %d\n",cam.dfn[i],cam.sz[i]);
//	for(int i=1;i<=lim2;i++)printf("B:%d %d\n",pol.dfn[i],pol.sz[i]);
	for(int i=1;i<=m;i++){
		if(q[i].tp==2)pol.merge2(q[i].a,q[i].b);
		if(q[i].tp==4)s2.cg(1,1,lim2,pol.dfn[pol.bel[q[i].a]],pol.dfn[pol.bel[q[i].a]]+pol.sz[pol.bel[q[i].a]]-1,i);
		if(q[i].tp==5){
			int tmp=s2.query(1,1,lim2,pol.dfn[q[i].a]);
			q[tmp].v.push_back(i);
		}
	}
	for(int i=1;i<=m;i++){
		if(q[i].tp==1)cam.merge2(q[i].a,q[i].b);
		if(q[i].tp==3)s1.add(1,1,lim1,cam.dfn[cam.bel[q[i].a]],cam.dfn[cam.bel[q[i].a]]+cam.sz[cam.bel[q[i].a]]-1,cam.bsz[q[i].a]);
		if(q[i].tp==4)for(int j=0;j<q[i].v.size();j++)res[q[i].v[j]]-=s1.query(1,1,lim1,cam.dfn[q[q[i].v[j]].a]);
		if(q[i].tp==5)res[i]+=s1.query(1,1,lim1,cam.dfn[q[i].a]),printf("%lld\n",res[i]);
	}
	return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：0)

发现有两类独立的操作，提出来分开维护。           

根据题目特性按照时间分别建立两棵 Kruskal 重构树维护操作 $1,3$ 和操作 $2,4$，由于 $n$ 的规模达到 $5 \times 10 ^ 5$ 所以尝试一只 $\log$ 的做法。             

我们不难发现对于 $1,2$ 操作都是平凡的合并两棵树，这个就直接维护好了。    

对于 $3,4$ 操作我们不难发现相当于全都是当前的子树内做一次相关操作，我们直接将时间当作维度全部离线下来，$3$ 操作挂到第一类树的子树的根节点上，$4$ 操作挂到第二类树的子树的根节点上。          

对于 $5$ 的查询我们有一种显然的思路：即找到最后一次变 $0$ 的时间然后算出从最后一次变 $0$ 后中间时间段对它能产生的增加量，就是一次查询的答案，由于操作已经离线就尝试把查询离线下来。                

然后就比较套路了：先对第二类树 dfs 一遍然后把路上的所有 $4$ 操作涉及到的时间 $t$ 全部存下来，遍历到叶子节点时，当前挂在当前叶子节点的所有查询都拿出来问一遍自己时间的前驱，这样就可以得到该询问之前最后一次变 $0$ 的时间。结束 dfs 时就直接扔掉不能用的 $t$ 就行了。         

接着再对第一类树 dfs 一遍，把时间轴拿出来用线段树维护，路径上的操作都形如 $(x,y)$ 表示 $x$ 时间之后该值应该加上 $y$，这个反应在线段树上就是个单点修改，遍历到叶子节点时就再把挂好的询问拿出来问一次区间查询即可，时间复杂度 $O(n \log m + m \log m)$。               

不过需要注意数据也有可能生成森林，这个就对每个根跑一遍即可。       

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 5;
int n,m;bool flag[Len],flaw[Len];
struct Edger
{
	int id,lim,head[Len],cnt,siz[Len << 1];
	struct node
	{
		int next,to;
	}edge[Len << 1];
	void add(int from,int to){edge[++ cnt].to = to;edge[cnt].next = head[from];head[from] = cnt;}
}E1,E2;
struct UnionSet
{
	int fa[Len];
	void makeSet(int x){for(int i = 1 ; i <= x ; i ++) fa[i] = i;}
	int findSet(int x){return fa[x] == x ? fa[x] : fa[x] = findSet(fa[x]);}
}S1,S2;
char s[5];
struct Node
{
	int add,tim;
	Node(){add = tim = 0;}
	Node(int ADD,int TIM){add = ADD , tim = TIM;} 
};
bool cmp(Node x,Node y){return x.tim < y.tim;}
vector<Node> v[Len][3];
long long Print[Len],sum[Len << 2];
int x,y,maxn[Len << 2];;
#define ls(x) x << 1
#define rs(x) x << 1 | 1
void push_up(int x)
{
	sum[x] = sum[ls(x)] + sum[rs(x)];
	maxn[x] = max(maxn[ls(x)] , maxn[rs(x)]);
}
void build(int p,int l,int r)
{ 
	sum[p] = maxn[p] = 0;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
}
void updatetim(int p,int l,int r,int idx,int w)
{
	if(l == r) 
	{
		maxn[p] = w;
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) updatetim(ls(p) , l , mid , idx , w);
	else updatetim(rs(p) , mid + 1 , r , idx , w);
	push_up(p);
}
int Neartim(int p,int l,int r,int idx)
{
	//if(idx == 8) printf("%d %d %d\n",l,r,maxn[p]);
	if(l == r) 
	{
		if(!maxn[p]) return 0;
		return l;
	}
	int mid = (l + r) >> 1 , res = 0;
	if(mid < idx) 
	{
		res = max(res , maxn[ls(p)]);
		res = max(res , Neartim(rs(p) , mid + 1 , r , idx));
		return res;
	}
	return Neartim(ls(p) , l , mid , idx);
}
void updatesum(int p,int l,int r,int idx,int w)
{
	if(l == r)
	{
		sum[p] += w;
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) updatesum(ls(p) , l , mid , idx , w);
	else updatesum(rs(p) , mid + 1 , r , idx , w);
	push_up(p);
}
long long querysum(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return sum[p];
	int mid = (l + r) >> 1;long long res = 0;
	if(nl <= mid) res += querysum(ls(p) , l , mid , nl , nr);
	if(nr > mid) res += querysum(rs(p) , mid + 1 , r , nl , nr);
	return res;
}
void dfs2(int x,int f)
{
	flaw[x] |= 1;
	for(int i = 0 ; i < v[x][1].size() ; i ++) 
	{
		//if(x == 3) printf("###%d\n",v[x][1][i].tim);
		updatetim(1 , 1 , m , v[x][1][i].tim , v[x][1][i].tim);
	}
	if(x <= n)
	{
		for(int i = 0 ; i < v[x][2].size() ; i ++) 
		{
			Print[v[x][2][i].add] = Neartim(1 , 1 , m , v[x][2][i].tim);
			//if(Print[v[x][2][i].add] == -1) Print[v[x][2][i].add] = 0;
			//printf("%d %d\n",v[x][2][i].add,Print[v[x][2][i].add]);
		}
	}
	for(int e = E2.head[x] ; e ; e = E2.edge[e].next)
	{
		int to = E2.edge[e].to;
		if(to == f) continue;
		dfs2(to , x);
	}
	for(int i = 0 ; i < v[x][1].size() ; i ++) updatetim(1 , 1 , m , v[x][1][i].tim , 0);
}
void dfs1(int x,int f)
{
	flaw[x] |= 1;
	for(int i = 0 ; i < v[x][0].size() ; i ++) 
	{
		//if(x == 3) printf("###%d %d\n",v[x][0][i].tim,v[x][0][i].add);
		updatesum(1 , 1 , m , v[x][0][i].tim , v[x][0][i].add);
	}
	if(x <= n)
	{
		for(int i = 0 ; i < v[x][2].size() ; i ++) 
		{
			int num = Print[v[x][2][i].add];
			Print[v[x][2][i].add] = querysum(1 , 1 , m , num + 1 , v[x][2][i].tim);
		}
	} 
	for(int e = E1.head[x] ; e ; e = E1.edge[e].next)
	{
		int to = E1.edge[e].to;
		if(to == f) continue;
		dfs1(to , x);
	}
	for(int i = 0 ; i < v[x][0].size() ; i ++) updatesum(1 , 1 , m , v[x][0][i].tim , -v[x][0][i].add);
}
int main()
{
	scanf("%d %d",&n,&m);
	E1.id = n , E2.id = n;E1.lim = n << 1 , E2.lim = n << 1;
	for(int i = 1 ; i <= n ; i ++) E1.siz[i] = E2.siz[i] = 1;
	S1.makeSet(E1.lim) , S2.makeSet(E2.lim);
	for(int i = 1 ; i <= m ; i ++)
	{
		scanf("%s",s + 1);
		if(s[1] == 'U') 
		{
			scanf("%d %d",&x,&y);int u = S1.findSet(x) , v = S1.findSet(y); 
			if(u == v) continue;
			S1.fa[u] = S1.fa[v] = ++ E1.id;
			E1.siz[E1.id] = E1.siz[u] + E1.siz[v];
			E1.add(E1.id , u) , E1.add(E1.id , v);
		}
		else if(s[1] == 'M') 
		{
			scanf("%d %d",&x,&y);
			int u = S2.findSet(x) , v = S2.findSet(y);
			if(u == v) continue;
			S2.fa[u] = S2.fa[v] = ++ E2.id;
			E2.siz[E2.id] = E2.siz[u] + E2.siz[v];
			E2.add(E2.id , u) , E2.add(E2.id , v);
		}
		else if(s[1] == 'A')
		{
			scanf("%d",&x);
			x = S1.findSet(x);
			v[x][0].push_back(Node(E1.siz[x] , i));
		}
		else if(s[1] == 'Z')
		{
			scanf("%d",&x);
			x = S2.findSet(x);
			v[x][1].push_back(Node(0 , i));
		}
		else if(s[1] == 'Q') 
		{
			scanf("%d",&x);
			v[x][2].push_back(Node(i , i));
			flag[i] |= 1; 
		}
	}	
	build(1 , 1 , m);
	for(int i = E2.id ; i >= 1 ; i --) if(!flaw[i]) dfs2(i , 0);
	for(int i = 1 ; i <= E2.id ; i ++) flaw[i] = 0;
	//for(int i = 1 ; i <= m ; i ++) if(flag[i]) printf("###%lld\n",Print[i]);
	build(1 , 1 , m);
	for(int i = E1.id ; i >= 1 ; i --) if(!flaw[i]) dfs1(i , 0);
	for(int i = 1 ; i <= m ; i ++) if(flag[i]) printf("%lld\n",Print[i]); 
	return 0;
}
```

---

