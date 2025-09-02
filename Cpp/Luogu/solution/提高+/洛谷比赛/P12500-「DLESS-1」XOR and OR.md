# 「DLESS-1」XOR and OR

## 题目描述

给定长度为 $n$ 的序列 $a$，支持 $q$ 次操作，每次操作形如以下两种中的一种：

- `1 l r x`：对所有 $i\in[l,r]$，将 $a_i$ 异或上 $x$。
- `2 l r`：求区间 $[l,r]$ 所有子区间权值按位或的异或和。

## 说明/提示

#### 【样例解释】

以下 $\operatorname{or}$ 表示按位或运算，$\operatorname{xor}$ 表示按位异或运算。

对于第一组样例的第二个询问，区间 $[2,4]$ 所有子区间按位或的异或和等于 $a_2\operatorname{xor}a_3\operatorname{xor}a_4\operatorname{xor}(a_2\operatorname{or}a_3)\operatorname{xor}(a_3\operatorname{or}a_4)\operatorname{xor}(a_2\operatorname{or}a_3\operatorname{or}a_4)$，等于 $4$。

#### 【数据范围】

对于所有数据，保证：
- $1\le n,q\le 5\times10^5$
- $0\le a_i,x<2^{60}$
- $1\le l\le r\le n$

**本题采用打包测试**，各测试包描述如下：

| Subtask | $n\le$ | $q\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $500$ | $500$ | 无 | $10$ |
| $2$ | $5000$ | $5000$ | 无 | $15$ |
| $3$ | $5\times10^5$ | $5\times10^5$ | 没有操作 $1$ | $25$ |
| $4$ | $5\times10^5$ | $10^5$ | $a_i<2^{20}$ | $25$ |
| $5$ | $5\times10^5$ | $5\times10^5$ | 无 | $25$ |

## 样例 #1

### 输入

```
5 5
0 6 7 2 6 
2 1 1 
2 2 4 
2 1 1 
1 1 5 2
2 2 3 
```

### 输出

```
0
4
0
4
```

## 样例 #2

### 输入

```
4 4
6 0 7 0 
1 2 3 5
2 1 3 
1 1 1 7
2 3 4 
```

### 输出

```
6
0```

## 样例 #3

### 输入

```
4 5
4 4 6 5 
1 3 4 6
1 2 4 0
2 1 3 
2 2 2 
2 3 4 
```

### 输出

```
4
4
0```

# 题解

## 作者：喵仔牛奶 (赞：16)

## Solution

考虑拆位。考虑求出按位或和为 $0$ 的区间数，用总区间减去这些就是按位或和为 $1$ 的区间数。

显然，按位或和为 $0$ 等价于区间内全部为 $0$。线段树维护左边和右边最长的 $0$ 连续段长度 $L,R$、区间内按位或和为 $0$ 的区间数 $s$、区间数反转后（$01$ 互换）的积 $w$。

线段树合并信息 $(L,R,s,w)(L',R',s',w')$ 时：
$$
\begin{cases}
s''=s+s'+R'\times L\\
L''=w\times L'+L\\
R''=w'\times R+R'\\
w''=w\times w'
\end{cases}
$$

由于有区间 $01$ 反转，还要维护区间 $01$ 反转后的答案。

这样直接做是 $\mathcal O(n\log n\log V)$ 的，无法通过。

考虑求的是异或和，即模 $2$ 的结果。加法和乘法在模 $2$ 意义下等价于按位异或、按位与。因此，将每位的线段树的信息压到一个数里面，合并时将加法改为异或、乘法改完按位与即可。

复杂度 $\mathcal O(n\log n)$。代码很好写，就不放了。

---

## 作者：Gold14526 (赞：9)

本文章中 $\operatorname{and}$ 表示按位与运算，$\operatorname{or}$ 表示按位或运算，$\operatorname{xor}$ 表示按位异或运算。

Hint1：考虑求出区间所有子区间按位与的异或和然后 $O(1)$ 转换成子区间按位或的异或和。

Hint2：与和异或有分配率，即 $a\operatorname{and}(b\operatorname{xor}c)=(a\operatorname{and}b)\operatorname{xor}(a\operatorname{and}c)$。

---

