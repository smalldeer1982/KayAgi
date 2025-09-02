# [USACO12OPEN] Bookshelf G

## 题目描述

When Farmer John isn't milking cows, stacking haybales, lining up his cows, or building fences, he enjoys sitting down with a good book.  Over the years, he has collected N books (1 <= N <= 100,000), and he wants to build a new set of bookshelves to hold them all.

Each book i has a width W(i) and height H(i).  The books need to be added to a set of shelves in order; for example, the first shelf should contain books 1...k for some k, the second shelf should start with book k+1, and so on.  Each shelf can have a total width of at most L (1 <= L <= 1,000,000,000).  The height of a shelf is equal to the height of the tallest book on that shelf, and the height of the entire set of bookshelves is the sum of the heights of all the individual shelves, since they are all stacked vertically.

Please help FJ compute the minimum possible height for the entire set of bookshelves.

## 样例 #1

### 输入

```
5 10
5 7
9 2
8 5
13 2
3 8```

### 输出

```
21```

# 题解

## 作者：chdy (赞：27)

这道题题意还是很明确的~~我是看着splay刷的没想到是dp。~~

首先题目中很详细的说书要一本一本放，这便为我们的动态规划划分好了阶段了，显然一个状态是 f[i]表示前i本书放到了若干个书架上的高度最小总和。

    f[i]=min{f[j]+cost[j+1][i]} 

    其中j∈flag-1~i-1 cost[j+1][i]=MAX{b[j+1]~b[i]};

-    发现这个东西需要枚举决策j 复杂度是n^2的考虑优化，但是显然我们感觉不太好优化，我们仔细看这个方程可以发现 对于 k<=j f[k]<=f[j] 这说明了 是具有单调性的。

- 然后对于每一个b来说都有一个控制区间在此区间内最左端的端点是最优的，单调队列存储一下这个b单调递减的区间然后 每次状态转移用当前区间的左端点+下个区间的b来更新即可。

- 少了一点是对于第一个决策点我们其实还有一个隐藏的决策点 就是flag-1+第一个决策点。注意好这些就是可以在不开o2的情况下得到95分。

```cpp
// luogu-judger-enable-o2
#include<iostream>
#include<queue>
#include<iomanip>
#include<cctype>
#include<cstdio>
#include<deque>
#include<utility>
#include<cmath>
#include<ctime>
#include<cstring>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<stack>
#include<map>
#include<set>
#include<bitset>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)>(y)?(y):(x))
#define INF 1000000000
#define ll long long
#define l(x) t[x].l
#define r(x) t[x].r
#define sum(x) t[x].sum
#define v(x) t[x].v
using namespace std;
char buf[1<<15],*fs,*ft;
inline char getc()
{
    return (fs==ft&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),fs==ft))?0:*fs++;
}
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void put(ll x)
{
    x<0?putchar('-'),x=-x:0;
    ll num=0;char ch[50];
    while(x)ch[++num]=x%10+'0',x/=10;
    num==0?putchar('0'):0;
    while(num)putchar(ch[num--]);
    putchar('\n');return;
}
const ll MAXN=100010;
ll n,m,maxx,cnt,flag;
ll a[MAXN],b[MAXN];
ll f[MAXN];//f[i]表示前i本书放入若干个书架的最小花费。
ll q[MAXN],l,r;
int main()
{
    //freopen("1.in","r",stdin);
    n=read();m=read();
    for(ll i=1;i<=n;++i)b[i]=read(),a[i]=read();
    memset(f,0x3f3f3f3f,sizeof(f));
    f[0]=0;flag=1;q[++r]=0;++l;
    for(ll i=1;i<=n;++i)
    {
        cnt+=a[i];
        while(cnt>m)++flag,cnt-=a[flag-1];
        while(l<=r&&q[l]<flag)++l;
        while(l<=r&&b[q[r]]<=b[i])--r;
        q[++r]=i;
        for(ll j=l;j<r;++j)f[i]=min(f[i],f[q[j]]+b[q[j+1]]);
        f[i]=min(f[i],f[flag-1]+b[q[l]]);
    }
    put(f[n]);
    return 0;
}

```
当然尽量要不开o2尽管这种优化看起来非常短非常好但是不够优秀。

考虑线段树优化 线段树上存在每一个点包含当前f值对于每一个b我们将其暴力区间覆盖。

然后查询区间最小值也就是最优决策即可。注意暴力覆盖的时候考虑时间复杂度有点高，采取两个优化线段树中存一个s h 一个高度取最大一个高度取最小，如果最小高度>=b直接跳过，如果当前最大高度<=b则懒标记直接区间覆盖即可。

- 复杂度的证明：对于一个值各不相同的区间第一次肯定是暴力覆盖 然后变成了一个单调递减的 这样的话下一次修改一部分是直接区间覆盖了，一部分是跳过了跳过了。然后均摊复杂度仍为nlogn.很完美的解决了这种类型的dp优化。

- 当然还有set优化不过很不好写（~~我上次写set优化真的难受死了~~那就分享两种优化方法好了~

-     segmenttree：

```cpp
#include<iostream>
#include<queue>
#include<iomanip>
#include<cctype>
#include<cstdio>
#include<deque>
#include<utility>
#include<cmath>
#include<ctime>
#include<cstring>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<stack>
#include<map>
#include<set>
#include<bitset>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)>(y)?(y):(x))
#define INF 10000000000000ll
#define ll long long
#define l(x) t[x].l
#define r(x) t[x].r
#define sum(x) t[x].sum
#define s(x) t[x].s
#define h(x) t[x].h
#define tag(x) t[x].tag
#define g(x) t[x].g
using namespace std;
char buf[1<<15],*fs,*ft;
inline char getc()
{
    return (fs==ft&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),fs==ft))?0:*fs++;
}
inline int read()
{
    int x=0,f=1;char ch=getc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
    return x*f;
}
inline void put(ll x)
{
    x<0?putchar('-'),x=-x:0;
    int num=0;char ch[50];
    while(x)ch[++num]=x%10+'0',x/=10;
    num==0?putchar('0'):0;
    while(num)putchar(ch[num--]);
    putchar('\n');return;
}
const int MAXN=100010;
int n,m,flag;
int a[MAXN],b[MAXN];
ll f[MAXN],maxx,cnt;//f[i]表示前i本书放入若干个书架的最小花费。
inline ll min1(ll x,ll y){return x>y?y:x;}
inline ll max1(ll x,ll y){return x>y?x:y;}
struct wy
{
    int l,r;
    ll sum,g;
    ll h,s;
    int tag;
}t[MAXN<<2];
inline void build(int p,int l,int r)
{
    l(p)=l;r(p)=r;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    return;
}
inline void pushdown(int p)
{
    tag(p<<1)=tag(p<<1|1)=tag(p);
    s(p<<1)=s(p<<1|1)=h(p<<1)=h(p<<1|1)=tag(p);
    sum(p<<1)=g(p<<1)+tag(p);
    sum(p<<1|1)=g(p<<1|1)+tag(p);
    tag(p)=0;return;
}
inline void change(int p,int l,int r,int x)
{
    if(h(p)>=x)return;
    if(l<=l(p)&&r>=r(p))
        if(s(p)<=x)
        {
            tag(p)=x;s(p)=h(p)=x;
            sum(p)=h(p)+g(p);
            return;
        }
    if(tag(p))pushdown(p);
    int mid=(l(p)+r(p))>>1;
    if(l<=mid)change(p<<1,l,r,x);
    if(r>mid)change(p<<1|1,l,r,x);
    s(p)=max(s(p<<1),s(p<<1|1));
    h(p)=min(h(p<<1),h(p<<1|1));
    g(p)=min(g(p<<1),g(p<<1|1));
    sum(p)=min(sum(p<<1),sum(p<<1|1));
}
inline ll ask(int p,int l,int r)
{
    if(l<=l(p)&&r>=r(p))return sum(p);
    int mid=(l(p)+r(p))>>1;
    ll cnt=INF;
    if(tag(p))pushdown(p);
    if(l<=mid)cnt=min1(cnt,ask(p<<1,l,r));
    if(r>mid)cnt=min1(cnt,ask(p<<1|1,l,r));
    s(p)=max(s(p<<1),s(p<<1|1));
    h(p)=min(h(p<<1),h(p<<1|1));
    sum(p)=min(sum(p<<1),sum(p<<1|1));
    g(p)=min(g(p<<1),g(p<<1|1));
    return cnt;
}
inline void insert(int p,int x)
{
    if(l(p)==r(p)){g(p)=f[x];return;}
    int mid=(l(p)+r(p))>>1;
    if(tag(p))pushdown(p);
    if(x<=mid)insert(p<<1,x);
    else insert(p<<1|1,x);
    g(p)=min(g(p<<1),g(p<<1|1));
}
int main()
{
    //freopen("1.in","r",stdin);
    n=read();m=read();
    for(int i=1;i<=n;++i)b[i]=read(),a[i]=read();
    build(1,0,n);f[0]=0;flag=1;
    for(int i=1;i<=n;++i)
    {
        cnt+=a[i];
        while(cnt>m)++flag,cnt-=a[flag-1];
        change(1,flag-1,i-1,b[i]);
        f[i]=ask(1,flag-1,i-1);
        //cout<<f[i]<<' ';
        if(i!=n)insert(1,i);
    }
    put(f[n]);
    return 0;
}
```
完工~

---

## 作者：Owen_codeisking (赞：19)

有神仙钦定我写一篇题解，我写一篇好了。

~~自己都忘了怎么做了~~

先从一个 naive 的 $O(n^2)$ dp 开始讲起。

$f_i$ 表示第 $i$ 本书结尾时高度和的最小值。

$$f_i=\min(f_j+\max(h_{j+1},...,h_i))(w_{j+1}+...+w_i\leq L)$$

$w$ 这个限制我们可以通过**二分**得到。

现在我们把问题转化成：

$$f_i=\min(f_j+\max(h_{j+1},...,h_i))(pos_i\leq j)$$

其中 $pos_i$ 为第 $i$ 个位置的**最左端点**。

那么，这道题就成为一道非常套路的线段树优化 dp 了。

相信大家用线段树维护下面的操作都会吧：

- 1. 区间赋值

- 2. 区间取 $\min$

- 3. 单点修改

首先，我们先开一个单调栈，对于每个位置找出第一个大于 $h_i$ 的位置 $l$，并将 $[l+1,i]$ 这段区间内的 $h$ 赋为 $h_i$。

我们发现每一个位置的 $f$ 是确定的，我们每次只需区间修改 $h$ 的值，然后维护 $f+h$ 和 $f$ 的最小值。

查询就直接在一段区间上查就行了。

顺便一提，这题因为 $L$ 是给定的，所以可以用单调队列。如果每个位置的 $L_i$ 是不固定的，这道题就只能用 $\log$ 数据结构了。

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
const int maxn=100000+10;
const ll inf=1e18;
int n,L,w[maxn],h[maxn],pre[maxn],sta[maxn],top;ll sum[maxn],f[maxn],Min[maxn<<2],val[maxn<<2],tag[maxn<<2];
// Min 为 f + h 的最小值
// val 为 f 的最小值

