# Speedrun

## 题目描述

You are playing a video game. The game has $ n $ quests that need to be completed. However, the $ j $ -th quest can only be completed at the beginning of hour $ h_j $ of a game day. The game day is $ k $ hours long. The hours of each game day are numbered $ 0, 1, \ldots, k - 1 $ . After the first day ends, a new one starts, and so on.

Also, there are dependencies between the quests, that is, for some pairs $ (a_i, b_i) $ the $ b_i $ -th quest can only be completed after the $ a_i $ -th quest. It is guaranteed that there are no circular dependencies, as otherwise the game would be unbeatable and nobody would play it.

You are skilled enough to complete any number of quests in a negligible amount of time (i. e. you can complete any number of quests at the beginning of the same hour, even if there are dependencies between them). You want to complete all quests as fast as possible. To do this, you can complete the quests in any valid order. The completion time is equal to the difference between the time of completing the last quest and the time of completing the first quest in this order.

Find the least amount of time you need to complete the game.

## 说明/提示

In the first test case, quests $ 1 $ and $ 4 $ must be completed at the beginning of the $ 12 $ -th hour of the day, but they cannot be completed during the same hour, because you also need to complete quests $ 2 $ and $ 3 $ between them. You can do all this in $ 24 $ hours, though. To do so, you start at $ 12 $ hours of the first game day by completing the first quest. At $ 16 $ hours you complete quest $ 2 $ . At $ 18 $ hours you complete quest $ 3 $ . Finally at $ 12 $ hours of the second day you can complete quest $ 4 $ . The total time elapsed (from the moment you completed the first quest and the moment you completed the last) is $ 24 $ hours.

In the third test case, you can complete the first quest and then complete the remaining quest right after. You start at $ 5 $ hours of the first day by completing the first quest. After this the second quest becomes available, you complete it as well. The total time elapsed is $ 0 $ .

In the fourth test case, you can start with the third quest. You start at $ 555 $ hours of the first day and you can finish at $ 35 $ hours of the second day. The total time elapsed is $ 1035-555=480 $ .

## 样例 #1

### 输入

```
6
4 4 24
12 16 18 12
1 2
1 3
2 4
3 4
4 3 10
2 6 5 9
1 4
2 4
3 4
2 1 10
5 5
1 2
5 0 1000
8 800 555 35 35
5 0 10
3 2 5 4 7
3 2 5
4 3 2
1 2
2 3```

### 输出

```
24
7
0
480
5
8```

# 题解

## 作者：樱雪喵 (赞：12)

## Description

~~别问为什么粘翻译，问就是题面的翻译是本喵写的。~~

你在玩一个游戏，要完成 $n$ 个任务。其中对于每个任务 $i$，它只能在某一天的第 $h_i$ 时刻完成。游戏每天有 $k$ 个小时，分别编号为 $0,1,...k-1$。

给出 $m$ 对任务间的依赖关系，$(a_i,b_i)$ 表示 $a_i$ 必须比 $b_i$ 先完成。保证依赖关系不形成环。

完成任务不需要时间，也就是说可以在同一天的同一时刻先后完成多个任务。

求完成所有任务所需的最短时间。这里的时间定义为：完成最后一个任务的时刻 与 开始第一个任务的时刻 之差。

多组数据，$T\le 10^5$，$\sum n,m\le 2\times 10^5$，$k\le 10^9$。

## Solution

假设我们知道每个任务开始做的时间。那么对于边 $(a,b)$，若 $h_a<h_b$，则他们在同一天完成；否则令 $b$ 在第二天的 $h_b$ 时刻完成。使用拓扑排序不难求出最后一个任务被完成的时刻。

同样假设所有没有限制的任务都从同一天开始做，这样并不一定是最优的，比如样例 3 就是反例。也就是说，最优方案是形如把一部分靠前时刻的东西挪到第二天开始做。

而被推迟的任务满足这样几条性质：

- 每个任务（包括非起点）最多只会推迟一天
- 被推迟的**起点任务**是 $h_i$ 的一个前缀

看起来似乎不难理解，所以证明留给读者自行解决。

至此，我们可以先假设它们都在同一天开始，求出答案；再按照 $h_i$ 递增的顺序将起点任务推迟。根据第一条性质，可以记录数组 $flag$ 表示那些点已经被推迟一天；而如果更新过程中遇到已经被推迟过的点，则不必继续更新。

综上，每个点最多只被更新了一次，时间复杂度 $O(n)$。


赛时写假了一发，所以代码很丑。

