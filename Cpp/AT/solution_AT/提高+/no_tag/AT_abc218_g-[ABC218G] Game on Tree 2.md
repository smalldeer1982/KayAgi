# [ABC218G] Game on Tree 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc218/tasks/abc218_g

$ N $ 頂点の木があり、各頂点には $ 1 $ から $ N $ までの番号が振られています。また、$ i\,(1\ \leq\ i\ \leq\ N-1) $ 本目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結んでおり、頂点 $ i\,(1\ \leq\ i\ \leq\ N) $ には偶数 $ A_i $ が書かれています。太郎君と次郎君がこの木と $ 1 $ つの駒を使ってゲームをします。

はじめ、駒は頂点 $ 1 $ に置かれています。二人は太郎君から始めて交互に、駒を現在置かれている頂点と直接辺で結ばれた頂点に移動させます。ただし、駒が一度訪れた頂点に移動させることはできません。駒を移動させることができなくなった時点でゲームが終了します。

太郎君はゲームが終了するまでに駒が訪れた頂点（頂点 $ 1 $ を含む）に書かれた数の（多重）集合の中央値を最大化、次郎君は最小化したいです。両者が最適に行動するとき、駒が訪れた頂点に書かれた数の集合の中央値を求めてください。

 中央値とは 大きさ $ K $ の数の（多重）集合の中央値は以下のように定義されます。

- $ K $ が奇数のとき、小さい方から $ \frac{K+1}{2} $ 番目の値
- $ K $ が偶数のとき、小さい方から $ \frac{K}{2} $ 番目の値と $ \frac{K}{2}+1 $ 番目の値の平均値
 
 例えば、$ \{\ 2,2,4\ \} $ の中央値は $ 2 $ 、$ \{\ 2,4,6,6\} $ の中央値は $ 5 $ です。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 2\ \leq\ A_i\ \leq\ 10^9 $
- $ A_i $ は偶数
- $ 1\ \leq\ u_i\ <\ v_i\ \leq\ N $
- 与えられるグラフは木
- 入力は全て整数

### Sample Explanation 1

両者が最適に行動するとき、ゲームは以下のように進行します。 - 太郎君が駒を頂点 $ 1 $ から頂点 $ 5 $ に移動させる - 次郎君が駒を頂点 $ 5 $ から頂点 $ 4 $ に移動させる - 太郎君が駒を頂点 $ 4 $ から頂点 $ 3 $ に移動させる - 次郎君は駒を動かせないのでゲームが終了する 駒が訪れた頂点に書かれた数の集合は $ \{2,10,8,6\} $ となるので、中央値である $ 7 $ を出力します。

### Sample Explanation 2

両者が最適に行動するとき、ゲームは以下のように進行します。 - 太郎君が駒を頂点 $ 1 $ から頂点 $ 4 $ に移動させる - 次郎君は駒を動かせないのでゲームが終了する 駒が訪れた頂点に書かれた数の集合は $ \{6,10\} $ となるので、中央値である $ 8 $ を出力します。

## 样例 #1

### 输入

```
5
2 4 6 8 10
4 5
3 4
1 5
2 4```

### 输出

```
7```

## 样例 #2

### 输入

```
5
6 4 6 10 8
1 4
1 2
1 5
1 3```

### 输出

```
8```

## 样例 #3

### 输入

```
6
2 2 6 4 6 6
1 2
2 3
4 6
2 5
2 6```

### 输出

```
2```

# 题解

## 作者：binbin_200811 (赞：5)

# 思路

## Part 1 转移方程

对于每一个节点而言，如果是小 T 推动，那么下一个推动的一定是小 J，小 J 推的情况同理。也就是说，每一个点推动的人是固定的，而叶子节点的中位数是固定且可以求出的。

那么对于叶子节点的父亲来说，若小 T 推，则会推向最大的点；反之推向最小的点。那么在考虑叶子节点的爷爷时可以把叶子节点的父亲当做新的叶子节点（因为走到它这个点会得到的中位数已经固定的）。依次类推，变可以得到转移方程。

