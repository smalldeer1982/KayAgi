# [USACO22FEB] Moo Network G

## 题目描述

农夫约翰有 $N$ 头牛（$1\le N\le10^5$） 它们在农场里分布的极其的远，因此希望你建立一个通讯网络，便于它们更容易地交换电子短信（当然，这些短信都包含 `moo` 的变形体，即数字）

第 $i$ 头牛位于位置 $(x_i，y_i)$ 其中 $0\le x\le 10^6$, $0\le y\le 10$. 在牛 $i$ 与牛 $j$ 之间建立通信链路的成本是它们之间的欧几里德距离的平方，即 $(x_i-x_j)^2+(y_i-y_j)^2$


请聪明的你构建一个所有奶牛都能交流的最低成本的通信网络。如果两头奶牛通过一条链接直接连接或者它们的信息可以沿着一条链接传播，那么认为他们可以通信。

#### 注意 此问题时间限制为4秒

## 说明/提示

测试点 2~3 满足 $N\le1000$。

测试点 4~15 没有特殊限制。

## 样例 #1

### 输入

```
10
83 10
77 2
93 4
86 6
49 1
62 7
90 3
63 4
40 10
72 0```

### 输出

```
660```

# 题解

## 作者：_sunkuangzheng_ (赞：31)

**【题目分析】**

我们充分发扬人类智慧：

因为 $y$ 值很小，所以对距离的影响也很小。

直接按照 $x$ 坐标排序，$x$ 坐标相同按 $y$ 排，每个点连它前面的 $25$ 个点跑 Kruskal。

这样速度快的飞起，最慢的点只跑了不到 $500\text{ms}$。

---

## 作者：Usada_Pekora (赞：8)

题意：给定平面上 $N$ 个点，第 $i$ 个点的坐标为 $(x_i,y_i)$ ，点 $i,j$ 相连需要花费 $(x_i - x_j) ^2 + (y_i -y_j) ^2$ 的费用，求使所有点可以相互到达的最小费用。

做法：一眼看出这是一个平面上的最小生成树，  $N\leq 1000$ 的分很好想：直接暴力连边， 然后跑 MST ，复杂度 $O(N^2)$ 。

众所周知，在 Kruskal 算法中，如果存在三个点 $a,b,c$ ， 且连通费用 $w(a,c) < w(a,b), w(b,c) < w(a,b)$ ， 那么 $w(a,b)$ 就是没用的一条边，因为 $a,b$ 在按边权选的过程中已经连通了。

那么对于 $a=(x_1, y_1),b=(x_2,y_2),c=(x_3,y_3)$ ，满足 $x_1 \leq x_2 < x_3, y_2 = y_3$ 。存在：

$w(a,b)=(x_2 -x_1)^2 + (y_2 - y_1) ^2 $ 。

$w(b,c) = (x_3 - x_2)^2$ 。

$w(a,c) = (x_3-x_1)^2+(y_2-y_1)^2$ 。

则 $w(a,b) < w(a,c),w(b,c)<w(a,c)$ , 不考虑添加 $w(a,c)$ 。

所以对于 $(x_1,y_1)$ ，只需要对横坐标大于等于它的一个 $(x_2, y_2)$ 连边就好了，注意两个点不能重合。

因为 $0\leq y_i\leq 10$ ，直接枚举纵坐标，然后用平衡树存点 ，复杂度是 $O(N\log_2 N)$ 。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 int128;
typedef __uint128_t uint128;
const int mod = 1e9 + 7, N = 1e5 + 5;
using namespace std;
inline int read() {
	int x = 0, f = 0, ch = getchar();
	while(ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
	while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
int fa[N], n, cnt, x[N], y[N];
inline int getfa(int x) {
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}
struct edge {
	int u, v;
	ll w;
	edge(int _u = 0, int _v = 0, ll _w = 0ll) : u(_u), v(_v), w(_w) {}
	bool operator < (const edge &x) const {
		return w < x.w;
	}
} e[N * 11];
map<int, int> s[11];
signed main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		x[i] = read(), y[i] = read();
		s[y[i]].insert(make_pair(x[i], i));
	}
	for(int i = 1; i <= n; i++) 
		for(int j = 0; j <= 10; j++) {
			map<int, int>::iterator it;
			if(y[i] == j) it = s[j].upper_bound(x[i]);
			else it = s[j].lower_bound(x[i]);
			if(it != s[j].end()) {
				ll dx = x[i] - it->first, dy = y[i] - j;
				e[++cnt] = edge(i, it->second, dx * dx + dy * dy);
			}
		}
	sort(e + 1, e + cnt + 1);
	for(int i = 1; i <= n; i++) fa[i] = i;
	ll ans = 0ll;
	for(int i = 1, tot = 0; i <= cnt; i++) {
		int fu = getfa(e[i].u), fv = getfa(e[i].v);
		if(fu != fv) {
			fa[fu] = fv;
			ans += e[i].w;
			tot++;
		} if(tot == n - 1) break;
	}
	cout << ans;
	return 0;
}

