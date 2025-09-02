# [ABC204E] Rush Hour 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc204/tasks/abc204_e

AtCoder国には $ N $ 個の都市と $ M $ 本の道路があります。

都市には $ 1 $ から $ N $ の番号が、道路には $ 1 $ から $ M $ の番号が振られています。道路 $ i $ は都市 $ A_i $ と都市 $ B_i $ を双方向に結びます。

AtCoder国には時刻 $ 0 $ をピークとするラッシュアワーがあり、時刻 $ t $ に道路 $ i $ の通行を始めると、移動するのに $ C_i+\ \left\lfloor\ \frac{D_i}{t+1}\ \right\rfloor $ の時間がかかります。 ( $ \lfloor\ x\rfloor $ は $ x $ を超えない最大の整数を表す)

高橋君は時刻 $ 0 $ またはそれ以降の **整数時刻に** 都市 $ 1 $ を出発して、道路を通行することで都市 $ N $ へ向かおうとしています。

高橋君が各都市で **整数時間** 待機することができるとき、高橋君が都市 $ N $ に到達することができる最も早い時刻を出力してください。なお、制約の下で答えは整数になることが証明できます。

ただし、都市 $ N $ に到達できないときはかわりに `-1` を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- $ 0\ \leq\ C_i,D_i\ \leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

最初に都市 $ 1 $ で時刻 $ 1 $ まで待機します。そして時刻 $ 1 $ に道路 $ 1 $ を使って移動をすると、移動に $ 2+\left\lfloor\ \frac{3}{1+1}\ \right\rfloor\ =\ 3 $ の時間がかかり、都市 $ 2 $ には時刻 $ 4 $ に到着することができます。 時刻 $ 4 $ より早く都市 $ 2 $ に到着することはできません。

### Sample Explanation 2

同じ都市の組を結ぶ道路が複数ある場合や、同じ都市に戻ってくる道路がある場合もあります。

### Sample Explanation 3

都市 $ 1 $ から都市 $ N $ に至る経路がないこともあります。

## 样例 #1

### 输入

```
2 1
1 2 2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
2 3
1 2 2 3
1 2 2 1
1 1 1 1```

### 输出

```
3```

## 样例 #3

### 输入

```
4 2
1 2 3 4
3 4 5 6```

### 输出

```
-1```

## 样例 #4

### 输入

```
6 9
1 1 0 0
1 3 1 2
1 5 2 3
5 2 16 5
2 6 1 10
3 4 3 4
3 5 3 10
5 6 1 100
4 2 0 110```

### 输出

```
20```

# 题解

## 作者：Redamancy_Lydic (赞：2)

变形的 dijkstra。

先思考什么情况下需要等待以及等待多长时间最优。我们把题目上的计算方法按照当前的时间 $t$ 和通过所需的时间 $f(t)$ 列个函数关系：

$$f(t)=t+c+\lfloor \frac{d}{t+1}\rfloor$$

