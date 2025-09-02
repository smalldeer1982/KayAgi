# [ABC137E] Coins Respawn

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc137/tasks/abc137_e

$ 1 $ から $ N $ までの番号がつけられた $ N $ 頂点と $ M $ 辺からなる有向グラフがあります。 $ i $ 番目の辺は頂点 $ A_i $ から頂点 $ B_i $ へと向かい、この辺の上には $ C_i $ 枚のコインが置かれています。 また、頂点 $ N $ にはボタンが設置されています。

このグラフ上でゲームを行います。 あなたは頂点 $ 1 $ でコインを $ 0 $ 枚持ってゲームを開始し、辺をたどってコインを拾いながら頂点 $ N $ を目指します。 $ 1 $ 本の辺を通るには $ 1 $ 分の時間がかかり、辺を通るたびにその辺の上に置かれているすべてのコインを拾うことができます。 ゲームの世界ではよくあるように、ある辺を通ってその上のコインを拾っても、その辺を次に通る際には同じ枚数のコインが再び出現しており、それらを再び拾うことができます。

頂点 $ N $ に到着したとき、ボタンを押してゲームを終了することができます。(ボタンを押さずに移動を続けることもできます。) ただし、ゲームを終了する際に、ゲーム開始からの経過時間を $ T $ 分として $ T\ \times\ P $ 枚のコインの支払いが要求されます。持っているコインの枚数が $ T\ \times\ P $ 枚未満の場合は、代わりに持っているコインをすべて支払います。

この支払いの後に残ったコインの枚数があなたのスコアとなります。 獲得できるスコアの最大値が存在するか判定し、存在する場合はその最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2500 $
- $ 1\ \leq\ M\ \leq\ 5000 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- $ 1\ \leq\ C_i\ \leq\ 10^5 $
- $ 0\ \leq\ P\ \leq\ 10^5 $
- 入力中の値はすべて整数である。
- 頂点 $ 1 $ から頂点 $ N $ に到達することが可能である。

### Sample Explanation 1

