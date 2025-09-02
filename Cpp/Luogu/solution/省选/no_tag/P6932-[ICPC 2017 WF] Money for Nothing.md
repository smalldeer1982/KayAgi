# [ICPC 2017 WF] Money for Nothing

## 题目描述

在这个问题中，你将解决自古以来人类面临的最深刻的挑战之一——如何赚很多钱。

你是小工具市场中的一个中间商。你的工作是从小工具生产公司购买小工具，然后将其出售给小工具消费公司。每个小工具消费公司每天都有一个开放的请求，直到某个结束日期，并且有一个愿意购买小工具的价格。另一方面，每个小工具生产公司都有一个开始交付小工具的日期和一个交付每个小工具的价格。

由于公平竞争法，你只能与一个生产公司和一个消费公司签订合同。你将从生产公司购买小工具，每天一个，从它可以开始交付的那天开始，到消费公司指定的日期结束。在这些天中，你赚取生产商的售价与消费者的购买价之间的差额。

你的目标是选择能够最大化利润的消费公司和生产公司。

## 说明/提示

时间限制：5 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2 2
1 3
2 1
3 5
7 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
1 2
10 10
9 11
11 9
```

### 输出

```
0
```

# 题解

## 作者：HenryHuang (赞：17)

# 「ICPC2017 WF」Money for Nothing

我们可将生产商和消费商都看成二维平面上的点，其坐标分别为 $(d_i,p_i)$，$(e_i,q_i)$。

那么问题转变为：

给定平面上的 $m$ 个 $A$ 类点 $(d_i,p_i)$，以及 $n$ 个 $B$ 类点 $(e_i,q_i)$。求选择一个 $A$ 类点作为矩形左下角，一个 $B$ 类点作为矩形右上角所能得到的最大面积。若不存在这样的矩形就输出零。

考虑如下几种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/3rdhn8k6.png)

在这种情况下 $A_1,A_2$ 都能与 $B$ 围成一个矩形，但显然 $A_1$ 更优秀。

故对于这样的 $A$ 点我们可以直接舍弃。

![](https://cdn.luogu.com.cn/upload/image_hosting/lkux9px4.png)

在这种情况下 $B_1,B_2$ 都能与 $A$ 围成一个矩形，但显然 $B_1$ 更优秀。

故对于这样的 $B$ 点我们可以直接舍弃。

舍弃掉这些点过后两种点在平面上的排布一定是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/qpr85721.png)

然后我们考虑这样一种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/syfg1b9t.png)

设 $A_1,B_1$ 围成的矩形是以 $A_1$ 为左下角的矩形当中最大的那一个。

我们可以得到这样一个结论：

$A_2$ 和 $B_2$ 围成的矩形的大小一定小于 $A_2$ 和 $B_1$ 围成的矩形的大小。

![](https://cdn.luogu.com.cn/upload/image_hosting/5rlrkrbo.png)

我们给这几个部分编个号，下面用编号代替上图中的部分。

根据我们前面的条件，有 $3+4+5>3+4+1+2\rightarrow 5>1+2$。

我们要证明的即 $4+6+5+7>4+6+2\rightarrow 5+7>2\rightarrow 1+2+7> 2$。

所以我们推广一下可以得到这样一个结论：对于每个红点，其围成最大矩形的黄点具有单调性。

根据这个性质我们直接分治就好了。

总时间复杂度为 $O(n\log_2n)$。

```cpp
/*---Author:HenryHuang---*/
/*---Never Settle---*/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=5e5+5;
struct cc{
	int x,y;
	LL operator*(const cc &h)const{
		return 1ll*(h.x-x)*(h.y-y);
	}
}a[maxn],b[maxn],p[maxn];
int sa,sb;
LL Ans;
void solve(int l,int r,int ll,int rr){
	if(l>r||ll>rr) return ;
	int mid=(l+r)>>1;
	LL ans=-1e18,id=0;
	for(int i=ll;i<=rr;++i){
		if(a[mid].x<b[i].x||a[mid].y<b[i].y){
			if(a[mid]*b[i]>ans){
				ans=a[mid]*b[i];
				id=i;
			}
		}
	}
	if(id!=0){
		solve(l,mid-1,ll,id);
		solve(mid+1,r,id,rr);
		Ans=max(Ans,ans);
	}
	
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int m,n;cin>>m>>n;
	for(int i=1;i<=m;++i){
		cin>>p[i].x>>p[i].y;
	}
	sort(p+1,p+m+1,[&](cc a,cc b){return a.x==b.x?a.y<b.y:a.x<b.x;});
	a[++sa]=p[1];
	for(int i=2;i<=m;++i){
		if(a[sa].y>p[i].y) a[++sa]=p[i];
	}
	for(int i=1;i<=n;++i){
		cin>>p[i].x>>p[i].y;
	}
	sort(p+1,p+n+1,[&](cc a,cc b){return a.x==b.x?a.y<b.y:a.x<b.x;});
	reverse(p+1,p+n+1);
	b[++sb]=p[1];
	for(int i=2;i<=n;++i){
		if(b[sb].y<p[i].y) b[++sb]=p[i];
	}
	reverse(b+1,b+sb+1);
	for(int i=1;i<=sb;++i) cout<<b[i].x<<' '<<b[i].y<<'\n';
	solve(1,sa,1,sb);
	cout<<Ans<<'\n';
	return 0;
}
```



---

## 作者：老莽莽穿一切 (赞：8)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16203886.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/P6932)

[**loj link**](https://loj.ac/p/6473)

一道可以作为决策单调性模板题刷的题。

考虑暴力怎么做，其实就是把生产商和消费商两两匹配算一遍答案，时间复杂度 $\mathcal O\left(n^2\right)$（$n$ 和 $m$ 同阶，所以时间复杂度中统一写作 $n$）。

直接暴力肯定是不行的，得考虑优化，可以先进行第一波基本优化——消去无用决策。

我们可以大力发扬人类智慧，利用生活常识进行剪枝，首先我们可以发现，如果两个生产商进行比较，一个生产商来得又晚，东西又贵，你显然嫌弃他，同理两个消费商中走得早还出钱少肯定也不行，可以考虑排序把这些都去掉。

这样我们现在将生产商和消费商都按时间排好序后剪枝就得到生产商的售价越来越低，消费商的买价也越来越低的两个数组。

然后考虑进一步优化，这里就需要用一点黑科技了，考虑决策单调性优化。

怎么发现决策单调性呢？可以考虑打表发现规律，也可以用四边形不等式，这里博主使用一种最最简单的办法——暴力算。

我们设第 $i$ 个生产商的到达时间为 $l_i$，售价为 $a_i$，第 $i$ 个消费商的离开时间为 $r_i$，买价为 $b_i$，则第 $i$ 个生产商和第 $j$ 个消费商组合的收益是 $(r_j-l_i)(b_j-a_i)$。

考虑反证法，设两个消费商 $i$ 和 $i'$ 满足 $l_i<l_{i'}$，两个生产商 $j$ 和 $j'$ 满足 $r_j<r_{j'}$，且满足对 $i$ 来说和 $j'$ 组合比和 $j$ 组合更优，而对 $i'$ 来说反而是 $j$ 更优，则满足下面的式子：

$$
\begin{aligned}
(r_{j'}-l_i)(b_{j'}-a_i)>(r_j-l_i)(b_j-a_i)\\
(r_{j'}-l_{i'})(b_{j'}-a_{i'})<(r_j-l_{i'})(b_j-a_{i'})
\end{aligned}
$$

对两个式子进行展开移项得到：

$$
\begin{aligned}
r_{j'}b_{j'}-r_jb_j>l_i(b_{j'}-b_j)+a_i(r_{j'}-r_j)\\
r_{j'}b_{j'}-r_jb_j<l_{i'}(b_{j'}-b_j)+a_{i'}(r_{j'}-r_j)
\end{aligned}
$$

合并得：

$$
l_i(b_{j'}-b_j)+a_i(r_{j'}-r_j)<l_{i'}(b_{j'}-b_j)+a_{i'}(r_{j'}-r_j)
$$

因为满足 $l_{i'}>l_i$，$a_{i'}<a_i$，$r_{i'}>r_i$，$b_{i'}<b_i$，所以与上式是矛盾的，所以假设错误，确实满足决策单调性。

满足决策单调性以后呢？怎么利用决策单调性优化我们的搜索，也就是在一个较优的时间复杂度内找到每个消费商的最优生产商。

我们考虑可以以一种类似整体二分的方式，用消费商去匹配生产商，利用分治的思想，以及利用之前找到的最优决策点来缩小我们现在的搜索区间，假设我们现在正在寻找 $[l,r]$ 这个区间里每个点的最优决策点，决策点的可能区间为 $[L,R]$，我们可以找到第 $mid=\left\lfloor\dfrac{l+r}2\right\rfloor$ 个消费商的决策点，我们发现 $[l,mid-1]$ 的最优决策点都在该决策点以左，$[mid+1,r]$ 同理，这样我们只要再递归解决，只需要递归 $\mathcal O\left(\log n\right)$ 层就能解决，每层搜索的总和是 $\mathcal O\left(n\right)$ 的，所以总时间复杂度 $\mathcal O\left(n\log n\right)$。

[**c++ 代码**](https://www.cnblogs.com/LaoMang-no-blog/p/16203886.html)

---

## 作者：UltiMadow (赞：5)

题意可简化为 $m$ 个矩形左下角和 $n$ 个矩形右上角能组成的最大矩形面积

对于每一个矩形左下角的点，发现满足对于 $\forall i,j, x_i\le x_j,y_i\le y_j$，那么 $j$ 一定不会比 $i$ 优，直接从序列中删除

同理对于每一个矩形右上角的点，发现满足对于 $\forall i,j,x_i\ge x_j,y_i\ge y_j$，那么 $j$ 一定不会比 $i$ 优，也直接从序列中删除

我们对于剩下来所有的左下角按 $x$ 坐标排序，发现对于 $\forall i,j,x_i<x_j$ 都有 $y_i>y_j$，所有右上角的点也是这样

于是我们可以发现一个决策单调性

我们假设有左上角 $(x_1,y_1), \ (x_2,y_2),\ x_1<x_2$，右下角 $(x_p,y_p)$，且 $(x_1,y_1)$ 比 $(x_2,y_2)$ 更优，那么有

$(x_p-x_1)(y_p-y_1)-(x_p-x_2)(y_p-y_2)>0$

整理得：$-x_p(y_1-y_2)-y_p(x_1-x_2)+(x_1y1-x_2y_2)>0$

那么对于右上角点 $(x_q,y_q),\ x_q<x_p$，有 $y_q>y_p$，又由于 $y_1-y_2>0$，$x_1-x_2<0$，所以决策单调性得证

发现上一步决策不会影响下一步决策，于是用分治法写决策单调性即可

时间复杂度 $\mathcal O(n\log n)$

code:

```cpp
#include<bits/stdc++.h>
#define MAXN 500010
#define inf 0x3f3f3f3f3f3f3f3f
#define int long long
using namespace std;
int n,m,ans;
struct Node{int x,y;}pld[MAXN],pru[MAXN],ld[MAXN],ru[MAXN];
bool cmp(Node a,Node b){return a.x==b.x?a.y<b.y:a.x<b.x;}
void solve(int l,int r,int L,int R){
	if(l>r)return;if(L>R)return;
	int mid=(l+r)>>1,p=L,now=0;
	for(int i=L;i<=R;i++){
		if(ru[mid].x-ld[i].x<=0&&ru[mid].y-ld[i].y<=0){
			solve(l,mid-1,L,i);solve(mid+1,r,i,R);
			return;
		}
		int val=(ru[mid].x-ld[i].x)*(ru[mid].y-ld[i].y);
		if(val>now)now=val,p=i;
	}
	ans=max(ans,now);
	solve(l,mid-1,L,p);solve(mid+1,r,p,R);
}
signed main(){
	scanf("%lld%lld",&m,&n);
	for(int i=1;i<=m;i++)scanf("%lld%lld",&pld[i].x,&pld[i].y);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&pru[i].x,&pru[i].y);
	sort(pld+1,pld+m+1,cmp);sort(pru+1,pru+n+1,cmp);
	int y=inf,M=0,N=0;
	for(int i=1;i<=m;i++)
		if(pld[i].y<y)ld[++M]=pld[i],y=pld[i].y;
	for(int i=1;i<=n;i++){
		while(N&&ru[N].y<pru[i].y)N--;
		ru[++N]=pru[i];
	}
	solve(1,N,1,M);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：灵华 (赞：4)