```cpp
#define int long long
const int N=2e5+5,inf=1e18;
int T,n,m,k;
struct node{
	int h,id;
}a[N];
bool cmp(node x,node y) {return x.h<y.h;}
int h[N],flag[N];
int in[N],s[N],t[N];
queue<int> q;
struct edge {int nxt,to;}e[N<<1];
int maxn,head[N],cnt;
il void add(int u,int v) {e[++cnt]={head[u],v};head[u]=cnt;}
int U[N],V[N];
int topo(int st)
{
	for(int i=1;i<=n;i++) in[i]=0,t[i]=0;
	for(int i=1;i<=m;i++) in[V[i]]++;
	for(int i=1;i<=n;i++)
	{
		if(in[i]) continue;
		if(h[i]<st) t[i]=k+h[i]-st;
		else t[i]=h[i]-st;
		q.push(i);
	}
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to; in[v]--;
			int qwq=0;
			if(h[v]>=h[u]) qwq=t[u]+h[v]-h[u];
			else qwq=t[u]+k+h[v]-h[u];
			t[v]=max(t[v],qwq);
			if(!in[v]) q.push(v);
		}
	}
	int res=0;
	for(int i=1;i<=n;i++) res=max(res,t[i]);
	maxn=res;
	return res;
}
void upd(int st)
{
	flag[st]=1; t[st]+=k;
	q.push(st);
	while(!q.empty())
	{
		int u=q.front(); q.pop(); maxn=max(maxn,t[u]);
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to; if(flag[v]) continue;
			int qwq=0;
			if(h[v]>=h[u]) qwq=t[u]+h[v]-h[u];
			else qwq=t[u]+k+h[v]-h[u];
			if(t[v]<qwq)
			{
				flag[v]=1,t[v]=qwq;q.push(v);
			}
		}
	}
}
signed main()
{
	T=read();
	while(T--)
	{
		n=read(),m=read(),k=read(); maxn=0;
		for(int i=1;i<=n;i++) h[i]=read(),flag[i]=0,in[i]=0;
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++) head[i]=0; cnt=0;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			U[i]=u,V[i]=v; in[v]++;
			add(u,v);
		}
		int tot=0;
		for(int i=1;i<=n;i++) if(!in[i]) a[++tot]={h[i],i};
		sort(a+1,a+tot+1,cmp);
		int ans=topo(0)-a[1].h;
		for(int i=1;i<tot;i++)
		{
			upd(a[i].id);
			ans=min(ans,maxn-a[i+1].h);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：mRXxy0o0 (赞：3)

# 题意

给出具有依赖关系的 $n$ 个任务，每个任务只能在某一天的第 $h_i$ 小时做。只要满足了依赖关系，一个小时可以做很多任务。求最小的完成时间。

# 分析

结合题目条件，很快发现这是一个有多个联通块的 DAG。

拆分一下问题，先考虑怎么求单个联通块的所有开始时间和结束时间，然后再合并起来。

对于结束时间，发现可以通过简单的 DP 得到。需要注意的是，要保证后做的任务时间大于等于先做的，为了达到这一点，每次增加的只会是整天的时间。

对于开始时间，可以对所有入度为零的点取 $\max$。

显然，如果把某些联通块的开始结束时间整体后推一天是有可能取到更优的值的。而且，一个块最多被推后一天。

所以就考虑枚举一个一天中的开始时间，并把小于的块开始结束时间整体后移。

但是，这样还是有问题的（WA 无数次的惨痛教训）。因为如果在某个块里还有一个更晚的开始时间，有可能结束时间根本就不会变动；更为恶心的是，由于这是一个 DAG，所以会有多个出度为零的点，它们当中可能有些点增加了，而另一些没有变动。

观察最初算时间的 DAG 上 DP 过程，发现如果一个入度非零的点 $u$ 需要增加一天，前提是它的前驱 $l$ 满足 $f_l+k>f_u$。

因此，再细分一下，对于每一个出度为 $0$ 的点 $i$，都去维护一个 $st_i$，表示会使 $i$ 增加一天的入度为 $0$ 的点中最小的开始时间，可以简单证明一定有这样的点。这样一来就可以按照前面的思路正确讨论了。

一个实现上的小细节：求 $st$ 数组的过程中可以在反图上进行记忆化搜索，很明显这是可以递推。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=2e5+10;
const ll inf=1e18;
int n,m,rd[N],tot;
ll f[N],k,suf[N],mn[N];
vector<int>G[N],G1[N];
struct node{
	ll x,y;
}b[N];
inline bool cmp(node x,node y){
	return x.x<y.x;
}
inline ll dfs(int u){
	if(mn[u]<inf) return mn[u];
	if(!G1[u].size()) return mn[u]=f[u];
	for(int v:G1[u]){
		if(f[u]-f[v]<k) mn[u]=min(mn[u],dfs(v));
	}
	return mn[u];
}
inline void topsort(){
	queue<int>q;
	for(int i=1;i<=n;++i){
		if(!rd[i]){
			q.push(i);
		}
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int v:G[u]){
			--rd[v];
			if(!rd[v]) q.push(v);
			if(f[u]>f[v]){
				f[v]+=(f[u]-f[v]+k-1)/k*k;
			}
		}
	}
	for(int i=1;i<=n;++i){
		if(G[i].empty()){
			b[++tot]={dfs(i),f[i]};
		}
	}
}
int main(){
	memset(mn,0x3f,sizeof mn);
	int T;
	scanf("%d",&T);
	while(T--){
		tot=0;
		scanf("%d%d%lld",&n,&m,&k);
		for(int i=1;i<=n;++i){
			scanf("%lld",&f[i]);
		}
		for(int i=1,x,y;i<=m;++i){
			scanf("%d%d",&x,&y);
			++rd[y];
			G[x].push_back(y);
			G1[y].push_back(x);
		}
		topsort();
		sort(b+1,b+1+tot,cmp);
		for(int i=tot;i>=1;--i){
			suf[i]=max(suf[i+1],b[i].y);
		}
		ll mx=0,ans=9e18;
		int j=1;
		for(int i=1;i<=tot;){
			while(j<i){
				mx=max(mx,b[j].y+k);
				++j;
			}
			ans=min(ans,max(suf[i],mx)-b[i].x);
			int tmp=b[i].x;
			while(i<=tot&&b[i].x==tmp) ++i;
		}
		printf("%lld\n",ans);
		for(int i=1;i<=n;++i){
			G[i].clear();
			G1[i].clear();
			rd[i]=suf[i]=0;
			mn[i]=inf;
		}
	}
	return 0;
}
```


---

## 作者：SunsetLake (赞：3)

