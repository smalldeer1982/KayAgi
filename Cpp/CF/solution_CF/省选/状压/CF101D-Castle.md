# Castle

## 题目描述

Gerald 现在位于一座古老的城堡中，这座城堡由 $n$ 个大厅和 $n-1$ 条走廊连接而成。从任意一个大厅到另一个大厅恰好只有一条路径。因此，这张图是一棵树。最初，在时间 $0$ 时刻，Gerald 位于 $1$ 号大厅。此外，城堡中的某个其他大厅藏有 Gerald 正在寻找的宝藏。宝藏的位置未知，它等概率地可能出现在其他 $n-1$ 个大厅中的任意一个。只有当 Gerald 进入藏有宝藏的大厅时，他才能发现宝藏，这一时刻即被视为他达成目标的时刻。

每条走廊的长度各不相同。与此同时，走廊很长，而大厅很小且光线充足，因此可以忽略 Gerald 在大厅中所花费的时间。由于城堡非常古老，每当某条走廊被人第二次经过时（无论方向），这条走廊就会坍塌。

Gerald 可以通过走廊在城堡中移动，直到找到宝藏为止。自然地，Gerald 希望尽快找到宝藏。换句话说，他希望采取一种策略，使得找到宝藏的平均时间尽可能小。由于每条走廊最多只能经过两次，因此 Gerald 必须选择一种能够确保访问到每个大厅的策略。

更正式地说，如果宝藏位于第二个大厅，那么 Gerald 第一次进入第二个大厅的时刻记为 $t_2$，他就会发现宝藏。如果宝藏在第三个大厅，Gerald 第一次进入第三个大厅的时刻记为 $t_3$，他就会发现宝藏。以此类推。因此，找到宝藏的平均时间等于
$$
\frac{t_2 + t_3 + \cdots + t_n}{n-1}
$$

## 说明/提示

在第一个测试样例中，城堡只有两个大厅，因此宝藏一定在第二个大厅。Gerald 只需花费一分钟从第一个大厅走到第二个大厅。

在第二个测试样例中，Gerald 只能从第一个大厅走到第三个大厅。他可以从第三个大厅回到第一个大厅，也可以前往第二个大厅，但回到第一个大厅后无法再前进，因此他需要前往第二个大厅。接着他应该去第四个大厅，因为其他大厅都已经访问过。如果宝藏在第三个大厅，Gerald 会在一分钟后找到它；如果在第二个大厅，则在两分钟后找到；如果在第四个大厅，则在三分钟后找到。平均时间为 $2$ 分钟。

