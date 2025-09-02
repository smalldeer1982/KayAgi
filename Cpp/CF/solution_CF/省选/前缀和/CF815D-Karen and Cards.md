# Karen and Cards

## 题目描述

Karen just got home from the supermarket, and is getting ready to go to sleep.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815D/d6b07c74db93ed793c45ff910937379fe578d8dc.png)After taking a shower and changing into her pajamas, she looked at her shelf and saw an album. Curious, she opened it and saw a trading card collection.

She recalled that she used to play with those cards as a child, and, although she is now grown-up, she still wonders a few things about it.

Each card has three characteristics: strength, defense and speed. The values of all characteristics of all cards are positive integers. The maximum possible strength any card can have is $ p $ , the maximum possible defense is $ q $ and the maximum possible speed is $ r $ .

There are $ n $ cards in her collection. The $ i $ -th card has a strength $ a_{i} $ , defense $ b_{i} $ and speed $ c_{i} $ , respectively.

A card beats another card if at least two of its characteristics are strictly greater than the corresponding characteristics of the other card.

She now wonders how many different cards can beat all the cards in her collection. Two cards are considered different if at least one of their characteristics have different values.

## 说明/提示

In the first test case, the maximum possible strength is $ 4 $ , the maximum possible defense is $ 4 $ and the maximum possible speed is $ 5 $ . Karen has three cards:

- The first card has strength $ 2 $ , defense $ 2 $ and speed $ 5 $ .
- The second card has strength $ 1 $ , defense $ 3 $ and speed $ 4 $ .
- The third card has strength $ 4 $ , defense $ 1 $ and speed $ 1 $ .

There are $ 10 $ cards that beat all the cards here:

1. The card with strength $ 3 $ , defense $ 3 $ and speed $ 5 $ .
2. The card with strength $ 3 $ , defense $ 4 $ and speed $ 2 $ .
3. The card with strength $ 3 $ , defense $ 4 $ and speed $ 3 $ .
4. The card with strength $ 3 $ , defense $ 4 $ and speed $ 4 $ .
5. The card with strength $ 3 $ , defense $ 4 $ and speed $ 5 $ .
6. The card with strength $ 4 $ , defense $ 3 $ and speed $ 5 $ .
7. The card with strength $ 4 $ , defense $ 4 $ and speed $ 2 $ .
8. The card with strength $ 4 $ , defense $ 4 $ and speed $ 3 $ .
9. The card with strength $ 4 $ , defense $ 4 $ and speed $ 4 $ .
10. The card with strength $ 4 $ , defense $ 4 $ and speed $ 5 $ .

In the second test case, the maximum possible strength is $ 10 $ , the maximum possible defense is $ 10 $ and the maximum possible speed is $ 10 $ . Karen has five cards, all with strength $ 1 $ , defense $ 1 $ and speed $ 1 $ .

Any of the $ 972 $ cards which have at least two characteristics greater than $ 1 $ can beat all of the cards in her collection.

## 样例 #1

### 输入

```
3 4 4 5
2 2 5
1 3 4
4 1 1
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 10 10 10
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
```

### 输出

```
972
```

# 题解

## 作者：Argvchs (赞：10)

首先可以想到对于每一张敌方卡牌，我们对能胜过其的卡牌求交集就可以了。

但是我们不会高维数据结构，于是考虑降维。

考虑到若一张卡牌能满足要求，那么所有严格大于它的卡牌都可以，即满足要求的卡牌是连续的，我们用 $f_{i, j}$ 表示当攻击为 $i$，防御为 $j$ 时满足要求的卡牌数量。

当添加一张属性为 $(a, b, c)$ 的卡牌时：

1. 对于 $i \le a$ 且 $j \le b$ 的卡牌，这种卡牌已经失败了，于是将 $f_{i, j}$ 置为 $0$；
2. 对于 $i > a$ 且 $j \le b$ 的卡牌，这种卡牌还需要一个更强的属性，那么它的速度必须在 $(c, C]$ 之间，于是将 $f_{i, j}$ 对 $C - c$ 取最小值；
3. 对于 $i \le a$ 且 $j > b$ 的卡牌，同 2；
4. 对于 $i > a$ 且 $j > b$ 的卡牌，这种卡牌已经赢了。

例如当 $A = 4$，$B = 5$，$C = 5$ 时，添加一张属性为 $(1, 2, 3)$ 的卡牌，此时 $f$ 的值是这样的：

