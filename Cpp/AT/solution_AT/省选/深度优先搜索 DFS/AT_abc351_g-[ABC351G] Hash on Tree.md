# [ABC351G] Hash on Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc351/tasks/abc351_g

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点の根付き木があります。  
 頂点 $ 1 $ が根で、頂点 $ i $ $ (2\ \leq\ i\ \leq\ N) $ の親は頂点 $ p_i $ です。$ (p_i\ \lt\ i) $  
 また、数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ があります。

根付き木の **ハッシュ値** を次の手順によって得られる値とします。

- $ f(n) $ $ (1\ \leq\ n\ \leq\ N) $ を $ n\ =\ N,\ N-1,\ \dots,\ 2,\ 1 $ の順に次の計算をすることで得られる値とする。
  - 頂点 $ n $ が葉の場合、$ f(n)\ =\ A_n $ とする。
  - 頂点 $ n $ が葉でない場合、$ n $ の子からなる集合を $ C(n) $ として $ \displaystyle\ f(n)\ =\ A_n\ +\ \prod_{c\ \in\ C(n)}\ f(c) $ とする。
- $ f(1)\ \bmod{998244353} $ を根付き木のハッシュ値とする。
 
$ Q $ 個のクエリを与えられる順に処理してください。  
 各クエリでは $ v,\ x $ が与えられるので、$ A_v $ の値を $ x $ に更新した後、根付き木のハッシュ値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ p_i\ \lt\ i $
- $ 0\ \leq\ A_i\ \lt\ 998244353 $
- $ 1\ \leq\ v\ \leq\ N $
- $ 0\ \leq\ x\ \lt\ 998244353 $
- 入力される値は全て整数
 
### Sample Explanation 1

はじめ、$ A\ =\ (3,\ 5,\ 1) $ です。 $ 1 $ 番目のクエリは次のように処理されます。 - $ A_3 $ を $ 4 $ に更新する。$ A\ =\ (3,\ 5,\ 4) $ となる。 - 根付き木のハッシュ値は以下の手順により $ 23 $ となるので、これを出力する。 - 頂点 $ 3 $ は子を持たない。よって $ f(3)\ =\ 4 $ である。 - 頂点 $ 2 $ は子を持たない。よって $ f(2)\ =\ 5 $ である。 - 頂点 $ 1 $ は頂点 $ 2,\ 3 $ を子に持つ。よって $ f(1)\ =\ 3\ +\ 5\ \times\ 4\ =\ 23 $ である。 - $ f(1)\ \bmod{998244353}\ =\ 23 $ を根付き木のハッシュ値とする。 $ 2 $ 番目のクエリは次のように処理されます。 - $ A_2 $ を $ 1 $ に更新する。$ A\ =\ (3,\ 1,\ 4) $ となる。 - 根付き木のハッシュ値は以下の手順により $ 7 $ となるので、これを出力する。 - 頂点 $ 3 $ は子を持たない。よって $ f(3)\ =\ 4 $ である。 - 頂点 $ 2 $ は子を持たない。よって $ f(2)\ =\ 1 $ である。 - 頂点 $ 1 $ は頂点 $ 2,\ 3 $ を子に持つ。よって $ f(1)\ =\ 3\ +\ 1\ \times\ 4\ =\ 7 $ である。 - $ f(1)\ \bmod{998244353}\ =\ 7 $ を根付き木のハッシュ値とする。

## 样例 #1

### 输入

```
3 2
1 1
3 5 1
3 4
2 1```

### 输出

```
23
7```

## 样例 #2

### 输入

```
5 4
1 1 2 2
2 5 4 4 1
3 3
5 0
4 5
5 2```

### 输出

```
29
17
17
47```

## 样例 #3

### 输入

```
10 10
1 2 1 2 5 6 3 5 1
766294629 440423913 59187619 725560240 585990756 965580535 623321125 550925213 122410708 549392044
1 21524934
9 529970099
6 757265587
8 219853537
5 687675301
5 844033519
8 780395611
2 285523485
6 13801766
3 487663184```

### 输出

```
876873846
952166813
626349486
341294449
466546009
331098453
469507939
414882732
86695436
199797684```

# 题解

## 作者：adam01 (赞：8)

考虑动态 dp 的套路，先树剖一下，令 $son(x)$ 为点 $x$ 的重儿子。 $g_x=\prod\limits_{u\in C(x)\land u\neq son(x)}f_u$。

于是有 $f_x=f_{son(x)}g_x+a_x$。

于是 $\begin{bmatrix}f_x&1\end{bmatrix}=\begin{bmatrix}f_{son(x)}&1\end{bmatrix}\begin{bmatrix}g_x&0\\ a_x&1\end{bmatrix}$。

然后直接线段树维护矩阵乘法就行了。

有一点细节，比如要维护儿子节点 $f=0$ 的个数。

