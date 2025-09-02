# [ABC324F] Beautiful Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc324/tasks/abc324_f

$ N $ 個の頂点と $ M $ 本の辺からなる有向グラフがあります。各辺には**美しさ**と**コスト**の $ 2 $ つの正整数値が定められています。

$ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ から頂点 $ v_i $ への有向辺であり、その美しさは $ b_i $ 、コストは $ c_i $ です。 ここで、$ u_i\ \lt\ v_i $ が制約として保証されます。

頂点 $ 1 $ から頂点 $ N $ へのパス $ P $ を $ 1 $ つ選んだときの、下記の値としてあり得る最大値を求めてください。

- $ P $ 上のすべての辺の美しさの総和を、$ P $ 上のすべての辺のコストの総和で割った値
 
ここで、与えられるグラフにおいて頂点 $ 1 $ から頂点 $ N $ へのパスが $ 1 $ 個以上存在することが制約として保証されます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i\ \lt\ v_i\ \leq\ N $
- $ 1\ \leq\ b_i,\ c_i\ \leq\ 10^4 $
- 頂点 $ 1 $ から頂点 $ N $ へのパスが存在する
- 入力される値はすべて整数
 
### Sample Explanation 1

パス $ P $ として、 $ 2,\ 6,\ 7 $ 番目の辺をこの順に通り頂点 $ 1\ \rightarrow\ 3\ \rightarrow\ 4\ \rightarrow\ 5 $ とたどるバスを選んだとき、「 $ P $ 上のすべての辺の美しさの総和を $ P $ 上のすべての辺のコストの総和で割った値」 は、 $ (b_2\ +\ b_6\ +\ b_7)\ /\ (c_2\ +\ c_6\ +\ c_7)\ =\ (9\ +\ 4\ +\ 2)\ /\ (5\ +\ 8\ +\ 7)\ =\ 15\ /\ 20\ =\ 0.75 $ であり、これがあり得る最大値です。

## 样例 #1

### 输入

```
5 7
1 2 3 6
1 3 9 5
2 3 1 5
2 4 5 3
2 5 1 9
3 4 4 8
4 5 2 7```

### 输出

```
0.7500000000000000```

## 样例 #2

### 输入

```
3 3
1 3 1 1
1 3 2 1
1 3 3 1```

### 输出

```
3.0000000000000000```

## 样例 #3

### 输入

```
10 20
3 4 1 2
7 9 4 5
2 4 4 5
4 5 1 4
6 9 4 1
9 10 3 2
6 10 5 5
5 6 1 2
5 6 5 2
2 3 2 3
6 10 4 4
4 6 3 4
4 8 4 1
3 5 3 2
2 4 3 2
3 5 4 2
1 5 3 4
1 2 4 2
3 7 2 2
7 8 1 3```

### 输出

```
1.8333333333333333```

# 题解

## 作者：不知名用户 (赞：7)

给定一个 $N$ 个点，$M$ 条边的有向图，边都从编号小的点连向编号大的点（很不平凡的有向无环图），每条边有两个属性 $b,c$，求一条 $1\to N$ 的路径，使得路径上的所有边 $b$ 之和除以 $c$ 之和最大。$1\le b,c\le10^4;1\le N,M\le10^5$，精度到 $10^{-9}$。

$b$ 之和除以 $c$ 之和明显想到 0/1 分数规划（不懂没关系），我们可以二分答案 $mid$，如果答案大于等于 $mid$，那么：

$$\exists path,\frac{\sum\limits_{edge\in path}edge_b}{\sum\limits_{edge\in path}edge_c}\ge mid\iff \sum\limits_{edge\in path}(edge_b-mid\cdot edge_c)\ge 0$$