事实上，知道上面这个差不多就做完了。

先不考虑修改。

我们维护线段树，每个节点上维护以下四个信息：

- $xl$：所有前缀与的异或和。
- $xr$：所有后缀与的异或和。
- $xsum$：所有区间与的异或和。
- $asum$：区间与。

当我们上传信息时，我们设当前节点为 $now$，左儿子为 $ls$，右儿子为 $rs$，由于与和异或有分配率，我们可以这样计算节点 $now$ 的 $xsum$ 信息：

$$xsum_{now}=xsum_{ls}\operatorname{xor}xsum_{rs}\operatorname{xor}(xr_{ls}\operatorname{and}xl_{rs})$$

即左右两边的贡献异或上跨过中点的贡献，跨过中点这一部分相当于是，我们把原来的先求出每个跨过中点的子区间与再异或起来，改成先把两边前后缀与异或起来再与。

同理，$xl,xr$ 也可以简单转移：

$$xl_{now}=xl_{ls}\operatorname{xor}(xl_{rs}\operatorname{and}asum_{ls})$$

$$xr_{now}=xr_{rs}\operatorname{xor}(xr_{ls}\operatorname{and}asum_{rs})$$

如果我们要带修的话，我们再维护取反过后的以上四个信息，异或 $x$ 时交换 $x$ 为 $1$ 的位即可，但是发现直接交换是多带个 $\log$ 的，所以我们考虑一下如何 $O(1)$ 交换 $a,b$ 中 $x$ 为 $1$ 的位，发现我们可以这样操作：

- 设 $p=a\operatorname{and}x,q=b\operatorname{and}x$。
- 将 $a,b$ 都异或上 $p\operatorname{xor}q$。

最后我们把这个答案转换为子区间按位或的异或和即可，这一步是简单的。

```cpp
#include<bits/stdc++.h>
#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
inline ll read()
{
	ll x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch-'0');
		ch=getchar();
	}
	return x;
}
inline void print(cll x)
{
	if(x<10)
	{
		putchar(x+'0');
		return;
	}
	cll y=x/10;
	print(y);
	putchar(x-y*10+'0');
}
inline void princh(cll x,const char ch)
{
	print(x);
	putchar(ch);
}
cint N=5e5,H=60;
cll inf=(1<<H)-1;
int n,q;
ll a[N+1];
namespace T{
	struct node{
		int l,r;
		ll tag,xl[2],xr[2],xsum[2],asum[2];
	}t[N<<1|1],z;
	inline void operator^=(node &x,cll y)
	{
		ll tmp;
		x.tag^=y;
		tmp=(x.xl[0]&y)^(x.xl[1]&y);
		x.xl[0]^=tmp,x.xl[1]^=tmp;
		tmp=(x.xr[0]&y)^(x.xr[1]&y);
		x.xr[0]^=tmp,x.xr[1]^=tmp;
		tmp=(x.xsum[0]&y)^(x.xsum[1]&y);
		x.xsum[0]^=tmp,x.xsum[1]^=tmp;
		tmp=(x.asum[0]&y)^(x.asum[1]&y);
		x.asum[0]^=tmp,x.asum[1]^=tmp;
	}
	inline node operator&(const node x,const node y)
	{
		z.l=x.l;
		z.r=y.r;
		z.tag=0;
		z.xl[0]=x.xl[0]^(y.xl[0]&x.asum[0]);
		z.xr[0]=y.xr[0]^(x.xr[0]&y.asum[0]);
		z.xsum[0]=x.xsum[0]^y.xsum[0]^(x.xr[0]&y.xl[0]);
		z.asum[0]=x.asum[0]&y.asum[0];
		z.xl[1]=x.xl[1]^(y.xl[1]&x.asum[1]);
		z.xr[1]=y.xr[1]^(x.xr[1]&y.asum[1]);
		z.xsum[1]=x.xsum[1]^y.xsum[1]^(x.xr[1]&y.xl[1]);
		z.asum[1]=x.asum[1]&y.asum[1];
		return z;
	}
	inline void push_down(cint p)
	{
		if(t[p].tag)
		{
			t[p<<1]^=t[p].tag;
			t[p<<1|1]^=t[p].tag;
			t[p].tag=0;
		}
	}
	inline void Build(cint p,cint l,cint r)
	{
		t[p].l=l;
		t[p].r=r;
		if(l==r)
		{
			t[p].xl[0]=t[p].xr[0]=t[p].xsum[0]=t[p].asum[0]=a[l];
			t[p].xl[1]=t[p].xr[1]=t[p].xsum[1]=t[p].asum[1]=a[l]^inf;
			return;
		}
		cint mid=l+r>>1;
		Build(p<<1,l,mid);
		Build(p<<1|1,mid+1,r);
		t[p]=t[p<<1]&t[p<<1|1];
	}
	inline void build()
	{
		Build(1,1,n);
	}
	inline void Update(cint p,cint l,cint r,cll x)
	{
		if(t[p].l>r||t[p].r<l)return;
		if(t[p].l>=l&&t[p].r<=r)
		{
			t[p]^=x;
			return;
		}
		push_down(p);
		Update(p<<1,l,r,x);
		Update(p<<1|1,l,r,x);
		t[p]=t[p<<1]&t[p<<1|1];
	}
	inline void update(cint l,cint r,cll x)
	{
		Update(1,l,r,x);
	}
	inline node Ask(cint p,cint l,cint r)
	{
		if(t[p].l>=l&&t[p].r<=r)return t[p];
		push_down(p);
		if(t[p<<1].r<l)return Ask(p<<1|1,l,r);
		if(t[p<<1|1].l>r)return Ask(p<<1,l,r);
		return Ask(p<<1,l,r)&Ask(p<<1|1,l,r);
	}
	inline ll ask(cint l,cint r)
	{
		const node res=Ask(1,l,r);
		return (res.xsum[1]^((1ll*(r-l+1)*(r-l+2)/2&1)*inf));
	}
}
inline void modify()
{
	cint l=read(),r=read();
	cll x=read();
	T::update(l,r,x);
}
inline void query()
{
	cint l=read(),r=read();
	princh(T::ask(l,r),'\n');
}
int main()
{
	// freopen("xaa.in","r",stdin);
	// freopen("xaa.out","w",stdout);
	n=read();
	q=read();
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
	}
	T::build();
	while(q--)
	{
		if(read()==1)modify();
		else query();
	}
	return 0;
}
```

