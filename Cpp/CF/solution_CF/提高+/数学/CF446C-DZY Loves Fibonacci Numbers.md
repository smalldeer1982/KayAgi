# DZY Loves Fibonacci Numbers

## 题目描述

In mathematical terms, the sequence $ F_{n} $ of Fibonacci numbers is defined by the recurrence relation

 $ F_{1}=1; F_{2}=1; F_{n}=F_{n-1}+F_{n-2} (n>2). $ DZY loves Fibonacci numbers very much. Today DZY gives you an array consisting of $ n $ integers: $ a_{1},a_{2},...,a_{n} $ . Moreover, there are $ m $ queries, each query has one of the two types:

1. Format of the query " $ 1\ l\ r $ ". In reply to the query, you need to add $ F_{i-l+1} $ to each element $ a_{i} $ , where $ l<=i<=r $ .
2. Format of the query " $ 2\ l\ r $ ". In reply to the query you should output the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF446C/9b1c73158dd7a4166f7d8fde16bb75f36899bc0e.png) modulo $ 1000000009 (10^{9}+9) $ .

Help DZY reply to all the queries.

## 说明/提示

After the first query, $ a=[2,3,5,7] $ .

For the second query, $ sum=2+3+5+7=17 $ .

After the third query, $ a=[2,4,6,9] $ .

For the fourth query, $ sum=2+4+6=12 $ .

## 样例 #1

### 输入

```
4 4
1 2 3 4
1 1 4
2 1 4
1 2 4
2 1 3
```

### 输出

```
17
12
```

# 题解

## 作者：AThousandSuns (赞：51)

学校模拟赛出了这道题……然后我想了个奇怪的做法居然过了……

别人的做法似乎都是把前缀和用斐波那契表示……我的做法是这样的：

斐波那契数有这样一个性质：$f_{n+m}=f_{n+1}f_m+f_{n}f_{m-1}$。

负的下标也没事。至于负的怎么求，可以通过后面的倒推，比如 $f_{-1}=f_1-f_0$。

那么考虑对 $[l,r]$ 修改是怎样的，发现对于一个位置 $x$，它加了 $f_{x-l+1}$。

拆开：$f_{x+1}f_{-l+1}+f_{x}f_{-l}$。

那么对于一个线段树节点，我们只需要维护区间和，和两个标记 $add1,add2$。$add1$ 表示这个点要加 $add1(f_{l+1}+f_{l+2}\dots f_{r+1})$，$add2$ 表示这个点要加 $add2(f_l+f_{l+1}+\dots+f_r)$。

那么修改和下推时就会简单很多。修改时，给 $add1$ 加上 $f_{1-l}$，给 $add2$ 加上 $f_{-l}$。下推时，直接让儿子的标记加上自己的标记即可。

如果还不懂可以看代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=333333,mod=1000000009;
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
    char ch=getchar();int x=0,f=0;
    while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}
int n,m,a[maxn],fib[maxn],pre[maxn],sum[maxn*4],add1[maxn*4],add2[maxn*4],rfib[maxn];
inline void pushup(int o){
    sum[o]=(sum[o<<1]+sum[o<<1|1])%mod;
}
inline void pushdown(int o,int l,int r){
    if(!add1[o] && !add2[o]) return;
    int mid=(l+r)>>1;
    add1[o<<1]=(add1[o<<1]+add1[o])%mod;
    add1[o<<1|1]=(add1[o<<1|1]+add1[o])%mod;
    add2[o<<1]=(add2[o<<1]+add2[o])%mod;
    add2[o<<1|1]=(add2[o<<1|1]+add2[o])%mod;	//给儿子下推标记
    sum[o<<1]=(sum[o<<1]+1ll*(pre[mid+1]-pre[l]+mod)%mod*add1[o]%mod)%mod;
    //加上add1(f_{l+1}+f_{l+2}+...+f_{r+1})
    sum[o<<1]=(sum[o<<1]+1ll*(pre[mid]-pre[l-1]+mod)%mod*add2[o]%mod)%mod;
    //加上add2(f_l+f_{l+1}+...+f_r)
    sum[o<<1|1]=(sum[o<<1|1]+1ll*(pre[r+1]-pre[mid+1]+mod)%mod*add1[o]%mod)%mod;
    sum[o<<1|1]=(sum[o<<1|1]+1ll*(pre[r]-pre[mid]+mod)%mod*add2[o]%mod)%mod;
    add1[o]=add2[o]=0;
}
void build(int o,int l,int r){
    if(l==r) return void(sum[o]=a[l]%mod);
    int mid=(l+r)>>1;
    build(lson);build(rson);
    pushup(o);
}
void update(int o,int l,int r,int ql,int qr,int a1,int a2){
    if(l>=ql && r<=qr){
        add1[o]=(add1[o]+a1)%mod;
        add2[o]=(add2[o]+a2)%mod;
        sum[o]=(sum[o]+1ll*(pre[r+1]-pre[l]+mod)%mod*a1%mod)%mod;
        sum[o]=(sum[o]+1ll*(pre[r]-pre[l-1]+mod)%mod*a2%mod)%mod;
        //直接加上
        return;
    }
    pushdown(o,l,r);
    int mid=(l+r)>>1;
    if(mid>=ql) update(lson,ql,qr,a1,a2);
    if(mid<qr) update(rson,ql,qr,a1,a2);
    pushup(o);
}
int query(int o,int l,int r,int ql,int qr){
    if(l>=ql && r<=qr) return sum[o];
    pushdown(o,l,r);
    int mid=(l+r)>>1,ans=0;
    if(mid>=ql) ans=(ans+query(lson,ql,qr))%mod;
    if(mid<qr) ans=(ans+query(rson,ql,qr))%mod;
    return ans;
}
int main(){
    n=read();m=read();
    FOR(i,1,n) a[i]=read();
    fib[1]=fib[2]=pre[1]=rfib[1]=1;
    rfib[0]=0;
    pre[2]=2;
    rfib[2]=mod-1;
    FOR(i,3,n+1){
        fib[i]=(fib[i-1]+fib[i-2])%mod;	//斐波那契数
        pre[i]=(pre[i-1]+fib[i])%mod;	//斐波那契前缀和
        rfib[i]=(i&1)?fib[i]:mod-fib[i];	//rfib[i]表示第-i个斐波那契数
    }
    build(1,1,n);
    FOR(i,1,m){
        int op=read(),l=read(),r=read();
        if(op==2) printf("%d\n",query(1,1,n,l,r));
        else update(1,1,n,l,r,rfib[l-1],rfib[l]);
        //add1加上f_{1-l}，add2加上f_{-l}
    }
}

