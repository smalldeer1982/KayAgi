# Eyes Closed

## 题目描述

Vasya and Petya were tired of studying so they decided to play a game. Before the game begins Vasya looks at array $ a $ consisting of $ n $ integers. As soon as he remembers all elements of $ a $ the game begins. Vasya closes his eyes and Petya does $ q $ actions of one of two types:

 $ 1) $ Petya says 4 integers $ l1,r1,l2,r2 $ — boundaries of two non-intersecting segments. After that he swaps one random element from the $ [l1,r1] $ segment with another random element from the $ [l2,r2] $ segment.

 $ 2) $ Petya asks Vasya the sum of the elements of $ a $ in the $ [l,r] $ segment.

Vasya is a mathematician so he answers Petya the mathematical expectation of the sum of the elements in the segment.

Your task is to write a program which will answer the second type questions as Vasya would do it. In other words your program should print the mathematical expectation of the sum of the elements of $ a $ in the $ [l,r] $ segment for every second type query.

## 样例 #1

### 输入

```
4 4
1 1 2 2
1 2 2 3 3
2 1 2
1 1 2 3 4
2 1 2
```

### 输出

```
3.0000000
3.0000000
```

## 样例 #2

### 输入

```
10 5
1 1 1 1 1 2 2 2 2 2
1 1 5 6 10
2 1 5
1 1 5 6 10
1 1 5 6 10
2 6 10
```

### 输出

```
6.0000000
8.0400000
```

## 样例 #3

### 输入

```
10 10
1 2 3 4 5 6 7 8 9 10
1 1 5 6 10
1 1 5 6 10
2 1 5
1 1 3 6 9
2 1 3
1 5 7 8 10
1 1 1 10 10
2 1 5
2 7 10
2 1 10
```

### 输出

```
23.0000000
14.0000000
28.0133333
21.5733333
55.0000000
```

# 题解

## 作者：yuzhechuan (赞：2)

期望推式子较简单题

---

### 题解：

首先由于期望的线性性，容易想到分开维护每个元素的期望，最后查询时求和

考虑推式子搞出每次修改对单个元素的影响

以第一个区间的一个元素$x_$为例

设$A,B$为区间1,2，$L_1L_2$为区间长度，$S_1S_2$为区间期望和，则：

$$E(x_i) = \dfrac{L_1 - 1}{L_1} * E(x_i) +\frac{1}{L_1}\times \sum\limits_{j\in B}\frac{E(x_j)}{L_2}$$

表示有$\frac{1}{L_1}$的概率被选中交换，交换得到的数也是在另外一个区间里等概率选一个数，其余情况保持不变

然后化简得到：

$$E(x_i) = \dfrac{L_1 - 1}{L_1} * E(x_i) +\frac{S_2}{L_1L_2}$$

第二个区间同理

于是我们可以用线段树维护区间加，区间乘，区间和（其实就是线段树2辣）

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int N=1e5+5;
double tr[N<<2],mtg[N<<2],ptg[N<<2];
int n,q;

void pushup(int x){
	tr[x]=tr[x<<1]+tr[x<<1|1];
}

void build(int x,int l,int r){
	mtg[x]=1;
	if(l==r){
		int v;
		tr[x]=read(v);
		return ;
	}
	int mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}

void pushdown(int x,int l,int r){
	int mid=l+r>>1;
	tr[x<<1]=tr[x<<1]*mtg[x]+ptg[x]*(mid-l+1);
	tr[x<<1|1]=tr[x<<1|1]*mtg[x]+ptg[x]*(r-mid);
	mtg[x<<1]*=mtg[x];
	mtg[x<<1|1]*=mtg[x];
	ptg[x<<1]=ptg[x<<1]*mtg[x]+ptg[x];
	ptg[x<<1|1]=ptg[x<<1|1]*mtg[x]+ptg[x];
	ptg[x]=0;
	mtg[x]=1;
}