```text
0 0 2 2 2
2 2 5 5 5
2 2 5 5 5
2 2 5 5 5
```

发现我们做的操作其实是：

1. 将前 $a$ 行对 $C - c$ 取最小值；
2. 将前 $b$ 列对 $C - c$ 取最小值；
3. 将一个左上角为 $(1, 1)$，右下角为 $(a, b)$ 的矩形置为 $0$。

对于操作 1 2，都是前缀取 $\min$，从后往前推一下即可。

对于操作 3，我们记录每一行置零的列数，这其实是一个前缀取 $\max$，与前两个操作同理。

我们记刚才每一行取到的最小值为 $x_i$，每一列取到的最小值为 $y_i$，每一行置零的列数为 $z_i$。

最后考虑如何统计答案，其实我们已经有 $f_{i, j} = [j > z_i]\min(x_i, y_j)$，可以做到 $O(1)$ 单点求值，但是这样还是太慢了。

发现 $x_i$ 和 $y_i$ 都是单调递增的，这启示我们使用一个均摊的算法。

可以对于每一行分别求和。

我们用双指针均摊 $O(1)$ 求出每一行第一个 $y_k > x_i$ 的 $k$，那么对于 $j \ge k$ 的答案即为 $(B - k + 1)x_i$；对于 $j < k$ 的答案为 $\sum_{1 \le j < k} y_j$，用前缀和维护即可。

然后还有一个置零需要考虑，这个直接让 $k$ 对 $z_i + 1$ 取最大值，并且在前缀和中减去就可以了。

时间复杂度 $O(n)$。

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 5e5 + 5;
int n, A, B, C, x[N], y[N], z[N];
i64 s[N], ans;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> A >> B >> C;
    for (int i = 1; i <= A; i++) x[i] = C;
    for (int i = 1; i <= B; i++) y[i] = C;
    for (int i = 1, a, b, c; i <= n; i++) {
        cin >> a >> b >> c;
        x[a] = min(x[a], C - c);
        y[b] = min(y[b], C - c);
        z[a] = max(z[a], b);
    }
    for (int i = A - 1; i >= 1; i--) x[i] = min(x[i], x[i + 1]);
    for (int i = B - 1; i >= 1; i--) y[i] = min(y[i], y[i + 1]);
    for (int i = A - 1; i >= 1; i--) z[i] = max(z[i], z[i + 1]);
    for (int i = 1; i <= B; i++) s[i] = s[i - 1] + y[i];
    for (int i = 1, j = 1; i <= A; i++) {
        while (j <= B && y[j] <= x[i]) ++j;
        int k = max(j, z[i] + 1);
        ans += s[k - 1] - s[z[i]] + (i64)(B - k + 1) * x[i];
    }
    cout << ans;
}
```

---

## 作者：AutumnKite (赞：8)

## Problem

给定$n$个三元组$(a_i,b_i,c_i)$，以及三元组中每个数的上限$p,q,r$，定义一个三元组能击败另一个三元组当且仅当这个三元组中有任意两个数**严格大于**另一个三元组**对应**的两个数。求有多少三元组能击败所有$n$个三元组。

## Solution

记满足条件的三元组为$(x,y,z)$。显然如果枚举$x$，则三元组可以分为两类：$a_i<x$与$a_i\ge x$。对于$a_i<x$的三元组，只需要满足$y>b_i$**或者**$z>c_i$。而对于$a_i\ge x$的三元组，需要满足$y>b_i$**并且**$z>c_i$。

记$smx_j(j\in [1,q])$表示$b_i\ge j$的三元组中最大的$c_i$，$mx3$表示$a_i\ge x$的三元组中最大的$c_i$。那么$z$的方案数就是$r-max(smx_y,mx3)$，即$z$需要满足$z>smx_y,z>mx3$，因为对于$a_i\ge x$的三元组，$z$一定大于$c_i$，且对于$b_i\ge y$的三元组，$z$也一定大于$c_i$。

记$mx2$表示$a_i\ge x$的三元组中最大的$b_i$，那么当$x$固定时，总方案可以用`for (int i=mx2+1;i<=q;i++) ans+=r-max(smx[i],mx3);`进行统计。

这样的话，因为我们要统计$a_i\ge x$的三元组中最大的$b_i$（$mx2$），最大的$c_i$（$mx3$），所以我们应该倒着枚举$x$。

时间复杂度？$\mathcal O(n^2)$。显然不能过。

考虑优化`for (int i=mx2+1;i<=q;i++) ans+=r-max(smx[i],mx3);`这段代码。

$max$很不好处理，我们考虑把它拆开分别计算。由$smx_i$的定义可得，$\{smx_i\}$单调不升，也就是$i$越小，$smx_i$越大。那么我们找到一个$max$分界线，记为$k$，使得$i\ge k$时，$smx_i\le mx3$，$i<k$时，$smx_i>mx3$。于是就可以$\mathcal O(1)$计算答案了，用前缀和维护$\{smx_i\}$的区间和即可。

显然，$\{smx_i\},mx2,mx3$很容易维护。那么$k$怎么办呢？因为$x$从大到小枚举，$mx3$会逐渐变大，而$\{smx_i\}$单调不升，所以$k$慢慢变小（向前），一直维护即可。

一些细节具体见代码。

## Source

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
using namespace std;
int read(){
	int x=0;
	int f=1,ch=getchar();
	for (;!isdigit(ch)&&ch!=EOF;ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^'0');
	return x*f;
}
const int N=500005;
int n,La,Lb,Lc,smx[N];
struct card{
	int b,c;
};
vector<card> d[N];
long long ans,sum[N];
int main(){
	n=read(),La=read(),Lb=read(),Lc=read(); //La,Lb,Lc分别代表p,q,r
	for (register int i=1;i<=n;++i){
		int a=min(La,read()),b=min(Lb,read()),c=min(Lc,read());
		d[a].push_back((card){b,c});
		smx[b]=max(smx[b],c);
	}
	for (register int i=Lb-1;i;--i) smx[i]=max(smx[i],smx[i+1]);
	for (register int i=1;i<=Lb;++i) sum[i]=sum[i-1]+smx[i]; //smx[i]的前缀和
	int mxb=0,mxc=0,k=Lb+1; //初始值
	for (register int x=La;x;--x){ //从大到小枚举
		for (register int i=0;i<d[x].size();++i){
			int y=d[x][i].b,z=d[x][i].c;
			mxb=max(mxb,y),mxc=max(mxc,z); //维护mx2和mx3
			while (k>mxb+1&&smx[k-1]<mxc) --k; //维护k
		}
		k=max(k,mxb+1); //防止越界
		ans+=1ll*(Lc-mxc)*(Lb-k+1)+1ll*Lc*(k-mxb-1)-sum[k-1]+sum[mxb]; //利用前缀和O(1)统计答案
	}
	printf("%lld",ans);
}
```

