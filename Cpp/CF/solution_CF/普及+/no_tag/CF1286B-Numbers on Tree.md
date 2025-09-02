# Numbers on Tree

## 题目描述

Evlampiy was gifted a rooted tree. The vertices of the tree are numbered from $ 1 $ to $ n $ . Each of its vertices also has an integer $ a_i $ written on it. For each vertex $ i $ , Evlampiy calculated $ c_i $ — the number of vertices $ j $ in the subtree of vertex $ i $ , such that $ a_j < a_i $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1286B/07b62e73f95acfbaad655944569605534cdd333f.png)Illustration for the second example, the first integer is $ a_i $ and the integer in parentheses is $ c_i $ After the new year, Evlampiy could not remember what his gift was! He remembers the tree and the values of $ c_i $ , but he completely forgot which integers $ a_i $ were written on the vertices.

Help him to restore initial integers!

## 样例 #1

### 输入

```
3
2 0
0 2
2 0```

### 输出

```
YES
1 2 1```

## 样例 #2

### 输入

```
5
0 1
1 3
2 1
3 0
2 0```

### 输出

```
YES
2 3 2 1 2```

# 题解

## 作者：ix35 (赞：12)

## CF 1286 B：Numbers on Tree

提供一种容易理解，和目前所有洛谷题解不同的做法。

题目要求构造一种权值方案，根据题目要求，其实只关心权值的**相对大小关系**。

因此我们可以先令一个集合 $S=\{1,\cdots,n\}$，并且算出 $S$ 中点权最小的一个点 $i$，将 $i$ 从 $S$ 中删去，再决定剩余 $S$ 中点的最小点权（即全树的次小点权），以此类推，做完 $n$ 轮以后就得到了所有点权的大小关系，再按顺序赋值 $1,\cdots,n$ 就得到了一种权值方案。

下面考虑怎么求出 $S$ 中权值最小者。

令 $d_i$ 表示满足 $j\in S$ 且 $j$ 在 $i$ 子树内的 $a_j<a_i$ 的个数，那么一开始 $d_i=c_i$。容易发现 $S$ 中点权最小的点的 $d_i$ 必然等于零（否则有一个更小的），下面就有两种处理方式：

1. 将所有 $d_i=0$ 的 $i$ 的点权设成一个相同的值 $C$，作为最小值。

2. 按照刚刚说的一个个来确定，如果有一对点是祖先关系，且 $d_i$ 都为 $0$，那么显然祖先应该小于等于后代（否则祖先的那个 $d_i$ 就不是 $0$ 了），所以在 $d_i=0$ 的情况下再按照深度从小到大排，决定权值大小。根据这种方法得到的权值是没有重复的。

从 $S$ 中取出最小值 $i$，还要对 $i$ 的所有祖先 $j$ 的 $d_j$ 值减 $1$，因为剩余集合中比 $j$ 小的数中已经不包含 $i$。

具体实现：可以用一个优先队列维护 $S$ 中所有 $d_i=0$ 的点 $i$，队列内按照深度排序，每次取出队首 $i$，将 $i$ 的所有祖先 $d_i$ 值减 $1$，如果减到了 $0$ 就将那个点加入优先队列。

注意如果某个时刻优先队列空了而还有点没有赋权，则答案就是 No。

