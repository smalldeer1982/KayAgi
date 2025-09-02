# [EPXLQ2024 fall round] 神奇磁铁

## 题目背景


lzy 给了 Cute_QiQi 很多组神奇的磁铁。

注：想拿到**快速 AK 变换奖**请在代码注释部分写明本题代码正确性证明。

## 题目描述

一组神奇的磁铁由 $2x$ 个磁铁排成一排组成，编号 $1,2,\dots,2x$，有激活和未激活两种状态。它们与普通的磁铁不同，不会简单地吸在一起。对于一组磁铁，当且仅当存在 $y \in [1,x]$，使得不存在两个激活的磁铁满足两者之间的距离为 $y$，整组磁铁才会吸在一起。不同组的磁铁之间不相互影响。

对于编号为 $i,j$ 的两个磁铁，它们之间的距离为 $|i-j|$。具体地，当 $x=2$ 时，磁铁组为 $\{1,2,3,4\}$。当激活的磁铁为 $\{1,2\}$ 时，整组磁铁可以吸在一起，因为对于 $y=2$，不存在两个磁铁之间的距离为 $2$。而激活的磁铁为 $\{1,2,3\}$ 时整组磁铁不能吸在一起。

lzy 给了 Cute_QiQi $n$ 组磁铁。现在，Cute_QiQi 希望把这 $n$ 组磁铁排成一排作为装饰，同组磁铁堆在一起。未被吸在一起的磁铁不便于摆放，因此，Cute_QiQi 希望所有的磁铁组内的磁铁都吸在一起。在此基础上，Cute_QiQi 希望激活**尽可能多**的磁铁。

另外，有时 lzy 会给 Cute_QiQi 一些额外的磁铁。

磁铁实在是太多了，以至于 Cute_QiQi 计算不出她最多能激活多少磁铁。因此，她希望你帮她写一个程序，支持下面两种操作：

- `1 l r x`，表示 lzy 给 $[l,r]$ 内所有的磁铁组添加了 $2x$ 个磁铁；
- `2 l r`，表示 Cute_QiQi 想知道在激活最多磁铁的情况下，$[l,r]$ 内的磁铁组总共有多少个磁铁被激活。

## 说明/提示

### 样例解释

初始时对应的激活磁铁的最大数量依次为 $1,1,5,6,1,5$。

进行修改操作后，对应的激活磁铁最大数量依次为 $4,4,8,6,1,5$。

可以证明，不可能再激活更多的磁铁。

### 数据规模与约定

**本题采用捆绑测试。**

设 $v$ 表示任意时刻，磁铁数最多的磁铁组内磁铁的数量。

| $\text{Subtask}$ | $n \le$ | $q \le$ | $v \le$ | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $0$ | $1000$ | $1000$ | $20$ | $10$ |
| $1$ | $1000$ | $1000$ | $10^9$ | $15$ |
| $2$ | $5 \times 10^5$ | $5 \times 10^5$ | $20$ | $10$ |
| $3$ | $5 \times 10^5$ | $5 \times 10^5$ | $5000$ | $25$ |
| $4$ | $5 \times 10^5$ | $5 \times 10^5$ | $10^9$ | $40$ |

对于所有数据，保证 $1 \le n,q \le 5 \times 10^5, 1 \le l \le r \le n, 1 \le v,a_i \le 10^9, -10^9 \le x \le 10^9$。

## 样例 #1

### 输入

```
6 6
1 1 4 5 1 4
2 1 6
1 1 3 2
2 1 4
2 1 6
1 1 3 -2
2 1 6```

### 输出

```
19
22
28
19```

# 题解

## 作者：ARIS2_0 (赞：5)

### 前言

好神奇的题面，赛时看了半天才看懂。

### 简化题意

设 $f(x)$ 为拥有 $x$ 块磁铁时，最大的能够激活的磁铁数量。

则本题题意即为：

给定长度为 $n$ 的数组 $a$，第一种操作将区间 $[l,r]$ 加上 $x$，第二种操作询问 $\sum\limits_{i=l}^rf(2\times i)$。

### 解题思路

