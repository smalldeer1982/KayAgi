# [ABC237E] Skiing

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc237/tasks/abc237_e

AtCoder スキー場には広場 $ 1 $ 、広場 $ 2 $ 、$ \ldots $ 、広場 $ N $ の $ N $ 個の広場があり、広場 $ i $ の標高は $ H_i $ です。 また、$ 2 $ つの広場を双方向に結ぶ $ M $ 本の坂があり、$ i $ $ (1\ \leq\ i\ \leq\ M) $ 本目の坂は広場 $ U_i $ と広場 $ V_i $ を双方向に結んでいます。どの $ 2 $ つの広場の間もいくつかの坂を使って移動することができます。

高橋君は坂を使うことによってのみ広場の間を移動でき、坂を通るごとに**楽しさ**が変化します。具体的には広場 $ X $ と広場 $ Y $ を直接結ぶ坂を使って広場 $ X $ から広場 $ Y $ まで移動したとき次のように楽しさが変化します。

- 広場 $ X $ が広場 $ Y $ より標高が真に高い場合、その標高差、すなわち $ H_X-H_Y $ だけ楽しさが**増加**する。
- 広場 $ X $ が広場 $ Y $ より標高が真に低い場合、その標高差の $ 2 $ 倍、すなわち $ 2(H_Y-H_X) $ だけ楽しさが**減少**する。
- 広場 $ X $ と広場 $ Y $ の標高が等しい場合、楽しさは変化しない。

楽しさは負の値になることもあります。

最初、高橋君は広場 $ 1 $ におり、楽しさは $ 0 $ です。 高橋君はいくつかの坂（ $ 0 $ 本でも良い）を移動した後に好きな広場で行動を終えることができるとしたとき、行動を終えた時点の高橋君の楽しさとしてありうる最大の値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ \min(\ 2\times\ 10^5,\frac{N(N-1)}{2}) $
- $ 0\ \leq\ H_i\leq\ 10^8 $ $ (1\ \leq\ i\ \leq\ N) $
- $ 1\ \leq\ U_i\ <\ V_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ M) $
- $ i\ \neq\ j $ ならば $ (U_i,V_i)\ \neq\ (U_j,\ V_j) $
- 入力はすべて整数である。
- どの $ 2 $ つの広場の間もいくつかの坂を使って移動することができる。

### Sample Explanation 1

広場 $ 1 $ $ \to $ 広場 $ 3 $ $ \to $ 広場 $ 4 $ と移動したとき、楽しさは次のように変化します。 - 広場 $ 1 $（標高 $ 10 $ ）から坂を使って広場 $ 3 $（標高 $ 12 $ ）へ移動します。楽しさは $ 2\times\ (12-10)=4 $ だけ減少し、$ 0-4=-4 $ になります。 - 広場 $ 3 $（標高 $ 12 $ ）から坂を使って広場 $ 4 $（標高 $ 5 $ ）へ移動します。楽しさは $ 12-5=7 $ だけ増加し、$ -4+7=3 $ になります。 ここで行動を終了したとき終了時の楽しさは $ 3 $ であり、このときが最大となります。

### Sample Explanation 2

一度も移動を行わない時、楽しさが最大となります。

## 样例 #1

### 输入

```
4 4
10 8 12 5
1 2
1 3
2 3
3 4```

### 输出

```
3```

## 样例 #2

### 输入

```
2 1
0 10
1 2```

### 输出

```
0```

# 题解

## 作者：Nightsky_Stars (赞：8)

这题要求最长路，我们可以将所有边取反，即将 $w$ 变成 $-w$，这样就把问题转化成了最短路。

而答案就是 $\max(h_{1}-h_{a1}+h_{a1}-h_{a2}\cdots-h_{i-1}+h_{i-1}-h_{i}-d_{i})$，化简得 $\max(h_{1}-h_{i}-d_{i})$。

