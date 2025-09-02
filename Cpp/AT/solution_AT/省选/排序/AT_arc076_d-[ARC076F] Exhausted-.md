# [ARC076F] Exhausted?

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc076/tasks/arc076_d

椅子が $ M $ 個数直線上に並んでおり、$ i $ 番目の椅子 $ (1\ ≦\ i\ ≦\ M) $ は座標 $ i $ にあります。

高橋君が $ N $ 人います。高橋君たちはゲームのやりすぎで全員腰を痛めたため、どこかの椅子に座る必要があります。 各々の高橋君たちが座る椅子にはこだわりがあって、$ i $ 人目の高橋君は座標 $ L_i $ 以下、もしくは座標 $ R_i $ 以上の椅子に座りたいです。当然ながら、同じ椅子には $ 1 $ 人しか座れません。

このままでは、高橋君たち全員を椅子に座らせることができないかもしれません。 高橋君たちの健康管理に気を遣っている青木君は、椅子をできるだけ少ない数追加することで、 高橋君たち全員のこだわりを満たすように高橋君たちを椅子に座らせることができるようにしたいです。

椅子は、任意の実数座標に追加できます。追加する必要のある椅子の最小の個数を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N,M\ ≦\ 2\ ×\ 10^5 $
- $ 0\ ≦\ L_i\ <\ R_i\ ≦\ M\ +\ 1(1\ ≦\ i\ ≦\ N) $
- 入力は全て整数である

### Sample Explanation 1

$ 4 $ 人の高橋君を順に座標 $ 3,2,1,4 $ にある椅子に座らせることができるため、椅子を追加する必要はありません。

### Sample Explanation 2

座標 $ 0 $ と $ 2.5 $ に椅子を追加すれば、$ 7 $ 人の高橋君を順に座標 $ 0,5,3,2,6,1,2.5 $ に座らせることができます。

## 样例 #1

### 输入

```
4 4
0 3
2 3
1 3
3 4```

### 输出

```
0```

## 样例 #2

### 输入

```
7 6
0 7
1 5
3 6
2 7
1 6
2 6
3 7```

### 输出

```
2```

## 样例 #3

### 输入

```
3 1
1 2
1 2
1 2```

### 输出

```
2```

## 样例 #4

### 输入

```
6 6
1 6
1 6
1 5
1 5
2 6
2 6```

### 输出

```
2```

# 题解

## 作者：asuldb (赞：17)

hall定理大概是匈牙利的理论基础吧

hall定理的内容：**二分图$G$的的左部点点集为$\rm X$，右部点点集为$\rm Y$，设$|\rm X|\leq |Y|$，则二分图$G$存在完美匹配，即匹配个数为$|\rm X|$当且仅当，对于$\rm X$的任一子集$\rm X'$，满足$|\rm X'|\leq |\rm Nb(X')|$，$\rm Nb(X')$为$\rm X'$的邻居点集**

必要性显然，考虑证明其充分性。

使用反证法，对于一张满足hall定理的二分图，设其不存在完美匹配，我们找到$\rm X$中一个不在最大匹配中的点，由于满足hall定理这个点一定连向了$\rm Y$中某些点，又因为该点不在最大匹配中，那么其连向的点都已经跟其他点匹配；我们再把跟这些点匹配的点考虑进来，根据hall定理，我们还能找到一些跟这些点相连但已经匹配的点，再把跟这些匹配的点考虑进来；最后不难推出，不存在满足hall定理但不存在完美匹配的二分图。

hall定理还有一条推论:**二分图$G$的最大匹配为$|\rm X|-\max(|X'|-|Nb(X')|)$**，这条推论对于我们求二分图最大匹配有一定启发

对于这道题，可以显然的构造一个二分图模型，答案就是n-最大匹配；