不懂的可以做一下 [P4719](https://www.luogu.com.cn/problem/P4719)。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define int ll

const int N = 2e5 + 5, p = 998244353;
int dfn[N], top[N], dn[N], fa[N], son[N], sz[N], a[N], c[N], f[N], g[N], g2[N], ts, n;
bool zz[N];

vector<int> e[N];
struct M
{
    int a[2][2];
    M operator*(M x)
    {
        M y; memset(y.a, 0, sizeof y.a);
        for(int i = 0; i < 2; i ++) for(int j = 0; j < 2; j ++) for(int k = 0; k < 2; k ++)
            (y.a[i][k] += a[i][j] * x.a[j][k]) %= p;
        return y;
    }
};

struct sgt
{
    M a[N << 2];
    void pu(int x) {a[x] = a[x << 1 | 1] * a[x << 1];}
    void upd(int q, int l, int r, int x, M v)
    {
        if(l == r) return a[x] = v, void();
        int mid = l + r >> 1;
        if(mid >= q) upd(q, l, mid, x << 1, v);
        else upd(q, mid + 1, r, x << 1 | 1, v);
        pu(x);
    }
    M qry(int ql, int qr, int l, int r, int x)
    {
        if(ql <= l && r <= qr) return a[x];
        int mid = l + r >> 1;
        if(mid < ql) return qry(ql, qr, mid + 1, r, x << 1 | 1);
        if(mid >= qr) return qry(ql, qr, l, mid, x << 1);
        return qry(ql, qr, mid + 1, r, x << 1 | 1) * qry(ql, qr, l, mid, x << 1);
    }
}t;

void dfs1(int x, int fa)
{
    sz[x] = 1;
    ::fa[x] = fa;
    f[x] = 1;
    for(int i : e[x])
    {
        dfs1(i, x);
        f[x] = f[x] * f[i] % p;
        sz[x] += sz[i];
        if(sz[i] >= sz[son[x]]) son[x] = i;
    }
    if(e[x].empty()) f[x] = 0;
    f[x] = (f[x] + a[x]) % p;
    zz[x] = f[x] == 0;
}

void dfs2(int x, int tp)
{
    dfn[x] = ++ts;
    top[x] = tp;
    dn[tp] = x;
    if(son[x]) dfs2(son[x], tp);
    g[x] = g2[x] = 1;
    for(int i : e[x])
        if(i != son[x])
        {
            dfs2(i, i);
            c[x] += !f[i];
            g[x] = g[x] * f[i] % p;
            if(f[i]) g2[x] = g2[x] * f[i] % p;
        }
    if(e[x].empty()) g[x] = g2[x] = 0;
    t.upd(dfn[x], 1, n, 1, {g[x], 0, a[x], 1});
}

int qpow(int a, int b)
{
    if(!b) return 1;
    return ((b & 1) ? a : 1ll) * qpow(a * a % p, b >> 1) % p;
}

void upd(int u, int v)
{
    M x = t.qry(dfn[u], dfn[u], 1, n, 1);
    x.a[1][0] = v;
    t.upd(dfn[u], 1, n, 1, x);
    while(fa[top[u]])
    {
        u = top[u];
        M y = t.qry(dfn[u], dfn[dn[u]], 1, n, 1);
        int nf = y.a[1][0];
        if(nf && zz[u]) c[fa[u]] --, zz[u] = 0;
        else if(nf == 0 && !zz[u]) c[fa[u]] ++, zz[u] = 1;
        M z = t.qry(dfn[fa[u]], dfn[fa[u]], 1, n, 1);
        if(f[u]) g2[fa[u]] = qpow(f[u], p - 2) * g2[fa[u]] % p;
        if(c[fa[u]]) g[fa[u]] = 0;
        else
        {
            g2[fa[u]] = g2[fa[u]] * nf % p;
            g[fa[u]] = g2[fa[u]];
        }
        f[u] = nf;
        z.a[0][0] = g[fa[u]];
        t.upd(dfn[fa[u]], 1, n, 1, z);
        u = fa[u];
    }
}

signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int q;
    cin >> n >> q;
    for(int i = 2; i <= n; i ++)
    {
        int x; cin >> x;
        e[x].push_back(i);
    }
    for(int i = 1; i <= n; i ++) cin >> a[i];
    dfs1(1, 0);
    dfs2(1, 1);
    while(q --)
    {
        int x, v; cin >> x >> v;
        upd(x, v);
        cout << t.qry(dfn[1], dfn[dn[1]], 1, n, 1).a[1][0] << "\n";
    }

    return 0;
}
```

---

## 作者：H_W_Y (赞：3)

> 给你一棵 $n$ 个节点的树，每个点有点权 $a_u$，定义每个节点的 $f_u$ 为
> $$
> f_u=
> \begin{cases}
> a_u & u 是叶子
> \\
> a_u + \prod_{v \in s_u} f_v & u不是叶子
> \end{cases}
> \pmod {998244353}
> $$
> 其中 $s_u$ 表示 $u$ 的儿子集合。
> 
> 给定 $Q$ 次修改，每次给出 $x,y$，将 $a_x$ 修改为 $y$，询问此时 $f_1$ 的值。
> 
> $1 \le n,Q \le 2 \times 10^5,0 \le a_i,y \lt 998244353$。

看到题目就容易发现这时一个动态 dp 问题，我们就可以往 ddp 方向考虑。

具体来说，对树进行树链剖分，我们希望每个节点只维护其轻儿子的乘积和，然后再用矩阵乘法进行转移。

每次修改只会在重链头修改，可以做到双 $\log$。现在问题就在于如何构建这个 dp 呢？



我们设 $g_u = \prod_{v \in s_u \land v \neq son_u} f_v$，也就是所有轻儿子的 $f$ 的乘积。

设 $f'_u = \prod_{v \in s_u} f_v$，那么有 $f_u = f'_u+a_u$。

我们尝试构造矩阵 $A$ 满足
$$
\left[
\begin{matrix}
f'_{son_u} & a_{son_u}
\end{matrix}
\right]
\times A = 
\left[ 
\begin{matrix}
f'_{u} & a_u
\end{matrix}
\right]
$$
容易发现这是简单的，构造出
$$
A= \left[
\begin{matrix}
g_{u} & 0
\\
g_u & \frac {a_u} {a_{son_u}}
\end{matrix}
\right]
$$
于是我们用线段树维护 $A$ 矩阵的乘积，那么最后的答案就可以从 $1$ 所在重链的乘积得到了。



但是这道题最恶心的地方在于 $a_u$ 可能为 $0$，也就是你根本没法求逆元。

对于这种情况，笔者的做法是将 $a_u$ 看成 $1$，并对其父亲的矩阵进行修改，也就是变成
$$
A= \left[
\begin{matrix}
g_{u} & 0
\\
0 & \frac {a_u} {a_{son_u}}
\end{matrix}
\right]
$$
反之如果 $a_u$ 是重链头，在算 $f$ 的时候需要 $-1$。

而对于我们维护的 $g$，显然不能把 $0$ 乘进去的，维护一下 $f_v=0$ 的个数，在线段树 update 的时候特判一下是否有 $0$ 即可。具体可见代码。



总时间复杂度 $\mathcal O(Q \log^2 n)$。[代码](https://atcoder.jp/contests/abc351/submissions/52904014)。

---

## 作者：lfxxx (赞：2)

来发单 $\log n$ Top tree 解法作为 Top tree 解决动态 dp 问题的示范。

首先如果一个问题可以动态 dp，代表可以写成矩阵的形式，这等价于对于一个联通子图来说，若其中只有一个叶子的值不确定，我们可以把这个联通子图的根的 dp 值写成关于不确定叶子的值的线性变换形式，对于这道题目而言就是 $y = k \times x + b$ 的一次函数形式。

更进一步地化简，因为 $dp_{u} = a_{u} + \prod dp_v$，而 $a_u$ 是一个很简单的项，所以不妨对于每个联通子图表示出 $\prod dp_v = k \times dp_{x} + b$ 这里 $x$ 表示联通子图中尚未确定的那个点的 $dp$ 值。

引出联通子图的划分结构后，接下来就是 Top tree 板子了，考虑对于一个簇（联通子图）维护出上述变换，然后考虑怎么合并。

在 compress 时假若把 $x,y$ 合并到 $w$ 上，并且 $u,v$ 表示簇的两个节点，那么 $w_k = x_k \times y_k,w_b = x_k \times y_b + x_k \times a_{x_v} + x_b$。

对于 rake 合并的情况，有 $w_k = y_k \times (x_k \times a_{x_v} + x_b),w_b = y_b \times (x_k \times a_{x_v} + x_b)$。

修改点就从这个点因为合并而不是界点的簇开始向上爬并不断地更新答案即可做到 $O(n \log n + q \log n)$。

卡卡常跑得很快，截至写这篇题解时，还是最优解。

```cpp
#include<bits/stdc++.h>
const int mod = 998244353;
//#define lowbit(x) (x&(-x))
using namespace std;
namespace IO{
    const int SIZE=1<<21;
    static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
    #define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
    #define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
    #define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
    #define puts(x) IO::Puts(x)
    template<typename T>
    inline void read(T&x){
        for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
        for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15);
        x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    inline void Puts(const char*s){
        for(int i=0;s[i];++i)
            putchar(s[i]);
        putchar('\n');
    }
    struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;
const int maxn = 4e5+114;
struct node{
	int u,v,id;
	int k,b;
	char type;
	//u 在上面 v 在下面
}cluster[maxn];
int n,m,a[maxn];
int pos[maxn],fa[maxn],ls[maxn],rs[maxn];
char type[maxn];//P 是边点 C 是 compress 点 R 是 rake 点
int root=1;//根簇
void compress(node x,node y,node &w){
	//x 在上面 y 在下面
	w.u=x.u;
	w.v=y.v;
	w.k=1ll*x.k*y.k%mod;
	w.b=(1ll*x.k*y.b%mod+1ll*x.k*a[x.v]%mod+x.b)%mod;
	pos[x.v]=w.id;
	fa[x.id]=fa[y.id]=w.id;
	ls[w.id]=x.id;
	rs[w.id]=y.id;
	//cout<<"compress"<<w.u<<" "<<w.v<<" "<<w.ans<<'\n';
	w.type='C';
	root=w.id;
}
void rake(node x,node y,node &w){
	//把 x rake 到 y 上
	w.u=x.u;
	w.v=y.v;
	w.k=1ll*y.k*(1ll*x.k*a[x.v]%mod+x.b)%mod;
	w.b=1ll*y.b*(1ll*x.k*a[x.v]%mod+x.b)%mod;
	pos[x.v]=w.id;
	fa[x.id]=fa[y.id]=w.id;
	ls[w.id]=x.id;
	rs[w.id]=y.id;
	//cout<<"rake"<<w.u<<' '<<w.v<<' '<<w.ans<<'\n';
	w.type='R';
	root=w.id;
}
void update(int u){
    if(u==0) return ;
    if(cluster[u].type=='C'){
        compress(cluster[ls[u]],cluster[rs[u]],cluster[u]);
        update(fa[u]);
    }else{
        rake(cluster[ls[u]],cluster[rs[u]],cluster[u]);
        update(fa[u]);
    }
}
vector<int> E[maxn];
int father_pos[maxn];//一个点到其父亲的边的簇编号
int father[maxn];
int son[maxn],sz[maxn],tot;
vector<int> st[maxn];//重链上的点存到链顶
void dfs1(int u){
	sz[u]=1;
	for(int v:E[u]){
		if(v==father[u]) continue;
		father[v]=u;
		father_pos[v]=++tot;
		cluster[tot].u=u,cluster[tot].v=v,cluster[tot].id=tot,cluster[tot].k=1,cluster[tot].b=0;
		dfs1(v);
		if(sz[v]>sz[son[u]]) son[u]=v;
		sz[u]+=sz[v];
	}
}
void dfs2(int u,int tp){
	st[tp].push_back(u);
	if(son[u]!=0) dfs2(son[u],tp);
	for(int v:E[u]){
		if(v==father[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
vector<int> vec[maxn];
vector<int> pre[maxn];
int solve(int l,int r,int u){
    if(l>r) return 0;
	if(l==r) return father_pos[vec[u][l]];
	int L=l,R=r;
	while(L+1<R){
		int mid=(L+R)>>1;
		if((pre[u][mid]-pre[u][l-1])*2<=(pre[u][r]-pre[u][l-1])) L=mid;
		else R=mid;
	}
	int mid=L;
	int lson=solve(l,mid,u);
	int rson=solve(mid+1,r,u);
	int res=++tot;
	cluster[tot].id=tot;
	rake(cluster[lson],cluster[rson],cluster[res]);
	return res;
}
int calc(int l,int r,int u){
    if(l>r) return 0;
    if(l==r) return father_pos[vec[u][l]];
	int L=l,R=r;
	while(L+1<R){
		int mid=(L+R)>>1;
		if((pre[u][mid]-pre[u][l-1])*2<=(pre[u][r]-pre[u][l-1])) L=mid;
		else R=mid;
	}
	int mid=L;
	int lson=calc(l,mid,u);
	int rson=calc(mid+1,r,u);
	int res=++tot;
    cluster[tot].id=tot;
	compress(cluster[lson],cluster[rson],cluster[res]);
	return res;
}
void dfs3(int u){
	for(int x:st[u]){
        if(son[x]==0) continue;
		pre[x].push_back(0);
		vec[x].push_back(0);
		for(int v:E[x]){
			if(v!=son[x]&&v!=father[x]){
				dfs3(v);
				//收缩 (x,v) 一个簇
				vec[x].push_back(v);
			}
		}
		//在对这些轻儿子簇按中点分治的方法合并起来
		for(int i=1;i<=vec[x].size()-1;i++){
			pre[x].push_back(pre[x][i-1]+sz[vec[x][i]]);
		}
		int rt=solve(1,vec[x].size()-1,x);
		if(rt!=0){
		    tot++;
		    cluster[tot].id=tot;
            rake(cluster[rt],cluster[father_pos[son[x]]],cluster[tot]);
            father_pos[son[x]]=tot;//rake 到重链上
		}
	}
	vec[u].clear();
	pre[u].clear();
	pre[u].push_back(0);
	vec[u].push_back(0);
	for(int x:st[u]){
		vec[u].push_back(x);
	}
	for(int i=1;i<=vec[u].size()-1;i++){
		pre[u].push_back(pre[u][i-1]+sz[vec[u][i]]-sz[son[vec[u][i]]]);
	}
	if(u!=1) father_pos[u]=calc(1,vec[u].size()-1,u);//把重链上的边 compress 成一条
	else father_pos[u]=calc(2,vec[u].size()-1,u);
	E[u].clear();
	E[u].push_back(father[u]);
	return ;
}
int sum;
int main(){
    read(n);
    read(m);
    for(int i=2;i<=n;i++){
        int p;
        read(p);
        E[p].push_back(i);
        E[i].push_back(p);
    }
    for(int i=1;i<=n;i++) read(a[i]);
    dfs1(1);
    dfs2(1,1);
    dfs3(1);
    while(m--){
        int x,v;
        read(x);
        read(v);
        a[x]=v;
        update(pos[x]);
        write(((1ll*cluster[root].k*a[cluster[root].v]+cluster[root].b)+a[cluster[root].u])%mod);
        putchar('\n');
    }
	return 0;
}
```

---

## 作者：RabbieWjy (赞：2)

题目链接：[洛谷](https://www.luogu.com.cn/problem/AT_abc351_g)，[AtCoder](https://atcoder.jp/contests/abc351/tasks/abc351_g)。

[不一定更好的阅读体验](https://rabbiew.github.io/2024/04/28/atcoder-beginner-contest-351-g/)。

赛时想出来的动态 DP 做法，但是赛时没调完。

--------------------

**题意**

给定一棵 $N$ 个点的有根树，编号为 $1$ 到 $N$，根节点为 $1$，点 $i$ 的父亲是 $p_i\space (p_i < i)$。

有一个序列 $a=(a_1,a_2,\cdots,a_N)$，初始值给定。定义函数 $f(x)$ 如下：

- 如果 $x$ 是叶子，则 $f(x) = a_x$；

- 否则 $f(x) = a_x + \prod \limits_{c \in son(x)} f(c)$。

定义这棵树的值为 $f(1) \operatorname{mod} 998244353$。

有 $Q$ 次询问，每次将 $a_x$ 改为 $y$，询问当前树的值。

$2 \le N \le 2 \times 10 ^ 5$，$1 \le Q \le 2 \times 10^5$，$0 \le a_i,y < 998244353$。

---------------------------------

**解法**

发现 $f(x)$ 的值由它的儿子转移得来，可以 DP 求出刚开始的所有 $f(x)$。观察到每次修改只会影响到修改的点到根路径上的 $f(x)$ 值。

对于一个点 $u$，有$f(p_u) = a_{p_u} + f(u) \prod \limits_{c\in son(p_u) \operatorname{and} c \ne u} f(c)$。如果 $f(u)$ 被修改了，这个式子中的其他部分并不会改变。也就是说，对于一条往上走的链，设这条链的底部是点 $v$，那么这条链的值写出来形如 $A_k(A_{k-1}(\cdots(A_1 f(v) + B_1) \cdots) + B_{k - 1}) + B_k$，也就是若干个 $Ax + B$ 嵌套起来。这种形式让我们想到可以用矩阵表示这样的转移，用线段树维护矩阵的区间积，而修改一个点的 $a_x$ 只需要修改它对应的一个矩阵就行了。

现在要把链的做法放到树上。考虑树链剖分，一个点的 $f$ 先算出轻儿子的贡献，再从重儿子直接转移过来。记这个点为 $u$，重儿子为 $v$，对应到上面的 $Ax + B$，也就是 $A = \prod \limits_{c\in son(u) \operatorname{and} c\ne v} f(c)$，$x = f(v)$，$B = a_u$。把转移写成矩阵形式如下：

$$
\left[ \begin{matrix} f(v) & 1 \end{matrix} \right] \times \left[ \begin{matrix} \prod \limits_{c\in son(u) \operatorname{and} c\ne v} f(c) & 0 \newline a_u & 1 \end{matrix} \right] = \left[ \begin{matrix} f(u) & 1 \end{matrix} \right]
$$

每次修改时，要修改被修改的点的矩阵的左下角，以及每次跳轻边的时候，要修改新算出来的链头父亲的矩阵左上角，总共 $O(\log n)$ 次修改。对于一个点 $u$，$f(u)$ 也就是把 $u$ 开始的重链拉出来，从下到上求一次矩阵乘法，左下角的值。这里可以按 dfn 建一棵维护矩阵的区间乘积的线段树，支持单点修改和区间查询，注意矩阵乘法的顺序。

跳轻边时，矩阵左上角的值可以除以之前链头贡献的值，再乘上新的链头的 $f$ 求出来。注意题目数据中存在先把一个点赋值为 $0$，再改成非 $0$ 值的情况，不能只维护当前的矩阵左上角的值，否则还原不回去。可以对每个点，记录儿子中有多少个 $0$ 以及非 $0$ 儿子的乘积，如果儿子中有 $0$，则矩阵左上角也为 $0$，否则为儿子的积。

总时间复杂度为 $O(QK \log ^2 n)$，其中 $K$ 是矩阵乘法的复杂度。

[AC 提交记录](https://atcoder.jp/contests/abc351/submissions/52901323)。

---

## 作者：Accelessar (赞：1)

[link](https://atcoder.jp/contests/abc351/tasks/abc351_g)

看完题面马上就想到动态 DP 啊！可是赛时死活没调出来，怎么会是呢。

不会动态 dp 的请先完成 [P4719 【模板】"动态 DP"&动态树分治](/problem/P4719)。

然后发现本题比上面这个模板题更加简单，因为题面直接把 dp 式子给出了。

记 $son_u$ 为 $u$ 的重儿子，$g_u=\prod\limits_{v\neq son_u}f_v$，则

$$
f_u=\begin{cases}
A_u ,&u\text{ is a leaf} \\
A_u+f_{son_u}\times g_u ,&\text{otherwise.}
\end{cases}
$$

写成矩阵形式：

$$
\begin{bmatrix}
g_u & A_u \\
0 & 1
\end{bmatrix}
\times
\begin{bmatrix}
f_{son_u} \\
1
\end{bmatrix}
=
\begin{bmatrix}
f_u \\
1
\end{bmatrix}
$$

然后套上 DDP 板子即可。

实现时注意单独维护积中 $0$ 的个数。

[submission](https://atcoder.jp/contests/abc351/submissions/52921627).

---

## 作者：Limie (赞：1)

神仙题，疯狂%%%出题人。

考虑 DP 转移，设 $v$ 为 $u$ 的儿子，有两种转移。

1. 当 $f_v$ 变成 $f'_v$ 的时候，可得 $f'_u=\frac{f_u-a_u}{f_v} \times f'_v+a_u$。

2. 设 $b_u$ 表示 $u$ 的除 $v$ 之外的儿子的 $f$ 的乘积，则 $f'_u=a_u+b_u \times f'_v$。

发现第二种转移很容易写成矩阵形式，如果方便维护 $b$，则可 $O(\log k)$ 从 $v$ 转移到 $v$ 的 $k$ 级祖先。

于是考虑重链剖分。

维护 $b_u$ 为除 $u$ 的重儿子外所有儿子的 $f$ 的乘积。

于是就结束了。

```cpp
#include<bits/stdc++.h>
namespace Limie{
	#define x first
	#define y second
	using namespace std;
	typedef long long LL;
	typedef pair<int,int> PII;
	typedef unsigned long long ULL;
	typedef long double LD;
}
using namespace Limie;
const int mod=998244353;
//the common
int n,q;
int fa[200010],a[200010],h[200010],e[200010],ne[200010],idx;
void add(int a,int b){e[idx]=b,ne[idx]=h[a],h[a]=idx++;}
int qmi(int a,int b)
{
	int ans=1;
	while(b){
		if(b&1)ans=(LL)ans*a%mod;
		a=(LL)a*a%mod;
		b>>=1;
	}
	return ans;
}
//the matrix
struct matrix{
	int f[2];
	int& operator[](const int x){return f[x];}
	friend matrix operator*(matrix a,matrix b){
		matrix c;c[0]=(LL)a[0]*b[0]%mod;
		c[1]=((LL)a[0]*b[1]%mod+a[1])%mod;return c;
	}
};
//the hld
int num;
int dfn[200010],top[200010],sz[200010],son[200010],d[200010];
int b[200010],c[200010],f[200010],id[200010],len[200010];
void dfs1(int u)
{
	d[u]=d[fa[u]]+1,sz[u]=1,f[u]=1;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];dfs1(j);sz[u]+=sz[j];
		f[u]=1ll*f[u]*f[j]%mod;
		if(sz[son[u]]<sz[j])son[u]=j;
	}if(!son[u])f[u]=0;
	f[u]=(f[u]+a[u])%mod;
}
void dfs2(int u,int top)
{
	dfn[u]=++num,id[num]=u,::top[u]=top;len[top]++;
	if(son[u])dfs2(son[u],top),b[u]=1;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];if(j==son[u])continue;dfs2(j,j);
		if(f[j])b[u]=1ll*b[u]*f[j]%mod;else c[u]++;
	}
}
//the sgt
#define ls (u<<1)
#define rs (u<<1|1)
#define mid (tr[u].l+tr[u].r>>1)
struct Node{int l,r;matrix s;}tr[800010];
void pushup(int u){tr[u].s=tr[ls].s*tr[rs].s;}
void build(int u,int l,int r)
{
	tr[u]={l,r};if(l==r){
		tr[u].s[0]=c[id[l]]?0:b[id[l]],tr[u].s[1]=a[id[l]];
		return;
	}build(ls,l,mid),build(rs,mid+1,r),pushup(u);
}
void modify(int u,int x)
{
	if(tr[u].l==tr[u].r)
	{tr[u].s[0]=c[id[x]]?0:b[id[x]],tr[u].s[1]=a[id[x]];return;}
	if(x<=mid)modify(ls,x);else modify(rs,x);pushup(u);
}
matrix query(int u,int l,int r)
{
	if(l<=tr[u].l&&tr[u].r<=r)return tr[u].s;
	if(r<=mid)return query(u<<1,l,r);
	if(mid<l)return query(u<<1|1,l,r);
	return query(u<<1,l,r)*query(u<<1|1,l,r);
}
#undef ls
#undef rs
#undef mid
//the main
int main()
{
	int i;
	cin>>n>>q;
	memset(h,-1,sizeof h);
	for(i=2;i<=n;i++)cin>>fa[i],add(fa[i],i);
	for(i=1;i<=n;i++)cin>>a[i];
	dfs1(1);
	dfs2(1,1);
	build(1,1,n);
	while(q--){
		int u,x;
		cin>>u>>x;
		a[u]=x;
		while(1){
			int la=query(1,dfn[top[u]],dfn[top[u]]+len[top[u]]-1)[1];
			modify(1,dfn[u]);u=top[u];
			int f=query(1,dfn[u],dfn[u]+len[u]-1)[1];
			if(u==1){cout<<f<<'\n';break;}u=fa[u];
			if(la)b[u]=(LL)b[u]*qmi(la,mod-2)%mod;else c[u]--;
			if(f)b[u]=(LL)b[u]*f%mod;else c[u]++;
		}
	} 
}

```

---

## 作者：未来姚班zyl (赞：1)

很好的一道题，让我变成了乐子。

## 题目大意

给定一颗根为 $1$ 的带权树，节点 $i$ 的点权为 $A_i$。

定义一个点的权值为 $f_x$，如果 $x$ 为叶子，则 $f_x=A_x$，否则等于 $A_x$ 加上儿子的权值之积。

$m$ 次修改，每次修改一个点的点权，每次修改后请你求出 $f(1)$。

## 题目分析

ddp 板子题。对树重剖，设 $g_x$ 为轻儿子的权值之积，则 $f_x=g_xf_{son_x}+A_x$，直接写成矩阵就可以线段树维护。

然后我在赛时打完了这道题，并且感觉能够在最后两分钟绝杀比赛，然后 judge 突然的变得巨慢，不过前面的点都一点没有问题，我都开始欢呼了，结果，[WA 了最后两个点](https://atcoder.jp/contests/abc351/submissions/52886804)。绝杀变成了乐子，问题出在哪捏？看数据的最后两个点的名字就知道了。

没错，这题要注意对 $0$ 的特判，事实上很简单，只需要记录轻儿子中权值为 $0$ 的个数与除了值为 $0$ 以外的儿子的权值的乘积即可通过此题，复杂度 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
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
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =2e5+5,M=1e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,h[N],m,to[N<<1],nxt[N<<1],cnt,a[N];
inline void add_(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
struct mac{
	int a[2][2];
	mac(){
		memset(a,0,sizeof(a));
	}
	mac friend operator*(mac a,mac b){
		mac c;
		rep(i,0,1)rep(k,0,1)if(a.a[i][k])rep(j,0,1)add(c.a[i][j],mul(a.a[i][k],b.a[k][j]));
		return c;
	}
}G[N],K;
int bac[N],f[N],val[N],top[N],dfn[N],Time,siz[N],son[N],g[N],Id[N];
int c0[N],W[N]; 
inline void dfs(int x,int fa){
	val[x]=a[x],f[x]=fa,siz[x]=1;
	int W=1;
	e(x)if(y^fa)dfs(y,x),Mul(W,val[y]),siz[x]+=siz[y],son[x]=siz[y]>siz[son[x]]?y:son[x];
	if(son[x])add(val[x],W);
}
inline void Dfs(int x,int low){
	top[x]=low,dfn[x]=++Time,Id[Time]=x,bac[low]=Time;
	if(son[x])Dfs(son[x],low),g[x]=W[x]=1;
	e(x)if(y^son[x]&&y^f[x]){
		Dfs(y,y),c0[x]+=!val[y],Mul(g[x],val[y]);
		if(val[y])Mul(W[x],val[y]);
	}
	G[x].a[0][0]=g[x],G[x].a[0][1]=a[x],G[x].a[1][1]=1;
}
mac xd[N<<2];
inline void build(int x,int l,int r){
	if(l==r)return xd[x]=G[Id[l]],void();
	build(lc),build(rc),xd[x]=xd[L]*xd[R];
}
inline void modify(int x,int l,int r,int p){
	if(l==r)return xd[x]=G[Id[l]],void();
	p<=mid?modify(lc,p):modify(rc,p);
	xd[x]=xd[L]*xd[R];
}
inline mac query(int x,int l,int r,int Ll,int Rr){
	if(OK)return xd[x];
	if(Rr<=mid)return query(lc,Ll,Rr);
	if(Ll>mid)return query(rc,Ll,Rr);
	return query(lc,Ll,Rr)*query(rc,Ll,Rr);
}
inline void change(int x,int k){
	a[x]=G[x].a[0][1]=k;
	while(1){
		mac pr=query(Root,dfn[top[x]],bac[top[x]]);
		modify(Root,dfn[x]);
		mac nx=query(Root,dfn[top[x]],bac[top[x]]);
		if(top[x]==1)return;
		pr=pr*K,nx=nx*K;
		int pw=pr.a[0][0],nw=nx.a[0][0];
		if(pw&&nw)Mul(G[f[top[x]]].a[0][0],mul(nw,INV(pw))),Mul(W[f[top[x]]],mul(nw,INV(pw)));
		else if(!pw&&nw){
			c0[f[top[x]]]--;
			if(!c0[f[top[x]]])G[f[top[x]]].a[0][0]=W[f[top[x]]]=mul(W[f[top[x]]],nw);
			else Mul(W[f[top[x]]],nw);
		}else if(pw&&!nw){
			c0[f[top[x]]]++;
			G[f[top[x]]].a[0][0]=0;
			Mul(W[f[top[x]]],INV(pw));
		}
		x=f[top[x]];
	}
}
inline void Main(){
	n=read(),m=read();
	rep(i,2,n){
		int x=read();
		add_(x,i);
	}
	repn(i)a[i]=read();
	dfs(1,0),Dfs(1,1);
	build(Root);
	K.a[1][0]=1;
	repm(o){
		int x=read(),k=read();
		change(x,k);
		mac ans=query(Root,1,bac[1]);
		ans=ans*K;
		cout <<ans.a[0][0]<<'\n';
	}
}
signed main(){
	int T=1;
	while(T--)Main(); 
	return 0;
}
```

最难绷的一场 abc。

---

## 作者：g1ove (赞：1)

这场 abc F、G 质量堪忧。怎么能扔板子上来呢？

板子：[P4719 【模板】"动态 DP"&动态树分治](https://www.luogu.com.cn/problem/P4719)

## Solution
这种每次修改对后面询问有影响，又每次都要输出答案的，离线就基本做不了了，这时候就往动态算法想，其实做过几道 ddp 的题就看出来这是个板子。

由于题目中的式子性质优良，我们很明显可以把它写成矩阵的形式。

我们预处理轻儿子的乘积和，即 $g_{u}=\prod\limits_{v\in son,v\ne Hson}f_v$，然后问题中的式子就可以写成这个矩阵：

$$
\begin{bmatrix}
f_{son} & 1 \\
\end{bmatrix}
\times
\begin{bmatrix}
g_{now} &  0\\
a_{now} &  1\\
\end{bmatrix}=

\begin{bmatrix}
f_{now} & 1 \\
\end{bmatrix}$$

然后因为不方便转移，要从后往前乘，我们改造一下就变成：
$$
\begin{bmatrix}
g_{now} &  a_{now}\\
0 &  1\\
\end{bmatrix}
\times 
\begin{bmatrix}
f_{son} \\ 1
\end{bmatrix}=
\begin{bmatrix}
f_{now} \\ 1
\end{bmatrix}
$$
初始矩阵是 $\begin{bmatrix}0 \\ 1\end{bmatrix}$。

这样就可以从根节点往下乘了。

然后之后操作修改就是模板了，撤销操作用逆元即可。

然后这题一个小麻烦的地方就来了。因为这题有 $0$，然后 $0$ 没有逆元，所以要进行一些适当的处理即可，这个地方我选择的使用一个数组记录下轻儿子 $0$ 的个数，$g$ 数组不乘 $0$。

然后就是 ddp 的一些细节了。

使用的是树剖的写法，$w=2$ 是矩阵大小，还有个求逆元，时间复杂度 $O(q\log^2 n\times w^3+q\log n\log mod)$ 。

因为笔者的习惯，代码中 $f$ 代表上述的 $g$ 数组，代码中的 $g$ 数组代表矩阵。

Code
```c++
#include<bits/stdc++.h>
#define N 200005
#define ll long long
using namespace std;
const int mod=998244353;
ll inv(ll a,ll x=mod-2)
{
	ll res=1;
	while(x)
	{
		if(x&1) res=res*a%mod;
		a=a*a%mod;
		x>>=1;
	}
	return res;
}
int n;
int head[N],tot=1;
int a[N];
struct edge{
	int to,next;
}e[N*2];
void add(int u,int v)
{
	e[tot]=(edge){v,head[u]};
	head[u]=tot++;
}
ll f[N],w[N];
struct node{
	int r[2][2];
	int n,m;
}g[N],oo,zero;
node operator * (node a,node b)
{
	node c;
	c.n=a.n,c.m=b.m;
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++)
			c.r[i][j]=0;
	for(int k=0;k<2;k++)
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				c.r[i][j]=(c.r[i][j]+(1ll*a.r[i][k]*b.r[k][j]%mod))%mod;
	return c;
}
int pos[N];
struct segtree{
	node tr[N*4];
	void modify(int l,int r,int p,int x)
	{
		if(l==r)
		{
			tr[x]=g[pos[p]];
			return;
		}
		int mid=(l+r)/2;
		if(p<=mid) modify(l,mid,p,x*2);
		else modify(mid+1,r,p,x*2+1);
		tr[x]=tr[x*2]*tr[x*2+1];
	} 
	node query(int l,int r,int L,int R,int x)
	{
		if(l>R||r<L) return oo;
		if(l>=L&&r<=R) return tr[x]; 
		int mid=(l+r)/2;
		node lv=query(l,mid,L,R,x*2),rv=query(mid+1,r,L,R,x*2+1);
		if(lv.n==-1) return rv;
		if(rv.n==-1) return lv;
		return lv*rv;
	}
}tr;
int fa[N],dep[N],siz[N],Son[N];
int ed[N],id[N],ids,top[N];
int tag[N];
void dfs1(int now,int f)
{
	fa[now]=f;
	dep[now]=dep[f]+1;
	siz[now]=1;
	int maxx=0;
	for(int i=head[now];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==f) continue;
		dfs1(v,now);
		siz[now]+=siz[v];
		if(siz[v]>maxx) maxx=siz[v],Son[now]=v;
	}
}
void dfs2(int now,int topf)
{
	++ids;
	id[now]=ids;
	pos[ids]=now;
	ed[topf]=id[now];
	top[now]=topf;
	if(Son[now]) dfs2(Son[now],topf),w[now]=w[Son[now]];
	f[now]=1;
	for(int i=head[now];i;i=e[i].next)
	{
		int son=e[i].to;
		if(son==fa[now]||son==Son[now]) continue;
		dfs2(son,son);
		w[now]=w[now]*w[son]%mod;
		if(!w[son]) tag[now]++;
		else f[now]=f[now]*w[son]%mod;
	}
	w[now]+=a[now],w[now]%=mod;
	g[now].n=g[now].m=2;
	g[now].r[0][0]=f[now],g[now].r[0][1]=a[now],
	g[now].r[1][0]=0,g[now].r[1][1]=1;
	if(tag[now]) g[now].r[0][0]=0;
	tr.modify(1,n,id[now],1);
}
void updata(int x,ll v)
{
	g[x].r[0][1]=v;
	while(x)
	{
		ll last=tr.query(1,n,id[top[x]],ed[top[x]],1).r[0][1];
		tr.modify(1,n,id[x],1);
		ll now=tr.query(1,n,id[top[x]],ed[top[x]],1).r[0][1];
		x=fa[top[x]];
		if(!last) tag[x]--;
		else f[x]=f[x]*inv(last)%mod;
		if(!now) tag[x]++;
		else f[x]=f[x]*now%mod;
		if(tag[x]) g[x].r[0][0]=0;
		else g[x].r[0][0]=f[x];
	}
}
int q;
int main()
{
	oo.n=-1;
	zero.n=zero.m=2;
	zero.r[1][1]=1;
	scanf("%d%d",&n,&q);
	for(int i=2;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		add(x,i);
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	dfs1(1,0);
	dfs2(1,1);
	while(q--)
	{
		int v,x;
		scanf("%d%d",&x,&v);
		updata(x,v);
		printf("%d\n",tr.query(1,n,1,ed[1],1).r[0][1]);
	}
	return 0;
}
```

---

## 作者：lzyqwq (赞：0)

主要是自己记录一下。

> - 给出 $n$ 个点的有根树和 $(a_1,\dots,a_n)$。定义 $f(u)$ 为：
>
>   - 若 $u$ 为叶子，则 $f(u)=a_u$。
>
>   - 否则，$f(u)=a_u+\prod\limits_{v\in\text{son}(u)}f(v)$。
>
> - $q$ 次询问，每次令 $a_x\leftarrow v$，求 $f(1)$。其中所有运算均在模 $998244353$ 意义下进行。
>
> - $n,q\le 2\times 10^5$，$\color{red}{0}$ $\le a_i,v< 998244353$。

不难发现是 ddp 吧。但事实上用不到矩阵。

先重链剖分。设 $\text{res}_u$ 表示 $u$ 所有轻儿子答案的乘积。

然后对于一个叶子，设其到重链顶端的链从上至下依次为 $(p_1,\dots,p_k)$。对于 $i$，令序列 $(b(i)_1,\dots,b(i)_{k-i+1})$，其中 $b(i)_j=p_{i+j-1}$。那么 $f(p_i)=\sum\limits_{j=1}^{k-i+1}\left[\left(\prod\limits_{l=1}^{j-1} \text{res}_{b(i)_l}\right)\times a_{b(i)_j}\right]$。

考虑归纳法证明这个东西，对于 $i=k$ 显然成立。

若对于 $i\in[x,k]$ 时成立，则当 $i = x-1$ 时：

此时，因为父子关系，$\forall\,j\in[2,k-x+2],b(x-1)_j=b(x)_{j-1}$，且 $b(x-1)_1=p_{x-1}$。

那么：

$$\begin{aligned}f(p_{x-1})&=\text{res}_{p_{x-1}}\times \left\{\sum\limits_{j=1}^{k-x+1}\left[\left(\prod\limits_{l=1}^{j-1}\text{res}_{b(x)_l}\right)\times a_{b(x)_j}\right]\right\}+a_{p_{x-1}}\\&=\sum\limits_{j=2}^{k-x+2}\left[\text{res}_{p_{x-1}}\times \left(\prod\limits_{l=2}^{j-1}\text{res}_{b(x-1)_l}\right)\times a_{b(x-1)_j}\right]+a_{p_{x-1}}\\&=\sum\limits_{j=2}^{k-x+2}\left[ \left(\prod\limits_{l=1}^{j-1}\text{res}_{b(x-1)_l}\right)\times a_{b(x-1)_j}\right]+\left(\prod\limits_{l=1}^0\text{res}_{b(x-1)_l}\right)\times a_{p_{x-1}}\\&=\sum\limits_{j=1}^{k-(x-1)+1}\left[\left(\prod\limits_{l=1}^{j-1}\text{res}_{b(x-1)_l}\right)\times a_{b(x-1)_j}\right]\end{aligned}$$

证毕。KE 说这个很显然，可是我看了半天呜呜。

然后因为重链 dfs 序是连续的，所以考虑在线段树上维护这个东西。记 $\text{id}_i$ 为 $\text{dfn}$ 为 $i$ 的节点编号。

我们令 $[L,R]$ 的答案为，令 $b_j=\text{id}_{j+L-1}$ 后的：

$$\sum\limits_{j=1}^{R-L+1}\left[\left(\prod\limits_{l=1}^{j-1} \text{res}_{b_l}\right)\times a_{b_j}\right]$$

合并 $[L,\text{mid}]$ 和 $[\text{mid}+1,R]$ 的时候，发现右半边区间的答案需要整体乘上左半边这段链的 $\text{res}$ 积。具体考虑把上积拆成两部分。所以再维护一个积即可。

其实矩阵的话就不用考虑这么多证明了。但是一开始写了个假的重剖然后以为矩阵被卡常。。。

那么现在你已经会维护信息了。然后考虑修改。每次修改，只有它本身和它根链上每条重链顶端的父亲对应的线段树叶节点的信息需要修改。这是基础的 ddp 了吧。那么计算一下修改前和修改后的值，考虑一下 $\text{res}$ 的变化就行了。但是**会出现 $\boldsymbol f$ 值为 $\boldsymbol 0$ 的情况**。这样你本来想除以原来的 $f$ 值，乘上新的 $f$ 值，得到新的 $\text{res}$ 值，就寄掉了。

考虑维护 $0$ 的个数和 $f$ 值非 $0$ 轻儿子的 $f$ 值积。然后判断 $0$ 的个数得到新的 $\text{res}$。每次修改 $0$ 个数以及非 $0$ 积都是容易的。

那么坑点被解决了。每次修改后查询根到链底的答案即可。

默认 $n,q$ 以及 $\log n,\log |V|$ 同阶，时间复杂度为 $\mathcal{O}\left(n\log^2 n\right)$，空间复杂度为 $\mathcal{O}(n)$。

[Code](https://atcoder.jp/contests/abc351/submissions/52918271)

---