inline int read()
{
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}

inline void pushup(int rt)
{
	Min[rt]=min(Min[lson],Min[rson]);
	val[rt]=min(val[lson],val[rson]);
}

inline void pushdown(int rt)
{
	if(tag[rt]!=inf)
	{
		Min[lson]=val[lson]+tag[rt];
		Min[rson]=val[rson]+tag[rt];
		tag[lson]=tag[rson]=tag[rt];tag[rt]=inf;
	}
}

void build(int l,int r,int rt)
{
	Min[rt]=val[rt]=tag[rt]=inf;
	if(l == r) return ;
	int mid=(l+r)>>1;
	build(l,mid,lson);build(mid+1,r,rson);
}

void update(int L,int R,int C,int l,int r,int rt)
{
	if(L <= l && r <= R)
	{
		Min[rt]=val[rt]+C;tag[rt]=C;
		return ;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(L <= mid) update(L,R,C,l,mid,lson);
	if(R > mid) update(L,R,C,mid+1,r,rson);
	pushup(rt);
}

void modify(int x,int l,int r,int rt)
{
	if(l == r)
	{
		Min[rt]=inf;val[rt]=f[l-1];
		return ;
	}
	pushdown(rt);
	int mid=(l+r)>>1;
	if(x <= mid) modify(x,l,mid,lson);
	else modify(x,mid+1,r,rson);
	pushup(rt);
}

ll query(int L,int R,int l,int r,int rt)
{
	if(L <= l && r <= R) return Min[rt];
	pushdown(rt);
	int mid=(l+r)>>1;ll ans=inf;
	if(L <= mid) ans=min(ans,query(L,R,l,mid,lson));
	if(R > mid) ans=min(ans,query(L,R,mid+1,r,rson));
	return ans;
}

int main()
{
	n=read(),L=read();
	for(int i=1;i<=n;i++)
	{
		h[i]=read(),w[i]=read();
		sum[i]=sum[i-1]+w[i];
	}
	sta[++top]=1;
	for(int i=2;i<=n;i++)
	{
		while(top&&h[i]>h[sta[top]]) top--;
		if(top) pre[i]=sta[top];
		sta[++top]=i;
	}
	build(1,n,1);
	for(int i=1;i<=n;i++)
	{
		modify(i,1,n,1);//初始化决策点
		if(pre[i]+1<=i) update(pre[i]+1,i,h[i],1,n,1);// 区间赋值
		int l=lower_bound(sum,sum+i+1,sum[i]-L)-sum;//二分左端点
		if(l<i) f[i]=query(l+1,i,1,n,1);//区间查询
	}
	printf("%lld\n",f[n]);
	return 0;
}
```

---

## 作者：巨型方块 (赞：13)

首先这道题目的最基本的n^2dp要会

那么之后就有2种做法

###线段树

首先这道题目的暴力dp那是显然的

f[i]可以从f[j-1]+max(h[j]……h[i])推得

不难发现无论是f[]还是当j确定的max(h[j]……h[i])，都是单调的；

那么我们大力线段树；

对于一个新加入的i点

简单来说就是维护h[j]=max(h[j]……h[i])，顺便吧答案维护了;

然后单调队列获得一段答案的可行区间last~i

那么在这段区间里取答案；

最后把答案放到f[i+1]

换句话说一开始的f[1]是0

这样的话每一个叶子节点的答案刚刚好就是f[j]+h[j]


```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const int N=1e5+5;
struct tree{int l,r,h,H,lazy;Ll f,v;}T[N*4];
int q[N],last;
int n,L,x,y;
Ll sum,ans;
void make(int id,int l,int r){
    T[id].l=l;T[id].r=r;
    if(l==r)return;
    int mid=l+r>>1;
    make(id*2  ,l,mid  );
    make(id*2+1,mid+1,r);
}
void push(int id){
    if(T[id].lazy==0||T[id].l==T[id].r)return;
    int x=id*2,y=x+1;
    T[x].H=T[x].h=T[y].H=T[y].h=T[x].lazy=T[y].lazy=T[id].lazy;
    T[x].v=T[x].f+T[x].H;T[y].v=T[y].f+T[y].H;T[id].lazy=0;
}
void change(int id,int l,int r,int x){
    push(id);
    if(l<=T[id].l&&T[id].r<=r){
        if(T[id].H<x){
            T[id].H=T[id].h=T[id].lazy=x;
            T[id].v=T[id].f+x;
        }else{
            if(T[id*2  ].h<x)change(id*2  ,l,r,x);
            if(T[id*2+1].h<x)change(id*2+1,l,r,x);
            T[id].H=max(T[id*2].H,T[id*2+1].H);
            T[id].h=min(T[id*2].h,T[id*2+1].h);
            T[id].v=min(T[id*2].v,T[id*2+1].v);
        }return;
    }
    if(T[id*2  ].r>=l)change(id*2  ,l,r,x);
    if(T[id*2+1].l<=r)change(id*2+1,l,r,x);   
    T[id].H=max(T[id*2].H,T[id*2+1].H);
    T[id].h=min(T[id*2].h,T[id*2+1].h);
    T[id].v=min(T[id*2].v,T[id*2+1].v);
}
Ll out(int id,int l,int r){
    push(id);
    if(l<=T[id].l&&T[id].r<=r){
//        if(l==4&&r==5)cout<<id<<' '<<T[id].h<<endl;
        return T[id].v;
    }
    Ll ans=1e18;
    if(T[id*2  ].r>=l)ans=min(ans,out(id*2  ,l,r));
    if(T[id*2+1].l<=r)ans=min(ans,out(id*2+1,l,r));
    return ans;
}
void add(int id,int x,Ll f){
    push(id);
    if(T[id].l==T[id].r){T[id].f=f;return;}
    if(T[id*2].r>=x)add(id*2,x,f);else add(id*2+1,x,f);
    T[id].f=min(T[id*2].f,T[id*2+1].f);
}
int main()
{
    scanf("%d%d",&n,&L);
    last=1;
    make(1,1,n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&x,&q[i]);
        sum+=q[i];
        while(sum>L)sum-=q[last++];
        change(1,1,i,x);
        ans=out(1,last,i);
        if(i!=n)add(1,i+1,ans);
    }printf("%lld",ans);
}
```
###单调队列

单调队列调出来了哈哈；

感觉单调队列并没有数据结构那么暴力那么好打；

这种做法完全依赖于这道题目的单调性；

首先先说几点

我的写法貌似并不是很快，而且在不开O2的情况下是比线段树还要慢点；

开了o2就是很快的啦；

然后对于这个set我每进进行一次插入删除，那么就需要一个log的时间，我的程序是带有很大的常数的，但感觉也是基本的一种做法；


对于基本的n^2的dp我就不在赘述了；

那么我们对于每一个读入i

首先就是需要确定可向左边扩展的最远点last

然后根据h[i]去更新这段区间里的h[j]；

然后把last~i这段区间的答案全放到一个set里面去

最后去一个最小值产生一个新的f[i]；

于是我开了一个队列q

代表现在last~i这段区间里，高度为h[j]最靠前的下标

因为当i确定的时候，h[j]>=h[j+1]

并且h[j]有很多相同的，那么我们要把h[j]合并起来

那么我们对于一个i，先把i放到q里面，然后不断找h[q[top]]<=h[i]把他弹出

之后再把h[j]<=h[i]的最靠前的重新插入，这样的话我们就可以维护关于h[j]了

然后我们考虑如何删除到不了的点，就是更新last值

首先我们判断当前的点是否在q里面，如果在的话就从队首弹出，不在的话，我们把h[j]跟新为h[j-1]

为什么呢，因为我们维护h[j]相同的一块的时候我们只是更新了h[j]值相同的最前面的一点，并且把这个点放到了q里面，那么之后的点的h[j]值其实就是h[j-1]，

最后我们要看看现在的last值是不是在队列里面，如果不在的话要从队首压入；

如果没听懂那么很抱歉，我的语文水平貌似太差了

其实就是找到单调性的h[j]规律而已

至于那个in[j]就代表j有没有在q里面


```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const Ll N=1e5+5;
Ll h[N],w[N],f[N],q[N],top;
bool in[N];
multiset<Ll>S;
Ll n,m,last,sum,l;
int main()
{
    scanf("%lld%lld",&n,&m);
    l=last=1;in[1]=1;
    for(Ll i=1;i<=n;i++){
        scanf("%lld%lld",&h[i],&w[i]);
        sum+=w[i];
        while(sum>m){
            if(in[last])S.erase(f[last-1]+h[last]),l++;else h[last]=h[last-1];
            in[last]=0;sum-=w[last++];    
        }
        if(!in[last]){
            in[last]=1;q[--l]=last;h[last]=h[last-1];
            S.insert(f[last-1]+h[last]);
        }
        q[++top]=i;S.insert(f[i-1]+h[i]);in[i]=1;
        while(top>=l&&h[q[top]]<=h[i]){
            in[q[top]]=0;
            S.erase(f[q[top]-1]+h[q[top]]);
            top--;        
        }
        in[q[++top]]=1;
        h[q[top]]=h[i];
        S.insert(f[q[top]-1]+h[q[top]]);
        f[i]=*S.begin();
    }
    printf("%lld",f[n]);
}
```

---

## 作者：GKxx (赞：10)

调了一下午，写篇题解庆祝一下

本蒟蒻还从未做过这种 dp 的优化

首先可以想到一个简单的 dp ：直接设 $dp(i)$ 表示前 $i$ 本书的最小高度和，转移的时候考虑在前 $j$ 本书的基础上，把第 $j+1$ 到第 $i$ 本书放到新的一层，于是

$$
dp(i) = \min\left\{dp(j) + \max_{k=j+1}^i\{h_k\}\mid s_i-s_j\leq L\right\}
$$

其中 $s_i$ 为 $w$ 数组的前缀和，这是为了满足宽度要求

这个 dp 是 $O\left(n^2\right)$ 的：

```cpp
void force() {
  dp[1] = h[1];
  for (int i = 2; i <= n; ++i) {
    dp[i] = inf;
    int mv = 0;
    for (int j = i - 1; j >= 0; --j) {
      if (s[i] - s[j] > L)
        break;
      if (h[j + 1] > mv)
        mv = h[j + 1];
      if (dp[j] + mv < dp[i])
        dp[i] = dp[j] + mv;
    }
  }
}
```

考虑对它进行优化。

首先我们发现， $mv_i(j)=\max_{k=j+1}^i\{h[k]\}$ 有一个特点：当 $j$ 递减的时候， $mv$ 的值是一段一段变化的。

如果记 $i$ 左侧第一个满足 $h_j>h_i$ 的 $j$ 为 $lft(i)$ ，我们发现 $\forall j\in[lft(i)+1,i]$ 都有 $mv_i(j)=h_i$。

基于这个性质再考察 dp 的决策：

当 $j,j+1\in[lft(i)+1,i]$ 时，两个决策分别为

- $dp(j)+mv_i(j)$
- $dp(j+1)+mv_i(j+1)$

而 $mv_i(j)=mv_i(j+1)$ ，又显然 $dp$ 值是非递减的，因此从 $j$ 转移一定比从 $j+1$ 转移更优。

所以对于一个给定的 $i$ ，它可能的最优决策点是这样的：

![luogu](https://cdn.luogu.com.cn/upload/pic/42630.png)

其中每个红点是可能的最优决策点。这里我们用 $lb$ 表示满足 $s_i-s_j\leq L$ 的最小的 $j$ ，这个可以二分得到（当然你也可以尺取，但并不会对复杂度带来什么优化）。在 $lb$ 左侧的那个红点是非法的，下面会提到如何处理。

考虑我们如何得到每个 $i$ 的 $lft$ 值，可以维护一个单调栈，保证里面的元素从下往上是递减的。对于一个 $i$ ，如果栈顶元素 $\leq h_i$ 就弹出，这样之后栈顶元素就是 $i$ 左边第一个大于 $h_i$ 的值了，记录一下之后再把第 $i$ 个元素加入栈顶。（实际操作时栈里通常保存下标而不是真实值）

```cpp
while (top && h[s[top]] <= h[i])
  --top;
