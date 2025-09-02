# Please, another Queries on Array?

## 题目描述

你有一个数组 $a_1,a_2,\cdots,a_n$。

现在你需要完成 $q$ 次操作，有以下两种操作形式：

1. `MULTIPLY l r x`，对于所有 $i(l\le i\le r)$，将 $a_i$ 乘上 $x$。

2. `TOTIENT l r`，求出 $\varphi(\prod_{i=l}^ra_i)$，对 $10^9+7$ 取模后的结果。其中 $\varphi$ 表示欧拉函数，$\varphi(n)$ 的定义为 $1\cdots n$ 中与 $n$ 互质的数的个数。


保证数据中至少有一次操作 $2$。

## 说明/提示

在样例中：  
对于第 $1$ 个询问 $\varphi(1)=1$；  
对于第 $2$ 个询问 $\varphi(2)=1$；  
对于第 $3$ 个询问 $\varphi(6)=2$。

## 样例 #1

### 输入

```
4 4
5 9 1 2
TOTIENT 3 3
TOTIENT 3 4
MULTIPLY 4 4 3
TOTIENT 4 4
```

### 输出

```
1
1
2
```

# 题解

## 作者：CGDGAD (赞：14)

### CF1114F Please, another Queries on Array?

----

### Part 0 有趣的事情

- 这题我在做的时候某处 $l$ 和 $r$ 写反了，调了两个多小时。
- 你需要有足够的耐心等待本题评测结束，本题共有 $100$ 个测试点，每个测试点 $3$ 秒左右。

那就开始吧！

---

### Part 1 题意简述

给定一个数列、两种操作。第一种操作，对 $[l, r]$ 内的所有数同乘以 $m$；第二种操作，求出 $\varphi(\prod\limits_{i=l}^{r}a_i) \bmod 1000000007$ 的值。

---

### Part 2 题目分析

由区间修改、查询想到线段树。

区间乘是很常见的一种线段树操作，但 求区间积的欧拉函数 比较难处理。

----

#### 难点 1: 如何求欧拉函数

作为一个啥数论都不会的菜鸡，我看了一下欧拉公式的定义：

> $\varphi(n)$ 为 $1\dots n$ 中与 $n$ 互质的数的个数。

而随便 bdfs 即可得到欧拉公式的求法：

$$\varphi(x)=x\cdot\prod_{i=1}^n(\dfrac{p_i-1}{p_i})\ (p_1, p_2, \dots p_n \text{为 } x \text{ 的所有质因数})$$

因为计算过程中，$x$ 需要取模，最终得到的 $x$ 并不是原来的 $x$，不能保证 $p$ 一定能被 $x$ 整除。所以后面的每个 $\dfrac{p - 1}{p}$ 需要提前进行计算，当进行查询操作的时候直接使用。这就是一个有理数取模的问题了，不了解的可以转到  [P2613](https://www.luogu.com.cn/problem/P2613)。

----

#### 难点 2: 如何找出一个数的所有质因数

找出所有的质因数，才能进行欧拉函数的计算。

其实大体思路比较好想，就是除了区间乘积以外，线段树内再维护一些数据——区间乘积包括哪些质因数。具体实现的话，使用状态压缩的概念会比较容易。$300$ 内有 $62$ 个质数，而 $2^{62}$ 恰好在 `long long` 的范围内，所以可以把一个数的质因数的情况压缩到一个 `long long` 内（暂且叫这个数为“质因数状态”吧）。

当然，同时也需要维护一个相应的 lazytag。这一块代码实现比较复杂，一定不要把细节写错了。

### Part 3 放进线段树板子里重新整理思路和注意点

#### 初始化

- 所有乘法 lazytag 为 1；
- 所有质因数状态相关的变量全都设为 0。
- 可以提前算好 $300$ 以内的质数。

#### update 操作

- update 操作里，除了更新当前区间的乘积以外，还要更新其乘积所含的质因数状态；
- 可以新加一个参数“质因数状态”，方便操作。

#### query 操作

- query 操作需要返回一个线段树节点（因为计算欧拉函数时既需要用乘积也需要用质因数，不能只返回一个）

#### pushUp 操作

- 父亲的乘积 $=$ 左儿子乘积 $\times$ 右儿子乘积；
- 父亲的质因数状态 $=$ 左儿子质因数状态 按位或 右儿子质因数状态；

#### pushDown 操作

- 子树的乘积乘以父亲的乘法 lazytag 的子树区间长度次方，子树的乘法 lazytag 乘以父亲的乘法 lazytag；
- 子树的质因数状态和它的 lazytag 都按位或上父亲的质因数状态 lazytag；
- 乘法的 lazytag 置 1，质因数状态的 lazytag 置 0。
- 取模别忘了。

#### 主程序

- 需要提前预处理计算欧拉函数所需的值；
- 进行修改操作之前，先找出乘上的那个数的所有的质因数，压缩成一个状态，传入 update 函数；
- 进行查询操作之后，要算出欧拉函数的值。


### Part 4 Code

```cpp
#include <cstdio>
#define int long long
#define MOD 1000000007
int mi(int a, int b, int mo); // 快速幂，不贴代码了
int read(); // 快读，不贴代码了
int readOpt() { // 读操作类型（修改操作返回 1，查询操作返回 2）
	char ch = getchar(); int ans;
	while (ch < 'A' || ch > 'Z') ch = getchar();
	if (ch == 'T') return 2;
	else return 1;
}
struct Node {
	int val; int p;
	int lazy, lazyP;
	Node() { val = 1; lazy = 1; p = 0; lazyP = 0; }
} xds[1600007]; // 线段树结点
int n, q;
int a[1600007];
int f[1001], inv[1001];
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89,97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};
void pushUp(int x) {
	xds[x].val = xds[x * 2].val * xds[x * 2 + 1].val % MOD;
	xds[x].p = xds[x * 2].p | xds[x * 2 + 1].p;
}
void pushDown(int x, int l, int m, int r) {
	// 更新子树乘积
    xds[x * 2].val = xds[x * 2].val * mi(xds[x].lazy, m - l + 1, MOD) % MOD;
    xds[x * 2 + 1].val = xds[x * 2 + 1].val * mi(xds[x].lazy, r - m, MOD) % MOD;
    // 更新子树乘法 lazytag
    xds[x * 2].lazy = xds[x * 2].lazy * xds[x].lazy % MOD;
    xds[x * 2 + 1].lazy = xds[x * 2 + 1].lazy * xds[x].lazy % MOD;
    // 更新子树质因数状态
    xds[x * 2].p |= xds[x].lazyP;
    xds[x * 2 + 1].p |= xds[x].lazyP;
    // 更新子树质因数状态 lazytag
    xds[x * 2].lazyP |= xds[x].lazyP;
    xds[x * 2 + 1].lazyP |= xds[x].lazyP;
	xds[x].lazy = 1;
	xds[x].lazyP = 0;
}
void build(int l, int r, int x) {
	if (l == r) {
		xds[x].val = a[l];
		for (int i = 0; i < 62; ++i)
			if (a[l] % prime[i] == 0)
				xds[x].p |= (1ll) << i; // 找出所有质因数
		return;
	}
	const int m = (l + r) >> 1;
	build(l, m, x * 2);
	build(m + 1, r, x * 2 + 1);
	pushUp(x);
}
void update(int x, int l, int r, int delta /* 乘上的数 */, int prime /* 即质因数状态 */, int cl, int cr) {
	if (cl > r || cr < l) return;
	if (l <= cl && cr <= r) {
		xds[x].val = xds[x].val * mi(delta, cr - cl + 1, MOD) % MOD;
		xds[x].lazy = xds[x].lazy * delta % MOD;
		xds[x].p |= prime;
		xds[x].lazyP |= prime;
		return;
	}
	const int m = (cl + cr) >> 1;
	pushDown(x, cl, m, cr);
	update(x * 2, l, r, delta, prime, cl, m);
	update(x * 2 + 1, l, r, delta, prime, m + 1, cr);
	pushUp(x);
}
Node query(int x, int l, int r, int cl, int cr) {
	if (cl > r || cr < l) return Node();
	if (l <= cl && r >= cr) { return xds[x]; }
	const int m = (cl + cr) >> 1;
	pushDown(x, cl, m, cr);
	Node n; Node ll = query(x * 2, l, r, cl, m); Node rr = query(x * 2 + 1, l, r, m + 1, cr);
	n.val = ll.val * rr.val % MOD;
	n.p = ll.p | rr.p;
	return n;
}
signed main() {
	n = read(), q = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	build(1, n, 1);
	
	// 计算每个 (p - 1) / p 的结果
	inv[1] = 1;
	for (int i = 2; i <= 300; ++i)
		inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
	for (int i = 0; i < 62; ++i)
		f[i] = inv[prime[i]] * (prime[i] - 1) % MOD;

	for (int i = 1; i <= q; i += 1) {
		int opt = readOpt(), x = read(), y = read();
		if (opt == 1) {
			int k = read();
			int t = 0;
			for (int i = 0; i < 62; ++i)
				if (k % prime[i] == 0)
					t |= (1ll) << i; // 找出所有质因数
			update(1, x, y, k, t, 1, n);
		} else {
			Node ans = query(1, x, y, 1, n);
			// 算欧拉函数
			int phi = ans.val;
			for (int i = 0; i < 62; ++i) {
				if (ans.p >> i & 1) {
					phi = phi * f[i] % MOD;
				}
			}
			printf("%lld\n", phi % MOD);
		}
	}
	return 0;
}
```

---

## 作者：AThousandSuns (赞：12)

在我的博客上看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/10362224.html)