[CF1863E](https://www.luogu.com.cn/problem/CF1863E)

参考[这篇博客](https://www.luogu.com.cn/blog/chenjunxiu/speedrun)，本题解作为我的学习笔记。

# 思路

首先观察到提上说的依赖关系，容易联想到建出一张有向无环图。因为 $a_i$ 要比 $b_i$ 先完成，所以从 $a_i$ 向 $b_i$ 连一条边。而任务必须从入度为零的点开始依次往下做，因此想到拓扑排序（~~但题目给的就是拓扑序？~~）。每次取入度为零的点进行扩展。

以下的图都是拓扑排序后的有向无环图。

一个比较显然的想法是：设 $dp_v$ 表示到 $v$ 这个节点时完成任务的最小时间是多少。每次就从连向 $v$ 的点（设其为 $u$）进行转移，如果 $h_v$ 比 $dp_u$ 还小，那就说明 $v$ 必须向后推迟若干天使它大于现在 $u$ 的天数。答案就是最大 $dp$ 值减去最小 $dp$ 值。

但是样例 $4$ 就 hack 掉了这个做法。为什么呢？我们可以注意到：开始时间是可以我们自己来定的，也就是说可能有些点推迟一些开始会更优。而推迟的点只可能是入度为零的点，因为如果不推迟他们而去推迟他们的后继，只会使答案越来越大。那我们就可以考虑把每个入度为零的点都推迟一天后再进行拓扑排序，但是时间复杂度接受不了。

不过我们可以发现：假如一个点 $u$ 被往后推迟了一天，被影响的点只会是这个点在图中的所有后继。因为他变大之前他的前驱的值 $dp_{pre_u}$ 就会比 $dp_u$ 的值小，他变大之后也一定满足。所以我们只需要考虑 $u$ 的后继被影响后能变到的最大值。

因为我们主要考虑后推的天数，因此换一种状态。设 $dp_v$ 表示 $v$ 这个点最少被推迟多少天。先将每个点原始的 $dp$ 值都递推出来。

再记一个 $mx_u$ 表示 $u$ 推迟一天后 $u$ 以及 $next_u$ 被影响后的最大值。有：

$mx_u=\max \{(dp_u+1)k+h_u,\max \{mx_v \times [dp_u+1+[h_u>h_v]>dp_v] \} \}$

其中 $v \in next_u$，$[]$ 是艾弗森括号。

$dp_u+1$ 就是 $u$ 推迟后的天数，如果满足 $h_u>h_v$，则 $v$ 需要再往后推迟一天。因此 $dp_v=\max \{dp_u+1+[h_u>h_v]\}$。如果 $dp_v$ 能被更新到，则 $mx_u$ 可以从 $mx_v$ 转移来，因为此时的 $dp_v$ 值变大，进而影响到所有的 $dp_{next_v}$，使 $mx_v$ 变大。

于是我们可以通过记忆化搜索来实现这一过程。

```cpp
ll dfs(int u){
	if(mx[u]!=-1)return mx[u];
	mx[u]=(dp[u]+1)*k+h[u];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(dp[u]+1+(h[u]>h[v])>dp[v])mx[u]=max(mx[u],dfs(v));
	}
	return mx[u];
}
```
最后就是统计答案了。我们需要记录一个 $res$ 表示当前最后一个任务完成的时刻。

首先考虑开始时间就是入度为零的点中最小的 $h_i$，此时 $res$ 就是原始 $dp$ 数组的 $\max \{dp_i \times k+h[i] \}$。

接着考虑把某些入度为零的点推迟后的 $res$ 如何计算。我们可以把这些点按照他们的 $h_i$ 从小到大排序得到 $b$ 数组，于是：

```cpp
ans=min(ans,res-h[b[i]]);
res=max(res,mx[b[i]]);
```
因为 $b$ 是从小到大排的,所以我们可以把每个 $h[b[i]]$ 当做开始时间，而在它前面的点 $h$ 值都比他小，因此他们都必须推迟一天后再开始任务，所以 $res$ 要更新为这些点推迟后的 $mx$ 值的最大值。动态更新就能求出答案了。

# 代码

[评测记录](https://codeforces.com/contest/1863/submission/222064470)


---

## 作者：cosf (赞：2)

## [CF1863E](https://codeforces.com/contest/1863/problem/E) [速通](https://www.luogu.com.cn/problem/CF1863E)

## 简要题意

在一个一天有 $k$ 个小时的世界里，有 $n$ 种任务需要完成，第 $i$ 种任务只能在每一天的第 $h_i$ 个小时完成。

这里还有 $m$ 个形如 $(a_i, b_i)$ 的限制（没有环形限制），意为想完成 $b_i$ 必须先完成 $a_i$。当然，每一个任务所需的时间等于 $0$，意思就是说每一个时刻可以完成存在限制关系的多个任务。

问：至少需要多久（小时）玩完所有任务？

## 分析

我们按照限制建图，可以得到一个 DAG。那么，我们可以用拓扑排序。这里可以维护一个序列 $s_i$，意为：

对于任务 $i$，从它被完成到所有被它限制或间接限制的任务都被完成的时间。

这个定义比较复杂，可以通过递推式来更加直观的判断。

令 $dif(a, b) = (a + k - b) \bmod k, T_i = \{\texttt{games which is directly constrained by the i-th game}\}$。（ $t_i$ 为直接限制的任务）

则有

$$
s_i = \begin{cases}
0 & T_i = \varnothing\\
\max_{j \in T_i}s_j + dif(h_j, h_i) & \operatorname{otherwise}
\end{cases}
$$

在整个拓扑网中，我们令入度为 $0$ 的节点集为 $O$。这些节点所代表的任务互相之间没有任何限制。

假设 $|O| = 1$，那么答案显然是 $O$ 中唯一元素的 $s$。因为，它的 $s$ 一定是所有节点中最大的（所有节点都被它指向了）。

但是，如果 $|O| \not=1$，那么我们就需要判断以 $O$ 中哪一个任务为起点。

注意，以上部分为 $O(n + m)$，以下为 $O(n\log n)$。

我们假定 $O = \{O_1, O_2, \dots, O_{cnt}\}$，并且有 $h_{O_1} \le h_{O_2} \le \dots \le h_{O_{cnt}}$。

此时，若选 $h_{o_i}$ 为起点的话，答案就是

$$
\max_{j \in O} s_j + dif(h_j - h_{O_i})
$$

注意到 $\{s_j + dif(h_j - h_{O_i}) | j \in O\}$ 这个集合是很好转移的（将 $i + 1$ 或 $- 1$）：它们的相对差是不变的，除了 $j = O_i$ 的那一项有所变化。那么，我们可以用 multiset 来维护它，再记录一下整体的偏移。

一些具体的步骤在代码注释里面。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

#define MAXN 200005
#define int long long

// 这里的变量名和上面有所不同

struct Edge
{
    int t, n;
} e[MAXN];
int h[MAXN]; // 建图（注意是反向的）

int d[MAXN]; // 反向图的入度
int o[MAXN]; // 正向图的入度（o[i] = 0 表示 i 在上文中的 O 集合中）
int cnt = 0; // 变量名重了，不过没事。

void add(int f, int t)
{
    e[++cnt] = {t, h[f]};
    h[f] = cnt;
    d[t]++;
    o[f]++;
}

int v[MAXN]; // 题目中的 h
int s[MAXN]; // 分析中的 s

int nds[MAXN]; // 真正的集合 o
int ins[MAXN]; // 当 s_j + dif(h_j, h_o_i) 第一次加入 multiset 时的值。

bool cmp(int a, int b) // 排序比较器。先按时间，再按 s
{
    return v[a] == v[b] ? s[a] < s[b] : v[a] < v[b];
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++)
        {
            cin >> v[i];
            h[i] = 0;
            d[i] = 0;
            o[i] = 0;
            s[i] = 0; // 记得清零
        }
        cnt = 0;
        for (int i = 1; i <= m; i++)
        {
            int a, b;
            cin >> a >> b;
            add(b, a); // 反向建边
        }
        queue<int> q; // 拓扑板子
        for (int i = 1; i <= n; i++)
        {
            if (d[i] == 0)
            {
                q.push(i);
            }
        }
        while (!q.empty())
        {
            int c = q.front();
            q.pop();
            for (int i = h[c]; i; i = e[i].n)
            {
                s[e[i].t] = max(s[e[i].t], s[c] + (k + v[c] - v[e[i].t]) % k);
                d[e[i].t]--;
                if (d[e[i].t] == 0)
                {
                    q.push(e[i].t);
                }
            }
        }
        multiset<int, greater<int>> st;
        int cnt = 0;
        for (int i = 1; i <= n; i++) // 计算 o 集合。这里的 cnt 是集合大小
        {
            if (o[i] == 0)
            {
                nds[++cnt] = i;
                ins[cnt] = 0;
            }
        }
        sort(nds + 1, nds + cnt + 1, cmp);
        if (cnt == 1) // 特判
        {
            cout << s[nds[cnt]] << endl;
            continue;
        }

        /*
         * 重点！！！
         *
         * 这里假定先以 o_cnt 作为起点
         * 然后再往前转移
         */
        st.insert(s[nds[cnt]]);
        int pls = v[nds[1]] + k - v[nds[cnt]];
        st.insert(ins[1] = s[nds[1]] + pls); // 这里的 pls 就是 dif，只不过以更方便的形式转移而已
        for (int i = 2; i < cnt; i++)
        {
            pls += v[nds[i]] - v[nds[i - 1]];
            st.insert(ins[i] = s[nds[i]] + pls); // 记录 ins
        }

        /*
         * 这里的 out 为输出
         * 这里的 pls 是整体的偏移
         */
        int out = *st.begin();
        pls = 0;
        for (int i = cnt - 1; i; i--)
        {
            pls += v[nds[i + 1]] - v[nds[i]]; // 记录偏移
            st.erase(st.find(ins[i])); // 注意不能直接 erase(ins[i])，那样会把所有一样的都删掉
            st.insert(ins[i] - k); // 在前一天就可以玩了，所以减 k
            out = min(out, *st.begin() + pls); // 记得 + pls
        }
        cout << out << endl;
    }
    return 0;
}

```

---

## 最后附上样例的解释

注意，给的图是拓扑网。

后面标了 `o` 的属于集合 $O$。带引号的边权是 $O$ 之间的 $dif$。

### 样例 1

![样例 1](https://cdn.luogu.com.cn/upload/image_hosting/0cgo3avr.png)

### 样例 3

![样例 3](https://cdn.luogu.com.cn/upload/image_hosting/wgywnww1.png)

### 样例 5

![样例 5](https://cdn.luogu.com.cn/upload/image_hosting/uagvvvnk.png)


---

## 作者：hanjinghao (赞：2)

# 思路

看到先后顺序的限制，先考虑拓扑排序（使用优先队列，以时间为第一关键字，编号为第二关键字），求出最长路，然后用最大值减去最小值。

然而，这不一定是最优解——把一些原本在第一天完成的任务延迟到第二天，可能会更优（比如样例中的第四组询问）。因此，我们需要计算把任务从第一天延迟到第二天给答案带来的影响。

考虑建出“最长路树”——如果 $ y $ 的结果是从 $ x $ 转移过来的，那么我们称 $ y $ 出发能到达的那些点都是被 $ x $ 支配的。如果 $ x $ 延迟了一天，那么被 $ x $ 支配的点也会延迟一天。

按时间顺序把每个点依次延迟一天，动态维护当前最早和最晚的时刻即可。

时间复杂度 $ O((n + m) \log n) $。

# 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

template < typename T >
inline void read(T &x)
{
	x = 0;
	bool flg = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline void writesp(T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline void writeln(T x)
{
	write(x);
	putchar(10);
}

const int N = 2e5 + 5;
int h[N], d[N], day[N], a[N];
ll tim[N], mxn[N];
vector < int > G[N];
priority_queue < pair < pair < int, int >, int >, vector < pair < pair < int, int >, int > >, greater < pair < pair < int, int >, int > > > q;

template < typename T >
inline void Chkmax(T &x, T y)
{
	if (y > x) x = y;
}

template < typename T >
inline void Chkmin(T &x, T y)
{
	if (y < x) x = y;
}

inline bool cmp(const int &x, const int &y)
{
	return tim[x] < tim[y];
}

void dfs(int x)
{
	mxn[x] = tim[x];
	for (auto &i : G[x])
		if (h[i] < h[x] && day[i] == day[x] + 1 || h[i] >= h[x] && day[i] == day[x]) 
		{
			if (mxn[i] == -1) dfs(i);
			Chkmax(mxn[x], mxn[i]);
		}
}

int main()
{
	int T;
	read(T);
	while (T--)
	{
		int n, m, k;
		read(n);
		read(m);
		read(k);
		for (int i = 1; i <= n; ++i)
		{
			read(h[i]);
			d[i] = 0;
			day[i] = 0;
			G[i].clear();
		}
		for (int i = 1; i <= m; ++i)
		{
			int x, y;
			read(x);
			read(y);
			G[x].emplace_back(y);
			++d[y];
		}
		for (int i = 1; i <= n; ++i)
			if (!d[i]) q.emplace(make_pair(0, h[i]), i);
		while (q.size())
		{
			pair < pair < int, int >, int > Top = q.top();
			q.pop();
			for (auto &i : G[Top.second])
			{
				if (h[i] < h[Top.second]) Chkmax(day[i], day[Top.second] + 1);
				else Chkmax(day[i], day[Top.second]);
				--d[i];
				if (!d[i]) q.emplace(make_pair(day[i], h[i]), i);
			}
		}
		ll maxn = 0, minn = LONG_LONG_MAX;
		for (int i = 1; i <= n; ++i)
		{
			tim[i] = (ll)k * day[i] + h[i];
			Chkmax(maxn, tim[i]);
			Chkmin(minn, tim[i]);
			mxn[i] = -1;
			a[i] = i;
		}
		ll ans = maxn - minn;
		for (int i = 1; i <= n; ++i)
			if (mxn[i] == -1) dfs(i);
		sort(a + 1, a + n + 1, cmp);
		for (int i = 1; i < n && tim[a[i + 1]] < k; ++i)
		{
			minn = tim[a[i + 1]];
			Chkmax(maxn, mxn[a[i]] + k);
			Chkmin(ans, maxn - minn);
		}
		writeln(ans);
	}
	return 0;
}
```

---

## 作者：jifbt (赞：1)

首先容易想到这样一种做法：对于每个没有入度的任务（称为初始任务），我们先假设它们都在第一天完成，用拓扑排序（这里由于总是从编号小的任务连向大的，也可以不用）算出答案。接下来，按照时间从早到晚的顺序，我们把这些任务依次推迟到第二天完成，更新所有会因此被推迟的任务的完成时间，并更新答案。每个任务最多被更新一次，因此时间复杂度为 $O(n\log n+m)$。这个做法已经可以通过本题，但是如果实现得不好，可能会很麻烦。

事实上，在拓扑排序时，我们就可以知道某个任务会在何时被推迟。当某个初始任务被推迟到第二天时，对于所有完成时间随之发生变化的任务，我们定义它们的「祖先」（$\mathrm{anc}_u$）为这个初始任务。对于非初始任务 $u$，它被推迟，只可能是因为某个前驱任务被推迟，进而影响到它，因此有 $\mathrm{anc}_u\in\{\mathrm{anc}_v\mid(v,u)\in G\}$。记其完成时间为 $\mathrm{ans}_u$，则 $\mathrm{ans}_u-k<\mathrm{ans}_v$ 时，$v$ 被推迟才可能导致 $u$ 被推迟，因此可以得到 $\mathrm{anc}_u\in\{\mathrm{anc}_v\mid(v,u)\in G,\mathrm{ans}_u+k<\mathrm{ans}_v\}$。如果只推迟该集合中的任意一个初始任务，都可以导致 $u$ 被推迟，因此 $u$ 的祖先为其中最早被推迟的，也就是完成时间最早的那个。

这样对于每个初始任务，我们可以得到以该它为「祖先」的任务中，最早和最晚的完成时间。在推迟某个初始任务时，只需把这两个值都加上 $k$，并更新答案即可。按照时间从早到晚的顺序，依次推迟每个初始任务，时间复杂度仍为 $O(n\log n+m)$，但实现得会较简单一些。以下是代码（变量名与公式中的有差异）：

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> void rd(T &x) {
    x = 0;
    int f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - 48;
        c = getchar();
    }
    x *= f;
}
template <typename T, typename... T2> void rd(T &x, T2 &...y) {
    rd(x), rd(y...);
}

