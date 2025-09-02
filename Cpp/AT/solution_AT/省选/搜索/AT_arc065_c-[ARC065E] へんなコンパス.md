# [ARC065E] へんなコンパス

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc065/tasks/arc065_c

$ xy $ 平面上に $ N $ 個の穴があります。$ i $ 番目の穴の位置は $ (x_i,y_i) $ です。

$ i $ 番目の穴と $ j $ 番目の穴のマンハッタン距離を $ d(i,j)(=|x_i-x_j|+|y_i-y_j|) $ と表します。

あなたはマンハッタンコンパスを持っています。 このコンパスは、常に $ 2 $ 個の穴を指します。 コンパスが $ p,\ q $ 番目の穴を指している状態と、$ q,\ p $ 番目の穴を指している状態は区別しません。

また、$ d(p,q)=d(p,r) $ で、$ p $ 番目の穴と $ q $ 番目の穴を指しているとき、$ p $ 番目の穴と $ r $ 番目の穴を指すよう動かすことができます。

はじめ、コンパスは $ a $ 番目の穴と $ b $ 番目の穴を指しています。 コンパスが指すことのできる穴の組の数を求めてください。

## 说明/提示

### 制約

- $ 2≦N≦10^5 $
- $ 1≦x_i,\ y_i≦10^9 $
- $ 1≦a\ <\ b≦N $
- $ i\ ≠\ j $ のとき $ (x_i,\ y_i)\ ≠\ (x_j,\ y_j) $
- $ x_i,\ y_i $ は整数である

### Sample Explanation 1

はじめ、コンパスは 穴 $ 1,\ 2 $ を指しています。 $ d(1,2)\ =\ d(1,3) $ なので、穴 $ 1,\ 3 $を指すことができます。 $ d(1,3)\ =\ d(3,4) $ なので、穴 $ 3,\ 4 $を指すことができます。 $ d(1,2)\ =\ d(2,5) $ なので、穴 $ 2,\ 5 $を指すことができます。 他の穴の組でコンパスが指せるものはないため、答えは $ 4 $ となります。

## 样例 #1

### 输入

```
5 1 2
1 1
4 3
6 1
5 5
4 8```

### 输出

```
4```

## 样例 #2

### 输入

```
6 2 3
1 3
5 3
3 5
8 4
4 7
2 5```

### 输出

```
4```

## 样例 #3

### 输入

```
8 1 2
1 5
4 3
8 2
4 7
8 8
3 3
6 6
4 8```

### 输出

```
7```

# 题解

## 作者：noone___ (赞：10)

> 给定 $n$ 个点的坐标 $(x_i,y_i)$ ，选择两个点满足其曼哈顿距离等于 $d$ ，求方案数。