void mup(int x,int l,int r,int p,int q,double v){ //区间乘
	if(p<=l&&r<=q){
		mtg[x]*=v;
		ptg[x]*=v;
		tr[x]*=v;
		return ;
	}
	pushdown(x,l,r);
	int mid=l+r>>1;
	if(p<=mid) mup(x<<1,l,mid,p,q,v);
	if(q>mid) mup(x<<1|1,mid+1,r,p,q,v);
	pushup(x);
}

void pup(int x,int l,int r,int p,int q,double v){ //区间加
	if(p<=l&&r<=q){
		ptg[x]+=v;
		tr[x]+=v*(r-l+1);
		return ;
	}
	pushdown(x,l,r);
	int mid=l+r>>1;
	if(p<=mid) pup(x<<1,l,mid,p,q,v);
	if(q>mid) pup(x<<1|1,mid+1,r,p,q,v);
	pushup(x);
}

double que(int x,int l,int r,int p,int q){
	if(p<=l&&r<=q) return tr[x];
	pushdown(x,l,r);
	int mid=l+r>>1;
	double res=0;
	if(p<=mid) res+=que(x<<1,l,mid,p,q);
	if(q>mid) res+=que(x<<1|1,mid+1,r,p,q);
	return res;
}

signed main(){
	read(n);read(q);
	build(1,1,n);
	while(q--){
		int op;
		read(op);
		if(op==1){
			int l1,r1,l2,r2;
			read(l1);read(r1);read(l2);read(r2);
			double sum1=que(1,1,n,l1,r1),sum2=que(1,1,n,l2,r2),len1=r1-l1+1,len2=r2-l2+1;
			mup(1,1,n,l1,r1,(len1-1)/len1); //我这个写法很暴力，常数有待优化
			pup(1,1,n,l1,r1,sum2/len1/len2);
			mup(1,1,n,l2,r2,(len2-1)/len2);
			pup(1,1,n,l2,r2,sum1/len1/len2);
		}
		else{
			int l,r;
			read(l);read(r);
			printf("%lf\n",que(1,1,n,l,r));
		}
	}
}
```

---

## 作者：Hoks (赞：1)

## 前言
推式子期望萌萌题，有点水了。

但是我不会写线段树 $2$。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
题面中这个操作一，我们考虑他到底是在做什么。

实际上就是对两个区间，算选出一个数的期望值，然后把这个期望值和另一个区间里的数交换，再计算期望。

考虑区间查出区间期望值，设这两个区间分别为 $l,r,x,y$，区间期望和为 $w1,w2$，则交换过去的数的期望值为 $\frac{w1}{r-l+1},\frac{w2}{y-x+1}$。

对于一个在区间 $[l,r]$ 的数，他不被交换的概率是 $\frac{r-l}{r-l+1}$，被交换的概率是 $\frac{1}{r-l+1}$，交换变成的权值是 $\frac{w2}{y-x+1}$，而对于 $[x,y]$ 区间也是同理。

所以题目就被转化成了区间和，区间乘，区间加，用线段树 $2$ 实现就行了。
## 代码
怎么有人线段树 $2$ 查询的时候没有 `pushdown` 啊。
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=1e5+10,M=3,INF=0x3f3f3f3f,mod=1004535809,p=13331;
int n,q,a[N],L[N<<2];double t[N<<2],lz[N<<2],mul[N<<2];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='?'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void build(int p,int l,int r)
{
    lz[p]=0;mul[p]=1;L[p]=r-l+1;if(l==r) return t[p]=read(),void();
    build(ls,l,mid);build(rs,mid+1,r);t[p]=t[ls]+t[rs];
}
inline void add(int p,double w){lz[p]+=w;t[p]+=w*L[p];}
inline void pushadd(int p){add(ls,lz[p]),add(rs,lz[p]);lz[p]=0;}
inline void mult(int p,double w){t[p]*=w;lz[p]*=w;mul[p]*=w;}
inline void pushmul(int p){mult(ls,mul[p]);mult(rs,mul[p]);mul[p]=1;}
inline void pushdown(int p){pushmul(p);pushadd(p);}
inline void modify(int p,int l,int r,int s,int e,double w)
{
    if(l>=s&&r<=e) return add(p,w),void();pushdown(p);
    if(mid>=s) modify(ls,l,mid,s,e,w);
    if(mid<e) modify(rs,mid+1,r,s,e,w);
    t[p]=t[ls]+t[rs];
}
inline void mdf(int p,int l,int r,int s,int e,double w)
{
    if(l>=s&&r<=e) return mult(p,w),void();pushdown(p);
    if(mid>=s) mdf(ls,l,mid,s,e,w);
    if(mid<e) mdf(rs,mid+1,r,s,e,w);
    t[p]=t[ls]+t[rs];
}
inline double query(int p,int l,int r,int s,int e)
{
    if(l>=s&&r<=e) return t[p];double res=0;pushdown(p);
    if(mid>=s) res+=query(ls,l,mid,s,e);
    if(mid<e) res+=query(rs,mid+1,r,s,e);
    return res;
}
inline void solve()
{
    n=read(),q=read();build(1,1,n);
    for(int i=1,op,l,r,x,y;i<=q;i++)
    {
        op=read(),l=read(),r=read();double w1,w2;
        if(op==2){printf("%.6lf\n",query(1,1,n,l,r));continue;}
        x=read(),y=read();w1=query(1,1,n,l,r)/(r-l+1)/(y-x+1),w2=query(1,1,n,x,y)/(r-l+1)/(y-x+1);
        mdf(1,1,n,l,r,1.0*(r-l)/(r-l+1));mdf(1,1,n,x,y,1.0*(y-x)/(y-x+1));
        modify(1,1,n,l,r,w2);modify(1,1,n,x,y,w1);
    }
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}

```

