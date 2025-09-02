# Guard Towers

## 题目描述

In a far away kingdom lives a very greedy king. To defend his land, he built $ n $ guard towers. Apart from the towers the kingdom has two armies, each headed by a tyrannical and narcissistic general. The generals can't stand each other, specifically, they will never let soldiers of two armies be present in one tower.

During defence operations to manage a guard tower a general has to send part of his army to that tower. Each general asks some fee from the king for managing towers. As they live in a really far away kingdom, each general evaluates his fee in the following weird manner: he finds two remotest (the most distant) towers, where the soldiers of his army are situated and asks for the fee equal to the distance. Each tower is represented by a point on the plane with coordinates $ (x,y) $ , and the distance between two points with coordinates $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ is determined in this kingdom as $ |x_{1}-x_{2}|+|y_{1}-y_{2}| $ .

The greedy king was not exactly satisfied with such a requirement from the generals, that's why he only agreed to pay one fee for two generals, equal to the maximum of two demanded fees. However, the king is still green with greed, and among all the ways to arrange towers between armies, he wants to find the cheapest one. Each tower should be occupied by soldiers of exactly one army.

He hired you for that. You should find the minimum amount of money that will be enough to pay the fees. And as the king is also very scrupulous, you should also count the number of arrangements that will cost the same amount of money. As their number can be quite large, it is enough for the king to know it as a remainder from dividing by $ 10^{9}+7 $ .

Two arrangements are distinct if the sets of towers occupied by soldiers of the first general are distinct.

## 说明/提示

In the first example there are only two towers, the distance between which is equal to 2. If we give both towers to one general, then we well have to pay 2 units of money. If each general receives a tower to manage, to fee will be equal to 0. That is the smallest possible fee. As you can easily see, we can obtain it in two ways.

## 样例 #1

### 输入

```
2
0 0
1 1
```

### 输出

```
0
2
```

## 样例 #2

### 输入

```
4
0 0
0 1
1 0
1 1
```

### 输出

```
1
4
```

## 样例 #3

### 输入

```
3
0 0
1000 1000
5000 5000
```

### 输出

```
2000
2
```

# 题解

## 作者：chihik (赞：12)

注意题目中的这句话 : 使得同组内的两座塔的曼哈顿距离的**最大值最小** , 很容易想到二分。

考虑二分一个长度$len$，显然，当两个点的曼哈顿距离大于$len$时，它们不能属于同一个集合。 

