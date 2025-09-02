# Water Distribution

## 题目描述

在一个二维平面上有 $N$ 个城市，第 $i$ 个城市的坐标是 $(x_i,y_i)$，一开始拥有的水量是 $a_i$。

现在你可以从一个城市向另一个城市运送任意数量的水，但水在运输过程中会有损耗，具体而言如果从 $x$ 城市运 $l$ 水到 $y$ 城市，最终 $y$ 城市得到的水量是 $\max\{0,l-\operatorname{dis}(x,y)\}$，其中 $\operatorname{dis}(x,y)$ 指 $x$ 和 $y$ 城市间的欧几里得距离。你可以多次进行这个操作。

你要使最终水量最少的城市水量尽量多，求这个值。

## 说明/提示

数据范围：$1 \le N \le 15$，$0 \le x_i, y_i, a_i \le 10^9$。

样例一解释：最优解是从第一个城市向第二个城市输送 $3.5$ 升的水。操作后，第一个和第二个城市的水量均为 $6.5$ 升，第三个城市的水量为 $8$ 升。

## 样例 #1

### 输入

```
3
0 0 10
2 0 5
0 5 8```

### 输出

```
6.500000000000```

## 样例 #2

### 输入

```
15
335279264 849598327 822889311
446755913 526239859 548830120
181424399 715477619 342858071
625711486 448565595 480845266
647639160 467825612 449656269
160714711 336869678 545923679
61020590 573085537 816372580
626006012 389312924 135599877
547865075 511429216 605997004
561330066 539239436 921749002
650693494 63219754 786119025
849028504 632532642 655702582
285323416 611583586 211428413
990607689 590857173 393671555
560686330 679513171 501983447```

### 输出

```
434666178.237122833729```

# 题解

## 作者：_Deer_Peach_ (赞：6)

题意已经够简洁了不再赘述。

思路：

首先分析题意可得两个结论：
1. 最终的答案肯定是相同的或者趋于相同的；
2. 送水的路线形成的图是无环的，也就是一棵树，那么整个图就可能是森林。

接下来给出证明：

结论一：如果答案相差很大，那么可以通过再次送水（除非路线太长）使水最少的城市答水更多。

结论二：如果有环则说明送水后还有多余的水可以送回原城市，那么这样消耗的水更多了，所以送水时不会有水送回原城市，所以整个送水的路线形成的是森林。

根据两条结论我们再想，可以想到，一个点集（即一次送水送到的城市）中的每个点的水都一样。

因为 $n$ 很小，所以我们能想到用状压 DP 来做。怎么表示状态不必多说，二进制下 $1$ 表示选反之不选，定义 $c_i$ 表示状态为 $i$ 时，这个子集内最小的送水路径之和，$dp_i$ 表示状态为 $i$ 时所送过水的城市的水最少的最大值。

设一个子集内送水路线的最小值为 $c_i$，水的总和为 $W$，子集点的数量为 $k$。

那么我们先预处理出不同子集的 $c_i$，然后再枚举不同状态，先计算 $c_i$ 是否小于 $W$。如果是，则该状态下可以直接送水，最少的水的最大值就是 $\frac{W-c_i}{k}$。