设 $f(i)$ 表示 $i$ 节点的最优选择（即小 T 选最大，小 J 选最小）。

若 $i$ 点小 T 推动：

$$
f(i)=\max(f(j))
$$

其中 $j$ 为 $i$ 的儿子节点。

若 $i$ 点小 J 推动：

$$
f(i)=\min(f(j))
$$

其中 $j$ 为 $i$ 的儿子节点。

若 $i$ 点为叶子节点 $f(i)$ 为该叶子节点的中位数值。

## Part 2 中位数

下面介绍求中位数的 $3$ 种方法。

### 方法 1 对顶堆

开一个大根堆，一个小根堆，且两堆元素个数相差最大为 $1$ 。若已知中位数，则大于中位数的放入小根堆，小于中位数的放入大根堆，接着维护两个元素差最大为 $1$ 的性质，即大根堆多了，将大根堆堆顶向小根堆加入，小根堆同理，那么可以保证两堆对顶的数肯定有一个为中位数（删除需要假删除，步骤同理）。其实一开始我们只有一个数的时候中位数就是这一个数，所以使用该结构即可在 $\log_n$ 的时间内完成求中位数。

### 方法 2 平衡树

使用平衡树，实现插入、删除、求排名操作，即可在 $\log_n$ 的时间完成求中位数。