我们将这样的点对连一条边，原问题等价与判断新图是否为一个[二分图](https://www.luogu.org/blog/chihik/er-fen-tu)。

这个很好做到，我们找一个未被遍历的点$u$，并向他的子节点扩散。

如果$u$的子节点$v$未染色，就染成与点$u$相反的颜色。

不然，如果点$u$的颜色与点$v$的颜色相同，说明原图不是二分图。

重复以上操作，直到遍历完每一条边。

然后，我们发现，方案数为2的联通块数量次方。因为每个联通快的x部和y部可以交换，就有两种分法。联通块数量可以在遍历图时顺便求出。

其实此题并不难，远远不到黑题水准。

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
#define Mod 1000000007

const int MAXN = 5000;
int n , m , u , v , num , Ans;
struct node1{
	int x , y;
}Point[ MAXN + 5 ];

int Fabs( int x ) {
	return x < 0 ? -x : x;
}
int Dis( int p1 , int p2 ) {
	return Fabs( Point[ p1 ].x - Point[ p2 ].x ) + Fabs( Point[ p1 ].y - Point[ p2 ].y );
}
int Quick_pow( int x , int po ) {
	int Ans = 1;
	while( po ) {
		if( po % 2 )
			Ans = 1ll * Ans * x % Mod;
		x = 1ll * x * x % Mod;
		po /= 2;
	}
	return Ans;
}

int Color[ MAXN + 5 ];
bool dfs( int u , int len ) {
	for( int v = 1 ; v <= n ; v ++ ) { 
		if( u == v || Dis( u , v ) <= len ) continue;
		if( Color[ v ] == -1 ) {
			Color[ v ] = !Color[ u ];
			if( !dfs( v , len ) ) return 0;
		}
		else if( Color[ v ] == Color[ u ] )
			return 0;	
	}
	return 1;
}
bool check( int len ) {
	int cnt = 0; 
	memset( Color , -1 , sizeof( Color ) );
	for( int i = 1 ; i <= n ; i ++ )
		if( Color[ i ] == -1 ) {
			cnt ++;
			if( !dfs( i , len ) ) return 0;
		}
	Ans = len , num = cnt;	
	return 1;
}
int solve( ) {
	int l = 0 , r = 10000 , Mid;
	while( l <= r ) {
		Mid = ( l + r ) / 2;
		if( check( Mid ) )
			r = Mid - 1;
		else
			l = Mid + 1;
	}
	return Ans;	
}

int main( ) {
	scanf("%d",&n);
	for( int i = 1 ; i <= n ; i ++ )
		scanf("%d %d", &Point[ i ].x , &Point[ i ].y );
	printf("%d\n", solve( ) );
	printf("%d\n", Quick_pow( 2 , num ) );
	return 0;
}
```


---

## 作者：☯☯枫☯☯ (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF85E)

---

**算法分析：二分答案+二分图判定**

首先分析题目大意。很显然，按照题意将塔分为两组后，同组内没有其他联系，于是我们可以想到二分图基本模型。题设的条件就是要求我们将若干座塔构造成一个二分图。于是将题意简化如下：

> 求一张二分图，使得每组内两个点之间的曼哈顿距离的**最大值最小**，并求出符合条件的方案数。

等等，我们应该如何建图？注意到**最大值最小**，可以尝试用**二分答案**的方式求解。对答案（曼哈顿距离的最大值的最小值）进行二分，在符合距离的两点间连边，然后采用染色法判定该图是不是二分图，如果是，就记录答案，这样一轮结束后，我们就可以得到第一问的答案。

接下来我们解决第二问。如何求方案数？我们先考虑最普通的二分图，其左部点和右部点可以确定。从样例一可以知道，左部和右部可以互换，因此在这种情况下，一共有两种情况。我们再看下图，下图显然是一个可行的二分图，但是有多个连通块，对于每个连通块都有两种方案，因为连通块内部的左部点和右部点互换对其他连通块并没有影响。记连通块数量为 $k$ ，那么总方案数就有 $2^k$ 种，由于 $k$ 可能较大，用快速幂会比较方便。

---

**细节提示**

注意到 $n\le 5000$，在极限情况下时空复杂度达到$n^2$ 级别，尽管可以勉强承受，但是过于浪费，因此不必显式建图，可以在染色的同时寻找符合要求的对象。

上代码：
```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(register int i=(a);i<=(b);i++)
using namespace std;
const int N=5005,mod=1e9+7;
int n,col[N],num,ans,cnt;
struct P {
	int x,y;
} a[N];
inline int dis(P a,P b) {//曼哈顿距离 
	return abs(a.x-b.x)+abs(a.y-b.y);
}
long long fc(int x,int y) {//快速幂 
	if(!y)return 1;
	long long pos=fc(x,y>>1)%mod;
	if(y&1)return pos*pos%mod*x%mod;
	return pos*pos%mod;
}
bool dfs(int x,int mi) {
	F(i,1,n){
		if(dis(a[x],a[i])<=mi or i==x)continue;
		if(!col[i]) {
			col[i]=col[x]^1;//染色
			if(!dfs(i,mi))return false;//染色失败，不是二分图
		} else if(col[i]==col[x])return false;//同上 
	}
	return true;
}
inline bool check(int mid) {
	memset(col,0,sizeof(col));//记录颜色 
	num=0;
	F(i,1,n) {
		if(!col[i]) {
			col[i]=2;
			num++;//一次dfs出的显然是一个连通块，num记录连通块数量 
			if(!dfs(i,mid))return false;
		}
	}
	cnt=num;//cnt记录答案的连通块数量 
	return true;
}
int main() {
	scanf("%d",&n);
	F(i,1,n)scanf("%d%d",&a[i].x,&a[i].y);
	int l=0,r=1e4;
	while(l<=r) {//二分答案 
		int mid=l+r>>1;
		check(mid)?r=mid-1,ans=mid:l=mid+1;
	}
	printf("%d\n%lld\n",ans,fc(2,cnt));
	return 0;
}
```

欢迎交流讨论，请点个赞哦~

[AC记录](https://www.luogu.com.cn/record/47245083)

---

## 作者：HenryHuang (赞：4)

# 「CF85E」 Guard Towers

~~模拟赛考了这题的加强版~~

~~然后我因为初值问题直接炸飞~~

**题目大意：**

给你二维平面上的 $n$ 个整点，你需要将它们平均分成两组，使得每组内任意两点间的曼哈顿距离的最大值最小。

本题数据范围为 $n\le 5\times 10^3 $。

这种极值问题，很容易想到的是二分答案，而本题也确实可行。

二分距离的最大值 $x$，将两点距离大于 $x$ 的点对连边，则问题转化为我们构建的新图是否为二分图。

~~其实我感觉复杂度挺假的~~

----

考虑曼哈顿距离在此处处理并不方便，所以我们可以将其转化为切比雪夫距离进行求解。

（定义可以去网上康康）

即令 $(x,y)=(x+y,x-y)$，得到的新的点之间的切比雪夫距离等价于原来的点之间的曼哈顿距离。

曼哈顿距离：$|x_1-x_2|+|y_1-y_2|$

切比雪夫距离：$\max\{|x_1-x_2|,|y_1-y_2|\}$。

于是现在的问题变为：在平面内用两个相同大小的正方形覆盖所有点的最小正方形大小。

首先，平面上的所有点可以被一个最小的矩形覆盖，那么根据切比雪夫距离的定义，两个正方形的某一个顶点必定与矩形的某个顶点重合，因为这个矩形的每条边上都有点的存在。

也就是说，我们找到的两个正方形一定长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/zkq9nmt3.png)

如图所示共有两种情况需要讨论。

那么问题就非常简单了：我们枚举每个点，比较重合端点与该点的距离，以决定该点的归属。

这样我们可以在线性时间内找到两种情况的答案，比较即可。

这样我们解决了第一问，即每个正方形的大小。

如何统计方案数？

首先用两种颜色染色就有两种染色方案。

然后最后我们找到的正方形可能长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/r76jgioq.png)

红色部分的点可以被任意分配，每个点有两种情况，假设共有 $x$ 个点，就有 $2^x$ 种分配方案。

现在仍然有一个棘手的问题，如果刚才的两种情况得到的答案大小相等怎么办？

将最终答案乘二即可。

但是，仍然存在特殊情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/je7pu15g.png)

当得到的正方形是这个样子的时候，我们上面讨论的两种情况是一样的，这个时候答案不需要发生改变。

综上，我们在 $O(n)$ 的时间复杂度内解决了此问题。

（代码是考场上写的改的，真的很丑）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
const int p=1e9+7;
int x[maxn],y[maxn];
int X1=36456,X2=-4746,y3=34563,y4=-2345234;//看这个地方就知道我的心情有多复杂... 
int dist(int X1,int Y1,int X2,int Y2){
	return max(abs(X1-X2),abs(Y1-Y2));
}
int Ans=-1,Cnt,n,mx,cnt;
int ksm(int a,int b,int p){
	int ans=1;
	while(b){
		if(b&1) ans=1ll*ans*a%p;
		b>>=1,a=1ll*a*a%p;
	}
	return ans;
}
void calc(){
	mx=0,cnt=0;
	for(int i=1;i<=n;++i){
		mx=max(mx,min(dist(x[i],y[i],X1,y3),dist(x[i],y[i],X2,y4)));
	}
	for(int i=1;i<=n;++i){
		if(dist(x[i],y[i],X1,y3)<=mx&&dist(x[i],y[i],X2,y4)<=mx) ++cnt;
	}
	if(Ans==-1) Ans=mx,Cnt=cnt;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	if(n==2) cout<<"0\n2\n",exit(0);
	for(int i=1;i<=n;++i){
		int a,b;cin>>a>>b;
		x[i]=a+b;
		y[i]=a-b;
	}
	for(int i=1;i<=n;++i){
		if(x[i]<X1) X1=x[i];
		if(x[i]>X2) X2=x[i];
		if(y[i]<y3) y3=y[i];
		if(y[i]>y4) y4=y[i];
	}
	calc();
	swap(y3,y4);
	calc();
	swap(y3,y4);
	if(mx<Ans){
		cout<<mx<<'\n'<<ksm(2,1+cnt,p)<<'\n';
	}
	else if(mx==Ans){
		cnt=0;
		for(int i=1;i<=n;++i){
			if(dist(x[i],y[i],X1,y3)<=mx&&dist(x[i],y[i],X2,y4)<=mx) ++cnt;
			else if(dist(x[i],y[i],X1,y4)<=mx&&dist(x[i],y[i],X2,y3)<=mx) ++cnt;
		}
		if(X2-X1>mx&&y4-y3>mx) cout<<mx<<'\n'<<ksm(2,2+cnt,p)<<'\n';
		else cout<<mx<<'\n'<<ksm(2,1+cnt,p)<<'\n';
	}
	else cout<<Ans<<'\n'<<ksm(2,1+Cnt,p)<<'\n';
	return 0;
}
```



---

## 作者：Z1qqurat (赞：2)

最大值最小想到二分（直接二分最大的曼哈顿距离），预处理任意两点的曼哈顿距离，将其看作边权；分成两组可以想到二分图。那么 check 函数就是判断是否可以是两组内最大距离为 $mid$，其实就是让曼哈顿距离大于 $mid$ 的点对不在同一个组。可以采取建新图的方式，只建边权大于 $mid$ 的边，让这些边组成二分图。采取不建新图的方式也直接可以给边标记是否可以走。

然后方案数也好说，对于一个二分图中的连通块有 $2$ 种染色方法，这是由染的第一个点染成的是 $1$ 还是 $2$。所以如果有 $x$ 个连通块，方案数为 $2^x$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5005, P = 1e9 + 7;
int n, x[N], y[N], dis[N][N], vis[N], ans = 1;

bool dfs(int u, int col, int x) {
	vis[u] = col;
	for (int v = 1; v <= n; ++v) {
		if(dis[u][v] <= x) continue;
		if(vis[v] == col) return 0;
		if(!vis[v]) {
			if(!dfs(v, 3 - col, x)) return 0;
		}
	}
	return 1;
}

bool check(int x) {
	for (int i = 1; i <= n; ++i) vis[i] = 0;
	int qwq = 1, as = 1;
	for (int i = 1; i <= n; ++i) if(!vis[i]) qwq &= dfs(i, 1, x), as = (as << 1) % P;
	if(qwq) ans = as;
	return qwq;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &x[i], &y[i]);
		for (int j = 1; j < i; ++j) {
			dis[i][j] = dis[j][i] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
		}
	}
	int l = -1, r = N << 1 | 1;
	while(l + 1 < r) {
		int mid = l + r >> 1;
		if(check(mid)) r = mid;
		else l = mid;
	}
	printf("%d\n%d", r, ans);
	return 0;
}
```

---

## 作者：quarmer (赞：2)

题意很明确，让距离的**最大值最小**，自然想到二分答案，也就是对距离进行二分。

问题来了，怎么 check？

很简单，我们发现二分一个长度为 len 时，记点对 $(u, v)$  为曼哈顿距离大于 len 的两个点肯定不属于统一集合。那么只需要判断有没有方案让每一组 $(u, v)$ 都不在同一集合。

很显然，这就是判断二分图。

讲每一个点对 $(u, v)$ 连一条边，直接跑一遍判断二分图，就可以进行 check。

（不熟悉二分图的先进[这里](https://www.luogu.com.cn/blog/xht37/er-fen-tu-yu-wang-lao-liu)学习。


至于方案数，因为此图为二分图，在每个连通块中左部可以和右部互换，所以每个连通块可以有两种方案。根据乘法原理，共有 $2^k$ 种方案，其中 $k$ 为连通块个数，这个个数可以在 check 里顺便求出来。

最后，因为方案数要取模，所以要手算幂，我这里用的是快速幂。而且一定要记得开 long long, $1e8 \times 1e8$ 会爆 int 。

代码：

```cpp

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <ctime>
#define ll long long
#define mr make_pair
#define ff first
#define ss second
using namespace std ;
const int mod = 1e9 + 7 ;
int n ;
struct node {
	int x, y ;
} d[5005] ;
int mypow(int x, int p) {
	ll bace = x, ans = 1 ;
	while(p) {
		if(p & 1) ans *= bace ;
		bace *= bace ;
		p >>= 1 ;
		ans %= mod, bace %= mod ;
	}
	return ans ;
}
int dis(node x, node y) {
	return abs(x.x - y.x) + abs(y.y - x.y) ;
}
int c[5005] ;
int cnt, ans ;
int mid ;
bool dfs(int x, int cl) {
	c[x] = cl ;
	for(int i = 1 ; i <= n ; i++) {
		if(i == x) continue ;
		if(dis(d[x], d[i]) <= mid) continue ;
		if(c[i] == -1) {
			if(!dfs(i, !cl)) return 0 ;
		}
		else if(c[i] == c[x]) return 0 ;
	}
	return 1 ;
}
bool check(int x) {
	memset(c, -1, sizeof(c)) ;
	cnt = 0 ;
	for(int i = 1 ; i <= n ; i++) {
		if(c[i] == -1) {
			cnt++ ;
			if(!dfs(i, 1)) return 0 ;
		}
	}
	ans = cnt ; 
	return 1 ;
}
signed main() {
	cin >> n ;
	for(int i = 1 ; i <= n ; i++) cin >> d[i].x >> d[i].y ;
	int l = 0 , r = 1e4, aans ;
	while(l <= r) {
		mid = l + r >> 1 ;
		if(check(mid))r = mid - 1, aans = mid ;
		else l = mid + 1 ;
	}
	cout << aans << endl ;
	cout << mypow(2, ans) ;
}