```

---

## 作者：81179332_ (赞：40)

这道题可以不用斐波那契的前缀和公式。

直接写出斐波那契的通项式为
$$F_n=\dfrac{1}{\sqrt5}[(\dfrac{1+\sqrt5}{2})^n-(\dfrac{1-\sqrt5}{2})^n]$$

然后可以直接转化为线段树维护区间加等比数列，直接套等比数列求和公式即可。

$\sqrt5$ 在 $\bmod 10^9+9$ 意义下有二次剩余为 $383008016$，所以就不用扩域啦。

然后就做完了，代码看上去很长，但是很好写，没debug就过了。

```cpp
#include<cstdio>
#include<cctype>
#define pprint(x) ::print(x),putchar(' ')
#define fprint(x) ::print(x),putchar('\n')
using namespace std;
inline long long read()
{
	long long x = 0;int f = 1;
	char ch = getchar();
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-')
			f = -1;
	for(;isdigit(ch);ch = getchar())
		x = x * 10 + (ch ^ 48);
	return x * f;
}
void print(long long x)
{
	if(x < 0)
		x = -x,putchar('-');
	if(x > 9)
		print(x / 10);
	putchar(x % 10 + '0');
}

const int N = 300010,mod = 1000000009,q1 = 691504013,q2 = 308495997,Inv = 276601605;

long long qpow(long long a,int b)
{
	long long ans = 1;
	while(b)
	{
		if(b & 1) ans = ans * a % mod;
		b >>= 1,a = a * a % mod;
	}
	return ans;
}
long long Mod(long long a)
{
	if(a > mod)
		a -= mod;
	else if(a < 0)
		a += mod;
	return a;
}

int n,m;

struct Seg_Tree
{
	long long q,inv,m[N];
	struct tree
	{
		int l,r;
		long long sum,lz;
	}t[N << 2];

	#define ls now << 1
	#define rs now << 1 | 1

	void build(int now,int l,int r)
	{
		t[now].l = l,t[now].r = r;
		t[now].sum = t[now].lz = 0;
		if(l == r)
			return;
		int mid = l + r >> 1;
		build(ls,l,mid),build(rs,mid + 1,r);
	}
	void init(int Q)
	{
		q = Q,inv = qpow(q - 1,mod - 2);
		m[1] = q;
		for(int i = 2;i <= n;i++)
			m[i] = m[i - 1] * q % mod;
		build(1,1,n);
	}

	void pusha(int now,long long a)
	{
		int l = t[now].l,r = t[now].r;
		t[now].lz = Mod(t[now].lz + a);
		t[now].sum = (t[now].sum + Mod(a * m[r - l + 1] % mod - a) * inv) % mod;
	}
	void pushdown(int now)
	{
		if(t[now].lz)
		{
			int l = t[now].l,r = t[now].r,mid = l + r >> 1;
			pusha(ls,t[now].lz);
			pusha(rs,t[now].lz * m[mid - l + 1] % mod);
			t[now].lz = 0;
		}
	}
	void pushup(int now)
	{
		t[now].sum = Mod(t[ls].sum + t[rs].sum);
	}
	void update(int now,int l,int r,int a)
	{
		if(t[now].l == l && t[now].r == r)
		{
			pusha(now,a);
			return;
		}
		pushdown(now);
		int mid = t[now].l + t[now].r >> 1;
		if(r <= mid)
			update(ls,l,r,a);
		else if(l > mid)
			update(rs,l,r,a);
		else
			update(ls,l,mid,a),update(rs,mid + 1,r,a * m[mid - l + 1] % mod);
		pushup(now);
	}
	long long query(int now,int l,int r)
	{
		if(t[now].l == l && t[now].r == r)
			return t[now].sum;
		pushdown(now);
		int mid = t[now].l + t[now].r >> 1;
		if(r <= mid)
			return query(ls,l,r);
		else if(l > mid)
			return query(rs,l,r);
		else
			return Mod(query(ls,l,mid) + query(rs,mid + 1,r));
		pushup(now);
	}

	#undef ls
	#undef rs
};

Seg_Tree t1,t2;
long long sum[N];

int main()
{
	n = read(),m = read();
	for(int i = 1;i <= n;i++)
		sum[i] = Mod(sum[i - 1] + read());
	t1.init(q1),t2.init(q2);
	while(m--)
	{
		int op = read(),l = read(),r = read();
		if(op == 1)
			t1.update(1,l,r,q1),t2.update(1,l,r,q2);
		else
		{
			long long a = t1.query(1,l,r);
			long long b = t2.query(1,l,r);
			a = Mod(a - b) * Inv % mod;
			fprint(Mod(Mod(a - sum[l - 1]) + sum[r]) % mod);
		}
	}
	return 0;
}
```

---

## 作者：Dzhao (赞：24)

# 题解 CF446C
这是一道数据结构题。

我们先翻译下题目：

给你一个n，给你一个长度为n的序列，给你一个m，给你m此操作，包括区间修改和查询，修改为在一个区间内每个数加上他所对应的斐波那契数，查询为查询区间和。

一看到区间修改和区间查询，我们就可以知道这是一道线段树的题目（不要问我怎么知道的，~~我也想知道~~）

进入正题：

我们一定要找到一种方法，维护区间和。

我们可以先把斐波那契数列的每一项拆开，找规律，我们会发现：

$$f_1=f_1,f_2=f_2$$
$$f_3=f_1+f_2,f_4=f_1+2*f_2$$
$$f_5=2*f_1+3*f_2,f_6=3*f_1+5*f_2$$

我们可以找到规律

$$f_i=f_{i-1}*f_2+f_{i-2}*f_1$$

因为在区间内加入一个斐波那契数列，这个区间任然满足斐波那契数列的关系，只是$f_1$和$f_2$变了而已，所以，我们可以用{a}来维护这个斐波那契数列，即可表示为：

$$a_i=f_{i-1}*a_2+f_{i-2}*a_1$$

因为是维护区间和，所以我们需要累加和，故，我们再将式子拆开，可以得到：

$$s_3=2*a_1+2*a_2$$
$$s_4=3*a_1+4*a_2$$
$$s_5=5*a_1+7*a_2$$

经过观察和归纳，我们可以发现：

$$\sum_ {i=1}^n a_i = f_n*a_1+(f_{n+1}-1)*a_2$$

于是我们就可一开始做这道题了。

我们用两个懒惰标记，分别为$f1$和$f2$，来维护某一段区间的和，当我们要求这段区间的和时，我们只要用上面那个公式求出区间和，然后加入值中就行了。

---------------------------------------------------我是~~超级可爱~~的分割线-------------------------------------------------

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=300009;
const ll P=1e9+9;
int n,m;
ll f[N];
struct Segtree
{
	ll v,f1,f2;
}tree[N<<2];
inline ll read()
{
	ll x=0,flag=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-') ch=getchar();flag=-1;}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*flag;
}
void build(int k,int l,int r)
{
	if(l==r)
	{
		tree[k].v=read();
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tree[k].v=tree[k<<1].v+tree[k<<1|1].v;
	tree[k].v%=P;
}
void push_down(int k,int l,int r) //标记下传 
{
	if(!(tree[k].f1==0 && tree[k].f2==0))
	{
		int mid=(l+r)>>1;
		tree[k<<1].f1+=tree[k].f1;
		tree[k<<1].f1%=P;
		tree[k<<1].f2+=tree[k].f2;
		tree[k<<1].f2%=P;
		tree[k<<1].v+=tree[k].f2*(f[mid-l+2]-1)+tree[k].f1*f[mid-l+1];
		tree[k<<1].v%=P; 
		int pos=mid-l+2;
		tree[k<<1|1].f1+=f[pos-1]*tree[k].f2+f[pos-2]*tree[k].f1;
		tree[k<<1|1].f1%=P;
		tree[k<<1|1].f2+=f[pos]*tree[k].f2+f[pos-1]*tree[k].f1;
		tree[k<<1|1].f2%=P;
		tree[k<<1|1].v+=tree[k].f2*(f[r-l+2]-1)+tree[k].f1*f[r-l+1]-tree[k].f2*(f[mid-l+2]-1)-tree[k].f1*f[mid-l+1];
		tree[k<<1|1].v%=P;
		tree[k].f1=0,tree[k].f2=0;
	}
}
void modify(int k,int l,int r,int x,int y)
{
	if(l>y || r<x) return;
	if(l>=x && r<=y) 
	{
		tree[k].f1+=f[l-x+1];
		tree[k].f1%=P;
		tree[k].f2+=f[l-x+2];
		tree[k].f2%=P;
		tree[k].v+=f[r-l+1]*f[l-x+1]%P+(f[r-l+2]-1)*f[l-x+2]%P; 
		tree[k].v%=P;
		return;
	}
	int mid=(l+r)>>1;
	push_down(k,l,r);
	modify(k<<1,l,mid,x,y);
	modify(k<<1|1,mid+1,r,x,y);
	tree[k].v=tree[k<<1].v+tree[k<<1|1].v;
	tree[k].v%=P;
}
void init()
{
	f[1]=1,f[2]=1;
	for(int i=3;i<=n+1;i++) f[i]=f[i-1]+f[i-2],f[i]%=P;
}
ll query(int k,int l,int r,int x,int y)
{
	if(l>y || r<x) return 0;
	if(l>=x && r<=y) return tree[k].v;
	push_down(k,l,r);
	int mid=(l+r)>>1;
	return (query(k<<1,l,mid,x,y)+query(k<<1|1,mid+1,r,x,y))%P;
}

int main()
{
	n=read();m=read();
	build(1,1,n);
	init();
	for(int i=1;i<=m;i++)
	{
		int t=read(),x=read(),y=read();
		if(t==1) modify(1,1,n,x,y);
		else printf("%lld\n",(query(1,1,n,x,y)%P+P)%P);
	}
	return 0;
}
```