详见 [平衡树模板P3369](https://www.luogu.com.cn/problem/P3369)。

### 方法 3 线段树

可以使用动态开点的线段树，或者离散化后使用线段树求排名。

具体实现请自行上网了解。

# 代码实现

实现给出的是动态开点线段树的实现方法。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define inf 1e9
#define lch(i) tree[i].lch
#define rch(i) tree[i].rch
#define ll long long

const ll maxn=2e5+5;

struct node
{
    ll to,nxt;
}edge[maxn*2];
struct node1
{
    ll l,r,lch,rch,val;
}tree[maxn*31];

ll n,tot=1,cnt;
ll f[maxn],a[maxn],head[maxn];

void add(ll x,ll y)
{
    cnt++;
    edge[cnt].to=y;
    edge[cnt].nxt=head[x];
    head[x]=cnt;
}

inline void updata(ll p){tree[p].val=tree[lch(p)].val+tree[rch(p)].val;}
inline void insert(ll p,ll l,ll r,ll x,ll v)//动态开点
{
    tree[p].l=l;
    tree[p].r=r;
    if(l==r)
    {
        tree[p].val+=v;
        return ;
    }

    ll mid=(l+r)/2;
    if(x<=mid)
    {
        if(!lch(p)) lch(p)=++tot;
        insert(lch(p),l,mid,x,v);
    }
    else
    {
        if(!rch(p)) rch(p)=++tot;
        insert(rch(p),mid+1,r,x,v);
    }
    updata(p);
}
inline ll gtrk(ll p,ll rk)//求排名
{
    if(tree[p].l==tree[p].r) return tree[p].l;
    if(tree[lch(p)].val>=rk) return gtrk(lch(p),rk);
    else return gtrk(rch(p),rk-tree[lch(p)].val);
}

inline void dfs(ll x,ll bj,ll fa,ll c)
{
    f[x]=-inf;
    insert(1,1,inf*2,a[x],1);
    ll kid=0;
    for(ll i=head[x];i;i=edge[i].nxt)
    {
        ll v=edge[i].to;
        if(v!=fa) {dfs(v,-bj,x,c+1);kid++;}
    }
    if(kid)//非叶子节点
    {
        for(ll i=head[x];i;i=edge[i].nxt)
        {
            ll v=edge[i].to;
            if(v==fa) continue;
            f[x]=max(f[v]*bj,f[x]);
        }
        f[x]=abs(f[x]);
    }
    else//叶子节点
    {
        if(c%2==0) f[x]=(gtrk(1,c/2)+gtrk(1,c/2+1))/2;
        else f[x]=gtrk(1,(c+1)/2);
    }
    insert(1,1,inf*2,a[x],-1);
}

int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(ll i=1;i<n;i++)
    {
        ll x,y; 
        scanf("%lld%lld",&x,&y);
        add(x,y);
        add(y,x);
    }
    dfs(1,1,1,1);
    printf("%lld",f[1]);
}
```

---

## 作者：DengDuck (赞：3)

这是一道缝合题。

可以看作两道题。

- 求叶子到根路径的中位数。
- 叶子取值的博弈问题。

说句实话，我觉得 BinBin 写得比我好，大家可以看他的。

# 求叶子到根路径的中位数

首先我们得弄明白怎么求中位数。

一种实现是对顶堆，我不喜欢它，但是它很快很好写，本题需要删除操作，可以考虑使用两个 `multiset` 实现。

一种实现是权值线段树查排名，我暗恋它，它又慢又不好写，本文使用这种方法。

那么转移到一棵树上怎么做呢？权值线段树的插入和删除都是很容易的，我们直接使用 DFS 遍历树。

到达一个节点时，我们将其值插入权值线段树，完成树内遍历后，删除这个值，离开。

那么显然我们到达某一节点时权值线段树保存的是这个节点到根的路径上的所有值，利用线段树的性质，我们可以很容易求出中位数。

我们设 $md_x$ 表示 $x$ 到根路径上的值即可。

# 这个博弈游戏

题目给了一个有点智障的博弈游戏，我们考虑动态规划，设 $f_x$ 表示在 $x$ 的子树进行博弈游戏

至于先手后手显然是由 $x$ 的深度的奇偶性决定的，所以对于每一个 $x$ 都有且只有一种可能，要么是先手走要么是右手走，无需增加一维表示。

因此我们以三种情况动态规划：

- 叶子节点值为 $f_x=md_x$。
- 先手值为 $f_x=\max\limits_{y\in xson}f_y$。
- 后手值为 $f_x=\min\limits_{y\in xson}f_y$。

本题即可轻松解决。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e6+5;
const LL inf=1e9;
struct node
{
	LL lc,rc,sz;
}t[N];
vector<LL>v[N];
LL n,a[N],tot,rt,x,y,md[N],f[N];
void ins(LL &rt,LL x,LL k,LL l,LL r)
{
	if(x<l||r<x)return;
	if(rt==0)rt=++tot;
	if(l==r)
	{
		t[rt].sz+=k;
		return;
	}
	LL mid=(l+r)/2;
	ins(t[rt].lc,x,k,l,mid);
	ins(t[rt].rc,x,k,mid+1,r);
	t[rt].sz=t[t[rt].lc].sz+t[t[rt].rc].sz;
}
LL rk(LL &rt,LL k,LL l,LL r)
{
	if(l==r)return l;
	LL mid=(l+r)/2;
	LL lc=t[rt].lc,rc=t[rt].rc;
	if(k<=t[lc].sz)return rk(lc,k,l,mid);
	return rk(rc,k-t[lc].sz,mid+1,r);
}
void dfs(LL x,LL fa)
{
	ins(rt,a[x],1,1,inf);
	if(t[rt].sz&1)
	{
		md[x]=rk(rt,(t[rt].sz+1)/2,1,inf);
	}
	else
	{
		md[x]=(rk(rt,(t[rt].sz)/2,1,inf)+rk(rt,t[rt].sz/2+1,1,inf))/2;
	}
	for(LL i:v[x])
	{
		if(i==fa)continue;
		dfs(i,x);
	}
	ins(rt,a[x],-1,1,inf);
}
void dfs2(LL x,LL fa,LL k)
{
	if(k==1)f[x]=inf*inf;
	for(LL i:v[x])
	{
		if(i==fa)continue;
		dfs2(i,x,k^1);
		if(k==1)f[x]=min(f[x],f[i]);
		else f[x]=max(f[x],f[i]);
	}
	LL len=v[x].size()-(fa!=0);
	if(len==0)f[x]=md[x];
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n-1;i++)
	{
		scanf("%lld%lld",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	dfs2(1,0,0);
	printf("%lld",f[1]);
	return 0;
}
```



