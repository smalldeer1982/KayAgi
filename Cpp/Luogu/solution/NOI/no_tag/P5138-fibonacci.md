# fibonacci

## 题目背景

Wolfycz 很喜欢 Fibonacci 数列（雾

## 题目描述

Wolfycz 热衷于研究 Fibonacci 数列，他定义 $Fib_i$ 为Fibonacci 数列的第 $i$ 项，同时定义 $Fib_0=0,Fib_1=1$，并且对于任意的$i$，满足 $Fib_i=Fib_{i-1}+Fib_{i-2}$。

Wolfycz 也喜欢植树，有一天他植了一颗滑稽树（就是 OI 中所说的树，$n$ 个点，$n-1$ 条边，以 $1$ 为根），初始时树上的节点都没有滑稽果，于是 Wolfycz 不惜花重金购入了金坷垃，每次他给滑稽树上的节点 $x$ 施肥 $k$ 克，会使 $x$ 以及它的子树都长出一堆滑稽果，具体来讲，如果 $x$ 子树中的某个节点距离 $x$ 的距离为 $D$，那么这个节点就会长出 $Fib_{D+k}$ 个滑稽果

Wolfycz 觉得滑稽树上滑稽果已经够多了，因此他想 Van 游戏，所以他会时不时询问你两个节点路径上有多少个滑稽果。

## 说明/提示

对于$30\%$的数据，$N,M,k\leqslant 10^3$

对于$100\%$的数据，$N,M\leqslant 10^5$，$1\leqslant x,y\leqslant N$，$1\leqslant k\leqslant 10^{18}$。

## 样例 #1

### 输入

```
5 10
2 1
1 3
2 4
5 2
Q 1 5
U 1 1
Q 1 1
Q 1 2
Q 1 3
Q 1 4
Q 1 5
U 2 2
Q 2 3
Q 4 5```

### 输出

```
0
1
2
2
4
4
4
10```

# 题解

## 作者：george0929 (赞：9)

**提供一种不使用 $Fib_{n+m}$ 公式的做法**。

先写出 Fib 矩阵 $M=\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}$。

每个点维护两个矩阵 $A,B$，其中 $A$ 固定，$B$ 会因为修改操作改变。

记一个节点的深度为 $dep$，根的深度为 $1$，则令这个点的 $A=M^{dep}$。

对于子树 $u$ 的加操作，转化为子树 $u$ 的每个点的 $B$ 加上 $M^{k-dep_u+1}$。

不难发现，一个点真正的 Fib 矩阵就是 $A\times B$，Fib 矩阵右下角即为这个点的点权（即滑稽果个数）。

使用重链剖分和 DFS 序，将树上问题转为序列问题。

序列问题是：每个下标有两个矩阵 $A,B$，需要支持 $B$ 的区间加、区间查询 $A\times B$ 的和。

用线段树维护，线段树每个节点维护 $Sa=\sum A$ 和 $Sab=\sum A\times B$，再维护一个懒标记 $K$。

对线段树上一个节点进行加 $B$，有 $Sab\leftarrow Sab+Sa\times B$，$K\leftarrow K+B$。

下传标记时，设线段树上当前点的父节点为 $fa$，有 $K\leftarrow K+K_{fa}$，$Sab\leftarrow Sab+Sa\times K_{fa}$。

时间复杂度 $O(n\log^2 n)$，八倍常数，[完全不卡常](https://www.luogu.com.cn/record/225744270)。

注意 $k$ 要开 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int mod=1e9+7;
inline void upd(int &x,int y){
	x=(x+y)%mod;
}
struct Mat{
	int a00,a01,a10,a11;
	Mat operator +(Mat b){
		return {(a00+b.a00)%mod,(a01+b.a01)%mod,
				(a10+b.a10)%mod,(a11+b.a11)%mod};
	}
	Mat operator *(Mat b){
		Mat c={0,0,0,0};
		c.a00  =  1ll*a00*b.a00%mod;
		upd(c.a00,1ll*a01*b.a10%mod);
		c.a01  =  1ll*a00*b.a01%mod;
		upd(c.a01,1ll*a01*b.a11%mod);
		c.a10  =  1ll*a10*b.a00%mod;
		upd(c.a10,1ll*a11*b.a10%mod);
		c.a11  =  1ll*a10*b.a01%mod;
		upd(c.a11,1ll*a11*b.a11%mod);
		return c;
	}
	bool ck(){
		return a00||a11||a10||a01;
	}
	void set0(){
		a00=a01=a10=a11=0;
	}
	void set1(){
		a00=a11=1,a10=a01=0;
	}
};
int n,m;
vector<int> V[100005];
Mat A[100005],_A[100005];
int f[100005],sz[100005],dep[100005];
int son[100005],top[100005],dfn[100005],out[100005];
int tot;
Mat M={1,1,1,0};
Mat invM[100005];
#define ll long long
Mat ksm(Mat a,ll b){
	Mat res;res.set1();
	while(b){
		if(b&1) res=res*a;
		a=a*a;
		b/=2;
	}
	return res;
}
struct SGT{
	struct node{
		Mat Sa,Sab,K;
	}t[400005];
	void pushup(int p){
		t[p].Sab=t[p*2].Sab+t[p*2+1].Sab;
	}
	void mul(int p,Mat X){
		t[p].K=t[p].K+X;
		t[p].Sab=t[p].Sab+(t[p].Sa*X);
	}
	void pushdown(int p){
		if(t[p].K.ck()){
			mul(p*2,t[p].K);
			mul(p*2+1,t[p].K);
			t[p].K.set0();
		}
	}
	void build(int p,int l,int r,Mat A[]){
		if(l==r){
			t[p].Sa=A[l];
			t[p].Sab=M*invM[dep[l]]; 
			return;
		}
		int mid=(l+r)/2;
		build(p*2,l,mid,A);
		build(p*2+1,mid+1,r,A);
		t[p].Sa=t[p*2].Sa+t[p*2+1].Sa;
		pushup(p);
	}
	void modify(int p,int l,int r,int L,int R,Mat X){
		if(L<=l&&r<=R){
			mul(p,X);
			return;
		}
		pushdown(p);
		int mid=(l+r)/2;
		if(mid>=L) modify(p*2,l,mid,L,R,X);
		if(mid<R) modify(p*2+1,mid+1,r,L,R,X);
		pushup(p);
	}
	void query(int p,int l,int r,int L,int R,int &res){
		if(L<=l&&r<=R){
			upd(res,t[p].Sab.a11);
			return;
		}
		pushdown(p);
		int mid=(l+r)/2;
		if(mid>=L) query(p*2,l,mid,L,R,res);
		if(mid<R) query(p*2+1,mid+1,r,L,R,res);
	}
	void modify(int l,int r,ll k){
		if(k<=0){
			Mat T=invM[-k];
			modify(1,1,n,l,r,T);
		}else{
			Mat T=ksm(M,k);
//			cout<<k<<"\n";
//			cout<<T.a00<<" "<<T.a01<<"\n"<<T.a10<<" "<<T.a11<<"\n"; 
			modify(1,1,n,l,r,T);
		}
		
	}
	int query(int l,int r){
//		cout<<l<<" "<<r<<"\n"; 
		int res=0;
		query(1,1,n,l,r,res);
//		cout<<res<<"\n";
		return res;
	}
}sgt;
void dfs1(int u,int fa){
	if(fa) A[u]=A[fa]*M;
	else A[u]=M;
	dep[u]=dep[fa]+1;
	sz[u]=1;
	f[u]=fa;
	for(int v:V[u]){
		if(v==fa) continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(!son[u]||sz[v]>sz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int tp){
	dfn[u]=++tot;
	_A[tot]=A[u];
	top[u]=tp;
	if(son[u]){
		dfs2(son[u],tp);
	}
	for(int v:V[u]){
		if(v!=f[u]&&v!=son[u]) dfs2(v,v);
	}
	out[u]=tot;
}
int Qry(int u,int v){
	int res=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		upd(res,sgt.query(dfn[top[u]],dfn[u]));
		u=f[top[u]];
	}
	upd(res,sgt.query(min(dfn[u],dfn[v]),
					  max(dfn[u],dfn[v])));
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		V[u].push_back(v);
		V[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,1);
	sgt.build(1,1,n,_A);
	invM[0]={1,0,0,1};
	for(int i=1;i<=n;i++){
		invM[i]={invM[i-1].a01,invM[i-1].a11,
				 invM[i-1].a11,(invM[i-1].a01-invM[i-1].a11+mod)%mod};
	}
	for(int i=1;i<=m;i++){
		char op;
		cin>>op;
		if(op=='U'){
			int x;
			ll k;
			cin>>x>>k;
			sgt.modify(dfn[x],out[x],k-dep[x]+1);
		}else{
			int u,v;
			cin>>u>>v; 
			cout<<Qry(u,v)<<"\n";
		}
	}
} 
```

---

## 作者：hzlqwq (赞：9)

由于涉及到斐波那契数列的下标加，我们需要用到一个很重要的公式：$F_{n+m}=F_{n+1}F_{m}+F_{n}F_{m-1}$。

简证：
$$
\begin{array}{l}
\because F_n=F_{n-1}+F_{n-2} \\[1mm]
\therefore
\begin{pmatrix}F_1\\
F_0
\end{pmatrix}
\begin{bmatrix}
1 & 1\\
1 & 0
\end{bmatrix}
^n=
\begin{pmatrix}
F_{n+1} \\
F_n
\end{pmatrix}\\[3mm]
\therefore
\begin{bmatrix}
1 & 1\\
1 & 0
\end{bmatrix}
^n=
\begin{pmatrix}
F_{n+1} & F_n \\
F_n & F_{n-1}
\end{pmatrix}\\[3mm]
\because
\begin{bmatrix}
1 & 1\\
1 & 0
\end{bmatrix}
^{n+m}=
\begin{bmatrix}
1 & 1\\
1 & 0
\end{bmatrix}^n
\begin{bmatrix}
1 & 1\\
1 & 0
\end{bmatrix}
^m\\[3mm]
\therefore 
\begin{pmatrix}
F_{n+m+1} & F_{n+m}\\
F_{n+m} & F_{n+m-1}
\end{pmatrix}=
\begin{pmatrix}
F_{n+1} & F_{n}\\
F_{n} & F_{n-1}
\end{pmatrix}
\begin{pmatrix}
F_{m+1} & F_{m}\\
F_{m} & F_{m-1}
\end{pmatrix}=
\begin{pmatrix}
F_{n+1}F_{m+1}+F_nF_m & F_{n+1}F_m+F_{n}F_{m-1}\\
F_{n}F_{m+1}+F_{n-1}F_{m} & F_nF_m+F_{n-1}F_{m-1}
\end{pmatrix}\\[3.mm]
\therefore F_{n+m}=F_{n+1}F_{m}+F_{n}F_{m-1}
\end{array}
$$

注意到有子树修改和路径查询，我们采用线段树 + 树链剖分维护，但维护什么信息需要分析：

考虑进行一次 $x,k$ 的修改对 $x$ 子树内的节点 $u$ 的影响：

$$
\large
\begin{aligned}
ans_u+&=F_{dis(x,u)+k}\\
&=F_{dep_u-dep_x+k}\\
&=F_{dep_u+1}F_{k-dep_x}+F_{dep_u}F_{k-dep_x-1}
\end{aligned}
$$

因为每个点的深度是确定的，$F_{dep_u+1}$ 和 $F_{dep_u}$ 也是确定的，而每次询问的 $F_{k-dep_x}$ 和 $F_{k-dep_x-1}$ 也是确定的，所以**每次修改相当于给每个点分别加上两个固定值的固定倍**（**一般的线段树相当于加上区间长的固定倍**），于是我们在每个节点中记录 $\sum F_{dep_u+1}$，$\sum F_{dep_u}$，$\sum F_{dep_u+1}$ 的系数懒标记，$\sum F_{dep_u}$ 的系数懒标记与 $\sum ans_u$，再像平常一样维护懒标记线段树即可。

因为 $k$ 非常大，所以斐波那契数列第 $k$ 项无法预处理，需要每次单独计算，此处采用矩阵快速幂实现，时间复杂度 $O(\log k)$。

总时间复杂度 $O(n\log n+m\log^2 n+m\log k)$。

强烈建议仔细看代码！虽然长但细节多且可读性高！看了就懂实现了！

```cpp
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 10, mod = 1e9 + 7;

int n, m;
vector<int> e[N];
int ans[2][2], trans[2][2], tmp[2][2];
int fa[N], dep[N], sz[N], son[N], top[N], dfn[N], id[N];

inline void speedup()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

inline void dfs1(int u, int father)
{
    fa[u] = father, dep[u] = dep[father] + 1, sz[u] = 1;
    for (auto j : e[u])
    {
        if (j == father)
            continue;
        dfs1(j, u);
        sz[u] += sz[j];
        if (sz[j] > sz[son[u]])
            son[u] = j;
    }
}

inline void dfs2(int u, int t)
{
    top[u] = t, dfn[++dfn[0]] = u, id[u] = dfn[0];
    if (!son[u])
        return;
    dfs2(son[u], t);
    for (auto j : e[u])
    {
        if (j == fa[u] || j == son[u])
            continue;
        dfs2(j, j);
    }
}

inline int fib(long long x)
{
    int sign = x >= 0 ? 1 : (x = -x, x % 2 ? 1 : -1);
    memset(ans, 0, sizeof ans), ans[0][0] = ans[1][1] = 1;
    memset(trans, 0, sizeof trans), trans[0][0] = trans[0][1] = trans[1][0] = 1;
    while (x)
    {
        if (x & 1)
        {
            memset(tmp, 0, sizeof tmp);
            for (int k = 0; k <= 1; k++)
                for (int i = 0; i <= 1; i++)
                    for (int j = 0; j <= 1; j++)
                        tmp[i][j] = (tmp[i][j] + (long long)ans[i][k] * trans[k][j]) % mod;
            memcpy(ans, tmp, sizeof ans);
        }
        tmp[0][0] = tmp[0][1] = tmp[1][0] = tmp[1][1] = 0;
        for (int k = 0; k <= 1; k++)
            for (int i = 0; i <= 1; i++)
                for (int j = 0; j <= 1; j++)
                    tmp[i][j] = (tmp[i][j] + (long long)trans[i][k] * trans[k][j]) % mod;
        memcpy(trans, tmp, sizeof trans);
        x >>= 1;
    }
    return sign * ans[0][1];
}

struct
{
    long long l, r, du, du1, kdx, kdx1, sum; // 前两个是常驻值，后两个是懒标记
} tr[N << 2];

inline void pushup(int u)
{
    tr[u].du = (tr[u << 1].du + tr[u << 1 | 1].du) % mod;
    tr[u].du1 = (tr[u << 1].du1 + tr[u << 1 | 1].du1) % mod;
    tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum) % mod;
}

inline void pushdown(int u)
{
    if (!tr[u].kdx && !tr[u].kdx1)
        return;
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    left.sum = (left.sum + left.du1 * root.kdx + left.du * root.kdx1) % mod;
    right.sum = (right.sum + right.du1 * root.kdx + right.du * root.kdx1) % mod;
    left.kdx = (left.kdx + root.kdx) % mod;
    right.kdx = (right.kdx + root.kdx) % mod;
    left.kdx1 = (left.kdx1 + root.kdx1) % mod;
    right.kdx1 = (right.kdx1 + root.kdx1) % mod;
    root.kdx = root.kdx1 = 0;
}

inline void build(int u, int l, int r)
{
    if (l == r)
    {
        tr[u] = {l, r, fib(dep[dfn[l]]), fib(dep[dfn[l]] + 1), 0, 0, 0};
        return;
    }
    tr[u].l = l, tr[u].r = r;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

inline void modify(int u, int l, int r, int kdx, int kdx1)
{
    if (tr[u].l >= l && tr[u].r <= r)
    {
        tr[u].sum = (tr[u].sum + tr[u].du1 * kdx + tr[u].du * kdx1) % mod;
        tr[u].kdx = (tr[u].kdx + kdx) % mod;
        tr[u].kdx1 = (tr[u].kdx1 + kdx1) % mod;
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid)
        modify(u << 1, l, r, kdx, kdx1);
    if (r > mid)
        modify(u << 1 | 1, l, r, kdx, kdx1);
    pushup(u);
}

inline int query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r)
        return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1, res = 0;
    if (l <= mid)
        res = query(u << 1, l, r);
    if (r > mid)
        res = (res + query(u << 1 | 1, l, r)) % mod;
    return res;
}

