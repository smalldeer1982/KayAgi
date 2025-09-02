# Vanya and Treasure

## 题目描述

Vanya is in the palace that can be represented as a grid $ n×m $ . Each room contains a single chest, an the room located in the $ i $ -th row and $ j $ -th columns contains the chest of type $ a_{ij} $ . Each chest of type $ x<=p-1 $ contains a key that can open any chest of type $ x+1 $ , and all chests of type $ 1 $ are not locked. There is exactly one chest of type $ p $ and it contains a treasure.

Vanya starts in cell $ (1,1) $ (top left corner). What is the minimum total distance Vanya has to walk in order to get the treasure? Consider the distance between cell $ (r_{1},c_{1}) $ (the cell in the row $ r_{1} $ and column $ c_{1} $ ) and $ (r_{2},c_{2}) $ is equal to $ |r_{1}-r_{2}|+|c_{1}-c_{2}| $ .

## 样例 #1

### 输入

```
3 4 3
2 1 1 1
1 1 1 1
2 1 1 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 3 9
1 3 5
8 9 7
4 6 2
```

### 输出

```
22
```

## 样例 #3

### 输入

```
3 4 12
1 2 3 4
8 7 6 5
9 10 11 12
```

### 输出

```
11
```

# 题解

## 作者：George1123 (赞：11)