---

## 作者：yhylivedream (赞：2)

可以看做两道题。

## 动态中位数

题解里还没有对顶 multiset，考虑维护两个 multiset，$A$ 存储小于等于中位数的值，$B$ 存储大于中位数的值，记 $size(x)$ 表示 $x$ 中元素个数，且 $size(A)\le size(B)$，$|size(A)-size(B)|\le 1$，为了方便可以在 $A$ 中插入极小值，$B$ 中插入极大值。

除了查询其他都是板子了，若 $2\mid size(A)+size(B)$，则答案为 $\frac{\max\lbrace A\rbrace+\min\lbrace B\rbrace}{2}$，否则为 $\max\lbrace A\rbrace$。

## 树形dp

设 $f_x$ 表示到 $x$ 点，最大或最小值，以下记根节点深度为 $0$。

- 若 $x$ 为叶子结点，$f_x=根到x的中位数$。

- 若 $x$ 深度为偶数，$f_x=\max_{y\in son} f_y$。

- 若 $x$ 深度为奇数，$f_x=\min_{y\in son} f_y$。

答案即为 $f_1$。

## 代码

```cpp
//author : yhy
#include <bits/stdc++.h> 

using namespace std;
using LL = long long;

const LL kMaxN = 1e5 + 5, kInf = 1e18;

LL n, a[kMaxN], f[kMaxN];
vector<LL> e[kMaxN];

struct Median {
  multiset<LL> l, g;
  void init() {
    l.clear(), g.clear(), l.insert(-kInf), g.insert(kInf);
  }
  void F() {
    for (; l.size() > g.size() + 1;) {
      auto it = (--l.end());
      g.insert(*it), l.erase(it);
    }
    for (; g.size() > l.size();) {
      auto it = g.begin();
      l.insert(*it), g.erase(it);
    }
  }
  void A(LL val) {
    (val <= *g.begin() ? l.insert(val) : g.insert(val)), F();
  }
  void D(LL val) {
    auto it = l.lower_bound(val);
    if (it != l.end()) {
      l.erase(it);
    } else {
      it = g.lower_bound(val), it != g.end() && (g.erase(it), 0);
    }
    F();
  }
  LL Calc() {
    if ((l.size() + g.size() - 2) % 2 == 0) {
      return (*l.rbegin() + *g.begin()) / 2;
    }
    return *l.rbegin();
  }
} s;

void S(LL x, LL fa, LL col) {
  s.A(a[x]), f[x] = (!col ? -kInf : kInf);
  for (LL nxt : e[x]) {
    if (nxt != fa) {
      S(nxt, x, col ^ 1);
      f[x] = (!col ? max(f[x], f[nxt]) : min(f[x], f[nxt]));
    }
  }
  (x != 1 && e[x].size() == 1) && (f[x] = s.Calc()), s.D(a[x]);
}

signed main() {
  cin >> n, s.init();
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (LL i = 1, x, y; i < n; i++) {
    cin >> x >> y, e[x].push_back(y), e[y].push_back(x);
  }
  S(1, 0, 0), cout << f[1];
}
```


这不比线段树好写 $114$ 倍。

---

## 作者：CrTsIr400 (赞：1)

