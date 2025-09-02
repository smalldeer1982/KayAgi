# Irrigation

## 题目描述

Misha 从小就对送水很感兴趣。因此，他的妈妈把他送去参加一年一度的创新灌溉奥林匹克（IOI）。来自 Berland 的学生们在这里比拼他们的浇水技能。举办这样一场奥林匹克的花费极高，所以在举办了前 $n$ 届奥林匹克后，主办方引入了新的主办城市选择规则。

奥林匹克的主办城市选择规则如下：Berland 有 $m$ 个城市希望承办奥林匹克，它们编号为 $1$ 到 $m$。每一届新的奥林匹克的主办城市，都会选择此前承办次数最少的城市。如果有多个城市承办次数相同，则选择编号最小的城市。

Misha 的妈妈想知道某些特定年份奥林匹克的主办城市。她只知道上述的选择规则，以及前 $n$ 届奥林匹克的主办城市。请你帮她解答，如果你能做到，她会让 Misha 不去淹你家。

## 说明/提示

在第一个样例中，Misha 的妈妈想知道新规则引入后前 $10$ 届奥林匹克的主办城市。对应的主办城市依次为 4、3、4、2、3、4、1、2、3、4。

在第二个样例中，新城市加入后，后续的主办城市依次为 2、3、1、2、3、5、1、2、3、4、5、1。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 4 10
3 1 1 1 2 2
7
8
9
10
11
12
13
14
15
16
```

### 输出

```
4
3
4
2
3
4
1
2
3
4
```

## 样例 #2

### 输入

```
4 5 4
4 4 5 1
15
9
13
6
```

### 输出

```
5
3
3
3
```

# 题解

## 作者：「已注销」 (赞：22)

如果所有城市举办次数一样，举办方式将是$1,2,...,m,1,...$

现在的问题是：可能会跳过一些城市

如果知道要跳过多少城市，就可以$\mathcal O(1)$计算答案

容易发现，要跳过的城市数量单调不减，想到二分

前$n$场比赛每场都会使某个城市在某次比赛时被跳过

设$n=0$时第$i$场比赛应该在时间$T_i$被举办

一次比赛导致的“跳过城市”的发生时间（记第$n+1$场为时间$0$）

$t_i=T_i-1-\sum_j[T_j<T_i]$

$\sum_j[T_j<T_i]$即比$T_i$小的$T$的个数

把$T$排序后减去下标即可实现

询问时二分得到$T_i<k-n$的个数即可

时间复杂度：$\mathcal O((n+q)\log n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=500001;
int n,m,q,c[N];
ll a[N],k;
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int x,i=1;i<=n;++i)
        scanf("%d",&x),a[i]=(ll)(c[x]++)*m+x;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i)a[i]-=i;
    while(q--){
        scanf("%lld",&k);
        k+=lower_bound(a+1,a+n+1,k-n)-a-1-n;
        printf("%lld\n",(k-1)%m+1);
    }
}
```


---

## 作者：cccgift (赞：9)

注：请不要搞错，本题解就是CF1181D的题解……

## 看到大多数人用的都是离线询问处理，这里给出一种在线、代码短、（常数小？）的算法。

首先，像官方题解说的那样，把它看成一个个矩形，每一次挑一个高度最小的把它加$1$。接下来我们考虑，如果没有刚开始那$n$年的随机乱摆，直接从一片平地（没有矩形）开始加，发现答案就是$(k-1)$ $mod$ $m+1$，视这种情况为一般情况。

但是，现在有了前$n$年，那么我们可以把它视为把前$n$个矩形的摆放顺序提前的特殊情况。

于是，我们预处理一个数组$a$，表示第$i$年所要摆放的矩形在一般情况下在$a[i]$年才能被摆到，再把$a$数组从小到大排序。

然后我们可以发现，从第$n+1$年开始摆放的矩形，都是尽量使每一列的总矩形高度接近，也就是接近一般情况。

那么，如果$k>a[n]$，就直接变成了一般情况，那么我们也可以直接输出$(k-1)$ $mod$ $m+1$。