明显线段树。

有一个想法是维护区间积的欧拉函数，但是这样时间复杂度和代码复杂度都很高……

我的做法是维护区间积。而欧拉函数，就是看看区间中包含什么质因子，然后除一下乘一下好了。

区间积就不用说了。

包含什么质因子？难道要开bool数组吗？时间复杂度很高……

经过后台黑科技操作发现 $300$ 以内的质数只有 $62$ 个。明摆着状压的节奏！

好的，这题做完了。细节的东西在代码中都有。

对于我的代码实现来说：（以下令 $k=62$）

建树 $O(kn)$。

合并节点 $O(1)$。

下推标记 $O(\log n)$。

区间乘 $O(\log^2 n+k)$。

查询欧拉函数 $O(\log n+k)$。

总时间复杂度应该是 $O((n+q)k+q\log^2n)$。其实跑得不慢，我跑得最慢的点是1934ms。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=400040,mod=1000000007;
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
int n,q,pri[66],pl,a[maxn],inv[333],f[66],tag1[maxn*4];    //tag1表示区间要乘多少
ll tag2[maxn*4];    //tag2表示区间会多出哪些质因子（也是压缩过的）
//为什么要两个标记呢？不能直接对tag1分解质因子吗？
//因为tag1乘几遍就会被取模，这样看起来质因子就变了。所以额外加一个tag2表示真的质因子集合。
bool vis[333];
void init(){
    FOR(i,2,300){
        if(!vis[i]) pri[++pl]=i;
        for(int j=1;j<=pl && i*pri[j]<=300;j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0) break;
        }
    }
    inv[1]=1;
    FOR(i,2,300) inv[i]=mod-1ll*(mod/i)*inv[mod%i]%mod;
    FOR(i,1,pl) f[i]=1ll*inv[pri[i]]*(pri[i]-1)%mod;
    //f[i]表示除以p[i]，再乘上p[i]-1，便于计算欧拉函数
}
inline int qpow(int a,int b){
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) ans=1ll*ans*a%mod;
    return ans;
}
struct node{
    int pro;ll has;
}nd[maxn*4];    //一个线段树节点，pro是区间积，has是区间包含哪些质因子（压缩过的）
void pushup(node &o,node l,node r){    //合并
    o.has=l.has|r.has;    //直接取或
    o.pro=1ll*l.pro*r.pro%mod;
}
void setmult(int o,int l,int r,int x,ll y){    //对第o个节点（管辖[l,r]）区间乘x，质因子多了y
    tag1[o]=1ll*tag1[o]*x%mod;
    tag2[o]|=y;
    nd[o].pro=1ll*nd[o].pro*qpow(x,r-l+1)%mod;    //记得乘r-l+1次方
    nd[o].has|=y;
}
void pushdown(int o,int l,int r){    //下传标记
    if(!tag2[o]) return;
    int mid=(l+r)>>1;
    setmult(lson,tag1[o],tag2[o]);
    setmult(rson,tag1[o],tag2[o]);
    tag1[o]=1;tag2[o]=0;    //记得tag1闲置时是1
}
void build(int o,int l,int r){
    tag1[o]=1;tag2[o]=0;
    if(l==r){
        nd[o].pro=a[l];
        FOR(i,1,pl)    //记录质因子集合
            if(a[l]%pri[i]==0) nd[o].has|=1ll<<(i-1);
        return;
    }
    int mid=(l+r)>>1;
    build(lson);build(rson);
    pushup(nd[o],nd[o<<1],nd[o<<1|1]);
}
void mult(int o,int l,int r,int ql,int qr,int x,ll y){    //外面调用时先把质因子集合弄好，会省时间
    if(l>=ql && r<=qr){
        setmult(o,l,r,x,y);    //直接设上
        return;
    }
    pushdown(o,l,r);
    int mid=(l+r)>>1;
    if(mid>=ql) mult(lson,ql,qr,x,y);
    if(mid<qr) mult(rson,ql,qr,x,y);
    pushup(nd[o],nd[o<<1],nd[o<<1|1]);
}
node query(int o,int l,int r,int ql,int qr){
    if(l>=ql && r<=qr) return nd[o];
    pushdown(o,l,r);
    int mid=(l+r)>>1;
    if(mid<ql) return query(rson,ql,qr);
    if(mid>=qr) return query(lson,ql,qr);
    node ans;
    pushup(ans,query(lson,ql,qr),query(rson,ql,qr));    //合并两边
    return ans;
}
int main(){
    init();
    n=read();q=read();
    FOR(i,1,n) a[i]=read();
    build(1,1,n);
    FOR(i,1,q){
        char op[11];
        scanf("%s",op);
        int l=read(),r=read();
        if(op[0]=='M'){    //乘操作
            int x=read();ll y=0;
            FOR(i,1,pl) if(x%pri[i]==0) y|=1ll<<(i-1);    //先处理质因子集合
            mult(1,1,n,l,r,x,y);
        }
        else{    //求欧拉函数操作
            node ans=query(1,1,n,l,r);
            int s=ans.pro;    //区间积
            FOR(i,1,pl) if(ans.has&(1ll<<(i-1))) s=1ll*s*f[i]%mod;    //区间含有第i个质数，那就要除以p[i]，再乘上p[i]-1
            printf("%d\n",s);
        }
    }
}
```

---

## 作者：smallpeter (赞：3)

# 前置芝士

1. 欧拉函数的计算方法
2. 线段树
3. 快速幂
4. ~~卡常技巧~~

# 解题思路

首先要知道欧拉函数的计算方式。

$φ(n)=n\times\prod\limits_{i=1}^k\dfrac{p_i-1}{p_i}$

其中 $p$ 为 $n$ 全部质因子组成的序列，$k$ 为 $n$ 不同质因子的个数。

现在题目让我们计算 $φ(a_l\times a_{l+1}\dots \times a_r)$，也就是计算 $((a_l\times a_{l+1}\dots \times a_r)\times\prod\limits_{i=1}^k\dfrac{p_i-1}{p_i}) \bmod 10^9+7$，同时有区间乘法修改操作。

显然前面的 $(a_l\times a_{l+1}\dots \times a_r)$ 这一堆东西可以用线段树维护，那么现在的问题就在于怎么求 $(\prod\limits_{i=1}^k\dfrac{p_i-1}{p_i})\bmod 10^9+7$。显然 ：
$$
(\prod\limits_{i=1}^k\dfrac{p_i-1}{p_i})\bmod 10^9+7=(\prod\limits_{i=1}^k(\dfrac{p_i-1}{p_i}\bmod 10^9+7))\bmod 10^9+7
$$

不难发现这一堆东西只与区间乘积的质因子是哪几个有关，与每个质因子有几个无关。同时题目约束 $a_i\le 300$，也就是说不会出现超过 300 的质数。1 到 300 中一共有62个质数，于是我们可以用一个 `long long` 把状态压缩（相当于以时间换空间，毕竟把这个压缩状态再还原需要 $\log$ 级别的时间，但能节省大量空间）。比如 $(000\dots 01011)_2$ 就表示这个数有质因子 2、3、7。

那么现在第二堆东西如何维护就很明朗了，用线段树维护一段区间有哪几个质因子，区间乘法修改的时候就把这一段区间的所有压缩状态全部 $or$ 上 $x$ 的压缩状态。至于为什么是 $or$，因为两个压缩状态合并的时候（我们假设数 $a$ 和数 $b$ 合并），如果质数 $p$ 是 $a$ 的质因数或者是 $b$ 的质因数，那么合并后肯定也有 $p$ 这个质因数。反之如果质数 $p$ 既不是 $a$ 的质因数，也不是 $b$ 的质因数，那么合并后肯定没有 $p$ 这个质因数。这个过程放到压缩状态运算里面去就是 $or$。 

# 卡常小技巧

由于我们在计算最终结果的时候会用到逆元，如果每次计算某个质数的贡献都要用一遍快速幂去计算就会~~凭空~~多乘 $\log(mod)$ ($mod$ 为取模的数，题目规定其为 $10^9+7$，下文中再次出现也是一样的意义) 的复杂度，于是我们要先预处理出每个质数的贡献。~~我才不会告诉你们我因为没这么做调了tle一个小时。~~

# 时间复杂度

线段树自带 $O(m\times \log(n))$，区间修改的时候会带个 $O(\log(n))$ (求快速幂带来的)，区间查询的时候需要累乘，会带个 $O(k)$（其中 $k$ 表示质因数个数，这里为62）。预处理每个质数的贡献，复杂度为 $O(k\times \log(mod))$。所以总复杂度就是 $O(k\times \log(mod)+m\times \log(n)\times (\log(n)+k))$，足以通过本题。~~甚至抢了个最优解rk3。~~

# 代码

```
#include<bits/stdc++.h>
using namespace std;