~~垃圾数据结构~~

---

## 作者：Treaker (赞：19)

$$\color{cornflowerblue}{\mathcal{Treaker}}$$
# 线段树 + 斐波那契数列
盯了3个小时，终于研究透彻了。。。

这道题，需要区间修改，区间查询，自然会想到线段树。。

其实区间加是很好维护的，但是下放标记是什么鬼。。

斐波那契数列的系数直接加？？？~~显然不对嘛~~

怎么办啊。。

我们考虑广义斐波那契数列$s_i$。

$$s_i  = a * f_{i-2} + b * f_{i-1}$$

并且有一个神奇的性质。
$$\sum_{i=1} ^ n s_i= s_{n+2} - s_2$$
这个是通过数学归纳法来证明的。具体的话就是这样。

我们设 
$$S_n = \sum_{i=1}^n s_i$$
则
$$S_n=S_{n-1} + s_i = s_{n+1} - s_2 + s_i = s_{n+2}-s_2$$


结合最上面的式子
$$S_n=\sum_{i=1} ^ n s_i= s_{n+2} - s_2 = a * s_n + b * s_{n+1} - b$$

那我们区间加也就是加上 $S_n$

那么怎么求$S_n$呢？ $f~$可以预处理 ， 关键就是求$a,b$。

$a,b$也就是$s_1,s_2$。 对于每个区间维护$s_1,s_2$。 

也就是区间的前两个位置。

区间修改时让$s_1,s_2$加上它所对应的位置的值，并更新区间和。
```cpp
inline void add(ll a,ll b)
{
     tag = (tag + a) % mod; laz = (laz + b) % mod;
     sum = (sum + a * f[len()] % mod + b * f[len() + 1] % mod - b) % mod;
}
```
考虑标记如何下放。

我的一个区间要往两个小区间里下放标记。

左区间的$s_1,s_2$位置和大区间对应，直接下放即可。

右区间我们需要求出来。也就是用通项公式来求。
```cpp
inline void down()
{
  if(!tag) return;
  ll tmpa = (tag * f[ls -> len() - 1] % mod + laz * f[ls -> len()] % mod) % mod;
  ll tmpb = (tag * f[ls -> len()] % mod + laz * f[ls -> len() + 1] % mod) % mod;
  ls -> add(tag,laz); rs -> add(tmpa,tmpb);
  tag = laz = 0;
}
```
然后其他操作就很常规。