时间复杂度为 $O(n^2)$，如果愿意的话可以优化到 $O(n\log n)$（只需要将祖先 $-1$ 这个操作用数据结构优化掉就可以了），代码比子树 sort 的要好理解一些吧。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2010;
int n,r,eg,dep[MAXN],f[MAXN],c[MAXN],a[MAXN],hd[MAXN],ver[2*MAXN],nx[2*MAXN];
struct cmp {
	bool operator () (int a,int b) {return dep[a]>dep[b];}
};
priority_queue <int,vector<int>,cmp> q;
void add_edge (int x,int y) {
	ver[++eg]=y;
	nx[eg]=hd[x];
	hd[x]=eg;
	return;
}
void dfs (int x,int fa) {
	dep[x]=dep[fa]+1;
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]!=fa) {
			dfs(ver[i],x);
		}
	}
	if (c[x]==0) {q.push(x);}
	return;
}
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&f[i],&c[i]);
		if (f[i]==0) {r=i;}
		if (f[i]) {add_edge(i,f[i]),add_edge(f[i],i);}
	}
	dfs(r,0);
	int cnt=0;
	while (!q.empty()) {
		int tmp=q.top();
		q.pop();
		cnt++;
		a[tmp]=cnt;
		while (tmp) {
			if (--c[tmp]==0) {q.push(tmp);}
			tmp=f[tmp];
		}
	}
	if (cnt==n) {
		printf("YES\n");
		for (int i=1;i<=n-1;i++) {
			printf("%d ",a[i]);
		}
		printf("%d\n",a[n]);
	} else {
		printf("NO\n");
	}
	return 0;
}
```


---

## 作者：gyh20 (赞：1)

构造

题目说输出必须在$1$~$10
^9$之间，但最后离散化即可，不用管。

考虑之后的做法。

将每一个节点的所有子树的值排序，然后将自己的值放在第$c[i]+1$个

但有时会出现相等的值，这时无法放在中间，所以我们需要使用实数和随机数，为每个叶子节点随机赋值。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0,f=1;
	re char v=getchar();
	while(v<'0'||v>'9'){
		if(v=='-')f=-1;
	v=getchar();}
	while(v>='0'&&v<='9'){
		t=(t<<3)+(t<<1)+(v^48);
		v=getchar();
	}
	return t*f;
}
struct edge{
	int to,next;
}e[4002];
int head[2002],cnt;
struct value{
	int pos;
	double val;
}vv[2002];
inline bool cmp(re value x,re value y){
	return x.val<y.val;
}
double num[2002][2002];
inline void add(re int x,re int y){
	e[++cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;}
int n,a,c[2002],m,rt,siz[2002];
bool ia;
double sss;
inline void dfs(re int x){
	for(re int i=head[x];i;i=e[i].next){
		dfs(e[i].to);
		if(ia)return;
		for(re int j=siz[x]+1;j<=siz[e[i].to]+siz[x];++j){
			num[x][j]=num[e[i].to][j-siz[x]];
		}
		siz[x]+=siz[e[i].to];
	}
	sort(num[x]+1,num[x]+siz[x]+1);
	if(c[x]>siz[x]){
		ia=1;
		puts("NO");
		return;
	}
	++siz[x];
	if(c[x]==0){
		if(siz[x]==1)num[x][siz[x]]=(rand()*rand()%1000000)+x;
		else num[x][siz[x]]=num[x][1]/2;
	}
	else if(c[x]==siz[x]-1){
		num[x][siz[x]]=(1e9+num[x][siz[x]-1])/2;
	}
	else num[x][siz[x]]=(num[x][c[x]]+num[x][c[x]+1])/2;
 
	vv[x].pos=x;
	vv[x].val=num[x][siz[x]];
}
int ans[2002];
int main(){
n=read();
srand((unsigned)time(NULL));
for(re int i=1;i<=n;++i){
	a=read();
	if(a==0)rt=i;
	else add(a,i);
	c[i]=read();
}
dfs(rt);
if(ia)return 0;
sort(vv+1,vv+n+1,cmp);
puts("YES");
/*
for(re int i=1;i<=n;++i){
	printf("%d %.4lf ",vv[i].pos,vv[i].val);
}*/
for(re int i=1;i<=n;++i)ans[vv[i].pos]=i;
for(re int i=1;i<=n;++i)printf("%d ",ans[i]);
}
```


---

## 作者：Purple_wzy (赞：1)


#### B. Numbers on Tree

题面：https://codeforces.com/contest/1287/problem/D

题解：考虑从下到上解决问题。

每次操作，我们可以把当前节点子树中的点的值都加进一个堆里，

