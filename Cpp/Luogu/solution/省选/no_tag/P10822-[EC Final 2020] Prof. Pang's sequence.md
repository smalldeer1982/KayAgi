# [EC Final 2020] Prof. Pang's sequence

## 题目描述

庞教授得到一个固定的序列 $a_1, \ldots, a_n$ 和 $m$ 个查询。

每个查询由两个整数 $l$ 和 $r$ 指定，满足 $1\le l\le r\le n$。对于每个查询，你需要回答满足 $l\le i\le j\le r$ 且 $a_i, \ldots, a_j$ 中不同整数的数量为奇数的整数对 $(i, j)$ 的数量。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5
1 2 3 2 1
5
1 5
2 4
1 3
2 5
4 4```

### 输出

```
10
3
4
6
1```

## 样例 #2

### 输入

```
5
2 3 5 1 5
5
2 3
1 1
1 3
2 5
2 4```

### 输出

```
2
1
4
6
4```

## 样例 #3

### 输入

```
10
2 8 5 1 10 5 9 9 3 5
10
6 8
1 2
3 5
5 7
1 7
3 9
4 9
1 4
3 7
2 5```

### 输出

```
4
2
4
4
16
16
12
6
9
6```

# 题解

## 作者：Nt_Tsumiki (赞：3)

先离线。

你考虑维护一个长得像历史和的 DS，你维护一个指针 $r$ 扫一遍整个序列，线段树上每个叶子 $l$ 代表 $[l,r]$，这段子区间的前缀中有多少个含有奇数个不同的数。

对于不同的数我们有经典 trick 你记一个 $pre_i$ 表示与 $a_{pre_i}=a_i$ 且离 $i$ 最近的数，那你每次要更改的就是 $[pre_r+1,r]$ 这段区间的奇偶性。

然后你对 $[1,r]$ 这段前缀所有为奇数的点进行一个整体加一，你考虑这个玩意咋维护。

一个比较 navie 的想法是上矩阵，常熟太大，我们有全♂新♂做♂法♂。

考虑维护两棵线段树，然后每次反转奇偶性就是交换对应区间，然后整体加一只对一棵线段树做就行了。

```cpp
bool M1;
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

#define N 500005
#define LL long long

inline int R() {
    int x=0; bool f=0; char c=getchar();
    while (!isdigit(c)) f|=(c=='-'),c=getchar();
    while (isdigit(c)) x=x*10+c-'0',c=getchar();
    return f?-x:x;
}

template<typename T>
void W(T x,char Extra=0) {
    if (x<0) putchar('-'),x=-x; if (x>9) W(x/10);
    putchar(x%10+'0'); if (Extra) putchar(Extra);
}

using namespace std;
int n,m,a[N],tmp[N],pre[N]; LL ans[N];

int tcnt,rt[2];
struct Tree { LL sum,tag; int siz,ls,rs; }t[N<<3];

void build(int &x,int l,int r,int op) {
    x=++tcnt;
    if (l==r) return t[x].siz=(!op),void();
    int mid=(l+r>>1);
    build(t[x].ls,l,mid,op); build(t[x].rs,mid+1,r,op);
    t[x].siz=t[t[x].ls].siz+t[t[x].rs].siz;
}

void pushdown(int x) {
    if (t[x].tag) {
        if (t[x].ls) t[t[x].ls].sum+=1ll*t[t[x].ls].siz*t[x].tag,t[t[x].ls].tag+=t[x].tag;
        if (t[x].rs) t[t[x].rs].sum+=1ll*t[t[x].rs].siz*t[x].tag,t[t[x].rs].tag+=t[x].tag;
        t[x].tag=0;
    }
}

void swp(int &x,int &y,int l,int r,int L,int R) {
    if (L<=l and r<=R) return swap(x,y),void();
    int mid=(l+r>>1); pushdown(x); pushdown(y);
    if (L<=mid) swp(t[x].ls,t[y].ls,l,mid,L,R);
    if (R>mid) swp(t[x].rs,t[y].rs,mid+1,r,L,R);
    t[x].sum=t[t[x].ls].sum+t[t[x].rs].sum;
    t[x].siz=t[t[x].ls].siz+t[t[x].rs].siz;
    t[y].sum=t[t[y].ls].sum+t[t[y].rs].sum;
    t[y].siz=t[t[y].ls].siz+t[t[y].rs].siz;
}

void upd(int x,int l,int r,int L,int R,int k) {
    if (L<=l and r<=R) return t[x].sum+=t[x].siz*k,t[x].tag+=k,void();
    int mid=(l+r>>1); pushdown(x);
    if (L<=mid) upd(t[x].ls,l,mid,L,R,k);
    if (R>mid) upd(t[x].rs,mid+1,r,L,R,k);
    t[x].sum=t[t[x].ls].sum+t[t[x].rs].sum;
}

LL ask(int x,int l,int r,int L,int R) {
    if (L<=l and r<=R) return t[x].sum;
    int mid=(l+r>>1); pushdown(x);
    if (R<=mid) return ask(t[x].ls,l,mid,L,R);
    else if (L>mid) return ask(t[x].rs,mid+1,r,L,R);
    else return ask(t[x].ls,l,mid,L,R)+ask(t[x].rs,mid+1,r,L,R);
}

struct Que { int l,id; };
vector<Que> que[N];

bool M2;