---

## 作者：Leap_Frog (赞：4)

### P.S.
来一个垃圾的带 $\log$ 做法。  
但是很好想，像我这种傻逼都想得到（  

### Description.
有 $n$ 个三元组，问有多少好的三元组，满足比所有给定的三元组都要大。  
一个三元组 $(a,b,c)$ 是好的，当且仅当：  
- $a\le p,b\le q,c\le r$

一个三元组 $(a,b,c)$ 比三元组 $(d,e,f)$ 大，当且仅当：  
- $[a>d]+[b>e]+[c>f]\ge2$  

### Solution.
看到这个值域的范围是 $500000$，很小。  
首先我们考虑 $O(V^2\times n)$ 的做法，首先枚举前两维，然后 $O(n)$ 找出它是否已经比所有三元组大了。  
如果 $\exists i\in[1,n],[a>a_i]+[b>b_i]<1$，则无解。  
如果 $\exists i\in[1,n],[a>a_i]+[b>b_i]>1$，则第三位任意。  
否则第三位就必须满足 $>c_i$。  
然后就可以知道第三位所有可能的取值了。  

考虑优化掉一个 $n$。  
每次枚举，未免太浪费了，考虑 $a$ 从小到大的过程中，$[a>a_i]+[b>b_i]$ 不减。  
所以我们从大到小枚举 $a$，这样限制只会变多，每次直接找出当前改变后增多的限制，然后加到 $c$ 里面去即可。  
复杂度 $O(V^2+V\times n)$。  