在第三个测试样例中，Gerald 需要访问 $4$ 个大厅：第二、第三、第四和第五号大厅。它们都只能从第一个大厅到达。因此，他需要依次前往这 $4$ 个大厅并返回。Gerald 会在一分钟后进入第一个大厅，在三分钟后进入第二个，在五分钟后进入第三个，在七分钟后进入第四个。平均时间为 $4$ 分钟。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
1 2 1
```

### 输出

```
1.0
```

## 样例 #2

### 输入

```
4
1 3 2
4 2 1
3 2 3
```

### 输出

```
4.333333333333334
```

## 样例 #3

### 输入

```
5
1 2 1
1 3 1
1 4 1
1 5 1
```

### 输出

```
4.0
```

# 题解

## 作者：George1123 (赞：5)


更蒻的体验 $\to $ [`George1123`](https://www.cnblogs.com/George1123/p/13851802.html)

---

## 题面

> [CF101D Castle](https://www.luogu.com.cn/problem/CF101D)

> 给一棵 $n$ 个节点的带权树，求一种遍历方案，从 $1$ 出发，每条边走两次，走过所有点，第一次经过每个节点的平均时间最小。输出这个平均时间。

> 数据范围：$2\le n\le 10^5$。

---

## 题解

可以对于每棵子树单独计算。

虽然子树内走的顺序是不固定的，但是要消耗的总时间是固定的。

设 $f_u$ 表示 $u$ 这棵子树内的第一次经过每个节点的 **时间和**，$w_{u,v}$ 是 $u,v$ 两点间的边权，$sz_u$ 是 $u$ 的子树大小，$szt_u$ 是走遍 $u$ 这棵子树的所需时间。

由于每棵子树遍历一次而且有顺序，记 $v_i$ 为 $u$ 第 $i$ 个遍历的子树。

$$f_u=\sum_{i} [f_{v_i}+sz_{v_i}w_{u,v_i}+(szt_{v_i}+2w_{u,v})\sum_{j>i} sz_{v_j}]$$

$\sum_{i} (f_{v_i}+sz_{v_i}w_{u,v_i})$ 是顺序不同时固定的，$\sum_{i} (szt_{v_i}+2w_{u,v})\sum_{j>i} sz_{v_j}$ 是会变的，所以这题的难点在于找到它的最小值。

蒟蒻想了好久，这个式子很眼熟，但是怎么化都貌似不能贪心，于是请教了旁边的保队长。

很明显，如果对于 $i\ge 3$，$v_i$ 都已经确定，那么 $p$ 和 $q$ 分别作为 $v_1,v_2$ 的贡献是

$$v_1=p,v_2=q:(szt_p+2w_{u,p})(sz_{q}+\sum_{j\ge 3} sz_{v_j})+(szt_p+2w_{u,p})\sum_{j\ge 3}sz_{v_j}+\cdots$$

$$v_1=q,v_2=p:(szt_q+2w_{u,q})(sz_{p}+\sum_{j\ge 3} sz_{v_j})+(szt_q+2w_{u,q})\sum_{j\ge 3}sz_{v_j}+\cdots$$

其实差别就在于 $(szt_p+2w_{u,p})sz_{q}$ 和 $(szt_q+2w_{u,q})sz_{p}$，而且手玩一下可以发现，对于任意两个 $v$ 顺序都是类似的。

所以把所有 $v\in son_u$ 丢进一个 `vector`，然后对于 $p$，$q$，按上面的差别排序即可。

---

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair((a),(b))
#define x first
#define y second
#define bg begin()
#define ed end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define R(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define L(i,a,b) for(int i=(b)-1,i##E=(a)-1;i>i##E;i--)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e5;
int n;

//Tree
vector<int> e[N],to,we;
void adde(int u,int v,int w){
    e[u].pb(sz(to)),to.pb(v),we.pb(w);
    e[v].pb(sz(to)),to.pb(u),we.pb(w);
}
int sz[N],szt[N];
ll dfs(int u,int fa){
    ll res=0; sz[u]=1,szt[u]=0;
    vector<int> cho;
    for(int v:e[u])if(to[v]^fa){
        res+=dfs(to[v],u);
        res+=1ll*we[v]*sz[to[v]];
        szt[to[v]]+=we[v]*2;
        sz[u]+=sz[to[v]],szt[u]+=szt[to[v]];
        cho.pb(to[v]);
    }
    sort(cho.bg,cho.ed,[&](int p,int q){
        return 1ll*szt[p]*sz[q]<1ll*szt[q]*sz[p];
    });
    int tot=sz[u]-1;
    for(int v:cho) tot-=sz[v],res+=1ll*szt[v]*tot;
    return res;
}

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cout.precision(12);
    cin>>n;
    R(i,1,n){int u,v,w; cin>>u>>v>>w,--u,--v,adde(u,v,w);}
    // cout<<dfs(0,-1)<<'\n';
    cout<<fixed<<1.*dfs(0,-1)/(n-1)<<'\n';
    return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：C3H5ClO (赞：4)

看到没题解，我就来写一个

设点$x$的子树大小为$siz[x]$，点$x$到达子树内节点时间之和为$f1[x]$，子树内边权和的两倍为$f2[x]$

假设已经给定了$x$孩子的访问顺序$a[1..cnt]$，设$b[i]=f2[a[i]]+w_{x,a[i]}\times 2,s[l..r]=\sum_{i=l}^rb[i]$，则有$f1[x]=\sum_{i=1}^{cnt}siz[a[i]]\times (s[1..i-1]+w_{x,a[i]})+f1[a[i]]$

对于$a[1..len]$中两个元素$a[i]$和$a[i+1]$，如果交换这两项，设交换前与交换后答案分别为$f1[x]$与$f1'[x]$

如果$i$在前更优，则$f1[x]\le f1'[x]$，$siz[a[i+1]]\times b[i]\le siz[a[i]]\times b[i+1]$

命题：将序列$a$按照$siz[a[j]]\times b[i]<siz[a[i]]\times b[j]$排序，所得$f1[x]$最小。

证明：

1.由于可以转化为$\frac{b[i]}{siz[a[i]]}<\frac{b[j]}{siz[a[j]]}$，此运算符满足严格弱序。

2.定义$siz[a[j]]\times b[i]>siz[a[i]]\times b[j]$中$(i,j)$为“逆序对”，同样满足此条件的$(i,i+1)$定义为“邻项逆序对”。假设存在一个序列，存在逆序对而能使答案最小。由于运算符满足严格弱序，存在逆序对就必定存在邻项逆序对，可以交换使答案更小，假设不成立。因此，不存在逆序对的序列答案最优。

3.按照这样排序可以使排序后序列$a$不含逆序对，因此按这样排序答案最小。

（感性理解：虽然每次交换$a[i]$与$a[j]$不一定会缩小答案，但排序最终结果最小）

然后树形dp即可。

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define ll long long
const int N=100005;
int n,x,y,z,f2[N],siz[N],len;
int head[N],ecnt;
ll f1[N];
struct edge{int to,w,nxt;}e[N<<1];
struct node{int x,y,z;}a[N];
inline void add(int x,int y,int z){e[++ecnt]={y,z,head[x]}; head[x]=ecnt;}
inline bool cmp(node a,node b){return 1ll*b.x*a.y<1ll*a.x*b.y;}
void dfs(int x,int fa)
{
	int y; siz[x]=1;
	for(int i=head[x];i;i=e[i].nxt)
		if((y=e[i].to)!=fa)
		{
			dfs(y,x);
			siz[x]+=siz[y]; f1[x]+=f1[y];
		}
	len=0;
	for(ri i=head[x];i;i=e[i].nxt)
		if((y=e[i].to)!=fa)a[++len]={siz[y],f2[y]+(e[i].w<<1),e[i].w};
	sort(a+1,a+len+1,cmp);
	for(ri i=1;i<=len;i++)f1[x]+=1ll*(f2[x]+a[i].z)*a[i].x,f2[x]+=a[i].y;
}
int main()
{
	scanf("%d",&n);
	for(ri i=1;i<n;i++)scanf("%d%d%d",&x,&y,&z),add(x,y,z),add(y,x,z);
	dfs(1,0);
	printf("%.10lf",(double)f1[1]/(n-1));
}
```