---

## 作者：complexly (赞：8)

## P12500 XOR and OR

一道很好玩的题。

看到题的第一反映是拆位，拆完位就很好做了，先取反，可以转化成求所有子区间权值按位与的异或和。

维护一下前缀后缀 $1$ 和 $0$ 的长度，合并的时候答案加上左边的后缀乘右边的前缀，就可以了，答案就是区间所有子区间权值按位与的和的奇偶性。

具体地：

1. $pre_{0/1}$ 表示前缀极长 $0/1$ 的长度（表示反转之后 / 之前前缀极长 $0$ 的奇偶性）。
2. $suf_{0/1}$ 表示后缀极长 $0/1$ 的长度（表示反转之后 / 之前后缀极长 $0$ 的奇偶性）。
3. $ans_{0/1}$ 表示反转之后 / 之前的的答案。

但是你发现这只有 $25$ 分。超空间了很难受。

考虑优化空间，你发现我只在乎奇偶性，所以 $pre_{0/1}$、$suf_{0/1}$、$ans_{0/1}$ 都是 bool 型，这样就不会超空间了。

但还是过不了，因为时间复杂度是 $O(n \log n \log V)$ 的。

这时你发现，这些全是 bool 型的，真的有必要全部分开算吗？

你发现我**只要能把我所有 bool 的转移换成位运算，就可以全部一起算**（因为位与位直接互不影响）。

于是你不拆位了，考虑把这些东西全部一起算。

1. $pre_{0/1}$ 的第 $i$ 位表示第 $i$ 位前缀极长 $0/1$ 的奇偶性（表示反转之后 / 之前前缀极长 $0$ 的奇偶性）。
2. $suf_{0/1}$ 的第 $i$ 位表示第 $i$ 位后缀极长 $0/1$ 的奇偶性（表示反转之后 / 之前后缀极长 $0$ 的奇偶性）。
3. $ans_{0/1}$ 的第 $i$ 位表示第 $i$ 位表示反转之后 / 之前的答案奇偶性。
4. $and_{0/1}$ 表示反转之后 / 之前的区间与（为了方便转移 $pre$ 和 $suf$）。