int main() {
    // cerr<<(&M2-&M1)/1024.0/1024<<'\n';
    // freopen("task.in","r",stdin);
    // freopen("task.out","w",stdout);
    n=R();
    for (int i=1;i<=n;i++) a[i]=R(),pre[i]=tmp[a[i]],tmp[a[i]]=i;
    m=R();
    for (int i=1;i<=m;i++) {
        int l=R(),r=R();
        que[r].push_back({l,i});
    }
    build(rt[0],1,n,0); build(rt[1],1,n,1);
    for (int i=1;i<=n;i++) {
        swp(rt[0],rt[1],1,n,pre[i]+1,i);
        upd(rt[1],1,n,1,i,1);
        for (auto [l,id]:que[i])
            ans[id]=ask(rt[0],1,n,l,i)+ask(rt[1],1,n,l,i);
    }
    for (int i=1;i<=m;i++) W(ans[i],'\n');
    return 0;
}
```

---

## 作者：_Yonder_ (赞：2)

这不是普通线段树吗，为什么要历史和，矩阵乘法。

考虑按 $r$ 扫描线，那么我们可以快速维护每个 $l$ 到 $r$ 的颜色个数的奇偶，就是区间异或嘛。

然后我们还需要给每个颜色个数为奇数的 $l$ 答案加一，显然可以打标记，答案就是直接查询区间和。

然后是标记该如何下传，我们可以让异或标记的优先级大于加标记，那么下传异或标记时反转加标记就行了。

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/P10822)

**题目大意**

> 给定 $a_1\sim a_n$，$q$ 次询问 $[l,r]$ 有多少子区间本质不同颜色数为奇数。
>
> 数据范围：$n,q\le 5\times 10^5$。

**思路分析**

设 $a_I$ 上一次出现为 $pre_i$，那么扫描线 $i-1\to i$ 时就会把 $l\in(pre_i,i]$ 范围的区间颜色数 $+1$。

维护奇偶性，我们要支持区间反转区间历史和。

类似区间加区间历史和，构造一个历史和标记，每个线段树节点维护：每次打历史标记时，当前节点的懒标记是处于反转还是未反转状态，对这两种情况分别记录次数即可。

信息合并和标记下传都是容易的。

时间复杂度：$\mathcal O((n+q)\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5e5+5;
int n,q;
struct SegmentTree {
	int sum[MAXN<<2],len[MAXN<<2];
	bool tg[MAXN<<2];
	int t0[MAXN<<2],t1[MAXN<<2];
	ll hsum[MAXN<<2];
	void adt(int p,int z0,int z1,int rv) {
		hsum[p]+=1ll*z0*sum[p]+1ll*z1*(len[p]-sum[p]);
		if(tg[p]) t0[p]+=z1,t1[p]+=z0;
		else t0[p]+=z0,t1[p]+=z1;
		if(rv) tg[p]^=1,sum[p]=len[p]-sum[p];
	}
	void psd(int p) { adt(p<<1,t0[p],t1[p],tg[p]),adt(p<<1|1,t0[p],t1[p],tg[p]),t0[p]=t1[p]=tg[p]=0; }
	void psu(int p) { sum[p]=sum[p<<1]+sum[p<<1|1],hsum[p]=hsum[p<<1]+hsum[p<<1|1]; }
	void init(int l=1,int r=n,int p=1) {
		len[p]=r-l+1;
		if(l==r) return ;
		int mid=(l+r)>>1;
		init(l,mid,p<<1),init(mid+1,r,p<<1|1);
	}
	void upd(int ul,int ur,int l=1,int r=n,int p=1) {
		if(ul<=l&&r<=ur) return adt(p,0,0,1),void();
		int mid=(l+r)>>1; psd(p);
		if(ul<=mid) upd(ul,ur,l,mid,p<<1);
		if(mid<ur) upd(ul,ur,mid+1,r,p<<1|1);
		psu(p);
	}
	ll qry(int ul,int ur,int l=1,int r=n,int p=1) {
		if(ul<=l&&r<=ur) return hsum[p];
		int mid=(l+r)>>1; psd(p);
		if(ur<=mid) return qry(ul,ur,l,mid,p<<1);
		if(mid<ul) return qry(ul,ur,mid+1,r,p<<1|1);
		return qry(ul,ur,l,mid,p<<1)+qry(ul,ur,mid+1,r,p<<1|1);
	}
}	T;
ll ans[MAXN];
int a[MAXN],p[MAXN];
vector <array<int,2>> Q[MAXN];
signed main() {
	ios::sync_with_stdio(false);
	cin>>n,T.init();
	for(int i=1;i<=n;++i) cin>>a[i];
	cin>>q;
	for(int i=1,l,r;i<=q;++i) cin>>l>>r,Q[r].push_back({l,i});
	for(int i=1;i<=n;++i) {
		T.upd(p[a[i]]+1,i),p[a[i]]=i,T.adt(1,1,0,0);
		for(auto z:Q[i]) ans[z[1]]=T.qry(z[0],i);
	}
	for(int i=1;i<=q;++i) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：2)

考虑求出每个数上一次出现位置后，这个问题变成数区间中有多少个子区间满足其中权值小于左端点的数数量为偶数，考虑对于一个 $r$ 将所有 $l$ 的答案扔到线段树上维护，每次新加入一个 $r$ 实际上就是让左端点在区间 $(pre_r,r]$ 内的所有区间奇偶翻转，再结合要回答子区间询问，所以线段树要支持区间翻转 $1,0$ 与查询区间历史和，考虑矩阵上维护区间 $0,1$ 的数量与历史和即可，本题使用矩阵较为卡常，笔者使用了将 vector 换成链表与将不同大小的矩阵不同封装的方法，下面给出笔者实现。

```cpp
#include<bits/stdc++.h>
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
const int maxn = 5e5+1;
struct Matrix{
    long long a[3][3];
    int n,m;
    Matrix(int N=0,int M=0){
        n=N,m=M;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++) a[i][j]=0;
    }
    Matrix operator*(const Matrix &x){
        Matrix res=Matrix(n,x.m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                for(int k=0;k<x.m;k++) res.a[i][k]=(res.a[i][k]+a[i][j]*x.a[j][k]);
        return res;
    }
    Matrix operator+(const Matrix &x){
        Matrix res=Matrix(n,m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++) res.a[i][j]=(a[i][j]+x.a[i][j]);
        return res;
    }
}e,tag[maxn<<2],tg1,tg2;
struct info{
    long long a[1][3];
    int n,m;
    info(int N=0,int M=0){
        n=N,m=M;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++) a[i][j]=0;
    }
    info operator*(const Matrix &x){
        info res=info(n,x.m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                for(int k=0;k<x.m;k++) res.a[i][k]=(res.a[i][k]+a[i][j]*x.a[j][k]);
        return res;
    }
    info operator+(const info &x){
        info res=info(n,m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++) res.a[i][j]=(a[i][j]+x.a[i][j]);
        return res;
    }
}tr[maxn<<2],sip;
void pushup(int cur){tr[cur]=tr[cur<<1]+tr[cur<<1|1];}
void pushdown(int cur){
    bool flag=true;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(tag[cur].a[i][j]!=e.a[i][j]) flag=false;
    if(flag==true) return ;
    tr[cur<<1]=tr[cur<<1]*tag[cur];
    tag[cur<<1]=tag[cur<<1]*tag[cur];
    tr[cur<<1|1]=tr[cur<<1|1]*tag[cur];
    tag[cur<<1|1]=tag[cur<<1|1]*tag[cur];
    tag[cur]=e;
    return ;
}
void mul(int cur,int lt,int rt,int l,int r,Matrix c){
    if(l>r) return ;
    if(l<=lt&&rt<=r){
        tr[cur]=tr[cur]*c;
        tag[cur]=tag[cur]*c;
        return ;
    }
    pushdown(cur);
    int mid=(lt+rt)>>1;
    if(l<=mid) mul(cur<<1,lt,mid,l,r,c);
    if(r>mid) mul(cur<<1|1,mid+1,rt,l,r,c);
    pushup(cur);
}
info ask(int cur,int lt,int rt,int l,int r){
    if(l>r) return info(1,3);
    if(l<=lt&&rt<=r) return tr[cur];
    pushdown(cur);
    int mid=(lt+rt)>>1;
    if(l<=mid&&r>mid) return ask(cur<<1,lt,mid,l,r)+ask(cur<<1|1,mid+1,rt,l,r);
    else if(l<=mid) return ask(cur<<1,lt,mid,l,r);
    else return ask(cur<<1|1,mid+1,rt,l,r);
}
int n,q;
long long answer[maxn];
int cnt[maxn];
struct star{
    int l,id,nxt;
}edge[maxn];
int head[maxn],tot;
int pre[maxn],a[maxn];
int main(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
        pre[i]=cnt[a[i]];
        cnt[a[i]]=i;
    }
    read(q);
    for(int i=1;i<=q;i++){
        int l,r;
        read(l);
        read(r);
        edge[++tot].l=l,edge[tot].id=i;
        edge[tot].nxt=head[r];
        head[r]=tot;
    }
    e=Matrix(3,3);
    sip=info(1,3);
    sip.a[0][0]=0;
    sip.a[0][1]=1;
    sip.a[0][2]=0;
    for(int i=0;i<3;i++) e.a[i][i]=1;
    for(int i=0;i<(maxn<<2);i++) tag[i]=e,tr[i]=sip;
    tg1=Matrix(3,3),tg2=Matrix(3,3);//翻转 不翻转
    tg1.a[0][1]=tg1.a[0][2]=tg1.a[1][0]=tg1.a[2][2]=1;
    tg2.a[0][0]=tg2.a[0][2]=tg2.a[1][1]=tg2.a[2][2]=1;
    for(int i=1;i<=n;i++){
        mul(1,1,n,pre[i]+1,i,tg1);
        mul(1,1,n,1,pre[i],tg2);
        for(int now=head[i];now;now=edge[now].nxt){
            info d=ask(1,1,n,edge[now].l,i);
            answer[edge[now].id]=d.a[0][2]+d.a[0][0];
        }
    }
    for(int i=1;i<=q;i++) write(answer[i]),putchar('\n');
    return 0;
}
```

---

## 作者：yhy2024 (赞：1)

线段树历史和 + 扫描线。

先离线下来，再扫过去，现在扫到了 $r$。维护一个序列，$b_l$ 表示以 $l$ 为左端点，区间 $[l,r]$ 是否可行。

考虑加入一个新数的影响。

设 $las_x$ 为 $x$ 上一次出现的位置。当加加入一个新数时，显然会对 $[las_{a_i}+1,i]$ 这一段区间的奇偶性会发生变化，其实就是区间异或 $1$。

因为为 $b$ 只有 $01$，所以异或等价于交换 $01$ 数量。

不难发现，答案就是区间 $1$ 的历史出现次数。

向量：

$$\begin{bmatrix}a\\b\\h\end{bmatrix}$$

$a$ 是 $1$ 的出现次数，$b$ 是 $0$ 的出现次数，$h$ 是 $1$ 的历史出现次数。

我们希望：

$$T\begin{bmatrix}a\\b\\h\end{bmatrix}=
\begin{bmatrix}b\\a\\h\end{bmatrix}
$$

不难发现：

$$T=
\begin{bmatrix}0&1&0\\1&0&0\\0&0&1\end{bmatrix}
$$

我们希望：

$$T\begin{bmatrix}a\\b\\h\end{bmatrix}=
\begin{bmatrix}a\\b\\h+a\end{bmatrix}
$$

不难发现：

$$T=
\begin{bmatrix}1&0&0\\0&1&0\\1&0&1\end{bmatrix}
$$

不化简已能通过此题，但无法通过加强版，化简比较麻烦。

可以先写成这样：

```cpp
mat operator * (const mat &o){
		mat res;
		res.x11=x11*o.x11+x12*o.x21+x13*o.x31;
		res.x12=x11*o.x12+x12*o.x22+x13*o.x32;
		res.x13=x11*o.x13+x12*o.x23+x13*o.x33;
		
		res.x21=x21*o.x11+x22*o.x21+x23*o.x31;
		res.x22=x21*o.x12+x22*o.x22+x23*o.x32;
		res.x23=x21*o.x13+x22*o.x23+x23*o.x33;
		
		res.x31=x31*o.x11+x32*o.x21+x33*o.x31;
		res.x32=x31*o.x12+x32*o.x22+x33*o.x32;
		res.x33=x31*o.x13+x32*o.x23+x33*o.x33;
		return res;
	}
