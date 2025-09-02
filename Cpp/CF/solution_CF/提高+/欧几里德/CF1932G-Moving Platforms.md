# Moving Platforms

## 题目描述

有一个迷宫，迷宫由 $n$ 个平台组成，所有平台间由 $m$ 条通道相连。

每个平台都在某个高度 $l_i$ 上， $l_i$ 是一个 $0$ 到 $H - 1$ 的整数。对于每一步移动，如果你当前在平台 $i$ 上，你可以选择停留在原地或者移动到另一个平台 $j$ 上。如果要移动到平台 $j$ ，那么它们必须由通道连接，并且它们的高度必须相同，即 $l_i = l_j$。

在每一步移动之后，所有平台的高度都会改变。对于所有 $i$，平台 $i$ 的新高度计算为 $l'_i = (l_i + s_i) \bmod H$。

你的起点是平台 $1$ 。请找到到达平台 $n$ 所需的最少步骤数。

## 样例 #1

### 输入

```
3
3 3 10
1 9 4
2 3 0
1 2
3 2
1 3
2 1 10
1 2
4 6
1 2
8 7 25
22 14 5 3 10 14 11 1
9 5 4 10 7 16 18 18
2 8
6 3
3 5
7 5
2 6
1 4
4 7```

### 输出

```
6
-1
52```

# 题解

## 作者：紊莫 (赞：6)

exgcd + dijkstra。  

---

首先求两点间最短路使用 dijkstra 算法解决，问题在于如何求解两点之间的边权。

根据题目要求，我们设在 $x$ 秒时 $l_u = l_v$。

则有：

$$\begin{aligned}
l_u+xs_u &\equiv l_v + xs_v \pmod{H}\\
l_u+xs_u + yH &=  l_v + xs_v \\
(s_u - s_v)x + Hy &= l_v - l_u
\end{aligned}$$

然后可以使用 exgcd 求出一个 $x$ 的可行解，然后要求出大于等于 $dis_u$ 的最小解。

首先构造出通解（设 $g = \gcd (s_u - s_v,H)$）：