[[ABC218G] Game on Tree](https://www.luogu.com.cn/problem/AT_abc218_g) 

这是本蒟蒻写的第 $99$ 篇题解，若有误请大家批评指正。

---

简单树上博弈题目。

众所周知，因为我们这道题的博弈树已经给出来了，所以直接暴力去决策每个人是可以接受的：$O(n)$ 的复杂度。

然后唯一难点在于计算叶子节点的答案。实际上，就是根到它路径上所有数的中位数。

带删除动态中位数是个经典问题，可以用 `__gnu_pbds::tree`，也可以用对顶 `multiset`，但是对于解决这道题而言用不着常数这么大的数据结构。

---

直接权值线段树/权值树状数组就能非常简洁地做出来。

权值线段树做法很显然，这里讲一下权值树状数组如何做第 $k$ 小。当然要离散化。

类似于倍增也类似于二分。首先先从高位入手，判断 $[x+1,x+2^i]$ 里面有没有答案，显然这是可以调用 $c[x+2^i]$ 求出的。

如果有的话 $x+2^i\to x$，否则 $x$ 不动，$i$ 缩小。此时最终的 $x$ 是满足 $\le x$ 的数的数量 $<k$，于是输出 $x+1$ 即可。

此时这个做法就能做第 $k$ 小了。具体看代码的 `kth` 部分。

空间复杂度很优秀，可以 $O(n)$，常数相较于其它数据结构较小，轻松拿下最优解。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
const I N=1e5+10;
I n,a[N],b[N],lsn,c[N],siz;
V add(I x,I y){siz+=y;for(;x<=lsn;x+=x&-x)c[x]+=y;}
I kth(I k){I x=0,s=0;
	for(I i=__lg(lsn);~i;--i){x+=1<<i;
		if(x>=lsn||s+c[x]>=k)x-=1<<i;
		else s+=c[x];}
	return x+1;}
I median(){
	if(siz&1)return b[kth((siz+1)/2)];
	return(b[kth(siz/2)]+b[kth(siz/2+1)])/2;}
I f[N],ey[N<<1],nx[N<<1],hd[N],ec;
V conn(I x,I y){ey[++ec]=y;nx[ec]=hd[x];hd[x]=ec;}
V dfs(I x,I fa=0,I d=0){
	add(a[x],1);
	if(!d)f[x]=-(1<<30);else f[x]=1<<30;
	bool u=0;
	for(I i=hd[x],y;y=ey[i],i;i=nx[i])if(y^fa){
		dfs(y,x,d^1);u=1;
		f[x]=(!d)?max(f[y],f[x]):min(f[y],f[x]);}
	if(!u)f[x]=median();
	add(a[x],-1);}
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	fo(i,1,n)cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);lsn=unique(b+1,b+n+1)-b-1;
	fo(i,1,n)a[i]=lower_bound(b+1,b+lsn+1,a[i])-b; 
	fo(i,2,n){I x,y;cin>>x>>y;conn(x,y);conn(y,x);}
	dfs(1);printf("%d\n",f[1]);
	return 0;}