~~小声* [蒟蒻的博客](https://noone40404.github.io/2021/11/15/%E6%9B%BC%E5%93%88%E9%A1%BF%E8%B7%9D%E7%A6%BB%E4%B8%8E%E5%88%87%E6%AF%94%E9%9B%AA%E5%A4%AB%E8%B7%9D%E7%A6%BB/)里总结了一点曼哈顿距离与切比雪夫距离转化的题。~~

提供一个码量较小且跑得比较快的方法。

对于求曼哈顿距离的题，一个思路是考虑转化为切比雪夫距离。

具体的，对于 $(x_O,y_O),(x_i,y_i)$ 有曼哈顿距离： $\text{abs}(x_O-x_i)+\text{abs}(y_O,y_i)$。

令 $x_i'=x_i+y_i\ ,\ y_i'=x_i-y_i$。

那么 $(x_O',y_O'),(x_i',y_i')$ 的切比雪夫距离： $\max\left(|x_O'-x_i'|,|y_O'-y_i'|\right)$ 即是原图两点的曼哈顿距离。

该题中如此转化更好处理，那么转化后的合法点对 $(x_1,y_1),(x_2,y_2)$ 需满足的条件即为：

$$\begin{cases} |x_1-x_2|=dis \\ |y_1-y_2|\leq dis \\\end{cases} $$
或
$$\begin{cases} |y_1-y_2|=dis \\ |x_1-x_2|\leq dis \\\end{cases} $$

通过对 $point$ 进行排序后二分查找，不难得到满足上述条件的 $y_l\sim y_r$ 或 $x_l\sim x_r$。

这里要注意两次查找中不能有重复情况，具体见代码。

考虑统计答案：对于合法的点对将两点连边。

那么上述条件给定的一个合法区间，该区间内的点两两相连并向 $(x_a,y_a)$ 连边。

维护一下每个点的出度，能与初始点 $a$ 连通的即为合法方案，求和即可（显然与 $b$ 连通的一定也与 $a$ 连通）。


```cpp
#include <bits/stdc++.h>
#define rei register int
#define ll long long
#define PII pair<int,int>
#define mk make_pair
using namespace std;

const int N=1e5+100;
PII point[N],sorted_poi[N];
int fa[N],cnt[N],delta[N],id[N];
int x[N],y[N];
int n,a,b,dis;
ll ans;

inline int read(){ rei ans=0; char ch=getchar(); while(ch<'0' || ch>'9') ch=getchar(); while(ch>='0' && ch<='9'){ ans=(ans<<1)+(ans<<3)+(ch^48); ch=getchar();} return ans;}
inline bool cmp(int x,int y){ return point[x]<point[y];}
int get_fa(int x){ return fa[x]==x ? x : fa[x]=get_fa(fa[x]);}
inline void merge(int x,int y){ fa[ get_fa(x) ]=get_fa(y);}
inline void solve(int now){
	for(rei i=1;i<=n;++i) id[i]=i;
	sort(id+1,id+1+n,cmp);
	memset(delta,0,sizeof delta);
	for(rei i=1;i<=n;++i) sorted_poi[i]=point[ id[i] ];
	for(rei i=1;i<=n;++i){
		rei l=lower_bound(sorted_poi+1,sorted_poi+1+n,mk(sorted_poi[i].first+dis,sorted_poi[i].second-dis+now))-sorted_poi;
		rei r=upper_bound(sorted_poi+1,sorted_poi+1+n,mk(sorted_poi[i].first+dis,sorted_poi[i].second+dis-now))-sorted_poi-1;
		if(l<=r){
			++delta[l],--delta[r];
			merge(id[i],id[l]);
			cnt[ id[i] ]+=r-l+1;
		}
	}
	rei pre=0;
	for(rei i=1;i<n;++i){
		pre+=delta[i];
		if(pre) merge(id[i],id[i+1]);
	}
}

int main(){
    n=read(),a=read(),b=read();
    for(rei i=1;i<=n;++i) fa[i]=i;
	for(rei i=1;i<=n;++i) x[i]=read(),y[i]=read(),point[i].first=x[i]+y[i],point[i].second=x[i]-y[i];
	dis=abs(x[a]-x[b])+abs(y[a]-y[b]);
	solve(0);
	for(rei i=1;i<=n;++i) swap(point[i].first,point[i].second);
	solve(1);
	for(rei i=1;i<=n;++i) if(get_fa(i)==get_fa(a)) ans+=cnt[i];
	printf("%lld\n",ans);
	getchar(),getchar();
	return 0;
}
```

---

## 作者：Krimson (赞：4)

[点击](https://www.cnblogs.com/Guts/p/14703653.html)获得更好的阅读体验  

--------------
曼哈顿距离和切比雪夫距离，一般出现了其中一个就要去想想是不是可以转换成另一个。 
本题就是一个典型的例子，在曼哈顿距离下会比较麻烦——每次可以转移到的点都是一个斜着的正方形，不方便枚举。  
而转换成了切比雪夫距离之后就变成了一个正着的正方形了。  

不难发现，无论怎么操作，每个点对之间的距离（无论是曼哈顿还是切比雪夫）都是不变的。
因此，在转换成了切比雪夫距离之后，只要知道了最终可以到达的集合 $p$ 中有哪些点，答案就是所有以这些点为几何中心，边长为 $2dis$ 的正方形的边上的点的个数之和。  
形式化地说，有 $
\begin{aligned}
ans&=\sum^{}_{i\in p} \sum^{n}_{j=1} ([x_{j}=x_{i}+dis,|y_{i}-y_{j}|\leq dis]+[x_{j}=x_{i}+dis,|y_{i}-y_{j}|\leq dis]+[x_{j}=x_{i}+dis,|y_{i}-y_{j}|\leq dis]+[x_{j}=x_{i}+dis,|y_{i}-y_{j}|\leq dis])
\end{aligned}
$  
这个东西可以用动态开点线段树维护，只需要支持单点插入和区间询问，比较好写，不过要记得特判一下正方形的四个角，否则会被算两次，特判方法可以看代码。
这里的时间复杂度是 $O(n \log n)$  

接下来是解决如何得到集合 $p$ 了。其实这个也不难，可以离散化，对每一个 $x$ 开一个 `set`，然后做一次 `bfs` ，直接暴力地去正方形四条边上找，把遍历到的点全部删掉。
因为每一个点只会被删除一次，因此这个地方的时间复杂度也是 $O(n \log n)$ 。

最后记得答案要除以二，因为点对是无序的，上面计算的过程中每一个点对都被统计了两次。


_Code_
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
const int MAXN=1e5+7;
struct node
{
    ll x,y;
}p[MAXN];
#define pll pair<ll,ll>  
int n,a,b;
int mark[MAXN];
ll dis,ans;
#define IT set<pll>::iterator
struct seg
{
    struct T
    {
        int c[2],sum;
    }t[MAXN<<8];
    #define mid (L+R>>1)
    #define lc t[u].c[0]
    #define rc t[u].c[1]
    int cnt;
    void update(int u){
        t[u].sum=0;
        if(lc) t[u].sum+=t[lc].sum;
        if(rc) t[u].sum+=t[rc].sum;
    }
    void insert(int &u,int pos,ll L=-2e9,ll R=2e9){
        if(!u) u=++cnt;
        if(L==pos&&R==pos){
            t[u].sum=1;
            return;
        }
        if(pos<=mid) insert(lc,pos,L,mid);
        else insert(rc,pos,mid+1,R);
        update(u);
    }
    ll query(int u,int l,int r,ll L=-2e9,ll R=2e9){
        if(!u||l>r) return 0;
        if(L==l&&R==r) return t[u].sum;
        if(r<=mid) return query(lc,l,r,L,mid);
        else if(l>mid) return query(rc,l,r,mid+1,R);
        else return (query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R));
    }
    #undef lc
    #undef rc
    #undef mid
}T[2];
int root[2][MAXN<<2];
int cnt;
#define pll pair<ll,ll>
#define IT set<pll>::iterator
set<pll> f[2][MAXN<<2];
map<int,int> id[2];
int main(){
    n=read(),a=read(),b=read();
    for(ri i=1;i<=n;++i){
        ll x=read(),y=read();
        p[i].x=x+y,p[i].y=x-y;
        if(!id[0].count(p[i].x)) id[0][p[i].x]=++cnt;
        T[0].insert(root[0][id[0][p[i].x]],p[i].y);
        f[0][id[0][p[i].x]].insert((pll){p[i].y,i});
        if(!id[1].count(p[i].y)) id[1][p[i].y]=++cnt;
        T[1].insert(root[1][id[1][p[i].y]],p[i].x);
        f[1][id[1][p[i].y]].insert((pll){p[i].x,i});
    }
    dis=max(abs(p[a].x-p[b].x),abs(p[a].y-p[b].y));
    queue<int> q;
    q.push(a),q.push(b);
    while(!q.empty()){
        int u=q.front();q.pop();
        if(mark[u]) continue;
        mark[u]=1;
        if(id[0].count(p[u].x+dis)){
            int now=id[0][p[u].x+dis];
            ans+=T[0].query(root[0][now],max(-2e9,p[u].y-dis),min(2e9,p[u].y+dis));
            set<pll> &s=f[0][now];
            for(IT it=s.lower_bound((pll){p[u].y-dis,0});it!=s.end()&&abs(it->first-p[u].y)<=dis;it=s.erase(it)) q.push(it->second);
        }
        if(id[0].count(p[u].x-dis)){
            int now=id[0][p[u].x-dis];
            ans+=T[0].query(root[0][now],max(-2e9,p[u].y-dis),min(2e9,p[u].y+dis));
            set<pll> &s=f[0][now];
            for(IT it=s.lower_bound((pll){p[u].y-dis,0});it!=s.end()&&abs(it->first-p[u].y)<=dis;it=s.erase(it)) q.push(it->second);
        }
        if(id[1].count(p[u].y+dis)){
            int now=id[1][p[u].y+dis];
            ans+=T[1].query(root[1][now],max(-2e9,p[u].x-dis+1),min(2e9,p[u].x+dis-1));
            set<pll> &s=f[1][now];
            for(IT it=s.lower_bound((pll){p[u].x-dis,0});it!=s.end()&&abs(it->first-p[u].x)<=dis;it=s.erase(it)) q.push(it->second);
        }
        if(id[1].count(p[u].y-dis)){
            int now=id[1][p[u].y-dis];
            ans+=T[1].query(root[1][now],max(-2e9,p[u].x-dis+1),min(2e9,p[u].x+dis-1));
            set<pll> &s=f[1][now];
            for(IT it=s.lower_bound((pll){p[u].x-dis,0});it!=s.end()&&abs(it->first-p[u].x)<=dis;it=s.erase(it)) q.push(it->second);
        }
    }
    print(ans>>1);
    return 0;
}
```


---

## 作者：Ebola (赞：4)

显然是一个BFS，主要问题在于BFS过程中如何快速解决一个点

根据哈密顿距离所定义的“圆”，是一个每条边都与坐标轴呈45度角的矩形，这让人很头疼

不如我们将它旋转45度，与坐标轴平行，然后哈密顿距离就变成了切比雪夫距离。具体地，对于一个点(x,y)，将其旋转45度并进行适量缩放之后，得到的点为(x+y,x-y)。可以证明，旋转后的点和旋转前的点是唯一对应的

将旋转后点的所有横坐标离散化，然后开若干个set，我们称之为Sx[x]，存储离散化之后横坐标为x的所有点，set里面用pair存储，first域是**未离散的**纵坐标，second域是点的编号。纵坐标也做一样的处理

这样，对于每个点，我们可以算出它矩形的4个顶点，然后算出它们旋转后的坐标。对于每一条边，发现它一定是某个set中的一段连续区间，这样只要在对应的set上二分出这段区间，然后枚举所有点就可以了

但这样会T飞。非常显然，一条边可以存在于若干个矩形中。因为一个已经处理过的点再让他入队是没有意义的，但是在处理不同的点时枚举到它，却是对答案有贡献的，我们需要找出一种不遍历它却又能统计到它对答案贡献的方法

我们开若干个vector，一开始存储的内容和set完全一样。记得存完之后对所有vector排序一下。这样，我们在对应的vector上二分出这段区间，然后区间端点减一下就是对答案的贡献了。set上我们照样枚举，只不过枚举到一个点之后我们把它erase掉，避免后期的重复遍历

注意，矩形顶点若对答案存在贡献，那它在相邻的两条边中都会被统计到答案，需要特殊处理。还有最后答案记得除2

```cpp
#include<bits/stdc++.h>
#define MP make_pair
#define FR first
#define SE second
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

typedef pair<int,int> pii;
typedef long long LL;
const int N=100010;
struct Point
{
    int x,y;
    Point(int _x=0,int _y=0):x(_x),y(_y){}
    Point rotate(){return Point(x+y,y-x);}
    bool operator != (Point b){return x!=b.x||y!=b.y;}
} org[N],rtg[N],prg[N];
set<pii> sx[N],sy[N];
vector<pii> vx[N],vy[N];
queue<int> q;
bool vis[N];
int Hx[N],Hy[N],mx,my;
int n,A,B,d;
LL ans=0;

void prework()
{
    sort(Hx+1,Hx+1+n);sort(Hy+1,Hy+1+n);
    mx=unique(Hx+1,Hx+1+n)-(Hx+1);
    my=unique(Hy+1,Hy+1+n)-(Hy+1);
    for(int i=1;i<=n;i++)
    {
        prg[i].x=lower_bound(Hx+1,Hx+1+mx,rtg[i].x)-Hx;
        prg[i].y=lower_bound(Hy+1,Hy+1+my,rtg[i].y)-Hy;
        sx[prg[i].x].insert(MP(rtg[i].y,i));
        sy[prg[i].y].insert(MP(rtg[i].x,i));
        vx[prg[i].x].push_back(MP(rtg[i].y,i));
        vy[prg[i].y].push_back(MP(rtg[i].x,i));
    }
    for(int i=1;i<=mx;i++) sort(vx[i].begin(),vx[i].end());
    for(int i=1;i<=my;i++) sort(vy[i].begin(),vy[i].end());
}

pii gao(set<pii> &s,vector<pii> &v,int l,int r)
{
    ans+=upper_bound(v.begin(),v.end(),MP(r,n))-lower_bound(v.begin(),v.end(),MP(l,0));
    auto pl=s.lower_bound(MP(l,0)),pr=s.upper_bound(MP(r,n));
    for(auto it=pl;it!=pr;)
    {
        if(!vis[it->SE])
        {
            vis[it->SE]=1;
            q.push(it->SE);
        }
        auto it2=it;it2++;
        s.erase(it);it=it2;
    }
    auto ppl=lower_bound(v.begin(),v.end(),MP(l,0));
    auto ppr=lower_bound(v.begin(),v.end(),MP(r,0));
    return MP(ppl==v.end()?0:ppl->SE,ppr==v.end()?0:ppr->SE);
}

void BFS()
{
    vis[A]=1;q.push(A);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        pii p1(0,0),p2(0,0),p3(0,0),p4(0,0);
        Point pt=org[u];
        Point pt1=Point(pt.x+d,pt.y).rotate();
        Point pt2=Point(pt.x,pt.y+d).rotate();
        Point pt3=Point(pt.x-d,pt.y).rotate();
        Point pt4=Point(pt.x,pt.y-d).rotate();
        int p=lower_bound(Hx+1,Hx+1+mx,pt1.x)-Hx;
        if(Hx[p]==pt1.x) p1=gao(sx[p],vx[p],pt1.y,pt2.y);
        p=lower_bound(Hx+1,Hx+1+mx,pt3.x)-Hx;
        if(Hx[p]==pt3.x) p2=gao(sx[p],vx[p],pt4.y,pt3.y);
        p=lower_bound(Hy+1,Hy+1+my,pt2.y)-Hy;
        if(Hy[p]==pt2.y) p3=gao(sy[p],vy[p],pt3.x,pt2.x);
        p=lower_bound(Hy+1,Hy+1+my,pt1.y)-Hy;
        if(Hy[p]==pt1.y) p4=gao(sy[p],vy[p],pt4.x,pt1.x);
        if(p1.SE&&p3.SE&&p1.SE==p3.SE) ans--;
        if(p2.SE&&p3.FR&&p2.SE==p3.FR) ans--;
        if(p2.FR&&p4.FR&&p2.FR==p4.FR) ans--;
        if(p4.SE&&p1.FR&&p4.SE==p1.FR) ans--;
    }
}