考虑用数据结构维护它。  
我们可以使用一棵线段树来维护 $b$，线段树上每个点 $i$ 代表 $b=i$ 时 $c$ 的最小值。  
然后我们从大到小枚举 $a$，刚开始线段树上所有 $\le b_i$ 的点都有限制 $c_i$，$>b_i$ 的点则没有。  
每次 $a=a_i$，线段树上 $\le b_i$ 的所有位置都无解了，所有 $>b_i$ 的点都有限制 $c_i$ 了。  
$c_i$ 的限制是对线段树取 $\max$，就为了这个套一个吉司机线段树不合适。  
考虑我们每次是把前缀赋成 $q+1$，后缀赋成 $c_i+1$，所以这个序列一定是单调的。  
所以我们直接线段树上二分然后区间覆盖即可。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
const int N=500005;int n,p,q,r,a[N],b[N],c[N],vl[N];
struct segm{ll sm;int mx,fg,ln;}T[N<<2];vector<int>vc[N];
inline void pushup(int x) {T[x].sm=T[x<<1].sm+T[x<<1|1].sm,T[x].mx=max(T[x<<1].mx,T[x<<1|1].mx);}
inline void allc(int x,int c) {T[x].sm=1ll*T[x].ln*c,T[x].mx=T[x].fg=c;}
inline void pushdw(int x) {if(T[x].fg) allc(x<<1,T[x].fg),allc(x<<1|1,T[x].fg),T[x].fg=0;}
inline void build(int x,int l,int r)
{
	T[x].fg=0,T[x].ln=r-l+1;if(l==r) return T[x].sm=T[x].mx=vl[l],void();
	build(x<<1,l,(l+r)>>1),build(x<<1|1,((l+r)>>1)+1,r),pushup(x);
}
inline void modif(int x,int l,int r,int dl,int dr,int dc)
{
	if(l>dr||dl>r) return;else if(dl<=l&&r<=dr) return allc(x,dc);else pushdw(x);
	modif(x<<1,l,(l+r)>>1,dl,dr,dc),modif(x<<1|1,((l+r)>>1)+1,r,dl,dr,dc),pushup(x);
}
inline void chang(int x,int l,int r,int dc)
{
	if(l==r) return T[x].sm=T[x].mx=max(T[x].mx,dc),void();else pushdw(x);
	if(T[x<<1|1].mx>dc) chang(x<<1|1,((l+r)>>1)+1,r,dc),pushup(x);
	else allc(x<<1|1,dc),chang(x<<1,l,(l+r)>>1,dc),pushup(x);
}
inline void debug(int x,int l,int r)
{
	if(l==r) return printf("%d%c",T[x].mx,l==q?'\n':' '),void();
	pushdw(x),debug(x<<1,l,(l+r)>>1),debug(x<<1|1,((l+r)>>1)+1,r);
}
int main()
{
	read(n),read(p),read(q),read(r),vl[q+1]=1;
	for(int i=1;i<=n;i++) read(a[i]),read(b[i]),read(c[i]),vc[a[i]].push_back(i);
	for(int i=1;i<=n;i++) vl[b[i]]=max(c[i]+1,vl[b[i]]);//a=p+1
	ll rs=0;for(int i=q;i>=1;i--) vl[i]=max(vl[i],vl[i+1]);
	//for(int i=1;i<=q;i++) printf("%d%c",vl[i],i==q?'\n':' ');
	build(1,1,q);for(int i=p;i>=1;i--,rs+=1ll*(r+1)*q-T[1].sm)
		for(auto j:vc[i]) chang(1,1,q,c[j]+1),modif(1,1,q,1,b[j],r+1);
	return printf("%lld\n",rs),0;
}
```

---

## 作者：shight (赞：3)

模拟赛遇到的题目。

看各位大佬的做法都不是很懂，于是自己一通乱搞搞出来了。

## 题意

[翻译清楚的不能再清楚了](https://www.luogu.com.cn/problem/CF815D)

## 做法

为了方便叙述，我们将每个给出的三元组表示成 $(a_i,b_i,c_i)$，所选的三元组表示成$(x,y,z)$。

首先我们考虑如果 $c_i$ 相等（设为 $c$）怎么做：

直接做看起来很麻烦，于是我们考虑正难则反，由算可行解数量改为算不可行解数量，并维护对于每一个 $y$ 可选的 $x$ ，显然对于每一个$y$，$x$的选择满足单调性。

然后我们分类讨论一下 $z$ 和 $c_i$ 的大小关系

当 $z \le c$ 时，对于每一个三元组,当 $y \in [1,b_i]$ 时， $x>p$；当 $y \in (b_i,q] $时，$x>a_i$。

当 $z>c$ 时，对于每一个三元组，只需满足当 $y \in [1,b_i]$时，$x>a_i$ 即可。

拿个线段树维护一下就可以了。

然后我们将这种做法拓展一下，我们先把原序列按 $c_i$ 从大到小排序，可以轻易发现此时当 $z \in (c_i,c_{i+1}]$ 时，每一个 $z$ 贡献都是一样的

对于每一个区间$(c_i,c_{i+1}]$，我们考虑上面的做法来算贡献，显然对于前 $i$ 个三元组，满足 $z>c$ 的条件，对于后面的三元组，满足 $z \le c$ 的条件。

且显然 $z \le c$ 的条件是比 $z > c$ 完全严格的，所以每次修改的时候把 $z > c$的条件给当前枚举到的三元组加上去就好了。

然后关于这个线段树，我们需要维护区间最大值，区间求和，这个可以自行百度解决（相信做到这道题的大佬都会）。

```cpp
#include <bits/stdc++.h>
#define int long long
#define INF 2147483647
#define N 1000005
#define mkp make_pair
#define pii pair<int,int>
#define pb push_back
using namespace std;
int n,A,B,C,ans=0;
struct Y{int a,b,c;}a[N];
int cmp(Y x,Y y){return x.c>y.c;}
struct Ji_seg{
	struct Tr{
		int mn,tag,t,se,sum;
	}tr[N<<2];
	int ls(int nw){return nw*2;}
	int rs(int nw){return nw*2+1;}
	void change(int nw,int l,int r,int k){//对nw节点的区间进行区间取max 
		if(k<=tr[nw].mn)return;
		if(k<tr[nw].se){
			tr[nw].sum+=(k-tr[nw].mn)*tr[nw].t;
			tr[nw].mn=k;tr[nw].t=max(tr[nw].t,1ll);tr[nw].tag=max(tr[nw].tag,k);
			return;
		}
		int mid=(l+r)/2;
		change(ls(nw),l,mid,k);change(rs(nw),mid+1,r,k);push_up(nw);
	}
	void push_down(int nw,int l,int r){
		if(tr[nw].tag){
			int mid=(l+r)/2;
			change(ls(nw),l,mid,tr[nw].tag);
			change(rs(nw),mid+1,r,tr[nw].tag);
			tr[nw].tag=0;
		}
	}
	void push_up(int nw){
		tr[nw].sum=tr[ls(nw)].sum+tr[rs(nw)].sum;
		if(tr[ls(nw)].mn==tr[rs(nw)].mn){
			tr[nw].mn=tr[ls(nw)].mn;
			tr[nw].t=tr[ls(nw)].t+tr[rs(nw)].t;
			tr[nw].se=min(tr[ls(nw)].se,tr[rs(nw)].se);
			return;
		}
		if(tr[ls(nw)].mn<tr[rs(nw)].mn){tr[nw].mn=tr[ls(nw)].mn;tr[nw].t=tr[ls(nw)].t;tr[nw].se=min(tr[ls(nw)].se,tr[rs(nw)].mn);}
			else {tr[nw].mn=tr[rs(nw)].mn;tr[nw].t=tr[rs(nw)].t;tr[nw].se=min(tr[rs(nw)].se,tr[ls(nw)].mn);}
	}
	void build(int nw,int l,int r){
		if(l==r){
			tr[nw].sum=0;tr[nw].mn=0;tr[nw].se=INF;tr[nw].t=1;tr[nw].tag=0;
			return;
		}
		int mid=(l+r)/2;
		build(ls(nw),l,mid);
		build(rs(nw),mid+1,r);
		push_up(nw);
	}
	void update(int nw,int l,int r,int x,int y,int k){
		if(x>y)return;
		if(x<=l&&r<=y){
			change(nw,l,r,k);
			return;
		}
		int mid=(l+r)/2;push_down(nw,l,r);
		if(x<=mid)update(ls(nw),l,mid,x,y,k);
		if(y>mid)update(rs(nw),mid+1,r,x,y,k);
		push_up(nw);
	}
}T;
signed main() {
	scanf("%lld %lld %lld %lld",&n,&A,&B,&C);
	for(int i=1;i<=n;i++)scanf("%lld %lld %lld",&a[i].a,&a[i].b,&a[i].c);
	sort(a+1,a+n+1,cmp);a[0]=Y{0,0,C};a[n+1]=Y{0,0,0};
	T.build(1,1,B);
	for(int i=1;i<=n;i++)T.update(1,1,B,1,a[i].b,a[i].a);
	for(int i=0;i<=n;i++){
		T.update(1,1,B,1,a[i].b,A);T.update(1,1,B,a[i].b+1,B,a[i].a);
		ans+=(a[i].c-a[i+1].c)*(A*B-T.tr[1].sum);
	}
	printf("%lld\n",ans);
	return 0;
}