$$
\left\{\begin{matrix}
x = x_0 + k \times \dfrac{H}{g}
 \\
y = y_0 + k \times \dfrac{s_u - s_v}{g}
\end{matrix}\right.
$$

首先算出 $x$ 的最小非负整数解记为 $x_0$，然后解如下不等式：

$$x_0 + k \times \dfrac{H}{g} >dis_u$$

求出 $x$ 后边权即为 $x+1$。

```cpp
// LUOGU_RID: 147990221
#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;

const int N = 200005, M = (N << 1), inf = 1e18, mod = 1e9 + 7;
int n, m, H, a[N], l[N], s[N], d[N], v[N];
vector<int> G[N];
struct node {
  int now, dis;
  bool operator<(node x) const { return dis > x.dis; }
};
int exgcd(int a, int b, int &x, int &y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  int d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}
void solve() {
  cin >> n >> m >> H;
  F(i, 1, n) G[i].clear(), d[i] = inf, v[i] = 0;
  F(i, 1, n) cin >> l[i];
  F(i, 1, n) cin >> s[i];
  F(i, 1, m) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  priority_queue<node> q;
  q.push({1, 0}), d[1] = 0;
  while (q.size()) {
    int f = q.top().now;
    q.pop();
    if (v[f]) continue;
    v[f] = 1;
    for (auto i : G[f]) {
      int w, x, y, g = exgcd((s[f] - s[i] + H) % H, H, x, y), t;
      if ((l[i] - l[f]) % g != 0) continue; // 无解退出
      x = x * (l[i] - l[f]) / g; // 算出原方程的解
      t = abs(H / g), x = (x % t + t) % t; // 求出最小非负整数解
      if (d[f] > x) x = x + (d[f] - x + t - 1) / t * t; //调大 x
      if (d[i] > x + 1) {
        d[i] = x + 1;
        q.push({i, d[i]});
      }
    }
  }
  if (d[n] >= inf) cout << "-1\n";
  else cout << d[n] << '\n';
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) solve();
  return 0;
}

```

UPD：原题解 ``inf`` 值有误，修改并优化了代码。

---

## 作者：是青白呀 (赞：3)

## 简要题意

有 $n$ 个平台，初始时它们的高度为 $l_i$，每隔一秒平台 $i$ 的高度都会从 $l_i$ 变为 $(l_i+s_i)\bmod H$。当两个平台高度相同时，你可以花费 $1$ 秒从一个平台走到另一个平台。求在初始时刻从 $1$ 号平台走到 $n$ 号平台所需的最短时间。

## 题解

考虑到尽早到达一个平台一定是不劣的，于是我们跑一遍最短路，在更新下一个点的距离的时候，将边权动态地设置为要等待的时长即可。

考虑如何求要等待的时长。假设要等待 $i$ 平台和 $j$ 平台高度变为相同，设当前时刻 $i$ 平台的高度为 $h_i$，$j$ 平台的高度为 $h_j$。当两个平台达到同一高度时，变化快的平台可能已经比变化慢的平台多跳了若干圈。不妨设 $s_i>s_j$，等待时间为 $x$ 秒，则可列出方程 $x(s_i-s_j)=kH+h_j-h_i$，其中 $x$ 和 $k$ 都是变量，利用 exgcd 求两者同时取到非负整数的前提下，$x$ 的最小解即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define lowbit(x) x&(-x)
#define mp make_pair
#define fir first
#define sec second
#define int long long
#define pii pair<int,int>
using namespace std;
typedef long long ll;
const int N=1e5+5,M=2e5+5,S=(1<<22)+5,mo=998244353,inf=1e18+7,bs=19491001;
const double eps=1e-8;
inline void read(int &p){
	int x=0,w=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int T;
int n,m,h,l[N],s[N];
struct edge{
	int to,nxt;
}e[2*N];
int fir[N],np;
void add(int x,int y){
	e[++np]=(edge){y,fir[x]};
	fir[x]=np;
}
bool vis[N];
int dis[N];
int exgcd(int a,int b,int &x1,int &y1){
	if(!b){
		x1=1,y1=0;
		return a;
	}
	int x2,y2;
	int gcdn=exgcd(b,a%b,x2,y2);
	x1=y2,y1=x2-a/b*y2;
	return gcdn;
}
int getd(int x,int y,int tms){
	if(s[x]<s[y])swap(x,y);
	int stx=(l[x]+tms%h*s[x]%h)%h,sty=(l[y]+tms%h*s[y]%h)%h; 
	int a=s[x]-s[y],b=h,c=(sty-stx+h)%h;
	int gcdn=__gcd(a,b);
	if(gcdn!=__gcd(gcdn,c))return inf;
	int nx,ny;
	exgcd(a,b,nx,ny);
	nx=c*nx/gcdn,ny=c*ny/gcdn;
	int dx=b/gcdn,dy=a/gcdn;
	if(ny>0){
        int cnt=ceil(ny/1.0/dy);
        nx+=cnt*dx,ny-=cnt*dy;
    }
    else if(ny<0){//倒过来之后,nx取最小的正数，ny取最大的负数，ny增大，nx减小 
    	int cnt=(-ny)/1.0/dy;
        nx-=cnt*dx,ny+=cnt*dy;
    }
    if(nx<0){
    	int cnt=ceil(-nx/1.0/dx);
    	nx+=dx*cnt;
    }
    return nx;
}
void dij(){
	rep(i,1,n)
	    dis[i]=inf;
	dis[1]=0;
	priority_queue<pii,vector<pii>,greater<pii>>q;
	q.push(mp(0,1));
	while(!q.empty()){
		pii nw=q.top();
		q.pop();
		if(vis[nw.sec])continue;
		vis[nw.sec]=1;
		for(int i=fir[nw.sec];i;i=e[i].nxt){
			int j=e[i].to;
			if(vis[j])continue;
			int val=getd(nw.sec,j,nw.fir);
			if(dis[j]>nw.fir+val+1)dis[j]=nw.fir+val+1,q.push(mp(dis[j],j));
		}
	}
}
void solve(){
	read(n),read(m),read(h),np=0;
	rep(i,1,n)
	    read(l[i]),vis[i]=0,fir[i]=0;
	rep(i,1,n)
	    read(s[i]);
	rep(i,1,m){
		int x,y;
		read(x),read(y),add(x,y),add(y,x); 
	}
	dij();
	printf("%lld\n",dis[n]==inf?-1:dis[n]);
}
signed main(){
	read(T);
	while(T--)
	    solve();
	return 0;
}
```

---

## 作者：Engulf (赞：2)

强行结合题挺没意思的。

对于两个平台 $u, v$，我们关心它们什么时候是联通的，设它们在 $x$ 步移动后联通，则有方程：

$$l_u + xs_u \equiv l_v + xs_v (\bmod H)$$

这个东西就是 [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)，你至少得会 exgcd。

移项，整理得

$$(s_u - s_v)x \equiv l_v - l_u (\bmod H)$$

这个方程等价于存在一个整数 $y$ 使得

$$(s_u - s_v)x + Hy = l_v - l_u$$

记 $d = \gcd(s_u - s_v, H)$。
- 若 $d \nmid l_v - l_u$，该不定方程无解（[裴蜀定理](https://oi-wiki.org/math/number-theory/bezouts/)）。
- 否则 $d \mid l_v - l_u$。通过 exgcd 我们求解出一组 $(x_0, y_0)$ 使得 $(s_u - s_v)x_0 + Hy_0 = d$，两边同乘 $\dfrac{l_v - l_u}{d}$ 得

$$(s_u - s_v)\dfrac{l_v - l_u}{d}x_0 + H\dfrac{l_v - l_u}{d}y_0 = l_v - l_u$$

故原方程 $(s_u - s_v)x + Hy = l_v - l_u$ 的解为

$$\left\{\begin{matrix}

x = \dfrac{l_v - l_u}{d}x_0+k\dfrac{H}{d}
\\
y = \dfrac{l_v - l_u}{d}y_0 - k\dfrac{s_u - s_v}{d}
\end{matrix}\right. k \in \mathbb{Z} $$

因为步数是非负整数，我们关心该方程的非负整数解。

先求 $x = \dfrac{l_v - l_u}{d}x_0+k\dfrac{H}{d} \ge 0$ 的最小非负整数 $x$，不难发现欲求的 $x$ 为 $\dfrac{l_v - l_u}{d}x_0 \bmod \dfrac{H}{d}$ 的最小非负整数。

那么平台 $u$ 和 $v$ 会在 $x + k\dfrac{H}{d}, k \in \mathbb{N}$ 步后联通。每条边存储 $x$ 和 $\dfrac{H}{d}$，考虑跑最短路。

记 $dis_u$ 为到达 $u$ 的最少步数。松弛操作，我们关心从 $u$ 到 $v$ 的最少步数，那么肯定是先等待，直到 $u, v$ 联通，一步走过去。即，求出 $x + k\dfrac{H}{d} \ge dis_u, k \in \mathbb{N}$ 的最小 $k$，移项可得 $k \ge \dfrac{(dis_u-x)d}{H}$，因为 $k \in \mathbb{N}$，所以 $k_{\min} = \left\lceil\dfrac{(dis_u-x)d}{H} \right\rceil$。


那么此时 $u$ 到 $v$ 的步数就是 $x+k\dfrac{H}{d} + 1$。

若你 Time Limit Exceed on Test 2，多半是因为使用了 spfa。在边权非负时，请使用 dijkstra 求最短路。

实现用的优先队列，所以时间复杂度 $O(m\log V + m\log m)$，那个 $\log V$ 是跑 exgcd 的复杂度，$V = \max\limits_{i=1}^{n}(|s_u-s_v|, H)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using edge = tuple<int, ll, ll>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 1e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int exgcd(int a, int b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

int n, m, h;

vector<edge> g[N];

int l[N], s[N];

ll dis[N];
bool vis[N];

ll dijkstra(int s, int t) {
    for (int i = 1; i <= n; i++) dis[i] = INF, vis[i] = 0;

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;

    q.push({0, s}); dis[s] = 0;
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w, t]: g[u]) {
            ll k = ceil(1.0 * (dis[u] - w) / t);
            if (dis[v] > w + k * t + 1) {
                dis[v] = w + k * t + 1;
                q.push({dis[v], v});
            }
        }
    }

    return dis[t] == INF ? -1 : dis[t];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        cin >> n >> m >> h;

        for (int i = 1; i <= n; i++) cin >> l[i];
        for (int i = 1; i <= n; i++) cin >> s[i];

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            // equation: l[u] + w * s[u] = l[v] + w * s[v] (mod h)

            ll w, y;
            int d = exgcd(s[u] - s[v], h, w, y);
            ll t = 0;

            if ((l[v] - l[u]) % d) w = INF;
            else {
                w *= (l[v] - l[u]) / d;
                t = abs(h / d);
                w = (w % t + t) % t;
            }

            if (!w) w = h;
            g[u].emplace_back(v, w, t);
            g[v].emplace_back(u, w, t);
        }

        cout << dijkstra(1, n) << "\n";

        for (int i = 1; i <= n; i++) g[i].clear();
    }
    return 0;
}
```

---

## 作者：北文 (赞：2)

首先根据题意可以在一个点停留，那么只需要计算出到达每个点的最短时间即可。这跟 dij 的更新方法是相吻合的。我们套用 dij 的模板，现在的问题就是求出在 $t$ 时刻， $x,y$ 间的距离。  
这也是 trival 的，考虑在 $t$ 时刻，$x$ 的等级和 $y$ 的等级已知，设为 $lx, ly$   
那么我们要求一个最小的时间 $d$ 使得：   
$$lx+ds_x \equiv ly+ds_y  \pmod m$$  
移项一下可以得到：  
$$(lx-ly)+d(s_x-s_y) \equiv 0 \pmod m$$  
这是 exgcd 模板题，详细请转 [Ex_gcd](https://www.luogu.com.cn/problem/P5656)，在这里简单说说：   
令 $A=lx-ly, B=s_x-s_y$ ，恒等式的经典处理办法，设 $k$ 有：  
$$A+dB=mk$$  
移项得：  
$$dB-mk=-A$$  
用 exgcd 可以求出 $d$ 的最小解。记得开 long long，和及时取模。  
复杂度是 dij 的 $n\log n$ 加上求距离的复杂度 $\log m$，总 $n\log nm$。

---

## 作者：zzxLLL (赞：1)

倒序开题，写错一句，痛失一血。/kk

---

一个容易发现的结论：对于一个点，早到总是比晚到好。显然地，假设在 $t$ 时刻到达 $u$，然后等到 $t_0$ 时刻到达 $v$，那么在小于 $t$ 时刻到达 $u$ 也一定能在 $t_0$ 或之前到达 $v$，但是大于 $t$ 时刻就只能在 $t_0$ 或之后到达 $v$。

依据这个就可以跑 Dijkstra：设 $f_u$ 为 $1$ 到 $u$ 的最短时间，那么如果要走到 $v$：

$$l_u+(t-1)\cdot s_u\equiv l_v+(t-1)\cdot s_v(\bmod\space H)$$

其中 $t$ 是大于 $f_u$ 且满足方程的最小整数。变形一下：

$$(s_u-s_v)\cdot t+H\cdot x=l_v-l_u$$

然后直接 exgcd 即可。时间复杂度 $O(n\log m)$。


```cpp
#include <bits/stdc++.h>
#define int long long
const int M = 2e5 + 10;
const long long inf = 4e18;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    long long d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}
long long cal(long long a, long long b, long long c) {
    long long x, y;
    long long gc = exgcd(a, b, x, y);
    x = x * c / gc, b /= gc;
    if (b < 0) b = -b;
    long long ans = x % b;
    if (ans <= 0) ans += b;
    return ans;
}
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long f[M];
int n, m, t, H, l[M], s[M];
std::vector<int> g[M];

bool vis[M];
struct Node {
    long long dis;
    int x;
    Node(long long _d = 0, int x = 0): dis(_d), x(x) {}
    inline bool operator > (const Node& o) const {
        return dis > o.dis;
    }
};
inline int h(int x, long long t) {
    return (l[x] + (t - 1) % H * s[x] % H) % H;
}
std::priority_queue<Node, std::vector<Node>, std::greater<Node> > q;
inline void Dijkstra() {
    f[1] = 0;
    q.push(Node(f[1], 1));
    while (!q.empty()) {
        Node t = q.top(); q.pop();
        if (vis[t.x]) continue;
        vis[t.x] = true;
        for (auto v : g[t.x]) {
            if (s[v] == s[t.x]) {
                if (l[v] != l[t.x]) continue;
                if (f[v] > f[t.x] + 1) {
                    f[v] = f[t.x] + 1;
                    q.push(Node(f[v], v));
                }
            } else {
                int u = t.x;
                long long A = s[u] - s[v], B = H, C = h(v, t.dis) - h(u, t.dis);
                if (C % gcd(A, B)) continue;
                long long x = cal(A, B, C);
                if (f[v] > f[t.x] + x) {
                    f[v] = f[t.x] + x;
                    q.push(Node(f[v], v));
                }
            }
        }
    }
}

signed main() {
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld%lld", &n, &m, &H);
        for (int i = 1; i <= n; i++) f[i] = inf, g[i].clear(), vis[i] = false;
        for (int i = 1; i <= n; i++) scanf("%lld", &l[i]);
        for (int i = 1; i <= n; i++) scanf("%lld", &s[i]);
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%lld%lld", &u, &v);
            g[u].push_back(v), g[v].push_back(u);
        }
        Dijkstra();
        if (f[n] == inf) printf("-1\n");
        else printf("%lld\n", f[n]);
    }
    return 0;
}
```

---

## 作者：Cure_Wing (赞：1)

更新 2024.2.25：修正了同余符号的写法。

------------

[CF1932G Moving Platforms](https://www.luogu.com.cn/problem/CF1932G)

### 思路

我们看到人在连边上走，自然而然的就想到的最短路。

但是直接告诉我们的只有边，边权似乎没有出现。

注意到题目描述中每一个时刻你可以不动，也可以走向一个直接相连的等高的平台。于是我们把边权定义为等待这一平台等高的时间和走过这一条边的时间。

假设我们走到 $u$ 点用了 $t$ 秒。显然，$t$ 越小越好。我们假设现在要通过 $(u,v)$ 去到 $v$，那么此时 $l'_u=(l_u+s_u\times t)\bmod h,l'_v=(l_v+s_v\times t)\bmod h$。贪心的想，为了让等的时间越少，肯定一旦出现等高就走过这条边，也就是对于下面这个式子：

$$l'_u+s_u\times w\equiv l'_v+s_v\times w\pmod h$$

我们要找到一个最小的正整数 $w$，使得它满足这个等式。

把它转化成等式，就是：

$$l'_u+s_u\times w-(l'_v+s_v\times w)=kh$$

$$(s_u-s_v)w-kh=l'_v-l'_u$$

我们发现这个等式就是标准的二元一次方程，解它的整数根就可以了。

具体怎么求可以参见[模板题](https://www.luogu.com.cn/problem/P5656)。

容易发现，由于 $w$ 为正整数，所以每条边权非负，于是我们就可以开心的使用 `Dijkstra` 跑最短路了。

注意求最小正整数根时，不要使用 `ceil`，不然会由于精度问题而爆炸。

时间复杂度 $O(\sum(n+m(\log m+\log H)))$，`Dijkstra` 用优先队列实现。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
using std::cin;using std::cout;
constexpr int N=100005;
constexpr long long inf=1e18;
int t,n,m,h,l[N],s[N],u,v;
long long dis[N];
bool vis[N];
std::vector<int>edge[N];
struct A{int u;long long dis;inline bool operator<(const A &b)const{return dis>b.dis;}};
std::priority_queue<A>q;
inline int exgcd(long long &x,long long &y,int a,int b){//解二元一次方程
	if(b==0){x=1;y=0;return a;}
	int t=exgcd(x,y,b,a%b);
	long long w=x;
	x=y;
	y=w-a/b*y;
	return t;
}
inline long long get(long long dis,int u,int v){//不开 long long 见祖宗
	int u1=(l[u]+1ll*(dis%h)*s[u]%h)%h,v1=(l[v]+1ll*(dis%h)*s[v]%h)%h,a=s[u]-s[v],b=h,c=v1-u1;//计算参数
	long long x,y;
	if(c<0){a=-a;b=-b;c=-c;}
	int aa=std::abs(a),bb=std::abs(b);
	int p=exgcd(x,y,aa,bb);
	if(c%p) return inf;//无解边权定为无穷大
	x*=c/p;
	if(a<0) x=-x;
	int w=bb/p;
	x=(x%w+w)%w;//注意要使用取模
	return x;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;cout<<(dis[n]==inf?-1:dis[n])<<'\n'){
		cin>>n>>m>>h;
		for(int i=1;i<=n;++i){edge[i].clear();cin>>l[i];dis[i]=inf;vis[i]=0;}//多测不清空，爆零两行泪
		for(int i=1;i<=n;++i) cin>>s[i];
		for(int i=1;i<=m;++i){
			cin>>u>>v;
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		dis[1]=0;q.push(A{1,0});
		while(!q.empty()){
			A k=q.top();q.pop();
			if(vis[k.u]) continue;
			vis[k.u]=1;
			for(int i:edge[k.u]){
				long long can=get(k.dis,k.u,i)+1;//不要忘记走过这条边需要 1 的时间
				if(dis[k.u]+can<dis[i]){
					dis[i]=dis[k.u]+can;
					q.push(A{i,dis[i]});
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：MaxBlazeResFire (赞：1)

怎么有人打完 ARC 还赛后 div3 双开的？

先写个 dijkstra 最短路板子。很明显，我们只需要解决给定 $dis_u,u,v$，求 $u$ 到 $v$ 最小需要的等待时间。

也就是说，记 $S_u=l_u+dis_u\times s_u,S_v=l_v+dis_u\times s_v$，我们需要找到一个最小的非负整数 $x$ 满足 $S_u+s_ux\equiv S_v+s_vx\pmod H$。

先判掉 $s_u=s_v$ 的情况，转化为 $A\equiv Bx\pmod H$。然后除掉 $\gcd(A,B)$ 变成 $A'\equiv B'x\pmod {H'}$（$\displaystyle H'=\frac{H}{\gcd(A,B)}$），此时如果 $\gcd(B',H)\neq 1$ 则无解。

然后用 exgcd 求解 $\displaystyle\frac{1}{B'}$，返回 $\displaystyle A'\times\frac{1}{B'}\bmod H'$ 的值即可。

复杂度 $O((n+m)(\log n+\log V))$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 100005

const int INF = 1000000000000000ll;

int n,m,H,l[MAXN],s[MAXN],dist[MAXN],vis[MAXN];
vector<int> E[MAXN];

struct node{ int x,dis; inline bool operator <( node A )const{ return A.dis < dis; } };

int gcd( int x , int y ){ return y ? gcd( y , x % y ) : x; }

int exgcd( int a , int b , int &x , int &y ){
	if( b == 0 ){ return x = 1,y = 0,a; }
	int g = exgcd( b , a % b , x , y );
	int x0 = y,y0 = x - y * ( a / b );
	x = x0,y = y0;
	return g;
}

inline int Qcost( int u , int v , int t ){
	int Su = ( l[u] + t % H * s[u] % H ) % H,Sv = ( l[v] + t % H * s[v] % H ) % H;
	int su = s[u],sv = s[v];
	if( su == sv && Su == Sv ) return 1;
	else if( su == sv ) return -1;
	int rg = ( sv - su + H ) % H;
	int lg = ( Su - Sv + H ) % H;
	int g = gcd( lg , rg );
	int Mod = H / gcd( H , g ); lg /= g,rg /= g;
	if( gcd( Mod , rg ) != 1 ) return -1;
	int X,Y; exgcd( rg , Mod , X , Y );
	if( X < 0 ) X += ( ( -X ) / Mod + 1 ) * Mod; X %= Mod;
	return ( lg + Mod ) % Mod * X % Mod + 1;
}

inline void dijkstra(){
	for( int i = 1 ; i <= n ; i ++ ) dist[i] = INF,vis[i] = 0;
	priority_queue<node> Q; Q.push( node{ 1 , 0 } ),dist[1] = 0;
	while( !Q.empty() ){
		int u = Q.top().x; Q.pop();
		if( vis[u] ) continue;
		vis[u] = 1;
		for( int v : E[u] ){
			int c = Qcost( u , v , dist[u] );
			if( c == -1 ) continue;
			if( dist[v] > dist[u] + c ){
				dist[v] = dist[u] + c;
				if( !vis[v] ) Q.push( node{ v , dist[v] } );
			}
		}
	}
}

inline void solve(){
	scanf("%lld%lld%lld",&n,&m,&H);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&l[i]);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&s[i]);
	for( int i = 1 ; i <= m ; i ++ ){
		int u,v; scanf("%lld%lld",&u,&v);
		E[u].emplace_back( v ),E[v].emplace_back( u );
	} dijkstra();
	if( dist[n] == INF ) puts("-1");
	else printf("%lld\n",dist[n]);
	for( int i = 1 ; i <= n ; i ++ ) E[i].clear();
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：Vitamin_B (赞：1)

# 思路
首先这题要用最短路是显然的，但是边权不固定（但对 dijkstra 过程没影响，因为边权没有负数）。在做 dijkstra 的时候，我们的边权取决于不固定的当前高度和固定的增长高度，然后类似 P1516 用 exgcd 把边权算出来松弛即可。
# 注意事项
请及时取模，否则在乘法和 exgcd 时会爆 `long long`。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const ll inf = 1e18;
struct node {
	int x;
	ll dis;
	bool operator < (const node& t) const {
		return dis > t.dis;
	}
} ;
ll exgcd (ll a, ll b, ll& x, ll& y) {
	if (! b) {
		x = 1, y = 0;
		return a;
	}
	ll g = exgcd (b, a % b, x, y), tmp = x;
	x = y, y = tmp - a / b * y;
	return g;
}
int t, n, m, x, y;
ll h, l[100005], s[100005], dis[100005], a, b, w, ans1, ans2, g;
vector <int> v[100005];
priority_queue <node> q;
ll exg (ll a, ll b, ll c) {
	if (a < 0)
		a = -a, c = -c;
	g = exgcd (a, b, ans1, ans2);
	if (c % g)
		return inf;
	b /= g, c /= g;
	return (ans1 * c % b + b) % b;
}
ll bfs () {
	fill (dis + 2, dis + n + 1, inf);
	q.push ({1, 0});
	while (! q.empty ()) {
		node t = q.top ();
		if (t.x == n) {
			while (! q.empty ())
				q.pop ();
			return t.dis;
		}
		q.pop ();
		if (t.dis > dis[t.x])
			continue ;
		for (int& i : v[t.x]) {
			w = exg (s[i] - s[t.x], h, (t.dis % h * (s[t.x] - s[i]) + l[t.x] - l[i]) % h) + 1;
			if (t.dis + w < dis[i])
				q.push ({i, dis[i] = t.dis + w});
		}
	}
	return -1;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> m >> h;
		for (int i = 1; i <= n; ++ i)
			cin >> l[i], v[i].clear ();
		for (int i = 1; i <= n; ++ i)
			cin >> s[i];
		while (m --) {
			cin >> x >> y;
			v[x].emplace_back (y);
			v[y].emplace_back (x);
		}
		cout << bfs () << '\n';
	}
	return 0;
}
```

---