inline int query_path(int x, int y)
{
    int res = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] > dep[top[y]])
            swap(x, y);
        res = ((long long)res + query(1, id[top[y]], id[y])) % mod;
        y = fa[top[y]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    res = ((long long)res + query(1, id[x], id[y])) % mod;
    return res;
}

int main()
{
    speedup();
    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y), e[y].push_back(x);
    }
    dfs1(1, 0), dfs2(1, 1);
    build(1, 1, n);
    while (m--)
    {
        char op;
        long long a, b;
        cin >> op >> a >> b;
        if (op == 'U')
            modify(1, id[a], id[a] + sz[a] - 1, fib(b - dep[a]), fib(b - dep[a] - 1));
        else
            cout << query_path(a, b) << "\n";
    }
    return 0;
}
```

> [一发入魂最优解！](https://www.luogu.com.cn/record/118056361)


---

## 作者：Jasper08 (赞：5)

首先我们有一个重要的式子：
$$
f_{n+m}=f_{n}f_{m+1}+f_{n-1}f_m
$$

> 证明：
>
> $m=0$ 时，显然有 $f_nf_1+f_{n-1}f_0=f_n$。
>
> 假设 $\forall m\in [0,k],m\in \mathbb{N}$ 结论成立，则 $m=k+1$ 时，有：
$$
 \begin{aligned}
 f_{n}f_{k+2}+f_{n-1}f_{k+1} &= f_nf_{k+1}+f_{n}f_{k}+f_{n-1}f_{k+1} \\
 &= (f_{n-1}f_{k}+f_{n}f_{k+1})+(f_{n-2}f_{k}+f_{n-1}f_{k+1}) \\
 &= f_{n+k}+f_{n+k-1} \\
 &= f_{n+k+1}
 \end{aligned}
$$

假设我们要计算 $u$ 的子树内的一个节点 $v$ 的增加量，则有：
$$
f_{d+k}=f_{dep_v+k-dep_u}=f_{dep_v}f_{k-dep_u+1}+f_{dep_v-1}f_{k-dep_u}
$$
注意到 $k-dep_u$ 可能小于 $0$，我们有 $f_{-n}=(-1)^{n-1}f_n$，可以证明其仍然满足上面的式子（因为递推式 $f_n=f_{n-1}+f_{n-2}$ 仍然成立）。

由于 $f_{dep_v},f_{dep_{v-1}}$ 均为常数，我们可以线段树维护两个常数 $\sum f_{dep_v},\sum{f_{dep_v-1}}$，两个增加量 $\sum f_{k-dep_u+1}, \sum f_{k-dep_u}$ 以及节点的增加量之和。由于 $k\le 10^{18}$，需要用矩阵快速幂计算 $f_i$。

树链剖分后用线段树维护即可。时间复杂度 $O(n\log ^2 n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define int long long

typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 2e5+10, P = 1e9+7;

int n, m;
vector<int> e[N];

struct Matrix {
    int num[4][4];
    Matrix() {
        memset(num, 0, sizeof num);
    }
};

Matrix operator *(const Matrix &a, const Matrix &b) {
    Matrix ans;
    for (int k = 1; k <= 2; ++k) {
        for (int i = 1; i <= 2; ++i) 
            for (int j = 1; j <= 2; ++j)
                ans.num[i][j] = (ans.num[i][j] + (ll)a.num[i][k] * b.num[k][j]) % P;  
    }
    return ans;
}

Matrix power(Matrix &a, int b) {
    Matrix ans; for (int i = 1; i <= 2; ++i) ans.num[i][i] = 1;
    while (b > 0) {
        if (b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}

int calc(ll k) {
    int f = 1;
    if (k < 0) k = -k, f = (k % 2) ? 1 : -1;
    if (k == 0) return 0;
    Matrix a, trans; 
    a.num[1][1] = a.num[1][2] = 1; trans.num[1][1] = trans.num[1][2] = trans.num[2][1] = 1;
    Matrix ans = a;
    if (k >= 2) ans = ans * power(trans, k-2);
    return (f*ans.num[1][1]%P+P)%P;
}

int idx, id[N], dfn[N];
int dep[N], siz[N], top[N], son[N], f[N];

void get_son(int u, int fa) {
    siz[u] = 1, dep[u] = dep[fa]+1, f[u] = fa;
    for (auto v : e[u]) {
        if (v == fa) continue;
        get_son(v, u), siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void get_top(int u, int t) {
    top[u] = t, id[u] = ++ idx, dfn[idx] = u;
    if (son[u]) get_top(son[u], t);
    for (auto v : e[u]) {
        if (v == f[u] || v == son[u]) continue;
        get_top(v, v);
    }
}

struct Node {
    int l, r, sum; pii val, tag;
} seg[N<<2];

void pushup(int u) {
    seg[u].val.first = (seg[u<<1].val.first + seg[u<<1|1].val.first) % P;
    seg[u].val.second = (seg[u<<1].val.second + seg[u<<1|1].val.second) % P;
    seg[u].sum = (seg[u<<1].sum + seg[u<<1|1].sum) % P;
}

void pushdown(Node &u, Node &now) {
    now.sum = (now.sum + (ll)now.val.first*u.tag.first%P + (ll)now.val.second*u.tag.second%P) % P;
    now.tag.first = ((ll)now.tag.first + u.tag.first) % P;
    now.tag.second = ((ll)now.tag.second + u.tag.second) % P;
}

void pushdown(int u) {
    pushdown(seg[u], seg[u<<1]), pushdown(seg[u], seg[u<<1|1]);
    seg[u].tag = make_pair(0, 0);
}

void build(int u, int l, int r) {
    seg[u].l = l, seg[u].r = r, seg[u].tag = make_pair(0, 0);
    if (l == r) seg[u].val.first = calc(dep[dfn[l]]), seg[u].val.second = calc(dep[dfn[l]]-1);
    else {
        int mid = l + r >> 1;
        build(u<<1, l, mid), build(u<<1|1, mid+1, r);
        pushup(u);
    }
}

int query(int u, int l, int r) {
    if (seg[u].l >= l && seg[u].r <= r) return seg[u].sum;
    pushdown(u);
    int mid = seg[u].l + seg[u].r >> 1, ans = 0;
    if (l <= mid) ans = ((ll)ans + query(u<<1, l, r)) % P;
    if (r > mid) ans = ((ll)ans + query(u<<1|1, l, r)) % P;
    return ans;
}

void modify(int u, int l, int r, ll val1, ll val2) {
    if (seg[u].l >= l && seg[u].r <= r) {
        Node tmp; tmp.tag = make_pair(val1, val2);
        pushdown(tmp, seg[u]);
        return ;
    }
    pushdown(u);
    int mid = seg[u].l + seg[u].r >> 1;
    if (l <= mid) modify(u<<1, l, r, val1, val2);
    if (r > mid) modify(u<<1|1, l, r, val1, val2);
    pushup(u); 
    return ;
}

int ask_path(int u, int v) {
    int sum = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        sum = ((ll)sum+query(1, id[top[u]], id[u])) % P;
        u = f[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    sum = ((ll)sum + query(1, id[u], id[v])) % P;
    return sum;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        e[u].push_back(v), e[v].push_back(u);
    }
    get_son(1, 1), get_top(1, 1);
    build(1, 1, n);
    
    char op; int x; ll y;
    for (int i = 1; i <= m; ++i) {
        cin >> op >> x >> y;
        if (op == 'U') modify(1, id[x], id[x]+siz[x]-1, calc(y-dep[x]+1), calc(y-dep[x]));
        else cout << ask_path(x, y) << '\n';
    }
    return 0;
}
```