然后在该状态的基础上分割成不同子集再转移，将 $dp_i$ 与两个子集的较小值取较大值。一个子集状态为 $j$，那么另一个子集状态为 $i-j$，可得转移方程 $dp_i \gets \max(dp_i,\min(dp_j,dp_{i-j}))$。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int N=20;
const double Max=0x3f3f3f3f3f3f3f3f;
int n;
struct node{
	double x,y,w;
}ns[N];
double c[(1<<N)];
double dp[(1<<N)];
double dis[N][N];
inline double num(int x){//求子集大小
	double res=0;
	while(x){
		res+=(x%2==1?1:0)*1.0;
		x/=2;
	}
	return res;
}
inline void DP(int x){//分割成两个子集
	for(int i=x;i;i=(i-1)&x){
		dp[x]=max(dp[x],min(dp[i],dp[x-i]));
	}
	return;
}
signed main(){
    IOS;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>ns[i].x>>ns[i].y>>ns[i].w;
	}
	for(int i=0;i<n;i++){//两点距离
		for(int j=0;j<n;j++){
			double xx=ns[i].x-ns[j].x;
			double yy=ns[i].y-ns[j].y;
			dis[i][j]=sqrt(xx*xx+yy*yy);
		}
	}
	for(int i=0;i<(1<<n);i++)c[i]=Max;
	for(int i=0;i<n;i++)c[(1<<i)]=0;
	for(int i=1;i<(1<<n);i++){//预处理子集内最小送水长度
		for(int j=0;j<n;j++){
			if(((i>>j)&1)==0)continue;
			for(int k=0;k<n;k++){
				if(((i>>k)&1)==1)continue;
				c[i+(1<<k)]=min(c[i+(1<<k)],c[i]+dis[j][k]);
			}
		}
	}
	for(int i=1;i<(1<<n);i++){//枚举状态
		double cnt=0;
		for(int j=0;j<n;j++){//求子集内水总和
			if((i>>j)&1)cnt+=ns[j].w;
		}
		if(cnt>c[i])dp[i]=(cnt-c[i])/num(i);//计算平均值
		DP(i);
	}
	printf("%.12Lf",dp[(1<<n)-1]);
	return 0;
}
```
[记录](https://atcoder.jp/contests/cf16-exhibition-final/submissions/65624147)。

---

## 作者：Provicy (赞：4)

$\text{Problem}:$[Water Distribution](https://atcoder.jp/contests/cf16-exhibition-final-open/tasks/cf16_exhibition_final_e)

$\text{Solution}:$

- 记 $F(S)$ 表示点集 $S$ 的最优解。考虑存在四个点 $a,b,c,d$，并需要做 $a\rightarrow b$ 和 $c\rightarrow d$ 的操作，那么 $a,b$ 与 $c,d$ 之间是独立的，也就是说 $F(\{a,b,c,d\})=\min\{F(\{a,b\}),F(\{c,d\})\}$。

- 考虑有两个操作 $i\rightarrow j$ 和 $i\rightarrow k$，则可以比较 $i\rightarrow j \rightarrow k$ 和分别做 $i\rightarrow j$ 和 $i\rightarrow k$ 取总路径最短的方案。

这启发我们可以把需要操作的两个点 $i,j$ 放在一个连通块中。那么问题转化为对每个连通块求最优解。

对于一个连通块，设初始总水量和为 $W$，总操作路径长度为 $B$，总点数为 $K$，则最优解上界为 $G=\cfrac{W-B}{K}$。首先，使得 $B$ 最小。显然，对连通块建出完全图后，求出最小生成树即可。接下来考虑对于任意情况都可以使最优解达到上界。随便钦定一个节点为最小生成树根，那么叶子节点 $x$ 与其父亲节点 $y$ 有以下关系：

- $a_{x}\geq G$，将 $a_{x}-G$ 转移到 $y$ 节点即可。
- $a_{x}<G$，此时把 $x$ 看作根节点，可以将 $G-a_{x}$ 转移到 $y$，然后转移给 $x$ 即可。

故一个连通块的答案就是 $G$。那么对于所有点集，预处理出点集作为一个连通块的答案，这一部分的时间复杂度为 $O(2^{n}n^{2}\log n)$。然后枚举子集 $dp$，这一部分的时间复杂度为 $O(3^{n})$。

$\text{Code}:$

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define int long long
#define ri register
#define mk make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define is insert
#define es erase
using namespace std; const int N=1010;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
	return s*w;
}
int n;
int X[N],Y[N],a[N],p[N];
double F[(1<<16)+5],W[(1<<16)+5],B[(1<<16)+5],dp[(1<<16)+5];
struct Node { int u,v; double w; }e[N]; int tot;
inline double Dis(int i,int j)
{
	return sqrt(1.0*(X[i]-X[j])*(X[i]-X[j])+1.0*(Y[i]-Y[j])*(Y[i]-Y[j]));
}
inline bool cp(Node x,Node y) { return x.w<y.w; }
struct Uni
{
	int f[N];
	inline void Init()
	{
		for(ri int i=1;i<=n;i++) f[i]=i;
	}
	inline int Find(int x) { return f[x]^x?f[x]=Find(f[x]):x; }
}A;
signed main()
{
	n=read();
	for(ri int i=1;i<=n;i++) X[i]=read(), Y[i]=read(), a[i]=read();
	for(ri int i=1;i<(1ll<<n);i++)
	{
		int cnt=0;
		for(ri int j=1;j<=n;j++) if((i>>(j-1))&1) p[++cnt]=j, W[i]+=1.0*a[j];
		if(cnt==1)
		{
			F[i]=W[i];
			continue;
		}
		tot=0;
		for(ri int j=1;j<=cnt;j++)
		for(ri int k=j+1;k<=cnt;k++)
		e[++tot]=(Node){p[j],p[k],Dis(p[j],p[k])};
		sort(e+1,e+1+tot,cp);
		A.Init();
		for(ri int j=1;j<=tot;j++)
		{
			int fx=A.Find(e[j].u), fy=A.Find(e[j].v);
			if(fx==fy) continue;
			A.f[fx]=fy, B[i]+=e[j].w;
		}
		F[i]=max(0.0,(W[i]-B[i])/cnt);
	}
	dp[0]=1e18;
	for(ri int i=1;i<(1ll<<n);i++)
	{
		for(ri int j=i;j;j=i&(j-1))
		{
			int k=i^j;
			dp[i]=max(dp[i],min(F[j],dp[k]));
		}
	}
	printf("%.12lf\n",dp[(1ll<<n)-1]);
	return 0;
}
```

