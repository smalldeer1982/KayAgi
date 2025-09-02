# Spanning Tree Queries

## 题目描述

You are given a connected weighted undirected graph, consisting of $ n $ vertices and $ m $ edges.

You are asked $ k $ queries about it. Each query consists of a single integer $ x $ . For each query, you select a spanning tree in the graph. Let the weights of its edges be $ w_1, w_2, \dots, w_{n-1} $ . The cost of a spanning tree is $ \sum \limits_{i=1}^{n-1} |w_i - x| $ (the sum of absolute differences between the weights and $ x $ ). The answer to a query is the lowest cost of a spanning tree.

The queries are given in a compressed format. The first $ p $ $ (1 \le p \le k) $ queries $ q_1, q_2, \dots, q_p $ are provided explicitly. For queries from $ p+1 $ to $ k $ , $ q_j = (q_{j-1} \cdot a + b) \mod c $ .

Print the xor of answers to all queries.

## 说明/提示

The queries in the first example are $ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 $ . The answers are $ 11, 9, 7, 3, 1, 5, 8, 7, 5, 7, 11 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1633E/cc44ec2a2f7074b3d4db31716a40d840e49d6671.png)The queries in the second example are $ 3, 0, 2, 1, 6, 0, 3, 5, 4, 1 $ . The answers are $ 14, 19, 15, 16, 11, 19, 14, 12, 13, 16 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1633E/8c952d1a0cb110f0d7bc671856ab3b11fe089a16.png)The queries in the third example are $ 75, 0, 0, \dots $ . The answers are $ 50, 150, 150, \dots $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1633E/0df04a7e4050b5f60aca076480a18740ebab3d6b.png)

## 样例 #1

### 输入

```
5 8
4 1 4
3 1 0
3 5 3
2 5 4
3 4 8
4 3 4
4 2 8
5 3 9
3 11 1 1 10
0 1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
6 7
2 4 0
5 4 7
2 4 0
2 1 7
2 6 1
3 4 4
1 4 8
4 10 3 3 7
3 0 2 1```

### 输出

```
5```

## 样例 #3

### 输入

```
3 3
1 2 50
2 3 100
1 3 150
1 10000000 0 0 100000000
75```

### 输出

```
164```

# 题解

## 作者：Legitimity (赞：11)

考虑 `kruskal` 的过程，实际上 `MST` 的构成只和按边权排序后结果有关。考虑任意两条边 $i$ 和 $j$ 之间的大小关系以 $x=\dfrac{w_i+w_j}{2}$ 为界，只有 $O(m^2)$ 种 `MST` ，我们可以对于每种情况跑出对应的 `MST`，此部分的时间复杂度为 $O(m^3\log m)$。~~（常数很小，且有 cf 的神机加持，跑的很快）~~

对于同种 `MST`，处理出要选那些边后，对于不同的 $x$ 可以用双指针处理。（具体来说按升序处理 $x$，同时按升序加入满足 $w_i\leq x$ 且在 `MST` 中的边，维护它们的数量和权和）

综合一下，我们得到这样一个算法：将询问的 $x$ 按升序排序，同时按升序处理不同段的 `MST`，求出当前段的 `MST` ，钦定选哪些边，后按升序处理询问，处理询问时按升序加边。~~（三指针）~~

如果使用快排，时间复杂度为 $O(m^3\log m +q\log q)$。


------------


~~你问给长度 $10^7$ 的数组排序不会有问题吗？当时我也觉得跑不过去，但事实证明你可以永远相信 `std::sort` 的常数，如果实在担心就用松氏基排。（雾）~~



---

## 作者：Morgen_Kornblume (赞：9)

## 前言

题目内容不多赘述。

反正，我管这东西，叫“绝对值函数最小生成树”。

这道题想出解法的核心就在于他给的数据范围（其实有提示的作用），还有绝对值函数的性质。

话不多说，我们开始正题。

## 分析

由题目中几个关键的数据范围：

$1 \leq n \leq 50$