using ll = long long;
const int Nmax = 2e5 + 5, Mmax = Nmax;
int t, n, m, k, h[Nmax];
vector<int> e[Nmax], re[Nmax];
int deg[Nmax];
ll tim[Nmax];
queue<int> q;
int fa[Nmax], clr[Nmax], cnt;
ll mx, ans;

struct Rng {
    ll mn, mx;
    bool operator<(const Rng &o) { return mn < o.mn; }
} rng[Nmax];

inline ll f(ll x, int y) { return (x - y + k - 1) / k * k + y; }
template <typename T> void max_eq(T &u, const T &v) { u = max(u, v); }

int main() {
    rd(t);
    while (t--) {
        rd(n, m, k);
        for (int i = 1; i <= n; ++i)
            rd(h[i]);
        for (int i = 1; i <= m; ++i) {
            int u, v;
            rd(u, v);
            e[u].push_back(v);
            re[v].push_back(u);
            ++deg[v];
        }
        for (int i = 1; i <= n; ++i)
            if (!deg[i]) q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            tim[u] = f(tim[u], h[u]);
            for (int v : re[u]) {
                if (f(tim[v], h[u]) == tim[u] &&
                    (!fa[u] || rng[clr[v]].mn < rng[clr[fa[u]]].mn))
                    fa[u] = v;
            }
            if (fa[u])
                clr[u] = clr[fa[u]];
            else {
                assert(re[u].empty());
                clr[u] = ++cnt;
                rng[cnt].mn = tim[u];
            }
            max_eq(rng[clr[u]].mx, tim[u]);
            max_eq(mx, tim[u]);
            for (int v : e[u]) {
                max_eq(tim[v], tim[u]);
                if (!--deg[v]) q.push(v);
            }
        }
        sort(rng + 1, rng + cnt + 1);
        ans = 1e18;
        for (int i = 1; i <= cnt; ++i) {
            ans = min(ans, mx - rng[i].mn);
            max_eq(mx, rng[i].mx + k);
        }
        printf("%lld\n", ans);
        for (int i = 1; i <= n; ++i) {
            e[i].clear();
            re[i].clear();
        }
        memset(deg, 0, (n + 1) * sizeof *deg);
        memset(tim, 0, (n + 1) * sizeof *tim);
        memset(fa, 0, (n + 1) * sizeof *fa);
        memset(rng, 0, (n + 1) * sizeof *rng);
        cnt = mx = 0;
    }
}
```

---

## 作者：luckydrawbox (赞：1)

又是一道赛后两分钟敲完的题。

[$\text{Link}$](https://codeforces.com/contest/1863/problem/E)

## 题意

你有 $n$ 个任务，第 $i$ 个任务完成的时间可以设定为 $xk+h_i(x\in[0,\infty))$，同时有 $m$ 个限制，要求第 $a_i$ 个任务完成的时间不超过第 $b_i$ 个任务完成的时间，且这种单向关系不会形成环（保证 $a_i<b_i$）。

求完成时间最晚与最早的任务的时间差的最小值。

## 分析

把题中的 $m$ 条限制当做有向边，那么这就是个有向无环图。

有一个贪心的想法是让每个任务完成的时间尽量靠前，于是我们可以在 $\text{DAG}$ 上 $\text{dp}$，记 $dep_u$ 表示第 $u$ 个任务的系数 $x$ 的最小值，那么对于 $v$ 的每条入边 $u\rightarrow v$，有：

$$dep_v=\max_{u\rightarrow v\in E}\{dep_u+[h_u>h_v]\}$$

答案为 $\max_{i=1}^n\{dep_ik+h_i\}-\min_{i=1}^n\{dep_ik+h_i\}$。

但是这样是错的，样例告诉我们，可以通过把完成时间最小的几个点的 $dep$ 值 $+1$ 来减小答案。显然，选择 $+1$ 的点只可能是入度为 $0$ 的点，选择其他点只会得不偿失，于是可以枚举选择的断点，改变那几个点的初始 $dep$，再重新拓扑排序。

可这样的时间复杂度仍高达 $O(n^2)$，考虑优化。可以发现，先选择一个点后，产生的变化都形如“如果 $dep_i$ 可以 $+1$，那么它对 $i$ 在 $\text{DAG}$ 上的后继以及本身影响后的最大值”，故我们将该值设为 $ch_i$，有：

$$ch_u=\max\{(dep_u+1)k+h_u,\max_{u\rightarrow v\in E}\{ch_v\times[dep_u+[h_u>h_v]+1>dep_v]\}\}$$

于是 $ch$ 可以通过记忆化搜索求出，最终可求出答案。

## 代码

~~虽然题目给的就是拓扑序，但我还是用了拓扑排序~~

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch))
	{if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=2e5+10;
int t,n,m,k;
ll h[N],dep[N];
int head[N],ver[N],nxt[N],tot,in[N];
void add(int x,int y){
	ver[++tot]=y;nxt[tot]=head[x];head[x]=tot;in[y]++;
}
queue<int>q;
void topu(){
	while(q.size())q.pop();
	for(int i=1;i<=n;i++){
		if(!in[i])
			q.push(i),dep[i]=0;
	}
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i];
			dep[y]=max(dep[y],dep[x]+(h[x]>h[y]));
			in[y]--;
			if(!in[y])
				q.push(y);
		}
	}
}
int a[N],top;
ll ch[N];
bool cmp(int x,int y){
	return h[x]<h[y];
}
ll dfs(int x){
	if(ch[x]!=-1)return ch[x];
	ch[x]=(dep[x]+1)*k+h[x];
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(dep[x]+(h[x]>h[y])+1>dep[y])
			ch[x]=max(ch[x],dfs(y));
	}
	return ch[x];
}
int main(){
	t=read();
	while(t--){
		n=read();m=read();k=read();
		for(int i=1;i<=n;i++){
			h[i]=read();in[i]=head[i]=dep[i]=0;
			ch[i]=-1;
		}
		tot=top=0;
		for(int i=1;i<=m;i++){
			int x=read(),y=read();
			add(x,y);
		}
		for(int i=1;i<=n;i++)
			if(!in[i])a[++top]=i;
		sort(a+1,a+top+1,cmp);
		topu();
		ll mx=0,ans=1e18;
		for(int i=1;i<=n;i++)
			mx=max(mx,dep[i]*k+h[i]);
		for(int i=1;i<=n;i++)dfs(i);
		for(int i=1;i<=top;i++){
			ans=min(ans,mx-h[a[i]]);
			mx=max(mx,ch[a[i]]);
		}
		write(ans);puts("");
	}
	return 0;
}
```