#define LL long long

const LL N=4e5+10,mod=1e9+7;

LL n,q,a[N],b[N],lq,rq,xq,p[N],t,inv[100];

inline LL read(){
    char ch=getchar();LL x=0,f=0;
    while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}

char s[100];

bool bl[301];

struct Tree{
	LL times;//区间乘法
	LL sor;//区间压缩状态或
	LL lazy;//区间乘法懒标记 
	LL lazy2;//区间压缩状态或 的懒标记 
}tree[N<<2];

LL ass(LL w){//手写取模会快一点 
	return (w<mod)?w:w%mod;
}

LL get(LL x){//把x这个数状态压缩 
	LL ans=0;
	for(LL i=0;i<=t;i++){
		if(x%p[i]==0){
			ans|=((LL)1<<i);
		}
	}
	return ans;
}

LL qsm(LL a,LL b){//快速幂模板 
    LL ans=1;
    for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) ans=1ll*ans*a%mod;
    return ans;
}

void init(){//预处理出a[i]的压缩状态和所有质数的逆元（求逆元是为了后面计算贡献，如果边算贡献边计算逆元，就会多一个log的复杂度） 
	bl[0]=bl[1]=true;
	t=-1;
	for(LL i=2;i<=300;i++){//筛质数 
		if(bl[i]==false){
			p[++t]=i;
		}
		for(LL j=2*i;j<=300;j+=i) bl[j]=true;
	}
	for(LL i=0;i<=t;i++) inv[i]=qsm(p[i],mod-2);
	for(LL i=1;i<=n;i++){
		b[i]=get(a[i]);
	}
	return ;
}

void pushup(LL w,LL l,LL r){
	LL mid=(l+r)>>1;
	tree[w].sor=tree[w<<1].sor|tree[w<<1|1].sor;
	tree[w].times=(tree[w<<1].times*tree[w<<1|1].times)%mod;
	return ;
}

void pushdown(LL w,LL l,LL r){
	LL mid=(l+r)>>1;
	if(tree[w].lazy!=1){
		//常规区间乘法下放，但因为卡常，所以阅读效果会差一点 
		tree[w<<1].lazy=ass(tree[w<<1].lazy*tree[w].lazy);
		tree[w<<1|1].lazy=ass(tree[w<<1|1].lazy*tree[w].lazy);
		LL ss=qsm(tree[w].lazy,r-mid);
		tree[w<<1].times=ass(ass(tree[w<<1].times*ss)*((mid-l+1==r-mid)?1:tree[w].lazy));
		tree[w<<1|1].times=ass(tree[w<<1|1].times*ss);
	}
	if(tree[w].lazy2!=0){
		//区间压缩状态或 的下放 
		tree[w<<1].lazy2|=tree[w].lazy2;
		tree[w<<1|1].lazy2|=tree[w].lazy2;
		tree[w<<1].sor|=tree[w].lazy2;
		tree[w<<1|1].sor|=tree[w].lazy2;
	}
	tree[w].lazy=1;
	tree[w].lazy2=0; 
	return ;
}

void build(LL l,LL r,LL w){
	tree[w].lazy=1;
	tree[w].sor=0;
	tree[w].times=1;
	tree[w].lazy2=0;
	if(l==r){
		tree[w].sor=b[l];
		tree[w].times=a[l];
		return ;
	}
	LL mid=(l+r)>>1;
	build(l,mid,w<<1);
	build(mid+1,r,w<<1|1);
	pushup(w,l,r);
	return ;
}

void change(LL l,LL r,LL w,LL lx,LL rx,LL x,LL y){
	if(l>=lx&&r<=rx){
		tree[w].sor|=x;
		tree[w].lazy2|=x;
		tree[w].times=ass(tree[w].times*qsm(y,r-l+1));
		tree[w].lazy=ass(tree[w].lazy*y);
		return ;
	}
	pushdown(w,l,r);
	LL mid=(l+r)>>1;
	if(mid>=lx){
		change(l,mid,w<<1,lx,rx,x,y);
	}
	if(mid<rx){
		change(mid+1,r,w<<1|1,lx,rx,x,y);
	}
	pushup(w,l,r);
	return ;
}

LL query_times(LL l,LL r,LL w,LL lx,LL rx){//询问区间乘法值 
	if(l>=lx&&r<=rx){
		return ass(tree[w].times);
	}
	pushdown(w,l,r);
	LL mid=(l+r)>>1,sum=1;
	if(mid>=lx){
		sum=ass(sum*query_times(l,mid,w<<1,lx,rx));
	}
	if(mid<rx){
		sum=ass(sum*query_times(mid+1,r,w<<1|1,lx,rx));
	}
	return sum;
}

LL query_or(LL l,LL r,LL w,LL lx,LL rx){//询问区间压缩状态或 值 
	if(l>=lx&&r<=rx){
		return tree[w].sor;
	}
	pushdown(w,l,r);
	LL mid=(l+r)>>1,ans=0;
	if(mid>=lx){
		ans|=query_or(l,mid,w<<1,lx,rx);
	}
	if(mid<rx){
		ans|=query_or(mid+1,r,w<<1|1,lx,rx);
	}
	return ans;
}

inline LL answ(LL l,LL r){//题目中的查询操作 
	LL ans1=query_times(1,n,1,l,r);
	LL ans2=query_or(1,n,1,l,r);
	LL st=0,sum=1,sz=ans2;
	while(sz){
		if(sz&1){
			sum=ass((ass(sum*(p[st]-1)))*inv[st]);
		}
		sz>>=1;
		st++;
	}
	return ass(ans1*sum);
}

