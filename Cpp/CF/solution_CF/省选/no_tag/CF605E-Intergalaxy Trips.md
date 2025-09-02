# Intergalaxy Trips

## 题目描述

The scientists have recently discovered wormholes — objects in space that allow to travel very long distances between galaxies and star systems.

The scientists know that there are $ n $ galaxies within reach. You are in the galaxy number $ 1 $ and you need to get to the galaxy number $ n $ . To get from galaxy $ i $ to galaxy $ j $ , you need to fly onto a wormhole $ (i,j) $ and in exactly one galaxy day you will find yourself in galaxy $ j $ .

Unfortunately, the required wormhole is not always available. Every galaxy day they disappear and appear at random. However, the state of wormholes does not change within one galaxy day. A wormhole from galaxy $ i $ to galaxy $ j $ exists during each galaxy day taken separately with probability $ p_{ij} $ . You can always find out what wormholes exist at the given moment. At each moment you can either travel to another galaxy through one of wormholes that exist at this moment or you can simply wait for one galaxy day to see which wormholes will lead from your current position at the next day.

Your task is to find the expected value of time needed to travel from galaxy $ 1 $ to galaxy $ n $ , if you act in the optimal way. It is guaranteed that this expected value exists.

## 说明/提示

In the second sample the wormhole from galaxy $ 1 $ to galaxy $ 2 $ appears every day with probability equal to $ 0.3 $ . The expected value of days one needs to wait before this event occurs is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF605E/5fb08847eb4bc2e36c3daebb706ac196eed82508.png).

## 样例 #1

### 输入

```
3
100 50 50
0 100 80
0 0 100
```

### 输出

```
1.750000000000000
```

## 样例 #2

### 输入

```
2
100 30
40 100
```

### 输出

```
3.333333333333333
```

# 题解

## 作者：SDNetFriend (赞：27)

## CF605E Intergalaxy Trips 题解

**期望好题（确信）**

总之就是，期望做得太少，人太菜，一上午做不出来。

#### 题意不再赘述啦