---

## 作者：Kedit2007 (赞：1)

### 思路

定义初始时没有任何前置任务的任务为**初始任务**，定义第一个完成的任务为**起始点**，显然起始点一定是一个初始任务。当选定一个初始任务作为起始点时，我们可以贪心地计算出所有任务做完需要的时间。

具体地，定义 $f(x) = nk$，其中 $n$ 是最大的使 $nk \le x$ 的整数，假设一个任务的所有前置任务中最晚完成的时间是 $t$，且这个任务需要在 $h$ 时完成，若 $t \bmod k \le h$，则其完成时间为 $f(t) + h$，否则，其完成时间则为 $f(t) + k + h$。按照这个过程，用类似拓扑排序的方式模拟，便可得到所有任务做完需要的时间。

但是，这样进行一次模拟的复杂度是 $O(n + m)$，如果要枚举每个初始任务进行模拟后取最小值，复杂度不能够接受。

考虑如何充分利用一次模拟得到的数据。如果从先到后选择一个个初始任务，我们可以发现每向后选择一个，就都有若干个（当然也可能没有）任务的完成时间被延后 $k$。而重要的是，每个任务**最多**被延后一次。这个结论很好证明，因为当我们将所有初始任务都遍历过一遍，就相当于把所有任务延后一天完成，在这种情况下，每个任务都被延后了 $k$。