找到分界位置把当前节点的$a[i]$赋值，并给其后面的对应点的值+1。

但这样做是不对的，因为有可能在一次操作中，这样的加操作可能会改变

之前子树内点的大小关系。考虑如何避免这个问题。

可以证明，如果有解，一定存在一种方案，使得所有点的$a[i]$都不一样。

因此，我们可以记录一下上次堆里的最大值，下次先给所有点的值加上这个最大值，再进堆。

时间复杂度：O($n^2$logn)

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline int
#define C(x,y) memset(x,y,sizeof(x))
#define STS system("pause")
I read(int &res){
	res=0;re g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
typedef pair<int,int>pii;
priority_queue<pii>q;
vector<int>e[2020];
int n,m,root,tot,bas,dep[2020],fa[2020],c[2020],w[2020];
pii b[2020];
I D_1(int x,int d){
	dep[x]=d;q.emplace(make_pair(d,x));
	for(auto p:e[x])D_1(p,d+1);
}
I D_2(int x){
	w[x]+=bas;
	b[++tot]=make_pair(w[x],x);
	for(auto p:e[x])D_2(p);
}
int main(){
	read(n);
	F(i,1,n)read(fa[i]),read(c[i]);
	F(i,1,n)if(!fa[i])root=i;else e[fa[i]].emplace_back(i);
	D_1(root,1);
	while(!q.empty()){
		m=q.top().second;q.pop();tot=bas=0;
		for(auto p:e[m]){
			D_2(p);sort(b+1,b+1+tot);bas=b[tot].first;
		}
		if(tot<c[m]){cout<<"NO";return 0;}
		sort(b+1,b+1+tot);w[m]=b[c[m]].first+1;
		F(i,c[m]+1,tot)w[b[i].second]++;
	}
	cout<<"YES"<<endl;
	F(i,1,n)cout<<w[i]<<" ";
	return 0;
}
```
更好的阅读体验：https://www.cnblogs.com/Purple-wzy/

---

## 作者：JoaoFelix (赞：1)

这是一道构造题！

那么如果有解，肯定能构造出每个数的权值都不同的一种解法

反之，不一定能构造出有数的权值相同的一种解法！

所以我们只考虑构造一种每个数的权值都不同的解！

我们想到一种构造方式：

我们按着dfs的顺序，把当前的点插入子树里已经统计出的答案里的第k[i] + 1个

然后每个子树的答案插在它前面一个子树的答案的后面，顺着构造即可

所以往往这种构造题，顺着构造即可，直接在dfs的过程中直接搞出答案！

核心代码如下：

```cpp
vector<int> solve(int u) {
	vector<int> res; res.clear();
	for (auto v : G[u]) {
		vector<int> tmp = solve(v);
		for (auto x : tmp) {
			if (res.size() == p[u]) res.push_back(u);
			res.push_back(x);
		}
	}
	if (res.size() == p[u]) res.push_back(u);
	if (res.size() < p[u]) { puts("NO"); exit(0); }
	return res;
}
```




---

## 作者：KiDDOwithTopTree (赞：1)

~~我学 DS 学傻了…~~

~~在模拟赛上看到有构造题就跑了，结果半小时后才发现这是我唯一会的一题…~~

#### 正文：

因为这一题的 $c_i$ 与 $i$ 的子树有关，于是不难想到从叶子节点向上构造。

首先我们可以发现一个性质：在 $i$ 的子树中，$a_i$ 排名为 $c_i+1$。

~~废话一句。~~

那我们在遍历到 $i$ 时，把在 $i$ 子树中的所有 $j$ 的 $a_j$ 全部放入一个数据结构 $b$ 中，然后把 $a_i$ 赋为 $b_{c_i}+1$，再把第 $c_i+1$ 到 $size_i-1$ 的 $a$ 全部 $+1$。

因为各个子树之间并没有什么关系，所以我们直接把后加入的子树中的点直接放在之前已经加入的点后面就阔以了。

这个数据结构可以用**数组**。想法很暴力，但我们一分析发现时复是 $O(n^2)$，可以通过。

~~但是我并没看数据范围，于是就开始了用 DS 优化的道路…~~

~~作为一名重工业数据结构选手，我一眼看出它可以用平衡树。~~

我们可以在每个点维护一棵平衡树。点 $i$ 的平衡树所包含的节点是由所有 $son_i$ 的平衡树的节点与 $i$。

那么我们可以充分利用 $son_i$ 的平衡树。我们可以把这些平衡树**合并**起来，然后再插入 $i$。

关于合并，有一个十分有用的东西：**启发式合并**。

于是乎我们把 $son_i$ 平衡树启发式合并一遍，就得到了 $i$ 的平衡树。时复 $O(n \log^2 n)$，如果用 splay 就是 $O(n \log n)$。

因为 $a_i$ 在运行途中会发生变化，所以我对平衡树进行了亿些魔改，可以对着代码格物致知一下来进行理解。

代码考场上写的，为了方便调试加了一些注释。各位大佬们可以忽略不看。

```cpp
#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
const int N=1e6+10;
/*------------链式前向星组件------------*/
struct edge_node{
	int from,to;
	int nxt;
};
struct edge{
	edge_node e[N];
	int head[N],tot;
	edge(){
		memset(head,-1,sizeof head);
	}
	inline void add(int from,int to){
		e[tot].from=from;
		e[tot].to=to;
		e[tot].nxt=head[from];
		head[from]=tot++;
	}
};
edge e;
/*------------链式前向星组件------------*/
/*------------fhq组件------------*/
struct fhq_treap{
	int lson,rson;
	int size;
	int key;
};
fhq_treap fhq[N];
int root[N],a[N];
inline int newnode(int pos){
	fhq[pos].key=rand();
	fhq[pos].size=1;
	return pos;
}
inline void pushup(int pos){
	int ls=fhq[pos].lson,rs=fhq[pos].rson;
	fhq[pos].size=fhq[ls].size+fhq[rs].size+1;
}
void fhq_split(int pos,int size,int &x,int &y){
	if(!pos) return void(x=y=0);
	int checker=fhq[fhq[pos].lson].size+1;
	if(checker<=size){
		x=pos;
		fhq_split(fhq[x].rson,size-checker,fhq[x].rson,y);
		pushup(x);
	}
	else{
		y=pos;
		fhq_split(fhq[y].lson,size,x,fhq[y].lson);
		pushup(y);
	}
}
int fhq_merge(int x,int y){
	if(!x||!y) return x+y;
	if(fhq[x].key<fhq[y].key){
		fhq[x].rson=fhq_merge(fhq[x].rson,y);
		pushup(x);
		return x;
	}
	else{
		fhq[y].lson=fhq_merge(x,fhq[y].lson);
		pushup(y);
		return y;
	}
}
void ins(int &rt,int pos,int size){
	int x,y;
	fhq_split(rt,size,x,y);
	rt=fhq_merge(fhq_merge(x,newnode(pos)),y);
}
/*------------fhq组件------------*/
/*------------启发式合并fhq------------*/
void fhq_dfs(int x,int &y){
	if(!x) return ;
	int ls=fhq[x].lson,rs=fhq[x].rson;
	fhq[x].lson=fhq[x].rson=0;
	fhq_dfs(ls,y);
	ins(y,x,fhq[y].size);
	fhq_dfs(rs,y);
}
void merge(int &x,int &y){
	if(fhq[x].size>fhq[y].size)
		swap(x,y);
	fhq_dfs(x,y);
}
/*------------启发式合并fhq------------*/
/*------------dfs计算ans------------*/
bool flag;
void dfs(int u){
	for(int i=e.head[u];~i;i=e.e[i].nxt){
		int v=e.e[i].to;
		dfs(v);
		merge(root[v],root[u]);
	}
	if(a[u]>fhq[root[u]].size) flag=true;
	else if(!flag) ins(root[u],u,a[u]);
}
/*------------dfs计算ans------------*/
/*------------dfs统计ans------------*/
int ans[N],cnt;
void get_ans(int x){
	if(!x) return ;
	get_ans(fhq[x].lson);
	ans[x]=++cnt;
	get_ans(fhq[x].rson);
}
/*------------dfs统计ans------------*/
int main(){
	int n;
	cin>>n;
	int rt;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x>>a[i];
		if(x) e.add(x,i);
		else rt=i;
	}
	dfs(rt);
	if(flag) cout<<"NO\n";
	else{
		cout<<"YES\n";
		get_ans(root[rt]);
		for(int i=1;i<=n;i++)
			cout<<ans[i]<<' ';
	}
}
/*
case #1:
input:
5
0 1
1 3
2 1
3 0
2 0
output:
YES
2 5 3 1 4

case #2:
input:
5
0 4
1 1
2 0
3 0
2 0
output:
YES
5 2 1 3 4

case #3:
input:
7
0 4
1 1
6 0
2 0
2 0
1 2
6 0
output:
5 6 2 7 4 3 1

case #4:
input:
3
2 0
0 2
2 0
output:
YES
2 3 1
*/
```

---

## 作者：liuyz11 (赞：1)

# 题解 CF1286B 【Numbers on Tree】

题目大意：有一颗有根树，每一个节点有一个值ai，用ci表示以i为根的子树中比i小的节点的j个数（即aj < ai）。现在给你n和c数组，让你给出满足以上条件的任意一种a的方案。

这题一开始完全不会，百度了题解后才过的：大佬的题解

我们发现一个子树整体无论变化多少，这个子树中所有节点都是满足情况的。

并且一个子树中只要大小关系保持不变，怎么变化也都是满足情况的。

那么我们只要将当前节点的子树按照原来节点的值排个序。每个节点的值直接改成它的编号，还是满足条件。

至于当前节点u，在这些节点的上面不会产生影响，只需要在编号c[u]处插入，后面的节点都忘后移就好（反正n才2000，够我们玩）。

当一个点的时候直接是1（就是c[u] + 1）了。

这边为了方便排序使用pair，表示节点的值和这个节点的数。

代码如下:

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 2005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int c[MAXN], ans[MAXN], sz[MAXN];
vi edge[MAXN];
vector<pii> ve[MAXN];

void dfs(int u){
    ve[u].clear();
    sz[u] = 1;
    rep(i, 0, SZ(edge[u]) - 1){
        int v = edge[u][i];
        dfs(v);
        sz[u] += sz[v];
        rep(j, 0, SZ(ve[v]) - 1) ve[u].pb(ve[v][j]);
    }
    if(c[u] >= sz[u]){
        puts("NO");
        exit(0);
    }
    sort(all(ve[u]));
    rep(i, 0, SZ(ve[u]) - 1) ve[u][i].fi = i + 1;
    ve[u].insert(ve[u].begin() + c[u], mp(c[u] + 1, u));
    rep(i, c[u] + 1, SZ(ve[u]) - 1) ve[u][i].fi++;
}

int main(){
    int n;
    scanf("%d", &n);
    int root;
    rep(i, 1, n){
        int fa;
        scanf("%d%d", &fa, &c[i]);
        if(!fa) root = i;
        else edge[fa].pb(i);
    }
    dfs(root);
    puts("YES");
    sort(all(ve[root]));
    rep(i, 0, SZ(ve[root]) - 1) ans[ve[root][i].se] = ve[root][i].fi;
    rep(i, 1, n) printf("%d ", ans[i]);
    puts("");
    return 0;
}
```