[CF605E Intergalaxy Trips](https://www.luogu.com.cn/problem/CF605E)

#### 朴素分析

首先有个思路，如果我们设 $f_i$ 为 $i\to n$ 的期望耗时，那么当我们转移时，我们**一定不会找比当前点更劣的点转移**。因为那样就是跑个自环也比跑那个劣的点划算，所以转移的时候只考虑比当前点优的点即可。

问题是自己不知道，别的也不知道，怎么判断？这个就要看转移方程了。

#### 状态转移

因为会选择最优策略，所以到了某个点，采取某个状态的唯一可能就是**比自己优的状态取不到了**，这个东西是可以描述出来的。而且如果所有状态都取不到那就自环，这是最劣的转移，不过也要考虑。于是我们的转移方程：
$$
f_i=\sum_{j}^{f_j<f_i}p_{i,j}f_j\prod_k^{f_k<f_j}(1-p_{i,k})+f_i\prod_{j}^{f_j<f_i}(1-p_{i,j})+1
$$
移项然后除一下可以得到：
$$
f_i=\frac{\sum_{j}^{f_j<f_i}p_{i,j}f_j\prod_k^{f_k<f_j}(1-p_{i,k})+1}{1-\prod_{j}^{f_j<f_i}(1-p_{i,j})}
$$

#### 实现思路

首先，对于上式中的更新 $i$ 的 $j$，显然是考虑的越多**值是单调不增的**，不然你也不会用那个点去转移。然后注意，**一个点是不可能比将它转移的点更优**的，因为要多走一步。

这说明了什么？当一个点是所有已知状态中最小的，那么它就不会再被别的状态转移了，这个性质很类似 Dijkstra ，所以我们可以每一轮选择最小的那个没有进行过转移的点，将其它没有进行过转移的点更新一下，类似朴素的 $O(n^2)$ 的 Dijkstra ，这样我们就能得到答案。

注意这里“转移”指的是**用当前点去更新别的点的答案**，即对于别的点 $i$ 来说，它相当于公式里面的 $j$。 

#### 实现细节

我们可以分别维护每个点的 $f_i,g_i,h_i$，$f_i$ 与上文含义相同，三者关系可表示为：
$$
f_i=\frac{g_i}{1-h_i}
$$
而且更有趣的是，当我们**用 $j$ 更新 $i$ 时**（注意不是任意时刻），还没被 $j$ 更新过的 $h_i$ 恰好等于 $\prod_k^{f_k<f_j}(1-p_{i,k})$，也就是每一轮更新我们可以这么写：

$g_i+=p_{i,j}f_jh_i$，$h_i*=1-p_{i,j}$，$f_i=\frac{g_i}{1-h_i}$ 

要注意转移顺序。

#### 贴代码

```cpp
#include <bits/stdc++.h>
#define lint long long
#define rint register int
using namespace std;
inline int read(){
	char c;int f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
const int N=1e3+5,inf=1e9;
double p[N][N],f[N],g[N],h[N];
//最后的f才是答案,其为g/(1-h) 
int q[N],tot,n;//q实质上是拓扑序排列
bool vis[N];//判断是否在队列里面 
inline void upd(){//用队头来更新 
	int j=q[tot];
	for(rint i=1;i<=n;++i){
		if(vis[i])continue;
		g[i]+=f[j]*p[i][j]*h[i];
		h[i]*=1-p[i][j];
		f[i]=g[i]/(1-h[i]);
	}
}
inline void solve(){
	for(rint i=1;i<n;++i)
		f[i]=g[i]=h[i]=1;
	f[n]=0;h[n]=1;
	//恰好都是1 
	vis[n]=true;
	q[++tot]=n;upd();
	while(tot<n){
		int id;double v=inf;
		for(rint i=1;i<=n;++i)
			if(!vis[i]&&f[i]<v)
				v=f[i],id=i;
		vis[id]=true;
		q[++tot]=id;upd();
	}
}
int main(){
	n=read();
	if(n==1){return puts("0"),0;}
	for(rint i=1;i<=n;++i)
		for(rint j=1;j<=n;++j)
			p[i][j]=read()/100.0;
	solve();
	printf("%.8lf",f[1]);
	return 0;
}


```


---

## 作者：小周猪猪 (赞：21)

## $\mathrm{Problem}$
- $n$ 个点的有向完全图。
- $i \to j$ 的边每天出现的概率均为 $p_{i,j}$，若 $i = j$，有 $p_{i,j} = 1$。
- 每天选择一条存在的出边走过去。
- 求最优策略下从 $1$ 到 $n$ 的期望天数。
- $n \le 10^3$。

---
## $\mathrm{Solution}$
~~搞了一天的期望神题~~ 

我们设 $E_x$ 表示节点 $x$ 接下来要到节点 $n$ 的期望天数。

有一些显然但很重要的结论，就是：
- 节点 $x$ 接下来转移的点一定是当前开放的出边中 $E$ 值最小的一个点。
- 对于若存在 $x,y$ 满足 $E_x<E_y$，则 $x$ 的期望决策点一定不包含$y$。

对于结论2：当 $x$ 已经被若干点更新过了，此时枚举到 $y$ 了，如果你计算了 $y$ 的贡献那么一定会使当前节点 $x$ 的期望值增加，因此 $x$ 一定不会被 $y$ 更新到。

因此我们便有了算法的大致思路：每一次都寻找一个期望值最小的点，并固定这个点的期望值；同时也用这个点的期望值去更新未被更新的期望值。

该算法的思路与Dijkstra算法类似。

考虑如何转移：我们发现若我们要转移节点 $i$，需要保证 $\forall j$ 在$E_j<E_i$的情况下通道是关闭的，因为上面提到贪心的原则是选取期望值最小的节点，且 $i$ 的通道是开的。因此假设已经完成转移的点为$a_1,a_2,...,a_m$且满足$E_1<E_2<...<E_m$。

$$E_i=\sum_{j=1}^{m} E_{a_j}\times p_{i,a_j} \prod_{k=1}^{j-1} (1-p_{i,a_k})$$

观察到我们此时计算的 $E_i$ 仅仅是与 $i$ 相连的通道中至少一条开启时的贡献，可能存在通道一条都不开启的情况。我们发现，通道每条都不开启的概率为$\sum p_{i,j}$,则通道至少开启的概率为$1-\sum p_{i,j}$，则至少一条开启的天数是：$\frac{1}{1-\sum p_{i,j}}$。

因此我们的期望天数就变成了$E_x/(1-\prod_{y}^{E_y<E_x}p_{x,y})$。

则上述转移方程就变成了：
$$E_i=\sum_{j=1}^{m}[E_{a_j}/(1-\prod_{k}^{E_{a_k}<E_{a_j}}p_{a_j,a_k})]\times p_{i,a_j} \prod_{k=1}^{j-1} (1-p_{i,a_k})$$

然后就可以愉快的转移辣

---
## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 2000;

int n;
int vis[N];
double s[N], P[N][N], E[N];

int read(void)
{
	int s = 0, w = 0; char c = getchar();
	while (!isdigit(c)) w |= c == '-', c = getchar();
	while (isdigit(c)) s = s*10+c-48, c = getchar();
	return w ? -s : s;
}

int main(void)
{
	n = read();
	for(int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			P[i][j] = 1.0 * read() / 100.0;
	if (n == 1) return puts("0"), 0;
	vis[n] = 1, E[n] = 0;
	for (int i=1;i<=n;++i) {
		E[i] = 1;
		s[i] = 1 - P[i][n];
	}
	for (int i=1;i<=n;++i)
	{
		int p = 0;
		double Min = 1e18;
		for (int j=1;j<=n;++j) 
			if (vis[j] == 0 && 1.0 * E[j] / (1 - s[j]) < Min) 
				Min = 1.0 * E[j] / (1 - s[j]), p = j;
		vis[p] = 1;
		if (p == 1) return printf("%.15lf\n", Min) * 0;
		for (int j=1;j<=n;++j)
			E[j] += 1.0 * E[p] / (1 - s[p]) * P[j][p] * s[j], s[j] *= 1.0 - P[j][p];
	}
	return 0;
} 
```


---

## 作者：George1123 (赞：20)

## 题解

随便讲讲这题的一种奇怪的做法（是 `CF` 上的最劣解）：

首先式子什么的前人之述备矣。

如果已经求出了 $E_u$ 序列的大小关系，那么算一遍可以轻松 $\Theta(n^2)$。

考虑用一种类似爬山算法的做法求得越来越精确的拓扑序：先随便定一个初始 $E_0(u)$，然后每次把前一次的 $E_{i-1}(u)$ 的顺序当作真实拓扑序，求新的一代 $E_i(u)$。

这样做 $n$ 次肯定是对的，但是由于后一次的结果只依赖于前一次的大小关系，所以其实真实中不需要 $n$ 次就可以得到正确的拓扑序。

所以可以一直跑，直到快要 `TLE` 为止。

---

## 代码


```cpp
//George1123
#include <bits/stdc++.h>
using namespace std;
 
typedef long long i64;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef vector<int> vi;
typedef pair<int,int> pii;
 
#define x first
#define y second
#define sz(a) (int)((a).size())
#define all(a) (a).begin(),(a).end()
#define R(i,n) for(int i=0;i<(n);++i)
#define L(i,n) for(int i=(n)-1;i>=0;--i)
 
constexpr int inf32=0x3f3f3f3f;
constexpr i64 inf64=0x3f3f3f3f3f3f3f3f;

const double eps=1e-15;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cout.precision(12),cout<<fixed;
    
    clock_t s=clock();
    
    int n;
    cin>>n;
    if(n==1) return !(cout<<0<<'\n');
    vector<vector<double>> 
    p(n,vector<double>(n,0));
    R(i,n)R(j,n){
    	int x;
    	cin>>x;
        p[i][j]=x/100.;
    }
 
    vi o(n);
    iota(all(o),0);
    vector<double> d(n,inf64);
    d[n-1]=0;
    while(1.*(clock()-s)/CLOCKS_PER_SEC<1.95){
        sort(all(o),[&]
        (const int &i,const int &j){
            return d[i]<d[j];
        });
        
        vector<double> f(n,0);
        for(const int &u:o){
            if(u==n-1) continue;
            double now=1;
            for(const int &v:o){
                if(d[v]>=d[u]) break;                
                f[u]+=now*p[u][v]*(f[v]+1);
                now*=(1-p[u][v]);
            }
            f[u]=(f[u]+now)/(1-now+eps);
        }
        
        swap(f,d);
    } 
    
    cout<<d[0]<<'\n';
 
    return 0;
}
 
/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?)
    * do smth instead of nothing and stay organized
    * WRITE STUFF DOWN
    * DON'T GET STUCK ON ONE APPROACH