---

## 作者：_Cheems (赞：1)

首先 $\max(0,l-dis(x,y))$ 不太好看，不妨放宽限制，不与 $0$ 取 $\max$，这显然不会有影响：现答案肯定不优于原答案，又因为最优情况中肯定不会有 $l\le dis(x,y)$，所以包含最优解。

然后让传递水的两个城市 $x,y$ 连无向边，权值为负就是 $y$ 向 $x$ 传水。不可能有环，因为可以把环中最大的边去掉，让那份水沿着更小的路径传递。

所以最终构成森林，对于一棵树 $T$，答案上界就是 $\frac{\sum a-\sum e}{|T|}$，也就是平均数，而且可以达到该上界，首先随便传水让每个点都到达平均数，然后若一条边被经过多次那么可以直接合并为一次。容易发现，该过程中不会有 $a$ 变成负数（当然是在原来合法的情况下）。

看到 $n\le 16$ 直接状压，先暴力枚举每个连通块，然后 $\min(\sum e)$ 就是最小生成树，最后做一次 dp 合并为森林。

复杂度 $O(2^nn^2\log n^2+3^n)$，可以通过。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define db double
const int N = 16;
const db inf = 1e18;
int n, fa[N], m;
db x[N], y[N], v[N], f[1 << N], g[1 << N];
struct edge{int u, v; db w;} e[N * N + 5];