## P6932 [ICPC2017 WF]Money for Nothing

***

因为赚取的差价就是等于时间之差与价格之差的乘积。

所以可以看成是平面上的问题。

建立一个直角坐标系，将时间作为横坐标，价格作为纵坐标。

然后将生产商和消费商的信息转为平面上的点，其中将生产商划为A类点，消费商划为B类点。

矩阵面积 = 长 $\times $ 宽

= （任意一个 $A$ 类点和一个 $B$ 类点的）两点横坐标之差 $\times $ 两点纵坐标之差

= 时间之差 $\times $ 价格之差

= 赚取的差价

之后问题就成了在平面上 **左下角为 $A$ 类点** **右上角为 $B$ 类点** 求最大的矩阵面积的问题。

***

在处理之前，可以先排除一些无用的状态。

先将 $A$ 类点按坐标进行排序。

![a](https://cdn.luogu.com.cn/upload/image_hosting/qgd3f5h6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果 $A$ 类点其中的两点出现了上图的情况。

显然，由 $ a_1 $ 点为左下角的矩阵一定不会比以 $ a_2 $ 点为左下角的矩阵的面积更大。

所以可以排除 $ a_1 $ 点，将 $ a_1 $ 点从候选集合中删去。

之后是将 $B$ 类点按坐标进行排序。

![b](https://cdn.luogu.com.cn/upload/image_hosting/x6pdc3zg.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果 $B$ 类点其中的两点出现了上图的情况。

同样，由 $ b_1 $ 点为右上角的矩阵一定不会比以 $ b_2 $ 点为右上角的矩阵的面积更大。

所以我们可以将 $ b_1 $ 点从候选集合中删去。

***

我们发现在排除所有无用的点之后，$A$ 类点和 $B$ 类点都呈现出 $x$ 递增 $y$ 递减的样子。

![ab](https://cdn.luogu.com.cn/upload/image_hosting/pklyypuu.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

（大概就是这样 $ \uparrow $ ）。

***

**之后可以列出状态转移方程：**

设 $ f_i $ 为以 $ a_i $ 为左下角的最大矩形面积。

$$
f_i = \max( val(i,j) ) (j\in B)
$$

$ val(i,j) $ 表示以 $ a_i $ 和 $ b_j $ 为左下角和右下角的矩形面积。

因为这个式子一看就是 $ O(n^2) $ 的复杂度，肯定会被卡。

***

考虑优化：

在去除无用点后的任意两个 $A$ 类点和任意两个 $B$ 类点中。

![ab2](https://cdn.luogu.com.cn/upload/image_hosting/zg65s4ay.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

引理：

如果 矩形 $ a_1 b_2 $ 的面积 $ > $ 矩形 $ a_1 b_1 $ 的面积。

那么 矩形 $ a_2 b_2 $ 的面积 $ > $ 矩形 $ a_2 b_1 $ 的面积。

证明（看上图）：

$ \because val(a_1,b_2) > val(a_1,b_2) $

$ \therefore 3 + 4 + 5 > 1 + 2 + 3 + 4 $

$ \therefore 5 > 1 + 2 $

而其中：

$ val(a_2,b_1) = 2 + 4 + 6 $

$ val(a_2,b_2) = 4 + 5 + 6 + 7 $

所以，又 $ \because 5 > 1 + 2 $

 $ \therefore 4 + 5 + 6 + 7 > 1 + 2 + 4 + 6 $

 $ \therefore 4 + 5 + 6 + 7 > 2 + 4 + 6 $

 $ \therefore val(a_2,b_2) > val(a_2,b_1) $

证毕。

由此我们就可以用决策单调性来优化。

复杂度： $ O(n\log n) $。

~~我感觉我的复杂度应该是比较优秀了。~~

~~为什么比他们那些俩个log的跑的还慢。~~

是我复杂度算错了吗，求路过的大佬指正。

***

好了，最后上AC代码。

## Code：

```cpp
#include <iostream>
#include <algorithm>
using namespace std ;

#define int long long

struct Point
{
	int x , y ;
	inline friend bool operator < ( Point i , Point j )
	{
		if ( i .x == j .x )
			return i .y < j .y ;
		return i .x < j .x ;
	}
} a[500005] , b[500005] , c[500005] , d[500005] ;

struct Node
{
	int j , l , r ;
} q[500005] ;

int n , m , nt , mt , head , tail , ans ;

inline int Abs ( int x )
{
	if ( x < 0 )
		return -x ;
	return x ;
}

inline int calc ( int i , int j )
{
	int f = 1 , res = Abs ( ( b [ j ] .x - a [ i ] .x ) * ( b [ j ] .y - a [ i ] .y ) ) ;
	if ( a [ i ] .x > b [ j ] .x || a [ i ] .y > b [ j ] .y )
		f = -1 ;
	return f * res ;
}

signed main ( )
{
	cin >> n >> m ;
	for ( int i = 1 ; i <= n ; ++ i )
		cin >> c [ i ] .x >> c [ i ] .y ;
	for ( int i = 1 ; i <= m ; ++ i )
		cin >> d [ i ] .x >> d [ i ] .y ;
	sort ( c + 1 , c + 1 + n ) ;
	sort ( d + 1 , d + 1 + m ) ;
	a [ 1 ] = c [ 1 ] ;
	nt = 1 ;
	for ( int i = 2 ; i <= n ; ++ i )
	{
		if ( c [ i ] .y < a [ nt ] .y )
			a [ ++ nt ] = c [ i ] ;
	}
	b [ 1 ] = d [ 1 ] ;
	mt = 1 ;
	for ( int i = 2 ; i <= m ; ++ i )
	{
		while ( mt && d [ i ] .y > b [ mt ] .y )
			-- mt ;
		b [ ++ mt ] = d [ i ] ;
	}
	head = tail = 1 ;
	q [ 1 ] .j = 1 ;
	q [ 1 ] .l = 1 ;
	q [ 1 ] .r = nt ;
	for ( int i = 2 ; i <= mt ; ++ i )
	{
		int pos = nt + 1 ;
		while ( head <= tail )
		{
			if ( ( calc ( q [ tail ] .l , i ) > 0 ) && calc ( q [ tail ] .l , i ) >= calc ( q [ tail ] .l , q [ tail ] .j ) )
			{
				pos = q [ tail ] .l ;
				-- tail ;
				continue ;
			}
			if ( calc ( q [ tail ] .r , i ) < calc ( q [ tail ] .r , q [ tail ] .j ) )
				break ;
			int l = q [ tail ] .l , r = q [ tail ] .r + 1 , mid ;
			while ( l < r )
			{
				mid = ( l + r ) >> 1 ;
				if ( calc ( mid , i ) >= calc ( mid , q [ tail ] .j ) )
					r = mid ;
				else
					l = mid + 1 ;
			}
			pos = r ;
			q [ tail ] .r = pos - 1 ;
			break ;
		}
		if ( pos <= nt )
		{
			q [ ++ tail ] .j = i ;
			q [ tail ] .l = pos ;
			q [ tail ] .r = nt ;
		}
	}
	for ( int i = 1 ; i <= nt ; ++ i )
	{
		while ( q [ head ] .r < i )
			++ head ;
		ans = max ( ans , calc ( i , q [ head ] .j ) ) ;
	}
	cout << ans << endl ;
	return 0 ;
}
```

***

---

## 作者：Loser_Syx (赞：1)

题面翻的不是特别好，其实是每天早上可以在生产商买一个，然后在晚上卖给消费商，那么显然赚的钱 $w=(e_y-d_x)(q_y-p_x)$。

然后发现，如果存在两个生产商 $i,j$ 满足 $d_i \leq d_j$ 且 $p_i \leq p_j$，那么选 $j$ 一定不如选 $i$，直接在可能决策中去除 $j$ 这个选项即可。

同样，对于消费者 $i,j$，如果存在 $e_i \geq e_j$ 且 $q_i \geq q_j$，也可以直接去除 $j$。

把题目转化成平面图上选两个点围成矩形最大，那么容易发现存在决策单调性，故考虑决策单调性分治。

复杂度 $O(n \log n)$。

```cpp
const int N = 5e5 + 19;
pii a[N], b[N];
int n, m, A=1, B=1, ans=0;
void solve(int l, int r, int pl, int pr) {
	if (l > r) return ;
	int mid((l + r) >> 1), pos=0, now=-1e18;
	for (int i=pl;i<=pr;++i) if ((b[i].F>=a[mid].F||b[i].S>=a[mid].S)&&(b[i].F-a[mid].F)*(b[i].S-a[mid].S)>now) {
		now=(b[i].F-a[mid].F)*(b[i].S-a[mid].S); pos=i;
	} if (pos) {
		smax(ans, now);
		solve(l, mid-1, pos, pr); solve(mid+1, r, pl, pos);
	}
}
signed main() {
	read(n, m);
	for (int i=1;i<=n;++i) read(a[i].F,a[i].S);
	for (int i=1;i<=m;++i) read(b[i].F,b[i].S);
	sort(a+1,a+1+n,[&](pii x,pii y) { return x.F==y.F?x.S<y.S:x.F<y.F; } );
	for (int i=2;i<=n;++i) if (a[i].S<a[A].S) a[++A]=a[i];
	sort(b+1,b+1+m,[&](pii x,pii y) { return x.F==y.F?x.S>y.S:x.F>y.F; } );
	for (int i=2;i<=m;++i) if (b[i].S>b[B].S) b[++B]=b[i];
	solve(1,A,1,B); write(ans);
	return 0;
}
```

---

## 作者：Reunite (赞：0)

丢到平面上，转化为在两个点集中选择两个点做为矩形左下和右上端点，最大化矩形面积。

显然对于对于左下角所在点集，若一个点左下有点则一定不优，右上同理，则最后两部分点集点都同时具有 $x,y$ 的单调性。

去掉无用的点，直接做是 $O(n^2)$ 的，简单画一下发现这个具有决策单调性，直接上分治就好了。复杂度 $O(n\log n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;

int n,m,mx;
struct node{int x,y;};
node a[500005];
node b[500005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline void solve(int l,int r,int L,int R){
	if(l>r) return ;
	int mid=(l+r)>>1,mxx=-1e18,pos=R;
	for(int i=L;i<=R;i++){
		int x=(b[i].x-a[mid].x)*(b[i].y-a[mid].y);
		if((b[i].x>=a[mid].x||b[i].y>=a[mid].y)&&x>mxx) mxx=x,pos=i;
	}
	mx=max(mx,mxx);
	solve(l,mid-1,pos,R);
	solve(mid+1,r,L,pos);
	return ;
}

signed main(){
	in(n),in(m);
	for(int i=1;i<=n;i++) in(a[i].x),in(a[i].y);
	for(int i=1;i<=m;i++) in(b[i].x),in(b[i].y);
	int nn=1,mm=1;
	sort(a+1,a+1+n,[](node p,node q){return p.x==q.x?p.y<q.y:p.x<q.x;});
	for(int i=2;i<=n;i++) if(a[i].y<a[nn].y) a[++nn]=a[i];
	sort(b+1,b+1+m,[](node p,node q){return p.x==q.x?p.y>q.y:p.x>q.x;});
	for(int i=2;i<=m;i++) if(b[i].y>b[mm].y) b[++mm]=b[i];
	solve(1,nn,1,mm);
	printf("%lld\n",mx);

	return 0;
}
```

---