于是以 $b-mid\cdot c$ 为边权建图，只需判断是否存在 $1\to N$ 的路边权和大于 0 即可。注意到边从小编号连向大编号，直接 DP 即可，时间复杂度 $\Theta(50(N+M))$，50 表示二分的次数。[AC code](https://atcoder.jp/contests/abc324/submissions/46559063)。

```cpp
#include<bits/stdc++.h>
#define lf long double
using namespace std;

const int N = 2e5 + 10;
const lf eps = 1e-11;

int n, m, u[N], v[N], b[N], c[N];

struct edge
{
	int e, ne;
	lf l;
}e[N];
int h[N], idx;

inline void add(int a, int b, lf c)
{
	e[++idx] = {b,h[a],c};h[a] = idx;
}

lf f[N];

bool check(lf mid)
{
	int i;
	for(i=1;i<=n;i++) h[i] = 0, f[i] = -1e15;
	idx = 0;
	for(i=1;i<=m;i++)
		add(u[i],v[i],(lf)1.0*b[i]-mid*c[i]);
	f[1] = 0;
	for(i=1;i<=n;i++)
	{
		for(int x=h[i];x;x=e[x].ne)
		{
			int to = e[x].e;
			lf l = e[x].l;
			if(f[i]+l>f[to]) f[to] = f[i] + l;
		}
	}
	return f[n] > -eps;
}

signed main()
{
	ios::sync_with_stdio(0);
	int i;
	cin>>n>>m;
	for(i=1;i<=m;i++)
		cin>>u[i]>>v[i]>>b[i]>>c[i];
	lf l = 0, r = 1e4, mid;
	for(i=1;i<=50;i++)
	{
		mid = (l + r) / 2;
		if(check(mid)) l = mid;
		else r = mid;
	}
	printf("%.15Lf\n", l);
	return 0;
}
```

---

## 作者：CrTsIr400 (赞：6)

## ABC324F Beautiful Path

### 题意

有一个**有向图**，图中有 $N$ 个顶点和 $M$ 条边。每条边有两个正整数值：**美观度**和**成本值**。

对于 $i = 1, 2, \ldots, M$，第 $i$ 条边从顶点 $u_i$ 指向顶点 $v_i$，美观度为 $b_i$，成本为 $c_i$。保证 $u_i \lt v_i$.

求从最大化 $1$ 到 $N$ 路径的 美观度之和 与 成本值之和 的比值。

保证至少有一条从顶点 $1$ 到顶点 $N$ 的路径。$N,M\le 2\times 10^5$。

### 思路

比赛时候没注意到保证 $u_i<v_i$，然后以为是一般图做法，很不幸地 TLE 了。

实际上，这张图是 DAG。

考虑 $0/1$ 分数规划，二分一个 $mid$，要求这段路径的比值大于等于 $mid$。

于是改写边权，每条从 $u$ 到 $v$ 的边权变为 $b-mid\times c$。若 $1$ 到 $n$ 的最长路边权大于 $0$，即可判断可行。

代码非常简短。注意 DAG 的 DP 要从每个节点开始。

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#define fo(i,a,b) for(auto i(a),_ed(b);i<=_ed;++i)
#define gch(k) for(;(k);CH=getchar())
using namespace std;using I=int;using LL=long long;using V=void;I FL,CH;LL InNum;LL in(){InNum=0;FL=1;gch(!isdigit(CH)&&CH!=EOF)FL=(CH=='-')?-1:1;gch(isdigit(CH))InNum=10*InNum+CH-'0';return InNum*FL;}
const I N=2e5+10;
using DB=long double;
vector<pair<array<I,3>,DB> >e[N];
I q[N],n,m,ql,qr,d[N],ind[N];
DB f[N];
const DB eps=1e-12;
bool pd(DB mid){
	fo(x,1,n)for(auto&i:e[x])i.second=i.first[1]-i.first[2]*mid;
	ql=1;qr=0;
	fo(i,1,n){
		ind[i]=d[i];
		if(!ind[i])q[++qr]=i;}
	for(;ql<=qr;++ql){I x=q[ql];
		for(auto&i:e[x]){
			I y=i.first[0];
			if((--ind[y])==0)q[++qr]=y;}}
	fo(i,1,n)f[i]=-1e30;
	f[1]=0;
	fo(k,1,qr){
		I x=q[k];
		for(auto&i:e[x]){
			I y=i.first[0];DB z=i.second;
			f[y]=max(f[y],f[x]+z);}}
	return f[n]>0;}
I main(){n=in();m=in();
	fo(i,1,m){I u=in(),v=in(),b=in(),c=in();
		e[u].push_back(make_pair(array<I,3>{v,b,c},0));++d[v];}
	DB l=0,r=1e9,mid,ans=-1;
	while(r-l>eps){
		mid=(l+r)/2;
		if(pd(mid))ans=mid,l=mid+eps;
		else r=mid-eps;}
	return printf("%.10Lf\n",ans),0;}
```

另外提一嘴，对于一般图做法就需要最长路+判断正环，算法需要使用 SPFA。不过要是这样的话 $n,m$ 就应该开到 $2\times 10^3$ 级别了。



---

## 作者：MornStar (赞：5)

# [ABC324F] Beautiful Path 题解
## update on 2024.1.25
修正了两处错误。

## 题目大意
给定一个 DAG，每条边有两个权值 $b_i$ 和 $c_i$。

设边的集合为 $E$。

你需要找到一条从 $1$ 到 $n$ 的路径 $P$ 使得：$\dfrac{\sum_{E_i\in P}{b_i}}{\sum_{E_i\in P}{c_i}}$ 最大。

求这个最大值。

## 思路
很裸的分数规划题。

分数规划顾名思义就是求一个分数表达式的最大（小）值。

以这道题为例，我们设这个式子的最大值为 $M$。

即：
$$
\dfrac{\sum_{E_i\in P}{b_i}}{\sum_{E_i\in P}{c_i}}\le M \Rightarrow \sum_{E_i\in P}{b_i}\le \sum_{E_i\in P}{c_i}\times M \Rightarrow 
\sum_{E_i\in P}{b_i}-\sum_{E_i\in P}{c_i}\times M \le 0
$$

也就是：

$$
\sum_{E_i\in P}({b_i}-{c_i}\times M) \le 0
$$

二分 $M$。

check 时将每条边的权值替换为 $b_i-c_i\times M$。如果 $1$ 到 $n$ 的最长路长度小于零，则 $M$ 偏大，否则偏小。

由于原图为 DAG 所以求最长路时可以使用拓扑排序。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct edge{
	int to;
	double b,c;
};
vector<edge> e[200005],k[200005];
int du[200005],cnt[200005];
double dis[200005];
queue<int>q;
void get() {
	for(int i=1;i<=n;i++){
		dis[i]=-0x3f3f3f3f;
		cnt[i]=0;
		if(du[i]==0)	q.push(i);
	}
	dis[1]=0;
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(auto it:k[now]){
			dis[it.to]=max(dis[it.to],dis[now]+it.b);
			cnt[it.to]++;
			if(cnt[it.to]==du[it.to])	q.push(it.to);
		}
	}
}
void add(int a,int b,double vala,double valb){
	e[a].push_back({b,vala,valb});
}
bool check(double x){
	for(int i=1;i<=n;i++){
		k[i].clear();
		for(auto it:e[i]){
			k[i].push_back({it.to,it.b-it.c*x,it.c});
		}
	}
	get();
	return dis[n]>=0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1,u,v,w,g;i<=m;i++){
		cin>>u>>v>>w>>g;
		add(u,v,w,g);
		du[v]++;
	}
	double l=-2e9,r=2e9;
	while(r-l>=1e-10){
		double mid=(l+r)/2;
		if(check(mid))	l=mid;
		else	r=mid;
	}
	cout<<fixed<<setprecision(10)<<l<<"\n";
}
```

---

## 作者：FL_sleake (赞：4)

## 题意简述

给定两个整数 $n,m$，表示有 $n$ 个点 $m$ 条边，随后 $m$ 行每行四个参数 $u,v,b,c$，表示 $u$ 到 $v$ 有一条边（保证有 $u\leq v$ ），这条边美丽值为 $b$，代价为 $c$。定义一条路径的美丽程度是这条路径上所有边的美丽值之和除以这条路径上所有边的美丽值之差。

问起点为 $1$，终点为 $n$ 的路径中，美丽程度最大是多少？保证存在一条起点为 $1$，终点为 $n$ 的路径。

## 解题思路

二分最大美丽程度。

一个很有用的条件是 $u\leq v$，这表明图中不存在环。而且我们可以通过从编号小的点遍历到编号大的点来计算最大值。因为当遍历到 $i$ 节点时，指向 $i$ 的边都在先前遍历过了。

需要注意的是不要直接用美丽值除以代价算，而是做个变形，~~这样就不会像我一样被卡精度了~~。

## 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int u;
	double b,c,num;
	bool operator<(const node &b)const{
		return num>b.num;
	}
};
int n,m;
double dis[200010];
vector<node> G[200010];
bool check(double num){
	for(int i=1;i<=n;i++) dis[i]=-1000000000000;
	dis[1]=0;//初始化
	for(int i=1;i<=n;i++){
		for(int j=0;j<G[i].size();j++){
			dis[G[i][j].u]=max(dis[G[i][j].u],dis[i]+G[i][j].b-G[i][j].c*num);
            //更新i节点能到的边。
            //做了一个转换，没有直接用除法计算美丽程度
            //而是根据当前二分的num判断符不符合
            //其实就是把分母乘过来然后两边同时减去啦
		}
	}
	return dis[n]>=0;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,b,c;
		cin>>u>>v>>b>>c;
		G[u].push_back({v,b,c});
        //单向边
	}
	double l=0,r=3000000000;
	for(int i=0;i<=100;i++){
    //浮点数二分模板
		double mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	printf("%.10lf\n",l);
	return 0;
}
```

---

## 作者：RiceFruit (赞：3)

## 题意

给定 $N$ 个点，$M$ 条边的有向图，保证对于每条边 $u,v$，皆满足 $u < v$，每条边有两个权值 $b,c$，定义一条路径的权值为：这条路径上边的 $b$ 之和除以 $c$ 之和。让你求出所有 $1$ 到 $n$ 的路径的权值最大值。

数据范围：$N,M\le 2\cdot 10^5;b,c\le 10^4$。

---

## 思路

乍一眼看，此题很像 `0/1分数规划`[^1]，算阶中有讲。
于是考虑二分，设最大值 $>k$，然后拓扑排序记录最大值，最后看一下第 $n$ 个点的最大值是否 $>0$ 即可。

---

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double
const int N = 200200;
const double eps = 1e-15;
int n, m;
int deg[N];
struct Edge {
    int nxt;
    int to;
    int w1;
    int w2;
    Edge() {}
    Edge(int x, int y, int w, int z)
        : nxt(x), to(y), w1(w), w2(z) {}
} e[N << 2];
int h[N], cnt;
void add(int u, int v, int w1, int w2) {
    e[++cnt] = Edge(h[u], v, w1, w2);
    h[u] = cnt;
    return;
}
double L = 0, R = 2e17;
double mx[N];
bool check(double x) {
    for (int i = 1; i <= n; ++i) {
        mx[i] = -2e17;
    }
    mx[1] = 0;
    for (int u = 1; u <= n; ++u) {
        for (int i = h[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            double w1 = e[i].w1, w2 = e[i].w2;
            mx[v] = max(mx[v], mx[u] + w1 - x * w2);
        }
    }
    if (mx[n] >= 0)
        return 1;
    return 0;
}
signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v, w1, w2;
        scanf("%d%d%d%d", &u, &v, &w1, &w2);
        add(u, v, w1, w2);
        deg[v]++;
    }
    while (R - L > eps) {
        double mid = (L + R) / 2.0;
        if (check(mid)) {
            L = mid;
        } else {
            R = mid;
        }
    }
    printf("%.18Lf\n", L);
    return 0;
}
```