*/ 
```

---

**祝大家学习愉快！**

---

## 作者：devout (赞：14)

**description**

现在有 $n$ 个点的有向完全图，边 $(i,j)$ 出现的概率是 $p_{i,j}$，$p_{i,i}=1$，问从 $1$ 到 $n$ 的最短路的期望长度

假设这个人足够聪明

$n\leq 1000$

**solution**

这道题因为这个人足够聪明，所以他可以对于一个情况动态的做出决定

因为正着推不太好确定还需要几步能到，所以我们考虑从 $n$ 倒着推，设 $E_i$ 表示从 $i$ 走到 $n$ 的答案

考虑 $E_i$ 的计算，对于 $E_i$ 的所有出边 $j$ ，显然只有当所有的 $E_k<E_j$ 的 $(i,k)$ 都没有出现的时候，我们才会考虑往 $j$ 走。所以我们可以推出一个转移

$$E_i=\sum_{j=1}^nE_j\times p_{i,j}\times \prod_{k}^{E_k<E_j}(1-p_{i,k})$$

但是这个转移是有问题的。

因为可能存在一个情况，使得这个时候 $i$ 没法走到其他的地方，这样的情况出现的概率是 $\prod_{j}(1-p_{i,j})$，但是这个时候因为 $E_i$ 只计算的是非自环上的期望，所以转移应该写成

$$E_i=\sum_{j=1}^n\dfrac{E_j}{1-\prod_{k=1}^n (1-p_{j,k})}\times  p_{i,j}\times \prod_{k}^{E_k<E_j}(1-p_{i,k})$$

考虑转移的顺序，显然在更新的时候，如果存在一个 $E_k<E_j$，并且还没有向那里走过，那么我们应该优先从 $i$ 往 $k$ 走。

所以我们可以每次枚举最小的之前没有更新过的 $E_j$ 更新

这个做法和朴素的 $\mathcal O(n^2)$ dijkstra 类似

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1005;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n;
double g[N][N];
double E[N],prod[N];
bool vis[N];

int main()
{
	read(n);
	Rep(i,1,n)
		Rep(j,1,n){
			int x;
			read(x);
			g[i][j]=1.*x/100;
		}
	if(n==1)return puts("0"),0;
	vis[n]=true;
	for(int i=1;i<n;i++){
		E[i]=1;
		prod[i]=1-g[i][n];	
	}
	Rep(i,1,n){
		double low=1e18;
		int pos=0;
		Rep(j,1,n)
			if(!vis[j]&&E[j]/(1-prod[j])<low)
				low=E[j]/(1-prod[j]),pos=j;
		if(pos==1)return printf("%.10lf\n",E[1]/(1-prod[1])),0;
		vis[pos]=true;
		Rep(j,1,n)
			E[j]+=E[pos]/(1-prod[pos])*g[j][pos]*prod[j],prod[j]*=(1-g[j][pos]);
	}
	return 0;
}
```


