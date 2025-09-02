# [ICPC 2021 Nanjing R] Paimon Segment Tree

## 题目描述

派蒙刚刚学习了可持久化线段树，她想马上练习一下。因此，荧决定给她出一道简单的问题：

给定数列$a_1, a_2, \cdots, a_n$，并进行$m$次操作。操作包含3个参数$l_i$, $r_i$ ($1 \le l_i \le r_i \le n$) 和 $x_i$，代表对该序列第$l_i$到第$r_i$个元素加上$x_i$。

记$a_{i, t}$为$t$次操作后$a_i$的值。注意若$a_i$未被修改，则$a_{i,t}$的值与$a_{i,t-1}$相同。定义$a_{i, 0}$是$a_i$的初始值。


完成所有操作后，荧进行$q$次询问，询问包含4个整数$l_k$, $r_k$, $x_k$ and $y_k$，派蒙需要回答

$$\sum\limits_{i=l_k}^{r_k}\sum\limits_{j=x_k}^{y_k} a_{i, j}^2$$

请将答案对$10^9 + 7$取模后输出。

## 样例 #1

### 输入

```
3 1 1
8 1 6
2 3 2
2 2 0 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 3 3
2 3 2 2
1 1 6
1 3 3
1 3 6
2 2 2 3
1 4 1 3
4 4 2 3
```

### 输出

```
180
825
8
```

# 题解

## 作者：xiezheyuan (赞：5)

## 简要题意

你需要维护一个 $(m+1)\times n$ 的矩阵 $A$，行从 $0$ 开始计数。初始时满足 $A_{0i}=A_{1i}=\cdots=A_{mi}=a_i$。

有 $m$ 次操作，第 $i$ 次操作给出区间 $[l,r]$ 和常数 $v$，表示将满足 $i\leq x\leq m,l\leq y\leq r$ 的 $A_{xy}$ 加上 $v$。

有 $q$ 次询问，每次询问给出给出区间 $[x,y]$ 和 $[l,r]$，求满足 $x\leq p\leq y,l\leq q\leq r$ 的 $A_{pq}$ 的平方和。对一个大质数取模。

$1\leq n,m,q\leq 5\times10^4$

## 思路

先差分，改为求 $[1,y]$ 的答案减去 $[1,x-1]$ 的答案。所以可以转成求区间历史平方和（应该叫做这个名字）。

考虑区间和 $B$、区间平方和 $C$、区间历史平方和 $D$ 与区间长度 $A$ 的关系。假设现在执行了区间加 $v$，则：