---
[^1]: post-01-fen-shuo-gui-hua

---

## 作者：qejwdi (赞：2)

这题就很典。。。。

看到求最值，直接考虑二分答案。

现在要 check 一个 `k` 是否可行，即存在：

$\frac{\sum b}{\sum c} \geq k$

移项得：

$\sum b \geq k \times \sum c$

再移向：

$\sum b - \sum c \times k \geq 0$

此时就可以把一条边的边权设为 $b_i - c_i \times k$，那么此时 `check` 的就变成了是否有 1 到 n 的路径边权和大于等于 0，这个东西你求个最长路就行了。

注意到 $u_i < v_i$ 所以可以直接 dp，每次往后面暴力更新即可。

# 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
#define rep(i,l,r) for (int i = (l); i <= (r); i++)
#define per(i,r,l) for (int i = (r); i >= (l); i--)
#define debug(x) cout << #x << '=' << x << '\n'
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int, int> PII;
typedef double db;
void tomax(int& a, int b) {a = max(a, b);}
void tomin(int& a, int b) {a = min(a, b);}
const int N = 2e5 + 5;
int n, m, d[N], q[N];
struct Node {
	int to, a, b;
	double w;
};
vector<Node> g[N];
double dp[N];
bool check(double x) {
	for (int i = 1; i <= n; i ++ ) {
		for (Node &o: g[i])
			o.w = o.a * 1.0 - o.b * x;
		dp[i] = -1e9;
	}
	dp[1] = 0;
	for (int i = 1; i <= n; i ++ ) {
		for (Node &o: g[i]) {
			int v = o.to;
			dp[v] = max(dp[v], dp[i] + o.w);
		}
	}
	if (dp[n] > 0) return true;
	else return false;
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i ++ ) {
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		g[u].pb((Node){v,a,b,0});
		d[v]++;
	}
	double l = 0, r = 1e9;
	for (int t = 0; t < 100; t ++ ) {
		double mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%.16lf", l);
	return 0;
}
```

---

## 作者：ForgotDream_CHN (赞：2)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17765214.html)

> 给出一张 DAG，每条边有两种边权 $b$ 与 $c$，求一条从 $1$ 到 $n$ 的路径，问路径经过的边的 $\dfrac{\sum b}{\sum c}$ 的最大值是多少。  
> $n, m \le 2 \times 10^5$。

这不是经典 01 分数规划吗？将题目中的要求写成如下形式：

$$
\begin{aligned}
& \text{Maximize } \dfrac{\sum_{1 \le i \le m} x_i b_i}{\sum_{1 \le i \le m} x_i c_i} \\
& \text{s.t. } \text{ 所有 } i \in [1, m] \land x_i = 1 \text{ 的边构成一条 } 1 \text{ 到 } n \text{ 的路径}
\end{aligned}
$$

我们考虑二分一个答案 $p$，使得有如下关系成立：

$$
\forall s \in S, \dfrac{\sum_{i \in s} b_i}{\sum_{i \in s} c_i} \le p
$$

其中 $S$ 为 $1$ 到 $n$ 的所有路径所构成的集合。容易看出 $p$ 的最小值就是所求的答案。将上边的式子转化一下，我们就得到：

$$
\begin{aligned}
\dfrac{\sum_{i \in s} b_i}{\sum_{i \in s} c_i} &\le p \\
\sum_{i \in s} b_i &\le p \sum_{i \in s} c_i \\
\sum_{i \in s} b_i - p \sum_{i \in s} c_i &\le 0 \\
\sum_{i \in s} \left(b_i - p c_i \right) &\le 0 \\
\end{aligned}
$$

将边权重定义为 $b - pc$，那么我们就容易发现上述条件成立等价于 $1$ 到 $n$ 的最长路小于等于 $0$，当且仅当 $p$ 取到答案时取等号。于是我们只需要二分这个答案 $p$，将边权重新定义，然后跑 $1$ 到 $n$ 的最长路即可。

这里需要注意的是，原题给定的是一张 DAG，那么最长路是可以用拓扑排序去跑的（而且据说 SPFA 被卡了），于是就得到了一个 $\mathcal{O}((n + m) \log V)$ 的做法。

记得拓扑排序的时候把每个入度为 $0$ 的点塞进去。

[代码](https://atcoder.jp/contests/abc324/submissions/46586959)

---

## 作者：LCat90 (赞：1)

一种贪心的思路是计算当前的答案值然后从大到小去更新最短路。但是很容易证伪。

观察到最终的答案是一堆和除以一堆和，想到使用 01 分数规划来处理。

二分最终的答案 $x$。我们要找到一组可行解使得答案刚好大于 $x$。考虑转化式子：

$$\dfrac{\sum a_i}{\sum b_i}\ge x \Rightarrow \sum a_i-x\sum b_i\ge 0\Rightarrow \sum(a_i-x\times b_i)\ge 0$$

相当于现在每条边的权值变成了 $a_i-x\times b_i$，计算从 $1$ 到 $N$ 的最长路。

有一个重要的条件：$u_i< v_i$，说明这是一个 DAG，怎么做都可以。直接 DP 或者是跑最短路，但听说 SPFA 会被卡。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 4e5 + 5, M = 1e13;
const double eps = 1e-11;
int n, m;
double dp[N]; bool vis[N];
struct edge { 
	int x, val, tim; 
}; 
vector<edge> G[N];
struct node { 
	int x, val, tim; 
	friend bool operator < (node a, node b) { return a.val * b.tim > b.val * a.tim; }
};
double check(double x) {
	for(int i = 1;i <= n; ++i) dp[i] = -1e15;
	dp[1] = 0;
	for(int i = 1;i <= n; ++i)
		for(int j = 0;j < G[i].size(); ++j) {
			int to = G[i][j].x;
			dp[to] = max(dp[to], dp[i] + G[i][j].val - x * G[i][j].tim); 
		}
	return dp[n];
}
signed main() {
	cin >> n >> m;
	for(int i = 1, x, y, ll, l6;i <= m; ++i) {
		cin >> x >> y >> ll >> l6;
		G[x].pb((edge){y, ll, l6});
		G[y].pb((edge){x, ll, l6});
	}
	double l = -1e10, r = 1e10;
    while (l + eps < r) {
        double mid = (l + r) / 2;
		if (check(mid) >= 0) l = mid;
        else r = mid;
    }
	printf("%.10lf", l);
	return 0;
}
```