---

## 作者：xht (赞：8)

> [CF605E Intergalaxy Trips](https://codeforces.com/contest/605/problem/E)

## 题意

- $n$ 个点的有向完全图。
- $i \to j$ 的边每天出现的概率均为 $p_{i,j}$，若 $i = j$，有 $p_{i,j} = 1$。
- 每天选择一条存在的出边走过去。
- 求最优策略下从 $1$ 到 $n$ 的期望天数。
- $n \le 10^3$。

## 题解

最优策略显然应该是贪心的找出边中期望天数尽量小的走过去，那么反向推一次，每次找当前期望天数最小的点，然后动态维护期望天数和剩余概率即可，时间复杂度 $\mathcal O(n^2)$。

## 代码

```cpp
const int N = 1e3 + 7;
int n, v[N];
ld p[N][N], a[N], d[N];

inline bool work() {
	int o;
	ld x = 1e100L;
	for (int i = 1; i <= n; i++)
		if (!v[i] && (d[i] + a[i]) / (1 - a[i]) <= x) x = (d[i] + a[i]) / (1 - a[i]), o = i;
	v[o] = 1, d[o] = (d[o] + a[o]) / (1 - a[o]);
	if (o == 1) return 1;
	for (int i = 1; i <= n; i++)
		if (!v[i]) d[i] += a[i] * p[i][o] * (d[o] + 1), a[i] *= 1 - p[i][o];
	return 0;
}

int main() {
	rd(n);
	for (int i = 1, x; i <= n; i++) {
		for (int j = 1; j <= n; j++) rd(x), p[i][j] = 0.01L * x;
		a[i] = 1;
	}
	a[n] = 0;
	for (int i = 1; i <= n; i++)
		if (work()) return cout << fixed << setprecision(15) << d[1] << endl, 0;
	return 0;
}

```

---

## 作者：Kubic (赞：7)

这道题原有的题解真的好简略啊。。。

首先设出一个值 $E_u$ 表示 $u$ 走到 $n$ 所需要的期望时间。

我们从结果出发，发现对于每一个 $E_u<E_v$，如果当前在 $u$ 那下一步一定不可能走到 $v$，因为这样走还不如走一次自环。那么这个转移图就一定是一个 DAG。

因为有自环，所以有 $E_u=p_u(E_u+1)+dp_u$，其中 $p_u$ 表示对于所有 $E_u<E_v$ 都有 $(u,v)$ 这条边被删去的概率，$dp_u$ 表示所有 $E_u<E_v$ 的 $v$ 对 $u$ 的贡献之和。于是我们可以得出 $E_u=\dfrac{dp_u+p_u}{1-p_u}$。

我们考虑这个 DAG 的拓扑序。假设当前拓扑序前 $i-1$ 个点都已经对其他点贡献过了，那么我们可以发现此时第拓扑序第 $i$ 个点的 $E$ 值已经是它最终的答案了，即没有其它点能对它再次产生贡献。那么现在需要解决的问题就是如何找到拓扑序第 $i$ 个点。

容易发现，当前 $E$ 值最小的点就是当前要选的点。

其实这个东西很像 Dijkstra 算法的思想。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1005
#define LIM 1000000
#define db double
#define gc() (P1==P2 && (P2=(P1=buf)+fread(buf,1,LIM,stdin),P1==P2)?EOF:*P1++)
char buf[LIM],*P1,*P2;
int n;db dp[N],nw[N],a[N][N];bool vs[N]; 
int rd()
{
	int res=0;char c=0;while(!isdigit(c)) c=gc();
	while(isdigit(c)) res=res*10+c-48,c=gc();return res;
}
db calc(int u) {return (dp[u]+nw[u])/(1-nw[u]);}
void release(int u)
{
	vs[u]=1;
	for(int i=1;i<=n;++i) if(!vs[i])
		dp[i]+=(calc(u)+1)*a[i][u]*nw[i],nw[i]*=1-a[i][u];
}
int main()
{
	n=rd();for(int i=1;i<n;++i) nw[i]=1;
	for(int i=1,x;i<=n;++i) for(int j=1;j<=n;++j)
		x=rd(),a[i][j]=0.01*x;release(n);
	for(int i=1,t=0;i<n;++i,t=0)
	{
		for(int j=1;j<=n;++j)
			if(!vs[j] && (!t || calc(j)<calc(t))) t=j;
		if(t==1) break;release(t);
	}printf("%.10lf\n",calc(1));return 0;
}
```

---

## 作者：little_sun (赞：6)

### 题目大意

有一个有$n$个点的有向完全图，每条边每天有一个开放几率$p[i][j]$，给定$p$，你需要求出从$1$到$n$的期望天数

$n \leq 10^3$

### 分析

我们可以考虑倒着做，类似$\texttt{dijkstra}$的思路，每次找到当前走到$1$期望天数最小的，并用它更新所有点的期望天数和路径概率，直到走到$n$为止。

时间复杂度$\mathcal{O}(n^2)$

### 代码

```cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)