# CODE:
```
#include<bits/stdc++.h>
using namespace std;
int n,m,s,to[500010],w[500010],nxt[500010],head[500010],h[500010],cnt,ans,d[500010];
bool vis[500010];
void add(int u,int v,int k){
    to[++cnt]=v;
    w[cnt]=-k;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void dijkstra(){
    memset(d,0x3f3f3f3f,sizeof(d));
    priority_queue<pair<int,int>> q;
    d[1]=0;
    q.push(make_pair(0,1));
    while(!q.empty()){
        int u=q.top().second;
        q.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(int i=head[u];~i;i=nxt[i]){
            int v=to[i];
            if(d[v]>d[u]+w[i]){
                d[v]=d[u]+w[i];
                q.push(make_pair(-d[v],v));
            }
        }
    }
}
int main(){
    cin>>n>>m;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(h[u]>=h[v]){
        	add(u,v,0);
		}else{
			add(u,v,h[u]-h[v]);
		}
        if(h[v]>=h[u]){
        	add(v,u,0);
		}else{
			add(v,u,h[v]-h[u]);
		}
    }
    dijkstra();
    for(int i=1;i<=n;i++){
        ans=max(ans,h[1]-h[i]-d[i]);
    }
    cout<<ans<<"\n";
    return 0;
}
```


---

## 作者：GI录像机 (赞：6)

更新：添加句末句号。

## 思路：

我们将所有边取反，最长路就变成了最短路。

SPFA 虽然可以卡过去，但出题人只要有心都是能干掉 SPFA 的，所以我们使用不会被干掉的 dijkstra。

dijkstra 的问题就在于跑不了负权边的最短路。我们考虑给每个边加上 $h_x-h_y$，如果 $h_x>h_y$，边权变为 $0$，否则变为 $-(h_x-h_y)$，消除了负权边。设 $-dis_{v}$ 表示 $1$ 到 $v$ 的实际距离，$a_i$ 表示路上经过的点，则最后算出的距离为 $-dis_{v}+(h_1-h_{a_1}+h_{a_1}-h_{a_2}\cdots-h_{a_k}+h_{a_k}-h_v)=-dis_{v}+h_1-h_v$。

然后就可以愉快地 AC 啦。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(long long x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
int n = read(), m = read(),  tot, head[N], h[N], sum;
long long dis[N], ans;
struct Node {
	int to, nxt, w;
} a[N << 1];
void add(int u, int v, int w) {
	a[++tot].to = v;
	a[tot].w = -w;
	a[tot].nxt = head[u];
	head[u] = tot;
}
struct node {
	int pos;
	long long w;
	bool operator <(const node& c)const {
		return c.w < w;
	}
};
void dijkstra() {
	dis[1] = 0;
	priority_queue<node>q;
	q.push({1, 0});
	while (!q.empty()) {
		node now = q.top();
		q.pop();
		int u = now.pos;
		if (now.w != dis[u])continue;
		for (int i = head[u]; i; i = a[i].nxt) {
			int v = a[i].to, w = a[i].w;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push({v, dis[v]});
			}
		}
	}
}
signed main() {
	for (int i = 1; i <= n; i++)h[i] = read();
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read();
		add(u, v, h[u] >= h[v] ? 0 : h[u] - h[v]);
		add(v, u, h[v] >= h[u] ? 0 : h[v] - h[u]);
	}
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	dijkstra();
	for (int i = 1; i <= n; i++)ans = max(ans, -dis[i] - h[i] + h[1]);
	write(ans);
	return 0;
}
```


---

## 作者：szh_AK_all (赞：3)

### 题意
一共有 $n$ 个节点，$m$ 条边，每条边都有其权值，我们要计算 $1$ 号节点到其他节点的最长路。

### 分析
假设 $x$ 到 $y$ 有一条边，则从 $x$ 到 $y$ 与从 $y$ 到 $x$ 所得的幸福感不一定相同，所以，对于一个无向边，将其拆成连个有向边，并考虑边的权值。

由于我们习惯于求最短路，所以在解决最长路时，我们可以将其转化为最短路。

如何进行转换呢？很显然的是，将每条边的权值乘上 $-1$，那么所有边权权值的大小关系都会倒转，这样，最长路就可以用最短路解决了。

对于每条边，只需判断两个端点的大小关系，然后确定权值即可。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
long long dis[200005], ans, h[200005];
int vis[200005];
vector<int>g[200005];
vector<int>w[200005];
int n;

struct node {
	int x;
	long long dis;
	node(int a, long long b) {
		x = a;
		dis = b;
	}
	friend bool operator <(node l, node r) {
		return l.dis < r.dis;
	}
};

void dij() {
	for (int i = 1; i <= n; i++)
		dis[i] = 1000000000000;
	dis[1] = 0;
	priority_queue<node>q;
	q.push(node(1, 0));
	while (!q.empty()) {
		int x = q.top().x;
		q.pop();
		if (vis[x])
			continue;
		vis[x] = 1;
		for (int i = 0; i < (int)g[x].size(); i++) {
			int y = g[x][i], ww = w[x][i];
			if (dis[y] > dis[x] + ww) {
				dis[y] = dis[x] + ww;
				q.push(node(y, -dis[y]));
			}
		}
	}
}

int main() {
	int m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> h[i];
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		if (h[u] < h[v])
			w[u].push_back(h[v] - h[u]);
		else
			w[u].push_back(0);
		if (h[v] < h[u])
			w[v].push_back(h[u] - h[v]);
		else
			w[v].push_back(0);
	}
	dij();
	for (int i = 1; i <= n; i++)
		ans = max(ans, -dis[i] - h[i] + h[1]);
	cout << ans;
}
```
给个赞吧！