```


---

## 作者：_Kenma_ (赞：0)

## 前言

有点困难题。

## 思路分析

考虑本质上是三维问题，考虑降维处理。

因为全部满足条件不好做，考虑正难则反，计算不合法的三元组个数。

首先对 $a_i$ 排序，从大往小做扫描线，每次维护 $b=i$ 时 $c$ 的最大不合法值，那么对于每一个 $a$，不合法的三元组数量等于全局和。

最开始，对于每个限制 $(a_i,b_i,c_i)$，设线段树维护的序列为 $d$，相当于 $\max_{j=1}^{b_i} d_j\le c_i$，因为只需要满足一个，所以在区间 $[1,b_i]$ 取 $\max$ 即可。

每次扫到限制 $(a_i,b_i,c_i)$ 时，$[1,b_i]$ 的部分合法，而 $[b_i+1,q]$ 的部分需要满足 $\max_{j=b_i+1}^{q} d_j \le c_i$，相当于两次区间取 $\max$。

为了区间取 $\max$ 写 seg_beat 肯定不值当，注意到我们维护的序列 $d$ 是有单调性的，所以直接线段树二分 + 区间推平就行。

总体复杂度 $O(v \log (n+v))$。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p,q,r,ans,now,minb[500005],minc[500005],d[500005];
struct node{
	int a,b,c;
}h[500005];
int val_sum[1000005],val_min[1000005],tag[1000005],ls[1000005],rs[1000005],dcnt,rt;
void pushup(int x){
	val_sum[x]=val_sum[ls[x]]+val_sum[rs[x]];
	val_min[x]=min(val_min[ls[x]],val_min[rs[x]]);
}
void pushdown(int l,int r,int x){
	if(!tag[x]) return;
	int mid=(l+r)>>1;
	tag[ls[x]]=tag[rs[x]]=val_min[ls[x]]=val_min[rs[x]]=tag[x];
	val_sum[ls[x]]=(mid-l+1)*tag[x];
	val_sum[rs[x]]=(r-mid)*tag[x];
	tag[x]=0;
}
void build(int l,int r,int &x){
	x=++dcnt;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,ls[x]);
	build(mid+1,r,rs[x]);
	pushup(x);
}
void modify(int l,int r,int ql,int qr,int k,int x){
	if(ql<=l && r<=qr){
		val_min[x]=tag[x]=k;
		val_sum[x]=(r-l+1)*k;
		return;
	}
	pushdown(l,r,x);
	int mid=(l+r)>>1;
	if(ql<=mid) modify(l,mid,ql,qr,k,ls[x]);
	if(qr>=mid+1) modify(mid+1,r,ql,qr,k,rs[x]);
	pushup(x);
}
int findl(int l,int r,int ql,int qr,int k,int x){
	if(l==r){
		if(val_min[x]>k) return -1;
		else return l;
	}
	pushdown(l,r,x);
	int mid=(l+r)>>1,ans=-1;
	if(ql<=mid){
		if(val_min[ls[x]]<=k) ans=findl(l,mid,ql,qr,k,ls[x]);
		if(ans!=-1) return ans;
	}
	if(qr>=mid+1){
		if(val_min[rs[x]]<=k) ans=findl(mid+1,r,ql,qr,k,rs[x]);
		if(ans!=-1) return ans;
	}
	return ans;
}
void add(int l,int r,int k){
	int p=findl(1,q,l,r,k,rt);
	if(p!=-1) modify(1,q,p,r,k,rt);
}
void init(){
	for(int i=1;i<=n;i++){
		add(1,h[i].b,h[i].c);
	}
}

bool cmp(node a,node b){
	return a.a<b.a;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>p>>q>>r;
	for(int i=1;i<=n;i++){
		cin>>h[i].a>>h[i].b>>h[i].c;
	}
	sort(h+1,h+1+n,cmp);
	build(1,q,rt);
	init();
	now=n;
	for(int i=p;i>=1;i--){
		while(now && h[now].a>=i){
			add(h[now].b+1,q,h[now].c);
			add(1,h[now].b,r);
			now--;
		}
		ans+=val_sum[1];
	}
	cout<<p*q*r-ans;
	return 0;
}
```