---

## 作者：UperFicial (赞：3)

> [**CF101D Castle**](https://www.luogu.com.cn/problem/CF101D) 解题报告。

套路贪心，给一个比较清晰的贪心证明。

由于平均时间的分母是固定的，我们只需要计算一个 $f_u$ 表示以 $u$ 为根的子树中最少的时间和。

考虑转移，我们需要钦定一个子树内的转移顺序，设 $v_i$ 表示第 $i$ 次进入的子树，由于子树内每一条边都要进去一次，出去一次，并且 $u\to v_i$ 这条边也同样进去一次，除去一次，所以我们可以设 $s_j$ 表示以 $j$ 为根的子树中，边权之和加上 $j$ 到其父亲的距离之和乘 $2$。

那么我们的转移方程是非常好表示的：

$$f_{u}=\sum_{i}\left(f_{v_{i}}+w_{u,v_i}\times siz_{v_i}+\left(\sum_{1\le j<i}s_{v_j}\right)\times siz_{v_i}\right)$$

那么现在问题是 $v_i$ 选择的顺序，这个很套路，直接采用贪心中常用的临项交换法。可以参考典中典 [**P1080 [NOIP2012 提高组] 国王游戏**](https://www.luogu.com.cn/problem/P1080)。

前一半部分的贡献是定的，只需要考虑后半部分，对于相邻的两个点 $v_i$ 和 $v_{i+1}$，交换或这不交换，对于 $j<i$ 的 $j$ 贡献是一样的，变更的之后 $i$ 和 $i+1$ 的贡献之和。

如果不交换它们，那么对于第 $i+1$ 个点和第 $i$ 个点的后半部分的贡献为 $\left(\sum_{1\le j\le i}s_{v_j}\right)\times siz_{v_{i+1}}+\left(\sum_{1\le j< i}s_{v_j}\right)\times siz_{v_{i}}$，如果交换它们，那么后半部分的贡献为 $\left(s_{v_{i+1}}+\sum_{1\le j< i}s_{v_j}\right)\times siz_{v_{i}}+\left(\sum_{1\le j< i}s_{v_j}\right)\times siz_{v_{i+1}}$。

直接进行一个式子的减，用一式减二式，得到 $s_{v_i}\times siz_{v_{i+1}}-s_{v_{i+1}}\times siz_{v_i}$，如果这个东西大于 $0$，那么说明交换更优，否则不优。

那么只需要根据上面那个式子，对 $u$ 的每一个儿子排一下序即可得到确定的顺序。

时间复杂度 $O(n\log n)$。瓶颈在排序。

为了放置被骂贴一下代码：

```cpp
inline bool cmp(int x,int y){return 1ll*siz[y]*s[x]<1ll*siz[x]*s[y];}
inline void dfs(int u,int fa)
{
	siz[u]=1;
	gra(i,u)
	{
		int v=edge[i].to;
		if(v!=fa) dfs(v,u);
	}
	int cnt=0;
	gra(i,u)
	{
		int v=edge[i].to,w=edge[i].cost;
		if(v!=fa) ver[++cnt]=v,f[u]=f[u]+f[v]+1ll*w*siz[v],siz[u]+=siz[v],s[v]+=(w<<1),s[u]+=s[v];
	}
	if(cnt) sort(ver+1,ver+1+cnt,cmp);
	ll sum=0;
	rep(i,1,cnt)
	{
		int v=ver[i];
		f[u]+=sum*siz[v],sum+=s[v];
	}
	return;
}
```

---

## 作者：jun头吉吉 (赞：2)

# 题意
有一棵节点数为$n$的数，边有边权。现有宝藏等概率的在$2\to n$点，求发现宝藏最短的期望时间。
## 题解
~~套路题~~

做此题前建议先$\text{A}$了[P3574](/problem/P3574)

考虑用$f_i$表示在$i$的子树中的最小期望时间，显然如果我们有排列好了遍历顺序，如果$w_i$为到$i$的边权，那么：
$$f_i=\sum_{Son\in son_i}(\text{等待时间}+w_{Son}+f_{Son})\times P(\text{宝藏在}Son\text{中})$$

即$tim_i$为遍历完$i$的子树的时间

那么再考虑如果$y$比$x$更优，则必然满足：
$$(f_x+w_x)\times P(in\ x)+((tim_x+2w_x)+f_y+w_y)\times P(in\ y)>(f_y+w_y)\times P(in\ y)+((tim_y+2w_y)+f_x+w_x)\times P(in\ x)$$
记$tim_x+2\times w_x=g_x$，$sz_x$为子树的大小。

经过简单的化简得到：

$$\frac {g_y} {sz_y}<\frac {g_x}{sz_x}$$

按$\frac g{sz}$从小到大排序，再更新$f$即可

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;char c=getchar();bool f=false;
	for(;!isdigit(c);c=getchar())f!=c=='-';
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	if(f)x=-x;
}
template<typename T ,typename ...Arg>
inline void read(T &x,Arg &...args){
	read(x);read(args...);
}
template<typename T>
inline void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
const int N=1e5+10;
int n,O,tim[N];//存遍历完子树再回来需要的时间
int sz[N];//树的大小 
double f[N];//存找到宝藏的期望 
vector<pair<int,int>>e[N];
#define pb push_back
void dfs(int u,int fa){
	tim[u]=f[u]=0;sz[u]=1;
	for(auto Edge:e[u]){
		int v=Edge.first,w=Edge.second;
		if(v==fa)continue;
		dfs(v,u);
		tim[u]+=2*w+tim[v];
		sz[u]+=sz[v];
	}
	vector<pair<double,pair<int,int>>>son;
	//first用来排序
	//second.first记录编号
	//second.second记录边权 
	for(auto Edge:e[u]){
		int v=Edge.first,w=Edge.second;
		if(v==fa)continue;
		son.pb({1.0*(2*w+tim[v])/sz[v],{v,w}});
	}
	int wait=0,tot;
	if(u==1)tot=sz[u]-1;
	else tot=sz[u];
	sort(son.begin(),son.end());
	for(auto Son:son){
		int v=Son.second.first;
		int w=Son.second.second;
		f[u]+=(wait+w+f[v])*1.0*sz[v]/tot;
		wait+=tim[v]+2*w;
	}
}
signed main(){
	read(n);
	for(int i=1,u,v,w;i<n;i++)
		read(u,v,w),
		e[u].pb({v,w}),e[v].pb({u,w});
	dfs(1,0);
	printf("%.8lf",f[1]);
}
```

---

## 作者：ZeroOf149 (赞：1)

# [CF101D Castle](https://www.luogu.com.cn/problem/CF101D)

## 题目描述

给一棵有根树，根为 $1$，此外每条边都有其通过时间。  
求一个 dfs 序，使得所有节点第一次到达的时间戳的和最小。   
你只需将答案乘上 $\dfrac{1}{n-1}$ 后输出。

## 解法说明

考虑记 $dp_u$ 为以 $u$ 为起点，遍历其子树的最小时间戳和，再记 $siz_u$ 为 $u$ 的子树大小，$sum_u$ 为遍历 $u$ 的子树所需时间。

对于叶子节点，显然 $dp_u = 0$；对于非叶子节点，不妨假设我们已经确定 $u$ 的孩子的遍历顺序 $\{v_1, v_2, \cdots, v_c\}$，如果我们对 $u$ 的孩子 $v$，记 $w_v$ 为 $(u, v)$ 边的通过时间，那么有：  
$\begin{aligned}
dp_u &= \displaystyle\sum_{i=1}^{c}siz_{v_i}\left(w_{v_i}+\sum_{j=1}^{i-1}(sum_{v_j}+2w_{v_j})\right)+dp_{v_i} \\
&= \sum_{i=1}^{c} dp_{v_i} - siz_{v_i}(sum_{v_i}+w_{v_i}) + \sum_{i=1}^{c}siz_{v_i}\sum_{j=1}^{i}(sum_{v_j}+2w_{v_j})
\end{aligned}$

若再对 $u$ 的孩子 $v_i$，记 $(a_i, b_i) = (siz_{v_i}, sum_{v_i}+2w_{v_i})$，问题转变为：适当重排 $(a_i, b_i)$，使得 $\displaystyle\sum_{i=1}^{c}a_i\sum_{j=1}^{i}b_j$ 达到最小值。

我们可以通过“邻项交换法”解决这种问题，过程如下：

容易发现，这样的重排一定满足如下性质：交换相邻两项一定不优。通过消掉相同的项，这可以改写为：对所有 $1\leq i<c$，都有 $a_{i+1}b_{i} \leq a_{i}b_{i+1}$，即 $\dfrac{b_{i}}{a_{i}} \leq \dfrac{b_{i+1}}{a_{i+1}}$，也就是该序列按照 $\dfrac{b_{i}}{a_{i}}$ 升序排序。对每个转移排序即可。

时间复杂度为 $\Theta(n\log n)$，可以通过本题。

## [代码实现](https://codeforces.com/contest/101/submission/319493359)

这个写法交换了上文 $a_i$ 与 $b_i$ 的定义，容易证明这两种写法等价。

```cpp
#include <algorithm>
#include <cstdio>
#include <vector>

using ll = long long;

constexpr int N = 1e5 + 5;

struct Ec {
  Ec(int vv, int ww) : v{vv}, w{ww} {}
  
  int v, w;
};

int n, siz[N];
ll sum[N], dp[N];
std::vector<Ec> g[N];

struct Helper {
  Helper(ll aa, ll bb) : a{aa}, b{bb} {}
  
  ll a, b;
};

bool operator<(Helper l, Helper r) {
  return 1.l * l.b / l.a < 1.l * r.b / r.a;
}

void dfs(int u, int f) {
  std::vector<Helper> tmp;
  siz[u] = 1;
  for (auto&& e : g[u]) {
    int v = e.v;
    if (v == f) continue;
    int w = e.w;
    dfs(v, u);
    siz[u] += siz[v];
    sum[u] += sum[v] + w * 2;
    dp[u] += dp[v] - siz[v] * (sum[v] + w);
    tmp.emplace_back(sum[v] + w * 2, siz[v]);
  }
  std::sort(tmp.begin(), tmp.end());
  ll pre = 0;
  for (auto&& pr : tmp) {
    pre += pr.b;
    dp[u] += pr.a * pre;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  dfs(1, 0);
  printf("%.9Lf", 1.l * dp[1] / (n - 1));
}
```

---

## 作者：Tony102 (赞：1)

[Link](https://www.luogu.com.cn/problem/CF101D)

[51nod 1527](https://www.51nod.com/Challenge/Problem.html#problemId=1527)

[My Blog](https://tony102.com/archives/131/)

## Sol

答案是非常好表示的，设 $p_i$ 表示某个点访问儿子的顺序， $f_i$ 为以 $i$ 为根的子树的最小时间。

因为子树中每一条边都要进去一次出去一个，进入和离开当前子树都要通过当前子树根与其父亲相连的边，我们用 $sum_i$ 就是当前子树内边权和与通往父亲那天边的总和 $\times 2$

那么：

$$
f_i = \sum\limits_{i=1}^{son_{i}} f_{p_i} + (\sum\limits_{j=1}^{i-1} sum_{p_j})\cdot siz_{p_i}
$$

前面加号前的东西值是不变的，现在要最小化后面那个东西。

考虑交换 $p_{i}$ 和 $p_{i+1}$ ，那么若 $siz_{p_i}\cdot sum_{p_{j+1}} - siz_{p_{j+1}} \cdot sum_{p_j} < 0$ 那么显然交换更优，那么也就是转移的时候用一个数组把这个东西记下来然后升序排序，从最小值开始取可以使答案最小。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef pair < double, double > PDD;
typedef vector < PDD > vec;
const int SIZE = 1e5 + 5;

int n, num;
int head[SIZE]; double f[SIZE], siz[SIZE], sum[SIZE];

struct node {
    int to, v, nxt;
} edge[SIZE << 1];

namespace GTR {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (c < 48 || c > 57) b ^= c == '-', c = fetch();
		while (c >= 48 && c <= 57) a = (a << 1) + (a << 3) + c - 48, c = fetch();
		return b ? a : -a;
	}
} using GTR::read;

void addEdge(int u, int v, int d) {
    edge[++ num] = (node) {v, d, head[u]}, head[u] = num;
}

void dfs(int u, int fa) {
    siz[u] = 1.000; vec tmp;
    for (int i = head[u], v; i; i = edge[i].nxt) {
        v = edge[i].to;
        if (v == fa) continue;
        dfs(v, u);
        f[u] += edge[i].v * siz[v] + f[v], siz[u] += siz[v], sum[u] += 2.000 * edge[i].v + sum[v];
        tmp.emplace_back((PDD) {sum[v] + 2.00 * edge[i].v, siz[v]});
    }
    if (!tmp.empty())
        std::sort(tmp.begin(), tmp.end(), [] (PDD a, PDD b) { return a.first * b.second < b.first * a.second; });
    double s = 0;
    for (PDD it: tmp) f[u] += s * it.second, s += it.first;
}

int main() {
    // freopen("code.in", "r", stdin);
    n = read();
    for (int i = 1, u, v, d; i < n; ++ i) {
        u = read(), v = read(), d = read();
        addEdge(u, v, d); addEdge(v, u, d);
    }
    dfs(1, 0);
    printf("%.7lf\n", f[1] / (n - 1));
    return 0;
}
```


---

## 作者：wangyibo201026 (赞：0)

## solution

首先将原题意可以转化为到达每个点的时间的和最小，然后需要注意到一条边只能走两次，很明显是走进子树和走出子树两次，这使得我们想到 DP 状物。

然后现在在树上进行考虑问题，令 $f_i$ 为子树 $i$ 内的答案，不难发现，如果知道了一个结点 $x$ 的所有儿子 $v$ 的走入顺序，相当于，我每次都走入一个 $v$，再走回 $x$，再走入令一个儿子 $v$，以此类推，那么我们可以很容易的通过 $f_v$ 的值求出 $f_x$ 的值，具体来说：

$$f_x = \sum_{v_i \in son_x} (f_{v_i} + siz_{v_i} \times (2 \times w_{u, v_i} + \sum_{j < i, v_j \in son_x} val_{v_j}))$$

解释一些东西，$siz_x$ 表示 $x$ 子树大小，$val_x$ 表示 $x$ 子树内所有边权和的 $2$ 倍，$w_{u, v}$ 表示树上 $u \to v$ 这条边的边权。为了方便，在代码编写过程中，可以将 $2 \times w_{u, v_i}$ 计入 $val_{v_i}$ 中。

现在如果我们解决了顺序问题，该题目就被解决了。此时我们思考邻项交换法，考虑到交换两个相邻儿子 $v_i, v_{i + 1}$ 的贡献变化量为 $siz_{v_{i + 1}} \times val_{v_i} - siz_{v_{i}} \times val_{v_{i + 1}}$（此时我们忽略掉前面与 $x$ 有关的任何系数。）。那么我们对于这一式子从大往小排序即可，这样每一个都可以取到负数。

---

## 作者：lfxxx (赞：0)

注意到我们一定是走某个 dfs 序，也就是走的过程是一个 dfs 的过程。

由于是在树上，所以就以子树结构来拆解问题，不妨 $dp_u$ 表示从 $u$ 出发走以 $u$ 为根的子树的答案，$sz_u,w_u$ 分别表示 $u$ 子树内点数与边权和的两倍（我们认为 $u$ 到其父亲的边也在其子树内）。

那么转移就是对于一个 $u$ 决定走儿子的顺序 $p$，有 $dp_u = \sum_{i} (dp_{p_i} + sz_{p_i} \times (t_{u,p_i} + \sum_{j<i} w_{p_j}))$。我们只考虑不确定也就是与 $p$ 有关的项，那就是最小化 $\sum_{i} (sz_{p_i} \times \sum_{j<i} w_{p_j})$。

定序问题可以考虑邻项交换法，具体而言对于 $i,i+1$ 来说，我们交换其造成的正面贡献是 $sz_{p_{i+1}} \times w_{p_i} - sz_{p_i} \times w_{p_{i+1}}$，那么我们对于两项 $x,y$ 按照 $sz_x \times w_y > sz_y \times w_x$ 这一优先级排序后便可以保证相邻两项交换带来的贡献均为负数，故取到最优情况，时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
int dp[maxn];//从根出发走遍的花费 
int sz[maxn],w[maxn];//子树内点数 边权和
vector< pair<int,int> > E[maxn];
int n; 
bool cmp(int x,int y){
	return sz[x]*w[y]>sz[y]*w[x];
}
void dfs(int u,int fa){
	sz[u]=1;
	for(pair<int,int> nxt:E[u]){
		int v=nxt.first,e=nxt.second;
		if(v!=fa){
			dfs(v,u);
			w[v]+=2*e;
			w[u]+=w[v];
			sz[u]+=sz[v];
		}
	}
}
int In[maxn];
void DP(int u,int fa){
	vector<int> son;
	for(pair<int,int> nxt:E[u]){
		int v=nxt.first,e=nxt.second;
		if(v!=fa){
			DP(v,u);
			In[v]=e;
			dp[u]+=dp[v];
			son.push_back(v);
		}
	}
	sort(son.begin(),son.end(),cmp);
	int sum=0;
	for(int x:son) dp[u]+=(sum+In[x])*sz[x],sum+=w[x];
	return ;
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		E[u].push_back(make_pair(v,w));
		E[v].push_back(make_pair(u,w));
	}
	dfs(1,0);
	DP(1,0);
	printf("%.6lf",dp[1]*1.0/(n-1)); 
	return 0;
}
```

---

## 作者：262620zzj (赞：0)

# 题意翻译
给定一棵树，初始在节点 $1$，走过一条边所耗费的时间是它的边权，每条边最多走 $2$ 次，最小化走到所有节点的总时间。

# 思路

首先可以发现，由于每条边只能走两次（一来一回），所以一旦走到一个节点，就一定要走完他的子树才能回去，否则的话，这个节点到它父节点的边就必须走超过 $2$ 次。

![](https://cdn.luogu.com.cn/upload/image_hosting/o0a71vok.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/9frn0gqn.png)

**那么需要决策的，就只有先走哪颗子树了。因为子树也是可以用相同方法递归解决的**。这样可以转化为接水问题。每个子树是一个人，接水要耗费不同的时间，我们要做的就是安排接水顺序，使所有人接水的时间总和最短。

类似于 [P1080国王游戏](https://www.luogu.com.cn/problem/P1080)，我们发现**交换相邻的两个子树的次序只影响他们之间所耗费的时间**可以看图更好地理解
 
![](https://cdn.luogu.com.cn/upload/image_hosting/qpijdbdb.png)
 
![](https://cdn.luogu.com.cn/upload/image_hosting/g49v1xob.png)

可以发现只有橙色的部分变化了。

设 $siz$ 为子树大小，$sum$ 为子树的边权和，如果先走红色子树，橙色部分耗费的时间是 $siz_{blue}\times sum_{red}$，反之亦然。所以只需将 `siz[blue]*sum[red]<siz[red]*sum[blue]` 塞进比较函数，用 sort 对于每一个点的子树排序就行了

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>void read(T &x){
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x*=f;
}
template<typename T,typename ...Args>
void read(T &x,Args &...rest){read(x);read(rest...);}
const int N=1e5+5;

struct edge{int v,w;};
struct node{
    int siz,sum;
    vector<edge> e;
}tr[N];
bool cmp(edge a,edge b){return 1ll*tr[a.v].siz*(tr[b.v].sum+b.w)>1ll*tr[b.v].siz*(tr[a.v].sum+a.w);}
int n,t[N],tim;
long long ans;

void prework(int u,int from){
    tr[u].siz=1;
    tr[u].sum=0;
    for(edge i:tr[u].e){
        int v=i.v,w=i.w;
        if(v==from)continue;
        tr[u].sum+=w;
        prework(v,u);
        tr[u].sum+=tr[v].sum;
        tr[u].siz+=tr[v].siz;
    }
    sort(tr[u].e.begin(),tr[u].e.end(),cmp);
}
void find_treasure(int u,int from){
    for(edge i:tr[u].e){
        int v=i.v,w=i.w;
        if(v==from)continue;
        tim+=w;
        t[v]=tim;
        find_treasure(v,u);
        tim+=w;
    }
}

int main(){
    read(n);
    for(int u,v,w,i=1;i<n;i++){
        read(u,v,w);
        tr[u].e.push_back({v,w});
        tr[v].e.push_back({u,w});
    }
    prework(1,0);
    find_treasure(1,0);
    for(int i=2;i<=n;i++)ans+=t[i];
    printf("%.7lf\n",1.0*ans/(n-1));
    return 0;
}
```


---

## 作者：gan1234 (赞：0)

## 分析

考虑树上 dp，设 $f_i$ 表示以 $i$ 为根的子树，每个点到达时间总和的最小值，$g_i$ 表示遍历完整棵子树所用时间，$siz_i$ 表示子树大小。

最终答案也就是 $\frac{f_1}{n-1}$。

$g_i$ 和 $siz_i$ 的处理很容易，直接子树向上合并就行了。

$f_i$ 怎么求？我们首先需要确定一种最优的遍历儿子顺序，那么 $f_i$ 就可以求出了。

$$f_i\gets\sum_{j\in son_i}(f_j+siz_j\times\sum_{k<j}g_k)$$

这个式子后半部分，$g_k$ 要乘上子树大小的原因是，之前使用的时间会导致每个结点的 $f_x$ 都增大。

可以发现，遍历儿子顺序只会影响 $siz_j\times\sum_{k<j}g_k$，而且交换两个相邻儿子不会对后面的贡献产生影响。

参考经典贪心题[国王游戏](https://www.luogu.com.cn/problem/P1080)，我们可以使用邻项交换法求出最优顺序。

令 $\sum_{k<i}g_k=Sg_i$，推一下式子。

$$siz_i\times Sg_{i-1}+siz_{i+1}\times (Sg_{i-1}+g_i)\le siz_{i+1}\times Sg_{i-1}+siz_{i}\times (Sg_{i-1}+ g_{i+1})$$

$$siz_{i+1}\times g_i\le siz_i\times g_{i+1}$$

直接按照这个式子排一下序就好了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 200005
#define P pair<int,int>
using namespace std;
struct Edge{
	int to,cost;
};
vector<Edge>G[MAXN];
int n;
int f[MAXN],g[MAXN],siz[MAXN];
int cmp(P p1,P p2){
	return p1.first*p2.second<p2.first*p1.second;
}
void dfs(int x,int pre){
	int l=G[x].size();
	siz[x]=1;
	if(l==1&&x!=1)return ;
	for(int i=0;l>i;i++)
		if(G[x][i].to!=pre){
			int y=G[x][i].to;
			dfs(y,x);
			siz[x]+=siz[y];
			f[y]+=G[x][i].cost*siz[y];
			g[y]+=G[x][i].cost*2;
			f[x]+=f[y];
		}
	vector<P>v;
	for(int i=0;l>i;i++)
		if(G[x][i].to!=pre){
			v.push_back(P(g[G[x][i].to],siz[G[x][i].to]));
		}
		
	
	sort(v.begin(),v.end(),cmp);
	for(int i=0;v.size()>i;i++){
		f[x]+=g[x]*v[i].second;
		g[x]+=v[i].first;
	}
	
	
}
signed main(){
	int x,y,z;
	cin>>n;
	for(int i=1;n>i;i++){
		cin>>x>>y>>z;
		G[x].push_back(Edge{y,z});
		G[y].push_back(Edge{x,z});
	}
	dfs(1,0);
	printf("%.7lf",(double)f[1]/(n-1));
	return 0;
}
```

---

## 作者：linyihdfj (赞：0)

## CF101D Castle
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
其实期望是没有什么意思的，因为我们只要可以求出最优的总的时间，除以 $n-1$ 就是期望。

我们可以考虑设 $dp[i]$ 表示以 $i$ 为根的子树从 $i$ 开始走题目要求的值是多少。

那么对于 $dp[i]$ 它的值难道是 $\sum_{j \in son[i]} dp[j]$ 吗？显然不是啊。

因为我们对于第 $i$ 次访问的子树，一定会对 $j > i$ 的子树 $j$ 产生影响，所以只需要把影响算好就好了。

那么假设我们固定了一种转移顺序，也就是 $v[i]$ 表示第 $i$ 个访问的子树，那么我们的 $dp$ 值就是：
$$
dp[i] = \sum_{j} dp_{v_j} + sz[v[j]] \times w[v[j]] + \sum_{k > j} (s[v[j]] + 2\times w[v[j]]) \times sz[v[k]]
$$
这里设 $sz[i]$ 代表 $i$ 这棵子树的大小，$w[i]$ 代表 $fa[i]$ 到 $i$ 权值的大小，$s[i]$ 代表完全遍历 $i$ 这棵子树并回到 $i$ 花费的时间。

那么就是确定转移顺序了，这个转移顺序也就是一个很显然的套路。
我们考虑对于两个儿子 $i,j$ 若 $i$ 在前面更优意味着什么：
首先对于 $i,j$ 谁在前谁在后对于在 $i,j$ 后面的数是没有影响的，只是他们两个之间的影响。

稍微推一下就可以发现其实就是：
$$
(s[i] + 2\times w[i]) \times sz[j] < (s[j] + 2\times w[j]) \times sz[i]
$$
然后按照这个值排一下序按照排序后的序列直接做就好了。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6+5;
struct edge{
	int nxt,to,val;
	edge(){}
	edge(int _nxt,int _to,int _val){
		nxt = _nxt,to = _to,val = _val;
	}
}e[2 * N];
int cnt,head[N],dp[N],s[N],sz[N],val[N];
bool cmp(int a,int b){
	return (s[a] + 2 * val[a]) * sz[b] < (s[b] + 2 * val[b]) * sz[a];
}
void add_edge(int from,int to,int val){
	e[++cnt] = edge(head[from],to,val);
	head[from] = cnt;
}
void dfs(int now,int fath){
	sz[now] = 1;//记录子树大小 
	s[now] = 0; //记录遍历子树需要花费的时间 
	vector<int> son;
	for(int i = head[now]; i;i = e[i].nxt){
		int to = e[i].to;
		if(to == fath)	continue;
		dfs(to,now);son.push_back(to);
		val[to] = e[i].val;
		sz[now] += sz[to];s[now] = s[now] + s[to] + 2 * val[to];
	}
	sort(son.begin(),son.end(),cmp);
	int tmp = 0;
	for(int i : son)	tmp += sz[i];
	for(int to : son){
		tmp -= sz[to];
		dp[now] = dp[now] + dp[to] + sz[to] * val[to] + (s[to] + 2 * val[to]) * tmp;
	}
}
signed main(){
	int n;
	scanf("%lld",&n);
	for(int i=1; i<n; i++){
		int from,to,val;
		scanf("%lld%lld%lld",&from,&to,&val);
		add_edge(from,to,val);add_edge(to,from,val);
	}
	dfs(1,0);
	printf("%.8f\n",1.0 * dp[1] / (n - 1));
	return 0;
} 
```

---