---

## 作者：kevinZ99 (赞：0)

# solution

看到题，似乎像是一个构造。

所以考虑将 $a$ 构造为一个序列。

因为是序列，所以对于根节点有 $a_{root}=c_{root}+1$。

可以发现其实对于一个节点 $x$，它的 $a$ 就是现在还没有被使用过的数中的第 $c_{x}+1$ 小的数。

**注意事项** 

1、若子树大小比 $c$ 小那么无解。

2、输出 NO 之后，记得退出程序。

# code

```cpp
//Author:Kevin Z K Y
#include <bits/stdc++.h>
#define up(a,b,c) for(int (a)=(b);(a)<=(c);(a)++)
#define dn(a,b,c) for(int (a)=(b);(a)>=(c);(a)--)
#define fst first
#define sed second
using namespace std;
using ull = unsigned long long ;
using ll = long long ;using hint = __int128 ;
using pii = pair<int,int> ;using pll = pair<ll,ll> ;
using vi = vector<int> ;using vl = vector<ll> ;
using vpi = vector<pii> ;using vpl = vector<pll> ;
using db = double ;namespace mystl{
	#define gc() getchar()
	ll qpow(ll a,ll b,const ll&p){if (a==0ll) return 0ll; ll c=1ll;
		while(b) { if(b & 1) c=a*c%p; a=a*a%p; b>>=1; } return c; }
	template<typename T>void read(T&x) {x=0; bool f=false; char ch;
		ch = gc(); while(ch<'0'||ch>'9') f |= ( ch=='-') , ch=gc();
		while(ch>='0'&&ch<='9') x=x*10+ch-'0' , ch=gc(); x=f?-x:x;}
	template<typename T>void write(T x){char s[40];short d=0;T y=x;
		if(x<0) putchar('-'),y=-y;if(x==0){ putchar('0'); return; }
		while(y){s[++d]=y%10+'0';y/=10;}while(d>0)putchar(s[d--]);}
	template<typename T>void wris(T x,char c){write(x);putchar(c);}
}using namespace mystl;
namespace my{
	const int N=2005;
	int n;
	vi g[N];
	int c[N];
	bool vis[N];
	int root=0;
	int ans[N];
	int siz[N];
	void dfs(int x,int fa){
		int get=0,now=1,id=-1;
		while(now<=n&&get<c[x]+1){
			if(!vis[now])get++,id=now;
			if(get==c[x]+1)break;
			now++;
		}if(id==-1){
			cout<<"NO\n";
			exit(0);
		}ans[x]=id,vis[id]=true;
		siz[x]=1;
		for(int v:g[x]){
			if(v==fa)continue;
			dfs(v,x);
			siz[x]+=siz[v];
		}if(siz[x]-1<c[x]){
			cout<<"NO\n";
			exit(0);
		}
	}
	void solve(){
		cin>>n;
		up(i,1,n){
			int x;cin>>x>>c[i];
			if(x==0){
				root=i;
				continue;
			}
			g[x].push_back(i);
			g[i].push_back(x);
		}
		dfs(root,-1);
		cout<<"YES\n";
		up(i,1,n)cout<<ans[i]<<' ';
	}
}
int main(){
//  freopen("","r",stdin);
//  freopen("","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	int _=1;while(_--)my::solve();return 0;
}
```