---

## 作者：王华 (赞：0)

首先考虑将问题形式化。
$$
\sum_{i=1}^p\sum_{j=1}^q\sum_{k=1}^r\prod_{w=1}^n[[a_w<i]+[b_w<j]+[c_w<k] \ge2]
$$
考虑一步步去降维解决这个问题，直接枚举是 $O(npqr)$的。

注意到，当 $a_w\ge i$ 时，后两项必然要符合条件。

我们记 $B(i)$ 表示，对于满足 $a_j\ge i$ 的所有 $j$，$b_j$ 的最大值，$C(i)$ 同理，是 $c_j$ 的最大值。

因此，可以改写为
$$
\sum_{i=1}^p\sum_{j=B(i)+1}^q\sum_{k=C(i)+1}^r\prod_{w=1}^n[[a_w<i]+[b_w<j]+[c_w<k] \ge2]
$$

我们考虑从大到小枚举 $i$，将所有卡牌按照 $a$ 从小到大排序，每次对 $a_j=i$ 的 $j$ 维护 $B(i)$ 和 $C(i)$，并且要和 $B(i+1),C(i+1)$ 取最大值，这样就能边枚举边维护 $B(i)$ 和 $C(i)$ 了。

由于卡牌顺序对答案没有影响，可以将其先按照上述规则，即按 $a$ 的大小排好序，我们可以用一个指针来辅助对$B(i)$和$C(i)$的维护，记为 $cnt$ ，依次要加入的卡牌编号只会不断变小，因此 $cnt$ 单调递减，我们的式子可以继续改写，我们已经在枚举 $i$，先不在式子里写 $i$ 的和式符号。
$$
\sum_{j=B(i)+1}^q\sum_{k=C(i)+1}^r\prod_{w=1}^{cnt-1}[[b_w<j]+[c_w<k] \ge 1]
$$