inline int find(int u) {return fa[u] == u ? u : fa[u] = find(fa[u]);}
inline db dist(int a, int b) {return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));}
signed main(){
	cin >> n;
	for(int i = 0; i < n; ++i) scanf("%lf%lf%lf", &x[i], &y[i], &v[i]); 
	for(int S = 1; S < 1 << n; ++S){
		m = 0;
		for(int i = 0; i < n; ++i)
			if((S >> i) & 1){
				fa[i] = i, f[S] += v[i];
				for(int j = i + 1; j < n; ++j)
					if((S >> j) & 1)
						e[++m] = {i, j, dist(i, j)};
			}
		sort(e + 1, e + 1 + m, [](edge A, edge B){return A.w < B.w;});
		for(int i = 1; i <= m; ++i){
			int fu = find(e[i].u), fv = find(e[i].v);
			if(fu != fv) fa[fu] = fv, f[S] -= e[i].w;
		}
		f[S] /= __builtin_popcount(S);
	}
	g[0] = inf;
	for(int S = 1; S < 1 << n; ++S)
		for(int S2 = S; S2; S2 = (S2 - 1) & S)
			g[S] = max(g[S], min(g[S ^ S2], f[S2]));
	printf("%.9lf", g[(1 << n) - 1]);
	return 0;
}
```

---

## 作者：0Io_oI0 (赞：1)

这道题目我们有 $3$ 个结论：

1. 在最优情况下，最后所有的点上的水量都是一样的。因为水多的可以向水少的运水。
2. 不存在间接运水的情况，这个由三角形的三边关系可以得到。
3. 最优运输路径，最后是树形的。

我们在不漏情况的条件下，枚举所有的树形。

接下来就是动态规划了！

很明显这道题目需要使用状压 dp。

我们让 $dp_{i}$ 表示在子集 $i$ 状态下的最小值的最大值。

而我们的动态规划的答案是 $dp_{2^n-1}$。

对于每个子集 $i$ 我们做整体和分割处理，整体处理就是把子集里的所有城市看成一个连通体，如果我们设总水量为 $S$ 城市数量为 $M$ 那么最小值最大化就是 $\frac{S-MST}{M}$ 其中 $MST$ 代表这个子集的最小生成树。

然后分割处理就是将子集 $i$ 分成两个不相交的子集 $j$ 和 $i\oplus j$ 我们分别计算 $dp_j$ 和 $dp_{i\oplus j}$ 然后与其他方式进行比较就好了。

上代码！

```cpp
#include<bits/stdc++.h>
#define I using
#define AK namespace
#define IOI std
#define i_ak return
#define ioi  0
#define i_will signed
#define ak main
#define IMO ()
#define int long long
I AK IOI;
const long double inf=1e18;
int a[20],b[20],c[20],n;
long double d[20][20],t[1<<16],dp[1<<16]; 
int counter(int x){
    int ans=0;
    while(x){
        ans+=x&1;
        x/=2;
    }
    return ans;
}
i_will ak IMO{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i]>>c[i];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)d[i][j]=sqrt(1ll*(a[i]-a[j])*(a[i]-a[j])+1ll*(b[i]-b[j])*(b[i]-b[j]));
    for(int i=0;i<(1<<n);i++)t[i]=inf;
    for(int i=1;i<=n;i++)t[1<<(i-1)]=0;
    for(int i=1;i<(1<<n);i++)for(int j=1;j<=n;j++)if(i>>(j-1)&1)for(int k=1;k<=n;k++)if(!(i>>(k-1)&1))t[i|(1<<(k-1))]=min(t[i|(1<<(k-1))],t[i]+d[j][k]);
    for(int i=1;i<(1<<n);i++){
        long double w=0;
        for(int j=1;j<=n;j++)if(i>>(j-1)&1)w+=c[j];
        if(w>t[i])dp[i]=(w-t[i])/counter(i); 
        for(int t=i&(i-1);t!=0;t=(t-1)&i)dp[i]=max(dp[i],min(dp[t],dp[i^t]));
    }
    printf("%.10Lf\n",dp[(1<<n)-1]); 
    i_ak ioi;
}
```
亲测可过，请勿抄袭！

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_cf16_exhibition_final_e)

**题目大意**

> 给定平面上 $n$ 个点 $p_1\sim p_n$，第 $i$ 个点上有水量 $w_i$，可以。
>
> 从处取 $p_i$ 处取 $v$ 容量的水运送到 $p_j$，会使得 $w_j$ 增加 $\max(0,v-\mathrm{dis}(p_i,p_j))$，$\mathrm{dis}$ 为欧几里得距离。
>
> 最大化 $\min w_i$。
>
> 数据范围：$n\le 16$。

**思路分析**

把所有的操作对应的边 $(i,j)$ 都写出来。

容易发现对于一个连通块，我们可以把他们内部的水量任意排列：取出一棵生成树，然后算出每条边的流量，容易发现一定有一种合法的操作顺序。

那么对于一个连通块 $S$，我们会让内部的总水量 $W$ 减少 $T$，$T$ 是 $S$ 的平面最小生成树大小，最优方法一定是每个点平均水量，即对答案的贡献为 $\dfrac{W-T}{|S|}$。

然后对于不同的连通块，枚举子集合并即可。

时间复杂度 $\mathcal O(3^n+n^22^n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ld long double
#define pc __builtin_popcount
using namespace std;
const ld inf=1e18;
int n,x[16],y[16],z[16];
ld d[16][16],c[1<<16],f[1<<16];
signed main() {
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d%d%d",&x[i],&y[i],&z[i]);
	for(int i=0;i<n;++i) for(int j=0;j<n;++j) {
		d[i][j]=sqrt(1ll*(x[i]-x[j])*(x[i]-x[j])+1ll*(y[i]-y[j])*(y[i]-y[j]));
	}
	for(int s=0;s<(1<<n);++s) c[s]=inf;
	for(int i=0;i<n;++i) c[1<<i]=0;
	for(int s=1;s<(1<<n);++s) for(int i=0;i<n;++i) if(s>>i&1) {
		for(int j=0;j<n;++j) if(!(s>>j&1)) {
			c[s|1<<j]=min(c[s|1<<j],c[s]+d[i][j]);
		}
	}
	for(int s=1;s<(1<<n);++s) {
		ld w=0;
		for(int i=0;i<n;++i) if(s>>i&1) w+=z[i];
		if(w>c[s]) f[s]=(w-c[s])/pc(s);
		for(int t=s&(s-1);t;t=(t-1)&s) f[s]=max(f[s],min(f[t],f[s^t]));
	}
	printf("%.20Lf\n",f[(1<<n)-1]);
	return 0;
}
```