const int MaxN = 1e3 + 10;

int n, vis[MaxN], a[MaxN];
double p[MaxN][MaxN], d[MaxN], sum[MaxN], pr[MaxN];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int now = 0;
        sum[i] = pr[i] = 1.0;
        for (int j = 1; j <= n; j++)
            scanf("%d", &now), p[i][j] = now * 0.01L;
    }
    vis[n] = 1, a[1] = n, d[0] = 1e18;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (vis[j]) continue;
            sum[j] += d[a[i - 1]] * p[j][a[i - 1]] * pr[j];
            pr[j] *= (1 - p[j][a[i - 1]]), d[j] = sum[j] / (1 - pr[j]);
        }
        int pos = 0;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && d[pos] > d[j])
                pos = j;
        vis[pos] = 1, a[i] = pos;
    }
    printf("%.10lf\n", d[1]);
    std::cerr << "tiger0132 /qq";
    return 0;
}
```



---

## 作者：shao0320 (赞：3)

#### 题目大意

- $n$ 个点的有向完全图。
- $i \to j$的边每天出现的概率均为 $p_{i,j} = 1$,若 $i = j$，有 $p_{i,j} = 1$
- 每天选择一条存在的出边走过去。
- 求最优策略下从 $1$ 到 $n$的期望等待天数。
- $n \le 10^3$

分析：

期望神题

首先考虑$DP$,设$E_x$表示$x$到$n$的期望等待天数

考虑$E_x$的转移，考虑一条出边$(x,v)$，由于他足够聪明，因此仅当所有$E_y\leq E_v$的点在当前都没出现，而这条边出现了。

所以容易得到一个转移是这个样子的：

$E_x=\sum{E_v*p_{x,v}*\prod^{E_v<E_y}p_{i,y}}$

但是这是不对的因为没有考虑自环，导致这个玩意狗屁不是。

考虑走的过程实际上是肯定是能不走自环就不走自环，先走自环走非自环。

因此实际上的转移应该是这样子的：

$E_x=\sum{\frac{E_v}{1-\prod{p_{i,y}}}p_{x,v}*\prod^{E_v<E_y}p_{i,y}}$

之所以除$\prod^{E_v<E_y}p_{i,y}$是因为这是分步做，乘法原理告诉我们分步做要用乘法。

而$\frac{1}{\prod{p_{x,v}}}$的现实意义是：在选择这条出边走出去之前要等待几天。

由于期望的可乘性，因此可以直接乘上需要等待几天

这题我**想了好几天都是因为这个，感谢czd、cjx、glq等一众大佬（（（

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,vis[N];
double E[N],a[N][N],prod[N];
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			int x=read();
			a[i][j]=1.0*x/100;			
		}
	}
	if(n==1)return puts("0"),0;
	for(int i=1;i<n;i++)
	{
		E[i]=1;
		prod[i]=1-a[i][n];
	}
	vis[n]=1;
	for(int i=1;i<=n;i++)
	{
		double minn=1e18;
		int pos=0;
		for(int j=1;j<=n;j++)
		{
			if(E[j]/(1-prod[j])<minn&&!vis[j])
			{
				minn=E[j]/(1-prod[j]);
				pos=j;
			}
		}
		vis[pos]=1;
		if(pos==1)return printf("%.12lf\n",E[pos]/(1-prod[pos])),0;
		for(int j=1;j<=n;j++)
		{
			E[j]+=E[pos]/(1-prod[pos])*a[j][pos]*prod[j];
			prod[j]*=(1-a[j][pos]);
		}
	}
	return 0;
}
```