为什么会这样呢？例如：

```cpp
  0  
  0  
0 000
00000
```

那么$a[n]$就是$13$（最高的那个矩形），若$k>13$，则先会变成这样：

```cpp
000
00000
00000
00000
```

这不就是一般情况吗？

所以我们只考虑$k≤a[n]$。

那么我们只要考虑这些新摆的矩形对于$k$的影响即可（肯定有影响，因为它无法变成一般情况）。

接下来，我们再处理出数组$b[i]=a[i]-i$，表示在一般情况下，先摆的矩形前面还有多少个矩形没有摆，因为$i$表示当前已有$i$个矩形，但期望（一般情况）是要$a[i]$个。

我们尝试找到第$k$个矩形在特殊情况下应该摆到一般情况下的哪个位置，那么，对接下来有影响的只有$b[i]$小于这个位置的矩形了（因为这些矩形会把本来该放的位置占住）。

然而，我们已经把$a$排序，而$a$中的数互不相同，所以$b$数组仍有单调性，我们可以直接二分找到这个位置，至于如果要消除影响，直接把$k$减去小于这个位置的矩形的个数然后再按照一般情况输出即可（想想为什么是这样）。

时间复杂度为$O((n+q)logn)$，没有任何数据结构，常数很小。如果有加强，可以把$m$设成$1e9$……

~~代码很短，如果不加上快读等，可以不到20行……~~