```

然后找常量化简。

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define rd read()
#define int long long
using namespace std;
int n,m,p[N],a[N],ans[N],t,l,r,op,las[N];
vector<pair<int,int> >q[N]; 
stack<int>s;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
		x=x*10+ch-'0',ch=getchar();
	return x*f;
}
struct ver{
	int x11,x21,x31;
	ver operator + (const ver &o){return {x11+o.x11,x21+o.x21,x31+o.x31};}
}tr[N<<2];
struct mat{
	int x11,x12;
	int x21,x22;
	int x31,x32;
	mat operator * (const mat &o){
		mat res;
		res.x11=x11*o.x11+x12*o.x21;
		res.x12=x11*o.x12+x12*o.x22;
		
		res.x21=x21*o.x11+x22*o.x21;
		res.x22=x21*o.x12+x22*o.x22;
		
		res.x31=x31*o.x11+x32*o.x21+o.x31;
		res.x32=x31*o.x12+x32*o.x22+o.x32;
		return res;
	}
	ver operator * (const ver &o){return {x11*o.x11+x12*o.x21,x21*o.x11+x22*o.x21,x31*o.x11+x32*o.x21+o.x31};}
}tag[N<<2];
inline void pushup(int k){tr[k]=tr[k<<1]+tr[k<<1|1];}
inline void build(int k,int l,int r){
	tag[k]={1,0,0,1,0,0};
	if(l==r){return tr[k].x21=1,void();}
	int mid=l+r>>1;
	build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	pushup(k);
}
inline void add(int k,mat v){
	tag[k]=v*tag[k];
	tr[k]=v*tr[k];
}
inline void pushdown(int k){
	add(k<<1,tag[k]);
	add(k<<1|1,tag[k]);
	tag[k]={1,0,0,1,0,0};
}
inline void modify(int k,int l,int r,int x,int y,mat v){
	if(x<=l&&r<=y){return add(k,v),void();}
	int mid=l+r>>1;
	pushdown(k);
	if(x<=mid) modify(k<<1,l,mid,x,y,v);
	if(y>mid) modify(k<<1|1,mid+1,r,x,y,v);
	pushup(k);
}
inline ver query(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y){return tr[k];}
	int mid=l+r>>1;
	ver res={0,0,0};
	pushdown(k);
	if(x<=mid) res=res+query(k<<1,l,mid,x,y);
	if(y>mid) res=res+query(k<<1|1,mid+1,r,x,y);
	return res;
}
signed main(){
	n=rd;
	build(1,1,n);
	for(int i=1;i<=n;i++) a[i]=rd;
	m=rd;
	for(int i=1;i<=m;i++) l=rd,r=rd,q[r].push_back({i,l});
	for(int i=1;i<=n;i++){
		modify(1,1,n,las[a[i]]+1,i,{0,1,1,0,0,0});modify(1,1,n,1,n,{1,0,0,1,1,0});
		las[a[i]]=i;
		for(auto [id,l]:q[i]) ans[id]=query(1,1,n,l,i).x31;
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
	return 0;
}	
```

