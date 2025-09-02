# Summer Homework

## 题目描述

By the age of three Smart Beaver mastered all arithmetic operations and got this summer homework from the amazed teacher:

You are given a sequence of integers $ a_{1},a_{2},...,a_{n} $ . Your task is to perform on it $ m $ consecutive operations of the following type:

1. For given numbers $ x_{i} $ and $ v_{i} $ assign value $ v_{i} $ to element $ a_{xi} $ .
2. For given numbers $ l_{i} $ and $ r_{i} $ you've got to calculate sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316E3/095e734be6677a366eba0d190d121c644f5bca60.png), where $ f_{0}=f_{1}=1 $ and at $ i>=2 $ : $ f_{i}=f_{i-1}+f_{i-2} $ .
3. For a group of three numbers $ l_{i} $ $ r_{i} $ $ d_{i} $ you should increase value $ a_{x} $ by $ d_{i} $ for all $ x $ $ (l_{i}<=x<=r_{i}) $ .

Smart Beaver planned a tour around great Canadian lakes, so he asked you to help him solve the given problem.

## 样例 #1

### 输入

```
5 5
1 3 1 2 4
2 1 4
2 1 5
2 2 4
1 3 10
2 1 5
```

### 输出

```
12
32
8
50
```

## 样例 #2

### 输入

```
5 4
1 3 1 2 4
3 1 4 1
2 2 4
1 2 10
2 1 5
```

### 输出

```
12
45
```

# 题解

## 作者：ZolaWatle (赞：4)

## CF316E 题解

### 题目大意

维护一个数据结构，支持以下三种操作：

1. ```1 x v```：将 $a_x$ 赋值为 $v$。
2. ```2 l r```：求以下式子的值：$\sum\limits^{r-l}_{x=0}{f_x\cdot a_{l+x} \text{ mod } 10^9 }$
3. ```3 l r d```： 使区间 $[l, r]$ 内所有元素加上 $d$。

$f$ 数组的定义如下：

 $$f_i = \begin{cases}
 1, i=0/1\\
 f_{i-2}+f_{i-1}
 \end{cases}$$

### 解题思路

可以想到使用线段树维护单点修改和区间加法，瓶颈在于区间的合并。

我们设 $ s_0 = f_0 \cdot a_0 + f_1\cdot a_1 +...+ f_n\cdot a_n, s_1 = f_1\cdot a_0 + f_2\cdot a_1 +...+ f_{n+1}\cdot a_n $，以此类推。

概括地讲，我们设：
$$
s_i = \sum\limits_{j=0}^{n}{f_{i+j}\cdot a_j}
$$

#### 引理证明

我们发现，序列 $f$ 实际上是一个斐波那契数列。将思路往这上面靠，我们发现，当 $ i\geq 2 $ 时，$s$ 满足 $ s_i = s_{i-1} + s_{i-2} $。下面给出这条引理的证明：
$$
s_{i-2} + s_{i-1} =\sum\limits_{j=0}^n{f_{i+j-2}\cdot a_j} + \sum\limits_{j=0}^n{f_{i+j-1}\cdot a_j}
$$

$$
s_{i-2} + s_{i-1} = \sum\limits_{j=0}^n{(f_{i+j-2}+f_{i+j-1})\cdot a_j}
$$

$$
s_{i-2} + s_{i-1} = \sum\limits_{j=0}^n{f_{i+j}\cdot a_j}
$$

即为：$ s_{i-2} + s_{i-1} = s_i $，证毕。

然而在进行询问时，上面的 $n$ 是会不断发生改变的。很显然，我们不能将所有的情况全搬进线段树里面维护。我们想到，斐波那契有加速递推，那这个 $s$ 是否也能由它的前几项推出呢？~~~（好吧其实和加速递推没什么关系）~~~

我们猜想，对于 $ \forall i \in [2, n] $，其 $s_i$ 都可以由 $s_0$ 和 $s_1$ 推出。我们设 $x = s_0, y = s_1$，首先，很显然地，我们得到 $ s_2 = s_0 + s_1 = x + y = f_0\cdot x + f_1\cdot y $。

考虑对其进行更进一步的推广。
$$
\because f_0 = f_1
$$

$$
\therefore f_2 = f_0 + f_1 =2f_1
$$

$$
\therefore s_3 = s_1 + s_2 = f_1\cdot y + (f_0\cdot x + f_1\cdot y) = f_1\cdot x + f_2\cdot y
$$