---

## 作者：2huk (赞：1)

# F - Beautiful Path

## Description

给定一张 $n$ 个点 $m$ 条边的有向无环图，第 $i$ 条边为 $u_i \to v_i$，且有两个属性 $b_i, c_i$。

请你找到一条从 $1$ 到 $n$ 的路径，使得经过的边的 $b_i$ 之和与 $c_i$ 之和的比值最大。

## Solution

01 分数规划入门~~坟~~题。

考虑二分答案。对于每次二分得到的中点 $mid$，我们判断是否存在一条路径使得这条路径的价值（价值指题意中“经过的边的 $b_i$ 之和与 $c_i$ 之和的比值”）大于或等于 $mid$。若存在，尝试找更大的答案；否则找更小的答案。

那么如果存在这条路径，不妨设这条路径上的边为 $\{e_k\}$，那么等价于这个式子：
$$
\dfrac{\sum b_{e_k}}{\sum c_{e_k}} \ge mid
$$
可得：
$$
\sum b_{e_k} - mid \times \sum c_{e_k} \ge 0
$$
那么我们将第 $e_k$ 条边的权值看作 $b_{e_k} - mid \times c_{e_k}$，现在只需要找到是否存在这样的一条路径使得总边权值 $\ge 0$ 即可。

我们可以找到按照这样给边赋权值的从 $1$ 到 $n$ 的最长路。若这条最长路径上的总权值 $\ge 0$，就代表找到了一种合法方案。于是就能判断当前的 $mid$ 是否合法了。