---

## 作者：lzyqwq (赞：5)

**[更好的阅读体验](https://www.cnblogs.com/MnZnOIerLzy/articles/17450300.html)**

~~神仙题 & 毒瘤题。~~

应该是最为详细的一篇题解了。

**[洛谷 P5138](https://www.luogu.com.cn/problem/P5138 "洛谷 P5138")**

>- 定义 $d_u$ 为点 $u$ 的深度，$f_i$ 为斐波那契数列第 $i$ 项，满足 $f_0=0,,f_1=1,f_i=f_{i-2}+f_{i-1}(i>2)$（同时定义 $i<0$ 时 $f_{i}=f_{i+2}-f_{i+1}$）。
>
> - 给出以 $1$ 为根的 $N$ 个点的树，每个点初始权值为 $0$。$M$ 次操作，两种类型：
>
>     - $\texttt{U }x\texttt{ }k$，将以 $x$ 为根子树内的所有点 $u$，将其权值加上 $f_{d_u-d_x+k}$。
>
>     - $\texttt{Q }x\texttt{ }y$，查询 $x,y$ 路径上点的权值和，模 $10^9+7$。
>
> - $N,M\le 10^5$，$k\le 10^{18}$。

需要用到的前置知识：

**Ⅰ - $i<0$ 时，$f_{i}=(-1)^{i-1}\times f_{-i}$**

粗略地证明：

考虑归纳。

- 易证当 $i=-1$，$i=-2$ 时成立。

- 假设在 $k\le i\le-2$ 时成立，则当 $i=k-1$ 时：

    - 若 $k$ 为奇数，则 $k+1$，$k-1$ 均为偶数，$k-2$ 为奇数。有：
	
      $$f_{k-1}=f_{k+1}-f_{k}=-f_{-k-1}-f_{-k}=-(f_{-k-1}+f_{-k})=-f_{-k+1}=(-1)^{k-2}\times f_{-(k-1)}$$
	
	  成立。
	
	- 若 $k$ 为偶数，则 $k+1$，$k-1$ 均为奇数，$k-2$ 为偶数。有：
	
	  $$f_{k-1}=f_{k+1}-f_{k}=f_{-k-1}-(-f_{-k})=f_{-k-1}+f_{-k}=f_{-k+1}=(-1)^{k-2}\times f_{-(k-1)}$$
	
	  成立。
	
证毕。

**Ⅱ - $f_{m+n}=f_{m-1}\times f_n+f_m\times f_{n+1}$**

粗略地证明：

首先 $f_{m-1}\times f_n+f_m\times f_{n+1}=f_{n-1}\times f_m+f_n\times f_{m+1}$。

考虑做差：

$$\begin{aligned}f_{m-1}\times f_n+f_m\times f_{n+1}-(f_{n-1}\times f_m+f_n\times f_{m+1})&=f_m\times(f_{n+1}-f_{n-1})-f_n\times(f_{m+1}-f_{m-1})\\&=f_m\times f_n-f_n\times f_m\\&=0\end{aligned}$$

所以上面那个式子是成立的。

先钦定 $m,n$ 为自然数。同样考虑归纳。

- 易证 $m=0$，$n=0$ 和 $m,n\in[0,1]$ 时均成立。

- 假设在 $m,n\in[1,k]$ 时成立，则当 $m,n\in[1,k+1]$ 时，在原值域上新增了三种情况：

    - 当 $m=k+1,n\in[1,k]$ 时：
	
	  $$\begin{aligned}f_{m+n}&=f_{m+n-2}+f_{m+n-1}\\&=f_{m-1+n-1}+f_{m-1+n}\\&=f_{m-2}\times f_{n-1}+f_{m-1}\times f_n+f_{m-2}\times f_n+f_{m-1}\times f_{n+1}\\&=f_{m-2}\times (f_{n+1}-f_{n})+f_{m-1}\times f_n+f_{m-2}\times f_n+f_{m-1}\times f_{n+1}\\&=f_{m-2}\times f_{n+1}-f_{m-2}\times f_n+f_{m-1}\times f_n+f_{m-2}\times f_n+f_{m-1}\times f_{n+1}\\&=f_{m-1}\times f_n+(f_{m-2}+f_{m-1})\times f_{n+1}\\&=f_{m-1}\times f_n+f_m\times f_{n+1}\end{aligned}$$
	
	  成立。
	
	- 当 $m\in[1,k],n=k+1$ 时（其实本质相同，但是为了完整还是写了）：
	
	  $$\begin{aligned}f_{m+n}&=f_{m+n-2}+f_{m+n-1}\\&=f_{m-1+n-1}+f_{m+n-1}\\&=f_{m-2}\times f_{n-1}+f_{m-1}\times f_n+f_{m-1}\times f_{n-1}+f_{m}\times f_{n}\\&=f_{m-2}\times f_{n-1}+f_{m-1}\times f_{n-1}+f_{m-1}\times f_n+f_{m}\times f_{n}\\&=f_m\times f_{n-1}+f_{m+1}\times f_n\\&=f_{m-1}\times f_n+f_m\times f_{n+1}\end{aligned}$$
	
	  成立。
	
	- 当 $m=n=k+1$ 时：
	
	  $$\begin{aligned}f_{m+n}&=f_{m+n-2}+f_{m+n-1}\\&=f_{m+n-2}+f_{m+n-3}+f_{m+n-2}\\&=f_{m-1+n-1}+f_{m-1+n-2}+f_{m-1+n-1}\\&=f_{m-2}\times f_{n-1}+f_{m-1}\times f_n+f_{m-2}\times f_{n-2}+f_{m-1} \times f_{n-1}+ f_{m-2}\times f_{n-1}+f_{m-1}\times f_n\\&=f_{m-1}\times f_n+f_{m-2}\times(f_{n-1}+f_{n-2}+f_{n-1})+f_{m-1}\times(f_n+f_{n-1})\\&=f_{m-1}\times f_n+f_{m-2}\times f_{n+1}+f_{m-1}\times f_{n+1}\\&=f_{m-1}\times f_n+f_m\times f_{n+1}\end{aligned}$$
	
	  成立。
	
因此当 $m,n\in[0,\infty)$ 时成立。
	
接下来考虑负数的情况：

假设 $m,n\in[k,\infty)$ 时成立，则当 $m,n\in[k-1,\infty)$ 时，同样新增三种情况：

- 当 $m=k-1,n\in[k,\infty)$ 时：

  $$\begin{aligned}f_{m+n}&=f_{m+n+2}-f_{m+n+1}\\&=f_{m+1+n+1}-f_{m+1+n}\\&=f_m\times f_{n+1}+f_{m+1}\times f_{n+2}-f_{m}\times f_{n}-f_{m+1}\times f_{n+1}\\&=f_m\times(f_{n+1}-f_n)+f_{m+1}\times(f_{n+2}-f_{n+1})\\&=f_{m}\times f_{n-1}+f_{m+1}\times f_n\\&=f_{m-1}\times f_n+f_m\times f_{n+1}\end{aligned}$$
  
  成立。
  
- 当 $m\in[k,\infty),n=k-1$ 时：

  $$\begin{aligned}f_{m+n}&=f_{m+n+2}-f_{m+n+1}\\&=f_{m+1+n+1}-f_{m+n+1}\\&=f_{m}\times f_{n+1}+f_{m+1}\times f_{n+2}-f_{m-1}\times f_{n+1}-f_m\times f_{n+2}\\&=f_{n+1}\times(f_m-f_{m-1})+f_{n+2}\times (f_{m+1}-f_m)\\&=f_{m-2}\times f_{n+1}+f_{m-1}\times f_{n+2}\\&=f_{m-2}\times f_{n+1}+f_{m-1}\times (f_n+f_{n+1})\\&=f_{m-2}\times f_{n+1}+f_{m-1}\times f_n + f_{m-1}\times f_{n+1}\\&=f_{m-1}\times f_n+(f_{m-2}+f_{m-1})\times f_{n+1}\\&=f_{m-1}\times f_n+f_m\times f_{n+1}\end{aligned}$$
  
  成立。
  
- 当 $m=n=k-1$ 时：

  $$\begin{aligned}f_{m+n}&=f_{m+n+2}-f_{m+n+1}\\&=f_{m+n+2}-(f_{m+n+3}-f_{m+n+2})\\&=f_{m+n+2}-f_{m+n+3}+f_{m+n+2}\\&=f_{m+1+n+1}-f_{m+2+n+1}+f_{m+1+n+1}\\&=f_{m}\times f_{n+1}+f_{m+1}\times f_{n+2} - f_{m+1}\times f_{n+1}-f_{m+2}\times f_{n+2} +f_{m}\times f_{n+1}+f_{m+1}\times f_{n+2}\\&=f_m\times f_{n+1}+f_{m}\times f_{n+1}+f_{m+1}\times (f_{n+2}-f_{n+1})-(f_{m+2}-f_{m+1})\times f_{n+2}\\&=f_{m}\times f_{n+1}+f_{m}\times f_{n+1}+f_{m+1}\times f_n-f_m\times f_{n+2}\\&=f_{m}\times f_{n+1}-f_m\times(f_{n+2}-f_{n+1}) +f_{m+1}\times f_n\\&=f_m\times f_{n+1}-f_m\times f_n+f_{m+1}\times f_n\\&=(f_{m+1}-f_m)\times f_n+f_m\times f_{n+1}\\&=f_{m-1}\times f_n+f_m\times f_{n+1}\end{aligned}$$
  
  成立。
  
因此当 $m,n\in(-\infty,\infty)$ 时成立，证毕。


有了这两个结论以后，就可以开始做这道题了。

求斐波那契数列想到矩阵快速幂。路径查询问题先想树剖。将以 $x$ 为根子树内的点 $u$ 权值加上 $f_{d_u-d_x+k}$，相当于加上 $f_{d_{u}-1}\times f_{k-d_x}+f_{d_u}\times f_{k-d_x+1}$。将 $f_{d_{u}-1}$ 和 $f_{d_u}$ 分开维护（分别记为 $a,b$），发现系数是常数，可做。对树剖后的序列建线段树，修改操作就是将子树在序列上对应的区间的两个系数区间加，维护区间权值和 $sum$，$a$ 值的和 $v_a$，$b$ 值的和 $v_b$，$a$ 值的系数懒标记 $tg_a$，$b$ 值的系数懒标记 $tg_b$。

记 $ls$ 为左子，$rs$ 为右子，$x$ 为当前节点（和输入的不同）。下传就是：

```cpp
void down(int x){
	if(tga[x]){//需要下传。
		sum[ls]=(sum[ls]+va[ls]*tga[x]%M)%M;//答案加上 va[ls]*tga[x]，注意这里要拿 a 值的和来乘，因为 tga[x] 是当前区间的系数，区间内每一项都要乘上这么多，根据乘法分配律就是给和乘上这么多。下面同理。
		tga[ls]=(tga[ls]+tga[x])%M;
		sum[rs]=(sum[rs]+va[rs]*tga[x]%M)%M;
		tga[rs]=(tga[rs]+tga[x])%M;
		tga[x]=0;
	}
	if(tgb[x]){
		sum[ls]=(sum[ls]+vb[ls]*tgb[x]%M)%M;
		tgb[ls]=(tgb[ls]+tgb[x])%M;
		sum[rs]=(sum[rs]+vb[rs]*tgb[x]%M)%M;
		tgb[rs]=(tgb[rs]+tgb[x])%M;
		tgb[x]=0;
	}
}
```

查询就是跳链查询。

时间复杂度为 $\mathcal{O}(M\log^2N)$，空间复杂度为 $\mathcal{O}(N)$。

**[评测记录](https://www.luogu.com.cn/record/109076181 "评测记录")**

```cpp
#include<bits/stdc++.h>
#define ls x<<1
#define rs x<<1|1
using namespace std;
typedef long long ll;
const ll M=1e9+7;
const int N=1e5+5;
char op;
int n,m,f[N],t[N],h[N],d[N],sz[N],dfn[N],id,st[N],ed[N];
ll tga[N<<2],tgb[N<<2],sum[N<<2],va[N<<2],vb[N<<2];
vector<int>g[N];
struct matrix{
	int r,c;
	ll a[3][3];
	matrix(){
		memset(a,r=c=0,sizeof a);
	}
}A,B,C;
matrix operator*(matrix u,matrix v){
	matrix ret;
	ret.r=u.r;
	ret.c=v.c;
	for(int i=1;i<=u.r;++i){
		for(int j=1;j<=v.c;++j){
			for(int k=1;k<=u.c;++k){
				ret.a[i][j]=(ret.a[i][j]+u.a[i][k]*v.a[k][j]%M)%M;
			}
		}
	}
	return ret;
}
matrix qpow(matrix x,ll y){
	matrix ret=C;
	while(y){
		if(y&1ll){
			ret=ret*x;
		}
		x=x*x;
		y>>=1ll;
	}
	return ret;
}
ll fib(ll/*WA 30pts 警钟长鸣不开 long long 见祖宗*/ x){
	if(x>=0){
		return(A*qpow(B,x)).a[1][1];
	}else{
		ll ret=(A*qpow(B,-x)).a[1][1];
		return(-x)&1ll?ret:M-ret;
	}
}
void down(int x){
	if(tga[x]){
		sum[ls]=(sum[ls]+va[ls]*tga[x]%M)%M;
		tga[ls]=(tga[ls]+tga[x])%M;
		sum[rs]=(sum[rs]+va[rs]*tga[x]%M)%M;
		tga[rs]=(tga[rs]+tga[x])%M;
		tga[x]=0;
	}
	if(tgb[x]){
		sum[ls]=(sum[ls]+vb[ls]*tgb[x]%M)%M;
		tgb[ls]=(tgb[ls]+tgb[x])%M;
		sum[rs]=(sum[rs]+vb[rs]*tgb[x]%M)%M;
		tgb[rs]=(tgb[rs]+tgb[x])%M;
		tgb[x]=0;
	}
}
void insert(int x,int l,int r,int k,ll a,ll b){//插入 a，b 两个值。
	if(l^r){
		int mid=(l+r)>>1;
		if(k<=mid){
			insert(ls,l,mid,k,a,b);
		}else{
			insert(rs,mid+1,r,k,a,b);
		}
		va[x]=(va[ls]+va[rs])%M;
		vb[x]=(vb[ls]+vb[rs])%M;
	}else{
		va[x]=a;
		vb[x]=b;
	}
}
void modify(int x,int l,int r,int ql,int qr,ll a,ll b){
	if(ql<=l&&r<=qr){
		if(a){
			sum[x]=(sum[x]+va[x]*a%M)%M;
			tga[x]=(tga[x]+a)%M;
		}
		if(b){
			sum[x]=(sum[x]+vb[x]*b%M)%M;
			tgb[x]=(tgb[x]+b)%M;
		}
	}else{
		down(x);
		int mid=(l+r)>>1;
		if(ql<=mid){
			modify(ls,l,mid,ql,qr,a,b);
		}
		if(qr>mid){
			modify(rs,mid+1,r,ql,qr,a,b);
		}
		sum[x]=(sum[ls]+sum[rs])%M;
	}
}
ll query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr){
		return sum[x];
	}
	down(x);
	int mid=(l+r)>>1;
	ll ret=0;
	if(ql<=mid){
		ret=(ret+query(ls,l,mid,ql,qr))%M;
	}
	if(qr>mid){
		ret=(ret+query(rs,mid+1,r,ql,qr))%M;
	}
	return ret;
}
ll pathquery(int x,int y){
	ll ret=0;
	while(t[x]^t[y]){
		if(d[t[x]]<d[t[y]]){
			swap(x,y);
		}
		ret=(ret+query(1,1,n,dfn[t[x]],dfn[x]))%M;
		x=f[t[x]];
	}
	if(d[x]>d[y]){
		swap(x,y);
	}
	return (ret+query(1,1,n,dfn[x],dfn[y]))%M;
}
void dfs1(int u,int fa){
	sz[u]=1;
	for(int v:g[u]){
		if(v^fa){
			d[v]=d[u]+1;
			dfs1(v,f[v]=u);
			sz[u]+=sz[v];
		}
	}
}
void dfs2(int u,int fa){
	for(int v:g[u]){
		if(v^fa){
			if((sz[v]<<1)>sz[u]){
				t[h[u]=v]=t[u];
			}else{
				t[v]=v;
			}
			dfs2(v,u);
		}
	}
}
void dfs3(int u,int fa){
	insert(1,1,n,st[u]=dfn[u]=++id,fib(1ll*d[u]-1ll),fib(1ll*d[u]));
	if(h[u]){
		dfs3(h[u],u);
	}
	for(int v:g[u]){
		if((v^fa)&&(v^h[u])){
			dfs3(v,u);
		}
	}
	ed[u]=id;
}
int main(){
	A.a[A.r=1][A.c=2]=B.a[1][2]=B.a[2][1]=B.a[B.r=2][B.c=2]=C.a[1][1]=C.a[C.r=2][C.c=2]=1ll;
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i^n;++i){
		scanf("%d%d",&u,&v);
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	dfs1(1,0);
	dfs2(t[1]=1,0);
	dfs3(1,0);
	for(int i=1,x;i<=m;++i){
		ll y;
		scanf(" %c%d%lld",&op,&x,&y);
		if(op^'Q'){
			modify(1,1,n,st[x],ed[x],fib(y-1ll*d[x]),fib(y-1ll*d[x]+1ll));
		}else{
			printf("%lld\n",pathquery(x,(int)y));
		}
	}
}
```

---

## 作者：Rorschachindark (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P5138)
# 题目大意
给出一个 $n$ 个点的树，有 $m$ 次操作，每次操作为以下两种操作之一：

- 给出 $x,k$，将 $x$ 子树内的节点 $u$ 权值增加 $f_{\text{dist}(x,u)+k}$

- 给出 $u,v$，查询 $u\to v$ 这条链上所有点的权值之和。

答案对 $10^9+7$ 取模。$f_{n}$ 表示斐波拉契数列第 $n$ 项。

$n,m\le 10^5$
# 思路
老实说这个题目不管是从思维难度还是代码实现难度来说都不算很难吧?

首先有一个众所周知的式子：

$$f_{n+m}=f_{n-1}\times f_m+f_n\times f_{m+1}$$

具体证明直接暴力把 $f_{n+m}$ 用 $f_{n}=f_{n-1}+f_{n-2}$ 展开即可。

然后我们发现对于点 $u$ 而言增加的值就可以写成：

$$f_{\text{dep}(u)-1}\times f_{k-\text{dep}(x)}+f_{\text{dep}(u)}\times f_{k-\text{dep}+1}$$

然后你发现后面对于每一次操作来说是个定值，前面一个对于每一个点来说是个定值。所以我们直接树链剖分上就好了，维护 $\sum f_{\text{dep}(u)}$ 以及 $\sum_{\text{dep}(u)-1}$ 、答案以及这两个系数的懒标记。

在求 $f_{n}$ 的时候不需要矩阵快速幂，直接扩域即可，可以证明 $\sqrt 5$ 的系数最后一定为 $0$。

时间复杂度 $\Theta(n\log^2n)$。
# $\texttt{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define mod 1000000007
#define inv2 (mod+1)/2
#define inv5 400000003
#define ll long long
#define MAXN 100005

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

int mul (int a,int b){return 1ll * a * b % mod;}
int dec (int a,int b){return a >= b ? a - b : a + mod - b;}
int add (int a,int b){return a + b >= mod ? a + b - mod : a + b;}
int qkpow (int a,int b){
	int res = 1;for (;b;b >>= 1,a = mul (a,a)) if (b & 1) res = mul (res,a);
	return res;
}

struct Sqrx{//表示asqrt{5}+b 
	int a,b;
	Sqrx(){}
	Sqrx(int _a,int _b){a = _a,b = _b;}
	Sqrx operator + (const int &p)const{return Sqrx(a,add (b,p));}
	Sqrx operator * (const int &p)const{return Sqrx(mul (a,p),mul (b,p));}
	Sqrx operator - (const Sqrx &p)const{return Sqrx(dec (a,p.a),dec (b,p.b));}
	Sqrx operator * (const Sqrx &p)const{return Sqrx(add (mul (a,p.b),mul (p.a,b)),add (mul (5,mul (a,p.a)),mul (b,p.b)));}
	template <typename T> Sqrx operator ^ (T b){
		Sqrx res (0,1),a = *this;
		for (;b;b >>= 1,a = a * a) if (b & 1) res = res * a;
		return res; 
	}
};

template <typename T> int Fib (T n){
	if (n < 0) return (-n) & 1 ? Fib (-n) : mod - Fib(-n);
	Sqrx res = (Sqrx(inv2,inv2) ^ n) - (Sqrx(mod - inv2,inv2) ^ n);
	return (res * Sqrx(1,0) * inv5).b;
}

int n,m,ind;
int dfn[MAXN],tur[MAXN],siz[MAXN],son[MAXN],dep[MAXN],par[MAXN],top[MAXN]; 

vector <int> G[MAXN];

void dfs (int u,int fa){
	par[u] = fa,dep[u] = dep[fa] + 1,siz[u] = 1;
	for (Int v : G[u]) if (v ^ fa){
		dfs (v,u);
		siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
}

void dfs1 (int u,int Top){
	tur[dfn[u] = ++ ind] = u,top[u] = Top;
	if (son[u]) dfs1 (son[u],Top);
	for (Int v : G[u]) if (v != par[u] && v != son[u]) dfs1 (v,v);
}

struct Segment{
#define PSS pair<int,int>
#define fi first
#define sc second
	int sum[MAXN << 2];
	PSS Firs[MAXN << 2],laz[MAXN << 2];
	void Pushadd (int x,int l,int r,PSS v){
		sum[x] = add (sum[x],add (mul (v.fi,Firs[x].fi),mul (v.sc,Firs[x].sc)));
		laz[x].fi = add (laz[x].fi,v.fi),laz[x].sc = add (laz[x].sc,v.sc); 
	}
	void Pushdown (int x,int l,int r){
		int mid = (l + r) >> 1;
		Pushadd (x << 1,l,mid,laz[x]);
		Pushadd (x << 1 | 1,mid + 1,r,laz[x]);
		laz[x] = make_pair (0,0);
	}
	void Pushup (int x){
		sum[x] = add (sum[x << 1],sum[x << 1 | 1]); 
	}
	void build (int x,int l,int r){
		if (l == r){
			Firs[x] = make_pair (Fib (dep[tur[l]] - 1),Fib (dep[tur[l]]));
			return ;
		}
		int mid = (l + r) >> 1;
		build (x << 1,l,mid),build (x << 1 | 1,mid + 1,r);
		Pushup (x),
		Firs[x].fi = add (Firs[x << 1].fi,Firs[x << 1 | 1].fi),
		Firs[x].sc = add (Firs[x << 1].sc,Firs[x << 1 | 1].sc);
	}
	void modify (int x,int l,int r,int ql,int qr,PSS v){
		if (l >= ql && r <= qr){
			Pushadd (x,l,r,v);	
			return ;
		}
		Pushdown (x,l,r);int mid = (l + r) >> 1;
		if (ql <= mid) modify (x << 1,l,mid,ql,qr,v);
		if (qr > mid) modify (x << 1 | 1,mid + 1,r,ql,qr,v);
		Pushup (x);
	}
	int query (int x,int l,int r,int ql,int qr){
		if (l >= ql && r <= qr) return sum[x];
		Pushdown (x,l,r);int mid = (l + r) >> 1,res = 0;
		if (ql <= mid) res = add (res,query (x << 1,l,mid,ql,qr));
		if (qr > mid) res = add (res,query (x << 1 | 1,mid + 1,r,ql,qr));
		return res; 
	}
}Tree;

int Tree_Query (int u,int v){
	int res = 0;
	while (top[u] ^ top[v]){
		if (dep[top[u]] < dep[top[v]]) swap (u,v);
		res = add (res,Tree.query (1,1,n,dfn[top[u]],dfn[u])),u = par[top[u]];  
	}
	if (dfn[u] > dfn[v]) swap (u,v);
	res = add (res,Tree.query(1,1,n,dfn[u],dfn[v])); 
	return res;
}

void Tree_Update (int x,ll k){
	Tree.modify (1,1,n,dfn[x],dfn[x] + siz[x] - 1,make_pair (Fib (k - dep[x]),Fib (k - dep[x] + 1))); 	
}

signed main(){
	read (n,m);
	for (Int i = 2,u,v;i <= n;++ i) read (u,v),G[u].push_back (v),G[v].push_back (u);
	dfs (1,0),dfs1 (1,1),Tree.build(1,1,n);
	for (Int i = 1;i <= m;++ i){
		char s[5] = {};scanf ("%s",s);
		if (s[0] == 'U'){
			int x;ll k;read (x,k);
			Tree_Update (x,k);
		}
		else{
			int x,y;read (x,y);
			write (Tree_Query (x,y)),putchar ('\n');
		}
	}
	return 0;
}
```

---

## 作者：Erusel (赞：2)

对于这道题感触好深啊，调了3天的树剖

---

题目要求支持两种操作：

1.查询书上一条链的权值和

2.给定一个$k$,将$x$及其子树的所有点加上$f[D+k]$，其中$D$表示该节点在子树内的深度,$f$表示斐波那契数列

考虑到子树内的深度不太好做，我们把它转化成每个节点到根节点的深度$dep[i]$

在修改的时候，$k-=dep[x]$

将深度转化成了在整棵树上的深度后，我们可以考虑树链剖分维护这两个操作

考虑到斐波那契数列有这样一个性质:

$f[n+m]=f[m-1]*f[n]+f[m]*f[n+1]$

证明：

通过数学归纳法

设$1$至$x-1$都两两满足$f[n+m]=f[m-1]*f[n]+f[m]*f[n+1]$

下证

$f[1+x]=f[x-1]*f[1]+f[x]*f[2]$

$f[2+x]=f[x-1]*f[2]+f[x]*f[3]$

$……$

$f[x-1+x]=f[x-1]*f[x-1]+f[x]*f[x]$

对于任意的$f[p+x]$

都有$f[p+x]=f[(p-1)+x]+f[(p-2)+x]$

$=f[p+(x-1)]+f[(p-1)+(x-1)]$

$=f[x-2]*f[p]+f[x-1]*f[p+1]+f[x-2]*f[p-1]+f[x-1]*f[p]$

$=f[x-2]*f[p+1]+f[x-1]*f[p+2]$

$=f[x]*f[p+1]-f[x-1]*f[p+1]+f[x-1]*f[p]+f[x-1]*f[p+1]$

$=f[x]*f[p+1]+f[x-1]*f[p]$

对于每一次的修改操作，我们只要维护$f[dep[x]+K]$，其中$K=D+k-dep[x]$
是个定值

$f[dep[x]+K]=f[K-1]*f[dep[x]]+f[K]*f[dep[x]+1]$

因此，我们对每个节点维护一个二元组$(f[dep[i]-1],f[dep[i]])$,就可以在$O(nlogn)$的时间复杂度内维护我们的线段树

把这个问题丢到树上，树剖维护一下即可

因为$K$有可能为负数，这里求$f[i]$利用了$f[-n]=(-1)^{n-1}f[n]$，配合矩阵乘法即可。

几个需要注意的点：

1.树剖每个节点的初始值要设为$f[dep[i]]$

2.矩阵乘法的中间矩阵记得要初始化

3.线段树要设定一个二元组配合维护答案

4.注意一些细节问题，比如说二元组的加法和乘法qwq

**Code:**

```
#include<bits/stdc++.h>

#define rd(x) x=read()

#define N 100005

#define int long long

using namespace std;

int n,m;
const int p=1e9+7;

struct node{
    int x,y;
    node(int _x=0,int _y=0){x=_x,y=_y;}
    node operator + (const node & r)const{return node((x+r.x)%p,(y+r.y)%p);}
    int operator * (const node & r)const{return (x*r.x+y*r.y)%p;}
};//二元组基本运算

struct matrix{
	int a[2][2];
	matrix(){memset(a,0,sizeof(a));}
	inline void init(){a[0][0]=a[1][1]=1;}
	matrix operator * (const matrix &x) const {
		matrix ans;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					ans.a[i][k]=(ans.a[i][k]+a[i][j]*x.a[j][k])%p;
		return ans;
	}
}tr;//矩阵

matrix fastPow(matrix a,int b)
{
	matrix ans;ans.init();
	for(;b;b>>=1,a=a*a)if(b&1)ans=ans*a;
	return ans;
}//快速幂

node fib(int x)
{
    matrix ans;ans.a[0][1]=1;ans=ans*fastPow(tr,x<0?-x-1:x);
    if(x>=0)return node(ans.a[0][0],ans.a[0][1]);
    ans.a[0][(x+1)&1]=-ans.a[0][(x+1)&1];return node(ans.a[0][1],ans.a[0][0]);
}//求斐波那契数列

namespace HLD{
	#define ls (rt<<1)
	#define rs (rt<<1|1)
	struct E{
		int nxt,to;
	}e[N<<2];
	struct T{
		int l,r;
		node v,tag;
		int sum;
		void print(){printf("%d %d\n%d %d\n%d %d\n%d\n",l,r,v.x,v.y,tag.x,tag.y,sum);}//DEBUG
	}t[N<<2];
	int v[N],head[N],s[N],d[N],f[N],sn[N],tp[N],rk[N],id[N],cnt;
	inline void addEdge(int u,int v){e[++cnt].nxt=head[u],e[cnt].to=v,head[u]=cnt;}

	void dfs1(int x)
	{
		s[x]=1,d[x]=d[f[x]]+1,v[x]=d[x];
		for(int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].to;
			if(y!=f[x])
			{
				f[y]=x,dfs1(y),s[x]+=s[y];
				if(s[sn[x]]<s[y])sn[x]=y;
			}
		}
	}
	
	void dfs2(int x,int top)
	{
		tp[x]=top,id[x]=++cnt,rk[cnt]=x;
		if(sn[x])dfs2(sn[x],top);
		for(int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].to;
			if(y!=f[x]&&y!=sn[x])dfs2(y,y);
		}
	}
	
	inline void pushup(int rt){t[rt].v=t[ls].v+t[rs].v,t[rt].sum=(t[ls].sum+t[rs].sum)%p;}
	
	void build(int rt,int l,int r)
	{
		int mid=(l+r)>>1;
		t[rt].l=l,t[rt].r=r;
	    if(l==r)
	    {
	        t[rt].v=fib(v[rk[l]]);
	        return;
	    }
	    build(ls,l,mid),build(rs,mid+1,r);
	    pushup(rt);
	}
	
	inline void pushdown(int rt)
	{
	    if(t[rt].tag.x||t[rt].tag.y)
	    {
	        t[ls].tag=t[ls].tag+t[rt].tag,t[rs].tag=t[rs].tag+t[rt].tag;
	        t[ls].sum=(t[ls].sum+t[ls].v*t[rt].tag)%p,t[rs].sum=(t[rs].sum+t[rs].v*t[rt].tag)%p;
	        t[rt].tag=node();
	    }
	}
	
	void update(int rt,int l,int r,node c)
	{
	    if(t[rt].l>=l&&t[rt].r<=r)
	    {
	    	t[rt].tag=t[rt].tag+c,t[rt].sum=(t[rt].sum+t[rt].v*c)%p;
	        return;
	    }
	    pushdown(rt);
	    int mid=(t[rt].l+t[rt].r)>>1;
	    if(mid>=l)update(ls,l,r,c);
	    if(mid<r)update(rs,l,r,c);
	    pushup(rt);
	}//线段树
	
	int query(int rt,int l,int r)
	{
	    if(t[rt].l>=l&&t[rt].r<=r)return t[rt].sum;
	    pushdown(rt);
	    int mid=(t[rt].l+t[rt].r)>>1,ans=0;
	    if(mid>=l)ans=(ans+query(ls,l,r))%p;
	    if(mid<r)ans=(ans+query(rs,l,r))%p;
	    return ans;
	}
	
	inline int sum(int rt,int y)
	{
	    int ret=0;
	    while(tp[rt]!=tp[y])
	    {
	        if(d[tp[rt]]<d[tp[y]])swap(rt,y);
	        ret=(ret+query(1,id[tp[rt]],id[rt]))%p;	
	        rt=f[tp[rt]];
	    }
	    if(d[rt]>d[y])swap(rt,y);
	    return (ret+query(1,id[rt],id[y]))%p;
	}
	
	void dfs(int rt,int l,int r)
	{
		if(l==r)
		{
			printf("--------------------\n%d\n",rt),t[rt].print();
			printf("--------------------\n");
			return ;
		}
		int mid=(l+r)>>1;
		dfs(ls,l,mid),dfs(rs,mid+1,r);
	}//DEBUG
}//树剖

inline int read()
{
    int f=1,x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    return x*f;
}

signed main()
{
	rd(n),rd(m),tr.a[0][1]=tr.a[1][0]=tr.a[1][1]=1;int u,v;
	for(int i=1;i<n;i++)rd(u),rd(v),HLD::addEdge(u,v),HLD::addEdge(v,u);
   HLD::cnt=0,HLD::dfs1(1),HLD::dfs2(1,1),HLD::cnt=0,HLD::build(1,1,n);
   #ifdef DEBUG
   for(int i=1;i<=n;i++)cout<<HLD::d[i]<<' '<<HLD::tp[i]<<' '<<HLD::s[i]<<' '<<HLD::f[i]<<endl;
   #endif
	while(m--)			
	{		
		char opt[5];int x,k;scanf("%s",opt);rd(x),rd(k);
        if(opt[0]=='U')k-=HLD::d[x]+1,HLD::update(1,HLD::id[x],HLD::id[x]+HLD::s[x]-1,fib(k));
        else printf("%d\n",HLD::sum(x,k));
        #ifdef DEBUG
        HLD::dfs(1,1,n);
        #endif
	}
    
    
    
   return 0;
}
```
您看看这篇代码里，满满是DEBUG的痕迹，还有一些痕迹都被删除了，

思维难度还行，代码难度较大qwq


---

## 作者：Wolfycz (赞：2)

这题首先想到树剖，但是直接树剖完全无法维护，因此我们需要知道Fibonacci数列的一个性质：$Fib_{n+m}=Fib_{m-1}*Fib_{n}+Fib_{m}*Fib_{n+1}$(证明请自行百度)

那么对于每个点加的值$Fib_{D+k}$，我们可以将其改为$Fib_d+k'$($d$为该点在树上的深度，且$D+k=d+k'$)，那么每个点加的值为$Fib_{d-1}*Fib_{k'}+Fib_d*Fid_{k'+1}$(或者其他方式)，因为$k'=D-d+k$，且$D-d$是个定值，所以$k'$是个定值，因此我们只要对于每个节点维护好$Fib_{d-1},Fib_{d}$，就可以用树剖+线段树维护其系数，细节可以看下代码

就算$k'$是负数也没关系，你可以用负数去尝试，依然满足该性质，$Fib_{k'}$使用$Fib_{k'+2}=Fib_{k'}+Fib_{k'+1}$倒序求即可（或者可以用$Fib_{-n}=(-1)^{n-1}Fib_{n}$求得，我使用后者）

由于$k'$达到了$10^{18}$，所以我们需要用矩乘求$Fib_{k'}$

```cpp
/*program from Wolfycz*/
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 0x7f7f7f7f
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
inline char gc(){
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int frd(){
	int x=0,f=1; char ch=gc();
	for (;ch<'0'||ch>'9';ch=gc())	if (ch=='-')	f=-1;
	for (;ch>='0'&&ch<='9';ch=gc())	x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
inline int read(){
	int x=0,f=1; char ch=getchar();
	for (;ch<'0'||ch>'9';ch=getchar())	if (ch=='-')	f=-1;
	for (;ch>='0'&&ch<='9';ch=getchar())	x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
inline void print(int x){
	if (x<0)	putchar('-'),x=-x;
	if (x>9)	print(x/10);
	putchar(x%10+'0');
}
const int N=1e5,Mod=1e9+7;
int n,m;
struct Node{
	int x,y;
	Node(){x=y=0;}
	Node(int _x,int _y){x=_x,y=_y;}
	Node operator +(const Node &tis)const{return Node((x+tis.x)%Mod,(y+tis.y)%Mod);}
	int operator *(const Node &tis)const{return (1ll*x*tis.x+1ll*y*tis.y)%Mod;}
};
struct Matrix{
	int v[2][2];
	Matrix(){memset(v,0,sizeof(v));}
	void init(){for (int i=0;i<2;i++)	v[i][i]=1;}
}trans;
Matrix operator *(const Matrix &x,const Matrix &y){
	Matrix z;
	for (int i=0;i<2;i++)
		for (int j=0;j<2;j++)
			for (int k=0;k<2;k++)
				z.v[i][k]=(z.v[i][k]+1ll*x.v[i][j]*y.v[j][k])%Mod;
	return z;
}
Matrix mlt(Matrix a,ll b){
	Matrix res; res.init();
	for (;b;b>>=1,a=a*a)	if (b&1)	res=res*a;
	return res;
}
Node Fib(ll x){
	Matrix res; res.v[0][1]=1;
	res=res*mlt(trans,x<0?-x-1:x);
	if (x>=0)	return Node(res.v[0][0],res.v[0][1]);
	res.v[0][(-x-1)&1]=-res.v[0][(-x-1)&1];
	return Node(res.v[0][1],res.v[0][0]);
}
void init(){trans.v[0][1]=trans.v[1][0]=trans.v[1][1]=1;}
int v[N+10],dfn[N+10],ID[N+10];
struct S1{
	#define ls (p<<1)
	#define rs (p<<1|1)
	struct node{
		int sum;
		Node val,tag;
	}tree[(N<<2)+10];
	void updata(int p){
		tree[p].val=tree[ls].val+tree[rs].val;
		tree[p].sum=(tree[ls].sum+tree[rs].sum)%Mod;
	}
	void Add_tag(int p,Node v){
		tree[p].sum=(tree[p].sum+tree[p].val*v)%Mod;
		tree[p].tag=tree[p].tag+v;
	}
	void pushdown(int p){
		if (!tree[p].tag.x&&!tree[p].tag.y)	return;
		Add_tag(ls,tree[p].tag);
		Add_tag(rs,tree[p].tag);
		tree[p].tag=Node(0,0);
	}
	void build(int p,int l,int r){
		if (l==r){
			tree[p].val=Fib(v[dfn[l]]);
			return;
		}
		int mid=(l+r)>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		updata(p);
	}
	void Modify(int p,int l,int r,int x,int y,Node v){
		if (x<=l&&r<=y){
			Add_tag(p,v);
			return;
		}
		pushdown(p);
		int mid=(l+r)>>1;
		if (x<=mid)	Modify(ls,l,mid,x,y,v);
		if (y>mid)	Modify(rs,mid+1,r,x,y,v);
		updata(p);
	}
	int Query(int p,int l,int r,int x,int y){
		if (x<=l&&r<=y)	return tree[p].sum;
		int mid=(l+r)>>1,res=0;
		pushdown(p);
		if (x<=mid)	res=(res+Query(ls,l,mid,x,y))%Mod;
		if (y>mid)	res=(res+Query(rs,mid+1,r,x,y))%Mod;
		return res;
	}
	#undef ls
	#undef rs
}ST;//Segment Tree
struct S2{
	int pre[(N<<1)+10],now[N+10],child[(N<<1)+10],tot,Time;
	int deep[N+10],fa[N+10],size[N+10],top[N+10],Rem[N+10];
	void join(int x,int y){pre[++tot]=now[x],now[x]=tot,child[tot]=y;}
	void insert(int x,int y){join(x,y),join(y,x);}
	void dfs(int x){
		deep[x]=deep[fa[x]]+1,size[x]=1,v[x]=deep[x];
		for (int p=now[x],son=child[p];p;p=pre[p],son=child[p]){
			if (son==fa[x])	continue;
			fa[son]=x,dfs(son);
			size[x]+=size[son];
			if (size[Rem[x]]<size[son])	Rem[x]=son;
		}
	}
	void build(int x){
		if (!x)	return;
		dfn[ID[x]=++Time]=x;
		top[x]=Rem[fa[x]]==x?top[fa[x]]:x;
		build(Rem[x]);
		for (int p=now[x],son=child[p];p;p=pre[p],son=child[p]){
			if (son==Rem[x]||son==fa[x])	continue;
			build(son);
		}
	}
	int work(int x,int y){
		int res=0;
		while (top[x]!=top[y]){
			if (deep[top[x]]<deep[top[y]])	swap(x,y);
			res=(res+ST.Query(1,1,n,ID[top[x]],ID[x]))%Mod;;
			x=fa[top[x]];
		}
		if (deep[x]>deep[y])	swap(x,y);
		res=(res+ST.Query(1,1,n,ID[x],ID[y]))%Mod;;
		return res;
	}
}HLD;//Heavy Light Decomposition
int main(){
	init(); char s[5];
	n=read(),m=read();
	for (int i=1;i<n;i++){
		int x=read(),y=read();
		HLD.insert(x,y);
	}
	HLD.dfs(1),HLD.build(1),ST.build(1,1,n);
	for (int i=1;i<=m;i++){
		scanf("%s",s);
		if (s[0]=='U'){
			int x=read(); ll k;
			scanf("%lld",&k);
			k-=v[x]+1;
			ST.Modify(1,1,n,ID[x],ID[x]+HLD.size[x]-1,Fib(k));
		}
		if (s[0]=='Q'){
			int x=read(),y=read();
			printf("%d\n",HLD.work(x,y));
		}
	}
	return 0;
}
```

---

## 作者：2022dyx (赞：1)

前情提要：这是一个复杂度为 $O(n+m\log n)$ 的做法。

对于一道有子树操作和链查询的题目来说，最无脑的处理肯定是扔到树链剖分上去。但由于这道题的询问 $q(u,v) $ 可以转化为 $q(u,1)+q(v,1)-q(lca,1)-q(fa_{lca},1)$，所以说如果能够直接维护到根的链和，就能规避掉树链剖分。后文中我们将一个点 $x$ 到根的链和称为这个点的权值 $val_x$。

在一次修改 $x\ k$ 中，对于 $x$ 子树中的点 $y$，其权值的增加量为 $Fib_k+Fib_{k+1}+...+Fib_{k-dep_x+dep_y}$。根据一个众所周知的结论 $Fib_1+Fib_2+...+Fib_i=Fib_{i+2}-1$（数学归纳法易证），我们可以将 $\Delta val_y$ 写成 $Fib_{k-dep_x+dep_y+2}-Fib_{k+1}$。后者只和 $k$ 有关，可以直接在线段树维护区间加，而前者可以整理为 $F_{(k-dep_x+2)+dep_y}$，是对 $Fib_{dep_y}$ 进行了一次位移，并且同一次询问中位移量均相等。

对斐波那契数列的位移看似很难办，但实际上我们矩阵乘法求斐波那契数列的时候就相当于在快速位移！所以说，设斐波那契转移矩阵为 $F$，则需要做的就是给所有 $x$ 子树中的 $y$ 同时乘上 $F^{k-dep_x+2}$ 并加到权值中。这正是线段树能做到的事情，因此用线段树维护权值向量与懒标记矩阵就可以完成本题。

另外，由于常数问题，朴素的做法甚至跑不过双 $\log$。因此我们需要一点优化。首先，由于底数固定所以使用光速幂就可以规避掉快速幂的 $\log$。然后，由于下传懒标记的常数很大，可以给线段树的节点维护一个空标记表示这个点的懒标记是否为空，如果为空就可以跳过不下传。加上这些优化后跑起来的效果就不错了。

下面附上代码：
```
#include <bits/stdc++.h>
#define file(x) freopen(#x ".in", "r", stdin); freopen(#x ".out", "w", stdout);
#define int long long
#define pb push_back
#define ls (x << 1)
#define rs ((x << 1) ^ 1)
#define mid ((l + r) >> 1)
using namespace std;
constexpr int N = 1e5 + 5;
constexpr int L = 1e3;
constexpr int mod = 1e9 + 7;
int n, m, f[N], fa[N][20], dep[N], dfn[N], siz[N], plc[N], tag[N], ans[N], nowtag, idx, up, pup;
char c;
vector <int> e[N];
struct Matrix{
	int val[2][2];
	Matrix () { memset(val, 0, sizeof val); }
	Matrix operator + (const Matrix &another) const {
		Matrix ret;
		for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) ret.val[i][j] = (val[i][j] + another.val[i][j]) % mod;
		return ret;
	}
	Matrix operator * (const Matrix &another) const {
		Matrix ret;
		for (int i = 0; i < 2; ++i) for (int k = 0; k < 2; ++k) for (int j = 0; j < 2; ++j) ret.val[i][j] = (ret.val[i][j] + val[i][k] * another.val[k][j]) % mod;
		return ret;
	}
	void clear() { memset(val, 0, sizeof val); }
} now, Up, pUp;
struct FastMatrix{
	Matrix bas, mat[6][L];
	void init() {
		mat[0][0].val[0][0] = mat[0][0].val[1][1] = mat[0][0].val[2][2] = 1;
		mat[1][0].val[0][0] = mat[1][0].val[1][1] = mat[1][0].val[2][2] = 1;
		mat[2][0].val[0][0] = mat[2][0].val[1][1] = mat[2][0].val[2][2] = 1;
        mat[3][0].val[0][0] = mat[3][0].val[1][1] = mat[3][0].val[2][2] = 1;
        mat[4][0].val[0][0] = mat[4][0].val[1][1] = mat[4][0].val[2][2] = 1;
        mat[5][0].val[0][0] = mat[5][0].val[1][1] = mat[5][0].val[2][2] = 1;
		for (int i = 1; i < L; ++i) mat[0][i] = mat[0][i - 1] * bas;
		mat[1][1] = mat[0][L - 1] * mat[0][1];
		for (int i = 2; i < L; ++i) mat[1][i] = mat[1][i - 1] * mat[1][1];
		mat[2][1] = mat[1][L - 1] * mat[1][1];
		for (int i = 2; i < L; ++i) mat[2][i] = mat[2][i - 1] * mat[2][1];
        mat[3][1] = mat[2][L - 1] * mat[2][1];
		for (int i = 2; i < L; ++i) mat[3][i] = mat[3][i - 1] * mat[3][1];
        mat[4][1] = mat[3][L - 1] * mat[3][1];
		for (int i = 2; i < L; ++i) mat[4][i] = mat[4][i - 1] * mat[4][1];
        mat[5][1] = mat[4][L - 1] * mat[4][1];
		for (int i = 2; i < L; ++i) mat[5][i] = mat[5][i - 1] * mat[5][1];
	}
	void pw(int x) {
		now = mat[0][x % L], x /= L;
		now = now * mat[1][x % L], x /= L;
		now = now * mat[2][x % L], x /= L;
        now = now * mat[3][x % L], x /= L;
        now = now * mat[4][x % L], x /= L;
        now = now * mat[5][x % L];
	}
} mat1, mat2;
struct Vector {
	int val[2];
	Vector () { memset(val, 0, sizeof val); }
	Vector operator + (const Vector &another) const {
		Vector ret;
		for (int i = 0; i < 2; ++i) ret.val[i] = (val[i] + another.val[i]) % mod;
		return ret;
	}
	Vector operator * (const Matrix &another) const {
		Vector ret;
		for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) ret.val[i] = (ret.val[i] + val[j] * another.val[j][i]) % mod;
		return ret;

	}
};
struct Node { bool emp = true; int val, laz, bas; Vector Val, Bas; Matrix Laz; } tree[N << 2];
void pushup(int x) { tree[x].val = (tree[ls].val + tree[rs].val) % mod, tree[x].Val = tree[ls].Val + tree[rs].Val; }
void update(int x) { tree[x].val = (tree[x].val + tree[x].bas * pup) % mod, tree[x].Val = tree[x].Val + tree[x].Bas * pUp, tree[x].laz = (tree[x].laz + pup) % mod, tree[x].Laz = tree[x].Laz + pUp, tree[x].emp = false; }
void pushdown(int x) {
    if (tree[x].emp) return;
	pup = tree[x].laz, swap(pUp, tree[x].Laz), tree[x].laz = 0, tree[x].Laz.clear(), tree[x].emp = true, update(ls), update(rs);
}
void build(int l, int r, int x) {
	if (l == r) return (plc[l] = x), void();
	build(l, mid, ls);
	build(mid + 1, r, rs);
}
void push(int l, int r, int x) {
	if (l == r) return (tree[x].bas = 1), void();
	push(l, mid, ls);
	push(mid + 1, r, rs);
	tree[x].bas = tree[ls].bas + tree[rs].bas;
	tree[x].Bas = tree[ls].Bas + tree[rs].Bas;
}
void modify(int l, int r, int x, int y, int z) {
	if (y <= l && r <= z) return pup = up, memcpy(pUp.val, Up.val, sizeof Up.val), update(x);
	pushdown(x);
	if (y <= mid) modify(l, mid, ls, y, z);
	if (z > mid) modify(mid + 1, r, rs, y, z);
	pushup(x);
}
int query(int l, int r, int x, int y) {
	if (!y) return 0;
	if (l == r) return (tree[x].val + tree[x].Val.val[0]) % mod;
	pushdown(x);
	if (y <= mid) return query(l, mid, ls, y);
	return query(mid + 1, r, rs, y);
}
void dfs(int x, int z) {
	dfn[x] = ++idx, siz[x] = 1;
	for (int y : e[x]) if (y != z) fa[y][0] = x, dep[y] = dep[x] + 1, dfs(y, x), siz[x] += siz[y];
	tree[plc[dfn[x]]].Bas.val[0] = f[dep[x]];
	tree[plc[dfn[x]]].Bas.val[1] = f[dep[x] - 1];
}
int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = 19; ~i; --i) if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if (x == y) return x;
	for (int i = 19; ~i; --i) if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}
void pw(int x) { x >= 0 ? mat1.pw(x) : mat2.pw(-x); }
int Query(int l, int r, int x, int y) {
	if (tag[y] == nowtag) return ans[y];
	tag[y] = nowtag, ans[y] = query(l, r, x, y);
	return ans[y];
}
signed main() {
	cin.tie(0) -> sync_with_stdio(false);
	memset(tag, -1, sizeof tag);
	mat1.bas.val[0][0] = mat1.bas.val[0][1] = mat1.bas.val[1][0] = 1;
	mat2.bas.val[0][1] = mat2.bas.val[1][0] = 1, mat2.bas.val[1][1] = -1;
	mat1.init(), mat2.init();
	cin >> n >> m;
	f[1] = 1;
	for (int i = 2; i <= n; ++i) f[i] = (f[i - 2] + f[i - 1]) % mod;
	for (int i = 2, x, y; i <= n; ++i) cin >> x >> y, e[x].pb(y), e[y].pb(x);
	build(1, n, 1), dep[1] = 1, dfs(1, 0), push(1, n, 1);
	for (int j = 1; j <= 19; ++j) for (int i = 1; i <= n; ++i) fa[i][j] = fa[fa[i][j - 1]][j - 1];
    for (int i = 1, x, y; i <= m; ++i) {
		cin >> c >> x >> y;
		if (c == 'U') {
			nowtag = i;
			pw(y + 1), up = (mod - now.val[1][0]) % mod;
			pw(y - dep[x] + 2), swap(Up, now);
			modify(1, n, 1, dfn[x], dfn[x] + siz[x] - 1);
		}
		if (c == 'Q') {
			int l = lca(x, y);
			cout << (Query(1, n, 1, dfn[x]) + Query(1, n, 1, dfn[y]) - Query(1, n, 1, dfn[l]) - Query(1, n, 1, dfn[fa[l][0]]) + mod + mod) % mod  << '\n';
		}
	}
}
```

---

## 作者：Piggy343288 (赞：0)

因为本题的代码难度远大于解法的思考，因此这里提供一种好写的写法。  

做法不再赘述，就是转化为 $depth$ 差以后上线段树分别维护两个信息以后求和。题解中大多数使用同一个线段树维护两个信息，可读性并不高，且比较难写。  

事实上我们注意到两棵线段树仅有初始的信息不一样，剩下需要支持的操作完全一样，这启发我们通过一些方式让我们方便的写两棵线段树。  

这里介绍一种广为人知的黑科技：在结构体中使用函数指针。具体的，本人使用的部分代码如下：   

```cpp
int (*func)(int);
void build(int p, int l, int r) {
    // printf("%d %d %d\n", p, l, r);
    if (l == r) {
        val[p] = func(l) % mod;
        return;
    }
    build(ls, l, mid), build(rs, mid + 1, r);
    val[p] = val[ls] + val[rs];
    val[p] %= mod;
}
```
那么，我们初始化两棵线段树，需要对 $func$ 赋值：  
```cpp
st1.func = [](int x) { return calcfib(depth[rev[x]]); };
st2.func = [](int x) { return calcfib(depth[rev[x]] - 1); };
st1.build(1, 1, n), st2.build(1, 1, n);
```
接着，我们重写两个函数以方便查询：  
```cpp
void update(int x, int y, int k) {
    st1.update(1, 1, n, x, y, calcfib(k + 1));
    st2.update(1, 1, n, x, y, calcfib(k));
}
int query(int x, int y) {
    return (st1.query(1, 1, n, x, y) + st2.query(1, 1, n, x, y)) % mod;
}
```

这样的代码个人认为要更优雅，可读性更好一些，避免了一堆结构体或 pair 的不便。  
放上最后的[代码](https://www.luogu.com.cn/paste/j0wg7xlt)。

---

## 作者：lemondinosaur (赞：0)

[题目传送门](https://www.luogu.org/problem/P5138)

---
# 分析
首先此题一眼算法树链剖分+线段树
~~然而只是知道而不会做(而且比赛的时候连树链剖分都不会)~~

这个$Fib_{D+k}=Fib_{D-1}*Fib_{k}+Fib_{D}*Fib_{k+1}$

可以在线段树中维护$Fib_{n-1},Fib_{n}$求解，

相当于区间每次累加打一个标记，再求和，

如果是负数，那么$Fib_{-n}=(-1)^{n-1}Fib_n$

然而深度怎么办，可以预先建线段树维护深度的斐波那契值使其成为一个定值

然而我~~作死~~找到了斐波那契循环节（From[斐波那契数列（加强版）](https://www.luogu.org/problem/P4000)），就可以矩阵分块了，

时间复杂度$O(89444*4+(4n+m)log_2n)$(循环展开)

然而发现出题人的标程维护$Fib_{n+1},Fib_n$，WA了照着标程改结果WA了两天

---
# 代码
```cpp
#include <cstdio>
#include <cctype>
#define rr register
using namespace std;
typedef long long ll;
const int N=100101,mod=1e9+7,he=44721;
inline signed mo(int x,int y){return x+y>=mod?x+y-mod:x+y;}
struct node{int y,next;}e[N<<1]; struct maix{int p[2][2];}A[he|15],B[he|15];
int n,k=1,m,ls[N],big[N],son[N],a[N],w[N<<2],dfn[N],tot,top[N],dep[N],fat[N];
struct rec{
    int fir,sec;
    rec operator +(const rec &t)const{return (rec){mo(fir,t.fir),mo(sec,t.sec)};}//累加项数
    signed operator *(const rec &t)const{return mo(1ll*fir*t.fir%mod,1ll*sec*t.sec%mod);}//统计答案
}wt[N<<2],lazy[N<<2];
inline signed iut(){
	rr int ans=0; rr char c=getchar();
	while (!isdigit(c)) c=getchar();
	while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
	return ans;
}
inline void print(int ans){
    if (ans<0) putchar('-'),ans=-ans;
	if (ans>9) print(ans/10);
	putchar(ans%10+48);
}
inline maix mul(maix A,maix B){
    rr maix C;
    C.p[0][0]=mo(1ll*A.p[0][0]*B.p[0][0]%mod,1ll*A.p[0][1]*B.p[1][0]%mod);
    C.p[0][1]=mo(1ll*A.p[0][0]*B.p[0][1]%mod,1ll*A.p[0][1]*B.p[1][1]%mod);
    C.p[1][0]=mo(1ll*A.p[1][0]*B.p[0][0]%mod,1ll*A.p[1][1]*B.p[1][0]%mod);
    C.p[1][1]=mo(1ll*A.p[1][0]*B.p[0][1]%mod,1ll*A.p[1][1]*B.p[1][1]%mod);
    return C;
}
inline rec fib(ll nn){
    rr ll n=nn>=0?nn:-nn+1;
    rr maix C=mul(B[n/he],A[n%he]);
    if (nn>=0) return (rec){C.p[0][0],C.p[0][1]};
    C.p[0][n&1^1]=mod-C.p[0][n&1^1];
    return (rec){C.p[0][1],C.p[0][0]};
}
inline void build(int k,int l,int r){
	if (l==r){wt[k]=fib(a[l]); return;}
	rr int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
    wt[k]=wt[k<<1]+wt[k<<1|1];
}
inline void pup(int k,rec z){
    w[k]=mo(w[k],wt[k]*z);
    lazy[k]=lazy[k]+z;
}
inline void pdown(int k){
    if (!lazy[k].fir&&!lazy[k].sec) return;
    pup(k<<1,lazy[k]),pup(k<<1|1,lazy[k]);
    lazy[k]=(rec){0,0};
}
inline signed query(int k,int l,int r,int x,int y){
	if (l==x&&r==y) return w[k];
    pdown(k); rr int mid=(l+r)>>1;
	if (y<=mid) return query(k<<1,l,mid,x,y);
	else if (x>mid) return query(k<<1|1,mid+1,r,x,y);
	else return mo(query(k<<1,l,mid,x,mid),query(k<<1|1,mid+1,r,mid+1,y));
}
inline void update(int k,int l,int r,int x,int y,rec z){
	if (l==x&&r==y) {pup(k,z); return;}
	pdown(k); rr int mid=(l+r)>>1;
	if (y<=mid) update(k<<1,l,mid,x,y,z);
	else if (x>mid) update(k<<1|1,mid+1,r,x,y,z);
	else update(k<<1,l,mid,x,mid,z),update(k<<1|1,mid+1,r,mid+1,y,z);
	w[k]=mo(w[k<<1],w[k<<1|1]);
}
inline signed Query(int x,int y){
	rr int ans=0;
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) x^=y,y^=x,x^=y;
		ans=mo(ans,query(1,1,n,dfn[top[x]],dfn[x]));
		x=fat[top[x]];
	}
	if (dep[x]>dep[y]) x^=y,y^=x,x^=y;
	return ans=mo(ans,query(1,1,n,dfn[x],dfn[y]));
}
inline void dfs1(int x,int fa){
	dep[x]=dep[fa]+1,fat[x]=fa,son[x]=1;
	for (rr int i=ls[x],mson=-1;i;i=e[i].next)
	if (e[i].y!=fa){
		dfs1(e[i].y,x);
		son[x]+=son[e[i].y];
		if (son[e[i].y]>mson) big[x]=e[i].y,mson=son[e[i].y];
	}
}
inline void dfs2(int x,int linp){
	dfn[x]=++tot,top[x]=linp,a[tot]=dep[x];
	if (!big[x]) return; dfs2(big[x],linp);
	for (rr int i=ls[x];i;i=e[i].next)
	if (e[i].y!=fat[x]&&e[i].y!=big[x]) dfs2(e[i].y,e[i].y);
}
signed main(){
    A[1].p[0][1]=A[1].p[1][0]=A[1].p[1][1]=A[0].p[1][1]=A[0].p[0][0]=1;
    for (rr int i=2;i<=he;++i) A[i]=mul(A[i-1],A[1]);
    B[0]=A[0],B[1]=A[he];
    for (rr int i=2;i<=he;++i) B[i]=mul(B[i-1],B[1]);
    n=iut(); m=iut();
    for (rr int i=1;i<n;++i){
        rr int x=iut(),y=iut();
        e[++k]=(node){y,ls[x]},ls[x]=k,
        e[++k]=(node){x,ls[y]},ls[y]=k;
    }
    dfs1(1,0),dfs2(1,1),build(1,1,n);
    while (m--){
        rr char c=getchar();
        while (c!='U'&&c!='Q') c=getchar();
        if (c=='U'){
            rr int x=iut(); rr ll y; scanf("%lld",&y);
            y=(y-dep[x]+1)%((mod+1)<<1);
            update(1,1,n,dfn[x],dfn[x]+son[x]-1,fib(y));
        }else print(Query(iut(),iut())),putchar(10);
    }
    return 0;
}
```

---