---

## 作者：M1saka16I72 (赞：1)

## 前言

线段树维护矩阵又是哪个星球的科技啊。

[更可爱的阅读体验](https://misaka16172.github.io/solution-p10822.html)

## 思路

考虑把询问离线按右端点排序之后扫描线。

记录每个数 $i$ 上次出现的位置 $lst_i$，每次加入一个新数 $a_r$ 对于 $l\in [1,lst_{a_r}]$ 的区间 $[l,r]$ 是没有贡献的，而对于 $l\in (lst_{a_r},r]$ 的区间，出现不同数字的奇偶性会翻转。

我们考虑用线段树维护一个 01 串 $b$，每次遍历到右端点 $r$ 时，$b_l$ 的意义是区间 $[l,r]$ 内出现的不同数字个数是否为奇数。于是问题就转化成了对每个询问 $[l,r]$，求 $b_i(i\in [l,r])$ 的历史和，线段树需要支持的操作则是区间翻转、区间求历史和。

直接打标记非常不好维护，考虑直接无脑使用线段树维护矩阵。设一段区间 $[l,r]$ 内，$\sum_{i=l}^r b_i=x$，历史和为 $h$，当前时间（即遍历到的右端点 $r$）为 $t$，$y=h-tx$（使用这个值的原因是随着 $t$ 的增大，如果区间没有被翻转，$y$ 会维持不变），长度 $len=r-l+1$。

在线段树每个节点上维护一个矩阵：

$$\begin{bmatrix} x \\ y\\ len\end{bmatrix}$$

将这段区间进行翻转，相当于 $x\gets len-x,y\gets h+(len-x)-(t+1)(len-x)$。

$$\begin{bmatrix} -1 & 0 & 1 \\ 2t & 1 & -t\\ 0 & 0 & 1\end{bmatrix} \begin{bmatrix} x \\ y\\ len\end{bmatrix}=\begin{bmatrix} len-x \\ y+2tx-t\cdot len\\ len\end{bmatrix}$$

注意这里的 $t$ 是操作前的 $t$（即 $r-1$）。

这样一来，我们每次翻转区间时打标记，给区间乘上左边的矩阵，查询时返回 $x+ty$ 即可。

时间复杂度 $\mathcal{O}(n\log n+q\log q)$，带一个矩阵乘法的 $3^2$ 常数。

## 代码

这题比较卡空间，矩阵需要用 vector 或者模板类实现才不会 MLE。我这里使用了模板类，缺点是模板类没办法使用变量作为模板参数，不过这题因为矩阵大小都是定值所以不受影响。

```cpp
constexpr int N = 5e5+5;

template<int X,int Y>
struct mat{
	ll a[X][Y];
	mat(){}
	mat(int val){
		for(int y=0;y<Y;y++){
			for(int x=0;x<X;x++)	a[x][y] = val;
		}
	}
	mat(vector<vector<ll>> _a){
		for(int y=0;y<Y;y++){
			for(int x=0;x<X;x++)	a[x][y] = _a[x][y];
		}
	}
	template<int _X,int _Y>
	inline bool operator ==(const mat<_X,_Y> &m)const{
		if(X!=_X || Y!=_Y)	return 0;
		for(int y=0;y<Y;y++){
			for(int x=0;x<X;x++)	if(a[x][y]!=m.a[x][y])	return 0;
		}
		return 1;
	}
	template<int _X,int _Y>
	inline bool operator !=(const mat<_X,_Y> &m)const{return !(*this==m);}
	template<int _X,int _Y>
	inline mat<_X,Y> operator *(const mat<_X,_Y> &m)const{
		mat<_X,Y> res;
		for(int y=0;y<Y;y++){
			for(int x=0;x<_X;x++){
				res.a[x][y] = 0;
				for(int i=0;i<X;i++)	res.a[x][y]+=m.a[x][i]*a[i][y];
			}
		}
		return res;
	}
	inline mat<X,Y> operator +(const mat<X,Y> &m)const{
		mat<X,Y> res;
		for(int y=0;y<Y;y++){
			for(int x=0;x<X;x++)	res.a[x][y] = a[x][y]+m.a[x][y];
		}
		return res;
	}
	template<int x,int y>
	inline ll get(){return a[x-1][y-1];}
	template<int x,int y>
	inline void upd(ll v){a[x-1][y-1] = v;}
};

const mat<3,3> de = mat<3,3>({{1,0,0},{0,1,0},{0,0,1}});

int n,a[N];

struct node{
	mat<1,3> v;
	mat<3,3> t;
};

struct SGT{
	node tr[N<<2];
	inline void up(int p){tr[p].v = tr[p<<1].v+tr[p<<1|1].v;}
	inline void down(int p){
		if(tr[p].t!=de){
			tr[p<<1].t = tr[p].t*tr[p<<1].t,tr[p<<1|1].t = tr[p].t*tr[p<<1|1].t;
			tr[p<<1].v = tr[p].t*tr[p<<1].v,tr[p<<1|1].v = tr[p].t*tr[p<<1|1].v;
			tr[p].t = de;
		}
	}
	void build(int l,int r,int p){
		tr[p].t = de;
		if(l==r)	tr[p].v = mat<1,3>({{0,0,1}});
		else{
			int mid = (l+r)>>1;
			build(l,mid,p<<1),build(mid+1,r,p<<1|1);
			up(p);
		}
	}
	void mul(int l,int r,int nl,int nr,int p,mat<3,3> v){
		if(nl^nr)	down(p);
		if(nl>=l && nr<=r){
			tr[p].v = v*tr[p].v;
			if(nl^nr)	tr[p].t = v*tr[p].t;
		}
		else{
			int mid = (nl+nr)>>1;
			if(mid>=l)	mul(l,r,nl,mid,p<<1,v);
			if(mid+1<=r)	mul(l,r,mid+1,nr,p<<1|1,v);
			up(p);
		}
	}
	ll query(int l,int r,int nl,int nr,int p,int t){
		if(nl^nr)	down(p);
		if(nl>=l && nr<=r)	return tr[p].v.get<1,1>()*t+tr[p].v.get<1,2>();
		else{
			int mid = (nl+nr)>>1;
			ll res = 0;
			if(mid>=l)	res+=query(l,r,nl,mid,p<<1,t);
			if(mid+1<=r)	res+=query(l,r,mid+1,nr,p<<1|1,t);
			return res;	
		}
	}
}sgt;

struct Query{
	int l,r,id;
	inline bool operator <(const Query &q)const{return r<q.r;}
}Q[N];

int q,lst[N];
ll ans[N];

void solve(){
    read(n);
    for(int i=1;i<=n;i++)	read(a[i]);
    read(q);
	for(int i=1;i<=q;i++)	read(Q[i].l,Q[i].r),Q[i].id = i;
	sort(Q+1,Q+1+q);
	int p = 1;
	sgt.build(1,n,1);
	for(int r=1;r<=n;r++){
		mat<3,3> d = mat<3,3>({{-1,2*(r-1),0},{0,1,0},{1,-(r-1),1}});
		sgt.mul(lst[a[r]]+1,r,1,n,1,d);
		lst[a[r]] = r;
		while(p<=q && Q[p].r==r){
			ans[Q[p].id] = sgt.query(Q[p].l,r,1,n,1,r);
			p++;
		}
	}
	for(int i=1;i<=q;i++)	cout<<ans[i]<<"\n";
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

[双倍经验。](https://www.luogu.com.cn/problem/P9990)

没有修改，考虑离线扫描线。

对于每个位置 $l$，维护 $[l, r]$ 中出现过的数的奇偶性，每次 $r \to r + 1$ 时，对于 $[pre_{a_{r + 1}} + 1, r + 1]$ 范围内的 $l$ 的奇偶性会发生变化；其中 $pre_x$ 表示上一个 $x$ 的位置。

对于询问 $[l, r]$，相当于扫到 $r$ 时，求 $[l, r]$ 的区间历史和。

则我们要支持区间异或 $1$，查询区间历史和；我们考虑对于一个区间，维护 $0, 1$ 的数量 $s_0, s_1$，和区间异或的懒标记 $tag$，以及这个区间的历史和 $hs$。

但是这还是不太够，还需要维护这个区间在操作序列中没有被反转了几次与被反转几次 $t_0, t_1$。

那么下传的时候，有：

$$hs \gets hs + t_{fa, 0} s_1 + t_{fa, 1} s_0$$

$$t_0 \gets t_0 + t_{fa, tag}$$

$$t_1 \gets t_1 + t_{fa, tag \oplus 1}$$

即看当前这个节点是处于翻转状态还是非翻转状态的。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define mkp(x, y) make_pair(x, y)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int uint;
bool Begin;
const int N = 1e6 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct Node{
	int l, r;
	ll s0, s1, t0, t1;
	ll sum;
	bool tag;
}X[N << 2];
int n, m, l, r;
int a[N], pre[N];
ll ans[N];
vector<pair<int, int>> Q[N];
inline void pushup(int k){
	X[k].s0 = X[k << 1].s0 + X[k << 1 | 1].s0;
	X[k].s1 = X[k << 1].s1 + X[k << 1 | 1].s1; 
}
inline void add(int k, ll t0, ll t1){
	X[k].sum += 1ll * X[k].s1 * t0 + 1ll * X[k].s0 * t1;
	if(X[k].tag){
		X[k].t0 += t1;
		X[k].t1 += t0;
	} 
	else{
		X[k].t0 += t0;
		X[k].t1 += t1;
	}
}
inline void rev(int k){
	swap(X[k].s0, X[k].s1);
	X[k].tag ^= 1;
}
inline void push_down(int k){
	if(X[k].t0 || X[k].t1){
		add(k << 1, X[k].t0, X[k].t1);
		add(k << 1 | 1, X[k].t0, X[k].t1);
		X[k].t0 = X[k].t1 = 0;
	}
	if(X[k].tag){
		rev(k << 1);
		rev(k << 1 | 1);
		X[k].tag = 0;
	}
}
inline void build(int k, int l, int r){
	X[k].l = l, X[k].r = r;
	if(l == r){
		X[k].s0 = 1;
		return ;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
inline void update(int k, int l, int r){
	if(X[k].l == l && r == X[k].r){
		rev(k);
		return ;
	}
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  update(k << 1, l, r);
	else if(l > mid)
	  update(k << 1 | 1, l, r);
	else{
		update(k << 1, l, mid);
		update(k << 1 | 1, mid + 1, r);
	}
	pushup(k);
}
inline ll query(int k, int l, int r){
	if(X[k].l == l && r == X[k].r)
	  return X[k].sum;
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  return query(k << 1, l, r);
	else if(l > mid)
	  return query(k << 1 | 1, l, r);
	else
	  return query(k << 1, l, mid) + query(k << 1 | 1, mid + 1, r);
}
bool End;
int main(){
	n = read();
	for(int i = 1; i <= n; ++i)
	  a[i] = read();
	build(1, 1, n);
	m = read();
	for(int i = 1; i <= m; ++i){
		l = read(), r = read();
		Q[r].push_back({l, i});
	}
	for(int i = 1; i <= n; ++i){
		update(1, pre[a[i]] + 1, i);
		add(1, 1, 0);
		for(auto t : Q[i])
		  ans[t.se] = query(1, t.fi, i);
		pre[a[i]] = i;
	}
	for(int i = 1; i <= m; ++i){
		write(ans[i]);
		putchar('\n');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：zhangjiting (赞：0)

考虑扫描线。

令 $lst_{a_i}$ 表示上一个 $a_i$ 出现的位置。

那加入 $a_i$ 时会使 $[l,i]$ 的颜色数 $+1$，也就是奇偶性发生变化，其中 $l \in (lst_{a_i},i]$。

我们需要可以维护区间异或和查询历史版本和的线段树，可以用矩阵，也可以更简单地用打两个标记的方法维护，更新和的时候需要加上两个标记分别乘上对应的出现次数的和。

代码：


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug(x) cerr<<#x<<':'<<x<<endl
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e6+5;
int n,m;
int a[N],tmp[N],lst[N],ans[N];
vector<int> p[N];
struct que{
    int l,r,id;
}q[N];
#define ls p<<1
#define rs p<<1|1
struct node{
    int len;
    int sum,cnt;
    int tag,tag0,tag1;
}tree[N<<2];
void add1(int p){
    tree[p].tag^=1;
    swap(tree[p].tag0,tree[p].tag1);
    tree[p].cnt=tree[p].len-tree[p].cnt;
}
void add2(int p,int tag0,int tag1){
    tree[p].sum+=tree[p].cnt*tag1+(tree[p].len-tree[p].cnt)*tag0;
    tree[p].tag0+=tag0,tree[p].tag1+=tag1;
}
void push_up(int p){
    tree[p].sum=tree[ls].sum+tree[rs].sum;
    tree[p].cnt=tree[ls].cnt+tree[rs].cnt;
}
void push_down(int p){
    if(tree[p].tag) add1(ls),add1(rs),tree[p].tag=0;
    if(tree[p].tag0||tree[p].tag1){
        add2(ls,tree[p].tag0,tree[p].tag1);
        add2(rs,tree[p].tag0,tree[p].tag1);
        tree[p].tag0=tree[p].tag1=0;
    }
}
void build(int p,int l,int r){
    tree[p].len=r-l+1;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(ls,l,mid),build(rs,mid+1,r);
}
void change(int p,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr) return add1(p);
    push_down(p);int mid=(l+r)>>1;
    if(ql<=mid) change(ls,l,mid,ql,qr);
    if(qr>mid) change(rs,mid+1,r,ql,qr);
    push_up(p);
}
int ask(int p,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr) return tree[p].sum;
    push_down(p);int mid=(l+r)>>1,res=0;
    if(ql<=mid) res+=ask(ls,l,mid,ql,qr);
    if(qr>mid) res+=ask(rs,mid+1,r,ql,qr);
    return res;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    IOS;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],lst[i]=tmp[a[i]],tmp[a[i]]=i;
    cin>>m;
    for(int i=1;i<=m;i++) cin>>q[i].l>>q[i].r,q[i].id=i,p[q[i].r].push_back(i);
    build(1,1,n);
    for(int i=1;i<=n;i++){
        change(1,1,n,lst[i]+1,i),add2(1,0,1);
        for(int x:p[i]) ans[q[x].id]=ask(1,1,n,q[x].l,i);
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
    return 0;
}
```

---

## 作者：Amadeus004 (赞：0)

## Step 0 题意
> 给定一个长为 $n$ 的序列 $a_n$，静态查询区间 $[l,r]$ 内满足颜色种类数为奇数的子区间个数。
## Step 1 分析
扫描线是显然的，把区间挂在右端点上处理。
每次将右端点向右推，在已知 $1\sim i$ 的情况下就可以直接查询 $[l,i]$ 的信息，子区间的信息等价于查询历史版本和。

接下来思考怎么处理。

记 $a_i$ 前一次出现的位置为 $pre_i$，若不存在则 $pre_i=0$。新加入一个数 $a_i$ 时，序列中多出了 $i$ 个以 $i$ 为右端点的区间，$a_i$ 对这些区间产生贡献当且仅当这些区间的左端点 $>pre_i$。

答案的贡献与种类数的奇偶性相关，令线段树维护一个辅助数组 $b$，$b$ 中的数均为 $0/1$。

当前扫到 $i$ 时，将 $[pre_i+1,i]$ 内的 $0/1$ 翻转。$b_j$ 为 $1$ 表示区间 $[j,i]$ 符合要求，统计区间 $[l,i]$ 内 $1$ 的个数即可知道所有以 $i$ 为右端点的满足要求区间个数。

## Step 2 维护
按照历史和的惯例，我们维护一个有关信息的交换半群 $(\mathcal{D},+)$ 和 有关标记的半群 $(\mathcal{M},*)$，满足 $\mathcal{D}\times\mathcal{M}\rightarrow\mathcal{D}$，$\times$ 对 $(\mathcal{D},+)$ 具有分配率。这里 $\mathcal{D}=(ans,sum,len)$，表示区间历史和，区间和，区间长度。$\mathcal{M}=(tag,upd_0,upd_1)$，表示区间是否被翻转，区间未翻转的状态数，区间翻转的状态数。

对于 $\mathcal{D}+\mathcal{D}\rightarrow\mathcal{D}$，有 $(\mathcal{D1}_{ans}+\mathcal{D2}_{ans},\mathcal{D1}_{s}+\mathcal{D2}_s,\mathcal{D1}_{len}+\mathcal{D2}_{len})\rightarrow\mathcal{D}$

对于 $\mathcal{M}*\mathcal{M}\rightarrow\mathcal{M}$，有 $(\mathcal{M1}_{tag}\otimes\mathcal{M2}_{tag},\mathcal{M1}_{upd_0}+\mathcal{M2}_{upd_{\mathcal{M1}_{tag}}},\mathcal{M1}_{upd_1}+\mathcal{M2}_{upd_{\mathcal{M1}_{tag}\otimes 1}})\rightarrow\mathcal{M}$

其中 $\otimes$ 表示异或。

对于$\mathcal{D}\times\mathcal{M}\rightarrow\mathcal{D}$，有 $(\mathcal{D}_{ans}+\mathcal{D}_s*\mathcal{M}_{upd_0}+(\mathcal{D}_{len}-\mathcal{D}_s)*\mathcal{M}_{upd_1},\mathcal{D}_s*(\mathcal{M}_{tag}\otimes1)+(len-\mathcal{D}_s)*\mathcal{M}_{tag},len)\rightarrow\mathcal{D}$

似乎没有写成矩阵的必要？推起来还是很方便的，且矩阵中有许多无用转移，在 [	
P9990 [Ynoi Easy Round 2023] TEST_90](https://www.luogu.com.cn/problem/P9990) 会被卡常。

## Step 3 Code
```cpp
#include<bits/stdc++.h>
#define ll long long
inline ll read(){
	ll tmp=1,f=0;
	char a;
	while(!isdigit(a=getchar()))tmp=a=='-'?-1:tmp;
	do{f=(f<<3)+(f<<1)+(a^48);}while(isdigit(a=getchar()));
	return tmp*f;
}
inline void write(ll x){
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
namespace solve{
	const int N=1e6+5;
	int n,m,a[N],pre[N],pos[N];
	ll ans[N];
	struct SegmentTree{
		struct Tag{
			ll tag,upd[2];
			inline Tag operator*(const Tag &x)const{return {tag^x.tag,upd[0]+x.upd[tag],upd[1]+x.upd[tag^1]};}
		}M[N<<2];
		struct node{
			ll ans,s,len;
			inline node operator+(const node &x)const{return {ans+x.ans,s+x.s,len+x.len};}
			inline node operator*(const Tag &x)const{return {ans+s*x.upd[0]+(len-s)*x.upd[1],x.tag?len-s:s,len};}
		}D[N<<2];
		#define ls(p) p<<1
		#define rs(p) p<<1|1
		inline void pushup(int p){D[p]=D[ls(p)]+D[rs(p)];}
		inline void pushdown(int p){
			D[ls(p)]=D[ls(p)]*M[p],D[rs(p)]=D[rs(p)]*M[p];
			M[ls(p)]=M[ls(p)]*M[p],M[rs(p)]=M[rs(p)]*M[p];
			M[p]={0,0,0};
		}
		inline void build(int p,int l,int r){
			if(l==r)return D[p]={0,0,1},M[p]={0,0,0},void();
			int mid=l+r>>1;
			build(ls(p),l,mid),build(rs(p),mid+1,r);
			pushup(p);
		}
		inline void modify(int p,int l,int r,int L,int R){
			pushdown(p);
			if(L<=l and r<=R)return D[p]=D[p]*SegmentTree::Tag({1,0,0}),M[p]=M[p]*SegmentTree::Tag({1,0,0}),void();
			int mid=l+r>>1;
			pushdown(p);
			if(L<=mid)modify(ls(p),l,mid,L,R);
			if(R>mid)modify(rs(p),mid+1,r,L,R);
			pushup(p);
		}
		inline ll query(int p,int l,int r,int L,int R){
			pushdown(p);
			if(L<=l and r<=R)return D[p].ans;
			int mid=l+r>>1;
			pushdown(p);
			return R<=mid?query(ls(p),l,mid,L,R):L>mid?query(rs(p),mid+1,r,L,R):query(ls(p),l,mid,L,R)+query(rs(p),mid+1,r,L,R);
		}
	}T;
	std::vector<std::pair<int,int> >G[N];
	void main(){
		n=read();
		for(int i=1;i<=n;i++)pre[i]=pos[a[i]=read()],pos[a[i]]=i;
		m=read();
		for(int i=1;i<=m;i++){
			int l=read(),r=read();
			G[r].push_back({l,i});
		}
		T.build(1,1,n);
		for(int i=1;i<=n;i++){
			T.modify(1,1,n,pre[i]+1,i);
			T.D[1]=T.D[1]*SegmentTree::Tag({0,1,0}),T.M[1]=T.M[1]*SegmentTree::Tag({0,1,0});
			for(int j=0;j<G[i].size();j++)ans[G[i][j].second]=T.query(1,1,n,G[i][j].first,i);
		}
		for(int i=1;i<=m;i++)write(ans[i]),putchar('\n');
		return;
	}
};
int main(){
	solve::main();
	return 0;
}
```

---

## 作者：harmis_yz (赞：0)

题解摘自[做题记录](https://www.luogu.com.cn/article/u60fmw50)。

## 分析

考虑扫描线。对于 $r$ 移动到 $r+1$，记 $pre_i$ 为最大的 $j(j<i)$，使得 $a_j=a_i$。那么对于 $[pre_r+1,r]$ 的所有 $l$，其区间出现过的数的个数都会较 $[l,r-1]$ 多 $1$。因为这题只考虑奇偶性，所以可以看作其奇偶性异或了 $1$。那么答案就是奇偶性为 $1$ 的子区间的数量。

像这种题，我们可以将子区间 $[l,r']$ 看作区间 $[l,r]$ 的前缀。只要我们扫描 $r$，我们就能在每个 $l$ 上面维护所有 $r\ge l$ 的前缀的答案了。记 $f_l$ 为 $l$ 的答案。则 $[l,r]$ 的所有子区间的答案就是 $\sum\limits_{l'=l}^{r} f_{l'}$。

那么这题就很简单了吧。不难发现，只有 $[pre_r+1,r]$ 的前缀较 $r-1$ 异或了 $1$，其余的相当于是复制一遍。因为要查询的是所有历史的前缀的和，我们记为 $sum$。又记 $cnt_0$ 为前缀为 $0$ 的数量，$cnt_1$ 同理。那么 $[pre_r+1,r]$ 的 $cnt_0$ 与 $cnt_1$ 将会交换。然后 $sum$ 增加量就为 $[1,r]$ 的 $cnt_1$。

这里有个 trick，就是像这种维护区间历史和的问题，通常可以用矩阵运算。形式化的，我们有：

对于异或操作：$\begin{bmatrix}cnt_0 &cnt_1&sum\end{bmatrix} \times \begin{bmatrix}0 & 1 & 0 \\ 1 & 0 & 0\\0 & 0 & 1\end{bmatrix}$。

对于更新历史和操作：$\begin{bmatrix}cnt_0 &cnt_1&sum\end{bmatrix} \times \begin{bmatrix}1 & 0 & 0 \\ 0 & 1 & 1\\0 & 0 & 1\end{bmatrix}$。

使用线段树与矩阵可以做到 $O(a^3n \log n)$ 的复杂度。

然后你会发现这题矩阵乘法过不了（如果不会卡常）。考虑正常懒标记。记 $tag1$ 表示区间翻转懒标记，$tag2$ 表示区间更新历史和的懒标记。实际上就是 CF997E 的做法，直接写上去就行了。时间复杂度 $O(n\log n)$。

注意懒标记下传的先后顺序，不然调很久。

## 代码

```cpp
il void up(int u){
	tr[u].cnt0=tr[ls(u)].cnt0+tr[rs(u)].cnt0;
	tr[u].cnt1=tr[ls(u)].cnt1+tr[rs(u)].cnt1;	
	tr[u].sum=tr[ls(u)].sum+tr[rs(u)].sum;
	return ;
}
il void down(int u){
	if(tr[u].tag1){
		swap(tr[ls(u)].cnt0,tr[ls(u)].cnt1);
		swap(tr[ls(u)].tag20,tr[ls(u)].tag21);
		swap(tr[rs(u)].cnt0,tr[rs(u)].cnt1);
		swap(tr[rs(u)].tag20,tr[rs(u)].tag21);
		tr[ls(u)].tag1^=1,tr[rs(u)].tag1^=1;
		tr[u].tag1=0;
	}	
	tr[ls(u)].sum+=tr[u].tag21*tr[ls(u)].cnt1+tr[u].tag20*tr[ls(u)].cnt0;
	tr[rs(u)].sum+=tr[u].tag21*tr[rs(u)].cnt1+tr[u].tag20*tr[rs(u)].cnt0;
	tr[ls(u)].tag21+=tr[u].tag21;
	tr[rs(u)].tag21+=tr[u].tag21;
	tr[ls(u)].tag20+=tr[u].tag20;
	tr[rs(u)].tag20+=tr[u].tag20;	
	tr[u].tag21=tr[u].tag20=0;	
	return ;
}
il void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r;
	if(l==r) return tr[u].cnt0=1,void(0);
	int mid=l+r>>1;
	build(ls(u),l,mid),build(rs(u),mid+1,r);
	up(u);
	return ;
}
il void modify1(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r){
		swap(tr[u].cnt0,tr[u].cnt1);
		swap(tr[u].tag20,tr[u].tag21);
		tr[u].tag1^=1;
		return ;
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify1(ls(u),l,r);
	if(mid< r) modify1(rs(u),l,r);
	up(u);
	return ;
}
il void modify2(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r){
		tr[u].sum+=tr[u].cnt1;
		tr[u].tag21+=1;
		return ;
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify2(ls(u),l,r);
	if(mid< r) modify2(rs(u),l,r);
	up(u);
	return ;
}
il int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r) return tr[u].sum;
	int mid=tr[u].l+tr[u].r>>1,sum=0;
	down(u);
	if(l<=mid) sum+=query(ls(u),l,r);
	if(mid< r) sum+=query(rs(u),l,r);
	up(u);
	return sum;
}

il void solve(){
	n=rd;
	for(re int i=1;i<=n;++i) a[i]=rd;
	m=rd;
	for(re int i=1;i<=m;++i){
		int l=rd,r=rd;
		v[r].push_back({l,i});
	}
	build(1,1,n);
	for(re int i=1;i<=n;++i){
		pre[i]=lst[a[i]],lst[a[i]]=i;
		modify1(1,pre[i]+1,i);
		modify2(1,1,i);
		for(auto x:v[i]) ans[x.y]=query(1,x.x,i);
	}
	for(re int i=1;i<=m;++i) printf("%lld\n",ans[i]);
    return ;
}
```

---

## 作者：xiezheyuan (赞：0)

双倍经验：P9990 [Ynoi Easy Round 2023] TEST_90。

给管理员的提示：这个矩阵乘法策略虽然比较奇怪，但是根据实践，确实是正确的。

## 思路

首先考虑离线下来，我们一个一个往后面添加 $a_i$，然后把所有询问按照右端点挂在 $a$ 的下标上。

我们维护一个序列，第 $j$ 项表示区间 $[j,i]$ 的颜色数除以 $2$ 的余数，则每次添加一个数，记 $a_i$ 上一次出现的位置为 $L$，则 $j\in [L+1,i]$ 都会对序列造成影响，其余的不会影响，并且这些影响是取反。取反可以看成是进行了一个函数 $f(x)=-x+1$。

对于询问，我们可以看成是询问一个历史和。可以用矩阵 + 线段树维护。我的转移矩阵好像和其他题解不一样。

具体来说，对于第 $i$ 个叶子结点，我们维护一个向量：

$$
\begin{bmatrix}
f& g& 1
\end{bmatrix}
$$

其中 $f$ 表示除以二的余数，$g$ 表示历史和。

则取反可以看成乘上一个转移矩阵：

$$
\begin{bmatrix}
-1&0&1\\
0&1&0\\
1&0&1
\end{bmatrix}
$$

然后我们需要更新全局历史和，相当于乘上一个转移矩阵：

$$
\begin{bmatrix}
1&1&1\\
0&1&0\\
0&0&1
\end{bmatrix}
$$

时间复杂度 $O(m\log n)$。

## 代码

[贡献一组大样例，可用于本地测试速度](https://xiezheyuan.lanzouh.com/igjZm2786d3a)。

```cpp
#include <bits/stdc++.h>
#define rint register int
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
using namespace std;

const int N = 1e6 + 5;
int n, q;

template<class T>
inline void read(T& x){
	x=0; rint f=1; char ch = getchar();
	while(ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-48; ch=getchar();}
	x = x*f;
}
template<class T>
void write(T x){
    static int sta[65];
    int top = 0;
    do {sta[top++] = x % 10; x /= 10; } while(x);
    while(top) putchar(sta[--top] + 48);
}

struct matrix{
    int n, m;
    long long a00, a01, a02, a10, a11, a12, a20, a21, a22;
    void init(int N, int M){
        n = N, m = M;
        a00 = a01 = a02 = a10 = a11 = a12 = a20 = a21 = a22 = 0;
    }
    void mkunit(int N, int M){
        n = N, m = M;
        a00 = a11 = a22 = 1;
        a01 = a02 = a10 = a12 = a20 = a21 = 0;
    }
};

matrix operator+ (matrix a, matrix b){
    a.a00 += b.a00; a.a01 += b.a01; a.a02 += b.a02;
    return a;
}

matrix simple_mul(matrix a, matrix b){
    matrix ans; ans.init(a.n, b.m);
    ans.a00 = a.a00 * b.a00 + a.a02 * b.a20;
    ans.a01 = a.a00 * b.a01 + a.a01 * b.a11 + a.a02 * b.a21;
    ans.a02 = a.a02 * b.a22;
    return ans;
}

matrix operator*(matrix a, matrix b){
    matrix ans; ans.init(a.n, b.m);
    ans.a00 = a.a00 * b.a00;
    ans.a01 = a.a00 * b.a01 + a.a01 * b.a11;
    ans.a11 = a.a11 * b.a11;
    ans.a20 = a.a20 * b.a00 + a.a22 * b.a20;
    ans.a21 = a.a20 * b.a01 + a.a21 * b.a11 + a.a22 * b.a21;
    ans.a22 = a.a22 * b.a22;
    return ans;
}

matrix t[N << 2], tag[N << 2];
bool havetag[N << 2];

void build(int i, int l, int r){
    tag[i].mkunit(3, 3);
    if(l == r){
        t[i].init(1, 3); t[i].a02 = 1;
        return;
    }
    build(ls, l, mid); build(rs, mid + 1, r);
    t[i] = t[ls] + t[rs];
}

void pushdown(int i){
    if(!havetag[i]) return;
    if(havetag[ls]) tag[ls] = tag[ls] * tag[i];
    else tag[ls] = tag[i];
    if(havetag[rs]) tag[rs] = tag[rs] * tag[i];
    else tag[rs] = tag[i];
    havetag[ls] = havetag[rs] = 1;
    t[ls] = simple_mul(t[ls], tag[i]); t[rs] = simple_mul(t[rs], tag[i]);
    havetag[i] = 0;
}

void update(int ql, int qr, matrix v, int i, int l, int r){
    if(ql <= l && r <= qr){
        if(havetag[i]) tag[i] = tag[i] * v;
        else tag[i] = v;
        t[i] = simple_mul(t[i], v);
        havetag[i] = 1;
        return;
    }
    pushdown(i);
    if(ql <= mid) update(ql, qr, v, ls, l, mid);
    if(mid < qr) update(ql, qr, v, rs, mid + 1, r);
    t[i] = t[ls] + t[rs];
}

long long query(int ql, int qr, int i, int l, int r){
    if(ql <= l && r <= qr) return t[i].a01;
    pushdown(i);
    if(ql <= mid && qr > mid) return query(ql, qr, ls, l, mid) + query(ql, qr, rs, mid + 1, r);
    if(ql <= mid) return query(ql, qr, ls, l, mid);
    return query(ql, qr, rs, mid + 1, r);
}

vector<pair<int,int> > vp[N];
int a[N], last[N], ytxy[N];
long long answer[N];

signed main(){
    read(n);
    build(1, 1, n);
    for(rint i=1;i<=n;i++){
        read(a[i]);
        ytxy[i] = last[a[i]];
        last[a[i]] = i;
    }
    read(q);
    for(rint i=1;i<=q;i++){
        int l, r;
        read(l); read(r);
        vp[r].push_back({l, i});
    }
    matrix rever; rever.init(3, 3);
    rever.a00 = -1; rever.a11 = rever.a20 = rever.a22 = 1;
    matrix uni; uni.mkunit(3, 3);
    uni.a01 = 1;
    for(rint i=1;i<=n;i++){
        update(ytxy[i] + 1, i, rever, 1, 1, n);
        update(1, n, uni, 1, 1, n);
        for(int j=0;j<vp[i].size();j++){
            int l=vp[i][j].first,id=vp[i][j].second;
            answer[id] = query(l, i, 1, 1, n);
        }
    }
    for(rint i=1;i<=q;i++) write(answer[i]), putchar('\n');
    return 0;
}

// Written by xiezheyuan
```

---