完整代码如下：
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#define ll long long
using namespace std;
const int N = 3e5+10 , inf = 1e9 , M = 3e5 + 5;
const ll mod = 1e9+9;
inline int read()
{
	int x = 0 , f = 1;	char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
int n , m;
ll f[N];
struct Segment_Tree
{
	inline void init()
	{
		f[0] = 0; f[1] = 1;
		for(int i = 2;i <= M;i ++) f[i] = (f[i-2] + f[i-1]) % mod;
	}
	struct node
	{
		node *ls , *rs;
		int l , r; ll sum , tag , laz;
		node(int l,int r) : l(l) , r(r) {ls = rs = NULL; tag = laz = sum = 0;}
        inline int len() {return r - l + 1;}
		inline void up() {sum = (ls -> sum + rs -> sum) % mod;}
        inline void add(ll a,ll b)
        {
            tag = (tag + a) % mod; laz = (laz + b) % mod;
            sum = (sum + a * f[len()] % mod + b * f[len() + 1] % mod - b) % mod;
        }
		inline void down()
		{
			if(!tag) return;
            ll tmpa = (tag * f[ls -> len() - 1] % mod + laz * f[ls -> len()] % mod) % mod;
            ll tmpb = (tag * f[ls -> len()] % mod + laz * f[ls -> len() + 1] % mod) % mod;
            ls -> add(tag,laz); rs -> add(tmpa,tmpb);
			tag = laz = 0;
		}
 	}*root;
	Segment_Tree() {root = NULL;}
    #define mid ((p -> l + p -> r) >> 1)
	void build(node *&p,int l,int r)
	{
		p = new node(l,r);
		if(p -> l == p -> r) return (void)(p -> sum = 1ll * read() % mod);
		build(p -> ls,l,mid); build(p -> rs,mid+1,r); p -> up();
	}
	ll query(node *p,int x,int y)
	{
		if(x <= p -> l && p -> r <= y) return p -> sum; p -> down();
		return ((x <= mid ? query(p -> ls,x,y) : 0) + (y > mid ? query(p -> rs,x,y) : 0)) % mod;
	}
	void chenge(node *p,int x,int y)
	{
		if(x <= p -> l && p -> r <= y) return (void)(p -> add(f[p -> l - x + 1],f[p -> l - x + 2]));
        p -> down();
		if(x <= mid) chenge(p -> ls,x,y);
		if(y > mid) chenge(p -> rs,x,y);
		p -> up();
	}
	inline void LOL()
	{
		init();
		n = read(); m = read();
		build(root,1,n);
		for(int i = 1 , opt , l , r , x;i <= m;i ++)
		{
			opt = read(); l = read(); r = read();
			if(opt ^ 1) printf("%lld\n",(query(root,l,r) + mod) % mod);	
			else chenge(root,l,r);
		}
	}
}DNF;
int main()
{
	DNF.LOL();
	return 0;
}
```

---

## 作者：HenryHuang (赞：18)

### 「CF446C」 DZY Loves Fibonacci Numbers

这里提供一种优美的根号分治做法。

首先，我们考虑一种不太一样的暴力。对于一个区间加斐波那契数的操作 $[a,b]$，以及一个区间求和的操作 $[p,q]$，仅需预处理斐波那契数列前缀和，我们就可以在 $O(1)$ 的时间内算出 $[a,b]$ 对 $[p,q]$ 的贡献。

这样的复杂度为 $O(n^2)$。

再考虑传统暴力：对于一个区间加斐波那契数的操作 $[a,b]$，直接将其作用到原数列 $a$ 上。

那么我们可不可以将多个区间加斐波那契数的操作一起作用到原数列上呢？

答案是肯定的。

首先有一个显然的结论：若 $a_i=a_{i-1}+a_{i-2},b_j=b_{j-1}+b_{j-2}$，则有 $a_i+b_j=a_{i-1}+a_{i-2}+b_{j-1}+b_{j-2}$。

这启发我们可以对于多次区间加操作同时进行递推。

我们维护每个区间加操作的起止点，在操作开始时加入数 $1$ 进行递推，操作结束时删除该操作所用到的两个数，就可以在 $O(n)$ 的时间内将多次操作同时进行。

具体可见代码，非常清晰。

若我们每 $T$ 次操作后将当前的多个区间加斐波那契数的操作一起作用到原数列上，其余时候暴力，这样的最坏复杂度为 $O(\frac{n^2}{T}+Tn)$。取 $T=\sqrt n $ 时复杂度最优，为 $O(n\sqrt n)$。虽在理论复杂度上逊于线段树解法，但其常数小，代码复杂度低，实际表现与实现一般的线段树相差无几甚至略优，不失为一种良好的解题方式。

同时注意，块长的调整可能会使该算法的效率进一步提升，因为显然 $O(Tn)$ 部分是达不到上界的，故代码对于重构的实现方式与题解略有不同。

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int p=1e9+9;
const int maxn=3e5+5;
int fib[maxn],sum[maxn];
int b[maxn],v[maxn],val[maxn];
int l[maxn],r[maxn],tot;
int n,m;
int md(int x){
	if(x>p) return x-p;
	if(x<0) return x+p;
	return x;
}
vector<int> p1[maxn],p2[maxn];
void rebuild(){
	for(int i=1;i<=tot;++i){
		p1[l[i]].emplace_back(i);
		p2[r[i]].emplace_back(i);
	}
	int a=0,b=0;
	for(int i=1;i<=n;++i){
		int c=md(a+b);
		val[i]=md(val[i]+c);
		a=b,b=c;
		for(auto x:p1[i]) b=md(b+1),val[i]=md(val[i]+1);
		for(auto x:p2[i]){
			int L=l[x],R=r[x];
			b=md(b-fib[R-L+1]);
			a=md(a-fib[R-L]);
		}
		v[i]=md(v[i-1]+val[i]);
	}
	for(int i=1;i<=tot;++i){
		p1[l[i]].clear();
		p2[r[i]].clear();
	}
	tot=0;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	fib[1]=1,fib[2]=1;
	for(int i=3;i<=n;++i) fib[i]=md(fib[i-1]+fib[i-2]);
	for(int i=1;i<=n;++i) sum[i]=md(sum[i-1]+fib[i]);
	for(int i=1;i<=n;++i) cin>>val[i],v[i]=md(v[i-1]+val[i]);
	int lim=sqrt(m);
	for(int _=1;_<=m;++_){
		int opt,a,b;cin>>opt>>a>>b;
		if(opt==1) l[++tot]=a,r[tot]=b;
		else{
			int ans=0;
			for(int i=1;i<=tot;++i){
				int L=max(a,l[i]),R=min(b,r[i]);
				if(L<=R){
					ans=md(ans+md(sum[R-l[i]+1]-sum[L-l[i]]));
					if(ans>p) ans-=p;
				}
			}
			cout<<md(ans+md(v[b]-v[a-1]))<<'\n';
		}
		if(tot==lim) rebuild();
	}
	return 0;
}
```





---

## 作者：xiaohuang (赞：15)

[更好的阅读体验](https://xiaohuang888.github.io/2019/08/02/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces446C%20DZY%20Loves%20Fibonacci%20Numbers)

### Solution

一些约定：把斐波那契数列的前两个数$F_1 = 1, F_2 = 1$换成另两个数，仍满足$F_n = F_{n - 1} + F_{n - 2}(n > 2)$的数列称为广义斐波那契数列。

`Fibonacci`数列有一些性质：

性质$1$. $F_n = (\sum^{n - 2}_{i = 1}{F_i}) + F_2(n > 2)$；

证明如下：

首先将前几项`Fibonacci`数列展开。

```
F(1) = 1
F(2) = 1
F(3) = F(1) + F(2)
F(4) = F(2) + F(3) = F(2) + F(1) + F(2)
F(5) = F(3) + F(4) = F(3) + F(2) + F(1) + F(2)
F(6) = F(4) + F(5) = F(4) + F(3) + F(2) + F(1) + F(2)
......
```

在$F_n = F_{n - 1} + F_{n - 2}$中，我们可以把$F_{n - 1}$按式子展开，可得$F_n = \sum^{n - 3}_{i = 1}{F_i} + F_2 + F_{n - 2}$，即$F_n = (\sum^{n - 2}_{i = 1}{F_i}) + F_2(n > 2)$，跟原式一模一样，故原式正确性得证。

性质$2$. 一个广义斐波那契数列数列$f_i$， 当$f_1 = x, f_2 = y$时，则有$f_n = x \times f_{n - 1} + y \times f_{n - 2}$

证明如下：

这个性质与性质`1`类似，证明方法也与性质`1`类似，列举几个：

```
f(1) = x
f(2) = y
f(3) = f(1) + f(2) = x × F(1)
f(4) = f(2) + f(3) = x × F(1) + y × F(2)
f(5) = f(3) + f(4) = x × F(2) + y × F(3)
f(6) = f(4) + f(5) = x × F(3) + y × F(4)
......
```

把上述规律推广到代数式：

$$\begin{aligned} f_n &= f_{n - 1} + f_{n - 2} \\ & = x \times f_{n - 2} + y \times f_{n - 3} + x \times f_{n - 3} + y \times f_{n - 4} \\ & = x \times (f_{n - 2} + f_{n - 3}) + y \times (f_{n - 3} + f_{n - 4}) \\ & = x \times f_{n - 1} + y \times f_{n - 2} \end{aligned}$$

证毕。

性质$3$. 任意两段不同的广义斐波那契数列段相加（逐项相加），所得的数列任然是广义斐波那契数列。

这个性质易证。

---

这题我们维护一棵线段树，线段树需要维护$L$至$R$区间的广义斐波那契数列的第一项，第二项与区间的和。

下传标记时，我们可以在左区间加广义斐波那契数列的前两项，在右区间可以求出总和再加上总和就行了，时间复杂$\text{O(n log n)}$。

### Code

```
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

typedef long long LL;
const int MAXN = 300005, MAXM = 1200005, mod = 1e9 + 9;
struct node {
    int c1, c2, sum;
} tree[MAXM];
int n, m, opt, x, y, a[MAXN], f[MAXN];
inline int add(int x, int y) {//两项相加并取模
    int ret = x + y;
    if (ret < 0) return ret += mod; else return ret % mod;
}
inline int calc1(int x, int y, int len) {//计算斐波那契
    if (len == 1) return x; else
    if (len == 2) return y; else return ((LL)x * f[len - 2] + (LL)y * f[len - 1]) % mod;
}
inline int calc2(int x, int y, int len) {//计算总和
    if (len == 1) return x; else
    if (len == 2) return add(x, y); else return add(calc1(x, y, len + 2), -y);
}
inline void pushup(int rt) {
    tree[rt].sum = add(tree[rt << 1].sum, tree[rt << 1 | 1].sum);
}
inline void pushdown(int rt, int l, int r) {//下传标记
    if (tree[rt].c1) {
        int mid = l + r >> 1;
        tree[rt << 1].c1 = add(tree[rt << 1].c1, tree[rt].c1);
        tree[rt << 1].c2 = add(tree[rt << 1].c2, tree[rt].c2);
        tree[rt << 1].sum = add(tree[rt << 1].sum, calc2(tree[rt].c1, tree[rt].c2, mid - l + 1));
        int x = calc1(tree[rt].c1, tree[rt].c2, mid - l + 2), y = calc1(tree[rt].c1, tree[rt].c2, mid - l + 3);
        tree[rt << 1 | 1].c1 = add(tree[rt << 1 | 1].c1, x);
        tree[rt << 1 | 1].c2 = add(tree[rt << 1 | 1].c2, y);
        tree[rt << 1 | 1].sum = add(tree[rt << 1 | 1].sum, calc2(x, y, r - mid));
        tree[rt].c1 = 0; tree[rt].c2 = 0;
    }
}
inline void update(int rt, int l, int r, int ansl, int ansr) {//线段树区间更新
    if (ansl <= l && r <= ansr) {
        tree[rt].c1 = add(tree[rt].c1, f[l - ansl + 1]);
        tree[rt].c2 = add(tree[rt].c2, f[l - ansl + 2]);
        tree[rt].sum = add(tree[rt].sum, calc2(f[l - ansl + 1], f[l - ansl + 2], r - l + 1));
        return ;
    }
    pushdown(rt, l, r);
    int mid = l + r >> 1;
    if (ansl <= mid) update(rt << 1, l, mid, ansl, ansr);
    if (ansr > mid) update(rt << 1 | 1, mid + 1, r, ansl, ansr);
    pushup(rt);
}
inline int query(int rt, int l, int r, int ansl, int ansr) {//线段树区间查询
    int ret = 0;
    if (ansl <= l && r <= ansr) {
        ret = tree[rt].sum;
        return ret;
    }
    pushdown(rt, l, r);
    int mid = l + r >> 1;
    if (ansl <= mid) ret = add(ret, query(rt << 1, l, mid, ansl, ansr));
    if (ansr > mid) ret = add(ret, query(rt << 1 | 1, mid + 1, r, ansl, ansr));
    return ret;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        a[i] = add(a[i - 1], x);
    }
    f[1] = 1; f[2] = 1;
    for (int i = 3; i <= n + 2; i++)
        f[i] = add(f[i - 1], f[i - 2]);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1) update(1, 1, n, x, y); else printf("%d\n", add(query(1, 1, n, x, y), a[y] - a[x - 1]));
    }
    return 0;
}
```

---

## 作者：EndSaH (赞：9)

[日常推广博客](https://endsah.cf)

# $\text{Description}$

给定数列 $a_1,a_2,\cdots,a_n$.

需要支持两种操作:

+ `1 l r`: 对 $l$ 到 $r$ 的每个数 $a_i$ 加上 $Fib_{i - l + 1}$.
+ `2 l r`: 询问区间 $l$ 到 $r$ 的和.

$Fib$ 即斐波那契数列,  此处 $Fib_1 = Fib_2 = 1$.

$n \le 3 \ast 10^5$, 答案对 $10^9 + 9$ 取模.

# $\text{Solution}$

对于这种区间修改和区间求和, 首先想到线段树.

但是该如何打标记, 这才是最关键的问题.

单单是维护区间和挺简单的:

对于一个修改操作, 记录 $Fib$ 数列的前缀和, 每次对应的加上就可以了.

具体来说, 设当前需要修改的线段树节点对应区间为 $[l, r]$, 修改区间为 $[L, R]$ (~~显然~~, $[l, r] \subseteqq [L, R]$)

那么当前区间应该加上的值是: $sum_{r - L + 1} - sum_{l - L}$

$sum$ 表示 $Fib$ 数列的前缀和.

`Pushdown`操作同理, 只不过是 $L=l, R=r$.

但这么做有个问题: **如何快速合并标记呢**?

我可能是那个头最铁的人, 想到这个思路直接开打, 直接**不合并标记**, 而是用一个`std::stack`存放所有标记, `Pushdown`再一个个下放... 可想而知这样的程序效率是多低, $5 \ast 10^4$ 的数据都跑了 $\text{3s}$ ...

那么, 我们是时候稍微转变一下标记的维护思路了.

在此之前, 你需要先了解[**广义斐波那契数列**](https://baike.baidu.com/item/%E5%B9%BF%E4%B9%89Fibonacci%E6%95%B0%E5%88%97).

通俗的来讲, 就是把 $Fib$ 数列的第一项和第二项变为 $a$ 和 $b$, 而不再是固定的 $1,1$.

它有一些非常优美的性质:

$$\sum_{i = 1}^nS_i=S_{n+2}-S_2$$
$$S_i=bFib_{i - 1}+aFib_{i - 2}$$

$S$ 即为广义 $Fib$ 数列, $S_1 = a, S_2 = b$.

~~证明? 自己想去~~

于是考虑记录广义 $Fib$ 数列的前两项作为懒标记.

为什么? 因为这样就可以**快速合并**了!

> **要合并(对应数各自相加)两个广义 $Fib$ 数列, 只需要将 $a$ 和 $b$ 各自相加即可.**

上面这句话请着重注意!  ~~证明是不存在的~~

因为它的这些性质, 那么合并标记, 快速求和等等一系列问题, 我们已经全部解决了.

接下来, 就是恶心的各类细节操作了- -

详见[代码](https://www.luogu.org/paste/4kxm4tgf).

重点看几个函数: `Add`, `Pushdown`, `Change中return部分`.

# $\text{Thank you for your consideration!}$

---

## 作者：Erusel (赞：7)

CF446C

题意翻译:

题面大意：给出一个数列，每次可以选取一个区间，按顺序加上第$i$个$Fibonacci Numbers$(斐波那契数)进行更新，也可以查询某一个区间的总和。

这题虽然是黑题，其实并不难

我们只要思考几件事：

1.线段树的标记下传（$pushdown$）能不能在$O(1)$内完成

2.线段树更新$sum$能不能在$O(1)$内完成

对于1，前文提到$f[n]=g[n-1]*a+g[n-2]*b$

对于2，这里再提一个性质：

令$s[i]=\sum_{i=1}^{n}f[i]$

$s[i]=f[n+2]-f[2]$

这个定理的证明

还是用数学归纳法。。。

显然当$i=1$时，原命题成立

设$i=k$时，原命题成立。

$s[k+1]=s[k]+f[k+1]=f[k+2]-f[2]+f[k+1]=f[k+3]-f[2]$

$\therefore$ 原命题成立

便能实现再$O(1)$内完成更新$sum$了

代码：

```
#include<bits/stdc++.h>

#define rd(x) x=read()
#define N 300005
#define ls rt<<1
#define rs rt<<1|1

using namespace std;

typedef long long ll;

ll n,m;
struct T{
	ll f1,f2,v;
}t[N*20];
ll a[N],f[N],sum[N];
const ll mod=1e9+9;

inline ll read()
{
    ll f=1,x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    return x*f;
}

void init()
{
	f[1]=1,f[2]=1;
	for(ll i=3;i<=n+1;i++)f[i]=(f[i-2]+f[i-1])%mod;
}//预处理斐波那契

void pushup(ll rt,ll pos)
{
	t[rt].f1%=mod,t[rt].f2%=mod;
	t[rt].v=t[ls].v+t[rs].v+(t[rt].f1*f[pos]+t[rt].f2*f[pos+1]-t[rt].f2),t[rt].v%=mod;
}//更新rt

void pushdown(ll rt,ll l,ll r)
{
	if(t[rt].f1==0&&t[rt].f2==0)return ;
	ll mid=(l+r)>>1;
	t[ls].f1+=t[rt].f1,t[rs].f1+=t[rt].f1*f[mid-l]+t[rt].f2*f[mid-l+1];
	t[ls].f2+=t[rt].f2,t[rs].f2+=t[rt].f1*f[mid-l+1]+t[rt].f2*f[mid-l+2];
	t[rt].f1=t[rt].f2=0;
	pushup(ls,mid-l+1),pushup(rs,r-mid); 
} //标记下传

void update(ll rt,ll l,ll r,ll L,ll R)
{
	if(L<=l&&r<=R)//边界条件
	{
		t[rt].f1+=f[l-L+1];
		t[rt].f2+=f[l-L+2];
		t[rt].f1%=mod,t[rt].f2%=mod;
		pushup(rt,r-l+1);
		return ;
	}
	pushdown(rt,l,r);
	ll mid=(l+r)>>1;
	if(L<=mid)update(ls,l,mid,L,R);
	if(mid<R)update(rs,mid+1,r,L,R);
	pushup(rt,r-l+1);
}//区间加斐波那契数列

ll query(ll rt,ll l,ll r,ll L,ll R)
{
	if(L<=l&&r<=R)return t[rt].v;
	pushdown(rt,l,r);
	ll res=0;
	ll mid=(l+r)>>1;
	if(L<=mid)res+=query(ls,l,mid,L,R);
	if(mid<R)res+=query(rs,mid+1,r,L,R);
	return res%mod;
}//查询和

int main()
{
	rd(n),rd(m);
	init();
	for(ll i=1;i<=n;i++)rd(a[i]),sum[i]=sum[i-1]+a[i];//预处理前缀和
	while(m--)
	{
		ll opt,l,r;
		rd(opt),rd(l),rd(r);
		if(opt==1)update(1,1,n,l,r);
		else printf("%lld\n",(query(1,1,n,l,r)+sum[r]-sum[l-1]+mod)%mod);
	}
	
		
    return 0;
}
```

---

## 作者：gzw2005 (赞：6)

### 第一步：找递推式！

发现一开始的 $a_i$ 是假的，最后加上前缀和就行。我们设一开始的数列 $f_i=0$，并满足以下条件：

设 $f_i=f_{i-1}+f_{i-2}+v_i$，一开始所有的 $v_i=0$。然后每一次对 $[l,r]$ 做区间 $fib$ 加时:

- 令 $v_l$ 加上 $1$；
- 令 $v_{r+1}$ 减去 $fib_{r-l}+fib_{r-l+1}$；
- 令 $v_{r+2}$ 减去 $fib_{r-l+1}$；

有点像差分的思想。可以这样做的原因是两个不同位置的斐波那契数列相加仍然满足递推式。

### 第二步：求前缀和！

现在递推的问题已经解决了，问题是求出区间总和，可以拆成两个前缀相减。推推柿子：

$$\begin{aligned}
s_i&=s_{i-1}+f_i\\
&=s_{i-1}+f_{i-1}+f_{i-2}+v_i\\
&=s_{i-1}+(s_{i-1}-s_{i-2})+(s_{i-2}-s_{i-3})+v_i\\
&=2s_{i-1}-s_{i-3}+v_i
\end{aligned}$$

### 第三步：填写矩阵！

看到递推，要快速求出某一项的值，自然可以想到用矩阵乘法来搞。

因为 $s_i$ 和 $s_{i-1},s_{i-3}$ 有关，而且有一个常数 $v_i$，所以矩阵要填四个数：

$$\begin{bmatrix} s_{i-1} & s_{i-2} & s_{i-3} & 1\end{bmatrix}
\times
\begin{bmatrix}
2&1&0&0\\
0&0&1&0\\
-1&0&0&0\\
v_i&0&0&1
\end{bmatrix}
=
\begin{bmatrix} s_{i} & s_{i-1} & s_{i-2} & 1\end{bmatrix}
$$

可见初始矩阵是 $\begin{bmatrix} 0 & 0 & 0 & 1\end{bmatrix}$，只要用初始矩阵乘上前 $i$ 个转移矩阵，第一行第一个数就是 $s_i$。

因为要支持单点修改，使用线段树维护矩阵乘法即可。

时间复杂度 $O(64·(n+m)\log m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Matrix {
	int f[4][4];
	Matrix() {
		memset(f,0,sizeof(f));
	}
};
const int mod=1e9+9;
void add(int &a,int b) {
	(a+=b)>=mod && (a-=mod);
}
Matrix operator *(Matrix a,Matrix b) {
	Matrix c;
	for(int i=0; i<4; i++)
		for(int k=0; k<4; k++)
			if(a.f[i][k])
				for(int j=0; j<4; j++)
					add(c.f[i][j],1ll*a.f[i][k]*b.f[k][j]%mod);
	return c;
}
int N,M;
const int MAXN=3e5+10;
int a[MAXN];
struct SegmentTree {
	Matrix c[MAXN<<2];
	void buildTree(int L,int R,int x) {
		if(L==R) {
			c[x].f[0][0]=2;
			c[x].f[2][0]=-1;
			c[x].f[0][1]=1;
			c[x].f[1][2]=1;
			c[x].f[3][3]=1;
			return ;
		}
		int mid=(L+R)>>1;
		buildTree(L,mid,x<<1);
		buildTree(mid+1,R,(x<<1)|1);
		c[x]=c[x<<1]*c[(x<<1)|1]; 
	}
	void update(int L,int R,int x,int pos,int val) {
		if(L==R) {
			add(c[x].f[3][0],val);
			return ;
		}
		int mid=(L+R)>>1;
		if(pos<=mid) update(L,mid,x<<1,pos,val);
		else update(mid+1,R,(x<<1)|1,pos,val);
		c[x]=c[x<<1]*c[(x<<1)|1];
	}
	Matrix query(int L,int R,int x,int r) {
		if(R<=r) return c[x];
		int mid=(L+R)>>1;
		if(r<=mid) return query(L,mid,x<<1,r);
		else return c[x<<1]*query(mid+1,R,(x<<1)|1,r);
	}
} st;
int fib[MAXN]={0,1,1};
int main() {
	scanf("%d%d",&N,&M);
	for(int i=3; i<=N; i++)
		(fib[i]=fib[i-1]+fib[i-2])>=mod && (fib[i]-=mod);
	for(int i=1; i<=N; i++) {
		scanf("%d",&a[i]);
		(a[i]+=a[i-1])>=mod && (a[i]-=mod);
	}
	st.buildTree(1,N,1);
	int opt,l,r,Ans;
	Matrix ori;
	ori.f[0][3]=1;
	for(int i=1; i<=M; i++) {
		scanf("%d%d%d",&opt,&l,&r);
		if(opt==1) {
			st.update(1,N,1,l,1);
			if(r<N) st.update(1,N,1,r+1,(mod-fib[r-l+1]+(r-l>=1 ? mod-fib[r-l] : 0))%mod);
			if(r+1<N) st.update(1,N,1,r+2,mod-fib[r-l+1]);
		} else {
			Ans=(ori*st.query(1,N,1,r)).f[0][0];
			if(l>1) {
				Ans-=(ori*st.query(1,N,1,l-1)).f[0][0];
				if(Ans<0) Ans+=mod;
			}
			add(Ans,(a[r]-a[l-1]+mod)%mod);
			printf("%d\n",Ans);
		}
	}
	return 0;
}
```

---

## 作者：傅思维666 (赞：5)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11799491.html)

~~2019.11.5模拟赛T3 40分场~~

$O(n^2)$的做法能水10分，普通线段树毫无优化能跑30分。感谢出题人@littleseven

一看是黑题顿时毫无思路。因为这道题涉及到的知识点：**线段树+$Fibonacci$数列**是联赛范围内，所以它就这样被收进了联赛模拟赛中。

介绍一下正解：

首先我们能想到，区间修改区间查询一定需要线段树。而且这道题难住我们的点就是如何维护修改操作，换句话说，如何进行下传标记。

但是我们稍微动动脑能发现这个性质：（我在考场上也推出来了）

对于一个要修改的区间$[l,r]$中的第$x$项，它需要加上这一项：$fib_{x-l+1}$。$fib$表示斐波那契数列。

而斐波那契数列有这样的性质：（很重要，虽然蒟蒻也是做了这道题才知道）
$$
fib[n+m]=fib[n+1]fib[m]+fib[n]fib[m-1]
$$
那么对于这个位置$x$，设$n=-l,m=x+1$，它加上了：
$$
fib[x-l+1]=fib[1-l]fib[x+1]+fib[x]fib[-l]
$$
那么对于线段树上的节点，我们需要维护两个标记：$add1[i],add2[i]$，分别统计对于一个区间为$[l,r]$的节点，$add1(fib_{l+1}+fib_{l+2}+\cdots+fib_{r+1})$，$add2(fib_{l}+fib_{l+1}+\cdots+fib_{r})$。

修改的时候，给$add1$加上$fib_{-l+1}$，给$add2$加上$fib_{-l}$，然后进行线段树的正常$pushdown$操作即可。

代码：

```cpp
#include<cstdio>
#define lson pos<<1
#define rson pos<<1|1
using namespace std;
const int maxn=3*1e5+10;
const int mod=1e9+9;
char *p1,*p2,buf[100000];
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
    int x=0,f=1;
    char ch=nc();
    while(ch<48){if(ch=='-')f=-1;ch=nc();}
    while(ch>47)    x=(((x<<2)+x)<<1)+ch-48,ch=nc();
    return x*f;
}
int n,m;
int a[maxn],sum[maxn],fib[maxn],ffib[maxn];
int tree[maxn<<2],add1[maxn<<2],add2[maxn<<2];
void fibonacci()
{
    fib[1]=fib[2]=sum[1]=ffib[1]=1;
    sum[2]=2;
    ffib[2]=mod-1;
    for(int i=3;i<=n+1;i++)
    {
        fib[i]=(fib[i-1]+fib[i-2])%mod;
        sum[i]=(sum[i-1]+fib[i])%mod;
        ffib[i]=(i&1)?fib[i]:mod-fib[i];
    }
}
void build(int pos,int l,int r)
{
    int mid=(l+r)>>1;
    if(l==r)
    {
        tree[pos]=a[l]%mod;
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
    tree[pos]=(tree[lson]+tree[rson])%mod;
}
void mark(int pos,int l,int r,int a1,int a2)
{
    add1[pos]=(add1[pos]+a1)%mod;
    add2[pos]=(add2[pos]+a2)%mod;
    tree[pos]=(tree[pos]+1ll*(sum[r+1]-sum[l]+mod)%mod*a1%mod)%mod;
    tree[pos]=(tree[pos]+1ll*(sum[r]-sum[l-1]+mod)%mod*a2%mod)%mod;
}
void pushdown(int pos,int l,int r)
{
    int mid=(l+r)>>1;
    mark(lson,l,mid,add1[pos],add2[pos]);
    mark(rson,mid+1,r,add1[pos],add2[pos]);
    add1[pos]=add2[pos]=0;
}
void update(int pos,int l,int r,int x,int y,int a1,int a2)
{
    int mid=(l+r)>>1;
    if(x<=l && r<=y)
    {
        mark(pos,l,r,a1,a2);
        return;
    }
    pushdown(pos,l,r);
    if(x<=mid)
        update(lson,l,mid,x,y,a1,a2);
    if(y>mid)
        update(rson,mid+1,r,x,y,a1,a2);
    tree[pos]=(tree[lson]+tree[rson])%mod;
}
int query(int pos,int l,int r,int x,int y)
{
    int ret=0;
    int mid=(l+r)>>1;
    if(x<=l && r<=y)
        return tree[pos]%mod;
    pushdown(pos,l,r);
    if(x<=mid)
        ret=(ret+query(lson,l,mid,x,y))%mod;
    if(y>mid)
        ret=(ret+query(rson,mid+1,r,x,y))%mod;
    return ret%mod;
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    fibonacci();
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int opt,l,r;
        opt=read();l=read();r=read();
        if(opt==1)
            update(1,1,n,l,r,ffib[l-1],ffib[l]);
        else
            printf("%d\n",query(1,1,n,l,r));
    }
    return 0;
}
```



---

## 作者：灼眼的夏娜 (赞：4)

更好的阅读体验——> [$blogs$](https://violetnymph.blog.luogu.org/solution-cf446c)

这题一开始有没有人想用矩乘？我一开始是想这么写的但说到底它只能优化暴力，然而考场上我居然写锅了。。。
## **正解：线段树+普通的斐波那契数列**
我们都知道$f[i] = f[i-1]+f[i-2]$，经典的斐波那契中是以1， 1为第一和第二项现在把它推广

于是有了广义的斐波那契：$F[i]=F[i-1]+F[i-2]$，其首项和次项为$a,b$，正确性是显然的

那就相当于$F[i]=a*f[i-2]+b*f[i-1]$

再有一个结论：$\sum_{i=1}^nF_i=F_{n+2}-F_2$

那我们可以拿着个搞点事情，预处理出一个前缀和，记为$S[i]$,那么有：

$S_n=S_{n-1}+F_{n}=F_{n+1}-F_2+F_n=F_{n+2}-F_2$,也就是

$S_n=a*F_n+b*F_{n+1}-b$

那我们就能用线段树来维护这个东西了！结合上述，只要维护$a,b$就好了

区间修改和区间查询大家肯定都会写，如何下穿标记？这是线段树的核心部分，如果是左区间，其$a,b$与大区间的相同，直接丢下去

而右区间不能直接丢，但我们可以根据性质把它算出来，这样就搞定了，至于怎么算，给出代码看吧，懒得说了
```cpp
inline void pushdown(int k) {
	//tag就是左边的首项，lay是次项，a，b就是右区间的两个端点
	LL a = (T[k].tag * f[T[ls].len - 1] % p + T[k].lay * f[T[ls].len] % p) % p;
	LL b = (T[k].tag * f[T[ls].len] % p + T[k].lay * f[T[ls].len + 1] % p) % p;
	add(ls, T[k].tag, T[k].lay);
	add(rs, a, b);
	T[k].tag = T[k].lay = 0;
}
```
这是$add$
```cpp
inline void add(int k, LL a, LL b) {
	T[k].tag = (T[k].tag + a) % p;
	T[k].lay = (T[k].lay + b) % p;
    //正如上述公式所说
	T[k].sum = (T[k].sum + a * f[Len] % p + b * f[Len + 1] % p - b) % p;
}
```
然后献上完整的代码

## code
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ls (k << 1)
#define rs (k << 1 | 1)
#define L (T[k].l)
#define R (T[k].r)
#define Len (T[k].len)

using namespace std;
typedef long long LL;
const int p = 1e9+9;
const int N = 3e5+5;
int n, m;
struct Tree {
	LL sum, lay, tag;
	int l, r, len;
}T[N<<2];
LL f[N], a[N];

inline void update(int k) {	T[k].sum = (T[ls].sum + T[rs].sum) % p; }

inline void add(int k, LL a, LL b) {
	T[k].tag = (T[k].tag + a) % p;
	T[k].lay = (T[k].lay + b) % p;
	T[k].sum = (T[k].sum + a * f[Len] % p + b * f[Len + 1] % p - b) % p;
}

inline void pushdown(int k) {
	LL a = (T[k].tag * f[T[ls].len - 1] % p + T[k].lay * f[T[ls].len] % p) % p;
	LL b = (T[k].tag * f[T[ls].len] % p + T[k].lay * f[T[ls].len + 1] % p) % p;
	add(ls, T[k].tag, T[k].lay);
	add(rs, a, b);
	T[k].tag = T[k].lay = 0;
}

void build(int k, int l, int r) {
	T[k].l = l, T[k].r = r, T[k].len = r - l + 1;
	if(l == r) { T[k].sum = a[l] % p; return; }
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	update(k);
}

void Change(int k, int l, int r) {
	if(L >= l && R <= r) {
		add(k, f[L - l + 1], f[L - l + 2]);
		return;
	}
	if(T[k].tag) pushdown(k);
	int mid = (L + R) >> 1;
	if(l <= mid) Change(ls, l, r);
	if(r > mid) Change(rs, l, r);
	update(k);
}

LL query(int k ,int l, int r) {
	if(L >= l && R <= r) return T[k].sum;
	if(T[k].tag) pushdown(k);
	int mid = (L + R) >> 1;
	LL res = 0;
	if(l <= mid) res = (res + query(ls, l, r) % p) % p;
	if(r > mid) res = (res + query(rs, l, r) % p) % p;
	return res;
}

inline void init() {
	f[1] = f[2] = 1;
	for(int i = 3;i < N;++ i)
		f[i] = (f[i - 1] + f[i - 2]) % p;
}

int main() {
	// freopen("d.in", "r", stdin);
	// freopen("d.out", "w", stdout);
	init();
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;++ i) scanf("%lld", &a[i]);
	build(1, 1, n);
	for(int i = 1, op, l, r, x;i <= m;++ i) {
		scanf("%d%d%d", &op, &l, &r);
		if(op == 2) printf("%lld\n", (query(1, l, r) + p) % p);
		if(op == 1) Change(1, l, r); 
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