$n-1 \leq m \leq 300$

$p \leq k \leq 10^7$

以及做一次最小生成树（MST）的时间复杂度是 $mlog(m)$（kruskal 算法），我们大概可以把对 $k$ 次询问每一个询问做一次 MST 的 BF 想法推翻，那么现在该怎么做呢？

不妨来观察一下题目条件中所给的绝对值函数的性质。

我们画个图（使用 geogebra）：

![](https://cdn.luogu.com.cn/upload/image_hosting/795s6rik.png)

我们知道，在这道题里面，做 MST 时每条边的权值应该是给定 $q$ （或者说 $x$）以后的权值（对应到图中便是给定横坐标 $x$，每个函数（边权值）所对应的 $y$ 值）。

然后看图可以发现，在一定范围内，边权函数的大小关系是确定的，然后增减性也是确定的，考虑 kruskal 算法的排序过程，不难发现当函数大小关系确定时，求出的 MST 也是唯一的。

好了，所以现在我们按照这些绝对值函数彼此之间还有它们与 $x$ 轴的交点，将数轴分段，对于每一段求出它开始点 $x$ 值对应的答案，并且统计增减性。这样，对于每一个 $q$ 我们可以二分查找到它的所在段，然后根据增减性 $O(1)$ 地计算出答案。

由以上过程可知，该算法总复杂度为： $O(m^3log(m)+klog(m^2))$，可以通过本题。

要注意的细节：

1. kruskal 排序边权时，以加绝对值后的边权为第一关键字升序，以加绝对值前的边权为第二关键字降序排序，这样可以让每一段中的减函数尽可能多，保持答案最小的正确性。

2. 不开 long long 见祖宗。

3. 分段端点要去重。

参考代码（有点丑）：

```cpp
/*
  Author:Lucky_Yukikaze
  
*/
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define re register
#define pb push_back
#define mp make_pair
#define pf pop_front
#define pob pop_back
#define fr front
#define bk back

using namespace std;
typedef pair<int,int> pii;
typedef long double ld;
typedef pair<ll,ll> pll;

int n,m;

struct dsu{
	
	int fa[55];
	
	void init(int x){
		for(int i=1;i<=x;i++)fa[i]=i;
	}
	
	int getfa(int x){
		return (fa[x]==x)?(x):(fa[x]=getfa(fa[x]));
	}
	
	bool merge(int x,int y){
		int fx=getfa(x),fy=getfa(y);
		if(fx==fy)return false;
		else{
			fa[fx]=fy;
			return true;
		}
	}
	
}bcj;

struct edge{
	int u,v,w,ow;
}e[310],et[310];

struct point{
	int val,up;
}poi[90010],uni[90010];int tot=0,cnt=1;
int ans[90010];

int bins(int q){
	int l=1,r=cnt;
	int res;
	while(l<=r){
		int mid=(l+r)>>1;
		if(uni[mid].val<=q)res=mid,l=mid+1;
		else r=mid-1;
	}
	return res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);

	cin>>n>>m;
	
	
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	sort(e+1,e+1+m,[](edge tp1,edge tp2){return tp1.w<tp2.w;});
	
	for(int i=1;i<=m;i++){
		for(int j=i;j<=m;j++){
			poi[++tot].val=(e[i].w+e[j].w)/2+((e[i].w+e[j].w)%2);
		}
	}
	
	sort(poi+1,poi+1+tot,[](point tp1,point tp2){return tp1.val<tp2.val;});
	
	uni[1]=(point){0,0};
	for(int i=1;i<=tot;i++){
		if(poi[i].val!=uni[cnt].val){
			uni[++cnt].val=poi[i].val;
		}
	}
	
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=m;j++){
			et[j]=(edge){e[j].u,e[j].v,labs(e[j].w-uni[i].val),e[j].w};
		}
		sort(et+1,et+1+m,[](edge tp1,edge tp2){return (tp1.w==tp2.w)?(tp1.ow>tp2.ow):(tp1.w<tp2.w);});
		bcj.init(n);
		for(int j=1;j<=m;j++){
			if(bcj.merge(et[j].u,et[j].v)){
				ans[i]+=et[j].w;
				if(et[j].ow<=uni[i].val)uni[i].up++;
			}
		}
	}
	
	int p,k,a,b,c;
	
	cin>>p>>k>>a>>b>>c;
	
	int final=0;
	int q;
	for(int i=1;i<=p;i++){
		cin>>q;
		int pos=bins(q);
		int tp=((ans[pos])+(q-uni[pos].val)*uni[pos].up-(q-uni[pos].val)*(n-1-uni[pos].up));
		final^=tp;
	}
	
	for(int i=p+1;i<=k;i++){
		q=(q*a+b)%c;
		int pos=bins(q);
		int tp=((ans[pos])+(q-uni[pos].val)*uni[pos].up-(q-uni[pos].val)*(n-1-uni[pos].up));
		final^=tp;	
		}
	
	cout<<final;
	
	return 0;
}
```


---

## 作者：Purslane (赞：5)

## Solution

好题 . 赛时细节写挂 , 退役 . 

建议评分 : 蓝 / 紫 .

这里的绝对值是一个很烦人的东西 , 它会让每条边的权值发生改变 .

考虑 $\text{Kruscal}$ . 我们对一个图求 MST 时 , 需要的是 **边权之间的相对大小关系** , 只要我们知道谁大谁小就可以求出该种情况的 MST .

加上绝对值后 , 任意两个数之间的大小关系都可能发生改变 ( 除非它们相等 ) . 这意味着题目中所述的 $m$ 条边会有 $\frac{m(m-1)}{2}$ 种相对大小关系 . 发现 $m$ 很小 , 那么可以把这么多种相对大小关系的 MST 都预处理出来 . 时间复杂度为 $\text{O(m}^\text{3} \text{log m)}$ . 当然 , 双指针可以去掉 $\text{log}$ , 但是会麻烦一些 . 

> 对于两个数 $a$ 和 $b$ ( 不妨设 $a < b$ ) , 使它们相对大小发生改变的 $x$ 的临界值为 $\lceil \frac{a+b}{2} \rceil$ . 我们实际上把这些临界值排序去重 , 然后把这些值当做 $x$ 带入求 MST .

对于每一个询问 , 找到不比它大的最大临界值 , 就相当于找到了这时候的相对大小关系 , 也就知道那些边可以选 , 那些边不可以选 . 

剩下的操作就是基础前缀和了 .

复杂度 : $ \text{O(m}^\text{3} \text{log m+k log m)} $ . CF 的评测机还是相当快的 .

[code](https://codeforces.com/contest/1633/submission/145180541) 

---

## 作者：创世游戏科技 (赞：3)

# Spanning Tree Queries

## 题目大意

给定一个图，求每条边边权与 $q$ 的差的**绝对值之和最小**的生成树。

## 思路解析

首先考虑本题的一个简化版本，考虑所有使得构成生成树的边的集合不同的 $q$ 的区间的取值。

注意到**构成生成树的边的集合**只与边的大小关系有关。

因为如果边的大小关系确定了，那么排序后边的排列就已经确定，树边集合就是唯一确定的了。

所以我们需要考虑边的大小关系一共有多少种。

![](https://cdn.luogu.com.cn/upload/image_hosting/zaj9kysc.png)

这是边权分别取 $3$ , $4$ , $5$  的函数情况。

根据图像，我们发现边的大小关系只在交点处发生改变。

一共 $ m $ 条边，最多有 $\frac{m(m-1)}{2}$ 个交点，这启发我们预处理出来在交点处的边的情况。

而且从一个交点到下一个交点处，边权的增减性也是唯一确定的。

所以我们还要预处理出来这一段区间**边权递增的数量和递减的数量**。

我们发现一个边权递增当且仅当 $ L_i \leq W_i $，就是在未取绝对值之前值 $ val \geq 0 $ 。

但是遇到了一个严重的问题，有增有减，我们如何保证最小？这是我们要尽量保证我们选的边在边权小的同时更多的是那些递减的边，所以我们需要**以绝对值之差为第一关键字升序，以原边权为第二关键词降序排列。**

注意把 $ 0 $ 加入第一个区间。

那么在求答案的时候只需要二分查找出所在的区间，如果区间左端点为 $ L $ ，有 $b$ 个递增的区间，交点处的最小生成树权值和为 $ R $，那么最终答案就为 $ R+(q-L)[b+(n-1-b)]$，因为用递增的个数减去递减的个数就是单位变化量。

## 代码实现

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=310;
int n,m,d[MAXN*MAXN],cnt,fa[MAXN],mincost[MAXN*MAXN],add[MAXN*MAXN],q,p,k,ans,a,b,c;
struct node{
    int x,y,w,pw;
}e[MAXN],r[MAXN];
bool cmp(node x,node y){
    if(x.w==y.w)return x.pw>y.pw;
    return x.w<y.w;
}
int ce(int x,int y){
    return x/y+!!(x%y);
}
int find(int x){
    if(x==fa[x])return x;
    return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    int p1=find(x),p2=find(y);
    fa[p1]=p2;
}
int calc(int x){
    int now=upper_bound(d+1,d+1+cnt,x)-d-1;
    int delta=(x-d[now])*(add[now]-(n-1-add[now]));
    return mincost[now]+delta;
}
signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].x>>e[i].y>>e[i].w;
    }
    d[++cnt]=0;
    for(int i=1;i<=m;i++){
        for(int j=i;j<=m;j++){
            d[++cnt]=ce(e[i].w+e[j].w,2);
        }
    }
    sort(d+1,d+1+cnt);
    cnt=unique(d+1,d+1+cnt)-d-1;
    
    for(int i=1;i<=cnt;i++){
        memset(r,0,sizeof r);
        for(int j=1;j<=n;j++)fa[j]=j;
        for(int j=1;j<=m;j++)r[j]={e[j].x,e[j].y,abs(e[j].w-d[i]),e[j].w};
        sort(r+1,r+1+m,cmp);
        for(int j=1;j<=m;j++){
            int u=r[j].x,v=r[j].y;
            if(find(u)!=find(v)){
                merge(u,v);
                mincost[i]+=r[j].w;
                if(d[i]>=r[j].pw)add[i]++;
            }
        }
    }
    cin>>p>>k>>a>>b>>c;
    for(int i=1;i<=p;i++){
        cin>>q;
        ans^=calc(q);
    }
    for(int i=p+1;i<=k;i++){
        q=(q*a+b)%c;
        ans^=calc(q);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：jun头吉吉 (赞：3)

## 题意
$k$ 次询问，每次询问边权是 $|w_i-x|$ 时的最小生成树。

$n\le 50,m\le 300,k\le 10^7$，保证联通。
## 题解
怎么题解全是 $\mathcal O(m^3\log m+k\log m)$ 的啊，这里介绍一种 $\mathcal O(m^2\alpha(m)\log W+k\log m)$ 的方法。

首先这个 $|w_i-x|$ 是凸的，凸的有什么性质呢？经过一些人类智慧我们发现一条边出现在最小生成树上的 $x$ 是一段连续的区间，证明交（wo）给（ye）读（bu）者（hui）自（zheng）证（ming）。

反正我们现在是有这个结论了，看上去非常靠谱。然后我们就能够直接二分找到这个区间的左端点和右端点了。把每条边的贡献区间算出来之后我们就能直接用前缀和计算每个 $x$ 对应的值了。

提交时是洛谷rk1。

其实还有更优的复杂度，可以去做一做【JOISC2022】复兴计划，等以后会了之后再来补。

## 代码
直接模拟。
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back
#define pc putchar
#define chkmx(a,b) (a)=max((a),(b))
#define chkmn(a,b) (a)=min((a),(b))
#define fi first
#define se second
using namespace std;
template<class T>
void read(T&x){x=0;char c=getchar();bool f=0;for(;!isdigit(c);c=getchar())f^=c=='-';for(;isdigit(c);c=getchar())x=x*10+c-'0';if(f)x=-x;}
template<class T,class ...ARK>void read(T&x,ARK&...ark){read(x);read(ark...);}
template<class T>void write(T x){if(x<0)pc('-'),x=-x;if(x>=10)write(x/10);pc(x%10+'0');}
template<class T,class ...ARK>void write(T x,ARK...ark){write(x);pc(' ');write(ark...);}
template<class ...ARK>void writeln(ARK...ark){write(ark...);pc('\n');}
typedef long long ll;
const int mod=998244353;
struct mint{
	int x;mint(int o=0){x=o;}mint&operator+=(mint a){return(x+=a.x)%=mod,*this;}mint&operator-=(mint a){return(x+=mod-a.x)%=mod,*this;}
	mint&operator*=(mint a){return(x=1ll*x*a.x%mod),*this;}mint&operator^=( int b){mint a=*this;x=1;while(b)(b&1)&&(*this*=a,1),a*=a,b>>=1;return*this;}
	mint&operator/=(mint a){return*this*=(a^=mod-2);}friend mint operator+(mint a,mint b){return a+=b;}friend mint operator-(mint a,mint b){return a-=b;}
	friend mint operator*(mint a,mint b){return a*=b;}friend mint operator/(mint a,mint b){return a/=b;}friend mint operator^(mint a, int b){return a^=b;}
};
#define lowbit(x) ((x)&-(x))
#define mid ((l+r)>>1)
#define lc (x<<1)
#define rc (x<<1|1)
const int N=1e5+10;
int n,m,q,k,lst,a,b,c,u[N],v[N],w[N],p[N];
int sa1[N],sa2[N];
int fa[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(int x,int y){x=find(x),y=find(y);fa[x]=y;}
bool chk(int x,int i){
	//边i是否在x时的生成树内。
	//先写 m log m，可以优化到 m α(m)
	vector<pair<int,int>>e(m),a,b;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)if(w[sa1[i]]>=x)a.eb(w[sa1[i]]-x,sa1[i]);
	for(int i=1;i<=m;i++)if(w[sa2[i]]<x)b.eb(x-w[sa2[i]],sa2[i]);
	merge(a.begin(),a.end(),b.begin(),b.end(),e.begin());
	for(auto E:e){
		int id=E.se;
		if(find(u[id])^find(v[id])){
			merge(u[id],v[id]);
			if(id==i)return 1;
		}
		if(id==i)return 0;
	}
	exit(1);
}
tuple<int,int,int>kk[N];//贡献
int cnt=0;
int pos[N];ll coef1[N],coef2[N];
ll calc(int x){
	int p=upper_bound(pos+1,pos+1+cnt,x)-pos-1;
	//writeln(coef1[p]*x+coef2[p]);
	return coef1[p]*x+coef2[p];
}
signed main(){
	read(n,m);
	for(int i=1;i<=m;i++)read(u[i],v[i],w[i]);
	iota(sa1+1,sa1+1+m,1);sort(sa1+1,sa1+1+m,[&](int i,int j){return w[i]==w[j]?i<j:w[i]<w[j];});
	iota(sa2+1,sa2+1+m,1);sort(sa2+1,sa2+1+m,[&](int i,int j){return w[i]==w[j]?i<j:w[i]>w[j];});
	read(q,k,a,b,c);
	for(int i=1;i<=m;i++){
		if(!chk(w[i],i))continue;
		int st=w[i],ed=w[i],l,r;
		l=0,r=w[i];while(l<=r)if(chk(mid,i))st=mid,r=mid-1;else l=mid+1;
		l=w[i],r=1e8;while(l<=r)if(chk(mid,i))ed=mid,l=mid+1;else r=mid-1;
		//存在的区间就是 [l,r]
		kk[++cnt]=mt(st,-1,w[i]);
		kk[++cnt]=mt(w[i]+1,2,-2*w[i]);
		kk[++cnt]=mt(ed+1,-1,w[i]);
	}
	sort(kk+1,kk+1+cnt);
	for(int i=1;i<=cnt;i++)
		pos[i]=get<0>(kk[i]),
		coef1[i]=coef1[i-1]+get<1>(kk[i]),
		coef2[i]=coef2[i-1]+get<2>(kk[i]);
	ll ans=0;int lst=0;
	for(int i=1;i<=q;i++)read(lst),ans^=calc(lst);
	for(int i=q+1;i<=k;i++)lst=(1ll*lst*a+b)%c,ans^=calc(lst);
	writeln(ans);
}
```

---

## 作者：qzhwlzy (赞：2)

### 大意
有一有 n 个节点和 m 条边的加权连通无向图。有 k 次询问，每次给出一个整数 $q_i$，求所有生成树中 $\sum\limits_{j=1}^{
n-1}|w_j-q_i|$（$w_j$ 为生成树各边的权值）的最小值。输出各次询问答案的异或和。
### 思路

我们先思考暴力的思路：也就是每次读入时计算每条边的权值，然后 Kruskal 即可，但是这样显然复杂度太高。于是我们思考，可不可以少进行几次算法呢？
我们发现，对于固定的 $w_1$ 与 $w_2$，改变 q 的值时，$|w_1-q|$ 和 $|w_2-q|$ 的大小关系不总是会改变。比如说，[如图](https://img2022.cnblogs.com/blog/2345790/202202/2345790-20220211164028773-2123928017.gif)，我们取 $w_1 = -3,w_2 = 1$ 进行模拟，画出 $y=|x-q|$ 的函数图像，在 x=-3 和 x=1 时取函数上的点 A 和 B。我们发现有 $\begin{cases}|w_1-q|<|w_2-q|&q\in(-\infty,-1)\\|w_1-q|=|w_2-q|&q=-1\\|w_1-q|>|w_2-q|&q\in(-1,+\infty)\end{cases}$ 。由此，我们可以推出，$\forall w_1,w_2(w_1 < w_2),\begin{cases}|w_1-q|<|w_2-q|&q\in(-\infty,\dfrac{w_1+w_2}{2})\\|w_1-q|=|w_2-q|&q=\dfrac{w_1+w_2}{2}\\|w_1-q|>|w_2-q|&q\in(\dfrac{w_1+w_2}{2},+\infty)\end{cases}$。

同时我们注意到，在一定范围内，q 改变时，边权的大小关系是一定的，最终结果与 q 的变化量是呈一次函数关系（因为 q+1 时，所有 $|w_i-q|$ 对应 +1 或 -1）。因此，我们按照所有的 $w_i$ 和所有的 $\dfrac{w_i+w_j}{2}$ 把数轴零点分段，并计算出改变 q 时最终结果的增减量，最后输入 q 时二分查找其所在段，根据增减量处理出答案即可。  

- Q：为什么所有的 $w_i$ 要算作零点？
- A：[如图](https://img2022.cnblogs.com/blog/2345790/202202/2345790-20220211164439110-419899053.gif)，我们发现，在 $(-\infty,w_i]$ 和 $[w_i,+\infty)$ 上，$y=|w_i-q|$ 的增减性并不相同，所以为了不影响答案计算（见 $Q\&A\ 4$），我们将 $w_i$ 也纳入零点中。


- Q：如何计算 q 增加时有多少的 $|w_i-q|$ 会增加？
- A：如上图，当 $w_i<q$ 时，$|w_i-q|$ 随 q 增加而增大，反之亦然。所以我们只需要统计多少 $w_i<q$ 即可。

- Q：为什么排序这么排？
- A：首先，第一关键字是 $|w_i-q|$，升序排序，这是显然的。第二关键字是 $w_i$，降序排列，使得MST选到的边多为 $w_i>q$ 的，使得最终答案最小（原因见 $Q\&A\ 2\And4$）。

- Q：结果怎么算？
- A：首先，假设二分出来的零点为 res，该零点处的 MST 答案为 $mst_{res}.cost$，由于最终结果与 q 的变化量是一次函数关系，所以最终结果 $=mst_{res}.cost+(\Delta q\times up-\Delta q\times(n-1-up))$（up 为随 q 增加而增加的 $|w_i-q|$ 数量，又由于生成树一共是 n-1 条边，固有 (n-1-up) 条边的 $|w_i-q|$ 随 q 增加而减小）。
### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
#define maxn 55
#define maxm 305
using namespace std;
ll n,m,u[maxm],v[maxm],w[maxm],p,k,aa,bb,cc,q;
struct node{
	ll from,to,dis,oridis;//两个端点、|w[i]-q|和原来的权值
}a[maxm];
struct msts{
	ll cost,up;//统计零点的MST价值和q增加时有多少|w[i]-q|会增加
}mst[maxm*maxm];
ll ld[maxm*maxm],len=0;//零点
ll f[maxn];
ll aabs(ll x) {return x<0?-x:x;}
bool cmp(node aaa,node bbb) {if(aaa.dis==bbb.dis) return aaa.oridis>bbb.oridis;else return aaa.dis<bbb.dis;}
void clear() {for(ll i=1;i<=n;i++) f[i]=i;}
ll ffind(ll x) {if(f[x]==x) return x;else return f[x]=ffind(f[x]);}
ll bisearch(ll q){//二分查找所属区间
	ll l=1,r=len,res=0,mid=0;
	while(l<=r){
		mid=(l+r)/2;
		if(q<ld[mid]) r=mid-1;else {res=mid;l=mid+1;}
	}
	return res;
}
int main(){
	//输入图的点和边 
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=m;i++) scanf("%lld%lld%lld",&u[i],&v[i],&w[i]);
	//处理所有零点 
	ld[++len]=0;
	for(ll i=1;i<=m;i++){
		for(ll j=i;j<=m;j++){
			ld[++len]=(w[i]+w[j])/2+((w[i]+w[j])%2);//将所有端点存入数组
		}
	}
	sort(ld+1,ld+1+len); len=unique(ld+1,ld+1+len)-ld-1;//排序+去重
	//处理所有零点的MST权值和 
	for(ll i=1;i<=len;i++){
		for(ll j=1;j<=m;j++){
			a[j]=(node){u[j],v[j],aabs(w[j]-ld[i]),w[j]};
		}
		sort(a+1,a+1+m,cmp);
		clear();
		for(ll j=1;j<=m;j++){
			ll r1=ffind(a[j].from),r2=ffind(a[j].to);
			if(r1!=r2) {f[r2]=r1;mst[i].cost+=a[j].dis;if(a[j].oridis<=ld[i]) mst[i].up++;}
		}
	}
	//读入并处理答案 
 	scanf("%lld%lld%lld%lld%lld",&p,&k,&aa,&bb,&cc);
	ll res,ans=0;
 	for(ll i=1;i<=k;i++){
		if(i<=p) scanf("%lld",&q);else q=(q*aa+bb)%cc;
		res=bisearch(q);//二分
		ans^=(mst[res].cost+(q-ld[res])*(mst[res].up-(n-1-mst[res].up)));//答案
//		printf("%d ",(mst[res].cost+(q-ld[res])*(mst[res].up-(n-1-mst[res].up))));
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：intel_core (赞：1)

首先注意到这个题 $n,m$ 比较小，但 $k,q_i$ 比较大，所以可以想到先处理好答案然后查询的时候直接二分。

考虑现在将 $q$ 固定，设边的边权为 $v_1 \le v_2 \le \cdots \le v_t \le q \le v_{t+1} \le \cdots \le v_m$ ，则不难发现 $|v_1-q| \ge |v_2-q| \ge \cdots \ge |v_t-q|$ ， $|v_{t+1}-q| \le|v_{t+2}-q| \le \cdots \le |v_m-q|$。 

然后注意到边权转换后的同侧的差是固定的，所以对于 $q$ 遍历一遍整数域，边权的大小关系只有 $O(m^2)$ 种。

然后我们就可以开心地 $\text{Kruskal}$ 了，复杂度 $O(m^3 \log m+k)$。 

另：如果把所有询问的 $q$ 用基排排序然后扫一遍可以做到 $O(k)$ 求答案，但每次二分 $O(k \log m)$ 也可以。

---

## 作者：I_am_Accepted (赞：1)

### Preface

一定要把代码写清楚了！不然赛后订正很痛苦。（我重写了）

赛时写出来但调了一刻钟无果，我选择死亡。

### Analysis

询问 $10^7$，明显回答时间不能超过 $\log$。那我们前期要预处理更多。

发现这是**带绝对值最小生成树**问题。遇到绝对值要分类，但是分成 $m$ 类好像不行……

回顾 Kruskal 的算法过程，发现如果边之间边权的大小关系确定了，那么贪心的排序就可以实现了。而大小关系在 $Q$（询问的数）不同时最多只有 $O(m^2)$ 种不同的边权的大小关系。因为考虑 $Q$ 从 $-\infty$ 到 $\infty$ 的过程，边权 $\le Q$ 的带绝对值边权在递增，而边权 $>Q$ 的递减，只有当 一个边权从 $>Q$ 变为 $\le Q$  或 一个绝对值边权与另一个绝对值边权的大小关系发生变化 时，才会有新的边权的大小关系出现，而 $m$ 个边权里选两个取平均数的规模是 $O(m^2)$ 的。

我们就得到了一些值 $Gap$（按升序排）来划分 $Q$ 的值域，使得 $Q$ 在每一段内时，绝对值边权的大小关系不变。

我们对于每个区间选最大的 $Q$ 为代表值，用她 $|Q-w_i|$ 这样的边权跑 Kruskal，同时记录最小生成树中有多少边本来的边权 $<Q$（在保证生成树最小时尽量使这个值最大，请读者思考）。

当询问时，二分到这段区间，通过代表值的答案来 $O(1)$ 推导答案即可。

时间 $O(m^3\log m\times\alpha(n)+k\log m)$。

### Code

[Link](https://codeforces.com/contest/1633/submission/145942192)

---

## 作者：hyman00 (赞：0)

## 001 做法

### 思路1

看到这个题，第一想法就是暴力，用并查集求 MST，复杂度 $O(kmlogm)$，肯定过不了。

### 思路2

发现答案是要求异或，就可以用 map 去重，但发现不仅没用，map 本身还慢！

$p=1,k=10^7,a=1,b=1,c=10^7,q_1=0$ 的时候 $q$ 就是 $0,1,2,\dots,10^7-1$，去重一点用没有。

### 思路3

题目中的图只有 $50$ 个点，$300$ 条边，因此不同的有可能作为答案的 $MST$ 只有 $O(m^2)$ 级别的！

于是可以预处理：

先计算 $x=0$ 时的 $MST$（以后记为 $go(0)$），然后二分下一个不同的 $MST$ 的 $x$ 最小是几。

复杂度 
$$
O(m^2*logA*mlogm+kn)=O(m^3logAlogm+kn)
$$
（$A$是值域）

### 思路4

预处理中的二分其实是不必要的

发现只有
$$
\left\lfloor\frac{w_i+w_j}{2}\right\rfloor-1,\left\lfloor\frac{w_i+w_j}{2}\right\rfloor,\left\lfloor\frac{w_i+w_j}{2}\right\rfloor+1
$$
是有用的，复杂度降为
$$
O(m^2*mlogm+kn)=O(m^3logm+kn)
$$
已经足够 $AC$！

## 002 代码

[本蒟蒻代码](https://codeforces.com/contest/1633/submission/144810641)

---