---

## 作者：localhost (赞：3)

设$E_x$为$x$到$n$的期望时间

$E_x = \sum_i E_i \times p_{xi}\prod_{j=1}^{i-1}(1-p_{xj})$

我们可以用类似`dij`的思想来更新

每次取出$E_x$最小的$x$来更新

要注意我们现在求出来的还没算上$1$需要先停留在原地的概率,

除掉一个$1-\prod p$才是最终的期望

上代码:

```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define rg register
    #define ll long long
    #define ull unsigned long long
    #define db double
    #define sht short
    #define MB template <class T>il
    #define Fur(i,x,y) for(int i(x);i<=y;++i)
    #define Fdr(i,x,y) for(int i(x);i>=y;--i)
    #define fl(i,x) for(int i(head[x]),to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) ((int)(log2(n)))
    #define inf 2122219134
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const int str=1<<20;static char in_buf[str],*in_s,*in_t;bool __=0;il char gc(){return (in_s==in_t)&&(in_t=(in_s=in_buf)+fread(in_buf,1,str,stdin)),in_s==in_t?EOF:*in_s++;}il void in(string &ch){ch.clear();if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)__=1;}il void in(char &ch){if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)__=1;else ch=c;}il void in(char *ch){*ch='\0';if(__)return;rg char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF){__=1;return;}*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)__=1;*ch='\0';}template<typename T>il void in(T &x){if(__)return;rg char c=gc();bool f=0;while(c!=EOF&&(c<'0'||c>'9'))f^=(c=='-'),c=gc();if(c==EOF){__=1;return;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=x*10+c-48,c=gc();if(c==EOF)__=1;if(f)x=-x;}template<typename T,typename ... arr>il void in(T &x,arr & ... y){in(x),in(y...);}const char ln='\n';static char out_buf[str],*out_s=out_buf,*out_t=out_buf+str;il void flush(){fwrite(out_buf,1,out_s-out_buf,stdout);out_s=out_buf;}il void pt(char c){(out_s==out_t)?(fwrite(out_s=out_buf,1,str,stdout),*out_s++=c):(*out_s++=c);}il void out(const char* s){while(*s)pt(*s++);}il void out(char* s){while(*s)pt(*s++);}il void out(char c){pt(c);}il void out(string s){for(int i=0;s[i];i++)pt(s[i]);}template<typename T>il void out(T x){if(!x){pt('0');return;}if(x<0)pt('-'),x=-x;char a[50],t=0;while(x)a[t++]=x%10,x/= 10;while(t--)pt(a[t]+'0');}template<typename T,typename ... arr>il void out(T x,arr & ... y){out(x),out(y...);}}using namespace IO;
#define N 1011
int n;
db g[N][N],p[N],E[N];
bool v[N];
int main(){
    in(n);
    int x;
    Fur(i,1,n)Fur(j,1,n)in(x),g[i][j]=x/100.0;
    if(n==1)return puts("0"),0;
    Fur(i,1,n)E[i]=1,p[i]=1-g[i][n];
    E[n]=0;v[n]=1;
    Fur(i,1,n){
        x=0;db mx=1e18;
        Fur(j,1,n)
        if(!v[j]&&E[j]/(1-p[j])<mx)
            mx=E[j]/(1-p[j]),x=j;
        v[x]=1;
        if(x==1)return printf("%.10f\n",E[1]/(1-p[1])),0;
        Fur(j,1,n)
            E[j]+=(E[x]/(1-p[x]))*g[j][x]*p[j],p[j]*=(1-g[j][x]);
    }
}
```