---

## 作者：Durancer (赞：1)

#### 题目描述

- 在一个平面内，给定$n$个点，将所有的点平均分配到两个集合中，求出在同一个集合内的曼哈顿距离的最大值的最小值（作为价格）同时求出符合条件的方案数量。

#### 讲前芝士（加餐加餐）

- 曼哈顿距离（图中的红线表示的就是曼哈顿距离）
![](https://cdn.luogu.com.cn/upload/image_hosting/74zgw97p.png)


- ~~染色原理（我不会，貌似就是一个打标记的过程）~~

#### 思路分析（CF的题确实很妙OVO）

- 首先，当看到最大值的最小值求法肯定是要用二分答案。

- 这个题目是要求分成两个相等的集合，那么我们可以有这么一种思路，将不同的集合标上不同的记号用以区别，然后在搜索的过程中不断搜索判断是否符合条件即可。

- 再看第二个询问，我们可以以每个集合内的最长曼哈顿距离来形成一个矩形，那么就会在图中形成两个矩形区间，那么这其中如果有一定的交集，那么我们假设交集内的元素个数为$x$,那么在交集内的元素就可以自由的进行组合，并且对答案不会有影响（因为答案已经是最优的了），那么得到的组合数就是$2^x$个

- 由此得出答案

#### 实现简述

- 首先用二分答案开始找最优解

- 在检查答案符合的过程中，每次遇到一个没有染过色的点就进行搜索，就记录方案数的幂指数，并且把所有与其相联系的都找一遍OVO.

- 利用曼哈顿原理判断是否符合条件即可
#### AC代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#define int long long
using namespace std;
const int N=5e3+9;
const int p=1e9+7;
struct node{
	int x;
	int y;
}tower[N];
int money;//最小花费 
int num,color[N];//染色大法好! 
int n;
int quick(int x,int k)//'快速'蜜 
{
	int res=1;
	while(k)
	{
		if(k&1) res=res*x%p;
		x=x*x%p;
		k>>=1;
	}
	return res;
} 
int Manhattan(int x,int y)
{
	return abs(tower[x].x-tower[y].x)+abs(tower[x].y-tower[y].y);
	//曼哈顿距离实则就是两个点之间用于求勾股定理的两条直角边的长度 
}
int search(int x,int len)
{
	for(int i=1;i<=n;i++)
	{
		if(i==x||Manhattan(i,x)<=len) continue;
		//如果，枚举到重复的或者他们的曼哈顿距离满足当前枚举的长度
		if(color[i]==-1)
		{
			color[i]=!color[x];//如果不符合上述要求，那么就一定不是在一起的
			if(!search(i,len)) return 0;		
		}
		else if(color[x]==color[i])//不在范围之中并且不符合要求，那么久不对
		return 0;	 
	}
	return 1;
} 
int check(int len)
{
	memset(color,-1,sizeof(color));//新的一轮查找，更新 
	int count=0;//计数，求答案
	for(int i=1;i<=n;i++)
		if(color[i]==-1)//说明他还没有找，那么搜索去找他
		{
			count++;//找到一种情况 
			if(!search(i,len))
			return 0;//如果搜索中不合法 
		}
	num=count;	
	return 1;//合法就输出1 
} 
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>tower[i].x>>tower[i].y;
	int l=0,r=10000;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			r=mid-1;
			money=mid;//更新最小答案 
		} 
		else l=mid+1; 
	}
	cout<<money<<endl;
	cout<<quick(2,num)<<endl;	
} 
```


---

## 作者：信息学carryHarry (赞：0)


### 思路：
- 看到最大值最小，我们想到了二分；
- 看到塔要分成两组，自然想到了二分图。

### 怎样解决两问？
#### 第一问
- 二分最大曼哈顿距离 $mid$。
- 两两枚举顶点 $x$ 和 $y$，若 $x$ 和 $y$ 的曼哈顿距离大于 $mid$，则连边。
- 跑二分图染色，若存在二分图，返回真，右边界 $=mid$，否则返回假，左边界 $=mid$。

注意：每次二分边的颜色要清零。
####  第二问
- 对于第一问的二分图，求连通块的数量 $tot$，答案为 $2^{tot}$。

注意：答案要模 $10^9+7$。

### code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005,mod=1e9+7;
int n,color[N],dis[N][N],x[N],y[N];
vector<int>nbr[N];
bool vis[N];
long long fast(int a,int b)
{
	int ans=1,res=a;
	while(b){
		if(b&1)
			ans=ans*res%mod;
		res=res*res%mod;
		b>>=1;
	}
	return ans%mod;
}
bool dfs(int x,int c)
{
	color[x]=c;
	for(int i=0;i<nbr[x].size();i++){
		int cur=nbr[x][i];
		if(color[cur]==c)
			return 0;
		if(color[cur]==0){
			if(dfs(cur,3-c)==0)
				return 0;
		}
	}
	return 1;
}
bool check(int x)
{
	for(int i=1;i<=n;i++){
		nbr[i].clear();
		color[i]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(dis[i][j]>x){
				nbr[i].push_back(j);
				nbr[j].push_back(i);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!color[i]&&dfs(i,1)==0)
			return 0;
	}
	return 1;
}
void find(int x)
{
	vis[x]=1;
	for(int i=0;i<nbr[x].size();i++){
		int cur=nbr[x][i];
		if(!vis[cur]){
			find(cur);
		}
	}
	return ;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			dis[i][j]=abs(x[i]-x[j])+abs(y[i]-y[j]);
		}
	}
	int lt=-1,rt=1e4+1;
	while(lt+1<rt){
		int mid=(lt+rt)>>1;
		if(check(mid))
			rt=mid;
		else
			lt=mid;
	}
	cout<<rt<<'\n';
	check(rt);
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(vis[i]==0){
			cnt++;
			find(i);
			
		}
	}
	cout<<fast(2,cnt);
	return 0;
}

```