---

## 作者：zhouzihang1 (赞：0)

# CF1286B Numbers on Tree 题解

[洛谷传送门](https://www.luogu.com.cn/problem/CF1286B)

[CF 传送门](https://codeforces.com/problemset/problem/1286/B)

[文章链接](https://www.luogu.com.cn/article/2d2w8yqw)

## 思路

先想一下什么情况会输出 `No`。

如果 $c_i \ge cnt_i$，则不成立。

注：$cnt_i$ 表示以 $i$ 为根的子树节点数。

那么想一下，若成立，答案编号一定可以为 $1$ 到 $n$，所以对于对于 $i$ 号节点，如果它的 $c_i$ 合法，那么答案就是从 $1$ 到 $n$ 中未使用的编号第 $c_i + 1$ 小的数字。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e3+10;
int n,ans[N],num[N],cnt[N];
bool flag[N],No;
vector<int> vc[N];
/*
ans[] 存放答案
num[] 就是上文中的 c
cnt[] 存以 i 为根的子树节点数
flag[] 记录数字是否使用过
No 表示是否不合法
vc[] 邻接表
*/
int judge(int k)//找第 k+1 小的未使用的数字
{
	int tot=0,j;
	for(j=1;j<=n&&tot<k;j++)
		if(!flag[j]) tot++;
	flag[--j]=1;
	return j;
}
void dfs(int u)
{
	int k=judge(num[u]+1);
	cnt[u]=1;ans[u]=k;
	for(int v:vc[u])
	{
		dfs(v);
		if(No) return;//不合法就不跑了
		cnt[u]+=cnt[v];//计节点数
	}
	if(cnt[u]<=num[u])
	{
		No=1;
		printf("No\n");
		return;
	}
}
int main()
{
	scanf("%d",&n);
	int rt;
	for(int i=1,u;i<=n;i++)
	{
		scanf("%d%d",&u,&num[i]);
		vc[u].push_back(i);
		if(u==0) rt=i;
	}
	dfs(rt);//树形dp
	if(No) return 0;
	printf("Yes\n");
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：yspm (赞：0)

注意数据范围 $n\le 2000$ 那么建议对应 $\Theta(n^2)$ 的做法

有一说一，这题解区又是平衡树，又是随机权值稍微有点牛的

首先如果出现 $c$ 不小于子树大小的则无解，否则一律有解

注意到我们只需要每个点权值的相对大小关系而非具体值，那么可以每个点整个 `std::vector` 存子树里面所有点的大小排序

在一个子树的根处合并所有子树的信息，由于不同子树之间互相独立，直接一个一个儿子往根的 vector 里面 push 就行

最后把根放到自己 vector 的合适位置，使得前面有 $c_{rt}-1$ 个元素即可

最后赋权直接给 $1\sim n$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define sec second
#define fir first
#define int long long
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;++i) 
#define Down(i,a,b) for(int i=a;i>=b;--i)
template<typename T>inline void ckmax(T &x,T y){x=x<y?y:x; return ;}
template<typename T>inline void ckmin(T &x,T y){x=x<y?x:y; return ;}
namespace FastIO{
    inline int read(){
        int res=0,f=1; char k;
        while(!isdigit(k=getchar())) if(k=='-') f=-1;
        while(isdigit(k)) res=res*10+k-'0',k=getchar();
        return res*f;
    }
    char OPUT[100];
    template<typename T>inline void print(T x){
        if(x<0) putchar('-'),x=-x; 
        int cnt=0; do OPUT[++cnt]=x%10,x/=10; while(x); 
        Down(i,cnt,1) putchar(OPUT[i]+'0'); putchar(' '); return ;
    }
}using namespace FastIO;
const int N=2010;
vector<int> g[N],seq[N];
int n,root,fa[N],siz[N],ans[N],ned[N];
inline void dfs(int x){
    siz[x]=1;
    for(auto t:g[x]){
        dfs(t); siz[x]+=siz[t];
        for(auto v:seq[t]) seq[x].pb(v);
    } if(siz[x]<=ned[x]) puts("No"),exit(0);
    seq[x].pb(x); for(int i=siz[x]-1;i>ned[x];--i) swap(seq[x][i],seq[x][i-1]);
    return ;
}
signed main(){
    n=read(); for(int i=1;i<=n;++i){
        fa[i]=read(); ned[i]=read();
        if(fa[i]) g[fa[i]].pb(i); else root=i;
    } dfs(root); for(int i=0;i<n;++i) ans[seq[root][i]]=i+1;
    puts("Yes"); rep(i,1,n) print(ans[i]); puts("");
    return 0;
}

```

---

## 作者：Suiseiseki (赞：0)

首先，我们考虑无解的情况，很明显，当有一个点的$c_i$要**大于等于**这个点的字数大小时，肯定无解。否则，当每个节点的值不同时，一定有解，证明显然。

题目中的限制是每个数在$1$ ~ $10^9$之间，但是没有意义，可以离散化变成$1,2,\cdots,n$的（~~虽然说我直接构造1~n了~~）。注意到这一题的权值与答案没有关系，我们所需的仅仅只是在每个权值不同时它们之间的**大小关系**。

很明显，叶子节点之间的大小关系时不影响答案的，那么我们可以给叶子节点之间的大小随便选。那么对于每一个非叶节点来说，在它的子树之间的大小全部被处理出来时，它只需要在将子树中的两个点拿出来，将自己的权值放在它们之间就可以了。

如果一开始就给节点赋值，最后很有可能会导致某个节点插在了两个相邻的权值之间，会出现浮点数，这很讨厌，所以，我们一开始不给节点赋值，只考虑维护权值之间的大小关系。

思考一种能够维护数列大小关系的数据结构，支持动态插入一个元素，要求插入时间复杂度不超过$O(n)$，查找时间复杂度不超过$O(n)$，~~这样的数据结构一个都想不出来就退役吧~~，我们有三个候选数据结构，分别是：
1. 数组，单次插入$O(n)$，单次查找$O(logn)$
2. 链表，单次插入$O(1)$，单次查找$O(n)$
3. 平衡树，单次插入$O(logn)$，单次查找$O(logn)$

我选用的是第二种，因为我觉得在动态插入时，链表更加直观。

所以到这里，思路就很清晰了，先将所有叶子节点用链表链接起来，然后考虑它们的父亲插在哪儿，再往上推一层，……，这样下去，就可以得到所有节点之间的大小关系，然后，遍历一遍链表，按大小关系赋值即可，时间复杂度$O(n^2)$。

代码可以去我的博客查看：[Codeforces 1286B. Numbers on Tree题解
](https://www.cnblogs.com/withhope/p/12285151.html)

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1286B)

不会啥来啥是吧。构造。这还有 $^*1800$？？？？

~~刚好上午模拟赛和构造大战了 2.5h，别人 10min 取之。~~

首先我们判断掉无解，这是容易的，如果 $c_u>siz_u-1$ 显然无解。

继续考虑。我们肯定不希望我们填出来的数有相等的，因为这会让我们的问题变得更复杂，也就是在判断排名的时候不方便。

观察到 $n\le 2000$，我们考虑一个 $n^2$ 的做法，就是我们维护子树内所有数的相对大小关系，这个用 `vec` 存即可。

在合并子树的时候，实际上我们发现子树之间是独立的，互不影响，我们只要把当前点 $u$，在 $c_u$ 的限制下插进去就行。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =3001;
vector<int> G[N],g[N];
int root,n,c[N],siz[N],p[N],ans[N];
void dfs(int u,int fath){
	siz[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fath)	continue;
		dfs(v,u),siz[u]+=siz[v]; 
	}
	if(c[u]>siz[u]-1)	cout<<"NO"<<endl,exit(0);
	if(siz[u]==1&&u!=root)	{G[u].push_back(u);return ;}
	int pre=c[u]; bool f=true;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i]; if(v==fath)	continue;
		if(c[u]>=(int)G[v].size()){
			for(int j=0;j<G[v].size();j++)	G[u].push_back(G[v][j]);
			c[u]-=(int)G[v].size();
		}	
		else{
			for(int j=0;j<c[u];j++)	G[u].push_back(G[v][j]);
			if(f==true)	G[u].push_back(u),f=false;
			for(int j=c[u];j<G[v].size();j++)	G[u].push_back(G[v][j]);
		}
	}
	if(f==true&&c[u]==0)	G[u].push_back(u);	
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i]>>c[i];
		if(p[i]!=0)	g[i].push_back(p[i]),g[p[i]].push_back(i); 
		else	root=i;
	}
	dfs(root,0);
	for(int i=0;i<G[root].size();i++)	ans[G[root][i]]=i+1;
	cout<<"YES"<<endl;
	for(int i=1;i<=n;i++)	cout<<ans[i]<<" ";
	cout<<endl;
	return 0; 
}
```

---