### 合并

再强调一次：**只要能把我所有 bool 的转移换成位运算，就可以全部一起算**。

```cpp
node merge(node a,node b){
    if(a.And0 == (1ll << 60) - 1 && a.And1 == (1ll << 60) - 1)return b;//这个无所谓，用来判掉a为空
    node c;
    c.pre1 = a.pre1 ^ (b.pre1 & a.And0);
    c.suf1 = b.suf1 ^ (a.suf1 & b.And0);
    c.pre0 = a.pre0 ^ (b.pre0 & a.And1);
    c.suf0 = b.suf0 ^ (a.suf0 & b.And1);
    c.ans1 = (a.ans1 ^ b.ans1 ^ (a.suf1 & b.pre1));
    c.ans0 = (a.ans0 ^ b.ans0 ^ (a.suf0 & b.pre0));
    c.And0 = a.And0 & b.And0;
    c.And0 = a.And1 & b.And1;
    return c;
}
```

首先： `pre , suf` 的转移。

```cpp
c.pre1 = a.pre1 ^ (b.pre1 & a.And0);
c.suf1 = b.suf1 ^ (a.suf1 & b.And0);
c.pre0 = a.pre0 ^ (b.pre0 & a.And1);
c.suf0 = b.suf0 ^ (a.suf0 & b.And1);
```

假设它是 bool 你会怎么写？

```cpp
c.pre1 = (a.And0 ? (a.pre1 ^ b.pre1) : a.pre1);
```

对吧？

翻译成人话就是如果 $a$ 管辖的区间全是 1 ，那么还要算上后面的贡献。

再看这个：

```cpp
c.pre1 = a.pre1 ^ (b.pre1 & a.And0);
```

具体一点：

`a.And0` 是 1 ， 那么这一位就是 `(a.pre1 ^ b.pre1)` 。

`a.And0` 是 0 ， 那么这一位就是 `(a.pre1 ^ (b.pre1 & 0))` 也就是 `a.pre1` 。

发现了吗？和上面那个是完全等价的，于是我们就成功的替换成位运算了。

其次：`ans` 的转移。

```cpp
c.ans1 = (a.ans1 ^ b.ans1 ^ (a.suf1 & b.pre1));
c.ans0 = (a.ans0 ^ b.ans0 ^ (a.suf0 & b.pre0));
```

假设它是 bool 你会怎么写？

```
c.ans1 = (a.ans1 ^ b.ans1 ^ (a.suf1 * b.pre1));
```

其实在 bool 中 * 和 & 是一样的，所有直接替换就行了。

最后：`And` 的转移。

本来就是位运算。

### 下传标记

接着就是要整体异或上一个值。

因为我们处理了一个数每一位取反后的值，所有我们其实是要交换某些位。

```cpp
void Swap(int &a,int &b,int x){
    int v = (a & x) ^ (b & x);
    a ^= v , b ^= v;
}
```

假设它是 bool 你会怎么写？

```cpp
void Swap(bool &a,bool &b,bool x){
    if(x)swap(a , b);
}
```

我们知道，swap 可以换成下面这样。

```cpp
void Swap(bool &a,bool &b,bool x){
    if(x){
        int t = a ^ b;
        a ^= t , b ^= t;
        //a ^= b ^= a ^= b;
    }
}
```

我们希望 $x = 0$ 时可以直接让 $a , b$ 不交换，也就是让 $t = 0$ 。

于是：

```cpp
void Swap(bool &a,bool &b,bool x){
    int t = (x & a) ^ (x & b);
    a ^= t , b ^= t;
}
```

有了这个东西，下传标记就很简单了。

```cpp
void Xor(node &rt , int x){
    Swap(rt.pre0 , rt.pre1 , x);
    Swap(rt.suf0 , rt.suf1 , x);
    Swap(rt.And0 , rt.And1 , x);
    Swap(rt.ans0 , rt.ans1 , x);
    return ;
}
void down(int u){
    if(lazy[u]){
        lazy[u << 1] ^= lazy[u] , lazy[u << 1 | 1] ^= lazy[u];
        Xor(tree[u << 1] , lazy[u]) , Xor(tree[u << 1 | 1] , lazy[u]);
        lazy[u] = 0;
    }
}
```