```

## 后记

+ 这个树状数组突然让我联想到了这个题：
+ [ABC287G - Balance Update Query](https://atcoder.jp/contests/abc287/tasks/abc287_g)
+ 题意是你要维护一个牌堆，每种牌可以改权值可以改数量，然后尽可能取出最大权值的那些卡片。
+ 显然可以权值线段树做，对于 $1$ 号的改权值操作很显然一加一减即可，对于 $2$ 号改数量的操作一加一减也可以，对于三号操作直接线段树二分即可。
+ 考虑树状数组来做有没有前途。
+ 先离散化所有涉及的权值，**给它倒序**，然后维护一个子树里面所有牌数和牌的权值和。
+ 直接查询第 $k$ 小即可，顺便维护子树牌权值和。时间复杂度只有一只 $\log$，注意边界情况。

总之就是，树状数组做可离线全局第 $k$ 大、全局 $k$ 的排名这种题目，还是有前途的。

---

## 作者：AKPC (赞：0)

事实上节点 $dep$ 的奇偶性决定了谁在这个节点操作。考虑从下往上搜索。设 $f_i$ 表示 $i$ 节点操作得到答案。在一个节点 $u$ 时，希望答案最大则会选择所有叶子中 $f$ 最大的那个，如果希望答案最小则选择 $f$ 最小的，直接转移即可。

问题在于如何求 $1\to i$ 的中位数（$i$ 是叶子），dfs 的时候使用一个对顶堆解决这个问题（对顶堆需要维护插入一个数，删除一个数以及查询中位数）。

[code](https://www.luogu.com.cn/paste/wzme6e4b)。

---

## 作者：Crazyouth (赞：0)

## 分析

不难发现，这题难点在于求一点到根的中位数，而不在于这个博弈论的幌子。既然是中位数，那么就可以想到使用 pb_ds 中的 tree 容器去存储当前经过路径上的点权（pb_ds 是不可重集所以带个点的编号组成 pair 再存进去），每次查询时使用它自带的 `find_by_order()` 函数即可。

至于这个假的博弈论，令 $dp_i$ 表示棋子从 $i$ 开始时最终得分，不难发现有转移：

$$
dp_i=
\begin{cases}
f_i & son_i=\varnothing\\
\max_{v\in son_i}{dp_v} & son_i\ne\varnothing \land2\mid dep_i\\
\min_{v\in son_i}{dp_v} & \text{otherwise}
\end{cases}
$$

其中 $f_i$ 表示 $i$ 到根路径上的点权中位数，$son_i$ 表示所有 $i$ 的儿子组成的集合，$dep_i$ 表示 $i$ 到 $1$ 最短路径上的点数。

## AC Code
```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define pii pair<int,int>
tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update> t;
const int N=1e5+10;
int a[N],f[N],dp[N],dep[N];
vector<int> G[N];
void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1;
	t.insert({a[u],u});
	f[u]=(t.size()%2?t.find_by_order(((t.size()+1)>>1)-1)->first:(t.find_by_order(t.size()/2-1)->first+t.find_by_order(t.size()/2)->first)/2);
	for(auto v:G[u])
	{
		if(v==fa) continue;
		dfs(v,u);
	}
	t.erase({a[u],u});
}
void dfs2(int u,int fa)
{
	int cnt=0;
	if(dep[u]%2==0) dp[u]=1e9;
	for(auto v:G[u])
	{
		if(v==fa) continue;
		cnt++;
		dfs2(v,u);
		dp[u]=(dep[u]%2?max(dp[u],dp[v]):min(dp[u],dp[v]));
	}
	if(!cnt) dp[u]=f[u];
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	dfs2(1,0);
	cout<<dp[1];
}

---

## 作者：Empty_Dream (赞：0)

## 题意

有一颗 $N$ 个点的树，每个点有点权 $A_i$，有一个节点在节点 $1$ 上。

- 有两个人 Alice 和 Bob 轮流操作：将棋子移动到所在节点的子节点。
- 到当前节点的得分定义为：经过点点权的中位数。
- Alice 希望得分尽可能大，Bob 希望得分尽可能小。
- 到达叶子节点，游戏结束。

Alice 先手操作，求最终得分。

## 分析