---

## 作者：cancan123456 (赞：0)

找到一到比较水的黑题。

更好的题面：

在直角坐标系上有 $n$ 座塔。

要求把这些塔分成两组，使得同组内的两座塔的曼哈顿距离的最大值最小，并求出在此前提下求出有多少种分组方案，对 $10^9+7$ 取模。

$n\le5000$。

看到最大值最小，想到二分答案，假设我们二分了一个答案 $x$，考虑如何判定。

将所有距离小于等于 $x$ 的点连边不行，那么我们将所有距离大于 $x$ 的点连边，显然这些点不能同时处于一组，即这张图必须是二分图。

判断二分图用染色法即可。那么我们就找到了第一问的答案。

发现在最后建出的这张图上（也就是 $x$ 等于第一问的答案）不同连通块之间互不干扰，每个连通块又有 $2$ 种方案（把两组的塔互换即可），假设最后有 $k$ 个连通块，那么答案就是 $2^k$。

时间复杂度 $O(n^2\log W)$，其中 $W=2\times5000=10000$ 为两个塔的最大距离。~~在 CF 神机的加持下稳过。~~

---

## 作者：Forever1507 (赞：0)

第一道黑题题解！！1

先读题，看到 曼哈顿距离的**最大值最小** 基本锁定二分， 那么接下来问题就是怎样写出 `check` 函数以求出正确答案。