于是，本来要 60 次现在用一次位运算解决了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i , l , r) for(int i = (l);i <= (r);++ i)
#define d(i , l , r) for(int i = (r);i >= (l);-- i)
#define pii pair<int,int>
#define pb push_back
#define fi first
#define sc second
#define lowbit(x) ((x)&-(x))
#define fre(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
using namespace std;
const int N = 5e5 + 10;
int n , q , a[N] , lazy[N<<2];
struct node{
    int suf1 , pre1 , suf0 , pre0 , ans1 , ans0 , And0 , And1;
}tree[N<<2];
node merge(node a,node b){
    if(a.And0 == (1ll << 60) - 1 && a.And1 == (1ll << 60) - 1)return b;
    node c;
    c.pre1 = a.pre1 ^ (b.pre1 & a.And0);
    c.suf1 = b.suf1 ^ (a.suf1 & b.And0);
    c.pre0 = a.pre0 ^ (b.pre0 & a.And1);
    c.suf0 = b.suf0 ^ (a.suf0 & b.And1);
    c.ans1 = (a.ans1 ^ b.ans1 ^ (a.suf1 & b.pre1));
    c.ans0 = (a.ans0 ^ b.ans0 ^ (a.suf0 & b.pre0));
    c.And0 = a.And0 & b.And0;
    c.And0 = a.And1 & b.And1;
    return c;
}
void up(int u){
    tree[u] = merge(tree[u << 1] , tree[u << 1 | 1]);
}
void Swap(int &a,int &b,int x){
    int v = (a & x) ^ (b & x);
    a ^= v , b ^= v;
}
void Xor(node &rt , int x){
    Swap(rt.pre0 , rt.pre1 , x);
    Swap(rt.suf0 , rt.suf1 , x);
    Swap(rt.And0 , rt.And1 , x);
    Swap(rt.ans0 , rt.ans1 , x);
    return ;
}
void down(int u){
    if(lazy[u]){
        lazy[u << 1] ^= lazy[u] , lazy[u << 1 | 1] ^= lazy[u];
        Xor(tree[u << 1] , lazy[u]) , Xor(tree[u << 1 | 1] , lazy[u]);
        lazy[u] = 0;
    }
}
void input(int u,int l,int r,int L,int R,int x){
    if(L <= l&&r <= R){
        Xor(tree[u] , x);
        lazy[u] ^= x;
        return ;
    }
    int mid = l + r >> 1;down(u);
    if(L <= mid)input(u << 1 , l , mid , L , R , x);
    if(R > mid)input(u << 1 | 1 , mid + 1 , r , L , R , x);
    return up(u);
}
node query(int u,int l,int r,int L,int R){
    if(L <= l && r <= R)return tree[u];
    int mid = l + r >> 1;node res = {0 , 0 , 0 , 0 , 0 , 0 , (1ll << 60) - 1 , (1ll << 60) - 1};
    down(u);
    if(L <= mid)res = merge(res , query(u << 1 , l , mid , L , R));
    if(R > mid)res = merge(res , query(u << 1 | 1 , mid + 1 , r , L , R));
    return res;
}
void build(int u,int l,int r){
    if(l == r){
        tree[u] = {a[l] , a[l] , a[l] ^ (1ll << 60) - 1 , a[l] ^ (1ll << 60) - 1 , a[l] , a[l] ^ (1ll << 60) - 1 , a[l] , a[l] ^ (1ll << 60) - 1};
        return ;
    }
    int mid = l + r >> 1;
    build(u << 1 , l , mid);
    build(u << 1 | 1 , mid + 1 , r);
    return up(u);
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0) , cout.tie(0);
    cin >> n >> q;
    f(i , 1 , n)cin >> a[i] , a[i] ^= (1ll << 60) - 1;
    build(1 , 1 , n);
    f(i , 1 , q){
        int l , r , x , op;
        cin >> op >> l >> r;
        if(op == 1)cin >> x , input(1 , 1 , n , l , r , x);
        else cout << (query(1 , 1 , n , l , r).ans1 ^ (((r - l + 1) * (r - l + 2) / 2 & 1) ? (1ll << 60) - 1 : 0ll)) << "\n";
    }
}
```

---

## 作者：HPXXZYY (赞：4)

$\color{blue}{\texttt{[Analysis]}}$

显然，一般的位运算的题目都是需要拆位考虑的。

> 位运算最大的特点就是按位运算，没有进位和退位，所以按位考虑是很常见的思路。
> 
> 而按位考虑最大的优势就是每一位数只有 $0$ 和 $1$，情况最多 $4$ 种组合，考虑起来方便很多。

考虑修改操作，异或上 $0$ 等于没变，异或上 $1$ 等于 $01$ 反转。

考虑询问操作，对于一个区间 $[l,r]$，其按位或结果为 $0$ 当且仅当区间内所有数都是 $0$。而异或为 $1$ 当且仅当有奇数个 $1$ 在异或。

于是询问操作等价于询问区间 $[l,r]$ 内有多少个子区间 $[x,y]$（即 $l \leq x \leq y \leq r$），满足 $a_{x \dots y}$ 中不全为 $0$。最后的结果取决于这个值的奇偶性。

显然，**不全为**并不是一个很方面考虑的命题，相反，它的否命题**全为**考虑起来更加方便。

正难则反，不全为 $0$ 的区间个数等于总数减去全为 $0$ 的区间个数。

于是需要维护一下几个量：

- $\text{ans}$：所有元素均为 $0$ 的子区间数量。
- $\text{pre}$：这一段区间开头连续的 $0$ 的数量。
- $\text{suf}$：这一段区间末尾连续的 $0$ 的数量。
- $\text{And}$：这一段区间内是否全部为 $0$，是为 $1$ 否则为 $0$。

为了书写方便，下面分别用 $a,b,c,d$ 表示上面的四个量。

合并两个区间 $(a_{1},b_{1},c_{1},d_{1}),(a_{2},b_{2},c_{2},d_{2})$ 时，有如下转移：

$$\begin{cases}
a&=a_{1}+a_{2}+c_{1}\times b_{2}\\
b&=b_{1}+d_{1}\times b_{2}\\
c&=c_{2}+d_{2}\times c_{1}\\
d &=d_{1}\times d_{2}
\end{cases}$$

因为区间可能发生 $01$ 反转，于是需要维护对称量。

但是这样做是 $O(n\log n \log V)$ 的，其中 $V$ 是值域，会超时。

我们发现我们求出区间个数是多此一举的，毕竟我们最终只关心个数的奇偶性。理论上奇偶性只需要一个 $0/1$ 就完全足够表示。本质就是对 $2$ 取模嘛。

再认真考虑一下就会发现，在对 $2$ 取模意义下，加法相当于异或，乘法相当于按位与。不信可以枚举一下所有情况。

于是我们可以用 $0/1$ 表示该位最终的结果，即拆完位后有把该位的答案用该位的 $0/1$ 表达完全。因此可以一次性把 $60$ 位全部维护出来。

细节看代码。

总时间复杂度 $O(n \log n)$。

```cpp
struct node{
	ll ans[2],pre[2],suf[2],And[2];
	node(){
		ans[0]=ans[1]=pre[0]=pre[1]=suf[0]=suf[1]=0;
		And[0]=And[1]=(1ll<<60)-1;
	}
};