```

---

## 作者：Moonlight_dreams (赞：6)

## [题目](https://www.luogu.com.cn/problem/P8191)

这道题就是一道最小生成树的题，但会难一点。

#### [不会最小生成树的看这里~~](https://www.luogu.com.cn/article/1bi79797)

### 思路

- **实现思路**

我们可以借助 Kruskal 算法来写。

这道题其实 kruskal 函数很好写，就是在存图的时候有点麻烦，因为 $1≤N≤10^5$，这个范围太大了，如果直接双重循环建图的话，肯定会超时。但我们也知道，$0≤y≤10$，$y$ 特别小，我们就可以利用这一点来写。

- **代码思路**

Kruskal 函数的模板不用改，直接照搬。

我们加一个 init 函数，用来存图。

函数中我们先按 $x$ 坐标从小到大来排序，然后我们枚举，每个点大概往后枚举二十五个点就好了。

最后再根据平面距离公式来求出边权就好了。

## AC 代码如下（含注释）

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5 , M = 5e6 + 5;
struct stu
{
	int x , y , val;
}s[M];
struct node
{
	int x , y;
}a[N];
int fa[N];
int get(int x)
{
	if (x == fa[x])
	{
		return x;
	}
	return fa[x] = get(fa[x]);
}
void unite(int x , int y)
{
	x = get(x);
	y = get(y);
	if (x != y)
	{
		fa[x] = y;
	}
	return ;
}
bool cmp1(stu a , stu b)
{
	return a.val < b.val;
}
bool cmp2(node a , node b)
{
	if (a.x != b.x)
	{
		return a.x < b.x;
	}
	return a.y < b.y;
}
int n , m;
void kruskal() // 直接套模板，详细注释去看我滴专栏就OK了
{
	for (int i = 1; i <= n; i++)
	{
		fa[i] = i;
	}
	sort (s + 1 , s + m + 1 , cmp1);
	int cnt = 0 , ans = 0;
	for (int i = 1; i <= m; i++)
	{
		int x = get(s[i].x) , y = get(s[i].y);
		if (x == y)
		{
			continue;
		}
		unite(x , y);
		cnt++;
		ans += s[i].val;
		if (cnt == n - 1)
		{
			cout << ans;
			return ;
		}
	}
}
void init()
{
	for (int i = 1; i <= n - 1; i++) // 枚举所有边
	{
		for (int j = i; j <= i + 25; j++) // 大概往后枚举这么多就够了
		{
			m++;
			s[m].x = i;
			s[m].y = j;
			s[m].val = (a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y); //平面距离公式
		}
	}
	return ;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].x >> a[i].y;
	}
	sort (a + 1 , a + n + 1 , cmp2); // 按照 x 坐标从小到大排序
	init();
	kruskal();
	return 0;
}
```

---

## 作者：xiaozeyu (赞：6)