s[++top] = i;
```

可以发现，在这个过程中，单调栈里的元素就恰到对应上图中的每个红点的左边一个位置。

也就是说我们用单调栈就已经把所有可能的最优决策点放进了连续的序列里，我们只要用一个线段树来维护单调栈中每一个决策的表达式，维护其最小值即可。

所以我们需要一个支持单点修改、区间查最小值的线段树，我写了简单好写常数小的 zkw 线段树。

对于每一个 $i$ ，我们可以二分来得出在 $lb$ 右侧的第一个决策点在单调栈中的位置，然后直接从线段树上读答案。但是还有一种情况， $lb$ 处可能也是一个决策，所以我们还需要二分找到 $lb$ 的具体位置，然后读取它的答案。

```cpp
int l = 1, r = top, pos = 0;
while (l <= r) {
  int mid = (l + r) / 2;
  if (sw[i] - sw[s[mid]] <= L) {
    pos = mid;
    r = mid - 1;
  } else
    l = mid + 1;
}
int pos2 = std::lower_bound(sw, sw + i + 1, sw[i] - L) - sw;
dp[i] = std::min(query(pos + 1, top), dp[pos2] + h[s[pos]]);
```

同时注意，在单调栈中加入 $i$ 元素的时候不要忘了在线段树上修改：

```cpp
while (top && h[s[top]] <= h[i])
  --top;
s[++top] = i;
modify(top, dp[s[top - 1]] + h[i]);
```

完整代码：

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define dwn(i, a, b) for (int i = (a); i >= (b); --i)
#define erp(i, x) for (int i = head[x]; i; i = next[i])

template <typename T> inline void read(T& t) {
	int f = 0, c = getchar(); t = 0;
	while (!isdigit(c)) f |= c == '-', c = getchar();
	while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
	if (f) t = -t;
}
template <typename T> void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
template <typename T> inline void writeln(T x) {
	write(x); puts("");
}
template <typename T> inline bool chkMin(T& x, const T& y) {
	return y < x ? (x = y, 1) : 0;
}
template <typename T> inline bool chkMax(T& x, const T& y) {
	return x < y ? (x = y, 1) : 0;
}

typedef long long LL;
const int maxn = 1e5 + 207;
const LL inf = 1e16;
LL mv[maxn << 2];
int M;
inline void update(int o) { mv[o] = std::min(mv[o << 1], mv[o << 1 | 1]); }
inline void build(int n) {
	for (M = 1; M < n + 2; M <<= 1);
	rep(i, M + 1, M + n) mv[i] = inf;
	dwn(i, M - 1, 1) update(i);
}
inline void modify(int x, LL nv) { for (mv[x += M] = nv, x >>= 1; x; update(x), x >>= 1); }
inline LL query(int s, int t) {
	LL ans = inf;
	for (--s += M, ++t += M; s ^ t ^ 1; s >>= 1, t >>= 1) {
		if (~s & 1) chkMin(ans, mv[s ^ 1]);
		if (t & 1) chkMin(ans, mv[t ^ 1]);
	}
	return ans;
}

LL h[maxn], w[maxn], sw[maxn], dp[maxn], L;
int s[maxn];
int n, top;

int main() {
	read(n); read(L);
	rep(i, 1, n) {
		read(h[i]); read(w[i]);
		sw[i] = sw[i - 1] + w[i];
	}
	build(n + 1);
	s[top = 1] = 0;
	modify(1, 0);
	rep(i, 1, n) {
		while (top && h[s[top]] <= h[i]) --top;
		s[++top] = i;
		modify(top, dp[s[top - 1]] + h[i]);
		int l = 1, r = top, pos = 0;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (sw[i] - sw[s[mid]] <= L) pos = mid, r = mid - 1;
			else l = mid + 1;
		}
		int pos2 = std::lower_bound(sw, sw + i + 1, sw[i] - L) - sw;
		dp[i] = std::min(query(pos + 1, top), dp[pos2] + h[s[pos]]);
	}
	writeln(dp[n]);
	return 0;
}
```

---

## 作者：nofind (赞：5)

题意:https://www.luogu.org/problem/P1848

有道弱化版：

P1295 [TJOI2011]书架:https://www.luogu.org/problem/P1295

这两道题本质是一样的,上面那道$W[]$和$h[]$是同一个数组,其他没有任何区别

定义$sum[i]=\sum_{i=1}^iW[i]$

设$f[i]$表示放置$1~i$的书的最小代价

$f[i]=min(f[j-1]+max(h[j],h[j+1]...h[i]))(sum[i]-sum[j-1]<=L)$

对于每个i,处理出$h[i]$向左第一个大于它的位置$pre[i]$,这个用单调栈即可

对于$[pre[i]+1,i]$,最大的$h[]$是定值,只需要找到最大的$f[j-1]$即可

以下统称最大的$h[]$为$max$

用一颗线段树维护$[l,r]$中$f[]$的最小值,$max$和$f[]+max$的最小值即可

code:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls(p) (p<<1)
#define rs(p) (p<<1|1)
#define minn(p) (seg[p].minn)
#define val(p) (seg[p].val)
#define tag(p) (seg[p].tag)
const int maxn=100010;
const int inf=1e18;
int n,m,top;
int a[maxn],b[maxn],sum[maxn],pre[maxn],s[maxn],f[maxn];
struct Seg
{
	int minn,val,tag;
}seg[maxn<<2];
inline void up(int p)
{
	minn(p)=min(minn(ls(p)),minn(rs(p)));
	val(p)=min(val(ls(p)),val(rs(p)));
}
inline void down(int p)
{
	if(tag(p)==inf)return;
	minn(ls(p))=val(ls(p))+tag(p);
	minn(rs(p))=val(rs(p))+tag(p);
	tag(ls(p))=tag(rs(p))=tag(p);tag(p)=inf;
}
void build(int p,int l,int r)
{
	if(l==r){minn(p)=val(p)=tag(p)=inf;return;}
	int mid=(l+r)>>1;
	build(ls(p),l,mid);build(rs(p),mid+1,r);
	up(p);
}
void change(int p,int L,int R,int pos)
{
	if(L==R){minn(p)=inf;val(p)=f[pos-1];return;}
	int mid=(L+R)>>1;
	down(p);
	if(pos<=mid)change(ls(p),L,mid,pos);
	else change(rs(p),mid+1,R,pos);
	up(p);
}
void update(int p,int L,int R,int l,int r,int k)
{
	if(L>=l&&R<=r){minn(p)=val(p)+k,tag(p)=k;return;}
	down(p);
	int mid=(L+R)>>1;
	if(l<=mid)update(ls(p),L,mid,l,r,k);
	if(r>mid)update(rs(p),mid+1,R,l,r,k);
	up(p);
}
int query(int p,int L,int R,int l,int r)
{
	if(L>=l&&R<=r)return minn(p);
	down(p);
	int mid=(L+R)>>1,ans=inf;
	if(l<=mid)ans=min(ans,query(ls(p),L,mid,l,r));
	if(r>mid)ans=min(ans,query(rs(p),mid+1,R,l,r));
	return ans;
}
signed main()
{
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i],&b[i]);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+b[i];
	s[++top]=0;a[0]=inf;
	for(int i=1;i<=n;i++)
	{
		while(top&&a[i]>a[s[top]])top--;
		pre[i]=s[top];
		s[++top]=i;	
	}
	build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		change(1,1,n,i);
		update(1,1,n,pre[i]+1,i,a[i]);
		int l=lower_bound(sum,sum+i+1,sum[i]-m)-sum;//找到符合条件的左端点
		if(l<i)f[i]=query(1,1,n,l+1,i);
	}
	printf("%lld",f[n]);
	return 0;
}
```


---

## 作者：qwaszx (赞：5)

这题调起来真是...

---

设$f[i]$表示前$i$个数分成若干段的最小答案，那么容易写出方程

$f[i]=\min\limits_{0\leq j<i,\sum\limits_{k=j+1}^iw[k]\leq L}\{f[j]+\max\limits_{j<k\leq i}h[k]\}$

观察这个方程，注意到当$i$固定时随着$j$的增大$f$单调不降和$\max\limits_{j<k\leq i}h[k]$单调不升.所以如果有两个决策$j_1<j_2$满足$\max\limits_{j_1<k\leq i}h[k]=\max\limits_{j_2<k\leq i}h[k]$那么$j_2$是没有用的.令$j_1=j_2-1$，那么这个条件变成$h[j_2]\leq \max\limits_{j_2<k\leq i}h[k]$并且$\sum\limits_{k=j_2}^i\leq L$.这个东西看起来就非常的单调队列，维护出所有可能的决策点即可.有一些细节可以看代码

但是这样只维护出了所有的决策点，还需要一个数据结构来维护所有决策点中的最优值.用一个支持删除的堆即可完成.

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e6;
struct Node{int id;long long w;bool operator <(const Node &a)const{return w<a.w;}};
struct Heap
{
	Node a[N];int size,pos[N];
	void push(Node x)
	{
		a[++size]=x;pos[x.id]=size;
		for(int o=size;o>1;o>>=1)if(a[o]<a[o>>1])swap(a[o],a[o>>1]),swap(pos[a[o].id],pos[a[o>>1].id]);else return;
	}
	void pop(int x)
	{
		pos[a[size].id]=pos[x],a[pos[x]]=a[size--];
		for(int o=pos[x];o>1;o>>=1)if(a[o]<a[o>>1])swap(a[o],a[o>>1]),swap(pos[a[o].id],pos[a[o>>1].id]);else break;
		for(int o=pos[x],son;(o<<1)<=size;o=son)
		{
			son=(o<<1|1)>size||a[o<<1]<a[o<<1|1]?(o<<1):(o<<1|1);
			if(a[son]<a[o])swap(a[son],a[o]),swap(pos[a[son].id],pos[a[o].id]);else break;
		}
		pos[x]=0;
	}
	Node top(){return a[1];}
}qs;
int q[N],lst[N],n,a[N],w[N];
long long f[N],m;
int main()
{
	scanf("%d%lld",&n,&m);
	long long s=0;
	for(int i=1,j=0;i<=n;i++)
	{
		scanf("%d%d",a+i,w+i);s+=w[i];
		while(s>m)s-=w[++j];
		lst[i]=j;if(lst[i]==i){puts("-1");return 0;}//预处理一个决策左端点
	}
	f[0]=0;q[1]=0;int head=1,tail=0;q[0]=0;
	for(int i=1;i<=n;i++)
	{
		while(q[head]<lst[i]&&head<=tail)qs.pop(q[head++]);
		while(head<=tail&&a[i]>=a[q[tail]])qs.pop(q[tail--]);
        //这一句话是因为单调队列中的决策一定满足i-1时的条件，然后再和这个条件合并
        //再根据之前的条件可以得到队尾元素是它到i中间最大的元素
		if(a[i-1]>a[i])//只有这样i-1才是有价值的决策
		{
			Node t={q[++tail]=i-1,f[i-1]+a[i]};
			qs.push(t);
		}
		else
			if(head<=tail)//这时候队尾元素(不含)到i的最大值可能还是到i-1的，需要在堆中更新一下;其他元素(不含)到i的最大值根据条件应该是其单调队列中的后继
			{
				qs.pop(q[tail]);
				Node t={q[tail],f[q[tail]]+a[i]};qs.push(t);
			}
		f[i]=f[lst[i]];
		if(head>tail)f[i]+=a[i];
		else 
			if(q[head]==lst[i])
				f[i]+=a[head==tail?i:q[head+1]];
			else f[i]+=a[q[head]];//用最前面那个转移一次 注意最大值的判断
		if(head<=tail)f[i]=min(f[i],qs.top().w);//用堆顶转移一次
	}
	cout<<f[n]<<endl;
}
```