node merge(node a,node b){
	if (a.And[0]==((1ll<<60)-1)&&a.And[1]==((1ll<<60)-1))
		return b;//a 没有初值就用 b 
	
	register node res;
	res.ans[0]=a.ans[0]^b.ans[0]^(a.suf[0]&b.pre[0]);
	res.ans[1]=a.ans[1]^b.ans[1]^(a.suf[1]&b.pre[1]);
	//所有的加法换成异或，所有的乘法换成按位与，咋看咋别扭 
	res.pre[0]=a.pre[0]^(b.pre[0]&a.And[1]);
	res.pre[1]=a.pre[1]^(b.pre[1]&a.And[0]);
	res.suf[0]=b.suf[0]^(a.suf[0]&b.And[1]);
	res.suf[1]=b.suf[1]^(a.suf[1]&b.And[0]);
	res.And[0]=a.And[0]&b.And[0];
	res.And[1]=a.And[1]&b.And[1];
	
	return res;
}

void Swap(ll &a,ll &b,ll x){
	ll tmp=(a&x)^(b&x);
	a^=tmp;b^=tmp;
}//如果 x=0 代表没有变化，因此需要先用按位与把 x=0 的位屏蔽
//事实上这个 swap 函数的思路来源于两个数交换的位运算写法
void Xor(node &a,ll x){
	Swap(a.ans[0],a.ans[1],x);
	Swap(a.pre[0],a.pre[1],x);
	Swap(a.suf[0],a.suf[1],x);
	Swap(a.And[0],a.And[1],x);
}