然后用 [Desmos](https://www.desmos.com/calculator?lang=zh-CN) 画个图可以得到图像（其实就是对勾函数）：

![image](https://cdn.luogu.com.cn/upload/image_hosting/00780iyc.png?x-oss-process=image/resize,m_lfit,h_800,w_800)


因为 $c,d\geq 0$，所以我们只考虑上半部分。容易发现这个函数是有最值的，根据高一数学知识可得此时 $t=\sqrt{d}-1$。

于是我们得到初步结论：跑最短路的时候比较当前时间和上面求出来的东西，如果当前时间已经在其之后，那么根据图象发现等待是不优的，所以正常转移。否则我们直接等到出现最小值的时刻再走就行了。

因为涉及到浮点数运算，所以需要注意精度问题。

一开始的时候发现无解判错了，怎么改都改不过，于是写了个并查集（我好菜）。

[提交记录](https://atcoder.jp/contests/abc204/submissions/58074074)

---

## 作者：_Ponder_ (赞：2)

[Rush Hour 2](https://www.luogu.com.cn/problem/AT_abc204_e)

### 题目大意

给定一张无向图，边带两个参数 $c_i,d_i$，在 $t$ 时间时经过第 $i$ 条边所需的时间是 $c_i+\lfloor\frac{d_i}{t+1}\rfloor$，求在时间 $0$ 时出发，在每个点可以停留非负整数时间，从点 $1$ 到点 $n$ 所需的最短时间。

### 思路分析

首先，容易发现在时间 $t$ 时经过第 $i$ 条边后的总时间是：$t+c_i+\lfloor\frac{d_i}{t+1}\rfloor$。

那么不妨设函数 $f(t)=t+c_i+\lfloor\frac{d_i}{t+1}\rfloor$，由均值不等式容易得 $f(t)_{\min}=f(\sqrt{d_i}-1)$。

也就是说，当我们想经过某一条边时，如果当前时间大于 $\sqrt {d_i}-1$，那么不用等待直接通过，否则等到 $\sqrt{d_i}-1$ 时再通过。

那么就可以使用普通的 Dijkstra 解决了。

### 代码

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
#define int long long
const int N=200100;

int n,m,idx=1,in1,in2,in3,in4;
int to[N],nxt[N],head[N];
int fa[N],vis[N];
int dis[N],c[N],d[N];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

void add(int u,int v,int x,int y){
    idx++;to[idx]=v;nxt[idx]=head[u];head[u]=idx;c[idx]=x;d[idx]=y;
}

struct Node{
    int x,time;
    bool operator < (const Node &b) const{
        return time>b.time;
    }
}now;

priority_queue <Node> q;

void Dijkstra(){
    memset(dis,0x3f,sizeof dis);
    dis[1]=0;q.push(Node{1,0});
    while(!q.empty()){
        now=q.top();q.pop();
        if(vis[now.x]) continue;
        vis[now.x]=1;
        for(int i=head[now.x];i;i=nxt[i]){
            int v=to[i],t;
            if(now.time<=round(sqrt(d[i]))-1) t=round(sqrt(d[i]))-1;
            else t=now.time; //判断通过时间
            if(dis[v]>t+c[i]+d[i]/(t+1)){
                dis[v]=t+c[i]+d[i]/(t+1);
                q.push(Node{v,dis[v]});
            }
        }
    }
}

signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++){
        scanf("%lld%lld%lld%lld",&in1,&in2,&in3,&in4);
        add(in1,in2,in3,in4);add(in2,in1,in3,in4);
        fa[find(in1)]=find(in2);
    }
    if(find(1)!=find(n)){cout<<"-1\n";return 0;}//并查集判连通
    Dijkstra();
    cout<<dis[n]<<'\n';
    return 0;
}
```

---

## 作者：zhujiangyuan (赞：1)

[[ABC204E] Rush Hour 2](https://www.luogu.com.cn/problem/AT_abc204_e)

一年前不会，现在秒了。

设第 $i$ 条边的两个端点为 $u$ 和 $v$，从 $u$ 离开走向 $v$ 的时刻为 $t$，则到达 $v$ 的时刻为 $t+c_i+\lfloor \frac{d_i}{t+1}\rfloor$，转化一下，变为 $t+1+\lfloor \frac{d_i}{t+1}\rfloor+c_i-1$，后面 $c_i-1$ 是定值，前面利用基本不等式可以得到最小值为 $2\sqrt{d_i}$，且此时 $t=\sqrt{d_i}-1$。

跑 Dijkstra，对于从 $u$ 到 $v$，如果 $dis_u\le \sqrt{d_i}-1$，可以等到 $\sqrt{d_i}-1$ 时再走，这样到 $v$ 的时间最早。如果 $dis_u>\sqrt{d_i}-1$，根据对勾函数图像，应该立即出发，否则到达 $v$ 的时间更晚。

时间复杂度为 Dijkstra 复杂度 $O((n+m)\log m)$。

[AC 代码](https://atcoder.jp/contests/abc204/submissions/59325303)

---

## 作者：This_Rrhar (赞：1)

设到达一点的时间为 $t$，并且在 $t'$ 时出发，根据题意可知，我们要求的是

$$
\left(t'+c_i+\left\lfloor\dfrac{d_i}{t'+1}\right\rfloor\right)_{\min}
$$

忽略向下取整符号，对原式求导得

$$
1-\dfrac{d_i}{(t'+1)^2}
$$

令其为 $0$，解得

$$
t'=\sqrt{d_i}-1
$$

注意根据题意有 $t\le t'$，若 $t>t'$ 则立即出发即可。

故可在 $O(1)$ 时间内计算出 $t'$，剩下就是最短路板子。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

#define N 100001

const ll INF=0x3f3f3f3f3f3f3f3fll;

struct edge
{
	ll v,x,y;
	double sq;
};
struct node
{
	ll i,t;
	bool operator<(const node&B)const{return t==B.t?i>B.i:t>B.t;}
};
priority_queue<node>q;
vector<edge>e[N];
bool vis[N];
ll dis[N];
ll nd(ll t,ll x,ll y,double sq)
{
	if(sq<t+1)return t+x+y/(t+1);
	if(ceil(sq)<t+1)return ll(sq)+y/ll(sq)+x-1;
	return min(ll(sq)+y/ll(sq),ll(ceil(sq))+y/ll(ceil(sq)))+x-1;
}
void dijkstra()
{
	memset(dis,0x3f,sizeof(dis)),dis[1]=0,q.push({1,0});
	while(!q.empty())
	{
		node u=q.top();
		q.pop();
		if(!vis[u.i])
		{
			vis[u.i]=true;
			for(auto i:e[u.i])
			{
				ll t=nd(u.t,i.x,i.y,i.sq);
				if(t<dis[i.v])q.push({i.v,dis[i.v]=t});
			}
		}
	}
}

ll n,m;

ll u,v,x,y;

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	while(m--)
	{
		cin>>u>>v>>x>>y;
		if(u!=v)e[u].push_back({v,x,y,sqrt(y)}),e[v].push_back({u,x,y,sqrt(y)});
	}
	dijkstra();
	if(dis[n]==INF)cout<<-1;
	else cout<<dis[n];
}
```

---

## 作者：lzbzl (赞：1)

## AT_abc204_e Rush Hour 2 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc204_e)
### 分析
看题面可知这题为最短路问题。这题与最短路板子题的区别就是每条边的通过时间变成了变量。既然如此便要找到最优方案。

首先先看题目给出的方程：
$$
c_i+⌊\frac{d_i}{t+1}⌋
$$
这是通过一条边的方程，总时间便为 $t+c_i+⌊\frac{d_i}{t+1}⌋$。
我们将方程改写成以下形式：
$$
t+1+c_i+⌊\frac{d_i}{t+1}⌋-1
$$

令 $x=t+1$，则有 $x+c_i+⌊\frac{d_i}{x}⌋-1$。将常数去掉，再根据均值不等式可得 
$x^2=d_i$，所以可得 $t=\sqrt{d_i}-1$。由此可知当 $t=\sqrt{d_i}-1$ 时为最优，由此可得策略：当 $t<\sqrt{d_i}-1$ 时等待，否则直接走。

将代码贴上。
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f
using namespace std;
const int N=2*1e5+100;
int n,m;
struct yee
{
    int dis,x;
    bool operator<(const yee &p)const{return dis>p.dis;}
};
int dis[N],head[N],e[N],ne[N],w[N],idx=1;
int vis[N];
int d[N],ans;
int x,y,z,zz;
void add(int x,int y,int z,int dd)
{
    d[idx]=dd;
    w[idx]=z;
    ne[idx]=head[x];
    e[idx]=y;
    head[x]=idx++;
}
void dijkstra()
{
    memset(dis,INF,sizeof(dis));
    dis[1]=0;
    priority_queue<yee>q;
    q.push({0,1});
    while(!q.empty())
    {
        yee u=q.top();
        q.pop();
        if(vis[u.x])continue;
        vis[u.x]=1;
        for(int i=head[u.x];i!=-1;i=ne[i])
        {
            int tim=0;
            if(u.dis<=ceil(sqrt(d[i]))-1)
                tim=ceil(sqrt(d[i]))-1;
            else tim=u.dis;
            if(dis[e[i]]>tim+w[i]+d[i]/(tim+1))
            {
                dis[e[i]]=tim+w[i]+d[i]/(tim+1);
                yee c={dis[e[i]],e[i]};
                q.push(c);
            }
        }
    }
}
signed main()
{
    memset(head,-1,sizeof(head));
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>x>>y>>z>>zz;
        add(x,y,z,zz);
        add(y,x,z,zz);
    }
    dijkstra();
    if(dis[n]<100000000000000000)cout<<dis[n];
    else cout<<-1;
    return 0;
}

```
感谢管理员审核。

---

## 作者：loser_seele (赞：1)

首先考虑只有一条边的情况怎么做。

设到达 $ b $ 的时刻为 $ x $，不难发现答案为 $ f(x)=c+x+\frac{d}{x+1} $，其中 $ c $ 为常数不影响答案。

于是问题转化为最大化 $ x+\frac{d}{x+1} $，这是经典的基本不等式，显然原式等价于 $ (x+1)+\frac{d}{x+1}-1 $，$ -1 $ 是常数忽略，所以最大化 $ (x+1)+\frac{d}{x+1} $ 的值。设 $ y=x+1 $，则有原式等于 $ y+\frac{d}{y} $，由基本不等式可得 $ y^2=d,y=\sqrt{d},x=\sqrt{d}-1 $。

于是我们采取的策略是：当到达点 $ a $ 的时候要么等到 $ \sqrt{d}-1 $ 的时候再出发，要么直接跑路。

于是问题转化为平凡的最短路，只要在 Dijkstra 转移的时候判一下 dis 即可。

时间复杂度 $ \mathcal{O}(m\log{m}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,n) for(ll i=0;i<n;i++)
using namespace std;
#define all(a) a.begin(),a.end()
typedef long long ll;
typedef pair<ll,ll> P;
typedef pair<P,ll>PP;
constexpr ll inf=1e17;
constexpr ll mod=998244353;
struct edge
{
	ll to,c,d;
};
ll dist[100005];
vector<edge>G[100005];
int main()
{
	int n,m;
	cin>>n>>m;
	rep(i,m)
	{
		ll a,b,c,d;cin>>a>>b>>c>>d;
		a--;b--;
		G[a].push_back({b,c,d});
		G[b].push_back({a,c,d});
	}
	priority_queue<P,vector<P>,greater<P>>Q;
	Q.push(P(0,0));
	rep(i,n)
	dist[i]=inf;
	dist[0]=0;
	while(Q.size())
	{
		P p=Q.top();
		Q.pop();
		int v=p.second;
		if(dist[v]<p.first)
		continue;
		for(auto e:G[v])
		{
			ll w=(sqrt(e.d)-(dist[v]+1));
			if(w<0)
			w=0;
			rep(i,2)
			{
				ll nc=dist[v]+e.c+e.d/(dist[v]+w+1)+w;
				if(dist[e.to]>nc)
				{
					dist[e.to]=nc;
					Q.push(P(nc,e.to));
				}
				w++;
			}
		}
	}
	if(dist[n-1]==inf)
	cout<<-1;
	else 
	cout<<dist[n-1];
}
```


---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
给定一个包含 $n$ 个点和 $m$ 条边的无向图，每条边具有两个属性 $c_i$ 和 $d_i$。从点 $1$ 出发到达点 $n$，初始时间为 $0$。在时间为 $t$ 时，经过第 $i$ 条边所需的时间是 $c_i+⌊\frac{d_i}{t+1} ⌋$，并且可以在城市中停留任意非负整数时间。最后如果可以到达就输出最短时间，否则输出 $-1$。
## 分析
边的权重会随着时间动态变化，这边还是选择优先队列。

定义状态为一个二元组 $(u,t)$，其中 $u$ 表示当前所在的节点，表示当前的时间。对于每个状态，我们需要记录从起点到达该状态所花费的最短时间。

然后就是优先队列，优先队列中的元素按照到达当前状态所花费的时间从小到大排序。在每次从优先队列中取出一个状态后，进行两种操作：

如果在 $u$ 点停留,停留时间为 $w$，如果通过在节点 $u$ 停留到达时间 $t+w$ 所花费的总时间比之前记录的到达该状态的最短时间更短，则更新时间并将状态 $(u,t+w)$ 加入优先队列。

停留时间的求法如下：
```cpp
int fun(int a,int b,int c){
    return b+c/(a+1);
}
```

如果停留：
```cpp
if(t+w<dis[u][t+w]) {​
     dis[u][t+w]=t+w;​
     qp.push(Node(u,t+w));​//更新
}
```


计算在时间 $t$ 通过这条边到达节点 $v$ 的新时间，为 $mint$，如果新时间比之前记录的到达节点 $v$ 的时间更短，就更新 $mint$，将新状态 $(u,mmint)$ 加入优先队列。

```cpp
for(const D&e:g[u]){​
     v=e.to;​
     c=e.c;​
     d=e.d;​
     mint=t+fun(t,c,d);​//计算停留时间
     if(mint<dis[v][mint]){​
        dis[v][mint]=mint;​
        qp.push(Node(v,mint));​
     }​
}
```


当从优先队列中取出的状态 $(u,t)$ 满足 $u=n$ 时，此时的 $t$ 就是答案。如果优先队列为空且仍未找到到达终点的路径，则说明无法到达，输出 $-1$。

---

## 作者：Nazq (赞：0)

题解里的均值不等式个人不太理解。本篇题解为官方思路，具体说明如何得到 $\lfloor\sqrt{d}\rceil$。

首先，到每个点时间越早越好，因为可以到了再等。

于是设 $dis_u$ 为 $1$ 到 $u$ 的最短时间。
最小的边权为
$$
\min_{t\ge dis_u}t + c_i + \left\lfloor \frac{d_i}{t+1} \right\rfloor
$$

对于这个函数的最小值讨论，等价于对 $g(t) = t + \left\lfloor \dfrac{d_i}{t} \right\rfloor$ 的讨论。

当 $\dfrac{d}{t}-\dfrac{d}{t+1}\gt 1$，则 $\left\lfloor\dfrac{d}{t}\right\rfloor-\left\lfloor\dfrac{d}{t+1}\right\rfloor\ge 1$，$g(t)-g(t+1)\ge 0$，单调不增。

当 $\dfrac{d}{t}-\dfrac{d}{t+1}\le 1$，则 $\left\lfloor\dfrac{d}{t}\right\rfloor-\left\lfloor\dfrac{d}{t+1}\right\rfloor\le 1$，$g(t)-g(t+1)\le 0$，单调不减。

于是最小值就是满足 $\dfrac{d}{t}-\dfrac{d}{t+1}\le 1$ 最小的非负整数 $t$。

解得，$t = \left\lceil\dfrac{-1+\sqrt{4d+1}}{2}\right\rceil$。

判断 $dis_u$ 和 $t$ 的关系。如果 $dis_u$ 在 $t$ 右边，则直接转移不停留。否则停留到 $t$ 时刻再转移。

到这里，场上直接代即可。


下面证明 $t = \lfloor\sqrt{d}\rceil$。

当 $d = 0$ 时，$\sqrt{4d+1}=2\sqrt{d}+1$，$t = \lfloor\sqrt{d}\rceil = 0$。

当 $d\gt 0$ 时，$0 \lt\Delta = (2\sqrt{d} + 1) - \sqrt{4d+1}\lt 1$ 。

$$
t = \left\lceil\dfrac{-1+2\sqrt{d}+1-\Delta}{2}\right\rceil = \left\lceil\sqrt{d}-\dfrac{\Delta}{2}\right\rceil
$$

$\dfrac{\Delta}{2}\in (0,\dfrac{1}{2})$

再分讨。

设 $dt$ 为 $\sqrt{d}$ 的小数部分。

当 $dt = 0$，$t = \sqrt{d} = \left\lfloor\sqrt{d}\right\rceil$。

当 $0\lt dt\lt \dfrac{1}{2}$，

若要使 $t = \left\lfloor\sqrt{d}\right\rceil = \left\lfloor\sqrt{d}\right\rfloor$，则需要满足$\sqrt{d}$ 减去 $\dfrac{\Delta}{2}$ 后个位减 $1$，即 $dt\le \dfrac{\Delta}{2}$。

$$
\begin{aligned}
& dt\le \frac{\Delta}{2}\\
& \sqrt{d} - \left\lfloor\sqrt{d}\right\rfloor\le \frac{(2\sqrt{d} + 1) - \sqrt{4d+1}}{2} \\
& 2\sqrt{d} - 2\left\lfloor\sqrt{d}\right\rfloor\le (2\sqrt{d} + 1) - \sqrt{4d+1} \\
& - 2\left\lfloor\sqrt{d}\right\rfloor\le 1 - \sqrt{4d+1} \\
& \sqrt{4d+1} - 2\left\lfloor\sqrt{d}\right\rfloor\le 1 \\
& \sqrt{4d+1} - (\left\lfloor\sqrt{4d}\right\rfloor - [dt\ge \frac{1}{2}])\le 1 \\
& \sqrt{4d+1} - \left\lfloor\sqrt{4d}\right\rfloor + 1 - [0\le dt\lt \frac{1}{2}]\le 1 \\
& \sqrt{4d+1} - \left\lfloor\sqrt{4d}\right\rfloor\lt [0\le dt\le \frac{1}{2}] \\
& \sqrt{4d+1} - \left\lfloor\sqrt{4d}\right\rfloor \le 1 \\
\end{aligned}
$$
最后一个式子形如 $\sqrt{r+1} - \left\lfloor\sqrt{r}\right\rfloor\le 1$。

设 $k = \left\lfloor\sqrt{r}\right\rfloor$。

$r = k^2 + t(0\le t\le 2k)$。

当 $0\le t\lt 2k$ 时，$\sqrt{r+1}\lt k+1$，即 $\sqrt{r+1}-k\lt 1$。

当 $t = 2k$ 时，$\sqrt{r + 1} - k = 1$。

于是 $\sqrt{4d+1} - \left\lfloor\sqrt{4d}\right\rfloor \le 1$ 恒成立。

因此 $t = \left\lfloor\sqrt{d}\right\rceil$。

当 $\dfrac{1}{2}\le dt\lt 1$，$t = \left\lfloor\sqrt{d}\right\rceil$。

综上，$t = \left\lfloor\sqrt{d}\right\rceil$。

---

## 作者：MMXIandCCXXII (赞：0)

$\Large{\text{Solution}}$

根据 @Redamancy_Lydi 大佬题解里的图像和分析，我们已经知道这是一个单谷的图像，所以我们为什么不考虑三分呢？

在 dijkstra 时用三分算出最快到达的时间，然后正常跑就行了。

$\Large{\text{Code}}$

```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair <int, int>
using namespace std;

struct node
{
	int b, c, d;
};
vector <node> v[100010];
int d[100010];
bool vis[100010];

void dijkstra()
{
	memset (d, 0x3f, sizeof d);
	d[1] = 0;
	priority_queue <pii, vector <pii>, greater <pii> > q;
	q.push ({d[1], 1});
	while (q.size ())
	{
		int u = q.top ().second;
		q.pop ();
		if (vis[u]) continue;
		vis[u] = true;
		for (node t : v[u])
		{
			int j = t.b, C = t.c, D = t.d;
			int l = 0, r = D;
			while (r - l > 2)
			{
				double mid1 = l + (r - l + 1) / 3.0;
				double mid2 = r - (r - l + 1) / 3.0;
				double res1 = mid1 + D / (mid1 + 1);
				double res2 = mid2 + D / (mid2 + 1);
				if (res1 <= res2) r = mid2;
				else l = mid1;
			}
			int w = 1e18, mint = 0;
			for (int i = l; i <= r; i++)
				if (i + D / (i + 1) < w)
					w = i + D / (i + 1), mint = i;
			mint = max (mint, d[u]);
			w = mint + C + D / (mint + 1);
			if (d[j] > w)
			{
				d[j] = w;
				q.push ({d[j], j});
			}
		}
	}
}

signed main()
{
//	freopen ("rush.in", "r", stdin);
//	freopen ("rush.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int A, B, C, D;
		cin >> A >> B >> C >> D;
		v[A].push_back ({B, C, D});
		v[B].push_back ({A, C, D});
	}
	dijkstra ();
	if (d[n] == 0x3f3f3f3f3f3f3f3f) cout << -1 << endl;
	else cout << d[n] << endl; 
	return 0;
}
```

---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc204_e)