int main(){
	n=read();
	q=read();
	cin.tie(0);
	for(LL i=1;i<=n;i++) a[i]=read();
	init();
	build(1,n,1);
	while(q--){
		cin>>s;
		if(s[0]=='T'){
			lq=read();
			rq=read();
			printf("%lld\n",answ(lq,rq));
		}
		else{
			lq=read();
			rq=read();
			xq=read();
			change(1,n,1,lq,rq,get(xq),xq);
		}
	} 
	return 0;
}
```

最后放张图让大伙乐一下。
![](https://cdn.luogu.com.cn/upload/image_hosting/xh1dlma2.png)

---

## 作者：xfrvq (赞：2)

[$\tt Link$](/problem/CF1114F "CF1114F Please, another Queries on Array?")。

神仙题/se/se

我们有 $\varphi$ 的公式：设 $n=\alpha_1^{\beta_1}\alpha_2^{\beta_2}\cdots \alpha_n^{\beta_n}$，  那么

$$\varphi(n)=n\times\prod_{i=1}
^n\dfrac{\alpha_i-1}{\alpha_i}$$

那么答案可以分成两部分：区间乘积以及后面的 $\displaystyle\prod_{i=1}
^n\dfrac{\alpha_i-1}{\alpha_i}$。

前者可以线段树维护区间乘积，后者怎么办？

因为 $a_i$ 以及乘法操作的 $x$ 都 $\le300$，所以分解出来的 $\alpha_i\le300$。

$300$ 以内的质数有 $62$ 个，可以使用 `long long` 进行状态压缩，每位代表有没有。

那么还是在刚刚的那棵线段树上，维护区间的质因数状压集合，然后就是一个区间按位或区间按位或的结果，线段树做完了。

---

> 一年前，我折戟沉沙。
> 
> 一年后，我在爬起的地方倒下。

[![](https://img-blog.csdnimg.cn/67af2b0312de466a956f8b13c58d10e2.png)](https://www.luogu.com.cn/record/list?pid=CF1114F&user=368107 "洛谷提交记录")

[$\tt CF\ submission$](https://codeforces.com/contest/1114/submission/137883911 "CF 提交记录")。

为什么一年前的 Code 又臭又长啊（大悲）。

---

## 作者：Arghariza (赞：2)

- 题目大意：

1. 区间修改：$a_i=a_i\times c,i\in[l,r]$
2. 区间询问：$\varphi(\prod\limits_{i=l}^{r}a_i)\mod (10^9+7)$

- $\mathtt{Solution:}$

去 [oi wiki](https://oi-wiki.org//math/number-theory/euler/) 上面可以看到一个 $\varphi$ 的求法：

$$\varphi(n)=n\prod\limits_{i=1}^{m}\frac{p_i-1}{p_i}$$

$m$ 表示 $n$ 质因子个数，$p$ 的长度为 $m$，表示 $n$ 的所有质因子。

以上柿子的证明省略，必要的可以去上面的链接看。

既然是和质因子有关，那就先把质数筛出来。

由于题目说 $a_i,x\le 300$ 于是我们发现 $300$ 以内的质数只有 $62$ 个，考虑压缩成二进制数的话正好在 `long long` 的范围之内。所以先预处理出 $p_i,inv_i,tp_i=\frac{p_i-1}{p_i}\mod (10^9+7)$。

所以我们用一个数表示 $k$ 的质因子状态，如果 $k$ 有这个质因子那就打上 $1$，否则是 $0$。两个数相乘的时候由于不考虑某个质因子的个数，所以把它们的质因子组成的 $01$ 二进制数按位或即可。

于是我们的线段树维护 $4$ 个信息：区间乘积，乘积的 `lazy tag` ，区间乘积的质因子情况，以及区间乘积的质因子情况的 `lazy tag` ，区间乘数的时候区间乘积和乘积的 `tag` 很好维护，然后把这个乘上的数质因数分解，算出这个数的质因子情况和当前区间的质因子情况按位或起来，最后打上标记就行了。

- $\mathtt{Pay\ attention:}$

1. 初始化 `tr[x].pd = tr[x].lz = 1, tr[x].fc = tr[x].lf = 0`：`pd` 表示节点代表区间的乘积（product），`lz` 为乘积的 tag ， `fc` 为质因子情况（factor），`lf` 为质因子情况的 tag 。由于是区间乘法， `pd` 和 `lz` 一开始赋 $1$ ；由于是区间或， `fc` 与 `lf` 一开始赋 $0$。
2. 开 `long long` ，左移和右移要写成 `(1ll) << k` 或 `(1ll) >> k` ，否则爆 `int`。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read() {
    int w = 1, q = 0;
    char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') w = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
    return w * q;
}

inline void write(int x) {
    if (x < 0) {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int ksm(int p, int q, int mod) {
	int res = 1;
	while (q) {
		if (q & 1) res = res * p % mod;
		p = p * p % mod;
		q >>= 1;
	}
	return res;
}

const int maxp = 1010;
const int maxn = 4e5 + 400;
const int mod = 1e9 + 7;
int n, m, cnt, s[maxn], pr[maxp], inv[maxp], tp[maxp];
bool v[maxp];

void init() {// 预处理。
	inv[1] = 1;
	for (int i = 2; i <= 300; i++) {
		if (!v[i]) pr[cnt++] = i;
		for (int j = 0; j <= cnt - 1 && i * pr[j] <= 300; j++) {
			v[i * pr[j]] = 1;
			if (i % pr[j] == 0) break;
		}
	}
	for (int i = 2; i <= 300; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 0; i <= cnt - 1; i++) tp[i] = inv[pr[i]] * (pr[i] - 1) % mod;
}

#define ls (x << 1)
#define rs (x << 1 | 1)

struct segtree {
	int pd, lz, fc, lf;
	segtree () { pd = lz = 1, fc = lf = 0; }// 初始化。
} tr[maxn << 2];

void pushup(int x) { tr[x].pd = tr[ls].pd * tr[rs].pd % mod, tr[x].fc = tr[ls].fc | tr[rs].fc; }// 上传信息。
void pushdown(int l, int r, int x) {// 下传 lazy tag。
	int mid = (l + r) >> 1;
	tr[ls].pd = tr[ls].pd * ksm(tr[x].lz, mid - l + 1, mod) % mod;
	tr[rs].pd = tr[rs].pd * ksm(tr[x].lz, r - mid, mod) % mod;
	tr[ls].lz = tr[ls].lz * tr[x].lz % mod;
	tr[rs].lz = tr[rs].lz * tr[x].lz % mod;
	tr[ls].fc |= tr[x].lf, tr[rs].fc |= tr[x].lf;
	tr[ls].lf |= tr[x].lf, tr[rs].lf |= tr[x].lf;
	tr[x].lz = 1, tr[x].lf = 0;
}

void build(int l, int r, int x) {// 建树。
	if (l == r) {
		tr[x].pd = s[l];
		for (int i = 0; i <= cnt - 1; i++) {// 分析质因子情况，下同。
			if (s[l] % pr[i] == 0) tr[x].fc |= ((1ll) << i);
		}
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, ls);
	build(mid + 1, r, rs);
	pushup(x);
}

void update(int l, int r, int s, int t, int c, int f, int x) {// 区间更新。
	if (s <= l && r <= t) {
		tr[x].pd = tr[x].pd * ksm(c, r - l + 1, mod) % mod;
		tr[x].lz = tr[x].lz * c % mod;
		tr[x].fc |= f, tr[x].lf |= f;
		return;
	}
	pushdown(l, r, x);
	int mid = (l + r) >> 1;
	if (s <= mid) update(l, mid, s, t, c, f, ls);
	if (t > mid) update(mid + 1, r, s, t, c, f, rs);
	pushup(x);
}

segtree query(int l, int r, int s, int t, int x) {// 区间查询。
	if (s <= l && r <= t) return tr[x];
	pushdown(l, r, x);
	int mid = (l + r) >> 1;
	if (s <= mid && t <= mid) return query(l, mid, s, t, ls);
	if (s > mid && t > mid) return query(mid + 1, r, s, t, rs);
	if (s > mid && t <= mid) return segtree();
	if (s <= mid && t > mid) {
		segtree res = segtree(), lres = query(l, mid, s, t, ls), rres = query(mid + 1, r, s, t, rs);
		res.pd = lres.pd * rres.pd % mod;
		res.fc = lres.fc | rres.fc;
		return res;
	} 
}

signed main() {
	init();
	n = read();
	m = read();
	for (int i = 1; i <= n; i++) s[i] = read();
	build(1, n, 1);
	for (int i = 1, x, y, z, f; i <= m; i++) {
		char op[20]; scanf("%s", op + 1);
		x = read(), y = read();
		if (op[1] == 'M') {
			z = read(), f = 0;
			for (int j = 0; j <= cnt - 1; j++) {
				if (z % pr[j] == 0) f |= ((1ll) << j);
			}
			update(1, n, x, y, z, f, 1);
		} else {
			segtree ress = query(1, n, x, y, 1);
			int ans = ress.pd;
			for (int j = 0; j <= cnt - 1; j++) {
				if ((ress.fc >> j) & 1) ans = ans * tp[j] % mod;
			}
			write(ans);
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：decoqwq (赞：2)

$F$

考虑到数字都在$300$以内，即质因数最多$62$个，那么只需要线段树维护区间出现的质数即可，$\varphi (p)=p\times \prod\limits_{i=1}^k(1-\frac{1}{p_i})$

注意到内存开不下，用$long long$状压一下出现了的质数即可

```cpp
#include <bits/stdc++.h> 
using namespace std;
#define ll long long
const int mod=1e9+7;
#define mymaxn 400400
int fpow(int a,int b)
{
	int s=1;if(a==1)return 1;
	while(b)
	{
		if(b&1)
		{
			s=1ll*s*a%mod;
		}
		a=1ll*a*a%mod;
		b>>=1;
	}
	return s;
}
ll qaqaq[mymaxn];
bool vis[mymaxn];int prime[mymaxn],cnt;
int n,Q,a[mymaxn];
int t[mymaxn<<2];
ll qwqwqwqwqwq[mymaxn<<2];
int tagt[mymaxn<<2];
ll pwpwpw[mymaxn<<2];
void Build(int now,int l,int r)
{
	t[now]=1;
	qwqwqwqwqwq[now]=0;
	tagt[now]=1;
	if(l==r)
	{
		t[now]=a[l];
		qwqwqwqwqwq[now]=qaqaq[a[l]];
		return;
	}
	int mid=(l+r)>>1;
	Build((now<<1),l,mid);
	Build((now<<1|1),mid+1,r);
	t[now]=1ll*t[(now<<1)]*t[(now<<1|1)]%mod;
	qwqwqwqwqwq[now]=qwqwqwqwqwq[(now<<1)]|qwqwqwqwqwq[(now<<1|1)];
}
void modify(int now,int l,int r,int L,int R,int w,ll W)
{
	if(L==l&&r==R)
	{
		tagt[now]=1ll*tagt[now]*w%mod;pwpwpw[now]|=W;
		return;
	}
	int mid=(l+r)>>1;
	if(L>mid)
	{
		modify((now<<1|1),mid+1,r,L,R,w,W);
	}
	else if(R<=mid)
	{
		modify((now<<1),l,mid,L,R,w,W);
	}
	else 
	{
		modify((now<<1),l,mid,L,mid,w,W);
		modify((now<<1|1),mid+1,r,mid+1,R,w,W);
	}
	qwqwqwqwqwq[now]|=W;
	t[now]=1ll*t[now]*fpow(w,R-L+1)%mod;
}
int queryqwq(int now,int l,int r,int L,int R)
{
	if(L==l&&r==R)
	{
		return 1ll*t[now]*fpow(tagt[now],r-l+1)%mod;
	}
	int mid=(l+r)>>1;
	if(R<=mid)
	{
		return 1ll*queryqwq((now<<1),l,mid,L,R)*fpow(tagt[now],R-L+1)%mod;
	}
	if(L>mid)
	{
		return 1ll*queryqwq((now<<1|1),mid+1,r,L,R)*fpow(tagt[now],R-L+1)%mod;
	}
	return 1ll*queryqwq((now<<1),l,mid,L,mid)*queryqwq((now<<1|1),mid+1,r,mid+1,R)%mod*fpow(tagt[now],R-L+1)%mod;
}
ll queryqaq(int now,int l,int r,int L,int R)
{
	if(L<=l&&r<=R)
	{
		return qwqwqwqwqwq[now]|pwpwpw[now];
	}
	ll ret=pwpwpw[now];
	int mid=(l+r)>>1;
	if(L<=mid)
	{
		ret|=queryqaq((now<<1),l,mid,L,R);
	}
	if(R>mid)
	{
		ret|=queryqaq((now<<1|1),mid+1,r,L,R);
	}
	return ret;
}
int inv[500];
int main()
{
	cin>>n>>Q;
	for(int i=2;i<=300;++i)
	{
		if(!vis[i])
		{
			prime[++cnt]=i;
			inv[cnt]=fpow(i,mod-2);
		}
		for(int j=i+i;j<=300;j+=i)
		{
			vis[j]=true;
		}
	}
	for(int i=2;i<=300;++i)
	{
		for(int j=1;j<=cnt;++j)
		{
			if(i%prime[j]==0)
			{
				qaqaq[i]|=1ll<<(j-1);
			}
		}
	}
		
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
	}
	Build(1,1,n);
	char ch[50];
	while(Q--)
	{
		scanf("%s",ch);
		int l,r;
		scanf("%d%d",&l,&r);
		if(ch[0]=='M')
		{
			int x;
			scanf("%d",&x);
			modify(1,1,n,l,r,x,qaqaq[x]);
		}
		else
		{
			ll S=queryqaq(1,1,n,l,r);
			int v=queryqwq(1,1,n,l,r);
			for(int i=0;i<cnt;++i)
			{
				if(S&(1ll<<i))
				{
					v=1ll*v*inv[i+1]%mod*(prime[i+1]-1)%mod;
				}	
			}		
			printf("%d\n",v);
		}
	}
	return 0;
}
``` 

[这一场cf的题解，打个广告](https://decorationqwq.com/archives/324/)


---

## 作者：SegTree (赞：0)

[题目链接。](https://www.luogu.com.cn/problem/CF1114F)

求 $\varphi(\prod\limits_{i=l}^{r}a_i)\bmod (10^9+7)$ 可以转化为求 $\prod\limits_{i=l}^{r}a_i\times \prod\limits\dfrac{p_i-1}{p_i}$，其中 $p_i$ 表示原式的质因子。

发现这里面有一个很特殊的限制为 $a_i,x\le 300$，然后 $300$ 以内共有 $62$ 个素数，所以可以直接压缩成一个数，记压缩成的数为 $f_x$。例如对于 $84=2^2\times 3\times 7$，表示为 $1011$，因为 $2,3,7$ 分别是第 $1,2,4$ 个质数所以右数第 $1,2,4$ 位为 $1$，记为质因子状态。因此需要定义两个 $\text{tag}$ 分别表示这个区间整体乘上的值、这个区间整体按位或的这个值，记为 $\text{lazy1}$ 和 $\text{lazy2}$。

对于线段树的每一个区间，定义 $\text{mul}_x$ 和 $\text{res}_x$ 表示区间乘积、区间质因子压缩后的结果。

于是，对于每次区间乘 $x$ 时，$\text{mul}_x\gets \text{mul}_x\times \large x^{\text{len}}$（$\text{len}$ 表示该区间的长度），
$\text{res}_x\gets \text{res}_x\ \text{or}\ f_x$。同时维护上面提到的两个 $\text{tag}$。Pushup 中 $\text{mul}_x$ 就是两个儿子的 $\text{mul}$ 乘积，$\text{res}_x$ 就是两个儿子 $\text{res}$ 按位或的值。Pushdown 中 $\text{mul}$ 需要乘上父亲的 $\text{lazy1}$ 的区间长度次方，$\text{res}$ 直接按位或父亲的 $\text{lazy2}$ 即可。

同时，还需要注意要提前预处理逆元，否则求逆元多一个 $\log$ 显然会 `TLE`。

[提交记录。](https://codeforces.com/contest/1114/submission/189390683)

---

## 作者：esquigybcu (赞：0)

> 2021-11-28 $\phi\to\varphi$

# 题意

维护一个序列 $a_{1\cdots n}$，支持：

- 区间乘

- 求区间乘积的 $\varphi$

## 关于 $\varphi$

题面里给的 $\varphi(n)$ 的定义是小于 $n$ 且与 $n$ 互质的数的个数。

设 $n$ 的质因数分解为 $p_1^{e_1}p_2^{e_2}\cdots p_k^{e_k}$. 

我们由中国剩余定理可知，一个 $0\le x<n$ 唯一对应它模 $p_i^{e_i}$ 的余数，而 $\gcd(x,n)=1$ 当且仅当 $\forall i,\gcd(n,p_i^{e_i})=1$. 这样，$x$ 模 $p_i^{e_i}$ 的余数就有 $p_i^{e_i}-p_i^{e_i-1}=p_i^{e_i}(1-\frac{1}{p_i})$ 种选择。所以 $\varphi(n)=\prod p_i^{e_i}(1-\frac{1}{p_i})=n\prod (1-\frac{1}{p_i})$.

# 做法

我们只需要维护区间乘，区间乘积，和区间里每个数有哪些质因子。题目告诉我们 $a_i\le300$，所以质因子只能是 $[2,300]$ 中的质数。而这样的质数只有 $62$ 个，因此我们可以将其状压到一个 long long 中。

维护两颗线段树：

- 第一颗用于保存数本身，支持区间乘，区间查乘积

- 第二颗用于保存数的因子状压，支持区间按位或，区间查按位或

# Code

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <utility>

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug printf
#endif

typedef long long ll;
const int N = 4e5 + 5, MOD = 1e9 + 7;

inline ll qpow(ll x, int k)
{
    if (k == 0) return 1;
    ll ans = qpow(x, k >> 1); ans = (ans * ans) % MOD;
    if (k & 1) ans = (ans * x) % MOD;
    return ans;
}

namespace times
{
    struct node
    {
        int l, r;
        ll prod, lazy;

        inline node() {prod = lazy = 1;}
    };
    struct segtree
    {
        node a[N << 2];

        #define u a[i]
        #define lc a[i << 1]
        #define rc a[i << 1 | 1]
        #define mid (u.l + u.r) >> 1
        #define len(v) (v.r - v.l)

        inline void pushup(int i)
        {
            u.prod = lc.prod * rc.prod; u.prod %= MOD;
        }

        inline void pushdown(int i)
        {
            if (u.lazy == 1) return;
            lc.prod *= qpow(u.lazy, len(lc)); lc.prod %= MOD;
            lc.lazy *= u.lazy;                lc.lazy %= MOD;
            rc.prod *= qpow(u.lazy, len(rc)); rc.prod %= MOD;
            rc.lazy *= u.lazy;                rc.lazy %= MOD;
            u.lazy = 1;
        }

        inline void build(ll *init, int i, int l, int r)
        {
            debug("times::QwQ.build(%d, %d, %d) called\n", i, l, r);
            u.l = l, u.r = r, u.lazy = 1;
            if (r - l == 1)
            {
                u.prod = init[l] % MOD;
                return;
            }
            build(init, i << 1, l, mid);
            build(init, i << 1 | 1, mid, r);
            pushup(i);
        }

        inline ll query(int i, int l, int r)
        {
            debug("times::QwQ.query(%d, %d, %d) called\n", i, l, r);
            if (l <= u.l && r >= u.r) return u.prod % MOD;
            if (r <= u.l || l >= u.r) return 1;
            pushdown(i);
            return (query(i << 1, l, r) * query(i << 1 | 1, l, r)) % MOD;
        }

        inline void modify(int i, int l, int r, ll k)
        {
            debug("times::QwQ.modify(%d, %d, %d, %lld) called\n", i, l, r, k);
            if (l <= u.l && r >= u.r)
            {
                u.prod *= qpow(k, len(u)); u.prod %= MOD;
                u.lazy *= k;               u.lazy %= MOD;
                return;
            }
            if (r <= u.l || l >= u.r) return;
            pushdown(i);
            modify(i << 1, l, r, k); modify(i << 1 | 1, l, r, k);
            pushup(i);
        }

        #undef u
        #undef lc
        #undef rc
        #undef mid
        #undef len
    }
    QwQ;
}

namespace bit_or
{
    struct node
    {
        int l, r;
        ll ans, lazy;

        inline node() {ans = lazy = 0;}
    };
    struct segtree
    {
        node a[N << 2];

        #define u a[i]
        #define lc a[i << 1]
        #define rc a[i << 1 | 1]
        #define mid (u.l + u.r) >> 1
        #define len(v) (v.r - v.l)

        inline void pushup(int i)
        {
            u.ans = lc.ans | rc.ans;
        }

        inline void pushdown(int i)
        {
            if (u.lazy == 0) return;
            lc.ans  |= u.lazy;
            lc.lazy |= u.lazy;
            rc.ans  |= u.lazy;
            rc.lazy |= u.lazy;
            u.lazy = 0;
        }

        inline void build(ll *init, int i, int l, int r)
        {
            debug("bit_or::QwQ.build(%d, %d, %d) called\n", i, l, r);
            u.l = l, u.r = r, u.lazy = 0;
            if (r - l == 1)
            {
                u.ans = init[l];
                return;
            }
            build(init, i << 1, l, mid);
            build(init, i << 1 | 1, mid, r);
            pushup(i);
        }

        inline ll query(int i, int l, int r)
        {
            debug("bit_or::QwQ.query(%d, %d, %d) called\n", i, l, r);
            if (l <= u.l && r >= u.r) return u.ans;
            if (r <= u.l || l >= u.r) return 0;
            pushdown(i);
            return query(i << 1, l, r) | query(i << 1 | 1, l, r);
        }

        inline void modify(int i, int l, int r, ll k)
        {
            if (l <= u.l && r >= u.r)
            {
                u.ans  |= k;
                u.lazy |= k;
                return;
            }
            if (r <= u.l || l >= u.r) return;
            pushdown(i);
            modify(i << 1, l, r, k); modify(i << 1 | 1, l, r, k);
            pushup(i);
        }

        #undef u
        #undef lc
        #undef rc
        #undef mid
        #undef len
    }
    QwQ;
}

int prime[305], rank[305];
inline void QwQ()
{
    prime[0] = 2; rank[2] = 0;
    prime[1] = 3; rank[3] = 1;
    prime[2] = 5; rank[5] = 2;
    prime[3] = 7; rank[7] = 3;
    prime[4] = 11; rank[11] = 4;
    prime[5] = 13; rank[13] = 5;
    prime[6] = 17; rank[17] = 6;
    prime[7] = 19; rank[19] = 7;
    prime[8] = 23; rank[23] = 8;
    prime[9] = 29; rank[29] = 9;
    prime[10] = 31; rank[31] = 10;
    prime[11] = 37; rank[37] = 11;
    prime[12] = 41; rank[41] = 12;
    prime[13] = 43; rank[43] = 13;
    prime[14] = 47; rank[47] = 14;
    prime[15] = 53; rank[53] = 15;
    prime[16] = 59; rank[59] = 16;
    prime[17] = 61; rank[61] = 17;
    prime[18] = 67; rank[67] = 18;
    prime[19] = 71; rank[71] = 19;
    prime[20] = 73; rank[73] = 20;
    prime[21] = 79; rank[79] = 21;
    prime[22] = 83; rank[83] = 22;
    prime[23] = 89; rank[89] = 23;
    prime[24] = 97; rank[97] = 24;
    prime[25] = 101; rank[101] = 25;
    prime[26] = 103; rank[103] = 26;
    prime[27] = 107; rank[107] = 27;
    prime[28] = 109; rank[109] = 28;
    prime[29] = 113; rank[113] = 29;
    prime[30] = 127; rank[127] = 30;
    prime[31] = 131; rank[131] = 31;
    prime[32] = 137; rank[137] = 32;
    prime[33] = 139; rank[139] = 33;
    prime[34] = 149; rank[149] = 34;
    prime[35] = 151; rank[151] = 35;
    prime[36] = 157; rank[157] = 36;
    prime[37] = 163; rank[163] = 37;
    prime[38] = 167; rank[167] = 38;
    prime[39] = 173; rank[173] = 39;
    prime[40] = 179; rank[179] = 40;
    prime[41] = 181; rank[181] = 41;
    prime[42] = 191; rank[191] = 42;
    prime[43] = 193; rank[193] = 43;
    prime[44] = 197; rank[197] = 44;
    prime[45] = 199; rank[199] = 45;
    prime[46] = 211; rank[211] = 46;
    prime[47] = 223; rank[223] = 47;
    prime[48] = 227; rank[227] = 48;
    prime[49] = 229; rank[229] = 49;
    prime[50] = 233; rank[233] = 50;
    prime[51] = 239; rank[239] = 51;
    prime[52] = 241; rank[241] = 52;
    prime[53] = 251; rank[251] = 53;
    prime[54] = 257; rank[257] = 54;
    prime[55] = 263; rank[263] = 55;
    prime[56] = 269; rank[269] = 56;
    prime[57] = 271; rank[271] = 57;
    prime[58] = 277; rank[277] = 58;
    prime[59] = 281; rank[281] = 59;
    prime[60] = 283; rank[283] = 60;
    prime[61] = 293; rank[293] = 61;
}

inline ll factor(int n)
{
    debug("factor(%d) called\n", n);
    ll ans = 0;
    for (register int i = 2; i * i <= n; i++)
        while (n % i == 0)
            n /= i, ans |= (1 << rank[i]);
    if (n > 1)
        ans |= (1ll << rank[n]);
    debug("factor(%d) = %d\n", n, ans);
    return ans;
}

ll init[N], facinit[N];
char rsg23[100];

int main()
{
    QwQ();
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &init[i]), facinit[i] = factor(init[i]);
    times::QwQ.build(init, 1, 1, n + 1);
    bit_or::QwQ.build(facinit, 1, 1, n + 1);

    while (q--)
    {
        int l, r; ll x;
        scanf("%s", rsg23);
        if (rsg23[0] == 'M')
        {
            scanf("%d %d %lld", &l, &r, &x);
            times::QwQ.modify(1, l, r + 1, x);
            bit_or::QwQ.modify(1, l, r + 1, factor(x));
        }
        if (rsg23[0] == 'T')
        {
            scanf("%d %d", &l, &r);
            ll ans = times::QwQ.query(1, l, r + 1); debug("ans = %lld\n", ans);
            ll fac = bit_or::QwQ.query(1, l, r + 1); debug("fac = %d\n", fac);
            for (int i = 0; i < 64; i++)
                if ((fac >> i) & 1)
                {
                    debug("ans has prime factor %d\n", prime[i]);
                    ans *= (prime[i] - 1);          ans %= MOD;
                    ans *= qpow(prime[i], MOD - 2); ans %= MOD;
                }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
```