考虑计算 $f(2\times i)$。由于要求有一个 $y\in[1,i]$ 使得没有任意两个激活的磁铁的距离为 $y$，不难发现，对于一个固定的 $y$，激活磁铁的最优策略一定是激活 $y$ 个，不激活 $y$ 个，再激活 $y$ 个，以此类推，直到第 $2\times i$ 个磁铁。

考虑把磁铁的激活构造为如下形式：设 $pos=\lceil\frac{2\times i}{3}\rceil$，我们采用前面激活 $pos$ 个，中间不激活 $pos$ 个，最后激活 $2\times i-2\times pos$ 个，总激活个数为 $2\times i-pos=2\times i-\lceil\frac{2\times i}{3}\rceil=\lfloor\frac{4\times i}{3}\rfloor=i+\lfloor\frac{i}{3}\rfloor$。

以下为证明：

- 若 $pos=\lceil\frac{2\times i}{3}\rceil+1$，前面激活和中间不激活的个数各 $+1$，后面激活的个数不多只少，不优。

- 若 $pos=\lceil\frac{2\times i}{3}\rceil-1$，前面激活和中间不激活的个数各 $-1$，而因为 $3\times pos<2\times i$，所以会有不激活的“第四部分”占据末尾，此时最大激活个数为 $2\times pos=2\times(\lceil\frac{2\times i}{3}\rceil-1)\le2\times\lfloor\frac{2\times i}{3}\rfloor\le\lfloor\frac{4\times i}{3}\rfloor$，同样不优。

这样，我们不是很严谨地证明了 $f(2\times i)=i+\lfloor\frac{i}{3}\rfloor$。

欢迎提供更严谨的证明，本蒟蒻还是太菜了。

### 代码实现

**下文称 $
\sum\limits_{i=l}^rf(2\times i)=\sum\limits_{i=l}^ri\times\lfloor\frac{i}{3}\rfloor$ 为区间 $[l,r]$ 的权值**。

使用线段树，维护每个区间的权值、模 $3$ 余 $0,1,2$ 的数的个数，分别记为 $w_i,rest_{i,0},rest_{i,1},rest_{i,2}$。

考虑如何实现区间加操作：假设现在要把编号为 $i$ ，长度为 $len$ 的区间加上 $pos$。

1. $pos \bmod 3=0$：$w_i+(pos+\lfloor\frac{pos}{3}\rfloor)\times len\to w_i$。

2. $pos \bmod 3=1$：$w_i+(pos+\lfloor\frac{pos}{3}\rfloor)\times len+rest_{i,2}\to w_i$，然后使 $rest_{i,0},rest_{i,1},rest_{i,2}$ 变为 $rest_{i,1},rest_{i,2},rest_{i,0}$。

3. $pos \bmod 3=2$：$w_i+(pos+\lfloor\frac{pos}{3}\rfloor)\times len+rest_{i,1}+rest_{i,2}\to w_i$，然后使 $rest_{i,0},rest_{i,1},rest_{i,2}$ 变为 $rest_{i,2},rest_{i,0},rest_{i,1}$。

于是，我们可以写出以下的 $\rm{maketag()}$ 函数：

```cpp
void maketag(int id,int pos,int len){
    tag[id]+=pos;
    switch(pos%3){
        case 0:{
            w[id]+=(pos+pos/3)*len;
            break;
        }
        case 1:{
            w[id]+=(pos+pos/3)*len+rest[id][2];
            int res=rest[id][2];
            rest[id][2]=rest[id][1];
            rest[id][1]=rest[id][0];
            rest[id][0]=res;
            break;
        }
        case 2:{
            w[id]+=(pos+pos/3)*len+rest[id][1]+rest[id][2];
            int res=rest[id][2];
            rest[id][2]=rest[id][0];
            rest[id][0]=rest[id][1];
            rest[id][1]=res;
            break;
        }
    }
}
```

但考虑到 $pos$ 可能为负数，这样写连样例都过不去。

不过，我们可以找到一个最大的 $ppos$ 满足 $ppos\le pos,ppos \bmod 3=0$，然后先调用 $\rm{maketag}(\textit{id,ppos,len})$，再调用 $\rm{maketag}(\textit{id,pos-ppos,len})$，这样可以保证正确性而且不用特判负数。