vp 之 tangshi 不会做绿题。

显然是最短路了，设 $dis_i$ 表示走到 $i$ 的最小时间。

一看到取整符号的第一反应就是整除分块？？？但是值域如此之大让我一点办法没有。

不过反正也是求 $t+c+\lfloor\dfrac{d}{t+1}\rfloor$ 的最大值，说不定可以 $O(1)$ 解呢？

先不看取整，显然有均值不等式可以得到当 $t=\sqrt{d}-1$ 可以取到最小。那么加上取整之后符号也不会差别很大吧，就是取个四舍五入的 $\sqrt{d}-1$ 作为 $t$ 的值。原因在于取整的变化只是把小数部分抹去了，所以就不可能有更优的 $t$。

当然了还要判断能不能取到了，如果取不到那么当前就是最优的。这里也是 ~~相当显然地~~ 因为当 $t+1\ge \sqrt{d}$ 时，$\lfloor\dfrac{d}{t+1}\rfloor\le \lfloor\dfrac{d}{t+2}\rfloor+1$。不想证了这个，可以打个表验证一下。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<ll,int>
#define mp make_pair
const int N=1e5+5;
const ll inf=1e18;
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n,m;
struct edge
{
	int u,v,nxt;ll c,d;
	ll f(ll t){return t+c+d/(t+1);}
}e[N<<1];
int cnt,head[N];ll dis[N];bool vis[N];
void add(int u,int v,ll c,ll d){e[++cnt]=(edge){u,v,head[u],c,d};head[u]=cnt;}
priority_queue<pii>q;
void Dijkstra()
{
	for(int i=1;i<=n;i++)dis[i]=inf;
	dis[1]=0;q.push(mp(0,1));
	while(!q.empty())
	{
		int u=q.top().second;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			ll w=e[i].f(max((ll)round(sqrt(e[i].d))-1,dis[u]));
			if(dis[v]>w)q.push(mp(-(dis[v]=w),v));
		}
	}
}
int main(){
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		int u,v;ll c,d;
		u=read();v=read();c=read();d=read();
		add(u,v,c,d);add(v,u,c,d);
	}
	Dijkstra();
	if(dis[n]!=inf)printf("%lld",dis[n]);
	else printf("-1");
	return 0;
}
```

---