这题还是非常好的emmmm

---

## 作者：LoliconAutomaton (赞：5)

Orz风以静心（网易博客）

明明是动规啊……单调队列，multiset维护一下……在此吐槽不开优化的STL的set的速度……机房里居然有神犇写线段树维护，厉害了。

来自风以静心（网易博客）的思路：

预处理w的前缀和s.

首先得到动规方程：f[i]=min{f[j]+max{h[j+1..i]} | s[i]-s[j]<=l}.

直接做是平方的，如何优化呢？

我们发现f[j]不减，且对某个i，max{h[j+1..i]}不增。

考虑维护hmax值相同的段。那么从i-1到i时，用h[i]把前面hmax比它小的段合并掉。

平衡树维护每段最前面的f值，决策时取最小的。


'''





```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
typedef long long LL;
const int maxn = 100010;
int H[maxn], W[maxn], sum[maxn];
LL f[maxn];
multiset<LL> s;
inline char getc(void){
    static char buf[1000000], *p1 = buf, *p2 = buf;
    if(p1 == p2){
        p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin);
        if(p1 == p2) return EOF;
    }
    return *p1++;
}
inline void read(int& x){
    x = 0; int f = 1; char ch = getc();
    for(;!(ch>='0' && ch<='9');ch=getc()) if(ch == '-') f = -1;
    for(;(ch>='0' && ch<='9');x=x*10+ch-'0', ch=getc());
    x *= f;
}
inline void write(LL x){
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int main()
{
    int n, L;
    int ans = 0, head = 1, tail = 0;
    read(n); read(L);
    for(int i=1;i<=n;i++){
        read(H[i]); read(W[i]);
        for(sum[++tail]=i-1;head<tail&&H[i]>H[sum[tail]];--tail)
            s.erase(s.find(f[sum[tail-1]]+H[sum[tail]]));
        s.insert(f[sum[tail]]+H[i]);
        sum[tail+1] = i;
        for(ans+=W[i];ans>L;ans-=W[sum[head]]){
            s.erase(s.find(f[sum[head]]+H[sum[head+1]]));
            if(++sum[head]==sum[head+1])
                ++head;
            else s.insert(f[sum[head]]+H[sum[head+1]]);
        }
        f[i] = *s.begin();
    }
    write(f[n]);
}
'''
```

---

## 作者：方杰123 (赞：4)

## [题面](https://www.luogu.com.cn/problem/P1848)
## 思路
首先DP思路蛮好想的：$f_i=min(f_j+max(h_{j+1},h_i))(sum(w_{j+1},w_i)\le L)$。

### 69pts
$sum(w_{j+1},w_i)$，这个条件是个滑动区间，边做边判断就好了。

$max(h_{j+1},h_i)$，这个max可以用ST表优化。

~~众所周知 $n^2$ 是能过 100000 的。所以我们可以直接暴力更新。~~

~~我承认我有赌的成分。~~
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=101000;
int read(){
	int x=0,f=1;char c=getchar();
	while(c>'9' || c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0' && c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,L,w[N];
int k[N],f[N<<2][18],dp[N];
void build(){
	for(int i=2;i<=n;i++)w[i]+=w[i-1];//前缀和
	for(int i=1;i<=17;i++)for(int j=1;j<=n;j++)f[j][i]=max(f[j][i-1],f[j+(1<<i-1)][i-1]);
	int now=0;for(int i=1;i<=n;i++){if((1<<now+1)<=i)now++;k[i]=now;}
	return;
}//ST表
int q[N<<1],head;
int stquery(int x,int y){return max(f[x][k[y-x+1]],f[y-(1<<k[y-x+1])+1][k[y-x+1]]); }
signed main(){
	n=read(),L=read();
	for(int i=1;i<=n;i++)f[i][0]=read(),w[i]=read();build();
	head=0;memset(dp,0x7f,sizeof(dp));dp[0]=0;
	for(int i=1;i<=n;i++){
		while(w[i]-w[head]>L)head++;//符合条件
		for(int j=head;j<i;j++)dp[i]=min(dp[i],dp[j]+stquery(j+1,i));
	} 
	printf("%lld\n",dp[n]);
	return 0;
} 
```
### 100pts
然后我们开始想，时间复杂度差在这个 ```min``` 上，每次整个区间重新求一次最小值，而区间大部分是重复的，多浪费啊。

那么怎么动态维护这个区间最小值呢？

显然每加入一个数 $i$，前面区间中每个数的 $max(j+1,i-1)$ 就改为了 $max(j+1,i)$。然后聪明的你一定能发现：**这个区间的 $max(j+1,i-1)$，$j$是递增的，区间在不断减小，那么值将是单调递减**。所以每次更新的数一定是靠右的一段区间，而这段区间是什么，我们可以预处理（对于每个 $h_i$，用单调栈预处理出它左边第一个大于等于他的数，在这个数右边，就是他更新的区间）。那么我们用线段树来维护一下吧。

**Q** ：可是我们要的是 $f_j+max(j+1,i)$ 的最小值，只能求出 $max(j+1,i)$ ，你怎么办？  
**A** : 事实上，一段区间的 $max(j+1,i)$ ，被更新成一样的之后，那么 $f_j+max(j+1,i)$ 的值只要看 $f_j$ 的值就行了（$max(j+1,i)$大家都一样），所以你可以用线段树维护一下 $f_j$ 的值。