---

## 作者：Piwry (赞：2)

## 解析

### Part 1

设 $E(x)$ 表示结点 $x$ 到 $n$ 的期望步数

首先可以想到最优策略下，每一步只会走向期望小于当前结点的结点（最坏情况下即走自环）

再将结点按 $E(x)$ 的大小关系升序排序，置于数组 $v[0..n-1]$ 中。接着可以得到 $E(x)$ 之间的关系式：

$E(v[i])=\sum\limits_{j=0}^{i-1}((E(v[j])+1)\cdot p(v[i], v[j])\cdot\prod\limits_{k=0}^{j-1}(1-p(v[i], v[k])))+(E(v[i])+1)\cdot\prod\limits_{j =0}^{i-1}(1-p(v[i], v[j]))$

### Part 2-1

如果对 $i\in [0, n-1]$ 都列出这样一个式子，我们就得到了 $n$ 个互相不成线性关系的方程（不过当 $i=0$ 时可能会有些矛盾，这只需另外定义即可）；如果能得到数组 $v[0..n-1]$，显然就可以直接解出所有 $E(x)$ 了

但我们还没法得知 $v[0..n-1]$。考虑已有的信息，即 $E(n)=0$，$v[0]=n$，并将其带入方程；再观察式子，发现若我们得知 $v[1]$ 的值，便可直接计算出 $E(v[1])$。接着不妨枚举 $v[1]$，取使计算得到的 $E(v[1])$ 最小的作为 $v[1]$ 的值（最优/正确性可考虑直接反证）。再如此反复，便可得到所有 $E(x)$ 的值

### Part 2-2

或者可以考虑一种类似 dijkstra 的做法

设已确定 $E(x)$ 的结点集合 $S$，且保证任意不在 $S$ 中的结点的期望均不小于 $S$ 中结点的期望。每次我们枚举所有不在 $S$ 中的结点，将其作为所有不在 $S$ 中的结点中期望最小的结点，这样就可以直接计算出它的 $E(x)$，同样也取计算得到的期望最小的结点加入 $S$。如此重复即可得到所有 $E(x)$ 的值

这种做法的证明也类似 dijkstra

## Part 3

两种算法要实现的东西其实差不多

先将刚才的式子化简一下：

由于每一步无论往哪个结点走都会导致贡献加一，我们不妨把这部分的贡献拆出来。即刚才的式子其实可以写成：

$E(v[i])=\sum\limits_{j=0}^{i-1}(E(j)\cdot p(v[i], v[j])\cdot\prod\limits_{k=0}^{j-1}(1-p(v[i], v[k])))+E(v[i])\cdot\prod\limits_{j =0}^{i-1}(1-p(v[i], v[j]))+1$