$$
\begin{aligned}
&A^{'}=A\\
&B^{'}=vA+B\\
&C^{'}=v^2A+2vB+C\\
&D^{'}=v^2A+2vB+C+D
\end{aligned}
$$

其中 $C^{'}$ 就是拆完全平方公式，其他没什么好提的。

不难发现假如我们用向量来表示每一个位置：

$$
\begin{bmatrix}
A&B&C&D
\end{bmatrix}
$$

则可以构造一个矩阵，用矩阵乘法的方法来修改：

$$
\begin{bmatrix}
A&B&C&D
\end{bmatrix}\times
\begin{bmatrix}
1&v&v^2&v^2\\
0&1&2v&2v\\
0&0&1&1\\
0&0&0&1
\end{bmatrix}
=
\begin{bmatrix}
A^{'}&B^{'}&C^{'}&D^{'}
\end{bmatrix}
$$

然后需要注意下没有修改的部分，区间历史平方和需要集体手动更新：

$$
\begin{aligned}
&A^{'}=A\\
&B^{'}=B\\
&C^{'}=C\\
&D^{'}=C+D
\end{aligned}
$$

则可以构造一个矩阵，用矩阵乘法的方法来修改：

$$
\begin{bmatrix}
A&B&C&D
\end{bmatrix}\times
\begin{bmatrix}
1&0&0&0\\
0&1&0&0\\
0&0&1&1\\
0&0&0&1
\end{bmatrix}
=
\begin{bmatrix}
A^{'}&B^{'}&C^{'}&D^{'}
\end{bmatrix}
$$

然后你抓一只无辜的线段树维护一下即可。

至于询问，可以离线，在每一次操作后计算一下需要计算的区间历史平方和。

时间复杂度 $O(q\log n)$ 带一个 $64$ 倍常数。其实可以优化矩阵乘法来减小常数，但是据说没必要，我就没有写了（于是就要丧心病狂的卡常了）。

## 实现上的小细节

- 输入的 $v$ 有负数，需要注意取模姿势。否则容易 WA 在第 $3$ 个点。
- 尽量减少取模次数，对于加法只需要做一次减法来代替直接取模，对于乘法没必要使用 `(1ll * x * y % mod + mod) % mod` 直接使用 `1ll * x * y % mod` 即可。
- 除了乘法，其他地方不要开 `long long`。

## 代码

喜提最优解最后一名！此代码目前只能在 Luogu 上通过，Gym 上被卡常了，开心。

[Submission](https://vjudge.net/solution/48888917/ay5tBVlfU5mjQQ9TMQU8)

```cpp
#include <bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

const int mod = 1e9 + 7, N = 5e4 + 5;

int M(long long x){return x%mod;}
int Add(long long x, long long y){return (x + y) > mod ? (x - mod + y) : (x + y);}

struct matrix{
    int n,m,a[5][5];
    void clear(){memset(a, 0, sizeof(a));}
    void init(int N, int M){n = N, m = M;clear();}
    int* operator[](int i){return a[i];}
};

matrix operator*(matrix a, matrix b){
    matrix ans;ans.init(a.n, b.m);
    assert(a.m == b.n);
    for(int k=1;k<=a.m;k++){
        for(int i=1;i<=a.n;i++){
            for(int j=1;j<=b.m;j++) ans[i][j] = Add(ans[i][j], M(1ll * a[i][k] * b[k][j]));
        }
    }
    return ans;
}

matrix operator+(matrix a, matrix b){
    matrix ans;ans.init(a.n, a.m);
    for(int i=1;i<=a.n;i++){
        for(int j=1;j<=a.m;j++) ans[i][j] = Add(a[i][j], b[i][j]);
    }
    return ans;
}


matrix t[N << 2], tag[N << 2];

void pushup(int i){t[i] = t[ls] + t[rs];}

void build(int i, int l, int r){
    tag[i].init(4, 4);
    tag[i][1][1] = tag[i][2][2] = tag[i][3][3] = tag[i][4][4] = 1;
    if(l == r){
        int v;cin>>v;
        t[i].init(1, 4);
        t[i][1][1] = 1;t[i][1][2] = v = Add(mod, v);
        t[i][1][3] = t[i][1][4] = M(1ll * v * v);
        return;
    }
    build(ls, l, mid);build(rs, mid + 1, r);
    pushup(i);
}

void pushdown(int i){
    tag[ls] = tag[ls] * tag[i];
    tag[rs] = tag[rs] * tag[i];
    t[ls] = t[ls] * tag[i];
    t[rs] = t[rs] * tag[i];
    tag[i].init(4, 4);
    tag[i][1][1] = tag[i][2][2] = tag[i][3][3] = tag[i][4][4] = 1;
}

void update(int ql, int qr, matrix v, int i, int l, int r){
    if(ql > qr) return;
    if(ql <= l && r <= qr){
        tag[i] = tag[i] * v;
        t[i] = t[i] * v;
        return;
    }
    pushdown(i);
    if(ql <= mid) update(ql, qr, v, ls, l, mid);
    if(qr > mid) update(ql, qr, v, rs, mid + 1, r);
    pushup(i);
}

matrix query(int ql, int qr, int i, int l, int r){
    if(ql <= l && r <= qr) return t[i];
    pushdown(i);
    if(ql <= mid && qr > mid) return query(ql, qr, ls, l, mid) + query(ql, qr, rs, mid + 1, r);
    if(ql <= mid) return query(ql, qr, ls, l, mid);
    else return query(ql, qr, rs, mid + 1, r);
}

vector<pair<int,int> > qs[N];
vector<int> ans[N];
int n,m,q;

struct Update{
    int l, r, v;
} updates[N];

struct Query{
    int p1, p2, q1, q2;
} qqs[N];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    build(1, 1, n);
    for(int i=1;i<=m;i++) cin>>updates[i].l>>updates[i].r>>updates[i].v;
    for(int i=1;i<=q;i++){
        int l,r,x,y;cin>>l>>r>>x>>y;
        qqs[i].p1 = qs[x].size();
        qqs[i].q1 = x;
        qs[x].push_back(make_pair(l, r));
        qqs[i].p2 = qs[y + 1].size();
        qqs[i].q2 = y + 1;
        qs[y + 1].push_back(make_pair(l, r));
    }
    for(auto i : qs[0]) ans[0].push_back(0);
    for(auto i : qs[1]) ans[1].push_back(query(i.first, i.second, 1, 1, n)[1][4]);
    for(int i=1;i<=m;i++){
        int l = updates[i].l, r = updates[i].r, v = updates[i].v;
        matrix mat;mat.init(4, 4);
        mat[1][1] = mat[2][2] = mat[3][3] = mat[3][4] = mat[4][4] = 1;
        mat[1][2] = v = Add(mod, v);
        mat[1][3] = mat[1][4] = M(1ll * v * v);
        mat[2][3] = mat[2][4] = Add(v, v);
        update(l, r, mat, 1, 1, n);
        mat.clear();
        mat[1][1] = mat[2][2] = mat[3][3] = mat[3][4] = mat[4][4] = 1;
        update(1, l - 1, mat, 1, 1, n);
        update(r + 1, n, mat, 1, 1, n);
        for(auto j : qs[i + 1]) ans[i + 1].push_back(query(j.first, j.second, 1, 1, n)[1][4]);
    }
    for(int i=1;i<=q;i++) cout<<Add(ans[qqs[i].q2][qqs[i].p2], mod - ans[qqs[i].q1][qqs[i].p1])<<'\n';
    return 0;
}
```


---

## 作者：Inui_Sana (赞：4)

先致敬 houzhe 学长经典：

>我看到我的队友写了个又臭又长的线段树，维护了一堆 tag，于是**一脚把他踹下去**，写了个**线段树维护矩阵**，然后就过了。

回到这题，题意即为求一段连续的版本 $[x,y]$ 中,所有版本的区间 $[l,r]$ 的值的平方和。

首先显然可以变成 $[1,y]$ 版本的答案减去 $[1,x]$ 版本的答案。然后变成一个历史版本和问题。解决历史版本和问题自然会想到维护矩阵。当然你打 tag 也是可以的，但是这样的话建议还是从矩阵的角度去推更新，否则很容易出问题。

具体地，SGT 上每个位置维护一个 $4\times 4$ 的矩阵，记录区间和，区间平方和，区间长度和区间历史版本和四个量，把 $\sum(a_i+k)^2$ 套路化地拆成 $\sum a_i^2+\sum a_i\times k+len\times k^2$，这也是一个矩阵很好维护的形式。每做完一次操作之后更新历史和即可。

细节不是很多，需要注意的有：

- tag 的矩阵初始值是单位矩阵而不是全 $0$ 矩阵。

- $a_i$ 和更新的 $x$ 都可能是负数。

结束了。跑的还挺快……吗？至少过了而且不是最劣解。/kk

code：

```cpp
int n,m,q,a[N],ans[N];
struct node{int l,r,x;}b[N];
struct Node{int l,r,s,id;};
vector<Node> g[N];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
struct SGT{
	struct mat{
		int a[4][4];
		mat(){mems(a,0);}
		il void reset(){mems(a,0);rep(i,0,3)a[i][i]=1;}
		il mat operator*(const mat &rhs)const{
			mat r;
			rep(k,0,3)rep(i,0,3)rep(j,0,3)r.a[i][j]=Mod(r.a[i][j],1ll*a[i][k]*rhs.a[k][j]%mod);
			return r;
		}
		il mat operator+(const mat &rhs)const{
			mat r;
			rep(i,0,3)rep(j,0,3)r.a[i][j]=Mod(a[i][j],rhs.a[i][j]);
			return r;
		}
	};
	struct Tnode{mat x,tag;}tr[N<<2];
	il void pushup(int o){tr[o].x=tr[o<<1].x+tr[o<<1|1].x;}
	il void reset(int o,mat &k){tr[o].x=tr[o].x*k,tr[o].tag=tr[o].tag*k;}
	il void pushdown(int o){reset(o<<1,tr[o].tag),reset(o<<1|1,tr[o].tag),tr[o].tag.reset();}
	void build(int l,int r,int o){
		tr[o].tag.reset();
		if(l==r)return tr[o].x.a[0][0]=Mod(a[l],mod),tr[o].x.a[0][1]=1ll*a[l]*a[l]%mod,tr[o].x.a[0][2]=1,void();
		int mid=(l+r)>>1;
		build(l,mid,o<<1),build(mid+1,r,o<<1|1);
		pushup(o);
	}
	void update(int l,int r,int o,int x,int y,mat k){
		if(l>=x&&r<=y)return reset(o,k);
		pushdown(o);
		int mid=(l+r)>>1;
		if(x<=mid)update(l,mid,o<<1,x,y,k);
		if(y>mid)update(mid+1,r,o<<1|1,x,y,k);
		pushup(o);
	}
	int query(int l,int r,int o,int x,int y){
		if(r<x||l>y)return 0;
		if(l>=x&&r<=y)return tr[o].x.a[0][3];
		pushdown(o);
		int mid=(l+r)>>1;
		return Mod(query(l,mid,o<<1,x,y),query(mid+1,r,o<<1|1,x,y));
	}
}T;
void Yorushika(){
	scanf("%d%d%d",&n,&m,&q),m++;
	rep(i,1,n)scanf("%d",&a[i]);
	rep(i,2,m)scanf("%d%d%d",&b[i].l,&b[i].r,&b[i].x);
	rep(i,1,q){
		int l,r,x,y;scanf("%d%d%d%d",&l,&r,&x,&y);
		g[x].eb((Node){l,r,-1,i}),g[y+1].eb((Node){l,r,1,i});
	}
	T.build(1,n,1),b[1]={1,1,0};
	SGT::mat x;x.reset();
	rep(i,1,m){
		SGT::mat tmp;int x=b[i].x;
		tmp.a[0][0]=1,tmp.a[0][1]=Mod(2ll*x%mod,mod);
		tmp.a[1][1]=1;
		tmp.a[2][0]=Mod(x,mod),tmp.a[2][1]=1ll*x*x%mod,tmp.a[2][2]=1;
		tmp.a[3][3]=1;
		T.update(1,n,1,b[i].l,b[i].r,tmp);
		tmp.reset(),tmp.a[1][3]=1;
		T.reset(1,tmp);
		for(Node j:g[i])ans[j.id]=Mod(ans[j.id],Mod(mod,T.query(1,n,1,j.l,j.r)*j.s));
	}
	rep(i,1,q)printf("%d\n",ans[i]);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：summ1t (赞：0)

和[比赛](https://www.luogu.com.cn/problem/P8868)有些相似之处，都是维护历史版本和，只不过这题可以用不卡常的矩阵做。

版本和是可以差分的，所以将 $[x,y]$ 的答案转化为 $[1,y]$ 减去 $[1,x-1]$ 区间的答案，接下来我们要做的就是查询区间历史平方版本和。

这是比较套路的，可以直接矩阵转移：维护区间长度 $len$，区间和 $s_1$，区间平方和 $s_2$，区间历史版本平方和 $S$，对于区间整体加 $x$，转移矩阵不难推出：

* $\begin{bmatrix}
 len & s_1 & s_2 &S
\end{bmatrix}\times \begin{bmatrix}
 1 & x & x^2 &x^2\\
0 & 1 & 2x & 2x\\
0 & 0& 1 & 1\\
0&0&0&1
\end{bmatrix}=\begin{bmatrix}len,s_1',s_2',S'\end{bmatrix}$

同时还要注意没有修改操作的区间，历史平方版本和也要改变：

* $\begin{bmatrix}
 len & s_1 & s_2 &S
\end{bmatrix}\times\begin{bmatrix}
 1 & 0 & 0 &0\\
0 & 1 & 0 & 0\\
0 & 0& 1 & 1\\
0&0&0&1
\end{bmatrix}=\begin{bmatrix}
 len & s_1 & s_2 &S'
\end{bmatrix}$

矩阵乘法具有结合律，线段树维护就好了，区间乘一个矩阵，询问区间矩阵和，这是好做的。

最后再提一点卡常的技巧：

* 快读快写啥的。
* 循环展开。
*  pushdown 时，如果懒标记是单位矩阵，一定要 return，可以大大减少运算量。
* 取模运算转化为减法,特别注意本题 $a_i,x_i$ 可能为**负数**，注意取模的正确姿势。
* 能不用 ```long long``` 就不用，只在计算时乘个 ```1ll```。
* 线段树维护的矩阵是 $1\times 4$ 的。

最后这个题就轻松过掉了，代码有点太长，就放剪贴板了。

[**code**](https://www.luogu.com.cn/paste/3n1vc6yv)

---

