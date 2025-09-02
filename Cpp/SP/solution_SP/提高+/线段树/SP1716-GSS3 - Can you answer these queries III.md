# GSS3 - Can you answer these queries III

## 题目描述

You are given a sequence A of N (N <= 50000) integers between -10000 and 10000. On this sequence you have to apply M (M <= 50000) operations:   
 modify the i-th element in the sequence or for given x y print max{Ai + Ai+1 + .. + Aj | x<=i<=j<=y }.

## 样例 #1

### 输入

```
4
1 2 3 4
4
1 1 3
0 3 -3
1 2 4
1 3 3```

### 输出

```
6
4
-3```

# 题解

## 作者：kradcigam (赞：60)

# 前言
首先说一下题意。就是每次给出 $x$ 和 $y$ 两个数，求 $x$ 到 $y$ 这个区间的最大子段和。
# 正文
## 分析
首先我们看这个数据范围，我们显然是要用线段树来做这道题。

我们考虑如何 `pushup`。

### `pushup` 的操作

![360截图17001020107151123.png](https://i.loli.net/2020/03/03/luVJw8qUL6gb1WT.png)

#### 区间最大子段和

我们考虑一个区间的最大子段。

我们分 $3$ 种情况讨论：

##### 1. 有可能是左边部分的最大子段和

![asdsajdfhiujhkja.png](https://i.loli.net/2020/03/03/MbQhGW7ruBJPYXk.png)

答案就是左边部分的最大子段和。

##### 2. 也有可能右边部分的最大子段和

![asdasajdfhiujhkja.png](https://i.loli.net/2020/03/03/EO9GtVwImgJ163u.png)

答案就是右边部分的最大子段和。

##### 3. 最大最大和有可能跨越了中间

![aasdasajdfhiujhkja.png](https://i.loli.net/2020/03/03/fpndbVqamoOIXtK.png)

答案就是左边部分右端点往左的最大子段和 $+$ 左端点往右的最大子段和。

#### 发现

所以，我们需要对于所有节点，还要维护它们以左端点往右的最大子段和、右端点往左的最大子段和。

我们再考虑如何维护一个区间以左端点往右的最大子段和、右端点往左的最大子段和。

#### 以左端点往右的最大子段和

我们先考虑以左端点往右的最大子段和。

我们分 $2$ 种情况讨论：

##### 1. 不跨越中间

![aaasajdfhiujhkja.png](https://i.loli.net/2020/03/03/b2BmrAucJ8jLdER.png)

答案就是左部分的以左端点往右的最大子段和。

##### 2. 跨越中间

![asdssssajdfhiujhkja.png](https://i.loli.net/2020/03/03/8TJ4RkfYzWdVSPX.png)

答案就是左部分的和 $+$ 右部分以左端点往右的最大子段和。

#### 以右端点往左的最大子段和

我们先考虑以右端点往左的最大子段和。

我们分 $2$ 种情况讨论：

##### 1. 不跨越中间

![kja.png](https://i.loli.net/2020/03/03/6Nv3yeZRlqLfo2C.png)

答案就是右部分的以左端点往右的最大子段和。

##### 2. 跨越中间

![df.png](https://i.loli.net/2020/03/03/ZuSvq8rM3mKwUsG.png)

答案就是右部分的和 $+$ 左部分以右端点往左的最大子段和。

#### 发现

我们发现我们还需要维护区间和，这个问题很简单，不再讲解了。

所以我们现在总共要维护 $4$ 个东西。

分别是：

$lans$、$rans$、$ans$、$sum$。

#### 边界情况——即整个区间是一个点
我们可以发现：

$lans$、$rans$、$ans$、$sum$ 都为这个点的值。
#### 代码

```cpp
Tree pushup(Tree L,Tree R){
	Tree z;
	z.sum=L.sum+R.sum;//和
	z.l=max(L.l,L.sum+R.l);//2种情况
	z.r=max(R.r,R.sum+L.r);//2种情况
	z.ans=max(max(L.ans,R.ans),L.r+R.l);//3种情况
	return z;
}
```
这里我写了一个带返回值的函数，就是为了下面方便啦。

### 查询

上文已经讲解了最大子段和的 $3$ 中情况，已经知道最大子段和跟 $4$ 个东西有关。

所以我们要定义一个返回值为 $Tree$ 的函数。

那么现在，关键就在于合并区间，那么现在之前的`pushup`就可以被调用了。

```cpp
Tree query(int x,int y,int num,int l,int r){
	if(x<=l&&r<=y)return t[num];
	int mid=(l+r)>>1;
	if(y<=mid)return query(x,y,ls,l,mid);//右区间和查询区间没有交，答案当然在左区间
	if(mid<x)return query(x,y,rs,mid+1,r);//左区间和查询区间没有交，答案当然在右区间
	return pushup(query(x,mid,ls,l,mid),query(mid+1,y,rs,mid+1,r));//是不是很简洁？
}
```

## 代码

我们已经把这道题的重点都搞清楚了，接下来就可以放代码了，至于单点修改不会的请自行去[学习](https://oi-wiki.org/ds/seg/)。

```cpp
#include <bits/stdc++.h>
#define ls num<<1
#define rs num<<1|1
using namespace std;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
template<typename T>void write(T x){
	if(x<0)putchar('-'),x*=-1;
	if(x>9)write(x/10);
	putchar(x%10+48);
}
template<typename T>void writen(T x){
	write(x);
	puts("");
}
const int MAXN=5e4+10;
struct Tree{
	int sum,l,r,ans;//维护的4个量
}t[MAXN*4];
int a[MAXN],f,x,y;
Tree pushup(Tree L,Tree R){
	Tree z;
	z.sum=L.sum+R.sum;//和
	z.l=max(L.l,L.sum+R.l);//2种情况
	z.r=max(R.r,R.sum+L.r);//2种情况
	z.ans=max(max(L.ans,R.ans),L.r+R.l);//3种情况
	return z;
}
void build(int l,int r,int num){//建树
	if(l==r){
		t[num].sum=a[l];
		t[num].l=a[l];
		t[num].r=a[l];
		t[num].ans=a[l];//边界初始化
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls);
	build(mid+1,r,rs);
	t[num]=pushup(t[ls],t[rs]);//pushup
}
void change(int l,int r,int num){//单点修改
	if(l==r){
		t[num].sum=y;
		t[num].l=y;
		t[num].r=y;
		t[num].ans=y;//边界初始化
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)change(l,mid,ls);
	else change(mid+1,r,rs);
	t[num]=pushup(t[ls],t[rs]);
}
Tree query(int x,int y,int num,int l,int r){
	if(x<=l&&r<=y)return t[num];
	int mid=(l+r)>>1;
	if(y<=mid)return query(x,y,ls,l,mid);//右区间和查询区间没有交，答案当然在左区间
	if(mid<x)return query(x,y,rs,mid+1,r);//左区间和查询区间没有交，答案当然在右区间
	return pushup(query(x,mid,ls,l,mid),query(mid+1,y,rs,mid+1,r));//是不是很简洁？
}
int main(){
	int n,T;
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	build(1,n,1);
	read(T);
	while(T--){
		read(f);read(x);read(y);
		if(f==0)change(1,n,1);
		else writen(query(x,y,1,1,n).ans);
	}
	return 0;
}
```

---

## 作者：Siyuan (赞：52)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[SPOJ 1716](https://www.spoj.com/problems/GSS3/)

维护一个长度为 $n$ 的序列 $A$，进行 $m$ 次询问或操作：

- `0 x y`：将 $A_x$ 单调修改为 $y$
- `1 x y`：求出 $\max\{\sum_{k=i}^j A_k\}(x\le i\le j\le y)$。

数据范围：$N,M\le 5\times 10^4$，$|A_i|\le 10^4$

------

## Solution

首先分析询问的本质：求出区间最大子段和！

很显然我们可以使用线段树维护序列，本题的难点主要在如何进行上传操作，即$\texttt{push up}$。

将子树 $l$ 和 $r$ 的节点信息上传到子树 $rt$ 时，对于 $rt$ 维护的序列中，和最大的子段有两种情况：

1. 子段不经过中点，那么 $rt$ 的答案为 $l$ 和 $r$ 的答案的最大值。
2. 子段经过了中点。这种情况比较复杂，因为我们无法知道子树的答案所对应的序列。这也是本题的难点所在。

**接下来对第 $2$ 种情况进行重点分析**：

我们记 $res$ 为区间最长子段和，$sum$ 为区间和，$prel$ 和 $prer$ 分别表示从区间左端点和右端点开始的最大子段和。

考虑这些信息如何上传：$sum$ 可以直接上传，$prel[rt]=\max(prel[l],sum[l]+prel[r])$（$prer$ 同理），$res[rt]=\max(res[l],res[r],prer[l]+prel[r])$

**时间复杂度**：$O(m\log n)$

------

## Code

```cpp
#include <cstdio>
#include <algorithm>
#define lson rt<<1
#define rson rt<<1|1
using std::max;
const int N=5e4+5;
int n,m,a[N];

struct Tree {
    int prel,prer,res,sum;
}seg[N<<2];

void pushup(int rt) {
    Tree L=seg[lson],R=seg[rson];
    seg[rt].sum=L.sum+R.sum;
    seg[rt].prel=max(L.prel,L.sum+R.prel);
    seg[rt].prer=max(R.prer,R.sum+L.prer);
    seg[rt].res=max(L.prer+R.prel,max(L.res,R.res));
}
void build(int rt,int l,int r) {
    if(l==r) {
        seg[rt].prel=seg[rt].prer=seg[rt].res=seg[rt].sum=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(rt);
}
void modify(int x,int rt,int l,int r,int val) {
    if(l==r) {
        seg[rt].prel=seg[rt].prer=seg[rt].res=seg[rt].sum=val;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) modify(x,lson,l,mid,val);
    else modify(x,rson,mid+1,r,val);
    pushup(rt);
}
Tree query(int x,int y,int rt,int l,int r) {
    if(x<=l&&r<=y) return seg[rt];
    int mid=(l+r)>>1;
    if(y<=mid) return query(x,y,lson,l,mid);
    if(mid<x) return query(x,y,rson,mid+1,r);
    Tree L=query(x,mid,lson,l,mid),R=query(mid+1,y,rson,mid+1,r),res;
    res.sum=L.sum+R.sum;
    res.prel=max(L.prel,L.sum+R.prel);
    res.prer=max(R.prer,R.sum+L.prer);
    res.res=max(L.prer+R.prel,max(L.res,R.res));
    return res;
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    build(1,1,n);
    for(scanf("%d",&m);m--;) {
        int opt,x,y;
        scanf("%d%d%d",&opt,&x,&y);
        if(opt) printf("%d\n",query(x,y,1,1,n).res);
        else modify(x,1,1,n,y);
    }
    return 0;
}
```

---

## 作者：i207M (赞：17)

## 题目总结

带修改区间最长连续子序列和

## 数据范围

N<=50000

## 解题思路

### 法一

当然，此题可以参考GSS 1，利用线段树维护前缀最大和，后缀最大和，区间最大和，搞一搞就好；

### 法二

很骚气的办法，用线段树维护矩阵连乘积；

考虑没有修改、查询全局最大子段和时候的方法；

![](https://cdn.luogu.com.cn/upload/pic/20401.png )

假如可修改，~~那么这就是动态DP了~~

接下来我们重新定义矩阵乘法；

![](https://cdn.luogu.com.cn/upload/pic/20403.png )

![](https://cdn.luogu.com.cn/upload/pic/20402.png )

```cpp
		memset(res.m, 0xc0, sizeof (res.m));
        for (ri i = 1; i <= sz; i++) {
            for (ri k = 1; k <= sz; k++) {
                for (ri j = 1; j <= sz; j++)
                    res.m[i][j] = max(res.m[i][j], m[i][k] + x.m[k][j]);
            }
        }
```

相比于普通的乘法，我们把对应元素相乘改为相加，统计答案时，把相加改为取最大值；

手玩一下发现这是正确的；

然后用线段树维护一个区间的矩阵乘法；

## 易错误区

统计答案时选好位置；

不要忘了初始化sz；

## 代码展示

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define ull unsigned long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
#define int ll
il char gc() {
    static const int BS = 1 << 22;
    static unsigned char buf[BS], *st, *ed;
    if (st == ed) ed = buf + fread(st = buf, 1, BS, stdin);
    return st == ed ? EOF : *st++;
}
#define gc getchar
template<class T>void in(T &x)
{
    x = 0; bool f = 0; char c = gc();
    while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
    while ('0' <= c && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
    if (f) x = -x;
}
#undef gc
void out(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) out(x / 10);
    putchar(x % 10 + '0');
}
#define N 50010<<2
#define Maxsz 5
struct Mat {
    int sz;
    int m[Maxsz][Maxsz];
    il void clear() {mem0(m);}
    Mat () {sz = 0; clear();}
    Mat operator*(const Mat &x)const {
        Mat res; res.sz = sz;
        memset(res.m, 0xc0, sizeof (res.m));
        for (ri i = 1; i <= sz; i++) {
            for (ri k = 1; k <= sz; k++) {
                for (ri j = 1; j <= sz; j++)
                    res.m[i][j] = max(res.m[i][j], m[i][k] + x.m[k][j]);
            }
        }
        return res;
    }
    void operator*=(const Mat &x) {
        *this = (*this) * x;
    }
    void print() {
        for (ri i = 1; i <= sz; i++) {
            for (ri j = 1; j <= sz; j++)
                printf("%lld ", m[i][j]);
            puts("");
        }
    }
    il int ans() {
        return max(m[1][2], m[3][2]);
    }
};
#define ls (x<<1)
#define rs (x<<1|1)
#define gm int mid=(l+r)>>1
#define now tre[x]
Mat tre[N];
Mat bs;
int n, m, a[N], rt;
il void up(int x) {
    tre[x] = tre[ls] * tre[rs];
}
void build(int x, int l, int r) {
    now.sz = 3;
    if (l == r) {
        bs.m[1][1] = bs.m[1][2] = bs.m[3][1] = bs.m[3][2] = a[l];
        memcpy(now.m, bs.m, sizeof (now.m));
        //now.print();
        return;
    }
    gm;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    up(x);
    //printf("B %lld %lld %lld\n",l,r,now.ans());
}
void update(int x, int l, int r, int &t, int &k) {
    if (l == r) {
        bs.m[1][1] = bs.m[1][2] = bs.m[3][1] = bs.m[3][2] = k;
        memcpy(now.m, bs.m, sizeof (now.m));
        return;
    }
    gm;
    if (t <= mid) update(ls, l, mid, t, k);
    else update(rs, mid + 1, r, t, k);
    up(x);
}
Mat query(int x, int l, int r, int &ql, int &qr) {
    if (ql <= l && r <= qr) {
        return tre[x];
    }
    gm;
    Mat ret;
    if (ql <= mid && mid < qr) ret = query(ls, l, mid, ql, qr) * query(rs, mid + 1, r, ql, qr);
    else if (ql <= mid) ret = query(ls, l, mid, ql, qr);
    else ret = query(rs, mid + 1, r, ql, qr);
    //printf("Q %lld %lld %lld\n",l,r,ret.ans());
    return ret;
}
void print() {
    for (ri i = 1; i <= n; ++i) {
        printf("%lld\n", query(rt, 1, n, i, i).ans());
    }
}
signed main() {
    bs.m[1][3] = bs.m[2][1] = bs.m[2][3] = -inf;
    bs.m[2][2] = bs.m[3][3] = 0;
    in(n);
    for (ri i = 1; i <= n; ++i) in(a[i]);
    build(rt = 1, 1, n);
    in(m);
    int op, x, y;
    while (m--) {
        //print();
        in(op), in(x), in(y);
        if (op == 0) {
            update(rt, 1, n, x, y);
        }
        else {
            printf("%lld\n", query(rt, 1, n, x, y).ans());
        }
    }
    return 0;
}
```

---

## 作者：Ajwallet (赞：16)

看到$dalao$们的题解都用了结构体，身为蒟蒻的我瑟瑟发抖，就打了个用两个变量来回答询问的，望管理给过

# 具体思路
维护我就不说了，完全跟$dalao$们的一样，但是在询问部分，如何不用结构体达到统计答案的目的呢？可以用两个变量$ans$和$pre$，一个表示最终答案，一个表示之前答案，就可以模拟结构体达到求解的目的了，这种方法的优势就是。。。 ~~看起来爽~~
# 代码
```cpp
#include<cstdio>
#include<algorithm>
#define ri register int
#define lson k<<1
#define rson k<<1|1
using namespace std;int sum[200001],lmax[200001],rmax[200001],n;
int dat[200001],a[50001],m,x,y,z,ans,pre;
inline void wh(ri k)//维护,Wei Hu
{
    sum[k]=sum[lson]+sum[rson];
    lmax[k]=max(lmax[lson],sum[lson]+lmax[rson]);
    rmax[k]=max(rmax[rson],sum[rson]+rmax[lson]);
    dat[k]=max(max(dat[lson],dat[rson]),rmax[lson]+lmax[rson]);
    return;
}
inline void build(ri k,ri l,ri r)//建树
{
    if(l==r)
    {
        sum[k]=a[l];lmax[k]=a[l];rmax[k]=a[l];dat[k]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(lson,l,mid);build(rson,mid+1,r);
    wh(k);
    return;
}
inline void change(ri k,ri l,ri r,ri x,ri d)//我这里没有多开两个数组而是多开了两个参数，因为听说这样比较快。。。
{
    if(l==r)
    {
        if(l==x){sum[k]=d;lmax[k]=d;rmax[k]=d;dat[k]=d;}//达到要修改的点则修改
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) change(lson,l,mid,x,d);else change(rson,mid+1,r,x,d);//修改
    wh(k);//维护
    return;
}
inline void ask(ri k,ri l,ri r,ri ql,ri qr)//询问
{
    if(ql<=l&&qr>=r)
    {
        ans=max(ans,dat[k]);//计算
        ans=max(ans,pre+lmax[k]);
        pre=max(rmax[k],pre+sum[k]);//维护pre
        return;
    }
    int mid=(l+r)>>1;
    int ans=0;
    if(ql<=mid) ask(lson,l,mid,ql,qr);
    if(qr>mid) ask(rson,mid+1,r,ql,qr);//继续向下
}
signed main()
{
    scanf("%d",&n);
    for(ri i=1;i<=n;i++) scanf("%d",a+i);
    build(1,1,n);
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d%d%d",&x,&y,&z);
        if(x==1){ans=-1147483645;pre=-1147483645;ask(1,1,n,y,z);printf("%d\n",ans);}//注意这里的ans和pre不能开太小，要不然出现负数的时候可能会WA
        else change(1,1,n,y,z);//修改
    }
}
```

---

## 作者：Karry5307 (赞：13)

### 题意
给一个序列，支持修改和查询最大子段和。
### 题解
[博客还是要安利一发的](https://karry5307.github.io)

可以看一下[这个题](https://www.luogu.org/problemnew/show/SP1043)以及[本蒟蒻的题解](https://www.luogu.org/blog/Karry5307/solution-sp1043)，这里重点说一下修改。

像GSS1一样，照样维护4个信息，在修改的时候将点的一些信息修改成这个值，再递归更新就好了。

最后说一句，写**结构体式线段树**会使这一题极其好写……
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=2e5+51;
struct SegmentTree{
    ll l,r,prefix,suffix,sum,maxn;  
};
SegmentTree tree[MAXN];
ll cnt,qcnt,l,r,x,val,op;
ll num[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void update(ll node)
{
    ll res;
    tree[node].sum=tree[node<<1].sum+tree[(node<<1)|1].sum;
    tree[node].maxn=max(tree[node<<1].maxn,tree[(node<<1)|1].maxn);
    res=tree[node<<1].suffix+tree[(node<<1)|1].prefix;
    tree[node].maxn=max(tree[node].maxn,res);
    res=tree[node<<1].sum+tree[(node<<1)|1].prefix;
    tree[node].prefix=max(tree[node<<1].prefix,res);
    res=tree[node<<1].suffix+tree[(node<<1)|1].sum;
    tree[node].suffix=max(tree[(node<<1)|1].suffix,res);
}
inline SegmentTree merge(SegmentTree x,SegmentTree y)
{
    SegmentTree res;
    res.sum=x.sum+y.sum;
    res.maxn=max(x.maxn,max(y.maxn,x.suffix+y.prefix));
    res.prefix=max(x.prefix,x.sum+y.prefix);
    res.suffix=max(y.suffix,x.suffix+y.sum);
    return res;
}
inline void create(ll l,ll r,ll node)
{
    tree[node].l=l,tree[node].r=r;
    if(l==r)
    {
        tree[node].sum=tree[node].maxn=num[l];
        tree[node].prefix=tree[node].suffix=num[l];
        return;
    }
    ll mid=(l+r)>>1;
    create(l,mid,node<<1);
    create(mid+1,r,(node<<1)|1);
    update(node);
}
inline void changePoint(ll pos,ll val,ll node)
{
    if(tree[node].l==tree[node].r)
    {
        tree[node].sum=tree[node].maxn=val;
        tree[node].prefix=tree[node].suffix=val;
        return;
    }
    ll mid=(tree[node].l+tree[node].r)>>1;
    if(pos<=mid)
    {
        changePoint(pos,val,node<<1);
    }
    else
    {
        changePoint(pos,val,(node<<1)|1);
    }
    update(node);
}
inline SegmentTree queryMax(ll l,ll r,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        return tree[node];
    }
    ll mid=(tree[node].l+tree[node].r)>>1;
    SegmentTree res;
    if(l>mid)
    {
        return queryMax(l,r,(node<<1)|1);
    }
    if(r<=mid)
    {
        return queryMax(l,r,node<<1);
    }
    else
    {
        SegmentTree x=queryMax(l,r,node<<1),y=queryMax(l,r,(node<<1)|1);
        return merge(x,y);
    }
}
int main()
{
    cnt=read();
    for(register int i=1;i<=cnt;i++)
    {
        num[i]=read();
    }
    create(1,cnt,1);
    qcnt=read();
    for(register int i=0;i<qcnt;i++)
    {
    	op=read();
    	if(op==0)
    	{
    		x=read(),val=read();
    		changePoint(x,val,1);
        }
        else
        {
            l=read(),r=read();
            printf("%d\n",queryMax(l,r,1).maxn);
        }
    }
}
```

---

## 作者：qiianr (赞：11)

# [SP1716 GSS3 - Can you answer these queries III](https://www.luogu.org/problemnew/show/SP1716)
思路：构建一个线段树结构体，除了区间端点外，再维护四个信息：**区间和sum,区间最大连续子段和dat,紧靠左端的最大连续子段和lmax，紧靠右端的最大连续子段和rmax**.

线段树整体框架不变，只需在build和change里多维护几个信息就好

如下(本题最重要的代码核心+思路要点)
```cpp
t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
t[p].lmax=max(t[p<<1].lmax,t[p<<1].sum+t[p<<1|1].lmax);
t[p].rmax=max(t[p<<1|1].rmax,t[p<<1|1].sum+t[p<<1].rmax);
t[p].dat=max(t[p<<1].dat,max(t[p<<1|1].dat,t[p<<1].rmax+t[p<<1|1].lmax));
```
每个区间的最大子段和可能是左右两个小区间的最大子段和，也可能是左区间的紧靠右端的最大连续子段和+右区间紧靠左端的最大连续子段和

所以我们同时维护区间和，及区间紧靠左右最大子段和，进而维护每个区间的最大连续子段和，最后询问的时候也要遵循这个方法求最大子段和

## ~~上菜~~√上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=500005;
int n,m,h;
 
struct node{
	int l,r,sum,dat,lmax,rmax;
}t[maxn*4];
 
void build(int p,int l,int r){
    t[p].l=l;t[p].r=r;
    if(l==r){
    	scanf("%d",&h);//省时间又省空间
    	t[p].dat=t[p].lmax=t[p].rmax=t[p].sum=h;
        return;
    }
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
    t[p].lmax=max(t[p<<1].lmax,t[p<<1].sum+t[p<<1|1].lmax);
    t[p].rmax=max(t[p<<1|1].rmax,t[p<<1|1].sum+t[p<<1].rmax);
    t[p].dat=max(t[p<<1].dat,max(t[p<<1|1].dat,t[p<<1].rmax+t[p<<1|1].lmax));
}

void change(int p,int x,int y){//x为要改的坐标，y为要改成的数
	if(t[p].l==x&&t[p].r==x){
    	t[p].dat=t[p].lmax=t[p].rmax=t[p].sum=y;
		return;
	}
	int mid=(t[p].l+t[p].r)>>1;
	if(mid<x) change(p<<1|1,x,y);
	else change(p<<1,x,y);
    t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
    t[p].lmax=max(t[p<<1].lmax,t[p<<1].sum+t[p<<1|1].lmax);
    t[p].rmax=max(t[p<<1|1].rmax,t[p<<1|1].sum+t[p<<1].rmax);
    t[p].dat=max(t[p<<1].dat,max(t[p<<1|1].dat,t[p<<1].rmax+t[p<<1|1].lmax));
}

node ask(int p,int l,int r){//[l,r]询问的区间
	if(t[p].l>=l&&t[p].r<=r){
		return t[p];
	}
	int mid=(t[p].l+t[p].r)>>1;
	if(mid<l)return ask(p<<1|1,l,r);
	else if(mid>=r)return ask(p<<1,l,r);
	else{
		node a,b;
		a=ask(p<<1,l,r);
		b=ask(p<<1|1,l,r);
		node ttt;
		ttt.dat=max(max(a.dat,b.dat),a.rmax+b.lmax);
		ttt.lmax=max(a.lmax,a.sum+b.lmax);
		ttt.rmax=max(b.rmax,a.rmax+b.sum);
		return ttt;
	}
}

int main(){
	scanf("%d",&n);
	build(1,1,n);
	scanf("%d",&m);
	int a,x,y;
	while(m--){
		scanf("%d%d%d",&a,&x,&y);
		if(a==0){
			change(1,x,y);
		}else{
			if(x>y) swap(x,y);
			node ans=ask(1,x,y);
			printf("%d\n",ans.dat);
		}
	}
	return 0;
}
```

---

## 作者：niiick (赞：11)

###这么经典的区间维护怎么少得了splay

lx[]数组维护区间内从以区间**最左端元素为第一个数**的最大连续子段和

rx[]数组维护区间内从以区间**最右端元素为最后一个数**的最大连续子段和

mx[]数组维护区间内最大连续子段和
那么维护的代码如下

```
void update(int p)//这里是splay写法,线段树lc=p<<1,rc=p<<1|1
{
    int lc=ch[p][0],rc=ch[p][1];
    size[p]=size[lc]+size[rc]+1;
    sum[p]=sum[lc]+sum[rc]+val[p];
    lx[p]=max(lx[lc],sum[lc]+lx[rc]+val[p]);
    rx[p]=max(rx[rc],sum[rc]+rx[lc]+val[p]);
    mx[p]=max(max(mx[lc],mx[rc]),rx[lc]+lx[rc]+val[p]);
}
```
lx[p]=max(lx[左子树], sum[左子树]+lx[右子树]+val[p]);

rx[p]=max(rx[右子树], sum[右子树]+rx[左子树]+val[p]);

mx[p]=max(mx[左子树], mx[右子树], rx[左子树]+lx[右子树]+val[p]);
***********************
完整代码

```
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
using namespace std;

int read()
{
    int f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

const int maxn=100010;
int n,m;
int rt;
int val[maxn],sum[maxn];
int ch[maxn][2],fa[maxn];
int size[maxn];
int lx[maxn],rx[maxn],mx[maxn];

void update(int p)
{
    int lc=ch[p][0],rc=ch[p][1];
    size[p]=size[lc]+size[rc]+1;
    sum[p]=sum[lc]+sum[rc]+val[p];
    lx[p]=max(lx[lc],sum[lc]+lx[rc]+val[p]);
    rx[p]=max(rx[rc],sum[rc]+rx[lc]+val[p]);
    mx[p]=max(max(mx[lc],mx[rc]),rx[lc]+lx[rc]+val[p]);
}

void build(int p,int ll,int rr)
{
    if(ll>rr) return;
    int mid=ll+rr>>1;
    fa[mid]=p; size[mid]=1;
    ch[p][mid>p]=mid;
    if(ll==rr) 
    { 
        lx[mid]=rx[mid]=max(val[mid],0); //注意要判断负数
        sum[mid]=mx[mid]=val[mid];  return;
    }
    build(mid,ll,mid-1); build(mid,mid+1,rr);
    update(mid);
}

void rotate(int &p,int x)
{
    int y=fa[x],z=fa[y];
    int d=(ch[y][0]==x);
    if(y==p) p=x;
    else if(ch[z][0]==y) ch[z][0]=x;
    else ch[z][1]=x;
    fa[y]=x; fa[ch[x][d]]=y; fa[x]=z;
    ch[y][d^1]=ch[x][d]; ch[x][d]=y;
    update(y); update(x);
}


void splay(int &p,int x)
{
    while(x!=p)
    {
        int y=fa[x],z=fa[y];
        if(y!=p)
        {
            if((ch[z][0]==y)^(ch[y][0]==x))rotate(p,x);
            else rotate(p,y);
        }
        rotate(p,x);
    }
}

int find(int p,int k) 
{ 
    int ss=size[ch[p][0]]; 
    if(k==ss+1) return p;    
    else if(k<=ss) return find(ch[p][0],k);
    else return find(ch[p][1],k-ss-1);  
}

void change(int k,int w)
{
    int x=find(rt,k); splay(rt,x);
    int y=find(rt,k+2); splay(ch[rt][1],y);
    int z=ch[y][0];//由于伸展出的区间只有一个点，所以直接修改
    val[z]=mx[z]=sum[z]=w;
    lx[z]=rx[z]=max(w,0);
    update(y); update(x);
}

void query(int ll,int rr)//直接伸展出对应区间，输出其mx
{
    int x=find(rt,ll); splay(rt,x);
    int y=find(rt,rr+2); splay(ch[rt][1],y);
    printf("%d\n",mx[ch[y][0]]);
}

int main()
{
    n=read();
    mx[0]=val[1]=val[n+2]=-1e9;//哨兵结点的值记得初始化-inf
    for(int i=2;i<=n+1;++i)
    val[i]=read();
    
    rt=n+3>>1;
    build(rt,1,n+2);
    
    m=read();
    while(m--)
    {
        int k=read(),x=read(),y=read();
        if(k==0) change(x,y);
        else if(k==1) query(x,y);
    }
    return 0;
}
```

---

## 作者：zmxqs (赞：6)


题意：
* 1、单点修改

* 2、区间查询最大连续子段和

Step1：建树

为了方便，我们可以用结构体来保存树
```cpp
struct node {
	int Ml , Mr;
	int Data , Sum;
	int Left ,Right ;
};
```
我们需要保存一个量，分别是区间的 $Left$ ，区间的 $Right$

保存从最左开始连续的最大和（方便更改）

保存从最右开始连续的最大和（同上）

$sum$ 保存区间和（查询速度快啊）

$Data$ 最终答案



建树也是板子,不会的童鞋可以左转线段树模板

```cpp
void build(int x , int Left , int Right) {
	t[x].Left = Left ;
	t[x].Right = Right ;
	if(Left == Right) {
		t[x].Data = a[Left];
		t[x].Ml = a[Left];
		t[x].Mr = a[Left];
		t[x].Sum = a[Left];//叶子节点就保存
		return;
	}
	int mid = (Left + Right) >> 1;
	build(x << 1 , Left , mid);
	build( x << 1 | 1 , mid + 1 ,Right);
	calc(x);//先不要急，往后看
	return;
}
```

Step2: 修改
```cpp
void change (int x, int u, int v) {
	if (t[x].Left == t[x].Right) {
		t[x].Sum = v;
		t[x].Ml = v;
		t[x].Mr = v;
		t[x].Data = v;//如果是叶子节点就更新
		
		return;
	}
	
	int mid = (t[x].Left + t[x].Right) / 2;
	
	if (mid >= u) change (x * 2, u, v);//从左子树进行修改
	else change (x * 2 + 1, u, v);//右子树
	
	calc (x);//往后看
}
```

Tips：

有童鞋可能会问了，这个calc是什么玩意
这个函数是进行更新当前节点的
```cpp
void calc (int x) {
	t[x].Sum = t[x * 2].Sum + t[x * 2 + 1].Sum;//和为两区间的和
	t[x].Ml = max(t[x * 2].Ml, t[x * 2].Sum + t[x * 2 + 1].Ml);//Ml的话取要么为左区间的Ml,要么是左区间的和+右区间的和
	t[x].Mr = max(t[x * 2 + 1].Mr, t[x * 2 + 1].Sum + t[x * 2].Mr);
   //Mr同理，在这里不再介绍了
	t[x].Data = max(max(t[x * 2].Data, t[x * 2 + 1].Data), t[x * 2].Mr + t[x * 2 + 1].Ml);//Data保存结果，要么是两个子节点的data，要么是中间一块的和
}
```
为什么要把更新打包成一个函数？

这样对于调试程序来说，是很有帮助的

如果重复写的话需要检查N遍，这样的话只要一遍
~~（是不是很方便）~~

Step3：查找

有人就会问了查找怎么玩？
与修改类似，从$root$(1)开始遍历，直到找到这个区间为止
要注意的是，一个区间的答案可能包含在几个小区间里，所以不能if完了就else，还要判断
```cpp
node ask(int x ,int l , int r) {
	if(l <= t[x].Left && r >= t[x].Right) {
		return t[x];
	}
	int mid = (t[x].Left + t[x].Right) / 2;
	node A , B ,C;
	A.Data = INT_MIN / 2;
	A.Ml = INT_MIN / 2;
	A.Mr = INT_MIN / 2;
	A.Sum = INT_MIN / 2;

	B.Data = INT_MIN / 2;
	B.Ml = INT_MIN / 2;
	B.Mr = INT_MIN / 2;
	B.Sum = INT_MIN / 2;//改为一个不可能的值，方便计算
	
	C.Sum = 0;
	if(l <= mid) {
		A = ask(x * 2, l , r);
		C.Sum += A.Sum;
	}//注意，就是这里，答案可能在两个区间
	if(r > mid) {
		B = ask(x * 2 + 1 , l , r);
		C.Sum += B.Sum;
	}
	C.Data =max( max(A.Data , B.Data ) , A.Mr + B.Ml);

	C.Ml = max(A.Ml , A.Sum + B.Ml);
	if(l > mid) {
		C.Ml = max(C.Ml , B.Ml);
	}

	C.Mr =max(B.Mr ,B.Sum + A.Mr);

	if(r <= mid) {
		C.Mr =max(C.Mr , A.Mr);
	}
	return C;
}
```
码风可能略丑，不要介意哈

完成了这些，基本可以完工了
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2000010;
struct node {
	int Ml , Mr;
	int Data , Sum;
	int Left ,Right ;
};
int a[MAXN << 2];
node t[MAXN];

void calc (int x) {
	t[x].Sum = t[x << 1].Sum + t[x << 1 | 1].Sum;
	t[x].Ml = max(t[x << 1].Ml, t[x << 1].Sum + t[x << 1 | 1].Ml);
	t[x].Mr = max(t[x << 1 | 1].Mr, t[x << 1 | 1].Sum + t[x << 1].Mr);
	t[x].Data = max(max(t[x << 1].Data, t[x << 1 | 1].Data), t[x << 1].Mr + t[x << 1 | 1].Ml);
}
void build(int x , int Left , int Right) {
	t[x].Left = Left ;
	t[x].Right = Right ;
//	cerr << x << ' ' << Left << ' ' << Right << '\n';
	if(Left == Right) {
		t[x].Data = a[Left];
		t[x].Ml = a[Left];
		t[x].Mr = a[Left];
		t[x].Sum = a[Left];
		return;
	}
	int mid = (Left + Right) >> 1;
	build(x << 1 , Left , mid);
	build( x << 1 | 1 , mid + 1 ,Right);
	calc(x);
	return;
}
node ask(int x ,int l , int r) {
	if(l <= t[x].Left && r >= t[x].Right) {
		return t[x];
	}
	int mid = (t[x].Left + t[x].Right) >> 1;
	node A , B ,C;
	A.Data = INT_MIN / 2;
	A.Ml = INT_MIN / 2;
	A.Mr = INT_MIN / 2;
	A.Sum = INT_MIN / 2;

	B.Data = INT_MIN / 2;
	B.Ml = INT_MIN / 2;
	B.Mr = INT_MIN / 2;
	B.Sum = INT_MIN / 2;
	
	C.Sum = 0;
	if(l <= mid) {
		A = ask(x << 1, l , r);
		C.Sum += A.Sum;
	}
	if(r > mid) {
		B = ask(x << 1 | 1 , l , r);
		C.Sum += B.Sum;
	}
	C.Data =max( max(A.Data , B.Data ) , A.Mr + B.Ml);

	C.Ml = max(A.Ml , A.Sum + B.Ml);
	if(l > mid) {
		C.Ml = max(C.Ml , B.Ml);
	}

	C.Mr =max(B.Mr ,B.Sum + A.Mr);

	if(r <= mid) {
		C.Mr =max(C.Mr , A.Mr);
	}
	return C;
}

void change (int x, int u, int v) {
	if (t[x].Left == t[x].Right) {
		t[x].Sum = v;
		t[x].Ml = v;
		t[x].Mr = v;
		t[x].Data = v;
		
		return;
	}
	
	int mid = (t[x].Left + t[x].Right) / 2;
	
	if (mid >= u) change (x << 1, u, v);
	else change (x << 1 | 1, u, v);
	
	calc (x);
}
int n , q;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	build(1 , 1 , n);
	cin >> q;
//	scanf("%d" , &q);
//	Print(1);
	for(int i = 1; i <= q; ++i) {
		int o , x , y;
		cin >> o >> x >> y;
		if(o == 0) {
			//	a[x] = y;
			change(1 , x, y);
		} else {
			if(x > y) {
				swap(x , y);
			}
			node ans = ask(1 , x , y);
			cout << ans.Data << '\n' ;
		}
	}
	return 0;
}
```
完整代码如上

# 重点来了，记好笔记
Q1、有同学问C++的cin好慢啊
可以这样，在开头加上


ios_base :: sync_with_stdio(false);

cin.tie(0);

分分钟速度就上来了

Tip2：*2可以写为<< 1

/2 = >> 1

*2+1=<< 1 | 1

为什么要占坑说一下这个呢？

这样的话，程序的速度会变得很快

本人第一篇blog，后续会写这篇题解的树状数组做法

$Update1:$删除了一些不必要的注释，增加了一些说明



---

## 作者：流逝丶 (赞：5)

维护最大子段和嘛，要维护这东西我们需要四个东西，

区间和sum，从最左端起的最大连续和ls，从最右端起最大的连续和rs，区间内最

大的连续和mx。

为什么是这四个呢？

我们区间合并的时候，大区间的mx，可能由左或右区间mx更新过

来，可能是左区间rs和右区间ls更新。

对于sum，我们为什么需要？

因为更新新区间的ls可能是原左区间的ls或左区间的sum和右区间的ls

同理更新新区间的rs可能是原右区间的rs或右区间的sum和左区间的rs

对于一个叶子结点，它的sum=ls=rs=mx=val

知道怎么维护了，就开始想change，因为是单点修改，所以直接修改叶子结点，

ask的话我们对于区间分开的话要分开找最后返回。

### [双倍经验](https://www.luogu.org/problem/P4513)

### [升级版](https://www.luogu.org/problem/P2572)

提供一种结构体重载的写法，省了不少码量

```cpp
#include<iostream>
#include<cstdio>
#define lson k<<1,l,mid
#define rson k<<1|1,mid+1,r
#define lso k<<1
#define rso k<<1|1
#define mid ((l+r)>>1)
using namespace std;
const int N=500000;
struct data{
	int ls,rs,mx,sum;
}tr[N<<2];
int n,m;
int a[N+5];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
data operator +(const data &a,const data &b){
	data c;
	c.ls=max(a.ls,a.sum+b.ls);
	c.rs=max(b.rs,b.sum+a.rs);
	c.sum=a.sum+b.sum;
	c.mx=max(a.mx,max(b.mx,a.rs+b.ls));
	return c;
}
void update(int k){
	tr[k]=tr[lso]+tr[rso];
}
void change(int k,int l,int r,int pos,int val){
	if(l==r){
		tr[k].ls=tr[k].rs=tr[k].mx=tr[k].sum=val;
		return;
	}
	if(pos<=mid)change(lson,pos,val);
	else change(rson,pos,val);
	update(k);
}
data ask(int k,int l,int r,int x,int y){
	if(l==x&&r==y)return tr[k];
	if(y<=mid)return ask(lson,x,y);
	else if(x>mid)return ask(rson,x,y);
	else {
		data temp1=ask(lson,x,mid);
		data temp2=ask(rson,mid+1,y);
		return temp1+temp2;
	}
}
void build(int k,int l,int r){
    if(l==r){
		tr[k].sum=tr[k].ls=tr[k].rs=tr[k].mx=a[l];
		return;
	}
    build(lson);build(rson);
    update(k);
}
int main(){
	n=read();
    for(int i=1;i<=n;i++)
       a[i]=read();
    m=read();
    build(1,1,n);
    for(int i=1;i<=m;i++){
        int t,x,y;
        t=read(),x=read(),y=read();
        if(t==1){
            if(x>y)swap(x,y);
            printf("%d\n",ask(1,1,n,x,y).mx);
        }
        if(t==0) 
            change(1,1,n,x,y);
    }
    return 0;
}
```


---

## 作者：azihmst (赞：4)

只写题解不交代码

主要思路

问题在于求最大连续子段和；

在线段树的叶子结点中，最大子段和无非以下几种可能

A:lid的max

B:rid的max

C:位于中间部分；

A和B易于解决，关键是C

我们假设在叶子结点中，从最右一个数开始的最大子段和为rmax，从最左一个数开始的最大子段和为lmax

那么c就等于lmax+ramx；

接下来的问题就是维护lmax和rmax；

以rmax为例

他等于右儿子的ramx与右儿子的sum+左儿子的rmax中的较大值。

那么需要维护的就只有lmax rmax sum max 了

完

求审核通过

---

## 作者：封禁用户 (赞：3)

[个人博客同步](http://www.cinema000.xyz/678.ruby)

这里可用线段树做，对于线段树上的每个结点，除区间端点外，再维护4个信息：区间和$sum$，区间最大连续子段和$data$，紧靠左端点的最大连续子段和$lmax$，紧靠右端点的最大连续子段和$rmax$。

线段树整体框架不变，只需在$build$和$change$函数中从下往上传递信息：

$t[p].sum = t[LEFT(p)].sum + t[RIGHT(p)].sum;$
$t[p].lmax = \max (t[LEFT(p)].lmax,t[LEFT(p)].sum + t[RIGHT(p)].lmax);$
$t[p].rmax = \max (t[RIGHT(p)].rmax,t[RIGHT(p)].sum + t[LEFT(p)].rmax);$
$t[p].data = \max (t[LEFT(p)].data,t[RIGHT(p)].data,t[LEFT(p)].rmax + t[RIGHT(p)].lmax);$
```cpp
#include<cstdio>

const int MAXN = 50000 + 6;
int A[MAXN];

class SegmentTree{
	public:int l,r;
	public:int sum,data,lmax,rmax;
};
SegmentTree t[MAXN * 4];

inline int LEFT(int x){return x << 1;}
inline int RIGHT(int x){return x << 1 | 1;}
inline int MID(int l,int r){return (l + r) >> 1;}
inline int max(int a,int b){return a > b ? a : b;}
inline int max(int a,int b,int c){return max(max(a,b),c);}

void build(int p,int l,int r){
	t[p].l = l;t[p].r = r;
	if(l == r){
		t[p].sum = t[p].data = t[p].lmax = t[p].rmax = A[l];
		return;
	}
	build(LEFT(p),l,MID(l,r));
	build(RIGHT(p),MID(l,r) + 1,r);
	t[p].sum = t[LEFT(p)].sum + t[RIGHT(p)].sum;
	t[p].lmax = max(t[LEFT(p)].lmax,t[LEFT(p)].sum + t[RIGHT(p)].lmax);
	t[p].rmax = max(t[RIGHT(p)].rmax,t[RIGHT(p)].sum + t[LEFT(p)].rmax);
	t[p].data = max(t[LEFT(p)].data,t[RIGHT(p)].data,t[LEFT(p)].rmax + t[RIGHT(p)].lmax);
}

void change(int p,int x,int v){
	if(t[p].l == t[p].r){
		t[p].sum = t[p].data = t[p].lmax = t[p].rmax = v;
		return;
	}
	if(x <= MID(t[p].l,t[p].r)){
		change(LEFT(p),x,v);
	}else{
		change(RIGHT(p),x,v);
	}
	t[p].sum = t[LEFT(p)].sum + t[RIGHT(p)].sum;
	t[p].lmax = max(t[LEFT(p)].lmax,t[LEFT(p)].sum + t[RIGHT(p)].lmax);
	t[p].rmax = max(t[RIGHT(p)].rmax,t[RIGHT(p)].sum + t[LEFT(p)].rmax);
	t[p].data = max(t[LEFT(p)].data,t[RIGHT(p)].data,t[LEFT(p)].rmax + t[RIGHT(p)].lmax);
}

SegmentTree ask(int p,int l,int r){
	if(l <= t[p].l && r >= t[p].r){
		return t[p];
	}
	SegmentTree g,gg;
	if(l > MID(t[p].l,t[p].r)){
		return ask(RIGHT(p),l,r);
	}else if(r <= MID(t[p].l,t[p].r)){
		return gg = ask(LEFT(p),l,r);
	}else{
		g = ask(LEFT(p),l,r);
		gg = ask(RIGHT(p),l,r);
		SegmentTree ans;
		ans.data = max(g.data,gg.data,g.rmax + gg.lmax);
		ans.lmax = max(g.lmax,g.sum + gg.lmax);
		ans.rmax = max(gg.rmax,gg.sum + g.rmax);
		return ans;
	}
}

int main(){
	int n;
	scanf("%d",&n);
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&A[i]);
	}
	
	build(1,1,n);
	
	int q;
	scanf("%d",&q);
	
	while(q--){
		int op,x,y;
		scanf("%d %d %d",&op,&x,&y);
		
		if(op == 0){
			change(1,x,y);
		}else{
			printf("%d\n",ask(1,x,y).data);
		}
	}
	
	return 0;
}
```

---

## 作者：codecode (赞：2)

若 $\LaTeX$ 炸了，可移步[云剪切版](https://www.luogu.com.cn/paste/adgkoh76)或[博客](https://www.luogu.com.cn/blog/codecodeakioi/solution-sp1716)。

#### 题解：

我们需要维护区间的最大子段和。

对于维护这种类型的数据，比较常用的就是线段树。

设区间 $(l,r)$ 的最大子段和为 $\operatorname{data}(l,r)$。

我们称区间内达到最大子段和的子段为最大子段。

将区间 $(l,r)$ 分成 $(l,mid) \cup (mid+1,r)$，那么区间 $(l,r)$ 的最大子段是哪一段呢？

- 完全包含于 $L=(l,mid)$；

- 完全包含于 $R=(mid+1,r)$；

- 区间 $L$ 的后一段与区间 $R$ 的前一段。

若为前两种，可将 $\operatorname{data}L$ 与 $\operatorname{data}R$ 加入候选值。

若为最后一种，我们需要左区间的后缀和与右区间的前缀和最大。不难发现，取到最大值时，必定是区间 $L$ 的最大后缀和与区间 $R$ 的最大前缀和之和。

设区间的最大前缀和 $\operatorname{pre}$ 与区间的最大后缀和 $\operatorname{suf}$。

在这些表示下，我们就能维护最大子段和了

$$\operatorname{data}(l,r)=\max(\operatorname{suf}L+\operatorname{pre}R,\max(\operatorname{data}L,\operatorname{data}R))$$

但是我们还要维护 $\operatorname{pre}$ 与 $\operatorname{suf}$。

对于区间 $(l,r)$，其最大前缀和可能是哪一段呢？ 

- $L$ 的最大前缀和；

- 整个 $L$ 再加上 $R$ 的最大前缀和。

设区间和 $\operatorname{sum}$，那么

$$\operatorname{pre}(l,r)=\max(\operatorname{pre}L,\operatorname{sum}L+\operatorname{pre}R)$$

同理，对于区间 $(l,r)$ 的最大后缀和，可能是

- $R$ 的最大后缀和；

- 整个 $R$ 再加上 $L$ 的最大后缀和。

即

$$\operatorname{suf}(l,r)=\max(\operatorname{suf}R,\operatorname{sum}R+\operatorname{suf}L)$$

最后还剩一个 $\operatorname{sum}$ 需要维护，即是线段树的常规操作了。

回顾一下我们的维护方式：

$$
\begin{aligned}
\operatorname{data}(l,r) & =\max(\operatorname{suf}L+\operatorname{pre}R,\max(\operatorname{data}L,\operatorname{data}R))\\
\operatorname{pre}(l,r) & =\max(\operatorname{pre}L,\operatorname{sum}L+\operatorname{pre}R)\\
\operatorname{suf}(l,r) & =\max(\operatorname{suf}R,\operatorname{sum}R+\operatorname{suf}L)
\end{aligned}
$$

于是可以用线段树 $\Theta((n+q)\log n)$ 完成此题。

代码中用结构体写的线段树。详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=50000+233;
int n,q,a[maxn];
struct Seg{
	int l,r,sum; //区间左右端点，区间和
	int data,pre,suf; //最大子段和，最大前缀和，最大后缀和
}tree[maxn*4];
void pushup(int pos){ //RT的维护
	tree[pos].sum=tree[pos*2].sum+tree[pos*2+1].sum;
	tree[pos].data=max(tree[pos*2].data,tree[pos*2+1].data);
	tree[pos].data=max(tree[pos].data,tree[pos*2].suf+tree[pos*2+1].pre);
	tree[pos].pre=max(tree[pos*2].pre,tree[pos*2].sum+tree[pos*2+1].pre);
	tree[pos].suf=max(tree[pos*2+1].suf,tree[pos*2].suf+tree[pos*2+1].sum);
}
void biuld(int pos,int l,int r){ //标准建树
	if(l==r){
		tree[pos].l=tree[pos].r=l;
		tree[pos].data=tree[pos].pre=tree[pos].suf=tree[pos].sum=a[l];
		return;
	}
	int mid=(l+r)/2;
	biuld(pos*2,l,mid);
	biuld(pos*2+1,mid+1,r);
	tree[pos].l=tree[pos*2].l;
	tree[pos].r=tree[pos*2+1].r;
	pushup(pos);	
}
void update(int pos,int x,int y){ //标准upd
	if(tree[pos].l==tree[pos].r){
		tree[pos].data=tree[pos].pre=tree[pos].suf=tree[pos].sum=y;
		return;
	}
	int mid=(tree[pos].l+tree[pos].r)/2;
	if(x<=mid)update(pos*2,x,y);
	else update(pos*2+1,x,y);
	pushup(pos);
}
Seg query(int pos,int l,int r){
	if(l<=tree[pos].l&&tree[pos].r<=r)return tree[pos];
	int mid=(tree[pos].l+tree[pos].r)/2;
	if(l<=mid&&r>mid){ //将(l,r)拆分成(l,mid)U(mid+1,r)
		Seg resl=query(pos*2,l,r);
		Seg resr=query(pos*2+1,l,r);
		Seg res;
		res.sum=resl.sum+resr.sum;
		res.data=max(resl.data,resr.data);
		res.data=max(res.data,resl.suf+resr.pre);
		res.pre=max(resl.pre,resl.sum+resr.pre);
		res.suf=max(resr.suf,resr.sum+resl.suf);
		return res;
	}
    else{ //若(l,r)没有完全包含pos所在区间，直接递归
        if(l<=mid)return query(pos*2,l,r);
        if(r>mid)return query(pos*2+1,l,r);
    }
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	biuld(1,1,n);
	cin>>q;
	for(int i=1;i<=q;i++){
		int opt,l,r;
		cin>>opt>>l>>r;
		if(opt)cout<<query(1,l,r).data<<endl;
		else update(1,l,r);
	}
	return 0;
}

```


---

## 作者：Genius_Z (赞：2)

题意就是要求区间最大子段和，带修。

维护前缀最大和后缀最大的思路由前几个GSS系列的题继承过来就行了，这里讲一点有意思的东西。

因为最近刚好在学习动态dp，这题正好也算是个典型，就又做了一遍。

动态dp是把正常的状态转移方程转化成矩阵的形式，然后用数据结构维护矩阵的连乘积。当然这里的矩阵乘法不是正常的矩阵乘法，重定义后的矩乘长这个亚子：

```cpp
struct matrix{
    ...
};
matrix operator* (matrix a,matrix b){
    matrix c;
    for(int i...){
        for(int j...){
            for(int k...){
                c[i][j]=max(c[i][j],a[i][k]+b[k][j]);
            }
        }
    }
}
```

也就是把乘变成了加，把加变成了取$max$

最大子段和的状态转移方程大概是这样的：

```cpp
for(int i=1;i<=n;i++){
    tmp=max(tmp+a[i],a[i]);
    ans=max(ans,tmp);
}
```

所以我们构造出的矩阵长这样:

$\left( \begin{matrix} tmp_{i-1}&ans_{i-1}&0\end{matrix} \right)\left( \begin{matrix}a_i&a_i&-inf\\ -inf&0&-inf\\ a_i&a_i&0\end{matrix} \right) = \left( \begin{matrix} tmp_{i}&ans_{i}&0\end{matrix} \right)$

我们只要用线段树维护这个矩阵的连乘积：$\left( \begin{matrix}a_i&a_i&-inf\\ -inf&0&-inf\\ a_i&a_i&0\end{matrix} \right)$

每次修改把四个$a_i$全部改掉，然后$pushup$就好了。

$\Large Code$ :

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#define inl inline
#define re register int
#define fa(x) fa[x]
#define son(x, y) t[x].child[y]
#define ls(x) child[x][0]
#define rs(x) child[x][1]
#define ll long long
const int inf = 0x3f3f3f3f;
#define lowbit(x) ((x) & (-x))
using namespace std;
struct matrix {
	int a[3][3];
	matrix() { a[0][0] = a[0][1] = a[0][2] = a[1][0] = a[1][1] = a[1][2] = a[2][0] = a[2][1] = a[2][2] = -inf; }
	matrix(bool x) { a[0][0] = a[1][1] = a[2][2] = 0, a[0][1] = a[0][2] = a[1][0] = a[1][2] = a[2][0] = a[2][1] = -inf; }
	inl int *operator[](int x) { return a[x]; }
	inl const int *operator[](int x) const { return a[x]; }
	friend matrix operator*(const matrix &a, const matrix &b) {
		matrix c;
		for (re i = 0; i < 3; i++) {
			for (re j = 0; j < 3; j++) {
				for (re k = 0; k < 3; k++) {
					c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
				}
			}
		}
		return c;
	}
	inl int getmax() { return max(a[0][1], a[2][1]); }
}t[200001];
inl void upd(int k) {
	t[k] = t[k << 1] * t[k << 1 | 1];
}
inl void build(int k, int l, int r) {
	if (l == r) return (void)(t[k][0][0] = t[k][0][1] = t[k][2][0] = t[k][2][1] = read<int>(), t[k][1][1] = t[k][2][2] = 0);
	re mid = l + r >> 1;
	build(k << 1, l, mid), build(k << 1 | 1, mid + 1, r);
	upd(k);
}
inl void change(int k, int l, int r, int p, int w) {
	if (l == r)return (void)(t[k][0][0] = t[k][0][1] = t[k][2][0] = t[k][2][1] = w);
	re mid = l + r >> 1;
	if (p <= mid)change(k << 1, l, mid, p, w);
	else change(k << 1 | 1, mid + 1, r, p, w);
	upd(k);
}
inl matrix query(int k, int l, int r, int x, int y) {
	if (l >= x && r <= y)return t[k];
	re mid = l + r >> 1;
	matrix ans = matrix(0);
	if (x <= mid)ans = ans * query(k << 1, l, mid, x, y);
	if (y > mid)ans = ans * query(k << 1 | 1, mid + 1, r, x, y);
	return ans;
}
signed main() {
	re n = read<int>(), m, op, x, y;
	build(1, 1, n);
	m = read<int>();
	while (m--) {
		op = read<int>(), x = read<int>(), y = read<int>();
		if (op) {
			writeln(query(1, 1, n, x, y).getmax());
		}
		else {
			change(1, 1, n, x, y);
		}
	}
}
```



---

## 作者：唔啊唔 (赞：2)

这道题目与[第一问](https://www.luogu.org/problemnew/show/SP1043)其实并无太大差异

仅仅只是加了一个单点修改

详情请看我第一问的题解

[题解 SP1043 【GSS1 - Can you answer these queries I】](https://www.luogu.org/blog/99247/solution-sp1043)

单点修改理解了的都会，就不做解释了

代码还是附上

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[5000000];
struct HZY{
	int l,r;
	int pre,suf,data,sum;
}t[5000000],s;
inline void build(int l,int r,int k){
	t[k].l=l;
	t[k].r=r;
	if(l==r){
		t[k].sum=a[l];
		t[k].pre=a[l];
		t[k].suf=a[l];
		t[k].data=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(l,mid,2*k);
	build(mid+1,r,2*k+1);
	t[k].data=max(t[2*k].data,t[2*k+1].data);
	t[k].data=max(t[k].data,t[2*k].suf+t[2*k+1].pre);
	t[k].pre=max(t[2*k].pre,t[2*k].sum+t[2*k+1].pre);
	t[k].suf=max(t[2*k].suf+t[2*k+1].sum,t[2*k+1].suf);
	t[k].sum=t[2*k].sum+t[2*k+1].sum; 
}
int cnt;
inline void ask(int l,int r,int k){
	if(l<=t[k].l&&r>=t[k].r){
		if(cnt==0){
			cnt=1;
			s=t[k];
		}
		else{
			s.pre=max(s.pre,s.sum+t[k].pre);
			s.sum=s.sum+t[k].sum;
			s.data=max(s.data,t[k].data);
			s.data=max(s.data,s.suf+t[k].pre);
			s.suf=max(t[k].suf,s.suf+t[k].sum);
		}
		return;
	}
	int mid=(t[k].l+t[k].r)/2;
	if(l<=mid) ask(l,r,2*k);
	if(r>mid) ask(l,r,2*k+1);
}
inline void change(int hzy,int lp,int k){
	if(t[k].l==hzy&&t[k].r==hzy){
		t[k].sum=lp;
		t[k].pre=lp;
		t[k].suf=lp;
		t[k].data=lp;
		return;
	}
	int mid=(t[k].l+t[k].r)/2;
	if(hzy<=mid)change(hzy,lp,2*k);
	else{
		change(hzy,lp,2*k+1);
	}
	t[k].data=max(t[2*k].data,t[2*k+1].data);
	t[k].data=max(t[k].data,t[2*k].suf+t[2*k+1].pre);
	t[k].pre=max(t[2*k].pre,t[2*k].sum+t[2*k+1].pre);
	t[k].suf=max(t[2*k].suf+t[2*k+1].sum,t[2*k+1].suf);
	t[k].sum=t[2*k].sum+t[2*k+1].sum;	
}
int main(){
	cin>>n;
	for(register int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	build(1,n,1);
	cin>>m;
	int x,y,xh;
	for(register int i=1;i<=m;i++){
		scanf("%d",&xh);
		scanf("%d%d",&x,&y);
		if(xh==0){
			change(x,y,1);
		}
		else{
			cnt=0;
			ask(x,y,1);
			printf("%d\n",s.data);
		}
	}
	return 0;
}
```




---

## 作者：xgzc (赞：2)

### [题面](https://www.luogu.org/problemnew/show/SP1716)

### 题解

相信大家写过的传统做法像这样：（这段代码蒯自[Karry5307的题解](https://www.luogu.org/blog/Karry5307/solution-sp1716)）

```cpp
struct SegmentTree{
    ll l,r,prefix,suffix,sum,maxn;  
};

//...

inline void update(ll node)
{
    ll res;
    tree[node].sum=tree[node<<1].sum+tree[(node<<1)|1].sum;
    tree[node].maxn=max(tree[node<<1].maxn,tree[(node<<1)|1].maxn);
    res=tree[node<<1].suffix+tree[(node<<1)|1].prefix;
    tree[node].maxn=max(tree[node].maxn,res);
    res=tree[node<<1].sum+tree[(node<<1)|1].prefix;
    tree[node].prefix=max(tree[node<<1].prefix,res);
    res=tree[node<<1].suffix+tree[(node<<1)|1].sum;
    tree[node].suffix=max(tree[(node<<1)|1].suffix,res);
}

//...
```

有没有觉得这种做法有些麻烦

这里将一种硬核做法：**动态dp**

这个部分参考了[GKxx 的博客](https://www.luogu.org/blog/gkxx-is-here/what-the-hell-is-ddp)

引入广义矩阵乘法：
$$\mathrm{C} = \mathrm{A} * \mathrm{B} \Leftrightarrow \mathrm{C}_{i,j} = \max_k\left\{\mathrm{A}_{i,k} + \mathrm{B}_{k,j}\right\}$$
这样的话，我们首先写出动态规划的柿子：

设$f_i$表示以$i$结尾的最大子段和，$g_i$表示$[1,i]$的最大子段和

于是
$$\begin{aligned} f_i &= \max(f_{i-1} + a_i, a_i) \\ g_i &= \max(g_{i-1}, f_i) \end{aligned}$$
欢乐地写出矩乘的柿子：
$$\begin{bmatrix}f_{i-1} & g_{i-1} & 0\end{bmatrix} \times\begin{bmatrix}a_i & a_i & -\infty\\-\infty & 0 & -\infty\\a_i & a_i & 0\end{bmatrix}=\begin{bmatrix}f_i & g_i & 0\end{bmatrix}$$
妙哉

因为矩阵乘法具有结合律，于是可以用线段树维护

当然资瓷单点修改和查询区间最大子段和了

### 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define RG register
#define file(x) freopen(#x".in", "r", stdin);freopen(#x".out", "w", stdout);
#define clear(x, y) memset(x, y, sizeof(x));

inline int read()
{
	int data = 0, w = 1;
	char ch = getchar();
	while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if(ch == '-') w = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') data = data * 10 + (ch ^ 48), ch = getchar();
	return data * w;
}

const int maxn(50010), INF(0x3f3f3f3f);
template<typename T> inline void chkmax(T &a, const T &b)
	{ return (void) (a < b ? a = b : 0); }
struct Matrix
{
	int a[3][3];
	inline int *operator [] (const int &x) { return a[x]; }
	inline const int *operator [] (const int &x) const { return a[x]; }
} mat[maxn << 2]; int n, Q, a[maxn];

inline Matrix operator * (const Matrix &a, const Matrix &b)
{
	Matrix c; for(int i = 0; i < 3; i++) c[i][0] = c[i][1] = c[i][2] = -INF;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 3; k++)
				chkmax(c[i][k], a[i][j] + b[j][k]);
	return c;
}

void build(int root = 1, int l = 1, int r = n)
{
	if(l == r)
	{
		Matrix &o = mat[root]; o[0][1] = o[2][0] = o[2][1] = -INF;
		o[0][0] = o[0][2] = o[1][0] = o[1][2] = a[l];
		o[1][1] = o[2][2] = 0; return;
	}
	int mid = (l + r) >> 1, lson = root << 1, rson = lson | 1;
	build(lson, l, mid), build(rson, mid + 1, r);
	mat[root] = mat[lson] * mat[rson];
}

void update(int id, int v, int root = 1, int l = 1, int r = n)
{
	if(l == r) return (void)
		(mat[root][0][0] = mat[root][0][2]
		 = mat[root][1][0] = mat[root][1][2] = v);
	int mid = (l + r) >> 1, lson = root << 1, rson = lson | 1;
	if(id <= mid) update(id, v, lson, l, mid);
	else update(id, v, rson, mid + 1, r);
	mat[root] = mat[lson] * mat[rson];
}

Matrix query(int ql, int qr, int root = 1, int l = 1, int r = n)
{
	if(ql <= l && r <= qr) return mat[root];
	int mid = (l + r) >> 1, lson = root << 1, rson = lson | 1;
	if(qr <= mid) return query(ql, qr, lson, l, mid);
	if(ql >  mid) return query(ql, qr, rson, mid + 1, r);
	return query(ql, qr, lson, l, mid) * query(ql, qr, rson, mid + 1, r);
}

int main()
{
	n = read();
	for(RG int i = 1; i <= n; i++) a[i] = read();
	build(); Q = read();
	while(Q--)
	{
		int opt = read(), x = read(), y = read();
		if(opt)
		{
			Matrix ans = query(x, y);
			printf("%d\n", std::max(ans[1][0], ans[1][2]));
		}
		else a[x] = y, update(x, y);
	}
	return 0;
}
```

---

## 作者：WNico (赞：2)

>本蒟蒻第一次写题解。。

>题目链接：[Can you answer these queries III](https://www.luogu.org/problemnew/show/SP1716)
------------

没什么说的，主要的式子就三个，最后把每个区间内的用这个式子加一遍就行

注释以后补（如果可以的话）

上代码（zkw线段树）

------------
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>	
#include<cmath>
#define il inline
using namespace std;
int n,m,np;
struct tree{
	int prel,prer,res,sum;
}a[1048579];

tree change(tree x,tree y){ 	//省字
	tree c;
	c.sum=x.sum+y.sum;
	c.prel=max(x.prel,y.prel+x.sum);
	c.prer=max(y.prer,x.prer+y.sum);
	c.res=max(x.res,max(y.res,x.prer+y.prel));
	return c;
}

void updat(int i){
	tree x=a[i*2],y=a[i*2+1];
	a[i]=change(x,y);
}

tree Query(int x,int y){
	tree bx=a[x=x+np-1],by=a[y=y+np-1];
	while(x>>1!=y>>1){
		if(x%2==0){
			bx=change(bx,a[x+1]);
		}
		if(y%2){
			by=change(a[y-1],by);
		}
		x>>=1,y>>=1;
	}
	return change(bx,by);
}

int main(){		//有点压行
	cin>>n;
	np=pow(2,ceil(log2(n)));
	for(int i=np;i<n+np;++i) {scanf("%d",&a[i].sum);a[i].prel=a[i].prer=a[i].res=a[i].sum;}
	for(int i=(np+n-1)/2;i>0;--i) updat(i);
	int t,x,y;
	cin>>m;
	for(int ii=1;ii<=m;++ii){
		scanf("%d%d%d",&t,&x,&y);
		if(t==0){
			x+=np-1;
			a[x].sum=a[x].prer=a[x].prel=a[x].res=y;
			x>>=1;
			while(x){
				updat(x);
				x>>=1;
			}
		}else if(t==1){
			if(x>y) swap(x,y);
			if(x==y) printf("%d\n",a[x+np-1].sum);
			else printf("%d\n",Query(x,y).res);
		}
	}
	return 0;
}
```



---

## 作者：lichenxi (赞：2)

既然没人写，让我来给你们普及普及吧
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,d[100001],ans,p;
struct oo{int a,b,sum,lx,rx,sumx;}s[400001];
void update(int x)
{
    int l=x<<1,r=x<<1|1;
    s[x].sum=s[l].sum+s[r].sum;
    s[x].sumx=max(s[l].sumx,s[r].sumx);
    s[x].sumx=max(s[x].sumx,s[l].rx+s[r].lx);
    s[x].rx=max(s[r].rx,s[l].rx+s[r].sum);
    s[x].lx=max(s[l].lx,s[l].sum+s[r].lx);
}
void build(int x,int l,int r)
{
    s[x].a=l,s[x].b=r;
    if(l==r)
    {
        s[x].sum=s[x].sumx=s[x].lx=s[x].rx=d[l];
        return ;
    }
    build(x<<1,l,l+r>>1);
    build(x<<1|1,(l+r>>1)+1,r);
    update(x);
}
void change(int x,int y,int v)
{
    if(s[x].a==s[x].b)
    {
        s[x].sum=s[x].sumx=s[x].lx=s[x].rx=v;
        return ;
    }
    int mid=s[x].a+s[x].b>>1;
    if(y<=mid)change(x<<1,y,v);
    else change(x<<1|1,y,v);
    update(x);
}
oo get(int x,int l,int r)
{
    if(l<=s[x].a&&r>=s[x].b)
        return s[x];
    int mid=s[x].a+s[x].b>>1;
    oo g,h;
    if(l>mid)return get(x<<1|1,l,r);
    else if(r<=mid)return h=get(x<<1,l,r);
    else
    {
        g=get(x<<1,l,r);
        h=get(x<<1|1,l,r);
        oo ans;
        ans.sumx=max(g.sumx,h.sumx);
        ans.sumx=max(ans.sumx,g.rx+h.lx);
        ans.lx=max(g.lx,g.sum+h.lx);
        ans.rx=max(h.rx,g.rx+h.sum);
        return ans;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&d[i]);
    build(1,1,n);int x,y,z;
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d",&p);
        ans=-1e9;
        if(p==1)
        {
            scanf("%d%d",&x,&y);
            printf("%d\n",get(1,x,y).sumx);
        }
        else
        {
            scanf("%d%d",&x,&y);
            change(1,x,y);
        }
    }
}

```

---

## 作者：xsI666 (赞：1)

这题就是[GSS1](https://www.luogu.org/problemnew/show/SP1043)的带修改版本，**建议**先看一看[我的题解](https://70581.blog.luogu.org/solution-sp1043)，了解不带修改的版本怎么写。

本题的代码基于[我GSS1的题解](https://70581.blog.luogu.org/solution-sp1043)，一些注释也可以在那里看到。

这里讲一讲怎么修改：

与线段树相似，如果当前已经访问到了叶子节点，就直接将这个节点的所有参数都设为要修改的值即可，否则就递归左子树或右子树。

最后记得上传节点！

下面给出$AC$代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>

using namespace std;

inline int gi()
{
    int f = 1, x = 0; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar();}
    return f * x;
}

int n, m;
struct Node
{
	int sum, lans, rans, ans;
} t[50005 << 2];

inline void pushup(int x)
{
	t[x].sum = t[x << 1].sum + t[(x << 1) | 1].sum;
	t[x].lans = max(t[x << 1].lans, t[x << 1].sum + t[(x << 1) | 1].lans);
	t[x].rans = max(t[(x << 1) | 1].rans, t[(x << 1) | 1].sum + t[x << 1].rans);
	t[x].ans = max(max(t[x << 1].ans, t[(x << 1) | 1].ans), t[x << 1].rans + t[(x << 1) | 1].lans);
}

void bulid(int s, int o, int p)
{
	if (s == o)
	{
		t[p].sum = t[p].lans = t[p].rans = t[p].ans = gi();
		return;
	}
	int mid = (s + o) >> 1;
	bulid(s, mid, p << 1);
	bulid(mid + 1, o, (p << 1) | 1);
	pushup(p);
}

void modify(int l, int r, int s, int o, int p)//修改操作
{
	if (s == o)//已经是叶子节点了
	{
		t[p].ans = t[p].lans = t[p].rans = t[p].sum = r;//就更新它的所有参数
		return;
	}
	int mid = (s + o) >> 1;//找中点
	if (l <= mid) modify(l, r, s, mid, p << 1);//点在中点左边就递归左子树
	else modify(l, r, mid + 1, o, (p << 1) | 1);//否则递归右子树
	pushup(p);//上传节点
}

Node getans(int l, int r, int s, int o, int p)
{
	if (l <= s && r >= o)
	{
		return t[p];
	}
	int mid = (s + o) >> 1;
	if (l > mid) return getans(l, r, mid + 1, o, (p << 1) | 1);
	if (r <= mid) return getans(l, r, s, mid, p << 1);
	else 
	{
		Node ans, a, b;
		a = getans(l, r, s, mid, p << 1), b = getans(l, r, mid + 1, o, (p << 1) | 1);
		ans.sum = a.sum + b.sum;
		ans.ans = max(max(a.ans, a.rans + b.lans), b.ans);
		ans.lans = max(a.lans, a.sum + b.lans);
		ans.rans = max(b.rans, b.sum + a.rans);
		return ans;
	}
}

int main()
{
	n = gi();
	bulid(1, n, 1);
	m = gi();
	for (int i = 1; i <= m; i++)
	{
		int fl = gi(), x = gi(), y = gi();
		if (fl == 1) printf("%d\n", getans(x, y, 1, n, 1).ans);//如果是要求答案就输出答案
		else modify(x, y, 1, n, 1);//否则就进行修改
	}
	return 0;
}
```

---

## 作者：EternalEpic (赞：1)

## lxl曾讲过的P4513小白逛公园的弱化版

这道题~~一眼就看出~~是具有快速合并性质的线段树问题

but。。。 怎么通过左右儿子维护的信息，推出父节点的最大子段和呢(⊙o⊙)？

~~（我这种天才只花了5s思考）~~ 经过冥思苦想

我有了个idea。

对于每一个节点，应该要维护4个data。分别是lmax, rmax, allmax和sum。

lmax是指从左端点l开始最大的左子区间和，rmax同理（右max和）

allmax是指在此区间中最大的连续子段和（即ans）

sum为区间和

可是如何合并左右子树信息呢？？？

有些dp的思想（最优转移方案）

对于lmax，可以是max（左子树lmax， 左子树sum + 右子树lmax）

rmax = max （右子树rmax， 右子树sum + 左子树rmax）

allmax = max（左allmax， 右allmax， 左rmax + 右lmax）

为方便转移， 我们采用结构体 + 重载运算符

```cpp
template <class T> inline T max(const T&x, const T&y, const T&z) {
	return x > y ? (x > z ? x : z) : (y > z ? y : z);
}
 struct Node {
 	int all_max, left_max, right_max, sum;
 	inline Node operator + (const Node&opt) {
        return (Node) {
       		max(all_max, opt.all_max, right_max + opt.left_max),
        	max(left_max, opt.left_max + sum),
        	max(opt.right_max, right_max + opt.sum), sum + opt.sum
        };
    }
}；
```


哈哈，搞清楚这个，剩下滴就是单点修改区间查询线段树模板了。

且慢！查询不太好写，一定要注意分类讨论，而且左右区间别弄反

## CODE：
```cpp
//Program written by Liu Zhaozhou ~~~
#include <bits/stdc++.h>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <deque>
#include <string>

#define lowbit(x) x & -x

#pragma GCC optimize(3)

using namespace std;

namespace Base {
inline char gc(void)
{
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

#define gc() getchar()

template <class T> inline void read(T &x)
{
	T flag = 1; x = 0; register char ch = gc();
	for (; !isdigit(ch); ch = gc()) if (ch == '-') flag = -1;
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch & 15);
	x *= flag; return;
}

template <class T> inline void write(T x) {
	if (x < 0) putchar('-'), x = -x;
	register T y = 1; int len = 1;
	for (; y <= x / 10; y *= 10) ++len;
	for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

template <class T> inline void writeln(T x) {write(x); puts("");}
template <class T> inline void writeln(T x, char c) {write(x); putchar(c);}
template <class T> inline void writeln(char c, T x) {putchar(c); write(x);}

template <class T> inline void chkmax(T &x, const T y) {x > y ? x = x : x = y;}
template <class T> inline void chkmin(T &x, const T y) {x < y ? x = x : x = y;}
template <class T> inline T max(const T&x, const T&y, const T&z) {
	return x > y ? (x > z ? x : z) : (y > z ? y : z);
}

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define Ms(arr, opt) memset(arr, opt, sizeof(arr))
#define Mp(x, y) make_pair(x, y)

inline void file(string str) {
	freopen((str + ".in").c_str(), "r", stdin);
	freopen((str + ".out").c_str(), "w", stdout);
}
}

using namespace Base;

enum {
	Maxn = 500005
};

int n, m, a[Maxn];

struct SegmentTree {
	struct Node {
    	int all_max, left_max, right_max, sum;
    	inline Node operator + (const Node&opt) {
        	return (Node) {
        	    max(all_max, opt.all_max, right_max + opt.left_max),
				max(left_max, opt.left_max + sum),
            	max(opt.right_max, right_max + opt.sum), sum + opt.sum
        	};
    	}
	} t[Maxn << 2], ans;

	inline void build(int pos, int l, int r) {
    	if (l == r) {
    	    t[pos] = (Node) {a[l], a[l], a[l], a[l]};
    	    return;
    	}
    	register int mid = l + r >> 1;
		build(pos << 1, l, mid);
		build(pos << 1 | 1, mid + 1, r);
		t[pos] = t[pos << 1] + t[pos << 1 | 1];
	}

	inline Node query(int pos, int l, int r, int tl, int tr) {
		if (l >= tl && r <= tr) return t[pos];
		register int mid = l + r >> 1;
		if (tr <= mid) return query(pos << 1, l, mid, tl, tr);
		else if (mid < tl) return query(pos << 1 | 1, mid + 1, r, tl, tr);
		else return query(pos << 1, l, mid, tl, mid) + query(pos << 1 | 1, mid + 1, r, mid + 1, tr);
	}

	inline void modify(int pos, int l, int r, int cur, int val){
		if (r < cur || l > cur) return;
		if (l == r) {t[pos] = (Node) {val, val, val, val}; return;}
    	register int mid = l + r >> 1;
		if (cur <= mid) modify(pos << 1, l, mid, cur, val);
		else modify(pos << 1 | 1, mid + 1, r, cur, val);
		t[pos] = t[pos << 1] + t[pos << 1 | 1]; return;
	}
	
	inline int query(int l, int r) {
		ans = query(1, 1, n, l, r);
		return ans.all_max;
	}

} sgt;

int op, x, y;

signed main(void) {
    read(n); read(m);
    for (int i = 1; i <= n; i++)
    	read(a[i]);
    sgt.build(1, 1, n);
    
	while (m--) {
        read(op); read(x); read(y);
        if (op == 1) {
            if (x > y) swap(x, y);
            writeln(sgt.query(x, y));
        } else sgt.modify(1, 1, n, x, y);
    }
    
    return 0;
}

/*SegmentTree, easy*/

```



---

## 作者：Five_D (赞：1)

### 题目简述

1. 单点修改

2. 查询区间最大字段和

### 题解

这是一个序列问题，很显然我们可以用线段树进行维护。

#### 建树（build）

我的代码是不建树的，刚开始的赋值直接用$change$操作。

#### 赋值更新（change）

最大子段和的更新，分类讨论：

1. 最大子段和完全在左区间中

   ```cpp
   a[k].max=a[k<<1].max;
   ```

2. 最大子段和完全在右区间中

   ```cpp
   a[k].max=a[k<<1|1].max;
   ```

3. 最大子段和一部分在左区间，一部分在右区间
   ```cpp
   a[k]=a[k<<1].rmax+a[k<<1|1].lmax;
   //a[k].lmax表示在当前块内包含左端点的最大子段和
   //a[k].rmax表示在当前块内包含右端点的最大子段和
   ```

那么，如何更新$a[k].lmax$和$a[k].rmax$呢



```cpp
a[k].lmax=max(a[k<<1].lmax,a[k<<1].sum+a[k<<1|1].lmax);
//a[k].lmax有两种情况：
//1. 只包含左区间
//2. 包含整段左区间（即左区间的和，用a[k].sum表示）和一部分右区间 
a[k].rmax=max(a[k<<1|1].rmax,a[k<<1|1].sum+a[k<<1].rmax);
//a[k].rmax同理
```
而$a[k].sum$是很好更新的。

```cpp
inline void change(int k,int l,int r,int x,int num)
{
	if (l==r)
	{
		a[k].sum=a[k].lmax=a[k].rmax=a[k].max=num;return;
	}
	int mid=(l+r)>>1;
	if (x<=mid) change(k<<1,l,mid,x,num);
	else change(k<<1|1,mid+1,r,x,num);
	a[k].sum=a[k<<1].sum+a[k<<1|1].sum;
	a[k].lmax=max(a[k<<1].lmax,a[k<<1].sum+a[k<<1|1].lmax);
	a[k].rmax=max(a[k<<1|1].rmax,a[k<<1|1].sum+a[k<<1].rmax);
	a[k].max=max(a[k<<1].rmax+a[k<<1|1].lmax,max(a[k<<1].max,a[k<<1|1].max));
}
```



#### 查询（ask）~~（我的查询好像和其他人的不大一样）~~

我们可以将询问分成很多块，块的个数应该不会超过$log n$，每个块的编号用$b$数组保存。

```cpp
inline void ask(int k,int l,int r,int x,int y)
{
	if (r<x || y<l) return;  //和查询区间没有交集
	if (x<=l && r<=y)
	{
		b[++tot]=k;return;  //保存块的编号
	}
	int mid=(l+r)>>1;
	ask(k<<1,l,mid,x,y),ask(k<<1|1,mid+1,r,x,y);
}
```



很显然，编号一定是从小到大的。

我们已经知道了每个块的$sum​$，$lmax​$，$rmax​$和$max​$。

然后我们便可以暴力枚举块的收尾来计算最大字段和。

对于第$i​$块到第$j​$块，$ans=a[b[i]].rmax+a[b[j]].lmax+\sum_{k=i+1}^{j-1} a[b[k]].sum​$。

如果$i==j$，需要特判$ans=a[b[i]].max$。

这个应该也能用普通求最大字段和的$dp​$来做。~~但我比较懒，只打了个暴力~~。

```cpp
inline int get_ans()
{
	int ans=INT_MIN;
	for (int i=1;i<=tot;i++)
	{
		ans=max(ans,a[b[i]].max);
		int sum=a[b[i]].rmax;
		for (int j=i+1;j<=tot;j++)
		{
			sum+=a[b[j]].sum;
			ans=max(ans,sum-a[b[j]].sum+a[b[j]].lmax);
			if (sum<=0) break;
             //如果sum<=0，那么前面的还不如不取，肯定不会比只取后面的答案优（和普通dp意思差不多）
		}
	}
	return ans;
}
```

#### 复杂度

如果像我一样查询打了暴力，复杂度应该是$O(nlog^2n)$，我跑了$30ms$。

但如果查询也用普通方法打了个$dp$的话，复杂度应该是$O(nlogn)$。

### 代码code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 50001
struct Tree
{
	int sum,lmax,rmax,max;
}a[N<<2];
int b[N<<2],tot=0;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0' || '9'<ch) 
	{
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while ('0'<=ch && ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}
inline void write(int x)
{
	if (x<0) putchar('-'),x=-x;
	if (x>9) write(x/10);
	putchar(x%10+'0');
}
inline void change(int k,int l,int r,int x,int num)
{
	if (l==r)
	{
		a[k].sum=a[k].lmax=a[k].rmax=a[k].max=num;return;
	}
	int mid=(l+r)>>1;
	if (x<=mid) change(k<<1,l,mid,x,num);
	else change(k<<1|1,mid+1,r,x,num);
	a[k].sum=a[k<<1].sum+a[k<<1|1].sum;
	a[k].lmax=max(a[k<<1].lmax,a[k<<1].sum+a[k<<1|1].lmax);
	a[k].rmax=max(a[k<<1|1].rmax,a[k<<1|1].sum+a[k<<1].rmax);
	a[k].max=max(a[k<<1].rmax+a[k<<1|1].lmax,max(a[k<<1].max,a[k<<1|1].max));
}
inline void ask(int k,int l,int r,int x,int y)
{
	if (r<x || y<l) return;
	if (x<=l && r<=y)
	{
		b[++tot]=k;return;
	}
	int mid=(l+r)>>1;
	ask(k<<1,l,mid,x,y),ask(k<<1|1,mid+1,r,x,y);
}
inline int get_ans()
{
	int ans=INT_MIN;
	for (int i=1;i<=tot;i++)
	{
		ans=max(ans,a[b[i]].max);
		int sum=a[b[i]].rmax;
		for (int j=i+1;j<=tot;j++)
		{
			sum+=a[b[j]].sum;
			ans=max(ans,sum-a[b[j]].sum+a[b[j]].lmax);
			if (sum<=0) break;
		}
	}
	return ans;
}
int main()
{
	int n=read();
	for (int i=1;i<=n;i++) 
	{
		int x=read();
		change(1,1,n,i,x);
	}
	int m=read();
	for (int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		tot=0,ask(1,1,n,x,y);
		write(get_ans()),putchar('\n');
	}
	return 0;
}
```







---

## 作者：学委 (赞：0)

- 线段树的每个结点维护区间的这些信息：

  所有数的和；最大前缀和；最大后缀和；最大子段和

- 如何update：

  所有数的和 = 左区间所有数的和 + 右区间所有数的和
  
  最大前缀和 = max(左区间最大前缀和，左区间所有数的和 + 右区间最大前缀和)
  
  最大后缀和 = max(右区间最大后缀和，右区间所有数的和 + 左区间最大后缀和)
  
  最大子段和 = max(左区间最大子段和，右区间最大子段和，左区间最大后缀和 + 右区间最大前缀和)
  
这些update的正确性都是比较显然的。

注意至少要选一个数，而上面的更新允许不选区间内任何一个数，所以当数列中只有负数的时候，上面的做法会输出0。所以我们顺便维护区间最大值，如果区间最大值是负数，就输出这个负数。

```cpp
#include <cstdio>
#include <algorithm>
using std::max;
const int N = 5e4 + 10, INF = 1e9;
int n, q, a[N];
struct Node {
  int maxson, sum, maxl, maxr, maxnum;
  Node() { maxson = sum = maxl = maxr = 0; maxnum = -INF; }
  void init(int w) {
    maxson = maxl = maxr = max(0, w);
    maxnum = sum = w;
  }
  Node operator+(const Node& g) {
    Node res;
    res.sum = sum + g.sum;
    res.maxson = max(maxr + g.maxl, max(maxson, g.maxson));
    res.maxl = max(maxl, sum + g.maxl);
    res.maxr = max(g.maxr, g.sum + maxr);
    res.maxnum = max(maxnum, g.maxnum);
    return res;
  }
} node[N * 4];
void build(int k, int l, int r) {
  if (l == r) {
    node[k].init(a[l]);
    return;
  } int mid = (l + r) / 2;
  build(k * 2, l, mid);
  build(k * 2 + 1, mid + 1, r);
  node[k] = node[k * 2] + node[k * 2 + 1];
}
void modify(int k, int l, int r, int x, int w) {
  if (l == r) {
    a[l] = w; node[k].init(a[l]);
    return;
  } int mid = (l + r) / 2;
  if (x <= mid) modify(k * 2, l, mid, x, w);
  else modify(k * 2 + 1, mid + 1, r, x, w);
  node[k] = node[k * 2] + node[k * 2 + 1];
}
Node query(int k, int l, int r, int x, int y) {
  if (y < l or r < x) return Node();
  if (x <= l and r <= y) return node[k];
  int mid = (l + r) / 2;
  return query(k * 2, l, mid, x, y) + query(k * 2 + 1, mid + 1, r, x, y);
}
int main() {
  scanf("%d", &n); for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  build(1, 1, n);
  scanf("%d", &q);
  while (q--) {
    int op; scanf("%d", &op);
    if (op == 0) {
      int x, y; scanf("%d %d", &x, &y);
      modify(1, 1, n, x, y);
    }
    else if (op == 1) {
      int l, r; scanf("%d %d", &l, &r);
      Node ans = query(1, 1, n, l, r);
      if (ans.maxnum < 0) printf("%d\n", ans.maxnum);
      else printf("%d\n", ans.maxson);
    }
  }
  return 0;
}
```

---

## 作者：Paranoid丶离殇 (赞：0)

题目传送门：[SP1043 GSS1 - Can you answer these queries I](https://www.luogu.org/problem/SP1716)

[更好的阅读体验](https://www.cnblogs.com/Paranoid-LS/p/11593000.html)

# 动态维护子段和最大值

### 前置知识

**静态维护子段和最大值**：[SP1043 GSS1 - Can you answer these queries I](https://www.luogu.org/problem/SP1043)

[题解传送](https://www.luogu.org/blog/Paranoid-LS/solution-sp1043)

## 题解：

提供结构体指针线段树写法：

设$l$为区间左端点， $r$为区间右端点；

$ls$为以$l$为左端点的最大子段和, $rs$为以$r$为右端点的最大子段和;

$sum$为区间和, $val$为区间子段和最大和。

$ch[0]$为左儿子, $ch[1]$为右儿子.

考虑维护：

> o->sum = ch[0]->sum + ch[1]->sum;
>
> o->ls = max(ch[0]->ls, ch[0]->sum + ch[1]->ls);
>
> o->rs = max(ch[1]->rs, ch[1]->sum + ch[0]->rs);
>
> o->val = max(max(ch[0]->val, ch[1]->val), max(max(o->ls, o->rs), ch[0]->rs + ch[1]->ls);

 这样可以考虑到所有的转移情况；

在询问时, 若询问区间跨过左右两个子区间, 则我们利用$ls, rs, sum$来更新出当前区间的$val$;

所以我们返回结构体指针。

题目中为单点修改，考虑如何写up()函数。

发现维护方式与建树时相同。

```cpp
void up() {
	sum = ch[0]->sum + ch[1]->sum;
	ls = Max(ch[0]->ls, ch[0]->sum + ch[1]->ls);
	rs = Max(ch[1]->rs, ch[1]->sum + ch[0]->rs);
	val = Max(Max(ch[0]->val, ch[1]->val), Max(Max(ls, rs), ch[0]->rs + ch[1]->ls));
}
```

~~直接乱搞即可。~~

### code：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 5e4 + 5;
int read() {
	int x = 0, f = 1; char ch;
	while(! isdigit(ch = getchar())) (ch == '-') && (f = -f);
	for(x = ch^48; isdigit(ch = getchar()); x = (x<<3) + (x<<1) + (ch^48));
	return x * f;
}
int n, m;
template <class T> T Max(T a, T b) { return a > b ? a : b; }
struct Segment {
	struct node {
		int l, r, ls, rs, sum, val;
		node *ch[2];
		node(int l, int r, int ls, int rs, int sum, int val) : l(l), r(r), ls(ls), rs(rs), sum(sum), val(val) {
			ch[0] = ch[1] = NULL;
		}
		inline int mid() { return (l + r) >> 1; }
		inline void up() {
			sum = ch[0]->sum + ch[1]->sum;
			ls = Max(ch[0]->ls, ch[0]->sum + ch[1]->ls);
			rs = Max(ch[1]->rs, ch[1]->sum + ch[0]->rs);
			val = Max(Max(ch[0]->val, ch[1]->val), Max(Max(ls, rs), ch[0]->rs + ch[1]->ls));
		}
	} *root;
	void build(node *&o, int l, int r) {
		o = new node(l, r, 0, 0, 0, 0);
		if(l == r) {
			o->ls = o->rs = o->sum = o->val = read();
			return;
		}
		build(o->ch[0], l, o->mid());
		build(o->ch[1], o->mid() + 1, r);
		o->up();
	}
	void change(node *o, int x, int v) {
		if(o->l == x && o->r == x) {
			o->ls = o->rs = o->sum = o->val = v;
			return;
		}
		if(x <= o->mid()) change(o->ch[0], x, v);
		if(x > o->mid()) change(o->ch[1], x, v);
		o->up();
	}
	node *query(node *o, int l, int r) {
		if(l <= o->l && o->r <= r) return o;
		if(r <= o->mid()) return query(o->ch[0], l, r);
		if(l > o->mid()) return query(o->ch[1], l, r);
		node *res = new node(l, r, 0, 0, 0, 0);
		node *t1 = query(o->ch[0], l, r), *t2 = query(o->ch[1], l, r);
		res->sum = t1->sum + t2->sum;
		res->ls = Max(t1->ls, t1->sum + t2->ls);
		res->rs = Max(t2->rs, t2->sum + t1->rs);
		res->val = Max(Max(t1->val, t2->val), Max(Max(res->ls, res->rs), t1->rs + t2->ls));
		return res;
	}
} tr;
int main() {
	n = read();
	tr.build(tr.root, 1, n);
	m = read();
	for(int i = 1, opt, l, r; i <= m; ++ i) {
		opt = read(); l = read(); r = read();
		if(opt & 1) printf("%d\n", tr.query(tr.root, l, r)->val);
		else tr.change(tr.root, l, r);
	}
	return 0;
}
```

---

## 作者：VenusM1nT (赞：0)

平衡树。和 `GSS1` 一样，做法和 `P2710 数列` 相似，但是这道题依然是可以使用线段树的，平衡树效率较低，不过接下来的 `GSS6` 就需要用平衡树了。

附上平衡树的代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 2e9
#define MAXN 500005
using namespace std;
struct FHQTreap
{
	int son[2],siz,key;
	ll val,maxn,lmax,rmax,rev,sum,cov;
}t[MAXN];
queue <int> q;
int n,m,root,a[MAXN],siz,stk[MAXN],top;
template <typename T> void Read(T &x)
{
    int fu=1;
    x=0;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') fu=-1;
    for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch-48);
    x*=fu;
}
int NewNode(ll val)
{
	int x;
	if(!q.empty())
	{
		x=q.front();
		q.pop();
	}
	else x=++siz;
	t[x].son[0]=t[x].son[1]=t[x].rev=0;
	t[x].cov=inf;
	t[x].key=rand();
	t[x].siz=1;
	t[x].val=t[x].sum=t[x].maxn=val;
	t[x].lmax=t[x].rmax=max(val,1ll*0);
	return x;
}
void Update(int x)
{
	if(t[x].son[0] && t[x].son[1])
	{
		t[x].siz=t[t[x].son[0]].siz+t[t[x].son[1]].siz+1;
		t[x].sum=t[t[x].son[0]].sum+t[t[x].son[1]].sum+t[x].val;
		t[x].maxn=max(t[t[x].son[0]].maxn,t[t[x].son[1]].maxn);
		t[x].maxn=max(t[x].maxn,t[t[x].son[0]].rmax+t[t[x].son[1]].lmax+t[x].val);	
		t[x].lmax=max(t[t[x].son[0]].lmax,t[t[x].son[0]].sum+t[t[x].son[1]].lmax+t[x].val);
		t[x].rmax=max(t[t[x].son[1]].rmax,t[t[x].son[1]].sum+t[t[x].son[0]].rmax+t[x].val);
	}
	else if(t[x].son[0])
	{
		t[x].siz=t[t[x].son[0]].siz+1;
		t[x].sum=t[t[x].son[0]].sum+t[x].val;
		t[x].maxn=max(t[t[x].son[0]].maxn,t[t[x].son[0]].rmax+t[x].val);
		t[x].lmax=max(t[t[x].son[0]].lmax,t[t[x].son[0]].sum+t[x].val);
		t[x].lmax=max(t[x].lmax,1ll*0);
		t[x].rmax=max(t[t[x].son[0]].rmax+t[x].val,1ll*0);
	}
	else if(t[x].son[1])
	{
		t[x].siz=t[t[x].son[1]].siz+1;
		t[x].sum=t[t[x].son[1]].sum+t[x].val;
		t[x].maxn=max(t[t[x].son[1]].maxn,t[t[x].son[1]].lmax+t[x].val);
		t[x].rmax=max(t[t[x].son[1]].rmax,t[t[x].son[1]].sum+t[x].val);
		t[x].rmax=max(t[x].rmax,1ll*0);
		t[x].lmax=max(t[t[x].son[1]].lmax+t[x].val,1ll*0);
	}
	else
	{
		t[x].siz=1;
		t[x].sum=t[x].maxn=t[x].val;
		t[x].lmax=t[x].rmax=max(t[x].val,1ll*0);
	}
}
void reverse(int x)
{
	swap(t[x].son[0],t[x].son[1]);
	swap(t[x].lmax,t[x].rmax);
	t[x].rev^=1;
}
void Change(int x,int val)
{
	t[x].val=val;
	t[x].sum=t[x].siz*val;
	t[x].lmax=t[x].rmax=max(t[x].sum,1ll*0);
	t[x].maxn=max(t[x].sum,t[x].val);
	t[x].cov=val;
}
void PushDown(int x)
{
	if(t[x].rev)
	{
		if(t[x].son[0]) reverse(t[x].son[0]);
		if(t[x].son[1]) reverse(t[x].son[1]);
	}
	if(t[x].cov!=inf)
	{
		if(t[x].son[0]) Change(t[x].son[0],t[x].cov);
		if(t[x].son[1]) Change(t[x].son[1],t[x].cov);
	}
	t[x].rev=0;
	t[x].cov=inf;
}
int BuildFHQTreap(int sum)
{
	memset(stk,0,sizeof(stk));
	top=0;
	int x,lat;
	for(int i=1;i<=sum;i++)
	{
		x=NewNode(a[i]);
		lat=0;
		while(top && t[stk[top]].key>t[x].key)
		{
			Update(stk[top]);
			lat=stk[top];
			stk[top--]=0;
		}
		if(top) t[stk[top]].son[1]=x;
		t[x].son[0]=lat;
		stk[++top]=x;
	}
	while(top) Update(stk[top--]);
	return stk[1];
}
int Merge(int x,int y)
{
	if(x) PushDown(x);
	if(y) PushDown(y);
	if(!x || !y) return x+y;
	if(t[x].key<t[y].key)
	{
		t[x].son[1]=Merge(t[x].son[1],y);
		Update(x);
		return x;
	}
	else
	{
		t[y].son[0]=Merge(x,t[y].son[0]);
		Update(y);
		return y;
	}
}
void Split(int rt,int pos,int &x,int &y)
{
	if(!rt) x=y=0;
	else
	{
		PushDown(rt);
		if(t[t[rt].son[0]].siz>=pos)
		{
			y=rt;
			Split(t[rt].son[0],pos,x,t[rt].son[0]);
		}
		else
		{
			x=rt;
			Split(t[rt].son[1],pos-t[t[rt].son[0]].siz-1,t[rt].son[1],y);
		}
		Update(rt);
	}
}
void Recycle(int x)
{
	if(!x) return;
	q.push(x);
	Recycle(t[x].son[0]);
	Recycle(t[x].son[1]);
}
void Modify()
{
	int x,pos,sum,val,ax,ay,bx,by;
	Read(x);
	Read(val);
	pos=x;
	sum=1;
	Split(root,pos-1,ax,bx);
	Split(bx,sum,ay,by);
	Change(ay,val);
	root=Merge(ax,Merge(ay,by));
}
void GetMax()
{
	int x,y,pos,sum,ax,ay,bx,by;
	Read(x);
	Read(y);
	pos=x;
	sum=y-x+1;
	Split(root,pos-1,ax,bx);
	Split(bx,sum,ay,by);
	printf("%lld\n",t[ay].maxn);
	root=Merge(ax,Merge(ay,by));
}
int main()
{
	Read(n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	root=BuildFHQTreap(n);
	Read(m);
	while(m--)
	{
		int opt;
		Read(opt);
		if(!opt) Modify();
		else GetMax();
	}
	return 0;
}
```

---