### 代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<utility>
#include<algorithm>
using namespace std;
#define res register int
#define ll long long
//#define cccgift
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++) //fread优化 
char buf[1<<21],*p1=buf,*p2=buf;
namespace wode{
    template<typename T> //快读 
    inline void read(T &x)
    {
        static char ch;bool f=1;
        for(x=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') f=0;
        for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());x=f?x:-x;
    }
    template<typename T> //快输 
    inline void print(T x,char ch=0) {
    	if(!x) {putchar(48);if(ch) putchar(ch);return;}
    	if(x<0) putchar('-'),x=-x;
    	static int Stack[sizeof(T)*3],top=-1;
    	for(;x;Stack[++top]=x%10,x/=10);
    	for(;~top;putchar(Stack[top--]+48));
    	if(ch) putchar(ch);
    }
    template<typename T>
    inline T max(T x,T y) {return x<y?y:x;}
    template<typename T>
    inline T min(T x,T y) {return x<y?x:y;}
    template<typename T>
    inline void chkmax(T &x,T y) {x=x<y?y:x;}
    template<typename T>
    inline void chkmin(T &x,T y) {x=x<y?x:y;}
}
using wode::read;using wode::chkmin;using wode::chkmax;using wode::print;
ll a[500001],k;
int tot[500001],n,m,q,x; //tot数组表示每一列的总矩形高度，用于下面处理a数组。
int main()
{
    read(n),read(m),read(q);
    for(res i=1;i<=n;++i) read(x),a[i]=(ll)(tot[x]++)*m+x;
    sort(a+1,a+1+n);for(res i=1;i<=n;++i) a[i]-=i; //这里直接把a变成b了，因为接下来只需要用到a[n]。 
    while(q--) {
    	read(k);if(k<=a[n]+n) k+=lower_bound(a+1,a+1+n,k-n)-a-n-1; //二分查找并减去（这里直接反着找了）
    	print((k-1)%m+1,'\n');
    }
    return 0;
}
```

---

## 作者：一Iris一 (赞：3)


 经简单分析可知

若是 $n = 0$，那么以后的比赛将会有周期性：$1,2,3,\dots,m$。

进一步来说，一定存在某个值使得，当 k 高于这个值的时候将会呈现于 m 有关的周期性。仔细分析之后可知，这个值为 $h\times m - n$。

所以我们只要考虑 k 小于这个临界值的询问（大于的直接取模就行

再将询问离线下来

将 n 次操作视为每次给每个点 +1，记为 $h[i]$ 。然后排一遍序。设一个指针为 p ，从最低的向高位依次推进，当每遇到一个新的 h 时，我们考虑前p个数都需要再举办到 h 次，然后才能向下枚举。这时我们的问题就只关于这前 p 个数，前 p 个数又一共需要举办 $h\times p$ 次，所以只要一个询问不大于 $h\times p$ ，我们就在本次解决，然后需要查询一下前 p 个数的下标第 k 大，这里使用树状数组上倍增解决。

凭借树状数组的小常数，目前成功苟在 rk2

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define lowbit(x) (x & (-x))

char xch,xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
template<typename _T>
inline int read(_T &x)
{
    x=0;
	int f=1;char ch=getc();
    while(ch<'0'|ch>'9'){if(ch=='-')f=-1;ch=getc();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
    return x*f;
}

const int np = 5e5 + 5;
struct query{
	int tim;
	int id;
	friend bool operator<(const query &a,const query &b)
	{
		return a.tim < b.tim;
	}
	
}qry[np + 10];
int n,h[np + 10],b[np + 10],index[np + 10];
int lg[np + 10];
int tree[np + 10],ans[np + 10];

inline bool cmp(int a,int b)
{
	return h[a] < h[b];
}

inline int add(int x)
{
	while(x <= n)
	{
		tree[x] += 1;
		x += lowbit(x);
	}
}

inline int binary(int kth)
{
	int res = 0;
	int step = 0;
	kth--;
	for(int i=lg[n];i>=0;i--)
	{
		if(step + (1 << i) > n) continue;
		if(res + tree[step + (1 << i)] <= kth)
		{
			res += tree[step + (1 << i)];
			step += 1 << i;
		}
	}
	return step + 1;
}

signed  main()
{
	int m,q;
	read(m);
	read(n);
	read(q);
	for(int i=1,x;i<=m;i++)
	{
		read(x);
		h[x] ++ ;
	 }
	int maxn = 0;
	for(int i=1;i<=n;i++) maxn = max(maxn , b[i]= h[i]),index[i] = i; 
	for(int i=2;i<=n;i++) lg[i] = lg[i>>1] + 1;
	
	int lim = maxn * n - m;
	
	sort(b + 1,b + 1 + n);
	sort(index + 1,index + 1 + n,cmp);
	
	for(int i=1,x;i<=q;i++)
	{
		read(x);
		x -= m;
		qry[i] = (query){x,i};
	}
	sort(qry + 1,qry + 1 + q);
	
	int p = 1;
	int res = 0;
	add(index[1]);
	for(int i=1;i<=q;)
	{
		if(qry[i].tim> lim)
		{
			if((qry[i].tim-lim) % n == 0) ans[qry[i].id] = n;
			else ans[qry[i].id] = (qry[i].tim-lim) % n;
			i++;
			continue;
		}
		while(b[p + 1] == b[p]) add(index[++p]);
		int c = b[p + 1] - b[p];
		while(res < qry[i].tim && qry[i].tim <= res + p * c)
		{
			int g = qry[i].tim - res;
			if(g % p == 0) g = binary(p);
			else g = binary(g%p);
			ans[qry[i].id] = g;
			i++;
		}
		res += p * c;
		p++;
		add(index[p]);
	}
	
	for(int i=1;i<=q;i++)
		printf("%lld ",ans[i]);
	return 0;
 }
```

---

## 作者：万弘 (赞：1)

~~在线咋做~~

考虑只有一个询问,询问第$x$次的城市.先令$x$减去$m$.  
设举办次数最少的城市为$cnt$个.接下来有两种情况:$x\le cnt:$$cnt$个城市中第$x$小的编号就是答案;$x>cnt$则最小的城市都将举办一次,直到变成次小的.再令$x$减去$cnt,$重复该过程即可.显然可以权值线段树/平衡树维护.

最后又两种情况:所有城市举办次数都相同了,此时$(x-1)\ mod\ n+1$就是答案.否则已经处理过了.

对于多组询问,离线排序即可.时间复杂度$\mathcal O((q+n)\log n)$