int main()
{
    n=read();A=read();B=read();
    for(int i=1;i<=n;i++)
    {
        org[i].x=read();
        org[i].y=read();
        rtg[i]=org[i].rotate();
        Hx[i]=rtg[i].x;
        Hy[i]=rtg[i].y;
    }
    d=abs(org[A].x-org[B].x)+abs(org[A].y-org[B].y);
    prework();BFS();
    printf("%lld\n",ans/2);
    return 0;
}
```



---

## 作者：yinianxingkong (赞：3)

在优化建图上一种不一样的解法。

首先转换题意，发现曼哈顿距离始终**不变**，令其为 $D$。将所有曼哈顿距离为 $D$ 的点连边，不难发现问题等价于求最开始的点所在连通块的边数。边数是度数和的一半，转为求连通块度数和。

一个点的度数即和它距离为 $D$ 的点的数量。曼哈顿距离下的相同距离点的集合呈斜正方形。斜线懒得统，转切比雪夫后就是正方形，就是统计两条竖线和两条横线上的点。这个只需要对每个坐标开动态数组二分就行了。

然后是连通块的问题。边太多了显然不能遍历，我们需要优化建图。注意到只需要选每条线上**最左**和**最右**的点即可覆盖所有可达点的情况，边数量变成 $8n$ 级别。暴力遍历即可。

代码实现不难，存点可以考虑 `map` 套 `vector`。这样会有两个 $\log$。将 `map` 换成 `gp_hash_table` 或者离散化可以优化成一个 $\log$。

代码有需求私信。

---

## 作者：dengchengyu (赞：3)

## arc065_c

第一次自己想出来黑题！纪念一下。
（其实感觉这道题的思维难度并没有黑题，代码也都是重复性的内容，并不难写）。

题目大意：给定 $n$ 个点，和初始无序点对 $(a,b)$，记 $dis(a,b)$ 表示点 $a,b$ 的曼哈顿距离，可以不断操作，每次操作可以从一个无序点对 $(a,b)$ 移动到另一个满足 $dis(a,c)=dis(a,b)$ 的无序点对 $(a,c)$ 问你最终能到达多少个无序点对。

首先，套路地，把曼哈顿距离转化为切比雪夫距离，把 $(x,y)\to (x+y,x-y)$。
实际上就是考虑到一个点曼哈顿距离相等的点，形成了一个倾斜 $45$ 度的正方形。把正方形转正，就从原来坐标系下的 $(x,y)$ 变成了新坐标系下的 $(x+y,x-y)$，曼哈顿就变成了切比雪夫距离。

切比雪夫距离就是对于两个点 $(x,y),(x',y')$，距离为 $\max(|x-x'|,|y-y'|)$。

回到题目上来，我们每次 $(a,b)\to(a,c)$ 实际上可以看作 $(b,a)\to(a,c)$。
我们只关心这个无序对的第二个点 $a$，然后每次移动就是把无序对的第二个点换成满足 $dis(a,b)=L$ 的 $b$，$L$ 为初始点对的距离。

然后我们能求出所有能出现在最终点对中的点，再对这些点统计答案。

这个问题可以 BFS 做，具体地，对每个 $x'$ 用 `set` 维护当前还没有遍历到的 $x=x'$ 的点及其 $y$， 对每个 $y'$ 也这样。
我们每次对 $x=x_u-L$ 的 `set`，二分位置取出 $y_u-L\le y\le y_u+L$ 的点，然后把这些点加入队列，对于 $x=x_u+L,y=y_u-L,y=y_u+L$ 的也类似。

每当一个点加入队列时，就把它对应 `set` 中的点删掉，这样就能保证每个遍历到的点都是新的点，保证了复杂度。
每个点在 `set` 中遍历 $O(1)$ 次，且加入队列更新其他点 1 次，所以这一部分的复杂度是 $O(n\log n)$ 的。

求出所有能遍历到的点后，距离其中一个点为 $L$ 的点与这个点都能形成合法点对。
再用类似方法求出个数即可。把点扔到  $x$ 和 $y$ 的 `vector` 里。二分位置，两个位置相减求个数。注意正方形的四个角可能算重。

最后由于是无序对，答案需要除以 2。

AC 代码，[AC 记录](https://atcoder.jp/contests/arc065/submissions/60418431)：

```cpp
const int N=1e5+5;
int n,t1,t2;
int X[N],Y[N];
int qx[N],qy[N];
int bx[N],by[N];
int bz[N];
set<pair<int,int> > x1[N],y1[N];
vector<int> x2[N],y2[N];
signed main(){
	read(n,t1,t2);
	fo(i,1,n){
		int x,y; read(x,y);
		X[i]=x+y,Y[i]=x-y;
		bx[i]=X[i],by[i]=Y[i];
	}
	sort(bx+1,bx+1+n);
	sort(by+1,by+1+n);
	int len=unique(bx+1,bx+1+n)-bx-1;
	fo(i,1,n)qx[i]=lower_bound(bx+1,bx+1+len,X[i])-bx;
	int lx=len;
	len=unique(by+1,by+1+n)-by-1;
	fo(i,1,n)qy[i]=lower_bound(by+1,by+1+len,Y[i])-by;
	fo(i,1,n)x1[qx[i]].insert({Y[i],i}),y1[qy[i]].insert({X[i],i});	
	queue<int> q;
	q.push(t1),bz[t1]=1;
	x1[qx[t1]].erase({Y[t1],t1}),y1[qy[t1]].erase({X[t1],t1});
	q.push(t2),bz[t2]=1;
	x1[qx[t2]].erase({Y[t2],t2}),y1[qy[t2]].erase({X[t2],t2});
	int L=max(abs(X[t1]-X[t2]),abs(Y[t1]-Y[t2]));
	while(q.size()){
		int u=q.front(); q.pop();
		int l=lower_bound(bx+1,bx+1+lx,X[u]-L)-bx;
		vector<int> add;
		if(bx[l]==X[u]-L){
			auto p1=x1[l].lower_bound({Y[u]-L,0}),p2=x1[l].lower_bound({Y[u]+L+1,0});
			while(p1!=p2){
				add.push_back(p1->second);
				++p1;
			}
		}
		l=lower_bound(bx+1,bx+1+lx,X[u]+L)-bx;
		if(bx[l]==X[u]+L){
			auto p1=x1[l].lower_bound({Y[u]-L,0}),p2=x1[l].lower_bound({Y[u]+L+1,0});
			while(p1!=p2){
				add.push_back(p1->second);
				++p1;
			}
		}
		l=lower_bound(by+1,by+1+len,Y[u]-L)-by;
		if(by[l]==Y[u]-L){
			auto p1=y1[l].lower_bound({X[u]-L,0}),p2=y1[l].lower_bound({X[u]+L+1,0});
			while(p1!=p2){
				add.push_back(p1->second);
				++p1;
			}
		}
		l=lower_bound(by+1,by+1+len,Y[u]+L)-by;
		if(by[l]==Y[u]+L){
			auto p1=y1[l].lower_bound({X[u]-L,0}),p2=y1[l].lower_bound({X[u]+L+1,0});
			while(p1!=p2){
				add.push_back(p1->second);
				++p1;
			}
		}
		sort(add.begin(),add.end());
		add.resize(unique(add.begin(),add.end())-add.begin());
		for(auto i:add){
			bz[i]=1;
			q.push(i);
			x1[qx[i]].erase({Y[i],i}),y1[qy[i]].erase({X[i],i});
		}
	}
	fo(i,1,lx)x1[i].clear();
	fo(i,1,len)y1[i].clear();
	fo(i,1,n)x1[qx[i]].insert({Y[i],i}),y1[qy[i]].insert({X[i],i});	
	fo(i,1,lx)for(auto j:x1[i])x2[i].push_back(j.first);
	fo(i,1,len)for(auto j:y1[i])y2[i].push_back(j.first);
	ll ans=0;
	fo(i,1,n){
		if(bz[i]){
			int l=lower_bound(bx+1,bx+1+lx,X[i]-L)-bx;
			if(bx[l]==X[i]-L)ans+=upper_bound(x2[l].begin(),x2[l].end(),Y[i]+L-1)-lower_bound(x2[l].begin(),x2[l].end(),Y[i]-L);
			l=lower_bound(bx+1,bx+1+lx,X[i]+L)-bx;
			if(bx[l]==X[i]+L)ans+=upper_bound(x2[l].begin(),x2[l].end(),Y[i]+L)-lower_bound(x2[l].begin(),x2[l].end(),Y[i]-L+1);
			l=lower_bound(by+1,by+1+len,Y[i]-L)-by;
			if(by[l]==Y[i]-L)ans+=upper_bound(y2[l].begin(),y2[l].end(),X[i]+L)-lower_bound(y2[l].begin(),y2[l].end(),X[i]-L+1);
			l=lower_bound(by+1,by+1+len,Y[i]+L)-by;
			if(by[l]==Y[i]+L)ans+=upper_bound(y2[l].begin(),y2[l].end(),X[i]+L-1)-lower_bound(y2[l].begin(),y2[l].end(),X[i]-L);
		}
	}
	write(ans/2);
	return 0;
}
```

---

## 作者：feecle6418 (赞：3)

其他题解都做得比较麻烦，这里提供一种只用了基本 STL 的方法。

不知道为什么黑题，感觉除了细节比较多没有思维难度

首先观察 $(x,y)$ 要满足什么条件才能到达。注意到若 $(x,y)$ 能到，$dis(x,y)=dis(x,z)$ 则 $(x,z)$ 也能到（废话，不就是题目中定义吗）。也就是说，假如有一个序列 $(a_1,a_2,\dots,a_n)$ 满足 $(a_1,a_2)$ 能到达且 $\forall i,dis(a_i,a_{i+1})=dis(a_1,a_2)$，则 $\forall i,x$ 满足 $dis(a_i,x)=dis(a_1,a_2)$ 都能到达。也就是，若在 $dis(A,B)=dis(i,j)$ 的 $(A,B)$ 之间连边，只要 $(x,y)$ 都和 $A,B$ 在一个连通块中且 $dis(x,y)=dis(A,B)$，$(x,y)$ 就能到达。

现在只需要解决两个问题：

1. 给出一个集合，求出有几对点距离为 $D=dis(A,B)$。
2. 若在 $dis(A,B)=dis(i,j)$ 的 $(A,B)$ 之间连边，找出连通块。

第一个问题可以用 map 解决，从左往右扫描所有点，那满足条件的点在两条斜线上，都形如 $x\pm y=k$，可以直接统计。

第二个问题采用 BFS+set，把 $x+y=k$（$-$ 同理）的点存进下标为 $k$ 的 set 里面，每次能访问到的是一段区间。set 里面暴力查询，一旦访问过了就把这个点删掉，复杂度显然正确。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,used[100005],A,B,tot=0;
ll d;
struct P{
	ll x,y,id;
}a[100005],b[100005];
const bool operator <(const P x,const P y){
	return x.x<y.x;
}
set<P> ssum[200005],sdiff[200005];
map<ll,ll> id;
queue<int> q;
void U(int x){
	if(used[x])return ;
	q.push(x),used[x]=1;
	ssum[id[a[x].x+a[x].y]].erase(a[x]);
	sdiff[id[a[x].x-a[x].y]].erase(a[x]);
}
ll Calc(){
	map<ll,ll> cnt1,cnt2;
	set<pair<ll,ll> > s;
	ll sum=0;
	sort(a+1,a+n+1);
	for(int i=1,j=1;i<=n;i++){
		while(a[j].x<a[i].x-d)cnt1[a[j].x+a[j].y]--,cnt2[a[j].x-a[j].y]--,j++;
		sum+=cnt1[a[i].x+a[i].y-d],sum+=cnt2[a[i].x-a[i].y-d];
		if(s.count(make_pair(a[i].x-d,a[i].y)))sum--;
		cnt1[a[i].x+a[i].y]++,cnt2[a[i].x-a[i].y]++;
		//cout<<i<<' '<<a[i].x<<' '<<a[i].y<<' '<<sum<<'\n';
		s.insert(make_pair(a[i].x,a[i].y));
	}
	return sum;
}
int main(){
	cin>>n>>A>>B;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y,a[i].id=i;
		if(!id.count(a[i].x+a[i].y))id[a[i].x+a[i].y]=++tot;
		if(!id.count(a[i].x-a[i].y))id[a[i].x-a[i].y]=++tot;
		ssum[id[a[i].x+a[i].y]].insert(a[i]);
		sdiff[id[a[i].x-a[i].y]].insert(a[i]);
	}
	d=abs(a[A].x-a[B].x)+abs(a[A].y-a[B].y);
	U(A),U(B);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		vector<int> tmp;
		if(id.count(a[x].x+a[x].y+d)){
			auto it=ssum[id[a[x].x+a[x].y+d]].lower_bound({a[x].x,0,0});
			while(it!=ssum[id[a[x].x+a[x].y+d]].end()&&(it->x)<=a[x].x+d){
				tmp.push_back(it->id);
				++it;
			}
		}
		if(id.count(a[x].x+a[x].y-d)){
			auto it=ssum[id[a[x].x+a[x].y-d]].lower_bound({a[x].x-d,0,0});
			while(it!=ssum[id[a[x].x+a[x].y-d]].end()&&(it->x)<=a[x].x){
				tmp.push_back(it->id);
				++it;
			}
		}
		if(id.count(a[x].x-a[x].y+d)){
			auto it=sdiff[id[a[x].x-a[x].y+d]].lower_bound({a[x].x,0,0});
			while(it!=sdiff[id[a[x].x-a[x].y+d]].end()&&(it->x)<=a[x].x+d){
				tmp.push_back(it->id);
				++it;
			}
		}
		if(id.count(a[x].x-a[x].y-d)){
			auto it=sdiff[id[a[x].x-a[x].y-d]].lower_bound({a[x].x-d,0,0});
			while(it!=sdiff[id[a[x].x-a[x].y-d]].end()&&(it->x)<=a[x].x){
				tmp.push_back(it->id);
				++it;
			}
		}
		for(int i:tmp)U(i);
	}
	ll ans=Calc();
	for(int i=1;i<=n;i++)if(!used[a[i].id])b[++m]=a[i];
	n=m;
	for(int i=1;i<=n;i++)a[i]=b[i];
	ans-=Calc();
	cout<<ans;
}
```