直接建图是不可取的，考虑使用上面的推论，我们需要找到一个$\rm X'$使得$\rm |X'|-|Nb(X')|$即可

对于第$i$个人他可以连边的区间是$[1,l_i]\cup [r_i,m]$，由于$\rm Nb(X)$本质上是点集的并，而这样不是很好考虑；于是我们做一个简单的转化，我们求一下不能连边的区间的交，对全集取一个补集得到的就是区间的并

于是我们的目标是找到一个集合$S$，最大化

$$|S|-(m-|\cap_{i\in S}(l_i,r_i)|)=|S|+|\cap_{i\in S}(l_i,r_i)|-m$$

先来考虑没有交的情况，那么只需要让$|S|$最大，于是答案就是$n-m$

再来考虑有交的情况，之后对于当前的一个区间$(l_i,r_i)$我们考虑交的左端点为$l_i$的时候的答案是多少，那么交为$(l_i,k)$的时候的答案就是$k-l_i+\sum [r_j\geq k][l_j\leq l_i]$；于是把区间排序之后线段树+扫描线维护即可。

代码

```cpp
#include<bits/stdc++.h>
#define re register
#define min(a,b) ((a)<(b)?(a):(b))
const int maxn=2e5+5;
struct Seg{int x,y;}a[maxn];
int n,m,ans;
inline int cmp(const Seg A,const Seg B) {return A.x==B.x?A.y>B.y:A.x<B.x;}
int l[maxn<<2],r[maxn<<2],tag[maxn<<2],mx[maxn<<2];
inline int max(int a,int b) {return a>b?a:b;}
inline void add(int i,int v) {tag[i]+=v,mx[i]+=v;}
inline void pushup(int i) {mx[i]=max(mx[i<<1],mx[i<<1|1]);}
void build(int x,int y,int i) {
	l[i]=x,r[i]=y;tag[i]=0;if(x==y){mx[i]=x;return;}
	int mid=x+y>>1;build(x,mid,i<<1),build(mid+1,y,i<<1|1);pushup(i);
}
inline void pushdown(int i) {
	if(!tag[i]) return;
	add(i<<1,tag[i]),add(i<<1|1,tag[i]);tag[i]=0;
}
void change(int x,int y,int v,int i) {
	if(x<=l[i]&&y>=r[i]) {add(i,v);return;}
	int mid=l[i]+r[i]>>1;pushdown(i);
	if(x<=mid) change(x,y,v,i<<1);
	if(y>mid) change(x,y,v,i<<1|1);
	pushup(i);
}
int query(int x,int y,int i) {
	if(x<=l[i]&&y>=r[i]) return mx[i];
	int mid=l[i]+r[i]>>1;pushdown(i);
	if(y<=mid) return query(x,y,i<<1);
	if(x>mid) return query(x,y,i<<1|1);
	return max(query(x,y,i<<1),query(x,y,i<<1|1));
}
int main() {
	scanf("%d%d",&n,&m);
	for(re int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
	std::sort(a+1,a+n+1,cmp);int nl=0,nr=m+1;
	for(re int i=1;i<=n;i++) nl=max(nl,a[i].x),nr=min(nr,a[i].y);
    ans=n+(nl<nr?nr-nl-1:0);
	build(0,m+1,1);
	for(re int i=1;i<=n;i++) {
		int nw=query(a[i].x+1,a[i].y,1);
		ans=max(ans,nw-a[i].x);
		change(0,a[i].y,1,1);
	}
	printf("%d\n",ans>m?ans-m:0);return 0;
}
```

---

## 作者：ezoiLZH (赞：13)

**我的[blog](https://www.cnblogs.com/ezoiLZH/p/9492929.html)**

## 题解
第一眼贪心，结果没过样例，就暴力打了个网络流。（结果我那个WA的贪心竟然比网络流高？！）

其实是我少考虑了。首先是如果是只有 $L$ 限制或是 $R$ 限制，那么很明显，先排序一遍，从两边开始往中间扫，能塞就塞，塞不了就加点。

但是，有了两个限制？我之前是按 $L$ 作为第一关键字，$R$ 作为第二关键字排序，但显然 $R$ 不单调，直接贪心显然WA。

我们再考虑一下，如果左边塞不下了，那么无论如何，都要有一个人坐到右边，那么我们可以吧左边有位置的一个人踢出来，让他坐在右边。那我们肯定是吧 $R$ 小的踢出来（容错率高）。

那就好办了，我们往左边塞的时候，坐不下就把 $R$ 最小的踢掉，可以用小根堆维护。把左边塞完之后，再把没座位的，以同样的方法往右边塞，实在没办法就只能补了。

## CODE：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

int n,m,ans=0,tmp[200005];
struct Student{
	int l,r;
	bool operator<(const Student &b)const{
		return l!=b.l?l<b.l:r>b.r;
	}
}s[200005];
priority_queue<int,vector<int>,greater<int> > q;

int main(){
//	freopen("data.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&s[i].l,&s[i].r);
	sort(s+1,s+n+1);
	int h=1,t=m;
	for(int i=1;i<=n;i++){
		q.push(s[i].r);
		if(h<=t&&h<=s[i].l)h++;
		else{
			tmp[++tmp[0]]=q.top();
			q.pop();
		}
	}
	sort(tmp+1,tmp+tmp[0]+1);
	for(int i=tmp[0];i>=1;i--){
		if(h<=t&&tmp[i]<=t)t--;
		else ans++;
	}
	printf("%d",ans);
}
```

---

## 作者：Krimson (赞：7)

又一道水黑?~~AT水黑还蛮多的~~  

首先先转换一下题意,即在不添加椅子的情况下保证能让最多的人做上椅子  
而题目的限制可以转换为有$n$个人,每个人都向坐标小于等于$l_i$或者大于等于$r_i$的椅子连边,问最大匹配个数  
~~于是就成了二分图匹配了?~~    

看一眼数据范围$n,m<2e5$,这显然没法直接二分图匹配啊~~如果有人曾发明出什么O(n)匈牙利算法那当我没说~~   
那么便去模拟一下二分图匹配的流程,去枚举当前的每一个点看有没有可以匹配的,如果没有的话就去做一个"增广路"  

但是同时有$l,r$的限制也太麻烦了  
于是试着去删掉一个维度的限制,先按照$l$排序,再去枚举点看能不能匹配$l$,当$l$无法匹配的时候再去$r$上找  
```cpp
for(ri i=1;i<=n&&L<=R;++i){
    if(L<=a[i].l) ++L,++ans;
}
```

这里有一个很显然的贪心是在当前枚举到的点$i$无法满足在$l_i$上找到椅子的时候,比起直接去$r_i$上找,一定是让在之前满足$l_j$且$r_j<r_i$的点去把位置让出来给$i$让后让$j$去$r_j$范围的椅子更优(显然$r_j$越小可以选择的范围就越大)  
这个过程可以用一个小顶堆来维护~~反悔贪心？~~  
```cpp
for(ri i=1;i<=n&&L<=R;++i){//s是无法匹配的人
      if(L<=a[i].l) ++L,++ans,q.push(a[i]);
      else{            
          if(!q.empty()&&a[i].r>q.top().r){
              s.push_back(q.top());
              q.pop();
              q.push(a[i]);
          }
          else s.push_back(a[i]);
      }
  }
```

  
最后会剩下一堆无法匹配$l$的点,用这些点去跟之前匹配$l$的时候一样操作就好了.
```cpp
for(ri i=0;i<s.size()&&R>=L;++i){
    if(R>=s[i].r) ++ans,--R;
}
``` 
  
代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
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
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
int n,m;
const int MAXN=2e5+7;
struct node
{
    int l,r,id;
    bool operator<(const node &x)const{
        return l==x.l?r>x.r:l<x.l;
    }
}a[MAXN];
struct cmp
{
    bool operator()(const node &x,const node &y)const{return x.r>y.r;}
};
bool Cmp(const node &x,const node &y){
    return x.r>y.r;
}
priority_queue<node,vector<node>,cmp> q;
vector<node> s;
int L,R,ans;
int main(){
    n=read(),m=read();
    for(ri i=1;i<=n;++i){
        a[i].l=read(),a[i].r=read(),a[i].id=i;
    }
    sort(a+1,a+n+1);
    L=1,R=m;
    for(ri i=1;i<=n&&L<=R;++i){
        if(L<=a[i].l) ++L,++ans,q.push(a[i]);
        else{            
            if(!q.empty()&&a[i].r>q.top().r){
                s.push_back(q.top());
                q.pop();
                q.push(a[i]);
            }
            else s.push_back(a[i]);
        }
    }
    sort(s.begin(),s.end(),Cmp);
    for(ri i=0;i<s.size()&&R>=L;++i){
        if(R>=s[i].r) ++ans,--R;
    } 
    print(n-ans);
    return 0;
}
```


---

## 作者：tommymio (赞：5)

### Method 1

设 $s_i$ 表示位置 $i$ 可能被选中的次数。

从 $1\sim n$ 遍历每个区间 $[l_i, r_i]$，将 $j\in[1, l_i]\cup[r_i, m]$ 的 $s_j$ 加上 $1$，并查询 $\max_{j\in [1, l_i]\cup[r_i, m]} s_j $ 是否大于 $m - (r_i - l_i - 1)$，如果大于则将 $j\in[1, l_i]\cup[r_i, m]$ 的 $s_j$ 加上 $-1$，并将答案 $+1$。

这么做的依据是，如果两段区间内没有大于区间总长度的 $s_j$，说明 $1\sim i$ 个人的约束能够使得存在一种方案，每个人在两段区间内都有位置坐，这是非常好证明的。而如果存在了这样的 $s_j$，说明 $s_j$ 恰好大于区间长度，这个人是没有位置坐的，必须加一个位置给他。这样的话第 $i$ 个人对应的位置已经被确定，且不在两段区间的整点上，所以对两段区间的 $s_j$ 都没有影响，需要 $-1$ 撤回 $+1$ 的影响。

### Method 1.5

我们可以将 $r_i$ 升序排序，使用数据结构维护 $l_i$。

注意到排序后 $r_i$ 升序，所以我们可以前缀和维护 $[r_i, m]$ 的 $+1/-1$ 操作，并且使用数据结构维护 $[1, l_i]$ 的 $+1/-1$ 操作和 $\max$ 查询。

这好像并没有什么变化。

### Method 2

问题模型是匹配模型。将每个人和所能坐的椅子连边，答案为 $n$ 减去最大匹配数。

不太能模拟网络流，也不太能优化建图然后跑网络流。似乎只剩下匹配特化的工具可以用了，想到 $\text{Hall}$ 定理。

> 对于一个二分图，存在完美匹配当且仅当所有左部点 $S$ 的子集 $S'$ 满足 $|S'|\leq|N(S')|$，其中 $N(S')$ 是 $S'$ 的邻域。

想到什么？对于 **Method 1** 的做法而言，本质上就是维护第 $1\sim i$ 个人的约束，并且通过添加椅子使得永远满足 $\text{Hall}$ 定理的充要条件。

$\text{Hall}$ 定理还有一条引理：

> 对于一个二分图，它的最大匹配数是左部点 $S$ 的个数 $|S| -  \max_{S'\in S} \{|S'| - |N(S')|\}$。

我们很难去枚举 $S'$，因为个数是 $2^n$ 的，但我们可以枚举 $S'$ 对应的 $N(S')$，这必然对应着某个 $S'$，而且必然是一个前缀和一个后缀的并。注意，这里的前缀和后缀可能来自于不同的两个人，并且**如果枚举的前后缀是取得最大匹配的前后缀的一个超集的话，答案一定不优**。

考虑确定一组前缀和后缀 $[1,L],[R,m]$ 后，即 $N(S')$，如何求 $|S'|$。不妨记 $|S'| = f(L,R)$。注意到满足 $l_i \leq L, r_i \geq R$ 的人必然在 $S'$ 中，这样我们就有了一个 $|S'|$ 的求法。

根据引理，最大匹配数为 $n - \max_{1\leq L\leq R\leq m}\{f(L, R) - (m - (R - L - 1))\}$，直接扫描线即可。具体来说，就是将 $l_i$ 从小到大排序，然后使用区间数据结构维护 $r_i$ 的这一维。

---

## 作者：Crane_w (赞：5)

# ARC076 F - Exhausted?



## [题目大意]

有 $m$ 个座位，分别位于坐标为 $1,2,3,...,m$ 的地方；$n$ 个客人，第 $i$  位客人只坐位于 $[0,li]∪[ri,m]$ 的座位。每个座位只能坐一个，问最少需要添加几个座位才能使所有人坐下？

## [Solution]

本题考察对霍尔定理的理解， 对于二分图 $G=<V_1, V_2, E>$ ,  设 $ |V_1| < |V_2|$ , 则 $G$ 中存在 $V_1$  到 $V_2$ 的完美匹配当且仅当对于任意 $S\subset V_1$，对于 $S$ 的邻域 $N(S)$, 均有 $|S| \le |N(S)| $。

而霍尔定理有一个推论， 就是若使 G 中存在完美匹配， 则最少补充 $\max\{0, |S| - |N(S)|\}$ 条边。



回到本题，对于一个人，把他看做左部点，把座位 1 到 m 看做右部，将客人向所有 $i\in[1, l_i] \cup [r_i, m]$ 连边。

因为左部S所对应的右部节点的形式为 $[1, l] \cup [r, m]$ 节点数为 $m - (r - l + 1）= m - r + l - 1$ 。

那么依据霍尔定理， 答案就是 $|S| - m + r - l + 1$。

那么，求出上述式子的最大值即可，但是枚举 $S$ 的复杂度太高，于是考虑右部区间 $[L, R]$ 找出对应的左部节点，所以可以将人 $l_i, r_i$ 按 $l_i$ 升序，建一棵线段树存储 $r_i$，将右部节点映射上去， 并把初值设为 $i$。迭代  $l$ ，每次将左端点是 $l$ 的 $r_i$,更新入线段树,即将 $[l, r]$ 区间加一，每次求出 $[L, m]$ 的最大值。

对于  $r_i = m + 1$  的点，在额外建一个点  $m + 1$ 存储即可。

```cpp
#include <bits/stdc++.h>
#define for_(i,a,b) for (ll i = (a); i < (b); i++)
#define rep_(i,a,b) for (ll i = (a); i <= (b); i++)
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
#define sz(a) a.size()
#define all(v) v.begin(), v.end()
#define int long long
using namespace std;
const int maxn = 5e5 + 10, mod = 1e9 + 7;// mod = 1949777;
const double EPS = 1e-3;
int n, m;
vector<int> a[maxn];
struct segment_tree{
    int N;
    long long P;
    vector<long long> ST, A, M, F; // A -> tag add  / M -> tag mul /F -> tag max
    segment_tree(int n) {
        N = 1;
        while(N < n) {
            N *= 2;
        }
        ST = vector<long long>(4 * N - 1, 0);
        A = ST;
        M = vector<long long>(4 * N - 1, 1);
        F = A;
        P = 1e15;
    }
    void pushdown(int s, int t, int p) {
        int l = 2 * p, r = 2 * p + 1, mid = s + ((t - s) >> 1);
        if (M[p] != 1) {
            M[l] *= M[p], M[l] %= P;
            A[l] *= M[p], A[l] %= P;
            ST[l] *= M[p], ST[l] %= P;
            F[l] *= M[p], F[l] %= P;
            M[r] *= M[p], M[r] %= P;
            A[r] *= M[p], A[r] %= P;
            ST[r] *= M[p], ST[r] %= P;
            F[r] *= M[p], F[r] %= P;
            M[p] = 1;
        }
        if (A[p] != 0) {
            ST[l] += A[p] * (mid - s + 1), ST[l] %= P;
            A[l] += A[p], A[l] %= P;
            F[l] += A[p], F[l] %= P;
            ST[r] += A[p] * (t - mid), ST[r] %= P;
            A[r] += A[p], A[r] %= P;
            F[r] += A[p], F[r] %= P;
            A[p] = 0; 
        }
        return;
    }
    void pushup(int p) {
        int l = 2 * p, r = 2 * p + 1;
        ST[p] = (ST[l] + ST[r]) % P;
        F[p] = max(F[l], F[r]);
        return;
    }
    void mul(int l, int r, int c, int s, int t, long long p) {
        if (l <= s && t <= r) {
            M[p] *= c, A[p] *= c, ST[p] *= c;
            M[p] %= P, A[p] %= P, ST[p] %= P;
            F[p] *= c, F[p] %= P;
            return;
        }
        int mid = s + ((t - s) >> 1);
        pushdown(s, t, p);
        if (l <= mid) mul(l, r, c, s, mid, p * 2);
        if (mid < r) mul(l, r, c, mid + 1, t, p * 2 + 1);
        //(ST[p] = ST[p * 2] + ST[p * 2 + 1]) %= P;
        pushup(p);
    }
    void add(int l, int r, int c, int s, int t, long long p) {
        if (l <= s && t <= r) {
            ST[p] += (t - s + 1) * c; ST[p] %= P;
            A[p] += c; A[p] %= P;
            F[p] += c, F[p] %= P;
            return;
        }
        int mid = s + ((t - s) >> 1);        
        pushdown(s, t, p);
        if (l <= mid) add(l, r, c, s, mid, 2 * p);
        if (mid < r) add(l, r, c, mid + 1, t, 2 * p + 1);
        //(ST[p] = ST[2 * p] + ST[2 * p + 1]) %= P;
        pushup(p);
        return;
    }
    long long getsum(int l, int r, int s, int t, int p) {
        if (l <= s && t <= r) {
            return ST[p];
        }
        int mid = s + ((t - s) >> 1);
        pushdown(s, t, p);
        long long res = 0;
        if (l <= mid) res += getsum(l, r, s, mid, 2 * p), res %= P;
        if (mid < r) res += getsum(l, r, mid + 1, t, 2 * p + 1), res %= P;
        return res;
    }
    int getmax(int l, int r, int s, int t, int p) {
        if (l <= s && t <= r) return F[p];
        pushdown(s, t, p);
        int mid = s + ((t - s) >> 1);
        int res = -1e15;
        if (l <= mid) res = max(res, getmax(l, r, s, mid, 2 * p));
        if (mid < r) res = max(res, getmax(l, r, mid + 1, t, 2 * p + 1));
        return res; 
    }
}; 
signed main() {
    cin >> n >> m;
    int ans = max(0LL, n - m);
    m++; // 由于线段树板子是Indexed_1，所以坐标整体+1
    segment_tree T(m + 2);
    for (int i = 1; i <= m + 1; i++) T.add(i, i, i - 1, 1, m + 1, 1);
    for (int i = 1; i <= n; i++) {
        int u, v; cin >> u >> v;
        u++, v++; 
        a[u].push_back(v);
    } 
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < (int)a[i].size(); j++) {
            T.add(1, a[i][j], 1, 1, m + 1, 1);    
        }
        ans = max(ans, -(i - 1) - (m - 1) - 1 + T.getmax(i + 1, m + 1, 1, m + 1, 1));     //即上文的式子  
    }
    cout << ans << endl;
    return 0;
}

```


---

## 作者：doge233 (赞：4)

简易题意：n个人，1-m是m个凳子。每个人坐在1-li或ri-n。问最少几个人没有座位。
题解：考虑只有一边（li)的情况。直接贪心扫一遍（入门难度）。考虑替换一个人。如果一个人另一侧比自己更占优势可以把他踢出去。维护一个堆。

原题题解里面给了一个二分图的神仙做法。


---

## 作者：xxxxxzy (赞：3)

#### Hall 定理

对于一张二分图 $G=(V,E)$，令 $N(v)$ 表示与 $v$ 相连的点构成的点集，则有如下结论：

**Hall定理** 设二分图两部分为 $V_{L},V_{R}$，且 $|V_{L}|<|V_{R}|$，那么存在一个大小为 $|V_{L}|$ 的匹配的充要条件为 $\forall S \subseteq  V_{L}$，都有 $|S| \le| \bigcup\limits_{v \in S}  N(v)|$。

**推论** 二分图 $G$ 的最大匹配为 $|V_{L}|-\max\limits_{S\subseteq V_{L}}(|S|-| \bigcup\limits_{v \in S}  N(v)|)$ ，也就等于 $\min\limits_{S\subseteq V_{L}}(|V_{L}-|S|+| \bigcup\limits_{v \in S}  N(v)|)$。

[[ARC076F] Exhausted?](https://www.luogu.com.cn/problem/AT_arc076_d)

题意：给定 $n$ 个人， $m$ 把椅子，一把椅子最多坐一个人，每个人只能坐 $[1,l_{i}]$ 或者 $[r_{i},m]$ 的椅子，求最少没坐到椅子的人。

$n$ 个人，$m$ 把椅子之间互不关联，所以这是张二分图，要求最大匹配，但是直接暴力建图肯定会炸。

考虑 **Hall** 定理的 **推论**，求的答案就等于 $n-(|V_{L}|-\max\limits_{S\subseteq V_{L}}(|S|-| \bigcup\limits_{v \in S}  N(v)|))$ 的最大值。

 $|V_{L}| = n $，所以其实就是 $\max\limits_{S\subseteq V_{L}}(|S|-| \bigcup\limits_{v \in S}  N(v)|)$，注意到这是两块分开的部分，并集不好处理，所以转化成交集，也就是  $m+ \max\limits_{S\subseteq V_{L}}(|S|+| \bigcap\limits_{v \in S}  N(v)|)$。

题目就被转化为了给 $n$ 个区间，选择任意个使得区间数量加交集长度最长。

按左端点排序，假设当前交集的左端点就是当前的左端点，那么右端点一定大于这个左端点，我们设交集为 $[l,k]$。

那么答案就是 $k-l-1+m+\sum [r_{j}\ge k] [l_{j} \le l]$，发现每次查询时，$-l,-1,m$ 都是常数。

于是建一棵线段树维护 $k+\sum[r_{j}\ge k][l_{j} \le l]$，具体来说，初始建树把 $i$ 位置的值赋值为 $i$，然后每次把 $[l,r]$ 加上一，维护 $[l,m+1]$ 最大值即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define drep(i,a,b) for(int i=a;i>=b;i--)
#define pb push_back
#define pii pair<int,int>
const int inf=1e9+5;
using namespace std;
struct SegmentTree{
	int lx[800005],rx[800005],mx[800005],tag[800005];
	void build(int p,int l,int r){
		lx[p]=l,rx[p]=r;
		if(l==r) return (void)(mx[p]=l);
		int mid=(l+r)>>1;
		build(p<<1,l,mid),build(p<<1|1,mid+1,r);
		mx[p]=max(mx[p<<1],mx[p<<1|1]);
	}
	void pushdown(int p){
		tag[p<<1]+=tag[p],tag[p<<1|1]+=tag[p];
		mx[p<<1]+=tag[p],mx[p<<1|1]+=tag[p];
		tag[p]=0;
	}
	int ask(int p,int l,int r){
		if(lx[p]>r||rx[p]<l) return 0;
		if(lx[p]>=l&&rx[p]<=r) return mx[p];
		pushdown(p);
		return max(ask(p<<1,l,r),ask(p<<1|1,l,r));
	}
	void adds(int p,int l,int r,int k){
		if(lx[p]>r||rx[p]<l) return;
		if(lx[p]>=l&&rx[p]<=r) return (void)(mx[p]+=k,tag[p]+=k);
		pushdown(p);
		adds(p<<1,l,r,k),adds(p<<1|1,l,r,k);
		mx[p]=max(mx[p<<1],mx[p<<1|1]);
	}
}st;
int n,m,ans;
struct node{
	int l,r;
}tt[200005]; 
bool cmp(node a,node b){
	return a.l<b.l;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	rep(i,1,n) cin>>tt[i].l>>tt[i].r;
	sort(tt+1,tt+1+n,cmp);
	ans=max(0ll,n-m);
	st.build(1,1,m+1);
	rep(i,1,n){
		st.adds(1,tt[i].l,tt[i].r,1);
		ans=max(ans,st.ask(1,tt[i].l+1,m+1)-tt[i].l-m-1);
	}
	cout<<ans;
}
```

---

## 作者：ez_lcw (赞：3)

~~一开始想的是线段树优化建图网络流。~~

但是看到 $n\leq10^5$ 就知道不可能了。

然后又尝试了一种错误的贪心：（这也是大多数人会想到的但是错误的贪心）

先将所有的 $(l_i,r_i)$ 按 $l_i$ 从小到大排序，其中 $l_i$ 相同的按 $r_i$ 从大到小排序。

然后从 $1$ 到 $n$ 扫每个人的要求，假设当前是第 $i$ 个人，那么我们就找到满足位置 $\leq l_i$ 且最靠右的那个椅子上；如果找不到，就找到满足位置 $\geq r_i$ 且最靠左的那个椅子上；如果还是找不到，那么这个人的需求就不能被满足。

但是发现这种方法会被一种情况 hack 掉：

```
3 4
1 3
2 5
2 5
```

用图来表示就是这样：（其中 ①②③ 代表的是排序后的每一个要求）

![](https://cdn.luogu.com.cn/upload/image_hosting/no9ynpv3.png)

按照我们刚才的贪心，我们会把第 $1$ 个人放在第 $1$ 个位置，把第 $2$ 个人放在第 $2$ 个位置，然后第 $3$ 个人没有位置放，所以答案是 $1$。（如上图）

虽然看起来很正确，但是你发现还有一种更优的解法，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8itfjdi8.png)

那么我们需要考虑如何避免这样的问题。

重新考虑开始的过程：从 $1$ 到 $n$ 扫每个人的要求，假设当前是第 $i$ 个人。

寻找满足位置 $\leq l_i$ 且最靠右的那个椅子，如果找到了的话：

显然，如果出现了刚刚的那种情况，那么我们就让另一个人坐这个椅子；如果没有出现，那么我们不如就让 $i$ 坐这个椅子。

所以不管有没有出现刚刚那种情况，这张椅子肯定是会被坐的。

那么我们先不妨假设 $i$ 坐上了这张椅子，然后遍历后面的某一个人 $j$ 的时候，如果在 $\leq l_j$ 的范围中找不到可以坐的椅子了，那么我们就看需不需要让 $i$ “反悔”，让 $j$ 坐 $i$ 坐着的这张椅子，$i$ 另外去 $\geq r_i$ 的地方找椅子。（注意排序过后 $l_i\leq l_j$，所以 $i$ 坐着的椅子 $j$ 肯定也能坐）

如何维护“反悔”这么一个操作？

我们可以设置一个小根堆，然后每次当 $i$ 找到 $\leq l_i$ 可以坐的椅子，然后在小根堆中插入 $r_i$，表示 $i$ 坐在了 $\leq l_i$ 的某一个位置，而且 $i$ 可以“反悔”——换到 $\geq r_i$ 的某一个空位。

但如果 $i$ 在 $\leq l_i$ 的位置中找不到可以坐的椅子，我们有两种选择：（假设当前小根堆的堆顶是 $r_j$）

1. 如果 $r_j\leq r_i$，那么肯定是让 $j$ 从位置 $\leq l_j$ 换到位置 $\geq r_j$ 更优，然后让 $i$ 坐 $j$ 本来坐着的那张椅子。

1. 如果 $r_j>r_i$，那么还不如让 $i$ 坐在 $\geq r_i$ 的那个位置。

那么我们通过这种方式就能安排好每一个人 $i$ 到底是坐在 $\leq l_i$ 还是 $\geq r_i$ 的位置了。

至于这时如何统计答案，可以直接用 $O(n\log n)$ 排序，当然也可以直接 $O(n)$ 做，具体做法见代码。

代码如下：

```cpp
#include<bits/stdc++.h>

#define N 200010

using namespace std;

struct Question
{
	int l,r;
}a[N];

int n,m,ans;
int b[N],c[N];

priority_queue<int,vector<int>,greater<int> >q;

bool cmp(Question a,Question b)
{
	if(a.l==b.l) return a.r<b.r;
	return a.l<b.l;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].l,&a[i].r);
	sort(a+1,a+n+1,cmp);
	int tot=0;
	for(int i=1;i<=n;i++)
	{
		if(!a[i].l)
		{
			c[a[i].r]++;
			continue;
		}
		if(tot==a[i].l)
		{
			int u=q.top();
			if(u<=a[i].r)
			{
				q.pop();
				c[u]++;
				q.push(a[i].r);
			}
			else c[a[i].r]++;
			continue;
		}
		++tot;
		b[tot]++;
		q.push(a[i].r);
	}
   //记录的数组b、c分别表示哪些位置要填<=li，哪些位置要填>=ri，然后直接动态记录答案就好了：
	int ltmp=0;
	ans+=b[0],b[m]+=b[m+1];
	for(int i=1;i<=m;i++)
	{
		if(i-ltmp>=b[i])
		{
			ltmp+=b[i];
			continue;
		}
		ans+=b[i]-(i-ltmp);
		ltmp=i;
	}
	int rtmp=m+1;
	ans+=c[m+1],c[1]+=c[0];
	for(int i=m;i>=ltmp+1;i--)
	{
		if(rtmp-i>=c[i])
		{
			rtmp-=c[i];
			continue;
		}
		ans+=c[i]-(rtmp-i);
		rtmp=i;
	}
	for(int i=ltmp;i>=1;i--)
	{
		if(rtmp-(ltmp+1)>=c[i])
		{
			rtmp-=c[i];
			continue;
		}
		ans+=c[i]-(rtmp-(ltmp+1));
		rtmp=ltmp+1;
	}
	printf("%d\n",ans);
	return 0;
}
/*
3 4	
1 3
2 5
2 5
*/
```

---

## 作者：Polaris_Australis_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT2645)

## 做法

本题有 hall 定理 + 线段树做法，详见[大佬的博客](https://www.cnblogs.com/lnxxqz/p/16318206.html)

思路：让所有的人先尽可能坐在左面，坐不下的做右面，然后实在坐不了的就填椅子。

实现：

* $ex_i$ 数组：果为 -1 即表示 $i$ 这个位置的椅子是空的，0 表示坐了人，其余数字均表示**有 $ex_i$ 个人还没有坐在椅子上，他们不可以坐在坐标小于 $i$ 的椅子上**。
* 把所有人按照以 $l$ 为第一关键字，$r$ 为第二关键字排序，$ex$ 数组初值均为 -1，每次选择一个人，看他前面能坐的椅子是否坐满，如果没满，就直接做当前所剩椅子中最左面的一个，并插入到优先队列中表示可以被替换，如果已经满了，就要从所有可以被替换的这些人里找第二关键字最小的一个替换（这样可以给后面留足够大的空间让更多人坐），这样的话自己就坐在了。
* 统计答案：考虑 $ex_i$ 数组后缀和的含义即为从 $i$ 到 $n$ 有多少个人没有椅子，且这些人一定要坐在坐标大于等于 $i$ 的位置，这样后缀和中最大的即为答案。

思路来自大佬 @[tjn1234](https://www.luogu.com.cn/user/645153)

![](//图.tk/3)

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Std {
int n, m, now, ex[200010], ans, res;
struct node {
  int l, r;
  friend bool operator<(const node& a, const node& b) {
    return (a.l == b.l) ? a.r < b.r : a.l < b.l;
  }
} t[200010];
struct num {
  int sum;
  friend bool operator<(const num& a, const num& b) { return a.sum > b.sum; }
};
priority_queue<num> q;
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &t[i].l, &t[i].r);
  }
  sort(t + 1, t + n + 1);
  for (int i = 1; i <= m; i++) ex[i] = -1;
  for (int i = 1; i <= n; i++) {
    if (t[i].l == 0) {
      ex[t[i].r]++;
    } else if (t[i].l == now) {
      num u = q.top();
      q.pop();
      ex[u.sum]++;
      u.sum = t[i].r;
      q.push(u);
    } else {
      ex[++now]++;
      num u;
      u.sum = t[i].r;
      q.push(u);
    }
  }
  for (int i = m + 1; i >= 0; i--) {
    res += ex[i];
    ans = max(ans, res);
  }
  printf("%d\n", ans);
  return 0;
}
}  // namespace Std
int main() { return Std::main(); }
```


---

## 作者：Z1qqurat (赞：1)

本题有两种做法，一种是线段树 + Hall 定理，另一种是贪心。

### 线段树 + Hall 定理

首先如果不考虑数据范围，相当于将人当作左部点，椅子当作右部点，人 $i$ 向 $[1, l_i], [r_i, m]$ 连边，那么要求能完美匹配，求的就是使其存在完美匹配的最少添加的右部点数。我们可以利用 Hall 定理的推广，设 $S$ 为左部点的一个集合，那么 $f(S)$ 就是与 $S$ 有连边的右部点集合。那么答案就是 $\max (|S| - |f(S)|)$。那怎么求这个呢？发现 $S$ 应该是一段前缀 $[1, L]$ 加上一段后缀 $[R, m]$ 的形式，于是我们考虑对每个 $f(S) = [1, L] \cup [R, m]$ 求出其最大的 $S$。此时得到的差值为 $|S| + R - L - m - 1$。我们考虑维护 $c_R = \max (|S| + R)$，初始设 $c_R = R$。那么我们将所有人以 $l$ 为第一关键字，以 $r$ 为第二关键字排序，依次插入每个人。因为当我们满足 $f(S) = [1, L] \cup [R, m]$ 时，需要满足 $\forall i \in S, l_i \le L, r_i \ge R$，所以我们插入 $i$ 时，对 $c_{0 \sim {r_i}}$ 做一个前缀 $+1$，那此时我们求出当 $L$ 为 $l_i$ 时的最大差值，也就是 $\max (|S| + R) = c_{l_i + 1 \sim m + 1}$ 中的最大值（$L < R$），最后差值就是 $\max (|S| + R) - m - l_i - 1$。

记得要维护的是 $c_{0 \sim m + 1}$，$ans$ 一开始至少为 $\max(0, n - m)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define lc p << 1
#define rc p << 1 | 1
using namespace std;
const int N = 2e5 + 10;
int n, m;
struct Rinne{
    int l, r;
    bool operator<(const Rinne &b) const{
        if(l == b.l) return r < b.r;
        return l < b.l;
    }
} a[N];

namespace SegT{
    int mx[N << 2], tag[N << 2];
    void pushup(int p) {
        mx[p] = max(mx[lc], mx[rc]); return ;
    }
    void build(int p, int l, int r) {
        tag[p] = 0;
        if(l == r) {
            mx[p] = l; return ;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid), build(rc, mid + 1, r);
        pushup(p); return ;
    }
    void addtag(int p, int v) {
        tag[p] += v, mx[p] += v; return ;
    }
    void pushdown(int p) {
        if(tag[p]) {
            addtag(lc, tag[p]), addtag(rc, tag[p]);
            tag[p] = 0;
        }
        return ;
    }
    void modify(int p, int l, int r, int x, int y, int v) {
        if(x <= l && r <= y) return addtag(p, v), void();
        pushdown(p);
        int mid = (l + r) >> 1;
        if(x <= mid) modify(lc, l, mid, x, y, v);
        if(y > mid) modify(rc, mid + 1, r, x, y, v);
        pushup(p); return ;
    }
    void modify(int x, int y, int v) {
        modify(1, 0, m + 1, x, y, v);
    }
    int query(int p, int l, int r, int x, int y) {
        if(x <= l && r <= y) return mx[p];
        pushdown(p);
        int mid = (l + r) >> 1, ret = 0;
        if(x <= mid) ret = max(ret, query(lc, l, mid, x, y));
        if(y > mid) ret = max(ret, query(rc, mid + 1, r, x, y));
        return ret;
    }
    int query(int x, int y) {
        return query(1, 0, m + 1, x, y);
    }
} using namespace SegT;

int main() {
    scanf("%d %d", &n, &m);
    build(1, 0, m + 1);
    for (int i = 1; i <= n; ++i) scanf("%d %d", &a[i].l, &a[i].r);
    sort(a + 1, a + n + 1);
    int ans = max(n - m, 0); //特判条件
    for (int i = 1; i <= n; ++i) {
        modify(0, a[i].r, 1);
        ans = max(ans, query(a[i].l + 1, m + 1) - m - 1 - a[i].l);
    }
    printf("%d\n", ans);
    return 0;
}
```

### 贪心

因为如果不添加椅子，那么每个位置就是只有一把椅子。那你想这初始的椅子我肯定尽量坐啊不坐白不坐浪费了，所以我们对于每个人 $i$，我们尽量让他坐在 $\le l_i$ 的位置，尽量把初始的椅子填满。

那怎么实现？我们先将所有人按 $l_i$ 从小到大排序，如果 $l_i$ 相同就按 $r_i$ 从小到大排序，现在我们考虑一个数组 $add_j$，表示 $j$ 这个位置需要加几把椅子。如果 $add_j = - 1$ 表示 $j$ 位置没有人坐，为 $0$ 表示有人坐了这把初始的椅子，其余情况表示有 $add_j$ 个人要坐在这里，所以需要添加这么多把椅子。

现在我们加入一个人 $a$，其上下限分别为 $a.l, a.r$。记录目前坐到的最右边的位置是 $lst$。

* $a.l = 0$，那么说明 $a$ 只能选择坐在 $\ge a.r$ 的位置，又因为我们**尽量把左边的椅子坐满**，人又是排序过的，所以 $a.r$ 可以坐（或者加椅子），$add_{a.r} + 1$  即可。

* $a.l = lst$，那么说明 $1 \sim lst$ 都有人坐了，而 $a$ 又只能坐在 $\le a.l$ 的位置，所以我们考虑将坐在 $1 \sim lst$ 位置上 $r$ 最小的人踢出来，让他坐到 $r$，然后将 $a$ 放到 $lst$ 位置上，并将其标记为可替换的。

* $a.l > lst$，那我们仍然遵循尽量坐左边的原则，让 $a$ 坐在 $lst + 1$ 位置上，同时将 $a$ 标记为可替换，$lst$ 自加。

具体可以将可替换的人的 $r$ 值放入一个优先队列中维护。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5;
int n, m, add[N], lst;
struct Rinne{
	int l, r;
	bool operator<(const Rinne &b) const{
		if(l == b.l) return r < b.r;
		return l < b.l;
	}
}b[N];
priority_queue <int, vector<int>, greater<int> > q;

void insert(Rinne a) {
	if(!a.l) add[a.r]++;
	else if(a.l == lst) {
		int u = q.top(); q.pop();
		add[u]++, q.emplace(a.r);
	}
	else {
		add[++lst]++, q.emplace(a.r);
	}
	return ;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d %d", &b[i].l, &b[i].r);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= m; ++i) add[i] = -1;
	for (int i = 1; i <= n; ++i) insert(b[i]);
	int ans = 0, sum = 0;
	for (int i = m + 1; i >= 1; --i) {
		sum += add[i];
		ans = max(ans, sum);
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：takanashi_mifuru (赞：1)

~~每次高桥君都看成高木君，今天这个彻底绷不住了，抓人抓累了丢椅子上长眠了是吧。~~

考虑 Hall 定理有一个无敌炫酷闪电旋风推广，就是一张二分图要把他补成完美匹配，需要的边数为 $\max(|S|-|f(S)|)$ 条，其中 $S$ 表示左部点集合的子集。

那你就考虑把高木同学抓来的人按照左端点排序，然后每次枚举到第 $i$ 个人的时候，因为他前面的人都比他小，那我们就在这些人里面选择右端点比他更大的全部统计好就可以了！

实际上只有二次元才会这么想，他有可能有一个区间的位置很尴尬上不去下不来。

![](https://pic.imgdb.cn/item/64f6a2b3661c6c8e5493a54a.jpg)

就像这张图一样，如果取三个区间可能还会更为优秀，但是我们这样跑只会拿一个区间，非常的劣。

我们考虑如何解决他，首先我的 $r$ 立在那里，比我 $r$ 要大的我必然取，因为取了肯定优，比我 $r$ 小的，考虑这样的前缀的数量，假设我取这样的点最后取了一个 $r'$，那么我就要付出 $r-r’$ 的代价，同时右端点在 $[r',m+1]$ 这个范围内的全部给一个贡献，这个怎么维护呢，我们考虑首先在第 $i$ 个点处加上 $-i$，然后每次就相当于是在一个前缀上做加法，表示这些位置都有我的影响，而每次取答案只需要求一个区间最小就可以了。

---

## 作者：Filberte (赞：0)

想解决此问题，需要先知道两个前置结论（证明可以阅读有关资料）：

**Hall 定理**

对于一个二分图 $G = (X,Y,E)$， $G$ 中有一个大小为 $|X|$ 的匹配 $\iff$ $\forall A\subseteq X$，$|N(A)| \ge |A|$。

其中 $N(A)$ 表示 $A$ 的 $Y$ 中与 $X$ 中的至少一个点相邻接的点的集合，也就是陪集。

**推论**

对于一个二分图 $G = (X,Y,E)$，其最大匹配数为 $|X| - \max\limits_{X'\subseteq X}(|X'| - |N(X')|)$。

回到这个题目，构建二分图模型，需要最小化未匹配左侧点的数量，即最大化匹配数量，因此答案为 $n - (n - \max\limits_{X'\subseteq X}\{|X'| - N(X')\}) = \max\limits_{X'\subseteq X}\{|X'| - N(X')\}$。$N(X')$ 本质上是 $X'$ 中每个点 $x$ 所对应 $N(x)$ 的交，交集不好维护，且每个点 $x$ 的 $N(x)$ 对应两段区间，因此考虑把一些集合的交交转化为全集减去每个集合补集的并，也就是求 $\max\limits_{X'\subseteq X}\{B(X')\} - m$，其中 $B(x)$ 表示左侧点 $x$ 不相邻的点的的集合，$B(X) = \bigcap\limits_{x \in X} B(x)$。

最终问题：给定 $n$ 个区间，从中选一些出来，最大化选择的区间个数加上这些区间的交集的大小。

一些区间的交集肯定肯定是连续的一段。考虑交集，若其左端点 $L$，若右端点为 $R$，则答案为 $R - L + 1 + \sum[l_i \le L][r_i \ge R]$。这类多个限制的问题，常见套路是第一维排序，第二维数据结构，（若有）第三维 cdq 分治。从小到达枚举 $L$，$1 - L$ 是定值，因为 $L$ 是枚举的，所以可以依次加入，只考虑 $l_i \le L$ 的线段，因此相当于求 $\max\limits_{k} \{k + \sum[r_i \ge k]\}$。使用线段树维护即可。

两个坑点：一是最少需要补充 $\max(0, n - m)$ 个椅子，应该将其设为初始值；二是对于第 $x$ 个人，$N(X)$ 的补集应当是 $[l_x + 1, r_x - 1]$ 而非 $[l_x,r_x]$。

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 100;
struct Segment_Tree{
    int Mx[N << 2], v[N << 2], tg[N << 2];
    void push_down(int u){
        if(tg[u]){
            Mx[u << 1] += tg[u];
            Mx[u << 1 | 1] += tg[u];
            tg[u << 1] += tg[u];
            tg[u << 1 | 1] += tg[u];
            tg[u] = 0;
        }
    }
    void push_up(int u){
        Mx[u] = max(Mx[u << 1], Mx[u << 1 | 1]);
    }
    void build(int u, int l, int r){
        Mx[u] = r;
        if(l == r) return ;
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }
    void add(int u, int l, int r, int L, int R){
        if(L <= l && r <= R){
            Mx[u]++, tg[u]++;
            return ;
        }
        int mid = (l + r) >> 1;
        push_down(u);
        if(L <= mid) add(u << 1, l, mid, L, R);
        if(R > mid) add(u << 1 | 1, mid + 1, r, L, R);
        push_up(u);
    }

    int Qry(int u, int l, int r, int L, int R){
        if(L <= l && r <= R) return Mx[u];
        int res = 0, mid = (l + r) >> 1;
        push_down(u);
        if(L <= mid) res = max(res, Qry(u << 1, l, mid, L, R));
        if(R > mid) res = max(res, Qry(u << 1 | 1, mid + 1, r, L, R));
        return res;
    }
}T;
int n, m;
vector<int> vec[N];
int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        int l, r;cin >> l >> r;
        if(r - 1 >= l + 1) vec[l + 1].push_back(r - 1);
    }
    int ans = max(0, n - m);
    T.build(1, 1, m);
    for(int L = 1;L <= m;L++){
        for(int R : vec[L]) T.add(1, 1, m, L, R);
        ans = max(ans, T.Qry(1, 1, m, L, m) - L + 1 - m);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

**Hall 定理**：对于一个二分图，若其左部点集为 $X$，右部点集为 $Y(|X|\le|Y|)$，那么有 $\forall X'\subseteq X,|X'|\le |f(X')|$，其中 $f(X)$ 表示 $X$ 中每个点的邻接点的集合。

由此可以得到一个推论：二分图最大匹配为 $|X|-\max\{|X'|-|f(X')|\}$。

答案显然为总数减去最大匹配，即 $\max\{|X'|-|f(X')|\}$。

$f$ 显然是一个并的形式，交不好求，改为求交。

交为空的时候可以单独算，显然是 $n-m$。

然后你交的结构非常简单，就是 $r_{min}-l_{max}$。

考虑钦定 $r_{min}$，因此按照 $r$ 降序排序，然后对 $l$ 扫描线即可。

注意 $X'$ 有空集的情况，答案要和 $0$ 取 $\max$。

---

## 作者：Galois_Field_1048576 (赞：0)

## 扩展 Hall 定理

**定理 (扩展 Hall 定理).** 设 $\Gamma = (V, E)$ 是一个二分图，$L$ 是其左部，$R$ 是其右部，对于 $X \subseteq L$，定义 $N(X)$ 为 $\{y \in R \mid \exists x \in X, (x, y) \in E\}$。则 $\Gamma$ 的最大匹配为：
$$
|L| - \max_{S \subseteq L} (|S| - |N(S)|).
$$

*证明.* 设 $\mathfrak M \subseteq E$ 为 $\Gamma$ 的最大匹配。定义 $\Gamma$ 上的 $\mathfrak M$-**交错路**为 $\Gamma$ 上一个路径 $v_0, v_1, \dots, v_n$，满足 $(v_i, v_{i+1}) \in \mathfrak M \iff 2 \mid i$。称集合 $S$ 对 $\mathfrak M$-交错路封闭，若对于任何起点在 $x \in S$ 的交错路，其重点都在 $S$ 中。类似地，可以定义 $S$ 对交错路的闭包。

取得 $S \subseteq L$。则考虑 $S$ 对 $\mathfrak M$-交错路的闭包 $\bar S$。令 $L_0 = \bar S \cap L, R_0 = \bar S \cap R$。则注意到我们有双射 $\phi : L_0 \setminus S \to R_0$：对于 $x \in L_0 \setminus S$，因为 $x \in \bar S$，所以存在 $\mathfrak M$-交错路 $v_0, v_1, \dots, v_n$ 使得 $v_n = x$。则规定 $\phi(x) = v_{n-1}$。不难证明 $\phi$ 为双射。

根据 $\phi$ 是双射，$|L_0| = |R_0| + |S|$，同时，不难验证 $R_0 = N(L_0)$，则取得 $|L_0| - |N(L_0)| = |S|$。因此，对于每一个 $S \subseteq L$，存在 $L_0$ 使得 $|L_0| - |N(L_0)| = S$。取得 $S$ 是 $\mathfrak M$ 中失配点，得证。

## 本题题解
我们注意到，所有人都可以坐在 $+\infty$ 处的椅子上，所以只需要在 $+\infty$ 处加失配人数个椅子就好。因此问题转化为失配人数。显然第 $i$ 个人想坐在 $I_i^\complement$ 的椅子上，其中 $I_i$ 是个区间。利用扩展 Hall 定理，则 $N(S)$ 可以写为：
$$
\operatorname{len}\left(\bigcup_{i \in S} I_i^\complement\right),
$$
也就是
$$
m - \operatorname{len}\left(\bigcap_{i \in S} I_i\right).
$$
（De Morgan 定理）因此，定义
$$
f(S) = -m + |S| +  \operatorname{len}\left(\bigcap_{i \in S} I_i\right),
$$
则
$$
f(S \sqcup \{I_k\}) > f(S) \iff I_k \supseteq \bigcap_{i \in S} I_i.
$$
（证明：$\impliedby$ 方向显然，$\implies$ 方向考虑证明其逆否，也即 $\neg \impliedby \neg$。关于逆否，在否定的前提下，不难发现 $\operatorname{len}\left(\bigcap_{i \in S} I_i\right)$ 这个量至少减少 $1$，而 $|S|$ 只会增加 $1$。）

因此，只需要维护有多少个区间包含 $I$，而这是线段树经典例题。

---

## 作者：LingHusama (赞：0)

## Exhausted? 题解
### 前言：
看本篇题解，您如果想要掌握所有知识点的话，请您先去了解下什么是霍尔定理，当然如果可以的话，可以去看看我的这个[博客](https://www.cnblogs.com/linghusama/p/17810937.html)。

### 涉及的算法和思想知识点：
1. 线段树、扫描线。
2. 霍尔定理。
3. 较少的容斥原理。

### 正文：
#### 理论分析：
1. 从简单入手：我们想想，要是值域再小一点的话，我们可以怎么做？我的想法是直接把人和合理的区间各个位置连边，形成一个二分图，求解最大匹配找到最多的能不添加椅子就可以做的人，然后用总共的减去就是最小的了。
2. 思维拔升：我们发现不可以建立图时，不然就是算法有问题不然就是要用各种理论来简化，对于二分图而言，一般建不了图，就是霍尔定理。我们将人看做 $V1$，根据定理，那么我们就是求解 $\max(|S1|-|S2|)$ 这个柿子。
3. 举例化简：现在我们随便选择两个点作为 $S1$ 那么就是求解他们 $S2$ 的并。我们稍微容斥一下，变为求解两个点区间的补集的交集的补集。这么说很混乱，我直接举例子吧，就是求 $[L1+1,R1-1]$ 和 $[L2+1,R2-1]$ 的交集的补集。我们用柿子表达，就是求 $\max(|S1|-m+R-L+1)$。注意下，要是没有交集，答案就是 $n-m$，所以答案至少为它。

4. 思考解决最值的方向：我们为了让上述柿子最大，像这种题目不然就是贪心，不然就是找函数最值，不然就是硬着头皮想方法维护。贪心的话我实在想不出来，用函数的话，我们会发现我们点选得越多，$R-L+1$ 却不会变长。两者是“你增加我可能减少”的关系，所以从函数本身来看似乎就不行了。那就只能硬着头皮去维护这个柿子了。
#### 代码实现思路（重点）：

因为我觉得维护很难想到，所以专门开了个重点来。

考虑到一个交集的左端点一定是一个原来的左端点之一，右端点同理。于是我现在想找一个左端点确定的交集查找答案（通过枚举线段来确定）。

当这个交集的左端点确定时，我选择的点只能是左端点在它左侧，右端点在他右侧的线段（否则的话交集左端点会变化或者不会有交集）。由于左端点确定，我们假设已经确定这个交集的右端点为 $K$，于是乎我们就可以得到这个交集 $[L,K]$ 给出的最终答案为 $|S1|-m+K-L+1$。我们此时还可以扩展 $|S1|$ 让答案更优，这些可以添加的点要求其左右端点不会更改交集即可。

所以最后就是：

$K-L-1-m+\sum_j [rj>=k] , [lj<=L]$。

具体做法是在线段树上把 $i$ 位置的初值设为 $i$，然后每次将 $[l,r]$ 区间增加一，求 $ [l,m]$ 的最大值。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int le;
	int ri;
}stu[200005]; 
bool cmp(node x,node y){
	if(x.le!=y.le)return x.le<y.le;
	else  return x.ri<y.ri;
}
int ans=0;
struct nod{
	int le;
	int ri;
	int val; 
	int lz;
}tree[800005];
vector<int>h[200005];
void pushup(int rt){
	tree[rt].val=max(tree[rt*2].val,tree[rt*2+1].val);
}
void pushdown(int rt){
	if(!tree[rt].lz){
		return;
	}
	tree[rt*2].lz+=tree[rt].lz;
	tree[rt*2+1].lz+=tree[rt].lz;
	tree[rt*2].val+=tree[rt].lz;
	tree[rt*2+1].val+=tree[rt].lz;
	tree[rt].lz=0;
	return;
}
void build(int rt,int L,int R){
	tree[rt].le=L;
	tree[rt].ri=R;
	if(L==R){
		tree[rt].val=L;
		return;
	}
	int mid=(L+R)>>1;
	build(rt*2,L,mid);
	build(rt*2+1,mid+1,R);
	pushup(rt);
}
void add(int rt,int L,int R,int v){
	int le=tree[rt].le;
	int ri=tree[rt].ri;
	if(le>=L&&ri<=R){
		tree[rt].val+=v;
		tree[rt].lz+=v;
		return;
	}
	if(le>R||ri<L){
		return;
	}
	pushdown(rt);
	add(rt*2,L,R,v);
	add(rt*2+1,L,R,v);
	pushup(rt);
}
int get(int rt,int L,int R){
	int le=tree[rt].le;
	int ri=tree[rt].ri;
	if(le>=L&&ri<=R){
		return tree[rt].val;
	} 
	if(le>R||ri<L){
		return 0;
	}
	pushdown(rt);
	int ret=0;
	ret=max(ret,get(rt*2,L,R));	
	ret=max(ret,get(rt*2+1,L,R));
	pushup(rt);
	return ret;	
}
int main(){
	ios::sync_with_stdio(false);
	int n,m;
	cin >>n >>m;
	for(int i=1;i<=n;i++){
		cin >> stu[i].le>>stu[i].ri;
		h[stu[i].le].push_back(stu[i].ri);
	}
	ans=max(0,n-m);
	build(1,0,m+1);
	for(int i=0;i<=m+1;i++){
		for(int j=0;j<h[i].size();j++){
			int to=h[i][j];
			add(1,0,to,1);
		}
		ans=max(ans,get(1,i+1,m+1)-i-m-1);
	}
	cout<<ans;
	
}
```





---

