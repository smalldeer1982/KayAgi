# Sereja and Dividing

## 题目描述

Let's assume that we have a sequence of doubles $ a_{1},a_{2},...,a_{|a|} $ and a double variable $ x $ . You are allowed to perform the following two-staged operation:

1. choose an index of the sequence element $ i $ $ (1<=i<=|a|) $ ;
2. consecutively perform assignments: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF380E/baffd80c48ee79165f910c02d82d94b1e032eff1.png).

Let's use function $ g(a,x) $ to represent the largest value that can be obtained from variable $ x $ , using the described operation any number of times and sequence $ a $ .

Sereja has sequence $ b_{1},b_{2},...,b_{|b|} $ . Help Sereja calculate sum: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF380E/61f426b3571521d30a29374c6c07cc3eb3b48dc9.png). Record $ [b_{i},b_{i+1},...,b_{j}] $ represents a sequence containing the elements in brackets in the given order. To avoid problems with precision, please, print the required sum divided by $ |b|^{2} $ .

## 样例 #1

### 输入

```
5
1 2 3 4 1
```

### 输出

```
1.238750000000000
```

# 题解

## 作者：lzytag (赞：2)

提供一种更加精确（可以取模），复杂度为 $O(n\log n)$ 的做法。

首先我们发现，水量为 $x$ 的杯子，再一个区间中的贡献与水量和它在区间中第几大有关（若有相同水量，则以数列中的位置为第二关键字即可）。若它是第 $y$ 大，那么贡献为 $\frac{x}{2^y}$。

我们对每一个杯子单独计算贡献，第 $i$ 个杯子贡献为。

$$b_i\times \sum_{l=1}^i\sum_{r=i}^n 0.5^{f(l,r,i)+1}$$

其中 $f(l,r,i)$ 代表区间 $[l,r]$ 中比水量 $b_i$ 大的杯子的个数。

很显然，$f(l,r,i) = f(l,i,i)+f(i,r,i)$ 继续变形即可得到。

$$0.5\times b_i\times\sum_{l=1}^i\sum_{r=i}^n (0.5^{f(l,i,i)}\times0.5^{f(i,i,r)})$$

运用乘法分配律，原式转换为。

$$0.5\times b_i\times\sum_{l=1}^i0.5^{f(l,i,i)}\times\sum_{r=i}^n0.5^{f(i,i,r)}$$