由于题目保证图是一个 DAG，所以求最长路直接跑拓扑排序即可。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m;
int h[N], e[N], ne[N], idx = 1;
double B[N], C[N];
int D[N], d[N];

void add(int a, int b, int c, int d)
{
	e[idx] = b, ne[idx] = h[a], A[idx] = c, B[idx] = d, h[a] = idx ++ , ++ D[b];
}

int q[N], hh, tt;
double f[N];

bool chk(double mid)
{
	for (int i = 2; i <= n; ++ i ) f[i] = -2e9, d[i] = D[i];
	f[1] = 0;
	hh = 0, tt = 0;
	
	for (int i = 1; i <= n; ++ i )
		if (!d[i])
			q[tt ++ ] = i;
	
	while (hh != tt)
	{
		int t = q[hh ++ ];
		if (hh == N) hh = 0;
		for (int i = h[t]; i; i = ne[i])
		{
			int j = e[i];
			f[j] = max(f[j], f[t] + B[i] - C[i] * mid);
			if (!( -- d[j])) q[tt ++ ] = j;
			if (tt == N) tt = 0;
		}
	}
	
	return f[n] >= 0;
}

int main()
{
	cin >> n >> m;
	
	while (m -- )
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		add(a, b, c, d);
	}
	
	double l = 0, r = 1e5;
	for (int i = 1; i <= 100; ++ i )		// 二分 100 次差不多就够了
	{
		double mid = (l + r) / 2;
		if (chk(mid)) l = mid;
		else r = mid;
	}
	
	printf("%.10lf\n", l);
	
	return 0;
}
```





---

## 作者：FReQuenter (赞：0)

考虑二分。

现在已经有了一个答案，怎么判断是否合法。

我们观察题目中给出的关系：需满足答案路径上 

$$\frac{sumb}{sumc}>mid$$

稍微变个型：

$$sumb-sumc\times mid>0$$

令

$$x=sumb-sumc\times mid$$

想到了啥？把上式作为图上每一条边的边权，这样就消去了除法不能加减的问题，就可以愉快地跑最长路了。如果最后到达 $n$ 时最长路 $\geq 0$ 那么显然就合法。

题目里给定了 $u_i<v_i$ 所以没有环，求最长路直接从 $1$ 到 $n$ 枚举起点和出边就行了。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
int n,m;
vector<pair<pair<int,double>,pair<double,double>>> gv[200005];
double dist[200005];
bool check(double mid){
	for(int i=1;i<=n;i++) dist[i]=-1e9;
	for(int i=1;i<=n;i++){
		for(auto &nx:gv[i]){
			nx.fi.se=nx.se.fi-mid*nx.se.se;
		}
	}
	dist[1]=0;
	for(int i=1;i<=n;i++){
		for(auto nx:gv[i]){
			dist[nx.fi.fi]=max(dist[nx.fi.fi],dist[i]+nx.fi.se);
		}
	}
	return dist[n]>=0;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		double u,v,a,b;
		cin>>u>>v>>a>>b;
		gv[(int)u].push_back({{v,0},{a,b}});
	}
	double l=0,r=2e9;
	for(int T=1;T<=100;T++){
		double mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	cout<<fixed<<setprecision(10)<<l;
}
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc324_f)
### 题解
求一个比率最大的问题，显然是 01 分数规划，考虑二分（雾。

设当前要检查的数为 $x$，设从 $1$ 到 $n$ 的一条路径美丽值和花费分别为 $b,c$。那么 $x$ 可能为答案，当且仅当存在 $b,c$ 使得 $\dfrac{b}{c}\ge x$，变换可得 $b-x\times c \ge 0$。也就是说，存在 $1$ 到 $n$ 的路径，每条边的权值为 $b-x\times c$，且路径上权值之和有大于等于 $0$ 的方案。

一定不要用 SPFA！我在这里死了！

关于 SPFA，他死了。
### 代码
```cpp
#pragma GCC optimize ("O2")
#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,-1,0,0},dy[] = {0,0,1,-1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		p >>= 1;
	}
	return ans;
}
const int N = 200010;
const double EPS = 1e-12;
int n,m;
vector <pair <int,PII> > g[N];
double f[N];
bool st[N];
bool check (double x) {
	for (int i = 1;i <= n;i++) f[i] = -9e18;
	f[1] = 0;
    for (int i = 1;i <= n - 1;i++) {
    	for (auto [v,w] : g[i]) {
    		auto [b,c] = w;
    		f[v] = max (f[v],f[i] + b - x * c);
		}
	}
    return f[n] >= 0;
}
int main () {
	ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0);
	cin >> n >> m;
	while (m--) {
		int u,v,b,c;
		cin >> u >> v >> b >> c;
		g[u].push_back ({v,{b,c}});
	}
	double l = 0,r = 1e5;