```cpp
/**********/
#define MAXN 500011
ll n,m,q;
struct Segment_Tree
{
    ll t[MAXN<<2|1];
    #define rt t[num]
    #define tl t[num<<1]
    #define tr t[num<<1|1]
    void modify(un pos,ll k,un l=1,un r=n,un num=1)
    {
        if(l==r){rt+=k;return;}
        un mid=(l+r)>>1;
        if(pos<=mid)modify(pos,k,l,mid,num<<1);
        else modify(pos,k,mid+1,r,num<<1|1);
        rt=tl+tr;
    }
    ll Qkth(ll k,un l=1,un r=n,un num=1)
    {
        if(l==r)return l;
        un mid=(l+r)>>1;
        if(k<=tl)return Qkth(k,l,mid,num<<1);
        else return Qkth(k-tl,mid+1,r,num<<1|1);
    }
    ll size(){return t[1];}
}sgt;
std::vector<ll>g[MAXN];
ll c[MAXN],ans[MAXN];
pll query[MAXN];
int main()
{
    m=read(),n=read(),q=read();
    for(ll i=1;i<=m;++i)++c[read()];
    for(ll i=1;i<=n;++i)g[c[i]].push_back(i);
    for(ll i=1;i<=q;++i)query[i]=pll(read()-m,i);
    std::sort(query+1,query+q+1);
    ll cur=0,sum=0,it=1;
    for(ll i=0;i<=m;++i)
    {
        for(auto x:g[i])sgt.modify(x,1),++cur;
        while(it<=q&&query[it].first-sum<=cur)ans[query[it].second]=sgt.Qkth(query[it].first-sum),++it;
        sum+=cur;
    }
    while(it<=q)ans[query[it].second]=sgt.Qkth((query[it].first-sum-1)%n+1),++it;
    for(ll i=1;i<=q;++i)printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：Kazdale (赞：1)

做法：二分+主席树

- ## 分析
	根据题意，当我们要举办一场比赛时，如果只有一个举办比赛次数最少的城市，就选那个城市，如果最少的不止一个，就选其中编号最小的。
    
    模拟一下，我们就会发现这个过程实际上可以转化为按举办次数从小到大排序，然后先使前 $x$ 个数的值相等，然后按编号从小到大加这前 $x$ 个数，若是这些数的值等于下一个数（即第 $x+1$ 个数），则将下一个数也加入此过程。
    
    显然这个过程可以简化为：我们先计算出到最后一共有多少个城市会举办比赛，然后求出剩余的比赛次数在这些城市循环加到哪里即可。

- ## 实现
	若是一个城市举办了比赛，那么说明原比赛次数比它小的都举办了比赛且总比赛次数等于它，所以我们按举办比赛次数从小到大排序，设若要第 $x$ 号城市举办比赛，则必须先举办 $ppc_x$ 次比赛，则 $ppc_x=\sum^{x}_{i=1}(a_{x}-a_{i})$（其中 $a_i$ 为初始比赛次数），这个式子的复杂度为 $\mathcal{O(n)}$，还需要进行以下的变化：
    
    $$\begin{aligned}\sum^{x}_{i=1}\left(a_{x}-a_{i}\right)\\=\sum^{x}_{i=1}a_{x}-\sum ^{x}_{i=1}a_{i}\\ =x \cdot a_x-\sum^{x}_{i=1}a_{i}\end{aligned}$$
    
    后面的部分显然可以前缀和预处理，这样就把复杂度降到了 $\mathcal{O(1)}$。
    
    然后我们就可以二分出最大的小于比赛次数的 $ppc_x$，将两者之间的差模 $x$，求出最后一次循环加的次数 $k$（若剩余次数为 $0$ 则特判成 $x$），直接找出第 $k$ 次操作的位置即可。
    
    值得注意的是，我们第一次排序的顺序与城市的编号无关，因为我们二分的是最大小于比赛次数的值，显然初始比赛次数相等时 $ppc$ 也相等，所以初始比赛次数相等的城市要么全选，要么全不选，所以与城市编号无关。（如果初始比赛次数均为 $x$ 的只有一部分有比赛举办可以理解为选择了所有比赛次数小于等于 $x$ 的城市，但是举办比赛次数不足，不能给所有的城市举办）
    
    显然，第 $k$ 次操作的位置为 $1\sim x$ 中编号第 $k$ 小的数的位置，我们可以直接用主席树维护，总时间复杂度为 $\mathcal{O(n+q\;\log\;m)}$，可以通过本题。
    
- ## 代码

```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
constexpr int MAXN(500007);
int ls[MAXN << 5], rs[MAXN << 5], sum[MAXN << 5], cnt;
int rt[MAXN], p[MAXN], ppc[MAXN];
int n, m, q;
struct node{
	int id, w;
	friend bool operator < (node x, node y) { return x.w < y.w; }
}a[MAXN];
struct HJT{
	#define mid ((l + r) >> 1)
	void update(int &p, int l, int r, int x, int val) {
		++cnt;
		ls[cnt] = ls[p], rs[cnt] = rs[p], sum[cnt] = sum[p] + val;
		p = cnt;
		if (l == r)  return ;
		if (x <= mid)  update(ls[p], l, mid, x, val);
		else  update(rs[p], mid + 1, r, x, val);
	}
	int query(int lst, int prz, int l, int r, int x) {
		if (l == r)  return l;
		if (x <= sum[ls[prz]] - sum[ls[lst]])  return query(ls[lst], ls[prz], l, mid, x);
		else  return query(rs[lst], rs[prz], mid + 1, r, x - sum[ls[prz]] + sum[ls[lst]]);
	}
	#undef mid
}Rin;
inline void read(int &temp) { cin >> temp; }
signed main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(n), read(m), read(q);
	for (int i(1), t; i <= n; ++i)  read(t), ++a[t].w;
	for (int i(1); i <= m; ++i)  a[i].id = i;
	sort(a + 1, a + m + 1);
	for (int i(1); i <= m; ++i)  rt[i] = rt[i - 1], Rin.update(rt[i], 1, m, a[i].id, 1);
	for (int i(1); i <= m; ++i)  p[i] = p[i - 1] + a[i].w;
	for (int i(1); i <= m; ++i)  ppc[i] = a[i].w * i - p[i];
	for (int i(1), k; i <= q; ++i) {
		read(k);
		k -= n;
		int x = lower_bound(ppc + 1, ppc + m + 1, k) - ppc - 1;
		k -= ppc[x], k %= x;
		if (!k)  k = x;
		cout << Rin.query(rt[0], rt[x], 1, m, k) << "\n";
	}
	return 0;
} 
```

---

## 作者：fighter (赞：1)

# 【题解】CF1181D Irrigation

## 题意

[传送门](https://www.luogu.org/problemnew/show/CF1181D)

给定$M$个城市，每年会选出一个城市举办比赛，现给出前$N$年城市举办比赛的情况。在接下来的年份中，每年的比赛会在举办比赛次数最小的城市举办，如果有很多城市举办次数均为最小值，则在编号最小的城市举办比赛。现给出 $Q$个询问，每次询问第 $K$ 年在哪个城市举办比赛。

## 分析

由于个人习惯，把题目中的$n$和$m$意义互换。

我们可以把问题抽象成有$n$个宽度相等高度不同的矩形，给出初始高度，每次选取最矮的矩形中编号最小的，并把它的高度+1，然后不断重复这个操作，要求回答第$K$次选取的矩形的编号。

我们看到要选取编号最小的，那么毫不犹豫先排序。~~（遇事不决先排序）~~

于是我们可以把原问题变成如下图一样：

![VLzwKs.png](https://s2.ax1x.com/2019/06/19/VLzwKs.png)

我们发现有几个高度相同的矩形会组成一段“平台”。于是想想怎么求这种“平台”。

如果我单独地把一段“平台拿出来”，由于高度相同，那么它们被选择的顺序一定是按编号大小排序并形成循环的。那么假如我要在这个平台的基础上求第$k$次选择，那么我们实际上求的是这段平台中编号第$k \% len$小的（其中$len$是平台的长度，并且如果$k\%len=0$，那么就是编号最大的）。

那么这个求平台中第$k$小的操作就可以使用权值线段树~~平衡树~~维护。

---

然而很不幸，我们的问题中显然不只一个平台，所以我们考虑从低到高进行“填坑操作”。~~偷一张官方题解的图~~。

为了处理方便，我们把询问离线，按照$k$的大小（即先后顺序）排序。

![VOSmd0.png](https://s2.ax1x.com/2019/06/19/VOSmd0.png)

比如在这张图中，前三个矩形构成了两个平台，那么我们发现高度更高的$\{2,5\}$并不会对$3$产生影响，必须得等到$3$到达$\{2,5\}$的高度后才会被影响。那么我们就可以放心地先把$3$填至$\{2,5\}$的高度，然后把$3$加入到平台中形成$\{2,3,5\}$这样的一个平台。显然经过填坑操作后，所有的平台都是原序列的前缀。在填坑过程中，有一些询问是可以被回答的，那么就通过平台的性质进行回答。同时我们也要把新加入到平台的元素插入到权值线段树中，以便下一次查询。

---

## 实现细节

在处理平台和询问的时候可以分别记录一个指针，表示当前处理到哪一个矩形或询问。同时再维护一个$now$表示当前已经进行了几次选择（初始值为给定的已操作次数）。然后对于矩形，每次向后找到一个平台，在此过程中把平台中的矩形编号插入到权值线段树中。接着向后枚举询问，如果当前的$now$加上下一个平台被填满所需的操作次数大于询问，那么说明这个询问可以在这次填坑中被回答，那么在权值线段树中查询得到答案。最后$now$累加上填坑所需操作次数即可。

## 复杂度

我们的两个指针都是线性扫描的，所以处理询问部分是$O((n+q)logn)$的，由于前面需要一遍排序也需要$O(nlogn)$的时间，所以总复杂度$O((n+q)logn)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAX 500005
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
#define mid ((l+r)>>1)
using namespace std;

namespace sgt{
    int s[MAX*4];

    void push_up(int p){
        s[p] = s[lc(p)]+s[rc(p)];
    }

    void update(int p, int l, int r, int u, int k){
        if(l == r){
            s[p] += k;
            return;
        }
        if(mid >= u) update(lc(p), l, mid, u, k);
        else update(rc(p), mid+1, r, u, k);
        push_up(p);
    }

    int query(int p, int l, int r, int k){
        if(l == r) return l;
        if(s[lc(p)] >= k){
            return query(lc(p), l, mid, k);
        }
        else return query(rc(p), mid+1, r, k-s[lc(p)]);
    }
}
//以上权值线段树模板

struct ask{		//询问离线
    ll k, id;
    friend bool operator <(ask a, ask b){
        return a.k < b.k;
    }
}q[MAX];

struct city{		//矩形
    ll h, id;

    friend bool operator <(city a, city b){
        if(a.h == b.h) return a.id < b.id;
        return a.h < b.h;
    }
}a[MAX];

int n, m;
ll Q, now, p, p1, p2, ans[MAX];

int main()
{
    cin >> m >> n >> Q;
    for(int i = 1; i <= n; ++i){
        a[i].id = i;
    }
    ll x;
    for(int i = 1; i <= m; ++i){
        scanf("%lld", &x);
        a[x].h++;
    }
    sort(a+1, a+n+1);
    for(int i = 1; i <= Q; ++i){
        scanf("%lld", &q[i].k);
        q[i].id = i;
    }
    sort(q+1, q+Q+1);
    //初始化：排序、离线

    p1 = p2 = 1;
    now = m;
    while(p1 <= n){
        p = p1;
        while(a[p].h == a[p1].h){		//向后找平台，并插入到权值线段树中
            sgt::update(1, 1, n, a[p].id, 1);
            p++;
        }
        while(now+(a[p].h-a[p1].h)*(p-1) >= q[p2].k){		//处理在这次填坑范围内的询问
            ll t = (q[p2].k-now)%(p-1);
            if(!t) t = p-1;
            ans[q[p2].id] = sgt::query(1, 1, n, t);
            p2++;
        }
        now += (a[p].h-a[p1].h)*(p-1);		//累加操作次数
        p1 = p;			//下一次平台的开始
    }
    for(int i = 1; i <= Q; ++i){
        //可能还有一些询问没有处理，但此时所有矩形都已形成一个平台，直接回答，甚至不需要权值线段树
        if(!ans[q[i].id]){
            ll t = (q[i].k-now)%n;
            if(!t) t = n;
            ans[q[i].id] = t;
        }
    }
    for(int i = 1; i <= Q; ++i){
        printf("%lld\n", ans[i]);
    }

    return 0;
}
```