同理可得：
$$
s_4 = s_2 + s_3 = (f_0\cdot x + f_1\cdot y) + (f_1\cdot x + f_2\cdot y) = f_2\cdot x + f_3\cdot y
$$

$$
s_5 = s_3 + s_4 = (f_1\cdot x + f_2\cdot y) + (f_2\cdot x + f_3\cdot y) = f_3\cdot x + f_4\cdot y
$$

$$
\cdots
$$

由数学归纳法，我们知道：对于 $\forall i\in [2, n]$，$s_i = f_{i-2}\cdot s_0 + f_{i-1}\cdot s_1$。

接下来我们考虑如何将这个结论运用到线段树中去维护信息。

#### 与线段树的结合

##### 建树操作

由前面的结论，我们发现对于每一个节点，我们只需要维护其 $s_0$ 和 $s_1$ 的值。对于叶子节点，我们发现它的区间长度为 $1$，因此，$s0, s1$ 的初值都为 $a_p\cdot f_0$，即 $a_p$，$p$ 为叶子节点编号。这里面向上传递的操作后面会讲。

```cpp
inline void Build(int p,int l,int r)
{
	sgt[p].ls=l,sgt[p].rs=r,sgt[p].len=r-l+1;
	if(l==r)
	{
		sgt[p].s1=sgt[p].s2=a[l];
		return;
	}
	re mid=l+r>>1;
	Build(p<<1,l,mid);
	Build(p<<1|1,mid+1,r);
	pushup(p);
}
```

##### 询问答案

这个部分比较简单。我们设当前询问的区间是 $[L, R]$。我们注意到，线段树的询问函数是递归进行的，因此，当询问到子区间 $[l, r]$ 时，应该返回的值是 $ f_{l-L+1}\cdot a_l + \cdots + f_{r-L+1}\cdot a_r $。一个值得注意的细节是，如果当前子区间的左端点与原区间的左端点重合时，我们称这个子区间并未偏移。对于这样的区间，只需返回代表子区间的节点的 $s_0$ 值即可。

代码中，$calc$ 函数求的是当前节点 $s_k$ 的值。

```cpp
inline ll query(int p,int l,int r)
{
	if(sgt[p].ls>=l&&sgt[p].rs<=r)
	{
		re k=sgt[p].ls-l;
		if(!k) return sgt[p].s1;
		else return calc(p,k);
	}
	pushdown(p);
	re mid=sgt[p].ls+sgt[p].rs>>1;
	ll ret=0;
	if(l<=mid) ret=(ret+query(p<<1,l,r))%mod;
	if(r>mid) ret=(ret+query(p<<1|1,l,r))%mod;
	return ret;
}
```

##### 单点修改

跟普通的线段树一样，此处不再赘述。记得修改时要将这个节点上的懒标记清除。

```cpp
inline void change(int p,int x,ll v)
{
	if(sgt[p].ls==sgt[p].rs)
	{
		sgt[p].s1=sgt[p].s2=v;
		sgt[p].tag=0;
		return;
	}
	pushdown(p);
	re mid=sgt[p].ls+sgt[p].rs>>1;
	if(x<=mid) change(p<<1,x,v);
	else change(p<<1|1,x,v);
	pushup(p);
}
```

##### 区间加法

假设令区间 $ [l, r] $ 内的所有元素增加 $d$。

手玩一下，我们将增加后的 $s_0$ 和先前的 $s_0$ 做差，得出增加量 :
$$
\Delta_{s_0} = f_1\cdot d + f_2\cdot d + \cdots + f_{r-l+1}\cdot d = (f_1 + f_2 + \cdots + f_{r-l+1})\cdot d
$$
我们发现，只需要先预处理出 $f$ 数组的前缀和，即可维护增加值对答案的贡献。$s_1$ 的增加量与 $s_0$ 类似，在此不做赘述。

```cpp
inline void add(int p,int l,int r,ll d)
{
	if(sgt[p].ls>=l&&sgt[p].rs<=r)
	{
		sgt[p].tag=(sgt[p].tag+d)%mod;
		sgt[p].s1=(sgt[p].s1+sf[sgt[p].len-1]*d%mod)%mod;
		sgt[p].s2=(sgt[p].s2+(sf[sgt[p].len]-1ll)*d%mod)%mod;
		return;
	}
	pushdown(p);
	re mid=sgt[p].ls+sgt[p].rs>>1;
	if(l<=mid) add(p<<1,l,r,d);
	if(r>mid) add(p<<1|1,l,r,d);
	pushup(p);
}
```