---

## 作者：Anonymely (赞：1)

模拟赛题，简单题。

首先选择的两点之间距离永远不变，设为 $d$。

对于一个确定的点 $x$，只要它能出现在一个对子里，其周围距离它为 $d$ 的点都可以出现在对子里。

也就是我们只需要考虑每个点周围距离为 $d$ 的点数量以及是否能到达。

暴力的思维是直接把四个平面拆开做 cdq，数据结构维护一下就行，$O(n \log^2 n)$ 场上没写。

考虑智慧一点的思维，曼哈顿转切比雪夫，这样距离 $x$ 为 $d$ 的点是一个边长为 $2d$，中心是 $x$ 的正方形边上，那拆成两条横线和两条竖线即可。

需要的是区间求和以及合并点对，并查集+主席树维护即可，复杂度 $O(n \log n)$。


```cpp
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "Debug.h"
#else
#define debug(x...) 0
#define dbg(x...) 0
#endif

#define QwQ01AwA return 0
#define uint unsigned int
#define i64 long long
#define u64 unsigned long long
#define i128 __int128
#define file(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> bool ckmax(T &x, const T y) {return x < y ? (x = y, 1) : 0;}
template <typename T> bool ckmin(T &x, const T y) {return y < x ? (x = y, 1) : 0;}

bool m1;
const int M = 1e7 + 5;
const int N = 1e5 + 5;
const int lim = 2e9;
int fa[N], ls[M], rs[M], cn, sum[M], head[M], val[M], nxt[M], cc;
int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
void merge(int u, int v) {u = find(u), v = find(v); if (u == v) return ; fa[u] = v;}
void ins(int &p, const int &l, const int &r, const int &x, const int &id) {
	if (!p) p = ++cn, sum[cn] = 0;
	sum[p]++, val[++cc] = id, nxt[cc] = head[p], head[p] = cc;
	if (l == r) return ;
	int mid = (l + r) / 2;
	x <= mid ? ins(ls[p], l, mid, x, id) : ins(rs[p], mid + 1, r, x, id);
}
void clr(const int &p, const int &id) {int st = head[p]; while (head[p]) merge(id, val[head[p]]), head[p] = nxt[head[p]]; nxt[head[p] = st] = 0;}
int work(const int &p, const int &l, const int &r, const int &L, const int &R, const int &id) {
	if (!p) return 0;
	if (L <= l && r <= R) return clr(p, id), sum[p];
	int mid = (l + r) / 2, res = 0;
	if (L <= mid) res += work(ls[p], l, mid, L, R, id);
	if (mid < R) res += work(rs[p], mid + 1, r, L, R, id);
	return res;
}
struct Point {
	int x, y;
} p[N];
int n, S, T, D, w[N];
map < pair <int, int>, int> mp;
int mpx[N], mpy[N], tx, ty, rtx[N], rty[N];
bool m2;

signed main() {
	cerr << abs(&m2 - &m1) / 1024.0 / 1024 << '\n';
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> S >> T, cn = n;
	for (int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y, fa[i] = i;
	D = abs(p[S].x - p[T].x) + abs(p[S].y - p[T].y);
	for (int i = 1; i <= n; i++) p[i] = {p[i].x + p[i].y, p[i].x - p[i].y}, mp[{p[i].x, p[i].y}] = 1, mpx[++tx] = p[i].x, mpy[++ty] = p[i].y;
	sort(mpx + 1, mpx + tx + 1), sort(mpy + 1, mpy + ty + 1);
	tx = unique(mpx + 1, mpx + tx + 1) - mpx - 1, ty = unique(mpy + 1, mpy + ty + 1) - mpy - 1;
	for (int i = 1; i <= n; i++) ins(rtx[lower_bound(mpx + 1, mpx + tx + 1, p[i].x) - mpx], 1, ty, lower_bound(mpy + 1, mpy + ty + 1, p[i].y) - mpy, i);
	for (int i = 1; i <= n; i++) ins(rty[lower_bound(mpy + 1, mpy + ty + 1, p[i].y) - mpy], 1, tx, lower_bound(mpx + 1, mpx + tx + 1, p[i].x) - mpx, i);
	for (int i = 1; i <= n; i++) {
		int lx, rx, ly, ry;
		lx = lower_bound(mpx + 1, mpx + tx + 1, max(-1ll * lim, 1ll * p[i].x - D)) - mpx;
		rx = upper_bound(mpx + 1, mpx + tx + 1, min(1ll * lim, 1ll * p[i].x + D)) - mpx - 1;
		ly = lower_bound(mpy + 1, mpy + ty + 1, max(-1ll * lim, 1ll * p[i].y - D)) - mpy;
		ry = upper_bound(mpy + 1, mpy + ty + 1, min(1ll * lim, 1ll * p[i].y + D)) - mpy - 1;
		if (p[i].x >= -lim + D && lx <= tx && mpx[lx] == p[i].x - D) w[i] += work(rtx[lx], 1, ty, ly, ry, i);
		if (p[i].x <= lim - D && rx >= 1 && mpx[rx] == p[i].x + D) w[i] += work(rtx[rx], 1, ty, ly, ry, i);
		if (p[i].y >= -lim + D && ly <= ty && mpy[ly] == p[i].y - D) w[i] += work(rty[ly], 1, tx, lx, rx, i);
		if (p[i].y <= lim - D && ry >= 1 && mpy[ry] == p[i].y + D) w[i] += work(rty[ry], 1, tx, lx, rx, i);
		if (mp.count({p[i].x - D, p[i].y - D})) w[i]--;
		if (mp.count({p[i].x - D, p[i].y + D})) w[i]--;
		if (mp.count({p[i].x + D, p[i].y - D})) w[i]--;
		if (mp.count({p[i].x + D, p[i].y + D})) w[i]--;
	}
	assert(find(S) == find(T));
	i64 ans = 0;
	for (int i = 1; i <= n; i++) if (find(i) == find(S)) ans += w[i];
	assert(ans % 2 == 0);
	cout << ans / 2 << '\n';
	look_time;
	QwQ01AwA;
}
/*
g++ -o sol sol.cpp -O2 -Wall -Wextra -Wl,--stack=536870912 -D LOCAL -D_GLIBCXX_ASSERTIONS
*/
```