class Segment_Tree{
	public:
		void clear(int n=0){
			if (n==0){
				memset(tree,0,sizeof(tree));
				memset(tag,0,sizeof(tag));
				memset(ls,0,sizeof(ls));
				memset(rs,0,sizeof(rs));
				rt=ndcnt=0;
			}
			else{
				for(int i=1;i<=(n<<1);i++)
					tag[i]=ls[i]=rs[i]=0;
				rt=ndcnt=0;
			}
		}
		
		void set_size(int n){
			this->n=n;
			clear(n);
		}
		
		Segment_Tree(){clear();}
		
		void build(int n,ll *a){
			set_size(n);
			build(rt,1,n,a);
		}
		void modify(int l,int r,ll val){
			modify(rt,1,n,l,r,val);
		}
		node query(int l,int r){
			return query(rt,1,n,l,r);
		}
	private:
		node tree[N<<1];
		int ls[N<<1],rs[N<<1],rt,ndcnt,n;
		ll tag[N<<1];
		
		void pushup(int o){
			tree[o]=merge(tree[ls[o]],tree[rs[o]]);
		}
		void pushdown(int o){
			tag[ls[o]]^=tag[o];
			tag[rs[o]]^=tag[o];
			Xor(tree[ls[o]],tag[o]);
			Xor(tree[rs[o]],tag[o]);
			tag[o]=0;
		}
		
		void build(int &o,int l,int r,ll *a){
			if (!o) o=++ndcnt;
			if (l==r){
				tree[o].pre[1]=tree[o].ans[1]=tree[o].suf[1]=tree[o].And[0]=a[l];
				tree[o].pre[0]=tree[o].ans[0]=tree[o].suf[0]=tree[o].And[1]=a[r]^((1ll<<60)-1);
				return;
			}
			
			int mid=(l+r)>>1;
			build(ls[o],l,mid,a);
			build(rs[o],mid+1,r,a);
			
			return pushup(o);
		}
		
		void modify(int o,int l,int r,int p,int q,ll val){
			if (p<=l&&r<=q){
				Xor(tree[o],val);
				tag[o]^=val;
				return;
			}
			
			if (tag[o]) pushdown(o);
			int mid=(l+r)>>1;
			if (p<=mid) modify(ls[o],l,mid,p,q,val);
			if (mid<q) modify(rs[o],mid+1,r,p,q,val);
			
			return pushup(o);
		}
		
		node query(int o,int l,int r,int p,int q){
			if (p<=l&&r<=q) return tree[o];
			if (tag[o]) pushdown(o);
			
			node res;int mid=(l+r)>>1;
			if (p<=mid) res=merge(res,query(ls[o],l,mid,p,q));
			if (mid<q) res=merge(res,query(rs[o],mid+1,r,p,q));
			
			return res;
		}
};

Segment_Tree sgt;

int n,q;ll a[N];

int main(){
	n=read();q=read();
	for(int i=1;i<=n;i++)
		a[i]=read()^((1ll<<60)-1);
	
	sgt.build(n,a);
	
	for(int i=1;i<=q;i++){
		int l,r,opt;
		
		opt=read();l=read();r=read();
		if (opt==1) sgt.modify(l,r,read());
		else{
			ll tmp=sgt.query(l,r).ans[1];
			if ((1ll*(r-l+1)*(r-l+2)/2)&1)
				tmp^=((1ll<<60)-1);
			printf("%lld\n",tmp);
		}
	}
	
	return 0;
}
```

---