##### 上传操作

依然先考虑对于 $s_0$ 的维护。

我们将其分为两个部分的和，其一为左儿子的 $s_0$；其二为**右儿子的左儿子长度的 $s_i$**。令当前节点为 $p$，其维护的区间为 $[l, r]$，其左儿子为 $ls$，右儿子为 $rs$。我们令 $A$ 式为“其一”，令 $B$ 式为“其二”。为了表述方便，我们令 $mid = \frac{l+r}{2}$，表示节点 $p$ 的区间中点（即左右儿子的分界）。考虑对以上转移进行如下证明：

$ A = s_0 [ p ] = f_1\cdot a_l + f_2\cdot a_{l+1} + \cdots + f_{r-l+1}\cdot a_r $，

$ B = s_0[ls] + s_{mid-l+1}[rs]$。

$   \ \ \ = (f_1\cdot a_l + f_2\cdot a_{l+1} + \cdots + f_{mid-l+1}\cdot a_{mid}) + (f_{(mid+1)-l+1)}\cdot a_{mid+1} + \cdots + f_{r-l+1}\cdot a_r)  $

$ \ \ \ = f_1\cdot a_l + f_2\cdot a_{l+1} + \cdots + f_{r-l+1}\cdot a_r $

发现 $ A = B $，即 $ s_0[p] = s_0[ls] + s_{mid-l+1}[rs] $。

至此，我们完成了上传操作正确性的证明。

```cpp
inline void pushup(int p)
{
	sgt[p].s1=(sgt[p<<1].s1+calc(p<<1|1,sgt[p<<1].len))%mod;
	sgt[p].s2=(sgt[p<<1].s2+calc(p<<1|1,sgt[p<<1].len+1))%mod;
}
```

##### 下传操作

普普通通的一个 $\text{pushdown}$，类比一下区间加法的操作即可。

```cpp
inline void pushdown(int p)
{
	if(!sgt[p].tag) return;
	rl t=sgt[p].tag;
	sgt[p<<1].tag=(sgt[p<<1].tag+t)%mod;
	sgt[p<<1|1].tag=(sgt[p<<1|1].tag+t)%mod;
	sgt[p<<1].s1=(sgt[p<<1].s1+sf[sgt[p<<1].len-1]*t%mod)%mod;
	sgt[p<<1].s2=(sgt[p<<1].s2+(sf[sgt[p<<1].len]-1ll)*t%mod)%mod;
	sgt[p<<1|1].s1=(sgt[p<<1|1].s1+sf[sgt[p<<1|1].len-1]*t%mod)%mod;
	sgt[p<<1|1].s2=(sgt[p<<1|1].s2+(sf[sgt[p<<1|1].len]-1ll)*t%mod)%mod;
	sgt[p].tag=0;
}
```

#### 注意事项

至此，我们清楚了如何将线段树与先前的引理相结合，运用到这个问题中，本题已经可以解决。

但我们还应该注意一下几点细节：

- 注意数组 $f$ 和 $sf$ 的边界，它们是不同的。
- 前面已经提到，我们的引理成立，当且仅当 $i\geq 2$。因此，在计算 $s_i$ 时，我们应该判断其是否越界。
- $\text{long long}$!

#### 完整代码