!\[入力例 1 で与えられるグラフの図\](https://img.atcoder.jp/ghi/5cb074e2d7c3282da137ac4ab2fbc700.png) 頂点 $ 1 $ から頂点 $ 3 $ に移動する方法は以下の $ 2 $ 通りです。 - 頂点 $ 1\ \rightarrow\ 2\ \rightarrow\ 3 $: 道中でコインを $ 20\ +\ 30\ =\ 50 $ 枚拾う。ゲーム開始から $ 2 $ 分後に頂点 $ 3 $ に着き、ボタンを押してコインを $ 2\ \times\ 10\ =\ 20 $ 枚支払い、$ 50\ -\ 20\ =\ 30 $ 枚残る。 - 頂点 $ 1\ \rightarrow\ 3 $: 道中でコインを $ 45 $ 枚拾う。ゲーム開始から $ 1 $ 分後に頂点 $ 3 $ に着き、ボタンを押してコインを $ 1\ \times\ 10\ =\ 10 $ 枚支払い、$ 45\ -\ 10\ =\ 35 $ 枚残る。 よって、獲得できるスコアの最大値は $ 35 $ です。

### Sample Explanation 2

!\[入力例 2 で与えられるグラフの図\](https://img.atcoder.jp/ghi/eb2188ad1e8189f963d233415fb293b6.png) 頂点 $ 1 $ から伸びる辺を通ると頂点 $ 2 $ に着き、ここで頂点 $ 2 $ から自分自身へと向かう辺を $ t $ 回通ってからボタンを押すとスコアは $ 90\ +\ 90t $ となります。よってスコアは無限に高めることができ、獲得できるスコアの最大値は存在しません。

### Sample Explanation 3

!\[入力例 3 で与えられるグラフの図\](https://img.atcoder.jp/ghi/217f7a224b80a05d8e25140c57e65ae7.png) 頂点 $ 1 $ から頂点 $ 4 $ へと直接向かう辺を通ること以外に頂点 $ 1 $ から頂点 $ 4 $ に移動する方法はありません。この辺の上で $ 1 $ 枚のコインを拾いますが、ゲーム終了時に $ 10 $ 枚のコインの支払いを要求されてスコアは $ 0 $ となります。 なお、頂点 $ 1 $ から頂点 $ 2 $ へと向かう辺を通るとその後コインを無限に拾えますが、頂点 $ 4 $ に到達してゲームを終了することができなくなるため無意味です。

## 样例 #1

### 输入

```
3 3 10
1 2 20
2 3 30
1 3 45```

### 输出

```
35```

## 样例 #2

### 输入

```
2 2 10
1 2 100
2 2 100```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 5 10
1 2 1
1 4 1
3 4 1
2 2 100
3 3 100```

### 输出

```
0```

# 题解

## 作者：Lynkcat (赞：6)

第一步先转化问题，我们发现每走一条边其实对答案的贡献是 $val-P$ ，那么我们可以把边权全部转化为 $val-P$ 。

我们再考虑什么情况下会无解，也就是答案无限大，那就是有一个边权和为正数的环与点 $n$ 联通。

否则我们肯定是找 $1$ 到 $n$ 的最长路，所以这道题就做完了。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
//#define int ll
#define N 10000005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,m,P,ans,dis[N],Vis[N],vis[N],q[N],cnt[N];
vector<pa>g[N];
vector<int>G[N];
void ad(int x,int y,int z)
{
	g[x].push_back({y,z});
}
void SPFA()
{
	memset(dis,-0x3f,sizeof(dis));
	dis[1]=0,Vis[1]=1;
	int l=1,r=0;q[++r]=1;
	while (l<=r)
	{
		int u=q[l];
		l++;
		Vis[u]=0;
		for (auto v:g[u])
		{
			if (!vis[v.fi])continue;
			if (dis[v.fi]<dis[u]+v.se)
			{
				dis[v.fi]=dis[u]+v.se;
				if (!Vis[v.fi]) {cnt[v.fi]++,Vis[v.fi]=1,q[++r]=v.fi;}
				if (cnt[v.fi]>n) 
				{
					ans=1;
					return;
				}
			}
		}
	}
}
void dfs(int k)
{
	if (vis[k]) return;
	vis[k]=1;
	for (auto u:G[k]) dfs(u);
}
signed main()
{
	n=read(),m=read(),P=read();
	for (int i=1;i<=m;i++)
	{
		int u=read(),v=read(),p=read();ad(u,v,p-P);G[v].push_back(u);
	}
	dfs(n);
	SPFA();
	if (ans) puts("-1"); else writeln(max(0,dis[n]));
}
/*

*/

```

---

## 作者：GHD3 (赞：4)

我发现我的思路和[这位同志的这篇文章](https://www.luogu.com.cn/article/wn6f66fg)一样，但是这位同志有些地方讲得不大明白，我再来补充一下。说明：此篇文章引用其他文章作者思路，已征得[原作者](https://www.luogu.com.cn/user/1065071)同意，在此表示感谢。

首先，正如这位同志所说：因为要最终减去 $T\times P$ 个硬币，所以不妨把每条边减去 $P$，就完美地解决了这个问题。随后要求出到 $n$ 点能最多获得几个硬币，且每条边可以重复走，这不难想出用[最长路](https://www.luogu.com.cn/problem/P1807)的方法做，因为有可能获得的硬币数量无上限（即出现正环），所以还需要判正环，因此可以使用 SFPA 实现。我们还需注意到的是如样例三这样的图：

![](https://img.atcoder.jp/ghi/217f7a224b80a05d8e25140c57e65ae7.png)

如果只按照上面的做法做，会在 $2$ 号点上浪费太多时间，因为 $2$ 号点上有环，而且 SPFA 算法还会告诉你图中有正环，硬币数量无上限，但是我们可以看到事实并非这样，事实是虽然 $2$ 号点有正环，但一进入 $2$ 号点，也回不来了，无法返回去 $n$ 号点（即 $4$ 号点）的正道了，所以 $2$ 号点的正环其实对答案没有影响。因此，我们不妨建一个反图，从终点 $n$ 出发，使用 DFS 寻找从终点出发能到的点。这样，在 SPFA 时就可以忽略掉从终点 $n$ 出发到不了的点，节省了时间，排除了对答案不影响的正环的干扰，可谓一举两得。

现在我们就可以设计出解决此题的算法：
1. 输入。
2. 使用 DFS 查找从终点出发可以到的点。（注意判重，别对查找过的点重新查找，陷入死循环）时间复杂度：$O(N+M)$。
3. SPFA 求最长路。（注意判正环，忽略从终点 $n$ 出发到不了的点）时间复杂度：$O(N\times M)$。
4. 输出。（如果有在有限范围内的解，且该解小于 $0$，记得把答案换成 $0$，因为最多也就把硬币扣光而已）

我们可以看到：核心算法时间复杂度为：$O(N+M+N\times M)$，我们再看：题目中说 $2\leq N\leq 2500$ 且 $1\leq M\leq 5000$，所以 $N+M+N\times M$ 最大情况下约是是 $1.25\times 10^7$，而时间限制是 $2.00s$，足以通过此题。

### AC Code
可参考文章开头想补充的[题解](https://www.luogu.com.cn/article/wn6f66fg)的代码。要说明的是，代码中不必像这位同志一样开 long long，开 int 就够了。

---

## 作者：ICE__LX (赞：3)

题目给了我们一个有向图，不看支付金币的话，就是简单的跑最长路。但题目还需减去用时 $T$ 与 $P$ 乘积，每走一步用时 $1$ 分钟，可以看作一个步数，每走一步到了终点就要多付 $P$ 枚硬币，由此边的权值就可以转化为：可获得的硬币数减去 $P$ 所得到的差。  
最后三点：一：若图中有正环且点 $n$ 包含其中就不存在正确解，判环可以用 SPFA 实现，判断正环中是否包含 $n$ 可以先从 $n$ 开始逆向遍历整个图并记录所有 $n$ 能抵达的点，让 SPFA 只枚举这些点；二：最后要进行判断，若解为负，输出 $0$；三：由于数据较大，要开 long long。  
### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6 + 5;
int n, m, p;
int dis[maxn],cnt[maxn],head[maxn],eid,head2[maxn],eid2;
bool vis[maxn],f[maxn];
struct Edge {
	int act,next,weight;
}*edge;
struct Edge2 {
	int act,next;
}*edge2;
void eadd(int u,int v,int w) {
	eid++;
	edge[eid].act=v;
	edge[eid].next=head[u];
	edge[eid].weight=w;
	head[u]=eid;
}
void eadd2(int u,int v) {
	eid2++;
	edge2[eid2].act=v;
	edge2[eid2].next=head2[u];
	head2[u]=eid2;
}
bool spfa(int s) {
	memset(dis, -0x3f, sizeof(dis));
	queue<int>q;
	dis[s]=0;
	q.push(s),vis[s]=true;
	while(!q.empty()) {
		int cur=q.front();
		q.pop();
		vis[cur]=false;
		for (int i=head[cur]; i; i=edge[i].next) {
			int nxt=edge[i].act,w=edge[i].weight;
			if (dis[nxt]<dis[cur]+w&&f[nxt]) {
				cnt[nxt]=cnt[cur]+1,dis[nxt]=dis[cur]+w;
				if (cnt[nxt]>=n)return true;
				if (vis[nxt]==0)vis[nxt]=1,q.push(nxt);
			}
		}
	}
	return false;
}
void dfs(int cur) {
	if(f[cur]) {
		return;
	}
	f[cur]=true;
	for(int i=head2[cur]; i; i=edge2[i].next)dfs(edge2[i].act);
}
signed main() {
	cin>>n>>m>>p;
	edge=new Edge[m+1];
	edge2=new Edge2[m+1];
	for (int i = 1; i <= m; i++) {
		int u,v,w;
		cin>>u>>v>>w;
		eadd(u,v,w-p);
		eadd2(v,u);
	}
	dfs(n);
	delete[]edge2;
	if(spfa(1)) cout<<-1;
	else cout<<(dis[n]<0?0:dis[n]);
	delete[]edge;
	return 0;
}
```

---

## 作者：Atserckcn (赞：3)

## [ABC137E] Coins Respawn 题解

[洛谷。](https://www.luogu.com.cn/problem/AT_abc137_e)

### 题目简述

给定一个 $n$ 个点，$m$ 条边的有向图，从点 1 走到点 n，若总共走了 $x$ 步，则最后需要减去 $xp$。

求是否有一个最大值，若有，输出。否则，输出 `-1`。

### 思路

先看需要减去 $xp$ 的问题。

显然每经过一条边都需要减去一个 $p$，那么不妨将每条边的权值减去 $p$。

再来看看没有答案的情况是咋样的。

显然，若图中出现了正权环，且是最长路上**经过**的环，则无解。

那么第一反应就是用 spfa 判正环。

再优化一下。

都知道了必须是路上经过的环，那么不如先 dfs 一遍，从 n 号点出发，因为是有向图，所以建个反图，暴力 dfs，并记录所有遇到的点。

在 spfa 中，若遇到了没有在路径上的点，则跳过，否则正常松弛操作。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ljl long long
const ljl N=2505,M=5005,inf=-1e18;
ljl n,m,p,head[N],cnt_e;
queue<ljl> q;
ljl dis[N],cnt[N];
bool vis[N],vis_in_dfs[N];
vector<ljl> vec[N];
struct E{
	ljl to,w,pre;
}e[M];
void add(ljl from,ljl to,ljl w)
{
	e[++cnt_e].to=to;
	e[cnt_e].w=w;
	e[cnt_e].pre=head[from];
	head[from]=cnt_e;
	return;
}
void dfs(ljl u)//暴力 dfs
{
	if(vis_in_dfs[u])return;
	vis_in_dfs[u]=1;
	for(auto i:vec[u])
		dfs(i);
	return;
}
bool spfa()
{
	for(ljl i=2;i<=n;++i)
		dis[i]=inf;
	q.push(1);vis[1]=1;
	while(!q.empty())
	{
		auto u=q.front();q.pop();
		vis[u]=0;
		for(ljl i=head[u];i;i=e[i].pre)
		{
			ljl v=e[i].to,w=e[i].w;
			if(!vis_in_dfs[v]) continue;//遇到了不可能在路径上的，直接跳过
			if(dis[v]<dis[u]+w)
			{
				dis[v]=dis[u]+w;
				if(!vis[v])
				{
					vis[v]=1;
					q.push(v);
					cnt[v]=cnt[u]+1;
					if(cnt[v]>=n)
						return 1;
				}
			}
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>p;
	for(ljl i=1,u,v,w;i<=m;++i)
	{
		cin>>u>>v>>w;
		add(u,v,w-p);vec[v].push_back(u);//正常的图和反图
	}
	dfs(n);
	if(spfa())
	{
		cout<<"-1\n";
		return 0;
	}
	cout<<max(0*1ll,dis[n])<<'\n';//记得和0取最大值，因为最后是扣光，而不是负债
	return 0;
}
```

---

## 作者：Stone_Xz (赞：3)

## [传送门：[ABC137E] Coins Respawn](https://www.luogu.com.cn/problem/AT_abc137_e)

## 简要题意：

> 给定一张有向图以及一个数 $P$，求从点 $1$ 到点 $n$ 的最长路，并减去 $T(经过的边数) \times P$。

## 分析：

1. 首先，题目要求点 $1$ 到点 $n$ 的最长路要减去 $T \times P$，对于这一点我们可以直接将每条边的边权减去 $P$，这样走了多少条边就减去了多少个 $P$。

2. 处理完边权，SPFA 跑最长路即可。现在重点是如何判断无解，直接在 SPFA 中判正环就行了吗？你会发现这样做过不了第三个样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/9s1n8d0l.png)

在这组数据中，SPFA 会找到点 $2$ 的自环，从而认为无解。然而如果走到了点 $2$，就根本走不到点 $4$ 了，走到点 $4$ 的路径是唯一的，正确答案也是唯一的。所以，无解的情况应为：有正环，并且可以从这个正环到达点 $n$。

3. 建个反图，从点 $n$ 开始在反图上 DFS，并标记经过的所有点（即在原图中能到达点 $n$ 的点）。不能到达点 $n$ 的那些点对答案没有任何贡献，我们在 SPFA 中不去松弛他们，这样就能避免找到一个无法到达点 $n$ 的正环。

4. 还有个小细节，如果 $1$ 到 $n$ 的最长路长度为负，要输出 $0$，因为题目中说：当你的硬币少于 $T \times P$ 时，你只需要支付全部的硬币。

PS：不开 long long 见祖宗。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2505;

int p, n, m, W, dis[N], cnt[N];

bool vis[N], lian[N];

struct Edge {
    int to, w;
};
vector<Edge> nbr[N];

vector<int> fan[N];

bool spfa(int s) // 已将边权取负，SPFA 跑最短路 and 判负环即可
{
    queue<int> q;
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);    
    memset(cnt, 0, sizeof cnt);
    dis[s] = 0;
    q.push(s);
    vis[s] = true;
    while(!q.empty())
    {
        int cur = q.front(); q.pop();
        vis[cur] = false;
        for(auto e : nbr[cur])
        {
            int nxt = e.to, w = e.w;
            if(dis[cur] + w < dis[nxt] && lian[nxt]) 
            {
                // 注意如果 nxt 无法到达点 n 就不能去
                dis[nxt] = dis[cur] + w;
                cnt[nxt] = cnt[cur] + 1;
                if(cnt[nxt] > n - 1) return true;
                if(!vis[nxt])
                {
                    q.push(nxt);
                    vis[nxt] = true;
                }
            }
        }
    }
    return false;
}

void dfs(int cur)
{
    lian[cur] = true;
    for(auto nxt : fan[cur])
        if(!lian[nxt]) dfs(nxt);
}

signed main()
{
    cin >> n >> m >> p;
    for(int i = 1; i <= m; i++)
    {
        int x, y, w; cin >> x >> y >> w;
        nbr[x].push_back((Edge){y, -(w - p)}); // 边权设为 w - p ，取负方便跑 SPFA
        fan[y].push_back(x); // 建反图
    }
    dfs(n); // 标记能到达点 n 的点
    if(spfa(1)) // 有正环
    {
        cout << "-1";
        return 0;
    }
    cout << max(0ll, -dis[n]); // 前面将边权取负了，dis[n] 记得改回来
    return 0;
}
```

---

## 作者：hyxgg (赞：2)

[题目](https://www.luogu.com.cn/problem/AT_abc137_e)
# 思路
假设我们走过第 $i$ 条边时，硬币的增量其实就是 $c_i-P$，将增量先处理出来再跑 SPFA 找最长路。

因为正权环不一定会在 $1$ 到 $n$ 的路径上，所以不能直接跳出，可以在找到一个正权环上的点后从它开始跑一个 DFS，标记其会影响的所有点（易证其时间复杂度是线性的），特判时判 $n$ 有没有被标记过就行了。

# 代码
代码如下，有问题评论区见。

```
#include<iostream>
#include<cstdio>
#include<queue>
#define ll long long
using namespace std;
struct edge{
	ll q,z,b,xg;
}ed[5005];
ll n,dd[2505],db=1,m,p,vis[2505],jl[2505],gs[2505];
bool pp[2505];
void fjq(ll q,ll z,ll b){
	ed[db].q=q,ed[db].z=z,ed[db].xg=dd[q],ed[db].b=b,dd[q]=db++;
}
queue<ll>q;
void dfs(ll root){
	for(ll i=dd[root];i;i=ed[i].xg){
		ll to=ed[i].z;
		if(pp[to])continue;
		pp[to]=1;
		dfs(to);
	}
}
int main(){
	scanf("%lld%lld%lld",&n,&m,&p);
	for(ll i=1;i<=n;i++){
		jl[i]=-1145141919810;
	}
	ll aa,bb,cc;
	for(ll i=1;i<=m;i++){
		scanf("%lld%lld%lld",&aa,&bb,&cc);
		cc-=p;
		fjq(aa,bb,cc);
	}
	jl[1]=0;
	vis[1]=1;
	q.push(1);
	while(!q.empty()){
		ll root=q.front();
		q.pop();
		vis[root]=0;
		if(gs[root]>n){
			pp[root]=1;
			dfs(root);
			continue;
		}
		for(ll i=dd[root];i;i=ed[i].xg){
			ll to=ed[i].z;
			if(pp[to]==1)continue;
			if(jl[to]<jl[root]+ed[i].b){
				jl[to]=jl[root]+ed[i].b;
				if(!vis[to])q.push(to),vis[to]=1,gs[to]++;
			}
		}
	}
	if(jl[n]==-1145141919810||pp[n]){
		printf("-1");
	}
	else if(jl[n]<0){
		printf("0");
	}
	else
	printf("%lld",jl[n]);
	return 0;
}
```

---

## 作者：__Deng_Rui_Song__ (赞：2)

# solution
首先最后要减去你走的边数乘 $P$ 个金币，相当于每走一条边就获得边权 $-P$ 个金币，因此建边的时候把边权 $-P$；

简化题意后大部分人马上想到一个思路，找正环，找到了就输出 -1，否则跑最长路；

测样例，样例 3 没过，为什么呢？我们发现虽然图中有正环，但是不能从正环到达 $N$，不会影响我们的答案，我们得找能到达 $N$ 的正环，怎么找呢？干脆不松弛不能到达 $N$ 的**点**吧，这样可以避免找到了不能到达 $N$ 的正环。
# code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2505;
struct node {
  int v, w;
};
int n, m, p, dis[N], cnt[N];
vector<node> g[N];
vector<int> G[N];
bool vis[N], f[N];
bool SPFA() {
  memset(dis, 0xcf, sizeof dis);
  queue<int> q;
  q.push(1);
  dis[1] = 0;
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    vis[x] = 0;
    for (int i = 0; i < g[x].size(); i++) {
      int nxt = g[x][i].v, num = g[x][i].w;
      if (dis[nxt] < dis[x] + num && f[nxt]) {//如果连通了才松弛
        dis[nxt] = dis[x] + num;
        if (!vis[nxt]) {
          q.push(nxt);
          cnt[nxt] = cnt[x] + 1;
          vis[nxt] = 1;
        }
        if (cnt[nxt] > n) return 1;//判断正环
      }
    }
  }
  return 0;
}
void dfs(int x) {
  if (f[x]) return;
  f[x] = 1;
  for (int i = 0; i < G[x].size(); i++) dfs(G[x][i]);
}
signed main() {
  cin >> n >> m >> p;
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].push_back({v, w - p});
    G[v].push_back(u);//一定要建反图
  }
  dfs(n);//找能到达N的点
  (SPFA() ? cout << "-1" : cout << max(dis[n],0ll));//跟0取max，因为金币不够只是清空，不是欠债
  return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：2)

## AT_abc137_e [ABC137E] Coins Respawn 题解
### 分析
气活了一堆可爱小错误调了好久，为了纪念调出来的伟大壮举，来发篇题解。

题面说到在结束时需要扣除 $t \times p$，其中 $t$ 为时间，也就是经过的边数。我们可以直接将这一条件放在边权中进行处理。也就是将每条边的权值减去 $p$。

然后跑最长路判环，有环就直接输出 `-1` 了，否则就输出 $dis_n$，但注意到题目要求“当您的硬币少于这个值时，你需要支付全部的硬币”，所以最后输出的时候将 $dis_n$ 与 $0$ 取最大值。

本题存在自环等情况，并且此图不连通，于是不与 $n$ 连通的点就没必要进行松弛了。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+5;
int n, m, dis[N], cnt[N], p;
bool vis[N];
struct node
{
	int y, w;
};
vector<node> nbr[N];
bool withn[N];//标记是否与n连通
void spfa()
{
	memset(dis,-0x7f,sizeof dis);
	memset(vis,0,sizeof vis);
	queue<int> q;
	q.push(1);
	dis[1]=0;
	while(!q.empty())
	{
		int cur=q.front();
		q.pop();
		vis[cur]=0;
		for(auto qq:nbr[cur])
		{
			int nxt=qq.y, val=qq.w;
			if(dis[cur]+val>dis[nxt]&&withn[nxt]==1)
			{
				dis[nxt]=dis[cur]+val;
				if(!vis[nxt])
				{
					cnt[nxt]=cnt[cur]+1;
					vis[nxt]=1;
					q.push(nxt);
				}
				if(cnt[nxt]>n)
				{
					cout<<-1;
					exit(0);
				}
			}
		}
	}
}
void check_n(int cur, int st)
{
	if(cur==n)
	{
		withn[st]=1;
		return ;
	}
	vis[cur]=1;
	for(auto i:nbr[cur])
	{	
		int nxt=i.y;
		if(!vis[nxt])
		{
			vis[nxt]=1;
			check_n(nxt,st);
		}
	}
}
signed main()
{
	cin>>n>>m>>p;
	for(int i=1;i<=m;i++)
	{
		int x, y, z;
		cin>>x>>y>>z;
		nbr[x].push_back((node){y,z-p});
	}
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof vis);	
		check_n(i,i);
	}
	spfa();
	cout<<max(dis[n],0ll);
}
```

---

## 作者：cwd2023 (赞：1)

# AT_abc137_e题解
### by cwd2023
---

### 思路：
1. 不难发现，由于边权都为 $1$，题目中的 $T$ 其实就是经过的边数，我们可以把这 $T\times P$ 个金币均摊到经过的每一条边上，即让每条边的边权减去 $T$。
2. 什么情况下我的答案无法确定呢？当然是答案可以无限大的时候，即图中有一个环，且环上所有边权之和大于 $0$（正环），只要我一直在环上走，答案就无限大。
3. 还有一个难以想到的条件：这个环必须在从 $1$ 到 $n$ 的路径上，这样我才有机会走到环上。我们可以 dfs 一下能到 $n$ 的每一个点。
4. 如何找到正环？SPFA 判负环都会吧？（不会点[这里](https://www.cnblogs.com/acioi/p/11694294.html)）那么只要把每一条边权取反，就变成判正环了。
5. 对于答案确定的情况下要怎么办？显然要找出从 $1$ 到 $n$ 的最长路径。最短路都会吧？（不会点[这里](https://blog.csdn.net/qq_35644234/article/details/61614581)）那么只要把每一条边权取反，就变成最长路了。
6. 所以，把边权取反是一举两得的，如果再使用 SFPA，那更是一举两得。

---

### Code：
#### 带注释：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,p;
ll dis[100010],cnt[100010];//dis用来存距离，cnt用来判断正环
bool inq[100010],d[100010];
//inq表示该点是否在队列中，d代表能否到n
struct N{
	ll v,w;
};
queue<ll>q;
vector<N>e[100010];//存图。
vector<ll>g[100010];//存反图。
inline void dfs(ll u){//dfs到每一个能到的点。
	d[u]=1;
	for(auto v:g[u])if(!d[v])dfs(v);
}
inline bool spfa(){
	dis[1]=0,inq[1]=1,q.push(1);
	while(q.size()){
		ll u=q.front();q.pop();inq[u]=0;
		for(auto k:e[u]){
			ll v=k.v,w=k.w;
			if(dis[v]>dis[u]+w&&d[v]){//记得加上d的判断。
				dis[v]=dis[u]+w;
                //找最长路顺便判正环
				cnt[v]=cnt[u]+1;//从1到v的最短路的边数。
				if(cnt[v]>=n)return 1;
                //若边数大于n,一定有正环。
				if(!inq[v])q.push(v),inq[v]=1;
			}
		}
	}
	return 0;//无正环。
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m>>p;
	for(ll i=1;i<=n;i++)dis[i]=1e18;
	for(ll i=1;i<=m;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		e[u].push_back({v,p-w});
		g[v].push_back(u);//从终点开始dfs，所以建反图。
	}
	dfs(n);
	spfa()?cout<<"-1\n":cout<<max(-dis[n],0ll)<<"\n";
//由于边权取反，答案也要取反，且要与0取最大值（看题面）。
	return 0;
}
```
#### 不带注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,p;
ll dis[100010],cnt[100010];
bool inq[100010],d[100010];
struct N{
	ll v,w;
};
queue<ll>q;
vector<N>e[100010];
vector<ll>g[100010];
inline void dfs(ll u){
	d[u]=1;
	for(auto v:g[u])if(!d[v])dfs(v);
}
inline bool spfa(){
	dis[1]=0,inq[1]=1,q.push(1);
	while(q.size()){
		ll u=q.front();q.pop();inq[u]=0;
		for(auto k:e[u]){
			ll v=k.v,w=k.w;
			if(dis[v]>dis[u]+w&&d[v]){
				dis[v]=dis[u]+w;
				cnt[v]=cnt[u]+1;
				if(cnt[v]>=n)return 1;
				if(!inq[v])q.push(v),inq[v]=1;
			}
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m>>p;
	for(ll i=1;i<=n;i++)dis[i]=1e18;
	for(ll i=1;i<=m;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		e[u].push_back({v,p-w});
		g[v].push_back(u);
	}
	dfs(n);
	spfa()?cout<<"-1\n":cout<<max(-dis[n],0ll)<<"\n";
	return 0;
}
```

最后，希望本篇题解对你有所帮助，感谢观看。
### 望管理员通过！

---

## 作者：lfxxx_ (赞：1)

## 题意简述
- 有一个有 $n$ 个点，$m$ 条边的有权图 $G$，求出一条从 $1$ 到 $N$ 的最长路，能达到无穷大，输出 `-1`。

## 解题报告

- 对于一个点 $x$，如果这个点和 $1$ 号点联通，且在反图上和 $n$ 号店联通，则我们称这个点为巨佬点。

- 我们去掉除巨佬点以外的点，得到一个新图 $H$。

- 另外，每条边的边权是原始边权 $c_i$ 减去经过一条边的花费 $P$，即每条边的边权为 $c_i-P$。

- 在图 $H$ 上跑最长路即可，要判断是否有正环，这里采用 spfa 算法。

## 代码公示

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2505;
int n,m,K;
vector<pair<int,int> >edge[N];
vector<int>G[N],rG[N];
int dis[N],neg[N];
bool inq[N];
bool vis[N];
int cnt[N];
bool spfa(int s)
{
	memset(dis,0xcf,sizeof dis);
	memset(neg,0,sizeof neg);
	memset(inq,0,sizeof inq);
	queue<int>q;
	q.emplace(s);
	dis[s]=0;
	inq[s]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();	
		inq[u]=0;
		for(auto &[v,w]:edge[u])
			if(dis[u]+w>dis[v]&&cnt[v]==2)
			{
				dis[v]=dis[u]+w;
				neg[v]=neg[u]+1;
				if(neg[v]>=n)
					return 1;
				if(!inq[v])
				{
					q.emplace(v);
					inq[v]=1;
				}
			}
	}
	return 0;
}
void bfs1(int s)
{
	queue<int>q;
	vis[s]=1;
	q.emplace(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		++cnt[u];
		for(auto &v:G[u])
			if(!vis[v])
				vis[v]=1,q.emplace(v);
	}
}
void bfs2(int s)
{
	memset(vis,0,sizeof vis);
	queue<int>q;
	vis[s]=1;
	q.emplace(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		++cnt[u];
		for(auto &v:rG[u])
			if(!vis[v])
				vis[v]=1,q.emplace(v);
	}
}
signed main()
{
	cin>>n>>m>>K;
	for(int i=1;i<=m;++i)
	{
		int u,v,w;
		cin>>u>>v>>w;
		edge[u].emplace_back(v,w-K);
		G[u].emplace_back(v);
		rG[v].emplace_back(u);
	}
	bfs1(1);
	bfs2(n);
	if(spfa(1))
		cout<<"-1";
	else
		cout<<max(0LL,dis[n]);
}
```

---

## 作者：small_john (赞：1)

## 思路

其实很简单。

由于最后到达终点要支付 $T\times P$ 枚金币，不妨把这些金币处理到每条边中，即每个边的权值间 $P$。

然后再跑一遍最长路，如果有环就输出 `-1`。

接下来判环。

![](https://cdn.luogu.com.cn/upload/image_hosting/wo2ki8zu.png)

上图就是一个环。红边表示松弛。可以发现，每个点都更新了一次 $1$ 号点。

所以，当一个点更新大于 $n$ 次时就有环。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e3+5;
int n,m,k,head[N],cnt,nxt[N],to[N],g[N],dis[N],s[N];
bool vis[N],vs[N];
void add(int x,int y,int z)
{
	nxt[++cnt] = head[x];
	head[x] = cnt;
	to[cnt] = y;
	g[cnt] = z;
}
void bfs()
{
	memset(vs,0,sizeof vs);
	dis[1] = 0;
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int u = q.front();q.pop();
		vs[u] = 0;
      	for(int i = head[u];i;i = nxt[i])
		{
			int v = to[i];
			if(dis[v]<dis[u]+g[i]&&vis[v])//不与n联通就没必要松弛了
			{
				dis[v] = dis[u]+g[i];
				if(!vs[v]) q.push(v),s[v]++,vs[v] = 1;
				if(s[v]>n)//判环
				{
					cout<<-1;
					exit(0);
				}
			}
		}
	}
}
void dfs(int x,int y)
{
	if(x==n)
	{
		vis[y] = 1;
		return;
	}
	for(int i = head[x];i;i = nxt[i])
		if(!vs[to[i]])
			vs[to[i]] = 1,dfs(to[i],y);
}//判是否与n联通
signed main()
{
	cin>>n>>m>>k;
	memset(dis,128,sizeof dis);
	for(int i = 1,x,y,z;i<=m;i++)
		cin>>x>>y>>z,add(x,y,z-k);
	for(int i = 1;i<=n;i++)
	{
		memset(vs,0,sizeof vs);
		vs[i] = 1;
		dfs(i,i);
	}
	bfs();
	if(dis[n]<0) dis[n] = 0;
	cout<<dis[n];
	return 0;
}
```

---

## 作者：Mu_leaf (赞：1)

### 前置知识：
[Bellman_Ford](https://zhuanlan.zhihu.com/p/352724346) 算法。

## [思路]

可以发现由于 $t$ 是线性的一次函数，所有可以将每条边的边权减去 $t$。

又因为如果存在正环，那么本题就没有最大值。所以要判断 $n \to 1$ 路径上是否存在环。

最短路领域最著名的迪杰斯特拉无法处理负边权，Floyd 可以处理但会达到 $O(n^3)$ 的时间复杂度。所以介绍一种既可以处理负边权又可以应对环的 Bellman_Ford 算法，尽管效率为 $O(n\times m)$ 但对于本题而言也足够了。

## [代码](https://atcoder.jp/contests/abc137/submissions/43711619)。

---

## 作者：CMWabc123 (赞：0)

# 第零部分 前言
练习最短路时遇到此题，用 Bellman-Ford  过掉了。看到题解区用 Ford 的人不多，所以来写一发题解。
# 第一部分 题目
[题目传送门](https://www.luogu.com.cn/problem/AT_abc137_e)
# 第二部分 分析
这道题大致流程有三步：

## 1.建图
+ 为了方便第二步，我们需要多建一个反图。
+ 由于最后要上交的钱平均下来就是每条路径要交 $p$ 元，所以边权要减 $p$ 。
+ 这道题需要求最长路，所以边权取反后再建图。

## 2.排除无关点
我们先从 $1$ 号点和 $n$ 号点出发，进行 dfs , 排除一些跟答案无关的点。这样可以防止环的出现。

## 3. Bellman-Ford
可以直接套用模版。


至此，这道题分析完毕。

【友情提示】由于是求最长路，所以输出时路径要取反。
# 第三部分 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,p;
struct edge {
	int v,w;
};
vector<edge>G1[2510],G2[2510];
int d[2510];
bool vis1[2510],vis2[2510];
void dfs1(int u) {
	vis1[u]=1;
	for(auto e:G1[u])if(!vis1[e.v])dfs1(e.v);
}
void dfs2(int u) {
	vis2[u]=1;
	for(auto e:G2[u])if(!vis2[e.v])dfs2(e.v);
}
bool Bellman_Ford(int st) {
	for(int i=1; i<=n; i++)d[i]=1e9;
	d[st]=0;
	for(int i=1; i<=n; i++) {
		bool flag=0;
		for(int u=1; u<=n; u++) {
			if(vis1[u]&&vis2[u]) {
				for(auto e:G1[u]) {
					if(vis1[e.v]&&vis2[e.v]&&d[e.v]>d[u]+e.w) {
						d[e.v]=d[u]+e.w;
						flag=1;
					}
				}
			}
		}
		if(!flag)return 1;
	}
	return 0;
}
int main() {
	cin>>n>>m>>p;
	for(int i=1; i<=m; i++) {
		int u,v,w;
		cin>>u>>v>>w;
		G1[u].push_back({v,p-w});
		G2[v].push_back({u,p-w});
	}
	dfs1(1),dfs2(n);
	if(!Bellman_Ford(1)) {
		cout<<-1;
	} else {
		cout<<max(0,-d[n]);
	}
	return 0;
}

```

---

## 作者：DragonForge (赞：0)

## 题解：AT_abc137_e [ABC137E] Coins Respawn

这是一道非常经典的求“正环”的题。由于走过每条边都需要 1 分钟，而平均每分钟都需要支付 `P` 枚金币，那么走过这条边真正能获得的金币数是边权减去 `P`。这样下来，题目就可以理解为：从 1 走到 `n`，输出可以得到金币的最大值。若金币数是负数或是无穷大，那么输出 `-1`。为了与判负环模板照应，我将做完差的边权值取相反数，最后输出就只需要再取相反数就行。

### code


```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN=2510,inf=1e18;

int n,m,p,dis[MAXN],vis[MAXN],h[MAXN],cnt[MAXN],visd[MAXN];
vector<pair<int,int>> e[MAXN];
vector<int> vec[MAXN];

inline void dfs(int u){
	if(visd[u]) return;
	visd[u]=1;
	for(auto v:vec[u]){
		dfs(v);
	}
}

inline bool spfa(){
  queue<int> q;
  fill(dis+2,dis+1+n,-inf);
  vis[1]=1;
  q.push(1);
  while(!q.empty()){
    int u=q.front();
    q.pop();
    vis[u]=0;
    for(auto [v,w]:e[u]){
    	if(!visd[v]) continue;
      if(dis[v]<dis[u]+w){
        dis[v]=dis[u]+w;
        if(!vis[v]){
          vis[v]=1;
			    q.push(v);
          cnt[v]=cnt[u]+1;
			    if(cnt[v]>=n){
			      return 1;
          }
        }
      }
    }
  }
  return 0;
}

signed main(){
  cin>>n>>m>>p;
  for(int i=1,u,v,w;i<=m;i++){
    cin>>u>>v>>w;
    e[u].push_back({v,w-p});
    vec[v].emplace_back(u);
  }
  dfs(n);
  if(spfa()) cout<<"-1";
  else cout<<max(0LL,dis[n]);
  return 0;
}
```

---

## 作者：foryou_ (赞：0)

显然这是一道求最长路问题，我们可以采用 SPFA 解决（因为可能有负边权）。

考虑到结束游戏时需要支付 $T \times P$ 枚硬币，我们直接将所有边权减去 $P$ 即可。

最后，无解的情形即为有正环的情形。

值得一提的是，本题的图不一定联通，我们需要跑一遍 BFS / DFS 搜索出所有点 $N$ 能到达的点，再跑 SPFA 即可。

[code](https://www.luogu.com.cn/paste/oqbkjoqn)，这里实现时是将边权取反跑的最短路。

---

## 作者：_zexal_ (赞：0)

#### 思路
考虑到最后答案存在 $p \times t$ 这一个部分，这其实是不好维护的，不妨考虑每走一步就减去一个 $p$ ，这样，就拆掉了 $p \times t$ 这一个部分。题目也就转换为了一个最长路题目。接下来考虑何时是可以一直走，显然是存在一个正权环，跑最长路的时候加一个判断即可。
#### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,p;
int head[1000005],to[1000005],nxt[1000005],tot,w[1000005],dis[1000005],vis1[1000005];
int vis[1000005],cnt[1000005],flag,q[1000005];
vector<int>G[1000005];
void add(int x,int y,int w1) {
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;	
	w[tot]=w1;
}
void spfa() {
	memset(dis,-0x3f,sizeof dis);
	dis[1]=0,vis[1]=1;
	int l=1,r=0;q[++r]=1;
	while(l<=r) {
		int u=q[l];l++;
		vis[u]=0;
		for(int i=head[u];i;i=nxt[i]) {
			if(!vis1[to[i]]) continue;
			if(dis[to[i]]<dis[u]+w[i]) {
				dis[to[i]]=dis[u]+w[i];
				if(!vis[to[i]]) {
					cnt[to[i]]++;vis[to[i]]=1;q[++r]=to[i];
				}
				if(cnt[to[i]]>n) {
					flag=1;return;
				}
			}
		}
	}
}
void dfs(int k)
{
	if (vis1[k]) return;
	vis1[k]=1;
	for (auto u:G[k]) dfs(u);
}
signed main() {
	scanf("%lld %lld %lld",&n,&m,&p);
	for(int i=1;i<=m;i++) {
		int u,v,w1;
		scanf("%lld %lld %lld",&u,&v,&w1);G[v].push_back(u);
		add(u,v,w1-p);
	}
	dfs(n);
	spfa();
	if(flag) printf("-1");
	else printf("%lld",max((int)0,dis[n]));
	return 0;
}
```


---

## 作者：GJX_Algorithm (赞：0)

# AT_abc137_e题解
## 题目描述
1. 给定一个有向图，点的编号为 $1 \sim N$，有 $M$ 条边，每条边为 $a_i \to b_i$，这条边上有 $c_i$ 枚硬币。
  
2. 你从节点 $1$ 出发，初始硬币为 $0$，你需要抵达 $N$，经过每条边耗时 $1$ 分钟，每次经过一条边你都能收获硬币。

3. 当您抵达 $N$ 时，你可以结束游戏，也可以继续游戏，但是当你结束游戏的时候，你需要支付 $T \times P$ 枚硬币，当您的硬币少于这个值时，你需要支付全部的硬币。

4. 你的分数就是在付款后所拥有的硬币数量，如果可以确定能获得一个最大分数，你需要输出可以获得的分数的最大值。

5. 如果没有最大值，输出 ```-1```。
## 解题思路
1. 不难想到可以把每条边的边权改成 $c_i - p$， 跑最长路。
  
2. 如果有与 $n$ 联通的正环，就没有最大值，至于如何判环，SPFA 即可，当然 Bellman-Ford 也行。

3. 注意正环一定要与 $n$ 联通，我是先建反图，再从 $n$ 开始标记能达到的点，最后只对标记的点进行 SPFA。

4. 十年 OI 一场空，__________________
## AC代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int n, m, p, u, v, w;
int dis[N], cnt[N];
bool vis[N], flag[N];
struct node
{
    int y, w;
};
vector<node> nbr[N];
vector<int> vt[N];
bool spfa(int s)
{
    memset(dis, -0x3f, sizeof dis);
    queue<int> q;
    dis[s] = 0;
    q.push(s), vis[s] = 1;
    while (q.empty() == 0)
    {
        int cur = q.front();
        q.pop();
        vis[cur] = 0;
        for (node tmp : nbr[cur])
        {
            int nxt = tmp.y, w = tmp.w;
            if (dis[nxt] < dis[cur] + w && flag[nxt] == 1)
            {
                cnt[nxt] = cnt[cur] + 1, dis[nxt] = dis[cur] + w;
                if (cnt[nxt] >= n) return 1;
                if (vis[nxt] == 0) vis[nxt] = 1, q.push(nxt);
            }
        }
    }
    return 0;
}
void dfs(int cur)
{
    if (flag[cur] == 1) return ;
    flag[cur] = 1;
    for (int nxt : vt[cur]) dfs(nxt);
}
signed main()
{
    cin >> n >> m >> p;
    for (int i = 1; i <= m; i++)
    {
        cin >> u >> v >> w;
        nbr[u].push_back({v, w - p});
        vt[v].push_back(u);
    }
    dfs(n);
    bool d = spfa(1);
    if (d == 1) cout << -1;
    else if (dis[n] < 0) cout << 0;
    else cout << dis[n];
    return 0;
}
```

---