---

## 作者：RedreamMer (赞：0)

[$\huge\texttt{AT2230}$](https://www.luogu.com.cn/problem/AT2230)

[$\texttt{In my cnblogs}$](https://www.cnblogs.com/RedreamMer/p/14471240.html)

模拟赛出这题，结束后恍然大悟，充分证明我的垃圾。

状压 DP 好题。

## 思路

（以下“集合的权值"意义均为题目中所求的最大值）

发现题目中给定的 $N$ 很小，考虑搜索或状压。

尝试使用状压。

对于一个集合，它之中所有节点的剩余水量相同，权值就是其所有节点剩余水量的最大值，还有可能由多个不相交子集的构成，权值就是多个子集权值的最小值。

对于某个集合的所有结点的剩余水量都相等，考虑如何流通传递水量。

+ 结论 1 ：流通传递的水量经过的边构成的一定是一颗树。

	证明：首先必然是一整个连通块，若不是，则会被第二种情况考虑，其次，若边构成了一个环，则肯定能隐去一条最大边，剩余的的传递关系仍然成立。

+ 结论 2 ：每条树边最多被经过一次
	证明：类似于网络流的反向边，如果一条边正反经过多次，是可以抵消一部分的，而多次同方向经过可以叠加。

用 $dp[i]$ 表示集合状态为 $i$ 最大的值。

计算两种情况的贡献，通过结论1、2，可知第一种值为 $\frac{suma_i-MST}{V}$ ( $V$ 是点数，$MST$ 是集合最小生成树边权值和)，第二种通过枚举子集得到 $dp[i]=\max (dp[j],dp[i\oplus j])$。

预处理所有集合的最小生成树和第一种情况的值，时间复杂度 $O(2^nn^2)$ ，第二种情况更新 DP 通过枚举子集时间复杂度 $O(3^n)$。

注意精度，好像不太卡。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define LD long double
const int N = 15;
inline int read()
{
    int s = 0;
    register bool neg = 0;
    register char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        neg |= (c == '-');
    for (; c >= '0' && c <= '9'; s = s * 10 + (c ^ 48), c = getchar())
        ;
    s = (neg ? -s : s);
    return s;
}

int a;
LD x[N + 1], y[N + 1], s[N + 1], dis[N + 1], val[(1 << N)], valt[1 << N], sum[1 << N], dp[1 << N];
bool vis[N + 1], vist[N + 1];

inline LD dist(LD _x, LD _y, LD xx, LD yy) { return sqrt((_x - xx) * (_x - xx) + (_y - yy) * (_y - yy)); }

inline LD prim(int n)
{
    for (int i = 0; i <= a; i++)
        dis[i] = 1e100;
    memset(vist, 0, sizeof(vist));
    for (int i = 1; i <= a; i++)
        if (vis[i])
        {
            dis[i] = 0;
            break;
        }
    for (int i = 1; i < n; i++)
    {
        int mn = 0;
        for (int j = 1; j <= a; j++)
            if (vis[j] && !vist[j] && dis[j] < dis[mn])
                mn = j;
        vist[mn] = 1;
        for (int j = 1; j <= a; j++)
            if (vis[j] && !vist[j])
            {
                LD tmp = dist(x[mn], y[mn], x[j], y[j]);
                if (dis[j] > tmp)
                    dis[j] = tmp;
            }
    }
    LD res = 0;
    for (int i = 1; i <= a; i++)
        if (vis[i])
            res += dis[i];
    return res;
}

signed main()
{
    a = read();
    const int mx = (1 << a);
    for (int i = 1; i <= a; i++)
        scanf("%Lf %Lf %Lf", &x[i], &y[i], &s[i]);
    for (int i = 1; i < mx; i++)
    {
        memset(vis, 0, sizeof(vis));
        for (int j = 1; j <= a; j++)
            if (i & (1 << (j - 1)))
                vis[j] = 1, sum[i]++, valt[i] += s[j];
        val[i] = prim(sum[i]);
    }
    for (int i = 1; i < mx; i++)
    {
        dp[i] = (valt[i] - val[i]) / sum[i];
        for (int j = (i & (i - 1)); j; j = ((j - 1) & i))
            dp[i] = max(dp[i], min(dp[j], dp[i ^ j]));
    }
    printf("%.10Lf", dp[mx - 1]);
    return 0;
}
```

---

## 作者：AsunderSquall (赞：0)

模拟赛出这题，最后 10 min 调才调出来，充分说明我的垃圾。

# 题解
我不知道这题官方题解做法的复杂度是怎样的，这里提供一个 $O(3^n \times n)$ 的屑方法。  

显然最终的答案是把整张图分为若干个集合，其中每个集合的水量都是一样的。  
考虑进行一次搬水，就将两个点之间连一条边，那么图被分成了若干个联通块。  
枚举每一个点集，算出这样的联通块最终相等的水量是多少。  

接下来考虑怎么计算最终相等的水量。  
显然，既然要求这个点集是联通块，那么任意两点之间可以自由传输水。 

------

下面证明一定可以在 经过路径长度在总边长数的距离内 将所有水量变成一样的。  
我们随便从一个点出发，构建一棵 dfs 树。  
假设我们目标使所有点的水量都变成 $x$。  
自深度大的点往深度小的点跳。假如当前节点比 $x$ 小，就从父亲那里搬一部分水来，否则就往父亲那里送水。  
我们取合适的 $x$ 可以使根节点一定最终为 $x$。  
这样每条路径只被经过了 $1$ 次。  
然后我们调整一下时间顺序，考虑到最终 $x>0$（否则 没有讨论的必要），那么一定存在方法使得任何时间没有节点的水量 $<0$。  
具体来说，先从底层往上把所有搬给父亲的水都搬去，然后再把父亲给儿子搬的水搬去。  

为什么这样一定是对的？  
我们考虑其实每个点都是加一些数，减一些数，最终变成某个数。那么我们这样做相当于先把加了的数给加了，再减去，这样一定不会变成负数。  

---

其实上面这一段奇怪的证明 感性理解很快，但是理性证明就是说得不太清楚，是我的问题。  

然后求出最短路径长度掏出一个最小生成树就行了。  
那么 $x=\dfrac{\sum_{i \in S} a_i-MST}{|S|}$  
我们对于每个集合把它存下来，设为 `dp[s]`。  

------
接下来，我们对于每个集合，进行更新答案。  
直接掏出转移式子 
$$dp[S]=\max_{T\subset S} \min(dp[T],dp[\complement_ST])$$  
解释一下，我们之前已经更新了 $S$ 的子集为最优解（即可以划分为多个集合），然后如果将 $dp[S]$ 拆分开来更加优秀，那么这样枚举即可。  
然后分析一下复杂度  
$$\sum_{S}\sum_{T \subset S}1=\sum_{S}2^{|S|}=\sum_{i=0}^n {n \choose i}2^i=\sum_{i=0}^n {n \choose i}2^i1^{n-i}=(2+1)^n=3^n$$  
由于我是屑，所以枚举子集的复杂度变成了 $|S|\times 2^{|S|}$，所以总复杂度多出了一只 $n$。  
其实复杂度只差这枚举子集，然后就比别人慢了 15 倍。  

答案即为 $dp[\{1,2,\cdots,n\}]$。

代码：（可能需要加火车头）
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
#define ri register signed
#define rd(x) x=read()
#define mp make_pair
#define lb lower_bound
using namespace std;
const int N=16;
const int M=40000;
const int maxn=5e6+5;
const int mod=1e9+7;
const int inf=0x3f3f3f3f3f3f3f3f;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if (ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline int ksm(int x,int y=mod-2,int z=mod){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}

int n,P;
double ans;
int b[N];
int x[N],y[N],a[N];
double dp1[M],dp[M],ddd[M];
struct Edge{int u,v;double w;};
Edge e[M];
double dis(int i,int j){return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));}
bool cmp(Edge i,Edge j){return i.w<j.w;}
int fa[N];
int getfa(int x){if (x==fa[x]) return x;return fa[x]=getfa(fa[x]);}
int get(int T,int S)
{
	int t=0;
	for (int i=0;i<n;i++) 
	{
		if (S>>i&1)
		{
			if ((T>>t)&1^1)
			S^=1<<i;
			t++;
		}
	}
	return S;
}
signed main()
{
	rd(n);P=(1<<n)-1;
	for (int i=1;i<=n;i++) {rd(x[i]);rd(y[i]);rd(a[i]);}

	for (int S=0;S<(1<<n);S++)
	{
		double tot=0,tmp=0;
		int T=0,t=0,tt=0;
		for (int i=1;i<=n;i++) if (S>>(i-1)&1) tot+=a[i],b[++t]=i;
		//以下为 MST 板子
		for (int i=1;i<=t;i++) for (int j=i+1;j<=t;j++) e[++T]=(Edge){i,j,dis(b[i],b[j])};
		sort(e+1,e+T+1,cmp);
		for (int i=1;i<=t;i++) fa[i]=i;
		for (int i=1;i<=T;i++)
		{
			int u=e[i].u,v=e[i].v;
			double w=e[i].w;
			u=getfa(u);v=getfa(v);
			if (u==v) continue;
			tmp+=w;fa[u]=v;tt++;
			if (tt==t) break;
		}
		//以上为 MST 板子
		dp[S]=(tot-tmp)/t;
	}
	for (int S=1;S<(1<<n);S++)//由于 S 的子集一定小于等于 S，所以这样顺序枚举就能保证 S 的子集比 S 先处理
	{
		int t=0;
		for (int i=0;i<n;i++) if (S>>i&1) t++;
		for (int T=1;T<(1<<t);T++)
		{
			int K=get(T,S);
			dp[S]=max(dp[S],min(dp[K],dp[S^K]));
		}
	}
	printf("%.10lf\n",dp[(1<<n)-1]);
}
```

---