通过不同的枚举顺序，我们成功将里面的取等条件消去一个，考虑继续消。

我们记 $mx_i$ 表示，对于所有 $j$ 满足 $b_j\ge i$，$c_j$的最大值。那我们的式子可以继续改写。

$$
\sum_{j=B(i)+1}^q r-\max(C(i),mx_j)
$$

我们之所以可以这样改写，是因为对于任意满足 $b_w\ge j$ 的 $w$，它们的下标都会比当前的 $cnt$ 要小，否则会因为不满足第一个条件被 $B(i)$ 统计到。要是不满足 $b$ 的限制，那么就必然要满足 $c$ 的限制，因此第三维的最小值必须要大于两者。

这个式子可以直接用数据结构维护，但事实上，我们可以继续优化。
根据 $mx$ 的定义，它必然是随着 $j$ 的递减单调递增，因此存在一个断点，断点的两端 $\max(C(i),mx_j)$ 分别只会都取左项或右项。

因为我们已经将卡牌排好序，卡牌的增添维护是单调的，这个断点也是单调的，我们可以也用一个类似 $cnt$ 的指针来维护它。断点一旦确定，就可以把上述式子用 $mx$ 的前缀和来 $O(1)$ 计算。我们获得了一个线性的做法。

---

## 作者：ningago (赞：0)

考虑直接降维，一维枚举，一维维护，一维作为值。

动态维护 $b$ 这一维，维护的值为能取到多少个 $c$ ，按照 $a/b>a_i/b_i$ 的满足情况，$c$ 的条件有三类：随便取 / $c>c_i$ / 怎么取都不行。

从大到小枚举 $a$ 这一维，每次会有若干个 $i$ 使得 $a>a_i$ 变得不满足，具体的限制变化情况为：

- 对于 $b>b_i$，限制从随便取变成 $c>c_i$。
- 对于 $b\leq b_i$，限制从 $c>c_i$ 变成无解。

相当于是在 $b$ 对应的数据结构上进行前缀修改无解，后缀 $chkmin(c_{mx}-c_i)$。

注意到对于后缀 $[j,b_{mx}]$ 进行 chkmin 时，$[1,j)$ 这个区间的所有数一定小于等于 $c_{mx}-c_i$，因为从开始就限制过了。所以后缀 chkmin 和全局 chkmin 没有区别。

又注意到，最开始的数组是单调递增的，所以整个过程使用双指针维护即可。

复杂度 $O(n)$。

https://codeforc.es/contest/815/submission/230975303

---