（当然直接纯代数过程也可以得到这个式子，[可见](https://www.luogu.com.cn/paste/2srm0avp)）

接着再将 $E(i)$ 全部移到左边，得到：

$E(i)=\frac {\sum\limits_{j=0}^{i-1}E(j)\cdot p(i, j)\cdot\prod\limits_{k=0}^{j-1}(1-p(i, k))+1} {1-\prod\limits_{j =0}^{i-1}(1-p(i, j))}$

对每个结点我们只需维护这个式子即可

首先分子分母可以分开维护。接着关于 $\prod$（连乘）部分，每次用到都暴力算一遍显然不行，我们其实可以在每确定一个 $v[i]$ 的值（每添加一个结点到 $S$）时，就为所有剩下的元素添加对应的贡献

如果对细节部分还有疑问可以参考代码

## 代码

两种思路最后得到的代码其实都差不多

```cpp
#include <cstdio>

namespace IO_number{
	int read(){
		int x =0; char c =getchar(); bool f =0;
		while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
		while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
		return (f) ? -x : x;
	}
	
	void write(const int &x){
		if(x < 0){
			putchar('-');
			write(-x);
		}
		else{
			if(x/10)
				write(x/10);
			putchar('0'+x%10);
		}
	}
}
using namespace IO_number;

const int MAXN =1e3+20;

double p[MAXN][MAXN];
double num[MAXN], den[MAXN]; // Ans；num 分子 den 分母 //

bool vis[MAXN];

int main(){
	const int n =read();
	for(int i =0; i < n; ++i)
		for(int j =0; j < n; ++j)
			p[i][j] =read()/100.0;
	
	num[n-1] =0, den[n-1] =1;
	for(int i =0; i < n-1; ++i)
		num[i] =(num[n-1]/den[n-1])*p[i][n-1]+1, den[i] =1-(1-p[i][n-1]);
	vis[n-1] =1;
	if(n == 1)
		return printf("%lf", 0.0) && 0;
	for(int _i =1; _i < n; ++_i){
		int mn_i =-1;
		double mn =1e18;
		for(int i =0; i < n; ++i)
			if(!vis[i] && num[i]/den[i] < mn)
				mn =num[i]/den[i], mn_i =i;
		vis[mn_i] =1;
		if(mn_i == 0)
			return printf("%lf", num[mn_i]/den[mn_i]) && 0;
		for(int i =0; i < n; ++i)
			if(!vis[i]){
				num[i] +=(num[mn_i]/den[mn_i])*p[i][mn_i]*(-(den[i]-1));
				--den[i], den[i] *=(1-p[i][mn_i]), ++den[i];
			}
	}
}
```

---

## 作者：关怀他人 (赞：2)

### CF605E
#### Solution
设$E(u)$表示从$u$到$n$的期望步数，考虑下一步，如果是走到$v$且$E(v)\geq E(u)$，那么当前这一步的最优策略肯定是停在原地。

所以我们永远不会走到一个比当前期望步数大的点，所以我们可以考虑将所有答案按从小到大的顺序算出，并以此扩展。

设$u$的后继分别为$v_i$且$E$非降，那么
$$
E(u)=\sum_i \dfrac{E(v_i)}{1-\prod_{j=1}^n(1-p_{v_i,j})}p_{u,v_i}\prod_{j=1}^{i-1} (1-p_{u,v_j})+1
$$
后面的$\prod_{j=1}^{i-1} (1-p_{u,v_j})$表示$v_i$可以走且所有期望步数小于$v_i$的都不能走，而前面除以$1-\prod_{j=1}^n(1-p_{v_i,j})$的原因是要去掉$v_i$没法走到其他地方的概率，因为$E_i$计算的是不考虑自环的概率，最后再加上当前这一步的贡献$1$即可。

用类似 $\mathrm{dijkstra}$ 的方式每次取最小的转移即可。

时间复杂度 $\mathcal O(n^2)$

#### Code
```cpp
int n;
int vis[MAXN],a[MAXN];
double p[MAXN][MAXN],E[MAXN],prod[MAXN];

int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= n;j++)
            scanf("%lf",&p[i][j]), p[i][j] /= 100;
    if(n == 1) {printf("0\n"); return 0;}
    for(int i = 1;i <= n;i++) E[i] = 1, prod[i] = 1 - p[i][n];
    vis[n] = 1; a[1] = n;
    for(int i = 1;i <= n;i++){
        double minval = llINF; int pos = 0;
        for(int j = 1;j <= n;j++){
            if(!vis[j] && E[j] / (1 - prod[j]) < minval){
                pos = j;
                minval = E[j] / (1 - prod[j]);
            }
        }
        vis[pos] = 1;
        for(int j = 1;j <= n;j++)
            E[j] += E[pos] / (1 - prod[pos]) * p[j][pos] * prod[j], prod[j] *= (1 - p[j][pos]);
    }
    printf("%.8f\n",E[1] / (1 - prod[1]));
    return 0;
}
```



---