[P8191 [USACO22FEB] Moo Network G](https://www.luogu.com.cn/problem/P8191)

暴力建边再 kruskal。

这道题不用相办法证明太多东西。

因为高度不超过 10，一看就是通过高度来简化操作。

我们知道都连最短边差不多就是最优，在这里就可以可以通过暴力向一个方向都连边。

按照横坐标再纵坐标排个序，去个重，就很好做了。

因为要向四周取最短，向正方向取个 25 个点差不多能保证正确性。

时间完全够用。

---


```cpp

#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define f(a) ((a)*(a))
#define p(x) printf("%lld ",(x))
#define fp(x) printf("%.10Lf ",(x))
#define P() puts("")
#define lowbit(x) ((x)&(-(x)))
using namespace std;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
inline char cread()
{
	char c=getchar();
	while(!isalpha(c)) c=getchar();
	return c;
}
inline void write(int re)
{
	if (re>9) write(re/10);
	putchar(re%10+'0');
}
const int maxn=100010;
struct pnt 
{
	int x,y;
}a[maxn];
struct edge
{
	int u,v,w;
}e[maxn*30];
int n,f[maxn],tot,cnt,ans;
inline bool cmp(pnt a,pnt b)
{
	if(a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}
inline bool cmp2(edge a,edge b)
{
	return a.w<b.w;
}
inline int getf(int x)
{
	if(f[x]==x) return x;
	return f[x]=getf(f[x]);
}
signed main()
{
	n=read();
	For(i,1,n)
	{
		a[i].x=read();a[i].y=read();
	}
	sort(a+1,a+n+1,cmp);
	For(i,1,n)
		For(j,i+1,min(n,i+25))
		{
			e[++cnt].u=i;
			e[cnt].v=j;
			e[cnt].w=f(a[i].x-a[j].x)+f(a[i].y-a[j].y);
		}//	add(i,j,f(a[i].x-a[j].x)+f(a[i].y-a[j].y));
	sort(e+1,e+cnt+1,cmp2);
	For(i,1,n) f[i]=i;
	int u,v,U,V;
	For(i,1,cnt)
	{
		u=e[i].u;v=e[i].v;
		U=getf(u);V=getf(v);
		if(U!=V)
		{
			ans+=e[i].w;
			f[V]=U;
			tot++;
		}
		if(tot>=n-1) break;
	}
	p(ans);
}

```

感谢管理员的审核。


---

## 作者：xkcdjerry (赞：6)

USACO 比赛上拿满分的唯一一道题，写一个题解纪念一下：

看到使用最小的代价让所有点互通考虑最小生成树，但是由于 $n \leqslant 10^5$ 的数据范围不能两两连边，考虑减少边的数量：

猜测：对于所有点向每个 $y$ 与左侧和右侧最接近的点连边等效于向所有点连边。

证明（此处为了简明使用 Kruskal 进行论证，Prim 的论证留作练习）：


（此处只证明为向左连边的情况，向右连边的情况同理可证）考虑这么连什么情况下不会产生最优解：

对于点 $i,j,k$（其中 $y_i=y_j$，$x_i < x_j \leqslant x_k$），假如连接边 $(i,k)$ 那么就意味着此连法不一定产生最优解。

为了达成这个，需要满足 $(i,k)$ 的长度小于 $(i,j)$ 或 $(j,k)$。因为如果 $i,k$  按长度排序后同时后于 $(i,j)$ 和 $(j,k)$ ，则当 Kruskal 遍历到边 $i,k$ 由于 $i,j,k$ 一定在一个连通块内，故边 $(i,k)$ 一定不会被选。

而 $(i,k)$ 的长度为 $(x_k-x_i)^2+(y_k-y_i)^2$，$(i,j)$ 长度为 $(x_j-x_i)^2$，$(j,k)$ 的长度为 $(x_k-x_j)^2+(y_k-y_j)^2$。

又因为 $(y_k-y_i)^2 \geqslant 0$，$(x_k-x_i)^2 > (x_j-x_i)^2$，所以 $(i,j)$ 的长度小于 $(i,k)$ 的长度。

类似的，$(y_k-y_j)^2=(y_k-y_i)^2$，$(x_k-x_j)^2 < (x_k-x_i)^2$，所以 $(j,k)$ 的长度小于 $(i,k)$ 的长度。

综上，$(i,j)$ 与 $(j,k)$ 均先于 $(i,k)$ 被考虑，即 $(i,k)$ 永远不会被选中，故此贪心正确。

而且由于所有最小生成树算法等效，理论上 Prim 也可以被用来解决该题。（未实践）

蒟蒻的代码如下：

```c++
#include <cstdio>
#include <algorithm>
#define N 100010
#define ll long long
int n,m,fa[N],f[11];
ll ans;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x, int y,ll w)
{
    if(find(x)!=find(y)) 
    {
        fa[find(x)]=find(y);
        ans+=w;
    }
}
struct edge
{
	int from,to; ll w;
	bool operator<(edge b) const {return w<b.w;}
}e[N*50];

void kruskal()
{
	for(int i=1;i<=n;i++) fa[i]=i;
	std::sort(e,e+m);
	for(int i=0;i<m;i++) merge(e[i].from,e[i].to,e[i].w);
}

struct oo{int x;int y;bool operator<(oo b)const{return x<b.x;}}a[N];
#define sq(x) (ll)(x)*(x)
inline ll calc(int x, int y) {return sq(a[x].x-a[y].x)+sq(a[x].y-a[y].y);}
void run(int x)
{
	for(int j=0;j<=10;j++) if(f[j])
		e[m++]=edge{f[j],x,calc(x,f[j])};
	f[a[x].y]=x;
}
int main()
{
	scanf("%d", &n);
	for(int i=1;i<=n;i++) scanf("%d%d", &a[i].x, &a[i].y);
	std::sort(a+1,a+1+n);
	f[a[1].y]=1;
	for(int i=2;i<=n;i++) run(i);
	
	for(int i=0;i<=10;i++) f[i]=0;
	f[a[n].y]=n;
	for(int i=n-1;i>=1;i--) run(i);
	kruskal();
	printf("%lld",ans);
}
```
[AC 记录](https://www.luogu.com.cn/record/70722739)（话说这题开 O2 和[不开](https://www.luogu.com.cn/record/70722817)区别好大呀 qwq）

---

## 作者：duanjingxiao (赞：5)

## 题目传送门:[P8191 [USACO22FEB] Moo Network G](https://www.luogu.com.cn/problem/P8191)

## 题目大意:
> 一共有 $n$ 头牛，给你它的位置，$x_i$ 和 $y_i$。两头牛的交流成本是欧几里得距离的平方。求，最低的成本。

## 分析：
> 首先，看到“最低成本”这几个字，立马反应，这是一道题的考点是最小生成树。
>
> 这里应该有两个排序，一个是把坐标从小到大排序，另一个是把距离从小到大排序。
>
> 这里还需要存个图，$v$ 代表的是两者间的距离。
## 思路：
> 用 Kruskal，因为这个好写一点。
>
> 然后，它的权值是距离，距离计算用一个 $dist$ 函数计算就好啦。
>
> 用一个 struct 类型的数组```g[]```存图，```g[].x```和```g[].y```存位置，```g[].v```存距离。用一个 $m$ 存边。到时候排序的时候不是```g+n+1```，而是```g+m+1```。
>
> 向左找 30 个点连边不会错。因为 $y\le10$ ，所以最小生成树的边，都在这里面建的边当中。
## 注意：
> 题目说是欧几里德距离的平方，前面就不需要写 ```sqrt``` 了。也不用 ```double``` 了。
> 
> 然后要开 ```long long``` ，不然只有 $10$ 分。
>
> 最优的话是连 $n-1$ 条边。
## 最后代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5,M=4e6+5;
#define int long long
int n,m;
int fa[N];
int cnt,ans;
struct node
{
	int x,y,v;
}g[M];//它存的是图,所以范围要大一些
struct Node
{
	int x,y;
}a[N];
int find(int x)//这里是找自己的根节点
{
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}
void un(int x,int y)//这里是合并
{
	x=find(x),y=find(y);
	if(x!=y)
		fa[x]=y;
	return ;
}
bool cmp(node q,node p)//将距离从小到大排序
{
	return q.v<p.v;
}
bool Cmp(Node q,Node p)//将位置从小到大排序
{
	if(q.x!=p.x)
		return q.x<p.x;
	return q.y<p.y;
}
void k()//kruskal啦,只是太长不想打那么多而已
{
	for(int i=1;i<=n;i++)//初始化,一开始每个人的根节点都是自己
		fa[i]=i;
	sort(g+1,g+m+1,cmp);//距离排序
	cnt=ans=0;//保险起见,初始值为0
	for(int i=1;i<=m;i++)//注意!这里不是n
	{
		if(find(g[i].x)!=find(g[i].y))//看它们有没有合并过
		{
			un(g[i].x,g[i].y);//合并
			ans+=g[i].v;//加上距离,也就是成本
			cnt++;//代表连的边+1
		}
		if(cnt==n-1)//一般是只有n-1条边( 最优),不过不写也没关系
			return ;
	}
	return ;
}
double dist(int x1,int y1,int x2,int y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);//这里是欧几里得算法距离的平方,也就是成本
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;//输入位置
	sort(a+1,a+n+1,Cmp);//将位置从小到大排序
	for(int i=1;i<=n-1;i++)
	{
		for(int j=i;j<=i+30;j++)//这里是为了保险,加了30意思是连它前30个点
		{
			m++;//这里4行是存图
			g[m].x=i;
			g[m].y=j;
			g[m].v=dist(a[i].x,a[i].y,a[j].x,a[j].y);
		}
	}
	k();//调用函数
	cout<<ans;//也可以在k函数里面输出
	return 0;
}
```

---

## 作者：_Imaginary_ (赞：5)

暴力出奇迹

## Problem

给定平面上一堆点，任两个点距离为横纵坐标之差的平方和，求这一些点的最小生成树。

特殊条件：任何一个点 x 坐标最大值为 $10^6$，y 坐标最大值为 $10$，且两者都是自然数。

## Solution 1

$N\le 1000.$

两两连边，跑最小生成树即可。

## Solution 2

我们有一个很重要的事情：y 坐标最大只有 $10$。

那么我们可以显然证明这个：

对于点 A，我们找到两个 x 坐标比 A 大的点 B 和 C，并且 C 的 x 坐标比 B 的大超过 $10$，则显然 B 离 A 更近。

所以，我们先按照 x 坐标排一遍序。

接下来，就可以发现最小生成树上的边连接的两个点对应的数组下标不会太远。（实际距离也不会太远）

所以，我们就让每个点和与它排完序后坐标差不超过 50 的点连边，其它的不连。（这个数字是怎么出来的，我其实也不知道）

**update: 50 是结合时间和空间考虑出来的。**

然后 Kruscal 就没了。

接下来，就能惊人地发现，你 A 了这题！

![](https://cdn.luogu.com.cn/upload/image_hosting/vd6dwxog.png)

时间的话，一秒以内能跑完吧。自己也没想出来怎么 hack。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=100005;
struct node{
	ll x,y;
	bool operator <(const node& p) const{return x<p.x;}
}a[N];
int n;
struct edge{
	int u,v;
	ll w;
	bool operator <(const edge& p) const{return w<p.w;}
	void init(int uu,int vv,ll ww){u=uu,v=vv,w=ww;};
}E[N*50];
int m=0;
ll dis(int p,int q)
{
	return (a[p].x-a[q].x)*(a[p].x-a[q].x)+(a[p].y-a[q].y)*(a[p].y-a[q].y);
}
int f[N];
int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].x,&a[i].y);
	sort(a+1,a+n+1);
	int now;
	for(int i=1;i<n;i++)
	{
		now=i+1;
		for(int j=1;j<=50;j++)
		{
			E[++m].init(i,now,dis(i,now));
			now++;
			if(now>n) break;
		}
	}
	for(int i=1;i<=n;i++) f[i]=i;
	sort(E+1,E+m+1);
	ll ans=0,tot=n;
	for(int i=1;i<=m;i++)
	{
		int u=E[i].u,v=E[i].v;
		ll w=E[i].w;
		if(find(u)==find(v)) continue;
		f[find(u)]=find(v);
		ans+=w;
		if(!(--tot)) break;
	}
	printf("%lld",ans);
	return 0;
}

```

完结撒花

---

## 作者：kardsOI (赞：4)

## 【题意】

给定平面内 $N$ 个点，其中点 $c_i$ 的坐标为 $(x_i,y_i)$，连接点 $i$ 和 $j$ 所需代价为 $(x_i-x_j)^2+(y_i-y_j)^2$，求将所有点连通所需的最小代价。

## 【分析】
（[需要先学会的最小生成树算法](https://www.luogu.com.cn/problem/P3366)）

有点经验的都可以一眼最小生成树，先将每个点坐标两两枚举加入待选边集合再跑 Kruscal，还不简单？

**且慢！数据范围！**

数据范围：$1 \le N \le 10^5$，$10^5$ 个左右点会有 $5\times 10^9$ 条左右的边，拿什么存边？拿数组存的话编译都过不了！

### 【优化】
我们看向 $y_i$ 的范围，$0 \le y_i \le 10$，又看见 $0 \le x_i \le 10^6$，突破口找到了！

由于 $y_i$ 范围那么小，所以整张图 _就是一条_ ，$y_i$ 对于是否建边的影响相对于 $x_i$ 而言很小。那么我们就可以知道横坐标距离太远的两个点中间如果有太多其他点，那它们肯定不可能直接相连！所以只用判断每个点是否连接它附近的几个点即可。

优化后算法：输入所有点后先按照 $x_i$ 从小到大排个序，然后对于点 $c_i$，取它前面最多 $30$ 个左右的点（即为 $c_i$ 附近的点，此处本人为了保险而取了最多 $40$ 个点），进行建边加入待选边集合，然后再跑 Kruscal，大功告成！
## 【满分代码】

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,fa[100010],m,un,an,bn;
long long total,kn;
struct point
{
	long long xm,ym;
}pn[200010];
struct side
{
    int a1,a2;
    long long d;
}a[8000010];
bool cmpp(point ax,point bx)
{
    return ax.xm<bx.xm;
}
bool cmps(side ax,side bx)
{
	return ax.d<bx.d;
}
int find(int a)
{
    while(a!=fa[a]) a=fa[a]=fa[fa[a]];
    return a;
}
int main()
{
//	freopen("5.in","r",stdin);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&pn[i].xm,&pn[i].ym);
        fa[i]=i;
    }
    sort(pn+1,pn+n+1,cmpp);
	for(int i=1;i<=n;i++)
	{
		for(int j=max(1,i-40);j<i;j++)
		{
			a[++kn].a1=i;
			a[kn].a2=j;
			a[kn].d=((pn[i].xm-pn[j].xm)*(pn[i].xm-pn[j].xm)+(pn[i].ym-pn[j].ym)*(pn[i].ym-pn[j].ym));
		}
	}
	sort(a+1,a+1+kn,cmps);
    for(int i=1;i<=kn;i++)
    {
        an=find(a[i].a1);
        bn=find(a[i].a2);
        if(an!=bn)
        {
            un++;
            total+=a[i].d;
            if(un==n-1) break;
            fa[an]=bn;
        }
    }
    printf("%lld",total);
    return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/drcj33pd.png)
萌新第一篇题解，有讲的不到位之处，请各位大佬指正。

---

## 作者：DUC27 (赞：1)

## 题意

如题，给定 $n$ 个点 $(x_i, y_i)$，进行连线，点 $i$ 和点 $j$ 的连线代价为 $(x_i - x_j)^2 + (y_i - y_j)^2 $ 求形成最小生成树的最小代价。

## 题解

已经给定了 $n$ 个点，选出需要可能会构成最小生成树的边，进行 kruskal 算法操作，即每次找出最小边权的边进行并查集操作。


好的，接下来我们考虑这样一个结构，以 $x$ 为区分，其中添加 $y$ 值为元素的结构体。

![1.png](https://s2.loli.net/2024/04/07/v176S2epAmuDPny.png)


然后再两个这样的之间进行添加边的操作时，就可以按照下图进行遍历。

![_20240407132513.png](https://s2.loli.net/2024/04/07/kLdAgbIczh12oV8.png)

不要忘记了自身之中的任意两个节点也可以形成边。
![2.png](https://s2.loli.net/2024/04/07/i6KFZ5RjDQqVGMW.png)


接下来，如果令当前节点为 $x_1$ 那么对于所有的 $x \le x_1 + 50$（有序情况下）都是有可能成为构成生成树的边之一。


这个 $50$ 的选取原因是，当两个 $x$ 的差值超过 $50$ 时，这两个点的权值必然大于差值小于 $50$ 的边的权值，所以不可能是生成树的构成边。

每次添加完 $50$ 范围内的边时，都要强制向后添加一个 $x$ 的点，防止在 $50$ 的范围内没有找到边，导致不能向后传。


把所有有可能的边全部丢进小根堆，进行 Kruskal 的操作。

最后附上完整代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<ll,ll>;
namespace DUC {
    struct col{
        ll y;
        ll num;
    };
    struct node{
        ll w;
        ll x;
        ll y;
        bool operator < (const node & b) const {return w > b.w;}
    };
    void solve(){
        ll n;
        cin >> n;
        // set<ll> u;
        vector<ll> a;//储存所有的x值
        vector<vector<col>> e(1e6 + 5);
        for(ll i = 1; i <= n; i++){
            ll x, y;
            cin >> x >> y;
            a.push_back(x);
            e[x].push_back({y, i});
        }
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());//给所有的x值排序并去重
        priority_queue<node> pq;
        vector<ll> fa(1e6 + 5);
        for(ll i = 1; i <= n; i++)fa[i] = i;
        ll cnt = 1;
        ll ans = 0;
        auto find = [&] (auto && find, ll x) -> ll {
            return x == fa[x] ? x : fa[x] = find(find, fa[x]);
        };
        ll si = a.size();
        for(ll k = 0; k < si; k++){
            ll i = k;
            if(i < si)
            while(a[i] <= a[k] + 50){
                if(i >= si)break;
                for(auto o : e[a[i]]){
                    for(auto p : e[a[k]]){
                        if(p.num != o.num)pq.push({(a[k] - a[i]) * (a[k] - a[i]) + (o.y - p.y) * (o.y - p.y), o.num, p.num});
                    }
                }
                i++;
            }
            if(i < si){//强制向后添加一个
                for(auto o : e[a[i]]){
                    for(auto p : e[a[k]]){
                        if(p.num != o.num)pq.push({(a[k] - a[i]) * (a[k] - a[i]) + (o.y - p.y) * (o.y - p.y), o.num, p.num});
                    }
                }
                i++;
            }
            
        }
        while(cnt != n){
            auto b = pq.top();
            pq.pop();

            while(!pq.empty() && find(find, b.x) == find(find, b.y)){b = pq.top(); pq.pop();}
            ans += b.w;
            ll o = find(find, b.x);
            ll p = find(find, b.y);
            fa[o] = p;
            cnt++;
        }
        cout << ans << "\n";
    }
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    DUC::solve();
    return 0;
}
```

---

## 作者：_Emperorpenguin_ (赞：1)

## 题意简述 
 
给定 $n$ 个点，每两个点之间互连一条边。求图上的最小生成树。 

## 思路

如果想把每两个点之间都连一条边，很明显，时空限制都不允许。考虑到 $y\leq 10$，所以点的 $y$ 坐标对答案的影响很小。

因此我们可以对点排序。比较函数如下。

```cpp
bool cmp(Node a,Node b){
	if(a.x==b.x)//横坐标相等 
		return a.y<b.y;//纵坐标从小到大排 
	return a.x<b.x;//横坐标从小到大排
}
``` 

然后对距离点 $a_i$ 较近的几个点连边。连 $25$ 条边足矣。连边代码如下。 

```cpp
for(int i=1;i<=n;i++)
		for(int j=i+1;j<=min(i+25,n);j++){
			add(i,j,1ll*((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y)));
			add(j,i,1ll*((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y)));
		}
```

其余就是最小生成树模板了，代码略去。记得开 ```long long```。

---

## 作者：sccc_ (赞：0)

## Solution

暴力一定超时，考虑其他方法。

因为 $y$ 的取值很小，所以切入点在于 $y$。

先按照 $x$ 坐标进行排序，因为要取最优，再往后枚举 25 个点左右就行了。

最后 Kruskal 一下就行。

## Code

```c++
#include <bits/stdc++.h>
#define int long long
#define x first
#define y second

using namespace std;

const int kMaxN = 1e5 + 10;

int n, fa[kMaxN], idx;
pair<int, int> a[kMaxN];
pair<int, pair<int, int>> tr[kMaxN * 25];

int Find(int x) {
  return (fa[x] == x ? x : fa[x] = Find(fa[x]));
}

int GetDis(int i, int j) {
  return (a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y);
}

signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  sort (a + 1, a + 1 + n, [](auto a, auto b) {return (a.x == b.x ? a.y < b.y : a.x < b.x);});
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= min(i + 25, n); j++) {
      tr[++idx] = {i, {j, GetDis(i, j)}};
    }
  }
  sort (tr + 1, tr + 1 + idx, [](auto a, auto b) {return a.y.y < b.y.y;});
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
  }
  int sum = 0, cnt = 0;
  for (int i = 1; i <= idx; i++) {
    int a = Find(tr[i].x), b = Find(tr[i].y.x);
    if (a != b) {
      fa[a] = b;
      sum += tr[i].y.y;
      cnt++;
    }
    if (cnt == n - 1) {
      cout << sum;
      return 0;
    }
  }
  return 0;
}
```

---