> [CF677D Vanya and Treasure](https://www.luogu.com.cn/problem/CF677D)

> 有一个 $n\times m$ 的矩阵 $a(1\le a_{i,j}\le p)$，求从起点 $(1,1)$ 出发依次遍历值为 $1\to p$ 的矩阵单元的最短路径曼哈顿距离。保证满足 $a_{i,j}=p$ 的 $(i,j)$ 唯一。

> 数据范围：$1\le n,m\le 300$，$1\le p\le n\cdot m$。

---
先记录 $\tt vector$ 数组 $w$，$w_t$ 表示 $a_{i,j}=t$ 的位置集合。

$w_t$ 的每个元素有三个属性：$x,y,g$。**$x$ 和 $y$ 是位置坐标，$g$ 是出发遍历矩阵值 $1\to t$ 后到 $(x,y)$ 的最短路径长度。**

---
**暴力做法**：从 $w_{i-1}$ 的所有 $g$ 值递推 $w_i$ 的所有 $g$ 值：

$$u.g=\min_{v\in w_{i-1}}\{v.g+{\rm abs}(u.x-v.x)+{\rm abs}(u.y-v.y)\}(u\in w_i)$$

**时间复杂度 $\Theta\left(\sum_{i\in[2,p]}|w_{i-1}|\cdot |w_i|\right)\le\Theta(n^2m^2)$**。

![image.png](https://i.loli.net/2020/05/23/8jBzyl31PX6skZ5.png)

- 怎么卡到 $\Theta(n^2m^2)$ 的？

比如 $n=300,m=300,p=2$，矩阵一半是 $1$ 一半是 $2$。

---
这题的优化是真的巧，反正我比赛时没想到。

**考虑以下情况：**

$$\forall i\in[2,p]:|w_{i-1}|\cdot|w_i|\le n\cdot m$$

**总的时间复杂度是：**

$$\Theta\left(\sum_{i\in[2,p]}|w_{i-1}|\cdot |w_i|\right)$$

同时满足 $\sum_{i=1}^p |w_i|=n\cdot m$，根据柯西不等式：

![image.png](https://i.loli.net/2020/05/23/UZ4vFhp1WP3D5Lk.png)

所以 $\sum_{i=2}^p|w_{i-1}|\cdot |w_i|\le n\cdot m\times\sqrt{n\cdot m}$。

**复杂为 $\Theta(n\cdot m\sqrt{n\cdot m})$ 可以通过。**

---
**但是如果 $\exists i\in[2,p]:|w_{i-1}|\cdot|w_i|>n\cdot m$ 怎么办呢？**

可以套个 $\Theta(V)$ 的**多源无向无权图最短路模板 $\tt Bfs$。**

所以此时单次递推的**时间复杂度也是 $\Theta(n\cdot m)$。**

这样的单次递推与 $|w_{i-1}|\cdot|w_i|=n\cdot m$ 相比：

1. 一次递推时间复杂度相等。

2. 由于对于这个 $i$ 的 $|w_{i-1}|\cdot|w_i|$ 大，所以对于其他 $i$ 的 $|w_{i-1}|\cdot|w_i|$ 较小。所以总时间复杂度小。

所以这样优化后**总时间复杂度 $\le \Theta(n\cdot m\sqrt{n\cdot m})$。** 可以通过。

---
- **代码：**

```cpp
//Data
const int N=3e2;
int n,m,k,a[N+7][N+7];
struct node{
	int x,y,g;
	node(int X=0,int Y=0,int G=0){x=X,y=Y,g=G;}
};
vector<node> w[N*N+7];

//Bfs
int d[N+7][N+7];
int tx[]={0,0,-1,1},ty[]={-1,1,0,0};
int ok(int x,int y){return 1<=x&&x<=n&&1<=y&&y<=m;}
void Bfs(vector<node>&s){ //多源无向无权图最短路模板 Bfs。
	vector<node> q;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) d[i][j]=inf;
	int sc=-1;
	q.pb(s[++sc]);
	for(int i=0;i<sz(q);i++){
		node v=q[i];
		while(sc+1<sz(s)&&s[sc+1].g<=v.g) q.pb(s[++sc]);
		for(int t=0;t<4;t++){
			node u=node(v.x+tx[t],v.y+ty[t]);
			if(ok(u.x,u.y)&&v.g+1<d[u.x][u.y]) d[u.x][u.y]=u.g=v.g+1,q.pb(u);
		}
	}
}

//Main
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
			if(a[i][j]==1) w[a[i][j]].pb(node(i,j,i+j-2));
			else w[a[i][j]].pb(node(i,j,inf));
		}
	for(int key=2;key<=k;key++){
		if(sz(w[key-1])*sz(w[key])<=n*m){
			for(node&u:w[key]) for(node v:w[key-1])
				u.g=min(u.g,v.g+abs(u.x-v.x)+abs(u.y-v.y));
		} else {
			vector<node> s;
			for(node v:w[key-1]) s.pb(v);
			Bfs(s);
			for(node&u:w[key]) u.g=d[u.x][u.y];
		}
	}
	printf("%d\n",w[k][0].g);
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：Purslane (赞：5)

# Solution

显然是分层图最短路。我们设 $dis_{x,y,z}$ 表示拥有了 $1,2,\dots,z$ 的钥匙，到达点 $(x,y)$ 的最短距离。答案就应当是 $dis_{px,py,p+1}$。

但是这有个麻烦。状态总数是 $O(n^4)$ 的。考虑到其实只有 $a_{x,y}+1=z$ 的时候这个关键点才有用。所以所以我们可以直接设 $dis_{x,y}$ 为拥有了 $1,2,\dots,a_{x,y}+1$ 的钥匙，到达 $(x,y)$ 的最短距离。

考虑两层之间转移。假设钥匙为 $k$ 的数量为 $w_k$。那么如果 $w_k w_{k+1}$ 比较小，我们可以直接枚举点对转移，这样复杂度是 $O(w_kw_{k+1})$ 的。如果比较大，我们可以考虑多源 BFS，这样复杂度是 $O(nm)$ 的。

那肯定贪心的选啊，看哪个快。现在证明复杂度是正确的。

如果 $w_kw_{k+1} >nm$，那么必有 $\max \{w_k,w_{k+1}\} > \sqrt {nm}$。而这样的点最多 $O(\sqrt{nm})$ 个，这意味着最多只有 $O(\sqrt{nm})$ 次 BFS。

如果 $w_kw_{k+1} \le nm$。考虑 $\sum w_k \le nm$，由均值不等式有 $\sum \sqrt{w_kw_{k+1}} \le nm$。不妨设 $\sqrt{w_kw_{k+1}}=a_k$。那么也就是求 $\sum a_k^2$ 大概是多少。我们假设 $a_k$ 的最大值为 $v$。由于 $v^2 \le mn$，$v \le \sqrt{nm}$。那么 $\sum a_k^2 \le v \sum a_k \le mn\sqrt{mn}$。也就是复杂度上限也是 $O(nm \sqrt{nm})$ 的。

总体复杂度为 $O(n^3)$。

[code](https://codeforces.com/contest/677/submission/211389061)

经验总结：

1. 对于初始不同的多源 BFS 要小心谨慎，选最小的那个作为源点，其他的源点在遍历到这个值得时候再加入。
2. 考场上遇到一种难题的多想几种方法，贪心的选择，说不定就过了。

---

## 作者：小菜鸟 (赞：5)

好题（

我们首先发现此题有明显的分层结构，即按格子内数字分$p$层

然后考虑如何建出分层图来跑最短路。

我们很容易想到两种建图方案：

#### 1.对于每个数字，建出一个$n \times m$的网格图。

此时在每一层内用`bfs`进行多源最短路即可。

最坏情况下$p=n \times m$，要更新约$300\times 300\times 90000$次，`TLE`。

#### 2.对于每个数字，直接将含有该数字的格子作为层内的点。

此时枚举相邻两层之间的全部点对，暴力更新答案即可。

最坏情况下$p=3$，$1$和$2$各占一半，要枚举约$45000\times 45000$对点，`TLE`。

---

我们发现以上两种想法均有其优秀之处，且最坏情况不会同时出现。

那么就可以通过特判使得点对较多（可以$n\times m$为阈值）的两层间用`bfs`更新，较少则枚举点对。

此时最坏情况显然是所有转移全部用`bfs`。点数多的层数不会多，因此最坏情况下更新次数不会超过约$300\times 300 \times 300$次，可以通过此题。

---

以上是在考场上想出解法的心路历程，并无严格证明（因为另一篇题解里的CF老哥已经证明了

但毕竟考场上更看重思想而不是证明（

总而言之就是暴力+特判=正解（不是

放代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>

typedef std::pair<int,int> point;

int n,m,k,mp[305][305];

std::vector<point> garden[90005];
int dis[305][305],dis2[305][305];
bool vis[305][305];

int dist(point a,point b)
{
	return abs(a.first-b.first)+abs(a.second-b.second);
}

void refresh(int lev)
{
	for(int i=0;i<garden[lev].size();++i)
	{
		int ux=garden[lev][i].first,uy=garden[lev][i].second;
		for(int j=0;j<garden[lev+1].size();++j)
		{
			int vx=garden[lev+1][j].first,vy=garden[lev+1][j].second;
			dis[vx][vy]=std::min(dis[vx][vy],dis[ux][uy]+dist(garden[lev][i],garden[lev+1][j]));
		}
	}
}

const int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};

void bfs(int lev)
{
	memset(dis2,0x3f,sizeof(dis2));
	static std::queue<int> qx,qy;
	for(int i=0;i<garden[lev].size();++i)
	{
		int ux=garden[lev][i].first,uy=garden[lev][i].second;
		dis2[ux][uy]=dis[ux][uy];
		qx.push(ux);
		qy.push(uy);
		vis[ux][uy]=1;
	}
	while(!qx.empty())
	{
		int ux=qx.front(),uy=qy.front();
		qx.pop();qy.pop();
		vis[ux][uy]=0;
		for(int i=0;i<4;++i)
		{
			int vx=ux+dx[i],vy=uy+dy[i];
			if(vx<0||vx>=n||vy<0||vy>=m)continue;
			if(dis2[vx][vy]>dis2[ux][uy]+1)
			{
				dis2[vx][vy]=dis2[ux][uy]+1;
				if(!vis[vx][vy])
				{
					qx.push(vx);
					qy.push(vy);
					vis[vx][vy]=1;
				}
			}
		}
	}
	for(int i=0;i<garden[lev+1].size();++i)
	{
		int ux=garden[lev+1][i].first,uy=garden[lev+1][i].second;
		dis[ux][uy]=dis2[ux][uy];
	}
}

void calc()
{
	for(int i=0;i<garden[1].size();++i)
	{
		int ux=garden[1][i].first,uy=garden[1][i].second;
		dis[ux][uy]=dist(garden[1][i],point(0,0));
	}
	for(int lev=1;lev<k;++lev)
	{
		if(garden[lev].size()*garden[lev+1].size()<n*m)
		{
			refresh(lev);
		}
		else
		{
			bfs(lev);
		}
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<m;++j)
		{
			scanf("%d",&mp[i][j]);
			garden[mp[i][j]].push_back(point(i,j));
		}
	}
	memset(dis,0x3f,sizeof(dis));
	calc();
	int res=0x3f3f3f3f;
	for(int i=0;i<garden[k].size();++i)
	{
		int ux=garden[k][i].first,uy=garden[k][i].second;
		res=std::min(res,dis[ux][uy]);
	}
	printf("%d",res);
}
```



---

## 作者：Zhao_daodao (赞：4)

# Vanya and Treasure

首先，这个题 $O(nm\sqrt{nm})$ 太屈才了。

所以，介绍一个 $O(nm\log^2(nm))$ 的做法。

---

首先，你可以枚举 $i\in[1,p]$ 转移答案。

转移式子如下：
$$
dp_{x,y}=\min_{p,q}dp_{p,q}+\operatorname{dis}((p,q),(x,y))
$$
其中 $a_{x,y}=i,a_{p,q}=i-1$。

可以开 $p$ 个 `vector`，每一次把 $(i,j)$ 放进 $a_{i,j}$ 对应的 `vector` 中。

这样就是 $O(n^2m^2)$ 的。

---

然后，你觉得这有点浪费。

因为每一个位置的转移都差不多，考虑全部拼起来。

![](https://img.picui.cn/free/2024/11/18/673ae3c8d8060.bmp)

- 对于第一区域的 $(p,q)$
  $$
  dp_{i,j}=(\min_{p,q} dp_{p,q}-p-q)+i+j
  $$

- 对于第二区域的 $(p,q)$
  $$
  dp_{i,j}=(\min_{p,q}dp_{p,q}-p+q)+i-j
  $$

- 对于第三区域的 $(p,q)$
  $$
  dp_{i,j}=(\min_{p,q}dp_{p,q}+p+q)-i-j
  $$

- 对于第四区域的 $(p,q)$
  $$
  dp_{i,j}=(\min_{p,q}dp_{p,q}+p-q)-i+j
  $$

然后你需要一个：

1. 能够在网格图中加入一些数
2. 查询从 $(1,1)$ 到 $(i,j)$ 的矩形中的最小值

可以使用**二维树状数组**。

那如何清空呢？

在加入的时候会遍历到一些位置，清空的时候，照着枚举一边，把途径的所有位置全部清空。

复杂度 $O(nm\log^2(nm))$。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define Pair pair<int,int>
#define mem(a,b) memset(a,b,sizeof a)
using namespace std;
const int MAXN=700+5;
const int inf=1e18;
int n,m,p,a[MAXN][MAXN];
int dp[MAXN][MAXN];
vector<Pair>G[MAXN*MAXN];
inline int dis(Pair a,Pair b){
	return abs(a.first-b.first)+abs(a.second-b.second);
}
#define lb(x) (x&-x)
int tr1[MAXN][MAXN],tr2[MAXN][MAXN],tr3[MAXN][MAXN],tr4[MAXN][MAXN];
#define Up1 for(int x=X;x<=n;x+=lb(x))
#define Down1 for(int x=X;x;x-=lb(x))

#define Up2 for(int y=Y;y<=m;y+=lb(y))
#define Down2 for(int y=Y;y;y-=lb(y))

inline void add1(int X,int Y,int k){Up1 Up2 tr1[x][y]=min(tr1[x][y],k);}
inline int qry1(int X,int Y){int ans=inf;Down1 Down2 ans=min(ans,tr1[x][y]);return ans;}
inline void init1(int X,int Y){Up1 Up2 tr1[x][y]=inf;}

inline void add2(int X,int Y,int k){Up1 Down2 tr2[x][y]=min(tr2[x][y],k);}
inline int qry2(int X,int Y){int ans=inf;Down1 Up2 ans=min(ans,tr2[x][y]);return ans;}
inline void init2(int X,int Y){Up1 Down2 tr2[x][y]=inf;}

inline void add3(int X,int Y,int k){Down1 Down2 tr3[x][y]=min(tr3[x][y],k);}
inline int qry3(int X,int Y){int ans=inf;Up1 Up2 ans=min(ans,tr3[x][y]);return ans;}
inline void init3(int X,int Y){Down1 Down2 tr3[x][y]=inf;}

inline void add4(int X,int Y,int k){Down1 Up2 tr4[x][y]=min(tr4[x][y],k);}
inline int qry4(int X,int Y){int ans=inf;Up1 Down2 ans=min(ans,tr4[x][y]);return ans;}
inline void init4(int X,int Y){Down1 Up2 tr4[x][y]=inf;}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
	cin>>n>>m>>p;
	G[0].push_back(Pair(1,1));
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		cin>>a[i][j];
		G[a[i][j]].push_back(Pair(i,j));
	}
	mem(tr1,0x3f),mem(tr2,0x3f),mem(tr3,0x3f),mem(tr4,0x3f);
	for(int t=1;t<=p;t++){
		for(auto [p,q]:G[t-1]){
			add1(p,q,dp[p][q]-p-q);
			add2(p,q,dp[p][q]-p+q);
			add3(p,q,dp[p][q]+p+q);
			add4(p,q,dp[p][q]+p-q);
		}
		for(auto [x,y]:G[t]){
			dp[x][y]=min({
				qry1(x,y)+x+y,
				qry2(x,y)+x-y,
				qry3(x,y)-x-y,
				qry4(x,y)-x+y
			});
		}
		for(auto [p,q]:G[t-1]){
			init1(p,q);
			init2(p,q);
			init3(p,q);
			init4(p,q);
		}
	}
	int ans=inf;
	for(auto [x,y]:G[p])ans=min(ans,dp[x][y]);
	cout<<ans<<"\n";
}
```

---

## 作者：QwQcOrZ (赞：4)

首先将每种数值的点都取出来，放在 k 个 vector 里

考虑换一种方法计算距离

我们强制 $x2>x1,y2>y1$，于是可以将原式变形：

$|x2-x1|+|y2-y1|$

$=x2-x1+y2-y1$

$=x2+y2-x1-y1$

$=(x2+y2)-(x1+y1)$

考虑转移：

$dp_{x2,y2}=dp_{x1,y1}+dis(x1,y1,x2,y2)$

$=dp_{x1,y1}+(x2+y2)-(x1+y1)$

$=(dp_{x1,y1}-x1-y1)+(x2+y2)$

也就是说我们把转移式分解成了两部分：和当前点有关的 $x2+y2$ 和与转移的点有关的 $dp_{x1,y1}-x1-y1$

那么只需要找到 $dp_{x1,y1}-x1-y1$ 的最大值转移即可

但回到最前面，我们发现这要在强制 $x2>x1,y2>y1$ 的情况下才能成立

也就是说点 $(x1,y1)$ 要在点 $(x2,y2)$ 的左上角

那么将上一个数值的所有点以 $x$ 坐标为第一关键字，$y$ 坐标为第二关键字排序

用一个类似二维数点的思想，从前往后加点并计算 $y$ 坐标小于当前 $y$ 坐标的最大 $dp_{x1,y1}-x1-y1$ 值，并加上 $x2+y2$ 即可

这个可以用树状数组轻松维护

但这样只考虑了 $x2>x1,y2>y1$（左上） 的情况，所以我们还要考虑另外的三种：$x2<x1,y2>y1$（右上），$x2<x1,y2<y1$（右下），$x2>x1,y2<y1$（左下）

此时我们可以通过翻转整个矩阵更方便的处理

也就是通过将 $i$ 变为 $n-i+1$，或将 $j$ 变为 $m-j+1$ 实现

这个讲起来可能比较抽象，可以结合代码理解

总而言之，先枚举数值，然后从四个方向暴力转移即可

$Code Below$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=9e4+5;
const ll inf=1ll<<60;

ll read()
{
	ll s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(ll x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(ll x,char c='\n')
{
	write(x);
	putchar(c);
}
struct node
{
	ll x,y,val,pos;//分别表示：横纵坐标、x+y-1的值、dp值存的位置
	bool operator <(const node &a)const
	{
		if (x==a.x) return y<a.y;
		return x<a.x;
	}
};
vector<node>a[N][4];
vector<ll>dp[N];
ll t[N],n,m,k,c[N],cnt=0;
bool b[N];
void add(ll x,ll y)
{
	for (;x<=m;x+=x&-x)
	{
		if (!b[x])
		{
			b[x]=1;
			c[++cnt]=x;
		}
		t[x]=min(t[x],y);
	}
}
ll query(ll x)
{
	ll ret=inf;
	for (;x;x-=x&-x) ret=min(ret,t[x]);
	return ret;
}//树状数组

int main()
{
	n=read();
	m=read();
	k=read();
	for (ll i=1;i<=k;i++)
	for (ll j=0;j<=3;j++) a[i][j].clear();
	for (ll i=1;i<=n;i++)
	for (ll j=1;j<=m;j++)
	{
		ll v=read();
		a[v][0].push_back((node){i,j,i+j-1,dp[v].size()});//从左上转移
		a[v][1].push_back((node){n-i+1,j,n-i+1+j-1,dp[v].size()});//从右上转移
		a[v][2].push_back((node){i,m-j+1,i+m-j+1-1,dp[v].size()});//从左下转移
		a[v][3].push_back((node){n-i+1,m-j+1,n-i+1+m-j+1-1,dp[v].size()});//从右下转移
		dp[v].push_back(inf);
	}
	for (ll i=1;i<=k;i++)
	for (ll j=0;j<=3;j++) sort(a[i][j].begin(),a[i][j].end());
	dp[0].push_back(-1);
	a[0][0].push_back((node){0,1,0,0});//建一个虚点作为起点，数值为0
	memset(b,0,sizeof(b));
	for (ll i=1;i<=m;i++) t[i]=inf;
	for (ll i=1;i<=k;i++)
	for (ll j=0;j<=3;j++)
	{
		ll l=0,r=0;
		for (ll ii=1;ii<=cnt;ii++) b[c[ii]]=0,t[c[ii]]=inf;//树状数组的清空不能直接清空，否则复杂度会达到O(mk)，所以要记录修改过的值清空
		cnt=0;
		while (l<a[i-1][j].size()&&r<a[i][j].size())//类似归并的思路转移
		if (a[i-1][j][l]<a[i][j][r])
		{
			add(a[i-1][j][l].y,dp[i-1][a[i-1][j][l].pos]-a[i-1][j][l].val);
			l++;
		}//插入一个被转移的点
		else
		{
			dp[i][a[i][j][r].pos]=min(dp[i][a[i][j][r].pos],query(a[i][j][r].y)+a[i][j][r].val);
			r++;
		}//转移
		while (l<a[i-1][j].size())
		{
			add(a[i-1][j][l].y,dp[i-1][a[i-1][j][l].pos]-a[i-1][j][l].val);
			l++;
		}//插入一个被转移的点
		while (r<a[i][j].size())
		{
			dp[i][a[i][j][r].pos]=min(dp[i][a[i][j][r].pos],query(a[i][j][r].y)+a[i][j][r].val);
			r++;
		}//转移
	}
	ll ans=inf;
	for (ll i=0;i<dp[k].size();i++) ans=min(ans,dp[k][i]);
	print(ans);

	return 0;
}
```

因为每个点只会被访问两次（一次被转移一次转移），所以复杂度可以达到优秀的$O(nmlogn)$，大概有8倍的常数，可以轻松通过此题

---

## 作者：鱼跃于渊 (赞：1)

## 做法  

一道简单的 dp 题。  

我们设 $S_{p}$ 为数字为 $p$ 的位置所构成的集合，$f_i$ 为解开位置 $i$ 上的锁所需的最小步数。  
转移是显然的，对于一个位置 $i\in S_{p}$，$f_i=\min_{j\in S_{p-1}}\{f_{j}+\lvert x_i-x_j \rvert+\lvert y_i-y_j \rvert \}$。  
暴力转移会被卡到 $O(n^2m^2)$，考虑如何快速求出 $f_i$。  
不难想到拆绝对值，我们分类讨论，发现有四种情况：  

$$ f_i = \min_{j\in S_{p-1}} f_j \begin{cases} -x_j-y_j+x_i+y_i &\text{ if } x_j\le x_i,y_j\le y_i\\
-x_j+y_j+x_i-y_i &\text{ if } x_j\le x_i,y_j > y_i\\
+x_j-y_j-x_i+y_i &\text{ if } x_j > x_i,y_j\le y_i\\
+x_j+y_j-x_i-y_i &\text{ if } x_j > x_i,y_j > y_i\\
\end{cases}$$

对这四种情况分别开一个二维树状数组即可做到快速转移。  
时间复杂度为 $O(n^2\log^2 n)$（这里认为 $n,m$ 同阶），可以通过此题。  


## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fisher{
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define pb push_back
#define epb emplace_back
#define all(x,l,r) &(x)[l],&(x)[r]+1
#define cto const auto
#define lowbit(x) ((x)&(-(x)))
template <class T> bool chkmn(T &x,T y){return x>y?(x=y,1):0;}
template <class T> bool chkmx(T &x,T y){return x<y?(x=y,1):0;}
char buf[1<<20],*p1,*p2;
#define getchar() ((p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2))?0:*p1++)
int read() {
    char ch=getchar();int x=0,f=1;
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*f;
}
#undef getchar
bool mbs;void cntime();
const int N=5e5+5,M=705,inf=1e18;
int n,m,k,ans=inf,f[N];
vector <array<int,2>> p[N];
struct BIT{
    int t[M][M];
    void init(){
        per(i,1,n) per(j,1,m) t[i][j]=inf;
    }
    void update(int x,int y,int k){
        for(int i=x;i<=n;i+=lowbit(i))
            for(int j=y;j<=m;j+=lowbit(j))
                chkmn(t[i][j],k);
    }
    void clear(int x,int y){
        for(int i=x;i<=n;i+=lowbit(i))
            for(int j=y;j<=m;j+=lowbit(j))
                t[i][j]=inf;
    }
    int query(int x,int y){
        int res=inf;
        for(int i=x;i;i-=lowbit(i))
            for(int j=y;j;j-=lowbit(j))
                chkmn(res,t[i][j]);
        return res;
    }
}t[4];
#define gid(x,y) (((x-1)*m+(y)))
#define fpx (n-x+1)
#define fpy (m-y+1)
#define dis(x1,y1,x2,y2) (abs(x1-x2)+abs(y1-y2))
void solve(int i){
    for(auto id:p[i-1]){
        int x=id[0],y=id[1],pl=gid(x,y);
        t[0].update(x,y,f[pl]-x-y);
        t[1].update(x,fpy,f[pl]-x+y);
        t[2].update(fpx,y,f[pl]+x-y);
        t[3].update(fpx,fpy,f[pl]+x+y);
    }
    for(auto id:p[i]){
        int x=id[0],y=id[1],pl=gid(x,y);
        chkmn(f[pl],t[0].query(x,y)+x+y);
        chkmn(f[pl],t[1].query(x,fpy)+x-y);
        chkmn(f[pl],t[2].query(fpx,y)-x+y);
        chkmn(f[pl],t[3].query(fpx,fpy)-x-y);
    }
    for(auto id:p[i-1]){
        int x=id[0],y=id[1];
        t[0].clear(x,y);
        t[1].clear(x,fpy);
        t[2].clear(fpx,y);
        t[3].clear(fpx,fpy);
    }
}
void main(){
    n=read();m=read();k=read();
    per(i,1,n) per(j,1,m)
        p[read()].pb({i,j});
    fill(all(f,1,n*m),inf);
    per(i,0,3) t[i].init();
    for(auto id:p[1])
        f[gid(id[0],id[1])]=dis(1,1,id[0],id[1]);
    per(i,2,k) solve(i);
    for(auto id:p[k]) chkmn(ans,f[gid(id[0],id[1])]);
    printf("%lld\n",ans);
    return cntime();
}
bool mbe;void cntime(){
    cerr<<"Time: "<<1e3*clock()/CLOCKS_PER_SEC<<" ms\n";
    cerr<<"Memory: "<<abs(&mbe-&mbs)/1024./1024.<<" MB\n";
}}
signed main(){
    fisher::main();
    return 0;
}
```

---

## 作者：_determination_ (赞：1)

这有啥好蓝的？？？

一眼 dp 设 $f_{i,j,k}$ 表示到 $(i,j)$ 的时候已经获得了前 $k$ 种权的最小步数。

显然这玩意要按层转移，设每种权的出现次数为 $w_i$ ，每个层有两种转移方式：

1. 点对点转移。

   显然有效转移只是从所有值在上一层的点转移到下一层的点。这样的话点对点转移复杂度就是 $O(w_iw_{i+1})$。

2. BFS 转移。

   多源 BFS 从全部上一层的点开始转移到全部下一层的点即可，复杂度 $O(nm)$。

两种情况都有对应的极限数据，他们的复杂度都是 $O(n^2m^2)$ 的。但是直接根号分治一下，阈值设为 $nm$ 即可做到 $O(nm\sqrt{nm})$。

https://codeforces.com/contest/677/submission/292134062

---

## 作者：Zi_Gao (赞：1)

## 前言

题解区有一些题解做法大体上每问题但是具体细节处理不到位，实际上时间复杂度并不能保证，所以这里提供一个更为清晰的题解。

## 正文

### 0x00 分析问题

由于题目的约束，在这个最短路中肯定经过了 $1,2,\cdots,p-1,p$ 一系列点，可以把问题划分成为 $p$ 个部分：

第一个部分：从 $(1,1)$ 到权值为 $1$ 的格子。

第二个部分：从权值为 $1$ 的格子到权值为 $2$ 的格子。

$\cdots$

第 $p$ 个部分：从权值为 $p-1$ 的格子到权值为 $p$ 的格子。

然后找到一个最短路。

### 0x01 解决问题

自然想到建立一个分层图，两层图之间的转移就是 $p$ 个阶段中的每一个阶段。

这里有两种（两层图之间）转移方式，设整个图大小为 $n\times m$ 两层的节点数分别为 $a,b$：

1. 直接两两计算转移，时间复杂度 $\mathcal{O}\left(ab\right)$。

2. 跑一个最短路，但是需要一个排序不然时间复杂度不稳定，$\mathcal{O}\left(a\log a + n+m\right)$，这里可以近似为 $\mathcal{O}\left(n+m\right)$。

实际上单纯用一种方法总会被卡 T。考虑进行缝合，当 $\mathcal{O}\left(ab\right)<\mathcal{O}\left(n+m\right)$ 时用第一种转移方式；否则用第二种。

这样可以保证时间复杂度不高于 $\mathcal{O}\left(\left(nm\right)^{1.5}\right)$ 具体证明可以看其他题解已经很清楚里。

这里要注意的点就是进行最短路可以使用类似 BFS 的技巧，不需要 Dijkstra，但是一定要排序一下，不然无法保证时间复杂度，当然这个题没有卡。

### 0x02 代码实现

AC CODE

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){register char s[20];register int i=0;if(x<0){x=-x;putchar('-');}if(x==0){putchar('0');return;}while(x){s[i++]=x%10;x/=10;}while(i){putchar(s[--i]+'0');}return;}

struct NODE{
    int x,y,w;
    bool operator < (const NODE another) const{
        return w>another.w;
    }
};

std::vector<NODE> e[310*310],s;
std::queue<NODE> Q;
int dis[310][310],n,m;

void bfs(){
    register int i,j;
    register NODE u;
    for(i=0;i<n;++i)
        for(j=0;j<m;++j) dis[i][j]=0x3f3f3f3f;
    std::priority_queue<NODE> Q;
    for(auto u:s) Q.push(u);
    while(!Q.empty()){
        u=Q.top();
        Q.pop();
        if(dis[u.x][u.y]<=u.w||(u.x<0)||u.x>=n||(u.y<0)||u.y>=m) continue;
        dis[u.x][u.y]=u.w;
        Q.push((NODE){u.x+1,u.y,u.w+1});
        Q.push((NODE){u.x-1,u.y,u.w+1});
        Q.push((NODE){u.x,u.y+1,u.w+1});
        Q.push((NODE){u.x,u.y-1,u.w+1});
    }
    return;
}

int abs(int x){return x<0?-x:x;}

int getDis(int x1,int y1,int x2,int y2){
    return abs(x1-x2)+abs(y1-y2);
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i,j,val,ans=0x3f3f3f3f;
    n=read();
    m=read();
    int p=read();
    for(i=0;i<n;++i)
        for(j=0;j<m;++j){
            val=read();
            e[val].push_back((NODE){i,j,val==1?getDis(0,0,i,j):0x3f3f3f3f});
        }

    for(val=2;val<=p;++val){
        if(e[val-1].size()*e[val].size()<=n*m*10)
            for(auto u:e[val-1])
                for(auto &v:e[val])
                    v.w=std::min(v.w,getDis(u.x,u.y,v.x,v.y)+u.w);
        else{
            s.clear();
            for(auto u:e[val-1]) s.push_back(u);
            bfs();
            for(auto &u:e[val]) u.w=dis[u.x][u.y];
        }
    }

    for(auto u:e[p]) ans=std::min(ans,u.w);

    print(ans);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

## 总结

根号分治的题，在思考过程中通常都会出现两种解法，一般我们只会执着于一种解法死磕和优化，但是不妨想一想这两种解法的优劣情况，并且最劣是否在同一种情况呢。若不是，那么大胆猜想吧！把他们“缝”在一起就好了！

---

## 作者：gcx114514 (赞：0)

首先我们发现这有着明显的分层图的结构，因为只有更新完 $val< i$ 的才会更新 $val=i$ 的，那么我们考虑如何通过第 $i-1$ 层的结果来更新第 $i$ 层的结果。

可以发现转移到一个点可以通过拆掉绝对值分为 $4$ 类， 依次为该点的左上、右上、左下和右下。这个讨论很简单。

现在已经分成了四个部分，显然是可以树套树得到一个 $O(nm\log^2 nm)$ 的做法。当然还可以更优秀：

我们考虑扫描线，从上到下扫描，将上一层横坐标在该行的加入线段树，然后更新左上和右上的答案。然后在从下到上扫描得到左下和右下的答案。那么现在的时间复杂度是 $O(nm\log nm)$，空间复杂度是 $O(nm)$ 的。

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb emplace_back
#define mid ((l+r)>>1)
#define ll long long
#define mk make_pair
#define rs now<<1|1
#define ls now<<1
#define reaD read
#define raed read
#define haed head
#define cotu cout
#define se second
#define fi first
#define itn int
using namespace std;
bool Mst;
const int Max=5e5+10;
const int mod=998244353;
const int inf=1e9+10;

inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

struct SGT{
	
	pii tr[1000<<2];
	
	void pushup(int now){
		tr[now].fi=max(tr[ls].fi,tr[rs].fi);
		tr[now].se=min(tr[rs].se,tr[ls].se);
	}
	
	void build(int now,int l,int r){
		tr[now]=mk(-inf,inf);
		if(l==r)return;
		build(ls,l,mid);build(rs,mid+1,r);		
	}
	
	void Modify(int now,int l,int r,int to,int val){
		if(l==r){
			tr[now].fi=max(tr[now].fi,val);
			tr[now].se=min(tr[now].se,val);
			return;
		}
		if(to<=mid)Modify(ls,l,mid,to,val);
		else Modify(rs,mid+1,r,to,val);
		pushup(now);
	}
	
	pii work(pii a,pii b){
		pii ans;
		ans.fi=max(a.fi,b.fi);ans.se=min(a.se,b.se);
		return ans;
	}
	
	pii Query(int now,int l,int r,int L,int R){
		if(L<=l&&R>=r)return tr[now];
		pii ans=mk(-inf,inf);
		if(L<=mid)ans=Query(ls,l,mid,L,R);
		if(R>mid)ans=work(ans,Query(rs,mid+1,r,L,R));
		return ans;
	}
 
}t1,t2; //可以换做树状数组 


vector<pii>pos[Max];
int ans[710][710];
int n,m,p;


void work1(int now){				//从上到下扫描 
	t1.build(1,1,m);t2.build(1,1,m);
	int j=0;
	for(auto i:pos[now]){ 
		while(j<(int)pos[now-1].size()&&pos[now-1][j].fi<=i.fi){
			auto las=pos[now-1][j];
			t1.Modify(1,1,m,las.se,las.se+las.fi-ans[las.fi][las.se]);
			t2.Modify(1,1,m,las.se,las.se-las.fi+ans[las.fi][las.se]); 
			++j;
		}
		int ans1=i.fi+i.se-t1.Query(1,1,m,1,i.se).fi;
		int ans2=i.fi-i.se+t2.Query(1,1,m,i.se,m).se;
		ans[i.fi][i.se]=min(ans1,ans2); 
	} 
}

void work2(int now){			//从下到上扫描 
	t1.build(1,1,m);t2.build(1,1,m);
	int j=pos[now-1].size()-1;
	for(int z=pos[now].size()-1;z>=0;--z){
		auto i=pos[now][z];
		while(j>=0&&pos[now-1][j].fi>=i.fi){
			auto las=pos[now-1][j];
			t1.Modify(1,1,m,las.se,las.fi-las.se+ans[las.fi][las.se]);
			t2.Modify(1,1,m,las.se,las.fi+las.se+ans[las.fi][las.se]);
			--j; 
		}
		int ans1=i.se-i.fi+t1.Query(1,1,m,1,i.se).se;
		int ans2=t2.Query(1,1,m,i.se,m).se-i.fi-i.se;
		int Ans=min(ans1,ans2);
		ans[i.fi][i.se]=min(ans[i.fi][i.se],Ans);
		
	}
}

bool Med;
signed main(){
	n=read(),m=read(),p=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			ans[i][j]=inf; 
			int x=read();
			if(x==1)ans[i][j]=i+j-2;
			pos[x].pb(mk(i,j));
		}
	} 
	for(int i=2;i<=p;++i){
		work1(i);
		work2(i);
	}
	int Ans=inf;
	for(auto i:pos[p]){
		Ans=min(Ans,ans[i.fi][i.se]);
	}
	cout << Ans << "\n";

	cerr<< "Time: "<<clock()/1000.0 << "s\n";
	cerr<< "Memory: " << (&Med-&Mst)/1000000.0 << "MB\n";
	return 0;
}
/*

*/

```

---

## 作者：Polarisx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF677D)。

## 思路

不妨记 $w_i$ 表示颜色为 $i$ 的点的数量，$p$ 表示有多少种颜色。

首先我们有一个很显然的 DP，记 $f_{k,i,j}$ 表示已经处理完 $1\sim k$ 的颜色，当前位置为 $(i,j)$ 的最小代价，那么

$$f_{k,i,j}=\min_{x,y,a_{x,y}=k-1} f_{k-1,x,y}+|i-x|+|j-y|$$

在 $w_iw_{i-1}\le nm$ 的情况下，时间复杂度是 $\mathcal O\left( \displaystyle \sum_{i=1}^{p}w_{i-1}w_i \right)\le \mathcal O \left({(nm)^{1.5}}\right)$，柯西不等式可得。

若 $w_iw_{i-1}\le nm$，那么我们就得到了一个 $\mathcal O (n^3)$ 的做法，考虑 $w_{i}w_{i-1}\gt nm$ 怎么做。

其实也很好做，对于一个点 $(x,y)$，它只会从它的左上/右上/左下/右下转移，这四种情况是类似的，下面仅介绍左上的做法：

我们有 $f_{k,i,j}=\min\limits_{x\le i,y\le j} f_{k-1,x,y}+|i-x|+|j-y|$，初始化 $dp_{i,j}=f_{k-1,i,j}$，那么有转移 $dp_{i,j}=\min(dp_{i-1,j}+1,dp_{i,j-1}+1,dp_{i,j})$，最后得到的 $dp_{i,j}$ 就是 $f_{k,i,j}$，时间复杂度 $\mathcal O \left((nm)^{1.5}\right)$。

两者结合就能得到一个 $\mathcal O (n^3)$ 的代码（$n,m$ 同阶）。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
using namespace std;

const int Maxn=710;
const int inf=2e9;
int n,m,p;
int a[Maxn][Maxn];
vector<pair<int,int> >e[Maxn*Maxn];
int f[Maxn][Maxn][2];

inline void work(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            f[i][j][1]=min(min(f[i-1][j][1],f[i][j-1][1])+1,f[i][j][1]);
    for(int i=n;i;i--)
        for(int j=m;j;j--)
            f[i][j][1]=min(min(f[i+1][j][1],f[i][j+1][1])+1,f[i][j][1]);
    for(int i=n;i;i--)
        for(int j=1;j<=m;j++)
            f[i][j][1]=min(min(f[i+1][j][1],f[i][j-1][1])+1,f[i][j][1]);
    for(int i=1;i<=n;i++)
        for(int j=m;j;j--)
            f[i][j][1]=min(min(f[i-1][j][1],f[i][j+1][1])+1,f[i][j][1]);
}


int main(){
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]),
            e[a[i][j]].emplace_back(i,j);
    for(int i=0;i<=n+1;i++)
        for(int j=0;j<=m+1;j++)
            f[i][j][0]=f[i][j][1]=inf;
    f[1][1][0]=0;
    e[0].emplace_back(1,1);

    for(int i=1;i<=p;i++){
        if(e[i].size()*e[i-1].size()<=n*m){
            for(auto j:e[i])
                for(auto k:e[i-1])
                    f[j.fi][j.se][1]=min(f[j.fi][j.se][1],f[k.fi][k.se][0]+abs(j.fi-k.fi)+abs(j.se-k.se));
            for(auto j:e[i-1]) f[j.fi][j.se][0]=inf;
            for(auto j:e[i]) swap(f[j.fi][j.se][0],f[j.fi][j.se][1]);
        }
        else{
            for(int j=0;j<=n+1;j++) for(int k=0;k<=m+1;k++) f[j][k][1]=f[j][k][0];
            work();
            for(int j=0;j<=n+1;j++) for(int k=0;k<=m+1;k++) f[j][k][0]=inf;
            for(auto j:e[i]) f[j.fi][j.se][0]=f[j.fi][j.se][1]; 
            for(int j=0;j<=n+1;j++) for(int k=0;k<=m+1;k++) f[j][k][1]=f[j][k][0];
        }
    }
    int ans=inf;
    for(auto j:e[p]) ans=min(ans,f[j.fi][j.se][0]);
    printf("%d",ans);
    return 0;
}
```

---