维护一棵线段树。
1. 一维护 $f_j$ 的值。有一个单点插入操作。
2. 二维护 $f_j+max(j+1,i)$ 的值，那么每次区间修改 $max(j+1,i)$ 的值的时候，用 $f_j$  的值更新它。
3. 具体看代码啦。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=201000;
int read(){
	int x=0,f=1;char c=getchar();
	while(c>'9' || c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0' && c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
struct node{
	int l,r,f,sum,lazy;//分开维护。lazy是这个区间的max(j+1,i) 
}e[N<<2];
int n,w[N],h[N],m,f[N];
int pre[N],st[N],top,L;
void pushup(int u){
	e[u].f=min(e[u<<1].f,e[u<<1|1].f);
	e[u].sum=min(e[u<<1].sum,e[u<<1|1].sum);
	return;
}
void pushdown(int u){
	if(e[u].lazy){
		e[u<<1].lazy=e[u<<1|1].lazy=e[u].lazy;
		e[u<<1].sum=e[u<<1].f+e[u].lazy;
		e[u<<1|1].sum=e[u<<1|1].f+e[u].lazy;
		e[u].lazy=0;
	}
	return;
}
void build(int u,int l,int r){
	e[u].l=l,e[u].r=r;if(l==r)return;
	int mid=l+r>>1;build(u<<1,l,mid);build(u<<1|1,mid+1,r);return;
}
void insert(int u,int x,int val){//插入一个f[i] 
	if(e[u].l==e[u].r){
		e[u].f=e[u].sum=val;
		return;
	}
	pushdown(u);
	int mid=e[u].l+e[u].r>>1;
	if(x<=mid)insert(u<<1,x,val);
	else insert(u<<1|1,x,val);
	pushup(u);
	return;
}
void update(int u,int l,int r,int val){
	if(l<=e[u].l && e[u].r<=r){
		e[u].lazy=val;
		e[u].sum=e[u].f+val;
		return;
	} 
	pushdown(u);
	int mid=e[u].l+e[u].r>>1;
	if(l<=mid)update(u<<1,l,r,val);
	if(r>mid)update(u<<1|1,l,r,val);
	pushup(u);
	return;
}
int query(int u,int l,int r){
	if(l<=e[u].l && e[u].r<=r)return e[u].sum;
	pushdown(u); 
	int mid=e[u].l+e[u].r>>1;
	int res=1e18;
	if(l<=mid)res=min(res,query(u<<1,l,r));
	if(r>mid)res=min(res,query(u<<1|1,l,r));
	return res;
}
signed main(){
	n=read();L=read();
	for(int i=1;i<=n;i++)h[i]=read(),w[i]=read();
	for(int i=2;i<=n;i++)w[i]+=w[i-1];
	for(int i=1;i<=n;i++){
		while(top && h[i]>h[st[top]])top--;
		if(top)pre[i]=st[top];else pre[i]=1;
		st[++top]=i;
	}//单调栈
	build(1,1,n);
	int head=0,nowmaxn=0;
	for(int i=1;i<=n;i++){
		nowmaxn=max(nowmaxn,h[i]);//当只有一段区间的时候，直接用最大值。
		while(w[i]-w[head]>L)head++;
		update(1,pre[i],i-1,h[i]);
		if(head==0){
			f[i]=query(1,head+1,i-1);
			f[i]=min(f[i],nowmaxn);
		}
		else f[i]=query(1,head,i-1);
		insert(1,i,f[i]);
	}
	printf("%lld\n",f[n]);
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：4)

### [双倍经验](https://www.luogu.com.cn/problem/P1295)


### 前置知识
单调队列，`dp`，`ST` 表

### 思路

首先 `dp` 方程是 $dp_i=\min\{dp_j+\max\{h_k\}\},\sum\limits_{k=j}^i w_k \le m,j<k\le i$。

考虑可以转移到 $dp_i$ 的两个状态 $dp_j+\max\{h_{j+1},h_{j+2}...h_i\}$ 和 $dp_{j+1}+\max\{h_{j+2},h_{j+3}...h_i\}$。显然 $dp_{j+1}\ge dp_j$，所以 $dp_{j+1}$ 能优于 $dp_j$ 的情况只有 $\max\{h_{j+2},h_{j+3}...h_i\}<\max\{h_{j+1},h_{j+2}...h_i\}$，所以 $h_{j+1}$ 为 $\max\{h_{j+1},h_{j+2}...h_i\}$ 时才可能取 $dp_{j+1}+\max\{h_{j+2},h_{j+3}...h_i\}$ 。

接下来用单调队列维护一个下降序列，弹出过期下标。我们记 $left_i$ 使 $w_{left_i}+w_{left_i+1}...+w_i\le m$ 且 $w_{left_i-1}+w_{left_i}...+w_i>m$，小于 $left_i$ 的下标可以直接弹出。 $left_i$ 可以用前缀和维护。接下来对每个单调队列中的下标与 ${left_i}$更新，更新中求 $h$ 的区间最大值可以用 `ST` 表容易地维护。

#### Update on 2022-10-3

这里就结束了？不！

感谢 [@Sham_Devour](https://www.luogu.com.cn/user/365542) 的问题，找到了这个做法的错误。

基于随机数列的单调队列期望长度，这个做法在平均情况下是 $\Theta(n\log n)$ 的，但是可以通过构造一个递减的、宽度全为 $1$ 的序列让单调队列长度变成 $\Theta(n)$ 来卡掉这个做法。

这个数据有点太水了……贡献一个数据生成器

```cpp
#include <stdio.h>
#include <stdlib.h>
#define lld long long
inline unsigned int randint() { return (rand() << 16) | rand(); }
inline unsigned lld randlld() { return ((1ll * randint()) << 32) | randint(); }
inline lld random(lld l, lld r) { return randlld() % (r - l + 1) + l; }
int main() {
	int n = 100000;
	printf("%d 1000000000\n", n);
	for (int i = 1; i <= n; ++ i) printf("%lld %lld\n", n - i + 1, 1);
}
```

所以用单调队列维护下降序列之后，每次找到前面第一个比当前点更大的点，用线段树进行区间修改即可。

### 代码

最后贴上代码：
```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define lld long long
using namespace std;
const int N = 100010;
int n, m;
lld w[N], h[N];
lld sum[N];
struct node {
	int l, r;
	lld val, ans, tag;
} tr[N << 2];
inline void pushdown(int k) {
//	printf("pushdown %d\n", k);
	tr[k << 1].tag = tr[k].tag;
	tr[k << 1 | 1].tag = tr[k].tag;
	tr[k].tag = 0;
	tr[k << 1].ans = tr[k << 1].val + tr[k << 1].tag;
	tr[k << 1 | 1].ans = tr[k << 1 | 1].val + tr[k << 1 | 1].tag;
}
inline void pushup(int k) {
	tr[k].val = min(tr[k << 1].val, tr[k << 1 | 1].val);
	tr[k].ans = min(tr[k << 1].ans, tr[k << 1 | 1].ans);
}
inline void build(int k, int l, int r) {
	tr[k].l = l, tr[k].r = r;
	if (l == r) {
		tr[k].ans = 0x3f3f3f3f3f3f3f3fll;
		tr[k].val = 0x3f3f3f3f3f3f3f3fll;
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
inline void modify(int k, int p, lld x) {
	if (tr[k].l == tr[k].r) {
		tr[k].val = x;
		tr[k].ans = x + tr[k].tag;
		return;
	}
	if (tr[k].tag) pushdown(k);
	int mid = (tr[k].l + tr[k].r) >> 1;
	if (p <= mid) modify(k << 1, p, x);
	else modify(k << 1 | 1, p, x);
	pushup(k);
}
inline lld query(int k, int l, int r) {
	if (l <= tr[k].l && tr[k].r <= r) {
//		printf("tr[%d]:%d~%d\n", k, tr[k].l, tr[k].r);
//		printf("tr[%d].tag = %lld\n", k, tr[k].tag);
//		printf("tr[%d].val = %lld\n", k, tr[k].val);
//		printf("tr[%d].ans = %lld\n", k, tr[k].ans);
//		printf("Query %d(%d~%d) %d~%d:%lld\n", k, tr[k].l, tr[k].r, l, r, tr[k].ans);
		return tr[k].ans;
	}
	if (tr[k].tag) pushdown(k);
	int mid = (tr[k].l + tr[k].r) >> 1;
	lld ans = 0x3f3f3f3f3f3f3f3fll;
	if (l <= mid) ans = min(ans, query(k << 1, l, r));
	if (mid < r) ans = min(ans, query(k << 1 | 1, l, r));
	return ans;
}
inline void modify2(int k, int l, int r, lld x) {
	if (l <= tr[k].l && tr[k].r <= r) {
		tr[k].tag = x;
		tr[k].ans = tr[k].val + tr[k].tag;
//		printf("tr[%d]:%d~%d\n", k, tr[k].l, tr[k].r);
//		printf("tr[%d].tag = %lld\n", k, tr[k].tag);
//		printf("tr[%d].val = %lld\n", k, tr[k].val);
//		printf("tr[%d].ans = %lld\n", k, tr[k].ans);
		return;
	}
	if (tr[k].tag) pushdown(k);
	int mid = (tr[k].l + tr[k].r) >> 1;
	if (l <= mid) modify2(k << 1, l, r, x);
	if (mid < r) modify2(k << 1 | 1, l, r, x);
	pushup(k);
//	printf("tr[%d]:%d~%d\n", k, tr[k].l, tr[k].r);
//	printf("tr[%d].tag = %lld\n", k, tr[k].tag);
//	printf("tr[%d].val = %lld\n", k, tr[k].val);
//	printf("tr[%d].ans = %lld\n", k, tr[k].ans);
}
inline int findpre(int x) {
	int l = 0, r = x, ans;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (sum[x] - sum[mid] <= m){
			ans = mid;
			r = mid - 1;
		} else l = mid + 1;
	}
	return ans;
}
int head, tail, q[N << 1];
void push(int x) {
    while (head <= tail && h[q[tail]] < h[x]) -- tail;
	modify2(1, head <= tail ? (q[tail] + 1) : 1, x, h[x]);
    q[++ tail] = x;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i) {
		scanf("%lld%lld", h + i, w + i);
		sum[i] = sum[i - 1] + w[i];
	}
	build(1, 1, n + 1);
	modify(1, 1, 0);
	int mn = 0;
	head = 1, tail = 1;
	q[head] = 0;
	lld res;
	for (int i = 1; i <= n; ++ i) {
		push(i);
		res = query(1, findpre(i) + 1, i);
		modify(1, i + 1, res);
	}
	printf("%lld\n", res);
}```

---

## 作者：18Michael (赞：3)

## 题解

设 $f_i$ 表示前 $i$ 本书满足条件时书架高度和的最小值。

那么对于当前位置 $i$，满足宽度限制的最小位置 $w$ 一定不减，可以用指针维护。

显然有 $f_i=\min\{f_{j-1}+\max\{H_j,\cdots,H_i\}\}(w\le j\le i)$。

我们把原来的 $H_j$ 变为 $H_j\sim H_i$ 的最大值，显然要动态维护 $H_w\sim H_i$ 的值，只需支持对 $H$ 后缀取 $\max$ 操作。

由于 $H$ 的最大值是不增的，所以取 $\max$ 相当于对一段后缀做区间覆盖。

线段树上二分找到当前要取 $\max$ 的分界点，剩下的前缀不会被影响。

我们还需维护区间内 $f_i$ 的 $\min$ 和 $f_i+H_i$ 的 $\min$，以及查询 $w\sim i$ 中最小的 $f_i+H_i$。

这都可以用线段树来维护。时间复杂度 $O(n\log n)$。

## Code
```cpp
#include<cstdio>
#define LL long long
#define inf 0x3f3f3f3f3f3f3f3f
int n,l,w=1,sum=0;
int H[100008],W[100008];
LL f[100008];
struct aaa
{
	LL mnf,mnfh,laz,mnh;
}arr[400008];
inline LL max(LL a,LL b)
{
	return a>b? a:b;
}
inline LL min(LL a,LL b)
{
	return a<b? a:b;
}
inline int lson(int x)
{
	return (x<<1);
}
inline int rson(int x)
{
	return ((x<<1)|1);
}
inline void build(int k,int l,int r)
{
	if(!l)arr[k]=(aaa){0,0,0,0};
	else arr[k]=(aaa){inf,inf,0,0};
	if(l==r)return ;
	int ls=lson(k),rs=rson(k),mid=((l+r)>>1);
	build(ls,l,mid),build(rs,mid+1,r);
}
inline void modifyH(int k,int l,int r,int l1,int r1,LL d)
{
	if(l1>r1)return ;
	if(l>=l1 && r<=r1){arr[k].laz=d,arr[k].mnh=d,arr[k].mnfh=arr[k].mnf+d;return ;}
	if(arr[k].laz)arr[k].mnh=arr[k].laz,arr[k].mnfh=arr[k].mnf+arr[k].mnh;
	int ls=lson(k),rs=rson(k),mid=((l+r)>>1);
	if(arr[k].laz)
	{
		arr[ls].laz=arr[k].laz,arr[ls].mnfh=arr[ls].mnf+arr[ls].laz,arr[ls].mnh=arr[ls].laz;
		arr[rs].laz=arr[k].laz,arr[rs].mnfh=arr[rs].mnf+arr[rs].laz,arr[rs].mnh=arr[rs].laz,arr[k].laz=0;
	}
	if(r1<=mid)modifyH(ls,l,mid,l1,r1,d);
	else if(l1>mid)modifyH(rs,mid+1,r,l1,r1,d);
	else modifyH(ls,l,mid,l1,mid,d),modifyH(rs,mid+1,r,mid+1,r1,d);
	arr[k].mnfh=min(arr[ls].mnfh,arr[rs].mnfh),arr[k].mnh=min(arr[ls].mnh,arr[rs].mnh);
}
inline LL query(int k,int l,int r,int l1,int r1)
{
	if(arr[k].laz)arr[k].mnh=arr[k].laz,arr[k].mnfh=arr[k].mnf+arr[k].mnh;
	if(l>=l1 && r<=r1)return arr[k].mnfh;
	int ls=lson(k),rs=rson(k),mid=((l+r)>>1);
	if(arr[k].laz)
	{
		arr[ls].laz=arr[k].laz,arr[ls].mnfh=arr[ls].mnf+arr[ls].laz,arr[ls].mnh=arr[ls].laz;
		arr[rs].laz=arr[k].laz,arr[rs].mnfh=arr[rs].mnf+arr[rs].laz,arr[rs].mnh=arr[rs].laz,arr[k].laz=0;
	}
	if(r1<=mid)return query(ls,l,mid,l1,r1);
	if(l1>mid)return query(rs,mid+1,r,l1,r1);
	return min(query(ls,l,mid,l1,mid),query(rs,mid+1,r,mid+1,r1));
}
inline void modifyF(int k,int l,int r,int x,LL d)
{
	if(arr[k].laz)arr[k].mnh=arr[k].laz,arr[k].mnfh=arr[k].mnf+arr[k].mnh;
	if(l==r){arr[k].mnf=d,arr[k].mnfh=d+arr[k].mnh;return ;}
	int ls=lson(k),rs=rson(k),mid=((l+r)>>1);
	if(arr[k].laz)
	{
		arr[ls].laz=arr[k].laz,arr[ls].mnfh=arr[ls].mnf+arr[ls].laz,arr[ls].mnh=arr[ls].laz;
		arr[rs].laz=arr[k].laz,arr[rs].mnfh=arr[rs].mnf+arr[rs].laz,arr[rs].mnh=arr[rs].laz,arr[k].laz=0;
	}
	if(x<=mid)modifyF(ls,l,mid,x,d);else modifyF(rs,mid+1,r,x,d);
	arr[k].mnf=min(arr[ls].mnf,arr[rs].mnf),arr[k].mnfh=min(arr[ls].mnfh,arr[rs].mnfh),arr[k].mnh=max(arr[ls].mnh,arr[rs].mnh);
}
inline int find(int k,int l,int r,int l1,int r1,LL d)
{
	if(arr[k].laz)arr[k].mnh=arr[k].laz,arr[k].mnfh=arr[k].mnf+arr[k].mnh;
	if(l==r)return (d>arr[k].mnh? l:n);
	int ls=lson(k),rs=rson(k),mid=((l+r)>>1);
	if(arr[k].laz)
	{
		arr[ls].laz=arr[k].laz,arr[ls].mnfh=arr[ls].mnf+arr[ls].laz,arr[ls].mnh=arr[ls].laz;
		arr[rs].laz=arr[k].laz,arr[rs].mnfh=arr[rs].mnf+arr[rs].laz,arr[rs].mnh=arr[rs].laz,arr[k].laz=0;
	}
	if(r1>mid && d<=max(arr[ls].mnh,arr[ls].laz))return find(rs,mid+1,r,max(mid+1,l1),r1,d);
	return find(ls,l,mid,l1,min(mid,r1),d);
}
int main()
{
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;++i)scanf("%d%d",&H[i],&W[i]);
	build(1,0,n);
	for(int i=1;i<=n;++i)
	{
		for(sum+=W[i];sum>l;++w)sum-=W[w];
		modifyH(1,0,n,find(1,0,n,0,i-1,H[i]),i-1,H[i]),f[i]=query(1,0,n,w-1,i-1),modifyF(1,0,n,i,f[i]);
	}
	printf("%lld",f[n]);
	return 0;
}
```


---

## 作者：Purslane (赞：1)

# Solution

考虑使用动态规划。$dp_x$ 表示前 $x$ 本书进行合法划分最小高度是多少。

转移得到：

$$dp_x=\min_{0 \le i < x ,\sum_{j=i+1}^x w_j \le l} \{dp_i+\max_{j=i+1}^x\{h_j\}\}$$

考虑用双指针维护 $i$ 的下界，并且用单调栈维护相同 $i$ 对应的 $\max_{j=i+1}^x\{h_j\}$。


时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100000+10;
int n,l,tot,pos,pre[MAXN],w[MAXN],h[MAXN],tag[MAXN<<2],mx[MAXN<<2],dp[MAXN];
stack<int> st;
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void push_down(int k,int l,int r) {return tag[lson]+=tag[k],tag[rson]+=tag[k],mx[lson]+=tag[k],mx[rson]+=tag[k],tag[k]=0,void();}
void update(int k,int l,int r,int x,int y,int v) {
	if(x<=l&&r<=y) return tag[k]+=v,mx[k]+=v,void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,v);
	if(y>mid) update(rson,mid+1,r,x,y,v);
	mx[k]=min(mx[lson],mx[rson]);
	return;
}
int query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return mx[k];
	push_down(k,l,r);
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return min(query(lson,l,mid,x,y),query(rson,mid+1,r,x,y));	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>l,h[0]=INT_MAX; st.push(0);
	ffor(i,1,n) cin>>h[i]>>w[i],pre[i]=pre[i-1]+w[i];
	update(1,0,n,0,0,h[1]);
	ffor(i,1,n) {
		while(pre[i]-pre[pos]>l) pos++;
		while(h[i]>h[st.top()]) {
			int u=st.top();
			st.pop();
			update(1,0,n,st.top(),u-1,h[i]-h[u]);
		}
		st.push(i);
		dp[i]=query(1,0,n,pos,i-1),update(1,0,n,i,i,dp[i]+h[i+1]);
	}
	cout<<dp[n];
	return 0;
}
```

---

## 作者：Lagerent (赞：1)

首先考虑暴力 dp。

设 $f_i$ 表示已经安置好 $i$ 本书的最小代价，则不难得到如下状态转移方程。

$$f_i = \min\{f_{j - 1} + \max_{k = j}^{i}\{h_k\}\}, \sum_{k = j}^{i}{w_k} \le L$$

时间复杂度 $O(n ^ 2)$。期望得分 64 pts。

```
f[1] = h[1];
rep(i, 2, n) {
	int res = 0;
	per(j, i - 1, 0) {
		if(s[i] - s[j] > m) break;
		res = max(res, h[j + 1]);
		f[i] = min(f[i], f[j] + res);
	}
}
```

（$s$ 是 $w$ 的前缀和数组。$m$ 即为 $L$。）

考虑优化。

不难发现，对于一个已经确定的 $i$，当 $j$ 单调递增时，$\max_{k = j}^{i}\{h_k\}$ 单调不增，$f_{k - 1}$ 单调不降。当我们枚举到 $i$ 时，$f_{k - 1}$ 已被更新过，即值已经确定，那么我们考虑 $h_i$ 对于答案的影响。

$\forall k \in [j, i] \text{且} h_k \le h_i$，不会对 $\max_{k = j} ^{i}\{h_k\}$ 产生贡献，那么我们记 $pre_i$，使得 $h_{pre_i}$ 是 $i$ 左侧的 $h$ 中第一个大于 $h_i$ 的数。那么 $max_{k = pre_i + 1}^{i} = h_i$。

因此我们需要维护一个数据结构，它需要维护每个位置的 $f$ 和 $f + h_{max}$，支持将 $[pre_i, i]$ 中的 $f + h_{max}$ 修改，和查询一段区间内 $f + h_{max}$ 的最小值，本题解采用线段树，在每个位置 $i$ 维护 $f_{i - 1} $ 和 $f_{i - 1} + h_{max}$ 的最小值。

至于限制条件 $\sum_{k = j}^{i}{w_k} \le L$，可以二分出第一个点 $t$，使得 $s_i - s_t \le L$。

------------

在枚举到每个点 $i$ 时，

- 单点修改，将线段树上第 $i$ 个位置改成 $f_{i - 1}$。
- 更新 $[pre_i, i]$ 的 $f + h_{max}$。
- 二分出第一个满足限制的点 $t$。
- 查询 $[t + 1, i]$ 中 $f + h_{max}$ 的最小值。

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
#define rep(a, b, c) for(int (a) = (b); (a) <= (c); ++ (a))
#define per(a, b, c) for(int (a) = (b); (a) >= (c); -- (a))
using namespace std;

const int N = 1e5 + 10, inf = 1e18;

int n, m;
int f[N], h[N], s[N], stk[N], top, pre[N], w[N];

struct Tree {
	int l, r;
	int f, res, tag;
}tr[N << 2];

void upd(int u) {
	tr[u].f = min(tr[u << 1].f, tr[u << 1 | 1].f);
	tr[u].res = min(tr[u << 1].res, tr[u << 1 | 1].res);
}

void psd(int u) {
	if(tr[u].tag) {
		tr[u << 1].res = tr[u << 1].f + tr[u].tag;
		tr[u << 1 | 1].res = tr[u << 1 | 1].f + tr[u].tag;
		tr[u << 1].tag = tr[u << 1 | 1].tag = tr[u].tag;
		tr[u].tag = 0;
	}
}

void build(int u, int l, int r) {
	tr[u].l = l, tr[u].r = r;
	if(l == r) {
		tr[u].f = tr[u].res = inf;
		tr[u].tag = 0;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
	upd(u);
}

void modify(int u, int pos) {
	if(tr[u].l == tr[u].r) {
		tr[u].res = inf;
		tr[u].f = f[pos - 1];
		return;
	}
	psd(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if(pos <= mid) modify(u << 1, pos);
	else modify(u << 1 | 1, pos);
	upd(u);
}

void modify(int u, int l, int r, int d) {
	if(l <= tr[u].l && r >= tr[u].r) {
		tr[u].res = tr[u].f + d;
		tr[u].tag = d;
		return;
	}
	psd(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if(l <= mid) modify(u << 1, l, r, d);
	if(r > mid) modify(u << 1 | 1, l, r, d);
	upd(u);
}

int query(int u, int l, int r) {
	if(l <= tr[u].l && r >= tr[u].r) return tr[u].res;
	psd(u);
	int mid = tr[u].l + tr[u].r >> 1;
	int res = inf;
	if(l <= mid) res = min(res, query(u << 1, l, r));
	if(r > mid) res = min(res, query(u << 1 | 1, l, r));
	return res;
}

signed main() {
	scanf("%lld%lld", &n, &m);
	rep(i, 1, n) scanf("%lld%lld", &h[i], &w[i]), s[i] = s[i - 1] + w[i];
	stk[ ++ top] = 1;
	rep(i, 2, n) {
		while(top && h[stk[top]] <= h[i]) -- top;
		if(top) pre[i] = stk[top];
		stk[ ++ top] = i;
	}
	build(1, 1, n);
	rep(i, 1, n) {
		modify(1, i);
		modify(1, pre[i] + 1, i, h[i]);
		int l = lower_bound(s, s + i + 1, s[i] - m) - s;
		f[i] = query(1, l + 1, i);
	}
	printf("%lld\n", f[n]);
	return 0;
}
```

后记：[双倍经验](https://www.luogu.com.cn/problem/P1295)。

作者学习时参考了[这篇题解](https://www.luogu.com.cn/blog/luckyblock/solution-p1295)。

---

## 作者：Stinger (赞：1)

调了两个下午+一个晚上，水篇题解是当然的事情。反正这道题对于我这种蒟蒻也是道神题，~~自己都很惊讶于为什么不看题解能做出来~~

# $\texttt{Description}$

> 有 $n$ 个数对 $(h_i,w_i)$，要求将这些数对分成任意个连续的段，要求每段 $w_i$ 之和均不超过 $L$，每段的花费为该段中 $h_i$ 的最大值，请输出最小的花费。

# $\texttt{Solution}$

首先看完题就应该想到 $O(n^2)$ 的暴力，$dp_i$ 表示划分了前 $i$ 个数对的最小花费，则 $dp_i=min^{j<n}_{j=lim_i}dp_j+mx_{j+1,i}$。 $lim_i$ 表示满足 $\sum\limits^{j\le i}_{j=0}\le L$ 的最小 $j$ 加上 $1$。$mx_{l,r}$ 表示 $max^{i\le r}_{i=l}h_i$，可以打个st表算，$lim$ 可以前缀和+二分。

然而这题 $n\le 10^5$ 的数据范围是不是太小了亿点，保不准哪天就被奇奇怪怪的暴力艹了（

优化？对于这道题，不难发现 $i$ 增加 $1$ 后，有的 $mx_{j,i}$ 不会变，有的会变。哪些会变呢？设 $left_i$ 表示 $i$ 前面第一个 $h$ 值大于等于 $i$ 的位置 $j$，不难发现 $mx_{left_i+1,i},mx_{left_i+2,i},mx_{left_i+3,i}...mx_{i,i}$ 相对于 $mx_{left_i+1,i-1},mx_{left_i+2,i-1},mx_{left_i+3,i-1}...mx_{i,i-1}$ 会变为 $h_i$。也就是说，$[left_i+1,i]$ 这段区间的 $mx$ 值会变化为一个定值。好像可以用线段树维护，但因为我们要维护的是 $dp_j+mx_{j,i}$ 的最大值，而不是两者任意一个的最大值，无法简单地使用线段树维护~~不然你觉得这题为什么会紫。~~

注意到 dp 数组单调不降，因此 $[left_i+1,i]$ 区间的 $mx$ 变一样了，意味着我们只需要考虑 $left_i+1$ 这个 dp 值最小的点。至于如果 $left_i+1<lim_i$ 怎么办，单独考虑 $lim_i$ 这个决策点即可。

直接把这些可能最优的决策点放到一个数据结构中。注意，如果之前 $[left_j+1,j]$ 区间的 $mx$ 值产生变化，而现在 $[left_i+1,i]$ 的 $mx$ 值又有变化，且满足 $left_i\leq left_j$，**直接舍弃 $left_j+1$ 这个决策点**。这意味着我们可以方便地使用单调栈维护可能的最优决策点。至于为什么呢？由于我们按照 $1...n$ 的顺序递推 dp 数组，因此一定存在 $j\le i$，那么 $left_i\le left_j$，不就意味着 $[left_j+1,j]$ 这段区间被**完全包含**，$left_j+1$ 也不再是 $mx$ 相同的一个连续段里下标最小的了吗？

每次弹栈，进栈时，用一颗线段树维护这些最优决策点的值。取 $[lim_i,i]$ 中的最优决策点值最小的，再单独考虑 $lim_i$ 这个决策点。如果你看懂了的话，会发现这道题就做完了。

# $\texttt{Code}$

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#define int long long
#define N 100005

const int INF = 1000000000000000000LL;
inline int min(const int x, const int y) {return x < y ? x : y;}
inline int max(const int x, const int y) {return x > y ? x : y;}
int w[N], h[N], lim[N], dp[N], lft[N], sub[N], s[N << 1], st[N][17], top;

struct Node {
	int l, r, v;
} c[N << 2];
void make_tree(const int O, const int L, const int R) {
	c[O].l = L, c[O].r = R, c[O].v = INF;
	if (L != R) {
		make_tree(O << 1, L, L + R >> 1);
		make_tree(O << 1 | 1, (L + R >> 1) + 1, R);
	}
}
void update(const int O, const int x, const int d) {
	if (c[O].l == c[O].r) {c[O].v = d; return;}
	int mid(c[O].l + c[O].r >> 1);
	if (x <= mid) update(O << 1, x, d);
	else update(O << 1 | 1, x, d);
	c[O].v = min(c[O << 1].v, c[O << 1 | 1].v);
}
int query(const int O, const int L, const int R) {
	if (L <= c[O].l && c[O].r <= R) return c[O].v;
	int mid(c[O].l + c[O].r >> 1), ans(INF);
	if (L <= mid) ans = query(O << 1, L, R);
	if (mid < R) ans = min(ans, query(O << 1 | 1, L, R));
	return ans;
}
inline int query(int L, int R) {
	int k(log2(R - L + 1));
	return max(st[L][k], st[R - (1 << k) + 1][k]);
}

signed main() {
	int n, L;
	scanf("%lld%lld", &n, &L);
	for (int i(1); i <= n; ++ i)
		scanf("%lld%lld", h + i, w + i), sub[i] = sub[i - 1] + w[i];
	for (int i(1); i <= n; ++ i) st[i][0] = h[i];
	for (int i(n); i >= 1; -- i)
	for (int j(1); i + (1 << j - 1) <= n; ++ j)
		st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
	for (int i(n); i; -- i) {
		while (top && h[s[top]] < h[i]) lft[s[top --]] = i;
		s[++ top] = i;
	}
	top = 0;
	for (int i(1); i <= n; ++ i)
		lim[i] = std::lower_bound(sub, sub + n + 1, sub[i] - L) - sub;
	make_tree(1, 0, n);
	for (int i(1); i <= n; ++ i) {
		while (top && lft[i] < s[top]) update(1, s[top --], INF);
		s[++ top] = lft[i], update(1, lft[i], dp[lft[i]] + h[i]);
		dp[i] = min(query(1, lim[i], i), dp[lim[i]] + query(lim[i] + 1, i));
	}
	printf("%lld", dp[n]);
	return 0;
}
```

# $\texttt{Summary}$

神题写一下解题总结还是有用的。

这种题核心在于优化 DP。单调队列/单调栈是最常见的数据结构优化 dp 的手段。线段树/树状数组/平衡树等其它数据结构也可能会用到。

所以需要充分挖掘题目的单调性。而且，对于 DP 和各种数据结构而言，**连续性**个人感觉是非常重要的一点。比如线段树，如果要修改的集合是一些零散的位置就很难高效地修改，反之，如果修改的集合是连续地区间就会容易很多。dp 也是，这道题规定了分出的段必须对于原来的位置是连续的，因此才可以定出这样的状态。不然如果转移顺序不明，可能就需要状压了。

---

## 作者：will5438 (赞：1)

emmm 这个题目肛了一个晚自修写出来（不包括思考过程）
主要思路楼上讲的很清楚吧，所以我就随便讲讲

简单的dp方程还是比较好想的但是n方的时间显然过不了
### f[i]=min(f[j]+max(h[i]....h[j])) sum[i..j]<=L
于是考虑优化以下分好几个点

------------
### 考虑到max(h[i])是一段段变化的可以合并且 f 单调不减因此只需考虑h[i]变化的点，即决策点 故有两种维护方法
#### 1.单调栈+二分位置
#### 2.对当前i位置的单调队列（保留最开始元素即head<tail不取等）
反正各有所爱吧，~~个人喜欢单调队列一点~~

### 然后在max(h[i]) 维护好的前提下f 的 dp只要考虑决策点且满足单调性
#### 1.数据结构 线段树（支持单点修改）~~暴力~~塞入决策点数据
#### 2.STL multiset 也是维护最小值取*begin（同样暴力塞进去）
#### 3.heap 小根堆（反正就是维护最小值嘛）差不多其实不过快一些，好像楼上都没讲到
#### 4.然后翻了一下看到还有一个方法就是写priority_queue看到一个神仙跑得飞快不吸氧200毫秒很可怕啊蒟蒻自叹不如


------------

最后么就是在最前面决策点不符合条件时往后移动一位(两个元素不相邻否则直接队头后移)，我的顺序是先更新队列然后删点再更新f

然后吐槽以下调试过程stl真的难调试 **哭**还有我自己的代码单调队列出问题了看一下机房神仙代码**玄学**一步看不懂啊很难受 线段树不怎么我的菜，**代码就不写了**，好像都差不多，顺便膜一下
### [神仙](https://www.luogu.org/space/show?uid=35069)rank 1 巨秀 瞬间秒掉20分钟敲完一遍A怀疑人生。。。还好写线段树比我stl慢~~嘻嘻嘻~~

---

## 作者：LinkyChristian (赞：0)

### 每周文章计划 2021.12 第二周第一篇

管理求过www。。。

[显然更好的阅读体验](https://lookcatbox.blog.luogu.org/solution-p1848)

题解原题：[P1295  [TJOI2011]书架](https://www.luogu.com.cn/problem/P1295) 此题为本题的 $w_i$ 和 $h_i$ 相等的情况，做法本质相同。

题目大意：**给出一个长度为 $n$ 的序列 $a$，请将 $a$ 分成若干段，满足每段数字之和都不超过 $m$，最小化每段的最大值之和。**

~~看不懂题解随便手打居然AC了嘤嘤嘤。~~

大部分题解使用线段树优化 $dp$ ，但线段树写着好累，不如来看一种堆的解法。

设 $f_i$ 为考虑到第 $i$ 个数，最大值之和的最小值。

很容易写出 $dp$ 式：

$f_i$ = $min$ ($f_i$ , $f_j$ $+$ $max${$a_{j+1},a_{j+2},··· ,a_i$} ) ($\sum_{k=j+1}^i a_k$ $\leq m$ )

枚举$i,j$即可获得 $O(n^2)$ 做法，得到 $30pt$ 。

考虑优化。

易得$f_i$ $\leq$ $f_j $ ($i<j$) , 证明$f_i$ 单调不降。

我们可以得到在 $max${$j+1,i$} 相同时，选取最小的 $j$ 总是最优的。

我们考虑用单调栈预处理出 $a_i$ 作为最大值的最长区间 $[mi_i,mx_i]$ 。

显然，如果我们选择 $a_i$ 作为转移时的最大值，那么$f_{mi_i-1}$ 必定是最小的 $f$ 。

用小根堆维护，分别记下：

$val$ , $id$ , $fr$ 表示状态的值，此状态所采取的最大值的编号，此状态所采取的 $f$ 值的编号。

考虑限制条件。

预处理 $lst$ 作为满足 $\{\sum_{j=lst+1}^i a_j \}$  $\leq$ $m$ 的最小值。

如果 $id$ $\leq$ $lst$ , 最大值到 $i$ 都已经 $>m$ 了，不行 ，$pop$ 。

如果 $mx_{id} < i $ 显然也不行，因为这时候 $a_i > a_{id}$  $id$ 已经影响不到 $i$ 了，$pop$ 。

如果 $fr < lst$ ，也是不行，所以直接 $pop$ ···吗？

显然这是不能直接$pop$ ， 虽然我理论上的最小值取不到了，但我还可以取此时还存在的最小值，将 $f_{mi_i-1}$ 替换成 $f_{lst}$ 不就可以取到，且满足在能取到且最大值为$a_{id}$的状态中最小吗。

因此对于第三种情况，我们把 $val$ 改为  $f_{lst}+a_{id}$ ，把 $fr$ 改为 $lst$ ，再扔回堆里（注意得先把原来的弹出再扔）。

最后 $f_i$ 直接取当前堆顶的 $val$ 即可。

注意在处理完$f_i$之后得先把 $a_{i+1}$ 作为最大值的状态扔进堆里。

其他细节看代码。

```cpp
#include<bits/stdc++.h>
#define N 500010
using namespace std;
long long n,m,mi[N],mx[N],f[N],sum[N],a[N];
struct node{
	long long val,id,fr;
	bool operator>(node a2) {return val<a2.val;};
};
struct Priority_queue{
    node tr[2*N];
    int cnt;
    void init() {cnt=0;}
    bool empty() {return !cnt;}
    void push(node num) {
    	tr[++cnt]=num;
		int now=cnt;
    	while(now!=1&&num>tr[now/2]) swap(tr[now],tr[now/2]),now/=2;
	} 
	void pop() {
	    swap(tr[1],tr[cnt]),cnt--;
	    int now=1;
	    while((2*now<=cnt&&tr[2*now]>tr[now])||(2*now+1<=cnt&&tr[2*now+1]>tr[now])) {
	    	if(2*now+1>cnt||tr[2*now]>tr[2*now+1]) swap(tr[now],tr[2*now]),now*=2;
			else swap(tr[now],tr[2*now+1]),now=2*now+1; 
		}
	}
	node top() {return tr[1];}
}q;
node stk[N];
int top;
int main()
{
	q.init();
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		cin>>a[i];int tmp=a[i];
		cin>>a[i];
		sum[i]=sum[i-1]+a[i],a[i]=tmp;
	}
	for(int i=1; i<=n; i++) {
		while(top&&stk[top].val<=a[i]) top--;
		if(!top) mi[i]=1;
		else mi[i]=stk[top].id+1;
		stk[++top]=node{a[i],i};
	}   
	top=0;
	for(int i=n; i>=1; i--) {
		while(top&&stk[top].val<=a[i]) top--;
		if(!top) mx[i]=n;
		else mx[i]=stk[top].id-1;
		stk[++top]=node{a[i],i};
	}  
    f[1]=a[1],q.push(node{a[1],1,0});
    int lst=0;
	for(int i=1; i<=n; i++) {
		while(sum[i]-sum[lst]>m) lst++;
		while(!q.empty()&&(q.top().id<=lst||mx[q.top().id]<i||q.top().fr<lst)) {
			if(q.top().id<=lst||mx[q.top().id]<i) q.pop();
			else {
				node tmp=node{f[lst]+a[q.top().id],q.top().id,lst};
				q.pop(),q.push(tmp);
			}
		}
		f[i]=q.top().val;
	    q.push(node{f[mi[i+1]-1]+a[i+1],i+1,mi[i+1]-1});
	}
    cout<<f[n];
	return 0;
}
```

ps：本来是想打[[ZJOI2006]书架](https://www.luogu.com.cn/problem/P2596)的（校内作业），结果因为打开了太多道“书架”，最后做成了这道。




---

## 作者：orz_z (赞：0)


[原题传送门](https://www.luogu.com.cn/problem/P1848)

### 题目大意
给出一个长度为 $n$ 的序列 $h$，和每一个数的 $val$ ，请将 $h$ 分成若干段，满足每段数字的 $val$ 之和都不超过 $m$，最小化每段的最大值之和。

### 解题思路
首先分析题意，得到动态转移方程：

$$f_i=min(f_{j-1}+max(h_j\sim h_i))\ \ (\sum\limits_{k=j}^i h_k\leq m)$$

用线段树存 $z_j=f_{j-1}+max(h_j\sim h_i))$。

求$f_i$ 直接区间最小值就行了。

考虑怎么在线段树上维护 $z$ 的值。

线段树上每个节点存这个区间 $z$ 的最小值，$h$ 的最大值以及 $f$ 的最大值。

每当 $i$ 向右移动一位，先考虑合法区间的左端点会不会因为 $\sum\limits_{k=j}^i h_k>m$ 向右移动。

然后因为右端加入了个 $h_i$ ，可以发现在区间 $[j,i]$ 里，从最靠左的满足 $h_x\le h_i$ 的位置 $x$ ，区间 $[x,i-1]$ 的 $h$ 都会变为 $h_i$，可以二分找出那个位置然后在线段树上区间修改 $h$ 的值。

最后别忘了把插入新的 $z$ ，$f$ 和 $h$ 。

还有，一定要看数据范围，要用 long long。
### AC CODE
```cpp
#include <bits/stdc++.h>
#define int long long
#define _ 100005
using namespace std;

int n, m;
int sum;
int a[_], val[_];

inline int read()
{
    int ans = 0, fh = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            fh = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        ans = ans * 10 + ch - '0', ch = getchar();
    return ans * fh;
}

struct Tree
{
    int z, f, h, lazy;
} tr[_ << 2];

void push_up(int o)
{
    tr[o].h = max(tr[o << 1].h, tr[o << 1 | 1].h);
    tr[o].f = min(tr[o << 1].f, tr[o << 1 | 1].f);
    tr[o].z = min(tr[o << 1].z, tr[o << 1 | 1].z);
}

void push_down(int o)
{
    if (tr[o].lazy)
    {
        tr[o << 1].h = tr[o].lazy;
        tr[o << 1].z = tr[o << 1].f + tr[o].lazy;
        tr[o << 1].lazy = tr[o].lazy;
        tr[o << 1 | 1].h = tr[o].lazy;
        tr[o << 1 | 1].z = tr[o << 1 | 1].f + tr[o].lazy;
        tr[o << 1 | 1].lazy = tr[o].lazy;
        tr[o].lazy = 0;
    }
}

inline void insert(int o, int l, int r, int d, int qf, int qh)
{
    if (l == r)
    {
        tr[o].f = qf;
        tr[o].h = qh;
        tr[o].z = qf + qh;
        return;
    }
    int mid = (l + r) >> 1;
    push_down(o);
    if (d <= mid)
        insert(o << 1, l, mid, d, qf, qh);
    else
        insert(o << 1 | 1, mid + 1, r, d, qf, qh);
    push_up(o);
}

inline void revise(int o, int l, int r, int ql, int qr, int qz)
{
    if (ql <= l && qr >= r)
    {
        tr[o].h = qz;
        tr[o].z = tr[o].f + qz;
        tr[o].lazy = qz;
        return;
    }
    int mid = (l + r) >> 1;
    push_down(o);
    if (ql <= mid)
        revise(o << 1, l, mid, ql, qr, qz);
    if (qr > mid)
        revise(o << 1 | 1, mid + 1, r, ql, qr, qz);
    push_up(o);
}

inline int geth(int o, int l, int r, int ql, int qr)
{
    if (ql <= l && qr >= r)
        return tr[o].h;
    int mid = (l + r) >> 1;
    int Ans = 0;
    push_down(o);
    if (ql <= mid)
        Ans = max(Ans, geth(o << 1, l, mid, ql, qr));
    if (qr > mid)
        Ans = max(Ans, geth(o << 1 | 1, mid + 1, r, ql, qr));
    return Ans;
}

inline int getz(int o, int l, int r, int ql, int qr)
{
    if (ql <= l && qr >= r)
        return tr[o].z;
    int mid = (l + r) >> 1;
    int Ans = LLONG_MAX;
    push_down(o);
    if (ql <= mid)
        Ans = min(Ans, getz(o << 1, l, mid, ql, qr));
    if (qr > mid)
        Ans = min(Ans, getz(o << 1 | 1, mid + 1, r, ql, qr));
    return Ans;
}

inline int getl(int l, int r, int z)
{
    int Ans = r + 1;
    int R = r;
    r++;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (geth(1, 1, n, mid, R) < z)
            Ans = r = mid;
        else
            l = mid + 1;
    }
    return Ans;
}

signed main()
{
    n = read();
    m = read();
    for (int i = 1; i <= n; i++)
        a[i] = read(), val[i] = read();
    insert(1, 1, n, 1, 0, a[1]);
    for (int l = 1, r = 1; r <= n; r++)
    {
        sum += val[r];
        while (sum > m)
            sum -= val[l++];
        int x = getl(l, r - 1, a[r]);
        if (x < r)
            revise(1, 1, n, x, r - 1, a[r]);
        if (r == n)
            cout << getz(1, 1, n, l, r) << endl;
        else
            insert(1, 1, n, r + 1, getz(1, 1, n, l, r), a[r + 1]);
    }
    return 0;
}
```

---

## 作者：intel_core (赞：0)

调了好久的题，写篇题解纪念一下       
这题其实有两种方法     
1. Sol1（简单$DP$）:    
预处理一下前缀和     
令$f[i]$表示以第$i$本书为当前最后一层的最后一本书的最小高度   
$f[i]=min\{f[j]+max\{h_k\}\}|\sum_{k=j+1}^{i}w_i\leq L$   
总复杂度$O(n^3)$  
2. Sol2（前缀$min$空间换时间）    
在$Sol1$的基础上令$a[j]$表示$max\{h_j....h_i\}$     
总复杂度来到了$O(n^2)$    
3. Sol3 （线段树+单调栈）    
考虑单调栈优化这个$DP$    
类似单调栈的证明，可以推出一共只有$O(n)$个区间会对$f$产生贡献    
使用线段树优化这些区间对$f$的贡献     
假设当前考虑到的区间是$[l,r]$      
那么$max\{h_k\}=h_r$     
使用线段树维护$min\{f_j\}$即可     
时间复杂度$O(nlog_2n)$，得分$100$    
4. Sol4 （单调队列+$multiset$）    
考虑在$Sol2$的基础上使用单调队列优化    
其实就是将线段树替换成了$STL$   $multiset+deque$    
因为使用了$STL$，所以常数更大    


下面放出 Sol3 代码    
###### 不保证所有代码的正确性    
###### ~~我是不会告诉你我线段树写错了的~~     

Code:   
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<stack>
using namespace std;
const int NR=1e5+10;
#define lson (id<<1)
#define rson (id<<1|1)
#define mid ((l+r)>>1)
#define int long long
int h[NR],w[NR];
int f[NR];
int sum[NR];
int n,L;
struct Segment_Tree{
	int minn[NR<<3];
	void init(){
		memset(minn,999999,sizeof(minn));
	}
	void update(int id){
		minn[id]=min(minn[lson],minn[rson]);
	}
	void change(int id,int l,int r,int pos,int k){
		if(l==r){
			minn[id]=min(minn[id],k);
			return;
		}
		if(pos<=mid)change(lson,l,mid,pos,k);
		else change(rson,mid+1,r,pos,k);
		update(id);
	}
	int query(int id,int l,int r,int L,int R){
		if(L>R)return 1e18;
		if(r<L||R<l)return 1e18;
		if(L<=l&&r<=R)return minn[id];
		return min(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
	}	
}lcy;
int q[NR];
int l,r;
void init(){
	stack<int>S;
	lcy.init();
	memset(f,999999,sizeof(f));
	int now=0;
	lcy.change(1,1,n+1,1,0);
	for(int i=1;i<=n;i++){
		l=1;r=0;
		while(!S.empty()&&h[S.top()]>=h[i])q[++r]=S.top(),S.pop();
		S.push(i);
		while(sum[i]-sum[max(0ll,now-1)]>L)now++;
		for(int j=l;j<=(l+r)/2;j++)swap(q[j],q[l+r-j]);
		while(l<=r&&q[l]<now)q[l++]=0;
		q[--l]=now-1;q[++r]=i;
		for(int j=l;j<r;j++){
			int x=q[j],y=q[j+1]-1;
			//printf("x:%lld y:%lld\n",x,y);
			f[i]=min(f[i],lcy.query(1,1,n+1,max(x+1,1ll),y+1)+h[y+1]);
		}
		lcy.change(1,1,n+1,i+1,f[i]);
		//printf("%lld\n",f[i]);
	}
}
signed main(){
	cin>>n>>L;
	for(int i=1;i<=n;i++)scanf("%lld%lld",&h[i],&w[i]),sum[i]=sum[i-1]+w[i];
	init();
	cout<<f[n]<<endl;
	return 0;
}
```


---