---

## 作者：ZnPdCo (赞：0)

点对似乎没有优化空间，是不是可以转换为一个点？

发现如果点对中一个点能够为 $x$，则所有与 $x$ 距离为 $d$（记 $\text{dis}(a,b)=d$）的点都能够成为点对的另一个点。

那么我们可以处理出每个点与它距离为 $d$ 的点的数量 $\text{num}_i$，那么答案就是所有的可以到达（可以为点对中的一个点）的点的 $\text{num}_i$ 之和，除以 $2$。

怎样的点才能算到达？

如果一个点可到达，那么距离这个点距离为 $d$ 的点都是可到达的。

一个点只能被计算一次，所以考虑 bfs，初始的时候把 $a$ 和 $b$ 加入，然后每次把距离当前点距离为 $d$ 且还没有加入过 bfs 的点加入即可。

怎么找出距离为 $d$（且还没有加入过 bfs）的点。

曼哈顿距离比较难处理（也可以做，留给读者自行思考），因为是个斜正方形，所以转一下，转为切比雪夫距离，那么和当前距离为 $d$ 的点都在一个正方形上，这就比较好处理。

拿个 `set` 维护一行、一列的点，每次二分。找出距离为 $d$ 可以直接用前缀和相减，找出距离为 $d$ 且还没有加入过 bfs 的点可以直接遍历一遍合法点，因为每个合法点访问过就会直接删除，所以复杂度是可以保证的。