于是我们想到从大到小枚举 $b_i$，定义 $v_i$ 数组，初始时全为 $1$，每枚举一个杯子 $x$ 就把 $v_x$ 设为 $0.5$，于是原式就变成了一个单点修改，求区间每个后缀/前缀乘积的和。直接开线段树维护，每个节点上记录每个后缀/前缀乘积的和，以及所有数的乘积即可轻松解决。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define lc c<<1
#define rc c<<1|1
#define mid (l+r>>1)
#define pb push_back
const int N = 3e5+5;
const double eps = 1e-8;
struct Node{
    double s,sl,sr;
};
Node operator + (Node i,Node j)
{
    return Node{i.s*j.s,i.sl+j.sl*i.s,i.sr*j.s+j.sr};
}
struct SGT{
    Node tr[N*4];
    void upd(int c){tr[c] = Node{0.5,0.5,0.5};}
    void Upd(int c,int l,int r,int x)
    {
        if(l == r) return upd(c),void();
        if(x > mid) Upd(rc,mid+1,r,x);
        else Upd(lc,l,mid,x);
        tr[c] = tr[lc] + tr[rc];
    }
    Node Qry(int c,int l,int r,int ql,int qr)
    {
        if(l == ql && r == qr) return tr[c];
        if(ql > mid) return Qry(rc,mid+1,r,ql,qr);
        else if(qr <= mid) return Qry(lc,l,mid,ql,qr);
        else return Qry(lc,l,mid,ql,mid)+Qry(rc,mid+1,r,mid+1,qr);
    }
    void build(int c,int l,int r)
    {
        tr[c] = Node{1,1,1};
        if(l == r) return ;
        build(lc,l,mid),build(rc,mid+1,r);
        tr[c] = tr[lc] + tr[rc];
    }
}tr1;
int a[N],n;
int id[N];
bool cmp(int i,int j)
{
    return a[i] > a[j];
}
double res;
int main()
{
    scanf("%d",&n);
    for(int i = 1;i <= n;i++) scanf("%d",a+i),id[i] = i;
    sort(id+1,id+1+n,cmp);
    tr1.build(1,1,n);
    for(int i = 1;i <= n;i++)
    {
        int j = id[i];
        Node l = tr1.Qry(1,1,n,1,j),r = tr1.Qry(1,1,n,j,n);
        res += l.sr*r.sl*0.5*a[j];
        tr1.Upd(1,1,n,j);
    }
    printf("%.9lf\n",res/n/n);
    return 0;
}
```

---

## 作者：Yukikaze_ (赞：2)

首先，为了使结果最大，一定是对杯子按照水的数量从小到大进行操作。

发现一个数列中，如果hi是第k大的，那么它对答案的贡献是hi/2^k。

于是可以舍弃k较大的数字，对于每个数字，求出左右比它大的前30个数字，然后直接统计答案。

求出数字可以先排序然后用链表依次插入，统计答案是个卷积的式子，展开就可以线性做了。

代码如下

```cpp
#include<bits/stdc++.h>
#define IT set<int>::iterator
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)? EOF:*p1++)
using namespace std;
typedef double ld;
const int N=1000010,lim=22;
char buf[1<<23],*p1=buf,*p2=buf;
int l[N],r[N],nxt[N],st[N],tp;
int h[N],n,id[N],rk[N];
ld er[31],ans;
int a[31],b[31];
int read()
{
	int res=0,fl=0;
	char a=getchar();
	while(a<'0'||a>'9') {if(a=='-') fl=1;a=getchar();}
	while(a>='0'&&a<='9') res=res*10+a-'0',a=getchar();
	return fl? -res:res;
}
bool cmp(int a,int b) {return h[a]>h[b];}
int main()
{
	freopen("drink.in","r",stdin);
	freopen("drink.out","w",stdout);
	int i,j,li,lj;
	n=read();
	for(i=1;i<=n;i++) h[i]=read(),id[i]=i;
	sort(id+1,id+n+1,cmp);
	for(i=1;i<=n;i++) rk[id[i]]=i;
	for(er[0]=1,i=1;i<=30;i++) er[i]=er[i-1]*2;
	for(i=1;i<=n+1;i++)
	{
		while(tp&&rk[st[tp]]>rk[i]) nxt[st[tp]]=i,tp--;
		st[++tp]=i;
	}
	r[0]=n+1;
	for(i=1;i<=n;i++)
	{
		memset(a,0,sizeof(a)),memset(b,0,sizeof(b));
		r[id[i]]=nxt[id[i]],l[id[i]]=l[nxt[id[i]]],r[l[id[i]]]=l[r[id[i]]]=id[i];
		for(li=id[i],lj=0;lj<lim&&li!=0;lj++,li=l[li]) a[lj]=li-l[li];
		for(li=id[i],lj=0;lj<lim&&li!=n+1;lj++,li=r[li]) b[lj]=r[li]-li;
		ld ti=0;
		for(j=0;j<lim;j++) ti+=(ld)(b[j])/er[j];
		for(j=0;j<lim;j++) ans+=(ld)(h[id[i]])*ld(a[j])/er[j+1]*ti;
	}
	printf("%.10lf",ans/(ld)n/(ld)n);
	return 0;
}
```


---

## 作者：Hoks (赞：0)

## 前言
好题，一道很好的洋葱题。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
一点思路也没有，怎么办？

先去找性质吧。

首先考虑下怎样倒水是最优的。

手玩下样例就知道肯定是从小到大一个一个倒过去最优。

感性理解一下，如果我目前杯和一个较大的杯倒过后，他的值变得较大，那么他再和一杯较小的倒就甚至有可能倒贴了。

所以肯定是从小到大更优。

那么我们考虑下准确的表达，精确的计算出每杯水的贡献。

因为是从小到大倒的，所以实际上一杯水的贡献只和他的水量以及第几大有关。

具体的，对于一杯有 $x$ 水，第 $y$ 大的水杯，他的贡献即为 $\frac{x}{2^y}$。

设第 $i$ 杯水在区间 $[j,k]$ 中的排名为 $f(i,j,k)-1$。

则可以把答案写为：
$$\sum\limits_{j=1}^n \sum\limits_{k=j}^n \sum\limits_{i=j}^k 0.5^{f(i,j,k)+1}a_i$$

考虑怎么来算这个式子，肯定是要数据结构了。

那么考虑经典套路尝试把对于同一杯水的计算合并，那么就可以先把式子化为：
$$\sum\limits_{i=1}^n a_i\times\sum\limits_{j=1}^i \sum\limits_{k=i}^n 0.5^{f(i,j,k)+1}$$

考虑继续化简这个式子。

不难发现，对于 $f$ 函数满足：
$$f(i,j,k)=f(i,j,i)+f(i,i,k)$$

用这个性质把上面的那个式子拆开得到：
$$\sum\limits_{i=1}^n a_i\times\sum\limits_{j=1}^i \sum\limits_{k=i}^n (0.5^{f(i,j,i)}\times0.5^{f(i,i,k)}\times0.5)$$

显然的是 $f(i,j,i)$ 与 $k$ 无关，而 $0.5$ 则与 $i,j,k$ 都无关，给他们都提出来得到：
$$0.5\times\sum\limits_{i=1}^n a_i\times\sum\limits_{j=1}^i 0.5^{f(i,j,i)}\times\sum\limits_{k=i}^n 0.5^{f(i,i,k)}$$

然后考虑如何计算这个式子。

我们只需要考虑把后面的那个 $\sum$ 分开计算即可。

考虑到 $f$ 函数是计算比 $i$ 大的个数，貌似不太好处理。

那么我们就直接按照 $a_i$ 大小从大往小枚举，此时我们不难发现，对于 $i$：
1. 如果他被枚举到了，那么算上这个数就是要多乘上一个 $0.5$。
2. 如果他没被枚举到，那么算上他就是要多乘一个 $1$。

而对于和式，直接用线段树维护前后缀乘积即可。

那么具体做法也就是：
1. 给所有点权赋 $1$，按 $a_i$ 从大往小枚举。
2. 用线段树求出前缀乘积和，后缀乘积和，按照上面的式子计算贡献。
3. 给枚举过的点权赋为 $0.5$。

最后输出累加的贡献和即可。
## 代码

```cpp
#include <bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=3e5+10,V=1e6,mod=1004535809,INF=0x3f3f3f3f3f3f3f3f;
struct node{double sl,sr,s;}t[N<<2];
int n,a[N],id[N];double ans;
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
    inline bool chk(char c) { return !(c>='a'&&c<='e'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='*'||c=='/'); }
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
inline bool cmp(int x,int y){return a[x]>a[y];}
inline node merge(node x,node y){return {x.sl+y.sl*x.s,x.sr*y.s+y.sr,x.s*y.s};}
inline void build(int p,int l,int r)
{
    if(l==r) return t[p]={1,1,1},void();
    build(ls,l,mid);build(rs,mid+1,r);t[p]=merge(t[ls],t[rs]);
}
inline void modify(int p,int l,int r,int x)
{
    if(l==r) return t[p]={0.5,0.5,0.5},void();
    if(mid>=x) modify(ls,l,mid,x);
    else modify(rs,mid+1,r,x);t[p]=merge(t[ls],t[rs]);
}
inline node query(int p,int l,int r,int s,int e)
{
    if(l>=s&&r<=e) return t[p];
    if(s>mid) return query(rs,mid+1,r,s,e);
    if(e<=mid) return query(ls,l,mid,s,e);
    return merge(query(ls,l,mid,s,mid),query(rs,mid+1,r,mid+1,e));
}
inline void solve()
{
    n=read();for(int i=1;i<=n;i++) a[i]=read(),id[i]=i;
    sort(id+1,id+1+n,cmp);build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        auto sl=query(1,1,n,1,id[i]),sr=query(1,1,n,id[i],n);
        ans+=sl.sr*sr.sl*0.5*a[id[i]];modify(1,1,n,id[i]);
    }printf("%.9lf",ans/n/n);
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