首先来看中位数怎么求，第一反应是用 `vector` 暴力存储，每次 `insert` 和 `erase` 来维护中位数，但是这个东西常数稍微有点大，导致会被卡，所以考虑别的方式。参考[这题](https://www.luogu.com.cn/problem/P1168)（虽然这题可以用 `vector` 过）用到了**对顶堆**，这里因为要 `erase` 所以考虑使用**对顶 `multiset`**，就是维护两个 `multiset`，$st1$ 和 $st2$ 分别存储小于等于中位数的和大于中位数的，始终保证 $size(st1) = size(st2)$ 或 $size(st1) = size(st2) + 1$。这样中位数就是 $\frac{\max\{st1\}+\min\{st2\}}{2}$ 或 $\max\{st1\}$。

解决完中位数之后我们可以得到每个叶子节点的得分 $ans_u$。考虑一棵子树的答案是怎么来的，不难发现每一棵子树的答案是固定的（从递归的角度想，倒数第二层答案肯定确定，倒数第三层的人肯定会选符合自己期望的，其实也就确定了，推广到全部节点也是相同的）。所以就可以设 $dp_u$ 表示从根节点走到 $u$ 并继续往下走的答案是什么，转移分两个人的情况：

- 当前节点 Alice 走：$dp_{u}=\max_{u \to v}\{dp_v\}$。
- 当前节点 Bob 走：$dp_u=\min_{u\to v}\{dp_v\}$。

当然，如果走到了叶子节点，$dp_u=ans_u$。最终答案就是 $dp_1$。

注意两个 `multiset` 的维护，如删除操作删迭代器而不是值。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define fir first
#define sec second
#define memset(a, b) memset(a, b, sizeof(a))
#define endl '\n'
using namespace std;

const int N = 1e5 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f3f3f3f3f;

int n;
int a[N], ans[N], dp[N], dep[N];
vector<int> g[N];
multiset<int> st1, st2;

int gets(){//取中位数
	if (st1.size() == st2.size()) return (*--st1.end() + *st2.begin()) / 2;
	return *--st1.end();
}

void dfs(int u, int fa){
	if (g[u].size() == 1 && u != 1) return dp[u] = gets(), void();//叶子节点就等于中位数
	dep[u] = dep[fa] + 1;//记录 dep，谁先手
	if (dep[u] % 2 == 0) dp[u] = inf;
	for (auto vv : g[u]){
		if (vv == fa) continue;
		if (a[vv] <= *--st1.end()) st1.insert(a[vv]);
		else st2.insert(a[vv]);
		while (st1.size() > st2.size() + 1) st2.insert(*--st1.end()), st1.erase(--st1.end());
		while (st2.size() > st1.size()) st1.insert(*st2.begin()), st2.erase(st2.begin());//维护对顶 multiset
		dfs(vv, u);
		if (st1.count(a[vv])) st1.erase(st1.find(a[vv]));
		else st2.erase(st2.find(a[vv]));
		while (st1.size() > st2.size() + 1) st2.insert(*--st1.end()), st1.erase(--st1.end());
		while (st2.size() > st1.size()) st1.insert(*st2.begin()), st2.erase(st2.begin());
		if (dep[u] & 1) dp[u] = max(dp[u], dp[vv]);//dp 转移，可以压在一起操作
		else dp[u] = min(dp[u], dp[vv]);
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1, u, v; i < n; i++){
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	st1.insert(a[1]);//先插入当前节点
	dfs(1, 0);
	cout << dp[1];
	return 0;
}
```

---

## 作者：Engulf (赞：0)

关心每个叶子节点到根的路径上的点权值的集合 $S$ 的中位数，转化为 $S$ 的第 $\left\lceil \dfrac{|S|}{2} \right\rceil$ 小值和 $\left\lceil \dfrac{|S| + 1}{2} \right\rceil$ 小值的平均值。

我们需要一个数据结构满足以下性质：
- 支持插入删除
- 支持查询 $k$ 小值。

不难想到用权值线段树维护，因为值域是 $[1, 10^9]$，动态开点即可。

考虑博弈的过程，对树黑白染色，根为黑色，相邻的节点颜色不同。容易发现，在黑色点时是 $A$ 的回合，在白色点时是 $B$ 的回合。因为 $A$ 希望中位数最大，所以肯定是往子树中能走到的最大值那里走，$B$ 就是选小的那个。

考虑一个动态规划，设 $f_u$ 为从 $u$ 出发，能得到的最大中位数。分讨一下：
- $u$ 是叶子，权值用线段树得到。
- $u$ 是黑点，$f_u = \max\limits_{v \in son_u} f_v$。
- $u$ 是白点，$f_u = \min\limits_{v \in son_u} f_v$。

自下而上 dp 一次即可。答案就是 $f_1$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e5 + 5;

int n;
int a[N];

vector<int> g[N];

int ls[N * 50], rs[N * 50];
int tr[N * 50];
int root, idx;

int tot;

void modify(int &p, int l, int r, int x, int v) {
    if (!p) p = ++idx;
    tr[p] += v;
    if (l == r) return;
    int mid = l + r >> 1;
    x <= mid ? modify(ls[p], l, mid, x, v) : modify(rs[p], mid + 1, r, x, v);
}

int query(int p, int l, int r, int k) {
    if (!p) return 0;
    if (l == r) return l;

    int mid = l + r >> 1;
    int cnt = tr[ls[p]];
    if (k <= cnt) return query(ls[p], l, mid, k);
    return query(rs[p], mid + 1, r, k - cnt);
}

inline int median() {return (query(root, 1, 1e9, (tot + 1) / 2) + query(root, 1, 1e9, (tot + 2) / 2)) / 2;}

int val[N];

void dfs(int u, int fa) {
    int child = 0;
    modify(root, 1, 1e9, a[u], 1);
    tot++;
    for (auto v: g[u]) {
        if (v == fa) continue;
        child++;
        dfs(v, u);
    }
    if (!child)
        val[u] = median();
    tot--;
    modify(root, 1, 1e9, a[u], -1);
}

void merge(int u, int fa, int col = 1) {
    int child = 0;
    for (auto v: g[u]) {
        if (v == fa) continue;
        child++;
        merge(v, u, col ^ 1);
    }
    if (!child) return;

    if (col) val[u] = 0;
    else val[u] = 2e9;
    for (auto v: g[u]) {
        if (v == fa) continue;
        if (col) val[u] = max(val[u], val[v]);
        else val[u] = min(val[u], val[v]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    dfs(1, 0);

    merge(1, 0);

    cout << val[1] << "\n";

    return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

考虑当前在 $u$，经过最优决策后会走向 $to$。

分情况讨论 $to$：

1. 当前该 $A$ 走，则 $to$ 的子树中的某一个叶子节点到根节点的路径上的中位数应该最大。

2. 当前该 $B$ 走，则 $to$ 的子树中的某一个叶子节点到根节点的路径上的中位数应该最小。

所以我们事实上只需要知道叶子节点的中位数，而叶子节点的中位数用权值线段树即可。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=1e5+10,M=60; 
int n; 
int p[N]; 
int rt[N]; 
int a[N],b[N]; 
int h[N],idx=0; 
struct Edge{ 
	int to,ne; 
}e[N<<1]; 
struct Node{ 
	int ls,rs; 
	int cnt; 
}tr[N*M]; 
il void add(int u,int v){
	e[idx].to=v,e[idx].ne=h[u],h[u]=idx++; 
} 
il void insert(int &u,int p,int l,int r,int x){ 
	u=++idx; tr[u]=tr[p]; tr[u].cnt++; 
	if(l==r) return ; int mid=l+r>>1; 
	if(x<=mid) insert(tr[u].ls,tr[p].ls,l,mid,x); 
	else insert(tr[u].rs,tr[p].rs,mid+1,r,x); 
} 
il int query(int u,int l,int r,int k){ 
	if(l==r) return l; 
	int mid=l+r>>1; int cnt=tr[tr[u].ls].cnt; 
	if(k<=cnt) return query(tr[u].ls,l,mid,k); 
	return query(tr[u].rs,mid+1,r,k-cnt); 
} 
int ans=1; 
pii Min[N],Max[N]; 
il int dfs(int u,int fa,int dep,bool flag){ 
	Min[u].x=1e9+7; 
	insert(rt[u],rt[fa],1,1e9+7,a[u]); 
	for(int i=h[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; 
		if(to==fa) continue; 
		int s=dfs(to,u,dep+1,flag^1); 
		if(Min[u].x>s) Min[u].x=s,Min[u].y=to;  
		if(s>Max[u].x) Max[u].x=s,Max[u].y=to; 
	} if(Min[u].x==1e9+7){ 
		if(dep&1) p[u]=query(rt[u],1,1e9+7,dep/2+1); 
		else p[u]=(query(rt[u],1,1e9+7,dep/2)+query(rt[u],1,1e9+7,dep/2+1))/2; 
		Min[u]=Max[u]={p[u],u}; 
		return p[u]; 
	} 
	if(flag) return Max[u].x;
	return Min[u].x;
} 

signed main(){ 
	memset(h,-1,sizeof h); 
	n=read(); int num=0; 
	for(int i=1;i<=n;i++) a[i]=read(); 
	for(int i=1,u,v;i<n;i++) u=read(),v=read(),add(u,v),add(v,u); 
	printf("%lld\n",dfs(1,0,1,1)); 
	return 0; 
} 
```

---