因为题目要求把塔分为两组，所以接下来我联想到了二分图这种好东西，综合一下，第一问的解法就是说我二分出一个 `mid` 并使曼哈顿距离大于 `mid` 的两座塔建边，跑一遍二分图判定，如果成功了，`mid` 可以满足，则调整右边界，反之调整左边界，最后二分出来的答案就是第一问的答案。

那么第二问如何解决呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/dpvjz7e4.png)

上图是一个正常的二分图（红线分割两边），我们知道，二分图的划分方式并不是唯一的，对于上图中的连通块（即蓝色圈圈部分），将其左右互换是 **不影响** 二分图的，所以，每一个连通块会形成两种放置方法，上图有两个连通块，所以有 $2 \times 2 = 4$ 种情况。

同样的，对于一张任意的二分图，假设其有 $x$ 个连通块，则情况有 $2^x$ 种，可以考虑快速幂。

找连通块怎么实现呢？并查集。把边全部连起来后但凡一个塔的父亲节点是自己，一个连通块就诞生的。

代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define k 1000000007
using namespace std;
int color[5005];
short u[12500005],v[12500005],w[12500005];
int n,m,x[5005],y[5005],cnt,fa[5005],ans;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int find(register int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
inline void unionn(register int x,register int y){
	int i=find(x),j=find(y);
	if(i!=j){
		fa[i]=j;
	}
}
struct node{
	int v,w;
};
vector<node>nbr[5005];
bool dfs(register int cur,register int c){//染色法判定二分图
	color[cur]=c;
	for(register int i=0;i<nbr[cur].size();++i){
		int nxt=nbr[cur][i].v;
		if(color[nxt]==3-c)continue;
		else if(color[nxt]==c)return 0;
		else if(color[nxt]==0){
			if(dfs(nxt,3-c)==0)return 0;
		}
	}
	return 1;
}
inline void add(register int u,register int v,register int w){
	nbr[u].push_back((node){v,w});
}
inline ll FastPow(register ll a,register ll b){
	ll base=a;
	ll ans=1;
	while(b){
		if(b&1)ans=ans*base%k;
		base=(base%k)*(base%k)%k;
		b>>=1;
	}
	return ans;
}
inline bool doo(register int x){
	ans=0;
	for(register int i=1;i<=n;++i)fa[i]=i;
	for(register int i=1;i<=cnt;++i){
		if(w[i]>x){
			unionn(u[i],v[i]);
		}
	}
	for(register int i=1;i<=n;++i){
		if(fa[i]==i)ans++;
	}
	return 1;
}
inline bool check(register int x){
	memset(color,0,sizeof(color));
	for(register int i=1;i<=n;++i)nbr[i].clear();
	for(register int i=1;i<=cnt;++i){
		if(w[i]>x){
			add(u[i],v[i],w[i]);
			add(v[i],u[i],w[i]);
		}
	}
	for(register int i=1;i<=n;++i){
		if(color[i])continue;	
		if(dfs(i,1)==0){只要有一个答案可以就行了
			return 0;
		}
	}
	return 1;
}
inline int binary_search(){
	int lt=-1,rt=1e4+1;
	while(lt+1<rt){
		int mid=lt+rt>>1;
		if(check(mid))rt=mid;
		else lt=mid;
	}
	doo(rt);
	return rt;
}
inline int Distance(register int i,register int j){
	return abs(x[i]-x[j])+abs(y[i]-y[j]);
}
signed main(){
	n=read();
	for(register int i=1;i<=n;++i){
		x[i]=read();
		y[i]=read();//常数较大，卡了好几次才过
		fa[i]=i;//初始化并查集
	}
	for(register int i=1;i<=n;++i){
		for(register int j=i+1;j<=n;++j){
			u[++cnt]=i;
			v[cnt]=j;//边要存起来，不然没法加边删边
			w[cnt]=Distance(i,j);//距离是曼哈顿！
		}
	}
	cout<<binary_search()<<'\n';
	cout<<FastPow(2,ans);
}
```


---