于是这道题就做完了。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int inf=1e16,maxn=5e5+10;
int a[maxn],w[4*maxn],rest[4*maxn][3],tag[4*maxn];
void pushup(int id){
    w[id]=w[id*2]+w[id*2+1];
    for(int i:{0,1,2})rest[id][i]=rest[id*2][i]+rest[id*2+1][i];
}
void build(int id,int l,int r){
    if(l==r){w[id]=a[l]+a[l]/3;rest[id][a[l]%3]=1;return;}
    int mid=(l+r)/2;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    pushup(id);
}
void maketag(int id,int pos,int len){
    if(pos<0 and pos%3){
        int ppos=pos;
        while(ppos%3)ppos--;
        maketag(id,ppos,len);
        maketag(id,pos-ppos,len);
        return;
    }
    tag[id]+=pos;
    switch(pos%3){
        case 0:{
            w[id]+=(pos+pos/3)*len;
            break;
        }
        case 1:{
            w[id]+=(pos+pos/3)*len+rest[id][2];
            int res=rest[id][2];
            rest[id][2]=rest[id][1];
            rest[id][1]=rest[id][0];
            rest[id][0]=res;
            break;
        }
        case 2:{
            w[id]+=(pos+pos/3)*len+rest[id][1]+rest[id][2];
            int res=rest[id][2];
            rest[id][2]=rest[id][0];
            rest[id][0]=rest[id][1];
            rest[id][1]=res;
            break;
        }
    }
}
void pushdown(int id,int l,int r){
    int mid=(l+r)/2;
    maketag(id*2,tag[id],mid-l+1);
    maketag(id*2+1,tag[id],r-mid);
    tag[id]=0;
}
bool inr(int l,int r,int cl,int cr){return cl<=l and r<=cr;}
bool outr(int l,int r,int cl,int cr){return cr<l or r<cl;}
void update(int id,int l,int r,int cl,int cr,int pos){
    if(inr(l,r,cl,cr)){maketag(id,pos,r-l+1);return;}
    if(outr(l,r,cl,cr))return;
    pushdown(id,l,r);
    int mid=(l+r)/2;
    update(id*2,l,mid,cl,cr,pos);
    update(id*2+1,mid+1,r,cl,cr,pos);
    pushup(id);
}
int check(int id,int l,int r,int cl,int cr){
    if(inr(l,r,cl,cr))return w[id];
    if(outr(l,r,cl,cr))return 0;
    pushdown(id,l,r);
    int mid=(l+r)/2;
    return check(id*2,l,mid,cl,cr)+check(id*2+1,mid+1,r,cl,cr);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	while(m--){
        int op,l,r;cin>>op>>l>>r;
        if(op==1){
            int x;cin>>x;
            update(1,1,n,l,r,x);
        }
        else cout<<check(1,1,n,l,r)<<"\n";
    }
	return 0;
}
```

### 后言

机房有同学通过找规律轻轻松松飚过 C 题和 E 题，我拼尽全力无法战胜。

果然还是技不如人吗。

---

## 作者：lzyqwq (赞：2)

记 $F(x)$ 表示 $x$ 块磁铁时的答案。转化一下问题：

> 给出集合 $A_x=\{1,\dots,2x\}$，选出一个子集 $S$，满足存在 $y\in [1,x]\cap \mathbb{Z}$，使得对于任意 $u,v\in S$ 都有 $|u-v|\ne y$。$F(x)$ 表示此时能选出的子集 $S$ 的最大元素个数。

**结论**

$$F(x)=x+\left\lfloor\dfrac{x}{3}\right\rfloor$$

**上界**

对于集合 $X$ 和不超过 $x$ 的正整数 $m$，记 $f(X,m)=\sum\limits_{i=1}^{|X|}([X_i+m\in A_x]+[X_i-m\in A_x])$。

性质 $1$：$f(X,m)\le 2|X|$。

对于 $X\sube A$，有性质 $2$：$f(X,m)\ge |X|$。

> $\bf{Lemma}$
>
> 若 $X$ 为好集合，且 $m$ 为一个不超过 $x$ 的正整数使得 $\forall\,u,v\in X,|u-v|\ne m$，根据定义一定存在这样的 $m$。记 $Y=\complement_{A_x}X$，则 $f(X,m)\le f(Y,m)$。
> 
> $\bf{Proof}$
>
> 因为 $X$ 是好集合，因此可以转化 $f(X,m)$：
> $$\begin{aligned}f(X,m)&= \sum\limits_{i=1}^{|X|}([X_i+m\in Y]+[X_i-m\in Y])\\&=\sum\limits_{i=1}^{|X|}\sum\limits_{j=1}^{|Y|}[X_i+m=Y_j]+\sum\limits_{i=1}^{|X|}\sum\limits_{j=1}^{|Y|}[X_i-m=Y_j]\end{aligned}$$
>
> 放缩 $f(Y,m)$：
>
> $$\begin{aligned}f(Y,m)&\ge\sum\limits_{i=1}^{|Y|}([Y_i+m\in X]+[Y_i-m]\in X)\\&=\sum\limits_{i=1}^{|Y|}\sum\limits_{j=1}^{|X|}[Y_i+m=X_j]+\sum\limits_{i=1}^{|Y|}\sum\limits_{j=1}^{|X|}[Y_i-m=X_j]\\&=\sum\limits_{i=1}^{|Y|}\sum\limits_{j=1}^{|X|}[X_j-m=Y_i]+\sum\limits_{i=1}^{|Y|}\sum\limits_{j=1}^{|X|}[X_j+m=Y_i]\\&=f(X,m)\end{aligned}$$
>
> $\mathcal{Q.E.D.}$

对于一个好的集合 $X$，沿用一些 $\bf{Proof}$ 部分的定义，由性质 $1$ 和性质 $2$ 得：

$$|X|\le f(X,m)\le f(Y,m)\le 2|Y|=4x-2|X|\\\Updownarrow \\3|X|\le 4x\\\Updownarrow\\|X|\le x + \left\lfloor\dfrac{x}{3}\right\rfloor$$

**构造**

- 若 $x\bmod 3\in\{0,2\}$，则考虑从 $\{1,\dots,2x\}$ 头尾各取 $\left\lfloor\dfrac{2x}{3}\right\rfloor$ 个元素。
- 若 $x\bmod 3=1$，则考虑从 $\{1,\dots,2x\}$ 头部取 $\left\lfloor\dfrac{2x}{3}\right\rfloor+1$ 个元素，从尾部取 $\left\lfloor\dfrac{2x}{3}\right\rfloor$ 个元素。

**数据结构**

此时问题变成区间加，求区间和、区间所有数乘 $\dfrac{1}{3}$ 再下取整的和。

考虑线段树。维护区间加标记、区间和、区间所有数区间所有数乘 $\dfrac{1}{3}$ 再下取整的和、区间中模 $3$ 余数为 $0/1/2$ 的数个数即可。

对于第二个信息修改时，加的值 $v$ 整除 $3$ 的部分可以直接打掉。对于 $v\bmod 3$ 的部分，区间中每种余数的数增量是固定的，讨论一下即可。而对于第三个信息修改时，原来每种余数被加后变成哪一种余数也是容易得到的，讨论一下即可。

时间复杂度 $\mathcal{O}(q\log n)$，空间复杂度 $\mathcal{O}(n)$。

注意可能加负数。


```cpp
#include <bits/stdc++.h>
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - 48; x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
using namespace std; typedef long long ll; const int N = 500005; int n, q, b[N];
struct node {
    ll s, a; int c[3]; node() { s = a = c[0] = c[1] = c[2] = 0; }
    node operator+(const node &o) const {
        node t; t.s = s + o.s; t.a = a + o.a;
        for (int i = 0; i < 3; ++i) t.c[i] = c[i] + o.c[i]; return t;
    }
    void U(ll x) {
        s += 1ll * (c[0] + c[1] + c[2]) * x; vector<int> d(3);
        for (int i = 0; i < 3; ++i) d[i] = c[i];
        if (x >= 0) a += 1ll * (c[0] + c[1] + c[2]) * (x / 3), x %= 3;
        else {
            ll y = ((-x + 2) / 3); x = (x % 3 + 3) % 3;
            a -= 1ll * (c[0] + c[1] + c[2]) * y;
        }
        for (int i = 0; i < 3; ++i) {
            c[i] = d[(i - x + 3) % 3]; if (i + x >= 3) a += d[i];
        }
    }
};
struct SGT {
    node a[N << 2]; ll t[N << 2];
    int ls(int x) { return x << 1; } int rs(int x) { return x << 1 | 1; }
    void B(int x, int l, int r) {
        if (l == r)
            return a[x].s = b[l], a[x].a = b[l] / 3, a[x].c[b[l] % 3] = 1, void();
        int m = l + r >> 1; B(ls(x), l, m); B(rs(x), m + 1, r);
        a[x] = a[ls(x)] + a[rs(x)];
    }
    void M(int x, int l, int r, int ql, int qr, ll v) {
        if (!x) return; if (ql <= l && r <= qr) return a[x].U(v), t[x] += v, void();
        int m = l + r >> 1; if (ql <= m) M(ls(x), l, m, ql, qr, v);
        if (qr > m) M(rs(x), m + 1, r, ql, qr, v);
        a[x] = a[ls(x)] + a[rs(x)]; a[x].U(t[x]);
    }
    node Q(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return a[x]; int m = l + r >> 1; node k;
        if (ql <= m) k = Q(ls(x), l, m, ql, qr);
        if (qr > m) k = k + Q(rs(x), m + 1, r, ql, qr); k.U(t[x]); return k;
    }
} T;
signed main() {
    read(n); read(q); for (int i = 1; i <= n; ++i) read(b[i]); T.B(1, 1, n);
    for (int op, l, r, x; q--;) {
        read(op); read(l); read(r); node t;
        if (op & 1) read(x), T.M(1, 1, n, l, r, x);
        else t = T.Q(1, 1, n, l, r), print(t.a + t.s);
    }
    return 0;
}
```

---

## 作者：Tachanka233 (赞：1)

赛时把结论猜出来了……
## 题意
对于一个数列，定义每个数 $x_i$ 的权值为：确定一个数 $y\in[1,x_i]$，使得在 $2\times x_i$ 个格子中选取一些格子，满足任两个格子的距离之差 $\not=y$，可选得格子的最大值。

数列支持两个操作:  
1. 将在区间 $[l,r]$ 内每个数加上 $k$。
2. 询问区间 $[l,r]$ 内每个数的权值和。

## 思路
首先看操作。区间修改、查询区间和，于是想到线段树。  
然后思考每个数的权值如何维护。猜测权值有一定规律。对于 $y=1$ 可以算得最多选择 $x$ 个格子。对于 $\forall y>1$，显然地，选择连续的 $y$ 个格子是最优的。于是我们可以推出公式：设 $m$ 为对于 $x$，当 $y$ 的值一定时，可以选的最多格子数，则有 $m=\lfloor\frac{x}{y}\rfloor\times y+\min(2x\bmod2y,y)$。先给出结论：$m_{max}=x+\lfloor\frac{x}{3}\rfloor$。下面进行证明：  
>考虑对于 $\lfloor\frac{x}{y}\rfloor$ 的值进行分类讨论。
>
>- 当 $\lfloor\frac{x}{y}\rfloor=1$ 时，若 $2x\bmod2y>y$，则 $m=\lfloor\frac{x}{y}\rfloor\times y+y=2y$ 且 $y\le\lfloor\frac{2x}{3}\rfloor$，所以 $m\le2\times\lfloor\frac{2x}{3}\rfloor$。若 $2x\bmod2y\le y$，则 $m=\lfloor\frac{x}{y}\rfloor\times y+2x\bmod2y=y+2x-2y=2x-y$ 且 $y\ge\lceil\frac{2x}{3}\rceil$，所以 $m\le2x-\lceil\frac{2x}{3}\rceil$。显然，$2x-\lceil\frac{2x}{3}\rceil\ge2\times\lfloor\frac{2x}{3}\rfloor$，所以可得出结论，$y=\lceil\frac{2x}{3}\rceil$ 最优，此时 $m=2x-\lceil\frac{2x}{3}\rceil=x+\lfloor\frac{x}{3}\rfloor$。
>
>- 当 $\lfloor\frac{x}{y}\rfloor=2$ 时，同上可得：当 $y\le\lfloor\frac{2x}{5}\rfloor$ 时，有 $m\le3\times\lfloor\frac{2x}{5}\rfloor$，当 $y\ge\lceil\frac{2x}{5}\rceil$ 时，有 $m\le2x-2\times\lceil\frac{2x}{5}\rceil$。对 $x\bmod5$ 分讨可得：当 $x\bmod5=1$ 时，$m=3\times\lfloor\frac{2x}{5}\rfloor=x+\frac{x-6}{5}\le x+\lfloor\frac{x}{3}\rfloor$，其他情况 $m=2x-2\times\lceil\frac{2x}{5}\rceil<x+\lfloor\frac{x}{3}\rfloor$。
>
>- 当 $\lfloor\frac{x}{y}\rfloor>2$ 时，考虑 $\lfloor\frac{x}{y}\rfloor\times y=x-x\bmod y$，那么 $m=x-x\bmod y+\min(2x\bmod 2y,y)\le x+x\bmod y\le x+\lfloor\frac{x}{3}\rfloor$，故一定更劣。
>
>综上，有 $m_{max}=x+\lfloor\frac{x}{3}\rfloor$。

那么如何用线段树维护 $x+\lfloor\frac{x}{3}\rfloor$ 呢？我们可以考虑维护区间内模 $3$ 余 $0,1,2$ 的数的数量。对于每一次修改的值，按模 $3$ 的余数分类，以此来更新答案与模 $3$ 余 $0,1,2$ 的数的数量。具体操作见代码注释。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 500001
#define il inline
int n,a[N],m;
struct node{
	int l,r,sum,add,num0,num1,num2;
}tr[N*4];
il int ls(int p){return p*2;}
il int rs(int p){return p*2+1;}
il void pushup(int p){
	tr[p].sum=tr[ls(p)].sum+tr[rs(p)].sum;
	tr[p].num0=tr[ls(p)].num0+tr[rs(p)].num0;
	tr[p].num1=tr[ls(p)].num1+tr[rs(p)].num1;
	tr[p].num2=tr[ls(p)].num2+tr[rs(p)].num2;
}
void build(int p,int l,int r){//初始化
	tr[p].l=l,tr[p].r=r;
	tr[p].sum=tr[p].add=0;
	tr[p].num0=tr[p].num1=tr[p].num2=0;
	if(l==r){
		tr[p].sum=a[l]+a[l]/3;
		switch(a[l]%3){
			case 0:tr[p].num0=1;break;
			case 1:tr[p].num1=1;break;
			case 2:tr[p].num2=1;break;
		}
		return;
	}
	int mid=(l+r)/2;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	pushup(p);
}
void pushdown(int p){
	tr[ls(p)].sum+=(tr[p].add+tr[p].add/3)*(tr[ls(p)].r-tr[ls(p)].l+1);//先按懒惰标记更新
	tr[rs(p)].sum+=(tr[p].add+tr[p].add/3)*(tr[rs(p)].r-tr[rs(p)].l+1);
	if(tr[p].add>=0){//如果大于0
		if(tr[p].add%3==1){//如果模3余1
			tr[ls(p)].sum+=tr[ls(p)].num2;//区间和加上模3余2的数的个数
			swap(tr[ls(p)].num0,tr[ls(p)].num1);
			swap(tr[ls(p)].num2,tr[ls(p)].num0);//更新数量 0<-2 1<-0 2<-1
			tr[rs(p)].sum+=tr[rs(p)].num2;
			swap(tr[rs(p)].num0,tr[rs(p)].num1);
			swap(tr[rs(p)].num2,tr[rs(p)].num0);
		}
		if(tr[p].add%3==2){//如果模3余2
			tr[ls(p)].sum+=tr[ls(p)].num2+tr[ls(p)].num1;//区间和加上模3余1,2的数的个数
			swap(tr[ls(p)].num0,tr[ls(p)].num2);
			swap(tr[ls(p)].num0,tr[ls(p)].num1);//更新数量 0<-1 1<-2 2<-0
			tr[rs(p)].sum+=tr[rs(p)].num2+tr[rs(p)].num1;
			swap(tr[rs(p)].num0,tr[rs(p)].num2);
			swap(tr[rs(p)].num0,tr[rs(p)].num1);
		}
	}
	else{//如果小于0
		if(tr[p].add%3==-1){//如果模3余2
			tr[ls(p)].sum-=tr[ls(p)].num0;//区间和减去模3余0的数的个数
			swap(tr[ls(p)].num0,tr[ls(p)].num1);
			swap(tr[ls(p)].num2,tr[ls(p)].num1);//更新数量 0<-1 1<-2 2<-0
			tr[rs(p)].sum-=tr[rs(p)].num0;
			swap(tr[rs(p)].num0,tr[rs(p)].num1);
			swap(tr[rs(p)].num2,tr[rs(p)].num1);
		}
		if(tr[p].add%3==-2){//如果模3余1
			tr[ls(p)].sum-=tr[ls(p)].num0+tr[ls(p)].num1;//区间和减去模3余0,1的数的个数
			swap(tr[ls(p)].num0,tr[ls(p)].num1);
			swap(tr[ls(p)].num0,tr[ls(p)].num2);//更新数量 0<-2 1<-0 2<-1
			tr[rs(p)].sum-=tr[rs(p)].num0+tr[rs(p)].num1;
			swap(tr[rs(p)].num0,tr[rs(p)].num1);
			swap(tr[rs(p)].num0,tr[rs(p)].num2);
		}
	}
	tr[ls(p)].add+=tr[p].add;
	tr[rs(p)].add+=tr[p].add;
	tr[p].add=0;
}
void update(int num,int l,int r,int p){
	if(l<=tr[p].l&&r>=tr[p].r){
		tr[p].sum+=(num+num/3)*(tr[p].r-tr[p].l+1);//先按修改值更新
		if(num>0){//如果大于0
			if(num%3==1){//如果模3余1
				tr[p].sum+=tr[p].num2;//区间和加上模3余2的数的个数
				swap(tr[p].num0,tr[p].num1);
				swap(tr[p].num2,tr[p].num0);//更新数量 0<-2 1<-0 2<-1
			}
			if(num%3==2){//如果模3余1
				tr[p].sum+=tr[p].num2+tr[p].num1;//区间和加上模3余1,2的数的个数
				swap(tr[p].num0,tr[p].num2);
				swap(tr[p].num1,tr[p].num0);//更新数量 0<-1 1<-2 2<-0
			}
		}
		else{
			if(num%3==-1){//如果模3余1
				tr[p].sum-=tr[p].num0;//区间和减去模3余0的数的个数
				swap(tr[p].num0,tr[p].num1);
				swap(tr[p].num2,tr[p].num1);//更新数量 0<-1 1<-2 2<-0
			}
			if(num%3==-2){//如果模3余1
				tr[p].sum-=tr[p].num0+tr[p].num1;//区间和减去模3余0,1的数的个数
				swap(tr[p].num0,tr[p].num1);
				swap(tr[p].num0,tr[p].num2);//更新数量 0<-2 1<-0 2<-1
			}
		}
		tr[p].add+=num;//更新懒惰标记
		return;
	}
	pushdown(p);
	int mid=(tr[p].l+tr[p].r)/2;
	if(l<=mid) update(num,l,r,ls(p));
	if(r>mid) update(num,l,r,rs(p));
	pushup(p);
}
int query(int l,int r,int p){
	if(l<=tr[p].l&&r>=tr[p].r) return tr[p].sum;
	pushdown(p);
	int mid=(tr[p].l+tr[p].r)/2,res=0;
	if(l<=mid) res+=query(l,r,ls(p));
	if(r>mid) res+=query(l,r,rs(p));
	return res;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int op,x,y,k;
		cin>>op>>x>>y;
		if(op==1){
			cin>>k;
			update(k,x,y,1);
		}
		else cout<<query(x,y,1)<<'\n';
	}
	return 0;
}
```

---