```cpp
#include <bits/stdc++.h>
#define int long long
#define N 100010
using namespace std;
int n, a, b, d, ans, num[N], x[N], y[N], vis[N], X, Y;
map<int, set<tuple<int, int, int>>> col, row;
queue<int> que;
int calc(auto &s, int l, int r, bool flag) {
    if(s.empty() || l > r) return 0;
    auto L = s.lower_bound(make_tuple(l, 0, 0)), R = s.lower_bound(make_tuple(r + 1, 0, 0));
    if(flag) {
        for(auto it = L; it != R; it ++, s.erase(prev(it))) {
            if(vis[get<1>(*it)]) continue;
            vis[get<1>(*it)] = true;
            que.push(get<1>(*it));
        }
        return 0;
    }
    if(L == s.end()) return 0;
    if(R == s.end()) return s.size() - get<2>(*L) + 1;
    return get<2>(*R) - get<2>(*L);
}
void init(auto &s) {
    auto t = s;
    s.clear();
    for(auto it : t) {
        int tmp = 0;
        for(auto jt : it.second)
            s[it.first].insert(make_tuple(get<0>(jt), get<1>(jt), ++ tmp));
    }
}
signed main() {
    cin >> n >> a >> b;
    for(int i = 1; i <= n; i ++) {
        cin >> X >> Y; x[i] = X + Y, y[i] = X - Y;
        col[x[i]].insert(make_tuple(y[i], i, 0)), row[y[i]].insert(make_tuple(x[i], i, 0));
    }
    d = max(abs(x[a] - x[b]), abs(y[a] - y[b]));
    init(col), init(row);
    for(int i = 1; i <= n; i ++) {
        num[i] += calc(col[x[i] - d], y[i] - d, y[i] + d - 1, 0);
        num[i] += calc(col[x[i] + d], y[i] - d + 1, y[i] + d, 0);
        num[i] += calc(row[y[i] - d], x[i] - d + 1, x[i] + d, 0);
        num[i] += calc(row[y[i] + d], x[i] - d, x[i] + d - 1, 0);
    }
    que.push(a), que.push(b), vis[a] = vis[b] = true;
    while(!que.empty()) {
        int i = que.front();
        que.pop();
        calc(col[x[i] - d], y[i] - d, y[i] + d, 1);
        calc(col[x[i] + d], y[i] - d, y[i] + d, 1);
        calc(row[y[i] - d], x[i] - d, x[i] + d, 1);
        calc(row[y[i] + d], x[i] - d, x[i] + d, 1);
        ans += num[i];
    }
    cout << ans / 2 << endl;
}
```

至于如果不转，可以用 `set` 维护一个斜线的点，然后每次在两条斜线上二分就可以了。也是很好写的。

---