那么利用这一点，我们先计算出以最早的初始任务为起始点的所有完成时间，接着按时间顺序遍历所有初始任务，将其完成时间延后 $k$，即模拟更换起始点的过程。遍历途中记录最小的答案，遍历结束后输出即可。由于上文每个任务最多延后一次的结论，这个过程也是 $O(n + m)$ 的。

总体时间复杂度还需要加上排序，为 $O(n \log n + n + m) = O(n \log n)$。

### 参考代码 

```cpp
void work()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> h(n), fin(n);
	for (int i = 0; i < n; i++)
	{
		cin >> h[i];
	}
	vector<vector<int>> nxt(n);
	vector<int> indeg(n);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--; v--;
		indeg[v]++;
		nxt[u].push_back(v);
	}
	map<int, vector<int>> roots;
	for (int i = 0; i < n; i++)
	{
		if (indeg[i] != 0) continue;
		roots[h[i]].push_back(i);
	}
	vector<int> pred(n);
	
	auto get_time = [&](int x, int pre)
	{
		int rem = pre % k;
		if (rem > h[x])
		{
			pre = pre - rem + k;
		}
		else
		{
			pre = pre - rem;
		}
		return pre + h[x];
	};
	
	auto process = [&](int x)
	{
		queue<int> q;
		q.push(x);
		while (!q.empty())
		{
			int cur = q.front();
			q.pop();
			int f = get_time(cur, pred[cur]);
			fin[cur] = f;
			for (const auto& node : nxt[cur])
			{
				indeg[node]--;
				pred[node] = max(pred[node], fin[cur]);
				if (indeg[node] == 0)
				{
					q.push(node);	
				}	
			}
		}
	};
	
	for (const auto& vec : roots)
	{
		for (const auto& root : vec.second)
		{
			process(root);
		}
	}
	
	int maxf = 0;
	
	for (const auto& f : fin)
	{
		maxf = max(maxf, f);
	}
	
	vector<bool> visited(n, false);
	
	auto update = [&](int x)
	{
		queue<int> q;
		q.push(x);
		visited[x] = true;
		while (!q.empty())
		{
			int cur = q.front();
			q.pop();
			fin[cur] += k;
			maxf = max(maxf, fin[cur]);
			for (const auto& node : nxt[cur])
			{
				if (visited[node] || get_time(node, fin[cur]) <= fin[node])	continue;
				visited[node] = true;
				q.push(node);
			}
		}	
	};
	
	int ans = numeric_limits<int>::max();
	
	for (const auto& p : roots)
	{
		ans = min(ans, maxf - p.first);
		for (const auto& root : p.second)
		{
			update(root);
		}
	}
	cout << ans << '\n';
}
```