---

## 作者：ttq012 (赞：3)

spfa 裸题。

由于要求的是最长路，所以每一条边的边权取反，跑最短路，然后把结果取反即可。

这里取反指的是 $x$ 变成 $-x$。

建边的时候如果 $d_u<d_v$ 那么就建一条边权是 $2\times (d_v-d_u)$ 的边，否则就建一条 $d_v-d_u$ 的边即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int h[N],dis[N];
vector<int>z[N];
bool vis[N];
int gd(int x,int y){
  if(h[x]<h[y])
    return 2*(h[y]-h[x]);
  return h[y]-h[x];
}
void spfa(){
  deque<int>q;
  q.push_back(1);
  memset(dis,0x3f,sizeof dis);
  vis[1]=true;
  dis[1]=0;
  while(q.size()){
    int f=q.front();
    q.pop_front();
    vis[f]=false;
    for(auto &i:z[f])
      if(dis[i]>dis[f]+gd(f,i)){
        dis[i]=dis[f]+gd(f,i);
        if(!vis[i]){
          vis[i]=true;
          if(q.size()&&dis[i]>dis[q.front()])
            q.push_back(i);
          else
            q.push_front(i);
        }
      }
  }
}
signed main(){
  int n,m;
  cin>>n>>m;
  for(int i=1;i<=n;i++)
    cin>>h[i];
  while(m--){
    int u,v;
    cin>>u>>v;
    z[u].push_back(v);
    z[v].push_back(u);
  }
  spfa();
  cout<<-*min_element(dis+1,dis+n+1)<<'\n';
  return 0;
}
```



---

## 作者：DengDuck (赞：2)

很久之前做的题了，现在感觉彻底理解了。

首先这题用 SPFA 时间复杂度显然是假的，考虑消除负边权，这样就可以跑 Dijkstra 了。

怎么消除？考虑转换我们求的东西，原来求的是 $dis_i$ 表示 $1\to i$ 的最长路，现在我们先把边权取反，然后每条边 $x\to y$ 加上 $h_x-h_y$，这样边权为负的边就变成 $0$，再跑 Dijkstra 就行了。

对于一条路径 $1\to a_1\to a_2\to a_3\to \cdots \to i$，我们把边权加上的值拿出来看：

$$
h_1-h_{a_1}+h_{a_1}-\cdots-h_{i}=h_1-h_i
$$

这显然是个定值（对于确定的 $i$），所以我们转换后求的是 $-dis_i+h_1-h_i$ 的最小值，等价于求 $dis_i$ 的最大值，所以是对的。

这个技巧在很多资料中称为增加势能，不过我个人认为理解可以不从势能角度入手。

其特点是可以构造一种方案，使转换后的求的答案等价于原先的方案。

为什么这里要转成反边权？因为不反过来的话你的目标是把 $2\times(h_x-h_y)$ 变成非负数，然后你发现方案使另外一条边变成负边是不可避免的。

这样时间复杂度才是严格的 $\mathcal O((n+m)\log n)$。

代码是我的远古马蜂，很丑。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    long long to,w,next;
}a[1000005];
long long n,m,t,x,y,h[200005],b[200005],ans,dis[200005];
void add(long long x,long long y,long long z)
{
    t++;
    a[t].to=y;
    a[t].w=z;
    a[t].next=h[x];
    h[x]=t;
}
struct nd{
    long long x,dis;
    bool operator <(const nd &xx)const
    {
        return dis>xx.dis;
    }
    nd(long long xx,long long xdis){
        x=xx;
        dis=xdis;
    }
};
priority_queue<nd>p;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        scanf("%lld",&b[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%lld%lld",&x,&y);
        if(b[x]>b[y])add(y,x,b[x]-b[y]),add(x,y,0);
        else add(x,y,b[y]-b[x]),add(y,x,0);
    }
    p.push(nd(1,0));
    memset(dis,127,sizeof(dis));
    dis[1]=0;
    for(int i=1;i<=n-1;i++)
    {
    //    cout<<t<<endl;
        long long t=p.top().x;
        p.pop();
        for(int j=h[t];j;j=a[j].next)
        {
       //     cout<<a[j].to<<' '<<a[j].w<<endl;
            if(dis[t]+a[j].w<dis[a[j].to])
            {
                dis[a[j].to]=dis[t]+a[j].w;
                p.push(nd(a[j].to,dis[a[j].to]));
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        ans=max(ans,b[1]-b[i]-dis[i]);
    }
    cout<<ans;
}
```