---

## 作者：Citnaris (赞：0)

# Please, another Queries on Array?

**题意**

一个序列 $a_{[1, n]}$ ，支持改变 / 查询

* $\forall l\le i\le r,a_i\leftarrow a_i\times x$
* $\varphi(\prod_{i = l}^{r}a_i)$

**前置知识**

$\text{Phi}$ / $\varphi$ 的求法：

记 $n = p_1^{a_1}\times p_2^{a_2}\cdots \times p_k^{a_k}$ ，则 $\varphi(n)=n\times \prod_{i = 1}^{k}\frac{p_i - 1}{p_i}$ 。

**思路**

显然，这是个数据结构，我们考虑线段树

* $\text{Naive Solution}$

线段树维护一下区间乘 $x$ ，区间乘积。

每次如果是操作 $1$ 就 `modify(1, 1, n, l, r, x)` ，否则 `printf("%lld\n", calcphi(query(1, 1, n, l, r)))` 。

这个做法有个非常明显的问题：会爆 `long long` ，如果高精度的话时间空间都会爆炸。

* $\text{Correct Solution}$

注意到 $\forall l\le i\le r,a_i\le 300, x\le 300$ ，$300$ 以内的质数个数为 $62$ ，我们考虑将区间的的质数因子的二进制状态压缩，维护区间乘积**模 $10^9+7$** ，以及区间的质数因子的状压。