---

## 作者：hfjh (赞：0)

# CF1863E. Speedrun

## 题意

给你一张 DAG，点 $n$ 个，边 $m$ 条，给你一个整数 $k$ ，给你一个序列 $a$。

你需要给点赋值，使得点权 $v_i \equiv a_i \pmod k$，并且若有边 $(x,y)$ ，需满足 $v_x \le v_y$。

最小化 $\max_{i=1}^n v_i - \min_{i=1}^n v_i$ 。

## 题解

首先拓扑一遍会得到一个相对优秀的解，但以下情况会不优秀。

> 两个点，没有边，$a = <1,9>, k = 10$ ，按照拓扑答案是 8，但更优秀的是 $v = <11,9>$ 答案是 2。 

也就是我们让最小值变大一点。

设拓扑后的点权为 $f_i$，我们发现在这种情况里面每个点的点权最多为 $f_i + k$。

并且如果要 $+k$，一定是从拓扑中的起点（度数为 0 的点） $+k$。

> 因为某个点 $+k$ 后，影响的是这个点可以 dfs 到的点，我们要让最小值变大，一定是从起点开始，这样可以影响的点最多。

然后把所有起点按照 $f_i$ 排序，从小到大 dfs/bfs 一次。

> 改变 $f_i$ 必须要把 $<f_i$ 全部更改，不然最小值没有改变。

遇到不需要更改的就 `return`。

> 因为当前没有更改，之后的也不可能更改。