//	cout << check (0.75) << endl;
//	for (int i = 1;i <= n;i++) cout << dist[i] << ' ';
//	cout << endl;
	for (int i = 1;i <= 100;i++) {
		double mid = (l + r) / 2;
		if (check (mid)) l = mid;
		else r = mid;
	}
	cout << fixed << setprecision (11) << l << endl;
	return 0;
}
```

---

## 作者：OldDriverTree (赞：0)

# Solution

由于题目要求两个和的比的最大值，考虑 01 分数规划

二分答案后转化成判断 $1\rightarrow n$ 是否存在一条路径满足 $\sum b-xc\ge 0$

由于题目保证每条边 $u_i<v_i$，可以发现这就是一个 DAG，图上 DP 求最长路即可

时间复杂度 $O((n+m)\log V)$

# Code
```c++
#include<bits/stdc++.h>
#define v to[i]
#define w val[i]-x*Val[i]
using namespace std;
const int N=2e5+1;
int tot,head[N],nxt[N];
int to[N],val[N],Val[N];
int n,m,deg[N],t[N];
double dis[N];

void add(int x,int y,int z,int Z) {
	to[tot]=y,val[tot]=z,Val[tot]=Z;
	nxt[tot]=head[x],head[x]=tot++;
}
bool check(double x)
{
	for (int i=1;i<=n;i++)
	deg[i]=t[i],dis[i]=-1e9;
	dis[1]=0;
	
	for (int u=1;u<=n;u++)
		for (int i=head[u];~i;i=nxt[i])
			dis[v]=max(dis[v],dis[u]+w);
	
	return dis[n]>=0;
}
int main()
{
	memset(head,-1,sizeof head);
	scanf("%d%d",&n,&m);
	while (m--) {
		int x,y,z,Z;
		scanf("%d%d%d%d",&x,&y,&z,&Z);
		add(x,y,z,Z),t[y]++;
	}
	double l=0,r=1e9;
	for (int i=0;i<100;i++)
	{
		double mid=(l+r)/2;
		if (check(mid) ) l=mid;
		else r=mid;
	}
	printf("%.16lf",l);
	return 0;
}
```

---

## 作者：DerrickLo (赞：0)

看见答案的式子很容易想到分数规划。

所以我们先二分答案 $mid$，然后把每条边的权值定义成 $b_i-mid\times c_i$，然后由于是 DAG，我们可以使用满足拓扑序的 dfs 求出 $1$ 到 $n$ 的最长路，注意要判断重边。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,u[200005],v[200005],b[200005],c[200005],vis[200005];
double dis[200005];
vector<pair<int,double> >ve[200005];
queue<int> q;
void dfs(int u){
	if(u==n)dis[u]=0;
	if(vis[u])return;
	vis[u]=1;
	for(auto v:ve[u]){
		dfs(v.first);
		dis[u]=max(dis[u],dis[v.first]+v.second);
	}
}
bool check(double mid){
	for(int i=1;i<=n;i++)ve[i].clear();
	memset(dis,-0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	for(int i=1;i<=m;i++)ve[u[i]].push_back({v[i],(double)b[i]-mid*c[i]});
	dfs(1);
	return dis[1]>0;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>u[i]>>v[i]>>b[i]>>c[i];
	double l=0,r=1e9,ans;
	while(r-l>1e-10){
		double mid=(l+r)/2.0;
		if(check(mid))l=mid,ans=mid;
		else r=mid;
	}
	printf("%.10lf",ans);
	return 0;
}
```

---