每次询问我们先算出区间乘积 $x$ 和区间二进制状压 $y$ ，则答案可以通过 $x$ 和 $x$ 在取模前的质因子(由 $y$ 推出)计算 $\varphi$ 而来，此处需使用有理数取余。

代码实现细节：

1. 状态压缩需要使用 `long long` 。
2. 线段树维护的是 区间乘 $x$ 区间查询乘积 和 区间 $\text{or\ binary\_of\_divisors}\ (x)$ 区间查询 $\text{or}$ 。
3. 记得取模
4. 乘积的线段树 $\text{lazy\ \&\ sum}$ 初值为 $1$ ，$\text{or}$ 的线段树 $\text{lazy\ \&\ sum}$ 初值为 $0$ 。
5. 见代码

**复杂度**

Time $\mathcal{O}(q\log^2 n)$

Memory $\mathcal{O}(n)$

**代码**

建议忽略质数打表部分。

```cpp
#include <cstdio>
#include <algorithm> 

#define int long long

using namespace std;

const int MOD = 1000000007;

int mp[300], pm[300], pw[300];

inline int qpow(int x, int y) {
    if (!y) return 1;
    int t = qpow(x, y >> 1);
    t = t * t % MOD;
    if (y & 1) t =  t * x % MOD;
    return t;
} // 快速幂，有理数取余用

inline int zy(int x) {
    int ret = 0;
    for (int i = 2; i * i <= x; ++i) {
        if (!(x % i)) ret |= pw[mp[i]];
        while (!(x % i)) x /= i;
    }
    if (x > 1) ret |= pw[mp[x]];
    return ret;
} // 状压

template < int SIZE > 
struct SegmentTreeTimes {
    int sum[SIZE << 2], lazy[SIZE << 2];

    inline void pushup(int p) {
        sum[p] = sum[p << 1] * sum[p << 1 | 1] % MOD;
    }

    inline void pushdown(int p, int l, int r) {
        if (lazy[p] == 1) return;
        int mid = l + r >> 1;
        sum[p << 1] = sum[p << 1] * qpow(lazy[p], mid - l + 1) % MOD;
        lazy[p << 1] = lazy[p << 1] * lazy[p] % MOD;
        sum[p << 1 | 1] = sum[p << 1 | 1] * qpow(lazy[p], r - mid) % MOD;
        lazy[p << 1 | 1] = lazy[p << 1 | 1] * lazy[p] % MOD;
        lazy[p] = 1;
    }

    inline void build(int p, int l, int r) {
        lazy[p] = sum[p] = 1;
        if (l == r) return;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    inline void modify(int p, int l, int r, int a, int b, int v) {
        if (r < a || l > b) return;
        if (a <= l && r <= b) {
            sum[p] = sum[p] * qpow(v, r - l + 1) % MOD, lazy[p] = lazy[p] * v % MOD;
            return;
        }
        pushdown(p, l, r);
        int mid = l + r >> 1;
        modify(p << 1, l, mid, a, b, v);
        modify(p << 1 | 1, mid + 1, r, a, b, v);
        pushup(p);
    }

    inline int query(int p, int l, int r, int a, int b) {
        if (r < a || l > b) return 1;
        if (a <= l && r <= b) return sum[p];
        pushdown(p, l, r);
        int mid = l + r >> 1;
        return query(p << 1, l, mid, a, b) * query(p << 1 | 1, mid + 1, r, a, b) % MOD;
    }
}; // times segtree

template < int SIZE > 
struct SegmentTreeOr {
    int sum[SIZE << 2], lazy[SIZE << 2];
    
    inline void pushup(int p) {
        sum[p] = sum[p << 1] | sum[p << 1 | 1];
    }

    inline void pushdown(int p) {
        if (lazy[p] == 0) return;
        sum[p << 1] = sum[p << 1] | lazy[p];
        lazy[p << 1] = lazy[p << 1] | lazy[p];
        sum[p << 1 | 1] = sum[p << 1 | 1] | lazy[p];
        lazy[p << 1 | 1] = lazy[p << 1 | 1] | lazy[p];
        lazy[p] = 0;
    }

    inline void build(int p, int l, int r) {
        if (l == r) {
            sum[p] = 0, lazy[p] = 0;
            return;
        }
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    inline void modify(int p, int l, int r, int a, int b, int v) {
        if (r < a || l > b) return;
        if (a <= l && r <= b) {
            sum[p] = sum[p] | v, lazy[p] = lazy[p] | v;
            return;
        }
        pushdown(p);
        int mid = l + r >> 1;
        modify(p << 1, l, mid, a, b, v);
        modify(p << 1 | 1, mid + 1, r, a, b, v);
        pushup(p);
    }

    inline int query(int p, int l, int r, int a, int b) {
        if (r < a || l > b) return 0;
        if (a <= l && r <= b) return sum[p];
        pushdown(p);
        int mid = l + r >> 1;
        return query(p << 1, l, mid, a, b) | query(p << 1 | 1, mid + 1, r, a, b);
    }
}; // or segtree

const int NR = 4e5 + 5;

SegmentTreeTimes < NR > st;
SegmentTreeOr < NR > st1;

int n, a[NR], q;
char op[20];

void init() {
	pw[0] = 1;
	for (int i = 1; i <= 62; ++i) pw[i] = pw[i - 1] * 2;
    mp[2] = 0;
    mp[3] = 1;
    mp[5] = 2;
    mp[7] = 3;
    mp[11] = 4;
    mp[13] = 5;
    mp[17] = 6;
    mp[19] = 7;
    mp[23] = 8;
    mp[29] = 9;
    mp[31] = 10;
    mp[37] = 11;
    mp[41] = 12;
    mp[43] = 13;
    mp[47] = 14;
    mp[53] = 15;
    mp[59] = 16;
    mp[61] = 17;
    mp[67] = 18;
    mp[71] = 19;
    mp[73] = 20;
    mp[79] = 21;
    mp[83] = 22;
    mp[89] = 23;
    mp[97] = 24;
    mp[101] = 25;
    mp[103] = 26;
    mp[107] = 27;
    mp[109] = 28;
    mp[113] = 29;
    mp[127] = 30;
    mp[131] = 31;
    mp[137] = 32;
    mp[139] = 33;
    mp[149] = 34;
    mp[151] = 35;
    mp[157] = 36;
    mp[163] = 37;
    mp[167] = 38;
    mp[173] = 39;
    mp[179] = 40;
    mp[181] = 41;
    mp[191] = 42;
    mp[193] = 43;
    mp[197] = 44;
    mp[199] = 45;
    mp[211] = 46;
    mp[223] = 47;
    mp[227] = 48;
    mp[229] = 49;
    mp[233] = 50;
    mp[239] = 51;
    mp[241] = 52;
    mp[251] = 53;
    mp[257] = 54;
    mp[263] = 55;
    mp[269] = 56;
    mp[271] = 57;
    mp[277] = 58;
    mp[281] = 59;
    mp[283] = 60;
    mp[293] = 61;
    pm[0] = 2;
    pm[1] = 3;
    pm[2] = 5;
    pm[3] = 7;
    pm[4] = 11;
    pm[5] = 13;
    pm[6] = 17;
    pm[7] = 19;
    pm[8] = 23;
    pm[9] = 29;
    pm[10] = 31;
    pm[11] = 37;
    pm[12] = 41;
    pm[13] = 43;
    pm[14] = 47;
    pm[15] = 53;
    pm[16] = 59;
    pm[17] = 61;
    pm[18] = 67;
    pm[19] = 71;
    pm[20] = 73;
    pm[21] = 79;
    pm[22] = 83;
    pm[23] = 89;
    pm[24] = 97;
    pm[25] = 101;
    pm[26] = 103;
    pm[27] = 107;
    pm[28] = 109;
    pm[29] = 113;
    pm[30] = 127;
    pm[31] = 131;
    pm[32] = 137;
    pm[33] = 139;
    pm[34] = 149;
    pm[35] = 151;
    pm[36] = 157;
    pm[37] = 163;
    pm[38] = 167;
    pm[39] = 173;
    pm[40] = 179;
    pm[41] = 181;
    pm[42] = 191;
    pm[43] = 193;
    pm[44] = 197;
    pm[45] = 199;
    pm[46] = 211;
    pm[47] = 223;
    pm[48] = 227;
    pm[49] = 229;
    pm[50] = 233;
    pm[51] = 239;
    pm[52] = 241;
    pm[53] = 251;
    pm[54] = 257;
    pm[55] = 263;
    pm[56] = 269;
    pm[57] = 271;
    pm[58] = 277;
    pm[59] = 281;
    pm[60] = 283;
    pm[61] = 293;
} // 打出质数表

signed main() {
    init();
    scanf("%lld %lld", &n, &q);
    st.build(1, 1, n), st1.build(1, 1, n);
    for (int i = 1; i <= n; ++i) 
        scanf("%lld", &a[i]), st.modify(1, 1, n, i, i, a[i]), st1.modify(1, 1, n, i, i, zy(a[i]));
    while (q --) {
        int l, r, x; scanf(" %s", op);
        if (op[0] == 'M') {
            scanf("%lld %lld %lld", &l, &r, &x);
            st.modify(1, 1, n, l, r, x);
            st1.modify(1, 1, n, l, r, zy(x)); // 更新
        }
        else {
            scanf("%lld %lld", &l, &r);
            int cj = st.query(1, 1, n, l, r) % MOD;
            int yz = st1.query(1, 1, n, l, r);
            for (int i = 61; i >= 0; --i)
                if (pw[i] <= yz) {
                    int tmp = pm[i];
                    cj = cj * (tmp - 1) % MOD * qpow(tmp, MOD - 2) % MOD;
                    yz -= pw[i];
                } // 计算 phi
            printf("%lld\n", cj % MOD);
        }
    }
    return 0;
}
```