## 代码
```cpp

#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 2e5 + 10;
int t, n, m, tot, x, y, head[N], d[N];
int fd[N], w, vis[N], pos;
ll v[N], mx, k, f[N], ans, mi;
queue<int>q;
struct node{
	int next, to;
}edge[N]; 
struct Node{
	int id;
	ll v;
	bool operator <(const Node &a)const{
		return v < a.v; 
	}
};
vector<Node>p;
void add(int x, int y){
	++tot;
	edge[tot].next = head[x];
	edge[tot].to = y;
	head[x] = tot;
}
void input(){
	cin>> n >> m >> k;
	for(int i = 1; i <= n; ++i) cin >> v[i]; 
	for(int i = 1; i <= m; ++i) cin >> x >> y, add(x, y), ++d[y];
}
void pre(){
	for(int i = 1; i <= n; ++i) fd[i] = d[i], f[i] = v[i];
	for(int i = 1; i <= n; ++i) if(!fd[i]) q.push(i);
	while(!q.empty()){
		x = q.front();
		q.pop();
		for(int i = head[x]; i; i = edge[i].next){
			y = edge[i].to;
			if(f[y] < f[x]) f[y] += (f[x] - f[y] + k - 1) / k * k;
			--fd[y];
			if(!fd[y]) q.push(y); 
		}
	}
	for(int i = 1; i <= n; ++i){
		mx = max(mx, f[i]);
		if(d[i] == 0)p.push_back({i, f[i]});
	}
	
}
void dfs(int x){
	mx = max(mx, f[x]);
	for(int i = head[x]; i; i = edge[i].next){
		int y = edge[i].to;
		if(f[x] > f[y]) f[y] += k, dfs(y); 
	}
}
void op(){
	sort(p.begin(), p.end());
	ans = min(ans, mx - p[0].v);
	 
	for(int i = 0; i < p.size() - 1; ++i){
		f[p[i].id] += k;
		dfs(p[i].id);
		ans = min(ans, mx - p[i + 1].v);
	}
}
void qk(){
	for(int i = 1; i <= n; ++i) head[i] = d[i] = vis[i] = 0;
	p.clear();
	mx = w = tot = 0;
	ans = mi = 1e18;
	
}
int main(){
	cin.tie(0)->sync_with_stdio(false);
	cin>>t;
	while(t--){
		qk();
		input();
		pre();
		op();
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：falling_cloud (赞：0)

开始时直接按照题意尝试去算小时数时可能会无从下手，所以可以先把整个问题分为两个部分：求出需要经过的天数 $x$，找到第一天的开始时间 $s$ 和最后一天的结束时间 $t$，使得 $t-s$ 最小。

显然对于一个从属关系 $a_i,b_i$，当 $h_{a_i} \leq h_{b_i}$ 时可以在同一天内完成，否则只能在次日完成，那么可以建图，在第一种情况下连 $0$ 边，另一种情况下连 $1$ 边，就可以用优先队列 bfs 的方式来求出每个点**最早**可以再那一天完成。

接下来可以发现，在起始时间 $s$ 增加的情况下，结束时间一定不会变小。因为会有一些点至多被延迟完成一天而不会出现提前完成的结果（这点可以画图理解）。所以考虑将入度为 $0$ 的点排序，然后以此枚举开始时间。

接下来考虑哪些点会被延时，显而易见的是，入度为 $0$ 的点中比开始时间早的点会被延时一天，那么可以从被延时的点开始 dfs 来找出其他被延时的点，这是因为只有被延时过的点才会带来改变。由因为这个过程中结束时间 $t$ 单调不降，所以可以很容易的维护所有点中的最晚完成时间 $t$。

实现细节见代码，~~个人认为代码难度大于思维难度~~。

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define PD if(flag) cout<<"Yes"<<endl; else cout<<"No"<<endl
using namespace std;
const int N = 1e6 + 5;
struct pi{int v,type;};
struct ki{int pos,val;bool operator >(const ki &x) const {return val>x.val;}};
priority_queue <ki,vector<ki>,greater<ki> > q;
vector <pi> vec[N];
int a[N],sum[N],dp[N],ans,cl,k,tMax;
ki st[N];
bool vi[N];
bool cmp(ki x,ki y){return x.val<y.val;}
void dfs(int pos)
{
	if(vi[pos])	return ;
	vi[pos]=true;
	tMax=max(tMax,(dp[pos]+1)*k+a[pos]);
	for(int i=0;i<vec[pos].size();i++)
		if(dp[pos]+1+vec[pos][i].type>dp[vec[pos][i].v])
			dfs(vec[pos][i].v);
}
void solve()
{
	int n,m,i,j,l,r,x,y,tp=0,Max;
	ans=0;tMax=0;
	while(!q.empty())	q.pop(); 
	cin>>n>>m>>k;		
	for(i=1;i<=n;i++)	
	{
		cin>>a[i];
		vec[i].clear(),dp[i]=-1;
		vi[i]=false,sum[i]=0;
	}
	for(i=1;i<=m;i++)
	{
		cin>>x>>y;
		if(a[y]>=a[x])	vec[x].push_back((pi){y,0});
		else			vec[x].push_back((pi){y,1});
		sum[y]++;
	}
	for(i=1;i<=n;i++)	
	{
		if(sum[i]==0)	
		{
			q.push((ki){i,0}),dp[i]=0;
			st[++tp]=(ki){i,a[i]};
		}
	}
	sort(st+1,st+tp+1,cmp);
	while(!q.empty())
	{
		while(!q.empty())
		{
			if(vi[q.top().pos])	q.pop();
			else				break;
		}
		if(q.empty())	break; 
		int u=q.top().pos,val=q.top().val;
		vi[u]=true;
		q.pop();
		for(i=0;i<vec[u].size();i++)
		{
			sum[vec[u][i].v]--;
			if(dp[vec[u][i].v]<=val+vec[u][i].type)
				dp[vec[u][i].v]=val+vec[u][i].type;
			if(sum[vec[u][i].v]==0)
				q.push((ki){vec[u][i].v,dp[vec[u][i].v]});
		}	
	}
	for(i=1;i<=n;i++)	
	{
		ans=max(ans,dp[i]*k+a[i]-st[1].val),
		tMax=max(tMax,dp[i]*k+a[i]);
	}
	for(i=1;i<=n;i++)	vi[i]=false;
	for(i=2;i<=tp;i++)
	{
		cl=st[i].val;
		tMax=max(tMax,k+st[i-1].val);
		dfs(st[i-1].pos);
		ans=min(ans,tMax-cl);
	}
	cout<<ans<<endl;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);
	int Ti;
	for(cin>>Ti;Ti;Ti--)
		solve();
	return 0;
}

```

---