---

## 作者：liuzhongrui (赞：1)

## 思路

首先警示一下大家，这题卡 SPFA ~~别问我怎么知道的~~。

理解一下题意，发现这题实际上是求最长路对吧，那我们转个弯，将所有边取反（这里取反的意思是把 $w$ 变成 $-w$），这很容易操作，只需在链式前向星中小改一下，这样就把问题转化成了最短路。

dijkstra 处理不了负权边，那这题中的边怎么求？如果 $H_y \le H_x$，边权设置为 $0$，否则加边时设置为 $H_x - H_y$。

这一切处理完后，跑一遍 dijkstra 板子。

答案怎么求？化简一下 $H_1-H_{a_1}+H_{a_1} \cdots -H_{i-1}+H_{i-1}-H_i$ 发现大部分抵消了，剩下 $H_1-H_i$，最终答案就是 $H_1-H_i-dis_i$ 中的最大值。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10,INF=0x3f3f3f3f;
#define PII pair<int,int>
int n,m,s;
int to[N],w[N],nx[N],h[N],H[N],idx;
int dis[N];
bool vis[N];
void add(int u,int v,int ww){
	to[++idx]=v;
	w[idx]=-ww;
	nx[idx]=h[u];
	h[u]=idx;
}
void d(){
	memset(dis,INF,sizeof dis);
	priority_queue<PII,vector<PII>,greater<PII> >q;
	dis[1]=0;
	q.push({0,1});
	while(!q.empty()){
		int t=q.top().second;
		q.pop();
		if(vis[t])continue;
		vis[t]=1;
		for(int i=h[t];i!=-1;i=nx[i]){
			int j=to[i];
			if(dis[j]>dis[t]+w[i]){
				dis[j]=dis[t]+w[i];
				q.push({dis[j],j});
			}
		}
	}
}
int main(){
	memset(h,-1,sizeof h);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>H[i];
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v,H[u] >= H[v] ? 0 : H[u] - H[v]);
		add(v,u,H[v] >= H[u] ? 0 : H[v] - H[u]);
	}
	d();
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,H[1]-H[i]-dis[i]);
	}
	cout<<ans;
	return 0;
}
```


---