为了避免篇幅过长，完整代码就不在这里贴出来了，如有需要请走[这边](https://www.luogu.com.cn/paste/e2qxmg9y)。

感谢阅读！

---

## 作者：zesqwq (赞：2)

# CF316E3 Summer Homework 题解

## Analysis

看到了 Fibonacci，而且又是要维护序列操作，不难想到用线段树+矩阵乘法维护。

先考虑没有操作 $3$ 的情况。

我们令 $A = \begin{bmatrix} 1&1\\1&0 \end{bmatrix}$，那么询问就是问我们 $\sum_{i=0}^{r-l}a_{l+x}A^i$ 所对应的矩阵。

我们让线段树的一个节点存该节点对应区间的大小 `siz` 和答案矩阵 `w`，那么当前节点 $u$ 的答案矩阵就为 $w_u=w_{lson} + A^{siz_{lson}}w_{rson}$。
这个做法的成正确性显然。

然后就是一个预处理快速幂，和维护单点修改，区间查询的平凡线段树了。

然后考虑带上操作 $3$。

我们发现给区间 $[l,r]$ 加上 $v$ 实际上对答案矩阵 $w$ 的影响就是 $w=w+v\sum_{i=0}^{siz-1}A^i$ 。

这样我们只需要预处理出 $\sum_{i=0}^xA^i$ 就可以在线段树上打标记了。

时间复杂度 $O(n\log n)$。

## code

```cpp
const long long p = 1e9;
struct Matrix {
    long long mat[2][2];
    inline Matrix operator*(Matrix b) {
        Matrix c;
        c.mat[0][0] = (mat[0][0] * b.mat[0][0] + mat[0][1] * b.mat[1][0]) % p;
        c.mat[0][1] = (mat[0][0] * b.mat[0][1] + mat[0][1] * b.mat[1][1]) % p;
        c.mat[1][0] = (mat[1][0] * b.mat[0][0] + mat[1][1] * b.mat[1][0]) % p;
        c.mat[1][1] = (mat[1][0] * b.mat[0][1] + mat[1][1] * b.mat[1][1]) % p;
        return c;
    }
    inline Matrix operator+(Matrix b) {
        Matrix c;
        c.mat[0][0] = (mat[0][0] + b.mat[0][0]) % p;
        c.mat[0][1] = (mat[0][1] + b.mat[0][1]) % p;
        c.mat[1][0] = (mat[1][0] + b.mat[1][0]) % p;
        c.mat[1][1] = (mat[1][1] + b.mat[1][1]) % p;
        return c;
    }
    inline Matrix operator^(long long v) const {
        Matrix c;
        c.mat[0][0] = (mat[0][0] * v) % p;
        c.mat[0][1] = (mat[0][1] * v) % p;
        c.mat[1][0] = (mat[1][0] * v) % p;
        c.mat[1][1] = (mat[1][1] * v) % p;
        return c;
    }
    inline bool operator==(Matrix b) { return mat[0][0] == b.mat[0][0] && mat[1][0] == b.mat[1][0] && mat[0][1] == b.mat[0][1] && mat[1][1] == b.mat[1][1]; }
};
const Matrix A = {1, 1, 1, 0}, I = {1, 0, 0, 1};
const int N = 2e5 + 10;
Matrix mi[N], sum[N];
inline Matrix qpw(int v) { return mi[v]; }
struct SegmentTree {
    struct Node {
        Matrix w;
        int siz;
    } w[N << 2];
    long long lzy[N << 2];
    inline void pushup(Node &u, Node ls, Node rs) {
        u.siz = ls.siz + rs.siz;
        u.w = ls.w + mi[ls.siz] * rs.w;
    }
    void build(int u, int L, int R) {
        if (L == R) {
            w[u].siz = 1;
            long long v;
            read(v), w[u].w = (I ^ v);
            return;
        }
        int M = L + R >> 1;
        build(u << 1, L, M), build(u << 1 | 1, M + 1, R);
        pushup(w[u], w[u << 1], w[u << 1 | 1]);
    }
    inline void maketag(int u, long long v) { w[u].w = w[u].w + (sum[w[u].siz - 1] ^ v), lzy[u] += v; }
    inline void pushdown(int u) {
        if (lzy[u]) maketag(u << 1, lzy[u]), maketag(u << 1 | 1, lzy[u]), lzy[u] = 0;
    }
    void update(int u, int L, int R, int x, int v) {
        if (L == R) return void(w[u].w = (I ^ v));
        int M = L + R >> 1;
        pushdown(u);
        if (x <= M)
            update(u << 1, L, M, x, v);
        else
            update(u << 1 | 1, M + 1, R, x, v);
        pushup(w[u], w[u << 1], w[u << 1 | 1]);
    }
    void update(int u, int L, int R, int l, int r, int v) {
        if (L >= l && R <= r) return maketag(u, v);
        if (L > r || R < l) return;
        int M = L + R >> 1;
        pushdown(u);
        update(u << 1, L, M, l, r, v), update(u << 1 | 1, M + 1, R, l, r, v);
        pushup(w[u], w[u << 1], w[u << 1 | 1]);
    }
    Node query(int u, int L, int R, int l, int r) {
        if (L >= l && R <= r) return w[u];
        int M = L + R >> 1;
        pushdown(u);
        if (r <= M) return query(u << 1, L, M, l, r);
        if (M < l) return query(u << 1 | 1, M + 1, R, l, r);
        Node ans;
        pushup(ans, query(u << 1, L, M, l, r), query(u << 1 | 1, M + 1, R, l, r));
        return ans;
    }
} seg;
int n, m;
int main() {
    read(n), read(m);
    int op, l, r, v;
    mi[0] = I, mi[1] = A;
    for (int i = 2; i < N; i++) mi[i] = mi[i - 1] * A;
    sum[0] = I;
    for (int i = 1; i < N; i++) sum[i] = mi[i] + sum[i - 1];
    seg.build(1, 1, n);
    Matrix ans;
    while (m--) {
        read(op), read(l), read(r);
        if (op == 1)
            seg.update(1, 1, n, l, r);
        else if (op == 2)
            ans = seg.query(1, 1, n, l, r).w, write((ans.mat[0][1] + ans.mat[1][1]) % p), putc('\n');
        else
            read(v), seg.update(1, 1, n, l, r, v);
    }
    return 0;
}

---

## 作者：Starrykiller (赞：1)

**约定：$\boldsymbol{\textcolor{red}{f_0=0,f_1=1}}$。**

建议升紫/kk（

我们有性质：

$$f_{n+m}=f_nf_m+f_{n-1}f_{m-1}$$

单个区间的信息是 $\sum_{i=1}^{r-l+1} f_i\cdot a_{l+i-1}$。

这启示我们：记录每个区间的 $\sum f_i\cdot a_{l+i-1}$ 和 $\sum f_{i-1}\cdot a_{l+i-1}$，然后直接合并信息即可。

打标记和信息合并是平凡的。

然后就做完了，时间复杂度 $\Theta(m\log n)$。[代码](https://codeforces.com/contest/316/submission/271322671)。

---

## 作者：shinkuu (赞：1)

[先阅读：E2 sol](https://www.luogu.com.cn/blog/Kato-Megumi/solution-cf316e2)

区间加有点难做，但此时可以手算找一下规律：

一开始的矩阵是这样的：

$$\begin{bmatrix}0&1&0\\1&1&a_i\\0&0&1\end{bmatrix}$$

乘上一个位置 $i+1$ 的矩阵后：

$$\begin{bmatrix}1&1&a_{i+1}\\1&2&a_i+a_{i+1}\\0&0&1\end{bmatrix}$$

乘上一个位置 $i+2$ 的矩阵后：

$$\begin{bmatrix}1&2&a_{i+1}+a_{i+2}\\2&3&a_i+a_{i+1}+2\times a_{i+2}\\0&0&1\end{bmatrix}$$

往后推到 $i+k$，可以发现 $(0,2)$ 位置相当于是 $\sum_{j=i+1}^k a_j\times f_{j-i}$，$(1,2)$ 位置相当于是 $\sum_{j=i}^k a_j\times f_{j-i+1}$。每次区间加 $d$ 相当于 $(0,2)$ 位置加上 $d\times s_{r-l}$，$(1,2)$ 位置加上 $d\times s_{r-l+1}$，其中 $s_i$ 为斐波那契数列第 $i$ 项的前缀和。

代码还算好写。

code：

```cpp
int n,m,e[N],f[N],s[N],tag[N<<2];
inline void Mod(int &x,int y){
	x=x+y>=mod?x+y-mod:x+y;
}
struct mat{
	int e[3][3];
	mat(){
		mems(e,0);
	}
	mat operator*(const mat &tmp)const{
		mat ret;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++)
				ret.e[i][j]=(1ll*e[i][0]*tmp.e[0][j]+1ll*e[i][1]*tmp.e[1][j]+1ll*e[i][2]*tmp.e[2][j])%mod;
		}
		return ret;
	}
}tr[N<<2],base;
inline void pushup(int o){
	tr[o]=tr[o<<1]*tr[o<<1|1];
}
inline void reset(int l,int r,int o,int k){
	Mod(tr[o].e[0][2],1ll*s[r-l]*k%mod);
	Mod(tr[o].e[1][2],1ll*s[r-l+1]*k%mod);
	tag[o]=(tag[o]+k)%mod;
}
inline void pushdown(int l,int r,int o){
	int mid=(l+r)>>1;
	reset(l,mid,o<<1,tag[o]);
	reset(mid+1,r,o<<1|1,tag[o]);
	tag[o]=0;
}
void build(int l,int r,int o){
	if(l==r){
		tr[o].e[0][1]=tr[o].e[1][0]=tr[o].e[1][1]=tr[o].e[2][2]=1;
		tr[o].e[1][2]=e[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
}
void update(int l,int r,int o,int x,int y,int k,bool op){
	if(l>=x&&r<=y){
		if(op)
			reset(l,r,o,k);
		else
			tr[o].e[1][2]=k;
		return;
	}
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(x<=mid)
		update(l,mid,o<<1,x,y,k,op);
	if(y>mid)
		update(mid+1,r,o<<1|1,x,y,k,op);
	pushup(o);
}
mat query(int l,int r,int o,int x,int y){
	if(l>=x&&r<=y)
		return tr[o];
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(x<=mid&&y>mid)
		return query(l,mid,o<<1,x,y)*query(mid+1,r,o<<1|1,x,y);
	if(x<=mid)
		return query(l,mid,o<<1,x,y);
	return query(mid+1,r,o<<1|1,x,y);
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		e[i]=read();
	f[0]=s[0]=0,f[1]=s[1]=1;
	for(int i=2;i<=n;i++){
		Mod(f[i],f[i-2]+f[i-1]);
		Mod(s[i],f[i]+s[i-1]);
	}
	base.e[0][1]=1;
	build(1,n,1);
	for(int i=1,op,x,y,k;i<=m;i++){
		op=read(),x=read(),y=read();
		if(op==1)
			update(1,n,1,x,x,y,0);
		if(op==2)
			printf("%d\n",(base*query(1,n,1,x,y)).e[0][2]);
		if(op==3){
			k=read();
			update(1,n,1,x,y,k,1);
		}
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

tips：如果被卡常可以尝试手写取模，还要注意 tag 数组不要越界。

---

## 作者：liujiaxi123456 (赞：0)

#### 思路：
区修区查，考虑线段树，先不考虑修改，考虑查询。

发现 pushup 时左儿子的答案可以直接继承。

但右儿子的系数不对，考虑推式子：
- 应该的答案：$\sum_{i=mid+1}^{r} = f_{i-l}\cdot a_i$

有边界不好推式子，考虑先退去掉边界的情况：
- 设 $g_i = \sum_{j=0}^{n-1}f_{i+j}\cdot a_{j+1}$
- 则有 $g_{i-1}+g_{i-2}=\sum_{j=0}^{n-1}(f_{i+j-1}+f_{i+j-2})\cdot a_{j+1} = \sum_{j=0}^{n-1}f_{i+j}\cdot a_{j+1} = g_i$
- $g_i = g_{i-1}+g_{i-2}=2g_{i-2}+g_{i-3}=3g_{i-3}+2g_{i-4}=\cdots=f_{i-j}\cdot g_{j}+f_{i-j-1}\cdot g_{j-1}=f_{i-1}\cdot g_1+f_{i-2}\cdot g_0$

考虑把式子带入线段树中维护：
- 相当于对线段树上的每个节点维护它的 $g_0,g_1$。
- pushup 时：
  + $g_{0, t} = g_{0, ls} + g_{mid-l+1, rs}$
  + $g_{1, t} = g_{1, ls} + g_{mid-l+2, res}$

现在考虑区间加：
- 写式子，设区间加 $d$：
  + $ \Delta_{g_0} = f_0\cdot d + f_1\cdot d + \cdots + f_{r-l}\cdot d = sumf_{r-l}\cdot d $
  + $\Delta_{g_1} = f_1\cdot d + f_2\cdot d + \cdots + f_{r-l+1}\cdot d = (sumf_{r-l+1}-f_0)\cdot d$
- 预处理 $f$ 的前缀和即可。
#### Code：
~~这是一个比次优解快了近两倍的代码。~~
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 2e5+5, MOD = 1e9;
int N;

class SegmentTree {
private:
	ll f[Maxn], sumf[Maxn];
	struct Segment { int tag; ll g0, g1; } seg[Maxn*4];
	inline int calc(int t, int k) {
		return (!k ?seg[t].g0 :(k==1 ?seg[t].g1 :(f[k-1]*seg[t].g1 + f[k-2]*seg[t].g0)%MOD));
	}
	inline void pushup(int t, int llen) {
		seg[t].g0 = (seg[t<<1].g0 + calc(t<<1|1, llen)) %MOD;
		seg[t].g1 = (seg[t<<1].g1 + calc(t<<1|1, llen+1)) %MOD;
	}
	inline void Add(int t, int len, int d) {
		seg[t].tag = (seg[t].tag + d) %MOD;
		seg[t].g0 = (seg[t].g0 + sumf[len-1]*d) %MOD;
		seg[t].g1 = (seg[t].g1 + sumf[len]*d-d) %MOD; // 差分掉 f[0]
	}
	inline void pushdown(int t, int l, int r) {
		if(seg[t].tag) {
			int mid = (l+r)>>1;
			Add(t<<1, mid-l+1, seg[t].tag);
			Add(t<<1|1, r-mid, seg[t].tag);
			seg[t].tag = 0;
		}
	}
	inline void Change(int t, int l, int r, int pos, int k) {
		if(l == r)	return seg[t].g0 = seg[t].g1 = k, void();
		int mid = (l+r)>>1; pushdown(t, l, r);
		if(pos <= mid)	Change(t<<1, l, mid, pos, k);
		else	Change(t<<1|1, mid+1, r, pos, k);
		pushup(t, mid-l+1);
	}
	inline ll Query(int t, int l, int r, int L, int R) {
		if(r<L || R<l)	return 0;
		if(L<=l && r<=R)	return calc(t, l-L);
		int mid = (l+r)>>1; pushdown(t, l, r);
		return Query(t<<1, l, mid, L, R) + Query(t<<1|1, mid+1, r, L, R);
	} 
	inline void Modify(int t, int l, int r, int L, int R, int d) {
		if(r<L || R<l)	return ;
		if(L<=l && r<=R)	return Add(t, r-l+1, d);
		int mid = (l+r)>>1; pushdown(t, l, r);
		Modify(t<<1, l, mid, L, R, d), Modify(t<<1|1, mid+1, r, L, R, d);
		pushup(t, mid-l+1);
	}
	inline void Build(int t, int l, int r, int *a) {
		if(l == r)	return seg[t].g0 = seg[t].g1 = a[l], void();
		int mid = (l+r)>>1; 
		Build(t<<1, l, mid, a), Build(t<<1|1, mid+1, r, a);
		pushup(t, mid-l+1);
	}
public:
	inline void init(int *a, int N) {
		f[0] = f[1] = 1, sumf[0] = 1, sumf[1] = 2;
		for(int i=2; i<=N; i++) {
			f[i] = (f[i-1] + f[i-2]) %MOD;
			sumf[i] = (sumf[i-1] + f[i]) %MOD;
		}
		Build(1, 1, N, a);
	}
	inline void Change(int pos, int y) { Change(1, 1, N, pos, y); }
	inline int Query(int l, int r) { return Query(1, 1, N, l, r) %MOD; }
	inline void Modify(int l, int r, int d) { Modify(1, 1, N, l, r, d); }
} seg;

namespace Josh_zmf {
	
	int Q, a[Maxn];

	inline int main() {
		cin>> N>> Q;
		for(int i=1; i<=N; i++)	cin>> a[i];
		seg.init(a, N);
		for(int opt, l, r, x, y; Q--; ) {
			cin>> opt;
			if(opt == 1) {
				cin>> x>> y;
				seg.Change(x, y);
			} else if(opt == 2) {
				cin>> l>> r;
				cout<< seg.Query(l, r)<< '\n';
			} else {
				cin>> l>> r>> x;
				seg.Modify(l, r, x);
			}
		}
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2300}$
---
### 解题思路：

入门数据结构题。

用线段树维护 $a=\sum_{i=l}^r a_if_{i-l}$ 和 $b=\sum_{i=l}^r a_if_{i-l+1}$，其中 $f_i$ 表示斐波那契数列的第 $i$ 项。单点修改和区间加都是平凡的，询问合并区间时要求 $\sum_{i=l}^r a_i f_{i-l+x}$。

容易发现 $a+b$ 就是 $\sum_{i=l}^r a_if_{i-l+2}$ 以此类推就得到了所有的项。

这个过程有两种优化思路，一种是和通常的斐波那契求法一样，用快速幂算出一个用 $a$ 和 $b$ 表示的式子，另一种是直接预处理出系数。前者用于值域较大的情况，后者用于值域较小的时候。本题 $10^5$ 直接预处理就好了。

具体地 $f_{n}=f_{n-i}f_{i}+f_{n-i-1}f_{i-1}$，也就是 $\sum_{i=l}^ra_if_{i-l+x}=f_{x-1}\sum_{i=l}^r a_if_{i-l+1}+f_{x-2}\sum_{i=l}^r a_if_{i-l}$。

证明直接归纳法，先用 $f_n=f_{n-1}f_1+f_{n-2}f_0$ 奠基，归纳步骤拆 $f_{n-i}f_i$ 项为 $f_if_{n-i-1}+f_if_{n-i-2}$，合并得到 $f_{i+1}f_{n-i-1}+f_if_{n-i-2}$ 恰好是下一项 $i+1$ 的形式。

---
数组不要开小，注意用 $\text{long long}$ 存。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
const int MAXN=800005,MOD=1000000000;
int n,m,f[MAXN],x[MAXN],lazy[MAXN],a[MAXN],b[MAXN],sum[MAXN],X,y,z,t;
int plus(int x,int a,int b){
	if(x==0)return a;
	if(x==1)return b;
	return ((f[x-2]*a)%MOD+(f[x-1]*b)%MOD)%MOD;
}
void pushdown(int now,int l,int r){
	if(lazy[now]==0)return;
	
	int mid=l+r>>1;
	lazy[now*2]=(lazy[now*2]+lazy[now])%MOD;
	lazy[now*2+1]=(lazy[now*2+1]+lazy[now])%MOD;
	
	a[now*2]=(a[now*2]+sum[mid-l]*lazy[now])%MOD;
	b[now*2]=(b[now*2]+(sum[mid-l+1]-1)*lazy[now])%MOD;
	
	a[now*2+1]=(a[now*2+1]+sum[r-mid-1]*lazy[now])%MOD;
	b[now*2+1]=(b[now*2+1]+(sum[r-mid]-1)*lazy[now])%MOD;
	lazy[now]=0;
}
void pushup(int now,int l,int r){
	int mid=l+r>>1;
	a[now]=(a[now*2]+plus(mid-l+1,a[now*2+1],b[now*2+1]))%MOD;
	b[now]=(b[now*2]+plus(mid-l+2,a[now*2+1],b[now*2+1]))%MOD;
}
void build(int now,int l,int r){
	if(l==r){
		a[now]=f[0]*x[l];
		b[now]=f[1]*x[l];
		return;
	}
	int mid=(l+r)/2;
	build(now*2,l,mid);
	build(now*2+1,mid+1,r);
	pushup(now,l,r);
}
void work1(int now,int l,int r,int x,int num){//单点修改 
	if(l==r){
		a[now]=b[now]=num;
		return;
	}
	pushdown(now,l,r);
	int mid=l+r>>1;
	if(x<=mid)work1(now*2,l,mid,x,num);
	else work1(now*2+1,mid+1,r,x,num);
	pushup(now,l,r);
}
void work3(int now,int l,int r,int L,int R,int num){//区间加 
	if(L<=l&&r<=R){
		lazy[now]=(lazy[now]+num)%MOD;
		a[now]=(a[now]+sum[r-l]*num)%MOD;
		b[now]=(b[now]+(sum[r-l+1]-1)*num)%MOD;
		return;
	}
	pushdown(now,l,r);
	int mid=l+r>>1;
	if(L<=mid)work3(now*2,l,mid,L,R,num);
	if(R>mid)work3(now*2+1,mid+1,r,L,R,num);
	pushup(now,l,r);
}
int query(int now,int l,int r,int L,int R){
	if(L<=l&&r<=R){
		if(l==L)return a[now];
		if(l==L+1)return b[now];
		return plus(l-L,a[now],b[now]);
	}
	pushdown(now,l,r);
	int mid=l+r>>1;
	int ans=0;
	if(L<=mid)ans+=query(now*2,l,mid,L,R);
	if(R>mid)ans+=query(now*2+1,mid+1,r,L,R);
	return ans%MOD;
}
signed main(){
	f[0]=f[1]=1;
	for(int i=1;i<=200000;i++)f[i]=(f[i-1]+f[i-2])%MOD;
	sum[0]=1;
	for(int i=1;i<=200000;i++)sum[i]=(sum[i-1]+f[i])%MOD;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&x[i]);
	build(1,1,n);
	while(m--){
		scanf("%lld",&t);
		if(t==1){
			scanf("%lld%lld",&X,&y);
			work1(1,1,n,X,y);
		}
		if(t==2){
			scanf("%lld%lld",&X,&y);
			printf("%lld\n",query(1,1,n,X,y)%MOD);
		}
		if(t==3){
			scanf("%lld%lld%lld",&X,&y,&z);
			work3(1,1,n,X,y,z);
		}
	}
	return 0;
}
```


---