---

## 作者：ChthollyTree (赞：0)

考虑第一个操作

设 $[l1,r1]$ 长度为 $x$,$[l2,r2]$ 长度为$y$


对于区间为 $[l1,r1]$的数，每个数有$\frac{1}{x}$的概率与$[l2,r2]$的数交换

如果交换对这个数期望的贡献为 $\frac{\sum_{i=l2}^{r2}a_i}{xy}$

如果不交换则第i个数对期望贡献为$\frac{x-1}{x}*a_i$

所以我们可以维护一颗线段树，资瓷区间加，区间乘，区间求和

```
#include<bits/stdc++.h>
using namespace std;

#define db double
#define MAXN 100005 
#define lc(i) ((i)<<1)
#define rc(i) (((i)<<1)|1) 
#define wt(x) printf("%.3lf\n",x)

int n,m;
struct aa
{
	int l,r,n;
	db s,c,j;
}c[MAXN<<2];
int a[MAXN];


void maintain(int i) {
	if(c[i].l == c[i].r) return; 
	c[i].s = c[lc(i)].s + c[rc(i)].s;
}

void jianshu(int i,int l,int r)
{
	int mid = (l+r)>>1;
	c[i].l = l;
	c[i].r = r;
	c[i].c = 1;
	c[i].n = r-l+1;
	if(l == r)  {
		c[i].s = a[l];
		return;
	}
	jianshu(lc(i),l,mid); 
	jianshu(rc(i),mid+1,r);
	 maintain(i); 
}

void QAQ(int i,db cc,db j)
{
	bool fl = 0;
	c[i].s = c[i].s*cc+j*c[i].n;
	c[i].c *= cc;
	c[i].j *= cc;
	c[i].j += j;
}

void pushdown(int i){
	if(c[i].l == c[i].r) return;
	QAQ(lc(i),c[i].c,c[i].j);
	QAQ(rc(i),c[i].c,c[i].j);
	c[i].j = 0;
	c[i].c = 1;
}


db he(int i,int l,int r) {
	pushdown(i);
	if(l <= c[i].l && c[i].r <= r) 
	{
		return c[i].s;
	}
	if(c[i].l > r || c[i].r < l) return 0;
	db ans = he(lc(i),l,r) + he(rc(i),l,r);
	return ans;
}

void cheng(int i,int l,int r,db cc) {
	pushdown(i);
	if(l <= c[i].l && c[i].r <= r)  {
		QAQ(i,cc,0);
		return;
	}
	if(c[i].l > r || c[i].r < l) return;
	cheng(lc(i),l,r,cc);
	cheng(rc(i),l,r,cc);
	maintain(i);
}

void jia(int i,int l,int r,db j)
{	 
	pushdown(i);
	if(l <= c[i].l && c[i].r <= r)  {
		QAQ(i,1,j);
		return;
	}
	if(c[i].l > r || c[i].r < l) return;
	jia(lc(i),l,r,j);
	jia(rc(i),l,r,j);
	maintain(i);
}

void rd() {
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i ++) 
		cin >> a[i];
}

int main()
{
	rd();
	jianshu(1,1,n); 
	for(int i = 1; i <= m; i ++)
	{
		int opt,la,lb,ra,rb;
		scanf("%d",&opt);
		if(opt == 1)
		{
			scanf("%d%d%d%d",&la,&ra,&lb,&rb);
			db x = ra-la+1,y = rb-lb+1;
			
			db ay = he(1,lb,rb)/y,ax = he(1,la,ra)/x;/
			cheng(1,la,ra,(x-1)/x);
			jia(1,la,ra,ay/x);	
			cheng(1,lb,rb,(y-1)/y);
			jia(1,lb,rb,ax/y);
		}
		if(opt == 2)
		{
			int l,r;
			scanf("%d%d",&l,&r); 
			db ans = he(1,l,r);
			printf("%.6lf\n",ans);
		}
	} 
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

这真的不是 AT_abc331_f？

考虑维护每一个数的值的期望。初始时时候显然 $i$ 位置的值期望为 $a_i$。

现在对于一次对 $[l_1,r_1],[l_2,r_2]$ 执行的操作。现在定义 $s_1=\sum\limits_{i=l_1}^{r_1}a_i,s_2=\sum\limits_{i=l_2}^{r_2}a_i$。分别考虑两个区间内元素期望值的变化：

1. 计算区间 $[l_1,r_1]$ 内值的期望变化。

区间 $[l_2,r_2]$ 中选择一个数的期望值为 $\frac{s_2}{r_2-l_2+1}$，和区间 $[l_1,r_1]$ 内某一个值交换的概率为 $\frac{1}{r_1-l_1+1}$。因此 $[l_1,r_1]$ 中某一个值 $i\in[l_1,r_1]$ 期望值有 $\frac{1}{r_1-l_1+1}$ 的概率变为 $\frac{s_2}{r_2-l_2+1}$，有 $\frac{r_1-l_1}{r_1-l_1+1}$ 的概率不变。

即 $\forall i\in[l_1,r_1],a'_i=\frac{1}{r_1-l_1+1}\times\frac{s_2}{r_2-l_2+1}+\frac{r_1-l_1}{r_1-l_1+1}\times a_i$。

2. 计算区间 $[l_2,r_2]$ 内值的期望变化。

该部分同理：区间 $[l_1,r_1]$ 中选择一个数的期望值为 $\frac{s_1}{r_1-l_1+1}$，和区间 $[l_2,r_2]$ 内某一个值交换的概率为 $\frac1{r_2-l_2+1}$。因此 $[l_2,r_2]$ 中某一个值 $i\in[l_2,r_2]$ 期望值有 $\frac1{r_2-l_2+1}$ 的概率变为 $\frac{s_1}{r_1-l_1+1}$，有 $\frac{r_2-l_2}{r_2-l_2+1}$ 的概率不变。

即 $\forall i\in[l_2,r_2],a_i'=\frac{1}{r_2-l_2+1}\times\frac{s_1}{r_1-l_1+1}+\frac{r_2-l_2}{r_2-l_2+1}\times a_i$。

问题即区间乘区间加区间求和，使用两个懒标记的线段树维护即可。时间复杂度为 $O(n\log n)$ 可以通过。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200010;
const int mod = 1e9 + 7;
int a[N];
struct Node {
    int l, r;
    double sum, add, mul;
    void init(int p) {
        l = r = p;
        sum = a[p];
        add = 0, mul = 1;
    }
    void push(double ladd, double lmul) {
        sum = sum * lmul + ladd * (r - l + 1);
        mul *= lmul;
        add = add * lmul + ladd;
    }
} tree[N << 2];
Node operator+(const Node &l, const Node &r) {
    return {l.l, r.r, l.sum + r.sum, 0.0, 1.0};
}
void build(int l, int r, int rt) {
    if (l == r) return tree[rt].init(l);
    int mid = l + r >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
void pushdown(int rt) {
    if (tree[rt].add != 0 || tree[rt].mul != 1) {
        tree[rt << 1].push(tree[rt].add, tree[rt].mul);
        tree[rt << 1 | 1].push(tree[rt].add, tree[rt].mul);
        tree[rt].add = 0, tree[rt].mul = 1;
    }
}
void modifyadd(int rt, int ll, int rr, double v) {
    int &l = tree[rt].l, &r = tree[rt].r;
    if (ll <= l && r <= rr) return tree[rt].push(v, 1.0);
    int mid = l + r >> 1;
    pushdown(rt);
    if (ll <= mid) modifyadd(rt << 1, ll, rr, v);
    if (mid < rr) modifyadd(rt << 1 | 1, ll, rr, v);
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
void modifymul(int rt, int ll, int rr, double v) {
    int &l = tree[rt].l, &r = tree[rt].r;
    if (ll <= l && r <= rr) return tree[rt].push(0.0, v);
    int mid = l + r >> 1;
    pushdown(rt);
    if (ll <= mid) modifymul(rt << 1, ll, rr, v);
    if (mid < rr) modifymul(rt << 1 | 1, ll, rr, v);
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
double query(int rt, int ll, int rr) {
    int &l = tree[rt].l, &r = tree[rt].r;
    if (ll <= l && r <= rr) return tree[rt].sum;
    int mid = l + r >> 1;
    double sum = 0;
    pushdown(rt);
    if (ll <= mid) sum = query(rt << 1, ll, rr);
    if (mid < rr) sum += query(rt << 1 | 1, ll, rr);
    return sum;
}
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, n, 1);
    while (q--) {
        int o;
        cin >> o;
        if (o == 1) {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            double s1 = query(1, l1, r1), s2 = query(1, l2, r2);
            modifymul(1, l1, r1, 1. * (r1 - l1) / (r1 - l1 + 1));
            modifyadd(1, l1, r1, 1. / (r1 - l1 + 1) * s2 / (r2 - l2 + 1));
            modifymul(1, l2, r2, 1. * (r2 - l2) / (r2 - l2 + 1));
            modifyadd(1, l2, r2, 1. / (r2 - l2 + 1) * s1 / (r1 - l1 + 1));
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(1, l, r) << '\n';
        }
    }
    return 0;
}
```

---

## 作者：tommymio (赞：0)

考虑 $1$ 操作对 $2$ 操作的影响。根据期望线性性质，计算区间期望和其实就是计算区间内每一个数的期望值。那么 $1$ 操作过后，以 $[L_1,R_1]$ 为例，$E(x_i)=\dfrac{R_1-L_1}{R_1-L_1+1}E(x_i)+\dfrac{1}{(R_1-L_1+1)(R_2-L_2+1)} \sum_{k\in[L_2,R_2]}E(x_k)$。所以维护区间和，支持区间乘、区间加即可。

---