**题外话**

推荐下大佬 @pzq_loves_qwq 的[数论 blog](https://www.luogu.com.cn/blog/alexcoderakioi/nt-huge-hole
) 。

---

## 作者：peterwuyihong (赞：0)

题意：区间乘，区间求积的欧拉函数。

乘的数和原序列的每个数不超过 $300$。

$300$。。。

我们于是有一个初级的想法，就是枚举每个质因子（不超过 $62$ 个），然后做一个区间加区间求和之类的东西，可以做到 $O(wn\log n)$ 的时间复杂度，$O(wn)$ 的空间复杂度。

如果你对每个质因子都处理一遍的话，可以做到 $O(n)$ 的空间复杂度，时间复杂度不变。

但是这个做法不大高明，我们考虑欧拉函数的性质。

那么你只需要维护区间乘积，再维护一下区间哪些质因数出现过即可，出现过就乘上一个 $\dfrac{p-1}p$。

维护质因数是否出现，可以压到一个 $\text{long long}$ 里面。

优化：注意到有些快速幂的底数不超过 $300$，这些光速幂。。。

分解质因数时可以每次除以这个数的最小质因子，这样分解 $n$ 的复杂度就是 $(\log n)$ 的。

时间复杂度，$w$ 指 $300$，$O(w\sqrt p+n(\log n+\log w)+m\log n\log c)$
```cpp
#define maxn 400010
const int p=1e9+7;
template<class _Tp,class _tp>void add(_Tp&x,const _tp& y){((x+=y)>=p)&&(x-=p);}template<class _Tp,class _tp>_Tp Add(_Tp x,const _tp y){add(x,y);return x;}
template<class _Tp,class _tp>void sub(_Tp&x,const _tp&y){((x-=y)<0)&&(x+=p);}template<class _Tp,class _tp>_Tp Sub(_Tp x,const _tp y){sub(x,y);return x;}
template<class _Tp,class _tp>void mul(_Tp&x,const _tp&y){x=1ll*x*y%p;}template<class _Tp,class _tp>_Tp Mul(const _Tp x,const _tp y){return 1ll*x*y%p;}
template<class _Tp,class _tp>_Tp ksm(_Tp a,_tp b){_Tp ans(1);for(;b;b>>=1,mul(a,a))if(b&1)mul(ans,a);return ans;} 
template<class _Tp>_Tp div2(_Tp a){if(a&1)a+=p;return a>>1;}
int n,m;
char ch[16];
int l,r,x;
struct prpr{
	int l,r;
	long long tag,u;
	int sm,g;
}tree[maxn<<2];
int pri[maxn],tot,to[maxn],lpf[maxn];
int gsm[322][32769][2];
void shai(int n){
	for(int i=2;i<=n;i++){
		if(!lpf[i])pri[lpf[i]=++tot]=i,to[i]=tot;
		for(int j=1;j<=lpf[i]&&i*pri[j]<=n;j++)lpf[i*pri[j]]=j;
	}
	for(int i=2;i<=300;i++){
		gsm[i][0][0]=gsm[i][0][1]=1;
		for(int j=1;j<=32768;j++)gsm[i][j][0]=Mul(gsm[i][j-1][0],i);
		for(int j=1;j<=32768;j++)gsm[i][j][1]=Mul(gsm[i][j-1][1],gsm[i][32768][0]);
	}
}
int Ksm(int i,int j){
	if(i==1)return 1;
	return Mul(gsm[i][j>>15][1],gsm[i][j&32767][0]);
}
void pushup(int x){
	tree[x].sm=Mul(tree[x<<1].sm,tree[x<<1|1].sm);
	tree[x].u=tree[x<<1].u|tree[x<<1|1].u;
}
void pushdown(int x){
	if(tree[x].g!=1){
		mul(tree[x<<1].g,tree[x].g);
		tree[x<<1].tag|=tree[x].tag;
		tree[x<<1].u|=tree[x].tag;
		mul(tree[x<<1|1].g,tree[x].g);
		tree[x<<1|1].tag|=tree[x].tag;
		tree[x<<1|1].u|=tree[x].tag;
		mul(tree[x<<1].sm,ksm(tree[x].g,tree[x<<1].r-tree[x<<1].l+1));
		mul(tree[x<<1|1].sm,ksm(tree[x].g,tree[x<<1|1].r-tree[x<<1|1].l+1));
		tree[x].g=1;tree[x].tag=0;
	}
}
void build(int l,int r,int o=1){
	tree[o].l=l,tree[o].r=r;
	tree[o].g=1;
	if(l==r){
		cin>>tree[o].sm;x=tree[o].sm;
		while(x-1)tree[o].u|=1ll<<lpf[x],x/=pri[lpf[x]];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,o<<1),build(mid+1,r,o<<1|1);
	pushup(o);
}
int xxy;
void change(int l,int r,long long _,int o=1){
	if(tree[o].l>=l&&tree[o].r<=r){
		tree[o].u|=_,tree[o].tag|=_;
		mul(tree[o].sm,Ksm(xxy,tree[o].r-tree[o].l+1));
		mul(tree[o].g,xxy);
		return;
	}pushdown(o);
	int mid=(tree[o].l+tree[o].r)>>1;
	if(l<=mid)change(l,r,_,o<<1);
	if(r>mid)change(l,r,_,o<<1|1);
	pushup(o);
}
void work(pair<int,long long>&a,pair<int,long long>b){
	mul(a.first,b.first);
	a.second|=b.second;
}
pair<int,long long>ask(int l,int r,int x=1){
	if(tree[x].l>=l&&tree[x].r<=r)return make_pair(tree[x].sm,tree[x].u);
	pushdown(x);
	int mid=(tree[x].l+tree[x].r)>>1;
	pair<int,long long>ans(1,0);
	if(l<=mid)work(ans,ask(l,r,x<<1));
	if(r>mid)work(ans,ask(l,r,x<<1|1));
	return ans;
}
long long gg;
int ans;
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n>>m;
	shai(300);
	build(1,n);
	while(m--){
		cin>>ch>>l>>r;
		if(ch[0]=='M'){
			cin>>x;
			xxy=x;
			gg=0;
			while(x-1)gg|=1ll<<lpf[x],x/=pri[lpf[x]];
			change(l,r,gg);
		}else{
			pair<int,long long>u=ask(l,r);
			ans=u.first;
			for(int i=1;i<=tot;i++)
			if(u.second>>i&1)mul(ans,Mul(pri[i]-1,Ksm(pri[i],p-2)));
			cout<<ans<<endl;
		}
	}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
我的 $\text{ask}$ 是用 $\text{pair}$ 存的，不大高明，而且快速也没 $\text{rk1}$ 高，被打爆了，只有 $\text{rk2}$。

---