---

## 作者：GreenDay (赞：0)

# 数据结构+贪心

[题面](https://www.luogu.org/problemnew/show/CF1181D)

询问分两类：

1、小于等于n的（直接搞）

2、大于n的（离线处理）

把询问排序后，考虑每次应该先填比赛数量最少的城市，**把这个城市的比赛数量填到第二小**

（就好比下雨填水坑一样，模拟一下过程）

然后找出比赛最小的城市之后，可以通过**取模**过程找到排名（按城市编号排序）

城市编号可以可以用权值线段树\平衡树维护 每一个城市“填满”之后向数据结构里插入下一个城市

还有，注意开long long (调了1个小时，原来要开long long)

如果水平比较高的应该可以主席树在线做 本蒟蒻还是不会

看代码吧

```
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

const int N=5e5+4;

template<typename T>
inline void Read(T &x)
{
    x=0;char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0' && c<='9') {x=x*10+(c-'0');c=getchar();}
}
template<typename T>
void print(T x)
{
    if(x>9) print(x/10);
    putchar(x%10+'0');
}

long long n;
int m,q,qq;

pair<int,int> city[N];//pair<举办比赛数量，城市编号>
pair<long long,int> ask[N];//pair<询问的年数，询问的编号>
long long prefix[N]={0},ans[N];//前缀和(城市)

int val[N<<2];
//这就是一颗线段树 
void insert(int x,int l,int r,int pos)
{
    if(l==r){val[x]=1;return;}
    int mid=l+r>>1;
    if(pos<=mid) insert(x<<1,l,mid,pos);
    else insert(x<<1|1,mid+1,r,pos);
    val[x]=val[x<<1]+val[x<<1|1];
}
int pos(int x,int l,int r,int rank)
{
    if(l==r) return l;
    int mid=l+r>>1;
    if(val[x<<1] >= rank)	return pos(x<<1,l,mid,rank);
    return pos(x<<1|1,mid+1,r,rank-val[x<<1]);
}

int old[N];

int main()
{
    Read(n),Read(m),Read(qq);
    for(register int i=1;i<=m;i++)
        city[i]=make_pair(0,i);
        
    for(register int i=1;i<=n;i++)
    {
        Read(old[i]);
        city[old[i]].first++;
    }
    
    for(register int i=1;i<=qq;i++)
    {
        long long temp;Read(temp);
        if(temp<=n) ans[i]=old[temp];
        else ask[++q]=make_pair(temp-n,i);
    }
    sort(city+1,city+1+m);
    sort(ask+1,ask+1+q); 
    *prefix=0ll;
    for(register int i=1;i<=m;i++)
        prefix[i]=prefix[i-1]+city[i].first;
    
    long long cnt=0;
    for(register int i=1,rank;i<=q;i++)
    {
        while( city[cnt+1].first * cnt - prefix[cnt] < ask[i].first && cnt!=m)
        {
            insert(1,1,m,city[++cnt].second);
            while(city[cnt].first == city[cnt+1].first )
                insert(1,1,m,city[++cnt].second);
        }
        rank=( ask[i].first-(cnt*city[cnt].first-prefix[cnt]) )%cnt;
        if(!rank) rank=cnt;
        ans[ ask[i].second ]=pos (1,1,m,rank);
    }
    
    for(register int i=1;i<=qq;i++)
        print(ans[i]),putchar(10);
        
    return 0;
}
```


---

